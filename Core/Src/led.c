#include "main.h"
#include "led.h"
#include "stm32c0xx_it.h"
#include "stm32c0xx_hal_tim.h"



// 初始化LED GPIO
void LED_Init(void)
{
    HAL_GPIO_WritePin(LED_15mins_GPIO_Port, LED_15mins_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_30mins_GPIO_Port, LED_30mins_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_Proc1_GPIO_Port, LED_Proc1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_Proc2_GPIO_Port, LED_Proc2_Pin, GPIO_PIN_RESET);
}
