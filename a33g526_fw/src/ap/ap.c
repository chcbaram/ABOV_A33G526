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
  while(1)
  {
    ledToggle(_DEF_LED1);
    ledToggle(_DEF_LED2);
    ledToggle(_DEF_LED3);
    ledToggle(_DEF_LED4);
    ledToggle(_DEF_LED5);
    delay(500);
  }
}
