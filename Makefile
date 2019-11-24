lib:
	unzip en.stsw-stm32054.zip
	tar czf STM32F10x_StdPeriph_Lib_V3.5.0.tar.gz STM32F10x_StdPeriph_Lib_V3.5.0
	rm -rf STM32F10x_StdPeriph_Lib_V3.5.0

image:
	docker build -t aguegu/stm32f10x-stdperiph-lib:3.5.0 .

push:
	docker push aguegu/stm32f10x-stdperiph-lib:3.5.0
	docker rmi aguegu/stm32f10x-stdperiph-lib:3.5.0

.PHONY: lib image push
