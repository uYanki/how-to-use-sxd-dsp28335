#include "usdk.mem.h"

void* _memcpy(void* dest, RO void* src, u32 len)
{
    u8*    dp = dest;
    RO u8* sp = src;
    while (len--) { *dp++ = *sp++; }
    return dest;
}

void* _memmove(void* dest, RO void* src, u32 len)
{
    u8*    dp = dest;
    RO u8* sp = src;
    if (dp < sp) {
        while (len--) {
            *dp++ = *sp++;
        }
    } else if (dp > sp) {
        dp += len;
        sp += len;
        while (len--) {
            *--dp = *--sp;
        }
    }
    return dest;
}

void* _memset(void* src, u8 chr, u32 len)
{
    u8* p = src;
    while (len--) { *p++ = chr; }
    return src;
}

void _memswap(void* src1, void* src2, u32 len)
{
    u8* p1 = (u8*)src1;
    u8* p2 = (u8*)src2;
    u8  tmp;
    while (len--) {
        tmp   = *p1;
        *p1++ = *p2;
        *p2++ = tmp;
    }
}

s32 _memcmp(RO void* src1, RO void* src2, u32 len)
{
    RO u8 *p1 = src1, *p2 = src2;

    while (len--) {
        if (*p1 != *p2)
            return (*p1 > *p2) ? 1 : -1;
        ++p1, ++p2;
    }

    return 0;
}

void* _memfrob(void* src, u8 chr, u32 len)
{
    u8* p = src;
    while (len--) { *p++ ^= chr; }
    return src;
}

void* _memchr(RO void* src, u8 chr, u32 len)
{
    RO u8* p = src;

    while (len--) {
        if (*p == chr) { return (void*)p; }
        ++p;
    }

    return nullptr;
}

void* _memrchr(RO void* src, u8 chr, u32 len)
{
    RO u8* p = (RO u8*)src + len - 1;

    while (len--) {
        if (*p == chr) { return (void*)p; }
        --p;
    }

    return nullptr;
}
