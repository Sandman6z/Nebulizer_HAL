#include "main.h"
#include "led.h"
#include "tim.h"
#include "stm32c0xx_it.h"
#include "stm32c0xx_hal_tim.h"


//// 当前LED索引
//static uint8_t current_proc_led = 0;
//static uint8_t proc_sequence_phase = 0; // 0: 依次熄灭, 1: 全亮, 2: 依次熄灭


// 设置LED状态
void LED_SetState(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, LED_State state)
{
    switch (state)
    {
    case LED_OFF:
        HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);  // 关闭 LED
        break;
    case LED_ON:
        HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);    // 打开 LED
        break;
    case LED_BLINK:
        HAL_GPIO_TogglePin(GPIOx, GPIO_Pin);  // 切换 LED 状态，闪烁
        break;
    }
}

// 初始化LED GPIO
void LED_Init(void)
{
    LED_SetState(LED_Proc1_GPIO_Port, LED_Proc1_Pin, LED_OFF);
    LED_SetState(LED_Proc2_GPIO_Port, LED_Proc2_Pin, LED_OFF);
    LED_SetState(LED_Proc3_GPIO_Port, LED_Proc3_Pin, LED_OFF);
    LED_SetState(LED_Proc4_GPIO_Port, LED_Proc4_Pin, LED_OFF);
    LED_SetState(LED_Proc5_GPIO_Port, LED_Proc5_Pin, LED_OFF);
    LED_SetState(LED_15mins_GPIO_Port, LED_15mins_Pin, LED_OFF);
    LED_SetState(LED_30mins_GPIO_Port, LED_30mins_Pin, LED_OFF);
    LED_SetState(LED_Normal_GPIO_Port, LED_Normal_Pin, LED_OFF);
    LED_SetState(LED_Alarm_GPIO_Port, LED_Alarm_Pin, LED_OFF);
}
