#include <SPI.h>
#include <MsTimer2.h>

const byte digits[] = {
    // const ：定数 byte ：符号 なし 8 ビットデータ
    0b11111100, // 0
    0b01100000, // 1
    0b11011010, // 2
    0b11110010, // 3
    0b01100110, // 4
    0b10110110, // 5
    0b10111110, // 6
    0b11100000, // 7
    0b11111110, // 8
    0b11110110, // 9
    0b00000001, // DP
};

int latch = 10;
int Switch = 2;
int LED = 9;
int i, j = 0;
int state = 0;
int sensorPin = A0; //アナログ0番ピンを指定
int sensorValue = 0;

int n1 = 0;
int n01 = 0;

// 割り込み時に処理される関数
void flash()
{
  static boolean output = HIGH; // プログラム起動前に１回だけHIGH(1)で初期化される

  digitalWrite(LED, output); // 13番ピン(LED)に出力する(HIGH>ON LOW>OFF)
  output = !output;          // 現在のoutput内容を反転(HIGH→LOW/LOW→HIGH)させoutputにセットする
}

//アナログ入力値を摂氏度℃に変換
float modTemp(float analog_val)
{
  float v = 2.56;                                // 基準電圧値( V )
  float tempC = ((v * analog_val) / 1023) * 100; // 摂氏に換算
  return tempC;
}
void setup()
{
  analogReference(INTERNAL);
  Serial.begin(9600);
  pinMode(latch, OUTPUT); //CS(チップセレクト)SS(スレーブセレクト)
  pinMode(Switch, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  SPI.begin();
  SPI.setBitOrder(LSBFIRST);
  SPI.setDataMode(0);

  //00表示
  digitalWrite(latch, 0); //7segoff
  SPI.transfer(digits[0]);
  SPI.transfer(digits[0]);
  digitalWrite(latch, 1); //7segon

  MsTimer2::set(500, flash); // 500ms毎にflash( )割込み関数を呼び出す様に設定
  MsTimer2::start();         // タイマー割り込み開始
}

void loop()
{
  //温度センサ読み取り
  float sum = 0;
  for (int i = 0; i < 10; i++)
  {
    float val = analogRead(sensorPin);
    sum = sum + val;
    delay(100);
  }

  float T = sum / 10;
  float temp = modTemp(T);

  n1 = (int(10 * temp) % 100) / 10;
  n01 = (int(10 * temp) % 100) % 10;

  digitalWrite(latch, 0);       //7segoff
  SPI.transfer(digits[n1] + 1); //1の位(+1でDP表示付き)
  SPI.transfer(digits[n01]);    //0.1の位
  digitalWrite(latch, 1);       //7segon

  Serial.print("Analog");
  Serial.print(T);
  Serial.print("  ℃=");
  Serial.println(temp);
}
