#define IR_RECEIVE_PIN A5 // 赤外線受光モジュールを接続するピン
#define IR_LED_PIN 2 // 赤外線LEDを接続するピン
#define BUTTON_PIN 3 // 押しボタンを接続するピン
#define DATA_ARRAY_LENGTH 800 // データ格納用配列の長さ
#define SAMPLING_RATE 100 // サンプリングレート[us] ※配列1要素あたりの長さ
//データ格納用配列
boolean data_array[DATA_ARRAY_LENGTH]; // "0","1"の2値であるためbool型を使う
// 赤外線信号送信関数
void ir_send() {
  for (int i = 0; i < DATA_ARRAY_LENGTH; i++) {
    if (data_array[i]) // データの要素が"1"ならば
      carrier_1();
    else // データの要素が"0"ならば
      carrier_0();
  }
  Serial.println("IR signal sent!");
  delay(500); // 送信後0.5秒待つ（ループバック、連送防止）
}
// データが"1"のときのキャリア生成
void carrier_1() {
  for (int i = 0; i < 4; i++) {
    PORTD |= _BV(IR_LED_PIN);
    delayMicroseconds(10);
    PORTD &= ~_BV(IR_LED_PIN);
    delayMicroseconds(19);
  }
}
// データが"0"のときのキャリア生成
void carrier_0() {
  for (int i = 0; i < 4; i++) {
    PORTD &= ~_BV(IR_LED_PIN);
    delayMicroseconds(10);
    PORTD &= ~_BV(IR_LED_PIN);
    delayMicroseconds(19);
  }
}
// ここからメインプログラム ////////////
void setup() {
  Serial.begin(115200);
  pinMode(IR_LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}
void loop() {
// 赤外線を受信しLOW(0)になるまで待機する
// その間にボタンが押されたら赤外線信号を送出する
  while (digitalRead(A5)) {
    if (!digitalRead(BUTTON_PIN)) ir_send();
}
// 赤外線を受信した瞬間から、受信ピンの値を配列に順次格納
   for (int i = 0; i < DATA_ARRAY_LENGTH; i++) {
    data_array[i] = !digitalRead(IR_RECEIVE_PIN); // 受信モジュールが負論理なので反転
    delayMicroseconds(SAMPLING_RATE); // 1要素あたりの時間を決定するために一時停止
  }
// 受信したデータをシリアルモニタに表示
  Serial.println("-- RESULT --");
  for (int i = 0; i < DATA_ARRAY_LENGTH; i++) {
    if (data_array[i] == 1) Serial.print("X");
    else Serial.print("_");
  }
  Serial.println();
}
