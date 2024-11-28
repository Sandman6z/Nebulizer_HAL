#ifndef __FSM_H__
#define __FSM_H__

// 定义状态枚举
typedef enum
{
    STATE_STANDBY,
    STATE_FREQ_SWEEP,
    STATE_PAUSE,
    STATE_ATOMIZE,
    STATE_FAULT
} SystemState_t;

void systemStateMachine(void);

#endif /* __FSM_H__ */