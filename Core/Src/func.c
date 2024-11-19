#include "func.h"
#include "tim.h"
#include "adc.h"
#include "gpio.h"
#include "FSM.h"
#include "main.h"

// 启动扫频
void startFrequency(void)
{
    // 启动频率扫频
    // 配置相关的定时器、PWM或ADC等
    __HAL_TIM_SET_AUTORELOAD(&htim1, (SystemCoreClock / SELECT_FREQ) - 1);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, (SystemCoreClock / (2 * SELECT_FREQ))); // 50% 占空比
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
}

// 设置PWM频率
void setPWMFrequency(uint32_t freq)
{
    // 设置PWM波的频率
    __HAL_TIM_SET_AUTORELOAD(&htim1, (SystemCoreClock / freq) - 1);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, (SystemCoreClock / (2 * freq))); // 50% 占空比
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
}

// 设置PWM占空比
void setPWMDutyCycle(uint32_t dutyCycle)
{
    // 设置PWM的占空比
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, (SystemCoreClock / (2 * SELECT_FREQ)) * dutyCycle / 100);
}

// 停止扫频
void stopFrequency(void)
{
    // 停止频率扫频
    HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_3);
}

// 启动雾化
void startAtomization(void)
{
    // 启动雾化功能
    HAL_GPIO_WritePin(GPIOA, L_LED_Pin, GPIO_PIN_SET); // 启动LED指示
    // 配置相关硬件，如启用某些GPIO或PWM控制
}

// 停止雾化
void stopAtomization(void)
{
    // 停止雾化功能
    HAL_GPIO_WritePin(GPIOA, L_LED_Pin, GPIO_PIN_RESET); // 停止LED指示
    // 关闭相关硬件，如禁用某些GPIO或PWM
}

// 故障处理函数
void handleFault(void)
{
    // 故障发生时，执行的操作，如报警或禁用某些硬件
    HAL_GPIO_WritePin(GPIOC, LED_Alarm_Pin, GPIO_PIN_SET); // 点亮报警灯
    // 停止相关功能，如停止PWM或其他硬件
}

// 清除故障状态
void clearFaultStatus(void)
{
    // 清除故障状态，重置状态
    HAL_GPIO_WritePin(GPIOC, LED_Alarm_Pin, GPIO_PIN_RESET); // 熄灭报警灯
    // 恢复正常工作模式
}
