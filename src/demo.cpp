#include "stm32-template.h"
#include "st7920/st7920-dm.h"
#include <cstring>
#include "dot-matrix/dot-matrix.h"
#include "dot-matrix/dot-char.h"
#include "dot-matrix/dot-font.h"
#include "dot-matrix/dot-string.h"

Gpio led_green(GPIOC, GPIO_Pin_9, RCC_APB2Periph_GPIOC);
Gpio led_blue(GPIOC, GPIO_Pin_8, RCC_APB2Periph_GPIOC);

Gpio st7920_rs(GPIOB, GPIO_Pin_9, RCC_APB2Periph_GPIOB);
Gpio st7920_en(GPIOB, GPIO_Pin_8, RCC_APB2Periph_GPIOB);
Gpio st7920_d4(GPIOB, GPIO_Pin_7, RCC_APB2Periph_GPIOB);
Gpio st7920_d5(GPIOB, GPIO_Pin_6, RCC_APB2Periph_GPIOB);
Gpio st7920_d6(GPIOB, GPIO_Pin_5, RCC_APB2Periph_GPIOB);
Gpio st7920_d7(GPIOB, GPIO_Pin_4, RCC_APB2Periph_GPIOB);

St7920Dm lcd(st7920_rs, st7920_en, st7920_d4, st7920_d5, st7920_d6, st7920_d7);
DotMatrix dm = lcd.getDotMatrix();

DotChar dc(dm, vfont_7x3);
DotString ds(dc, 16, true);

void setup() {
	led_green.init(GPIO_Mode_Out_PP);
	led_blue.init(GPIO_Mode_Out_PP);

	nvic.configure(TIM2_IRQn, 0, 3, ENABLE);
	Tim t2(TIM2, RCC_APB1Periph_TIM2, RCC_APB1PeriphClockCmd);
	t2.init(1000, 1000);
	t2.configureIT(TIM_IT_Update);
	t2.setState();

	lcd.init();

	dm.setLine(63, 0, 63, 63);
	dm.setLine(0, 31, 127, 31);
	dm.setMoveDirection(DotMatrix::BIT_IN_COL_NEGA);

	ds.printf("hello, world.");
	ds.postAt(0, 0);
}

void loop() {
	static uint8_t i = 0;
	while (usart.available()) {
		char c = usart.read();
		fprintf(stdout, "0x%02X\r\n", c);
		led_blue.toggle();
	}

	fprintf(stdout, "0x%02x\r\n", i++);

	lcd.putDM();
	dm.move(true);
	delay(200);
}
