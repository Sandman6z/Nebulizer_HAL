#ifndef WEIGHTED_MOVING_AVERAGE_FILTER_H
#define WEIGHTED_MOVING_AVERAGE_FILTER_H

#include <stdint.h>

// 通过宏控制是否启用加权递推平均滤波功能
#if WEIGHTED_MOVING_AVERAGE_FILTER

// 定义滤波窗口大小
#define N 12

// 加权递推平均滤波函数
uint16_t weighted_moving_average_filter(uint16_t new_value);

#endif // WEIGHTED_MOVING_AVERAGE_FILTER

#endif // WEIGHTED_MOVING_AVERAGE_FILTER_H