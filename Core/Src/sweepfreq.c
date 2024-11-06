#include "main.h"
float I_sum=0;
float cnt = 0;
enum WORKMODE = {fault,wuhua,.....}
void sweepfreq(void)
{
    for (uint32_t freq = START_FREQ; freq <= END_FREQ; freq += STEP_FREQ)
    {
        // 启动PWM
    // PWM的频率已知
        // 根据PWM频率计算出定时器的时间
        // 设置定时器
        // 使能定时器
        I_sum+=ADC_Value[2];
        cnt ++;
        // 等待定时器结束
    }
   
}

void work()
switch (workmode)
{
case sweepfreq:
    freq = (+=step)
    pwm
    sweepfreq(freq);
    
    dispcontext = .....
    displayEN;
    display()
    comm();
    // 状态切换条件
    if(切换了)
    workmode = wuhua;
    break;
case wuhua:
    wuhua——task（）
    disp_task()
    dispcontext = .....
    // 状态切换条件
    if(nowater了)
        workmode = fault;
    break;
case fault;
case alarm;
....
default:
    break;
}

void display(dispcontext)

void comm()

