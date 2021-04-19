################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/main.c \
../src/ringBuf.c \
../src/stm32l0xx_it.c \
../src/syscalls.c \
../src/system_stm32l0xx.c \
../src/uart.c \
../src/xbee.c \
../src/xbee2.c 

OBJS += \
./src/main.o \
./src/ringBuf.o \
./src/stm32l0xx_it.o \
./src/syscalls.o \
./src/system_stm32l0xx.o \
./src/uart.o \
./src/xbee.o \
./src/xbee2.o 

C_DEPS += \
./src/main.d \
./src/ringBuf.d \
./src/stm32l0xx_it.d \
./src/syscalls.d \
./src/system_stm32l0xx.d \
./src/uart.d \
./src/xbee.d \
./src/xbee2.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -DSTM32 -DSTM32L0 -DSTM32L053C8Tx -DSTM32L0538_DISCO -DDEBUG -DSTM32L053xx -DUSE_HAL_DRIVER -I"/Users/grantweiss/Documents/workspace/xbee2/HAL_Driver/Inc/Legacy" -I"/Users/grantweiss/Documents/workspace/xbee2/Utilities/Components/gde021a1" -I"/Users/grantweiss/Documents/workspace/xbee2/Utilities/Components/stlm75" -I"/Users/grantweiss/Documents/workspace/xbee2/Utilities/Components/hx8347d" -I"/Users/grantweiss/Documents/workspace/xbee2/Utilities/Components/Common" -I"/Users/grantweiss/Documents/workspace/xbee2/Utilities/Components/mfxstm32l152" -I"/Users/grantweiss/Documents/workspace/xbee2/inc" -I"/Users/grantweiss/Documents/workspace/xbee2/CMSIS/device" -I"/Users/grantweiss/Documents/workspace/xbee2/CMSIS/core" -I"/Users/grantweiss/Documents/workspace/xbee2/Utilities/STM32L0538-Discovery" -I"/Users/grantweiss/Documents/workspace/xbee2/HAL_Driver/Inc" -I"/Users/grantweiss/Documents/workspace/xbee2/Utilities/Components/st7735" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


