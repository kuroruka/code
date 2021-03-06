#include <math.h>
#define DIV_RESISTOR 10000 // ①分圧抵抗の値[10kΩ]
#define R_25 10000 // サーミスタの25度における抵抗値[10kΩ]
#define T_25 25 //25度
#define B 3435 //B定数
#define T_ABS 273.16 //絶対温度


void setup(){
  Serial.begin(9600);
}

void loop(){
  double adc = analogRead(A0);

  // ②読み取ったアナログ値を電圧に変換する式(1行)
  // 5/1024を行った数値が0.0048828125
  double V_adc= 0.0048828125*adc;

  // ③分圧抵抗からサーミスタの抵抗を計算する式(1行)
  double R_thermistor= (V_adc*DIV_RESISTOR)/(5-V_adc);
  
  // ④サーミスタの抵抗から温度を計算する式

  //抵抗Rが混じったlogをとりあえず計算
  double r= log(R_thermistor / R_25);
  
  //B定数が混じった式をとりあえず計算
  double b= B / (T_25 + T_ABS);
  
  //計算開始
  double temperature= B/(r+b)-T_ABS;
  
  Serial.print("Temperature:");
  Serial.print(temperature);
  Serial.println("[C]");
  delay(500);
}
