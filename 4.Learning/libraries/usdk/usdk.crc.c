#include "usdk.crc.h"

u8 crc8(RO u8* dat, u16 len)
{
    //  x^8 + x^2 + x^1 + 1
    u8 i, crc = 0x00;

    while (len--) {
        crc ^= *dat++;
        for (i = 0; i < 8; ++i) {
            if (crc & 0x80) {
                crc = (crc << 1) ^ 0x07;
            } else {
                crc <<= 1;
            }
        }
    }

    return crc;
}

u16 crc16(RO u8* dat, u16 len)
{
    // x^16 + x^15 + x^2 + 1

    u16 i, crc = 0xFFFF;

    while (len--) {
        crc ^= *dat++;
        for (i = 0; i < 8; ++i) {
            if (crc & 0x0001) {
                crc = (crc >> 1) ^ 0xA001;
            } else {
                crc >>= 1;
            }
        }
    }

    return crc;
}
