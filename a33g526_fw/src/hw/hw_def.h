/*
 * hw_def.h
 *
 *  Created on: 2021. 7. 26.
 *      Author: baram
 */

#ifndef SRC_HW_HW_DEF_H_
#define SRC_HW_HW_DEF_H_

#include "bsp.h"


#define _DEF_FIRMWATRE_VERSION    "V210726R1"
#define _DEF_BOARD_NAME           "A33G526"



#define _USE_HW_LED
#define      HW_LED_MAX_CH          6

#define _USE_HW_UART
#define      HW_UART_MAX_CH         1

#define _USE_HW_LOG
#define      HW_LOG_CH              _DEF_UART1

#define _USE_HW_BUTTON
#define      HW_BUTTON_MAX_CH       1


#endif /* SRC_HW_HW_DEF_H_ */
