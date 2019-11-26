
debug:
	docker run -t --rm -v ${CURDIR}:/root/workspace aguegu/stm32f10x-stdperiph-lib:3.5.0 sh -c "\
		make -f stm32.Makefile debug \
		&& chown $(UID):$(GID) -R . \
	"
	st-flash --format ihex write Debug/blink.hex

release:
	docker run -t --rm -v ${CURDIR}:/root/workspace aguegu/stm32f10x-stdperiph-lib:3.5.0 sh -c "\
		make -f stm32.Makefile release \
		&& chown $(UID):$(GID) -R . \
	"
	st-flash --format ihex write Release/blink.hex

clean:
	docker run -t --rm -v ${CURDIR}:/root/workspace aguegu/stm32f10x-stdperiph-lib:3.5.0 sh -c "\
		make -f stm32.Makefile clean \
	"

.PHONY: debug release clean
