#include "stm32f1xx_hal.h"

#define G_HIGH 1900
#define G_MID 1500
#define G_LOW 1100

int G_direction[9]={G_LOW,1200,1300,1400,G_MID,1600,1700,1800,G_HIGH};

extern int G_dir;

//gimbal pen(yaw) direction controll 
void servo_mot_dir()
{
        TIM1->CCR1=G_direction[G_dir];
        printf("D%d",G_dir);
}