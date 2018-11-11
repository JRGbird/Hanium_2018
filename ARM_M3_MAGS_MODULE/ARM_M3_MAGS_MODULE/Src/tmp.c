#include "stm32f1xx_hal.h"
#include "module.h"

#define DQ_INPUT  0x00000040U// Input Floating Mode
#define DQ_OUTPUT 0x00000030U// Output Push Pull Mode
#define DQ        ((GPIOA->IDR & GPIO_PIN_1) == (uint32_t)GPIO_PIN_RESET) // 0 for high input, 1 for low input


int reset_ds18b20(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    int existence;

    // Master TX low output
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
    GPIOA->CRL=DQ_OUTPUT;
    //500us delay
    HAL_Delay(500);
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
    
    // Master Rx input mode
    GPIOA->CRL=DQ_INPUT;
    //50us delay
    HAL_Delay(50);
    
    // Master checks the existence
    existence = HAL_GPIO_ReadPin(GPIOx,GPIO_Pin)==(uint32_t)GPIO_PIN_RESET;//DQ;
    //500us delay
    HAL_Delay(500);
    // Output mode before write
    GPIOA->CRL=DQ_OUTPUT;
    
    return existence;
}

uint8_t read_byte(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    uint8_t data = 0x00;
    int i;
 
    for (i=0; i<8; i++)
    { 
        HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);   // pull the signal line low
        HAL_Delay(2);
        
        GPIOA->CRL=DQ_INPUT;
        HAL_Delay(10);
        
        if ((HAL_GPIO_ReadPin(GPIOx,GPIO_Pin)==(uint32_t)GPIO_PIN_RESET) == 0)//input HIgh
        {
            data |= (1<<i);
        }
        
        HAL_Delay(55);  // wait for ds18b20 to pull the line high
        HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
        GPIOA->CRL=DQ_OUTPUT;
        HAL_Delay(2);   // recovery time
    }
    return data;
}

// Write a byte to ds18b20
void write_byte(uint8_t data,GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    int i;
    for (i=0; i<8; i++)
    {
        // for and if statements give enough delay between slots
        if (data & (1<<i))  // data is high
        {
          HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);   // short period of a low state before pulling the signal line high
          HAL_Delay(2);
          HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);   
        }
        else
        {
          HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
        }
        
        HAL_Delay(60); // wait ds18b20 sampling time
        HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);         // high status between slots
    }
}
