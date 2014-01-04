/* 
 * File:   ultrasom.h
 * Author: victor
 *
 * Created on May 12, 2013, 2:49 AM
 */

#ifndef ULTRASOM_H
#define	ULTRASOM_H

#define ULTRASOUND_SHIELD_DDR           DDRC
#define ULTRASOUND_SHIELD_PORT          PORTC
#define ULTRASOUND_SHIELD_PIN           PINC
#define ULTRASOUND1_ECHO                PC1             //configurado como entrada
#define ULTRASOUND1_TRIG                PC2             //configurado como saida

#define US_ERROR                        0xFFFF
#define  US_NO_OBSTACLE                 0xFFFE

unsigned int getPulseWidth(void);
unsigned int get_UltrasoundData(void);

#endif	/* ULTRASOM_H */


