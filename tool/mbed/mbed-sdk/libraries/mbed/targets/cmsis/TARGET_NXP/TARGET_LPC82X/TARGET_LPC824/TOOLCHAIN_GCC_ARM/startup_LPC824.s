/* File: startup_ARMCM0.S
 * Purpose: startup file for Cortex-M0 devices. Should use with 
 *   GCC for ARM Embedded Processors
 * Version: V1.2
 * Date: 15 Nov 2011
 * 
 * Copyright (c) 2011, ARM Limited
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the ARM Limited nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ARM LIMITED BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
    .syntax unified
    .arch armv6-m

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
    .equ    Stack_Size, 0x80
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
    .equ    Heap_Size, 0x80
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
    .long    0                     /* Reserved */
    .long    0                     /* Reserved */
    .long    0                     /* Reserved */
    .long    0                     /* Reserved */
    .long    0                     /* Reserved */
    .long    0                     /* Reserved */
    .long    0                     /* Reserved */
    .long    SVC_Handler           /* SVCall Handler */
    .long    0                     /* Reserved */
    .long    0                     /* Reserved */
    .long    PendSV_Handler        /* PendSV Handler */
    .long    SysTick_Handler       /* SysTick Handler */

/* LPC824 interrupts */
    .long    SPI0_IRQHandler                         // SPI0 controller
    .long    SPI1_IRQHandler                         // SPI1 controller
    .long    0                                       // Reserved
    .long    UART0_IRQHandler                        // UART0
    .long    UART1_IRQHandler                        // UART1
    .long    UART2_IRQHandler                        // UART2
    .long    0                                       // Reserved
    .long    I2C1_IRQHandler                         // I2C ch1 controller
    .long    I2C0_IRQHandler                         // I2C ch0 controller
    .long    SCT_IRQHandler                          // Smart Counter Timer
    .long    MRT_IRQHandler                          // Multi-Rate Timer
    .long    CMP_IRQHandler                          // Comparator
    .long    WDT_IRQHandler                          // PIO1 (0:11)
    .long    BOD_IRQHandler                          // Brown Out Detect
    .long    Flash_IRQHandler                        // Flash interrupt
    .long    WKT_IRQHandler                          // Wakeup timer
    .long    ADC_SEQA_IRQHandler                     // ADC sequence A completion
    .long    ADC_SEQB_IRQHandler                     // ADC sequence B completion
    .long    ADC_THCMP_IRQHandler                    // ADC threshold compare
    .long    ADC_OVR_IRQHandler                      // ADC overrun
    .long    DMA_IRQHandler                          // DMA interrupt
    .long    I2C2_IRQHandler                         // I2C2 controller
    .long    I2C3_IRQHandler                         // I2C3 controller
    .long    0                                       // Reserved
    .long    PININT0_IRQHandler                      // PIO INT0
    .long    PININT1_IRQHandler                      // PIO INT1
    .long    PININT2_IRQHandler                      // PIO INT2
    .long    PININT3_IRQHandler                      // PIO INT3
    .long    PININT4_IRQHandler                      // PIO INT4
    .long    PININT5_IRQHandler                      // PIO INT5
    .long    PININT6_IRQHandler                      // PIO INT6
    .long    PININT7_IRQHandler                      // PIO INT7
    
    .size    __isr_vector, . - __isr_vector

    .section .text.Reset_Handler
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

    subs    r3, r2
    ble    .Lflash_to_ram_loop_end

    movs    r4, 0
.Lflash_to_ram_loop:
    ldr    r0, [r1,r4]
    str    r0, [r2,r4]
    adds    r4, 4
    cmp    r4, r3
    blt    .Lflash_to_ram_loop
.Lflash_to_ram_loop_end:

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

    def_default_handler     NMI_Handler
    def_default_handler     HardFault_Handler
    def_default_handler     SVC_Handler
    def_default_handler     PendSV_Handler
    def_default_handler     SysTick_Handler
    def_default_handler     Default_Handler

    .macro    def_irq_default_handler    handler_name
    .weak     \handler_name
    .set      \handler_name, Default_Handler
    .endm

    def_irq_default_handler    SPI0_IRQHandler
    def_irq_default_handler    SPI1_IRQHandler
    def_irq_default_handler    UART0_IRQHandler
    def_irq_default_handler    UART1_IRQHandler
    def_irq_default_handler    UART2_IRQHandler
    def_irq_default_handler    I2C0_IRQHandler
    def_irq_default_handler    I2C1_IRQHandler
    def_irq_default_handler    I2C2_IRQHandler
    def_irq_default_handler    I2C3_IRQHandler
    def_irq_default_handler    SCT_IRQHandler
    def_irq_default_handler    MRT_IRQHandler
    def_irq_default_handler    CMP_IRQHandler
    def_irq_default_handler    WDT_IRQHandler
    def_irq_default_handler    BOD_IRQHandler
    def_irq_default_handler    Flash_IRQHandler
    def_irq_default_handler    WKT_IRQHandler
    def_irq_default_handler    ADC_SEQA_IRQHandler
    def_irq_default_handler    ADC_SEQB_IRQHandler
    def_irq_default_handler    ADC_THCMP_IRQHandler
    def_irq_default_handler    ADC_OVR_IRQHandler
    def_irq_default_handler    DMA_IRQHandler
    def_irq_default_handler    PININT0_IRQHandler
    def_irq_default_handler    PININT1_IRQHandler
    def_irq_default_handler    PININT2_IRQHandler
    def_irq_default_handler    PININT3_IRQHandler
    def_irq_default_handler    PININT4_IRQHandler
    def_irq_default_handler    PININT5_IRQHandler
    def_irq_default_handler    PININT6_IRQHandler
    def_irq_default_handler    PININT7_IRQHandler

    .end

