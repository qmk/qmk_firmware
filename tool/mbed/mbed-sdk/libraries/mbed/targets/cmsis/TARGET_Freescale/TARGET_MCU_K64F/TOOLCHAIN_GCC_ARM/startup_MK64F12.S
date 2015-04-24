/* K64F startup ARM GCC
 * Purpose: startup file for Cortex-M4 devices. Should use with
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
    .equ    Stack_Size, 0xC00
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
    .equ    Heap_Size, 0x400
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
    .long   __StackTop                  /* Top of Stack */
    .long   Reset_Handler               /* Reset Handler */
    .long   NMI_Handler                 /* NMI Handler                  */
    .long   HardFault_Handler           /* Hard Fault Handler           */
    .long   MemManage_Handler           /* MPU Fault Handler            */
    .long   BusFault_Handler            /* Bus Fault Handler            */
    .long   UsageFault_Handler          /* Usage Fault Handler          */
    .long   0                           /* Reserved                     */
    .long   0                           /* Reserved                     */
    .long   0                           /* Reserved                     */
    .long   0                           /* Reserved                     */
    .long   SVC_Handler                 /* SVCall Handler               */
    .long   DebugMon_Handler            /* Debug Monitor Handler        */
    .long   0                           /* Reserved                     */
    .long   PendSV_Handler              /* PendSV Handler               */
    .long   SysTick_Handler             /* SysTick Handler              */

    /* External Interrupts */
    .long   DMA0_IRQHandler  /* DMA Channel 0 Transfer Complete */
    .long   DMA1_IRQHandler  /* DMA Channel 1 Transfer Complete */
    .long   DMA2_IRQHandler  /* DMA Channel 2 Transfer Complete */
    .long   DMA3_IRQHandler  /* DMA Channel 3 Transfer Complete */
    .long   DMA4_IRQHandler  /* DMA Channel 4 Transfer Complete */
    .long   DMA5_IRQHandler  /* DMA Channel 5 Transfer Complete */
    .long   DMA6_IRQHandler  /* DMA Channel 6 Transfer Complete */
    .long   DMA7_IRQHandler  /* DMA Channel 7 Transfer Complete */
    .long   DMA8_IRQHandler  /* DMA Channel 8 Transfer Complete */
    .long   DMA9_IRQHandler  /* DMA Channel 9 Transfer Complete */
    .long   DMA10_IRQHandler  /* DMA Channel 10 Transfer Complete */
    .long   DMA11_IRQHandler  /* DMA Channel 11 Transfer Complete */
    .long   DMA12_IRQHandler  /* DMA Channel 12 Transfer Complete */
    .long   DMA13_IRQHandler  /* DMA Channel 13 Transfer Complete */
    .long   DMA14_IRQHandler  /* DMA Channel 14 Transfer Complete */
    .long   DMA15_IRQHandler  /* DMA Channel 15 Transfer Complete */
    .long   DMA_Error_IRQHandler  /* DMA Error Interrupt */
    .long   MCM_IRQHandler  /* Normal Interrupt */
    .long   FTFE_IRQHandler  /* FTFE Command complete interrupt */
    .long   Read_Collision_IRQHandler  /* Read Collision Interrupt */
    .long   LVD_LVW_IRQHandler  /* Low Voltage Detect, Low Voltage Warning */
    .long   LLW_IRQHandler  /* Low Leakage Wakeup */
    .long   Watchdog_IRQHandler  /* WDOG Interrupt */
    .long   RNG_IRQHandler  /* RNG Interrupt */
    .long   I2C0_IRQHandler  /* I2C0 interrupt */
    .long   I2C1_IRQHandler  /* I2C1 interrupt */
    .long   SPI0_IRQHandler  /* SPI0 Interrupt */
    .long   SPI1_IRQHandler  /* SPI1 Interrupt */
    .long   I2S0_Tx_IRQHandler  /* I2S0 transmit interrupt */
    .long   I2S0_Rx_IRQHandler  /* I2S0 receive interrupt */
    .long   UART0_LON_IRQHandler  /* UART0 LON interrupt */
    .long   UART0_RX_TX_IRQHandler  /* UART0 Receive/Transmit interrupt */
    .long   UART0_ERR_IRQHandler  /* UART0 Error interrupt */
    .long   UART1_RX_TX_IRQHandler  /* UART1 Receive/Transmit interrupt */
    .long   UART1_ERR_IRQHandler  /* UART1 Error interrupt */
    .long   UART2_RX_TX_IRQHandler  /* UART2 Receive/Transmit interrupt */
    .long   UART2_ERR_IRQHandler  /* UART2 Error interrupt */
    .long   UART3_RX_TX_IRQHandler  /* UART3 Receive/Transmit interrupt */
    .long   UART3_ERR_IRQHandler  /* UART3 Error interrupt */
    .long   ADC0_IRQHandler  /* ADC0 interrupt */
    .long   CMP0_IRQHandler  /* CMP0 interrupt */
    .long   CMP1_IRQHandler  /* CMP1 interrupt */
    .long   FTM0_IRQHandler  /* FTM0 fault, overflow and channels interrupt */
    .long   FTM1_IRQHandler  /* FTM1 fault, overflow and channels interrupt */
    .long   FTM2_IRQHandler  /* FTM2 fault, overflow and channels interrupt */
    .long   CMT_IRQHandler  /* CMT interrupt */
    .long   RTC_IRQHandler  /* RTC interrupt */
    .long   RTC_Seconds_IRQHandler  /* RTC seconds interrupt */
    .long   PIT0_IRQHandler  /* PIT timer channel 0 interrupt */
    .long   PIT1_IRQHandler  /* PIT timer channel 1 interrupt */
    .long   PIT2_IRQHandler  /* PIT timer channel 2 interrupt */
    .long   PIT3_IRQHandler  /* PIT timer channel 3 interrupt */
    .long   PDB0_IRQHandler  /* PDB0 Interrupt */
    .long   USB0_IRQHandler  /* USB0 interrupt */
    .long   USBDCD_IRQHandler  /* USBDCD Interrupt */
    .long   Reserved71_IRQHandler  /* Reserved interrupt 71 */
    .long   DAC0_IRQHandler  /* DAC0 interrupt */
    .long   MCG_IRQHandler  /* MCG Interrupt */
    .long   LPTimer_IRQHandler  /* LPTimer interrupt */
    .long   PORTA_IRQHandler  /* Port A interrupt */
    .long   PORTB_IRQHandler  /* Port B interrupt */
    .long   PORTC_IRQHandler  /* Port C interrupt */
    .long   PORTD_IRQHandler  /* Port D interrupt */
    .long   PORTE_IRQHandler  /* Port E interrupt */
    .long   SWI_IRQHandler  /* Software interrupt */
    .long   SPI2_IRQHandler  /* SPI2 Interrupt */
    .long   UART4_RX_TX_IRQHandler  /* UART4 Receive/Transmit interrupt */
    .long   UART4_ERR_IRQHandler  /* UART4 Error interrupt */
    .long   UART5_RX_TX_IRQHandler  /* UART5 Receive/Transmit interrupt */
    .long   UART5_ERR_IRQHandler  /* UART5 Error interrupt */
    .long   CMP2_IRQHandler  /* CMP2 interrupt */
    .long   FTM3_IRQHandler  /* FTM3 fault, overflow and channels interrupt */
    .long   DAC1_IRQHandler  /* DAC1 interrupt */
    .long   ADC1_IRQHandler  /* ADC1 interrupt */
    .long   I2C2_IRQHandler  /* I2C2 interrupt */
    .long   CAN0_ORed_Message_buffer_IRQHandler  /* CAN0 OR'd message buffers interrupt */
    .long   CAN0_Bus_Off_IRQHandler  /* CAN0 bus off interrupt */
    .long   CAN0_Error_IRQHandler  /* CAN0 error interrupt */
    .long   CAN0_Tx_Warning_IRQHandler  /* CAN0 Tx warning interrupt */
    .long   CAN0_Rx_Warning_IRQHandler  /* CAN0 Rx warning interrupt */
    .long   CAN0_Wake_Up_IRQHandler  /* CAN0 wake up interrupt */
    .long   SDHC_IRQHandler  /* SDHC interrupt */
    .long   ENET_1588_Timer_IRQHandler  /* Ethernet MAC IEEE 1588 Timer Interrupt */
    .long   ENET_Transmit_IRQHandler  /* Ethernet MAC Transmit Interrupt */
    .long   ENET_Receive_IRQHandler  /* Ethernet MAC Receive Interrupt */
    .long   ENET_Error_IRQHandler  /* Ethernet MAC Error and miscelaneous Interrupt */
    
    .size    __isr_vector, . - __isr_vector

    .section .text.Reset_Handler
    .thumb
    .thumb_func
    .align  2
    .globl   Reset_Handler
    .type    Reset_Handler, %function
Reset_Handler:
/*     Loop to copy data from read only memory to RAM. The ranges
 *      of copy from/to are specified by following symbols evaluated in
 *      linker script.
 *      __etext: End of code section, i.e., begin of data sections to copy from.
 *      __data_start__/__data_end__: RAM address range that data should be
 *      copied to. Both must be aligned to 4 bytes boundary.  */

disable_watchdog:
    /* unlock */
    ldr r1, =0x4005200e
    ldr r0, =0xc520
    strh r0, [r1]
    ldr r0, =0xd928
    strh r0, [r1]
    /* disable */
    ldr r1, =0x40052000
    ldr r0, =0x01d2
    strh r0, [r1]

    ldr    r1, =__etext
    ldr    r2, =__data_start__
    ldr    r3, =__data_end__

    subs   r3, r2
    ble    .Lflash_to_ram_loop_end

    movs    r4, 0
.Lflash_to_ram_loop:
    ldr    r0, [r1,r4]
    str    r0, [r2,r4]
    adds   r4, 4
    cmp    r4, r3
    blt    .Lflash_to_ram_loop
.Lflash_to_ram_loop_end:

    ldr   r0, =SystemInit
    blx   r0
    ldr   r0, =_start
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

/* Exception Handlers */

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

/* IRQ Handlers */
    def_irq_default_handler     DMA0_IRQHandler
    def_irq_default_handler     DMA1_IRQHandler
    def_irq_default_handler     DMA2_IRQHandler
    def_irq_default_handler     DMA3_IRQHandler
    def_irq_default_handler     DMA4_IRQHandler
    def_irq_default_handler     DMA5_IRQHandler
    def_irq_default_handler     DMA6_IRQHandler
    def_irq_default_handler     DMA7_IRQHandler
    def_irq_default_handler     DMA8_IRQHandler
    def_irq_default_handler     DMA9_IRQHandler
    def_irq_default_handler     DMA10_IRQHandler
    def_irq_default_handler     DMA11_IRQHandler
    def_irq_default_handler     DMA12_IRQHandler
    def_irq_default_handler     DMA13_IRQHandler
    def_irq_default_handler     DMA14_IRQHandler
    def_irq_default_handler     DMA15_IRQHandler
    def_irq_default_handler     DMA_Error_IRQHandler
    def_irq_default_handler     MCM_IRQHandler
    def_irq_default_handler     FTFE_IRQHandler
    def_irq_default_handler     Read_Collision_IRQHandler
    def_irq_default_handler     LVD_LVW_IRQHandler
    def_irq_default_handler     LLW_IRQHandler
    def_irq_default_handler     Watchdog_IRQHandler
    def_irq_default_handler     RNG_IRQHandler
    def_irq_default_handler     I2C0_IRQHandler
    def_irq_default_handler     I2C1_IRQHandler
    def_irq_default_handler     SPI0_IRQHandler
    def_irq_default_handler     SPI1_IRQHandler
    def_irq_default_handler     I2S0_Tx_IRQHandler
    def_irq_default_handler     I2S0_Rx_IRQHandler
    def_irq_default_handler     UART0_LON_IRQHandler
    def_irq_default_handler     UART0_RX_TX_IRQHandler
    def_irq_default_handler     UART0_ERR_IRQHandler
    def_irq_default_handler     UART1_RX_TX_IRQHandler
    def_irq_default_handler     UART1_ERR_IRQHandler
    def_irq_default_handler     UART2_RX_TX_IRQHandler
    def_irq_default_handler     UART2_ERR_IRQHandler
    def_irq_default_handler     UART3_RX_TX_IRQHandler
    def_irq_default_handler     UART3_ERR_IRQHandler
    def_irq_default_handler     ADC0_IRQHandler
    def_irq_default_handler     CMP0_IRQHandler
    def_irq_default_handler     CMP1_IRQHandler
    def_irq_default_handler     FTM0_IRQHandler
    def_irq_default_handler     FTM1_IRQHandler
    def_irq_default_handler     FTM2_IRQHandler
    def_irq_default_handler     CMT_IRQHandler
    def_irq_default_handler     RTC_IRQHandler
    def_irq_default_handler     RTC_Seconds_IRQHandler
    def_irq_default_handler     PIT0_IRQHandler
    def_irq_default_handler     PIT1_IRQHandler
    def_irq_default_handler     PIT2_IRQHandler
    def_irq_default_handler     PIT3_IRQHandler
    def_irq_default_handler     PDB0_IRQHandler
    def_irq_default_handler     USB0_IRQHandler
    def_irq_default_handler     USBDCD_IRQHandler
    def_irq_default_handler     Reserved71_IRQHandler
    def_irq_default_handler     DAC0_IRQHandler
    def_irq_default_handler     MCG_IRQHandler
    def_irq_default_handler     LPTimer_IRQHandler
    def_irq_default_handler     PORTA_IRQHandler
    def_irq_default_handler     PORTB_IRQHandler
    def_irq_default_handler     PORTC_IRQHandler
    def_irq_default_handler     PORTD_IRQHandler
    def_irq_default_handler     PORTE_IRQHandler
    def_irq_default_handler     SWI_IRQHandler
    def_irq_default_handler     SPI2_IRQHandler
    def_irq_default_handler     UART4_RX_TX_IRQHandler
    def_irq_default_handler     UART4_ERR_IRQHandler
    def_irq_default_handler     UART5_RX_TX_IRQHandler
    def_irq_default_handler     UART5_ERR_IRQHandler
    def_irq_default_handler     CMP2_IRQHandler
    def_irq_default_handler     FTM3_IRQHandler
    def_irq_default_handler     DAC1_IRQHandler
    def_irq_default_handler     ADC1_IRQHandler
    def_irq_default_handler     I2C2_IRQHandler
    def_irq_default_handler     CAN0_ORed_Message_buffer_IRQHandler
    def_irq_default_handler     CAN0_Bus_Off_IRQHandler
    def_irq_default_handler     CAN0_Error_IRQHandler
    def_irq_default_handler     CAN0_Tx_Warning_IRQHandler
    def_irq_default_handler     CAN0_Rx_Warning_IRQHandler
    def_irq_default_handler     CAN0_Wake_Up_IRQHandler
    def_irq_default_handler     SDHC_IRQHandler
    def_irq_default_handler     ENET_1588_Timer_IRQHandler
    def_irq_default_handler     ENET_Transmit_IRQHandler
    def_irq_default_handler     ENET_Receive_IRQHandler
    def_irq_default_handler     ENET_Error_IRQHandler
    def_irq_default_handler     DefaultISR
    
/* Flash protection region, placed at 0x400 */
    .text
    .thumb
    .align 2
    .section .kinetis_flash_config_field,"a",%progbits
kinetis_flash_config:
    .long 0xffffffff
    .long 0xffffffff
    .long 0xffffffff
    .long 0xfffffdfe

    .end
