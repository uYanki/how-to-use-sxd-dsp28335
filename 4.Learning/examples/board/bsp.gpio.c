#include "bsp.gpio.h"

#include "bsp.delay.h"
#include "lib.lcd1602.h"

static void GPIO_LED_Init(void);
static void GPIO_BEEP_Init(void);
static void GPIO_KEY_Init(void);
static void GPIO_STEPPER_Init(void);
static void GPIO_DCMOTOR_Init(void);

void GPIO_Init(void)
{
    EALLOW;
    // enable gpio clock
    SysCtrlRegs.PCLKCR3.bit.GPIOINENCLK = 1;
    EDIS;

    GPIO_LED_Init();
    GPIO_BEEP_Init();
    GPIO_KEY_Init();
    GPIO_STEPPER_Init();
    GPIO_DCMOTOR_Init();
}

static void GPIO_LED_Init(void)
{
#if CONFIG_USING_GPIO_LED

    EALLOW;

    // config gpio
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = GPIO_PIN_TYPE_STD;
    GpioCtrlRegs.GPADIR.bit.GPIO0  = GPIO_DIR_MODE_OUT;
    GpioCtrlRegs.GPAPUD.bit.GPIO0  = GPIO_PULL_UP;

    EDIS;

    // set output level as high
    GpioDataRegs.GPASET.bit.GPIO0 = 1;

#endif
}

static void GPIO_BEEP_Init(void)
{
#if CONFIG_USING_GPIO_BEEP

    EALLOW;

    GpioCtrlRegs.GPBMUX2.bit.GPIO53 = GPIO_PIN_TYPE_STD;
    GpioCtrlRegs.GPBDIR.bit.GPIO53  = GPIO_DIR_MODE_OUT;

    EDIS;

    // set output level as high
    GpioDataRegs.GPBSET.bit.GPIO53 = 1;

#endif
}

static void GPIO_KEY_Init(void)
{
#if CONFIG_USING_GPIO_KEY

    EALLOW;

    GpioCtrlRegs.GPAMUX1.bit.GPIO13 = GPIO_PIN_TYPE_STD;
    GpioCtrlRegs.GPADIR.bit.GPIO13  = GPIO_DIR_MODE_IN;
    GpioCtrlRegs.GPAPUD.bit.GPIO13  = GPIO_PULL_UP;

    GpioCtrlRegs.GPBMUX2.bit.GPIO60 = GPIO_PIN_TYPE_STD;
    GpioCtrlRegs.GPBDIR.bit.GPIO60  = GPIO_DIR_MODE_IN;
    GpioCtrlRegs.GPBPUD.bit.GPIO60  = GPIO_PULL_UP;

    GpioCtrlRegs.GPBMUX2.bit.GPIO61 = GPIO_PIN_TYPE_STD;
    GpioCtrlRegs.GPBDIR.bit.GPIO61  = GPIO_DIR_MODE_IN;
    GpioCtrlRegs.GPBPUD.bit.GPIO61  = GPIO_PULL_UP;

    EDIS;

#endif
}

static void GPIO_STEPPER_Init(void)
{
#if CONFIG_USING_GPIO_STEPPER

    EALLOW;

    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = GPIO_PIN_TYPE_STD;
    GpioCtrlRegs.GPADIR.bit.GPIO2  = GPIO_DIR_MODE_OUT;

    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = GPIO_PIN_TYPE_STD;
    GpioCtrlRegs.GPADIR.bit.GPIO3  = GPIO_DIR_MODE_OUT;

    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = GPIO_PIN_TYPE_STD;
    GpioCtrlRegs.GPADIR.bit.GPIO4  = GPIO_DIR_MODE_OUT;

    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = GPIO_PIN_TYPE_STD;
    GpioCtrlRegs.GPADIR.bit.GPIO5  = GPIO_DIR_MODE_OUT;

    EDIS;

    GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;
    GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;
    GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;
    GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;

#endif
}

static void GPIO_DCMOTOR_Init(void)
{
#if CONFIG_USING_GPIO_DCMOTOR

    EALLOW;

    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = GPIO_PIN_TYPE_STD;
    GpioCtrlRegs.GPADIR.bit.GPIO0  = GPIO_DIR_MODE_OUT;
    GpioCtrlRegs.GPAPUD.bit.GPIO0  = GPIO_PULL_UP;

    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = GPIO_PIN_TYPE_STD;
    GpioCtrlRegs.GPADIR.bit.GPIO1  = GPIO_DIR_MODE_OUT;
    GpioCtrlRegs.GPAPUD.bit.GPIO1  = GPIO_PULL_UP;

    EDIS;

    GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;
    GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;

#endif
}

//

#if CONFIG_USING_GPIO_STEPPER

void stepper_docycle(u32 cycle, direction_e dir)
{
    static u8 CCW[] = {0b1110, 0b1100, 0b1101, 0b1001, 0b1011, 0b0011, 0b0111, 0b0110};
    static u8 CW[]  = {0b0110, 0b0111, 0b0011, 0b1011, 0b1001, 0b1101, 0b1100, 0b1110};

    u8 *arr = dir ? CCW : CW;
    u8  i, j;

    while (cycle--)
    {
        for (j = 0; j < 8; ++j)
        {
            for (i = 0; i < 8; ++i)
            {
                STEPPER_WRITE(arr[i]);
                DelayBlockMS(1);  // minimum response time
            }
        }
    }

    STEPPER_WRITE(1);
}

/**
 * @param angle: relative angle。 该值必须为 STEPPER_STEP_ANGLE 的整数倍，并向上取整。
 */
void steeper_rotate(u32 angle, direction_e dir)
{
    if (angle == 0) { return; }
    stepper_docycle(angle * STEPPER_GEAR_RATIO / 360.f, dir);
}

#endif  // CONFIG_USING_GPIO_STEPPER

//

static void EXIT_KEY_Init(void);

void EXIT_Init(void)
{
    EXIT_KEY_Init();

    EINT;  // enable global interrupt
}

static void EXIT_KEY_Init(void)
{
    EALLOW;

    /**
     * @note:
     *
     *  首先选择 GPIOx 作为 XINTx 的输入口, 然后配置 PIE 某组上中断向量, 最后使能 XINTx 所在的中断组对应的中断线
     *
     *  // GPIO0~31 <-> XINT1~2,  GPIO32~64 <->XINT3~7
     *
     *  在触发 GROUPx 的 PIE 中断后，需往 PIEACKx 对应位写1, 否则中断将无法进入 CPU 中断。
     *  eg1: PieCtrlRegs.PIEACK.bit.ACK1 = 1;
     *  eg2: PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
     *
     */

#if CONFIG_USING_EXIT_KEY3 == 1  ///< INT1.4 (XINT1)

    // synchronize XINT1(外部中断1) with SYSCLKOUT(系统时钟)
    GpioCtrlRegs.GPAQSEL1.bit.GPIO13     = GPIO_QUAL_SYNC;  // No Qualifier
    // select GPIO13 as XINT1 input
    GpioIntRegs.GPIOXINT1SEL.bit.GPIOSEL = 13;

    // re-map IRQ
    PieVectTable.XINT1            = &EXTI1_IRQn;
    // enable PIE GROUP1.INT4
    PieCtrlRegs.PIEIER1.bit.INTx4 = 1;

    // trigger mode: falling edge
    XIntruptRegs.XINT1CR.bit.POLARITY = GPIO_INT_TYPE_FALLING_EDGE;
    // enable XINT1
    XIntruptRegs.XINT1CR.bit.ENABLE   = 1;

    IER |= M_INT1;                 // enable CPU interrupt : INT1

#elif CONFIG_USING_EXIT_KEY3 == 2  ///< INT1.5 (XINT2)

#  if 1
    // 使用6次采样的采样窗(为了消除输入引脚噪声所用)
    GpioCtrlRegs.GPAQSEL1.bit.GPIO13  = GPIO_QUAL_6SAMPLE;
    // 采样周期=510*系统时钟周期
    // 采样窗时间=采样周期*(6-1)
    GpioCtrlRegs.GPACTRL.bit.QUALPRD1 = 0xFF;
#  else
    GpioCtrlRegs.GPAQSEL1.bit.GPIO13 = 0;
#  endif

    GpioIntRegs.GPIOXINT2SEL.bit.GPIOSEL = 13;

    PieVectTable.XINT2            = &EXTI2_IRQn;
    PieCtrlRegs.PIEIER1.bit.INTx5 = 1;

    XIntruptRegs.XINT2CR.bit.POLARITY = GPIO_INT_TYPE_FALLING_EDGE;
    XIntruptRegs.XINT2CR.bit.ENABLE   = 1;

    IER |= M_INT1;  // enable CPU interrupt : INT1 (GROUP)

#endif

#if CONFIG_USING_EXIT_KEY4  ///< INT12.1 (XINT3)

    // synchronize XINT3 with SYSCLKOUT
    GpioCtrlRegs.GPBQSEL2.bit.GPIO60     = GPIO_QUAL_SYNC;  // No Qualifier
    // select GPIO60 as XINT3 input
    GpioIntRegs.GPIOXINT3SEL.bit.GPIOSEL = 60;

    // re-map IRQ
    PieVectTable.XINT3             = &EXTI3_IRQn;
    // enable PIE GROUP12.INT3
    PieCtrlRegs.PIEIER12.bit.INTx1 = 1;

    XIntruptRegs.XINT3CR.bit.POLARITY = GPIO_INT_TYPE_FALLING_EDGE;
    XIntruptRegs.XINT3CR.bit.ENABLE   = 1;

    // enable CPU interrupt : INT12
    IER |= M_INT12;

#endif

#if CONFIG_USING_EXIT_KEY5  ///< INT12.2 (XINT4)

    GpioCtrlRegs.GPBQSEL2.bit.GPIO61     = GPIO_QUAL_SYNC;
    GpioIntRegs.GPIOXINT4SEL.bit.GPIOSEL = 61;

    // GROUP12.INT4
    PieVectTable.XINT4             = &EXTI4_IRQn;
    PieCtrlRegs.PIEIER12.bit.INTx2 = 1;

    XIntruptRegs.XINT4CR.bit.POLARITY = GPIO_INT_TYPE_FALLING_EDGE;
    XIntruptRegs.XINT4CR.bit.ENABLE   = 1;

    IER |= M_INT12;

#endif

    EDIS;
}

#if CONFIG_USING_EXIT_DEMO_IRQ

#  if (CONFIG_USING_EXIT_KEY3 == 1)

interrupt void EXTI1_IRQn(void)
{
    while (KEY3_READ()) {}  // wait for release
    LED_TOGGLE();
    PieCtrlRegs.PIEACK.bit.ACK1 = 1;
}

#  elif (CONFIG_USING_EXIT_KEY3 == 2)

interrupt void EXTI2_IRQn(void)
{
    while (KEY3_READ()) {}
    LED_TOGGLE();
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

#  endif

#  if CONFIG_USING_EXIT_KEY4

interrupt void EXTI3_IRQn(void)
{
    while (KEY4_READ()) {}
    LED_TOGGLE();
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;
}

#  endif

#  if CONFIG_USING_EXIT_KEY5

interrupt void EXTI4_IRQn(void)
{
    while (KEY5_READ()) {}
    LED_TOGGLE();
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;
}

#  endif

#endif
