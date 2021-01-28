#include <Arduino.h>
#include <Wire.h>

// デバイスアドレス(スレーブ)
uint8_t DEVICE_ADDRESS = 0x53; //SDO=GNDに接続した場合

// XYZレジスタ用のテーブル(6byte)
uint8_t RegTbl[6];

int pin = 13;
volatile int state = LOW; //グローバル変数として定義

void blink()
{
  state = !state;
}
void setup()
{
  Serial.begin(9600);
  pinMode(pin, OUTPUT);
  pinMode(7, INPUT_PULLUP);
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
  digitalWrite(pin, state);
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

  // 各XYZ軸の加速度(m/s^2)を出力する
  Serial.print("X : ");
  Serial.print(x * 0.0041); //4.1/1000*9.80665
  Serial.print(" Y : ");
  Serial.print(y * 0.0041);
  Serial.print(" Z : ");
  Serial.print((z * 0.0041 + 0.02));
  Serial.println("g");

  delay(100);
}
