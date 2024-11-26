#ifndef __FUNC_H__
#define __FUNC_H__

#include "stdint.h"

extern volatile uint8_t is_signal_lost;
    
void startNeb(void);
void CheckSignalTimeout(void);

// 声明频率处理函数
void Handle_4Hz_Signal(void);
void Handle_8Hz_Signal(void);
void Handle_16Hz_Signal(void);
void Handle_Unknown_Signal(void);

#endif /*__FUNC_H__*/