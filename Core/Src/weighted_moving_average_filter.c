/**
 * @file weighted_moving_average_filter.c
 * @brief 加权递推平均滤波
 * 
 * 该模块实现了加权递推平均滤波的方法，用于平滑ADC采样值。
 * 
 * @author Sandman
 * @date 2024-10-09
 * 
 * @note
 * - 可以通过宏 `WEIGHTED_MOVING_AVERAGE_FILTER` 控制是否启用该功能。
 */

#include "weighted_moving_average_filter.h"
#include <stdint.h>

// 通过宏控制是否启用加权递推平均滤波功能
#if WEIGHTED_MOVING_AVERAGE_FILTER

// 定义滤波窗口大小
#define N 12

// 定义权重数组
const uint8_t weights[N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

// 定义存储采样值的缓冲区
uint16_t value_buf[N];
uint8_t index = 0;
uint32_t weighted_sum = 0;
uint32_t total_weight = 0;

// 初始化权重总和
static void initialize_weights()
{
    for (uint8_t i = 0; i < N; i++)
    {
        total_weight += weights[i];
    }
}

// 加权递推平均滤波函数
uint16_t weighted_moving_average_filter(uint16_t new_value)
{
    if (index == 0)
    {
        initialize_weights();
    }

    weighted_sum -= value_buf[index] * weights[index];
    value_buf[index] = new_value;
    weighted_sum += new_value * weights[index];
    index = (index + 1) % N;

    return (uint16_t)(weighted_sum / total_weight);
}

#endif // WEIGHTED_MOVING_AVERAGE_FILTER
