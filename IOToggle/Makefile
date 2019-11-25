UID = $(shell id -u)
GID = $(shell id -g)

dist:
	docker run -t --rm -v ${CURDIR}:/root/workspace aguegu/stm32f10x-stdperiph-lib:3.5.0 sh -c "\
		make -f stm32.Makefile \
		&& chown $(UID):$(GID) -R . \
	"

flash:
	st-flash --format ihex write Debug/ch.hex

# Debug:
# 	rm -rf $@
# 	docker run -t --rm -v ${CURDIR}:/root/workspace aguegu/stm32f10x-stdperiph-lib:3.5.0 sh -c "\
# 		make -f stm32.Makefile $@\
# 		&& chown $(UID):$(GID) -R . \
# 	"
# 	st-flash --format ihex write $@/ch.hex
#
# release:
# 	rm -rf $@
# 	docker run -t --rm -v ${CURDIR}:/root/workspace aguegu/stm32f10x-stdperiph-lib:3.5.0 sh -c "\
# 		make -f stm32.Makefile $@\
# 		&& chown $(UID):$(GID) -R . \
# 	"
# 	st-flash --format ihex write $@/ch.hex

clean:
	rm -rf Debug
	# rm -rf release

all:
	make clean
	make dist
	make flash

.PHONY: clean dist release all
