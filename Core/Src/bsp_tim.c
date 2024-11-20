#include "bsp_tim.h"
#include "main.h"
#include "sweep_freq.h"
#include "func.h"

volatile uint32_t input_captures[2] = {0}; // ???????
volatile uint32_t capture_index = 0;      // ????
volatile uint32_t signal_period = 0;      // ???????

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM3 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)
    {
        // ???????
        input_captures[capture_index] = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_3);

        // ????
        if (capture_index == 1) // ??????
        {
            if (input_captures[1] >= input_captures[0])
            {
                signal_period = input_captures[1] - input_captures[0];
            }
            else
            {
                signal_period = (htim->Init.Period + 1) + input_captures[1] - input_captures[0];
            }

            // ??????
            capture_index = 0;

            // ????????(??????? 8Hz)
            float frequency = 1.0f / (signal_period * (1.0f / 40000)); // ????
            if (frequency > 7.5 && frequency < 8.5)
            {
                startNeb();
            }
        }
        else
        {
            capture_index++;
        }
    }
}



