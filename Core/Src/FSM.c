#include "FSM.h"
#include "main.h"
#include "func.h"

// 系统状态机
void systemStateMachine(void)
{
    switch (currentState)
    {
    case STATE_STANDBY:
        if (isSweepRequested())
        {
            currentState = STATE_FREQ_SWEEP;
            startFrequencySweep();
        }
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
            // clearFaultStatus();
        }
        break;

    default:
        break;
    }
}
