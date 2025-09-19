/*
 * task_sample.c
 *
 *  Created on: Jun 30, 2025
 *      Author: Wenxiao Han
 */

#include "task_sample.h"
#include "usart.h"
#include "i2c.h"
osMutexId_t sample_mutex;
osStaticMutexDef_t sample_mutex_control_block;
const osMutexAttr_t sample_mutex_attributes = {
    .name = "show_mutex",
    .cb_mem = &sample_mutex_control_block,
    .cb_size = sizeof(sample_mutex_control_block),
  };
uint8_t tx_buf[33] = {0};
uint8_t rx_buf[33] = {0};
void task_sample_run()
{

    uint8_t data[256];
    for (int i = 0; i < 256; i++)
    {
        data[i] = i + 1;
    }
    for(;;)
    {
        osDelay(100);
    }

}



void task_sample_init(void)
{
    // sample_mutex = osMutexNew(&sample_mutex_attributes);
    // if(sample_mutex == NULL)
    // {
    //     LOG_ERROR("sample_mutex creation failed");
    // }
//    task_sample_cfg.cmd = NORMAL_LOOP_EVENT;
//    dev_vol.vol_cali_en = 1;
//    for(uint8_t i = 0; i < 6; i++)
//        dev_cur.cur_cali_en[i] = 1;
//
//    cfg_set_d_sample_en(0);
//    cfg_set_r_sample_en(0);
//    cfg_set_64_vol_sample_en(0);
//    cfg_set_bias_en(0);
//
//    ring_buf_init(&avg_data,(uint8_t*)avg_data_buf,sizeof(avg_data_buf));

    task_sample_handle = osThreadNew(task_sample_run,NULL, &task_sample_attributes);
    if (task_sample_handle == NULL)
    {
    }
}
