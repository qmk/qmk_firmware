/* File: startup_ARMCM3.s
 * Purpose: startup file for Cortex-M3/M4 devices. Should use with 
 *   GNU Tools for ARM Embedded Processors
 * Version: V1.1
 * Date: 17 June 2011
 * 
 * Copyright (C) 2011 ARM Limited. All rights reserved.
 * ARM Limited (ARM) is supplying this software for use with Cortex-M3/M4 
 * processor based microcontrollers.  This file can be freely distributed 
 * within development tools that are supporting such ARM based processors. 
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
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
    .equ    Stack_Size, 0xc00
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
    .equ    Heap_Size, 0x800
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


    .long    PIN_INT0_Handler      /* All GPIO pin can be routed to PIN_INTx */
    .long    PIN_INT1_Handler
    .long    PIN_INT2_Handler
    .long    PIN_INT3_Handler
    .long    PIN_INT4_Handler
    .long    PIN_INT5_Handler
    .long    PIN_INT6_Handler
    .long    PIN_INT7_Handler
    .long    GINT0_Handler
    .long    GINT1_Handler         /* PIO0 (0:7) */
    .long    0
    .long    0
    .long    OSTIMER_Handler
    .long    0
    .long    SSP1_Handler          /* SSP1 */
    .long    I2C_Handler           /* I2C */
    .long    CT16B0_Handler        /* 16-bit Timer0 */
    .long    CT16B1_Handler        /* 16-bit Timer1 */
    .long    CT32B0_Handler        /* 32-bit Timer0 */
    .long    CT32B1_Handler        /* 32-bit Timer1 */
    .long    SSP0_Handler          /* SSP0 */
    .long    USART_Handler         /* USART */
    .long    USB_Handler           /* USB IRQ */
    .long    USB_FIQHandler        /* USB FIQ */
    .long    ADC_Handler           /* A/D Converter */
    .long    WDT_Handler           /* Watchdog timer */
    .long    BOD_Handler           /* Brown Out Detect */
    .long    FMC_Handler           /* IP2111 Flash Memory Controller */
    .long    OSCFAIL_Handler       /* OSC FAIL */
    .long    PVTCIRCUIT_Handler    /* PVT CIRCUIT */
    .long    USBWakeup_Handler     /* USB wake up */
    .long    0

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
 *      _etext: End of code section, i.e., begin of data sections to copy from.
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

    ldr    r0, =SystemInit
    blx    r0
    ldr    r0, =_start
    bx    r0
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

    def_irq_default_handler    PIN_INT0_Handler
    def_irq_default_handler    PIN_INT1_Handler
    def_irq_default_handler    PIN_INT2_Handler
    def_irq_default_handler    PIN_INT3_Handler
    def_irq_default_handler    PIN_INT4_Handler
    def_irq_default_handler    PIN_INT5_Handler
    def_irq_default_handler    PIN_INT6_Handler
    def_irq_default_handler    PIN_INT7_Handler
    def_irq_default_handler    GINT0_Handler
    def_irq_default_handler    GINT1_Handler
    def_irq_default_handler    OSTIMER_Handler
    def_irq_default_handler    SSP1_Handler
    def_irq_default_handler    I2C_Handler
    def_irq_default_handler    CT16B0_Handler
    def_irq_default_handler    CT16B1_Handler
    def_irq_default_handler    CT32B0_Handler
    def_irq_default_handler    CT32B1_Handler
    def_irq_default_handler    SSP0_Handler
    def_irq_default_handler    USART_Handler
    def_irq_default_handler    USB_Handler
    def_irq_default_handler    USB_FIQHandler
    def_irq_default_handler    ADC_Handler
    def_irq_default_handler    WDT_Handler
    def_irq_default_handler    BOD_Handler
    def_irq_default_handler    FMC_Handler
    def_irq_default_handler    OSCFAIL_Handler
    def_irq_default_handler    PVTCIRCUIT_Handler
    def_irq_default_handler    USBWakeup_Handler
    def_irq_default_handler    DEF_IRQHandler

    .end

