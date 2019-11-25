UID = $(shell id -u)
GID = $(shell id -g)


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

clean:
	rm -rf develop
	rm -rf release


.PHONY: clean develop release
