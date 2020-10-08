#include <Servo.h>

// ピストンステータス
#define STATUS_STOP 0
#define STATUS_LOW  1
#define STATUS_MIDDLE 2
#define STATUS_HIGH 3
#define STATUS_REST 4

// pin番号
int togglePin = 7;
int servoPin = 9;

// サーボモータインスタンス
Servo servo;

// トグルスイッチ
int toggleVal = LOW;
int oldToggleVal = LOW;

// ピストン
int pistonStatus = 0;
int defaultPistonSpeed = 90;
int pistonSpeed = 90;
int loopCnt = 1;
int speedRange = 8;
int phaseLength = 120;

void setSpeed() {
    // ステータスごとにスピードを変更
    switch (pistonStatus) {
    case STATUS_STOP:
    case STATUS_REST:
      defaultPistonSpeed = 90;
      break;
    case STATUS_LOW:
      defaultPistonSpeed = 110;
      break;
    case STATUS_MIDDLE:
      defaultPistonSpeed = 130;
      break;
    case STATUS_HIGH:
      defaultPistonSpeed = 150;
      break;
    }
    pistonSpeed = defaultPistonSpeed;

    Serial.print("[Setting Status] Status=");
    Serial.print(pistonStatus);
    Serial.print(", Piston speed=");
    Serial.println(defaultPistonSpeed);
}

void setup() {
  Serial.begin(9600);
  Serial.println("[Starting Piston Machine]");
  pinMode(togglePin, INPUT_PULLUP);
  servo.attach(servoPin);
  setSpeed();
}

void loop() {
  toggleVal = digitalRead(togglePin);

  // トグルスイッチが押されたら
  if (toggleVal == LOW && oldToggleVal== HIGH) {
    Serial.println("[Toggle switch pushed]");
    // ステータスを変更
    if (pistonStatus == STATUS_STOP) {
      pistonStatus = STATUS_LOW; 
    } else {
      pistonStatus = STATUS_STOP;
    }
    setSpeed();
  }
  oldToggleVal = toggleVal;
  
  if (pistonStatus != STATUS_STOP) { 
    pistonSpeed += random(7) - 3;
    if (pistonSpeed < defaultPistonSpeed - speedRange) {
      pistonSpeed = defaultPistonSpeed - speedRange;
    } else if (pistonSpeed > defaultPistonSpeed + speedRange) {
      pistonSpeed = defaultPistonSpeed + speedRange;
    }

    if (loopCnt % phaseLength == 0) {
      Serial.println("[Phase end]");
      switch (pistonStatus) {
      case STATUS_LOW: // LOWのままか、MIDDLEに移行
        pistonStatus += random(2);
        break;
      case STATUS_MIDDLE: // MIDDLEのままか、HIGHに移行
        pistonStatus += random(2);
        break;
      case STATUS_HIGH: // HIGHのままか、RESTに移行
        pistonStatus += random(2);
        break;
      case STATUS_REST: // LOWかHIGHに移行
        pistonStatus = random(2) * 2 + 1;
        break;
      }
      
      loopCnt = 0;
      setSpeed();
    }
    
    //Serial.println(pistonSpeed);
  }
  
  servo.write(pistonSpeed);

  loopCnt++;

  delay(100); 
}
