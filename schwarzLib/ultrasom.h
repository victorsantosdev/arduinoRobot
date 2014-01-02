/* 
 * File:   ultrasom.h
 * Author: victor
 *
 * Created on May 12, 2013, 2:49 AM
 */

#ifndef ULTRASOM_H
#define	ULTRASOM_H

#define ULTRASOUND_SHIELD_DDR           DDRD
#define ULTRASOUND_SHIELD_PORT          PORTD
#define ULTRASOUND_SHIELD_PIN           PIND
#define ULTRASOUND1_ECHO                PD3             //configurado como entrada
#define ULTRASOUND1_TRIG                PD2             //configurado como saida
//#define ULTRASOUND2_TRIG                PC2
//#define ULTRASOUND2_ECHO                PC3
#define STEPPER_DDR                     DDRC
#define STEPPER_PORT                    PORTC
#define STEPPER_DIRECTION               PC3        
#define STEPPER_STEP                    PC4

#define US_ERROR                        0xFFFF
#define  US_NO_OBSTACLE                 0xFFFE

//#define SENSOR_SONAR_1 1
//#define SENSOR_SONAR_2 2

uint16_t getPulseWidth(void);
uint16_t get_UltrasoundData(void);

#endif	/* ULTRASOM_H */


