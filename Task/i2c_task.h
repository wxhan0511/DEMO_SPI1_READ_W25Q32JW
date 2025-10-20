#ifndef __I2C_TASK_H
#define __I2C_TASK_H

#include "cmsis_os.h"

extern osThreadId_t slaveTxTaskHandle;
extern osThreadId_t slaveRxTaskHandle;
extern const osThreadAttr_t slaveTxTask_attributes;
extern const osThreadAttr_t slaveRxTask_attributes;

void SlaveTxTask(void *argument);
void SlaveRxTask(void *argument);
void MasterTxTask(void *argument);
void MasterRxTask(void *argument);

extern osThreadId_t masterTxTaskHandle;
extern osThreadId_t masterRxTaskHandle;

void slave_rx_task_init();
void slave_tx_task_init();
void master_tx_task_init();
void master_rx_task_init();

void I2C_Semaphore_Init(void);

extern osSemaphoreId_t i2c1Semaphore;
extern osSemaphoreId_t i2c2Semaphore;
#endif