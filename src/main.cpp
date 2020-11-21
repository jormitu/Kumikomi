void setup()
{
}

void loop()
{

  int val = analogRead(0);      //入力値読み取り
  float f = val * 5.0 / 1023.0; //電圧値変換

  //serial
  Serial.print(f);
  Serial.print(" , ");
  Serial.println(val);
  delay(1000);
}