//main_mot.c
void main_mot_speed();
void main_mot_dir();
//water_mot.c
void water_mot_con(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
//G_servo.c
void servo_mot_dir();
//B_ADC.c
void Bat_check(ADC_HandleTypeDef* hadc);
//GPS.c
void GPS(UART_HandleTypeDef *huart1,UART_HandleTypeDef *huart2);
double long_Parse();
double lat_Parse();
double Yaw_Parse(UART_HandleTypeDef *huart1,UART_HandleTypeDef *huart2);

