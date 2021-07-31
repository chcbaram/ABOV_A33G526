
  .syntax unified
  .cpu cortex-m3
  .fpu softvfp
  .thumb

.global g_pfnVectors
.global Default_Handler

/* start address for the initialization values of the .data section.
defined in linker script */
.word _sidata
/* start address for the .data section. defined in linker script */
.word _sdata
/* end address for the .data section. defined in linker script */
.word _edata
/* start address for the .bss section. defined in linker script */
.word _sbss
/* end address for the .bss section. defined in linker script */
.word _ebss


/**
 * @brief  This is the code that gets called when the processor first
 *          starts execution following a reset event. Only the absolutely
 *          necessary set is performed, after which the application
 *          supplied main() routine is called.
 * @param  None
 * @retval : None
*/

  .section .text.Reset_Handler
  .weak Reset_Handler
  .type Reset_Handler, %function
Reset_Handler:
  ldr   sp, =_estack    		 /* set stack pointer */

/* Copy the data segment initializers from flash to SRAM */
  movs r1, #0
  b LoopCopyDataInit

CopyDataInit:
  ldr r3, =_sidata
  ldr r3, [r3, r1]
  str r3, [r0, r1]
  adds r1, r1, #4

LoopCopyDataInit:
  ldr r0, =_sdata
  ldr r3, =_edata
  adds r2, r0, r1
  cmp r2, r3
  bcc CopyDataInit
  ldr r2, =_sbss
  b LoopFillZerobss
/* Zero fill the bss segment. */
FillZerobss:
  movs r3, #0
  str r3, [r2], #4

LoopFillZerobss:
  ldr r3, = _ebss
  cmp r2, r3
  bcc FillZerobss

/* Call the clock system intitialization function.*/
/*    bl  SystemInit */
/* Call static constructors */
    bl __libc_init_array
/* Call the application's entry point.*/
  bl main
  bx lr
.size Reset_Handler, .-Reset_Handler

/**
 * @brief  This is the code that gets called when the processor receives an
 *         unexpected interrupt.  This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 *
 * @param  None
 * @retval : None
*/
    .section .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
  b Infinite_Loop
  .size Default_Handler, .-Default_Handler
/******************************************************************************
*
* The minimal vector table for a Cortex M3.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/
  .section .isr_vector,"a",%progbits
  .type g_pfnVectors, %object
  .size g_pfnVectors, .-g_pfnVectors


g_pfnVectors:

  .word _estack
  .word Reset_Handler
  .word NMI_Handler
  .word HardFault_Handler
  .word MemManage_Handler
  .word BusFault_Handler
  .word UsageFault_Handler
  .word 0
  .word 0
  .word 0
  .word 0
  .word SVC_Handler
  .word DebugMon_Handler
  .word 0
  .word PendSV_Handler
  .word SysTick_Handler

  .word LVDFAIL_Handler
  .word MXOSCFAIL_Handler
  .word SXOSCFAIL_Handler
  .word WDT_Handler
  .word FRT_Handler
  .word TIMER0_Handler
  .word TIMER1_Handler
  .word TIMER2_Handler
  .word TIMER3_Handler
  .word TIMER4_Handler
  .word TIMER5_Handler
  .word TIMER6_Handler
  .word TIMER7_Handler
  .word TIMER8_Handler
  .word TIMER9_Handler
  .word MCKFAIL_Handler
  .word GPIOA_Handler
  .word GPIOB_Handler
  .word GPIOC_Handler
  .word GPIOD_Handler
  .word GPIOE_Handler
  .word GPIOF_Handler
  .word Default_Handler
  .word Default_Handler
  .word PWM0_Handler
  .word PWM1_Handler
  .word PWM2_Handler
  .word PWM3_Handler
  .word PWM4_Handler
  .word PWM5_Handler
  .word PWM6_Handler
  .word PWM7_Handler
  .word SPI0_Handler
  .word SPI1_Handler
  .word Default_Handler
  .word Default_Handler
  .word I2C0_Handler
  .word I2C1_Handler
  .word UART_0_Handler
  .word UART_1_Handler
  .word UART_2_Handler
  .word UART_3_Handler
  .word Default_Handler
  .word ADC_Handler
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0


/*******************************************************************************
*
* Provide weak aliases for each Exception handler to the Default_Handler.
* As they are weak aliases, any function with the same name will override
* this definition.
*
*******************************************************************************/

  .weak NMI_Handler
  .thumb_set NMI_Handler,Default_Handler

  .weak HardFault_Handler
  .thumb_set HardFault_Handler,Default_Handler

  .weak MemManage_Handler
  .thumb_set MemManage_Handler,Default_Handler

  .weak BusFault_Handler
  .thumb_set BusFault_Handler,Default_Handler

  .weak UsageFault_Handler
  .thumb_set UsageFault_Handler,Default_Handler

  .weak SVC_Handler
  .thumb_set SVC_Handler,Default_Handler

  .weak DebugMon_Handler
  .thumb_set DebugMon_Handler,Default_Handler

  .weak PendSV_Handler
  .thumb_set PendSV_Handler,Default_Handler

  .weak SysTick_Handler
  .thumb_set SysTick_Handler,Default_Handler


  .weak LVDFAIL_Handler
  .thumb_set LVDFAIL_Handler,Default_Handler

  .weak MXOSCFAIL_Handler
  .thumb_set MXOSCFAIL_Handler,Default_Handler

  .weak SXOSCFAIL_Handler
  .thumb_set SXOSCFAIL_Handler,Default_Handler

  .weak WDT_Handler
  .thumb_set WDT_Handler,Default_Handler

  .weak FRT_Handler
  .thumb_set FRT_Handler,Default_Handler

  .weak TIMER0_Handler
  .thumb_set TIMER0_Handler,Default_Handler

  .weak TIMER1_Handler
  .thumb_set TIMER1_Handler,Default_Handler

  .weak TIMER2_Handler
  .thumb_set TIMER2_Handler,Default_Handler

  .weak TIMER3_Handler
  .thumb_set TIMER3_Handler,Default_Handler

  .weak TIMER4_Handler
  .thumb_set TIMER4_Handler,Default_Handler

  .weak TIMER5_Handler
  .thumb_set TIMER5_Handler,Default_Handler

  .weak TIMER6_Handler
  .thumb_set TIMER6_Handler,Default_Handler

  .weak TIMER7_Handler
  .thumb_set TIMER7_Handler,Default_Handler

  .weak TIMER8_Handler
  .thumb_set TIMER8_Handler,Default_Handler

  .weak TIMER9_Handler
  .thumb_set TIMER9_Handler,Default_Handler

  .weak MCKFAIL_Handler
  .thumb_set MCKFAIL_Handler,Default_Handler

  .weak GPIOA_Handler
  .thumb_set GPIOA_Handler,Default_Handler

  .weak GPIOB_Handler
  .thumb_set GPIOB_Handler,Default_Handler

  .weak GPIOC_Handler
  .thumb_set GPIOC_Handler,Default_Handler

  .weak GPIOD_Handler
  .thumb_set GPIOD_Handler,Default_Handler

  .weak GPIOE_Handler
  .thumb_set GPIOE_Handler,Default_Handler

  .weak GPIOF_Handler
  .thumb_set GPIOF_Handler,Default_Handler

  .weak PWM0_Handler
  .thumb_set PWM0_Handler,Default_Handler

  .weak PWM1_Handler
  .thumb_set PWM1_Handler,Default_Handler

  .weak PWM2_Handler
  .thumb_set PWM2_Handler,Default_Handler

  .weak PWM3_Handler
  .thumb_set PWM3_Handler,Default_Handler

  .weak PWM4_Handler
  .thumb_set PWM4_Handler,Default_Handler

  .weak PWM5_Handler
  .thumb_set PWM5_Handler,Default_Handler

  .weak PWM6_Handler
  .thumb_set PWM6_Handler,Default_Handler

  .weak PWM7_Handler
  .thumb_set PWM7_Handler,Default_Handler

  .weak SPI0_Handler
  .thumb_set SPI0_Handler,Default_Handler

  .weak SPI1_Handler
  .thumb_set SPI1_Handler,Default_Handler

  .weak I2C0_Handler
  .thumb_set I2C0_Handler,Default_Handler

  .weak I2C1_Handler
  .thumb_set I2C1_Handler,Default_Handler

  .weak UART_0_Handler
  .thumb_set UART_0_Handler,Default_Handler

  .weak UART_1_Handler
  .thumb_set UART_1_Handler,Default_Handler

  .weak UART_2_Handler
  .thumb_set UART_2_Handler,Default_Handler

  .weak UART_3_Handler
  .thumb_set UART_3_Handler,Default_Handler

  .weak ADC_Handler
  .thumb_set ADC_Handler,Default_Handler

