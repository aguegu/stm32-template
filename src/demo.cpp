#include "stm32-template.h"
#include "at24c/at24c.h"

Gpio led_green(GPIOC, GPIO_Pin_9, RCC_APB2Periph_GPIOC);
Gpio led_blue(GPIOC, GPIO_Pin_8, RCC_APB2Periph_GPIOC);

I2c i2c(I2C1, RCC_APB1Periph_I2C1);

Gpio i2c_scl(GPIOB, GPIO_Pin_6, RCC_APB2Periph_GPIOB);
Gpio i2c_sda(GPIOB, GPIO_Pin_7, RCC_APB2Periph_GPIOB);

At24c eeprom(i2c, 16, 0x50);

uint8_t data[16];
uint8_t data2[16];
float data3[4];

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

	i2c.init(I2C_Mode_I2C, 400000);

	for (uint8_t i = 0; i < 16; i++) {
		data[i] = i;
		data2[i] = ~data[i];
	}

	data3[0] = 10.0;
	data3[1] = 1.0;
	data3[2] = 0.01;
	data3[3] = 0.001;
}

void loop() {
	while (usart.available()) {
		char c = usart.read();
		fprintf(stdout, "0x%02X\r\n", c);
		led_blue.toggle();
	}

	uint8_t c[16];
	eeprom.read(0x00, c, 16);

	for (uint8_t i = 0; i < 16; i++)
		fprintf(stdout, "0x%02X, ", c[i]);
	fprintf(stdout, "\r\n");

	eeprom.read(0x100, c, 16);

	for (uint8_t i = 0; i < 16; i++)
		fprintf(stdout, "0x%02X, ", c[i]);
	fprintf(stdout, "\r\n\r\n");

	float flt[4];
	eeprom.read(0x200, flt, 16);

	for (uint8_t i = 0; i < 4; i++)
		fprintf(stdout, "%f ", flt[i]);

	printf("\r\n");

	static uint8_t index = 0;
	eeprom.write(index, data, 16);
	delay(5);
	eeprom.write(0x100 + index++, data2, 16);
	delay(5);
	eeprom.write(0x200 + (index++) % 4 * sizeof(float), data3,
			sizeof(float) * 4);

	index %= 16;

	led_blue.toggle();
	delay(1000);
}

