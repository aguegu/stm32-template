FROM debian:buster-slim

WORKDIR /root

ADD STM32F10x_StdPeriph_Lib_V3.5.0.tar.gz .

ADD https://armkeil.blob.core.windows.net/developer/Files/downloads/gnu-rm/8-2019q3/RC1.1/gcc-arm-none-eabi-8-2019-q3-update-linux.tar.bz2 .
RUN tar xjf gcc-arm-none-eabi-8-2019-q3-update-linux.tar.bz2 && rm gcc-arm-none-eabi-8-2019-q3-update-linux.tar.bz2
ENV PATH /root/gcc-arm-none-eabi-8-2019-q3-update/bin:$PATH

VOLUME /root/workspace
