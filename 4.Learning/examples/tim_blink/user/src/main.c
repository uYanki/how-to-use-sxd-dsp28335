#include "board.h"

void main(void)
{
    InitSysCtrl();

    InitPieCtrl();
    IER = 0x0000;
    IFR = 0x0000;
    InitPieVectTable();

    /* User Code Begin */

    GPIO_Init();

#if CPU_FRQ_150MHZ
    TIM0_Init(150, 1e6);
    // TIM1_Init(150, 1e6);
    // TIM2_Init(150, 1e6);
#elif CPU_FRQ_100MHZ
    TIM0_Init(100, 1e6);
    // TIM1_Init(100, 1e6);
    // TIM2_Init(100, 1e6);
#endif

    while (1)
    {
    }

    /* User Code End */
}
