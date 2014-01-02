/* -----------------------------------------------------------------------------
 * File:			fsm.h
 * Module:			Projeto Integrador 2 : Controle : Receptor : Maquina de Estados Finita
 * Author:			Victor Santos
 * Version:			1.0
 * Last edition:	10/05/2013
 * -------------------------------------------------------------------------- */

#ifndef _FSM_H
#define	_FSM_H

//state machine definitions
#define EVENTS_COUNT 5
#define STATES_COUNT 5
#define EVENT_QUEUE_SIZE 5

//globals to use in C file

typedef enum STATE {
    STATE_IDLE,
    STATE_MOVING_FORWARD,
    STATE_MOVING_BACK,
    STATE_TURN_LEFT,
    STATE_TURN_RIGHT,        
} STATE;

typedef enum EVENT {
    EVENT_GO_IDLE,
    EVENT_GO_FORWARD,
    EVENT_GO_BACK,
    EVENT_TURN_LEFT,
    EVENT_TURN_RIGHT,
} EVENT;


typedef void (*TPF)();

typedef struct TRANSITION {
    STATE next_state;
    TPF action;
} TRANSITION;


//fsm callback functions prototypes
void go_idle(void);
void go_forward(void);
void turn_right(void);
void turn_left(void);
void go_back(void);
void go_autonomo(int flag);

//generic function for BT data acquisition
uint8_t getDadosBT(void);

//gira o carrinho se o celular mandar null
int8 procura_bolinha(void);
void segue_coordenadas(int8 dados);
#endif	/* FSM_H */

