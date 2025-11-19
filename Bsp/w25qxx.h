#ifndef W25QXX_H
#define W25QXX_H

#include "stm32f4xx_hal.h"  // 根据你的 HAL 库调整

// 设备 ID 定义
#define W25Q80   0xEF13
#define W25Q16   0xEF14  // W25Q16GW 对应此 ID
#define W25Q32   0xEF15
#define W25Q64   0xEF16
#define W25Q128  0xEF17
#define W25Q256  0xEF18

#define W25QXX_CS_GPIO_Port    GPIOA
#define W25QXX_CS_Pin          GPIO_PIN_4

// 片选引脚（假设 PA4，根据硬件调整）
#define W25QXX_CS()  HAL_GPIO_WritePin(W25QXX_CS_GPIO_Port, W25QXX_CS_Pin, GPIO_PIN_SET)   // CS 高（未选中）
#define W25QXX_CS_0() HAL_GPIO_WritePin(W25QXX_CS_GPIO_Port, W25QXX_CS_Pin, GPIO_PIN_RESET) // CS 低（选中）

// 指令集
#define W25X_WriteEnable       0x06
#define W25X_WriteDisable      0x04
#define W25X_ReadStatusReg     0x05
#define W25X_WriteStatusReg    0x01
#define W25X_ReadData          0x03
#define W25X_PageProgram       0x02
#define W25X_BlockErase        0xD8
#define W25X_SectorErase       0x20
#define W25X_ChipErase         0xC7
#define W25X_JedecDeviceID     0x9F  // 读取 JEDEC ID
#define W25X_Enable_Reset      0x66
#define W25X_Reset_Device      0x99

// 函数声明
void W25QXX_Init(void);
uint32_t W25QXX_ReadID(void);
uint8_t W25QXX_Read_SR(void);
void W25QXX_Write_SR(uint8_t sr);
void W25QXX_Write_Enable(void);
void W25QXX_Write_Disable(void);
void W25QXX_Read(uint8_t* pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead);
void W25QXX_Write(uint8_t* pBuffer, uint32_t WriteAddr, uint32_t NumByteToWrite);
void W25QXX_Erase_Sector(uint32_t Dst_Addr);
void W25QXX_Wait_Busy(void);
void W25XX_Reset_With_Soft(void);
uint8_t SPI1_ReadWriteByte(uint8_t TxData);
extern SPI_HandleTypeDef hspi1;  // 你的 SPI 句柄

#endif