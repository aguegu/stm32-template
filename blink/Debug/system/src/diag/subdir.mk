# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../system/src/diag/Trace.c \
../system/src/diag/trace_impl.c

OBJS += \
./system/src/diag/Trace.o \
./system/src/diag/trace_impl.o

C_DEPS += \
./system/src/diag/Trace.d \
./system/src/diag/trace_impl.d


# Each subdirectory must supply rules for building sources it contributes
system/src/diag/%.o: ../system/src/diag/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc $(CXXFLAGS) $(DEFS) $(INCLUDES) $(GCCFLAGS) -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
