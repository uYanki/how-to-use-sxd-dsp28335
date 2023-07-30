
#include "lib.lcd1602.h"

#if CONFIG_USING_XINTF_LCD1602

u8 display_control, display_mode;

static u8 row_offsets[] = {LCD_LINE1_START, LCD_LINE2_START, LCD_LINE3_START, LCD_LINE4_START};

#define LCD_Delay DelayBlockMS // 使用 DelayBlockUS 可能会导致无法正常显示

void LCD_Init(void)
{
    LCD_WriteCmd(0x38);  // 0b00111000 显示模式设置(2行，5x7)
    LCD_Delay(100);
    LCD_WriteCmd(0x38);
    LCD_Delay(100);

    LCD_WriteCmd(0x0C);                    // 0b00001100 开启显示开关但不闪烁
    LCD_WriteCmd(display_mode = 0x06);     // 0b00000110 显示光标移动位置
    LCD_WriteCmd(display_control = 0x01);  // 0b00000001 清除屏幕

    LCD_WriteCmd(LCD_RETURNHOME);
    // Display on/off control --> D=0,C=0, B=0  ---> display off
    LCD_WriteCmd(LCD_DISPLAYCONTROL | LCD_DISPLAYOFF);
    // clear display
    LCD_WriteCmd(LCD_CLEARDISPLAY);
    // Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
    LCD_WriteCmd(display_mode = LCD_ENTRYMODESET | LCD_ENTRYLEFT);
    // Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
    LCD_WriteCmd(display_control = LCD_DISPLAYCONTROL | LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF);
}

void LCD_Reset(void)
{
    LCD1602_RS = 0;
    LCD_Delay(1);
    LCD1602_RW = 0;
    LCD_Delay(1);
    LCD1602_EN = 0;
}

void LCD_WriteByte(u8 byte, u8 mode /* rs = 0x00:cmd, 0x01:data */)
{
    LCD1602_RS  = mode;
    LCD1602_RW  = 0;
    LCD1602_EN  = 1;
    LCD1602_DAT = byte;
    LCD1602_EN  = 0;
    LCD_Delay(1);
}

void LCD_ShowChar(const char ch) { LCD_WriteData(ch); }

void LCD_ShowString(const char *str)
{
    while (*str)
    {
        LCD_WriteData(*str++);
    }
}

void LCD_ClearLine(u8 line)
{
    // 仅适用于写入方向为左的情况 ( display_mode & LCD_ENTRYLEFT != 0 )
    LCD_SetCursor(0x00, line);
    LCD_ShowString("                ");  // 16
}

void LCD_SetCursor(u8 col, u8 row)
{
    if (row >= LCD_DISPLAY_LINES)
    {
        row = LCD_DISPLAY_LINES - 1;
    }
    LCD_WriteCmd(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

// 显示字符串（带自动换行）
void LCD_ShowStringWrap(u8 col, u8 row, const char *str)
{
    // set cursor
    row += col / LCD_DISPLAY_LENGTH;
    if (row >= LCD_DISPLAY_LINES)
    {
        return;
    }
    col %= LCD_DISPLAY_LENGTH;
    LCD_WriteCmd(LCD_SETDDRAMADDR | (col + row_offsets[row]));
    // show string
    for (u8 i = col; *str; ++i)
    {
        if (i == LCD_DISPLAY_LENGTH)
        {
            if (++row == LCD_DISPLAY_LINES)
            {
                return;
            }
            LCD_WriteCmd(LCD_SETDDRAMADDR | row_offsets[row]);  // wrap
            i = 0;
        }
        LCD_WriteData(*str++);
    }
}

// Allows us to fill the first 8 CGRAM locations with custom characters 显示自定义字符
void LCD_CreateChar(u8 location /*0~7*/, u8 charmap[])
{
    // u8 cgram[8] = {0x40, 0x48, 0x50, 0x58, 0x60, 0x68, 0x70, 0x78};
    location &= 0x07;  // only have 8 locations
    LCD_WriteCmd(LCD_SETCGRAMADDR | (location << 3));
    for (u8 i = 0; i < 8; ++i)
    {
        LCD_WriteData(charmap[i]);
    }
}

// Turn the display on (quickly)
void LCD_DisplayOn(void) { LCD_WriteCmd(display_control |= LCD_DISPLAYON); }

// Turn the display off (quickly)
void LCD_DisplayOff(void) { LCD_WriteCmd(display_control &= ~LCD_DISPLAYON); }

// Turns the underline cursor on
void LCD_CursorOn(void) { LCD_WriteCmd(display_control |= LCD_CURSORON); }

// Turns the underline cursor off
void LCD_CursorOff(void) { LCD_WriteCmd(display_control &= ~LCD_CURSORON); }

// Turn on the blinking cursor
void LCD_BlinkOn(void) { LCD_WriteCmd(display_control |= LCD_BLINKON); }

// Turn off the blinking cursor
void LCD_BlinkOff(void) { LCD_WriteCmd(display_control &= ~LCD_BLINKON); }

// This is for text that flows Left to Right
void LCD_LeftToRight(void) { LCD_WriteCmd(display_mode |= LCD_ENTRYLEFT); }

// This is for text that flows Right to Left
void LCD_RightToLeft(void) { LCD_WriteCmd(display_mode &= ~LCD_ENTRYLEFT); }

// This will 'right justify' text from the cursor 每写1个字符，屏幕左移1次，但光标位置不变, 以实现内容右对齐光标
void LCD_AutoScrollOn(void) { LCD_WriteCmd(display_mode |= LCD_ENTRYSHIFTINCREMENT); }

// This will 'left justify' text from the cursor
void LCD_AutoScrollOff(void) { LCD_WriteCmd(display_mode &= ~LCD_ENTRYSHIFTINCREMENT); }

// These commands scroll the display without changing the RAM  (once)
// - LCD_CURSORSHIFT: 光标移动（可选），
// - LCD_DISPLAYMOVE：显示屏内容移动（可选），
// - LCD_MOVELEFT / LCD_MOVERIGHT：移动的方向
void LCD_ScrollLeft(void) { LCD_WriteCmd(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT); }

void LCD_ScrollRight(void) { LCD_WriteCmd(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT); }

// set cursor position to zero 光标归位
void LCD_ReturnHome(void) { LCD_WriteCmd(LCD_RETURNHOME); }

// clear display, set cursor position to zero
void LCD_Clear(void) { LCD_WriteCmd(LCD_CLEARDISPLAY); }

#endif  // CONFIG_USING_XINTF_LCD1602
