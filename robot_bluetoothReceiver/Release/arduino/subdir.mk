################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/CDC.o \
/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/HID.o \
/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/HardwareSerial.o \
/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/IPAddress.o \
/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/Print.o \
/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/Stream.o \
/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/Tone.o \
/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/USBCore.o \
/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/WInterrupts.o \
/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/WMath.o \
/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/WString.o \
/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/main.o \
/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/new.o \
/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/wiring.o \
/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/wiring_analog.o \
/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/wiring_digital.o \
/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/wiring_pulse.o \
/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/wiring_shift.o 

CPP_SRCS += \
/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/CDC.cpp \
/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/HID.cpp \
/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/HardwareSerial.cpp \
/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/IPAddress.cpp \
/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/Print.cpp \
/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/Stream.cpp \
/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/Tone.cpp \
/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/USBCore.cpp \
/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/WMath.cpp \
/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/WString.cpp \
/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/main.cpp \
/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/new.cpp 

C_SRCS += \
/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/WInterrupts.c \
/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/wiring.c \
/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/wiring_analog.c \
/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/wiring_digital.c \
/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/wiring_pulse.c \
/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/wiring_shift.c 

OBJS += \
./arduino/CDC.o \
./arduino/HID.o \
./arduino/HardwareSerial.o \
./arduino/IPAddress.o \
./arduino/Print.o \
./arduino/Stream.o \
./arduino/Tone.o \
./arduino/USBCore.o \
./arduino/WInterrupts.o \
./arduino/WMath.o \
./arduino/WString.o \
./arduino/main.o \
./arduino/new.o \
./arduino/wiring.o \
./arduino/wiring_analog.o \
./arduino/wiring_digital.o \
./arduino/wiring_pulse.o \
./arduino/wiring_shift.o 

C_DEPS += \
./arduino/WInterrupts.d \
./arduino/wiring.d \
./arduino/wiring_analog.d \
./arduino/wiring_digital.d \
./arduino/wiring_pulse.d \
./arduino/wiring_shift.d 

CPP_DEPS += \
./arduino/CDC.d \
./arduino/HID.d \
./arduino/HardwareSerial.d \
./arduino/IPAddress.d \
./arduino/Print.d \
./arduino/Stream.d \
./arduino/Tone.d \
./arduino/USBCore.d \
./arduino/WMath.d \
./arduino/WString.d \
./arduino/main.d \
./arduino/new.d 


# Each subdirectory must supply rules for building sources it contributes
arduino/CDC.o: /home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/CDC.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino -I/home/victor/workspace/avr_work/misc_libs -I"/home/victor/workspace/avr_work/robot_bluetoothReceiver" -I/home/victor/arduino/arduino-1.0.5/hardware/arduino/variants/standard -I/home/victor/workspace/avr_work/schwarzLib -I"/home/victor/workspace/avr_work/robot_bluetoothReceiver" -I"/home/victor/arduino/arduino-1.0.5/libraries/SoftwareSerial" -D__IN_ECLIPSE__=1 -DUSB_VID= -DUSB_PID= -DARDUINO=105 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '

arduino/HID.o: /home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/HID.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino -I/home/victor/workspace/avr_work/misc_libs -I"/home/victor/workspace/avr_work/robot_bluetoothReceiver" -I/home/victor/arduino/arduino-1.0.5/hardware/arduino/variants/standard -I/home/victor/workspace/avr_work/schwarzLib -I"/home/victor/workspace/avr_work/robot_bluetoothReceiver" -I"/home/victor/arduino/arduino-1.0.5/libraries/SoftwareSerial" -D__IN_ECLIPSE__=1 -DUSB_VID= -DUSB_PID= -DARDUINO=105 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '

arduino/HardwareSerial.o: /home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/HardwareSerial.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino -I/home/victor/workspace/avr_work/misc_libs -I"/home/victor/workspace/avr_work/robot_bluetoothReceiver" -I/home/victor/arduino/arduino-1.0.5/hardware/arduino/variants/standard -I/home/victor/workspace/avr_work/schwarzLib -I"/home/victor/workspace/avr_work/robot_bluetoothReceiver" -I"/home/victor/arduino/arduino-1.0.5/libraries/SoftwareSerial" -D__IN_ECLIPSE__=1 -DUSB_VID= -DUSB_PID= -DARDUINO=105 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '

arduino/IPAddress.o: /home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/IPAddress.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino -I/home/victor/workspace/avr_work/misc_libs -I"/home/victor/workspace/avr_work/robot_bluetoothReceiver" -I/home/victor/arduino/arduino-1.0.5/hardware/arduino/variants/standard -I/home/victor/workspace/avr_work/schwarzLib -I"/home/victor/workspace/avr_work/robot_bluetoothReceiver" -I"/home/victor/arduino/arduino-1.0.5/libraries/SoftwareSerial" -D__IN_ECLIPSE__=1 -DUSB_VID= -DUSB_PID= -DARDUINO=105 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '

arduino/Print.o: /home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/Print.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino -I/home/victor/workspace/avr_work/misc_libs -I"/home/victor/workspace/avr_work/robot_bluetoothReceiver" -I/home/victor/arduino/arduino-1.0.5/hardware/arduino/variants/standard -I/home/victor/workspace/avr_work/schwarzLib -I"/home/victor/workspace/avr_work/robot_bluetoothReceiver" -I"/home/victor/arduino/arduino-1.0.5/libraries/SoftwareSerial" -D__IN_ECLIPSE__=1 -DUSB_VID= -DUSB_PID= -DARDUINO=105 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '

arduino/Stream.o: /home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/Stream.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino -I/home/victor/workspace/avr_work/misc_libs -I"/home/victor/workspace/avr_work/robot_bluetoothReceiver" -I/home/victor/arduino/arduino-1.0.5/hardware/arduino/variants/standard -I/home/victor/workspace/avr_work/schwarzLib -I"/home/victor/workspace/avr_work/robot_bluetoothReceiver" -I"/home/victor/arduino/arduino-1.0.5/libraries/SoftwareSerial" -D__IN_ECLIPSE__=1 -DUSB_VID= -DUSB_PID= -DARDUINO=105 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '

arduino/Tone.o: /home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/Tone.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino -I/home/victor/workspace/avr_work/misc_libs -I"/home/victor/workspace/avr_work/robot_bluetoothReceiver" -I/home/victor/arduino/arduino-1.0.5/hardware/arduino/variants/standard -I/home/victor/workspace/avr_work/schwarzLib -I"/home/victor/workspace/avr_work/robot_bluetoothReceiver" -I"/home/victor/arduino/arduino-1.0.5/libraries/SoftwareSerial" -D__IN_ECLIPSE__=1 -DUSB_VID= -DUSB_PID= -DARDUINO=105 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '

arduino/USBCore.o: /home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/USBCore.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino -I/home/victor/workspace/avr_work/misc_libs -I"/home/victor/workspace/avr_work/robot_bluetoothReceiver" -I/home/victor/arduino/arduino-1.0.5/hardware/arduino/variants/standard -I/home/victor/workspace/avr_work/schwarzLib -I"/home/victor/workspace/avr_work/robot_bluetoothReceiver" -I"/home/victor/arduino/arduino-1.0.5/libraries/SoftwareSerial" -D__IN_ECLIPSE__=1 -DUSB_VID= -DUSB_PID= -DARDUINO=105 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '

arduino/WInterrupts.o: /home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/WInterrupts.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino -I/home/victor/workspace/avr_work/misc_libs -I"/home/victor/workspace/avr_work/robot_bluetoothReceiver" -I/home/victor/arduino/arduino-1.0.5/hardware/arduino/variants/standard -I/home/victor/workspace/avr_work/schwarzLib -I"/home/victor/workspace/avr_work/robot_bluetoothReceiver" -I"/home/victor/arduino/arduino-1.0.5/libraries/SoftwareSerial" -D__IN_ECLIPSE__=1 -DARDUINO=105 -DUSB_PID= -DUSB_VID= -Wall -Os -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

arduino/WMath.o: /home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/WMath.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino -I/home/victor/workspace/avr_work/misc_libs -I"/home/victor/workspace/avr_work/robot_bluetoothReceiver" -I/home/victor/arduino/arduino-1.0.5/hardware/arduino/variants/standard -I/home/victor/workspace/avr_work/schwarzLib -I"/home/victor/workspace/avr_work/robot_bluetoothReceiver" -I"/home/victor/arduino/arduino-1.0.5/libraries/SoftwareSerial" -D__IN_ECLIPSE__=1 -DUSB_VID= -DUSB_PID= -DARDUINO=105 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '

arduino/WString.o: /home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/WString.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino -I/home/victor/workspace/avr_work/misc_libs -I"/home/victor/workspace/avr_work/robot_bluetoothReceiver" -I/home/victor/arduino/arduino-1.0.5/hardware/arduino/variants/standard -I/home/victor/workspace/avr_work/schwarzLib -I"/home/victor/workspace/avr_work/robot_bluetoothReceiver" -I"/home/victor/arduino/arduino-1.0.5/libraries/SoftwareSerial" -D__IN_ECLIPSE__=1 -DUSB_VID= -DUSB_PID= -DARDUINO=105 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '

arduino/main.o: /home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/main.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino -I/home/victor/workspace/avr_work/misc_libs -I"/home/victor/workspace/avr_work/robot_bluetoothReceiver" -I/home/victor/arduino/arduino-1.0.5/hardware/arduino/variants/standard -I/home/victor/workspace/avr_work/schwarzLib -I"/home/victor/workspace/avr_work/robot_bluetoothReceiver" -I"/home/victor/arduino/arduino-1.0.5/libraries/SoftwareSerial" -D__IN_ECLIPSE__=1 -DUSB_VID= -DUSB_PID= -DARDUINO=105 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '

arduino/new.o: /home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/new.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino -I/home/victor/workspace/avr_work/misc_libs -I"/home/victor/workspace/avr_work/robot_bluetoothReceiver" -I/home/victor/arduino/arduino-1.0.5/hardware/arduino/variants/standard -I/home/victor/workspace/avr_work/schwarzLib -I"/home/victor/workspace/avr_work/robot_bluetoothReceiver" -I"/home/victor/arduino/arduino-1.0.5/libraries/SoftwareSerial" -D__IN_ECLIPSE__=1 -DUSB_VID= -DUSB_PID= -DARDUINO=105 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '

arduino/wiring.o: /home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/wiring.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino -I/home/victor/workspace/avr_work/misc_libs -I"/home/victor/workspace/avr_work/robot_bluetoothReceiver" -I/home/victor/arduino/arduino-1.0.5/hardware/arduino/variants/standard -I/home/victor/workspace/avr_work/schwarzLib -I"/home/victor/workspace/avr_work/robot_bluetoothReceiver" -I"/home/victor/arduino/arduino-1.0.5/libraries/SoftwareSerial" -D__IN_ECLIPSE__=1 -DARDUINO=105 -DUSB_PID= -DUSB_VID= -Wall -Os -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

arduino/wiring_analog.o: /home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/wiring_analog.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino -I/home/victor/workspace/avr_work/misc_libs -I"/home/victor/workspace/avr_work/robot_bluetoothReceiver" -I/home/victor/arduino/arduino-1.0.5/hardware/arduino/variants/standard -I/home/victor/workspace/avr_work/schwarzLib -I"/home/victor/workspace/avr_work/robot_bluetoothReceiver" -I"/home/victor/arduino/arduino-1.0.5/libraries/SoftwareSerial" -D__IN_ECLIPSE__=1 -DARDUINO=105 -DUSB_PID= -DUSB_VID= -Wall -Os -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

arduino/wiring_digital.o: /home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/wiring_digital.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino -I/home/victor/workspace/avr_work/misc_libs -I"/home/victor/workspace/avr_work/robot_bluetoothReceiver" -I/home/victor/arduino/arduino-1.0.5/hardware/arduino/variants/standard -I/home/victor/workspace/avr_work/schwarzLib -I"/home/victor/workspace/avr_work/robot_bluetoothReceiver" -I"/home/victor/arduino/arduino-1.0.5/libraries/SoftwareSerial" -D__IN_ECLIPSE__=1 -DARDUINO=105 -DUSB_PID= -DUSB_VID= -Wall -Os -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

arduino/wiring_pulse.o: /home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/wiring_pulse.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino -I/home/victor/workspace/avr_work/misc_libs -I"/home/victor/workspace/avr_work/robot_bluetoothReceiver" -I/home/victor/arduino/arduino-1.0.5/hardware/arduino/variants/standard -I/home/victor/workspace/avr_work/schwarzLib -I"/home/victor/workspace/avr_work/robot_bluetoothReceiver" -I"/home/victor/arduino/arduino-1.0.5/libraries/SoftwareSerial" -D__IN_ECLIPSE__=1 -DARDUINO=105 -DUSB_PID= -DUSB_VID= -Wall -Os -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

arduino/wiring_shift.o: /home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/wiring_shift.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino -I/home/victor/workspace/avr_work/misc_libs -I"/home/victor/workspace/avr_work/robot_bluetoothReceiver" -I/home/victor/arduino/arduino-1.0.5/hardware/arduino/variants/standard -I/home/victor/workspace/avr_work/schwarzLib -I"/home/victor/workspace/avr_work/robot_bluetoothReceiver" -I"/home/victor/arduino/arduino-1.0.5/libraries/SoftwareSerial" -D__IN_ECLIPSE__=1 -DARDUINO=105 -DUSB_PID= -DUSB_VID= -Wall -Os -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


