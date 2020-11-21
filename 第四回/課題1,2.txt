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
void setup()
{
  pinMode(latch, OUTPUT); //CS(チップセレクト)SS(スレーブセレクト)
  pinMode(Switch, INPUT_PULLUP);
  SPI.begin();
  SPI.setBitOrder(LSBFIRST);
  SPI.setDataMode(0);
}

void loop()
{
  //digitalWrite(latch, 1); //7segoff

  for (int j = 0; j < 10; j++)
  {
    for (int i = 0; i < 10; i++)
    {
      digitalWrite(latch, 0); //7segoff
      SPI.transfer(digits[j]);
      SPI.transfer(digits[i]);
      digitalWrite(latch, 1); //7segon
      delay(100);
    }
  }