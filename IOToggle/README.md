docker run -t --rm -v $PWD:/root/workspace aguegu/stm32f10x-stdperiph-lib:3.5.0 sh -c "\
  make -f stm32.Makefile develop/main.o \
  && chown $(UID):$(GID) -R . \
"
