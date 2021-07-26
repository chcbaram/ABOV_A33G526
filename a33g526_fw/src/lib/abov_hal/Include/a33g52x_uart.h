/**********************************************************************
* @file		A33G52x_uart.h
* @brief	Contains all macro definitions and function prototypes
* 			support for UART firmware library on A31L12x
* @version	1.0.10
* @date: 	2020-11-16
* @author	BC Lee, AE TEAM
*
* Copyright(C) 2017-2020, ABOV Semiconductor. All rights reserved.
**********************************************************************/

#ifndef _UART_H_
#define _UART_H_

/* Includes ------------------------------------------------------------------- */
#include <stdio.h>
#include <stdarg.h>
#include "A33G52x.h"
//#include "def.h"
#include "aa_types.h"


#ifdef __cplusplus
extern "C"
{
#endif

/** UART time-out definitions in case of using Read() and Write function
 * with Blocking Flag mode
 */
#define UART_BLOCKING_TIMEOUT			(0xFFFFFFFFUL)

/* Private Macros ------------------------------------------------------------- */

/* --------------------- BIT DEFINITIONS -------------------------------------- */
/**********************************************************************
 * Macro defines for Macro defines for UART interrupt enable register
 **********************************************************************/
#define UART_IER_DRIE			((uint8_t)(1<<0)) 	/*!< RBR Interrupt enable*/
#define UART_IER_THREIE			((uint8_t)(1<<1)) 	/*!< THR Interrupt enable*/
#define UART_IER_RLSIE			((uint8_t)(1<<2)) 	/*!< RX line status interrupt enable*/
#define UART_IER_TEMTIE			((uint8_t)(1<<3)) 	/*!< TXE interrupt enable */
#define UART_IER_BITMASK		((uint8_t)(0x0F)) /*!< UART interrupt enable register bit mask */

/**********************************************************************
 * Macro defines for Macro defines for UART interrupt identification register
 **********************************************************************/
#define UART_IIR_INTSTAT_PEND	((uint8_t)(1<<0))	/*!<Interrupt Status - Active low */
#define UART_IIR_INTID_RLS		((uint8_t)(3<<1)) 	/*!<Interrupt identification: Receive line status*/
#define UART_IIR_INTID_RDA		((uint8_t)(2<<1)) 	/*!<Interrupt identification: Receive data available*/
#define UART_IIR_INTID_THRE		((uint8_t)(1<<1)) 	/*!<Interrupt identification: THRE interrupt*/
#define UART_IIR_INTID_TXE		((uint8_t)(1<<4)) 	/*!<Interrupt identification: TXE interrupt*/
#define UART_IIR_INTID_MASK		((uint8_t)(7<<1))	/*!<Interrupt identification: Interrupt ID mask */
#define UART_IIR_BITMASK		((uint8_t)(0x1F))	/*!< UART interrupt identification register bit mask */

/**********************************************************************
 * Macro defines for Macro defines for UART line control register
 **********************************************************************/
#define UART_LCR_WLEN5     		((uint8_t)(0))   		/*!< UART 5 bit data mode */
#define UART_LCR_WLEN6     		((uint8_t)(1<<0))   	/*!< UART 6 bit data mode */
#define UART_LCR_WLEN7     		((uint8_t)(2<<0))   	/*!< UART 7 bit data mode */
#define UART_LCR_WLEN8     		((uint8_t)(3<<0))   	/*!< UART 8 bit data mode */
#define UART_LCR_STOPBIT_SEL	((uint8_t)(1<<2))   	/*!< UART Two Stop Bits Select */
#define UART_LCR_PARITY_EN		((uint8_t)(1<<3))		/*!< UART Parity Enable */
#define UART_LCR_PARITY_ODD		((uint8_t)(0<<4))       	/*!< UART Odd Parity Select */
#define UART_LCR_PARITY_EVEN	((uint8_t)(1<<4))		/*!< UART Even Parity Select */
#define UART_LCR_PARITY_F_1		((uint8_t)(2<<4))		/*!< UART force 1 stick parity */
#define UART_LCR_PARITY_F_0		((uint8_t)(3<<4))		/*!< UART force 0 stick parity */
#define UART_LCR_BREAK_EN		((uint8_t)(1<<6))		/*!< UART Transmission Break enable */
#define UART_LCR_BITMASK		((uint8_t)(0x7F))		/*!< UART line control bit mask */

/**********************************************************************
 * Macro defines for Macro defines for UART data control register
 **********************************************************************/
#define UART_DCR_TXINV		((uint8_t)(1<<2)) 	/*!<data control register: Tx Data Inversion*/
#define UART_DCR_RXINV		((uint8_t)(1<<3)) 	/*!<data control register: Rx Data Inversion*/
#define UART_DCR_LBON		((uint8_t)(1<<4)) 	/*!<data control register: Local loopback test mode*/
#define UART_DCR_BITMASK	((uint8_t)(0x7<<2)) 	/*!<UART data control bit mask */

/**********************************************************************
 * Macro defines for Macro defines for UART line status register
 **********************************************************************/
#define UART_LSR_RDR		((uint8_t)(1<<0)) 	/*!<Line status register: Receive data ready*/
#define UART_LSR_OE			((uint8_t)(1<<1)) 	/*!<Line status register: Overrun error*/
#define UART_LSR_PE			((uint8_t)(1<<2)) 	/*!<Line status register: Parity error*/
#define UART_LSR_FE			((uint8_t)(1<<3)) 	/*!<Line status register: Framing error*/
#define UART_LSR_BI			((uint8_t)(1<<4)) 	/*!<Line status register: Break interrupt*/
#define UART_LSR_THRE		((uint8_t)(1<<5)) 	/*!<Line status register: Transmit holding register empty*/
#define UART_LSR_TEMT		((uint8_t)(1<<6)) 	/*!<Line status register: Transmitter empty*/
#define UART_LSR_BITMASK	((uint8_t)(0x7F)) 	/*!<UART Line status bit mask */

/* Public Types --------------------------------------------------------------- */
/***********************************************************************
 * @brief UART enumeration
**********************************************************************/
/**
 * @brief UART Databit type definitions
 */
typedef enum {
	UART_DATABIT_5		= 0,     		/*!< UART 5 bit data mode */
	UART_DATABIT_6,		     			/*!< UART 6 bit data mode */
	UART_DATABIT_7,		     			/*!< UART 7 bit data mode */
	UART_DATABIT_8		     			/*!< UART 8 bit data mode */
} UART_DATABIT_Type;

/**
 * @brief UART Stop bit type definitions
 */
typedef enum {
	UART_STOPBIT_1		= (0),   					/*!< UART 1 Stop Bits Select */
	UART_STOPBIT_2		 							/*!< UART 2 Stop Bits Select */
} UART_STOPBIT_Type;

/**
 * @brief UART Parity type definitions
 */
typedef enum {
	UART_PARITY_NONE 	= 0,					/*!< No parity */
	UART_PARITY_ODD,	 						/*!< Odd parity */
	UART_PARITY_EVEN, 							/*!< Even parity */
	UART_PARITY_SP_1, 							/*!< Forced "1" stick parity */
	UART_PARITY_SP_0 							/*!< Forced "0" stick parity */
} UART_PARITY_Type;

/*********************************************************************
* @brief UART Interrupt Type definitions
**********************************************************************/
typedef enum {
	UART_INTCFG_RBR = 0,	/*!< RBR Interrupt enable*/
	UART_INTCFG_THRE,		/*!< THR Interrupt enable*/
	UART_INTCFG_RLS,		/*!< RX line status interrupt enable*/
	UART_INTCFG_TXE		/*!< TXE interrupt */
} UART_INT_Type;

/**
 * @brief UART Data Control type definition
 */
typedef enum {
	UART_DATA_CONTROL_LOOPBACK	= 0,		/*!< Loop back mode select */
	UART_DATA_CONTROL_RXINV,
	UART_DATA_CONTROL_TXINV,
	UART_DATA_CONTROL_RTXINV,
} UART_DATA_CONTROL_Type;

/********************************************************************
* @brief UART Configuration Structure definition
**********************************************************************/
typedef struct {
  uint32_t Baud_rate;   		/**< UART baud rate */
  UART_DATABIT_Type Databits;   /**< Number of data bits, should be:
							   - UART_DATABIT_5: UART 5 bit data mode
							   - UART_DATABIT_6: UART 6 bit data mode
							   - UART_DATABIT_7: UART 7 bit data mode
							   - UART_DATABIT_8: UART 8 bit data mode
							   */
  UART_PARITY_Type Parity;    	/**< Parity selection, should be:
							   - UART_PARITY_NONE: No parity
							   - UART_PARITY_ODD: Odd parity
							   - UART_PARITY_EVEN: Even parity
							   - UART_PARITY_SP_1: Forced "1" stick parity
							   - UART_PARITY_SP_0: Forced "0" stick parity
							   */
  UART_STOPBIT_Type Stopbits;   /**< Number of stop bits, should be:
							   - UART_STOPBIT_1: UART 1 Stop Bits Select
							   - UART_STOPBIT_2: UART 2 Stop Bits Select
							   */

  uint8_t	*RxTxBuffer;
  uint16_t	RxBufferSize;
  uint16_t	TxBufferSize;

} UART_CFG_Type;

/* Public Functions ----------------------------------------------------------- */
/* UART Init/DeInit functions --------------------------------------------------*/
void UART_Init(UART_Type *UARTn, UART_CFG_Type *UART_ConfigStruct);
void UART_DeInit(UART_Type* UARTn);
void UART_ConfigStructInit(UART_CFG_Type *UART_InitStruct);
UART_Type * UART_Get_Object (int uart_no);

/* UART Send/Receive functions -------------------------------------------------*/
void UART_SendByte(UART_Type* UARTn, uint8_t Data);
uint8_t UART_ReceiveByte(UART_Type* UARTn);
uint32_t UART_Send(UART_Type *UARTn, uint8_t *txbuf, uint32_t buflen, TRANSFER_BLOCK_Type flag);
uint32_t UART_Receive(UART_Type *UARTn, uint8_t *rxbuf, uint32_t buflen, TRANSFER_BLOCK_Type flag);

/* UART operate functions -------------------------------------------------------*/
void UART_SetDivisors(UART_Type *UARTn, uint32_t baudrate);
void UART_IntConfig(UART_Type *UARTn, UART_INT_Type UARTIntCfg, FunctionalState NewState);
uint8_t UART_GetLineStatus(UART_Type* UARTn);
FlagStatus UART_CheckBusy(UART_Type *UARTn);
void UART_ForceBreak(UART_Type* UARTn);
void UART_DataControlConfig(UART_Type *UARTn, UART_DATA_CONTROL_Type Mode, FunctionalState NewState);
void UART_IFDelayConfig(UART_Type *UARTn, uint8_t waitval);

/* UART Send/Receive NEW functions ----------------------------------------------*/
typedef struct {
	volatile uint16_t	rxhead,rxtail,rxsize;
	volatile uint16_t	txhead,txtail,txsize;
	uint16_t	rxqsize,txqsize;
	uint8_t		status;
	uint8_t		*buffer;
} UARTBUFFER;

void 	uputc(UART_Type* UARTn, uint8_t Data);
int32_t	uwrite(UART_Type *UARTn,void *p,int size);
int32_t	uread(UART_Type *UARTn,void *p,int size);
int32_t	uputs(UART_Type *UARTn,char *s);

#define OS_INTEGER_UART_PRINTF_TMP_ARRAY_SIZE	128

int32_t	uprintf(UART_Type *UARTn, const char* format, ...);

int32_t	ugetq(UARTBUFFER *ub);
int32_t	ucheck(UART_Type* UARTn);
int32_t	ugetc(UART_Type* UARTn);
int32_t	ugetchar(UART_Type* UARTn);
int32_t	ugets(UART_Type* UARTn, char *strin, int32_t maxsize);

void	uflush(UART_Type* UARTn);


#ifdef __cplusplus
}
#endif


#endif /* _UART_H_ */

/* --------------------------------- End Of File ------------------------------ */
