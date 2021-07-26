/**********************************************************************
* @file		debug_frmwrk.h
* @brief	Contains some utilities that used for debugging through UART or USART in UART mode
* @version	1.2
* @date: 	2020-03-19
* @author	BC Lee
*
* Copyright(C) 2020, ABOV Semiconductor. All rights reserved.
**********************************************************************/

#ifndef _DEBUG_FRMWRK_H_
#define _DEBUG_FRMWRK_H_

/* Includes ------------------------------------------------------------------- */
#include "A33G52x_uart.h"

#define DEBUG_PORT_NUMBER	0

#if (DEBUG_PORT_NUMBER == 0)
#define DEBUG_PORT	UART0
#elif (DEBUG_PORT_NUMBER == 1)
#define DEBUG_PORT	UART1
#elif (DEBUG_PORT_NUMBER == 2)
#define DEBUG_PORT	UART2
#elif (DEBUG_PORT_NUMBER == 3)
#define DEBUG_PORT	UART3
#endif


int32_t	cgetc(void);
int32_t	cgetchar(void);
int32_t	cgets(char *strin, int32_t maxsize);
void	cputc(char ch);
int32_t	cputs(char *strin);
void	cflush(void);
int32_t	cwrite(void *p,int size);
int32_t	cread(void *p,int size);
int32_t	cprintf(const  char *format, ...);

void 	debug_frmwrk_init(void);
void	_dbg_init(void);
int32_t	dbg_console_check(void);
void	_DBG(const char *msg);



typedef struct {
	int32_t		type;
	char		*name;
	void		*variable;
	int32_t		arguement;
} DEBUG_VARIABLES;


#endif /* _DEBUG_FRMWRK_H_ */

/* --------------------------------- End Of File ------------------------------ */
