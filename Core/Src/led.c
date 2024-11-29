#include "main.h"
#include "led.h"
#include "tim.h"
#include "stm32c0xx_it.h"
#include "stm32c0xx_hal_tim.h"


//// 当前LED索引
//static uint8_t current_proc_led = 0;
//static uint8_t proc_sequence_phase = 0; // 0: 依次熄灭, 1: 全亮, 2: 依次熄灭

// 初始化LED GPIO
void LED_Init(void)
{
    // 初始化 GPIO 引脚配置, 例如:
    // HAL_GPIO_WritePin(LED_Proc1_GPIO_Port, LED_Proc1_Pin, GPIO_PIN_RESET);
    // HAL_GPIO_WritePin(LED_Normal_GPIO_Port, LED_Normal_Pin, GPIO_PIN_SET);
}

// 设置LED状态
void LED_SetState(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, LED_State state)
{
    switch (state)
    {
    case LED_OFF:
        HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);  // 关闭 LED
        break;
    case LED_ON:
        HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);    // 打开 LED
        break;
    case LED_BLINK:
        HAL_GPIO_TogglePin(GPIOx, GPIO_Pin);  // 切换 LED 状态，闪烁
        break;
    }
}


