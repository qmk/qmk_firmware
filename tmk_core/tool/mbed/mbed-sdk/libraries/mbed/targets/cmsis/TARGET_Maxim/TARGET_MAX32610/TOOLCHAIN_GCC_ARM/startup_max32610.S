/*******************************************************************************
 * Copyright (C) 2015 Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *******************************************************************************
 */

    .syntax unified
    .arch armv7-m

/* Memory Model
   The HEAP starts at the end of the DATA section and grows upward.
   
   The STACK starts at the end of the RAM and grows downward.
   
   The HEAP and stack STACK are only checked at compile time:
   (DATA_SIZE + HEAP_SIZE + STACK_SIZE) < RAM_SIZE
   
   This is just a check for the bare minimum for the Heap+Stack area before
   aborting compilation, it is not the run time limit:
   Heap_Size + Stack_Size = 0x80 + 0x80 = 0x100
 */
    .section .stack
    .align 3
#ifdef __STACK_SIZE
    .equ    Stack_Size, __STACK_SIZE
#else
    .equ    Stack_Size, 0x00001000
#endif
    .globl    __StackTop
    .globl    __StackLimit
__StackLimit:
    .space    Stack_Size
    .size __StackLimit, . - __StackLimit
__StackTop:
    .size __StackTop, . - __StackTop

    .section .heap
    .align 3
#ifdef __HEAP_SIZE
    .equ    Heap_Size, __HEAP_SIZE
#else
    .equ    Heap_Size, 0x00000C00
#endif
    .globl    __HeapBase
    .globl    __HeapLimit
__HeapBase:
    .space    Heap_Size
    .size __HeapBase, . - __HeapBase
__HeapLimit:
    .size __HeapLimit, . - __HeapLimit

    .section .isr_vector
    .align 2
    .globl __isr_vector
__isr_vector:
    .long    __StackTop            /* Top of Stack */
    .long    Reset_Handler         /* Reset Handler */
    .long    NMI_Handler           /* NMI Handler */
    .long    HardFault_Handler     /* Hard Fault Handler */
    .long    MemManage_Handler     /* MPU Fault Handler */
    .long    BusFault_Handler      /* Bus Fault Handler */
    .long    UsageFault_Handler    /* Usage Fault Handler */
    .long    0                     /* Reserved */
    .long    0                     /* Reserved */
    .long    0                     /* Reserved */
    .long    0                     /* Reserved */
    .long    SVC_Handler           /* SVCall Handler */
    .long    DebugMon_Handler      /* Debug Monitor Handler */
    .long    0                     /* Reserved */
    .long    PendSV_Handler        /* PendSV Handler */
    .long    SysTick_Handler       /* SysTick Handler */

    /* Externals interrupts */
    .long UART0_IRQHandler          /* 16: 1 UART0 */
    .long UART1_IRQHandler          /* 17: 2 UART1 */
    .long I2CM0_IRQHandler          /* 18: 3 I2C Master 0 */
    .long I2CS_IRQHandler           /* 19: 4 I2C Slave */
    .long USB_IRQHandler            /* 20: 5 USB */
    .long PMU_IRQHandler            /* 21: 6 DMA */
    .long AFE_IRQHandler            /* 22: 7 AFE */
    .long MAA_IRQHandler            /* 23: 8 MAA */
    .long AES_IRQHandler            /* 24: 9 AES */
    .long SPI0_IRQHandler           /* 25:10 SPI0 */
    .long SPI1_IRQHandler           /* 26:11 SPI1 */
    .long SPI2_IRQHandler           /* 27:12 SPI2 */
    .long TMR0_IRQHandler           /* 28:13 Timer32-0 */
    .long TMR1_IRQHandler           /* 29:14 Timer32-1 */
    .long TMR2_IRQHandler           /* 30:15 Timer32-1 */
    .long TMR3_IRQHandler           /* 31:16 Timer32-2 */
    .long RSVD0_IRQHandler          /* 32:17 RSVD */
    .long RSVD1_IRQHandler          /* 33:18 RSVD */
    .long DAC0_IRQHandler           /* 34:19 DAC0  (12-bit DAC) */  
    .long DAC1_IRQHandler           /* 35:20 DAC1  (12-bit DAC) */  
    .long DAC2_IRQHandler           /* 36:21 DAC2  (8-bit DAC) */
    .long DAC3_IRQHandler           /* 37:22 DAC3  (8-bit DAC) */
    .long ADC_IRQHandler            /* 38:23 ADC */
    .long FLC_IRQHandler            /* 39:24 Flash Controller */
    .long PWRMAN_IRQHandler         /* 40:25 PWRMAN */
    .long CLKMAN_IRQHandler         /* 41:26 CLKMAN */
    .long RTC0_IRQHandler           /* 42:27 RTC INT0 */
    .long RTC1_IRQHandler           /* 43:28 RTC INT1 */
    .long RTC2_IRQHandler           /* 44:29 RTC INT2 */
    .long RTC3_IRQHandler           /* 45:30 RTC INT3 */
    .long WDT0_IRQHandler           /* 46:31 WATCHDOG0 */
    .long WDT0_P_IRQHandler         /* 47:32 WATCHDOG0 PRE-WINDOW */
    .long WDT1_IRQHandler           /* 48:33 WATCHDOG1 */
    .long WDT1_P_IRQHandler         /* 49:34 WATCHDOG1 PRE-WINDOW */
    .long GPIO_P0_IRQHandler        /* 50:35 GPIO Port 0  */
    .long GPIO_P1_IRQHandler        /* 51:36 GPIO Port 1  */
    .long GPIO_P2_IRQHandler        /* 52:37 GPIO Port 2  */
    .long GPIO_P3_IRQHandler        /* 53:38 GPIO Port 3  */
    .long GPIO_P4_IRQHandler        /* 54:39 GPIO Port 4  */
    .long GPIO_P5_IRQHandler        /* 55:40 GPIO Port 5  */
    .long GPIO_P6_IRQHandler        /* 56:41 GPIO Port 6  */
    .long GPIO_P7_IRQHandler        /* 57:42 GPIO Port 7  */
    .long TMR16_0_IRQHandler        /* 58:43 Timer16-s0 */
    .long TMR16_1_IRQHandler        /* 59:44 Timer16-s1 */
    .long TMR16_2_IRQHandler        /* 60:45 Timer16-s2 */
    .long TMR16_3_IRQHandler        /* 61:46 Timer16-s3 */
    .long I2CM1_IRQHandler          /* 62:47 I2C Master 1 */

	
    .text 	
    .thumb
    .thumb_func
    .align 2
    .globl   Reset_Handler
    .type    Reset_Handler, %function
Reset_Handler:
/*     Loop to copy data from read only memory to RAM. The ranges
 *      of copy from/to are specified by following symbols evaluated in
 *      linker script.
 *      __etext: End of code section, i.e., begin of data sections to copy from.
 *      __data_start__/__data_end__: RAM address range that data should be
 *      copied to. Both must be aligned to 4 bytes boundary.  */

    ldr    r1, =__etext
    ldr    r2, =__data_start__
    ldr    r3, =__data_end__

.Lflash_to_ram_loop:
    cmp     r2, r3
    ittt    lt
    ldrlt   r0, [r1], #4
    strlt   r0, [r2], #4
    blt    .Lflash_to_ram_loop

.Lflash_to_ram_loop_end:

    ldr    r0, =SystemInit
    blx    r0
    ldr    r0, =_start
    bx     r0
    .pool
    .size Reset_Handler, . - Reset_Handler
    
    .text
/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers */
    .macro    def_default_handler    handler_name
    .align 1
    .thumb_func
    .weak    \handler_name
    .type    \handler_name, %function
\handler_name :
    b    .
    .size    \handler_name, . - \handler_name
    .endm

    def_default_handler    NMI_Handler
    def_default_handler    HardFault_Handler
    def_default_handler    MemManage_Handler
    def_default_handler    BusFault_Handler
    def_default_handler    UsageFault_Handler
    def_default_handler    SVC_Handler
    def_default_handler    DebugMon_Handler
    def_default_handler    PendSV_Handler
    def_default_handler    SysTick_Handler
    def_default_handler    Default_Handler

    .macro    def_irq_default_handler    handler_name
    .weak     \handler_name
    .set      \handler_name, Default_Handler
    .endm
 
    def_irq_default_handler UART0_IRQHandler          /* 16: 1 UART0 */
    def_irq_default_handler UART1_IRQHandler          /* 17: 2 UART1 */
    def_irq_default_handler I2CM0_IRQHandler          /* 18: 3 I2C Master 0 */
    def_irq_default_handler I2CS_IRQHandler           /* 19: 4 I2C Slave */
    def_irq_default_handler USB_IRQHandler            /* 20: 5 USB */
    def_irq_default_handler PMU_IRQHandler            /* 21: 6 DMA */
    def_irq_default_handler AFE_IRQHandler            /* 22: 7 AFE */
    def_irq_default_handler MAA_IRQHandler            /* 23: 8 MAA */
    def_irq_default_handler AES_IRQHandler            /* 24: 9 AES */
    def_irq_default_handler SPI0_IRQHandler           /* 25:10 SPI0 */
    def_irq_default_handler SPI1_IRQHandler           /* 26:11 SPI1 */
    def_irq_default_handler SPI2_IRQHandler           /* 27:12 SPI2 */
    def_irq_default_handler TMR0_IRQHandler           /* 28:13 Timer32-0 */
    def_irq_default_handler TMR1_IRQHandler           /* 29:14 Timer32-1 */
    def_irq_default_handler TMR2_IRQHandler           /* 30:15 Timer32-1 */
    def_irq_default_handler TMR3_IRQHandler           /* 31:16 Timer32-2 */
    def_irq_default_handler RSVD0_IRQHandler          /* 32:17 RSVD */
    def_irq_default_handler RSVD1_IRQHandler          /* 33:18 RSVD */
    def_irq_default_handler DAC0_IRQHandler           /* 34:19 DAC0  (12-bit DAC) */  
    def_irq_default_handler DAC1_IRQHandler           /* 35:20 DAC1  (12-bit DAC) */  
    def_irq_default_handler DAC2_IRQHandler           /* 36:21 DAC2  (8-bit DAC) */
    def_irq_default_handler DAC3_IRQHandler           /* 37:22 DAC3  (8-bit DAC) */
    def_irq_default_handler ADC_IRQHandler            /* 38:23 ADC */
    def_irq_default_handler FLC_IRQHandler            /* 39:24 Flash Controller */
    def_irq_default_handler PWRMAN_IRQHandler         /* 40:25 PWRMAN */
    def_irq_default_handler CLKMAN_IRQHandler         /* 41:26 CLKMAN */
    def_irq_default_handler RTC0_IRQHandler           /* 42:27 RTC INT0 */
    def_irq_default_handler RTC1_IRQHandler           /* 43:28 RTC INT1 */
    def_irq_default_handler RTC2_IRQHandler           /* 44:29 RTC INT2 */
    def_irq_default_handler RTC3_IRQHandler           /* 45:30 RTC INT3 */
    def_irq_default_handler WDT0_IRQHandler           /* 46:31 WATCHDOG0 */
    def_irq_default_handler WDT0_P_IRQHandler         /* 47:32 WATCHDOG0 PRE-WINDOW */
    def_irq_default_handler WDT1_IRQHandler           /* 48:33 WATCHDOG1 */
    def_irq_default_handler WDT1_P_IRQHandler         /* 49:34 WATCHDOG1 PRE-WINDOW */
    def_irq_default_handler GPIO_P0_IRQHandler        /* 50:35 GPIO Port 0  */
    def_irq_default_handler GPIO_P1_IRQHandler        /* 51:36 GPIO Port 1  */
    def_irq_default_handler GPIO_P2_IRQHandler        /* 52:37 GPIO Port 2  */
    def_irq_default_handler GPIO_P3_IRQHandler        /* 53:38 GPIO Port 3  */
    def_irq_default_handler GPIO_P4_IRQHandler        /* 54:39 GPIO Port 4  */
    def_irq_default_handler GPIO_P5_IRQHandler        /* 55:40 GPIO Port 5  */
    def_irq_default_handler GPIO_P6_IRQHandler        /* 56:41 GPIO Port 6  */
    def_irq_default_handler GPIO_P7_IRQHandler        /* 57:42 GPIO Port 7  */
    def_irq_default_handler TMR16_0_IRQHandler        /* 58:43 Timer16-s0 */
    def_irq_default_handler TMR16_1_IRQHandler        /* 59:44 Timer16-s1 */
    def_irq_default_handler TMR16_2_IRQHandler        /* 60:45 Timer16-s2 */
    def_irq_default_handler TMR16_3_IRQHandler        /* 61:46 Timer16-s3 */
    def_irq_default_handler I2CM1_IRQHandler          /* 62:47 I2C Master 1 */

    .end
