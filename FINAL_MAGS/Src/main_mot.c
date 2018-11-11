#include "stm32f1xx_hal.h"

#define M_HIGH 2000
#define M_MID 1500
#define M_LOW 1000

int calibration=0;//calibration variation
int M_speed[8]={1425,M_MID,1575,1600,1625,1650,1675,1700};
int M_direction[11]={1010,1100,1200,1300,1400,1500,1600,1700,1800,1900,1990};

extern int flag_1,flag_2,flag_3;
extern int M_spd;
extern int M_dir;


//main moter calibration fun
void main_mot_cal()
{
    switch(calibration)
    {
        case 2 :    TIM3->CCR3=M_MID;         break;
        case 3 :    TIM3->CCR3=M_LOW;         break;
        case 4 :    TIM3->CCR3=M_HIGH;        break;
        case 5 :    TIM3->CCR3=M_MID;         break;
        default : break;
    }
}

//main moter calibration_ PORTC_PIN8_EXTI
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin==GPIO_PIN_8)
    {
        calibration++;
        main_mot_cal();                                 //main moter calibration ft
        if(calibration>6)
           calibration=0;
    }
}

//main moter speed controll
void main_mot_speed()
{       
        TIM3->CCR3=M_speed[M_spd];
        if((flag_1!=0)&&(flag_2!=0)&&(flag_3!=0))
        printf("s%d",M_spd);
}      

//main moter direction controll
void main_mot_dir()
{ 
        TIM3->CCR1=M_direction[M_dir];
            if((0<=M_dir)&&(M_dir<10))
              printf("d0%d",M_dir);
            else
              printf("d%d",M_dir);
 }