/*
 * hw.c
 *
 *  Created on: 2021. 7. 26.
 *      Author: baram
 */


#include "hw.h"


__attribute__((section(".version"))) firm_version_t boot_ver =
    {
        _DEF_FIRMWATRE_VERSION,
        _DEF_BOARD_NAME
    };


bool hwInit(void)
{
  bspInit();

  logInit();
  ledInit();
  buttonInit();
  uartInit();
  uartOpen(_DEF_UART1, 115200);

  logPrintf("[ Bootloader Begin... ]\r\n");
  logPrintf("Booting..Name \t\t: %s\r\n", _DEF_BOARD_NAME);
  logPrintf("Booting..Ver  \t\t: %s\r\n", _DEF_FIRMWATRE_VERSION);

  flashInit();

  return true;
}
