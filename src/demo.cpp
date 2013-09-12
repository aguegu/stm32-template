#include "stm32-template.h"
#include "gpio-array/gpio-array.h"

Gpio led_green(GPIOC, GPIO_Pin_9, RCC_APB2Periph_GPIOC);
Gpio led_blue(GPIOC, GPIO_Pin_8, RCC_APB2Periph_GPIOC);
GpioArray leds(2);

Gpio dip_0(GPIOB, GPIO_Pin_14, RCC_APB2Periph_GPIOB);
Gpio dip_1(GPIOB, GPIO_Pin_13, RCC_APB2Periph_GPIOB);
Gpio dip_2(GPIOB, GPIO_Pin_12, RCC_APB2Periph_GPIOB);
Gpio dip_3(GPIOB, GPIO_Pin_11, RCC_APB2Periph_GPIOB);
Gpio dip_4(GPIOB, GPIO_Pin_10, RCC_APB2Periph_GPIOB);
Gpio dip_5(GPIOB, GPIO_Pin_0, RCC_APB2Periph_GPIOB);
Gpio dip_6(GPIOB, GPIO_Pin_1, RCC_APB2Periph_GPIOB);

// Gpio dip_7(GPIOB, GPIO_Pin_2, RCC_APB2Periph_GPIOB);
// PB2 is BOOT1, which is pull down by external resistor
// just leave it alone


GpioArray dips(7);

void setup() {
	leds.setGpio(0, led_blue);
	leds.setGpio(1, led_green);
	leds.init(GPIO_Mode_Out_PP);

	leds.set(0x01);

	dips.setGpio(0, dip_0);
	dips.setGpio(1, dip_1);
	dips.setGpio(2, dip_2);
	dips.setGpio(3, dip_3);
	dips.setGpio(4, dip_4);
	dips.setGpio(5, dip_5);
	dips.setGpio(6, dip_6);

	dips.init(GPIO_Mode_IPU);

	nvic.configure(TIM2_IRQn, 0, 3, ENABLE);
	Tim t2(TIM2, RCC_APB1Periph_TIM2, RCC_APB1PeriphClockCmd);
	t2.init(1000, 1000);
	t2.configureIT(TIM_IT_Update);
	t2.setState();
}

void loop() {

	while (usart.available()) {
		char c = usart.read();
		fprintf(stdout, "0x%02X\r\n", c);
	}

	fprintf(stdout, "0x%02lx\r\n", dips.getInput());

	leds.toggle();

	delayMicroseconds(500000);
}

