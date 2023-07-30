#include "board.h"

#include <stdio.h>
#include <string.h>

// 注: 若编译不通过，可尝试把未使用的 CMD 给删除掉
#define CONFIG_RUNIN_RAM   1 // cmd_ram or cmd_flash version
#define CONFIG_RUNIN_FLASH 1 // cmd_flash

void main()
{
    InitSysCtrl();

    InitPieCtrl();
    IER = 0x0000;
    IFR = 0x0000;
    InitPieVectTable();

    /* User Code Begin */

#if CONFIG_RUNIN_RAM && CONFIG_RUNIN_FLASH

    // Copy program from RAM to FLASH
    // @note: RamfuncsLoadStart、 RamfuncsLoadEnd、 和RamfuncsRunStart generate by F28335.cmd
    MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);
    // Calling InitFlash() to set the flash to waiting state (this function must run in RAM)
    InitFlash();

#endif

    GPIO_Init();
    SCIB_Init();
    SCIC_Init();

    while (1)
    {
        while (KEY3_READ())  // press key !!!
        {
#if CONFIG_RUNIN_RAM

            ///< code run in RAM memory (support %f...)

            SCIB_Println("<SCIB_Println>");
            SCIB_Println("[%d][%.4f][%3d]", 10000, 23.157, 12345);
            SCIB_Println("[0x%x][%o][%c][%s]", 12, 22, 'd', "hello");

            DelayBlockMS(10);

            SCIC_Println("<SCIC_Println>");
            SCIC_Println("[%d][%.4f][%3d]", 10000, 23.157, 12345);
            SCIC_Println("[0x%x][%o][%c][%s]", 12, 22, 'd', "hello");

            DelayBlockMS(10);

            println("<println>");
            println("[%d][%.4f][%3d]", 10000, 23.157, 12345);
            println("[0x%x][%o][%c][%s]", 12, 22, 'd', "hello");

            DelayBlockS(1);

#elif CONFIG_RUNIN_FLASH

            ///< code run in FLASH memory (unsupport %f...)

            // flash 中调用 DelayBlockS(1) 会导致程序卡死

            SCIB_Println("<SCIB_Println>");
            SCIB_Println("[%d][%3d]", 10000, 12345);
            SCIB_Println("[0x%x][%o][%c][%s]", 12, 22, 'd', "hello");

            SCIC_Println("<SCIC_Println>");
            SCIC_Println("[%d][%3d]", 10000, 12345);
            SCIC_Println("[0x%x][%o][%c][%s]", 12, 22, 'd', "hello");

            println("<println>");
            println("[%d][%3d]", 10000, 12345);
            println("[0x%x][%o][%c][%s]", 12, 22, 'd', "hello");

            FirewareDelay(10);

#endif

            LED_TOGGLE();
        }
    }

    /* User Code End */
}
