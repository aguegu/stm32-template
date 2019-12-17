OUTPUT_DIR := debug

STD_PERIPH_SRC := ../STM32F10x_StdPeriph_Driver/src
STD_PERIPH_INC := ../STM32F10x_StdPeriph_Driver/inc
INCLUDES := -I"./include" -I"./system/include" -I"./system/include/cmsis" -I"$(STD_PERIPH_INC)"

CXXFLAGS := -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -flto -fno-move-loop-invariants -Werror -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wpadded -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -g3
DEFS := -DDEBUG -DUSE_FULL_ASSERT -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000
GCCFLAGS := -std=gnu11 -Wmissing-prototypes -Wstrict-prototypes -Wbad-function-cast -MMD -MP
GPPFLAGS := -std=gnu++11 -fabi-version=0 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics -Wctor-dtor-privacy -Wnoexcept -Wnon-virtual-dtor -Wstrict-null-sentinel -Wsign-promo -MMD -MP

C_SRCS = \
$(wildcard ./system/src/newlib/*.c) \
$(wildcard ./system/src/diag/*.c) \
$(wildcard ./system/src/cortexm/*.c) \
$(wildcard ./system/src/cmsis/*.c)

C_SRCS += \
$(wildcard ./src/*.c) \
$(STD_PERIPH_SRC)/misc.c \
$(STD_PERIPH_SRC)/stm32f10x_gpio.c \
$(STD_PERIPH_SRC)/stm32f10x_rcc.c \
$(STD_PERIPH_SRC)/stm32f10x_pwr.c \
$(STD_PERIPH_SRC)/stm32f10x_exti.c \

CPP_SRCS = \
./system/src/newlib/_cxx.cpp

OBJS := $(addprefix $(OUTPUT_DIR)/, $(notdir $(C_SRCS:.c=.o))) $(addprefix $(OUTPUT_DIR)/, $(notdir $(CPP_SRCS:.cpp=.o)))

VPATH = system/src/newlib:system/src/diag:system/src/cortexm:system/src/cmsis:src:$(STD_PERIPH_SRC)

PROJECT := ch

all: $(OUTPUT_DIR) $(OUTPUT_DIR)/$(PROJECT).hex $(OUTPUT_DIR)/$(PROJECT).siz

$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

$(OUTPUT_DIR)/%.o: %.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C++ Compiler'
	arm-none-eabi-g++ $(CXXFLAGS) $(DEFS) $(INCLUDES) $(GPPFLAGS) -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

$(OUTPUT_DIR)/%.o: %.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc $(CXXFLAGS) $(DEFS) $(INCLUDES) $(GCCFLAGS) -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

$(OUTPUT_DIR)/$(PROJECT).elf: $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM Cross C++ Linker'
	arm-none-eabi-g++ $(CXXFLAGS) -T mem.ld -T libs.ld -T sections.ld -nostartfiles -Xlinker --gc-sections -L"./ldscripts" -Wl,-Map,"$(OUTPUT_DIR)/$(PROJECT).map" --specs=nano.specs -o $@ $(OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

$(OUTPUT_DIR)/%.hex: $(OUTPUT_DIR)/%.elf
	@echo 'Invoking: GNU ARM Cross Create Flash Image'
	arm-none-eabi-objcopy -O ihex "$<"  "$@"
	@echo 'Finished building: $@'
	@echo ' '

$(OUTPUT_DIR)/%.siz: $(OUTPUT_DIR)/%.elf
	@echo 'Invoking: GNU ARM Cross Print Size'
	arm-none-eabi-size --format=berkeley $<
	@echo 'Finished building: $@'
	@echo ' '

clean:
	rm -rf $(OUTPUT_DIR)

.PHONY: all clean $(OUTPUT_DIR)
