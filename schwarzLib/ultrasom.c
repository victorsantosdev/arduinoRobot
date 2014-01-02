/********************************************************************

Example program to learn interfacing Ultra Sonic Range Finder Module
with AVR ATmega32 Microcontroller.
      
                                     NOTICE
                           --------
NO PART OF THIS WORK CAN BE COPIED, DISTRIBUTED OR PUBLISHED WITHOUT A
WRITTEN PERMISSION FROM EXTREME ELECTRONICS INDIA. THE LIBRARY, NOR ANY PART
OF IT CAN BE USED IN COMMERCIAL APPLICATIONS. IT IS INTENDED TO BE USED FOR
HOBBY, LEARNING AND EDUCATIONAL PURPOSE ONLY. IF YOU WANT TO USE THEM IN 
COMMERCIAL APPLICATION PLEASE WRITE TO THE AUTHOR.

WRITTEN BY:
 *   AVINASH GUPTA
me@avinashgupta.com
 ********************************************************************/

#include "../header/LS_defines.h"
#include "../header/LS_ATmega328.h"
#include "../header/ultrasom.h"
#include "../header/LS_HD44780.h"
#include <util/delay.h>

/********************************************************************

Configuration Area.
UltraSonic (US) sensor connection.

in this example it is connected to PORTA bit 0

Adjust the following to connect is to different i/o

 ********************************************************************

This function measusers the width of high pulse in micro second.

 ********************************************************************/

//globals
uint16_t resp;
int distance;

uint16_t getPulseWidth(void)
{
    uint32_t i = 0, result;

    //Wait for the rising edge
    for (i = 0; i < 600000; i++) {
        if (!(ULTRASOUND_SHIELD_PIN & (1 << ULTRASOUND1_ECHO))) {
            continue;
        } else {
            break;
        }
    }

    if (i == 600000) {
        return US_ERROR; //Indicates time out
    }
    //High Edge Found

    //Setup Timer1
    TCCR1A = 0X00;
    TCCR1B = (1 << CS11); //Prescaler = Fcpu/8
    TCNT1 = 0x00; //Init counter

    //Now wait for the falling edge
    for (i = 0; i < 600000; i++) {
        if (ULTRASOUND_SHIELD_PIN & (1 << ULTRASOUND1_ECHO)) {
            if (TCNT1 > 60000) {
                break;
            } else {
                continue;
            }
        } else {
            break;
        }
    }


    if (i == 600000) {
        return US_ERROR; //Indicates time out
    }
    //Falling edge found

    result = TCNT1;

    //Stop Timer
    TCCR1B = 0x00;

    if (result > 60000) {
        return US_NO_OBSTACLE; //No obstacle
    } else {
        return (result >> 1);
    }
}

uint16_t get_UltrasoundData(void)
{
    int8 obstaculo_sonar = 0;


    //Set Ultra Sonic Port as out
    //set trigger port as output
    set_bit(ULTRASOUND_SHIELD_DDR, ULTRASOUND1_TRIG);
    //turn trigger LOW
    clr_bit(ULTRASOUND_SHIELD_PORT, ULTRASOUND1_TRIG);
    _delay_us(2);
    //turn trigger HIGH
    set_bit(ULTRASOUND_SHIELD_PORT, ULTRASOUND1_TRIG);
    _delay_us(10);
    //trigger pin turn back to LOW
    clr_bit(ULTRASOUND_SHIELD_PORT, ULTRASOUND1_TRIG);

    //set echo as input
    clr_bit(ULTRASOUND_SHIELD_DDR, ULTRASOUND1_ECHO);

    //Measure the width of pulse
    resp = getPulseWidth();

    //Handle Errors
    if (resp == US_ERROR) {
        //LCD_CLEAR_SCREEN();
        //printf("ERROR ON <%d>\n", sensor_n);
        //_delay_ms(500);
        //fazer alguma logica aqui para retornar o erro ao prog principal
    } else if (resp == US_NO_OBSTACLE) {
        //LCD_CLEAR_SCREEN();
        //printf("clear\n");
    } else {

        distance = (resp / 58.0); //Convert to cm
        printf("distancia sonar: %d\n", distance);
        //LCDWriteIntXY(0,0,d,4);
        // LCDWriteString(" cm");
    }
    /* valor de distancia ajustado de acordo com o desejo do usuario*/
    if (distance >= 200 || distance <= 0) {
        obstaculo_sonar = 0x02;
    } else {
        if (distance < 10) { /* 10 centimetros */
            obstaculo_sonar = 1;
        } else {
            obstaculo_sonar = 0;
        }
    }
    return obstaculo_sonar;
}
