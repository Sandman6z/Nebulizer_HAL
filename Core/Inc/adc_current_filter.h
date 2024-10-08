#ifndef ADC_CURRENT_FILTER_H
#define ADC_CURRENT_FILTER_H

#include <stdint.h>

// 声明滤波函数
uint16_t weighted_moving_average_filter(uint16_t new_value);

#endif // ADC_CURRENT_FILTER_H