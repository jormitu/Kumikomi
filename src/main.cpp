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
int i, j = 0;
int state = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(latch, OUTPUT); //CS(チップセレクト)SS(スレーブセレクト)
  pinMode(Switch, INPUT_PULLUP);
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

  if (digitalRead(Switch) == 0)
  {
    state++;
    delay(100);              //チャタリング防止
    digitalWrite(latch, 0);  //7segoff
    SPI.transfer(digits[j]); //10の位
    SPI.transfer(digits[i]); //1の位
    digitalWrite(latch, 1);  //7segon
    delay(100);

    i++;
    if (i >= 10)
    {
      i = 0;
      j++;
    }
    if (j >= 10)
    {
      j = 0;
    }
    while (digitalRead(Switch) == 0) //ボタンが放されるのを末
    {
    }
  }

  // if ((state % 2) == 1)
  // {
  //   digitalWrite(latch, 0);  //7segoff
  //   SPI.transfer(digits[j]); //10の位
  //   SPI.transfer(digits[i]); //1の位
  //   digitalWrite(latch, 1);  //7segon
  //   delay(100);

  //   i++;
  //   if (i >= 10)
  //   {
  //     i = 0;
  //     j++;
  //   }
  //   if (j >= 10)
  //   {
  //     j = 0;
  //   }
  // }

  Serial.println("state=");
  Serial.print(state);
}