#include "FSM.h"
#include "main.h"
#include "func.h"
#include "sweep_freq.h"

// 系统状态机
void systemStateMachine(void)
{
    switch (currentState)
    {
    case STATE_STANDBY:
//        if (isSweepRequested())
//        {
//            currentState = STATE_FREQ_SWEEP;
//            startFrequencySweep();
//        }
        break;

    case STATE_FREQ_SWEEP:
        // if (isFaultDetected())
        // {
        //     currentState = STATE_FAULT;
        //     handleFault();
        // }
        // else if (isSweepComplete())
        // {
        //     sweepFreq();
        //     currentState = STATE_PAUSE;
        // }
        
        sweepFreq();

        break;

    case STATE_PAUSE:
//        if (isAtomizeRequested())
//        {
//            currentState = STATE_ATOMIZE;
//            startAtomization();
//        }
//        else if (isStandbyRequested())
//        {
//            currentState = STATE_STANDBY;
//            stopAtomization();
//        }
        break;

    case STATE_ATOMIZE:
//        if (isFaultDetected())
//        {
//            currentState = STATE_FAULT;
//            handleFault();
//        }
//        else if (isPauseRequested())
//        {
//            currentState = STATE_PAUSE;
//            stopAtomization();
//        }
        break;

    case STATE_FAULT:

            //currentState = STATE_STANDBY;
            // clearFaultStatus();
        break;

    default:
        break;
    }
}


/*
void System_StateMachine(void) {
    static uint32_t elapsedTime = 0; // 记录经过的时间
    switch (systemState) {
        case SYSTEM_IDLE:
            // 状态灯保持亮
            LED_Control(&leds[7], LED_ON);
            // 所有其他灯灭
            for (int i = 0; i < 7; i++) {
                LED_Control(&leds[i], LED_OFF);
            }
            break;

        case SYSTEM_WORK_15MIN:
        case SYSTEM_WORK_30MIN: {
            // 工作时段逻辑
            uint32_t targetTime = (systemState == SYSTEM_WORK_15MIN) ? 15 * 60 * 1000 : 30 * 60 * 1000; // 毫秒
            uint8_t timeLedIndex = (systemState == SYSTEM_WORK_15MIN) ? 5 : 6;

            // 对应时间灯常亮
            LED_Control(&leds[timeLedIndex], LED_ON);

            // 进程灯渐少逻辑
            uint32_t stepTime = targetTime / 5;
            currentProcessLed = elapsedTime / stepTime;

            for (int i = 0; i < 5; i++) {
                if (i < currentProcessLed) {
                    LED_Control(&leds[i], LED_OFF); // 已完成的进程灯灭
                } else if (i == currentProcessLed) {
                    LED_Control(&leds[i], LED_BLINK); // 当前灯闪烁
                } else {
                    LED_Control(&leds[i], LED_ON); // 未来的进程灯亮
                }
            }

            elapsedTime += 100; // 假设每次调用间隔100ms
            if (elapsedTime >= targetTime) {
                systemState = SYSTEM_IDLE; // 工作结束后回到待机
                elapsedTime = 0;
            }
            break;
        }
    }
}
*/