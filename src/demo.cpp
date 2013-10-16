#include "stm32-template.h"

#include "tubes/iv22.h"

Gpio led_green(GPIOC, GPIO_Pin_9, RCC_APB2Periph_GPIOC);
Gpio led_blue(GPIOC, GPIO_Pin_8, RCC_APB2Periph_GPIOC);

Gpio ultrasonic_sensor_trig(GPIOB, GPIO_Pin_8, RCC_APB2Periph_GPIOB);
Gpio ultrasonic_sensor_echo(GPIOA, GPIO_Pin_8, RCC_APB2Periph_GPIOA);

Gpio tube_din(GPIOB, GPIO_Pin_6, RCC_APB2Periph_GPIOB);
Gpio tube_oe(GPIOB, GPIO_Pin_5, RCC_APB2Periph_GPIOB);
Gpio tube_st(GPIOB, GPIO_Pin_4, RCC_APB2Periph_GPIOB);
Gpio tube_sh(GPIOB, GPIO_Pin_3, RCC_APB2Periph_GPIOB);

Iv22 tubes(tube_din, tube_oe, tube_st, tube_sh, 4);

void setup() {

	led_green.init(GPIO_Mode_Out_PP);
	led_blue.init(GPIO_Mode_Out_PP);

	nvic.configure(TIM2_IRQn, 0, 3, ENABLE);
	nvic.configure(TIM1_CC_IRQn, 0, 1, ENABLE);
	Tim t2(TIM2, RCC_APB1Periph_TIM2, RCC_APB1PeriphClockCmd);
	t2.init(1000, 1000);

	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	ultrasonic_sensor_trig.init(GPIO_Mode_AF_PP, GPIO_Speed_50MHz);
	ultrasonic_sensor_echo.init(GPIO_Mode_IPU, GPIO_Speed_50MHz);

	//ultrasonic_sensor_trig.set(Bit_RESET);

	Tim t4(TIM4, RCC_APB1Periph_TIM4, RCC_APB1PeriphClockCmd);
	t4.init(100000, 10000);

	TimOc t4_oc3(TIM4, TIM_OC3Init, TIM_SetCompare3);
	t4_oc3.init(TIM_OCMode_PWM1,
	TIM_OutputState_Enable,
	TIM_OutputNState_Disable);
	t4_oc3.setCompare(1);

	Tim t1(TIM1, RCC_APB2Periph_TIM1, RCC_APB2PeriphClockCmd);
	t1.init(2000000);

	TimIc t1_ic1(TIM1);
	t1_ic1.init(TIM_Channel_1);

	TimIc t1_ic2(TIM1);
	t1_ic2.init(TIM_Channel_2, TIM_ICPolarity_Falling,
	TIM_ICSelection_IndirectTI);

	TIM_SelectInputTrigger(TIM1, TIM_TS_TI1FP1);
	TIM_SelectSlaveMode(TIM1, TIM_SlaveMode_Reset);
	TIM_SelectMasterSlaveMode(TIM1, TIM_MasterSlaveMode_Enable);

	TIM_ITConfig(TIM1, TIM_IT_CC2, ENABLE);

	tubes.init();
}

void loop() {

	extern uint16_t capture;

	while (usart.available()) {
		char c = usart.read();
		fprintf(stdout, "0x%02X\r\n", c);
	}

	led_blue.toggle();

	uint16_t mm = 5 * capture / 58;
	fprintf(stdout, "%d mm %d\r\n", mm, capture);

	tubes.clear();
	tubes.setBackgroundColor((Color) (mm / 500 % 8));
	tubes.printf("%4d", mm);
	tubes.setPoint(2);
	tubes.display();

	delay(200);

}

