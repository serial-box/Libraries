/*
	serial_obstacle_avoidance.h - Library for automatic obstacle avoidance of Serial car
	Created by Maurice Adjei, 31 January 2022
	Company: Serial
*/

#ifndef serial_obstacle_avoidance.h
#define serial_obstacle_avoidance.h


#include "Arduino.h"
#include <MoveCar.h>
#include "Servo.h"


#define MAX_DISTANCE 300
#define SONIC_TIMEOUT (MAX_DISTANCE * 60)
#define SOUND_VELOCITY 340

#define OBSTACLE_DISTANCE 40
#define OBSTACLE_DISTANCE_ONSIDE 15


extern Servo servo;
extern char servoOffset;
extern int speedOffset;

void automaticObstacleAvoidance();
float getSonar();
void voltageCompensationForSpeed();
void servoCalibrate();

#endif