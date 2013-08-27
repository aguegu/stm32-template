#include "stm32-template.h"
#include "at24c/at24c.h"

Gpio led_green(GPIOC, GPIO_Pin_9, RCC_APB2Periph_GPIOC);
Gpio led_blue(GPIOC, GPIO_Pin_8, RCC_APB2Periph_GPIOC);

I2c i2c(I2C1, RCC_APB1Periph_I2C1);

Gpio i2c_scl(GPIOB, GPIO_Pin_6, RCC_APB2Periph_GPIOB);
Gpio i2c_sda(GPIOB, GPIO_Pin_7, RCC_APB2Periph_GPIOB);

At24c eeprom(i2c, 16, 0x50);

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

	i2c.init();
}

void loop() {
	while (usart.available()) {
		char c = usart.read();
		fprintf(stdout, "0x%02X\r\n", c);
		led_blue.toggle();
	}

	uint8_t c[2];
	uint8_t k = eeprom.read(0x00, c, 2);
	//fprintf(stdout, "0x%02X, 0x%02X\r\n", c[0], c[1]);
	fprintf(stdout, "0x%02X\r\n", k);

	delay(5);

	static uint8_t s[2] = { 0xbe, 0xef };
	eeprom.write(0, s, 2);

	s[0]++;
	s[1]++;

	led_blue.toggle();
	delay(1000);
}

