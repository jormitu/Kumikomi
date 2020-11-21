void setup()
{
  pinMode(11, OUTPUT);
}

void loop()
{

  int val = analogRead(0);      //入力値読み取り
  float f = val * 5.0 / 1023.0; //電圧値変換
  int intensity = map(val, 0, 1023, 0, 255);
  analogWrite(11, intensity);
  //serial
  Serial.print(f);
  Serial.print(" , ");
  Serial.println(val);
  delay(100);
}