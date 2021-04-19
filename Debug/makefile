################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include startup/subdir.mk
-include src/subdir.mk
-include Utilities/STM32L0538-Discovery/subdir.mk
-include Utilities/Components/stlm75/subdir.mk
-include Utilities/Components/st7735/subdir.mk
-include Utilities/Components/mfxstm32l152/subdir.mk
-include Utilities/Components/hx8347d/subdir.mk
-include Utilities/Components/gde021a1/subdir.mk
-include HAL_Driver/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: xbee2.elf

# Tool invocations
xbee2.elf: $(OBJS) $(USER_OBJS) /Users/grantweiss/Documents/workspace/xbee2/LinkerScript.ld
	@echo 'Building target: $@'
	@echo 'Invoking: MCU GCC Linker'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -T"/Users/grantweiss/Documents/workspace/xbee2/LinkerScript.ld" -Wl,-Map=output.map -Wl,--gc-sections -o "xbee2.elf" @"objects.list" $(USER_OBJS) $(LIBS) -lm
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

post-build:
	-@echo 'Generating binary and Printing size information:'
	arm-none-eabi-objcopy -O binary "xbee2.elf" "xbee2.bin"
	arm-none-eabi-size "xbee2.elf"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
