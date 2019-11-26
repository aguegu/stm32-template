stm32f10x-stdperiph-lib
===

with gcc-arm-none-eabi-8-2019-q3-update

* Original `STM32F10x_StdPeriph_Lib_V3.5.0` can be downloaded within `en.stsw-stm32054.zip` from https://www.st.com/content/st_com/en/products/embedded-software/mcu-mpu-embedded-software/stm32-embedded-software/stm32-standard-peripheral-libraries/stsw-stm32054.html

  `STM32F10x_StdPeriph_Driver` in this repo is ported from `https://gnu-mcu-eclipse.github.io`, with modification to surpress compile warnings.

```
$ docker build -t "aguegu/stm32f10x-stdperiph-lib:3.5.0" .
```

* how to

get a stm32f103c8t6 mini/bluepill attached to a STLink Device, and also got [stlink](https://github.com/texane/stlink) and `docker` installed in your os

```
$ docker pull aguegu/stm32f10x-stdperiph-lib:3.5.0
$ cd blink
$ make debug
or
$ make release
```

Now you may enjoy stm32 development without IDEs. :)
