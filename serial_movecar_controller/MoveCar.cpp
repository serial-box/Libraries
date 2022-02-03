#include "Arduino.h"
#include "MoveCar.h"

float batteryVoltage = 0;
bool isBuzzered = false;

void alarm(u8 beat, u8 repeat){
  for (int j = 0; j < repeat; j++){
    for (int i = 0; i < beat; i++){
      setBuzzer(true);
      delay(100);
      setBuzzer(false);
      delay(100);
    }
    delay(500);
  }
}

void setBuzzer(bool flag){
  isBuzzered = flag;
  pinMode(BUZZER_PIN, flag);
  digitalWrite(BUZZER_PIN, flag);
}

void pinsSetup(){
// Motor pins setup
  pinMode(PIN_DIRECTION_LEFT, OUTPUT);
  pinMode(PIN_DIRECTION_RIGHT, OUTPUT);
  pinMode(PIN_MOTOR_PWM_LEFT, OUTPUT);
  pinMode(PIN_MOTOR_PWM_RIGHT, OUTPUT);

// UltraSonic pins setup
  pinMode(SONIC_TRIG_PIN, OUTPUT);
  pinMode(SONIC_ECHO_PIN, INPUT);

// Line Tracking Sensor pins setup
  pinMode(LEFT_TRACKING_PIN, INPUT);
  pinMode(CENTER_TRACKING_PIN, INPUT);
  pinMode(RIGHT_TRACKING_PIN, INPUT);

// turn buzzer off
  setBuzzer(false);
}

void carDrive(int speedl, int speedr){
  int dirL = 0, dirR = 0;
  if (speedl > 0){
    dirL = 0;
  }
  else {
    dirL = 1;
    speedl = -speedl;
  }
  if (speedr > 0){
    dirR = 1;
  }
  else {
    dirR = 0;
    speedr = -speedr;
  }

  speedl = constrain(speedl, 1, 255);
  speedr = constrain(speedr, 1, 255);

  digitalWrite(PIN_DIRECTION_LEFT, dirL);
  digitalWrite(PIN_DIRECTION_RIGHT, dirR);
  analogWrite(PIN_MOTOR_PWM_LEFT, speedl);
  analogWrite(PIN_MOTOR_PWM_RIGHT, speedr);
}

bool getBatteryVoltage() {
  if (!isBuzzered) {
    pinMode(BATTERY_PIN, INPUT);
    int batteryADC = analogRead(BATTERY_PIN);
    if (batteryADC < 614) // 3V/12V ,Voltage read: <2.1V/8.4V
    {
     batteryVoltage = batteryADC / 1023.0 * 5.0 * 4;
     return true;
    }
  }
  return false;
}


void stopCar(){
  setBuzzer(false);
  carDrive(0,0);
  isBuzzered = false;
}
