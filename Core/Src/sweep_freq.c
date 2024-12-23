#include "sweep_freq.h"


#define START_FREQ 105000
#define END_FREQ 115000
#define STEP_FREQ 500 

uint32_t best_freq = START_FREQ;

void adcValue(void)
{
    for (int i = 0; i < ADC_BUFFER_SIZE; i++)
    {
        ADC_Value[i] = (adcBuffer[i] * 3300) / 4095.0f;

        switch (i % 2)
        {
        case 0:
            adcData.current_MOS = ADC_Value[i];
            break;
        case 1:
            adcData.voltage_MOS = ADC_Value[i];
            break;
        }
    }
}

void sweepFreq(void)
{
    uint32_t freq = START_FREQ;

    for (freq = START_FREQ; freq <= END_FREQ; freq += STEP_FREQ)
    {
        // 设置PWM频率
        StartPWM(&htim1, TIM_CHANNEL_1, freq); // 调用喷雾函数
        SEGGER_RTT_printf(0, "Freq: %lu Hz, Current: %.2f V\n", freq, adcBuffer);

        HAL_Delay(500); // 延迟，确保系统稳定

        // 停止PWM输出
        HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_3);
    }
}
