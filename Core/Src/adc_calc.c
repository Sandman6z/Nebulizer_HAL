#include "adc_calc.h"

// 假设VREF是ADC参考电压，这里需要根据实际情况设置
#define VREF 3.3f // 参考电压，单位：伏特

/**
 * @brief 将ADC值转换为电压
 * @param adc_value ADC原始值，范围为0到4095
 * @return 转换后的电压值，单位：伏特
 */
int32_t ADC_To_Voltage(uint16_t adc_value) {
    // 将12位ADC值转换为电压值
    return (uint16_t)adc_value * VREF / 4095.0f;
}
