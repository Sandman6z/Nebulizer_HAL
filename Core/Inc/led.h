#ifndef __LED_H__
#define __LED_H__

#include "main.h"

// LED状态定义
typedef enum
{
    LED_OFF,
    LED_ON,
    LED_BLINK
} LEDState_t;

// 进程灯
typedef enum
{
    INDICATE_LED_Proc1,
    INDICATE_LED_Proc2,
    INDICATE_LED_Proc3,
    INDICATE_LED_Proc4,
    INDICATE_LED_Proc5,
    INDICATE_LED_Count // 总数
} ProcessLED_t;

// 时间灯
typedef enum
{
    TIME_LED_15Min,
    TIME_LED_30Min
} TimeLED_t;

// 系统指示灯（状态和报警）
typedef enum
{
    INDICATOR_LED_Normal,
    INDICATOR_LED_Alarm
} IndicatorLED_t;

// 灯的GPIO定义
typedef struct
{
    GPIO_TypeDef *port;
    uint16_t pin;
} LEDPin_t;

// 函数声明
void ProcessLED_Ctl(ProcessLED_t led, LEDState_t state);
void TimeLED_Ctl(TimeLED_t led, LEDState_t state);
void IndicatorLED_Ctl(IndicatorLED_t led, LEDState_t state);
void LED_Blink_Handler(void); // 处理所有灯的闪烁逻辑

#endif /* __LED_H__ */
