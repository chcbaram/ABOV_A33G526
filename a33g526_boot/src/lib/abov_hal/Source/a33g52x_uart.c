/**********************************************************************
* @file		A33G52x_uart.c
* @brief	Contains all functions support for UART firmware library on A31G31x_Series
* @ Version : V1.0.10
* @date:	2020-11-16
* @author	BC Lee, AE TEAM
*
* Copyright(C) 2017-2020, ABOV Semiconductor. All rights reserved.
**********************************************************************/

/* Includes ------------------------------------------------------------------- */
#include "A33G52x_uart.h"
#include "A33G52x_pmu.h"
#include <A33G52x.h>
//#include "def.h"
#include "debug_frmwrk.h"

/* Private Functions ---------------------------------------------------------- */
uint32_t UartBaseClock;

void UART_SetDivisors(UART_Type *UARTn, uint32_t baudrate);



UARTBUFFER	UART_Buffer[2];

UARTBUFFER *uart_get_buffer(UART_Type *UARTn)
{
	UARTBUFFER	*ub;

	if (UARTn == UART0) {
		ub = &UART_Buffer[0];
	} else if (UARTn == UART1) {
		ub = &UART_Buffer[1];
	} else {
		ub = NULL;
	}

	return ub;
}

void	uart_set_buffer(UART_Type *UARTn, uint8_t *buffer, uint32_t rxqsize, uint32_t txqsize)
{
	UARTBUFFER	*ub;

	ub = uart_get_buffer(UARTn);

	if (ub != NULL) {
		ub->status = 0;
		ub->rxhead = ub->rxtail = ub->rxsize = 0;
		ub->txhead = ub->txtail = ub->txsize = 0;

		if (buffer == NULL) {
			ub->buffer = NULL;
			ub->rxqsize = 0;
			ub->txqsize = 0;
		} else {
			ub->buffer = buffer;
			ub->rxqsize = rxqsize;
			ub->txqsize = txqsize;
		}
	}
}

//=========================================================================
//	global variables
//=========================================================================

/*********************************************************************
 * @brief		UART Handler routine
 * @param[in]	UARTn	Pointer to selected UART peripheral, should be:
 * 					- UART0	:UART0 peripheral
 * 					- UART1	:UART1 peripheral
 * 				ub		UART buffer
 * @return 		None
 **********************************************************************/
void	UART_Handler(UART_Type *UARTn)
{
	int			ch;
	uint32_t	iir,lsr;
	UARTBUFFER	*ub;

	ub = uart_get_buffer(UARTn);
	for (;;) {
		iir = UARTn->IIR & 0x07;

		if(iir==0x01)
			break;

		switch (iir) {
		case 0x04:
			ch = UARTn->RBR;
			if (ub->rxsize<ub->rxqsize) {
				ub->rxsize++;
				ub->buffer[ub->rxtail]=ch;
				if (++ub->rxtail>=ub->rxqsize)
					ub->rxtail=0;
			}
			break;
		case 0x02:
			if (ub->txsize==0) {
				UARTn->IER |= UART_IER_THREIE;	// = 0uawrite(port,IA_IER,uaread(port,IA_IER)&~IER_TIE);
			} else if (ub->txqsize > 0) {
				ch = ub->buffer[ub->rxqsize + ub->txhead];
				if (++ub->txhead >= ub->txqsize)
					ub->txhead = 0;
				UARTn->THR = ch;	//uawrite(port,IA_THR,ch);
				if (--(ub->txsize) <= 0)
					break;
			}
			break;
		case 0x06:
			lsr = UARTn->LSR;	//uaread(port,IA_LSR);
			if (lsr & 0x10)
				ub->status |= 0x10;
			if (lsr & 0x04)
				ub->status |= 0x04;
			if (lsr & 0x08)
				ub->status |= 0x08;
			break;
		}
	}
}

#ifdef UART0
void	UART0_Handler(void)
{
	UART_Handler(UART0);
}
#endif

#ifdef UART1
void	UART1_Handler(void)
{
	UART_Handler(UART1);
}
#endif

#ifdef UART2
void	UART2_Handler(void)
{
	UART_Handler(UART2);
}
#endif

#ifdef UART3
void	UART3_Handler(void)
{
	UART_Handler(UART3);
}
#endif

/*********************************************************************
 * @brief		Determines best dividers to get a target clock rate
 * @param[in]	UARTn	Pointer to selected UART peripheral, should be:
 * 					- UART0	:UART0 peripheral
 * 					- UART1	:UART1 peripheral
 * @param[in]	baudrate Desired UART baud rate.
 * @return 		None
 **********************************************************************/
void UART_SetDivisors(UART_Type *UARTn, uint32_t baudrate)
{
	uint32_t 	numerator;
	uint32_t 	denominator;
	uint32_t 	bdr, bfr;
	uint32_t 	fd;
	uint32_t	lcr;

	//------------------------------------------------------------------------------
	// numerator & denominator
	//
	// bdr = (UartBaseClock) / (16 * baudrate * 2)
	//------------------------------------------------------------------------------
	numerator = UartBaseClock;
	denominator = 16 * baudrate;

	bdr = numerator / denominator;

	//------------------------------------------------------------------------------
	//	fraction = numerator - bdr x denominator
	//
	//	bfr = INT (fraction * 256) = ((f x d ) << 8) / d
	//------------------------------------------------------------------------------

	fd = numerator - (bdr * denominator);
	bfr = (fd * 256) / denominator;
#ifdef A33G52x
	lcr = UARTn->LCR;
	UARTn->LCR = 0x80;
	UARTn->DLL = bdr & 0xff;
	UARTn->DLM = (bdr >> 8) & 0xff;
	UARTn->LCR = lcr;
#else
	UARTn->BDR= (uint16_t)(bdr&0xffff);
#endif
	UARTn->BFR= (uint8_t)(bfr&0xff);
}

/* End of Private Functions ---------------------------------------------------- */

/* Public Functions ----------------------------------------------------------- */
/* UART Init/DeInit functions -------------------------------------------------*/
/********************************************************************
 * @brief		Initializes the UARTn peripheral according to the specified
 *               parameters in the UART_ConfigStruct.
 * @param[in]	UARTn	UART peripheral selected, should be:
 * 					- UART0	:UART0 peripheral
 * 					- UART1	:UART1 peripheral
 * @param[in]	UART_ConfigStruct Pointer to a UART_CFG_Type structure
 *              that contains the configuration information for the
 *              specified UART peripheral.
 * @return 		None
 *********************************************************************/
void UART_Init(UART_Type *UARTn, UART_CFG_Type *UART_ConfigStruct)
{
	uint8_t tmp;

#ifdef A33G52x
	if (UARTn == UART0) {
		PMU->PCCR |= PMU_PCCR_UART0;
		PMU->PER &= ~PMU_PER_UART0;
		PMU->PER |=  PMU_PER_UART0;
	}
	if (UARTn == UART1) {
		PMU->PCCR |= PMU_PCCR_UART1;
		PMU->PER &= ~PMU_PER_UART1;
		PMU->PER |=  PMU_PER_UART1;
	}
	if (UARTn == UART2) {
		PMU->PCCR |= PMU_PCCR_UART2;
		PMU->PER &= ~PMU_PER_UART2;
		PMU->PER |=  PMU_PER_UART2;
	}
	if (UARTn == UART3) {
		PMU->PCCR |= PMU_PCCR_UART3;
		PMU->PER &= ~PMU_PER_UART3;
		PMU->PER |=  PMU_PER_UART3;
	}
#else
#ifdef UART0
	if(UARTn == UART0) {
		/* Set up peripheral clock for UART0 module */
		SCUCG->PPCLKEN2 |= SCUCG_PPCLKEN2_UT0CLKE_Msk;
		SCUCG->PPRST2 |= SCUCG_PPRST2_UT0RST_Msk;
		SCUCG->PPRST2 &= ~SCUCG_PPRST2_UT0RST_Msk;
	}
#endif
#ifdef UART1
	if(UARTn == UART1) {
		/* Set up peripheral clock for UART1 module */
		SCUCG->PPCLKEN2 |= SCUCG_PPCLKEN2_UT1CLKE_Msk;
		SCUCG->PPRST2 |= SCUCG_PPRST2_UT1RST_Msk;
		SCUCG->PPRST2 &= ~SCUCG_PPRST2_UT1RST_Msk;
	}
#endif
#endif
	// Dummy reading
	while (UARTn->LSR & UART_LSR_RDR)
	{
		tmp = UARTn->RBR;
	}
	// Wait for current transmit complete
	while (!(UARTn->LSR & UART_LSR_THRE));

	// Disable interrupt
	UARTn->IER = 0;
	// Set LCR, DCR to default state
	UARTn->LCR = 0;

#ifndef A33G52x
	UARTn->DCR = 0;
#endif

	// Dummy reading
	tmp = UARTn->LSR;
	tmp = UARTn->IIR;

	// uart clock set
//	SCU->MCCR7 &=0xffff0000;
//	SCU->MCCR7 |=((4<<8)|(2)); // MCLK
#ifdef A33G52x
	UartBaseClock = SystemPeriClock / 2;
#else
	UartBaseClock = SystemPeriClock;
#endif

	// Set Line Control register ----------------------------
	UART_SetDivisors(UARTn, (UART_ConfigStruct->Baud_rate));

	tmp = (UARTn->LCR & UART_LCR_BREAK_EN) & UART_LCR_BITMASK;

	switch (UART_ConfigStruct->Databits){
	case UART_DATABIT_5:
		tmp |= UART_LCR_WLEN5;
		break;
	case UART_DATABIT_6:
		tmp |= UART_LCR_WLEN6;
		break;
	case UART_DATABIT_7:
		tmp |= UART_LCR_WLEN7;
		break;
	case UART_DATABIT_8:
	default:
		tmp |= UART_LCR_WLEN8;
		break;
	}

	if (UART_ConfigStruct->Parity == UART_PARITY_NONE) {
		// Do nothing...
	} else {
		tmp |= UART_LCR_PARITY_EN;
		switch (UART_ConfigStruct->Parity)
		{
		case UART_PARITY_ODD:
			tmp |= UART_LCR_PARITY_ODD;
			break;

		case UART_PARITY_EVEN:
			tmp |= UART_LCR_PARITY_EVEN;
			break;

		case UART_PARITY_SP_1:
			tmp |= UART_LCR_PARITY_F_1;
			break;

		case UART_PARITY_SP_0:
			tmp |= UART_LCR_PARITY_F_0;
			break;
		default:
			break;
		}
	}

	switch (UART_ConfigStruct->Stopbits){
	case UART_STOPBIT_2:
		tmp |= UART_LCR_STOPBIT_SEL;
		break;
	case UART_STOPBIT_1:
	default:
		// Do no thing
		break;
	}

	UARTn->LCR = (uint8_t)(tmp & UART_LCR_BITMASK);

	uart_set_buffer(UARTn, UART_ConfigStruct->RxTxBuffer, UART_ConfigStruct->RxBufferSize, UART_ConfigStruct->TxBufferSize);

	if (UART_ConfigStruct->RxTxBuffer != NULL) {
		UART_IntConfig(UARTn, UART_INTCFG_RBR, ENABLE);

#ifdef A33G52x
		if (UARTn == UART0) {
			NVIC_EnableIRQ(UART0_IRQn);
		}
		if (UARTn == UART1) {
			NVIC_EnableIRQ(UART1_IRQn);
		}
		if (UARTn == UART2) {
			NVIC_EnableIRQ(UART2_IRQn);
		}
		if (UARTn == UART3) {
			NVIC_EnableIRQ(UART3_IRQn);
		}
#else
#ifdef UART0
		if (UARTn == UART0) {
			NVIC_EnableIRQ(UART0_IRQn);
			EInt_MaskDisable(MSK_UART0);
		}
#endif
#ifdef UART1
		if (UARTn == UART1) {
			NVIC_EnableIRQ(UART1_IRQn);
			EInt_MaskDisable(MSK_UART1);
		}
#endif
#endif
	}
}

/*********************************************************************
 * @brief		De-initializes the UARTn peripheral registers to their
 *              default reset values.
 * @param[in]	UARTn	UART peripheral selected, should be:
 * 					- UART0	:UART0 peripheral
 * 					- UART1	:UART1 peripheral
 * @return 		None
 **********************************************************************/
void UART_DeInit(UART_Type* UARTn)
{
#ifdef A33G52x
	if (UARTn == UART0) {
		NVIC_DisableIRQ(UART0_IRQn);
		PMU->PER &= ~PMU_PER_UART0;
		PMU->PCCR &= ~PMU_PCCR_UART0;
	}
	if (UARTn == UART1) {
		NVIC_DisableIRQ(UART1_IRQn);
		PMU->PER &= ~PMU_PER_UART1;
		PMU->PCCR &= ~PMU_PCCR_UART1;
	}
	if (UARTn == UART2) {
		NVIC_DisableIRQ(UART2_IRQn);
		PMU->PER &= ~PMU_PER_UART2;
		PMU->PCCR &= ~PMU_PCCR_UART2;
	}
	if (UARTn == UART3) {
		NVIC_DisableIRQ(UART3_IRQn);
		PMU->PER &= ~PMU_PER_UART3;
		PMU->PCCR &= ~PMU_PCCR_UART3;
	}
#else
#ifdef UART0
	if (UARTn == UART0) {
		NVIC_DisableIRQ(UART0_IRQn);
		EInt_MaskEnable(MSK_UART0);
		/* Set up peripheral clock for UART0 module */
		SCUCG->PPCLKEN2 &= ~SCUCG_PPCLKEN2_UT0CLKE_Msk;
		SCUCG->PPRST2 &= ~SCUCG_PPRST2_UT0RST_Msk;
	}
#endif
#ifdef UART1
	if (UARTn == UART1) {
		NVIC_DisableIRQ(UART1_IRQn);
		EInt_MaskEnable(MSK_UART1);
		/* Set up peripheral clock for UART0 module */
		SCUCG->PPCLKEN2 &= ~SCUCG_PPCLKEN2_UT1CLKE_Msk;
		SCUCG->PPRST2 &= ~SCUCG_PPRST2_UT1RST_Msk;
	}
#endif
#endif
}

/******************************************************************************
 * @brief		Fills each UART_InitStruct member with its default value:
 * 					- 38400 bps
 * 					- 8-bit data
 * 					- 1 Stopbit
 * 					- None Parity
 * @param[in]	UART_InitStruct Pointer to a UART_CFG_Type structure which will
 * 				be initialized.
 * @return		None
 *******************************************************************************/
void UART_ConfigStructInit(UART_CFG_Type *UART_InitStruct)
{
	UART_InitStruct->Baud_rate = 38400;
	UART_InitStruct->Databits = UART_DATABIT_8;
	UART_InitStruct->Parity = UART_PARITY_NONE;
	UART_InitStruct->Stopbits = UART_STOPBIT_1;
	UART_InitStruct->RxTxBuffer = NULL;
	UART_InitStruct->RxBufferSize = 0;
	UART_InitStruct->TxBufferSize = 0;
}

/******************************************************************************
 * @brief		Get UART object number:
 * @param[in]	uart_no : 0 ~ 3
 * 				be initialized.
 * @return		UART_Type variables
 *              - UART0
 *              - UART1
 *              - UART2
 *              - UART3 
*******************************************************************************/
UART_Type * UART_Get_Object (int uart_no)
{

	UART_Type *	p_obj; 


	switch (uart_no)
	{
	case 0: 
		p_obj = UART0; 
		break; 
		
	case 1: 
		p_obj = UART1; 
		break; 

	case 2: 
		p_obj = UART2; 
		break; 
		
	case 3: 
		p_obj = UART3; 
		break; 		

	default:
		p_obj = (UART_Type *) 0; 
		break; 
	}


	return (p_obj); 

}

/* UART Send/Recieve functions -------------------------------------------------*/
/**********************************************************************
 * @brief		Transmit a single data through UART peripheral
 * @param[in]	UARTn	UART peripheral selected, should be:
 * 					- UART0	:UART0 peripheral
 * 					- UART1	:UART1 peripheral
 * @param[in]	Data	Data to transmit (must be 8-bit long)
 * @return 		None
 **********************************************************************/
void	uflush(UART_Type* UARTn)
{
	UARTBUFFER	*ub;

	ub = uart_get_buffer(UARTn);

	if (ub != NULL) {
		ub->status=0;
		ub->rxhead=ub->rxtail=ub->rxsize=0;
		ub->txhead=ub->txtail=ub->txsize=0;
	}
}


void uputc(UART_Type* UARTn, uint8_t Data)
{

	UARTBUFFER	*ub;

	ub = uart_get_buffer(UARTn);

	if (ub != NULL) {

		if(ub->txqsize>0) {
			if (ub->txsize == 0 && (UARTn->LSR & UART_LSR_THRE)!=0) {
				UARTn->THR = Data;
			}
			else {
				while(ub->txsize==ub->txqsize) ;
				DI();
				ub->buffer[ub->rxqsize+ub->txtail]=Data;
				if(++ub->txtail>=ub->txqsize)
					ub->txtail=0;
				ub->txsize++;
				UARTn->IER |= UART_IER_THREIE;	//_b.THREIE = 1;	//uawrite(port,IA_IER,uaread(port,IA_IER)|IER_TIE);
				EI();
			}
		}
		else {
			while ((UARTn->LSR & (UART_LSR_THRE | UART_LSR_TEMT)) != (UART_LSR_THRE | UART_LSR_TEMT));
			UARTn->THR = Data;
		}
	} else {
		while ((UARTn->LSR&(UART_LSR_THRE|UART_LSR_TEMT)) != (UART_LSR_THRE|UART_LSR_TEMT));
		UARTn->THR = Data;
	}
}

int32_t	uwrite(UART_Type *UARTn,void *p,int size)
{
	int32_t i;
	uint8_t	*dp=p;

	for (i = 0; i < size; i++) {
		uputc(UARTn,*dp++);
	}
	return size;
}

int32_t	uread(UART_Type *UARTn,void *p,int size)
{
	int32_t i;
	uint8_t	*dp=p;
	for (i = 0; i < size; i++) {
		*dp++=ugetc(UARTn);
	}
	return i;
}

int32_t	uputs(UART_Type *UARTn,char *s)
{
	int32_t	i;
	int	ch;
	for(i=0;;i++) {
		ch=*s++;
		if(ch==0)
			break;
		uputc(UARTn,ch);
	}
	return i;
}

int32_t uprintf(UART_Type *UARTn, const char* format, ...)
{
	int32_t ret;
    va_list ap;

    static char buf[OS_INTEGER_UART_PRINTF_TMP_ARRAY_SIZE];

  va_start (ap, format);

  // TODO: rewrite it to no longer use newlib, it is way too heavy


  // Print to the local buffer
  ret = vsnprintf (buf, sizeof(buf), format, ap);
  if (ret > 0)
    {
      // Transfer the buffer to the device
      uwrite(UARTn, buf, (size_t)ret);
    }

  va_end (ap);
  return ret;
}

void UART_SendByte(UART_Type* UARTn, uint8_t Data)
{
	//UARTn->UART_THR = Data;
	uputc(UARTn, Data);
}

/**********************************************************************
 * @brief		Receive a single data from UART peripheral
 * @param[in]	UARTn	UART peripheral selected, should be:
 * 					- UART0	:UART0 peripheral
 * 					- UART1	:UART1 peripheral
 * @return 		Data received
 **********************************************************************/
int32_t	ugetq(UARTBUFFER *ub)
{
	int	ch;

	if (ub->rxsize == 0)
		return -1;
	DI();
	ch = ub->buffer[ub->rxhead];
	if (++ub->rxhead>=ub->rxqsize)
		ub->rxhead=0;
	ub->rxsize--;
	EI();

	return ch;
}

int32_t	ucheck(UART_Type* UARTn)
{
	UARTBUFFER *ub;

	ub = uart_get_buffer(UARTn);
	if (ub != NULL) {
		return (ub->rxsize);
	}
	return UARTn->LSR & UART_LSR_RDR;
}

int32_t	ugetc(UART_Type* UARTn)
{
	UARTBUFFER *ub;

	ub = uart_get_buffer(UARTn);
	if (ub != NULL) {
		int	ch;
		while ((ch = ugetq(ub)) < 0);
		return ch;
	}

	while ((UARTn->LSR & UART_LSR_RDR) == 0);
	return UARTn->RBR;
}

int32_t	ugetchar(UART_Type* UARTn)
{
	int	ch = -1;

	if (ucheck(UARTn))
		ch = ugetc(UARTn);

	return ch;
}

int32_t	ugets(UART_Type* UARTn, char *strin, int32_t maxsize)
{
	int i;

	for (i = 0; i < maxsize-1; i++) {
		int32_t	ch;

		ch = ugetc(UARTn);
		if (ch == '\r')
			break;
		strin[i] = ch;
	}
	strin[i++] = 0;
	return i;
}

uint8_t UART_ReceiveByte(UART_Type* UARTn)
{
//	return (UARTn->UARTn_RBR);
	return ugetc(UARTn);
}

/**********************************************************************
 * @brief		Send a block of data via UART peripheral
 * @param[in]	UARTn	Selected UART peripheral used to send data, should be:
 * 					- UART0	:UART0 peripheral
 * 					- UART1	:UART1 peripheral
 * @param[in]	txbuf 	Pointer to Transmit buffer
 * @param[in]	buflen 	Length of Transmit buffer
 * @param[in] 	flag 	Flag used in  UART transfer, should be
 * 					- NONE_BLOCKING
 * 					- BLOCKING
 * @return 		Number of bytes sent.
 *
 * Note: when using UART in BLOCKING mode, a time-out condition is used
 * via defined symbol UART_BLOCKING_TIMEOUT.
 **********************************************************************/
uint32_t UART_Send(UART_Type *UARTn, uint8_t *txbuf, uint32_t buflen, TRANSFER_BLOCK_Type flag)
{
	int bSent;

	for (bSent = 0; bSent < buflen; bSent++) {
		uputc(UARTn, txbuf[bSent]);
	}
	return bSent;
}

/*********************************************************************
 * @brief		Receive a block of data via UART peripheral
 * @param[in]	UARTn	Selected UART peripheral used to send data,
 * 				should be:
 * 					- UART0	:UART0 peripheral
 * 					- UART1	:UART1 peripheral
 * @param[out]	rxbuf 	Pointer to Received buffer
 * @param[in]	buflen 	Length of Received buffer
 * @param[in] 	flag 	Flag mode, should be:
 * 					- NONE_BLOCKING
 * 					- BLOCKING
 * @return 		Number of bytes received
 *
 * Note: when using UART in BLOCKING mode, a time-out condition is used
 * via defined symbol UART_BLOCKING_TIMEOUT.
 **********************************************************************/
uint32_t UART_Receive(UART_Type *UARTn, uint8_t *rxbuf, uint32_t buflen, TRANSFER_BLOCK_Type flag)
{
	int bRecv;

	for (bRecv = 0; bRecv < buflen; bRecv++) {
		rxbuf[bRecv] = ugetc(UARTn);
	}
	return bRecv;
}

/*********************************************************************
 * @brief		Force BREAK character on UART line, output pin UARTn TXD is
				forced to logic 0.
 * @param[in]	UARTn	UART peripheral selected, should be:
 * 					- UART0	:UART0 peripheral
 * 					- UART1	:UART1 peripheral
 * @return 		None
 **********************************************************************/
void UART_ForceBreak(UART_Type* UARTn)
{
	UARTn->LCR |= UART_LCR_BREAK_EN;
}

/********************************************************************
 * @brief 		Enable or disable specified UART interrupt.
 * @param[in]	UARTn	UART peripheral selected, should be
 * 					- UART0	:UART0 peripheral
 * 					- UART1	:UART1 peripheral
 * @param[in]	UARTIntCfg	Specifies the interrupt flag,
 * 				should be one of the following:
 * 					- UART_INTCFG_RBR 	:RBR Interrupt enable
 * 					- UART_INTCFG_THRE 	:THR Interrupt enable
 * 					- UART_INTCFG_RLS 	:RX line status interrupt enable
 * 					- UART_INTCFG_DRX 	:THR Interrupt enable
 * 					- UART_INTCFG_DTX 	:RX line status interrupt enable
 * @param[in]	NewState New state of specified UART interrupt type,
 * 				should be:
 * 					- ENALBE	:Enable this UART interrupt type.
 * 					- DISALBE	:Disable this UART interrupt type.
 * @return 		None
 *********************************************************************/
void UART_IntConfig(UART_Type *UARTn, UART_INT_Type UARTIntCfg, FunctionalState NewState)
{
	uint32_t tmp;

	switch(UARTIntCfg){
		case UART_INTCFG_RBR:
			tmp = UART_IER_DRIE;
			break;
		case UART_INTCFG_THRE:
			tmp = UART_IER_THREIE;
			break;
		case UART_INTCFG_RLS:
			tmp = UART_IER_RLSIE;
			break;
		case UART_INTCFG_TXE:
			tmp = UART_IER_TEMTIE;
			break;
	}

	if (NewState == ENABLE)
	{
		UARTn->IER |= tmp;
	}
	else
	{
		UARTn->IER &= (~tmp) & UART_IER_BITMASK;
	}
}


/*********************************************************************
 * @brief 		Get current value of Line Status register in UART peripheral.
 * @param[in]	UARTn	UART peripheral selected, should be:
 * 					- UART0	:UART0 peripheral
 * 					- UART1	:UART1 peripheral
 * @return		Current value of Line Status register in UART peripheral.
 * Note:	The return value of this function must be ANDed with each member in
 * 			UART_LS_Type enumeration to determine current flag status
 * 			corresponding to each Line status type. Because some flags in
 * 			Line Status register will be cleared after reading, the next reading
 * 			Line Status register could not be correct. So this function used to
 * 			read Line status register in one time only, then the return value
 * 			used to check all flags.
 *********************************************************************/
uint8_t UART_GetLineStatus(UART_Type* UARTn)
{
	return ((UARTn->LSR) & UART_LSR_BITMASK);
}

/**********************************************************************
 * @brief		Check whether if UART is busy or not
 * @param[in]	UARTn	UART peripheral selected, should be:
 * 					- UART0	:UART0 peripheral
 * 					- UART1	:UART1 peripheral
 * @return		RESET if UART is not busy, otherwise return SET.
 **********************************************************************/
FlagStatus UART_CheckBusy(UART_Type *UARTn)
{
	if (UARTn->LSR & UART_LSR_TEMT){
		return RESET;
	} else {
		return SET;
	}
}

/*********************************************************************
 * @brief		Configure Data Control mode for UART peripheral
 * @param[in]	UARTn
 * @param[in]	Data Control mode, should be:
 * 					- UART_DATA_CONTROL_LOOPBACK	:Loop back mode.
 * 					- UART_DATA_CONTROL_RXINV	: RX Data inversion mode.
 * 					- UART_DATA_CONTROL_TXINV	:TX Data inversion mode.
 * 					- UART_DATA_CONTROL_RTXINV	:TX RX Data inversion mode.
 * @param[in]	NewState New State of this mode, should be:
 * 					- ENABLE	:Enable this mode.
					- DISABLE	:Disable this mode.
 * @return none
 **********************************************************************/
#ifndef A33G52x
void UART_DataControlConfig(UART_Type *UARTn, UART_DATA_CONTROL_Type Mode, FunctionalState NewState)
{
	uint8_t tmp;

	switch(Mode){
	case UART_DATA_CONTROL_LOOPBACK:
		tmp = UART_DCR_LBON;
		break;
	case UART_DATA_CONTROL_RXINV:
		tmp = UART_DCR_RXINV;
		break;
	case UART_DATA_CONTROL_TXINV:
		tmp = UART_DCR_TXINV;
		break;
	case UART_DATA_CONTROL_RTXINV:
		tmp = UART_DCR_RXINV | UART_DCR_TXINV;
		break;
	default:
		break;
	}

	if (NewState == ENABLE)
	{
		UARTn->DCR |= tmp;
	}
	else
	{
		UARTn->DCR &= (~tmp) & UART_DCR_BITMASK;
	}
}
#endif

/*********************************************************************
 * @brief		Configure inter-frame delay time for UART peripheral
 * @param[in]	UARTn
 * @param[in]	inter-frame delay time : 1 bit time  unit (0~7)
 * @return none
 **********************************************************************/
void UART_IFDelayConfig(UART_Type *UARTn, uint8_t waitval)
{
#ifdef A33G52x
	if (waitval<8){
		UARTn->DTR=waitval;
	}
#else
	if (waitval<8){
		UARTn->IDTR=waitval;
	}
#endif
}

