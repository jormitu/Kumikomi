//#include <Arduino.h>
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

void setup()
{
  pinMode(mainRed, OUTPUT);
  pinMode(mainYellow, OUTPUT);
  pinMode(mainGreen, OUTPUT);
  pinMode(crossRed, OUTPUT);
  pinMode(crossGreen, OUTPUT);
  pinMode(button, INPUT_PULLUP); // プルアップ有効
  //digitalWrite(mainGreen, HIGH); //　車道用初期状態（緑）
  //digitalWrite(crossRed, HIGH);  //　歩行者用初期状態（赤）
}

void loop()
{

  int state = digitalRead(button); // 押しボタンのチェック
  digitalWrite(crossGreen, LOW);   //　車道用初期状態（緑）
  digitalWrite(mainRed, HIGH);
  digitalWrite(mainYellow, LOW);
  digitalWrite(mainGreen, LOW);
  delay(200);

  digitalWrite(mainRed, LOW);
  digitalWrite(mainYellow, HIGH);
  digitalWrite(mainGreen, LOW);
  delay(200);

  digitalWrite(mainRed, LOW);
  digitalWrite(mainYellow, LOW);
  digitalWrite(mainGreen, HIGH);
  delay(200);

  digitalWrite(mainGreen, LOW);
  digitalWrite(crossGreen, LOW); //　車道用初期状態（緑）
  digitalWrite(crossRed, HIGH);  //　歩行者用初期状態（赤）
  delay(200);
  digitalWrite(crossGreen, HIGH); //　車道用初期状態（緑）
  digitalWrite(crossRed, LOW);    //　歩行者用初期状態（赤）
  delay(200);
  // 押しボタンが押されたか？
  // if()
  // {
  //   delay(2000); //  車道用が黄色に変わるまでの時間
  //   switchLights();
  // }
}

void switchLights()
{

  //緑点滅10回（0.25s間隔）
  // for(){

  // }

  digitalWrite(crossRed, HIGH);  //　歩行者用赤をON
  digitalWrite(mainGreen, HIGH); //　車道用緑をON
  digitalWrite(mainRed, LOW);    //　車道用赤をOFF
}