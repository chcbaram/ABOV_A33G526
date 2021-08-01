/**********************************************************************
* @file		debug_frmwrk.c
* @brief	Contains some utilities that used for debugging through UART
* @version	2.0
* @date: 	2020-01-08
* @author	BC Lee
*
* Copyright(C) 2017-2020, ABOV Semiconductor. All rights reserved.
**********************************************************************/

#ifndef _DEBUG_FRMWRK_
#define _DEBUG_FRMWRK_

/* Includes ------------------------------------------------------------------- */
#include "debug_frmwrk.h"
#include "A33G52x_pcu.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Debug framework */

/*********************************************************************//**
 * @brief		Initialize Debug frame work through initializing UART port
 * @param[in]	None
 * @return		None
 **********************************************************************/

#define	DEBUG_TX_SIZE	64
#define	DEBUG_RX_SIZE	64
static uint8_t	_debug_buffer[DEBUG_RX_SIZE + DEBUG_TX_SIZE];

#if (DEBUG_PORT_NUMBER == 0 || DEBUG_PORT_NUMBER == 1)
void 	debug_frmwrk_init_uart(void)
{
	UART_CFG_Type UARTConfigStruct;

#ifdef A33G52x
#if (DEBUG_PORT_NUMBER == 0)
	/*
	 * Initialize UART0 pin connect
	 */
	PCU_SetDirection(PCC, PIN_8, LOGIC_INPUT);
	PCU_ConfigureFunction(PCC, PIN_8, PC8_MUX_RXD0);
	PCU_ConfigurePullupdown(PCC, PIN_8, PULLUP_ENABLE);

	PCU_SetDirection(PCC, PIN_9, PUSHPULL_OUTPUT);
	PCU_ConfigureFunction(PCC, PIN_9, PC9_MUX_TXD0);

#elif (DEBUG_PORT_NUMBER == 1)
	/*
	 * Initialize UART1 pin connect
	 */
	PCU_SetDirection(PCD, PIN_12, LOGIC_INPUT);
	PCU_ConfigureFunction(PCD, PIN_12, PD12_MUX_RXD1);
	PCU_ConfigurePullupdown(PCD, PIN_12, PULLUP_ENABLE);

	PCU_SetDirection(PCD, PIN_13, PUSHPULL_OUTPUT);
	PCU_ConfigureFunction(PCD, PIN_13, PD13_MUX_TXD1);

#elif (DEBUG_PORT_NUMBER == 2)
	/*
	 * Initialize UART1 pin connect
	 */
	PCU_SetDirection(PCC, PIN_10, LOGIC_INPUT);
	PCU_ConfigureFunction(PCC, PIN_10, PC10_MUX_RXD2);
	PCU_ConfigurePullupdown(PCC, PIN_10, PULLUP_ENABLE);

	PCU_SetDirection(PCC, PIN_11, PUSHPULL_OUTPUT);
	PCU_ConfigureFunction(PCC, PIN_11, PC11_MUX_TXD2);

#elif (DEBUG_PORT_NUMBER == 3)
	/*
	 * Initialize UART1 pin connect
	 */
	PCU_SetDirection(PCE, PIN_6, LOGIC_INPUT);
	PCU_ConfigureFunction(PCE, PIN_6, PE6_MUX_RXD3);
	PCU_ConfigurePullupdown(PCE, PIN_6, PULLUP_ENABLE);

	PCU_SetDirection(PCE, PIN_7, PUSHPULL_OUTPUT);
	PCU_ConfigureFunction(PCE, PIN_7, PE7_MUX_TXD3);

#endif
#else
#if (DEBUG_PORT_NUMBER == 0)
	/*
	 * Initialize UART0 pin connect
	 */
	PCU_SetDirection(PB, 5, ALTERN_FUNC);
	PCU_ConfigureFunction(PB, 5, FUNC1);
	PCU_ConfigurePullupdown(PB, 5, ENPU);

	PCU_SetDirection(PB, 4, ALTERN_FUNC);		
	PCU_ConfigureFunction(PB, 4, FUNC1);

	PCU_SetDirection(PCD, PIN_2, PUSHPULL_OUTPUT);
	PCU_ConfigurePullupdown(PBD, PIN_2, PUPD_DISABLE);

#elif (DEBUG_PORT_NUMBER == 1)
	/*
	 * Initialize UART1 pin connect
	 */
	PCU_SetDirection(PB, 7, ALTERN_FUNC);
	PCU_ConfigureFunction(PB, 7, FUNC1);
	PCU_ConfigurePullupdown(PB, 7, ENPU);
	
	PCU_SetDirection(PB, 6, ALTERN_FUNC);
	PCU_ConfigureFunction(PB, 6, FUNC1);
	
#endif
#endif

	/* Initialize UART Configuration parameter structure to default state:
	 * Baudrate = 38400bps
	 * 8 data bit
	 * 1 Stop bit
	 * None parity
	 */
	UART_ConfigStructInit(&UARTConfigStruct);
	UARTConfigStruct.Baud_rate = 38400;
	UARTConfigStruct.RxTxBuffer = _debug_buffer;
	UARTConfigStruct.RxBufferSize = DEBUG_RX_SIZE;
	UARTConfigStruct.TxBufferSize = DEBUG_TX_SIZE;
	
	// Initialize DEBUG_UART_PORT peripheral with given to corresponding parameter
	UART_Init((UART_Type*)DEBUG_PORT, &UARTConfigStruct);
}
#endif

#if (DEBUG_PORT_NUMBER == 10 || DEBUG_PORT_NUMBER == 11 || DEBUG_PORT_NUMBER == 12 || DEBUG_PORT_NUMBER == 13)
void 	debug_frmwrk_init_usart(void)
{
	UST_CFG_Type UST_InitStruct;

#if (DEBUG_PORT_NUMBER == 10)
	/*
	 * Initialize USART10 pin connect
	 */
	PCU_SetDirection(PB, 1, ALTERN_FUNC);
	PCU_ConfigureFunction(PB, 1, FUNC1);
	PCU_ConfigurePullupdown(PB, 1, ENPU);

	PCU_SetDirection(PB, 0, ALTERN_FUNC);
	PCU_ConfigureFunction(PB, 0, FUNC1);

#elif (DEBUG_PORT_NUMBER == 11)
	/*
	 * Initialize USART11 pin connect
	 */
	PCU_SetDirection(PD, 3, ALTERN_FUNC);
	PCU_ConfigureFunction(PD, 3, FUNC1);
	PCU_ConfigurePullupdown(PD, 3, ENPU);

	PCU_SetDirection(PD, 2, ALTERN_FUNC);
	PCU_ConfigureFunction(PD, 2, FUNC1);

#elif (DEBUG_PORT_NUMBER == 12)
	/*
	 * Initialize USART12 pin connect
	 */
	PCU_SetDirection(PE, 13, ALTERN_FUNC);
	PCU_ConfigureFunction(PE, 13, FUNC1);
	PCU_ConfigurePullupdown(PE, 13, ENPU);

	PCU_SetDirection(PE, 12, ALTERN_FUNC);
	PCU_ConfigureFunction(PE, 12, FUNC1);

#elif (DEBUG_PORT_NUMBER == 13)
	/*
	 * Initialize USART13 pin connect
	 */
	PCU_SetDirection(PE, 9, ALTERN_FUNC);
	PCU_ConfigureFunction(PE, 9, FUNC1);
	PCU_ConfigurePullupdown(PE, 9, ENPU);

	PCU_SetDirection(PE, 8, ALTERN_FUNC);
	PCU_ConfigureFunction(PE, 8, FUNC1);

#endif

	/* Initialize UART Configuration parameter structure to default state:
	 * Baudrate = 38400bps
	 * 8 data bit
	 * 1 Stop bit
	 * None parity
	 */
	UST_UART_Mode_ConfigStructInit(&UST_InitStruct);
	UST_InitStruct.Baud_rate = 38400;
	UST_InitStruct.RxTxBuffer = _debug_buffer;
	UST_InitStruct.RxBufferSize = DEBUG_RX_SIZE;
	UST_InitStruct.TxBufferSize = DEBUG_TX_SIZE;

	// Initialize DEBUG_UART_PORT peripheral with given to corresponding parameter
	UST_Init(DEBUG_PORT, &UST_InitStruct);
}
#endif

void 	debug_frmwrk_init(void)
{
#if (DEBUG_PORT_NUMBER == 0 || DEBUG_PORT_NUMBER == 1)
	debug_frmwrk_init_uart();
#elif (DEBUG_PORT_NUMBER == 10 || DEBUG_PORT_NUMBER == 11 || DEBUG_PORT_NUMBER == 12 || DEBUG_PORT_NUMBER == 13)
	debug_frmwrk_init_usart();
#endif
}


void	_DBG(const char *msg)
{
#if (DEBUG_PORT_NUMBER == 0 || DEBUG_PORT_NUMBER == 1)
	uputs(DEBUG_PORT, (void*)msg);
#elif (DEBUG_PORT_NUMBER == 10 || DEBUG_PORT_NUMBER == 11 || DEBUG_PORT_NUMBER == 12 || DEBUG_PORT_NUMBER == 13)
	usputs(DEBUG_PORT, (void*)msg);
#endif
}

#if (DEBUG_PORT_NUMBER == 0 || DEBUG_PORT_NUMBER == 1)
int32_t	cgetc(void)		{	return ugetc(DEBUG_PORT);		}
int32_t	cgetchar(void)	{	return ugetchar(DEBUG_PORT);	}
int32_t	cgets(char *strin, int32_t maxsize)	{	return ugets(DEBUG_PORT, strin, maxsize);	}
void	cputc(char ch)	{	uputc(DEBUG_PORT, ch);	}
int32_t	cputs(char *strin)	{	return uputs(DEBUG_PORT, strin);	}
int32_t	cwrite(void *p,int size)	{	return uwrite(DEBUG_PORT, p, size);	}
int32_t	cread(void *p,int size)		{	return uread(DEBUG_PORT, p, size);		}
void	cflush(void)	{	uflush(DEBUG_PORT);		}

#elif (DEBUG_PORT_NUMBER == 10 || DEBUG_PORT_NUMBER == 11 || DEBUG_PORT_NUMBER == 12 || DEBUG_PORT_NUMBER == 13)
int32_t	cgetc(void)		{	return usgetc(DEBUG_PORT);		}
int32_t	cgetchar(void)	{	return usgetchar(DEBUG_PORT);	}
int32_t	cgets(char *strin, int32_t maxsize)	{	return usgets(DEBUG_PORT, strin, maxsize);	}
void	cputc(char ch)	{	usputc(DEBUG_PORT, (uint8_t)ch);	}
int32_t	cputs(char *strin)	{	return usputs(DEBUG_PORT, strin);	}
int32_t	cwrite(void *p,int size)	{	return uswrite(DEBUG_PORT, p, size);	}
int32_t	cread(void *p,int size)		{	return usread(DEBUG_PORT, p, size);		}
void	cflush(void)	{	usflush(DEBUG_PORT);		}

#endif

#define	OS_INTEGER_DEBUG_PRINTF_TMP_ARRAY_SIZE	128

int32_t cprintf(const char* format, ...)
{
  int ret;
  va_list ap;
  static char buf[OS_INTEGER_DEBUG_PRINTF_TMP_ARRAY_SIZE];
    
  va_start (ap, format);

  // TODO: rewrite it to no longer use newlib, it is way too heavy


  // Print to the local buffer
  ret = vsnprintf (buf, sizeof(buf), format, ap);
  if (ret > 0)
    {
      // Transfer the buffer to the device
      cwrite(buf, (size_t)ret);
    }

  va_end (ap);
  return ret;
}

/**************************************************************************
 *
 *	Debug
 *		type: 	0=Executable, 1=Byte, 2=Short, 4=Int32(Long), (bit-16 = 1) = string
 *				-1=end-of-table.
 *		name: command name string
 *		variable:	variable ptr or function ptr to execute.
 *		arguement:	function arguement when the variable is a function.
 *
 **************************************************************************/
#define MAX_DBG_CMD_LIST	255
#define	MAX_DBG_CMD_CHAR	64

static	int32_t	_cmd_line_size;
static	char	_cmd_line[MAX_DBG_CMD_CHAR];

extern	DEBUG_VARIABLES dbg_variables[];

DEBUG_VARIABLES	*dbg_find_table(char *name)
{
	DEBUG_VARIABLES	*p;
	int	i;

	for(i = 0; i < MAX_DBG_CMD_LIST; i++) {
		p = &dbg_variables[i];
		if (p->type < 0) {
			break;
		}
		if (strcmp(name, p->name) == 0) {
			return p;
		}
	}
	return NULL;
}

int32_t	dbg_print_value(char *name)
{
	DEBUG_VARIABLES	*p;

	p = dbg_find_table(name);
	if (p != NULL) {
		if (p->type < 0) {
			;
		} else {
			switch (p->type) {
			default:	cputs(" Not supported format.");
			case 0:	//executable
					cputs(" - Not available.");
					break;
			case 1:	//byte
					cprintf(" %s = %d, 0x%02X ('%c')", name, *((int8_t*)p->variable), *((uint8_t*)p->variable), *((uint8_t*)p->variable) );
					break;
			case 2:	//byte
					cprintf(" %s = %d (0x%04X)", name, *((int16_t*)p->variable),*((uint16_t*)p->variable) );
					break;
			case 4:	//byte
					cprintf(" %s = %d (0x%08X)", name, *((int32_t*)p->variable),*((uint32_t*)p->variable) );
					break;
			}
		}
	} else {
		cputs(" - command not found.");
	}
	//cputs("\r\n");
	return 0;
}

uint32_t	datol(char *a)
{
	int			i;
	uint32_t	value;

	i = 0;
	value = 0;
	if (a[0] == '0' && a[1] == 'x') {
		for (i = 2; i < 10; i++) {
			uint32_t	t;
			t = a[i];
			if (t >= '0' && t <= '9') {
				value <<= 4;
				value += t - '0';
			} else if (t >= 'a' && t <='f') {
				value <<= 4;
				value += t - 'a' + 10;
			} else if (t >= 'A' && t <='F') {
				value <<= 4;
				value += t - 'A' + 10;
			} else break;
		}
	} else {
		int sign = 0;
		if (a[0] == '-') {
			sign = 1;
		}
		for (i = sign; i < 16; i++) {
			uint32_t	t;
			t = a[i];
			if (t >= '0' && t <= '9') {
				value *= 10;
				value += t - '0';
			} else break;
		}
		if (sign)
			value = (uint32_t)(-(int32_t)value);
	}
	return value;
}

int32_t	dbg_set_value(char *name, char *pvalue)
{
	DEBUG_VARIABLES	*p;

	p = dbg_find_table(name);
	if (p != NULL) {
		if (p->type < 0) {
			;
		} else {
			switch (p->type) {
			default:	cputs(" Not supported format.");
			case 0:	//executable
					cputs(" - Not available.");
					break;
			case 1:	//byte
					*((uint8_t*)p->variable) = datol(pvalue);
					break;
			case 2:	//short
					*((uint16_t*)p->variable) = datol(pvalue);
					break;
			case 4:	//long
					*((uint32_t*)p->variable) = datol(pvalue);
					break;
			}
		}
	} else {
		cputs(" - command not found.");
	}
	//cputs("\r\n");
	return 0;
}

int32_t	dbg_run_value(char *name, char *cmd)
{
	int32_t	result = 0;
	DEBUG_VARIABLES	*p;

	p = dbg_find_table(name);
	if (p != NULL) {
		if (p->type < 0) {
			;
		} else if (p->type == 0) {
 			int32_t	(*exec)(int32_t);
			*(void**)&exec = p->variable;
			(*exec)(p->arguement);
		} else {
			cputs(" - Not available.");
		}
	} else if (name[0] == 0) {
		;
	} else {
		extern	int cmd_run(char *cmd);
		//cputs(" - command not found.");
		cmd_run(cmd);
	}
	//cputs("\r\n");
	return result;
}

int32_t	dbg_execute(char *cmd)
{
	char	ch;
	int		size;
	char	varname[16];
	char	*p = cmd;

	while (*p == ' ') p++;

	if (p[0] == 0) {
		return 0;
	}

	cputs("\r\n");

	size = 0;
	while (1) {
		ch = *p++;
		if (ch == ' ') {
			break;
		}
		if (ch == '?' || ch == '=' || ch == '\r' || ch == '\n' || ch == 0) {
			break;
		}
		varname[size++] = ch;
	}
	varname[size++] = 0;

	if (ch == ' ') {
		while ((ch = *p++) == ' ');
	}

	if (ch == '?') {
		dbg_print_value(varname);
	} else if (ch == '=') {
		while (*p == ' ') p++;
		dbg_set_value(varname, p);
	} else {
		dbg_run_value(varname, cmd);
	}

	return 1;
}

void	_dbg_init(void)
{
	_cmd_line_size = 0;
	memset((void*)_cmd_line,0,sizeof(_cmd_line));
	cputs("\r\n*");
}

int32_t	dbg_console_check(void)
{
	int result = 0;
	int	ch;

	ch = cgetchar();
	if (ch >= 0) {
		if (ch == 8) {
			if (_cmd_line_size > 0) {
				cputc(ch);
				_cmd_line_size--;
			}
		} else if (ch == '\n') {

		} else if (ch == '\r') {
			//cputs("\n");
			_cmd_line[_cmd_line_size++] = 0;
			result = dbg_execute(_cmd_line);
			_dbg_init();
		} else {
			cputc(ch);
			_cmd_line[_cmd_line_size++] = ch;
		}
	}
	return result;
}



#endif /* _DEBUG_FRMWRK_ */

/* --------------------------------- End Of File ------------------------------ */
