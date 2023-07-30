#ifndef __BSP_GPIO_H__
#define __BSP_GPIO_H__

#include "common.h"

/**
 * GpioCtrlRegs
 *    .GPGMUX          Defines pin-muxing selection
 *    .GPCR            Configuration lock commit bit
 *    .GPLOCK          Configuration Lock bit
 *    .GPINV           Input inversion control
 *    .GPAMSEL         Analog Mode select
 *    .GPCSEL          Master CPU Select
 *    .GPQSEL          Select input qualification type
 *    .GPPUD           Pull-Up Disable control
 *    .GPODR           Outpout Open-Drain control
 *    .GPDIR           Defines direction
 *    .GPMUX           Defines pin-muxing selection
 *    .GPCTRL          GPIO Qualification Sampling Period Control
 *       .QUALPRD      Qualification sampling period
 *
 * GpioDataRegs
 *    .GPDAT           Data Register
 *    .GPSET           Output Set bit
 *    .GPCLEAR         Output Clear bit
 *    .GPTOGGLE        Output Toggle bit
 *
 */

// ---------------------------
// GPIO_PinType
// ---------------------------
#define GPIO_PIN_TYPE_STD          0x0000U  //!< Push-pull output or floating input
#define GPIO_PIN_TYPE_PULLUP       0x0001U  //!< Pull-up enable for input
#define GPIO_PIN_TYPE_INVERT       0x0002U  //!< Invert polarity on input
#define GPIO_PIN_TYPE_OD           0x0004U  //!< Open-drain on output

// ---------------------------
// GPIO_PullMode
// ---------------------------
#define GPIO_PULL_UP               0
#define GPIO_PULL_DOWN             1

// ---------------------------
// GPIO_Direction
// ---------------------------
#define GPIO_DIR_MODE_IN           0  //!< Pin is a GPIO input
#define GPIO_DIR_MODE_OUT          1  //!< Pin is a GPIO output

// ---------------------------
// GPIO_QualificationMode
// ---------------------------
#define GPIO_QUAL_SYNC             0  //!< Synchronization to SYSCLK
#define GPIO_QUAL_3SAMPLE          1  //!< Qualified with 3 samples
#define GPIO_QUAL_6SAMPLE          2  //!< Qualified with 6 samples
#define GPIO_QUAL_ASYNC            3  //!< No synchronization

// ---------------------------
// GPIO_ExternalIntNum
// ---------------------------
#define GPIO_INT_XINT1             0  //!< External Interrupt 1
#define GPIO_INT_XINT2             1  //!< External Interrupt 2
#define GPIO_INT_XINT3             2  //!< External Interrupt 3
#define GPIO_INT_XINT4             3  //!< External Interrupt 4
#define GPIO_INT_XINT5             4  //!< External Interrupt 5
#define GPIO_INT_XINT6             5  //!< External Interrupt 6
#define GPIO_INT_XINT7             6  //!< External Interrupt 7
#define GPIO_INT_XINT8             7  //!< External Interrupt 8

//----------------------------
// GPIO_IntType
// ---------------------------
#define GPIO_INT_TYPE_FALLING_EDGE 0  //!< Interrupt on falling edge
#define GPIO_INT_TYPE_RISING_EDGE  1  //!< Interrupt on rising edge
// #define GPIO_INT_TYPE_FALLING_EDGE 2  //!< Interrupt on falling edge
#define GPIO_INT_TYPE_BOTH_EDGES   3  //!< Interrupt on both edges

// -------------------------------------------------------------------------

#if CONFIG_USING_GPIO_LED

// Green Led

#  define LED_OFF()        (GpioDataRegs.GPASET.bit.GPIO0 = 1)     // gpio.set
#  define LED_ON()         (GpioDataRegs.GPACLEAR.bit.GPIO0 = 1)   // gpio.clear
#  define LED_TOGGLE()     (GpioDataRegs.GPATOGGLE.bit.GPIO0 = 1)  // gpio.toggle
#  define LED_WRITE(state) (GpioDataRegs.GPADAT.bit.GPIO0 = (state) ? 1 : 0)

#endif  // CONFIG_USING_GPIO_LED

#if CONFIG_USING_GPIO_BEEP

#  define BEEP_ON()         (GpioDataRegs.GPBCLEAR.bit.GPIO53 = 1)
#  define BEEP_OFF()        (GpioDataRegs.GPBSET.bit.GPIO53 = 1)
#  define BEEP_TOGGLE()     (GpioDataRegs.GPBTOGGLE.bit.GPIO53 = 1)
#  define BEEP_WRITE(state) (GpioDataRegs.GPBDAT.bit.GPIO53 = (state) ? 1 : 0)

#endif  // CONFIG_USING_GPIO_BEEP

#if CONFIG_USING_GPIO_KEY

#  define KEY3_READ() (GpioDataRegs.GPADAT.bit.GPIO13 == 0)
#  define KEY4_READ() (GpioDataRegs.GPBDAT.bit.GPIO60 == 0)
#  define KEY5_READ() (GpioDataRegs.GPBDAT.bit.GPIO61 == 0)

#endif  // CONFIG_USING_GPIO_KEY

#if CONFIG_USING_GPIO_STEPPER

#  define STEPPER_GEAR_RATIO       64     // 减速比
#  define STEPPER_STEP_ANGLE       5.625  // 步距角度 360°/STEPPER_GEAR_RATIO

///< 28BYJ-48
#  define STEPPER_IN1_WRITE(state) (GpioDataRegs.GPADAT.bit.GPIO2 = (state) ? 1 : 0)
#  define STEPPER_IN2_WRITE(state) (GpioDataRegs.GPADAT.bit.GPIO3 = (state) ? 1 : 0)
#  define STEPPER_IN3_WRITE(state) (GpioDataRegs.GPADAT.bit.GPIO4 = (state) ? 1 : 0)
#  define STEPPER_IN4_WRITE(state) (GpioDataRegs.GPADAT.bit.GPIO5 = (state) ? 1 : 0)

#  define STEPPER_WRITE(state)     WriteBits32(GpioDataRegs.GPADAT.all, (state) &0xF, 2, 4);

void steeper_rotate(u32 angle, direction_e dir);

#endif  // CONFIG_USING_GPIO_STEPPER_MOTOR

#if CONFIG_USING_GPIO_DCMOTOR

#  define DCMOTOR_IN1_WRITE(state) (GpioDataRegs.GPADAT.bit.GPIO0 = (state) ? 1 : 0)
#  define DCMOTOR_IN2_WRITE(state) (GpioDataRegs.GPADAT.bit.GPIO1 = (state) ? 1 : 0)

#endif  // CONFIG_USING_GPIO_DCMOTOR

void GPIO_Init(void);

// -------------------------------------------------------------------------

void EXIT_Init(void);

interrupt void EXTI1_IRQn(void);
interrupt void EXTI2_IRQn(void);
interrupt void EXTI3_IRQn(void);
interrupt void EXTI4_IRQn(void);

#endif  // __BSP_GPIO_H__
