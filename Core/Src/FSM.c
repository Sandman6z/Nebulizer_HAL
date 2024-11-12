#include "FSM.h"
#include "main.h"

// 系统状态机
void systemStateMachine(void)
{
    switch (currentState)
    {
    case STATE_STANDBY:
        if (isSweepRequested())
        {
            currentState = STATE_FREQUENCY_SWEEP;
            startFrequencySweep();
        }
        break;

    case STATE_FREQUENCY_SWEEP:
        if (isFaultDetected())
        {
            currentState = STATE_FAULT;
            handleFault();
        }
        else if (isSweepComplete())
        {
            best_freq = getBestFrequency();
            currentState = STATE_PAUSE;
        }
        break;

    case STATE_PAUSE:
        if (isAtomizeRequested())
        {
            currentState = STATE_ATOMIZE;
            startAtomization();
        }
        else if (isStandbyRequested())
        {
            currentState = STATE_STANDBY;
            stopAtomization();
        }
        break;

    case STATE_ATOMIZE:
        if (isFaultDetected())
        {
            currentState = STATE_FAULT;
            handleFault();
        }
        else if (isPauseRequested())
        {
            currentState = STATE_PAUSE;
            stopAtomization();
        }
        break;

    case STATE_FAULT:
        if (isFaultCleared())
        {
            currentState = STATE_STANDBY;
            clearFaultStatus();
        }
        break;

    default:
        break;
    }
}
