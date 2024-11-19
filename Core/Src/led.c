#include "main.h"
#include "led.h"
#include "tim.h"
#include "stm32c0xx_it.h"
#include "stm32c0xx_hal_tim.h"

#ifdef ENABLE_LED

// 进程灯GPIO表
LEDPin_t processLEDs[INDICATE_LED_Count] = {
    {LED_Proc1_GPIO_Port, LED_Proc1_Pin},
    {LED_Proc2_GPIO_Port, LED_Proc2_Pin},
    {LED_Proc3_GPIO_Port, LED_Proc3_Pin},
    {LED_Proc4_GPIO_Port, LED_Proc4_Pin},
    {LED_Proc5_GPIO_Port, LED_Proc5_Pin}};

// 时间灯GPIO表
LEDPin_t timeLEDs[] = {
    {L_LED_GPIO_Port, L_LED_Pin}, // 15分钟灯
    {H_LED_GPIO_Port, H_LED_Pin}  // 30分钟灯
};

// 指示灯GPIO表
LEDPin_t indicateLEDs[] = {
    {LED_Normal_GPIO_Port, LED_Normal_Pin}, // 状态灯
    {LED_Alarm_GPIO_Port, LED_Alarm_Pin}    // 报警灯
};

// 闪烁状态记录
static uint8_t blinkState = 0; // 用于控制闪烁

// 控制进程灯
void ProcessLED_Ctl(ProcessLED_t led, LEDState_t state)
{
    if (led >= INDICATE_LED_Count)
        return;
    HAL_GPIO_WritePin(processLEDs[led].port, processLEDs[led].pin,
                      (state == LED_ON) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    if (state == LED_BLINK)
    {
        // 这里可以添加到一个闪烁管理表中
    }
}

// 控制时间灯
void TimeLED_Ctl(TimeLED_t led, LEDState_t state)
{
    HAL_GPIO_WritePin(timeLEDs[led].port, timeLEDs[led].pin,
                      (state == LED_ON) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

// 控制指示灯
void IndicatorLED_Ctl(IndicatorLED_t led, LEDState_t state)
{
    HAL_GPIO_WritePin(indicateLEDs[led].port, indicateLEDs[led].pin,
                      (state == LED_ON) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

// 闪烁管理器
void LED_Blink_Handler(void)
{
    blinkState = !blinkState;
    // 遍历所有需要闪烁的灯，按需开关
    // 示例代码中没有具体实现闪烁管理表
}



// // 初始化LED GPIO
// void LED_Init(void)
// {
//     // 初始化 GPIO 引脚配置, 例如:
//     // HAL_GPIO_WritePin(LED_Proc1_GPIO_Port, LED_Proc1_Pin, GPIO_PIN_RESET);
//     // HAL_GPIO_WritePin(LED_Normal_GPIO_Port, LED_Normal_Pin, GPIO_PIN_SET);
// }

// // 设置LED状态
// void LED_SetState(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, LED_State state)
// {
//     switch (state)
//     {
//     case LED_OFF:
//         HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
//         break;
//     case LED_ON:
//         HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
//         break;
//     case LED_BLINK:
//         LED_Toggle(GPIOx, GPIO_Pin);
//         break;
//     case LED_BREATHE:
//         // 呼吸灯效果通过PWM控制
//         break;
//     }
// }

// // 切换LED状态
// void LED_Toggle(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
// {
//     HAL_GPIO_TogglePin(GPIOx, GPIO_Pin);
// }

// // 控制LED_Proc1~5的顺序亮灭
// void LED_CtlSequence(void)
// {
//     // 重置所有LED
//     LED_SetState(LED_Proc1_GPIO_Port, LED_Proc1_Pin, LED_OFF);
//     LED_SetState(LED_Proc2_GPIO_Port, LED_Proc2_Pin, LED_OFF);
//     LED_SetState(LED_Proc3_GPIO_Port, LED_Proc3_Pin, LED_OFF);
//     LED_SetState(LED_Proc4_GPIO_Port, LED_Proc4_Pin, LED_OFF);
//     LED_SetState(LED_Proc5_GPIO_Port, LED_Proc5_Pin, LED_OFF);

//     if (proc_sequence_phase == 0) // 依次熄灭
//     {
//         if (current_proc_led < 5)
//         {
//             LED_SetState(LED_Proc1_GPIO_Port + current_proc_led, LED_Proc1_Pin << current_proc_led, LED_ON);
//             current_proc_led++;
//         }
//         else
//         {
//             current_proc_led = 0;
//             proc_sequence_phase = 1; // 切换到全亮阶段
//         }
//     }
//     else if (proc_sequence_phase == 1) // 全亮
//     {
//         LED_SetState(LED_Proc1_GPIO_Port, LED_Proc1_Pin, LED_ON);
//         LED_SetState(LED_Proc2_GPIO_Port, LED_Proc2_Pin, LED_ON);
//         LED_SetState(LED_Proc3_GPIO_Port, LED_Proc3_Pin, LED_ON);
//         LED_SetState(LED_Proc4_GPIO_Port, LED_Proc4_Pin, LED_ON);
//         LED_SetState(LED_Proc5_GPIO_Port, LED_Proc5_Pin, LED_ON);
//         proc_sequence_phase = 2; // 切换到依次熄灭阶段
//     }
//     else if (proc_sequence_phase == 2) // 依次熄灭
//     {
//         if (current_proc_led < 5)
//         {
//             LED_SetState(LED_Proc1_GPIO_Port + current_proc_led, LED_Proc1_Pin << current_proc_led, LED_OFF);
//             current_proc_led++;
//         }
//         else
//         {
//             current_proc_led = 0;
//             proc_sequence_phase = 0; // 切换回依次亮起阶段
//         }
//     }
// }

// // 控制LED_Alarm闪烁100ms
// void toggle_LED_Alarm(void)
// {
//     static uint8_t toggle = 0;
//     toggle = !toggle;
//     if (toggle)
//     {
//         LED_SetState(LED_Alarm_GPIO_Port, LED_Alarm_Pin, LED_ON);
//     }
//     else
//     {
//         LED_SetState(LED_Alarm_GPIO_Port, LED_Alarm_Pin, LED_OFF);
//     }
// }

// // 更新H_LED呼吸灯效果
// void update_H_LED_Breathe(void)
// {
//     static uint8_t breathe_direction = 1; // 呼吸灯亮度增加或减少
//     static uint16_t h_led_breathe_value = 0;

//     if (breathe_direction)
//     {
//         h_led_breathe_value++;
//         if (h_led_breathe_value >= 255)
//         {
//             breathe_direction = 0; // 反向
//         }
//     }
//     else
//     {
//         h_led_breathe_value--;
//         if (h_led_breathe_value == 0)
//         {
//             breathe_direction = 1; // 反向
//         }
//     }

//     // 通过PWM控制亮度
//     __HAL_TIM_SET_COMPARE(&htim14, TIM_CHANNEL_1, h_led_breathe_value);
// }

// // 更新L_LED呼吸灯效果
// void update_L_LED_Breathe(void)
// {
//     static uint8_t breathe_direction = 1; // 呼吸灯亮度增加或减少
//     static uint16_t l_led_breathe_value = 0;

//     if (breathe_direction)
//     {
//         l_led_breathe_value++;
//         if (l_led_breathe_value >= 255)
//         {
//             breathe_direction = 0; // 反向
//         }
//     }
//     else
//     {
//         l_led_breathe_value--;
//         if (l_led_breathe_value == 0)
//         {
//             breathe_direction = 1; // 反向
//         }
//     }

//     // 通过PWM控制亮度
//     __HAL_TIM_SET_COMPARE(&htim17, TIM_CHANNEL_1, l_led_breathe_value);
// }

#endif