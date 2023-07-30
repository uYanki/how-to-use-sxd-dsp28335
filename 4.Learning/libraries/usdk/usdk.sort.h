#ifndef __USDK_SORT_H__
#define __USDK_SORT_H__

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "usdk.basic.h"

//---------------------------------------------------------------------------
// Types
//---------------------------------------------------------------------------

typedef s32 (*sort_cmp_t)(RO void*, RO void*);

//---------------------------------------------------------------------------
// Function
//---------------------------------------------------------------------------

///< swap elements when function ('cmp') return value is greater than 0
void _bsort(void* array, u32 count, u32 size, sort_cmp_t cmp);
void _qsort(void* array, u32 count, u32 size, sort_cmp_t cmp);

#ifdef __cplusplus
}
#endif

#endif
