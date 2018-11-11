double wind_speed(ADC_HandleTypeDef* hadc);

int reset_ds18b20(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
uint8_t read_byte(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void write_byte(uint8_t data,GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
double temperature(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

