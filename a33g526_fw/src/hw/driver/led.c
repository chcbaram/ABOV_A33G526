/*
 * led.c
 *
 *  Created on: 2021. 7. 26.
 *      Author: baram
 */


#include "led.h"


typedef struct
{
  PCU_Type  *pcu;
  GPIO_Type *port;
  uint32_t   pin;
  uint32_t   func;
  uint8_t    on_state;
  uint8_t    off_state;
} led_tbl_t;



static const led_tbl_t led_tbl[LED_MAX_CH] =
    {
        {PCD, PD, PIN_0, PD0_MUX_PD0, _DEF_HIGH, _DEF_LOW},
        {PCD, PD, PIN_1, PD1_MUX_PD1, _DEF_HIGH, _DEF_LOW},
        {PCD, PD, PIN_2, PD2_MUX_PD2, _DEF_HIGH, _DEF_LOW},
        {PCD, PD, PIN_3, PD3_MUX_PD3, _DEF_HIGH, _DEF_LOW},
        {PCD, PD, PIN_4, PD4_MUX_PD4, _DEF_HIGH, _DEF_LOW},
        {PCD, PD, PIN_5, PD5_MUX_PD5, _DEF_HIGH, _DEF_LOW},
    };




bool ledInit(void)
{

  for (int i=0; i<LED_MAX_CH; i++)
  {
    PCU_ConfigureFunction(led_tbl[i].pcu, led_tbl[i].pin, led_tbl[i].func);
    PCU_SetDirection(led_tbl[i].pcu, led_tbl[i].pin, PUSHPULL_OUTPUT);
    PCU_ConfigurePullupdown(led_tbl[i].pcu, led_tbl[i].pin, PUPD_DISABLE);

    ledOff(i);
  }

  return true;
}

void ledOn(uint8_t ch)
{
  if (ch >= LED_MAX_CH) return;


  if (led_tbl[ch].on_state == _DEF_HIGH)
  {
    GPIO_OutputHigh(led_tbl[ch].port, led_tbl[ch].pin);
  }
  else
  {
    GPIO_OutputLow(led_tbl[ch].port, led_tbl[ch].pin);
  }
}

void ledOff(uint8_t ch)
{
  if (ch >= LED_MAX_CH) return;


  if (led_tbl[ch].off_state == _DEF_HIGH)
  {
    GPIO_OutputHigh(led_tbl[ch].port, led_tbl[ch].pin);
  }
  else
  {
    GPIO_OutputLow(led_tbl[ch].port, led_tbl[ch].pin);
  }
}

void ledToggle(uint8_t ch)
{
  uint16_t pin_value;


  if (ch >= LED_MAX_CH) return;


  pin_value = GPIO_ReadValue (led_tbl[ch].port);

  if (pin_value & (1<<led_tbl[ch].pin))
  {
    GPIO_OutputLow(led_tbl[ch].port, led_tbl[ch].pin);
  }
  else
  {
    GPIO_OutputHigh(led_tbl[ch].port, led_tbl[ch].pin);
  }
}
