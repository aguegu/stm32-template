#include "stm32-template.h"

Gpio led_green(GPIOC, GPIO_Pin_9, RCC_APB2Periph_GPIOC);
Gpio led_blue(GPIOC, GPIO_Pin_8, RCC_APB2Periph_GPIOC);

Gpio ultrasonic_sensor_trig(GPIOB, GPIO_Pin_9, RCC_APB2Periph_GPIOB);
Gpio ultrasonic_sensor_echo(GPIOA, GPIO_Pin_8, RCC_APB2Periph_GPIOA);

void setup() {

	led_green.init(GPIO_Mode_Out_PP);
	led_blue.init(GPIO_Mode_Out_PP);

	ultrasonic_sensor_trig.init(GPIO_Mode_AF_PP, GPIO_Speed_50MHz);
	ultrasonic_sensor_echo.init(GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);

	Tim t4(TIM4, RCC_APB1Periph_TIM4, RCC_APB1PeriphClockCmd);
	t4.init(100000, 10000);

	TimOc t4_oc4;
	t4_oc4.init(TIM_OCMode_PWM1, TIM_OutputState_Enable,
	TIM_OutputNState_Disable, 1);
	t4_oc4.apply(TIM4, TIM_OC4Init);

	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICFilter = 0x0;
	TIM_ICInit(TIM1, &TIM_ICInitStructure);

	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_IndirectTI;
	TIM_ICInit(TIM1, &TIM_ICInitStructure);

	TIM_SelectInputTrigger(TIM1, TIM_TS_TI1FP1);
	TIM_SelectSlaveMode(TIM1, TIM_SlaveMode_Reset);
	TIM_SelectMasterSlaveMode(TIM1, TIM_MasterSlaveMode_Enable);

	Tim t1(TIM1, RCC_APB2Periph_TIM1, RCC_APB2PeriphClockCmd);
//	t1.init(24000000);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

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

	led_blue.toggle();

	if (TIM_GetITStatus(TIM1, TIM_IT_CC1) == SET) {
		TIM_ClearITPendingBit(TIM1, TIM_IT_CC1);
		fprintf(stdout, "%d\r\n", TIM_GetCapture1(TIM1));
	}

	delay(1000);
}

