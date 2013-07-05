#include "stm32-template.h"

Gpio led_green(GPIOC, GPIO_Pin_9, RCC_APB2Periph_GPIOC);
Gpio led_blue(GPIOC, GPIO_Pin_8, RCC_APB2Periph_GPIOC);
Gpio potentiometer(GPIOA, GPIO_Pin_6, RCC_APB2Periph_GPIOA);
Adc adc(ADC1, RCC_APB2Periph_ADC1);
Dma dma(DMA1_Channel1, RCC_AHBPeriph_DMA1, DMA1_FLAG_TC1);

void setup() {

	led_green.init(GPIO_Mode_Out_PP);
	led_blue.init(GPIO_Mode_Out_PP);
	potentiometer.init(GPIO_Mode_AIN);

	nvic.init(TIM2_IRQn, 0, 3, ENABLE);
	Tim t2(TIM2, RCC_APB1Periph_TIM2, RCC_APB1PeriphClockCmd);
	t2.init(1000, 1000);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	adc.init(ADC_Mode_Independent, DISABLE, DISABLE, ADC_ExternalTrigConv_None);
	adc.configChannel(ADC_Channel_6, 1);

	adc.calibrate();
}

void loop() {
	while (usart.available()) {
		char c = usart.read();
		fprintf(stdout, "0x%02X\r\n", c);
		led_blue.toggle();
	}

	adc.startSoftwareConvert();
	printf("%d\r\n", adc.getValue());

	led_blue.toggle();

	delayMicroseconds(100000);
}

