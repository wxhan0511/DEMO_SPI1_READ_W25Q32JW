/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    i2c.h
  * @brief   This file contains all the function prototypes for
  *          the i2c.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __I2C_H__
#define __I2C_H__

#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>
#include "cmsis_os2.h" // Add this line to define osMutexId_t

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */
#define SLAVE_ADDR 0x37 // 从机地址，注意左移一位，因为HAL库需要左移一位传递给I2C函数
#define DATA_SIZE 256
#define I2C_TIMEOUT 100

extern osSemaphoreId_t i2cSemaphore;
extern osThreadId_t slaveTxTaskHandle, slaveRxTaskHandle;

extern uint8_t tx_buf[33]; // 发送缓冲区
extern uint8_t rx_buf[33]; // 接收缓冲区
#define FRAME_CMD_HEADER_TX 0xF8
#define FRAME_CMD_HEADER_RX 0x8F
#define FRAME_DATA_HEADER_TX 0xE7
#define FRAME_DATA_HEADER_RX 0x7E

extern volatile uint8_t exti_notify_from_peer; // 外部中断通知标志
extern volatile uint8_t master_data_ready; // 主机有数据要发
extern volatile uint8_t slave_data_ready;  // 从机有数据要发标志位
extern volatile uint8_t i2c_bus_busy; // I2C总线忙标志
extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c2;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void send_data_to_master(uint8_t* tx_buf, uint16_t len);
void MX_I2C1_Init(void);
void MX_I2C2_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __I2C_H__ */

