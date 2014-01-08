################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/victor/arduino/arduino-1.0.5/libraries/SoftwareSerial/SoftwareSerial.cpp 

OBJS += \
./SoftwareSerial/SoftwareSerial.o 

CPP_DEPS += \
./SoftwareSerial/SoftwareSerial.d 


# Each subdirectory must supply rules for building sources it contributes
SoftwareSerial/SoftwareSerial.o: /home/victor/arduino/arduino-1.0.5/libraries/SoftwareSerial/SoftwareSerial.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino -I/home/victor/workspace/avr_work/misc_libs -I"/home/victor/workspace/avr_work/robot_bluetoothReceiver" -I/home/victor/arduino/arduino-1.0.5/hardware/arduino/variants/standard -I/home/victor/workspace/avr_work/schwarzLib -I"/home/victor/workspace/avr_work/robot_bluetoothReceiver" -I"/home/victor/arduino/arduino-1.0.5/libraries/SoftwareSerial" -D__IN_ECLIPSE__=1 -DUSB_VID= -DUSB_PID= -DARDUINO=105 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '


