/* -----------------------------------------------------------------------------
 * File:			motores.h
 * Module:			Projeto Integrador 2 : Definicoes para o Motor Shield
 * Author:			Victor Santos
 * Version:			1.0
 * Last edition:	10/05/2013
 * -------------------------------------------------------------------------- */

#ifndef _MOTORES_H
#define	_MOTORES_H
#define MOTOR_SHIELD_DDR        DDRD
#define MOTOR_SHIELD_PORT       PORTD
#define MOTOR_SHIELD_PIN        PIND
#define MOTOR_INA               PD4             //roda da esquerda
#define MOTOR_INB               PD7             //roda de direita
#define MOTOR_PWMA              PD5
#define MOTOR_PWMB              PD6

void move_motores(int joyX, int joyY);


#endif
