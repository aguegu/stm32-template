stm32f10x-stdperiph-lib
===

1. Download `en.stsw-stm32054.zip` from https://www.st.com/content/st_com/en/products/embedded-software/mcu-mpu-embedded-software/stm32-embedded-software/stm32-standard-peripheral-libraries/stsw-stm32054.html

2. create `STM32F10x_StdPeriph_Lib_V3.5.0.tar.gz`

```
$ unzip en.stsw-stm32054.zip
$ tar czf STM32F10x_StdPeriph_Lib_V3.5.0.tar.gz STM32F10x_StdPeriph_Lib_V3.5.0
$ rm -rf STM32F10x_StdPeriph_Lib_V3.5.0
```

3. build image

```
$ docker build -t "stm32f10x-stdperiph-lib:3.5.0" .
```

arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -flto -fno-move-loop-invariants -Werror -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f1-stdperiph" -std=gnu11 -MMD -MP -MF"system/src/stm32f1-stdperiph/misc.d" -MT"system/src/stm32f1-stdperiph/misc.o" -c -o "system/src/stm32f1-stdperiph/misc.o" "../system/src/stm32f1-stdperiph/misc.c"

https://github.com/artem-smotrakov/stm32f103-template
