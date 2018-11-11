#include "stm32f1xx_hal.h"
#include "module.h"

#define DS18B20_TEMP_STEP 0.0625

double wind_speed(ADC_HandleTypeDef* hadc)
{
    double raw_data=0,tmp=0;
    double wind=0;
    HAL_ADC_Start(hadc);
    if(HAL_ADC_PollForConversion(hadc,1000)==HAL_OK)
    {   
        raw_data=HAL_ADC_GetValue(hadc);
        tmp=(double)raw_data/4096*3.3;
        wind=(tmp-0.4)/1.6*32.4;
        if(wind<0)
        wind=0;
        //printf("w%.1lf\r\n",wind);
        //HAL_Delay(50000);
    }
    return wind;
}

double temperature(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    uint8_t MSB=0, LSB=0;
    uint16_t temp=0;
    double end=0;
    int i;

      i=reset_ds18b20(GPIOx, GPIO_Pin);
      if (i == 1) 
      {
        write_byte(0xCC,GPIOx, GPIO_Pin);// skip Rom
        write_byte(0x44,GPIOx, GPIO_Pin);// tmp Convert
        HAL_Delay(750000);//750ms 
        
        reset_ds18b20(GPIOx, GPIO_Pin);
        write_byte(0xCC,GPIOx, GPIO_Pin);// skip Rom
        write_byte(0xBE,GPIOx, GPIO_Pin);// read scratch pad
        
        LSB = read_byte(GPIOx, GPIO_Pin);
        MSB = read_byte(GPIOx, GPIO_Pin);
        temp=(MSB<<8)|LSB;
        
        if(temp & 0x8000)
	{
		temp = ~temp;
		temp += 1;
		//end = (DS18B20_TEMP_STEP * temp * -1);
	}
	else
	{
		end = (DS18B20_TEMP_STEP * temp);
                //printf("t%lf \r\n",end);
	}
        i=0;
      }
      return end;
}