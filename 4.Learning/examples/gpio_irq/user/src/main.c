#include "board.h"

void main()
{
    InitSysCtrl();

    InitPieCtrl();
    IER = 0x0000;  // disable CPU interrupts
    IFR = 0x0000;  // clear all CPU interrupt flags
    InitPieVectTable();

    /* User Code Begin */

    GPIO_Init();
    EXIT_Init();

    while (1) {
    }

    /* User Code End */
}
