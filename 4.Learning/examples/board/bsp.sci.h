#ifndef __BSP_SCI_H__
#define __BSP_SCI_H__

#include "common.h"

/**
 * SCI_CCR             Communications control register
 *    .SCICHAR_M       Character length control
 *    .ADDRIDLE_MODE   ADDR/IDLE Mode control
 *    .LOOPBKENA       Loop Back enable
 *    .PARITYENA       Parity enable
 *    .PARITY          Even or Odd Parity
 *    .STOPBITS        Number of Stop Bits
 *
 * SCI_CTL1            Control register 1
 *    .RXENA           SCI receiver enable
 *    .TXENA           SCI transmitter enable
 *    .SLEEP           SCI sleep
 *    .TXWAKE          Transmitter wakeup method
 *    .SWRESET         Software reset
 *    .RXERRINTENA     Receive error interrupt enable
 *
 * SCI_HBAUD           SCI 16-bit Baud rate (high) register
 * SCI_LBAUD           SCI 16-bit Baud rate (low) register
 *
 * SCI_CTL2            Control register 2
 *     TXINTENA        Transmit interrupt enable
 *     RXBKINTENA      Receiver-buffer break enable
 *     TXEMPTY         Transmitter empty flag
 *     TXRDY           Transmitter ready flag
 *
 * SCI_RXST            Receive status register
 *    .RXWAKE          Receiver wakeup detect flag
 *    .PE              Parity error flag
 *    .OE              Overrun error flag
 *    .FE              Framing error flag
 *    .BRKDT           Break-detect flag
 *    .RXRDY           Receiver ready flag
 *    .RXERROR         Receiver error flag
 *
 * SCI_RXEMU           Receive emulation buffer register
 *
 * SCI_RXBUF           Receive data buffer
 *    .SAR             Receive Character bits
 *    .SCIFFPE         Receiver error flag
 *    .SCIFFFE         Receiver error flag
 *
 * SCI_TXBUF           Transmit data buffer
 *
 * SCI_FFTX            FIFO transmit register
 *    .TXFFIL          Interrupt level
 *    .TXFFIENA        Interrupt enable
 *    .TXFFINTCLR      Clear INT flag
 *    .TXFFINT         INT flag
 *    .TXFFST          FIFO status
 *    .TXFIFORESET     FIFO reset
 *    .SCIFFENA        Enhancement enable
 *    .SCIRST          SCI reset rx/tx channels
 *
 * SCI_FFRX            FIFO receive register
 *    .RXFFIL          Interrupt level
 *    .RXFFIENA        Interrupt enable
 *    .RXFFINTCLR      Clear INT flag
 *    .RXFFINT         INT flag
 *    .RXFFST          FIFO status
 *    .RXFIFORESET     FIFO reset
 *    .RXFFOVRCLR      Clear overflow
 *    .RXFFOVF         FIFO overflow
 *
 * SCI_FFCT            FIFO control register
 *    .FFTXDLY         FIFO transmit delay
 *    .CDC             Auto baud mode enable
 *    .ABDCLR          Auto baud clear
 *    .ABD             Auto baud detect
 *
 * SCI_PRI             SCI priority control
 *    .FREESOFT        Emulation modes
 */

// --------------------------
// SCI_Interrupt
// --------------------------

#define SCIx_SetIntState_RxError(SCIx, state) (SCIx.SCICTL1.bit.RXERRINTENA = (state))  // Receive error
#define SCIx_SetIntState_RxBreak(SCIx, state) (SCIx.SCICTL2.bit.RXBKINTENA = (state))   // Receiver buffer break
#define SCIx_SetIntState_TxReady(SCIx, state) (SCIx.SCICTL2.bit.TXRDY = (state))        // Transmit interrupt
#define SCIx_SetIntState_TxFIFO(SCIx, state)  (SCIx.SCIFFTX.bit.TXFFIENA = (state))     // TX FIFO level
#define SCIx_SetIntState_RxFIFO(SCIx, state)  (SCIx.SCIFFRX.bit.RXFFIENA = (state))     // RX FIFO level

// ---------------------------
// SCI_FIFOLevel
// ---------------------------
#define SCI_FIFO_LVL_0                        0x0000U  //!< empty
#define SCI_FIFO_LVL_1                        0x0001U  //!< 1/16 full
#define SCI_FIFO_LVL_2                        0x0002U  //!< 2/16 full
#define SCI_FIFO_LVL_3                        0x0003U  //!< 3/16 full
#define SCI_FIFO_LVL_4                        0x0004U  //!< 4/16 full
#define SCI_FIFO_LVL_5                        0x0005U  //!< 5/16 full
#define SCI_FIFO_LVL_6                        0x0006U  //!< 6/16 full
#define SCI_FIFO_LVL_7                        0x0007U  //!< 7/16 full
#define SCI_FIFO_LVL_8                        0x0008U  //!< 8/16 full
#define SCI_FIFO_LVL_9                        0x0009U  //!< 9/16 full
#define SCI_FIFO_LVL_10                       0x000AU  //!< 10/16 full
#define SCI_FIFO_LVL_11                       0x000BU  //!< 11/16 full
#define SCI_FIFO_LVL_12                       0x000CU  //!< 12/16 full
#define SCI_FIFO_LVL_13                       0x000DU  //!< 13/16 full
#define SCI_FIFO_LVL_14                       0x000EU  //!< 14/16 full
#define SCI_FIFO_LVL_15                       0x000FU  //!< 15/16 full
#define SCI_FIFO_LVL_16                       0x0010U  //!< full

// ---------------------------
// SCI_Config: ScixRegs.SCICCR
// ---------------------------

#define SCI_CFG_DATABITS_MASK                 0x0007U  //!< Mask for extracting word length
#define SCI_CFG_DATABITS_8                    0x0007U  //!< 8 bit data
#define SCI_CFG_DATABITS_7                    0x0006U  //!< 7 bit data
#define SCI_CFG_DATABITS_6                    0x0005U  //!< 6 bit data
#define SCI_CFG_DATABITS_5                    0x0004U  //!< 5 bit data
#define SCI_CFG_DATABITS_4                    0x0003U  //!< 4 bit data
#define SCI_CFG_DATABITS_3                    0x0002U  //!< 3 bit data
#define SCI_CFG_DATABITS_2                    0x0001U  //!< 2 bit data
#define SCI_CFG_DATABITS_1                    0x0000U  //!< 1 bit data

#define SCI_CFG_STOPBITS_MASK                 0x0080U  //!< Mask for extracting stop bits
#define SCI_CFG_STOPBITS_ONE                  0x0000U  //!< One stop bit
#define SCI_CFG_STOPBITS_TWO                  0x0080U  //!< Two stop bits

#define SCI_CFG_PARITY_MASK                   0x0060U  //!< Parity Mask
#define SCI_CFG_PARITY_NONE                   0x0000U  //!< No parity
#define SCI_CFG_PARITY_EVEN                   0x0060U  //!< Even parity
#define SCI_CFG_PARITY_ODD                    0x0020U  //!< Odd parity

// directly connect RX and TX internally
#define SCIx_SetLoopBack(SCIx, state)         (ScicRegs.SCICCR.bit.LOOPBKENA = !!(state))

#define SCIx_SetFrameFormat(SCIx, format)     (SCIx.SCICCR.all = (format))

// ---------------------------
// SCI_RxStatus: ScixRegs.SCIRXST
// ---------------------------
#define SCI_RXSTATUS_WAKE                     0x0002U  //!< Receiver wake up detect
#define SCI_RXSTATUS_PARITY                   0x0004U  //!< Parity error
#define SCI_RXSTATUS_OVERRUN                  0x0008U  //!< Overrun error
#define SCI_RXSTATUS_FRAMING                  0x0010U  //!< Framing error
#define SCI_RXSTATUS_BREAK                    0x0020U  //!< Break detect
#define SCI_RXSTATUS_READY                    0x0040U  //!< Receiver ready
#define SCI_RXSTATUS_ERROR                    0x0080U  //!< Receiver error

// ---------------------------
// SCI_SetBaudrate
// ---------------------------
// baud set @LSPCLK = 37.5MHz.
#define SCIx_SetBaudrate(SCIx, baudrate)                     \
    do {                                                     \
        u32 _baudrate = 37500000UL / (8UL * baudrate) - 1UL; \
        SCIx.SCIHBAUD = _baudrate >> 8;                      \
        SCIx.SCILBAUD = _baudrate & 0xff;                    \
    } while (0)

// ---------------------------
// SCIx_SetMode: ScixRegs.SCICTL1
// ---------------------------

#define SCI_MODE_RX              0x0001U
#define SCI_MODE_TX              0x0002U

#define SCIx_SetMode(SCIx, mode) WriteBits32(SCIx.SCICTL1.all, mode, 0, 2)

// ---------------------------
// SCIx_SoftReset: ScixRegs.SCICTL1
// ---------------------------

#define SCIx_SoftReset(SCIx)     SETBIT(SCIx.SCICTL1.all, 5)

// -------------------------------------------------------------------------

void SCI_Init(void);

#if CONFIG_USING_SCIB_RS232

void SCIB_Init(void);
void SCIB_TxChar(u8 chr);
void SCIB_TxString(RO u8 *str);
void SCIB_TxBytes(RO u8 *arr, u16 len);
u8   SCIB_RxChar(void);

#  if CONFIG_USING_SCIB_PRINTF
#    define SCIB_Println(fmt, ...) SCIB_Printf(fmt "\n", ##__VA_ARGS__)
s32 SCIB_Printf(u8 *fmt, ...);
#  endif

#endif  // CONFIG_USING_SCIB_RS232

#if CONFIG_USING_SCIC_RS232

void SCIC_Init(void);
void SCIC_TxChar(u8 chr);
void SCIC_TxString(RO u8 *str);
void SCIC_TxBytes(RO u8 *arr, u16 len);
u8   SCIC_RxChar(void);

#  if CONFIG_USING_SCIC_PRINTF
#    define SCIC_Println(fmt, ...) SCIC_Printf(fmt "\n", ##__VA_ARGS__)
s32 SCIC_Printf(u8 *fmt, ...);
#  endif

#endif  // CONFIG_USING_SCIC_RS232

#endif  // __BSP_SCI_H__
