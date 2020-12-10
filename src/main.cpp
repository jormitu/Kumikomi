#include <I2CLiquidCrystal.h>
#include <Wire.h>

I2CLiquidCrystal lcd(0x3c, (uint8_t)127);

int sensorPin = A0; //アナログ0番ピンを指定
int sensorValue = 0;

//アナログ入力値を摂氏度℃に変換
float modTemp(float analog_val)
{
  float v = 2.56;                                // 基準電圧値( V )
  float tempC = ((v * analog_val) / 1023) * 100; // 摂氏に換算
  return tempC;
}
void setup()
{
  //analogReference(INTERNAL);
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.println("hello,world!!");
}

void loop()
{
  //温度センサ読み取り
  // float sum = 0;
  // for (int i = 0; i < 10; i++)
  // {
  //   float val = analogRead(sensorPin);
  //   sum = sum + val;
  //   delay(100);
  // }

  // float T = sum / 10;
  // float temp = modTemp(T);

  lcd.setCursor(0, 1); //2行目一列にカーソル位置を指定
  lcd.print(millis() / 1000);

  // Serial.print("Analog");
  // Serial.print(T);
  // Serial.print("  ℃=");
  // Serial.println(temp);
}