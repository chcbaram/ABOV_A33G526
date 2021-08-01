/**********************************************************************
* @file		a33g52x_pmu.h
* @brief	Contains all macro definitions and function prototypes
* 			support for SCU firmware library on AC34Mx256
* @ Version : V1.0.10
* @ date:    2020-11-16
* @author	ABOV M team
*
* Copyright(C) 2017-2020, ABOV Semiconductor
* All rights reserved.
*
**********************************************************************/

#ifndef _A33G52X_PMU_H_
#define _A33G52X_PMU_H_

/* Includes ------------------------------------------------------------------- */
#include "A33G52x.h"
#include "aa_types.h"

#ifdef __cplusplus
extern "C"
{
#endif


/* External sub crystal oscillator control */
#define EXSOSC_STOP					0x0
#define EXSOSC_EN					0x2
#define EXSOSC_EN_DIV2				0x3


/* External sub crystal oscillator stable timeout */
#define SOSC_STARTUP_TIMEOUT 0xFFFFFFFFUL

	/* low speed oscillator control */
#define LSIOSC_STOP               	0x0
#define LSIOSC_EN					0x2
#define LSIOSC_EN_DIV2            	0x3

	/* Internal high speed oscillator control */
#define HSIOSC_STOP               	0x0
#define HSIOSC_EN					0x2
#define HSIOSC_EN_DIV2            	0x3

/* External crystal oscillator control */
#define EXOSC_STOP					0x0
#define EXOSC_EN                    0x2
#define EXOSC_EN_DIV2            	0x3

/* system clock control setting */
#define SC_LSIOSC					0x00
#define SC_SOSC	   					0x01
#define SC_HSIOSC          			0x03
#define SC_HSIOSCPLL     			0x02
#define SC_EXOSC          			0x13
#define SC_EXOSCPLL     			0x12


/* External crystal oscillator stable timeout */
#define MOSC_STARTUP_TIMEOUT 0xFFFFFFFFUL

/* PLL stable timeout */
#define PLL_STARTUP_TIMEOUT 0xFFFFFFFFUL


//===================================================================
// PMUIDR
//
//				@ addr = 0x4000_0000
//
//===================================================================




//===================================================================
// PMU_MR
//
//				@ addr = 0x4000_0004
//
//===================================================================
#define PMU_MR_PVDCLP					(0x0001UL<<6)

#define PMU_MR_PREVMODE_RUN				(0x0000UL<<4)
#define PMU_MR_PREVMODE_SLEEP			(0x0001UL<<4)
#define PMU_MR_PREVMODE_PWDN			(0x0002UL<<4)
#define PMU_MR_PREVMODE_INIT				(0x0003UL<<4)
#define PMU_MR_PREVMODE_MASK			(0x0003UL<<4)

#define PMU_MR_ECLKMD							(0x0001UL<<3)
#define PMU_MR_ECLKMD_AUTOOFF			(0x0000UL<<3)
#define PMU_MR_ECLKMD_MANOFF 			(0x0001UL<<3)

#define PMU_MR_VDCLP							(0x0001UL<<2)
#define PMU_MR_VDCLP_EN						(0x0001UL<<2)
#define PMU_MR_VDCLP_DIS					(0x0000UL<<2)

#define PMU_MR_PMU_MODE_RUN				(0x0000UL<<0)
#define PMU_MR_PMU_MODE_SLEEP			(0x0001UL<<0)
#define PMU_MR_PMU_MODE_PWDN			(0x0002UL<<0)
#define PMU_MR_PMU_MODE_INIT				(0x0003UL<<0)
#define PMU_MR_PMU_MODE_MASK			(0x0003UL<<0)


//===================================================================
// PMU_CFGR
//
//				@ addr = 0x4000_0008
//
//===================================================================
#define PMU_CFGR_STBYOP							(0x0001UL<<4)
#define PMU_CFGR_STBYOP_LOW_ACTIVE		(0x0000UL<<4)
#define PMU_CFGR_STBYOP_HIGH_ACTIVE 	(0x0001UL<<4)

#define PMU_CFGR_SOFTRST						(0x0001UL<<0)



//===================================================================
// PMU_WSER
//
//				@ addr = 0x4000_0010
//
//===================================================================
#define PMU_WSER_GPIOFE					(0x0001UL<<10)
#define PMU_WSER_GPIOEE					(0x0001UL<<9)
#define PMU_WSER_GPIODE				(0x0001UL<<8)
#define PMU_WSER_GPIOCE					(0x0001UL<<7)
#define PMU_WSER_GPIOBE					(0x0001UL<<6)
#define PMU_WSER_GPIOAE				(0x0001UL<<5)
#define PMU_WSER_FRTE					(0x0001UL<<4)
#define PMU_WSER_WDTE					(0x0001UL<<3)
#define PMU_WSER_SXFAILE				(0x0001UL<<2)
#define PMU_WSER_MXFAILE				(0x0001UL<<1)
#define PMU_WSER_LVDE					(0x0001UL<<0)




//===================================================================
// PMU_WSSR
//
//				@ addr = 0x4000_0014
//
//===================================================================
#define PMU_WSSR_GPIOF					(0x0001UL<<10)
#define PMU_WSSR_GPIOE					(0x0001UL<<9)
#define PMU_WSSR_GPIOD					(0x0001UL<<8)
#define PMU_WSSR_GPIOC					(0x0001UL<<7)
#define PMU_WSSR_GPIOB					(0x0001UL<<6)
#define PMU_WSSR_GPIOA					(0x0001UL<<5)
#define PMU_WSSR_FRT					(0x0001UL<<4)
#define PMU_WSSR_WDT					(0x0001UL<<3)
#define PMU_WSSR_SXFAIL					(0x0001UL<<2)
#define PMU_WSSR_MXFAIL					(0x0001UL<<1)
#define PMU_WSSR_LVD					(0x0001UL<<0)




//===================================================================
// PMU_RSER
//
//				@ addr = 0x4000_0018
//
//===================================================================
#define PMU_RSER_MCKFAILRSTE			(0x0001UL<<7)
#define PMU_RSER_RSTRSTE				(0x0001UL<<6)
#define PMU_RSER_SYSRSTE				(0x0001UL<<5)
#define PMU_RSER_SWRSTE					(0x0001UL<<4)
#define PMU_RSER_WDTRSTE				(0x0001UL<<3)
#define PMU_RSER_SXFAILRSTE				(0x0001UL<<2)
#define PMU_RSER_MXFAILRSTE				(0x0001UL<<1)
#define PMU_RSER_LVDRSTE				(0x0001UL<<0)




//===================================================================
// PMU_RSSR
//
//				@ addr = 0x4000_001C
//
//===================================================================
#define PMU_RSSR_MCKFAILRST				(0x0001UL<<7)
#define PMU_RSSR_RSTRST					(0x0001UL<<6)
#define PMU_RSSR_SYSRST					(0x0001UL<<5)
#define PMU_RSSR_SWRST					(0x0001UL<<4)
#define PMU_RSSR_WDTRST				(0x0001UL<<3)
#define PMU_RSSR_SXFAILRST				(0x0001UL<<2)
#define PMU_RSSR_MXFAILRST				(0x0001UL<<1)
#define PMU_RSSR_LVDRST					(0x0001UL<<0)



//===================================================================
// PMU_PERR
//
//				@ addr = 0x4000_0020
//
//===================================================================
#define PMU_PERR_JTAGEN					(0x0001UL<<31)
#define PMU_PERR_PMC					(0x0001UL<<29)
#define PMU_PERR_ADC					(0x0001UL<<28)
//------------------------------------------------------------------------
#define PMU_PERR_PWM4_7				(0x0001UL<<25)
#define PMU_PERR_PWM0_3				(0x0001UL<<24)
//------------------------------------------------------------------------
#define PMU_PERR_UART3					(0x0001UL<<23)
#define PMU_PERR_UART2					(0x0001UL<<22)
#define PMU_PERR_UART1					(0x0001UL<<21)
#define PMU_PERR_UART0					(0x0001UL<<20)
//------------------------------------------------------------------------
#define PMU_PERR_I2C1					(0x0001UL<<19)
#define PMU_PERR_I2C0					(0x0001UL<<18)
#define PMU_PERR_SPI1					(0x0001UL<<17)
#define PMU_PERR_SPI0					(0x0001UL<<16)
//------------------------------------------------------------------------
#define PMU_PERR_CRC16					(0x0001UL<<14)
#define PMU_PERR_GPIOF					(0x0001UL<<13)
#define PMU_PERR_GPIOE					(0x0001UL<<12)
#define PMU_PERR_GPIOD					(0x0001UL<<11)
#define PMU_PERR_GPIOC					(0x0001UL<<10)
#define PMU_PERR_GPIOB					(0x0001UL<<9)
#define PMU_PERR_GPIOA					(0x0001UL<<8)
//------------------------------------------------------------------------
#define PMU_PERR_TC6_9					(0x0001UL<<7)
#define PMU_PERR_TC2_5					(0x0001UL<<6)
#define PMU_PERR_TC0_1					(0x0001UL<<5)
#define PMU_PERR_FRT						(0x0001UL<<4)
//------------------------------------------------------------------------
#define PMU_PERR_WDT					(0x0001UL<<3)



#define PMU_PERR_ALL_PERI				(PMU_PERR_PMC|PMU_PERR_ADC|PMU_PERR_PWM4_7|PMU_PERR_PWM0_3|\
										PMU_PERR_UART3|PMU_PERR_UART2|PMU_PERR_UART1|PMU_PERR_UART0|\
										PMU_PERR_I2C1|PMU_PERR_I2C0|PMU_PERR_SPI1|PMU_PERR_SPI0|\
										PMU_PERR_CRC16|\
										PMU_PERR_GPIOF|PMU_PERR_GPIOE|PMU_PERR_GPIOD|PMU_PERR_GPIOC|PMU_PERR_GPIOB|PMU_PERR_GPIOA|\
										PMU_PERR_TC6_9|PMU_PERR_TC2_5|PMU_PERR_TC0_1|PMU_PERR_FRT|PMU_PERR_WDT)


#define PMU_PERR_ALL_PERI_WITH_JTAG	(PMU_PERR_JTAGEN|PMU_PERR_ALL_PERI)


//===================================================================
// PMU_PER
//
//				@ addr = 0x4000_0024
//
//===================================================================
#define PMU_PER_JTAGEN				(0x0001UL<<31)
#define PMU_PER_PMC						(0x0001UL<<29)
#define PMU_PER_ADC						(0x0001UL<<28)
//------------------------------------------------------------------------
#define PMU_PER_PWM4_7				(0x0001UL<<25)
#define PMU_PER_PWM0_3				(0x0001UL<<24)
//------------------------------------------------------------------------
#define PMU_PER_UART3					(0x0001UL<<23)
#define PMU_PER_UART2					(0x0001UL<<22)
#define PMU_PER_UART1					(0x0001UL<<21)
#define PMU_PER_UART0					(0x0001UL<<20)
//------------------------------------------------------------------------
#define PMU_PER_I2C1						(0x0001UL<<19)
#define PMU_PER_I2C0						(0x0001UL<<18)
#define PMU_PER_SPI1						(0x0001UL<<17)
#define PMU_PER_SPI0						(0x0001UL<<16)
//------------------------------------------------------------------------
#define PMU_PER_CRC16 					(0x0001UL<<14)
#define PMU_PER_GPIOF					(0x0001UL<<13)
#define PMU_PER_GPIOE					(0x0001UL<<12)
#define PMU_PER_GPIOD					(0x0001UL<<11)
#define PMU_PER_GPIOC					(0x0001UL<<10)
#define PMU_PER_GPIOB					(0x0001UL<<9)
#define PMU_PER_GPIOA					(0x0001UL<<8)
//------------------------------------------------------------------------
#define PMU_PER_TC6_9					(0x0001UL<<7)
#define PMU_PER_TC2_5					(0x0001UL<<6)
#define PMU_PER_TC0_1					(0x0001UL<<5)
#define PMU_PER_FRT						(0x0001UL<<4)
//------------------------------------------------------------------------
#define PMU_PER_WDT						(0x0001UL<<3)



#define PMU_PER_MODULE_OFF_FOR_GPIO_WKUP 	(PMU_PER_ADC|PMU_PER_PWM4_7|PMU_PER_PWM0_3|\
										PMU_PER_UART3|PMU_PER_UART2|PMU_PER_UART1|PMU_PER_UART0|\
										PMU_PER_I2C1|PMU_PER_I2C0|PMU_PER_SPI1|PMU_PER_SPI0|\
										PMU_PER_TC6_9|PMU_PER_TC2_5|PMU_PER_TC0_1|PMU_PER_FRT|PMU_PER_WDT)



#define PMU_PER_MODULE_OFF_FOR_FRT_WKUP 	(PMU_PER_ADC|PMU_PER_PWM4_7|PMU_PER_PWM0_3|\
										PMU_PER_UART3|PMU_PER_UART2|PMU_PER_UART1|PMU_PER_UART0|\
										PMU_PER_I2C1|PMU_PER_I2C0|PMU_PER_SPI1|PMU_PER_SPI0|\
										PMU_PER_GPIOF|PMU_PER_GPIOD|PMU_PER_GPIOC|PMU_PER_GPIOB|PMU_PER_GPIOA|\
										PMU_PER_TC6_9|PMU_PER_TC2_5|PMU_PER_TC0_1|PMU_PER_WDT)


#define PMU_PER_MODULE_OFF_FOR_WDT_WKUP 	(PMU_PER_ADC|PMU_PER_PWM4_7|PMU_PER_PWM0_3|\
										PMU_PER_UART3|PMU_PER_UART2|PMU_PER_UART1|PMU_PER_UART0|\
										PMU_PER_I2C1|PMU_PER_I2C0|PMU_PER_SPI1|PMU_PER_SPI0|\
										PMU_PER_GPIOF|PMU_PER_GPIOD|PMU_PER_GPIOC|PMU_PER_GPIOB|PMU_PER_GPIOA|\
										PMU_PER_TC6_9|PMU_PER_TC2_5|PMU_PER_TC0_1|PMU_PER_FRT)


//===================================================================
// PMU_PCCR
//
//				@ addr = 0x4000_0028
//
//===================================================================
#define PMU_PCCR_ADC					(0x0001UL<<28)
//------------------------------------------------------------------------
#define PMU_PCCR_PWM4_7				(0x0001UL<<25)
#define PMU_PCCR_PWM0_3				(0x0001UL<<24)
//------------------------------------------------------------------------
#define PMU_PCCR_UART3					(0x0001UL<<23)
#define PMU_PCCR_UART2					(0x0001UL<<22)
#define PMU_PCCR_UART1					(0x0001UL<<21)
#define PMU_PCCR_UART0					(0x0001UL<<20)
//------------------------------------------------------------------------
#define PMU_PCCR_I2C1					(0x0001UL<<19)
#define PMU_PCCR_I2C0					(0x0001UL<<18)
#define PMU_PCCR_SPI1					(0x0001UL<<17)
#define PMU_PCCR_SPI0					(0x0001UL<<16)
//------------------------------------------------------------------------
#define PMU_PCCR_CRC16 					(0x0001UL<<14)
#define PMU_PCCR_GPIO					(0x0001UL<<8)
//------------------------------------------------------------------------
#define PMU_PCCR_TC6_9					(0x0001UL<<7)
#define PMU_PCCR_TC2_5					(0x0001UL<<6)
#define PMU_PCCR_TC0_1					(0x0001UL<<5)
#define PMU_PCCR_FRT						(0x0001UL<<4)
//------------------------------------------------------------------------
#define PMU_PCCR_WDT					(0x0001UL<<3)




#define PMU_PCCR_MODULE_OFF_FOR_GPIO_WKUP 	(PMU_PCCR_ADC|PMU_PCCR_PWM4_7|PMU_PCCR_PWM0_3|\
												PMU_PCCR_UART3|PMU_PCCR_UART2|PMU_PCCR_UART1|PMU_PCCR_UART0|\
												PMU_PCCR_I2C1|PMU_PCCR_I2C0|PMU_PCCR_SPI1|PMU_PCCR_SPI0|\
												PMU_PCCR_TC6_9|PMU_PCCR_TC2_5|PMU_PCCR_TC0_1|PMU_PCCR_FRT|PMU_PCCR_WDT)



#define PMU_PCCR_MODULE_OFF_FOR_FRT_WKUP 	(PMU_PCCR_ADC|PMU_PCCR_PWM4_7|PMU_PCCR_PWM0_3|\
												PMU_PCCR_UART3|PMU_PCCR_UART2|PMU_PCCR_UART1|PMU_PCCR_UART0|\
												PMU_PCCR_I2C1|PMU_PCCR_I2C0|PMU_PCCR_SPI1|PMU_PCCR_SPI0|\
												PMU_PCCR_GPIO|\
												PMU_PCCR_TC6_9|PMU_PCCR_TC2_5|PMU_PCCR_TC0_1|PMU_PCCR_WDT)


#define PMU_PCCR_MODULE_OFF_FOR_WDT_WKUP 	(PMU_PCCR_ADC|PMU_PCCR_PWM4_7|PMU_PCCR_PWM0_3|\
												PMU_PCCR_UART3|PMU_PCCR_UART2|PMU_PCCR_UART1|PMU_PCCR_UART0|\
												PMU_PCCR_I2C1|PMU_PCCR_I2C0|PMU_PCCR_SPI1|PMU_PCCR_SPI0|\
												PMU_PCCR_GPIO|\
												PMU_PCCR_TC6_9|PMU_PCCR_TC2_5|PMU_PCCR_TC0_1|PMU_PCCR_FRT)


//===================================================================
// PMU_CCR
//
//				@ addr = 0x4000_0030
//
//===================================================================
#define PMU_CCR_ROSCEN_DIV_BY_1		(0x0002UL<<6)
#define PMU_CCR_ROSCEN_DIV_BY_2		(0x0003UL<<6)
#define PMU_CCR_ROSCEN_MASK			(0x0003UL<<6)

#define PMU_CCR_IOSC16EN_STOP			(0x0000UL<<4)
#define PMU_CCR_IOSC16EN_DIV_BY_1		(0x0002UL<<4)
#define PMU_CCR_IOSC16EN_DIV_BY_2		(0x0003UL<<4)
#define PMU_CCR_IOSC16EN_MASK 			(0x0003UL<<4)

#define PMU_CCR_SXOSCEN_STOP			(0x0000UL<<2)
#define PMU_CCR_SXOSCEN_DIV_BY_1		(0x0002UL<<2)
#define PMU_CCR_SXOSCEN_DIV_BY_2		(0x0003UL<<2)
#define PMU_CCR_SXOSCEN_MASK			(0x0003UL<<2)

#define PMU_CCR_MXOSCEN_STOP			(0x0000UL<<0)
#define PMU_CCR_MXOSCEN_DIV_BY_1		(0x0002UL<<0)
#define PMU_CCR_MXOSCEN_DIV_BY_2		(0x0003UL<<0)
#define PMU_CCR_MXOSCEN_MASK			(0x0003UL<<0)
//--------------------------------------------------------




//===================================================================
// PMUCMR
//
//				@ addr = 0x4000_0034
//
//===================================================================
//#define PMU_CMR_SXOSCIE					(0x0001UL<<15)
#define PMU_CMR_MXOSCIE					(0x0001UL<<14)
//#define PMU_CMR_SXOSCMNT				(0x0001UL<<9)
#define PMU_CMR_MXOSCMNT				(0x0001UL<<8)
//#define PMU_CMR_SXOSCIF					(0x0001UL<<7)
#define PMU_CMR_MXOSCIF					(0x0001UL<<6)
//#define PMU_CMR_SXOSCSTS				(0x0001UL<<1)
#define PMU_CMR_MXOSCSTS				(0x0001UL<<0)



//===================================================================
// PMUMCMR
//
//				@ addr = 0x4000_0038
//
//===================================================================
#define PMU_MCMR_RECOVER 				(0x0001UL<<15)
#define PMU_MCMR_MCKIE					(0x0001UL<<14)
#define PMU_MCMR_MCKMNT					(0x0001UL<<8)
#define PMU_MCMR_MCKIF 					(0x0001UL<<6)
#define PMU_MCMR_MCKSTS 				(0x0001UL<<0)






//===================================================================
// PMUBCCR
//
//				@ addr = 0x4000_003C
//
//===================================================================
#define PMU_BCCR_PCLKDIV					(0x0001UL<<10)
#define PMU_BCCR_PCLKDIV_DIV_BY_1		(0x0000UL<<10)
#define PMU_BCCR_PCLKDIV_DIV_BY_2		(0x0001UL<<10)
#define PMU_BCCR_PCLKDIV_MASK			(0x0001UL<<10)


#define PMU_BCCR_HCLKDIV_DIV_BY_1		(0x0000UL<<8)
#define PMU_BCCR_HCLKDIV_DIV_BY_2		(0x0002UL<<8)
#define PMU_BCCR_HCLKDIV_DIV_BY_4		(0x0003UL<<8)
#define PMU_BCCR_HCLKDIV_MASK			(0x0003UL<<8)

#define PMU_BCCR_PLLCLKDIV				(0x0001UL<<5)
#define PMU_BCCR_PLLCLKDIV_DIV_BY_1		(0x0000UL<<5)
#define PMU_BCCR_PLLCLKDIV_DIV_BY_2		(0x0001UL<<5)

#define PMU_BCCR_PLLCLKSEL				(0x0001UL<<4)
#define PMU_BCCR_PLLCLKSEL_IOSC16M		(0x0000UL<<4)
#define PMU_BCCR_PLLCLKSEL_XTAL			(0x0001UL<<4)


#define PMU_BCCR_MCLKSEL_RING_OSC		(0x0000UL<<0)
#define PMU_BCCR_MCLKSEL_SUB_OSC			(0x0001UL<<0)
#define PMU_BCCR_MCLKSEL_PLL				(0x0002UL<<0)
#define PMU_BCCR_MCLKSEL_PLL_BYPASS		(0x0003UL<<0)
#define PMU_BCCR_MCLKSEL_MASK			(0x0003UL<<0)





//===================================================================
// PMU_PCSR
//
//				@ addr = 0x4000_0040
//
//===================================================================
#define PMU_PCSR_T69CS_MAIN_XTAL		(0x0000UL<<8)
#define PMU_PCSR_T69CS_IOSC16M			(0x0001UL<<8)
#define PMU_PCSR_T69CS_SUB_XTAL		(0x0002UL<<8)
#define PMU_PCSR_T69CS_IOSC1M			(0x0003UL<<8)
#define PMU_PCSR_T69CS_MASK			(0x0003UL<<8)

#define PMU_PCSR_T25CS_MAIN_XTAL		(0x0000UL<<6)
#define PMU_PCSR_T25CS_IOSC16M			(0x0001UL<<6)
#define PMU_PCSR_T25CS_SUB_XTAL		(0x0002UL<<6)
#define PMU_PCSR_T25CS_IOSC1M			(0x0003UL<<6)
#define PMU_PCSR_T25CS_MASK			(0x0003UL<<6)

#define PMU_PCSR_T01CS_MAIN_XTAL		(0x0000UL<<4)
#define PMU_PCSR_T01CS_IOSC16M			(0x0001UL<<4)
#define PMU_PCSR_T01CS_SUB_XTAL		(0x0002UL<<4)
#define PMU_PCSR_T01CS_IOSC1M			(0x0003UL<<4)
#define PMU_PCSR_T01CS_MASK			(0x0003<<4)

#define PMU_PCSR_FRTCS_MAIN_XTAL		(0x0000UL<<2)
#define PMU_PCSR_FRTCS_IOSC16M			(0x0001UL<<2)
#define PMU_PCSR_FRTCS_SUB_XTAL		(0x0002UL<<2)
#define PMU_PCSR_FRTCS_IOSC1M			(0x0003UL<<2)
#define PMU_PCSR_FRTCS_MASK			(0x0003UL<<2)

#define PMU_PCSR_WDTCS_MAIN_XTAL		(0x0000UL<<0)
#define PMU_PCSR_WDTCS_IOSC16M		(0x0001UL<<0)
#define PMU_PCSR_WDTCS_SUB_XTAL		(0x0002UL<<0)
#define PMU_PCSR_WDTCS_RINGOSC		(0x0003UL<<0)
#define PMU_PCSR_WDTCS_MASK			(0x0003UL<<0)



//===================================================================
// PMU_COR
//
//				@ addr = 0x4000_0044
//
//===================================================================
#define PMU_COR_TRACEKEY_B 				(0x000BUL<<12)
#define PMU_COR_TRACEKEY_A 				(0x000AUL<<12)

#define PMU_COR_TRACEDIV_VAL(n)			(((n)&0x07UL)<<8)
#define PMU_COR_TRACEDIV_MASK			(0x0007UL<<8)

#define PMU_COR_TRACECLK_INV			(0x0001UL<<7)
#define PMU_COR_TRACECLK_DELAY			(0x0001UL<<6)

#define PMU_COR_CLKOSEL 					(0x0001UL<<5)
#define PMU_COR_CLKOSEL_PLL 			(0x0000UL<<5)
#define PMU_COR_CLKOSEL_MCLK 			(0x0001UL<<5)


#define PMU_COR_CLKOEN 					(0x0001UL<<4)
#define PMU_COR_CLKOEN_CLKO_OFF		(0x0000UL<<4)
#define PMU_COR_CLKOEN_CLKO_ON			(0x0001UL<<4)

#define PMU_COR_CLKODIV_VAL(n)			(((n)&0x000FUL)<<0)
#define PMU_COR_CLKODIV_MASK			(0x000FUL<<0)


#define PMU_COR_MASK					(0x003FUL<<0)			// For both legacy mode and normal mode





//===================================================================
// PLLCON
//
//				@ addr = 0x4000_0050
//
//===================================================================
#define PLL_SOURCE_XTAL
#define PLLCON_VCOMODE					(0x0001UL<<28)
#define PLLCON_VCOMODE_NORMAL	(0x0000UL<<28)
#define PLLCON_VCOMODE_DOUBLE	(0x0001UL<<28)

#define PLLCON_MULTI_VAL(n) 			(((n)&0x00FFUL)<<20)
#define PLLCON_MULTI_MASK 				(0x00FFUL<<20)

#define PLLCON_DIV_VAL(n) 				(((n)&0x000FUL)<<16)
#define PLLCON_DIV_MASK 				(0x000FUL<<16)


#define PLLCON_PLLnRESB					(0x0001UL<<15)
#define PLLCON_PLLEN						(0x0001UL<<14)
#define PLLCON_BYPASS					(0x0001UL<<13)
#define PLLCON_BYPASS_DISABLE		(0x0001UL<<13)
#define PLLCON_LOCKSTS					(0x0001UL<<12)

#define PLLCON_PREDIV_VAL(n)			(((n)&0x0007UL)<<8)
#define PLLCON_PREDIV_MASK 			(0x0007UL<<8)

#define PLLCON_POSTDIV_VAL(n) 		(((n)&0x000FUL)<<0)
#define PLLCON_POSTDIV_MASK  		(0x000FUL<<0)

typedef enum _pllStatus {
	PLL_OK = 0,
	PLL_WRONG = -1,
} pllStatus;

typedef enum _pllInClk {
	XTAL4MHz = 4,
	XTAL8MHz = 8,
	XTAL10MHz = 10,
	IOSC16MHz= 16,
} pllInClk;

typedef enum _pllFreq {
	PLL1MHz = 1,
	PLL2MHz = 2,
	PLL3MHz = 3,
	PLL4MHz = 4,
	PLL5MHz = 5,
	PLL6MHz = 6,
	PLL7MHz = 7,
	PLL8MHz = 8,
	PLL9MHz = 9,
	PLL10MHz = 10,
	PLL11MHz = 11,
	PLL12MHz = 12,
	PLL13MHz = 13,
	PLL14MHz = 14,
	PLL15MHz = 15,
	PLL16MHz = 16,
	PLL17MHz = 17,
	PLL18MHz = 18,
	PLL19MHz = 19,
	PLL20MHz = 20,
	PLL21MHz = 21,
	PLL22MHz = 22,
	PLL23MHz = 23,
	PLL24MHz = 24,
	PLL25MHz = 25,
	PLL26MHz = 26,
	PLL27MHz = 27,
	PLL28MHz = 28,
	PLL29MHz = 29,
	PLL30MHz = 30,
	PLL31MHz = 31,
	PLL32MHz = 32,
	PLL33MHz = 33,
	PLL34MHz = 34,
	PLL35MHz = 35,
	PLL36MHz = 36,
	PLL37MHz = 37,
	PLL38MHz = 38,
	PLL39MHz = 39,
	PLL40MHz = 40,
	PLL41MHz = 41,
	PLL42MHz = 42,
	PLL43MHz = 43,
	PLL44MHz = 44,
	PLL45MHz = 45,
	PLL46MHz = 46,
	PLL47MHz = 47,
	PLL48MHz = 48,
	PLL49MHz = 49,
	PLL50MHz = 50,
	PLL51MHz = 51,
	PLL52MHz = 52,
	PLL53MHz = 53,
	PLL54MHz = 54,
	PLL55MHz = 55,
	PLL56MHz = 56,
	PLL57MHz = 57,
	PLL58MHz = 58,
	PLL59MHz = 59,
	PLL60MHz = 60,
	PLL61MHz = 61,
	PLL62MHz = 62,
	PLL63MHz = 63,
	PLL64MHz = 64,
	PLL65MHz = 65,
	PLL66MHz = 66,
	PLL67MHz = 67,
	PLL68MHz = 68,
	PLL69MHz = 69,
	PLL70MHz = 70,
	PLL71MHz = 71,
	PLL72MHz = 72,
	PLL73MHz = 73,
	PLL74MHz = 74,
	PLL75MHz = 75,
} pllFreq;

//===================================================================
// LVDCON
//
//				@ addr = 0x4000_0054
//
//===================================================================
#define LVDCON_LVDEN					(0x0001UL<<15)
#define LVDCON_LVDRF					(0x0001UL<<14)
#define LVDCON_LVDREN					(0x0001UL<<11)

#define LVDCON_LVDRL_Pos					(8)
#define LVDCON_LVDRL_2_60V				(0x0000UL<<8)
#define LVDCON_LVDRL_2_80V				(0x0001UL<<8)
#define LVDCON_LVDRL_3_00V				(0x0002UL<<8)
#define LVDCON_LVDRL_3_30V				(0x0003UL<<8)
#define LVDCON_LVDRL_3_75V				(0x0004UL<<8)
#define LVDCON_LVDRL_4_00V				(0x0005UL<<8)
#define LVDCON_LVDRL_4_25V				(0x0006UL<<8)
#define LVDCON_LVDRL_4_50V				(0x0007UL<<8)
#define LVDCON_LVDRL_MASK				(0x0007UL<<8)
#define LVDCON_LVDRL_VAL(n)				(((n)&0x0007UL)<<8)

#define LVDCON_LVDIF					(0x0001UL<<6)
#define LVDCON_LVDICS					(0x0001UL<<5)
#define LVDCON_LVDIEN					(0x0001UL<<3)

#define LVDCON_LVDIL_2_60V				(0x0000UL<<0)
#define LVDCON_LVDIL_2_80V				(0x0001UL<<0)
#define LVDCON_LVDIL_3_00V				(0x0002UL<<0)
#define LVDCON_LVDIL_3_30V				(0x0003UL<<0)
#define LVDCON_LVDIL_3_75V				(0x0004UL<<0)
#define LVDCON_LVDIL_4_00V				(0x0005UL<<0)
#define LVDCON_LVDIL_4_25V				(0x0006UL<<0)
#define LVDCON_LVDIL_4_50V				(0x0007UL<<0)
#define LVDCON_LVDIL_MASK				(0x0007UL<<0)
#define LVDCON_LVDIL_VAL(n)				(((n)&0x0007UL)<<0)


//===================================================================
// VDCCON
//
//				@ addr = 0x4000_0058
//
//===================================================================
#define VDCCON_DFLVL 					(0x0001UL<<31)

#define VDCCON_DFLVL_EN_VAL(n)			(((n)&0x0003UL)<<22)




//===================================================================
// IOSC16TRIM
//
//				@ addr = 0x4000_005C
//
//===================================================================
#define IOSC16TRIM_LT_EN 				(0x0001UL<<20)
#define IOSC16TRIM_LTM_EN 				(0x0001UL<<19)
#define IOSC16TRIM_TSL_EN 				(0x0001UL<<18)
#define IOSC16TRIM_UDCH_EN 			(0x0001UL<<17)
#define IOSC16TRIM_TCAL_EN 			(0x0001UL<<16)

#define IOSC16TRIM_LT_VAL(n) 			(((n)&0x000FUL)<<10)
#define IOSC16TRIM_LTM_VAL(n) 			(((n)&0x0003UL)<<8)
#define IOSC16TRIM_TSL_VAL(n) 			(((n)&0x0007UL)<<5)
#define IOSC16TRIM_UDCH_VAL(n) 		(((n)&0x0003UL)<<3)
#define IOSC16TRIM_TCAL_VAL(n) 			(((n)&0x0007UL)<<0)



//===================================================================
// EOSCCON
//
//				@ addr = 0x4000_0060
//
//===================================================================
#define EOSCCON_MAGIC_CODE 			(0x18A2UL<<16)

#define EOSCCON_SOSCNF					(0x0001UL<<15)
#define EOSCCON_SOSCNF_ON				(0x0000UL<<15)
#define EOSCCON_SOSCNF_OFF			(0x0001UL<<15)

#define EOSCCON_SOSCISEL_VAL(n)		(((n)&0x0003UL)<<12)
#define EOSCCON_SOSCISEL_MASK 		(0x0003UL<<12)

#define EOSCCON_MOSCNF 				(0x0001UL<<7)
#define EOSCCON_MOSCNF_ON 			(0x0000UL<<7)
#define EOSCCON_MOSCNF_OFF 			(0x0001UL<<7)

#define EOSCCON_MOSCNFSEL_VAL(n) 		(((n)&0x0003UL)<<4)
#define EOSCCON_MOSCNFSEL_MASK 		(0x0003UL<<4)

#define EOSCCON_MOSCISEL_VAL(n) 		(((n)&0x0003UL)<<0)
#define EOSCCON_MOSCISEL_MASK 		(0x0003UL<<0)




//===================================================================
// EXTMODER
//
//				@ addr = 0x4000_0070
//
//===================================================================



//===================================================================
//	PMULEGACY
//
//		@ address		= 0x4000_00F8
//
//===================================================================
#define PMU_LEGACY_MODE						(0x0001UL<<31)
#define PMU_LEGACY_MODE_NORMAL				(0x0000UL<<31)
#define PMU_LEGACY_MODE_LEGACY 				(0x0001UL<<31)


#define PMU_LEGACY_LEGACY_STEP1 				(0xDADAUL<<0)
#define PMU_LEGACY_LEGACY_STEP2 				(0xDA00UL<<0)

#define PMU_LEGACY_NORMAL_STEP1 				(0xDADAUL<<0)
#define PMU_LEGACY_NORMAL_STEP2 				(0xDAADUL<<0)



//===================================================================
// macros
//===================================================================

void 	SCU_SetSOSC(uint32_t esosccon);
Status 	SCU_WaitForSOSCStartUp(void);
void 	SCU_SetLSIOSC(uint32_t ringosc);
void 	SCU_SetHSIOSC(uint32_t hsiosc);
void 	SCU_SetMOSC(uint32_t eosccon);
Status 	SCU_WaitForMOSCStartUp(void);
void	SCU_SetClockMonitoring(uint32_t enable);
void 	SCU_ChangeSysClk(uint32_t sysclkcon);
void 	SCU_SetCOR(uint8_t divval, FunctionalState endis);
Status 	SCU_SetPLLandWaitForPLLStartUp(FunctionalState pllsetstate, uint8_t selbypass, uint8_t selfin,  uint8_t PREDIV, uint8_t POSTDIV1, uint8_t POSTDIV2, uint8_t OUTDIV);

//===================================================================
// function declarations
//===================================================================
void PMU_PLLEnable (PMU_Type *pmu, uint32_t prediv, uint32_t mul, uint32_t div, uint32_t postdiv, uint32_t vco_mode);
int32_t PMU_SetPLLFreq(PMU_Type *pmu, uint32_t pllInClk, uint32_t setPllFreq)	;			// PLL Calcuator
void PMU_ConfigureInterrupt (PMU_Type *pmu, uint32_t intr_mask, uint32_t enable);
void PMU_CheckResetEvent (PMU_Type *pmu);


#ifdef __cplusplus
}
#endif

#endif /* end _a33g52x_PMU_H_ */

/* --------------------------------- End Of File ------------------------------ */
