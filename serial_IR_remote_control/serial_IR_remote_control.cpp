/*
 
 serial_IR_remote_control.cpp - Library for controlling Serial car using IR remote
 Created by Maurice Adjei, 10 February 2022
 Company: Serial

*/

#include "serial_IR_remote_control.h"

IRrecv irrecv(IR_RECEIVER_PIN);
decode_results results;

bool noSignal = false;
u32 lastIRUpdateTIme = 0;
u32 currentKeyCode, lastKeyCode;

void IRReceiverSetup(){
	irrecv.enableIRIn();	// this initialises the IR receiver
}

void remoteControlledCar(){
	if(irrecv.decode(&results)){	// this bit of code receives the signal from the remote and decodes it
	   noSignal = false;
	   currentKeyCode = results.value; // set the value of the currentKeyCode to the value of the decoded signal
	   /*
		  the code below ensures that the value of a constant keypress (0xFFFFFFFF) will be ignored but rather 
		  only the initial value of the same keypress will be used in running the "switch" code block.
	   */
	   if (currentKeyCode != IR_REMOTE_KEYCODE_REPEAT){
		   lastKeyCode = currentKeyCode;
	   }
	   switch (lastKeyCode){
		   case IR_REMOTE_KEYCODE_UP:	// if the forward button is pressed move the car forward
			carDrive(IR_CAR_SPEED, IR_CAR_SPEED);
			break;
		   case IR_REMOTE_KEYCODE_DOWN: // if the down button is pressed move the car backward
			carDrive(-IR_CAR_SPEED, -IR_CAR_SPEED);
			break;
		   case IR_REMOTE_KEYCODE_LEFT: // if the left button is pressed move the car left
		    	carDrive(-IR_CAR_SPEED, IR_CAR_SPEED);
			break;
		   case IR_REMOTE_KEYCODE_RIGHT: // if the right button is pressed move the car right
		    	carDrive(IR_CAR_SPEED, -IR_CAR_SPEED);
			break;
		   case IR_REMOTE_KEYCODE_CENTER: // if the center button is pressed honk the horn (turn on the buzzer)
		    	setBuzzer(true);
			break;
		   default:
		    	break;
	   }
	   irrecv.resume();  // listen for a new signal
	   lastIRUpdateTIme = millis();	// record the time that the last signal was received
	}
	/*
		this next bit of code ensures that if the car is no longer receiving a signal it stops moving
	*/
	else{
		if (millis() - lastIRUpdateTIme > IR_UPDATE_TIMEOUT){ // if the new time and the last recorded time exceed the IR timeout value
			if (!noSignal){
				noSignal = true;
				carDrive(0, 0);
				setBuzzer(false);
			}
			lastIRUpdateTIme = millis();
		}
	}
}
	