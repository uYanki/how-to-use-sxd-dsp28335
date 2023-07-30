#ifndef __USDK_CRC_H__
#define __USDK_CRC_H__

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "usdk.basic.h"

//---------------------------------------------------------------------------
// Functions
//---------------------------------------------------------------------------

///< @note website for crc test: http://www.ip33.com/crc.html

u8  crc8(RO u8* dat, u16 len);
u16 crc16(RO u8* dat, u16 len);

#ifdef __cplusplus
}
#endif

#endif