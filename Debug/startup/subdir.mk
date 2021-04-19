################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32l053xx.s 

OBJS += \
./startup/startup_stm32l053xx.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-as -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -I"/Users/grantweiss/Documents/workspace/xbee2/HAL_Driver/Inc/Legacy" -I"/Users/grantweiss/Documents/workspace/xbee2/Utilities/Components/gde021a1" -I"/Users/grantweiss/Documents/workspace/xbee2/Utilities/Components/stlm75" -I"/Users/grantweiss/Documents/workspace/xbee2/Utilities/Components/hx8347d" -I"/Users/grantweiss/Documents/workspace/xbee2/Utilities/Components/Common" -I"/Users/grantweiss/Documents/workspace/xbee2/Utilities/Components/mfxstm32l152" -I"/Users/grantweiss/Documents/workspace/xbee2/inc" -I"/Users/grantweiss/Documents/workspace/xbee2/CMSIS/device" -I"/Users/grantweiss/Documents/workspace/xbee2/CMSIS/core" -I"/Users/grantweiss/Documents/workspace/xbee2/Utilities/STM32L0538-Discovery" -I"/Users/grantweiss/Documents/workspace/xbee2/HAL_Driver/Inc" -I"/Users/grantweiss/Documents/workspace/xbee2/Utilities/Components/st7735" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


