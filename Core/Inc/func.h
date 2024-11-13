#ifndef __FUNC_H__
#define __FUNC_H__

#ifndef FUNC_H
#define FUNC_H

#include "main.h"

// 启动、暂停和停止的控制函数
void startFrequencySweep(void);
void stopFrequencySweep(void);
void startAtomization(void);
void stopAtomization(void);

// 状态相关的控制函数
void handleFault(void);
void clearFaultStatus(void);

// PWM波相关的频率设置函数
void setPWMFrequency(uint32_t freq);
void setPWMDutyCycle(uint32_t dutyCycle);

#endif // FUNC_H


#endif /* __FUNC_H__ */