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

    while (1)
    {
        while (KEY3_READ())
        {
        	// 注：不要重定向 printf

            println("<println>");
            println("[%d][%3d]", 10000, 12345);
            println("[0x%x][%o][%c][%s]", 12, 22, 'd', "hello");

            LED_TOGGLE();

            DelayBlockMS(500);
        }
    }

    /* User Code End */
}
