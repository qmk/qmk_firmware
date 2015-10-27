/* File: startup_ARMCM4.S
 * Purpose: startup file for Cortex-M4 devices. Should use with
 *   GCC for ARM Embedded Processors
 * Version: V1.4
 * Date: 20 Dezember 2012
 *
 */
/* Copyright (c) 2011 - 2012 ARM LIMITED

   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   - Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   - Neither the name of ARM nor the names of its contributors may be used
     to endorse or promote products derived from this software without
     specific prior written permission.
   *
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
   ---------------------------------------------------------------------------*/


    .syntax unified
    .arch armv7-m

    .section .stack
    .align 3
.ifdef __STACK_SIZE
    .equ    Stack_Size, __STACK_SIZE
.else
    .equ    Stack_Size, 0x00000400
.endif
    .globl    __StackTop
    .globl    __StackLimit
__StackLimit:
    .space    Stack_Size
    .size __StackLimit, . - __StackLimit
__StackTop:
    .size __StackTop, . - __StackTop

    .section .heap
    .align 3
.ifdef __HEAP_SIZE
    .equ    Heap_Size, __HEAP_SIZE
.else
    .equ    Heap_Size, 0x00000C00
.endif
    .globl    __HeapBase
    .globl    __HeapLimit
__HeapBase:
    .if    Heap_Size
    .space    Heap_Size
    .endif
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

    /* External interrupts */
    .long    DAC_IRQHandler        /*  0:  DAC                       */
    .long    M0CORE_IRQHandler     /*  1:  M4-M0 communication       */
    .long    DMA_IRQHandler        /*  2:  -                         */
    .long    0                     /*  3:  Reserved                  */
    .long    FLASHEEPROM_IRQHandler/*  4:  ORed flash bank A/B, EEPROM int */
    .long    ETHERNET_IRQHandler   /*  5:  Ethernet interrupt        */
    .long    SDIO_IRQHandler       /*  6:  SD/MMC interrupt          */
    .long    LCD_IRQHandler        /*  7:  -                         */
    .long    USB0_IRQHandler       /*  8:  OTG interrupt             */
    .long    USB1_IRQHandler       /*  9:  -                         */
    .long    SCT_IRQHandler        /* 10: SCT combined interrupt     */
    .long    RITIMER_IRQHandler    /* 11: -                          */
    .long    TIMER0_IRQHandler     /* 12: -                          */
    .long    TIMER1_IRQHandler     /* 13: -                          */
    .long    TIMER2_IRQHandler     /* 14: -                          */
    .long    TIMER3_IRQHandler     /* 15: -                          */
    .long    MCPWM_IRQHandler      /* 16: Motor control PWM          */
    .long    ADC0_IRQHandler       /* 17: -                          */
    .long    I2C0_IRQHandler       /* 18: -                          */
    .long    I2C1_IRQHandler       /* 19: -                          */
    .long    SPI_IRQHandler        /* 20: -                          */
    .long    ADC1_IRQHandler       /* 21: -                          */
    .long    SSP0_IRQHandler       /* 22: -                          */
    .long    SSP1_IRQHandler       /* 23: -                          */
    .long    USART0_IRQHandler     /* 24: -                          */
    .long    UART1_IRQHandler      /* 25: Combined UART int w Modem int */
    .long    USART2_IRQHandler     /* 26: -                          */
    .long    USART3_IRQHandler     /* 27: combined USART int w IrDA int */
    .long    I2S0_IRQHandler       /* 28: -                          */
    .long    I2S1_IRQHandler       /* 29: -                          */
    .long    SPIFI_IRQHandler      /* 30: -                          */
    .long    SGPIO_IRQHandler      /* 31: -                          */
    .long    PIN_INT0_IRQHandler   /* 32: GPIO pin interrupt 0       */
    .long    PIN_INT1_IRQHandler   /* 33: GPIO pin interrupt 1       */
    .long    PIN_INT2_IRQHandler   /* 34: GPIO pin interrupt 2       */
    .long    PIN_INT3_IRQHandler   /* 35: GPIO pin interrupt 3       */
    .long    PIN_INT4_IRQHandler   /* 36: GPIO pin interrupt 4       */
    .long    PIN_INT5_IRQHandler   /* 37: GPIO pin interrupt 5       */
    .long    PIN_INT6_IRQHandler   /* 38: GPIO pin interrupt 6       */
    .long    PIN_INT7_IRQHandler   /* 39: GPIO pin interrupt 7       */
    .long    GINT0_IRQHandler      /* 40: GPIO global interrupt 0    */
    .long    GINT1_IRQHandler      /* 41: GPIO global interrupt 1    */
    .long    EVENTROUTER_IRQHandler/* 42: Event router interrupt     */
    .long    C_CAN1_IRQHandler     /* 43: -                          */
    .long    0                     /* 44: Reserved                   */
    .long    0                     /* 45: Reserved                   */
    .long    ATIMER_IRQHandler     /* 46: Alarm timer interuupt      */
    .long    RTC_IRQHandler        /* 47: -                          */
    .long    0                     /* 48: Reserved                   */
    .long    WWDT_IRQHandler       /* 49: -                          */
    .long    0                     /* 50: Reserved                   */
    .long    C_CAN0_IRQHandler     /* 51: -                          */
    .long    QEI_IRQHandler        /* 52: -                          */

    .size    __isr_vector, . - __isr_vector

    .text
    .thumb
    .thumb_func
    .align 2
    .globl    Reset_Handler
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

.LC0:
    cmp     r2, r3
    ittt    lt
    ldrlt   r0, [r1], #4
    strlt   r0, [r2], #4
    blt    .LC0

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

    def_irq_default_handler    DAC_IRQHandler
    def_irq_default_handler    M0CORE_IRQHandler
    def_irq_default_handler    DMA_IRQHandler
    def_irq_default_handler    FLASHEEPROM_IRQHandler
    def_irq_default_handler    ETHERNET_IRQHandler
    def_irq_default_handler    SDIO_IRQHandler
    def_irq_default_handler    LCD_IRQHandler
    def_irq_default_handler    USB0_IRQHandler
    def_irq_default_handler    USB1_IRQHandler
    def_irq_default_handler    SCT_IRQHandler
    def_irq_default_handler    RITIMER_IRQHandler
    def_irq_default_handler    TIMER0_IRQHandler
    def_irq_default_handler    TIMER1_IRQHandler
    def_irq_default_handler    TIMER2_IRQHandler
    def_irq_default_handler    TIMER3_IRQHandler
    def_irq_default_handler    MCPWM_IRQHandler
    def_irq_default_handler    ADC0_IRQHandler
    def_irq_default_handler    I2C0_IRQHandler
    def_irq_default_handler    I2C1_IRQHandler
    def_irq_default_handler    SPI_IRQHandler
    def_irq_default_handler    ADC1_IRQHandler
    def_irq_default_handler    SSP0_IRQHandler
    def_irq_default_handler    SSP1_IRQHandler
    def_irq_default_handler    USART0_IRQHandler
    def_irq_default_handler    UART1_IRQHandler
    def_irq_default_handler    USART2_IRQHandler
    def_irq_default_handler    USART3_IRQHandler
    def_irq_default_handler    I2S0_IRQHandler
    def_irq_default_handler    I2S1_IRQHandler
    def_irq_default_handler    SPIFI_IRQHandler
    def_irq_default_handler    SGPIO_IRQHandler
    def_irq_default_handler    PIN_INT0_IRQHandler
    def_irq_default_handler    PIN_INT1_IRQHandler
    def_irq_default_handler    PIN_INT2_IRQHandler
    def_irq_default_handler    PIN_INT3_IRQHandler
    def_irq_default_handler    PIN_INT4_IRQHandler
    def_irq_default_handler    PIN_INT5_IRQHandler
    def_irq_default_handler    PIN_INT6_IRQHandler
    def_irq_default_handler    PIN_INT7_IRQHandler
    def_irq_default_handler    GINT0_IRQHandler
    def_irq_default_handler    GINT1_IRQHandler
    def_irq_default_handler    EVENTROUTER_IRQHandler
    def_irq_default_handler    C_CAN1_IRQHandler
    def_irq_default_handler    ATIMER_IRQHandler
    def_irq_default_handler    RTC_IRQHandler
    def_irq_default_handler    WWDT_IRQHandler
    def_irq_default_handler    C_CAN0_IRQHandler
    def_irq_default_handler    QEI_IRQHandler

    .end
