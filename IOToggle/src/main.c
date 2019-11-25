#include "stm32f10x.h"

int main(void) {
  GPIO_InitTypeDef GPIO_InitStructure;

  // enable clock on APB2
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,  ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  while(1);
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
