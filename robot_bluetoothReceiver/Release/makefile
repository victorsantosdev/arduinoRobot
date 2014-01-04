################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include arduino/avr-libc/subdir.mk
-include arduino/subdir.mk
-include SoftwareSerial/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
robot_bluetoothReceiver.lss \

FLASH_IMAGE += \
robot_bluetoothReceiver.hex \

EEPROM_IMAGE += \
robot_bluetoothReceiver.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: robot_bluetoothReceiver.elf secondary-outputs

dependents:
	-cd /home/victor/workspace/avr_work/ArduinoCore/Release && $(MAKE) all

# Tool invocations
robot_bluetoothReceiver.elf: $(OBJS) $(USER_OBJS) /home/victor/workspace/avr_work/ArduinoCore/Release/libArduinoCore.a
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C++ Linker'
	avr-gcc -s -Os -o"robot_bluetoothReceiver.elf" $(OBJS) $(USER_OBJS) $(LIBS) -lm -L"/Release" -L"/home/victor/workspace/avr_work/ArduinoCore/Release" -mmcu=atmega328p
	@echo 'Finished building target: $@'
	@echo ' '

robot_bluetoothReceiver.lss: robot_bluetoothReceiver.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S robot_bluetoothReceiver.elf  >"robot_bluetoothReceiver.lss"
	@echo 'Finished building: $@'
	@echo ' '

robot_bluetoothReceiver.hex: robot_bluetoothReceiver.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex robot_bluetoothReceiver.elf  "robot_bluetoothReceiver.hex"
	@echo 'Finished building: $@'
	@echo ' '

robot_bluetoothReceiver.eep: robot_bluetoothReceiver.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex robot_bluetoothReceiver.elf  "robot_bluetoothReceiver.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: robot_bluetoothReceiver.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p robot_bluetoothReceiver.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(CXX_DEPS)$(S_UPPER_DEPS)$(C++_DEPS)$(ASM_DEPS)$(CC_DEPS)$(CPP_DEPS)$(C_UPPER_DEPS)$(SIZEDUMMY) robot_bluetoothReceiver.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:
/home/victor/workspace/avr_work/ArduinoCore/Release/libArduinoCore.a:

-include ../makefile.targets
