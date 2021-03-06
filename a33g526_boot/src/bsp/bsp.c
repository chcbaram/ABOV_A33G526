/*
 * bsp.c
 *
 *  Created on: 2021. 7. 26.
 *      Author: baram
 */


#include "bsp.h"



static volatile uint32_t systick_counter = 0;
extern uint32_t __isr_vector_addr;


static void PCU_Init(void);


void SysTick_Handler(void)
{
  systick_counter++;
}





bool bspInit(void)
{
  PCU_Init();

  SCB->VTOR = (uint32_t)&__isr_vector_addr;

  SystemInit();
  SystemCoreClockUpdate();               // 74Mhz


  SysTick_Config(SystemCoreClock/1000);  // 1ms interrupt
  SysTick_Run (SysTick, INTR_ENABLE);
  __enable_irq();


  return true;
}

void bspDeInit(void)
{
  // Disable Interrupts
  //
  for (int i=0; i<8; i++)
  {
    NVIC->ICER[i] = 0xFFFFFFFF;
    __DSB();
    __ISB();
  }
  SysTick->CTRL = 0;
}

void delay(uint32_t time_ms)
{
  uint32_t pre_time = systick_counter;

  while(systick_counter-pre_time < time_ms);
}

uint32_t millis(void)
{
  return systick_counter;
}





void PCU_Init(void)
{
  //Peripheral Enable Register 1  0:Disable, 1:Enable
  PMU->PER=PMU->PER
    | (1<<13)   // GPIOF
    | (1<<12)   // GPIOE
    | (1<<11)   // GPIOD
    | (1<<10)   // GPIOC
    | (1<<9)    // GPIOB
    | (1<<8)    // GPIOA
    ;
//Peripheral Clock Enable Register 1 0:Disable, 1:Enable
  PMU->PCCR=PMU->PCCR
    | (1<<8)    // GPIO
    ;

  //--------------------------------------------------------------
  //  PORT INIT
  //    PA, PB, PC, PD, PE, PF
  //--------------------------------------------------------------
  // PORT - A
  PCA->MR = 0
    | (0x0UL<<30)              // 0:PA15    1:T9C     2:        3:AN15
    | (0x0UL<<28)              // 0:PA14    1:T8C     2:        3:AN14
    | (0x0UL<<26)              // 0:PA13    1:T7C     2:        3:
    | (0x0UL<<24)              // 0:PA12    1:T6C     2:        3:
    | (0x0UL<<22)              // 0:PA11    1:T5C     2:        3:
    | (0x0UL<<20)              // 0:PA10    1:T4C     2:        3:
    | (0x0UL<<18)              // 0:PA9     1:T3C     2:        3:
    | (0x0UL<<16)              // 0:PA8     1:T2C     2:        3:
    | (0x0UL<<14)              // 0:PA7     1:T1C     2:        3:AN7
    | (0x0UL<<12)              // 0:PA6     1:T0C     2:        3:AN6
    | (0x0UL<<10)              // 0:PA5     1:        2:        3:AN5
    | (0x0UL<<8)               // 0:PA4     1:        2:        3:AN4
    | (0x0UL<<6)               // 0:PA3     1:        2:        3:AN3
    | (0x0UL<<4)               // 0:PA2     1:        2:        3:AN2
    | (0x0UL<<2)               // 0:PA1     1:        2:        3:AN1
    | (0x0UL<<0)               // 0:PA0     1:        2:        3:AN0
    ;

  PCA->CR = 0              // 0 : Output(Push-pull) Mode, 1 : Output(Open-drain) Mode,  2 : Input,  3: Analog
    | (0x3UL<<30)              // P15
    | (0x3UL<<28)              // P14
    | (0x3UL<<26)              // P13
    | (0x3UL<<24)              // P12
    | (0x3UL<<22)              // P11
    | (0x3UL<<20)              // P10
    | (0x3UL<<18)              // P9
    | (0x3UL<<16)              // P8
    | (0x3UL<<14)              // P7
    | (0x3UL<<12)              // P6
    | (0x3UL<<10)              // P5
    | (0x3UL<<8)              // P4
    | (0x3UL<<6)              // P3
    | (0x3UL<<4)              // P2
    | (0x3UL<<2)              // P1
    | (0x3UL<<0)              // P0
    ;

  PCA->PCR = 0
    | (0x0UL<<31)             // P15    0: Pull up,     1: Pull down
    | (0x0UL<<30)             // P14    0: Pull up,     1: Pull down
    | (0x0UL<<29)             // P13    0: Pull up,     1: Pull down
    | (0x0UL<<28)             // P12    0: Pull up,     1: Pull down
    | (0x0UL<<27)             // P11    0: Pull up,     1: Pull down
    | (0x0UL<<26)             // P10    0: Pull up,     1: Pull down
    | (0x0UL<<25)             // P9     0: Pull up,     1: Pull down
    | (0x0UL<<24)             // P8     0: Pull up,     1: Pull down
    | (0x0UL<<23)             // P7     0: Pull up,     1: Pull down
    | (0x0UL<<22)             // P6     0: Pull up,     1: Pull down
    | (0x0UL<<21)             // P5     0: Pull up,     1: Pull down
    | (0x0UL<<20)             // P4     0: Pull up,     1: Pull down
    | (0x0UL<<19)             // P3     0: Pull up,     1: Pull down
    | (0x0UL<<18)             // P2     0: Pull up,     1: Pull down
    | (0x0UL<<17)             // P1     0: Pull up,     1: Pull down
    | (0x0UL<<16)             // P0     0: Pull up,     1: Pull down
    | (0x0UL<<15)             // P15    0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<14)             // P14    0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<13)             // P13    0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<12)             // P12    0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<11)             // P11    0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<10)             // P10    0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<9)              // P9     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<8)              // P8     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<7)              // P7     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<6)              // P6     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<5)              // P5     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<4)              // P4     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<3)              // P3     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<2)              // P2     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<1)              // P1     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<0)              // P0     0: Disable PU/PD  1: Enable PU/PD
    ;

//////////////////////////////////////////////////////////////////////////////////////////////////////
  // PORT - B
  PCB->MR = 0
    | (0x0UL<<30)              // 0:PB15    1:SDA0      2:        3:
    | (0x0UL<<28)              // 0:PB14    1:SCL0      2:        3:
    | (0x0UL<<26)              // 0:PB13    1:MISO0     2:        3:
    | (0x0UL<<24)              // 0:PB12    1:MOSI0     2:        3:
    | (0x0UL<<22)              // 0:PB11    1:SCK0      2:        3:
    | (0x0UL<<20)              // 0:PB10    1:SS0     2:        3:
    | (0x0UL<<18)              // 0:PB9     1:T9O     2:        3:
    | (0x0UL<<16)              // 0:PB8     1:T8O     2:        3:
    | (0x0UL<<14)              // 0:PB7     1:T7O     2:        3:
    | (0x0UL<<12)              // 0:PB6     1:T6O     2:        3:
    | (0x0UL<<10)              // 0:PB5     1:T5O     2:        3:
    | (0x0UL<<8)               // 0:PB4     1:T4O     2:        3:
    | (0x0UL<<6)               // 0:PB3     1:T3O     2:        3:
    | (0x0UL<<4)               // 0:PB2     1:T2O     2:        3:
    | (0x0UL<<2)               // 0:PB1     1:T1O     2:        3:
    | (0x0UL<<0)               // 0:PB0     1:T0O     2:        3:
    ;

  PCB->CR = 0              // 0 : Output(Push-pull) Mode, 1 : Output(Open-drain) Mode,  2 : Input,  3: Analog
    | (0x3UL<<30)              // P15
    | (0x3UL<<28)              // P14
    | (0x3UL<<26)              // P13
    | (0x3UL<<24)              // P12
    | (0x3UL<<22)              // P11
    | (0x3UL<<20)              // P10
    | (0x3UL<<18)              // P9
    | (0x3UL<<16)              // P8
    | (0x3UL<<14)              // P7
    | (0x3UL<<12)              // P6
    | (0x3UL<<10)              // P5
    | (0x3UL<<8)              // P4
    | (0x3UL<<6)              // P3
    | (0x3UL<<4)              // P2
    | (0x3UL<<2)              // P1
    | (0x3UL<<0)              // P0
    ;

  PCB->PCR = 0
    | (0x0UL<<31)             // P15    0: Pull up,     1: Pull down
    | (0x0UL<<30)             // P14    0: Pull up,     1: Pull down
    | (0x0UL<<29)             // P13    0: Pull up,     1: Pull down
    | (0x0UL<<28)             // P12    0: Pull up,     1: Pull down
    | (0x0UL<<27)             // P11    0: Pull up,     1: Pull down
    | (0x0UL<<26)             // P10    0: Pull up,     1: Pull down
    | (0x0UL<<25)             // P9     0: Pull up,     1: Pull down
    | (0x0UL<<24)             // P8     0: Pull up,     1: Pull down
    | (0x0UL<<23)             // P7     0: Pull up,     1: Pull down
    | (0x0UL<<22)             // P6     0: Pull up,     1: Pull down
    | (0x0UL<<21)             // P5     0: Pull up,     1: Pull down
    | (0x0UL<<20)             // P4     0: Pull up,     1: Pull down
    | (0x0UL<<19)             // P3     0: Pull up,     1: Pull down
    | (0x0UL<<18)             // P2     0: Pull up,     1: Pull down
    | (0x0UL<<17)             // P1     0: Pull up,     1: Pull down
    | (0x0UL<<16)             // P0     0: Pull up,     1: Pull down
    | (0x0UL<<15)             // P15    0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<14)             // P14    0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<13)             // P13    0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<12)             // P12    0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<11)             // P11    0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<10)             // P10    0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<9)              // P9     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<8)              // P8     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<7)              // P7     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<6)              // P6     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<5)              // P5     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<4)              // P4     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<3)              // P3     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<2)              // P2     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<1)              // P1     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<0)              // P0     0: Disable PU/PD  1: Enable PU/PD
    ;

//////////////////////////////////////////////////////////////////////////////////////////////////////
  // PORT - C
  PCC->MR = 0
    | (0x0UL<<30)              // 0:PC15    1:XTALI     2:CLKIN     3:
    | (0x0UL<<28)              // 0:PC14    1:XTALO     2:        3:
    | (0x0UL<<26)              // 0:PC13    1:CLKO      2:        3:
    | (0x0UL<<24)              // 0:PC12    1:STBYO     2:        3:
    | (0x0UL<<22)              // 0:PC11    1:TXD2      2:        3:
    | (0x0UL<<20)              // 0:PC10    1:RXD2      2:        3:
    | (0x0UL<<18)              // 0:PC9     1:TXD0      2:        3:
    | (0x0UL<<16)              // 0:PC8     1:RXD0      2:        3:
    | (0x0UL<<14)              // 0:PC7     1:        2:        3:
    | (0x1UL<<12)              // 0:PC6     1:nRESET    2:        3:
    | (0x0UL<<10)              // 0:PC5     1:        2:        3:
    | (0x1UL<<8)               // 0:PC4     1:TDO     2:        3:
    | (0x1UL<<6)               // 0:PC3     1:TCK     2:        3:
    | (0x1UL<<4)               // 0:PC2     1:TMD     2:        3:
    | (0x1UL<<2)               // 0:PC1     1:TDI     2:        3:
    | (0x1UL<<0)               // 0:PC0     1:nTRST     2:        3:
    ;

  PCC->CR = 0              // 0 : Output(Push-pull) Mode, 1 : Output(Open-drain) Mode,  2 : Input,  3: Analog
    | (0x3UL<<30)              // P15
    | (0x3UL<<28)              // P14
    | (0x3UL<<26)              // P13
    | (0x3UL<<24)              // P12
    | (0x3UL<<22)              // P11
    | (0x3UL<<20)              // P10
    | (0x3UL<<18)              // P9
    | (0x3UL<<16)              // P8
    | (0x3UL<<14)              // P7
    | (0x2UL<<12)              // P6
    | (0x3UL<<10)              // P5
    | (0x0UL<<8)              // P4
    | (0x2UL<<6)              // P3
    | (0x2UL<<4)              // P2
    | (0x2UL<<2)              // P1
    | (0x2UL<<0)              // P0
    ;

  PCC->PCR = 0
    | (0x0UL<<31)             // P15    0: Pull up,     1: Pull down
    | (0x0UL<<30)             // P14    0: Pull up,     1: Pull down
    | (0x0UL<<29)             // P13    0: Pull up,     1: Pull down
    | (0x0UL<<28)             // P12    0: Pull up,     1: Pull down
    | (0x0UL<<27)             // P11    0: Pull up,     1: Pull down
    | (0x0UL<<26)             // P10    0: Pull up,     1: Pull down
    | (0x0UL<<25)             // P9     0: Pull up,     1: Pull down
    | (0x0UL<<24)             // P8     0: Pull up,     1: Pull down
    | (0x0UL<<23)             // P7     0: Pull up,     1: Pull down
    | (0x0UL<<22)             // P6     0: Pull up,     1: Pull down
    | (0x0UL<<21)             // P5     0: Pull up,     1: Pull down
    | (0x0UL<<20)             // P4     0: Pull up,     1: Pull down
    | (0x0UL<<19)             // P3     0: Pull up,     1: Pull down
    | (0x0UL<<18)             // P2     0: Pull up,     1: Pull down
    | (0x0UL<<17)             // P1     0: Pull up,     1: Pull down
    | (0x0UL<<16)             // P0     0: Pull up,     1: Pull down
    | (0x0UL<<15)             // P15    0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<14)             // P14    0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<13)             // P13    0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<12)             // P12    0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<11)             // P11    0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<10)             // P10    0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<9)              // P9     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<8)              // P8     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<7)              // P7     0: Disable PU/PD  1: Enable PU/PD
    | (0x1UL<<6)              // P6     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<5)              // P5     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<4)              // P4     0: Disable PU/PD  1: Enable PU/PD
    | (0x1UL<<3)              // P3     0: Disable PU/PD  1: Enable PU/PD
    | (0x1UL<<2)              // P2     0: Disable PU/PD  1: Enable PU/PD
    | (0x1UL<<1)              // P1     0: Disable PU/PD  1: Enable PU/PD
    | (0x1UL<<0)              // P0     0: Disable PU/PD  1: Enable PU/PD
    ;

//////////////////////////////////////////////////////////////////////////////////////////////////////
  // PORT - D
  PCD->MR = 0
    | (0x0UL<<30)              // 0:PD15    1:SDA1      2:        3:
    | (0x0UL<<28)              // 0:PD14    1:SCL1      2:        3:
    | (0x0UL<<26)              // 0:PD13    1:TXD1      2:        3:
    | (0x0UL<<24)              // 0:PD12    1:RXD1      2:        3:
    | (0x0UL<<22)              // 0:PD11    1:MISO1     2:        3:
    | (0x0UL<<20)              // 0:PD10    1:MOSI1     2:        3:
    | (0x0UL<<18)              // 0:PD9     1:SCK1      2:        3:
    | (0x0UL<<16)              // 0:PD8     1:SS1     2:        3:
    | (0x0UL<<14)              // 0:PD7     1:MPWMA7    2:        3:
    | (0x0UL<<12)              // 0:PD6     1:MPWMA6    2:        3:
    | (0x0UL<<10)              // 0:PD5     1:MPWMA5    2:        3:
    | (0x0UL<<8)               // 0:PD4     1:MPWMA4    2:        3:
    | (0x0UL<<6)               // 0:PD3     1:MPWMA3    2:        3:
    | (0x0UL<<4)               // 0:PD2     1:MPWMA2    2:        3:
    | (0x0UL<<2)               // 0:PD1     1:MPWMA1    2:        3:
    | (0x0UL<<0)               // 0:PD0     1:MPWMA0    2:        3:
    ;

  PCD->CR = 0              // 0 : Output(Push-pull) Mode, 1 : Output(Open-drain) Mode,  2 : Input,  3: Analog
    | (0x3UL<<30)              // P15
    | (0x3UL<<28)              // P14
    | (0x3UL<<26)              // P13
    | (0x3UL<<24)              // P12
    | (0x3UL<<22)              // P11
    | (0x3UL<<20)              // P10
    | (0x3UL<<18)              // P9
    | (0x3UL<<16)              // P8
    | (0x3UL<<14)              // P7
    | (0x3UL<<12)              // P6
    | (0x3UL<<10)              // P5
    | (0x3UL<<8)              // P4
    | (0x3UL<<6)              // P3
    | (0x3UL<<4)              // P2
    | (0x3UL<<2)              // P1
    | (0x3UL<<0)              // P0
    ;

  PCD->PCR = 0
    | (0x0UL<<31)             // P15    0: Pull up,     1: Pull down
    | (0x0UL<<30)             // P14    0: Pull up,     1: Pull down
    | (0x0UL<<29)             // P13    0: Pull up,     1: Pull down
    | (0x0UL<<28)             // P12    0: Pull up,     1: Pull down
    | (0x0UL<<27)             // P11    0: Pull up,     1: Pull down
    | (0x0UL<<26)             // P10    0: Pull up,     1: Pull down
    | (0x0UL<<25)             // P9     0: Pull up,     1: Pull down
    | (0x0UL<<24)             // P8     0: Pull up,     1: Pull down
    | (0x0UL<<23)             // P7     0: Pull up,     1: Pull down
    | (0x0UL<<22)             // P6     0: Pull up,     1: Pull down
    | (0x0UL<<21)             // P5     0: Pull up,     1: Pull down
    | (0x0UL<<20)             // P4     0: Pull up,     1: Pull down
    | (0x0UL<<19)             // P3     0: Pull up,     1: Pull down
    | (0x0UL<<18)             // P2     0: Pull up,     1: Pull down
    | (0x0UL<<17)             // P1     0: Pull up,     1: Pull down
    | (0x0UL<<16)             // P0     0: Pull up,     1: Pull down
    | (0x0UL<<15)             // P15    0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<14)             // P14    0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<13)             // P13    0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<12)             // P12    0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<11)             // P11    0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<10)             // P10    0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<9)              // P9     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<8)              // P8     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<7)              // P7     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<6)              // P6     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<5)              // P5     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<4)              // P4     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<3)              // P3     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<2)              // P2     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<1)              // P1     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<0)              // P0     0: Disable PU/PD  1: Enable PU/PD
    ;

//////////////////////////////////////////////////////////////////////////////////////////////////////
  // PORT - E
  PCE->MR = 0
    | (0x0UL<<30)              // 0:PE15    1:TraceCLK    2:        3:
    | (0x0UL<<28)              // 0:PE14    1:TraceD0   2:        3:
    | (0x0UL<<26)              // 0:PE13    1:TraceD1   2:        3:
    | (0x0UL<<24)              // 0:PE12    1:TraceD2   2:        3:
    | (0x0UL<<22)              // 0:PE11    1:TraceD3   2:        3:
    | (0x1UL<<18)              // 0:PE9     1:SXOUT     2:        3:
    | (0x1UL<<16)              // 0:PE8     1:SXIN      2:        3:
    | (0x0UL<<14)              // 0:PE7     1:MPWMB7    2:TXD3      3:
    | (0x0UL<<12)              // 0:PE6     1:MPWMB6    2:RXD3      3:
    | (0x0UL<<10)              // 0:PE5     1:MPWMB5    2:        3:
    | (0x0UL<<8)               // 0:PE4     1:MPWMB4    2:        3:
    | (0x0UL<<6)               // 0:PE3     1:MPWMB3    2:        3:
    | (0x0UL<<4)               // 0:PE2     1:MPWMB2    2:        3:
    | (0x0UL<<2)               // 0:PE1     1:MPWMB1    2:        3:
    | (0x0UL<<0)               // 0:PE0     1:MPWMB0    2:        3:
    ;

  PCE->CR = 0              // 0 : Output(Push-pull) Mode, 1 : Output(Open-drain) Mode,  2 : Input,  3: Analog
    | (0x3UL<<30)              // P15
    | (0x3UL<<28)              // P14
    | (0x3UL<<26)              // P13
    | (0x3UL<<24)              // P12
    | (0x3UL<<22)              // P11
    | (0x3UL<<18)              // P9
    | (0x3UL<<16)              // P8
    | (0x3UL<<14)              // P7
    | (0x3UL<<12)              // P6
    | (0x3UL<<10)              // P5
    | (0x3UL<<8)              // P4
    | (0x3UL<<6)              // P3
    | (0x3UL<<4)              // P2
    | (0x3UL<<2)              // P1
    | (0x3UL<<0)              // P0
    ;

  PCE->PCR = 0
    | (0x0UL<<31)             // P15    0: Pull up,     1: Pull down
    | (0x0UL<<30)             // P14    0: Pull up,     1: Pull down
    | (0x0UL<<29)             // P13    0: Pull up,     1: Pull down
    | (0x0UL<<28)             // P12    0: Pull up,     1: Pull down
    | (0x0UL<<27)             // P11    0: Pull up,     1: Pull down
    | (0x0UL<<25)             // P9     0: Pull up,     1: Pull down
    | (0x0UL<<24)             // P8     0: Pull up,     1: Pull down
    | (0x0UL<<23)             // P7     0: Pull up,     1: Pull down
    | (0x0UL<<22)             // P6     0: Pull up,     1: Pull down
    | (0x0UL<<21)             // P5     0: Pull up,     1: Pull down
    | (0x0UL<<20)             // P4     0: Pull up,     1: Pull down
    | (0x0UL<<19)             // P3     0: Pull up,     1: Pull down
    | (0x0UL<<18)             // P2     0: Pull up,     1: Pull down
    | (0x0UL<<17)             // P1     0: Pull up,     1: Pull down
    | (0x0UL<<16)             // P0     0: Pull up,     1: Pull down
    | (0x0UL<<15)             // P15    0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<14)             // P14    0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<13)             // P13    0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<12)             // P12    0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<11)             // P11    0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<9)              // P9     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<8)              // P8     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<7)              // P7     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<6)              // P6     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<5)              // P5     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<4)              // P4     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<3)              // P3     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<2)              // P2     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<1)              // P1     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<0)              // P0     0: Disable PU/PD  1: Enable PU/PD
    ;

//////////////////////////////////////////////////////////////////////////////////////////////////////
  // PORT - F
  PCF->MR = 0
    | (0x0UL<<22)              // 0:PF11    1:        2:FRTO_FMF    3:
    | (0x0UL<<20)              // 0:PF10    1:        2:        3:
    | (0x0UL<<18)              // 0:PF9   1:        2:        3:
    | (0x0UL<<16)              // 0:PF8   1:        2:        3:
    | (0x0UL<<14)              // 0:PF7   1:        2:        3:
    | (0x0UL<<10)              // 0:PF5   1:        2:        3:AN13
    | (0x0UL<<8)               // 0:PF4   1:        2:        3:AN12
    | (0x0UL<<6)               // 0:PF3   1:        2:        3:AN11
    | (0x0UL<<4)               // 0:PF2   1:        2:        3:AN10
    | (0x0UL<<2)               // 0:PF1   1:        2:        3:AN9
    | (0x0UL<<0)               // 0:PF0   1:        2:        3:AN8
    ;

  PCF->CR = 0              // 0 : Output(Push-pull) Mode, 1 : Output(Open-drain) Mode,  2 : Input,  3: Analog
    | (0x3UL<<22)              // P11
    | (0x3UL<<20)              // P10
    | (0x3UL<<18)              // P9
    | (0x3UL<<16)              // P8
    | (0x3UL<<14)              // P7
    | (0x3UL<<10)              // P5
    | (0x3UL<<8)              // P4
    | (0x3UL<<6)              // P3
    | (0x3UL<<4)              // P2
    | (0x3UL<<2)              // P1
    | (0x3UL<<0)              // P0
    ;

  PCF->PCR = 0
    | (0x0UL<<27)             // P11    0: Pull up,     1: Pull down
    | (0x0UL<<26)             // P10    0: Pull up,     1: Pull down
    | (0x0UL<<25)             // P9     0: Pull up,     1: Pull down
    | (0x0UL<<24)             // P8     0: Pull up,     1: Pull down
    | (0x0UL<<23)             // P7     0: Pull up,     1: Pull down
    | (0x0UL<<21)             // P5     0: Pull up,     1: Pull down
    | (0x0UL<<20)             // P4     0: Pull up,     1: Pull down
    | (0x0UL<<19)             // P3     0: Pull up,     1: Pull down
    | (0x0UL<<18)             // P2     0: Pull up,     1: Pull down
    | (0x0UL<<17)             // P1     0: Pull up,     1: Pull down
    | (0x0UL<<16)             // P0     0: Pull up,     1: Pull down
    | (0x0UL<<11)             // P11    0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<10)             // P10    0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<9)              // P9     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<8)              // P8     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<7)              // P7     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<5)              // P5     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<4)              // P4     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<3)              // P3     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<2)              // P2     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<1)              // P1     0: Disable PU/PD  1: Enable PU/PD
    | (0x0UL<<0)              // P0     0: Disable PU/PD  1: Enable PU/PD
    ;
}
