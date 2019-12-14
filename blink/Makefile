UID = $(shell id -u)
GID = $(shell id -g)

debug:
	docker run -t --rm -v ${CURDIR}:/root/workspace aguegu/stm32f10x-stdperiph-lib:3.5.0 sh -c "\
		make -f debug.Makefile \
		&& chown $(UID):$(GID) -R . \
	"
	st-flash --format ihex write $@/ch.hex

release:
	docker run -t --rm -v ${CURDIR}:/root/workspace aguegu/stm32f10x-stdperiph-lib:3.5.0 sh -c "\
		make -f release.Makefile \
		&& chown $(UID):$(GID) -R . \
	"
	st-flash --format ihex write $@/ch.hex

clean:
	docker run -t --rm -v ${CURDIR}:/root/workspace aguegu/stm32f10x-stdperiph-lib:3.5.0 sh -c "\
		make -f debug.Makefile clean \
		&& make -f release.Makefile clean \
	"

.PHONY: debug release clean
