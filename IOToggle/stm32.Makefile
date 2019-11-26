# path to STM32F103 standard peripheral library
STD_PERIPH_LIBS ?= ../STM32F10x_StdPeriph_Lib_V3.5.0/

# list of source files
SRC  = src/main.c src/stm32f10x_it.c src/core_cm3.c
# SOURCES = $(STD_PERIPH_LIBS)/Libraries/CMSIS/CM3/CoreSupport/core_cm3.c
SOURCES = $(STD_PERIPH_LIBS)/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.c
SOURCES += $(STD_PERIPH_LIBS)/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.c
SOURCES += $(STD_PERIPH_LIBS)/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.c
SOURCES += $(STD_PERIPH_LIBS)/Libraries/STM32F10x_StdPeriph_Driver/src/misc.c

# SOURCES += $(STD_PERIPH_LIBS)/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/TrueSTUDIO/startup_stm32f10x_md.s

ASRC = $(STD_PERIPH_LIBS)/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/TrueSTUDIO/startup_stm32f10x_md.s

# name for output binary files
PROJECT ?= ch

TRGT = arm-none-eabi-
AS   = $(TRGT)as
CC   = $(TRGT)gcc
LD   = $(TRGT)gcc
CP   = $(TRGT)objcopy
SZ   = $(TRGT)size

# specify compiler flags

LDSCRIPT = stm32_flash.ld
LDFLAGS += -T$(LDSCRIPT) -mcpu=cortex-m3 -mthumb --specs=nosys.specs
# LSCRIPT = ./ld/stm32.ld
# LFLAGS += -nostdlib
LDFLAGS += -static
# LFLAGS += -T$(LSCRIPT)

CFLAGS  = -g -O2
CFLAGS += -Wall
# CFLAGS += -T$(LDSCRIPT)
CFLAGS += -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -flto -fno-move-loop-invariants -Werror -Wextra -g3
CFLAGS += -DHSE_VALUE=8000000
CFLAGS += -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER
# CFLAGS += -DDEBUG -DUSE_FULL_ASSERT
CFLAGS += -Wl,--gc-sections
CFLAGS += -I./include
CFLAGS += -I$(STD_PERIPH_LIBS)/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/
CFLAGS += -I$(STD_PERIPH_LIBS)/Libraries/CMSIS/CM3/CoreSupport
CFLAGS += -I$(STD_PERIPH_LIBS)/Libraries/STM32F10x_StdPeriph_Driver/inc
CFLAGS += -I../gcc-arm-none-eabi-8-2019-q3-update/arm-none-eabi/include
CFLAGS += -I../gcc-arm-none-eabi-8-2019-q3-update/lib/gcc/arm-none-eabi/8.3.1/include
CFLAGS += -I../gcc-arm-none-eabi-8-2019-q3-update/lib/gcc/arm-none-eabi/8.3.1/include-fixed

ASFLAGS = -mcpu=cortex-m3
ASFLAGS += -mthumb
ASFLAGS += -Wall
ASFLAGS += -Wl,--gc-sections
# ASFLAGS += -c
# ASFLAGS += -fmessage-length=0

# all: develop/$(PROJECT).elf release/$(PROJECT).elf

# release: $(SOURCES)
# 	mkdir -p $@
# 	$(CC) $(CFLAGS) $^ -o $@/$(PROJECT).elf
# 	$(HEX) $@/$(PROJECT).elf $@/$(PROJECT).hex
# 	$(BIN) $@/$(PROJECT).elf $@/$(PROJECT).bin
# 	$(SZ) $@/$(PROJECT).elf
#
# develop: CFLAGS += -DDEBUG -DUSE_FULL_ASSERT
# develop: $(SOURCES)
# 	mkdir -p $@
# 	$(CC) $(CFLAGS) $^ -o $@/$(PROJECT).elf
# 	$(HEX) $@/$(PROJECT).elf $@/$(PROJECT).hex
# 	$(BIN) $@/$(PROJECT).elf $@/$(PROJECT).bin
# 	$(SZ) $@/$(PROJECT).elf

# %.o: %.c $(HEADERS) $(THIS_MAKEFILE)
# 	$(CC) $(CFLAGS) -c $< -o $@
#
# %.o: %.s $(HEADERS) $(THIS_MAKEFILE)
# 	$(CC) $(CFLAGS) -c $< -o $@

BUILDDIR = Debug

OBJ = $(addprefix $(BUILDDIR)/, $(SRC:.c=.o))
OBJECTS = $(SOURCES:.c=.o) $(ASRC:.s=.o)

# OBJECTS = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(SOURCES))))
ELF = $(BUILDDIR)/$(PROJECT).elf
HEX = $(ELF:.elf=.hex)

$(HEX): $(ELF)
	$(SZ) $<
	$(CP) -O ihex $< $@

$(ELF): $(OBJ) $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^

$(BUILDDIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@

%.o: %.s
	# mkdir -p $(dir $@)
	# $(CC) -c $(CFLAGS) $< -o $@
	$(CC) -x assembler-with-cpp -c $(ASFLAGS) $< -o $@

clean:
	rm -rf develop/

.PHONY: clean all
