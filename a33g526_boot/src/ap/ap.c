/*
 * ap.c
 *
 *  Created on: 2021. 7. 26.
 *      Author: baram
 */


#include "ap.h"
#include "boot/boot.h"



cmd_t cmd;





void apInit(void)
{
  if (buttonGetPressed(_DEF_BUTTON1) == false)
  {
    if (bootVerifyFw() == true && bootVerifyCrc() == true)
    {
      bootJumpToFw();
    }
  }

  cmdInit(&cmd);
  cmdOpen(&cmd, _DEF_UART1, 115200);
}

void apMain(void)
{
  uint32_t pre_time;


  pre_time = millis();
  while(1)
  {
    if (millis()-pre_time >= 100)
    {
      pre_time = millis();
      ledToggle(_DEF_LED1);
    }

    if (cmdReceivePacket(&cmd) == true)
    {
      bootProcessCmd(&cmd);
    }
  }
}
