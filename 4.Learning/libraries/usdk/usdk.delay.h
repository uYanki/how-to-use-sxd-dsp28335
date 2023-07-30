#ifndef __USDK_DELAY_H__
#define __USDK_DELAY_H__

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "usdk.basic.h"

//---------------------------------------------------------------------------
// Declarations
//---------------------------------------------------------------------------

#define TIME_UNIT_US 1UL
#define TIME_UNIT_MS (TIME_UNIT_US * 1e3)
#define TIME_UNIT_S  (TIME_UNIT_MS * 1e3)

//---------------------------------------------------------------------------
// Functions
//---------------------------------------------------------------------------

void   DelayInit(void);
void   DelayBlock(u32 nWaitTime);
bool_e DelayNonBlock(u32 nStartTick, u32 nWaitTime);
void   FirewareDelay(u32 nWaitTime);

#ifdef __cplusplus
}
#endif

#endif
