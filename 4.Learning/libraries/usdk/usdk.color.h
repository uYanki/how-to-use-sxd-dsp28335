#ifndef __USDK_COLOR_H__
#define __USDK_COLOR_H__

#include "usdk.basic.h"

//---------------------------------------------------------------------------
// Structure
//---------------------------------------------------------------------------

typedef struct {
    union {
        u32 v;
        struct {
            u8 a;  ///< alpha: 0(fully transparent)~128(translucent)~255(opaque)
            u8 r;  ///< red value
            u8 g;  ///< green value
            u8 b;  ///< blue value
        };
    };
} ARGB_t, RGB_t;

typedef struct {
    union {
        u32 v;
        struct {
            u8 a;
            u8 b;
            u8 g;
            u8 r;
        };
    };
} ABGR_t, BGR_t;

typedef struct {
    f32 h;  //|< hue 色相 0(RED)~120(GREEN)~240(BLUE)~360(RED)
    f32 s;  //|< saturation 饱和度: 0(colorless)~1(colorful)
    f32 v;  //|< value  明度 0(BLACK)~1(WHITE)
} HSV_t;

//---------------------------------------------------------------------------
// Constants
//---------------------------------------------------------------------------

/**
 * @brief RGB colors
 * @note Recommend installing the vscode extension `Color Highlight` to view colors
 */

#define RGBCR_RED                0xFF0000  ///< 红色
#define RGBCR_GREEN              0x00FF00  ///< 绿色
#define RGBCR_BLUE               0x0000FF  ///< 蓝色
#define RGBCR_YELLOW             0xFFFF00  ///< 黄色
#define RGBCR_PURPLE             0x800080  ///< 紫色
#define RGBCR_ORANGE             0xFFA500  ///< 橙色
#define RGBCR_PINK               0xFFC0CB  ///< 粉色
#define RGBCR_BROWN              0xA52A2A  ///< 棕色
#define RGBCR_GRAY               0x808080  ///< 灰色
#define RGBCR_BLACK              0x000000  ///< 黑色
#define RGBCR_WHITE              0xFFFFFF  ///< 白色
#define RGBCR_SILVER             0xC0C0C0  ///< 银色
#define RGBCR_GOLD               0xFFD700  ///< 金色
#define RGBCR_NAVY               0x000080  ///< 海军蓝
#define RGBCR_TEAL               0x008080  ///< 鸭绿色
#define RGBCR_OLIVE              0x808000  ///< 橄榄色
#define RGBCR_MAROON             0x800000  ///< 栗色
#define RGBCR_FUCHSIA            0xFF00FF  ///< 紫红色
#define RGBCR_CYAN               0x00FFFF  ///< 青色
#define RGBCR_CORAL              0xFF7F50  ///< 珊瑚色
#define RGBCR_SKY_BLUE           0x87CEEB  ///< 天蓝色
#define RGBCR_TURQUOISE          0x40E0D0  ///< 绿松石色
#define RGBCR_INDIGO             0x4B0082  ///< 靛蓝色
#define RGBCR_VIOLET             0xEE82EE  ///< 紫罗兰色
#define RGBCR_BEIGE              0xF5F5DC  ///< 米色
#define RGBCR_KHAKI              0xF0E68C  ///< 卡其色
#define RGBCR_SALMON             0xFA8072  ///< 鲑鱼色
#define RGBCR_TOMATO             0xFF6347  ///< 番茄红
#define RGBCR_ORCHID             0xDA70D6  ///< 紫兰色
#define RGBCR_LIGHT_GRAY         0xD3D3D3  ///< 浅灰色
#define RGBCR_LIGHT_CORAL        0xF08080  ///< 浅珊瑚色
#define RGBCR_LIGHT_SEA_GREEN    0x20B2AA  ///< 浅海洋绿
#define RGBCR_LIGHT_BLUE         0xADD8E6  ///< 淡蓝色
#define RGBCR_LIGHT_GREEN        0x90EE90  ///< 淡绿色
#define RGBCR_LIGHT_YELLOW       0xFFFFE0  ///< 浅黄色
#define RGBCR_LIGHT_PINK         0xFFB6C1  ///< 浅粉色
#define RGBCR_DARK_GREEN         0x006400  ///< 暗绿色
#define RGBCR_DARK_BLUE          0x00008B  ///< 暗蓝色
#define RGBCR_DARK_RED           0x8B0000  ///< 暗红色
#define RGBCR_DARK_CYAN          0x008B8B  ///< 暗青色
#define RGBCR_DARK_MAGENTA       0x8B008B  ///< 暗洋红色
#define RGBCR_DARK_ORANGE        0xFF8C00  ///< 暗橙色
#define RGBCR_DARK_VIOLET        0x9400D3  ///< 暗紫罗兰色
#define RGBCR_DARK_GOLDENROD     0xB8860B  ///< 暗金黄色
#define RGBCR_DARK_KHAKI         0xBDB76B  ///< 暗卡其色
#define RGBCR_DARK_OLIVE_GREEN   0x556B2F  ///< 暗橄榄绿色
#define RGBCR_DARK_SEA_GREEN     0x8FBC8F  ///< 暗海绿色
#define RGBCR_DARK_SLATE_BLUE    0x483D8B  ///< 暗灰蓝色
#define RGBCR_DARK_TURQUOISE     0x00CED1  ///< 暗绿宝石色
#define RGBCR_DARK_SALMON        0xE9967A  ///< 暗肉色
#define RGBCR_DARK_GRAY          0xA9A9A9  ///< 暗灰色
#define RGBCR_DEEP_SKY_BLUE      0x00BFFF  ///< 深天蓝色
#define RGBCR_FIRE_BRICK         0xB22222  ///< 火砖色
#define RGBCR_FOREST_GREEN       0x228B22  ///< 森林绿
#define RGBCR_GAINSBORO          0xDCDCDC  ///< 淡灰色
#define RGBCR_INDIAN_RED         0xCD5C5C  ///< 印第安红
#define RGBCR_DIM_GRAY           0x696969  ///< 暗灰色
#define RGBCR_MEDIUM_BLUE        0x0000CD  ///< 中蓝色
#define RGBCR_CRIMSON            0xDC143C  ///< 深红色
#define RGBCR_PALE_GREEN         0x98FB98  ///< 苍绿色
#define RGBCR_SEA_GREEN          0x2E8B57  ///< 海绿色
#define RGBCR_STEEL_BLUE         0x4682B4  ///< 钢蓝色
#define RGBCR_ROSY_BROWN         0xBC8F8F  ///< 玫瑰棕色
#define RGBCR_AQUAMARINE         0x7FFFD4  ///< 绿色宝石
#define RGBCR_BLUE_VIOLET        0x8A2BE2  ///< 蓝紫色
#define RGBCR_CHOCOLATE          0xD2691E  ///< 巧克力色

//---------------------------------------------------------------------------
// Marcos
//---------------------------------------------------------------------------

#define MAKE_ARGB(s, A, R, G, B) (s.a = A, s.r = R, s.g = G, s.b = B, s)
#define MAKE_RGB(s, R, G, B)     MAKE_ARGB(s, 0xFF, R, G, B)
#define MAKE_ABGR(s, A, B, G, R) MAKE_ARGB(s, A, R, G, B)
#define MAKE_BGR(s, B, G, R)     MAKE_ABGR(s, 0xFF, B, G, R)

#define RGB(r, g, b)             ((0xFF & (r)) << 16 | (0xFF & (g)) << 8 | (0xFF & (b)))
#define BGR(b, g, r)             ((0xFF & (b)) << 16 | (0xFF & (g)) << 8 | (0xFF & (r)))

#define RGB2BGR(rgb)             (((0xFF0000 & (rgb)) >> 16) | (0x00FF00 & (rgb)) | ((0x0000FF & (rgb)) << 16))
#define BGR2RGB(bgr)             (((0xFF0000 & (bgr)) >> 16) | (0x00FF00 & (bgr)) | ((0x0000FF & (bgr)) << 16))

#define RGB_GetR(rgb)            (0xFF & ((rgb) >> 16))
#define RGB_GetG(rgb)            (0xFF & ((rgb) >> 8))
#define RGB_GetB(rgb)            (0xFF & ((rgb) >> 0))

#define BGR_GetB(bgr)            (0xFF & ((bgr) >> 16))
#define BGR_GetG(bgr)            (0xFF & ((bgr) >> 8))
#define BGR_GetR(bgr)            (0xFF & ((bgr) >> 0))

//---------------------------------------------------------------------------
// Functions
//---------------------------------------------------------------------------

void RGB2HSV(u8 r, u8 g, u8 b, f32* h, f32* s, f32* v);

#endif