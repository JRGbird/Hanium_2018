#include "stm32f1xx_hal.h"
#include "total.h"

extern uint8_t buffer[1];

#define M_HIGH 2000
#define M_MID 1500
#define M_LOW 1000

//need to start value
int flag_1,flag_2,flag_3;
//lat, lon parse flag
int flag_4,flag_5;
//stop to GPS_Auto_sailing
int stop_flag=0;
//moter speed, moder direction, gimbal direction
int M_spd=1,M_dir=5,G_dir=4;

int flag_6;


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart1)
{
  if(huart1->Instance == USART1)
  {     
    switch(buffer[0])
    {
        case 'w' :
          if(flag_5==0)
          {
            M_spd++;
            if(M_spd>10)
              M_spd=10;
            main_mot_speed();           
            if(flag_1==0)
            {
                M_spd--;
                TIM3->CCR3=M_HIGH;
                flag_1=1;
            }
            else if(flag_3==0)
            {
                M_spd--;
                TIM3->CCR3=M_MID;
                flag_3=1;
            }
            buffer[0]=0;
          }
            break;
        case 's' :
          if(flag_5==0)
          {
            M_spd--;
            if(M_spd<0)
              M_spd=0;
            main_mot_speed();            
            if(flag_2==0)
            {
                M_spd++;
                TIM3->CCR3=M_LOW;
                flag_2=1;
            }
            buffer[0]=0;
          }
            break;
        case 'd' : 
          if(flag_5==0)
          {
            M_dir++;
            if(M_dir>10)
              M_dir=10;
            main_mot_dir();
            buffer[0]=0;
          }
            break;
        case 'a' : 
          if(flag_5==0)
          { 
            M_dir--;
            if(M_dir<0)
              M_dir=0;
            main_mot_dir();
            buffer[0]=0;
          }
            break;
        case 'q' : 
            G_dir++;
            if(G_dir>8)
              G_dir=8;
            servo_mot_dir();
            buffer[0]=0;
            break;
        case 'e' : 
            G_dir--;
            if(G_dir<0)
              G_dir=0;
            servo_mot_dir();
            buffer[0]=0;
            break;      
        case 'i' : 
            if(stop_flag>=1)
            {
              stop_flag=0;
              break;
            }
            stop_flag++;
            printf("i");
            buffer[0]=0;
            break;
        case 't' : 
          if(flag_5==0)
          {
            flag_4=1;
            printf("T");
            buffer[0]=0;
          }
            break;
        case 'p' : 
            flag_6=1;
            break;       
        default : break;
    }
  }
}