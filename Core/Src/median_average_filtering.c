/**
 * @file median_average_filtering.c
 * @brief 中位值平均滤波
 * 
 * 该模块实现了中值滤波器结合均值滤波的方法，用于去除ADC采样值中的噪声。
 * 具体步骤如下：
 * 1. 从ADC获取N个采样值。
 * 2. 对这些采样值进行排序。
 * 3. 去掉最小值和最大值，对剩下的N-2个值求平均值。
 * 4. 返回计算得到的平均值。
 * 
 * @author Sandman
 * @date 2024-10-09
 * 
 * @note
 * - N值的选取范围为3到14。
 */

#include "median_average_filtering.h"
#include <stdint.h>

#define N 11    // N值的选取：3~14

uint16_t MedianAverageFilter()
{
    uint8_t count, i, j;
    uint16_t value_buf[N];
    uint32_t sum = 0;
    uint16_t temp = 0;

    // 采样
    for (count = 0; count < N; count++)
    {
//        value_buf[count] = get_ad();  // 获取ADC采样值
    }

    // 从小到大冒泡排序
    for (j = 0; j < (N - 1); j++)
    {
        for (i = 0; i < (N - j - 1); i++)
        {
            if (value_buf[i] > value_buf[i + 1])
            {
                temp = value_buf[i];
                value_buf[i] = value_buf[i + 1];
                value_buf[i + 1] = temp;
            }
        }
    }

    // 去极值并求平均值
    for (count = 1; count < N - 1; count++)
    {
        sum += value_buf[count];
    }

    return (uint16_t)(sum / (N - 2));  // 返回平均值
}