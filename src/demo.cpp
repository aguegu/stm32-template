#include "stm32-template.h"
#include "gpio-array/gpio-array.h"

Gpio led_green(GPIOC, GPIO_Pin_9, RCC_APB2Periph_GPIOC);
Gpio led_blue(GPIOC, GPIO_Pin_8, RCC_APB2Periph_GPIOC);
GpioArray leds(2);

void setup() {
	leds.setGpio(0, led_blue);
	leds.setGpio(1, led_green);
	leds.init(GPIO_Mode_Out_PP);

	nvic.configure(TIM2_IRQn, 0, 3, ENABLE);
	Tim t2(TIM2, RCC_APB1Periph_TIM2, RCC_APB1PeriphClockCmd);
	t2.init(1000, 1000);
	t2.configureIT(TIM_IT_Update);
	t2.setState();
}

void loop() {

	static uint8_t i = 0;
	while (usart.available()) {
		char c = usart.read();
		fprintf(stdout, "0x%02X\r\n", c);
	}

	fprintf(stdout, "0x%02x\r\n", i++);

	leds.set(i & 0x01 ? 0x01 : 0x02);

	delayMicroseconds(500000);
}

