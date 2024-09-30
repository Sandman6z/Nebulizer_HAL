#ifndef __LED_H__
#define __LED_H__

#include "main.h"

extern uint16_t led_alarm_time_counter;
extern uint16_t h_led_time_counter;
extern uint16_t l_led_time_counter;
extern uint16_t proc_led_time_counter;

// LED 状态枚举
typedef enum {
    LED_OFF,
    LED_ON,
    LED_BLINK,
    LED_BREATHE
} LED_State;

// 函数声明
void LED_Init(void);
void LED_SetState(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, LED_State state);
void LED_Toggle(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void LED_ControlSequence(void);   // 控制LED_Proc1~5的顺序变化
void toggle_LED_Alarm(void);      // 控制LED_Alarm的100ms闪烁
void update_H_LED_Breathe(void);  // 控制H_LED的呼吸灯
void update_L_LED_Breathe(void);  // 控制L_LED的呼吸灯

#endif /* __LED_H__ */
