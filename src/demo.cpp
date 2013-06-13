#include "stm32-template.h"
//#include "i2c/i2c.h"
#include "i2c-soft/i2c-soft.h"

Gpio led_green(GPIOC, GPIO_Pin_9, RCC_APB2Periph_GPIOC );
Gpio led_blue(GPIOC, GPIO_Pin_8, RCC_APB2Periph_GPIOC );

Gpio i2c_scl(GPIOB, GPIO_Pin_6, RCC_APB2Periph_GPIOB );
Gpio i2c_sda(GPIOB, GPIO_Pin_7, RCC_APB2Periph_GPIOB );
I2cSoft ds3231(i2c_sda, i2c_scl);

void setup() {

	led_green.init(GPIO_Mode_Out_PP);
	led_blue.init(GPIO_Mode_Out_PP);

	nvic.init(TIM2_IRQn, 0, 3, ENABLE);
	Tim t2(TIM2, RCC_APB1Periph_TIM2, RCC_APB1PeriphClockCmd);
	t2.init(1000, 1000);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM2, ENABLE);


}

void loop() {
	while (usart.available()) {
		char c = usart.read();
		fprintf(stdout, "0x%02X\r\n", c);
		led_blue.toggle();
	}


//	sd2068.start();
//	sd2068.transmit((0x68 << 1) | 0x01);
//	vu32 t = sd2068.waitAck();
//	sd2068.stop();

	u8 t = 0, cmd = 0, w = 0;

	w = ds3231.write(0xd0, &cmd, 1);
	ds3231.readFrom(0xd0, &t, 1);

	printf("[%02x] %02x\r\n", w, t);

	led_blue.toggle();

	delay(500);

}

