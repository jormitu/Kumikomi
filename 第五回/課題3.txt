#include <Arduino.h>
#include <SPI.h>

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
int LED = 11;
int i, j = 0;
int state = 0;
int sensorPin = A0; //アナログ0番ピンを指定
int sensorValue = 0;

int a = 0;
int b = 0;

//アナログ入力値を摂氏度℃に変換
float modTemp(float analog_val)
{
  float v = 2.56;                                // 基準電圧値( V )
  float tempC = ((v * analog_val) / 1024) * 100; // 摂氏に換算
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
}

void loop()
{
  float sensor = analogRead(sensorPin);
  float temp = modTemp(sensor);

  a = (int)temp / 10;
  b = (int)temp % 10;

  digitalWrite(latch, 0);  //7segoff
  SPI.transfer(digits[a]); //10の位
  SPI.transfer(digits[b]); //1の位
  digitalWrite(latch, 1);  //7segon

  if (temp > 25)
  {
    digitalWrite(LED, HIGH);
  }
  else
  {
    digitalWrite(LED, LOW);
  }

  Serial.print("Analog");
  Serial.print(sensor);
  Serial.print("  ℃=");
  Serial.println(temp);
}