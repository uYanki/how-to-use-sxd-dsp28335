#include "board.h"
#include "lib.lcd1602.h"

void main(void)
{
    InitSysCtrl();

    /* User Code Begin */

    XINTF_Init();

    LCD_Init();
    LCD_SetCursor(0, 0);
    LCD_ShowString("hello world");
    LCD_SetCursor(4, 1);
    LCD_ShowString("hello world");

    while (1)
    {
    }

    /* User Code End */
}
