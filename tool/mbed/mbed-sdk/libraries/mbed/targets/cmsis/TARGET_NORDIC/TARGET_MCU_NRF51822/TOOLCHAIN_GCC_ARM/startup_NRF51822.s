/* 
Copyright (c) 2013, Nordic Semiconductor ASA
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of Nordic Semiconductor ASA nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/* 
NOTE: Template files (including this one) are application specific and therefore 
expected to be copied into the application project folder prior to its use!
*/

    .syntax unified
    .arch armv6-m

    .section .stack
    .align 3
#ifdef __STACK_SIZE
    .equ    Stack_Size, __STACK_SIZE
#else
    .equ    Stack_Size, 2048
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
    .equ    Heap_Size, 2048
#endif
    .globl    __HeapBase
    .globl    __HeapLimit
__HeapBase:
    .if    Heap_Size
    .space    Heap_Size
    .endif
    .size __HeapBase, . - __HeapBase
__HeapLimit:
    .size __HeapLimit, . - __HeapLimit
    
    .section .Vectors
    .align 2
    .globl __Vectors
__Vectors:
    .long    __StackTop            /* Top of Stack */
    .long   Reset_Handler               /* Reset Handler */
    .long   NMI_Handler                 /* NMI Handler */
    .long   HardFault_Handler           /* Hard Fault Handler */
    .long   0                           /* Reserved */
    .long   0                           /* Reserved */
    .long   0                           /* Reserved */
    .long   0                           /* Reserved */
    .long   0                           /* Reserved */
    .long   0                           /* Reserved */
    .long   0                           /* Reserved */
    .long   SVC_Handler                 /* SVCall Handler */
    .long   0                           /* Reserved */
    .long   0                           /* Reserved */
    .long   PendSV_Handler              /* PendSV Handler */
    .long   SysTick_Handler             /* SysTick Handler */

  /* External Interrupts */
    .long 	POWER_CLOCK_IRQHandler		 /*POWER_CLOCK */
    .long 	RADIO_IRQHandler		 /*RADIO */
    .long 	UART0_IRQHandler		 /*UART0 */
    .long 	SPI0_TWI0_IRQHandler		 /*SPI0_TWI0 */
    .long 	SPI1_TWI1_IRQHandler		 /*SPI1_TWI1 */
    .long 	0		 /*Reserved */
    .long 	GPIOTE_IRQHandler		 /*GPIOTE */
    .long 	ADC_IRQHandler		 /*ADC */
    .long 	TIMER0_IRQHandler		 /*TIMER0 */
    .long 	TIMER1_IRQHandler		 /*TIMER1 */
    .long 	TIMER2_IRQHandler		 /*TIMER2 */
    .long 	RTC0_IRQHandler		 /*RTC0 */
    .long 	TEMP_IRQHandler		 /*TEMP */
    .long 	RNG_IRQHandler		 /*RNG */
    .long 	ECB_IRQHandler		 /*ECB */
    .long 	CCM_AAR_IRQHandler		 /*CCM_AAR */
    .long 	WDT_IRQHandler		 /*WDT */
    .long 	RTC1_IRQHandler		 /*RTC1 */
    .long 	QDEC_IRQHandler		 /*QDEC */
    .long 	LPCOMP_IRQHandler		 /*LPCOMP */
    .long 	SWI0_IRQHandler		 /*SWI0 */
    .long 	SWI1_IRQHandler		 /*SWI1 */
    .long 	SWI2_IRQHandler		 /*SWI2 */
    .long 	SWI3_IRQHandler		 /*SWI3 */
    .long 	SWI4_IRQHandler		 /*SWI4 */
    .long 	SWI5_IRQHandler		 /*SWI5 */
    .long 	0		 /*Reserved */
    .long 	0		 /*Reserved */
    .long 	0		 /*Reserved */
    .long 	0		 /*Reserved */
    .long 	0		 /*Reserved */
    .long 	0		 /*Reserved */


    .size    __Vectors, . - __Vectors

/* Reset Handler */

    .equ    NRF_POWER_RAMON_ADDRESS,            0x40000524
    .equ    NRF_POWER_RAMON_RAMxON_ONMODE_Msk,  0x3  

    .text
    .thumb
    .thumb_func
    .align 1
    .globl    Reset_Handler
    .type    Reset_Handler, %function
Reset_Handler:
    .fnstart

/* Make sure ALL RAM banks are powered on */
    LDR     R0, =NRF_POWER_RAMON_ADDRESS
    LDR     R2, [R0]
    MOVS    R1, #NRF_POWER_RAMON_RAMxON_ONMODE_Msk
    ORRS    R2, R1
    STR     R2, [R0]

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
    ble     .LC0

.LC1:
    subs    r3, 4
    ldr    r0, [r1,r3]
    str    r0, [r2,r3]
    bgt    .LC1
.LC0:
    
    LDR     R0, =SystemInit
    BLX     R0
    LDR     R0, =_start
    BX      R0

    .pool
    .cantunwind
    .fnend
    .size   Reset_Handler,.-Reset_Handler

    .section ".text"


/* Dummy Exception Handlers (infinite loops which can be modified) */

    .weak   NMI_Handler
    .type   NMI_Handler, %function
NMI_Handler:
    B       .
    .size   NMI_Handler, . - NMI_Handler


    .weak   HardFault_Handler
    .type   HardFault_Handler, %function
HardFault_Handler:
    B       .
    .size   HardFault_Handler, . - HardFault_Handler


    .weak   SVC_Handler
    .type   SVC_Handler, %function
SVC_Handler:
    B       .
    .size   SVC_Handler, . - SVC_Handler


    .weak   PendSV_Handler
    .type   PendSV_Handler, %function
PendSV_Handler:
    B       .
    .size   PendSV_Handler, . - PendSV_Handler


    .weak   SysTick_Handler
    .type   SysTick_Handler, %function
SysTick_Handler:
    B       .
    .size   SysTick_Handler, . - SysTick_Handler


/* IRQ Handlers */

    .globl  Default_Handler
    .type   Default_Handler, %function
Default_Handler:
    B       .
    .size   Default_Handler, . - Default_Handler

    .macro  IRQ handler
    .weak   \handler
    .set    \handler, Default_Handler
    .endm

    IRQ  POWER_CLOCK_IRQHandler
    IRQ  RADIO_IRQHandler
    IRQ  UART0_IRQHandler
    IRQ  SPI0_TWI0_IRQHandler
    IRQ  SPI1_TWI1_IRQHandler
    IRQ  GPIOTE_IRQHandler
    IRQ  ADC_IRQHandler
    IRQ  TIMER0_IRQHandler
    IRQ  TIMER1_IRQHandler
    IRQ  TIMER2_IRQHandler
    IRQ  RTC0_IRQHandler
    IRQ  TEMP_IRQHandler
    IRQ  RNG_IRQHandler
    IRQ  ECB_IRQHandler
    IRQ  CCM_AAR_IRQHandler
    IRQ  WDT_IRQHandler
    IRQ  RTC1_IRQHandler
    IRQ  QDEC_IRQHandler
    IRQ  LPCOMP_IRQHandler
    IRQ  SWI0_IRQHandler
    IRQ  SWI1_IRQHandler
    IRQ  SWI2_IRQHandler
    IRQ  SWI3_IRQHandler
    IRQ  SWI4_IRQHandler
    IRQ  SWI5_IRQHandler


  .end

