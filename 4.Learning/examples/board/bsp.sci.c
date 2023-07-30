#include "bsp.sci.h"

#include "bsp.gpio.h"

#include <stdarg.h>

#if CONFIG_USING_SCIB_RS232

void SCIB_Init(void)
{
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.SCIBENCLK = 1;
    EDIS;

    // InitScibGpio();
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO14   = GPIO_PULL_UP;
    GpioCtrlRegs.GPAPUD.bit.GPIO15   = GPIO_PULL_UP;
    GpioCtrlRegs.GPAQSEL1.bit.GPIO15 = GPIO_QUAL_ASYNC;
    GpioCtrlRegs.GPAMUX1.bit.GPIO14  = 2;  // SCITXDB
    GpioCtrlRegs.GPAMUX1.bit.GPIO15  = 2;  // SCIRXDB
    EDIS;

    ScibRegs.SCIFFTX.bit.TXFFINTCLR   = 1;  // clear int flag
    ScibRegs.SCIFFTX.bit.TXFIFOXRESET = 1;  // reset tx FIFO
    ScibRegs.SCIFFTX.bit.SCIFFENA     = 1;  // enable enhancement
    ScibRegs.SCIFFTX.bit.SCIRST       = 1;  // reset tx/rx channels

    SCIx_SetMode(ScibRegs, SCI_MODE_RX | SCI_MODE_TX);
    SCIx_SetIntState_RxError(ScibRegs, 0);
    SCIx_SetIntState_TxFIFO(ScibRegs, 1);
    SCIx_SetIntState_RxBreak(ScibRegs, 1);
    SCIx_SetFrameFormat(ScibRegs, CONFIG_SCIB_FRAME_FORMAT);
    SCIx_SetBaudrate(ScibRegs, CONFIG_SCIB_BAUDRATE);

    SCIx_SoftReset(ScibRegs);
}

void SCIB_TxChar(u8 ch)
{
    if (ch == '\n')
    {
        while (ScibRegs.SCIFFTX.bit.TXFFST) {}
        ScibRegs.SCITXBUF = '\r';
    }
    while (ScibRegs.SCIFFTX.bit.TXFFST) {}
    ScibRegs.SCITXBUF = ch;
}

void SCIB_TxString(RO u8 *str)
{
    while (*str) { SCIB_TxChar(*str++); }
}

void SCIB_TxBytes(RO u8 *arr, u16 len)
{
    while (len--) { SCIB_TxChar(*arr++); }
}

u8 SCIB_RxChar(void)
{
    // wait for inc character
    while (!ScibRegs.SCIFFRX.bit.RXFFST)
        ;  // wait for XRDY = 1 for empty state
    // get character
    return ScibRegs.SCIRXBUF.all;
}

#  if CONFIG_USING_SCIB_PRINTF

s32 SCIB_Printf(u8 *fmt, ...)
{
    static u8 buf[CONFIG_SPRINTF_BUFFER_SIZE];

    va_list args;

    u8 *ptr = buf;
    u32 len;

    va_start(args, fmt);
    len = vsnprintf(buf, CONFIG_SPRINTF_BUFFER_SIZE - 1, fmt, args);
    va_end(args);

#    if 0
     while (*ptr)
#    else
    while (len--)
#    endif
    {
        SCIB_TxChar(*ptr++);
    }

    return ptr - buf;
}

#  endif  // CONFIG_USING_SCIB_PRINTF

#endif    // CONFIG_USING_SCIB_RS232

#if CONFIG_USING_SCIC_RS232

void SCIC_Init(void)
{
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.SCICENCLK = 1;
    EDIS;

    // InitScicGpio();
    EALLOW;
    GpioCtrlRegs.GPBPUD.bit.GPIO62   = GPIO_PULL_UP;
    GpioCtrlRegs.GPBPUD.bit.GPIO63   = GPIO_PULL_UP;
    GpioCtrlRegs.GPBQSEL2.bit.GPIO62 = GPIO_QUAL_ASYNC;  // Asynch input
    GpioCtrlRegs.GPBMUX2.bit.GPIO62  = 1;                // SCIRXDC
    GpioCtrlRegs.GPBMUX2.bit.GPIO63  = 1;                // SCITXDC
    EDIS;

    ScicRegs.SCIFFTX.bit.TXFFINTCLR   = 1;  // clear int flag
    ScicRegs.SCIFFTX.bit.TXFIFOXRESET = 1;  // reset tx FIFO
    ScicRegs.SCIFFTX.bit.SCIFFENA     = 1;  // enable enhancement
    ScicRegs.SCIFFTX.bit.SCIRST       = 1;  // reset tx/rx channels

    SCIx_SetMode(ScicRegs, SCI_MODE_RX | SCI_MODE_TX);
    SCIx_SetIntState_RxError(ScicRegs, 0);
    SCIx_SetIntState_TxFIFO(ScicRegs, 1);
    SCIx_SetIntState_RxBreak(ScicRegs, 1);
    SCIx_SetFrameFormat(ScicRegs, CONFIG_SCIC_FRAME_FORMAT);
    SCIx_SetBaudrate(ScicRegs, CONFIG_SCIC_BAUDRATE);

    SCIx_SoftReset(ScicRegs);
}

void SCIC_TxChar(u8 chr)
{
    if (chr == '\n')
    {
        while (ScicRegs.SCIFFTX.bit.TXFFST) {}
        ScicRegs.SCITXBUF = '\r';
    }
    while (ScicRegs.SCIFFTX.bit.TXFFST) {}
    ScicRegs.SCITXBUF = chr;
}

void SCIC_TxString(RO u8 *str)
{
    while (*str) { SCIC_TxChar(*str++); }
}

void SCIC_TxBytes(RO u8 *arr, u16 len)
{
    while (len--) { SCIC_TxChar(*arr++); }
}

u8 SCIC_RxChar(void)
{
    while (!ScicRegs.SCIFFRX.bit.RXFFST) {}
    return ScicRegs.SCIRXBUF.all;
}

#  if CONFIG_USING_SCIC_PRINTF

s32 SCIC_Printf(u8 *fmt, ...)
{
    static u8 buf[CONFIG_SPRINTF_BUFFER_SIZE];

    va_list args;

    u8 *ptr = buf;
    u32 len;

    va_start(args, fmt);
    len = vsnprintf(buf, CONFIG_SPRINTF_BUFFER_SIZE - 1, fmt, args);
    va_end(args);

#    if 0
     while (*ptr)
#    else
    while (len--)
#    endif
    {
        SCIC_TxChar(*ptr++);
    }

    return ptr - buf;
}

#  endif  // CONFIG_USING_SCIC_PRINTF

#endif    // CONFIG_USING_SCIC_RS232
