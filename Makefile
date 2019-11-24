image:
	docker build -t aguegu/stm32f10x-stdperiph-lib:3.5.0 .

push:
	docker push aguegu/stm32f10x-stdperiph-lib:3.5.0
	docker rmi aguegu/stm32f10x-stdperiph-lib:3.5.0

.PHONY: image push
