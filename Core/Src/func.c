#include "func.h"
#include "main.h"
#include "tim.h"



void startNeb(void)
{  __HAL_TIM_SET_AUTORELOAD(&htim1, (SystemCoreClock / SELECT_FREQ) - 1);
  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, (SystemCoreClock / (1.5f * SELECT_FREQ))); // 50% 占空�??
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
}