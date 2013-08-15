#include "stm32-template.h"
#include "i2c/i2c.h"

Gpio led_green(GPIOC, GPIO_Pin_9, RCC_APB2Periph_GPIOC );
Gpio led_blue(GPIOC, GPIO_Pin_8, RCC_APB2Periph_GPIOC );

I2c i2c(I2C1, RCC_APB1Periph_I2C1 );

void setup() {

	led_green.init(GPIO_Mode_Out_PP);
	led_blue.init(GPIO_Mode_Out_PP);

	nvic.configure(TIM2_IRQn, 0, 3, ENABLE);
	Tim t2(TIM2, RCC_APB1Periph_TIM2, RCC_APB1PeriphClockCmd);
	t2.init(1000, 1000);
	t2.configureIT(TIM_IT_Update);
	t2.setState();

	Gpio i2c_scl(GPIOB, GPIO_Pin_6, RCC_APB2Periph_GPIOB );
	Gpio i2c_sda(GPIOB, GPIO_Pin_7, RCC_APB2Periph_GPIOB );
	i2c_scl.init(GPIO_Mode_AF_OD);
	i2c_sda.init(GPIO_Mode_AF_OD);

	i2c.init();

	uint8_t w;

	uint8_t cache[] = { 0x0e, 0x9c };
	w = i2c.write(0x68, cache, 2);
	fprintf(stderr, "%02x:\r\n", w);

	uint8_t cache2[] = { 0x0f, 0x00 };
	w = i2c.write(0x68, cache2, 2);
	fprintf(stderr, "%02x:\r\n", w);

	uint8_t cache3[] = {0x00, 0x00, 0x48, 0x22, 0x05, 0x13, 0x06, 0x13};
	w = i2c.write(0x68, cache3, 8);
}

void loop() {
	while (usart.available()) {
		char c = usart.read();
		fprintf(stdout, "0x%02X\r\n", c);
		led_blue.toggle();
	}

	static u8 s[7];
	uint8_t w, r;

	uint8_t cmd = 0;
	w = i2c.write(0x68, &cmd, 1);
	r = i2c.read(0x68, s, 7);

	fprintf(stderr, "[%02x %02x] %02x-%02x-%02x %02x %02x:%02x:%02x\r\n", w, r,
			s[6], s[5], s[4], s[3], s[2], s[1], s[0]);

	led_blue.toggle();
	delay(1000);
}

