/*
 * ultrasom_stepper.cpp
 *
 *  Created on: Jan 4, 2014
 *      Author: victor
 */
//////////////////////////////////////////////////////////////////
//©2011 bildr
//Released under the MIT License - Please reuse change and share
//Using the easy stepper with your arduino
//use rotate and/or rotateDeg to controll stepper motor
//speed is any number from .01 -> 1 with 1 being fastest -
//Slower Speed == Stronger movement
/////////////////////////////////////////////////////////////////


#include  "ultrasom_stepper.h"
#include "Arduino.h"
#include "sensorIR.h"

void set_stepper_zero(void) {
	int zero_position = HIGH;
	int i = 0;
	for (i=0; i<=50;i+=5) {
		zero_position = digitalRead(FIM_DE_CURSO);
		//Serial.println("Chave fim de curso: ");
		//Serial.print(zero_position);
		if (zero_position == HIGH) {
			obstacleAlarm();
			obstacleAlarm(); //beep 2 times
			break;
		} else {
			rotate(-5, .02); //reverse
			//delay(5); //era 50
			delayMicroseconds(25);
		}
	}

}

void rotate(int steps, float speed){

	//rotate a specific number of microsteps (8 microsteps per step) - (negative for reverse movement)
	//speed is any number from .01 -> 1 with 1 being fastest - Slower is stronger
	int dir = (steps > 0)? HIGH:LOW;
	steps = abs(steps);

	digitalWrite(STEPPER_DIRECTION,dir);

	float usDelay = (1/speed) * 70;

	for(int i=0; i < steps; i++){
		digitalWrite(STEPPER_STEP, HIGH);
		delayMicroseconds(usDelay);

		digitalWrite(STEPPER_STEP, LOW);
		delayMicroseconds(usDelay);
	}
}

void rotateDeg(float deg, float speed){
	//rotate a specific number of degrees (negitive for reverse movement)
	//speed is any number from .01 -> 1 with 1 being fastest - Slower is stronger
	int dir = (deg > 0)? HIGH:LOW;
	digitalWrite(STEPPER_DIRECTION,dir);

	int steps = abs(deg)*(1/0.225);
	float usDelay = (1/speed) * 70;

	for(int i=0; i < steps; i++){
		digitalWrite(STEPPER_STEP, HIGH);
		delayMicroseconds(usDelay);

		digitalWrite(STEPPER_STEP, LOW);
		delayMicroseconds(usDelay);
	}
}

void stepper_sweep(void) {
	rotate(25, .01);
	delay(50);

	rotate(-25, .01); //reverse
	delay(50);
}
