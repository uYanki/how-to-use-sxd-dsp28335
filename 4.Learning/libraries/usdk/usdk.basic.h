#ifndef __USDK_BASIC_H__
#define __USDK_BASIC_H__

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// Modifier
//---------------------------------------------------------------------------

#define RW        ///< read / write
#define RO const  ///< read only

#define _IN_      ///< input
#define _OUT_     ///< output
#define _INOUT_

#define fn_inline  static inline
#define fn_public  extern
#define fn_private static

#define REG        volatile

#define UNUSED(x)  ((void)(x))

//---------------------------------------------------------------------------
// Types
//---------------------------------------------------------------------------

typedef signed char      s8, int8_t;
typedef signed short     s16, int16_t;
typedef signed long      s32, int32_t;
typedef signed long long s64, int64_t;

typedef unsigned char      u8, uint8_t;
typedef unsigned short     u16, uint16_t;
typedef unsigned long      u32, uint32_t;
typedef unsigned long long u64, uint64_t;

typedef float  f32, float32_t;
typedef double f64, float64_t;
// typedef long double f64, float64_t;

//---------------------------------------------------------------------------

typedef unsigned char      BYTE;
typedef unsigned short     WORD;
typedef unsigned long      DWORD;
typedef unsigned long long QWORD;
typedef float              REAL;

//---------------------------------------------------------------------------

typedef REG u8*  REG8;
typedef REG u16* REG16;
typedef REG u32* REG32;
typedef REG u64* REG64;

//---------------------------------------------------------------------------
// Enums
//---------------------------------------------------------------------------

typedef enum {
    FALSE = 0U,
    TRUE  = !FALSE,
} bool_e;

typedef enum {
    RESET = 0U,
    SET   = !RESET,
} state_e;

typedef enum {
    DISABLE = 0U,
    ENABLE  = !DISABLE
} enable_e;

typedef enum {
    OFF = 0U,
    ON  = !OFF,
} switch_e;

typedef enum {
    FAILURE = 0U,
    SUCCESS = !FAILURE,
} result_e;

typedef enum {
    DIR_CCW = 0,         ///< Clockwise, 顺时针
    DIR_CW  = !DIR_CCW,  ///< Counterclockwise, 逆时针
} direction_e;

//---------------------------------------------------------------------------
// Constants
//---------------------------------------------------------------------------

#ifndef NULL
#define NULL 0
#endif

#ifndef nullptr
#define nullptr ((void*)0)
#endif

//---------------------------------------------------------------------------

#define S8_MIN                                     (s8)0x80                 ///< -128
#define S16_MIN                                    (s16)0x8000              ///< -32678
#define S32_MIN                                    (s32)0x80000000          ///< -2147483648
#define S64_MIN                                    (s64)0x8000000000000000  ///< -9223372036854775808

#define S8_MAX                                     (s8)0x7F                 ///< +127
#define S16_MAX                                    (s16)0x7FFF              ///< +32767
#define S32_MAX                                    (s32)0x7FFFFFFF          ///< +2147483647
#define S64_MAX                                    (s64)0x7FFFFFFFFFFFFFFF  ///< +9223372036854775807

#define U8_MAX                                     (u8)0xFF                 ///< 255
#define U16_MAX                                    (u16)0xFFFF              ///< 65535
#define U32_MAX                                    (u32)0xFFFFFFFF          ///< 4294967295
#define U64_MAX                                    (u64)0xFFFFFFFFFFFFFFFF  ///< 18446744073709551615

#define F32_MIN                                    1.17549435e-38f
#define F64_MIN                                    2.2250738585072014e-308

#define F32_MAX                                    3.40282347e+38f
#define F64_MAX                                    1.7976931348623157e+308

//---------------------------------------------------------------------------

#define PI                                         3.1415926f  ///< 圆周率 π = 3.14159265358979323846
#define PI_X2                                      6.2831852f  ///< 2π
#define PI_X100                                    314         ///< 100π

#define RAD2DGE                                    57.295779f  ///< 1 radians to 57.295780 degress
#define DEG2RAD                                    0.017453f   ///< 1 degress to  0.017453 radians

#define SIN15                                      0.258819f
#define SIN30                                      0.5f
#define SIN45                                      0.707106f  ///< sqrt(2)/2
#define SIN60                                      0.866025f  ///< sqrt(3)/2
#define SIN75                                      0.965925f

#define COS15                                      SIN75
#define COS30                                      SIN60
#define COS45                                      SIN45
#define COS60                                      SIN30
#define COS75                                      SIN15

//---------------------------------------------------------------------------

#define PHI                                        1.618033f  ///< 黄金比例 φ = (1 + sqrt(5)) / 2

#define SQRT2                                      1.414213f
#define SQRT3                                      1.732050f
#define SQRT5                                      2.236067f
#define INVSQRT2                                   0.707106f  ///< 1/sqrt(2)
#define INVSQRT3                                   0.577350f  ///< 1/sqrt(3)
#define INVSQRT5                                   0.447213f  ///< 1/sqrt(5)

//---------------------------------------------------------------------------
// Macros
//---------------------------------------------------------------------------

/**
 * @param lhs: left-hand side
 * @param rhs: right-hand side
 */
#define MIN(lhs, rhs)                              (((lhs) < (rhs)) ? (lhs) : (rhs))
#define MAX(lhs, rhs)                              (((lhs) > (rhs)) ? (lhs) : (rhs))

#define MIN3(a, b, c)                              (MIN(a, MIN(b, c)))
#define MAX3(a, b, c)                              (MAX(a, MAX(b, c)))

/**
 * @param lo: lowest allowable value
 * @param hi: highest allowable value
 */
#define CLAMP(val, lo, hi)                         (MAX(lo, MIN(val, hi)))
#define INOPEN(val, lo, hi)                        (((lo) < (val)) && ((val) < (hi)))    ///< check if the val is within the open range
#define INCLOSE(val, lo, hi)                       (((lo) <= (val)) && ((val) <= (hi)))  ///< check if the val is within the closed range

/**
 *              OutMax - OutMin
 *  outVal  = -------------------  x  ( inVal - inMin ) + outMin
 *               inMax - inMin
 */
#define MapTo(inVal, inMin, inMax, outMin, outMax) ((((outMax) - (outMin)) / (f32)((inMax) - (inMin))) * ((inVal) - (inMin)) + (outMin))

//---------------------------------------------------------------------------

///< val of elements in an array
#define ARRAY_SIZE(array)                          (sizeof(array) / sizeof(*(array)))
///< byte offset of member in structure (OFFSETOF)
#define MEMBER_OFFSET(structure, member)           ((u32) & (((structure*)0)->member))
///< size of a member of a structure
#define MEMBER_SIZE(structure, member)             (sizeof(((structure*)0)->member))

//---------------------------------------------------------------------------

/**
 * @brief swap integer variable
 * @note  when rhs and lhs are equal, the XOR result of rhs and lhs is 0.
 */
#define SWAP_INT(lhs, rhs)                            \
    do {                                              \
        if (lhs != rhs) { lhs ^= rhs ^= lhs ^= rhs; } \
    } while (0)

///< swap variable
#define SWAP_ANY(type, lhs, rhs) \
    do {                         \
        type tmp;                \
        tmp   = (lhs);           \
        (lhs) = (rhs);           \
        (rhs) = tmp;             \
    } while (0)

//---------------------------------------------------------------------------

#define RETURN_CASE(condition, greater, equal, less) \
    do {                                             \
        u8 caseval = (condition);                    \
        if (caseval > 0) return (greater);           \
        if (caseval < 0) return (less);              \
        return (equal);                              \
    } while (0)

//---------------------------------------------------------------------------
// Functions
//---------------------------------------------------------------------------

// #define _round(x) ((x) >= 0 ? (s32)((x) + 0.5) : (s32)((x)-0.5))   ///< 四舍五入
// #define _floor(x) ((x) >= 0 ? (s32)(x) : (s32)((x)-1))             ///< 向下取整
// #define _ceil(x)  ((x) >= 0 ? (s32)((x) + 0.99999999) : (s32)(x))  ///< 向上取整

fn_inline f32 _floor(f32 x) { return (f32)((s32)x - (x < 0.0 && x != (s32)x)); }
fn_inline f32 _ceil(f32 x) { return (f32)((s32)x + (x > 0.0 && x != (s32)x)); }
fn_inline f32 _round(f32 x) { return (x >= 0.0) ? _floor(x + 0.5) : _ceil(x - 0.5); }

#ifdef __cplusplus
}
#endif

#endif
