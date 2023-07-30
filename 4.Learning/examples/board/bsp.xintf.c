#include "bsp.xintf.h"

#include "bsp.gpio.h"

static void XINTF_LCD1602_Init(void);

void XINTF_Init(void)
{
    XINTF_LCD1602_Init();
}

void XINTF_LCD1602_Init(void)
{
#if CONFIG_USING_XINTF_LCD1602

    EALLOW;
    // enable gpio clock
    SysCtrlRegs.PCLKCR3.bit.GPIOINENCLK = 1;
    EDIS;

    extern void InitXintf(void);
    InitXintf();

    EALLOW;
    GpioCtrlRegs.GPBMUX2.bit.GPIO60 = GPIO_PIN_TYPE_STD;
    GpioCtrlRegs.GPBDIR.bit.GPIO60  = GPIO_DIR_MODE_OUT;
    GpioCtrlRegs.GPBMUX2.bit.GPIO61 = GPIO_PIN_TYPE_STD;
    GpioCtrlRegs.GPBDIR.bit.GPIO61  = GPIO_DIR_MODE_OUT;
    GpioCtrlRegs.GPAMUX2.bit.GPIO27 = GPIO_PIN_TYPE_STD;
    GpioCtrlRegs.GPADIR.bit.GPIO27  = GPIO_DIR_MODE_OUT;
    EDIS;

#endif
}
