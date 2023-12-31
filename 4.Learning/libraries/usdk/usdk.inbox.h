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
// Enums
//---------------------------------------------------------------------------

typedef enum {
    TIMES_ONESHOT    = 0,  // 单次
    TIMES_CONTINUOUS = 1,  // 连续
} times_e;

//---------------------------------------------------------------------------
// Functions
//---------------------------------------------------------------------------

s32 gcd(s32 a, s32 b);               ///< 求最大公约数, Greatest Common Divisor
s32 lcm(s32 a, s32 b);               ///< 求最小公倍数, Least Common Multiple

s32 isPrime(s32 n);                  ///< 是否为质数
u8  isPalindromeNumber(s32 num);     ///< 是否为回文数
u8  isPalindromeString(RO u8* str);  ///< 是否为回文字符串

#ifdef __cplusplus
}
#endif

#endif