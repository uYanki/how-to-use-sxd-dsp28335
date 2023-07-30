#ifndef __TIM_H__
#define __TIM_H__

#include "common.h"

/**
* CPUTIMER
*   TIM              Counter
*   PRD              Period 
*   TCR              Control Register
*       .TSS         Stop status bit
*       .TRB         Timer reload
*       .SOFT        Emulation modes
*       .FREE        Emulation modes
*       .TIE         Interrupt Enable
*       .TIF         Interrupt Flag
*   TPR              Prescale Low
*       .TDDR        Divide-Down
*       .PSC         Prescale Counter
*   TPRH             Prescale High
*       .TDDRH       Divide-Down
*       .PSCH        Prescale Counter
*/

// -------------------------------------------------------------------------

typedef enum {
    //! Denotes that the timer will stop after the next decrement
    CPUTIMER_EMULATIONMODE_STOPAFTERNEXTDECREMENT = 0x0000,
    //! Denotes that the timer will stop when it reaches zero
    CPUTIMER_EMULATIONMODE_STOPATZERO             = 0x0400,
    //! Denotes that the timer will run free
    CPUTIMER_EMULATIONMODE_RUNFREE                = 0x0800
} CPUTimer_EmulationMode;

typedef enum {
    //! System Clock Source
    CPUTIMER_CLOCK_SOURCE_SYS     = 0x0,
    //! Internal Oscillator 1 Clock Source
    CPUTIMER_CLOCK_SOURCE_INTOSC1 = 0x1,
    //! Internal Oscillator 2 Clock Source
    CPUTIMER_CLOCK_SOURCE_INTOSC2 = 0x2,
    //! External Clock Source
    CPUTIMER_CLOCK_SOURCE_XTAL    = 0x3,
    //! Auxiliary PLL Clock Source
    CPUTIMER_CLOCK_SOURCE_AUX     = 0x6
} CPUTimer_ClockSource;

typedef enum {
    CPUTIMER_CLOCK_PRESCALER_1  = 0,  //!< Prescaler value of / 1
    CPUTIMER_CLOCK_PRESCALER_2  = 1,  //!< Prescaler value of / 2
    CPUTIMER_CLOCK_PRESCALER_4  = 2,  //!< Prescaler value of / 4
    CPUTIMER_CLOCK_PRESCALER_8  = 3,  //!< Prescaler value of / 8
    CPUTIMER_CLOCK_PRESCALER_16 = 4   //!< Prescaler value of / 16
} CPUTimer_Prescaler;

// -------------------------------------------------------------------------

// TIMX = CpuTimer?Regs
#define TIM_Run(TIMx)  (TIMx.TCR.bit.TSS = 0)
#define TIM_Stop(TIMx) (TIMx.TCR.bit.TSS = 1)

/**
 * @brief 
 * 
 * @param freq CPU frequency, unit: MHZ
 * @param period TIMER Period, unit: us
 * 
 * @example TIMx_Init(150, 1e3) => T = 1ms
 * @example TIMx_Init(150, 1e6) => T = 1s
 */
void TIM0_Init(f32 freq, f32 period);
void TIM1_Init(f32 freq, f32 period);
void TIM2_Init(f32 freq, f32 period);

interrupt void TIM0_IRQn(void);
interrupt void TIM1_IRQn(void);
interrupt void TIM2_IRQn(void);

#endif  //! __TIM_H__
