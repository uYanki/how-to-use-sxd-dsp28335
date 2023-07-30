#ifndef __LCD1602_H__
#define __LCD1602_H__

#include "bsp.xintf.h"
#include "bsp.delay.h"

#if CONFIG_USING_XINTF_LCD1602

#  define LCD_DISPLAY_LINES       2   // number of visible lines of the display
#  define LCD_DISPLAY_LENGTH      16  // visibles characters per line of the display

/*

引脚说明:
- VL: 对比度调整, 接近VDD时对比度最弱, 接近VSS时对比度最强.
- RS: 寄存器选择, 高电平选择数据寄存器, 低电平选择指令寄存器
- RW: 读写信号线, 高电平进行读操作, 低电平进行写操作
    - RS=RW=0   可写入指令或显示地址
    - RS=1,RW=1 可读取忙信号
    - RS=1,RW=0 可写入数据
- EN: 使能端, 其在高电平变低电平(下降沿)时, 液晶模块执行命令
- D0-D7: 8位双向数据线
- BLA: 背光正极
- BLK: 背光负极

*/

/**************/

// commands
#  define LCD_CLEARDISPLAY        0x01  // clear display
#  define LCD_RETURNHOME          0x02  // return home
#  define LCD_ENTRYMODESET        0x04  // entry mode set
#  define LCD_DISPLAYCONTROL      0x08  // display control
#  define LCD_CURSORSHIFT         0x10  // cursor shift
#  define LCD_FUNCTIONSET         0x20  // function set
#  define LCD_SETCGRAMADDR        0x40  // set cgram addr
#  define LCD_SETDDRAMADDR        0x80  // set ddram addr

// - flags for display entry mode
#  define LCD_ENTRYRIGHT          0x00  // decrement cursor
#  define LCD_ENTRYLEFT           0x02  // increment cursor
#  define LCD_ENTRYSHIFTINCREMENT 0x01
#  define LCD_ENTRYSHIFTDECREMENT 0x00

// - flags for display on/off control
#  define LCD_DISPLAYON           0x04
#  define LCD_DISPLAYOFF          0x00
#  define LCD_CURSORON            0x02
#  define LCD_CURSOROFF           0x00
#  define LCD_BLINKON             0x01
#  define LCD_BLINKOFF            0x00

// - flags for display/cursor shift
#  define LCD_DISPLAYMOVE         0x08
#  define LCD_CURSORMOVE          0x00
#  define LCD_MOVERIGHT           0x04
#  define LCD_MOVELEFT            0x00

// - flags for function set
#  define LCD_8BITMODE            0x10
#  define LCD_4BITMODE            0x00
#  define LCD_2LINE               0x08
#  define LCD_1LINE               0x00
#  define LCD_5x10DOTS            0x04
#  define LCD_5x7DOTS             0x00
// LCD_4BITMODE | LCD_1LINE | LCD_5x7DOTS = 0x00
// LCD_4BITMODE | LCD_2LINE | LCD_5x7DOTS = 0x08
// LCD_8BITMODE | LCD_1LINE | LCD_5x7DOTS = 0x10
// LCD_8BITMODE | LCD_2LINE | LCD_5x7DOTS = 0x18

// internal line length of the display
#  define LCD_LINE_LENGTH         0x40
//  DDRAM address of first char of line
#  define LCD_LINE1_START         0x00
#  define LCD_LINE2_START         0x40
#  define LCD_LINE3_START         0x14
#  define LCD_LINE4_START         0x54

void LCD_WriteByte(u8 byte, u8 mode);
#  define LCD_WriteCmd(byte)  LCD_WriteByte(byte, 0x00)
#  define LCD_WriteData(byte) LCD_WriteByte(byte, 0x01)

void LCD_Init(void);
void LCD_ShowChar(const char ch);
void LCD_ShowString(const char *str);
void LCD_ShowStringWrap(u8 col, u8 row, const char *str);

void LCD_ClearLine(u8 line);
void LCD_SetCursor(u8 col, u8 row);

void LCD_ReturnHome(void);
void LCD_Clear(void);

void LCD_DisplayOn(void);
void LCD_DisplayOff(void);

void LCD_CursorOn(void);
void LCD_CursorOff(void);
void LCD_BlinkOn(void);
void LCD_BlinkOff(void);

void LCD_ScrollLeft(void);
void LCD_ScrollRight(void);

void LCD_LeftToRight(void);
void LCD_RightToLeft(void);
void LCD_AutoScrollOn(void);
void LCD_AutoScrollOff(void);

void LCD_CreateChar(u8 location, u8 charmap[]);

#endif  // CONFIG_USING_XINTF_LCD1602

#endif
