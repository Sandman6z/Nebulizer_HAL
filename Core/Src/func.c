#include "func.h"
#include "main.h"
#include "tim.h"

void startNeb(void)
{
  __HAL_TIM_SET_AUTORELOAD(&htim1, (SystemCoreClock / SELECT_FREQ) - 1);
  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, (SystemCoreClock / (1.5f * SELECT_FREQ))); // 50% 占空�??
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
}

void Handle_4Hz_Signal(void)
{
  startNeb(); // 调用喷雾函数
  // pwm output 4hz
}

// 处理 8Hz 信号
void Handle_8Hz_Signal(void)
{
  startNeb(); // 调用喷雾函数
  // pwm output 8hz
}

// 处理 16Hz 信号
void Handle_16Hz_Signal(void)
{
    // printf("Detected 16Hz signal\n");
  // 添加16Hz信号的处理逻辑，例如警报处理
  // 控制报警灯或者其他对应功能
}

// 处理未知信号
void Handle_Unknown_Signal(void)
{
  // printf("Unknown signal frequency: %.2f Hz\n", frequency);
  HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_3);
}