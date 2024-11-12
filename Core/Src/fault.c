#include "fault.h"
#include "main.h"

void handleFault(void)
{
    // 处理故障
    disableAtomizer();
    stopFrequencySweep();
}

bool isFaultDetected(void)
{
    // 检测是否发生故障
    return readFaultStatus();
}

bool isFaultCleared(void)
{
    // 检测故障是否清除
    return readFaultStatus() == 0;
}
