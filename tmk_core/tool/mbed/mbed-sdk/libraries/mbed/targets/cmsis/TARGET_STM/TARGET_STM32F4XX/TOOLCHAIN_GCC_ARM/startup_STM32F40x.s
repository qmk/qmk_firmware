/* File: startup_STM32F40x.S
 * Purpose: startup file for Cortex-M4 devices. Should use with
 *   GCC for ARM Embedded Processors
 * Version: V1.4
 * Date: 09 July 2012
 *
 * Copyright (c) 2011, 2012, ARM Limited
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
    .arch armv7-m

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
    .equ    Heap_Size, 0
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
    .long     WWDG_IRQHandler               /* Window WatchDog */
    .long     PVD_IRQHandler                /* PVD through EXTI Line detection */
    .long     TAMP_STAMP_IRQHandler         /* Tamper and TimeStamps through the EXTI line */
    .long     RTC_WKUP_IRQHandler           /* RTC Wakeup through the EXTI line */
    .long     FLASH_IRQHandler              /* FLASH */
    .long     RCC_IRQHandler                /* RCC */
    .long     EXTI0_IRQHandler              /* EXTI Line0 */
    .long     EXTI1_IRQHandler              /* EXTI Line1 */
    .long     EXTI2_IRQHandler              /* EXTI Line2 */
    .long     EXTI3_IRQHandler              /* EXTI Line3 */
    .long     EXTI4_IRQHandler              /* EXTI Line4 */
    .long     DMA1_Stream0_IRQHandler       /* DMA1 Stream 0 */
    .long     DMA1_Stream1_IRQHandler       /* DMA1 Stream 1 */
    .long     DMA1_Stream2_IRQHandler       /* DMA1 Stream 2 */
    .long     DMA1_Stream3_IRQHandler       /* DMA1 Stream 3 */
    .long     DMA1_Stream4_IRQHandler       /* DMA1 Stream 4 */
    .long     DMA1_Stream5_IRQHandler       /* DMA1 Stream 5 */
    .long     DMA1_Stream6_IRQHandler       /* DMA1 Stream 6 */
    .long     ADC_IRQHandler                /* ADC1, ADC2 and ADC3s */
    .long     CAN1_TX_IRQHandler            /* CAN1 TX */
    .long     CAN1_RX0_IRQHandler           /* CAN1 RX0 */
    .long     CAN1_RX1_IRQHandler           /* CAN1 RX1 */
    .long     CAN1_SCE_IRQHandler           /* CAN1 SCE */
    .long     EXTI9_5_IRQHandler            /* External Line[9:5]s */
    .long     TIM1_BRK_TIM9_IRQHandler      /* TIM1 Break and TIM9 */
    .long     TIM1_UP_TIM10_IRQHandler      /* TIM1 Update and TIM10 */
    .long     TIM1_TRG_COM_TIM11_IRQHandler /* TIM1 Trigger and Commutation and TIM11 */
    .long     TIM1_CC_IRQHandler            /* TIM1 Capture Compare */
    .long     TIM2_IRQHandler               /* TIM2 */
    .long     TIM3_IRQHandler               /* TIM3 */
    .long     TIM4_IRQHandler               /* TIM4 */
    .long     I2C1_EV_IRQHandler            /* I2C1 Event */
    .long     I2C1_ER_IRQHandler            /* I2C1 Error */
    .long     I2C2_EV_IRQHandler            /* I2C2 Event */
    .long     I2C2_ER_IRQHandler            /* I2C2 Error */
    .long     SPI1_IRQHandler               /* SPI1 */
    .long     SPI2_IRQHandler               /* SPI2 */
    .long     USART1_IRQHandler             /* USART1 */
    .long     USART2_IRQHandler             /* USART2 */
    .long     USART3_IRQHandler             /* USART3 */
    .long     EXTI15_10_IRQHandler          /* External Line[15:10]s */
    .long     RTC_Alarm_IRQHandler          /* RTC Alarm (A and B) through EXTI Line */
    .long     OTG_FS_WKUP_IRQHandler        /* USB OTG FS Wakeup through EXTI line */
    .long     TIM8_BRK_TIM12_IRQHandler     /* TIM8 Break and TIM12 */
    .long     TIM8_UP_TIM13_IRQHandler      /* TIM8 Update and TIM13 */
    .long     TIM8_TRG_COM_TIM14_IRQHandler /* TIM8 Trigger and Commutation and TIM14 */
    .long     TIM8_CC_IRQHandler            /* TIM8 Capture Compare */
    .long     DMA1_Stream7_IRQHandler       /* DMA1 Stream7 */
    .long     FSMC_IRQHandler               /* FSMC */
    .long     SDIO_IRQHandler               /* SDIO */
    .long     TIM5_IRQHandler               /* TIM5 */
    .long     SPI3_IRQHandler               /* SPI3 */
    .long     UART4_IRQHandler              /* UART4 */
    .long     UART5_IRQHandler              /* UART5 */
    .long     TIM6_DAC_IRQHandler           /* TIM6 and DAC1&2 underrun errors */
    .long     TIM7_IRQHandler               /* TIM7 */
    .long     DMA2_Stream0_IRQHandler       /* DMA2 Stream 0 */
    .long     DMA2_Stream1_IRQHandler       /* DMA2 Stream 1 */
    .long     DMA2_Stream2_IRQHandler       /* DMA2 Stream 2 */
    .long     DMA2_Stream3_IRQHandler       /* DMA2 Stream 3 */
    .long     DMA2_Stream4_IRQHandler       /* DMA2 Stream 4 */
    .long     ETH_IRQHandler                /* Ethernet */
    .long     ETH_WKUP_IRQHandler           /* Ethernet Wakeup through EXTI line */
    .long     CAN2_TX_IRQHandler            /* CAN2 TX */
    .long     CAN2_RX0_IRQHandler           /* CAN2 RX0 */
    .long     CAN2_RX1_IRQHandler           /* CAN2 RX1 */
    .long     CAN2_SCE_IRQHandler           /* CAN2 SCE */
    .long     OTG_FS_IRQHandler             /* USB OTG FS */
    .long     DMA2_Stream5_IRQHandler       /* DMA2 Stream 5 */
    .long     DMA2_Stream6_IRQHandler       /* DMA2 Stream 6 */
    .long     DMA2_Stream7_IRQHandler       /* DMA2 Stream 7 */
    .long     USART6_IRQHandler             /* USART6 */
    .long     I2C3_EV_IRQHandler            /* I2C3 event */
    .long     I2C3_ER_IRQHandler            /* I2C3 error */
    .long     OTG_HS_EP1_OUT_IRQHandler     /* USB OTG HS End Point 1 Out */
    .long     OTG_HS_EP1_IN_IRQHandler      /* USB OTG HS End Point 1 In */
    .long     OTG_HS_WKUP_IRQHandler        /* USB OTG HS Wakeup through EXTI */
    .long     OTG_HS_IRQHandler             /* USB OTG HS */
    .long     DCMI_IRQHandler               /* DCMI */
    .long     CRYP_IRQHandler               /* CRYP crypto */
    .long     HASH_RNG_IRQHandler           /* Hash and Rng */
    .long     FPU_IRQHandler                /* FPU */

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

    def_irq_default_handler     WWDG_IRQHandler
    def_irq_default_handler     PVD_IRQHandler
    def_irq_default_handler     TAMP_STAMP_IRQHandler
    def_irq_default_handler     RTC_WKUP_IRQHandler
    def_irq_default_handler     FLASH_IRQHandler
    def_irq_default_handler     RCC_IRQHandler
    def_irq_default_handler     EXTI0_IRQHandler
    def_irq_default_handler     EXTI1_IRQHandler
    def_irq_default_handler     EXTI2_IRQHandler
    def_irq_default_handler     EXTI3_IRQHandler
    def_irq_default_handler     EXTI4_IRQHandler
    def_irq_default_handler     DMA1_Stream0_IRQHandler
    def_irq_default_handler     DMA1_Stream1_IRQHandler
    def_irq_default_handler     DMA1_Stream2_IRQHandler
    def_irq_default_handler     DMA1_Stream3_IRQHandler
    def_irq_default_handler     DMA1_Stream4_IRQHandler
    def_irq_default_handler     DMA1_Stream5_IRQHandler
    def_irq_default_handler     DMA1_Stream6_IRQHandler
    def_irq_default_handler     ADC_IRQHandler
    def_irq_default_handler     CAN1_TX_IRQHandler
    def_irq_default_handler     CAN1_RX0_IRQHandler
    def_irq_default_handler     CAN1_RX1_IRQHandler
    def_irq_default_handler     CAN1_SCE_IRQHandler
    def_irq_default_handler     EXTI9_5_IRQHandler
    def_irq_default_handler     TIM1_BRK_TIM9_IRQHandler
    def_irq_default_handler     TIM1_UP_TIM10_IRQHandler
    def_irq_default_handler     TIM1_TRG_COM_TIM11_IRQHandler
    def_irq_default_handler     TIM1_CC_IRQHandler
    def_irq_default_handler     TIM2_IRQHandler
    def_irq_default_handler     TIM3_IRQHandler
    def_irq_default_handler     TIM4_IRQHandler
    def_irq_default_handler     I2C1_EV_IRQHandler
    def_irq_default_handler     I2C1_ER_IRQHandler
    def_irq_default_handler     I2C2_EV_IRQHandler
    def_irq_default_handler     I2C2_ER_IRQHandler
    def_irq_default_handler     SPI1_IRQHandler
    def_irq_default_handler     SPI2_IRQHandler
    def_irq_default_handler     USART1_IRQHandler
    def_irq_default_handler     USART2_IRQHandler
    def_irq_default_handler     USART3_IRQHandler
    def_irq_default_handler     EXTI15_10_IRQHandler
    def_irq_default_handler     RTC_Alarm_IRQHandler
    def_irq_default_handler     OTG_FS_WKUP_IRQHandler
    def_irq_default_handler     TIM8_BRK_TIM12_IRQHandler
    def_irq_default_handler     TIM8_UP_TIM13_IRQHandler
    def_irq_default_handler     TIM8_TRG_COM_TIM14_IRQHandler
    def_irq_default_handler     TIM8_CC_IRQHandler
    def_irq_default_handler     DMA1_Stream7_IRQHandler
    def_irq_default_handler     FSMC_IRQHandler
    def_irq_default_handler     SDIO_IRQHandler
    def_irq_default_handler     TIM5_IRQHandler
    def_irq_default_handler     SPI3_IRQHandler
    def_irq_default_handler     UART4_IRQHandler
    def_irq_default_handler     UART5_IRQHandler
    def_irq_default_handler     TIM6_DAC_IRQHandler
    def_irq_default_handler     TIM7_IRQHandler
    def_irq_default_handler     DMA2_Stream0_IRQHandler
    def_irq_default_handler     DMA2_Stream1_IRQHandler
    def_irq_default_handler     DMA2_Stream2_IRQHandler
    def_irq_default_handler     DMA2_Stream3_IRQHandler
    def_irq_default_handler     DMA2_Stream4_IRQHandler
    def_irq_default_handler     ETH_IRQHandler
    def_irq_default_handler     ETH_WKUP_IRQHandler
    def_irq_default_handler     CAN2_TX_IRQHandler
    def_irq_default_handler     CAN2_RX0_IRQHandler
    def_irq_default_handler     CAN2_RX1_IRQHandler
    def_irq_default_handler     CAN2_SCE_IRQHandler
    def_irq_default_handler     OTG_FS_IRQHandler
    def_irq_default_handler     DMA2_Stream5_IRQHandler
    def_irq_default_handler     DMA2_Stream6_IRQHandler
    def_irq_default_handler     DMA2_Stream7_IRQHandler
    def_irq_default_handler     USART6_IRQHandler
    def_irq_default_handler     I2C3_EV_IRQHandler
    def_irq_default_handler     I2C3_ER_IRQHandler
    def_irq_default_handler     OTG_HS_EP1_OUT_IRQHandler
    def_irq_default_handler     OTG_HS_EP1_IN_IRQHandler
    def_irq_default_handler     OTG_HS_WKUP_IRQHandler
    def_irq_default_handler     OTG_HS_IRQHandler
    def_irq_default_handler     DCMI_IRQHandler
    def_irq_default_handler     CRYP_IRQHandler
    def_irq_default_handler     HASH_RNG_IRQHandler
    def_irq_default_handler     FPU_IRQHandler
    def_irq_default_handler     DEF_IRQHandler

    .end
