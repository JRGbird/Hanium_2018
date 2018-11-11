#include "stm32f1xx_hal.h"
#include <string.h>
#include "total.h"


//  int k=0,q=0;
//  int count3 = 0;
//  int u=0;
//  int index=0;
//  
//  uint8_t rx_buf[1];
//  uint8_t gps_buf[500];
//  uint8_t BUF[600];
//  uint8_t lat1[2];
//  uint8_t lat2[2];
//  uint8_t lat3[5];
//  uint8_t longt1[3];
//  uint8_t longt2[2];
//  uint8_t longt3[5];
  uint8_t YAW[25];
  uint8_t YawP[5];
  uint8_t YAWT[1];
  
  
  int intyaw1;
  int intyaw2;
  int intyaw3;
  int intyaw4;
  int intyaw5;
  double Yaw;
  
//  uint8_t DGPS1[9];
//  uint8_t DGPS2[10];

 
  
  
//void GPS(UART_HandleTypeDef *huart1,UART_HandleTypeDef *huart2)
//{
//      int i;
//      int count=0;
//
//      while(1)
//      {
//        if(HAL_UART_Receive(huart2,rx_buf,1,100)==HAL_OK){
//          BUF[count] = *rx_buf; 
//          count++;
//        }
//        if(count==600){
//          count=0;
//          break;
//        }
//      }
//      //HAL_UART_Transmit(huart1,BUF,600,1000);
//}
//  
//double lat_Parse()
//{
//	int i, j, s;
//	int f=0;
//	int count = 0;
//	int d=0;
//	int lati1;
//	double lati2;
//	double latitude;
//	int latnum1;
//	int latnum2;
//	int latdouble1;
//	int latdouble2;
//	int latdouble3;
//	int latdouble4;
//	int latdouble5;
//	int latdouble6;
//	int latdouble7;
//	
//    for(i=0; i<strlen(BUF); i++)
//    {
//      if(BUF[i] == 'R')
//      {
//        f=i;
//      }
//    }
//    
//    for(j=f; j<strlen(BUF); j++)
//        {
//          if(BUF[j] == ',')
//          {
//            count++;
//          }
//          if(count == 2)
//          {
//            d=j;
//            for(s=0; s<2; s++)
//            {
//              lat1[s] = BUF[d+s+3];
//            }
//            for(s=0; s<2; s++)
//            {
//              lat2[s] = BUF[d+s+5];
//            }
//            for(s=0; s<5; s++)
//            {
//              lat3[s] = BUF[d+s+8];
//            }
//            count = 0;
//            break;
//          }
//        }
//    
//    latnum1 = lat1[0]-48;
//    latnum2 = lat1[1]-48;
//    
//    latdouble1 = lat2[0]-48;
//    latdouble2 = lat2[1]-48;
//    latdouble3 = lat3[0]-48;
//    latdouble4 = lat3[1]-48;
//    latdouble5 = lat3[2]-48;
//    latdouble6 = lat3[3]-48;
//    latdouble7 = lat3[4]-48;
//    
//    lati1 = latnum1*10 + latnum2;
//    lati2 = latdouble1*10 + latdouble2 + latdouble3*0.1 + latdouble4*0.01 + 
//			latdouble5*0.001 + latdouble6*0.0001 + latdouble7*0.00001;
//    
//    latitude = lati1 + lati2*0.01666;
//    
//    return latitude;
//}
//
//double long_Parse()
//{
//	int i, j, s;
//	int h=0;
//	int f=0;
//	int count =0;
//	int long1;
//    double long2;
//    double longtitude;
//    int longnum1;
//    int longnum2;
//    int longnum3;
//    int longdouble1;
//    int longdouble2;
//    int longdouble3;
//    int longdouble4;
//    int longdouble5;
//    int longdouble6;
//    int longdouble7;
//    for(i=0; i<strlen(BUF); i++)
//    {
//      if(BUF[i] == 'R')
//      {
//        f=i;
//      }
//    }
//    for(j=f; j<strlen(BUF); j++)
//        {
//          if(BUF[j] == ',')
//          {
//            count++;
//          }
//          
//          if(count == 5)
//          {
//            h=j;
//            for(s=0; s<3; s++)
//            {
//              longt1[s] = BUF[h+s+1];
//            }
//            for(s=0; s<2; s++)
//            {
//              longt2[s] = BUF[h+s+4];
//            }
//            for(s=0; s<5; s++)
//            {
//              longt3[s] = BUF[h+s+7];
//            }
//            
//            count = 0;
//            break;
//          }
//          
//        }
//    
//    longnum1 = longt1[0]-48;
//    longnum2 = longt1[1]-48;
//    longnum3 = longt1[2]-48;
//    
//    longdouble1 = longt2[0]-48;
//    longdouble2 = longt2[1]-48;
//    longdouble3 = longt3[0]-48;
//    longdouble4 = longt3[1]-48;
//    longdouble5 = longt3[2]-48;
//    longdouble6 = longt3[3]-48;
//    longdouble7 = longt3[4]-48;
//    
//    long1 = longnum1*100 + longnum2*10 + longnum3;
//    long2 = longdouble1*10 + longdouble2 + longdouble3*0.1 + longdouble4*0.01 
//			+ longdouble5*0.001 + longdouble6*0.0001 + longdouble7*0.00001 ;
//    
//    longtitude = long1 + long2*0.01666;
//
//    return longtitude;
//}

double Yaw_Parse(UART_HandleTypeDef *huart1,UART_HandleTypeDef *huart2)
{
	int i,j;
	int count2 = 0;
        int index1=0;
      HAL_UART_Receive(huart2, YAW, 25, 10);
      
      for(i=0; i<25; i++)
      {
        if(YAW[i]==',')
        {
          count2++;
          if(count2==2)
            index1=i;
        }
      }
      
      for(j=0; j<5; j++)
      {
        YawP[j] = YAW[index1+1+j];
      }
      
      count2 = 0;
      
      if(YawP[0]=='-')
      {
        if(YawP[4]=='.')
        {
          intyaw1 = YawP[1]-48;
          intyaw2 = YawP[2]-48;
          intyaw3 = YawP[3]-48;
          
          Yaw = -(intyaw1*100 + intyaw2*10 + intyaw3);
          //HAL_UART_Transmit(huart1, YawP, 5, 10000);
        }
        if(YawP[3]=='.')
        {
          intyaw1 = YawP[1]-48;
          intyaw2 = YawP[2]-48;
          intyaw3 = YawP[4]-48;
          
          Yaw = -(intyaw1*10 + intyaw2 + intyaw3*0.1);
          //HAL_UART_Transmit(huart1, YawP, 5, 10000);
        }
      }
      
      else if(YawP[3]=='.')
      {
        intyaw1 = YawP[0]-48;
        intyaw2 = YawP[1]-48;
        intyaw3 = YawP[2]-48;
        intyaw4 = YawP[4]-48;
        
        Yaw = intyaw1*100 + intyaw2*10 + intyaw3 + intyaw4*0.1;
        //HAL_UART_Transmit(huart1, YawP, 5, 10000);
      }
      if(YawP[2]=='.')
      {
        intyaw1 = YawP[0]-48;
        intyaw2 = YawP[1]-48;
        intyaw3 = YawP[3]-48;
        intyaw4 = YawP[4]-48;
        
        Yaw = intyaw1*10 + intyaw2 + intyaw3*0.1 + intyaw4*0.01;
        //HAL_UART_Transmit(huart1, YawP, 5, 1000);
      }
      
      return Yaw;
}





    
      
        
        
        
          
    
  