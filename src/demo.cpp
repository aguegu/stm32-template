#include "stm32-template.h"

Gpio led_green(GPIOC, GPIO_Pin_9, RCC_APB2Periph_GPIOC);
Gpio led_blue(GPIOC, GPIO_Pin_8, RCC_APB2Periph_GPIOC);

Gpio ultrasonic_sensor_trig(GPIOB, GPIO_Pin_9, RCC_APB2Periph_GPIOB);
Gpio ultrasonic_sensor_echo(GPIOA, GPIO_Pin_8, RCC_APB2Periph_GPIOA);

void setup() {

	led_green.init(GPIO_Mode_Out_PP);
	led_blue.init(GPIO_Mode_Out_PP);

	nvic.init(TIM2_IRQn, 0, 3, ENABLE);
	Tim t2(TIM2, RCC_APB1Periph_TIM2, RCC_APB1PeriphClockCmd);
	t2.init(1000, 1000);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM2, ENABLE);

	ultrasonic_sensor_trig.init(GPIO_Mode_AF_PP, GPIO_Speed_50MHz);
	ultrasonic_sensor_echo.init(GPIO_Mode_IPD, GPIO_Speed_50MHz);

	//ultrasonic_sensor_trig.set(Bit_RESET);

	Tim t4(TIM4, RCC_APB1Periph_TIM4, RCC_APB1PeriphClockCmd);
	t4.init(100000, 10000);

	TimOc t4_oc4;
	t4_oc4.init(TIM_OCMode_PWM1, TIM_OutputState_Enable,
			TIM_OutputNState_Disable, 1);

	t4_oc4.apply(TIM4, TIM_OC4Init);
}

void loop() {
	while (usart.available()) {
		char c = usart.read();
		fprintf(stdout, "0x%02X\r\n", c);
		led_blue.toggle();
	}

	led_blue.toggle();

//	ultrasonic_sensor_trig.set(Bit_SET);
//	ultrasonic_sensor_trig.set(Bit_RESET);

	uint32_t t = 0;

	while (ultrasonic_sensor_echo.getInput() == Bit_RESET)
		;
	while (ultrasonic_sensor_echo.getInput() == Bit_SET) {
		t++;
	}

	fprintf(stdout, "%ld\r\n", t);

	delay(1000);
}

