#include "board.h"
#include "math.h"

f32 FIR(f32 *Xn, f32 *Hn, u16 cnt);

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
        f32 Hn[] = {
            0.0, 0.0, 0.001, -0.002, -0.002, 0.01, -0.009,
            -0.018, 0.049, -0.02, 0.11, 0.28, 0.64, 0.28,
            -0.11, -0.02, 0.049, -0.018, -0.009, 0.01,
            -0.002, -0.002, 0.001, 0.0, 0.0};

        f32 Xn[256 + ARRAY_SIZE(Hn)];
        f32 Yn = 0.0;

        // generate singal
        f32 a1 = 0.0, a2 = PI * 0.1;

        u16 i = 0;

        while (1)
        {
            if (KEY3_READ())
            {
                // right shift datas
                i = ARRAY_SIZE(Hn);
                while (--i) Xn[i] = Xn[i-1];

                // generate new data
                Xn[0] = sin(a1) + cos(a2) / 6.0;
                a1 += PI_X2 / 30;
                if (a1 >= PI_X2) a1 -= PI_X2;
                a2 += PI_X2 * 1.4;
                if (a2 >= PI_X2) a2 -= PI_X2;

                // do FIR filter
                Yn = FIR(Xn, Hn, ARRAY_SIZE(Hn));

                // display input and output
                usdk_println("%.2f,%.2f", Xn[0],Yn);
                DelayBlockUS(1);
            }
        }
    }

    /* User Code End */
}

f32 FIR(f32 *Xn, f32 *Hn, u16 cnt)
{
    u16 idx;
    f32 sum = 0;

    for (idx = 0; idx < cnt; ++idx)
        sum += (Xn[idx] * Hn[idx]);

    return sum;
}
