#include "stm32-template.h"
#include "ds3231/ds3231.h"

Gpio led_green(GPIOC, GPIO_Pin_9, RCC_APB2Periph_GPIOC);
Gpio led_blue(GPIOC, GPIO_Pin_8, RCC_APB2Periph_GPIOC);

I2c i2c(I2C1, RCC_APB1Periph_I2C1);
Ds3231 ds(i2c);

Gpio i2c_scl(GPIOB, GPIO_Pin_6, RCC_APB2Periph_GPIOB);
Gpio i2c_sda(GPIOB, GPIO_Pin_7, RCC_APB2Periph_GPIOB);

void setup() {

	led_green.init(GPIO_Mode_Out_PP);
	led_blue.init(GPIO_Mode_Out_PP);

	nvic.configure(TIM2_IRQn, 0, 3, ENABLE);
	Tim t2(TIM2, RCC_APB1Periph_TIM2, RCC_APB1PeriphClockCmd);
	t2.init(1000, 1000);
	t2.configureIT(TIM_IT_Update);
	t2.setState();

	i2c_scl.init(GPIO_Mode_AF_OD);
	i2c_sda.init(GPIO_Mode_AF_OD);

	ds.init();

	ds.setTime(12, 34, 56);
	ds.setDate(13, 8, 21, 3);
}

void loop() {
	while (usart.available()) {
		char c = usart.read();
		fprintf(stdout, "0x%02X\r\n", c);
		led_blue.toggle();
	}

	ds.refresh();

	fprintf(stdout, "%02x-%02x-%02x %02x %02x:%02x:%02x %.2f\r\n",
			ds.getHexData(YEAR),
			ds.getHexData(MONTH),
			ds.getHexData(DATE),
			ds.getHexData(WEEKDAY),
			ds.getHexData(HOUR),
			ds.getHexData(MINUTE),
			ds.getHexData(SECOND),
			ds.getTemperature()
	);

	led_blue.toggle();
	delay(1000);
}

