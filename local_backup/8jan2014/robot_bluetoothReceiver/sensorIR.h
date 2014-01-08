/*
 * sensorIR.h
 *
 *  Created on: Dec 30, 2013
 *      Author: victor
 */

#ifndef SENSORIR_H_
#define SENSORIR_H_
#define ALARM_PIN	8 //PB0
#define ALARM_FREQUENCY	2000 //3kHz
#define ALARM_DURATION 50 //duracao em ms

int verificaObstaculo(void);
void obstacleAlarm(void);
#endif /* SENSORIR_H_ */
