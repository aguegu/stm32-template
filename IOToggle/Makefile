UID = $(shell id -u)
GID = $(shell id -g)

dist:
	docker run -t --rm -v ${CURDIR}:/root/workspace aguegu/stm32f10x-stdperiph-lib:3.5.0 sh -c "\
		make -f stm32.Makefile \
		&& chown $(UID):$(GID) *.bin *.elf *.hex \
	"

flash:
	st-flash --format ihex write ch.hex

clean:
	rm -f *.elf *.hex *.bin

all:
	make dist && make flash

.PHONY: dist flash clean
