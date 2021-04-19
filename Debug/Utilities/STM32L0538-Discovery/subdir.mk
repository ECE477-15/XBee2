################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Utilities/STM32L0538-Discovery/font12epd.c \
../Utilities/STM32L0538-Discovery/font16epd.c \
../Utilities/STM32L0538-Discovery/font20epd.c \
../Utilities/STM32L0538-Discovery/font8epd.c \
../Utilities/STM32L0538-Discovery/stm32l0538_discovery.c \
../Utilities/STM32L0538-Discovery/stm32l0538_discovery_epd.c 

OBJS += \
./Utilities/STM32L0538-Discovery/font12epd.o \
./Utilities/STM32L0538-Discovery/font16epd.o \
./Utilities/STM32L0538-Discovery/font20epd.o \
./Utilities/STM32L0538-Discovery/font8epd.o \
./Utilities/STM32L0538-Discovery/stm32l0538_discovery.o \
./Utilities/STM32L0538-Discovery/stm32l0538_discovery_epd.o 

C_DEPS += \
./Utilities/STM32L0538-Discovery/font12epd.d \
./Utilities/STM32L0538-Discovery/font16epd.d \
./Utilities/STM32L0538-Discovery/font20epd.d \
./Utilities/STM32L0538-Discovery/font8epd.d \
./Utilities/STM32L0538-Discovery/stm32l0538_discovery.d \
./Utilities/STM32L0538-Discovery/stm32l0538_discovery_epd.d 


# Each subdirectory must supply rules for building sources it contributes
Utilities/STM32L0538-Discovery/%.o: ../Utilities/STM32L0538-Discovery/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -DSTM32 -DSTM32L0 -DSTM32L053C8Tx -DSTM32L0538_DISCO -DDEBUG -DSTM32L053xx -DUSE_HAL_DRIVER -I"/Users/grantweiss/Documents/workspace/xbee2/HAL_Driver/Inc/Legacy" -I"/Users/grantweiss/Documents/workspace/xbee2/Utilities/Components/gde021a1" -I"/Users/grantweiss/Documents/workspace/xbee2/Utilities/Components/stlm75" -I"/Users/grantweiss/Documents/workspace/xbee2/Utilities/Components/hx8347d" -I"/Users/grantweiss/Documents/workspace/xbee2/Utilities/Components/Common" -I"/Users/grantweiss/Documents/workspace/xbee2/Utilities/Components/mfxstm32l152" -I"/Users/grantweiss/Documents/workspace/xbee2/inc" -I"/Users/grantweiss/Documents/workspace/xbee2/CMSIS/device" -I"/Users/grantweiss/Documents/workspace/xbee2/CMSIS/core" -I"/Users/grantweiss/Documents/workspace/xbee2/Utilities/STM32L0538-Discovery" -I"/Users/grantweiss/Documents/workspace/xbee2/HAL_Driver/Inc" -I"/Users/grantweiss/Documents/workspace/xbee2/Utilities/Components/st7735" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


