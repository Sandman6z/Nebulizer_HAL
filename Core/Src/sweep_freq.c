#include "sweep_freq.h"
#include "main.h"
#include "adc.h"
#include "tim.h"

#define START_FREQ 120000
#define END_FREQ 130000
#define STEP_FREQ 500 

uint32_t best_freq = START_FREQ;

void adcValue(void)
{
    for (int i = 0; i < ADC_BUFFER_SIZE; i++)
    {
        ADC_Value[i] = (adcBuffer[i] * 3.3f) / 4095.0f;

        switch (i % 7)
        {
        case 0:
            adcData.button = (ADC_Value[i] > 1.65f) ? 1 : 0;
            break;
        case 1:
            adcData.MCU_Temperature = ADC_Value[i];
            break;
        case 2:
            adcData.MCU_Vref = ADC_Value[i];
            break;
        case 3:
            adcData.MCU_VDD = ADC_Value[i];
            break;
        case 4:
            adcData.MCU_VSS = ADC_Value[i];
            break;
        case 5:
            adcData.current_MOS = ADC_Value[i];
            break;
        case 6:
            adcData.voltage_MOS = ADC_Value[i];
            break;
        }
    }
}

void sweepFreq(void)
{
    float max_current = 0.0f;
    
    uint32_t freq = START_FREQ;

    for (uint32_t freq = START_FREQ; freq <= END_FREQ; freq += STEP_FREQ)
    {
        // 设置PWM频率
        __HAL_TIM_SET_AUTORELOAD(&htim1, (SystemCoreClock / freq) - 1);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, (SystemCoreClock / (2 * freq))); // 50% 占空比
        HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);

        HAL_Delay(1000); // 延迟，确保系统稳定

        if(adcData.current_MOS > max_current)
        {
            max_current = adcData.current_MOS;
            best_freq = freq;
        }

        // 停止PWM输出
        HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_3);
    }
}