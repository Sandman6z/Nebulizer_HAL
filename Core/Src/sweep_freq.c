#include "sweep_freq.h"

float max_power = 0.0f;
uint32_t best_freq = START_FREQ; // 最佳频率
volatile uint32_t freq = 130000;


typedef struct
{
  uint8_t button; // IN1 PA1
  float MCU_Temperature;
  float MCU_Vref;
  float MCU_VDD;
  float MCU_VSS;
  float current_MOS; // IN17  PB0
  float voltage_MOS; // IN18  PB1
} ADCData;

ADCData adcData = {0};

uint16_t adcValue()
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
        // printf("Frequency: %d Hz, Voltage: %.2f V, Current: %.2f A\n", freq, voltage, current); // 可以在这里添加更多数据采集和处理代码
    }
}

uint16_t sweep_freq()
{
    for (uint32_t freq = START_FREQ; freq <= END_FREQ; freq += STEP_FREQ)
    {
        // 设置PWM频率
        __HAL_TIM_SET_AUTORELOAD(&htim1, (SystemCoreClock / freq) - 1);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, (SystemCoreClock / (2 * freq))); // 50% 占空�?
        HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);

        HAL_Delay(500); // 延迟，确保系统稳�?

        // 读取电压和电流（假设IN17和IN18分别是电压和电流通道�?
        // voltage = (adcBuffer[0] * 3.3f) / 4095.0f; // IN17电压
        current = (adcBuffer[1] * 3.3f) / 4095.0f; // IN18电流

        power = voltage * current;                                                                                    // 计算功率
        printf("Frequency: %d Hz, Voltage: %.2f V, Current: %.2f A, Power: %.2f W\n", freq, voltage, current, power); // 可以在这里添加更多数据采集和处理代码
    } // 测试完成后，关闭PWM输出

    // 判断�?大功�?
    if (power > max_power)
    {
        max_power = power;
        best_freq = freq;
    }
}

// 扫频完成后，设置TIM1为最佳频率
__HAL_TIM_SET_AUTORELOAD(&htim1, (SystemCoreClock / freq) - 1);
__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, (SystemCoreClock / (2 * best_freq))); // 50% 占空�?
HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
}