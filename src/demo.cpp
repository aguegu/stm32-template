#include "stm32-template.h"

Gpio led_green(GPIOC, GPIO_Pin_9, RCC_APB2Periph_GPIOC);
Gpio led_blue(GPIOC, GPIO_Pin_8, RCC_APB2Periph_GPIOC);

Gpio ultrasonic_sensor_trig(GPIOB, GPIO_Pin_9, RCC_APB2Periph_GPIOB);
Gpio ultrasonic_sensor_echo(GPIOA, GPIO_Pin_8, RCC_APB2Periph_GPIOA);

void setup() {

	led_green.init(GPIO_Mode_Out_PP);
	led_blue.init(GPIO_Mode_Out_PP);

	nvic.init(TIM2_IRQn, 0, 3, ENABLE);
	nvic.init(TIM1_CC_IRQn, 0, 1, ENABLE);
	Tim t2(TIM2, RCC_APB1Periph_TIM2, RCC_APB1PeriphClockCmd);
	t2.init(1000, 1000);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	ultrasonic_sensor_trig.init(GPIO_Mode_AF_PP, GPIO_Speed_50MHz);
	ultrasonic_sensor_echo.init(GPIO_Mode_IPU, GPIO_Speed_50MHz);

	//ultrasonic_sensor_trig.set(Bit_RESET);

	Tim t4(TIM4, RCC_APB1Periph_TIM4, RCC_APB1PeriphClockCmd);
	t4.init(100000, 10000);

	TimOc t4_oc4(TIM4, TIM_OC4Init, TIM_SetCompare4);
	t4_oc4.init(TIM_OCMode_PWM1, TIM_OutputState_Enable,
	TIM_OutputNState_Disable);
	t4_oc4.setCompare(1);

	Tim t1(TIM1, RCC_APB2Periph_TIM1, RCC_APB2PeriphClockCmd);
	t1.init(2000000);
	TIM_ICInitTypeDef TIM_ICInitStructure;

	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICFilter = 0x0;

	TIM_ICInit(TIM1, &TIM_ICInitStructure);

	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_IndirectTI;
	TIM_ICInit(TIM1, &TIM_ICInitStructure);

	TIM_SelectInputTrigger(TIM1, TIM_TS_TI1FP1);
	TIM_SelectSlaveMode(TIM1, TIM_SlaveMode_Reset);
	TIM_SelectMasterSlaveMode(TIM1, TIM_MasterSlaveMode_Enable);

	TIM_ITConfig(TIM1, TIM_IT_CC2, ENABLE);
}

void loop() {

	extern uint16_t capture;

	while (usart.available()) {
		char c = usart.read();
		fprintf(stdout, "0x%02X\r\n", c);
	}

	led_blue.toggle();

	fprintf(stdout, "%d cm %d\r\n", capture / 58 / 2, capture);
	delay(200);
}

