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

      if (rx_data == 'm')
      {
        logPrintf("m menu\n");
        logPrintf("e erase\n");
        logPrintf("w write\n");
        logPrintf("s show\n");
      }

      if (rx_data == 'e')
      {
        logPrintf("erase..");
        flashErase(0x00000000, 256);
        logPrintf("OK\n");
      }

      if (rx_data == 'w')
      {
        uint8_t w_data[256];

        for (int i=0; i<256; i++)
        {
          w_data[i] = i;
        }

        logPrintf("write..");
        flashWrite(0x00000000, w_data, 256);
        logPrintf("OK\n");
      }

      if (rx_data == 's')
      {
        uint8_t r_data[256];


        flashRead(0, r_data, 256);

        for (int i=0; i<256; i++)
        {
          logPrintf("%d : %d\n", i, r_data[i]);
        }
      }
    }
  }
}
