
#ifndef __LIB_PCA9557_H__
#define __LIB_PCA9557_H__

#include "bsp.i2c.h"

#define PCA9557_I2C_ADDR 0x1C

typedef enum {
    REG_PCA9557_INPUT_PORT   = 0x00,  ///< RO, input port
    REG_PCA9557_OUTPUT_PORT  = 0x01,  ///< RW, output port
    REG_PCA9557_POLARITY_INV = 0x02,  ///< RW, polarity inversion ( 0:normal, 1:invert )
    REG_PCA9557_CONFIG       = 0x03,  ///< RW, configuration ( 0:output, 1:input )
} PCA9557_REG_e;

#endif
