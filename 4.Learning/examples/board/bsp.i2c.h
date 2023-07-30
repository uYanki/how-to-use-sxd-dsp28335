#ifndef __BSP_I2C_H__
#define __BSP_I2C_H__

#include "common.h"

/**
* OAR            I2C Own address
*  .OAR          I2C Own address
* IER            I2C Interrupt Enable
*  .ARBL         Arbitration-lost interrupt enable
*  .NACK         No-acknowledgment interrupt enable
*  .ARDY         Register-access-ready interrupt enable
*  .RRDY         Receive-data-ready interrupt enable
*  .XRDY         Transmit-data-ready interrupt enable
*  .SCD          Stop condition detected interrupt enable
*  .AAS          Addressed as slave interrupt enable
* STR            I2C Status
*  .ARBL         Arbitration-lost interrupt flag bit
*  .NACK         No-acknowledgment interrupt flag bit.
*  .ARDY         Register-access-ready interrupt flag bit
*  .RRDY         Receive-data-ready interrupt flag bit.
*  .XRDY         Transmit-data-ready interrupt flag bit.
*  .SCD          Stop condition detected bit.
*  .BYTESENT     Byte transmit over indication
*  .AD0          Address 0 bits
*  .AAS          Addressed-as-slave bit
*  .XSMT         Transmit shift register empty bit.
*  .RSFULL       Receive shift register full bit.
*  .BB           Bus busy bit.
*  .NACKSNT      NACK sent bit.
*  .SDIR         Slave direction bit
* CLKL           I2C Clock low-time divider
* CLKH           I2C Clock high-time divider
* CNT            I2C Data count
* DRR            I2C Data receive
*  .DATA         Receive data
* SAR            I2C Slave address
*  .SAR          Slave Address
* DXR            I2C Data Transmit
*  .DATA         Transmit data
* MDR            I2C Mode
*  .BC           Bit count bits.
*  .FDF          Free Data Format
*  .STB          START Byte Mode
*  .IRS          I2C Module Reset
*  .DLB          Digital Loopback Mode
*  .RM           Repeat Mode
*  .XA           Expanded Address Mode
*  .TRX          Transmitter Mode
*  .MST          Master Mode
*  .STP          STOP Condition
*  .STT          START condition bit
*  .FREE         Debug Action
*  .NACKMOD      NACK mode bit
* ISRC            I2C Interrupt Source
*  .INTCODE       Interrupt code bits.
*  .WRITE_ZEROS   Always write all 0s to this field
* EMDR            I2C Extended Mode
*  .BC            Backwards compatibility mode
*  .FCM           Forward Compatibility for Tx behav in Type1
* PSC             I2C Prescaler
*  .IPSC          I2C Prescaler Divide Down
* FFTX            I2C FIFO Transmit
*  .TXFFIL        Transmit FIFO Interrupt Level
*  .TXFFIENA      Transmit FIFO Interrupt Enable
*  .TXFFINTCLR    Transmit FIFO Interrupt Flag Clear
*  .TXFFINT       Transmit FIFO Interrupt Flag
*  .TXFFST        Transmit FIFO Status
*  .TXFFRST       Transmit FIFO Reset
*  .I2CFFEN       Transmit FIFO Enable
* FFRX            I2C FIFO Receive
*  .RXFFIL        Receive FIFO Interrupt Level
*  .RXFFIENA      Receive FIFO Interrupt Enable
*  .RXFFINTCLR    Receive FIFO Interrupt Flag Clear
*  .RXFFINT       Receive FIFO Interrupt Flag
*  .RXFFST        Receive FIFO Status
*  .RXFFRST       Receive FIFO Reset
*/

// ---------------------------
// I2C_Commands
// ---------------------------
#define I2C_CONTROLLER_SEND_MODE    0x0600U  //!< Controller-transmitter mode
#define I2C_CONTROLLER_RECEIVE_MODE 0x0400U  //!< Controller-receiver mode
#define I2C_TARGET_SEND_MODE        0x0200U  //!< Target-transmitter mode
#define I2C_TARGET_RECEIVE_MODE     0x0000U  //!< Target-receiver mode

#define I2C_REPEAT_MODE             0x0080U  //!< Only applies to Controller mode
#define I2C_START_BYTE_MODE         0x0010U  //!< Enable start byte mode
#define I2C_FREE_DATA_FORMAT        0x0008U  //!< Enable free data (no addr) format

// ---------------------------
// I2C_Interrupt
// ---------------------------
#define I2C_INT_ARB_LOST            0x00001U  //!< Arbitration-lost interrupt
#define I2C_INT_NO_ACK              0x00002U  //!< NACK interrupt
#define I2C_INT_REG_ACCESS_RDY      0x00004U  //!< Register-access-ready interrupt
#define I2C_INT_RX_DATA_RDY         0x00008U  //!< Receive-data-ready interrupt
#define I2C_INT_TX_DATA_RDY         0x00010U  //!< Transmit-data-ready interrupt
#define I2C_INT_STOP_CONDITION      0x00020U  //!< Stop condition detected
#define I2C_INT_ADDR_TARGET         0x00200U  //!< Addressed as target interrupt
#define I2C_INT_RXFF                0x10000U  //!< RX FIFO level interrupt
#define I2C_INT_TXFF                0x20000U  //!< TX FIFO level interrupt

//
// Helpful define to mask out the bits in the I2CSTR register that aren't
// associated with interrupts.
//
#define I2C_STR_INTMASK             \
    ((u16) I2C_INT_ARB_LOST |       \
     (u16) I2C_INT_NO_ACK |         \
     (u16) I2C_INT_REG_ACCESS_RDY | \
     (u16) I2C_INT_RX_DATA_RDY |    \
     (u16) I2C_INT_TX_DATA_RDY |    \
     (u16) I2C_INT_STOP_CONDITION | \
     (u16) I2C_INT_ADDR_TARGET)

// ---------------------------
// I2C_Status
// ---------------------------
#define I2C_STS_ARB_LOST       0x0001U  //!< Arbitration-lost
#define I2C_STS_NO_ACK         0x0002U  //!< No-acknowledgment (NACK)
#define I2C_STS_REG_ACCESS_RDY 0x0004U  //!< Register-access-ready (ARDY)
#define I2C_STS_RX_DATA_RDY    0x0008U  //!< Receive-data-ready
#define I2C_STS_TX_DATA_RDY    0x0010U  //!< Transmit-data-ready
#define I2C_STS_STOP_CONDITION 0x0020U  //!< Stop condition detected
#define I2C_STS_BYTE_SENT      0x0040U  //!< Byte transmit complete
#define I2C_STS_ADDR_ZERO      0x0100U  //!< Address of all zeros detected
#define I2C_STS_ADDR_TARGET    0x0200U  //!< Addressed as target
#define I2C_STS_TX_EMPTY       0x0400U  //!< Transmit shift register empty
#define I2C_STS_RX_FULL        0x0800U  //!< Receive shift register full
#define I2C_STS_BUS_BUSY       0x1000U  //!< Bus busy, wait for STOP or reset
#define I2C_STS_NACK_SENT      0x2000U  //!< NACK was sent
#define I2C_STS_TARGET_DIR     0x4000U  //!< Addressed as target transmitter

// -------------------------------------------------------------------------

typedef enum {
    I2C_INTSRC_NONE,            //!< No interrupt pending
    I2C_INTSRC_ARB_LOST,        //!< Arbitration-lost interrupt
    I2C_INTSRC_NO_ACK,          //!< NACK interrupt
    I2C_INTSRC_REG_ACCESS_RDY,  //!< Register-access-ready interrupt
    I2C_INTSRC_RX_DATA_RDY,     //!< Receive-data-ready interrupt
    I2C_INTSRC_TX_DATA_RDY,     //!< Transmit-data-ready interrupt
    I2C_INTSRC_STOP_CONDITION,  //!< Stop condition detected
    I2C_INTSRC_ADDR_TARGET      //!< Addressed as target interrupt
} I2C_InterruptSource_e;

typedef enum {
    I2C_FIFO_TXEMPTY = 0x0000U,  //!< Transmit FIFO empty
    I2C_FIFO_TX0     = 0x0000U,  //!< Transmit FIFO empty
    I2C_FIFO_TX1     = 0x0001U,  //!< Transmit FIFO 1/16 full
    I2C_FIFO_TX2     = 0x0002U,  //!< Transmit FIFO 2/16 full
    I2C_FIFO_TX3     = 0x0003U,  //!< Transmit FIFO 3/16 full
    I2C_FIFO_TX4     = 0x0004U,  //!< Transmit FIFO 4/16 full
    I2C_FIFO_TX5     = 0x0005U,  //!< Transmit FIFO 5/16 full
    I2C_FIFO_TX6     = 0x0006U,  //!< Transmit FIFO 6/16 full
    I2C_FIFO_TX7     = 0x0007U,  //!< Transmit FIFO 7/16 full
    I2C_FIFO_TX8     = 0x0008U,  //!< Transmit FIFO 8/16 full
    I2C_FIFO_TX9     = 0x0009U,  //!< Transmit FIFO 9/16 full
    I2C_FIFO_TX10    = 0x000AU,  //!< Transmit FIFO 10/16 full
    I2C_FIFO_TX11    = 0x000BU,  //!< Transmit FIFO 11/16 full
    I2C_FIFO_TX12    = 0x000CU,  //!< Transmit FIFO 12/16 full
    I2C_FIFO_TX13    = 0x000DU,  //!< Transmit FIFO 13/16 full
    I2C_FIFO_TX14    = 0x000EU,  //!< Transmit FIFO 14/16 full
    I2C_FIFO_TX15    = 0x000FU,  //!< Transmit FIFO 15/16 full
    I2C_FIFO_TX16    = 0x0010U,  //!< Transmit FIFO full
    I2C_FIFO_TXFULL  = 0x0010U   //!< Transmit FIFO full
} I2C_TxFIFOLevel_e;

typedef enum {
    I2C_FIFO_RXEMPTY = 0x0000U,  //!< Receive FIFO empty
    I2C_FIFO_RX0     = 0x0000U,  //!< Receive FIFO empty
    I2C_FIFO_RX1     = 0x0001U,  //!< Receive FIFO 1/16 full
    I2C_FIFO_RX2     = 0x0002U,  //!< Receive FIFO 2/16 full
    I2C_FIFO_RX3     = 0x0003U,  //!< Receive FIFO 3/16 full
    I2C_FIFO_RX4     = 0x0004U,  //!< Receive FIFO 4/16 full
    I2C_FIFO_RX5     = 0x0005U,  //!< Receive FIFO 5/16 full
    I2C_FIFO_RX6     = 0x0006U,  //!< Receive FIFO 6/16 full
    I2C_FIFO_RX7     = 0x0007U,  //!< Receive FIFO 7/16 full
    I2C_FIFO_RX8     = 0x0008U,  //!< Receive FIFO 8/16 full
    I2C_FIFO_RX9     = 0x0009U,  //!< Receive FIFO 9/16 full
    I2C_FIFO_RX10    = 0x000AU,  //!< Receive FIFO 10/16 full
    I2C_FIFO_RX11    = 0x000BU,  //!< Receive FIFO 11/16 full
    I2C_FIFO_RX12    = 0x000CU,  //!< Receive FIFO 12/16 full
    I2C_FIFO_RX13    = 0x000DU,  //!< Receive FIFO 13/16 full
    I2C_FIFO_RX14    = 0x000EU,  //!< Receive FIFO 14/16 full
    I2C_FIFO_RX15    = 0x000FU,  //!< Receive FIFO 15/16 full
    I2C_FIFO_RX16    = 0x0010U,  //!< Receive FIFO full
    I2C_FIFO_RXFULL  = 0x0010U   //!< Receive FIFO full
} I2C_RxFIFOLevel_e;

typedef enum {
    I2C_BITCOUNT_1 = 1U,  //!< 1 bit per data byte
    I2C_BITCOUNT_2 = 2U,  //!< 2 bits per data byte
    I2C_BITCOUNT_3 = 3U,  //!< 3 bits per data byte
    I2C_BITCOUNT_4 = 4U,  //!< 4 bits per data byte
    I2C_BITCOUNT_5 = 5U,  //!< 5 bits per data byte
    I2C_BITCOUNT_6 = 6U,  //!< 6 bits per data byte
    I2C_BITCOUNT_7 = 7U,  //!< 7 bits per data byte
    I2C_BITCOUNT_8 = 0U   //!< 8 bits per data byte
} I2C_BitCount_e;

typedef enum {
    I2C_ADDR_MODE_7BITS  = 0x0000U,  //!< 7-bit address
    I2C_ADDR_MODE_10BITS = 0x0100U   //!< 10-bit address
} I2C_AddressMode_e;

typedef enum {
    I2C_EADDR_MODE_BC  = 1U,  //!<  Backward compatibility
    I2C_EADDR_MODE_FWD = 2U   //!<  Forward compatibility
} I2C_ExtendedMode_e;

typedef enum {
    //! If SCL is low, keep it low. If high, stop when it goes low again.
    I2C_EMULATION_STOP_SCL_LOW = 0x0000U,
    //! Continue I2C operation regardless
    I2C_EMULATION_FREE_RUN     = 0x4000U
} I2C_EmulationMode_e;

typedef enum {
    I2C_DUTYCYCLE_33,  //!< Clock duty cycle is 33%
    I2C_DUTYCYCLE_50   //!< Clock duty cycle is 55%
} I2C_DutyCycle_e;

// -------------------------------------------------------------------------

void I2CA_Init(void);
u16  I2CA_WriteMem(u16 dev, u16 reg, u16 dat);

#endif
