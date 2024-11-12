#include "sweep_freq.h"
#include "main.h"
#include "adc.h"
#include "tim.h"

#define START_FREQ 125000
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
            ADCData.button = (ADC_Value[i] > 1.65f) ? 1 : 0;
            break;
        case 1:
            ADCData.MCU_Temperature = ADC_Value[i];
            break;
        case 2:
            ADCData.MCU_Vref = ADC_Value[i];
            break;
        case 3:
            ADCData.MCU_VDD = ADC_Value[i];
            break;
        case 4:
            ADCData.MCU_VSS = ADC_Value[i];
            break;
        case 5:
            ADCData.current_MOS = ADC_Value[i];
            break;
        case 6:
            ADCData.voltage_MOS = ADC_Value[i];
            break;
        }
    }
}

float calculateCurrentIntegral(uint16_t *adcBuffer, size_t N, float samplingFrequency)
{
    float integral = 0.0f;
    float deltaT = 1.0f / samplingFrequency;

    for (size_t i = 0; i < N; i++)
    {
        integral += adcBuffer[i] * deltaT;
    }

    return integral;
}

void sweepFreq(void)
{
    float max_integral = 0.0f;
    uint32_t freq = START_FREQ;

    for (uint32_t freq = START_FREQ; freq <= END_FREQ; freq += STEP_FREQ)
    {
        // 设置PWM频率
        __HAL_TIM_SET_AUTORELOAD(&htim1, (SystemCoreClock / freq) - 1);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, (SystemCoreClock / (2 * freq))); // 50% 占空比
        HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);

        HAL_Delay(1000); // 延迟，确保系统稳定

        // 计算当前频率下的积分值
        float integral = calculateCurrentIntegral(adcBuffer, ADC_BUFFER_SIZE, samplingFrequency);

        // 比较并更新最大积分值和最佳频率
        if (integral > max_integral)
        {
            max_integral = integral;
            best_freq = freq; // best_freq 就是拥有最大积分值的最佳频率
        }

        // 停止PWM输出
        HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_3);
    }
}
