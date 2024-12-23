#include "main.h"
#include "led.h"
#include "tim.h"
#include "stm32g0xx_it.h"
#include "stm32g0xx_hal_tim.h"

// 定义进度灯的 GPIO 配置
static GPIO_TypeDef *progress_led_ports[] = {
    LED_Proc1_GPIO_Port,
    LED_Proc2_GPIO_Port,
    LED_Proc3_GPIO_Port,
    LED_Proc4_GPIO_Port,
    LED_Proc5_GPIO_Port,
};

static const uint16_t progress_led_pins[] = {
    LED_Proc1_Pin,
    LED_Proc2_Pin,
    LED_Proc3_Pin,
    LED_Proc4_Pin,
    LED_Proc5_Pin,
};

/**
 * @brief 设置指定 LED 的状态
 * @param GPIOx: LED 所在的 GPIO 端口
 * @param GPIO_Pin: LED 所对应的 GPIO 引脚
 * @param state: 要设置的 LED 状态 (LED_OFF, LED_ON, LED_BLINK)
 */
void LED_SetState(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, LED_State state)
{
    switch (state)
    {
    case LED_OFF:
        HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET); // 关闭LED
        break;
    case LED_ON:
        HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET); // 打开LED
        break;
    case LED_BLINK:
        HAL_GPIO_TogglePin(GPIOx, GPIO_Pin); // 切换LED状态，闪烁
        break;
    }
}

/**
 * @brief 初始化所有进度灯
 */
void ProgressLED_Init(void)
{
    for (uint8_t i = 0; i < sizeof(progress_led_pins) / sizeof(progress_led_pins[0]); i++)
    {
        LED_SetState(progress_led_ports[i], progress_led_pins[i], LED_OFF);
    }
}

/**
 * @brief 设置指定进度灯的状态
 * @param index: 进度灯的索引 (0~4)
 * @param state: 要设置的 LED 状态 (LED_OFF, LED_ON, LED_BLINK)
 */
void ProgressLED_SetState(uint8_t index, LED_State state)
{
    if (index < sizeof(progress_led_pins) / sizeof(progress_led_pins[0]))
    {
        LED_SetState(progress_led_ports[index], progress_led_pins[index], state);
    }
}

/**
 * @brief 初始化所有 LED，默认关闭
 */
void LED_Init(void)
{
    // 进度灯
    ProgressLED_Init();

    // 时间指示灯
    LED_SetState(LED_15mins_GPIO_Port, LED_15mins_Pin, LED_OFF);
    LED_SetState(LED_30mins_GPIO_Port, LED_30mins_Pin, LED_OFF);

    // 状态和报警灯
    LED_SetState(LED_Normal_GPIO_Port, LED_Normal_Pin, LED_OFF);
    LED_SetState(LED_Alarm_GPIO_Port, LED_Alarm_Pin, LED_OFF);
}
