UID = $(shell id -u)
GID = $(shell id -g)

clean:
	rm -rf develop
	rm -rf release

develop:
	rm -rf $@
	docker run -t --rm -v ${CURDIR}:/root/workspace aguegu/stm32f10x-stdperiph-lib:3.5.0 sh -c "\
		make -f stm32.Makefile $@\
		&& chown $(UID):$(GID) -R . \
	"
	st-flash --format ihex write $@/ch.hex

release:
	rm -rf $@
	docker run -t --rm -v ${CURDIR}:/root/workspace aguegu/stm32f10x-stdperiph-lib:3.5.0 sh -c "\
		make -f stm32.Makefile $@\
		&& chown $(UID):$(GID) -R . \
	"
	st-flash --format ihex write $@/ch.hex

.PHONY: clean develop release
