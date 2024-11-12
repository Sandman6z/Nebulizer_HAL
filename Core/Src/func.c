#include "control.h"
#include "driver.h"
#include "main.h"

void startFrequencySweep(void)
{
    // 扫频开始的具体实现
    setFrequency(108.0f); // 设置初始频率
    startADCSampling();
}

void stopFrequencySweep(void)
{
    // 停止扫频
    stopADCSampling();
}

float getBestFrequency(void)
{
    // 返回找到的最佳频率
    return best_freq;
}

void startAtomization(void)
{
    // 启动雾化
    enableAtomizer();
}

void stopAtomization(void)
{
    // 停止雾化
    disableAtomizer();
}
