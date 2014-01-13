// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef robot_bluetoothReceiver_H_
#define robot_bluetoothReceiver_H_
#include "Arduino.h"
//add your includes for the project robot_bluetoothReceiver here
#include "motores.h"
#include "SoftwareSerial.h"
#include "LS_ATmega328.h"
#include "sensorIR.h"
#include "ultrasom.h"
#include "ultrasom_stepper.h"
#include "debug.h"
//end of add your includes here
#ifdef __cplusplus
extern "C" {
#endif
void loop();
void setup();
#ifdef __cplusplus
} // extern "C"
#endif

//add your function definitions for the project robot_bluetoothReceiver here
void sendData(byte button, byte data);
void setLED(int LEDstatus);
void setJoystick_Int(byte data[5]);
byte GetdataByte(void);
void PWM_init(void);
void ADC_init(void);
void stepper_init(void);
void buzzer_init(void);
void switch_init(void);
void stepper_init(void);
//Do not add code below this line
#endif /* robot_bluetoothReceiver_H_ */
