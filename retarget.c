#include <stdio.h>
#include "stm32c0xx_hal.h"
//#include "core_cm4.h"
#include "SEGGER_RTT.h"

//#pragma import(__use_no_semihosting)
//#pragma import(__use_no_semihosting_swi)

void _sys_exit(int x)
{
    x = x;
}

struct FILE {
    int handle;
};

FILE __stdout;
FILE __stdin;

int fputc(int ch, FILE *stream)
{
    return (SEGGER_RTT_PutChar(0, ch));

    //while((USART6->SR & 0X40) == 0);
    //USART6->DR = (uint8_t) ch;

    //while(USART_GetFlagStatus(USART6, USART_FLAG_TC) == RESET);
    //USART_SendData(USART6, (uint8_t)ch);

    //return ch;
}

int fgetc(FILE *stream)
{
    //while (ITM_CheckChar() != 1) {__NOP();}
    //return (ITM_ReceiveChar());
    return 0;
}

int ferror(FILE *stream)
{
    /* Your implementation of ferror */
    return EOF;
}

void _ttywrch(int ch)
{
    //while (ITM->PORT[0].u32 == 0) {__NOP();}
    //ITM->PORT[0].u8 = (unsigned char)ch;
}

