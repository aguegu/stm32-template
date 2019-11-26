################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/src/cmsis/system_stm32f10x.c \
../system/src/cmsis/vectors_stm32f10x.c 

OBJS += \
./system/src/cmsis/system_stm32f10x.o \
./system/src/cmsis/vectors_stm32f10x.o 

C_DEPS += \
./system/src/cmsis/system_stm32f10x.d \
./system/src/cmsis/vectors_stm32f10x.d 


# Each subdirectory must supply rules for building sources it contributes
system/src/cmsis/%.o: ../system/src/cmsis/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc $(CXXFLAGS) $(INCLUDES) $(GCCFLAGS) -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


