#ifndef __BSP_ADC_H_
#define __BSP_ADC_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32c0xx_hal.h"
// #include "bsp_errno.h"


#define ADC_QUEUE_NUM   32
#define ADC_CHANL_NUM   2


extern volatile uint16_t gAdcResAvg[ADC_CHANL_NUM];

extern void bsp_ADC_Start_DMA(void);
extern void bsp_ADC_Stop_DMA(void);
extern uint16_t bsp_ADCtoMV(uint16_t value);

#ifdef __cplusplus
}
#endif

#endif /* __BSP_ADC_H_ */

