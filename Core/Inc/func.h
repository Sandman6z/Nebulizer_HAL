#ifndef __FUNC_H__
#define __FUNC_H__

void startNeb(void);

// 声明频率处理函数
void Handle_4Hz_Signal(void);
void Handle_8Hz_Signal(void);
void Handle_16Hz_Signal(void);
void Handle_Unknown_Signal(void);

#endif /*__FUNC_H__*/