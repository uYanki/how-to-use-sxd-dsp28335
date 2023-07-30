#include "board.h"
#include "math.h"

// 在线卷积计算: https://www.rapidtables.org/zh-CN/calc/math/convolution-calculator.html

/**
 * @brief 离散线性卷积（原理: 对位相乘求和法实现卷积）
 * 
 * @param [in]  xn : inputs 
 * @param [in]  hn : coeffs 
 * @param [in]  x : inputs
 * @param [in]  h : coeffs
 * @param [out] y : outputs
 * 
 *       @note outputs length = (inputs length) + (coeffs length) - 1 => yn=xn+hn-1
 */
void LinearConvolution(u16 xn, u16 hn, u16 *x, u16 *h, u16 *y)
{
    u16 i, j, k, l;
    u16 yn = xn + hn - 1;

    i = yn;
    while (i--) { y[i] = 0; }  // fill zero

    k = yn - 1, i = hn;
    while (--i)
    {
        l = k--;
        j = xn;
        while (--j) { y[l--] += h[i] * x[j]; }

        y[l] += x[0] * h[i];
    }

    l = k, i = xn;
    while (--i) { y[l--] += h[0] * x[i]; }

    y[l] += x[0] * h[0];
}

void main(void)
{
    InitSysCtrl();

    InitPieCtrl();
    IER = 0x0000;
    IFR = 0x0000;
    InitPieVectTable();

    /* User Code Begin */

    GPIO_Init();
    SCIB_Init();
    {
        u16 x[] = {3, 2, 1};
        u16 h[] = {4, 3, 2, 1};
        u16 y[ARRAY_SIZE(x) + ARRAY_SIZE(h) - 1];

        LinearConvolution(ARRAY_SIZE(x), ARRAY_SIZE(h), x, h, y);

        while (1)
        {
            if (KEY3_READ())
            {
                DEBUG_PRINT_ARRAY("in1:", " %d", x, ARRAY_SIZE(x));
                DEBUG_PRINT_ARRAY("in2:", " %d", h, ARRAY_SIZE(h));
                DEBUG_PRINT_ARRAY("out:", " %d", y, ARRAY_SIZE(y));
                DelayBlockS(2);
            }
        }
    }

    /* User Code End */
}
