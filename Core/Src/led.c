#include "main.h"
#include "led.h"
#include "tim.h"
#include "stm32c0xx_it.h"
#include "stm32c0xx_hal_tim.h"

#ifdef ENABLE_LED

// LED状态枚举
typedef enum
{
    LED_OFF,  // 灭
    LED_ON,   // 亮
    LED_BLINK // 闪烁
} LEDState_t;

// LED控制结构
typedef struct
{
    GPIO_TypeDef *port; // GPIO端口
    uint16_t pin;       // GPIO引脚
    LEDState_t state;   // 当前状态
} LED_t;

LED_t leds[] = {
    {LED_Proc1_GPIO_Port, LED_Proc1_Pin, LED_OFF},  // 进程灯1
    {LED_Proc2_GPIO_Port, LED_Proc2_Pin, LED_OFF},  // 进程灯2
    {LED_Proc3_GPIO_Port, LED_Proc3_Pin, LED_OFF},  // 进程灯3
    {LED_Proc4_GPIO_Port, LED_Proc4_Pin, LED_OFF},  // 进程灯4
    {LED_Proc5_GPIO_Port, LED_Proc5_Pin, LED_OFF},  // 进程灯5
    {L_LED_GPIO_Port, L_LED_Pin, LED_OFF},          // 时间灯15min (L_LED)
    {H_LED_GPIO_Port, H_LED_Pin, LED_OFF},          // 时间灯30min (H_LED)
    {LED_Normal_GPIO_Port, LED_Normal_Pin, LED_ON}, // 状态灯（上电默认亮）
    {LED_Alarm_GPIO_Port, LED_Alarm_Pin, LED_OFF}   // 警告灯
};

// 时间基准变量
uint32_t lastBlinkTime = 0;    // 闪烁计时
uint8_t currentProcessLed = 0; // 当前闪烁的进程灯索引

// GPIO控制函数
void LED_Control(LED_t *led, LEDState_t state)
{
    switch (state)
    {
    case LED_OFF:
        HAL_GPIO_WritePin(led->port, led->pin, GPIO_PIN_RESET);
        break;
    case LED_ON:
        HAL_GPIO_WritePin(led->port, led->pin, GPIO_PIN_SET);
        break;
    case LED_BLINK:
        if ((HAL_GetTick() - lastBlinkTime) >= 500)
        { // 1Hz频率
            HAL_GPIO_TogglePin(led->port, led->pin);
            lastBlinkTime = HAL_GetTick();
        }
        break;
    }
}

// // 全局计数器
// uint16_t led_alarm_time_counter = 0; // LED_Alarm闪烁计数器
// uint16_t h_led_time_counter = 0;     // H_LED呼吸灯计数器
// uint16_t l_led_time_counter = 0;     // L_LED呼吸灯计数器
// uint16_t proc_led_time_counter = 0;  // LED_Proc1~5顺序控制计数器

// // 当前LED索引
// static uint8_t current_proc_led = 0;
// static uint8_t proc_sequence_phase = 0; // 0: 依次熄灭, 1: 全亮, 2: 依次熄灭

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
// void LED_ControlSequence(void)
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