#include "stm32f10x.h"

// void delay(u32 ms) {
// 	extern vu32 millis;
// 	uint32_t start = millis;
//
// 	while (ms) {
// 		if (millis - start) {
// 			ms--;
// 			start++;
// 		}
// 	}
// }

void delay(int millis) {
	while (millis--) {
		volatile int x = 5971;
		while (x--) {
			__asm("nop");
		}
	}
}

void main(void) {
  GPIO_InitTypeDef GPIO_InitStructure;

  // enable clock on APB2
  // SysTick_Config(SystemCoreClock / 1000);	// Tick per ms
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,  ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  while(1) {
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
		delay(100);
    GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		delay(100);
  }
}


#ifdef  USE_FULL_ASSERT
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
void assert_failed(uint8_t* file, uint32_t line) {
  while (1);
}
#pragma GCC diagnostic pop
#endif
