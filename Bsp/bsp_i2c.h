//
// Created by 薛斌 on 24-8-17.
//

#ifndef BSP_I2C_H
#define BSP_I2C_H

#include <bsp.h>

typedef struct
{
    void* handle;
    uint8_t dev_addr;
} i2c_dev_t;

#endif //BSP_I2C_H
