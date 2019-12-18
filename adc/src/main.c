#include "cmsis_device.h"
#include "cortexm/ExceptionHandlers.h"

void delay(u32);

vu32 millis = 0;

void delay(u32 ms) {
	uint32_t start = millis;

	while (ms) {
		if (millis - start) {
			ms--;
			start++;
		}
		__WFI();
	}
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void main(int argc, char* argv[]) {
  SysTick_Config(SystemCoreClock / 10000);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

	// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	// GPIO_Init(GPIOA, &GPIO_InitStructure);

  RCC_ADCCLKConfig(RCC_PCLK2_Div8); // 72MHz / 8 = 9MHz
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  ADC_DeInit(ADC1);

  ADC_InitTypeDef  ADC_InitStructure;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Left;
  ADC_InitStructure.ADC_NbrOfChannel = 1;

  ADC_Init(ADC1, &ADC_InitStructure);
  ADC_Cmd(ADC1, ENABLE);

  ADC_ResetCalibration(ADC1);
  while(ADC_GetResetCalibrationStatus(ADC1)) {

	}
  ADC_StartCalibration(ADC1);
  while(ADC_GetCalibrationStatus(ADC1)) {

	}

	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_239Cycles5);

 	u32 pw = 200;
	u32 t = 1000;
  while (1) {
		ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	 	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
		pw = ADC_GetConversionValue(ADC1) >> 8;

    GPIO_SetBits(GPIOC, GPIO_Pin_13);
		delay(pw);
    GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		delay(t - pw);
  }
}

#pragma GCC diagnostic pop

void SysTick_Handler (void) {
  millis++;
}
