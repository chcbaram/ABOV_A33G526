/*
 * uart.c
 *
 *  Created on: 2021. 7. 31.
 *      Author: baram
 */


#include "uart.h"
#include "qbuffer.h"


#ifdef _USE_HW_UART



#define UART_RX_BUF_LENGTH      1024


typedef enum
{
  UART_HW_TYPE_MCU,
  UART_HW_TYPE_USB,
} UartHwType_t;


typedef struct
{
  bool     is_open;
  uint32_t baud;
  UartHwType_t type;


  uint8_t  rx_buf[UART_RX_BUF_LENGTH];
  qbuffer_t qbuffer;
  UART_Type *p_huart;
  UART_CFG_Type uart_init;
} uart_tbl_t;


static uart_tbl_t uart_tbl[UART_MAX_CH];





bool uartInit(void)
{
  for (int i=0; i<UART_MAX_CH; i++)
  {
    uart_tbl[i].is_open = false;
    uart_tbl[i].baud = 57600;
  }

  return true;
}

bool uartOpen(uint8_t ch, uint32_t baud)
{
  bool ret = false;


  switch(ch)
  {
    case _DEF_UART1:
      uart_tbl[ch].type    = UART_HW_TYPE_MCU;
      uart_tbl[ch].baud    = baud;

      uart_tbl[ch].p_huart                = UART0;
      uart_tbl[ch].uart_init.Baud_rate    = baud;
      uart_tbl[ch].uart_init.Databits     = UART_DATABIT_8;
      uart_tbl[ch].uart_init.Parity       = UART_PARITY_NONE;
      uart_tbl[ch].uart_init.Stopbits     = UART_STOPBIT_1;
      uart_tbl[ch].uart_init.RxTxBuffer   = NULL;
      uart_tbl[ch].uart_init.RxBufferSize = 0;
      uart_tbl[ch].uart_init.TxBufferSize = 0;


      qbufferCreate(&uart_tbl[ch].qbuffer, uart_tbl[ch].rx_buf, UART_RX_BUF_LENGTH);

      PCU_SetDirection(PCC, PIN_8, LOGIC_INPUT);
      PCU_ConfigureFunction(PCC, PIN_8, PC8_MUX_RXD0);
      PCU_ConfigurePullupdown(PCC, PIN_8, PULLUP_ENABLE);

      PCU_SetDirection(PCC, PIN_9, PUSHPULL_OUTPUT);
      PCU_ConfigureFunction(PCC, PIN_9, PC9_MUX_TXD0);


      UART_Init(uart_tbl[ch].p_huart, &uart_tbl[ch].uart_init);

      uart_tbl[ch].p_huart->IER = UART_IER_DRIE;

      NVIC_SetPriority(UART0_IRQn, 5);
      NVIC_EnableIRQ(UART0_IRQn);

      uart_tbl[ch].is_open = true;


      ret = true;
      break;
  }

  return ret;
}

bool uartClose(uint8_t ch)
{
  return true;
}

uint32_t uartAvailable(uint8_t ch)
{
  uint32_t ret = 0;

  switch(ch)
  {
    case _DEF_UART1:
      ret = qbufferAvailable(&uart_tbl[ch].qbuffer);
      break;
  }

  return ret;
}

bool uartFlush(uint8_t ch)
{
  uint32_t pre_time;

  pre_time = millis();
  while(uartAvailable(ch))
  {
    if (millis()-pre_time >= 10)
    {
      break;
    }
    uartRead(ch);
  }

  return true;
}

uint8_t uartRead(uint8_t ch)
{
  uint8_t ret = 0;

  switch(ch)
  {
    case _DEF_UART1:
      qbufferRead(&uart_tbl[ch].qbuffer, &ret, 1);
      break;
  }

  return ret;
}

uint32_t uartWrite(uint8_t ch, uint8_t *p_data, uint32_t length)
{
  uint32_t ret = 0;

  switch(ch)
  {
    case _DEF_UART1:
      ret = (uint32_t)uwrite(uart_tbl[ch].p_huart, (void *)p_data, (int)length);
      break;
  }

  return ret;
}

uint32_t uartPrintf(uint8_t ch, const char *fmt, ...)
{
  char buf[256];
  va_list args;
  int len;
  uint32_t ret;

  va_start(args, fmt);
  len = vsnprintf(buf, 256, fmt, args);

  ret = uartWrite(ch, (uint8_t *)buf, len);

  va_end(args);


  return ret;
}

uint32_t uartGetBaud(uint8_t ch)
{
  uint32_t ret = 0;


  switch(ch)
  {
    case _DEF_UART1:
      ret = uart_tbl[ch].baud;
      break;
  }

  return ret;
}





void UART_0_Handler(void)
{
  uart_tbl_t *p_uart = &uart_tbl[_DEF_UART1];
  uint32_t iir_reg;
  uint32_t isr_id;

  iir_reg = p_uart->p_huart->IIR;
  isr_id  = iir_reg & 0x07;

  if (isr_id == 0x04)
  {
    uint8_t read_data;

    read_data = p_uart->p_huart->RBR;
    qbufferWrite(&p_uart->qbuffer, &read_data, 1);
  }
  return;
}


#endif
