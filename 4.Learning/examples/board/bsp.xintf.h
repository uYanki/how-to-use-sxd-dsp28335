#ifndef __BSP_XINTF_H__
#define __BSP_XINTF_H__

#include "common.h"

#if CONFIG_USING_XINTF_LCD1602

#  include "lib.lcd1602.h"

#  define LCD1602_EN  GpioDataRegs.GPBDAT.bit.GPIO61
#  define LCD1602_RW  GpioDataRegs.GPADAT.bit.GPIO27
#  define LCD1602_RS  GpioDataRegs.GPBDAT.bit.GPIO60
#  define LCD1602_DAT (*((volatile Uint16 *) 0x2c0000))

#endif  // CONFIG_USING_XINTF_LCD1602

void XINTF_Init(void);

#endif
