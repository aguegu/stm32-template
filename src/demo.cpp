#include "stm32-template.h"

#include "hd44780/hd44780-gpio.h"

Gpio led_green(GPIOC, GPIO_Pin_9, RCC_APB2Periph_GPIOC);
Gpio led_blue(GPIOC, GPIO_Pin_8, RCC_APB2Periph_GPIOC);

Gpio hd44780_rs(GPIOB, GPIO_Pin_9, RCC_APB2Periph_GPIOB);
Gpio hd44780_en(GPIOB, GPIO_Pin_8, RCC_APB2Periph_GPIOB);
Gpio hd44780_d4(GPIOB, GPIO_Pin_7, RCC_APB2Periph_GPIOB);
Gpio hd44780_d5(GPIOB, GPIO_Pin_6, RCC_APB2Periph_GPIOB);
Gpio hd44780_d6(GPIOB, GPIO_Pin_5, RCC_APB2Periph_GPIOB);
Gpio hd44780_d7(GPIOB, GPIO_Pin_4, RCC_APB2Periph_GPIOB);

Hd44780Gpio lcd(hd44780_rs, hd44780_en, hd44780_d4, hd44780_d5, hd44780_d6,
		hd44780_d7);

void setup() {

	led_green.init(GPIO_Mode_Out_PP);
	led_blue.init(GPIO_Mode_Out_PP);

	nvic.configure(TIM2_IRQn, 0, 3, ENABLE);
	Tim t2(TIM2, RCC_APB1Periph_TIM2, RCC_APB1PeriphClockCmd);
	t2.init(1000, 1000);
	t2.configureIT(TIM_IT_Update);
	t2.setState();

	lcd.init();
	lcd.printf("hello, world.");
	lcd.putCache();
}

void loop() {

	static uint8_t i = 0;
	while (usart.available()) {
		char c = usart.read();
		fprintf(stdout, "0x%02X\r\n", c);
		led_blue.toggle();
	}

	fprintf(stdout, "0x%02x\r\n", i++);

	lcd.printf(0x1c, "0x%02x", i);
	lcd.putCache();

	//led_blue.toggle();
	delayMicroseconds(500000);
}

