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
/* Exported types ------------------------------------------------------------*/
extern osThreadId_t thread_id_gtb;
extern const osThreadAttr_t server_gtb_attr;
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
