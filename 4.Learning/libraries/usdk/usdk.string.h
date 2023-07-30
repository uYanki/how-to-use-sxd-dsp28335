#ifndef __USDK_STRING_H__
#define __USDK_STRING_H__

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

fn_inline int _islower(int c) { return ('a' <= c && c <= 'z'); }
fn_inline int _isupper(int c) { return ('A' <= c && c <= 'Z'); }

fn_inline int _isalpha(int c) { return _islower(c) || _isupper(c); }

///< is decimal number
fn_inline int _isdigit(int c) { return ('0' <= c && c <= '9'); }
///< is hexadecimal number
fn_inline int _isxdigit(int c) { return (_isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')); }

fn_inline int _isspace(int c) { return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v'); }

s32 _str2dec(_IN_ RO u8* str);                          ///< ascii to decimal integer
u32 _str2hex(_IN_ RO u8* str);                          ///< ascii to hexadecimal integer
f32 _str2flt(_IN_ RO u8* str);                          ///< ascii to real
u8* _int2str(_OUT_ u8* str, s32 num, u8 base);          ///< integers from 2 to 36 bases convert to ascii

u32 _strlen(RO u8* str);                                ///< calculate the length of a string
s32 _strcmp(RO u8* str1, RO u8* str2);                  ///< compare the size of two strings
u8* _strcpy(u8* dest, RO u8* src);                      ///< copy the source string to the destination string
u8* _strncpy(u8* dest, RO u8* src, u32 len);            ///< copy the first n characters of the source string to the destination string
u8* _strcat(u8* dest, RO u8* src);                      ///< append the source string to the end of the destination string
u8* _strstr(RO u8* str, RO u8* substr);                 ///< find the position of a substring in a string
u8* _substr(u8* dest, RO u8* src, u32 start, u32 len);  ///< take n characters from a string starting at a certain position

u8* _strlwr(RO u8* str);                                ///< lower
u8* _strupr(RO u8* str);                                ///< upper

#ifdef __cplusplus
}
#endif

#endif
