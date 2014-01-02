/*
 * motores.cpp
 * Trata o acionamento dos motores do robô
 *  Created on: Dec 30, 2013
 *      Author: victor
 */
#include "Arduino.h"
#include "motores.h"
#include "LS_ATmega328.h"
#include "sensorIR.h"

void move_motores(int joyX, int joyY)
{
	int obstaculo_ir = 0;

	//int8_t a = 0; //variavel de PWM do motor A :roda da direita
	//int8_t b = 0; //variavel de PWM do motor B :roda da esquerda
	int a_tmp = 0;
	int b_tmp = 0;
	int joyX_tmp = 0;
	int joyY_tmp = 0;

	//trata primeiro quadrante e quarto quadrante
	if ( ((joyY > 0 && joyX > 0) || (joyY < 0 && joyX > 0)) && (joyX < 70) ) {
		joyX_tmp = abs(100 - joyX);
	}
	else joyX_tmp = joyX;

	//trata segundo quadrante e terceiro quadrante
		if ( ((joyY > 0 && joyX < 0) || (joyY < 0 && joyX < 0)) && (abs(joyY) < 70) ) {
			joyX_tmp = abs(100 + joyX);
			joyY_tmp = abs(100 - joyY);

		}
		else joyY_tmp = joyY;
	//printf("a: %d\nb: %d\n\n", a, b); //debug

		a_tmp = 3 * abs(joyX_tmp);
		if (a_tmp >= 255) a_tmp = 255;

		b_tmp = 3 * abs(joyY_tmp);
		if (b_tmp >= 255) b_tmp = 255;

	//	a_tmp = (int) (abs(a_tmp));
	//	b_tmp = (int) (abs(b_tmp));

		analogWrite(MOTOR_PWMA, a_tmp);
		analogWrite(MOTOR_PWMB, b_tmp);

		Serial.print("Motor PWMA: ");
		Serial.print(a_tmp);
		Serial.print(",Motor PWMB:");
		Serial.println(b_tmp);

	if (joyX > 0) { //vou para direita, aciona a roda da esquerda
		pinMode(MOTOR_INA, INPUT);
		digitalWrite(MOTOR_INA, HIGH);

	} else {  //vou para esquerda, aciona a roda da direita
		pinMode(MOTOR_INA, OUTPUT);
		digitalWrite(MOTOR_INA, LOW);
	}

	if (joyY > 0) {  //vou para frente
		pinMode(MOTOR_INB, INPUT);
		digitalWrite(MOTOR_INB, HIGH);

	} else {  //vou para trás
		pinMode(MOTOR_INB, OUTPUT);
		digitalWrite(MOTOR_INB, LOW);
	}

	//////////////////////////////////
	//	//if (eixoY >= 150) {
	//	if (joyY >= 150) {
	//		obstaculo_ir = verificaObstaculo();
	//		//obstaculo_sonar = get_UltrasoundData();
	//		//printf("variavel obstaculo_sonar: %u\n", obstaculo_sonar);
	//	}
	//	//if ((obstaculo_ir == 0 && obstaculo_sonar == 0) || (obstaculo_ir == 0 && obstaculo_sonar == 0x02)) {
	//	if (obstaculo_ir == 0) {
	//
	//		Serial.println("sem obstaculo\n");
	//		TIMER0_COMPARE_A_CONFIGURE(a_tmp);
	//		TIMER0_COMPARE_B_CONFIGURE(b_tmp);
	//
	//		if (joyX > 0) {
	//			pinMode(MOTOR_INA, INPUT);
	//			digitalWrite(MOTOR_INA, HIGH);
	//
	//		} else {
	//			pinMode(MOTOR_INA, OUTPUT);
	//			digitalWrite(MOTOR_INA, LOW);
	//		}
	//
	//		if (joyY > 0) {
	//			pinMode(MOTOR_INB, INPUT);
	//			digitalWrite(MOTOR_INB, HIGH);
	//
	//		} else {
	//			pinMode(MOTOR_INB, OUTPUT);
	//			digitalWrite(MOTOR_INB, LOW);
	//		}
	//		//} else if (obstaculo_ir == 1 || obstaculo_sonar == 1) {
	//	} else if (obstaculo_ir == 1) {
	//		Serial.println("obstaculo\n");
	//		//TIMER0_CLOCK_PRESCALER_OFF();
	//		analogWrite(MOTOR_PWMA, 0);
	//		analogWrite(MOTOR_PWMB, 0);
	//		obstaculo_ir = 0;
	//		//obstaculo_sonar = 0;
	//	}
}



