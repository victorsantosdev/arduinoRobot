/* 
 * File:   sensorIR.c
 * Author: victor
 *
 * Created on May 12, 2013, 2:49 AM
 */

#include "../header/LS_defines.h"
#include "../header/LS_ATmega328.h"
#include "../header/sensorIR.h"
#include <util/delay.h>

//globals

int8 verificaObstaculo(void)
{
    int result_tmp = 0;
    int8 result_final = 0;
    int result_media = 0;
    int8 i = 0;
    const int8 n_samples = 5;

    result_tmp = 0;

    for (i = n_samples; i > 0; i--) {
        ADC_START_CONVERSION();
        adcWaitConversionFinish();
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

