#include "stm32f1xx_hal.h"

void Bat_check(ADC_HandleTypeDef* hadc)
{
    double volt=0,temp=0;
    HAL_ADC_Start(hadc);
    if(HAL_ADC_PollForConversion(hadc,1000)==HAL_OK)
    {
        temp=(double)(3.3*(HAL_ADC_GetValue(hadc))/4096);
        volt=(double)(temp*(double)102/20);//R1+R2/R2
        printf("b%.1lf",volt);
    }
}
