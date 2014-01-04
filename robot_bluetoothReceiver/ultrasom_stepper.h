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
#define STEPPER_DIRECTION               PB1
#define STEPPER_STEP                    PB2
#define FIM_DE_CURSO_DDR                DDRB
#define FIM_DE_CURSO_PORT               PORTB
#define FIM_DE_CURSO_ESQUERDA           PB3
#define FIM_DE_CURSO_DIREITA            PB4

void rotate(int steps, float speed);
void rotateDeg(float deg, float speed);

#endif /* ULTRASOM_STEPPER_H_ */
