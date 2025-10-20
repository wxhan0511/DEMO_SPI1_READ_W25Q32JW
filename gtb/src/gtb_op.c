#include "bsp_gtb.h"
#include "tp_define.h"


extern uint8_t dynamic_cmd[MAXCMDCOUNT][MAXCMDSIZE];
//gloable variables initial
void gtb_global_var_init(tp_config_t *tp_config)
{
    tp_config->debug_enable = false;
    tp_config->flash_program_flash = false;
    tp_config->int_trans = true;
    tp_config->fw_mode = FWMODE_DISABLE;
    tp_config->raw_data_flag = false;
    tp_config->long_packet_enable = false;
    tp_config->long_packet_count = 0;
    tp_config->ic_touch_data_len = 0;
    tp_config->ic_touch_data_index = 0;
    tp_config->ic_type_index = 0xff;
    tp_config->transfer_flag = false;
    tp_config->cs_high_en = true;
    tp_config->cs_low_en = true;
    tp_config->one_cs_for_host_download_enable = false;
    tp_config->int_flag = false;
    tp_config->ex_ti_flag = false;
    tp_config->download_enable = false;
    tp_config->download_complete = false;
    tp_config->offline_mode = 0;
    tp_config->fw_len = 0;
    tp_config->transfer_feedback_enable = false;
//    gbSPI_TX_Flag = false;
//    gbSPI_RX_Flag = false;
//    gI2CSPIRegAddress = 0;
    tp_config->i2c_slave_address = 0x4c;
    tp_config->spi_i2c_data_len = 0;
    tp_config->spi_i2c_count = 0;
    tp_config->interface_mode = I2C_MODE;
    tp_config->dynamic_cmd_count = 0;
    tp_config->dynamic_total_cmd_num = 0;
    tp_config->dynamic_cmd_data_len = 0;
    tp_config->transfer_status = 0;
    tp_config->fw_data_len = 0;
    tp_config->fw_data_len1 = 0;
    for(int i = 0;i < MAXCMDCOUNT;i++)
    {
        for(int j = 0;j < MAXCMDSIZE;j++)
            dynamic_cmd[i][j] = 0;
    }

//    for(int i = 0;i < (MAXUSBPACKETSIZE - 8);i++)
//        flash_Buffer[i] = 0;
//
//    memset(gUSBBuf_TX,0,sizeof(gUSBBuf_TX));
//    for(int i = 0;i < sizeof(gUSBBuf_RX);i++)
//    {
//        gUSBBuf_RX[i] = 0;
//    }
//    memset(gI2CSPIBuf_TX,0,sizeof(gI2CSPIBuf_TX));
//    memset(gI2CSPIBuf_RX,0,sizeof(gI2CSPIBuf_RX));
//    memset(SPI_Buffer_Tx,0,sizeof(SPI_Buffer_Tx));
//    memset(SPI_Buffer_Rx,0,sizeof(SPI_Buffer_Rx));
//    memset(gCOMBuf_TX,0,sizeof(gCOMBuf_TX));
//    memset(gCOMBuf_RX,0,sizeof(gCOMBuf_RX));
}