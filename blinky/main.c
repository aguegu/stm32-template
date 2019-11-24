#include <stm32f10x.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>

int main(void) {
  GPIO_InitTypeDef GPIO_InitStructure;

  // enable clock on APB2
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,  ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;    // output push-pull mode
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   // highest speed
  GPIO_Init(GPIOC, &GPIO_InitStructure) ;             // initialize port

  GPIO_SetBits(GPIOC, GPIO_Pin_13);    // turn the LED on
  while(1);
}
