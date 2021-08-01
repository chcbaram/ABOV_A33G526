/*
 * ap.c
 *
 *  Created on: 2021. 7. 26.
 *      Author: baram
 */


#include "ap.h"





void apInit(void)
{

}

void apMain(void)
{
  uint32_t pre_time;

  pre_time = millis();
  while(1)
  {
    if (millis()-pre_time >= 500)
    {
      pre_time = millis();
      ledToggle(_DEF_LED1);
      ledToggle(_DEF_LED2);
      ledToggle(_DEF_LED3);
      ledToggle(_DEF_LED4);
      ledToggle(_DEF_LED5);
    }

    if (uartAvailable(_DEF_UART1) > 0)
    {
      uint8_t rx_data;

      rx_data = uartRead(_DEF_UART1);

      logPrintf("rx : 0x%X\n", rx_data);
    }
  }
}
