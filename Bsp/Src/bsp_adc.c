#include "bsp_adc.h"
#include "adc.h"
#include "main.h"

volatile uint16_t gAdcResAvg[ADC_CHANL_NUM];

static volatile uint16_t gAdcResBuf[ADC_QUEUE_NUM * 2][ADC_CHANL_NUM];

void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc)
{
    uint32_t i = 0, j = 0;
    uint32_t AdcResSum[ADC_CHANL_NUM] = {0};

    for (i = 0; i < ADC_CHANL_NUM; i++) {
        for (j = 0; j < ADC_QUEUE_NUM; j++) {
            AdcResSum[i] += gAdcResBuf[j][i];
        }
        gAdcResAvg[i] = (AdcResSum[i] / ADC_QUEUE_NUM);
    }
    // HAL_ADC_Stop_DMA(hadc);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    uint32_t i = 0, j = 0;
    uint32_t AdcResSum[ADC_CHANL_NUM] = {0};

    for (i = 0; i < ADC_CHANL_NUM; i++) {
        for (j = ADC_QUEUE_NUM; j < ADC_QUEUE_NUM * 2; j++) {
            AdcResSum[i] += gAdcResBuf[j][i];
        }
        gAdcResAvg[i] = (AdcResSum[i] / ADC_QUEUE_NUM);
    }
    // HAL_ADC_Stop_DMA(hadc);
}

void bsp_ADC_Start_DMA(void)
{
    if (HAL_OK != HAL_ADCEx_Calibration_Start(&hadc1))
    {
        /* Calibration Error */
        Error_Handler();
    }

    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)gAdcResBuf, ADC_CHANL_NUM * ADC_QUEUE_NUM * 2);
}

void bsp_ADC_Stop_DMA(void)
{
    HAL_ADC_Stop_DMA(&hadc1);
}

uint16_t bsp_ADCtoMV(uint16_t value)
{
    float temp;
    if (value == 0) {
        return 0;
    }
    temp = 0.805664 * value + 0.5;
    return (uint16_t)temp;
}
