/*
 * ultrasom.cpp
 *
 *  Created on: Jan 3, 2014
 *      Author: victor
 */
/********************************************************************

Example program to learn interfacing Ultra Sonic Range Finder Module
with AVR ATmega32 Microcontroller.

                                     NOTICE
                           --------
NO PART OF THIS WORK CAN BE COPIED, DISTRIBUTED OR PUBLISHED WITHOUT A
WRITTEN PERMISSION FROM EXTREME ELECTRONICS INDIA. THE LIBRARY, NOR ANY PART
OF IT CAN BE USED IN COMMERCIAL APPLICATIONS. IT IS INTENDED TO BE USED FOR
HOBBY, LEARNING AND EDUCATIONAL PURPOSE ONLY. IF YOU WANT TO USE THEM IN
COMMERCIAL APPLICATION PLEASE WRITE TO THE AUTHOR.

WRITTEN BY:
 *   AVINASH GUPTA
me@avinashgupta.com
 ********************************************************************/
#include "ultrasom.h"
//#include "../header/LS_defines.h"
#include "LS_ATmega328.h"
#include "Arduino.h"
#include <util/delay.h>
#include "ultrasom_stepper.h"


/********************************************************************

Configuration Area.
UltraSonic (US) sensor connection.

in this example it is connected to PORTA bit 0

Adjust the following to connect is to different i/o

 ********************************************************************

This function measusers the width of high pulse in micro second.

 ********************************************************************/

//globals
unsigned int resp;
int distance;

//******************** Função utilizando a lib do Arduino *************************************

/* HC-SR04 Sensor
https://www.dealextreme.com/p/hc-sr04-ultrasonic-sensor-distance-measuring-module-133696
This sketch reads a HC-SR04 ultrasonic rangefinder and returns the
distance to the closest object in range. To do this, it sends a pulse
to the sensor to initiate a reading, then listens for a pulse
to return. The length of the returning pulse is proportional to
the distance of the object from the sensor.
The circuit:
 * VCC connection of the sensor attached to +5V
 * GND connection of the sensor attached to ground
 * TRIG connection of the sensor attached to digital pin 2
 * ECHO connection of the sensor attached to digital pin 4


Original code for Ping))) example was created by David A. Mellis
Adapted for HC-SR04 by Tautvidas Sipavicius

This example code is in the public domain.
 */


const int trigPin = A2; //PC2
const int echoPin = A1; //PC1


long microsecondsToInches(long microseconds)
{
	// According to Parallax's datasheet for the PING))), there are
	// 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
	// second). This gives the distance travelled by the ping, outbound
	// and return, so we divide by 2 to get the distance of the obstacle.
	// See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
	return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
	// The speed of sound is 340 m/s or 29 microseconds per centimeter.
	// The ping travels out and back, so to find the distance of the
	// object we take half of the distance travelled.
	return microseconds / 29 / 2;
}


int sonar_arduino() {

	int obstaculo = 0;
	// establish variables for duration of the ping,
	// and the distance result in inches and centimeters:
	long duration, inches, cm;

	// The sensor is triggered by a HIGH pulse of 10 or more microseconds.
	// Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
	pinMode(trigPin, OUTPUT);
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);

	// Read the signal from the sensor: a HIGH pulse whose
	// duration is the time (in microseconds) from the sending
	// of the ping to the reception of its echo off of an object.
	pinMode(echoPin, INPUT);
	duration = pulseIn(echoPin, HIGH);

	// convert the time into a distance
	//inches = microsecondsToInches(duration);
	cm = microsecondsToCentimeters(duration);

	if (cm <= 10) {
		obstaculo = 1;
	} else {
		obstaculo = 0;
	}

	return obstaculo;
}

//*********************************************************************************************

//*********** Função do sonar toda feita em C, sem a lib do Arduino ***************************

unsigned int getPulseWidth(void)
{
	unsigned int i = 0, result;

	//Wait for the rising edge
	for (i = 0; i < 600000; i++) {
		if (!(ULTRASOUND_SHIELD_PIN & (1 << ULTRASOUND1_ECHO))) {
			continue;
		} else {
			break;
		}
	}

	if (i == 600000) {
		return US_ERROR; //Indicates time out
	}
	//High Edge Found

	//Setup Timer1
	TCCR1A = 0X00;
	TCCR1B = (1 << CS11); //Prescaler = Fcpu/8
	TCNT1 = 0x00; //Init counter

	//Now wait for the falling edge
	for (i = 0; i < 600000; i++) {
		if (ULTRASOUND_SHIELD_PIN & (1 << ULTRASOUND1_ECHO)) {
			if (TCNT1 > 60000) {
				break;
			} else {
				continue;
			}
		} else {
			break;
		}
	}


	if (i == 600000) {
		return US_ERROR; //Indicates time out
	}
	//Falling edge found

	result = TCNT1;

	//Stop Timer
	TCCR1B = 0x00;

	if (result > 60000) {
		return US_NO_OBSTACLE; //No obstacle
	} else {
		return (result >> 1);
	}
}

unsigned int get_UltrasoundData(void)
{
	int obstaculo_sonar = 0;


	//Set Ultra Sonic Port as out
	//set trigger port as output
	set_bit(ULTRASOUND_SHIELD_DDR, ULTRASOUND1_TRIG);
	//turn trigger LOW
	clr_bit(ULTRASOUND_SHIELD_PORT, ULTRASOUND1_TRIG);
	_delay_us(2);
	//turn trigger HIGH
	set_bit(ULTRASOUND_SHIELD_PORT, ULTRASOUND1_TRIG);
	_delay_us(10);
	//trigger pin turn back to LOW
	clr_bit(ULTRASOUND_SHIELD_PORT, ULTRASOUND1_TRIG);

	//set echo as input
	clr_bit(ULTRASOUND_SHIELD_DDR, ULTRASOUND1_ECHO);

	//Measure the width of pulse
	resp = getPulseWidth();

	//Handle Errors
	if (resp == US_ERROR) {
		//printf("ERROR ON <%d>\n", sensor_n);
		//fazer alguma logica aqui para retornar o erro ao prog principal
	} else if (resp == US_NO_OBSTACLE) {
		//printf("clear\n");
	} else {

		distance = (resp / 58.0); //Convert to cm
		//Serial.println("distancia sonar: ");
		//Serial.print(distance);

	}
	/* valor de distancia ajustado de acordo com o desejo do usuario*/
	if (distance >= 200 || distance <= 0) {
		obstaculo_sonar = 0x02;
	} else {
		if (distance < 10) { /* 10 centimetros */
			obstaculo_sonar = 1;
		} else {
			obstaculo_sonar = 0;
		}
	}
	return obstaculo_sonar;
}
//*********************************************************************************************

int sweep_sonar(void) {
	int i = 0;
	int obstaculo = 0;

	for (i=0; i <=25; i+=5) {
		//obstaculo = get_UltrasoundData();
		obstaculo = sonar_arduino();
		if (obstaculo == 1) {
			break;
		}
		rotate(5, .02);
		//delay(100); //era 50

		delayMicroseconds(50);
	}

	set_stepper_zero();
	return obstaculo;
}
