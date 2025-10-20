/**
 * @file       bsp_i2c_bus.h
 * @brief      RA_PowerEX
 * @author     wxhan
 * @version    1.0.0
 * @date       2025-10-13
 * @copyright  Copyright (c) 2025 gcoreinc
 * @license    MIT License
 */

#ifndef __BSP_I2C_BUS_H
#define __BSP_I2C_BUS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdbool.h>
#include "drv_defines.h"
/* Exported types ------------------------------------------------------------*/


/* Exported constants --------------------------------------------------------*/
extern I2C_HandleTypeDef hi2c;
/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
typedef enum{
    I2C_SPEED_100KHZ = 100000,
    I2C_SPEED_400KHZ = 400000
}bsp_i2c_speed;

typedef struct {
    void* handle;
    void (*init)(void *handle,uint32_t speed);
    BSP_STATUS_T (*read_data)(void *handle,uint8_t address,uint8_t command,uint8_t *data,uint32_t size);
    BSP_STATUS_T (*write_data)(void *handle,uint8_t address,uint8_t command,const uint8_t *data,uint32_t size);
}bsp_i2c_hw_t;

void bsp_i2c_bus_hw_init(void *handle,uint32_t speed);

BSP_STATUS_T bsp_i2c_bus_hw_write_data(void *handle,uint8_t address,uint8_t command,const uint8_t *data,uint32_t size);

BSP_STATUS_T bsp_i2c_bus_hw_read_data(void *handle,uint8_t address,uint8_t command,uint8_t *data,uint32_t size);

#endif /* __BSP_I2C_BUS_H */
