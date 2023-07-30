#include "board.h"

#if 1

// key led beep

void main()
{
    InitSysCtrl();

    /* User Code Begin */

    GPIO_Init();
    while (1) {
        LED_WRITE(!KEY3_READ());
        BEEP_WRITE(!KEY4_READ());
        // FirewareDelay(1);
    }

    /* User Code End */
}

#else

// key stepper

void main()
{
    direction_e dir;

    InitSysCtrl();

    /* User Code Begin */

    GPIO_Init();

    while (1) {
        dir = KEY5_READ() ? DIR_CW : DIR_CCW;

        if (KEY3_READ()) {
            steeper_rotate(_ceil(STEPPER_STEP_ANGLE), dir);
        } else if (KEY4_READ()) {
            steeper_rotate(360, dir);
        }
    }

    /* User Code End */
}

#endif
