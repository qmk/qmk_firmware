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

    /* External interrupts */
    .long   WDT_IRQHandler              /*  0: Windowed watchdog timer      */
    .long   BOD_IRQHandler              /*  1: Brown-Out Detect             */
    .long   FMC_IRQHandler              /*  2: Flash controller             */
    .long   EEPROM_IRQHandler           /*  3: EEPROM controller            */
    .long   DMA_IRQHandler              /*  4: DMA                          */
    .long   GINT0_IRQHandler            /*  5: GPIO group 0                 */
    .long   GINT1_IRQHandler            /*  6: GPIO group 1                 */
    .long   PIN_INT0_IRQHandler         /*  7: PIO INT0                     */
    .long   PIN_INT1_IRQHandler         /*  8: PIO INT1                     */
    .long   PIN_INT2_IRQHandler         /*  9: PIO INT2                     */
    .long   PIN_INT3_IRQHandler         /* 10: PIO INT3                     */
    .long   PIN_INT4_IRQHandler         /* 11: PIO INT4                     */
    .long   PIN_INT5_IRQHandler         /* 12: PIO INT5                     */
    .long   PIN_INT6_IRQHandler         /* 13: PIO INT6                     */
    .long   PIN_INT7_IRQHandler         /* 14: PIO INT7                     */
    .long   RIT_IRQHandler              /* 15: Repetitive Interrupt Timer   */
    .long   SCT0_IRQHandler             /* 16: State configurable timer     */
    .long   SCT1_IRQHandler             /* 17: State configurable timer     */
    .long   SCT2_IRQHandler             /* 18: State configurable timer     */
    .long   SCT3_IRQHandler             /* 19: State configurable timer     */
    .long   MRT_IRQHandler              /* 20: Multi-Rate Timer             */
    .long   UART0_IRQHandler            /* 21: UART0                        */
    .long   UART1_IRQHandler            /* 22: UART1                        */
    .long   UART2_IRQHandler            /* 23: UART2                        */
    .long   I2C0_IRQHandler             /* 24: I2C0 controller              */
    .long   SPI0_IRQHandler             /* 25: SPI0 controller              */
    .long   SPI1_IRQHandler             /* 26: SPI1 controller              */
    .long   CAN_IRQHandler              /* 27: C_CAN0                       */
    .long   USB_IRQHandler              /* 28: USB IRQ                      */
    .long   USB_FIQHandler              /* 29: USB FIQ                      */
    .long   USBWakeup_IRQHandler        /* 30: USB wake-up                  */
    .long   ADC0A_IRQHandler            /* 31: ADC0 sequence A completion   */
    .long   ADC0B_IRQHandler            /* 32: ADC0 sequence B completion   */
    .long   ADC0_THCMP_IRQHandler       /* 33: ADC0 threshold compare       */
    .long   ADC0_OVR_IRQHandler         /* 34: ADC0 overrun                 */
    .long   ADC1A_IRQHandler            /* 35: ADC1 sequence A completion   */
    .long   ADC1B_IRQHandler            /* 36: ADC1 sequence B completion   */
    .long   ADC1_THCMP_IRQHandler       /* 37: ADC1 threshold compare       */
    .long   ADC1_OVR_IRQHandler         /* 38: ADC1 overrun                 */
    .long   DAC_IRQHandler              /* 39: DAC                          */
    .long   ACMP0_IRQHandler            /* 40: Analog Comparator 0          */
    .long   ACMP1_IRQHandler            /* 41: Analog Comparator 1          */
    .long   ACMP2_IRQHandler            /* 42: Analog Comparator 2          */
    .long   ACMP3_IRQHandler            /* 43: Analog Comparator 3          */
    .long   QEI_IRQHandler              /* 44: Quadrature Encoder Interface */	
    .long   RTC_ALARM_IRQHandler        /* 45: RTC alarm                    */
    .long   RTC_WAKE_IRQHandler         /* 46: RTC wake-up                  */

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
 
    def_irq_default_handler     WDT_IRQHandler
    def_irq_default_handler     BOD_IRQHandler
    def_irq_default_handler     FMC_IRQHandler
    def_irq_default_handler     EEPROM_IRQHandler
    def_irq_default_handler     DMA_IRQHandler
    def_irq_default_handler     GINT0_IRQHandler
    def_irq_default_handler     GINT1_IRQHandler
    def_irq_default_handler     PIN_INT0_IRQHandler
    def_irq_default_handler     PIN_INT1_IRQHandler
    def_irq_default_handler     PIN_INT2_IRQHandler
    def_irq_default_handler     PIN_INT3_IRQHandler
    def_irq_default_handler     PIN_INT4_IRQHandler
    def_irq_default_handler     PIN_INT5_IRQHandler
    def_irq_default_handler     PIN_INT6_IRQHandler
    def_irq_default_handler     PIN_INT7_IRQHandler
    def_irq_default_handler     RIT_IRQHandler
    def_irq_default_handler     SCT0_IRQHandler
    def_irq_default_handler     SCT1_IRQHandler
    def_irq_default_handler     SCT2_IRQHandler
    def_irq_default_handler     SCT3_IRQHandler
    def_irq_default_handler     MRT_IRQHandler
    def_irq_default_handler     UART0_IRQHandler
    def_irq_default_handler     UART1_IRQHandler
    def_irq_default_handler     UART2_IRQHandler
    def_irq_default_handler     I2C0_IRQHandler
    def_irq_default_handler     SPI0_IRQHandler
    def_irq_default_handler     SPI1_IRQHandler
    def_irq_default_handler     CAN_IRQHandler
    def_irq_default_handler     USB_IRQHandler
    def_irq_default_handler     USB_FIQHandler
    def_irq_default_handler     USBWakeup_IRQHandler
    def_irq_default_handler     ADC0A_IRQHandler
    def_irq_default_handler     ADC0B_IRQHandler
    def_irq_default_handler     ADC0_THCMP_IRQHandler
    def_irq_default_handler     ADC0_OVR_IRQHandler
    def_irq_default_handler     ADC1A_IRQHandler
    def_irq_default_handler     ADC1B_IRQHandler
    def_irq_default_handler     ADC1_THCMP_IRQHandler
    def_irq_default_handler     ADC1_OVR_IRQHandler
    def_irq_default_handler     DAC_IRQHandler
    def_irq_default_handler     ACMP0_IRQHandler
    def_irq_default_handler     ACMP1_IRQHandler
    def_irq_default_handler     ACMP2_IRQHandler
    def_irq_default_handler     ACMP3_IRQHandler
    def_irq_default_handler     QEI_IRQHandler
    def_irq_default_handler     RTC_ALARM_IRQHandler
    def_irq_default_handler     RTC_WAKE_IRQHandler
    def_irq_default_handler     DEF_IRQHandler

    .end

