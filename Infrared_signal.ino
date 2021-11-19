#define IR_RECEIVE_PIN A5 // 赤外線受光モジュールを接続するピン
#define DATA_ARRAY_LENGTH 800 // データ格納用配列の長さ
#define SAMPLING_RATE 100 // サンプリングレート[us] ※配列1要素あたりの長さ
//データ格納用配列
boolean data_array[DATA_ARRAY_LENGTH]; // "0","1"の2値であるためbool型を使う
void setup() {
Serial.begin(115200);
}
void loop() {
// 赤外線を受信しLOW(0)になるまで待機
while (digitalRead(IR_RECEIVE_PIN)) {}
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
