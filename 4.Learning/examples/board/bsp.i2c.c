#include "bsp.i2c.h"

#include "bsp.gpio.h"

void I2CA_Init(void)
{
    EALLOW;
    // enable clock
    SysCtrlRegs.PCLKCR3.bit.GPIOINENCLK = 1;
    SysCtrlRegs.PCLKCR0.bit.I2CAENCLK   = 1;
    EDIS;

    {
        EALLOW;
        GpioCtrlRegs.GPBPUD.bit.GPIO32   = GPIO_PULL_UP;  // SDAA
        GpioCtrlRegs.GPBPUD.bit.GPIO33   = GPIO_PULL_UP;  // SCLA
        GpioCtrlRegs.GPBQSEL1.bit.GPIO32 = GPIO_QUAL_ASYNC;
        GpioCtrlRegs.GPBQSEL1.bit.GPIO33 = GPIO_QUAL_ASYNC;
        GpioCtrlRegs.GPBMUX1.bit.GPIO32  = GPIO_PIN_TYPE_PULLUP;
        GpioCtrlRegs.GPBMUX1.bit.GPIO33  = GPIO_PIN_TYPE_PULLUP;
        EDIS;
    }
    {
        I2caRegs.I2CSAR = 0x0000;      // Slave address - EEPROM control code

#if (CPU_FRQ_150MHZ)                   // Default - For 150MHz SYSCLKOUT
        I2caRegs.I2CPSC.all = 15 - 1;  // Prescaler - need 7-12 Mhz on module clk (150/15 = 10MHz)
#endif
#if (CPU_FRQ_100MHZ)                   // For 100 MHz SYSCLKOUT
        I2caRegs.I2CPSC.all = 10 - 1;  // Prescaler - need 7-12 Mhz on module clk (100/10 = 10MHz)
#endif

        // I2C_DUTYCYCLE_33
        I2caRegs.I2CCLKL = 10;          // NOTE: must be non zero
        I2caRegs.I2CCLKH = 5;           // NOTE: must be non zero

        I2caRegs.I2CIER.all = 0x24;     // Enable SCD & ARDY interrupts

        I2caRegs.I2CMDR.all = 0x0020;   // Take I2C out of reset
                                        // Stop I2C when suspended

        I2caRegs.I2CFFTX.all = 0x6000;  // Enable FIFO mode and TXFIFO
        I2caRegs.I2CFFRX.all = 0x2040;  // Enable RXFIFO, clear RXFFINT
    }
}

u16 I2CA_WriteMem(u16 dev, u16 reg, u16 dat)
{
    if (I2caRegs.I2CMDR.bit.STP)
    {
        return I2C_STP_NOT_READY_ERROR;
    }

    // Set slave address
    I2caRegs.I2CSAR = dev;

    if (I2caRegs.I2CSTR.bit.BB)
    {
        return I2C_BUS_BUSY_ERROR;
    }

    I2caRegs.I2CCNT = 2;

    // Setup data to send
    I2caRegs.I2CDXR = reg;
    I2caRegs.I2CDXR = dat;

    // Send start as master transmitter
    I2caRegs.I2CMDR.all = 0x6E20;

    return I2C_SUCCESS;
}
