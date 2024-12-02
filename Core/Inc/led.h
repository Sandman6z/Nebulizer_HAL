#ifndef __LED_H
#define __LED_H

#include "main.h"

// 定义 LED 状态枚举
typedef enum
{
    LED_OFF = 0, // 关闭 LED
    LED_ON,      // 打开 LED
    LED_BLINK    // 闪烁 LED
} LED_State;

// 定义 LED 时间控制枚举
typedef enum
{
    LED_15mins, // 15分钟 LED
    LED_30mins  // 30分钟 LED
} LED_time;

// LED 控制函数声明
void LED_SetState(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, LED_State state); // 设置 LED 状态
void ProgressLED_Init(void);
void ProgressLED_SetState(uint8_t index, LED_State state);
void LED_Init(void); // 初始化 LED

#endif /* __LED_H */
