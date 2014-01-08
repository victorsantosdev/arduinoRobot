/*
 * sensorIR.cpp
 *
 *  Created on: Dec 30, 2013
 *      Author: victor
 */

/* O sensor IR utiliza o canal 0 do ADC PORTC0 como porta de leitura */

#include "sensorIR.h"
#include <util/delay.h>
#include "LS_ATmega328.h"
#include "Arduino.h"
//globals

void obstacleAlarm(void) {
//buzzer para alarmar obstaculo
	tone(ALARM_PIN, ALARM_FREQUENCY, ALARM_DURATION);
	delay(25);
	noTone(ALARM_PIN);
	delay(25);
}

int verificaObstaculo(void)
{
	int result_tmp = 0;
	int result_final = 0;
	int result_media = 0;
	int i = 0;
	const int n_samples = 5;

	result_tmp = 0;

	for (i = n_samples; i > 0; i--) {
		ADC_START_CONVERSION();
		ADC_WAIT_CONVERSION_FINISH();
		result_tmp += ADC; //lê os 10 bits do ADC
		_delay_us(25); //tempo de cada amostragem utilizando a frequencia do ADC em 1MHz
	}

	result_media = (result_tmp / n_samples); //faço uma média para evitar falsos positivos

	//printf("ADC result:\t%d\n", result_media); //debug

	if (result_media > 500) {
		result_final = 1;
	}

	if (result_media <= 500) {
		result_final = 0;
	}
	result_media = 0;

	return result_final;
}


