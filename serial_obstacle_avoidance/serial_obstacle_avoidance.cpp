#include "serial_obstacle_avoidance.h"

Servo servo;
 
char servoOffset = 0;
int speedOffset;


void voltageCompensationForSpeed(){
	getBatteryVoltage();
	float voltageOffset = 8.4 - batteryVoltage;
	speedOffset = voltageOffset * 20;
}


float getSonar(){
	unsigned long pingTime;
	float distance;
	
	digitalWrite(SONIC_TRIG_PIN, HIGH);
	delayMicroseconds(10);
	digitalWrite(SONIC_TRIG_PIN, LOW);
	
	pingTime = pulseIn(SONIC_ECHO_PIN, HIGH, SONIC_TIMEOUT);
	if (pingTime != 0){
		distance = (float)pingTime * SOUND_VELOCITY / 2 / 10000;
	}
	else {
		distance = MAX_DISTANCE;
	}
	return distance;
}

void servoCalibrate(){
	servo.attach(SERVO_PIN);
	servo.write(90 + servoOffset);
}

void automaticObstacleAvoidance(){
	int distance[3], tempDistance[3][5], sumDistance;
	static u8 leftToRight = 0, servoAngle = 0, lastServoAngle = 0;
	const u8 scanAngle[2][3] = { {150, 90, 30}, {30, 90, 150} };
	
	for (int i = 0; i < 3; i++){
		servoAngle = scanAngle[leftToRight][i];
		servo.write(servoAngle);
		if (lastServoAngle != servoAngle){
			delay(130);
		}
		lastServoAngle = servoAngle;
		for (int j = 0; j < 5; j++){
			tempDistance[i][j] = getSonar();
			delayMicroseconds(2 * SONIC_TIMEOUT);
			sumDistance += tempDistance[i][j];
		}
		if (leftToRight == 0){
			distance[i] = sumDistance / 5;
		}
		else {
			distance[2-i] = sumDistance / 5;
		}
		sumDistance = 0;
	}
	leftToRight = (leftToRight + 1) % 2; 
	
	if (distance[1] < OBSTACLE_DISTANCE){
		if(distance[0] > OBSTACLE_DISTANCE && distance[0] > distance[2]){
			carDrive(-(150 + speedOffset), -(150 + speedOffset));
			delay(100);
			carDrive(-(150 + speedOffset), (150 + speedOffset));
		}
		else if (distance[2] > OBSTACLE_DISTANCE && distance[2] > distance[0]){
			carDrive(-(150 + speedOffset), -(150 + speedOffset));
			delay(100);
			carDrive((150 + speedOffset), -(150 + speedOffset));
		}
		else {
			carDrive(-(150 + speedOffset), -(150 + speedOffset));
			delay(100);
			carDrive(-(150 + speedOffset), (150 + speedOffset));
		}
	}
	else {
		if (distance[0] < OBSTACLE_DISTANCE_ONSIDE){
			carDrive(-(150 + speedOffset), -(150 + speedOffset));
			delay(100);
			carDrive((180 + speedOffset), (50 + speedOffset));
		}
		else if (distance[2] < OBSTACLE_DISTANCE_ONSIDE){
			carDrive(-(150 + speedOffset), -(150 + speedOffset));
			delay(100);
			carDrive((50 + speedOffset), (180 + speedOffset));
		}
		else {
			 carDrive((80 + speedOffset), (80 + speedOffset));
		}
	}
}