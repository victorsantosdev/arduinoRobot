/* -----------------------------------------------------------------------------
 * File:			fsm.c
 * Module:			Projeto Integrador 2 : Controle : Receptor : Maquina de Estados Finita
 * Author:			Victor Santos
 * Version:			1.0
 * Last edition:	10/05/2013
 * -------------------------------------------------------------------------- */

#include "../header/LS_defines.h"
#include "../header/LS_ATmega328.h"
#include "../header/motores.h"
#include "../header/fsm.h"
#include "../header/LS_usart.h"
#include "../header/sensorIR.h"

//debug
//#define DEBUG
//#define sensorir    //habilita ou nao o sensor de obstaculos IR sharp

//defines bluetooth celular
#define CEL_NULL 0x00
#define CEL_FRENTE 0x01
#define CEL_DIREITA 0x02
#define CEL_ESQUERDA 0x03

//defines bluetooth
#define BIT0 PD3
#define BIT1 PD4

#define _NULL (!tst_bit(PIND, BIT0) && !tst_bit(PIND, BIT1))      //00
#define _FRENTE (!tst_bit(PIND, BIT0) && tst_bit(PIND, BIT1))     //01
#define _DIREITA (tst_bit(PIND, BIT0) && !tst_bit(PIND, BIT1))    //10  
#define _ESQUERDA (tst_bit(PIND, BIT0) && tst_bit(PIND, BIT1))    //11  

//global variables

/* -----------------------------------------------------------------------------
 * 
 *
 * Funções de Callback da Máquina de Estados
 * 
 * 
 * -------------------------------------------------------------------------- */
void go_idle(void)
{
    TIMER0_CLOCK_DISABLE(); //inicio sem clock
    TIMER0_CLOCK_PRESCALER_64(); //frequencia de oscilacao de 1KHz
    TIMER0_COMPARE_A_CONFIGURE(0); //duty cycle 50%
    TIMER0_COMPARE_B_CONFIGURE(0); //duty cycle 50%

#ifdef DEBUG
    printf("em idle...\n");
#endif
}

void go_forward(void)
{
    int16 obstaculo = 0;

#ifdef sensorir    
    obstaculo = verificaObstaculo();
    if (obstaculo == 0) {
#endif        
        TIMER0_CLOCK_PRESCALER_64(); //frequencia de oscilacao de 1KHz
        TIMER0_COMPARE_A_CONFIGURE(255); //duty cycle 100%
        TIMER0_COMPARE_B_CONFIGURE(245); //duty cycle 100%
        clr_bit(MOTOR_SHIELD_DDR, MOTOR_INA); //seta a direcao como entrada INA
        clr_bit(MOTOR_SHIELD_DDR, MOTOR_INB); //seta a direcao como entrada INB
        set_bit(MOTOR_SHIELD_PORT, MOTOR_INA); //set_bit : sentido horario, clr_bit: sentido anti-horario
        set_bit(MOTOR_SHIELD_PORT, MOTOR_INB);
#ifdef DEBUG        
        printf("driving forward...\n");
#endif

#ifdef sensorir    

    } else if (obstaculo == 1) {
        go_idle();
        obstaculo = 0;
#ifdef DEBUG
        printf("obstacle, going idle to not crash...\n");
#endif
    }
#endif    
}

void turn_right(void)
{
    TIMER0_CLOCK_PRESCALER_64(); //frequencia de oscilacao de 1KHz
    TIMER0_COMPARE_A_CONFIGURE(255); //duty cycle 100% 
    TIMER0_COMPARE_B_CONFIGURE(0); //duty cycle 25%        //volta mais rapida //era 25% = 64 ou 0 para ficar parado  //teste com 255, era 0 21/julho
    clr_bit(MOTOR_SHIELD_DDR, MOTOR_INA);
    clr_bit(MOTOR_SHIELD_DDR, MOTOR_INB);

    set_bit(MOTOR_SHIELD_PORT, MOTOR_INA); //roda de esquerda em sentido horario
    clr_bit(MOTOR_SHIELD_PORT, MOTOR_INB); //roda da direita no sentido anti-horario
#ifdef DEBUG
    printf("turning right...\n");
#endif
}

void turn_left(void)
{
    TIMER0_CLOCK_PRESCALER_64(); //frequencia de oscilacao de 1KHz
    TIMER0_COMPARE_A_CONFIGURE(0); //duty cycle 25% //era 25% = 64 ou 0 para parar totalmente o motor  //teste com 255, era 0 21/julho
    TIMER0_COMPARE_B_CONFIGURE(255); //duty cycle 100% 
    clr_bit(MOTOR_SHIELD_DDR, MOTOR_INA);
    clr_bit(MOTOR_SHIELD_DDR, MOTOR_INB);

    clr_bit(MOTOR_SHIELD_PORT, MOTOR_INA); //roda de esquerda em sentido anti-horario
    set_bit(MOTOR_SHIELD_PORT, MOTOR_INB); //roda da direita no sentido horario
#ifdef DEBUG
    printf("turning left...\n");
#endif
}

void go_back(void)
{
    TIMER0_CLOCK_PRESCALER_64(); //frequencia de oscilacao de 1KHz
    TIMER0_COMPARE_A_CONFIGURE(255); //duty cycle 100%
    TIMER0_COMPARE_B_CONFIGURE(255); //duty cycle 100%
    set_bit(MOTOR_SHIELD_DDR, MOTOR_INA);
    set_bit(MOTOR_SHIELD_DDR, MOTOR_INB);
    clr_bit(MOTOR_SHIELD_PORT, MOTOR_INA); //inversao de sentido nas duas rodas
    clr_bit(MOTOR_SHIELD_PORT, MOTOR_INB);
#ifdef DEBUG
    printf("driving back...\n");
#endif
}

/* -------------------------------------------------------------------------- */

/* -----------------------------------------------------------------------------
 * 
 *
 * Funções para tratar o modo autônomo
 * 
 * 
 * -------------------------------------------------------------------------- */
uint8_t getDadosBT(void)
{
    int8 data = 0;
    int8 flag = 0;

    if (_NULL) {
        if (flag == 0) {
            data = CEL_NULL;
            flag = 1;
        }
    } else if (_DIREITA) {
        if (flag == 0) {
            data = CEL_DIREITA;
            flag = 1;
        }
    } else if (_ESQUERDA) {
        if (flag == 0) {
            data = CEL_ESQUERDA;
            flag = 1;
        }
    } else if (_FRENTE) {
        if (flag == 0) {
            data = CEL_FRENTE;
            flag = 1;
        }
    }
    flag = 0;

    return data;
}

void segue_coordenadas(int8 dados)
{
    //o objetivo é centralizar a bolinha antes de seguir em frente    

    int16 obstaculo = 0;

    switch (dados) {

    case CEL_DIREITA:
        turn_right();
#ifdef DEBUG
        printf("cellphone turning right...\n");
#endif
        break;

    case CEL_ESQUERDA:
        turn_left();
#ifdef DEBUG
        printf("cellphone turning left...\n");
#endif
        break;

    case CEL_FRENTE:
#ifdef sensorir    
        obstaculo = verificaObstaculo();
        if (obstaculo == 0) {
#endif   
            go_forward();
#ifdef DEBUG

            printf("no obstacle, go ahead...\n");
#endif
#ifdef sensorir    

        } else if (obstaculo == 1) {
            go_idle(); 
            obstaculo = 0;
#ifdef DEBUG
            printf("obstacle, going idle to not crash...\n");
#endif
        }
#endif       

    default:
        break;

    }

}

void go_autonomo(int flag)
{
    int8_t dados_tmp[3] = {0, 0, 0};
    int8_t dado_correto = 0;

    if (flag == 1) {
#ifdef DEBUG
        printf("Autonomous MODE: ON...\n");
#endif
        dados_tmp[0] = getDadosBT();
#ifdef DEBUG       
        printf("tmp0:   \n\n%d\n\n", dados_tmp[0]);
#endif
        _delay_ms(20);

        dados_tmp[1] = getDadosBT();
#ifdef DEBUG
        printf("tmp1:   \n\n%d\n\n", dados_tmp[1]);
#endif        
        _delay_ms(20);
        dados_tmp[2] = getDadosBT();
#ifdef DEBUG
        printf("tmp2:   \n\n%d\n\n", dados_tmp[2]);
#endif        

        if ((dados_tmp[0] == dados_tmp[1]) && (dados_tmp[0] == dados_tmp[2])) {
            dado_correto = dados_tmp[0];
#ifdef DEBUG
            printf("DADO_CORRETO:   \n\n%d\n\n", dado_correto);
#endif            
            switch (dado_correto) {

            case CEL_NULL:
#ifdef DEBUG
                printf("recebi null, vou procurar esta bolinha! %d\n", dado_correto);
#endif
                turn_right();
                break;

            case CEL_FRENTE:
#ifdef DEBUG
                printf("recebi o dado: %d : tenho que ir para frente\n", dado_correto);
#endif
                segue_coordenadas(dado_correto);
                break;

            case CEL_DIREITA:
#ifdef DEBUG
                printf("recebi o dado: %d : tenho que ir para direita\n", dado_correto);
#endif
                segue_coordenadas(dado_correto);
                break;

            case CEL_ESQUERDA:
#ifdef DEBUG
                printf("recebi o dado: %d : tenho que ir para esquerda\n", dado_correto);
#endif
                segue_coordenadas(dado_correto);
                break;

            default:
#ifdef DEBUG
                printf("nao sei o que recebi, vou ficar parado: %d\n", dado_correto);
#endif
                go_idle(); //se nao sabe o que recebe fica parado
                break;
            }

        } else {
            go_idle(); //se nao sabe o que faz, nao faz nada
#ifdef DEBUG
            printf("estou parado, nao sei aonde esta a bolinha...\n");
#endif
        }

    } else {
        //garante que o carrinho nao se mexe se flag = 0
        go_idle();

    }

    dados_tmp[0] = 0;
    dados_tmp[1] = 0;
    dados_tmp[2] = 0;

    dado_correto = 0;
}

