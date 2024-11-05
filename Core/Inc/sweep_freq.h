#ifndef __SWEEP_FREQ_H
#define __SWEEP_FREQ_H

#include "main.h"
#include "adc.h" // 确保包含adc.h，便于访问adcData

extern uint32_t best_freq;

void adcValue(void);

/**
 * @brief Sweeps through frequency range and finds the best frequency 
 * based on current_MOS value from ADC.
 */
void sweepFreq(void);

#endif /* __SWEEP_FREQ_H */
