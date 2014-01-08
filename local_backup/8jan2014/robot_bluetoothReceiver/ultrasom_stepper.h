/*
 * ultrasom_stepper.h
 *
 *  Created on: Jan 4, 2014
 *      Author: victor
 */

#ifndef ULTRASOM_STEPPER_H_
#define ULTRASOM_STEPPER_H_

#define STEPPER_DDR                     DDRB
#define STEPPER_PORT                    PORTB
#define STEPPER_DIRECTION               12		//12	//PB4 //cinza/verde //roxo é gnd
#define STEPPER_STEP                    13		//13 	//PB5 //branco/amarelo
#define FIM_DE_CURSO_DDR                DDRB
#define FIM_DE_CURSO_PORT               PORTB
#define FIM_DE_CURSO		            11 	//11		//PB3  //laranja/branco

void rotate(int steps, float speed);
void rotateDeg(float deg, float speed);
int read_switches(void);
void set_stepper_zero(void); //seta motor para posição inicial
void stepper_sweep(void); //faz a varredura do sonar
#endif /* ULTRASOM_STEPPER_H_ */
