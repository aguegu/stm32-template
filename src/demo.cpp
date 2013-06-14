#include "stm32-template.h"
//#include "i2c/i2c.h"
#include "i2c-soft/i2c-soft.h"

Gpio led_green(GPIOC, GPIO_Pin_9, RCC_APB2Periph_GPIOC );
Gpio led_blue(GPIOC, GPIO_Pin_8, RCC_APB2Periph_GPIOC );

Gpio i2c_sda(GPIOB, GPIO_Pin_7, RCC_APB2Periph_GPIOB );
Gpio i2c_scl(GPIOB, GPIO_Pin_6, RCC_APB2Periph_GPIOB );
I2cSoft isl1208(i2c_sda, i2c_scl);

#define I2C_ADDR	0x6f
//#define I2C_ADDR	0x32

void setup() {

	led_green.init(GPIO_Mode_Out_PP);
	led_blue.init(GPIO_Mode_Out_PP);

	nvic.init(TIM2_IRQn, 0, 3, ENABLE);
	Tim t2(TIM2, RCC_APB1Periph_TIM2, RCC_APB1PeriphClockCmd);
	t2.init(1000, 1000);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM2, ENABLE);

	isl1208.init();

	uint8_t cmd[2] = { 0x07, 0x90 };
	isl1208.write(I2C_ADDR, cmd, 2);
}

void loop() {
	while (usart.available()) {
		char c = usart.read();
		fprintf(stdout, "0x%02X\r\n", c);
		led_blue.toggle();
	}

	u8 t[8], cmd = 0;
	isl1208.write(I2C_ADDR, &cmd, 1);
	isl1208.read(I2C_ADDR, t, 8);

	for (u8 i = 0; i < 8; i++)
		usart.write(t[i]);

	led_blue.toggle();

	delay(1000);

}

