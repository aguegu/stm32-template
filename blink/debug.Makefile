RM := rm -rf

ELF_SRCS :=
C_UPPER_SRCS :=
CXX_SRCS :=
C++_SRCS :=
OBJ_SRCS :=
CC_SRCS :=
ASM_SRCS :=
C_SRCS :=
CPP_SRCS :=
S_UPPER_SRCS :=
O_SRCS :=
CC_DEPS :=
C++_DEPS :=
OBJS :=
C_UPPER_DEPS :=
CXX_DEPS :=
SECONDARY_FLASH :=
SECONDARY_SIZE :=
ASM_DEPS :=
S_UPPER_DEPS :=
C_DEPS :=
CPP_DEPS :=
USER_OBJS :=
LIBS :=

STD_PERIPH_SRC := ../../STM32F10x_StdPeriph_Driver/src
STD_PERIPH_INC := ../../STM32F10x_StdPeriph_Driver/inc
INCLUDES := -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"$(STD_PERIPH_INC)"

CXXFLAGS := -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -flto -fno-move-loop-invariants -Werror -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wpadded -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -g3
DEFS := -DDEBUG -DUSE_FULL_ASSERT -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000
GCCFLAGS := -std=gnu11 -Wmissing-prototypes -Wstrict-prototypes -Wbad-function-cast -MMD -MP
GPPFLAGS := -std=gnu++11 -fabi-version=0 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics -Wctor-dtor-privacy -Wnoexcept -Wnon-virtual-dtor -Wstrict-null-sentinel -Wsign-promo -MMD -MP

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

system/src/stm32f1-stdperiph/%.o: $(STD_PERIPH_SRC)/%.c
	mkdir -p $(dir $@)
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc $(CXXFLAGS) $(DEFS) $(INCLUDES) $(GCCFLAGS) -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

-include ../system/src/newlib/subdir.mk
-include ../system/src/diag/subdir.mk
-include ../system/src/cortexm/subdir.mk
-include ../system/src/cmsis/subdir.mk
-include ../src/subdir.mk

PROJECT := ch

# Add inputs and outputs from these tool invocations to the build variables
SECONDARY_FLASH += \
$(PROJECT).hex \

SECONDARY_SIZE += \
$(PROJECT).siz \

# All Target
all: $(PROJECT).elf secondary-outputs

# Tool invocations
$(PROJECT).elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM Cross C++ Linker'
	arm-none-eabi-g++ $(CXXFLAGS) -T mem.ld -T libs.ld -T sections.ld -nostartfiles -Xlinker --gc-sections -L"../ldscripts" -Wl,-Map,"$(PROJECT).map" --specs=nano.specs -o "$(PROJECT).elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

$(PROJECT).hex: $(PROJECT).elf
	@echo 'Invoking: GNU ARM Cross Create Flash Image'
	arm-none-eabi-objcopy -O ihex "$(PROJECT).elf"  "$(PROJECT).hex"
	@echo 'Finished building: $@'
	@echo ' '

$(PROJECT).siz: $(PROJECT).elf
	@echo 'Invoking: GNU ARM Cross Print Size'
	arm-none-eabi-size --format=berkeley "$(PROJECT).elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(OBJS)$(C_UPPER_DEPS)$(CXX_DEPS)$(SECONDARY_FLASH)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS)$(CPP_DEPS) $(PROJECT).elf $(PROJECT).map
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents
