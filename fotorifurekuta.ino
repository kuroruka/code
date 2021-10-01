#define THRESHOLD 950 // 実測後、適切な値に調整する

const int LED_PIN = 13;
void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
}
void loop() {
  int val_a0 = analogRead(A0);
  Serial.println(val_a0);
  if(val_a0 > THRESHOLD) {
  digitalWrite(LED_PIN, HIGH); // 紙の色が白のとき点灯
}
  else {
    digitalWrite(LED_PIN, LOW); // 紙の色が黒のとき消灯
  }
}
