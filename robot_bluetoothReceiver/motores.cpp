/*
 * motores.cpp
 * Trata o acionamento dos motores do robô
 *  Created on: Dec 30, 2013
 *      Author: victor
 */
/* Autor do algoritmo de controle das rodas: Jonatha Fogaça
 * Created on: 02/01/2014
 * */

#include "Arduino.h"
#include "motores.h"
#include "LS_ATmega328.h"
#include "sensorIR.h"
#include "ultrasom.h"
#include "ultrasom_stepper.h"
#include "math.h"
#include "debug.h"
//#include "StopWatch.h"

void calcula_coordenadas(int joyX, int joyY, float &motor_esquerda, float &motor_direita) {

	float resultante = 0;
	float mystic_number = 78;
	float tmp = 0, tempX = 0, tempY = 0;

	tempY = pow(joyY,2);
	tempX = pow(joyX,2);
	tmp = tempX + tempY;
	resultante = sqrt(tmp);
	motor_direita = sqrt(tempX + tempY - (200*joyX) + 10000);
	motor_esquerda = sqrt(tempX + tempY + (200*joyX) + 10000);
	motor_direita = (int)(motor_direita*resultante)/mystic_number;
	motor_esquerda = (int)(motor_esquerda*resultante)/mystic_number;
	if (motor_direita >= 255) motor_direita = 255;
	if (motor_esquerda >= 255) motor_esquerda = 255;

#ifdef ROBOT_DEBUG
		Serial.println("resultante: ");
		Serial.print(resultante);
		Serial.println("\nmotor_direita: ");
		Serial.print(motor_direita);
		Serial.println("\nmotor_esquerda: ");
		Serial.print(motor_esquerda);
#endif
	return;
}

void move_motores(int joyX, int joyY)
{
	int obstaculo_ir = 0;
	unsigned int obstaculo_sonar = 0;
	float motor_direita = 0;
	float motor_esquerda = 0;
	//unsigned long tempo_gasto  = 0;
	//StopWatch cronometro;

	//inicia a contagem da função
	//cronometro.start();

	if (joyY > 0) {
		obstaculo_ir = verificaObstaculo();

#ifdef DYNAMIC_ULTRASOUND //definido em ultrasom.h
		obstaculo_sonar = sweep_sonar();		   //sweep dinamico
#else
		obstaculo_sonar = get_UltrasoundData();  //sweep estatico
#endif
#ifdef ROBOT_DEBUG
		Serial.print("obstaculo_sonar: ");
		Serial.print(obstaculo_sonar);
#endif
	}
	//if (obstaculo_ir == 0) {
	if ((obstaculo_ir == 0 && obstaculo_sonar == 0) || (obstaculo_ir == 0 && obstaculo_sonar == 0x02)) {  //teste
		//if (obstaculo_ir == 0 && obstaculo_sonar == 0) {
		//Serial.println("sem obstaculo\n");
		calcula_coordenadas(joyX, joyY, motor_esquerda, motor_direita);
		analogWrite(MOTOR_PWMA, (int) motor_esquerda);
		analogWrite(MOTOR_PWMB, (int) motor_direita);

		//primeiro quadrante
		if (joyY > 0) {
			pinMode(MOTOR_INB, INPUT);
			digitalWrite(MOTOR_INB, HIGH);
			pinMode(MOTOR_INA, INPUT);
			digitalWrite(MOTOR_INA, HIGH);

		} else {
			pinMode(MOTOR_INB, OUTPUT);
			digitalWrite(MOTOR_INB, LOW);
			pinMode(MOTOR_INA, OUTPUT);
			digitalWrite(MOTOR_INA, LOW);
		}

	}

	//else if (obstaculo_ir == 1) {
	else if (obstaculo_ir == 1 || obstaculo_sonar == 1) {
	#ifdef ROBOT_DEBUG
		Serial.println("obstaculo\n");
	#endif
		analogWrite(MOTOR_PWMA, 0);
		analogWrite(MOTOR_PWMB, 0);
		obstacleAlarm();
		obstaculo_ir = 0;
		obstaculo_sonar = 0;
		//cronometro.stop();
		//tempo_gasto =  cronometro.elapsed();
		//Serial.println("tempo gasto pela função move_motores: ");
		//Serial.print(tempo_gasto);
		//cronometro.reset();
	}

}



