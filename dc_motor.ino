/*
 * TB6643KQqを使用（TA8428Kも同様）
 * [1] Arduino 5
 * [2] Arduino 6
 * [3] DCモータ
 * [4] GND
 * [5] DCモータ
 * [6] NC
 * [7] 電源（乾電池8本使用）
 */

int val1 = 0;
int val2 = 0;

void setup(){
  pinMode(7, INPUT_PULLUP); // タクトスイッチ1
  pinMode(8, INPUT_PULLUP); // タクトスイッチ2
}

void loop(){
  val1 = digitalRead(7);
  val2 = digitalRead(8);  
  
  if (val1 == LOW && val2 == LOW) { 
    analogWrite(5, 128);
    analogWrite(6, 0);
  } else if (val1 == LOW && val2 == HIGH) {
    analogWrite(5, 64);
    analogWrite(6, 0);
  } else if (val1 == HIGH && val2 == LOW) {
    analogWrite(5, 48);
    analogWrite(6, 0);
  } else {
    analogWrite(5, 0);
    analogWrite(6, 0);
  }

  delay(100);
}
