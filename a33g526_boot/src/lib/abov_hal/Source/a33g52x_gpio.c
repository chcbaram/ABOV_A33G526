/**
**********************(C) Copyright 2017 ABOV Semiconductor Co., Ltd *******************
* @ File : a33g52x_gpio.c
*
* @ Author : Application Team, ABOV Semiconductor Co., Ltd
*
* @ Version : V1.0.10
*
* @ date:    2020-11-16
*
* @ Description
*   ABOV Semiconductor is supplying this software for use with A33G52x
*   processor. This software contains the confidential and proprietary information
*   of ABOV Semiconductor Co., Ltd ("Confidential Information").
*
*
**************************************************************************************
* DISCLAIMER
*
* 	THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* 	WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* 	TIME. AS A RESULT, ABOV SEMICONDUCTOR DISCLAIMS ALL LIABILITIES FROM ANY
* 	DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* 	FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* 	CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
**************************************************************************************
*/




#include <stdint.h>
#include "A33G52x.h"
#include "a33g52x_gpio.h"



/**
************************************************************************************
* @ Name : GPIO_OutputHigh
*
* @ Parameter
*		- gpio		= GPIO_A ~ GPIO_F
*		- pin_no		= PIN_0 ~ PIN_15
*
*
************************************************************************************
*/
void GPIO_OutputHigh (GPIO_Type * const Px, uint32_t pin_no)
{

	uint32_t 	reg_val;

	//---------------------------------------------------------------------------
	// bit set
	//
	// 					PASRR		@ address = 0x4000_0308
	// 					PBSRR		@ address = 0x4000_0318
	// 					PCSRR		@ address = 0x4000_0328
	// 					PDSRR		@ address = 0x4000_0338
	// 					PESRR		@ address = 0x4000_0348
	// 					PFSRR		@ address = 0x4000_0358
	//
	//---------------------------------------------------------------------------
	reg_val = (0x0001<<pin_no);
	Px->SRR = reg_val;

}




/**
************************************************************************************
* @ Name : GPIO_OutputLow
*
* @ Parameter
*		- gpio		= GPIO_A ~ GPIO_F
*		- pin_no		= PIN_0 ~ PIN_15
*
*
************************************************************************************
*/
void GPIO_OutputLow (GPIO_Type * const Px, uint32_t pin_no)
{

	uint32_t 	reg_val;


	//---------------------------------------------------------------------------
	// bit clear
	//
	// 					PASRR		@ address = 0x4000_0308
	// 					PBSRR		@ address = 0x4000_0318
	// 					PCSRR		@ address = 0x4000_0328
	// 					PDSRR		@ address = 0x4000_0338
	// 					PESRR		@ address = 0x4000_0348
	// 					PFSRR		@ address = 0x4000_0358
	//
	//---------------------------------------------------------------------------
	reg_val = (0x0001UL<<(pin_no+16));
	Px->SRR = reg_val;


}


/*-------------------------------------------------------------------------*//**
 * @brief         Set Value for bits that have output direction on GPIO port.
 * @param[in]     Px
 *                   Pointer to a target peripheral.
 *                   -  PA ~ PF
 * @param[in]     bitValue
 *                   Value that contains all bits on GPIO to set.
 *                   -  0x0000 ~ 0xffff
 *                   -  Example: Use the value of 0x0003 to set bit 0 and bit 1.
 * @return        none
 * @remark        Available GPIO Pin: PA[9:0], PB[12:0], PC[11:0], PD[7:0], PE[4:0], PF[3:0]
 *//*-------------------------------------------------------------------------*/
void GPIO_SetValue( GPIO_Type* Px, uint16_t bitValue )
{
   Px->SRR = bitValue;
}

/*-------------------------------------------------------------------------*//**
 * @brief         Clear Value for bits that have output direction on GPIO port.
 * @param[in]     Px
 *                   Pointer to a target peripheral.
 *                   -  PA ~ PF
 * @param[in]     bitValue
 *                   Value that contains all bits on GPIO to clear.
 *                   -  0x0000 ~ 0xffff
 *                   -  Example: Use the value of 0x0003 to clear bit 0 and bit 1.
 * @return        none
 * @remark        Available GPIO Pin: PA[9:0], PB[12:0], PC[11:0], PD[7:0], PE[4:0], PF[3:0]
 *//*-------------------------------------------------------------------------*/
void GPIO_ClearValue( GPIO_Type* Px, uint16_t bitValue )
{
   Px->SRR = (bitValue << 16);
}


/**
************************************************************************************
* @ Name : GPIO_OutputLow
*
* @ Parameter
*		- gpio		= GPIO_A ~ GPIO_F
*		- pin_no		= PIN_0 ~ PIN_15
*
*
************************************************************************************
*/
uint16_t GPIO_ReadValue (GPIO_Type * const Px)
{
	//---------------------------------------------------------------------------
	// Input Data Register
	//
	// 					PAIDR		@ address = 0x4000_0304
	// 					PBIDR		@ address = 0x4000_0314
	// 					PCIDR		@ address = 0x4000_0324
	// 					PDIDR		@ address = 0x4000_0334
	// 					PEIDR		@ address = 0x4000_0344
	// 					PFIDR		@ address = 0x4000_0354
	//
	//---------------------------------------------------------------------------
	return (Px->IDR);
}

