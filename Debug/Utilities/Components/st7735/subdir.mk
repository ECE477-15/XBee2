################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Utilities/Components/st7735/st7735.c 

OBJS += \
./Utilities/Components/st7735/st7735.o 

C_DEPS += \
./Utilities/Components/st7735/st7735.d 


# Each subdirectory must supply rules for building sources it contributes
Utilities/Components/st7735/%.o: ../Utilities/Components/st7735/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -DSTM32 -DSTM32L0 -DSTM32L053C8Tx -DSTM32L0538_DISCO -DDEBUG -DSTM32L053xx -DUSE_HAL_DRIVER -I"/Users/grantweiss/Documents/workspace/xbee2/HAL_Driver/Inc/Legacy" -I"/Users/grantweiss/Documents/workspace/xbee2/Utilities/Components/gde021a1" -I"/Users/grantweiss/Documents/workspace/xbee2/Utilities/Components/stlm75" -I"/Users/grantweiss/Documents/workspace/xbee2/Utilities/Components/hx8347d" -I"/Users/grantweiss/Documents/workspace/xbee2/Utilities/Components/Common" -I"/Users/grantweiss/Documents/workspace/xbee2/Utilities/Components/mfxstm32l152" -I"/Users/grantweiss/Documents/workspace/xbee2/inc" -I"/Users/grantweiss/Documents/workspace/xbee2/CMSIS/device" -I"/Users/grantweiss/Documents/workspace/xbee2/CMSIS/core" -I"/Users/grantweiss/Documents/workspace/xbee2/Utilities/STM32L0538-Discovery" -I"/Users/grantweiss/Documents/workspace/xbee2/HAL_Driver/Inc" -I"/Users/grantweiss/Documents/workspace/xbee2/Utilities/Components/st7735" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


