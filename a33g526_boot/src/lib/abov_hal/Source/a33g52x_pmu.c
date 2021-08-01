/**********************************************************************
* @file		a33g52x_pmu.c
* @brief	Contains all functions support for SCU firmware library on A33G52x
* @ Version : V1.0.10
* @ date:    2020-11-16
* @author	ABOV M team
*
* Copyright(C) 2017, ABOV Semiconductor
* All rights reserved.
*
**********************************************************************/

/* Includes ------------------------------------------------------------------- */
#include <stdint.h>
#include "A33G52x.h"
#include "a33g52x_pmu.h"
#include "a33g52x_flash.h"
#include "debug_frmwrk.h"


extern uint32_t		SystemCoreClock;
extern uint32_t		SystemPeriClock;

/**********************************************************************
 * @brief 		Configure external sub clock
 *             Before exteranl crystal enable setting, you have to set clock ports as SXIN,SXOUT in MOD,AFSRx reg
 * @param[in]	esosccon 	Function mode, should be:
 * 					- EXSOSC_STOP	   : 0
 * 					- EXSOSC_EN    	   : 8
 * 					- EXSOSC_EN_DIV2 : 9
  * 					- EXSOSC_EN_DIV2 : 10
 * @return		None
 **********************************************************************/
void PMU_SetSOSC(uint32_t esosccon)
{
	uint32_t reg_val32;

// enable external sub clock
// Before exteranl crystal enable setting, you have to set clock ports as SXIN,SXOUT in MOD,AFSRx reg
	reg_val32 = PMU->CCR;
	reg_val32 &= ~(0x03 << 2); //
	reg_val32 |= (esosccon << 2); // 0:Stop SOSC, 8:Enable SOSC/1, 9:Enable SOSC/2, 10:Enable SOSC/4
	PMU->CCR = reg_val32;
}

/**********************************************************************
 * @brief 	  monitoring External sub oscillator
 * @param  none
 * @return	status enumeration value:
 *              - ERROR
 *              - SUCCESS
 **********************************************************************/
Status SCU_WaitForSOSCStartUp(void)
{
//	__IO uint32_t StartUpCounter = 0;
//	__IO uint16_t status;
	uint32_t i;

	// monitoring External sub oscillator
//	SCU->CMR |= (1<<11); // 0:External sub oscillator monitoring disabled, 1:External sub oscillator monitoring enable

	/* Wait till SOSC is ready and if timeout is reached exit */
//	do
//	{
//		status = (SCU->CMR & SCU_CMR_SOSCSTS_Msk);
//		StartUpCounter++;
//	} while((StartUpCounter != SOSC_STARTUP_TIMEOUT) && (status != SCU_CMR_SOSCSTS_Msk));

	/* need more Wait for SOSC stable, check SXOUT pin oscillation  */
	for (i=0;i<0x100;i++)
	{
		__NOP();
	}

//	status = (SCU->CMR & SCU_CMR_SOSCSTS_Msk);
//	if (status != SCU_CMR_SOSCSTS_Msk){
//		return ERROR;
//	}
//	else {
		return SUCCESS;
//	}
}

/**********************************************************************
 * @brief 		Configure low speed internal osc clock
 * @param[in]	ringosc Function mode, should be:
 * 					- LSIOSC_STOP        : 0
 * 					- LSIOSC_EN             : 8
 * 					- LSIOSC_EN_DIV2     : 9
 * 					- LSIOSC_EN_DIV4     : 10
 * @return		None
 **********************************************************************/
void SCU_SetLSIOSC(uint32_t ringosc)
{
	uint32_t reg_val32;

// enable internal clock
	reg_val32 = PMU->CCR;
	reg_val32 &= ~(0x03 << 6); //
	reg_val32 |= (ringosc<<6); // 0:Stop LSI, 8:Enable LSI/1, 9:Enable LSI/2, 10:Enable LSI/4
	PMU->CCR = reg_val32;
}

/**********************************************************************
 * @brief 		Configure high speed internal osc clock
 * @param[in]	hsiosc Function mode, should be:
 * 					- HSIOSC_STOP        : 0
 * 					- HSIOSC_EN             : 8
 * 					- HSIOSC_EN_DIV2     : 9
 * 					- HSIOSC_EN_DIV4     : 10
 * 					- HSIOSC_EN_DIV8     : 11
 * 					- HSIOSC_EN_DIV16    : 12
 * 					- HSIOSC_EN_DIV32    : 13
 * @return		None
 **********************************************************************/
void SCU_SetHSIOSC(uint32_t hsiosc)
{
	uint32_t reg_val32;

// enable internal clock
	reg_val32 = PMU->CCR;
	reg_val32 &= ~(0x03 << 4);
	reg_val32 |= (hsiosc << 4); // 0:Stop LSI, 8:Enable LSI/1, 9:Enable LSI/2, 10:Enable LSI/4, 11:Enable LSI/8, 12:Enable LSI/16, 13:Enable LSI/32
	PMU->CCR = reg_val32;
}

/**********************************************************************
 * @brief 		Configure external clock
 *             Before exteranl crystal enable setting, you have to set clock ports as XIN,XOUT in MR.
 * @param[in]	eosccon 	Function mode, should be:
 * 					- EXOSC_STOP        : 0
 * 					- EXOSC_EN             : 8
 * 					- EXOSC_EN_DIV2     : 9
 * 					- EXOSC_EN_DIV4     : 10
 * @return		None
 **********************************************************************/
void SCU_SetMOSC(uint32_t eosccon)
{
	uint32_t reg_val32;

// enable external clock
// Before exteranl crystal enable setting, you have to set clock ports as XIN,XOUT in MOD,AFSRx reg
	reg_val32 = PMU->CCR;
	reg_val32 &= ~(0x03 << 0); //
	reg_val32 |= (eosccon << 0); // 0:Stop MOSC, 8:Enable MOSC/1, 9:Enable MOSC/2, 10:Enable MOSC/4
	PMU->CCR = reg_val32;
}

/**********************************************************************
 * @brief 		Clock Monitoring Enable
 *             Set Clock Monitoring Function.
 * @param[in]	eosccon 	Function mode, should be:
 * 					- EXOSC_STOP        : 0
 * 					- EXOSC_EN             : 8
 * 					- EXOSC_EN_DIV2     : 9
 * 					- EXOSC_EN_DIV4     : 10
 * @return		None
 **********************************************************************/
void SCU_SetClockMonitoring(uint32_t enable)
{
	PMU->CMR = enable;
}

/**********************************************************************
 * @brief 	  monitoring External oscillator
 * @param  none
 * @return	status enumeration value:
 *              - ERROR
 *              - SUCCESS
 **********************************************************************/
Status SCU_WaitForMOSCStartUp(void)
{
	__IO uint32_t StartUpCounter = 0;
	__IO uint16_t status;
	uint32_t i;

	// monitoring External oscillator
	PMU->CMR |= 0x0101; // 0:External oscillator monitoring disabled, 1:External oscillator monitoring enable

	/* Wait till MOSC is ready and if timeout is reached exit */
	do {
		status = (PMU->CMR & PMU_CMR_MXOSCSTS);
		StartUpCounter++;
	} while ((StartUpCounter < MOSC_STARTUP_TIMEOUT) && (status != PMU_CMR_MXOSCSTS));

	/* need more Wait for MOSC stable, check XOUT pin oscillation  */
	for (i = 0 ; i < 0x800 ; i++) {
		__NOP();
	}

	status = (PMU->CMR & PMU_CMR_MXOSCSTS);
	if (status != PMU_CMR_MXOSCSTS){
		return ERROR;
	} else {
		return SUCCESS;
	}
}

/**********************************************************************
 * @brief 		change system clock control
 * @param[in]	sysclkcon mode, should be:
 * 					- SC_LSIOSC		         : 0x00
 * 					- SC_SOSC  	             : 0x01
 * 					- SC_HSIOSC  	         : 0x03
 * 					- SC_HSIOSCPLL           : 0x02
 * 					- SC_EXOSC               : 0x13
 * 					- SC_EXOSCPLL            : 0x12
 * @return		None
 **********************************************************************/
void SCU_ChangeSysClk(uint32_t sysclkcon)
{
	uint32_t reg_val32;
//	int i;

	reg_val32 = PMU->BCCR;
	reg_val32 &= ~(0x1F << 0); //
	reg_val32 |= sysclkcon;
	PMU->BCCR = reg_val32;

//	for(i=0; i < 1000; i++);			// delay for clock stabilization

}


/**********************************************************************
 * @brief 		Configure clock out  on PF4
 *       Before this function setting, you have to set PF4 as CLKO in PF.MODand PF.AFSR0.
 * @param[in]	divval(=CLKODIV) : 0~15  // CLKO=MCLK/(2*(CLKODIV+1))
 *                   ex) MCLK=20Mh, CLKODIV=4,    20Mhz/ (2*(4+1)) = 2Mhz
 * @param[in]	FunctionalState, should be:
 * 					- DISABLE		   : 0
 * 					- ENABLE    	   : 1
 * @return		None
 **********************************************************************/
void SCU_SetCOR(uint8_t divval, FunctionalState endis)
{
	PMU->COR=(endis<<4)|(divval&0xf);
}

/**********************************************************************
 * @brief 	  monitoring External oscillator
 * @param  none
 * @return	status enumeration value:
 *              - ERROR
 *              - SUCCESS
 **********************************************************************/
Status SCU_SetPLLandWaitForPLLStartUp(FunctionalState pllsetstate, uint8_t selbypass, uint8_t selfin,  uint8_t PREDIV, uint8_t POSTDIV1, uint8_t POSTDIV2, uint8_t OUTDIV)
{
	__IO uint32_t StartUpCounter = 0;
	__IO uint32_t status;
//	uint32_t i;

	PMU->PLLCON = 0x80750000;			// Key value for setting PLL Frequency (Extended Mode)

	if (pllsetstate == DISABLE){
		PMU->PLLCON = 0;
		return SUCCESS;
	} else {
// PLLenable    PLL freq = (FIN or FIN/2) * M / N
		PMU->PLLCON = 0
		|(1 << 15)   // PLL reset is negated
		|(1 << 14)  // PLLEn
		|((selbypass & 1) << 13)     	//BYPASS 0:FOUT is bypassed as FIN, 1:FOUT is PLL output
//		|((selfin & 1) << 20)           //PLL VCO mode  0:VCO is the same with FOUT, 1:VCO frequency is x2 of FOUT   D
		|((PREDIV & 0x7) << 8)      	//PREDIV        R
		|((POSTDIV1 & 0xff) << 20)    	//POSTDIV1   N1 = MULT
		|((POSTDIV2 & 0xf) << 16)     	//POSTDIV2   N2
		|((OUTDIV & 0xf) << 0)         	//OUTDIV	     P
			;

//		PMU->PLLCON&=~(1<<23);   // PLL reset is asserted
//		for (i=0;i<1000;i++);
//		PMU->PLLCON|=(1<<23);     // PLL reset is negated

	  /* Wait till PLL LOCK is ready and if timeout is reached exit */
		do
		{
			status = (PMU->PLLCON & PLLCON_LOCKSTS);
			StartUpCounter++;
		} while ((StartUpCounter != PLL_STARTUP_TIMEOUT) && (status != PLLCON_LOCKSTS));

		status = (PMU->PLLCON & PLLCON_LOCKSTS);
		if (status != PLLCON_LOCKSTS){
			return ERROR;
		}
		else {
			return SUCCESS;
		}
	}
}

/**
************************************************************************************
* @ Name : PMU_SetPLLFreq
*
* @ Parameters
*
*		- pmu				PMU
*		- pllInClk 			XTAL4MHz, XTAL8MHz, XTAL10MHz, IOSC16MHz
*		- setPLLFreq		PLL75MHz, PLL74MHz, ..., PLL1MHz
*
* @ Description : this function helps users easilly set the value of PLL operating frequency.
************************************************************************************
*/
int32_t PMU_SetPLLFreq(PMU_Type *pmu, uint32_t pllInClk, uint32_t setPllFreq) {
	uint32_t	reg_val;

	uint32_t r       = 0;							// PLL input clock divider (R)
	uint32_t n1 	= 0;							// PLL multiplyer (N1)
	uint32_t n2 	= 0;							// PLL divider (N2)
	uint32_t p 		= 0;							// PLL post-divider (P)
	uint32_t d		= 0;							// PLL VCO doubler bit value (D)

	uint32_t f_in   = 0;							// PLL input clock freq.
	uint32_t f_vco = 0;							// PLL VCO freq.


	PMU->PLLCON = 0x80750000;			// Key value for setting PLL Frequency (Extended Mode)
	FMC->CFG = 0x0303;						// Set Flash Access Timing (Max 75MHz/(2+3) = 15.00MHz)


	if(pllInClk == XTAL4MHz || pllInClk == XTAL8MHz ||  pllInClk == XTAL10MHz) {
		PMU->CCR |= PMU_CCR_MXOSCEN_DIV_BY_1;		// Activate XTAL oscillation

		PMU->CMR |= PMU_CMR_MXOSCMNT;					// Activate monitoring function of MXOSC oscillation
		while(!(PMU->CMR & PMU_CMR_MXOSCSTS));		// Check whether MXOSC oscillation working properly

		reg_val = 0;
		reg_val |= PMU_BCCR_HCLKDIV_DIV_BY_1 \
					| PMU_BCCR_PCLKDIV_DIV_BY_1 \
					| PMU_BCCR_PLLCLKDIV_DIV_BY_1 \
					| PMU_BCCR_PLLCLKSEL_XTAL \
					| PMU_BCCR_MCLKSEL_PLL;					// Select PLL Input Freq. = XTAL / 1 = 4/8/10MHz
		PMU->BCCR = reg_val;									// Select the XTAL as a PLL Input

	}
	else if (pllInClk == IOSC16MHz) {
		PMU->CCR |= PMU_CCR_IOSC16EN_DIV_BY_1;
		PMU->BCCR |= PMU_BCCR_PLLCLKSEL_IOSC16M;	// Select the IOSC16 as a PLL Input

		reg_val = 0;
		reg_val |= PMU_BCCR_HCLKDIV_DIV_BY_1 \
					| PMU_BCCR_PCLKDIV_DIV_BY_1 \
					| PMU_BCCR_PLLCLKDIV_DIV_BY_1 \
					| PMU_BCCR_PLLCLKSEL_IOSC16M \
					| PMU_BCCR_MCLKSEL_PLL;					// Select PLL Input Freq. = IOSC16 / 2 = 8MHz
		PMU->BCCR = reg_val;									// Select the IOSC16 as a PLL Input

	}
	else {
		return PLL_WRONG;
	}

	// Set Deviders
	if(pllInClk == XTAL4MHz) 			r = 1;							// FIN = 4/(1+1) == 2
	else if(pllInClk == XTAL8MHz)		r = 3;							// FIN = 8/(1+3) == 2
	else if(pllInClk == XTAL10MHz)		r = 4;							// FIN = 10/(1+4) == 2
	else if(pllInClk == IOSC16MHz)		r = 7;							// FIN = 16/(1+7) == 2
	else return PLL_WRONG;

	f_in = pllInClk/(r+1);												// f_in is fixed to 2MHz.

	if(f_in == 2) {
		if( (setPllFreq <= 75) && (setPllFreq >= 26)) {
			n1 = setPllFreq-1;
			n2 = 0;
			p = 1;
			d = 0;
		} else if( (setPllFreq <= 25) && (setPllFreq >= 11)) {
			n1 = (setPllFreq*3)-1;
			n2 = 0;
			p = 5;
			d = 0;
		} else if( (setPllFreq <= 10) && (setPllFreq >= 4)) {
			n1 = (setPllFreq*8)-1;
			n2 = 0;
			p = 15;
			d = 0;
		} else if( (setPllFreq <= 3) && (setPllFreq >= 2)) {
			n1 = (setPllFreq*16)-1;
			n2 = 1;
			p = 15;
			d = 0;
		} else if(setPllFreq == 1) {
			n1 = (setPllFreq*32);
			n2 = 3;
			p = 15;
			d = 0;
		} else {
			return PLL_WRONG;
		}

		f_vco = f_in * n1;
		if( f_vco <= 200) {
			PMU_PLLEnable (PMU, r, n1, n2, p, d);
		}
	}
	else {
		return	PLL_WRONG;
	}

	SystemCoreClock = (setPllFreq * 1000000);
	SystemPeriClock =  (setPllFreq * 1000000);

	return PLL_OK;
}

/**
************************************************************************************
* @ Name : PMU_PLLEnable
*
* @ Parameters
*
*		- pmu			PMU
*		- prediv 			0~7
*		- mul			(0~255
*		- div			0~15
*		- postdiv			0~15
*		- vco_mode 		PLLCON_VCOMODE_NORMAL, PLLCON_VCOMODE_DOUBLE
*
************************************************************************************
*/

void PMU_PLLEnable (PMU_Type *pmu, uint32_t prediv, uint32_t mul, uint32_t div, uint32_t postdiv, uint32_t vco_mode)
{
	uint32_t			reg_val = 0;

	// PLL Setting
	reg_val = (PLLCON_PLLnRESB|PLLCON_PLLEN);
	reg_val |= (PLLCON_PREDIV_VAL(prediv)|PLLCON_MULTI_VAL(mul)|PLLCON_DIV_VAL(div)|\
		          PLLCON_POSTDIV_VAL(postdiv)|vco_mode);

	PMU->PLLCON = reg_val;

	while(!(PMU->PLLCON & PLLCON_LOCKSTS)); 			//  Is the PLL stable(lock-state)?

	PMU->PLLCON |= PLLCON_BYPASS_DISABLE;				// PLL-bypass (0 = bypass the input clock on PLL to the out-clock , 1 = multiply the input clock on PLL to the out-clock)
}


/**
************************************************************************************
* @ Name : PMU_ConfigureInterrupt
*
* @ Parameter
*		pmu			= PMU
*
*		intr_mask	= PMUCMR_SXOSCIE, PMUCMR_MXOSCIE, (PMUCMR_SXOSCIE|PMUCMR_MXOSCIE)
*
*		enable		= INTR_ENABLE, INTR_DISABLE
*
*
************************************************************************************
*/
void PMU_ConfigureInterrupt (PMU_Type *pmu, uint32_t intr_mask, uint32_t enable)
{
	uint32_t		reg_val;

	reg_val = PMU->CMR;
	reg_val &= ~(PMU_CMR_MXOSCIE); 							//disable interrupt

	PMU->CMR = (reg_val|(PMU_CMR_MXOSCIF)); 			// clear interrupt flag

	if (enable)
	{
		reg_val |= (intr_mask & (PMU_CMR_MXOSCIE)); 	// enable interrupt
		PMU->CMR = reg_val;
	}
}

/**
************************************************************************************
* @ Name : PMU_CheckResetEvent
*
* @ Parameter
*		pmu			= PMU
*
* @ Function
*		Print Reset Event
************************************************************************************
*/
void PMU_CheckResetEvent (PMU_Type *pmu)
{
	uint32_t		reg_val;

	reg_val = (pmu->RSSR);
	cprintf("\r\n\r\n[0x%08X] Reset Event by ", reg_val);

	if((reg_val&PMU_RSSR_MCKFAILRST) == PMU_RSSR_MCKFAILRST)
		cprintf("/Main Clock Failure ");
	if((reg_val&PMU_RSSR_RSTRST) == PMU_RSSR_RSTRST)
		cprintf("/nReset");
	if((reg_val&PMU_RSSR_SYSRST) == PMU_RSSR_SYSRST)
		cprintf("/Core Reset Request ");
	if((reg_val&PMU_RSSR_SWRST) == PMU_RSSR_SWRST)
		cprintf("/Software Request ");
	if((reg_val&PMU_RSSR_WDTRST) == PMU_RSSR_WDTRST)
		cprintf("/Watchdog Reset ");
	if((reg_val&PMU_RSSR_MXFAILRST) == PMU_RSSR_MXFAILRST)
		cprintf("/Main X-tal OSC Failure ");
	if ((reg_val&PMU_RSSR_LVDRST) == PMU_RSSR_LVDRST)
		cprintf("/LVD Reset ");
	if(reg_val == 0x0)
		cputs("/Power On Reset\r\n");

	pmu->RSSR = 0;
	cputs("\r\n");

}


/* --------------------------------- End Of File ------------------------------ */
