/*
 
 CarMove.h - Library for autonomously controlling Serial car
 Created by Maurice Adjei, 27 December 2021
 Company: Serial

*/
#ifndef MoveCar.h
#define MoveCar.h

#include "Arduino.h"

// Motor pins
#define PIN_DIRECTION_LEFT 4
#define PIN_DIRECTION_RIGHT 3
#define PIN_MOTOR_PWM_LEFT 6
#define PIN_MOTOR_PWM_RIGHT 5

// UltraSonic Sensor pins
#define SONIC_TRIG_PIN 7
#define SONIC_ECHO_PIN 8
#define SERVO_PIN 2

// Line Tracking Sensor pins
#define LEFT_TRACKING_PIN A1
#define CENTER_TRACKING_PIN A2
#define RIGHT_TRACKING_PIN A3

#define BUZZER_PIN A0
#define BATTERY_PIN A0



void pinsSetup();
bool getBatteryVoltage();
void carDrive(int speedl, int speedr);
void alarm(u8 beat, u8 repeat);
void setBuzzer(bool flag);
void stopCar();
extern float batteryVoltage;


#endif
