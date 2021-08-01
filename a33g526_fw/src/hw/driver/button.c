/*
 * button.c
 *
 *  Created on: 2021. 8. 1.
 *      Author: baram
 */


#include "button.h"
#include "cli.h"


#ifdef _USE_HW_BUTTON


typedef struct
{
  PCU_Type     *pcu;
  GPIO_Type    *port;
  uint32_t      pin;
  uint32_t      func;
  uint8_t       on_state;
} button_tbl_t;


button_tbl_t button_tbl[BUTTON_MAX_CH] =
    {
        {PCB, PB, PIN_1, PB1_MUX_PB1, _DEF_LOW},
    };


#ifdef _USE_HW_CLI
static void cliButton(cli_args_t *args);
#endif


bool buttonInit(void)
{
  bool ret = true;





  for (int i=0; i<BUTTON_MAX_CH; i++)
  {
    PCU_ConfigureFunction(button_tbl[i].pcu, button_tbl[i].pin, button_tbl[i].func);
    PCU_SetDirection(button_tbl[i].pcu, button_tbl[i].pin, LOGIC_INPUT);
    PCU_ConfigurePullupdown(button_tbl[i].pcu, button_tbl[i].pin, PUPD_DISABLE);
  }

#ifdef _USE_HW_CLI
  cliAdd("button", cliButton);
#endif

  return ret;
}

bool buttonGetPressed(uint8_t ch)
{
  bool ret = false;
  uint16_t port_value;
  uint8_t  pin_state;

  if (ch >= BUTTON_MAX_CH)
  {
    return false;
  }

  port_value = GPIO_ReadValue(button_tbl[ch].port);
  if (port_value & (1<<button_tbl[ch].pin))
  {
    pin_state = _DEF_HIGH;
  }
  else
  {
    pin_state = _DEF_LOW;
  }


  if (pin_state == button_tbl[ch].on_state)
  {
    ret = true;
  }

  return ret;
}

void buttonObjCreate(button_obj_t *p_obj, uint8_t ch, uint32_t repeat_time)
{
  p_obj->ch = ch;
  p_obj->state = 0;
  p_obj->pre_time = millis();
  p_obj->repeat_time = repeat_time;
}

bool buttonObjGetClicked(button_obj_t *p_obj, uint32_t pressed_time)
{
  bool ret = false;


  switch(p_obj->state)
  {
    case 0:
      if (buttonGetPressed(p_obj->ch) == true)
      {
        p_obj->state = 1;
        p_obj->pre_time = millis();
      }
      break;

    case 1:
      if (buttonGetPressed(p_obj->ch) == true)
      {
        if (millis()-p_obj->pre_time >= pressed_time)
        {
          ret = true; // 버튼 클릭됨
          p_obj->state = 2;
          p_obj->pre_time = millis();
        }
      }
      else
      {
        p_obj->state = 0;
      }
      break;

    case 2:
      if (buttonGetPressed(p_obj->ch) == true)
      {
        if (millis()-p_obj->pre_time >= p_obj->repeat_time)
        {
          p_obj->state = 1;
          p_obj->pre_time = millis();
        }
      }
      else
      {
        p_obj->state = 0;
      }
      break;
  }

  return ret;
}


#ifdef _USE_HW_CLI

void cliButton(cli_args_t *args)
{
  bool ret = false;


  if (args->argc == 1 && args->isStr(0, "show"))
  {
    while(cliKeepLoop())
    {
      for (int i=0; i<BUTTON_MAX_CH; i++)
      {
        cliPrintf("%d", buttonGetPressed(i));
      }
      cliPrintf("\n");

      delay(100);
    }

    ret = true;
  }


  if (ret != true)
  {
    cliPrintf("button show\n");
  }
}
#endif



#endif
