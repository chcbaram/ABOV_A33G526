/*
 * hw_def.h
 *
 *  Created on: 2021. 7. 26.
 *      Author: baram
 */

#ifndef SRC_HW_HW_DEF_H_
#define SRC_HW_HW_DEF_H_

#include "bsp.h"


#define _DEF_FIRMWATRE_VERSION    "B210801R1"
#define _DEF_BOARD_NAME           "A33G526_BOOT"


#define _USE_HW_FLASH

#define _USE_HW_LED
#define      HW_LED_MAX_CH          6

#define _USE_HW_UART
#define      HW_UART_MAX_CH         1

#define _USE_HW_LOG
#define      HW_LOG_CH              _DEF_UART1

#define _USE_HW_BUTTON
#define      HW_BUTTON_MAX_CH       1

#define _USE_HW_CMD
#define      HW_CMD_MAX_DATA_LENGTH 1024




#define FLASH_ADDR_TAG              0x0008000
#define FLASH_ADDR_FW               0x0008400
#define FLASH_ADDR_FW_VER           0x0008800

#define FLASH_ADDR_START            0x0008000
#define FLASH_ADDR_END              (FLASH_ADDR_START + (256-32)*1024)


#endif /* SRC_HW_HW_DEF_H_ */
