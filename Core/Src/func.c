#include "func.h"
#include "main.h"
#include "tim.h"
#include "led.h"

#define SELECT_FREQ 109000
#define SIGNAL_TIMEOUT_MS 1000 // 超时阈值（单位：毫秒）

volatile uint8_t is_signal_lost = 0; // 标志位：信号丢失状态

void startNeb(void)
{
  __HAL_TIM_SET_AUTORELOAD(&htim1, (SystemCoreClock / SELECT_FREQ) - 1);
  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, (SystemCoreClock / (1.5f * SELECT_FREQ))); // 50% 占空�??
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
}

void CheckSignalTimeout(void)
{

  uint32_t current_tick = HAL_GetTick();
  if ((current_tick - last_interrupt_tick > SIGNAL_TIMEOUT_MS) && !is_signal_lost)
  {
    // 信号超时，触发停止
    Handle_Unknown_Signal();
    is_signal_lost = 1; // 设置信号丢失标志
  }
  else if ((current_tick - last_interrupt_tick <= SIGNAL_TIMEOUT_MS) && is_signal_lost)
  {
    // 信号恢复
    is_signal_lost = 0;
  }
}

void Handle_4Hz_Signal(void)
{
  startNeb(); // 调用喷雾函数
  LED_SetState(LED_15mins_GPIO_Port, LED_15mins_Pin, LED_ON);
  for (uint8_t i = 0; i < 5; i++)
  {
    ProgressLED_SetState(i, LED_BLINK);
  }
}

// 处理 8Hz 信号
void Handle_8Hz_Signal(void)
{
  startNeb(); // 调用喷雾函数
  LED_SetState(LED_30mins_GPIO_Port, LED_30mins_Pin, LED_ON);
    for(uint8_t i = 0; i < 5; i++)
    {
  ProgressLED_SetState(i, LED_BLINK);
    }
    
    
    
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
    startNeb();
//  HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_3);
    ProgressLED_Init();
  LED_SetState(LED_15mins_GPIO_Port, LED_15mins_Pin, LED_OFF);
  LED_SetState(LED_30mins_GPIO_Port, LED_30mins_Pin, LED_OFF);
  LED_SetState(LED_Normal_GPIO_Port, LED_Normal_Pin, LED_ON);
}