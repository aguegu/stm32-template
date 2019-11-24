# path to STM32F103 standard peripheral library
STD_PERIPH_LIBS ?= ../STM32F10x_StdPeriph_Lib_V3.5.0/

# list of source files
SOURCES  = src/main.c
SOURCES += $(STD_PERIPH_LIBS)/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.c
SOURCES += $(STD_PERIPH_LIBS)/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.c
SOURCES += $(STD_PERIPH_LIBS)/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.c
SOURCES += $(STD_PERIPH_LIBS)/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/TrueSTUDIO/startup_stm32f10x_md.s

# name for output binary files
PROJECT ?= ch

# compiler, objcopy (should be in PATH)
TRGT = arm-none-eabi-
CC   = $(TRGT)gcc
CP   = $(TRGT)objcopy
SZ   = $(TRGT)size
HEX  = $(CP) -O ihex
BIN  = $(CP) -O binary

# specify compiler flags
CFLAGS  = -g -O2
# CFLAGS += -Wall
CFLAGS += -T./stm32_flash.ld
CFLAGS += -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -flto -fno-move-loop-invariants -Werror -Wextra -g3
CFLAGS += -DHSE_VALUE=8000000
CFLAGS += -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER
CFLAGS += -Wl,--gc-sections
CFLAGS += -I./include
CFLAGS += -I$(STD_PERIPH_LIBS)/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/
CFLAGS += -I$(STD_PERIPH_LIBS)/Libraries/CMSIS/CM3/CoreSupport
CFLAGS += -I$(STD_PERIPH_LIBS)/Libraries/STM32F10x_StdPeriph_Driver/inc

# OBJS = $(SOURCES:.c=.o)

# all: develop/$(PROJECT).elf release/$(PROJECT).elf

release: $(SOURCES)
	mkdir -p $@
	$(CC) $(CFLAGS) $^ -o $@/$(PROJECT).elf
	$(HEX) $@/$(PROJECT).elf $@/$(PROJECT).hex
	$(BIN) $@/$(PROJECT).elf $@/$(PROJECT).bin
	$(SZ) $@/$(PROJECT).elf

develop: CFLAGS += -DDEBUG -DUSE_FULL_ASSERT
develop: $(SOURCES)
	mkdir -p $@
	$(CC) $(CFLAGS) $^ -o $@/$(PROJECT).elf
	$(HEX) $@/$(PROJECT).elf $@/$(PROJECT).hex
	$(BIN) $@/$(PROJECT).elf $@/$(PROJECT).bin
	$(SZ) $@/$(PROJECT).elf

clean:
	rm -rf release/
	rm -rf develop/

.PHONY: clean all
