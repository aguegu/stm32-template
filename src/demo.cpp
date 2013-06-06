#include "stm32-template.h"
#include "st7735r/st7735r.h"

Gpio spi2_sck(GPIOB, GPIO_Pin_13, RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO );
Gpio spi2_mosi(GPIOB, GPIO_Pin_15, RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO );
Gpio spi2_miso(GPIOB, GPIO_Pin_14, RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO );

Gpio led_green(GPIOC, GPIO_Pin_9, RCC_APB2Periph_GPIOC );
Gpio led_blue(GPIOC, GPIO_Pin_8, RCC_APB2Periph_GPIOC );

Spi spi(SPI2, RCC_APB1Periph_SPI2, RCC_APB1PeriphClockCmd);
Gpio tft_ss(GPIOC, GPIO_Pin_0, RCC_APB2Periph_GPIOC );
Gpio tft_reset(GPIOC, GPIO_Pin_1, RCC_APB2Periph_GPIOC );
Gpio tft_rs(GPIOC, GPIO_Pin_2, RCC_APB2Periph_GPIOC );

St7735r tft(spi, tft_ss, tft_reset, tft_rs);

void setup() {

	fprintf(stderr, "hello, world\r\n");

	spi2_sck.init(GPIO_Mode_AF_PP, GPIO_Speed_50MHz);
	spi2_mosi.init(GPIO_Mode_AF_PP, GPIO_Speed_50MHz);
	spi2_miso.init(GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);

	led_green.init(GPIO_Mode_Out_PP);
	led_blue.init(GPIO_Mode_Out_PP);

	nvic.init(TIM2_IRQn, 0, 3, ENABLE);
	Tim t2(TIM2, RCC_APB1Periph_TIM2, RCC_APB1PeriphClockCmd);
	t2.init(1000, 1000);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM2, ENABLE);

	tft.init();
}

uint16_t colors[4] = { 0xffff, 0x1f, 0x07e0, 0xf800 };

void loop() {
	while (usart.available()) {
		char c = usart.read();
		fprintf(stdout, "0x%02X\r\n", c);
		led_blue.toggle();
	}

	static uint8_t i = 0;

	i %= 4;

	for (uint8_t j = 0; j < 4; j++) {
		uint16_t x = (i + j) % 4 / 2 * 64, y = (i + j) % 4 % 2 * 64;
		tft.setAddrWindow(x, y, x + 63, y + 63);
		tft.write16(1, colors[j], 64 * 64);
	}

	i++;

	led_blue.toggle();

	delay(200);
}

