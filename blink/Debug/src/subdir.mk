# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/BlinkLed.c \
../src/Timer.c \
../src/_write.c \
../src/main.c

OBJS += \
./src/BlinkLed.o \
./src/Timer.o \
./src/_write.o \
./src/main.o

C_DEPS += \
./src/BlinkLed.d \
./src/Timer.d \
./src/_write.d \
./src/main.d


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc $(CXXFLAGS) $(INCLUDES) $(GCCFLAGS) -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
