/* KL25Z startup ARM GCC
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

    .section .vector_table,"a",%progbits
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

    /* External interrupts */
    .long   DMA0_IRQHandler         /* DMA channel 0 transfer complete interrupt */
    .long   DMA1_IRQHandler         /* DMA channel 1 transfer complete interrupt */
    .long   DMA2_IRQHandler         /* DMA channel 2 transfer complete interrupt */
    .long   DMA3_IRQHandler         /* DMA channel 3 transfer complete interrupt */
    .long   Default_Handler         /* Reserved interrupt 20 */
    .long   FTFA_IRQHandler         /* FTFA interrupt */
    .long   LVD_LVW_IRQHandler      /* Low Voltage Detect, Low Voltage Warning */
    .long   LLW_IRQHandler          /* Low Leakage Wakeup */
    .long   I2C0_IRQHandler         /* I2C0 interrupt */
    .long   I2C1_IRQHandler         /* I2C0 interrupt 25 */
    .long   SPI0_IRQHandler         /* SPI0 interrupt */
    .long   SPI1_IRQHandler         /* SPI1 interrupt */
    .long   UART0_IRQHandler        /* UART0 status/error interrupt */
    .long   UART1_IRQHandler        /* UART1 status/error interrupt */
    .long   UART2_IRQHandler        /* UART2 status/error interrupt */
    .long   ADC0_IRQHandler         /* ADC0 interrupt */
    .long   CMP0_IRQHandler         /* CMP0 interrupt */
    .long   TPM0_IRQHandler         /* TPM0 fault, overflow and channels interrupt */
    .long   TPM1_IRQHandler         /* TPM1 fault, overflow and channels interrupt */
    .long   TPM2_IRQHandler         /* TPM2 fault, overflow and channels interrupt */
    .long   RTC_IRQHandler          /* RTC interrupt */
    .long   RTC_Seconds_IRQHandler  /* RTC seconds interrupt */
    .long   PIT_IRQHandler          /* PIT timer interrupt */
    .long   Default_Handler         /* Reserved interrupt 39 */
    .long   USB0_IRQHandler         /* USB0 interrupt */
    .long   DAC0_IRQHandler         /* DAC interrupt */
    .long   TSI0_IRQHandler         /* TSI0 interrupt */
    .long   MCG_IRQHandler          /* MCG interrupt */
    .long   LPTimer_IRQHandler      /* LPTimer interrupt */
    .long   Default_Handler         /* Reserved interrupt 45 */
    .long   PORTA_IRQHandler        /* Port A interrupt */
    .long   PORTD_IRQHandler        /* Port D interrupt */

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

    def_irq_default_handler     DMA0_IRQHandler
    def_irq_default_handler     DMA1_IRQHandler
    def_irq_default_handler     DMA2_IRQHandler
    def_irq_default_handler     DMA3_IRQHandler
    def_irq_default_handler     FTFA_IRQHandler
    def_irq_default_handler     LVD_LVW_IRQHandler
    def_irq_default_handler     LLW_IRQHandler
    def_irq_default_handler     I2C0_IRQHandler
    def_irq_default_handler     I2C1_IRQHandler
    def_irq_default_handler     SPI0_IRQHandler
    def_irq_default_handler     SPI1_IRQHandler
    def_irq_default_handler     UART0_IRQHandler
    def_irq_default_handler     UART1_IRQHandler
    def_irq_default_handler     UART2_IRQHandler
    def_irq_default_handler     ADC0_IRQHandler
    def_irq_default_handler     CMP0_IRQHandler
    def_irq_default_handler     TPM0_IRQHandler
    def_irq_default_handler     TPM1_IRQHandler
    def_irq_default_handler     TPM2_IRQHandler
    def_irq_default_handler     RTC_IRQHandler
    def_irq_default_handler     RTC_Seconds_IRQHandler
    def_irq_default_handler     PIT_IRQHandler
    def_irq_default_handler     USB0_IRQHandler
    def_irq_default_handler     DAC0_IRQHandler
    def_irq_default_handler     TSI0_IRQHandler
    def_irq_default_handler     MCG_IRQHandler
    def_irq_default_handler     LPTimer_IRQHandler
    def_irq_default_handler     PORTA_IRQHandler
    def_irq_default_handler     PORTD_IRQHandler
    def_irq_default_handler     DEF_IRQHandler

/* Flash protection region, placed at 0x400 */
    .text
    .thumb
    .align 2
    .section .kinetis_flash_config_field,"a",%progbits
kinetis_flash_config:
    .long 0xffffffff
    .long 0xffffffff
    .long 0xffffffff
    .long 0xfffffffe

    .end
