################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/Lab\ G.c 

OBJS += \
./source/Lab\ G.o 

C_DEPS += \
./source/Lab\ G.d 


# Each subdirectory must supply rules for building sources it contributes
source/Lab\ G.o: ../source/Lab\ G.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_LPC802M001JDH20 -DCPU_LPC802M001JDH20_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I../board -I../source -I../ -I../drivers -I../device -I../CMSIS -I../component/uart -I../utilities -I../board/boards -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"source/Lab G.d" -MT"source/Lab\ G.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


