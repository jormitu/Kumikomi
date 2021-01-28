#include <Arduino.h>
#include <Wire.h>
#include <I2CLiquidCrystal.h>

// デバイスアドレス(スレーブ)
uint8_t DEVICE_ADDRESS = 0x53; //SDO=GNDに接続した場合
I2CLiquidCrystal lcd(0x3c, (uint8_t)127);

// XYZレジスタ用のテーブル(6byte)
uint8_t RegTbl[6];

int LED = 13;
int buzzer = 12;
int x = 0;
volatile int state = 0; //グローバル変数として定義

void blink()
{
  if ((x % 2) == 1)
  {
    state = !state;
  }
  x++;
}

void setup()
{
  Serial.begin(9600);
  pinMode(LED, OUTPUT);     //LED
  pinMode(buzzer, OUTPUT);  //buzzer
  pinMode(7, INPUT_PULLUP); //タクトスイッチ(プルアップ)
  lcd.begin(16, 2);

  attachInterrupt(digitalPinToInterrupt(7), blink, CHANGE); //orattachInterrupt(4, blink, CHANGE);

  // マスタとしてI2Cバスに接続する
  Wire.begin();

  // DATA_FORMAT(データ形式の制御)
  Wire.beginTransmission(DEVICE_ADDRESS);
  // DATA_FORMATのアドレス
  Wire.write(0x31);
  // 「最大分解能モード」 及び 「±2g」 (0x08 == 1000)
  Wire.write(0x08);
  // 「10bit固定分解能モード」 及び　「±16g」にする場合 (0x03 == 0011)
  // Wire.write(0x03);
  Wire.endTransmission();

  // POWER_TCL(節電機能の制御)
  Wire.beginTransmission(DEVICE_ADDRESS);
  // POWER_CTLのアドレス
  Wire.write(0x2d);
  // 測定モードにする
  Wire.write(0x08);
  Wire.endTransmission();
}

void loop()
{
  digitalWrite(LED, state % 2); //LED表示
  noTone(buzzer);               //ブザーOFF
  //lcd.clear();              //lcdの表示を再起動

  // XYZの先頭アドレスに移動する
  Wire.beginTransmission(DEVICE_ADDRESS);
  Wire.write(0x32);
  Wire.endTransmission();

  // デバイスへ6byteのレジスタデータを要求する
  Wire.requestFrom(DEVICE_ADDRESS, 6);

  // 6byteのデータを取得する
  int i;
  for (i = 0; i < 6; i++)
  {
    while (Wire.available() == 0)
    {
    }
    RegTbl[i] = Wire.read();
  }

  // データを各XYZの値に変換する(LSB単位)
  int16_t x = (((int16_t)RegTbl[1]) << 8) | RegTbl[0];
  int16_t y = (((int16_t)RegTbl[3]) << 8) | RegTbl[2];
  int16_t z = (((int16_t)RegTbl[5]) << 8) | RegTbl[4];

  float x_theta = asin(x * 0.0041 / 1) * 180 / PI; //radian to degree
  float y_theta = asin(y * 0.0041 / 1) * 180 / PI;

  //角度が絶対値20度以上
  if (abs(x_theta) > 20 || abs(y_theta) > 20)
  {
    tone(buzzer, 262); // ドの音を鳴らす
  }

  //lcd表示
  lcd.setCursor(0, 0); //2行目0列にカーソル位置を指定
  lcd.print("x_deg=");
  lcd.print(x_theta);
  lcd.print("deg");
  lcd.setCursor(0, 1); //2行目1列目にカーソル位置を指定
  lcd.print("y_deg=");
  lcd.print(y_theta);
  lcd.print("deg");

  delay(100);
}
