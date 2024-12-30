#ifndef __SWEEP_FREQ_H
#define __SWEEP_FREQ_H

#include "main.h"
#include "func.h"
#include "adc.h"
#include "tim.h"
#include <stdio.h>
#include "SEGGER_RTT.h"

extern uint32_t best_freq;

void adcValue(void);
void sweepFreq(void);

#endif /* __SWEEP_FREQ_H */
