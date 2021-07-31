/*
 * hw.c
 *
 *  Created on: 2021. 7. 26.
 *      Author: baram
 */


#include "hw.h"





bool hwInit(void)
{
  bspInit();

  logInit();
  ledInit();
  uartInit();
  uartOpen(_DEF_UART1, 57600);

  return true;
}
