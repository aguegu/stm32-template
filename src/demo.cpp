#include "stm32-template.h"
#include "st7920/st7920.h"
#include <cstring>
#include "dot-matrix/dot-matrix.h"

Gpio led_green(GPIOC, GPIO_Pin_9, RCC_APB2Periph_GPIOC);
Gpio led_blue(GPIOC, GPIO_Pin_8, RCC_APB2Periph_GPIOC);

Gpio st7920_rs(GPIOB, GPIO_Pin_9, RCC_APB2Periph_GPIOB);
Gpio st7920_en(GPIOB, GPIO_Pin_8, RCC_APB2Periph_GPIOB);
Gpio st7920_d4(GPIOB, GPIO_Pin_7, RCC_APB2Periph_GPIOB);
Gpio st7920_d5(GPIOB, GPIO_Pin_6, RCC_APB2Periph_GPIOB);
Gpio st7920_d6(GPIOB, GPIO_Pin_5, RCC_APB2Periph_GPIOB);
Gpio st7920_d7(GPIOB, GPIO_Pin_4, RCC_APB2Periph_GPIOB);

St7920 lcd(st7920_rs, st7920_en, st7920_d4, st7920_d5, st7920_d6, st7920_d7);

void setup() {

	led_green.init(GPIO_Mode_Out_PP);
	led_blue.init(GPIO_Mode_Out_PP);

	nvic.configure(TIM2_IRQn, 0, 3, ENABLE);
	Tim t2(TIM2, RCC_APB1Periph_TIM2, RCC_APB1PeriphClockCmd);
	t2.init(1000, 1000);
	t2.configureIT(TIM_IT_Update);
	t2.setState();

	lcd.init();

	//lcd.clear();
//	uint8_t *p = (uint8_t *)malloc(sizeof(uint8_t) * 1024);
//	memset(p, 0x0f, 512);
//	memset(p + 512, 0xf0, 512);
//


	DotMatrix dm(128, 64);
	dm.setLine(0,0, 127, 63);

	uint8_t *ppa = dm.output();
	uint8_t *ppb = dm.output() + 512;

	for (uint8_t r = 0; r < 0x20; r++) {
		lcd.setDdRam(r); // y
		lcd.setDdRam(0x00); // x

		lcd.transmit(true, ppa, 0x10);
		lcd.transmit(true, ppb, 0x10);

		ppa += 0x10;
		ppb += 0x10;
	}
//
//	for (uint8_t r = 0; r < 0x20; r++) {
//		lcd.setDdRam(r); // y
//		lcd.setDdRam(0x08); // x
//		for (uint8_t i = 16; i--;)
//			lcd.writeData(*pp++);
//	}
}

void loop() {

	static uint8_t i = 0;
	while (usart.available()) {
		char c = usart.read();
		fprintf(stdout, "0x%02X\r\n", c);
		led_blue.toggle();
	}

	fprintf(stdout, "0x%02x\r\n", i++);

	//led_blue.toggle();
	delayMicroseconds(500000);
}

