#include "w25qxx.h"
#include "spi.h"  // 包含你的 SPI 函数

uint16_t W25QXX_TYPE = 0;  // 设备类型

// 软件复位
void W25XX_Reset_With_Soft(void) {
    W25QXX_CS_0();
    SPI1_ReadWriteByte(W25X_Enable_Reset);
    W25QXX_CS();
    W25QXX_CS_0();
    SPI1_ReadWriteByte(W25X_Reset_Device);
    W25QXX_CS();
    HAL_Delay(1);
}

// 初始化
void W25QXX_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOA_CLK_ENABLE();  // 使能 GPIOA 时钟（根据 CS 引脚调整）

    // 配置 CS 引脚 (PA4)
    GPIO_InitStruct.Pin = W25QXX_CS_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(W25QXX_CS_GPIO_Port, &GPIO_InitStruct);
    W25QXX_CS();  // 初始高电平

    // 假设 SPI1 已由 CubeMX 初始化

    W25XX_Reset_With_Soft();  // 复位
    W25QXX_TYPE = W25QXX_ReadID();  // 读取 ID 验证
}

// 读取 ID
uint32_t W25QXX_ReadID(void) {
    uint32_t id = 0;
    W25QXX_CS_0();
    SPI1_ReadWriteByte(W25X_JedecDeviceID);
    id = ((uint32_t)SPI1_ReadWriteByte(0xFF) << 16);
    id |= ((uint32_t)SPI1_ReadWriteByte(0xFF) << 8);
    id |= (uint32_t)SPI1_ReadWriteByte(0xFF);
    printf("W25QXX ID: 0x%06X\r\n", id);
    printf("The FLASH ID reading is unstable and requires multiple power cycles for reliable retrieval\r\n");
    W25QXX_CS();
    return id;
}

// 读取状态寄存器
uint8_t W25QXX_Read_SR(void) {
    uint8_t sr = 0xFF;
    W25QXX_CS_0();
    SPI1_ReadWriteByte(W25X_ReadStatusReg);
    sr = SPI1_ReadWriteByte(0xFF);
    W25QXX_CS();
    printf("W25QXX Status Register: 0x%02X\r\n", sr);
    printf("[BUSY=%d]\r\n", (sr & 0x01) ? 1 : 0);// BUSY:1
    printf("[WEL=%d]\r\n", (sr & 0x02) ? 1 : 0);// Write enable:1
    printf("[BP0=%d]\r\n", (sr & 0x04) ? 1 : 0);// Block protect bit 0
    printf("[BP1=%d]\r\n", (sr & 0x08) ? 1 : 0);// Block protect bit 1
    printf("[BP2=%d]\r\n", (sr & 0x10) ? 1 : 0);// Block protect bit 2
    printf("[SRP=%d]\r\n", (sr & 0x80) ? 1 : 0);// Status register protect 
    return sr;
}

// 写状态寄存器
void W25QXX_Write_SR(uint8_t sr) {
    W25QXX_Wait_Busy();
    W25QXX_Write_Enable();
    W25QXX_CS_0();
    SPI1_ReadWriteByte(W25X_WriteStatusReg);
    SPI1_ReadWriteByte(sr);
    W25QXX_CS();
    W25QXX_Wait_Busy();
}

// 写使能
void W25QXX_Write_Enable(void) {
    W25QXX_CS_0();
    SPI1_ReadWriteByte(W25X_WriteEnable);
    W25QXX_CS();
}

// 写禁用
void W25QXX_Write_Disable(void) {
    W25QXX_CS_0();
    SPI1_ReadWriteByte(W25X_WriteDisable);
    W25QXX_CS();
}

// 等待空闲
void W25QXX_Wait_Busy(void) {
    while ((W25QXX_Read_SR() & 0x01) == 0x01);  // BUSY 位为 1 时等待
}

// 扇区擦除 (4KB)
void W25QXX_Erase_Sector(uint32_t Dst_Addr) {
    W25QXX_Write_Enable();
    W25QXX_CS_0();
    SPI1_ReadWriteByte(W25X_SectorErase);
    SPI1_ReadWriteByte((uint8_t)((Dst_Addr >> 16) & 0xFF));
    SPI1_ReadWriteByte((uint8_t)((Dst_Addr >> 8) & 0xFF));
    SPI1_ReadWriteByte((uint8_t)(Dst_Addr & 0xFF));
    W25QXX_CS();
    W25QXX_Wait_Busy();
}

// 读取数据
void W25QXX_Read(uint8_t* pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead) {
    uint32_t i;
    W25QXX_CS_0();
    SPI1_ReadWriteByte(W25X_ReadData);
    SPI1_ReadWriteByte((uint8_t)((ReadAddr >> 16) & 0xFF));
    SPI1_ReadWriteByte((uint8_t)((ReadAddr >> 8) & 0xFF));
    SPI1_ReadWriteByte((uint8_t)(ReadAddr & 0xFF));
    for (i = 0; i < NumByteToRead; i++) {
        pBuffer[i] = SPI1_ReadWriteByte(0xFF);
    }
    W25QXX_CS();
}

// 写入数据（包含页面编程，需先擦除）
void W25QXX_Write(uint8_t* pBuffer, uint32_t WriteAddr, uint32_t NumByteToWrite) {
    uint32_t addr = WriteAddr;
    uint32_t end_addr = WriteAddr + NumByteToWrite - 1;
    uint32_t page_addr, bytes_in_page;

    while (addr <= end_addr) {
        // 擦除扇区（如果地址对齐）
        if ((addr % 4096) == 0) {
            W25QXX_Erase_Sector(addr);
        }

        // 页面编程（最大 256 字节）
        page_addr = addr & ~(0xFF);  // 页面对齐
        bytes_in_page = (end_addr - page_addr + 1) > 256 ? 256 : (end_addr - page_addr + 1);

        W25QXX_Write_Enable();
        W25QXX_CS_0();
        SPI1_ReadWriteByte(W25X_PageProgram);
        SPI1_ReadWriteByte((uint8_t)((page_addr >> 16) & 0xFF));
        SPI1_ReadWriteByte((uint8_t)((page_addr >> 8) & 0xFF));
        SPI1_ReadWriteByte((uint8_t)(page_addr & 0xFF));

        for (uint32_t i = 0; i < bytes_in_page; i++) {
            SPI1_ReadWriteByte(pBuffer[addr - page_addr + i]);
        }
        W25QXX_CS();
        W25QXX_Wait_Busy();

        addr += bytes_in_page;
    }
}

uint8_t SPI1_ReadWriteByte(uint8_t TxData) {
    uint8_t RxData;
    HAL_StatusTypeDef status = HAL_SPI_TransmitReceive(&hspi1, &TxData, &RxData, 1, HAL_MAX_DELAY);
    if(status != HAL_OK) {
       printf("SPI transmit/receive error\n");
    }
    return RxData;
}