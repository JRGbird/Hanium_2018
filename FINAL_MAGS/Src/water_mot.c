#include "stm32f1xx_hal.h"

void water_mot_con(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    if(HAL_GPIO_ReadPin(GPIOx,GPIO_Pin)==GPIO_PIN_SET)
      TIM3->CCR2=20000;
    else
      TIM3->CCR2=0;
}