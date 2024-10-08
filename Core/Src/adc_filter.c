#include "adc_filter.h"
#include <stdint.h>

#define N 11    //N值的选取：3~14

char filter()
{
    uint8_t count, i, j;
    uint16_t Value_buf[N];
    uint32_t sum = 0;
    uint16_t temp;

    // 采样
    for (count = 0; count < N; count++)
    {
        Value_buf[count] = get_ad();        //get_ad()get_ad()get_ad()get_ad()get_ad()get_ad()get_ad()get_ad()get_ad()get_ad()get_ad()get_ad()get_ad()get_ad()get_ad()get_ad()
    }

    // 排序
    for (j = 0; j < (N - 1); j++)
    {
        for (i = 0; i < (N - j - 1); i++)
        {
            if (Value_buf[i] > Value_buf[i + 1])
            {
                temp = Value_buf[i];
                Value_buf[i] = Value_buf[i + 1];
                Value_buf[i + 1] = temp;
            }
        }
    }

    // 去极值并求平均值
    for (count = 1; count < N - 1; count++)
    {
        sum += Value_buf[count];
    }

    return (char)(sum / (N - 2));
}