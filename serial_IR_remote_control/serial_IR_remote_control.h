/*
 
 serial_IR_remote_control.h - Library for controlling Serial car using IR remote
 Created by Maurice Adjei, 10 February 2022
 Company: Serial

*/

#ifndef serial_IR_remote_control_h
#define serial_IR_remote_control_h

#include "Arduino.h"
#include <MoveCar.h>
#include <IRremote.h>

#define IR_REMOTE_KEYCODE_UP 0xFF02FD
#define IR_REMOTE_KEYCODE_DOWN 0xFF9867
#define IR_REMOTE_KEYCODE_LEFT 0xFFE01F
#define IR_REMOTE_KEYCODE_RIGHT 0xFF906F
#define IR_REMOTE_KEYCODE_CENTER 0xFFA857
#define IR_REMOTE_KEYCODE_REPEAT 0xFFFFFFFF

#define IR_UPDATE_TIMEOUT 120
#define IR_CAR_SPEED 180

extern IRrecv irrecv;
extern decode_results results;

extern bool noSignal;
extern u32 lastIRUpdateTime, currentKeyCode, lastKeyCode;

void remoteControlledCar();
void IRReceiverSetup();

#endif