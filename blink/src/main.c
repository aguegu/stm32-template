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
	}
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void main(int argc, char* argv[]) {
  SysTick_Config(SystemCoreClock / 1000);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  while (1) {
    GPIO_SetBits(GPIOC, GPIO_Pin_13);
		delay(1000);
    GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		delay(1000);
  }
}

#pragma GCC diagnostic pop

void SysTick_Handler (void) {
  millis++;
}
