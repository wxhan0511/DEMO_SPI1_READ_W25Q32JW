/**
 * @file       gtb.h
 * @brief      GTB module header.
 * @author     wxhan
 * @version    1.0.0
 * @date       2025-10-09
 * @copyright  Copyright (c) 2025 gcoreinc
 * @license    MIT License
 */

#ifndef __GTB_H
#define __GTB_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cmsis_os2.h"
#include "usbd_def.h"
/* Exported types ------------------------------------------------------------*/
extern osThreadId_t thread_id_gtb;
extern const osThreadAttr_t server_gtb_attr;
extern uint8_t hid_state_fs;
extern uint8_t USB_Recive_Buffer[64];
// Declare the external USB device handle
extern USBD_HandleTypeDef hUsbDeviceHS;
/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/

#ifdef __cplusplus
}
#endif
/* Exported functions prototypes ---------------------------------------------*/
void server_gtb(void *argument);
void server_gtb_suspend();
void server_gtb_init();
#endif /* __GTB_H */
