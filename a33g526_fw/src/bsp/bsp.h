/*
 * bsp.h
 *
 *  Created on: 2021. 7. 26.
 *      Author: baram
 */

#ifndef SRC_BSP_BSP_H_
#define SRC_BSP_BSP_H_

#include "def.h"


#include "A33G52x.h"
#include "a33g52x_gpio.h"
#include "a33g52x_pcu.h"
#include "a33g52x_nvic.h"
#include "a33g52x_uart.h"
#include "a33g52x_flash.h"


bool bspInit(void);

void delay(uint32_t ms);
uint32_t millis(void);


void logPrintf(const char *fmt, ...);

#endif /* SRC_BSP_BSP_H_ */
