################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
$(STD_PERIPH_SRC)/misc.c \
$(STD_PERIPH_SRC)/stm32f10x_gpio.c \
$(STD_PERIPH_SRC)/stm32f10x_rcc.c

OBJS += \
./system/src/stm32f1-stdperiph/misc.o \
./system/src/stm32f1-stdperiph/stm32f10x_gpio.o \
./system/src/stm32f1-stdperiph/stm32f10x_rcc.o

C_DEPS += \
./system/src/stm32f1-stdperiph/misc.d \
./system/src/stm32f1-stdperiph/stm32f10x_gpio.d \
./system/src/stm32f1-stdperiph/stm32f10x_rcc.d


# Each subdirectory must supply rules for building sources it contributes
system/src/stm32f1-stdperiph/%.o: $(STD_PERIPH_SRC)/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc $(CXXFLAGS) $(DEFS) $(INCLUDES) $(GCCFLAGS) -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
