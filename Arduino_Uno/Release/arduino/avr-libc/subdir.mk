################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/avr-libc/malloc.c \
/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/avr-libc/realloc.c 

OBJS += \
./arduino/avr-libc/malloc.o \
./arduino/avr-libc/realloc.o 

C_DEPS += \
./arduino/avr-libc/malloc.d \
./arduino/avr-libc/realloc.d 


# Each subdirectory must supply rules for building sources it contributes
arduino/avr-libc/malloc.o: /home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/avr-libc/malloc.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I/home/victor/arduino/arduino-1.0.5/hardware/arduino/variants/standard -I/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino -DUSB_VID= -DUSB_PID= -DARDUINO=105 -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -g  -ffunction-sections  -fdata-sections -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

arduino/avr-libc/realloc.o: /home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino/avr-libc/realloc.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I/home/victor/arduino/arduino-1.0.5/hardware/arduino/variants/standard -I/home/victor/arduino/arduino-1.0.5/hardware/arduino/cores/arduino -DUSB_VID= -DUSB_PID= -DARDUINO=105 -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -g  -ffunction-sections  -fdata-sections -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


