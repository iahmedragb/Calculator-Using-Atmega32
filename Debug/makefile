################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/EXTI/subdir.mk
-include MCAL/EEPROM/subdir.mk
-include MCAL/DIO/subdir.mk
-include MCAL/ADC/subdir.mk
-include HAL/Switch/subdir.mk
-include HAL/SSD/subdir.mk
-include HAL/Relay/subdir.mk
-include HAL/LED/subdir.mk
-include HAL/LCD/subdir.mk
-include HAL/Keypad/subdir.mk
-include HAL/Buzzer/subdir.mk
-include APP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Fully_Functional_Calculator.lss \

SIZEDUMMY += \
sizedummy \


# All Target
all: Fully_Functional_Calculator.elf secondary-outputs

# Tool invocations
Fully_Functional_Calculator.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Fully_Functional_Calculator.map -mmcu=atmega32 -o "Fully_Functional_Calculator.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Fully_Functional_Calculator.lss: Fully_Functional_Calculator.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Fully_Functional_Calculator.elf  >"Fully_Functional_Calculator.lss"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Fully_Functional_Calculator.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 Fully_Functional_Calculator.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Fully_Functional_Calculator.elf
	-@echo ' '

secondary-outputs: $(LSS) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
