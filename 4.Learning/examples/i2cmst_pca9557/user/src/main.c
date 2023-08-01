

#include "board.h"
#include "lib.pca9557.h"

void main(void)
{
    InitSysCtrl();

    /* User Code Begin */
    {
        u8 led = 0b00001010;

        I2CA_Init();

        // OUTPUT mode
        I2CA_WriteMem(PCA9557_I2C_ADDR, REG_PCA9557_CONFIG, 0x00);

        while (1)  // 流水灯
        {
            I2CA_WriteMem(PCA9557_I2C_ADDR, REG_PCA9557_OUTPUT_PORT, led);
            led = _rol(led, 1, 8);  // 循环左移
            DelayBlockMS(300);
        }
    }
    /* User Code End */
}
