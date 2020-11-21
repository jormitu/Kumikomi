#include <Arduino.h>
//  押しボタン式信号機の制御

// 車道用信号機
int mainRed = 10;
int mainYellow = 11;
int mainGreen = 12;

// 歩行者用信号機
int crossRed = 8;
int crossGreen = 9;
int button = 7;
int crossTime = 4000; // 歩行者用横断時間

void switchLights();

void setup()
{
  pinMode(mainRed, OUTPUT);
  pinMode(mainYellow, OUTPUT);
  pinMode(mainGreen, OUTPUT);
  pinMode(crossRed, OUTPUT);
  pinMode(crossGreen, OUTPUT);
  pinMode(button, INPUT_PULLUP); // プルアップ有効
  digitalWrite(mainGreen, HIGH); //　車道用初期状態（緑）
  digitalWrite(crossRed, HIGH);  //　歩行者用初期状態（赤）
}

void loop()
{

  int state = digitalRead(button); // 押しボタンのチェック
  int val = analogRead(0);
  digitalWrite(crossGreen, LOW); //　車道用初期状態（緑）
  digitalWrite(mainRed, HIGH);
  digitalWrite(mainYellow, LOW);
  digitalWrite(mainGreen, LOW);
  delay(val);

  digitalWrite(mainRed, LOW);
  digitalWrite(mainYellow, HIGH);
  digitalWrite(mainGreen, LOW);
  delay(val);

  digitalWrite(mainRed, LOW);
  digitalWrite(mainYellow, LOW);
  digitalWrite(mainGreen, HIGH);
  delay(val);

  digitalWrite(mainGreen, LOW);
  digitalWrite(crossGreen, LOW); //　車道用初期状態（緑）
  digitalWrite(crossRed, HIGH);  //　歩行者用初期状態（赤）
  delay(val);
  digitalWrite(crossGreen, HIGH); //　車道用初期状態（緑）
  digitalWrite(crossRed, LOW);    //　歩行者用初期状態（赤）
  delay(val);
  // 押しボタンが押されたか？
  if (state == 0)
  {
    delay(val); //  車道用が黄色に変わるまでの時間
    switchLights();
  }
}

void switchLights()
{
  digitalWrite(mainGreen, LOW);   //　車道用初期状態（緑）
  digitalWrite(crossRed, HIGH);   //　歩行者用初期状態（赤）
  digitalWrite(mainYellow, HIGH); //黄色
  delay(3000);                    //3秒
  digitalWrite(mainYellow, LOW);  //黄色

  digitalWrite(mainRed, HIGH);    //赤(道路)
  digitalWrite(crossRed, LOW);    //　歩行者用初期状態（赤）
  digitalWrite(crossGreen, HIGH); //緑(歩行)
  delay(4000);
  digitalWrite(mainRed, HIGH); //赤(道路)
  //digitalWrite(crossGreen, HIGH); //緑(歩行)

  //緑点滅10回（0.25s間隔）
  for (int i = 0; i < 5; i++)
  {
    digitalWrite(crossGreen, HIGH); //緑
    delay(250);
    digitalWrite(crossGreen, LOW); //緑
    delay(250);
  }

  digitalWrite(crossRed, HIGH);  //　歩行者用赤をON
  digitalWrite(mainGreen, HIGH); //　車道用緑をON
  digitalWrite(mainRed, LOW);    //　車道用赤をOFF
}
