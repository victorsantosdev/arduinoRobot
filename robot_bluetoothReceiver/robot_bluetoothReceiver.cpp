/*
 * robot_bluetoothReceiver.cpp
 * Função principal do robô
 * Trata o recebimento dos comandos do módulo bluetooth
 *
 *  Created on: Dec 30, 2013
 *      Author: victor
 */

// Do not remove the include below
#include "robot_bluetoothReceiver.h"

// V9.0: ** Release for Android BT Commander V3.0 AND HIGHER ONLY **

#define    DEBUG        true
//  Arduino pin#2 to TX BlueTooth module
//  Arduino pin#3 to RX BlueTooth module
#define    STX          0x02		//start TX: inicio do protocolo de envio
#define    ETX          0x03		//end TX:	fim do protocolo de envio

//global variables
SoftwareSerial mySerial(2,3);         // BlueTooth module: pin#2=TX pin#3=RX
int i=0;
byte cmd[6] = {0, 0, 0, 0, 0, 0};     // bytes received : protocolo de 6 bytes <STX MSB-X LSB-X MSB-Y LSB-Y ETX>
long previousMillis = 0;              // will store last Buttons status was updated
long interval = 1000;                 // interval to transmit Buttons status (milliseconds)
byte dataByte = 0;                    // second Byte sent to Android device
byte buttonStatus = 0;                // first Byte sent to Android device
byte flagAutonomo = 0;

void sendData(byte button, byte data)    {
	mySerial.write(STX); mySerial.write((button<<2)+4); mySerial.write(data+4); mySerial.write(ETX); // +4: avoid 0x2 & 0x3
}

void PWM_init(void) {
	pinMode(MOTOR_PWMA,OUTPUT);
	pinMode(MOTOR_PWMB, OUTPUT);

	//TIMER 0 config: PWM
	//TIMER0_CLOCK_PRESCALER_OFF(); //prescaler = 1
	TIMER0_FAST_PWM_MAX_MODE();
	TIMER0_OC0A_CLEAR_ON_COMPARE();
	TIMER0_OC0B_CLEAR_ON_COMPARE();
	Serial.println("PWM setup DONE...");
}

void ADC_init(void) {
	DDRC = 0x00;

	//ADC em 10bits : usado no sensoriamento IR : sem shift left ou right
	ADC_REFERENCE_AREF(); //referencia do ADC em 5V
	ADC_CLOCK_PRESCALER_16(); /* a frequência original do ADC neste projeto era 125KHz (PS = 128), estou tentando amostrar mais rápido em 1MHzz
	                                  existe perda de precisão quando trabalhamos em 10bits com uma frequencia de amostragem maior que 200KHz, mas para este caso
	                                  acaba não sendo tão crucial assim.*/
	ADC_ENABLE();
	ADC_SELECT_CHANNEL_0();
	ADC_DIGITAL_INPUT_0_DISABLE();
	ADC_START_CONVERSION(); //descarto a primeira amostra, que leva 25 ciclos de clock
	ADC_WAIT_CONVERSION_FINISH();
	Serial.println("ADC setup DONE...");
}

void setup()  {

	Serial.begin(57600);
	mySerial.begin(9600);   //9600           // 57600 = max value for softserial
	Serial.println("Projeto robô usando Android Joystick BT commander V3.0");
	Serial.println("Setup...");
	//configura o PWM do motor
	Serial.println("Enter PWM init...");
	PWM_init();
	//configura o ADC
	Serial.println("Enter ADC init...");
	ADC_init();

	//habilita as mascaras de interrupcao
	sei();
	delay(300);
}

void setLED(int LEDstatus)  {
	switch (LEDstatus) {
	case '1':
		buttonStatus |= 0b0001;    // Button_1: ON
		Serial.println("Button_1: ON");
		// your code...
		Serial.println("AUTO mode ON...");
		flagAutonomo = 1;
		break;
	case '2':
		buttonStatus &= 0b1110;    // Button_1: OFF
		Serial.println("Button_1: OFF");
		// your code...
		Serial.println("AUTO mode OFF...");
		flagAutonomo = 0;
		break;
	case '3':
		buttonStatus |= 0b0010;    // Button_2: ON
		Serial.println("Button_2: ON");
		// your code...
		break;
	case '4':
		buttonStatus &= 0b1101;    // Button_2: OFF
		Serial.println("Button_2: OFF");
		// your code...
		break;
	case '5':                    // configured as momentary button
		//      buttonStatus |= B0100;     // Button_3: ON
		Serial.println("Button_3: ON");
		// your code...
		break;
		//    case '6':
		//      buttonStatus &= B1011;     // Button_3: OFF
		//      Serial.println("Button_3: OFF");
		//      // your code...
		//      break;
	case '7':                    // configured as momentary button
		//      buttonStatus |= B1000;     // Button_4: ON
		Serial.println("Button_4: ON");
		// your code...
		break;
		//    case '8':
		//      buttonStatus &= B0111;    // Button_4: OFF
		//      Serial.println("Button_4: OFF");
		//      // your code...
		//      break;
	}
	sendData(buttonStatus, dataByte);
}

void setJoystick_Int(byte data[5])    {
	// Demo
	int joyX = (data[1]<<7) + data[2];
	int joyY = (data[3]<<7) + data[4];
	joyX = joyX - 200;               // Transmission offset = 110
	joyY = joyY - 200;               // to avoid negative numbers

	Serial.print("Joystick data: X: ");
	Serial.print(joyX);
	Serial.print(", Y:");
	Serial.println(joyY);
	// Your code here ...
	move_motores(joyX, joyY);

}

byte GetdataByte()  {
	// Demo
	static byte i=0;
	i +=5;
	if(i >100)    i = 0;
	return i;

	// Your code ...
}


void loop() {
	if(mySerial.available())  {            // received from smartphone
		delay(5);
		cmd[0] =  mySerial.read();
		if(DEBUG)  Serial.println(cmd[0]);   // to serial monitor
		if(cmd[0] == STX)  { //identifica inicio de protocolo
			i=1;
			while(mySerial.available() && ((cmd[i]=mySerial.read()) != ETX)) { //enquanto nao recebe o fim do protocolo (ETX) fica em loop recebendo dados
				if(i>5)  break;
				if(DEBUG)    {Serial.print(i); Serial.print(": "); Serial.println(cmd[i]);}
				i++;
			}
		}
		if(i==2)    setLED(cmd[1]);
		else if(i==5)    setJoystick_Int(cmd);  // 6 Bytes: recebeu todos os 6 bytes
		else Serial.println("****");
	}  else  {
		unsigned long currentMillis = millis();
		if(currentMillis - previousMillis > interval) {		//para nao implementar timer foi utilizado um sistema recursivo de cálculo de tempo
			dataByte = GetdataByte();
			sendData(buttonStatus, dataByte);
			previousMillis = currentMillis;
		}
	}
	delay(5);
}





