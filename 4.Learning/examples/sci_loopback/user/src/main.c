#include "board.h"

// FIFO 效果:
//   在关闭 LoopBack 的情况下，上位机往下位机一次性发送 `AAAAAAAAAAAAAAAAAAAAAAAA` (24个A)
// 在收到第 1 个 A 后延时 1s, 在该段等待时间内 FIFO 被填冲 16 个 A。剩余的 7 个 A 没有及时接
// 收到，就被丢掉了。(注：FIFO 深度最大为 16)。因此 LED 的电平在 17s 内，翻转了 1+16 = 17 次

void main()
{
    u8 txch = 'A', rxch;

    InitSysCtrl();

    InitPieCtrl();
    IER = 0x0000;
    IFR = 0x0000;
    InitPieVectTable();

    /* User Code Begin */

    GPIO_Init();
    EXIT_Init();

    SCIB_Init();
    SCIC_Init();

    // SCIx_SetLoopBack(ScicRegs, TRUE);

    while (1) {
        SCIC_TxChar(txch);
        rxch = SCIC_RxChar();
        if (txch == rxch) {
            LED_TOGGLE();
            DelayBlockS(1);
        }
    }

    /* User Code End */
}
