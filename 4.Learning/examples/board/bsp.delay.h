#ifndef __DELAY_H__
#define __DELAY_H__

#include "common.h"

///<! only supports RAM, not FLASH
#define DelayBlockUS(us) DSP28x_usDelay((((1e3 * (f64) (us)) / (f64) CPU_RATE) - 9.0L) / 5.0L)
#define DelayBlockMS(ms) DelayBlockUS(1e3 * (ms))
#define DelayBlockS(s)   DelayBlockMS(1e3 * (s))

#endif  //! __DELAY_H__
