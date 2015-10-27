/* File: startup_MK20DX256.s
 * Purpose: startup file for Cortex-M4 devices. Should use with
 *   GCC for ARM Embedded Processors
 * Version: V1.3
 * Date: 08 Feb 2012
 *
 * Copyright (c) 2015, ARM Limited
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
    .equ    Stack_Size, 0x400
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
    .equ    Heap_Size, 0xC00
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
                .long     DMA0_IRQHandler   // DMA channel 0 transfer complete interrupt  
                .long     DMA1_IRQHandler   // DMA channel 0 transfer complete interrupt 
                .long     DMA2_IRQHandler   // DMA channel 0 transfer complete interrupt 
                .long     DMA3_IRQHandler   // DMA channel 0 transfer complete interrupt 
                .long     DMA4_IRQHandler   // DMA channel 0 transfer complete interrupt                      
                .long     DMA5_IRQHandler   // DMA channel 0 transfer complete interrupt 
                .long     DMA6_IRQHandler   // DMA channel 0 transfer complete interrupt 
                .long     DMA7_IRQHandler   // DMA channel 0 transfer complete interrupt 
                .long     DMA8_IRQHandler   // DMA channel 0 transfer complete interrupt 
                .long     DMA9_IRQHandler   // DMA channel 0 transfer complete interrupt 
                .long     DMA10_IRQHandler  // DMA channel 0 transfer complete interrupt 
                .long     DMA11_IRQHandler  // DMA channel 0 transfer complete interrupt 
                .long     DMA12_IRQHandler  // DMA channel 0 transfer complete interrupt 
                .long     DMA13_IRQHandler  // DMA channel 0 transfer complete interrupt 
                .long     DMA14_IRQHandler  // DMA channel 0 transfer complete interrupt 
                .long     DMA15_IRQHandler  // DMA channel 0 transfer complete interrupt 
                .long     DMA_Error_IRQHandler      // DMA error interrupt                
                .long     Reserved33_IRQHandler     // Reserved interrupt 33
                .long     FTFL_IRQHandler           // FTFL interrupt
                .long     Read_Collision_IRQHandler // Read collision interrupt
                .long     LVD_LVW_IRQHandler        // Low Voltage Detect, Low Voltage Warning
                .long     LLW_IRQHandler            // Low Leakage Wakeup
                .long     Watchdog_IRQHandler       // WDOG interrupt                
                .long     Reserved39_IRQHandler     // Reserved interrupt 39          
                .long     I2C0_IRQHandler           // I2C0 interrupt
                .long     I2C1_IRQHandler           // I2C1 interrupt
                .long     SPI0_IRQHandler           // SPI0 interrupt
                .long     SPI1_IRQHandler           // SPI1 interrupt
                .long     Reserved44_IRQHandler     // Reserved interrupt 44
                .long     CAN0_ORed_Message_buffer_IRQHandler   // CAN0 OR'd message buffers interrupt
                .long     CAN0_Bus_Off_IRQHandler       // CAN0 bus off interrupt
                .long     CAN0_Error_IRQHandler         // CAN0 error interrupt
                .long     CAN0_Tx_Warning_IRQHandler    // CAN0 Tx warning interrupt
                .long     CAN0_Rx_Warning_IRQHandler    // CAN0 Rx warning interrupt
                .long     CAN0_Wake_Up_IRQHandler       // CAN0 wake up interrupt                
                .long     I2S0_Tx_IRQHandler        // I2S0 transmit interrupt
                .long     I2S0_Rx_IRQHandler        // I2S0 receive interrupt                
                .long     Reserved53_IRQHandler     // Reserved interrupt 53 
                .long     Reserved54_IRQHandler     // Reserved interrupt 54
                .long     Reserved55_IRQHandler     // Reserved interrupt 55
                .long     Reserved56_IRQHandler     // Reserved interrupt 56
                .long     Reserved57_IRQHandler     // Reserved interrupt 57
                .long     Reserved58_IRQHandler     // Reserved interrupt 58
                .long     Reserved59_IRQHandler     // Reserved interrupt 59                
                .long     UART0_LON_IRQHandler      // UART0 LON interrupt
                .long     UART0_RX_TX_IRQHandler    // UART0 receive/transmit interrupt
                .long     UART0_ERR_IRQHandler      // UART0 error interrupt
                .long     UART1_RX_TX_IRQHandler    // UART1 receive/transmit interrupt
                .long     UART1_ERR_IRQHandler      // UART1 error interrupt
                .long     UART2_RX_TX_IRQHandler    // UART2 receive/transmit interrupt
                .long     UART2_ERR_IRQHandler      // UART2 error interrupt                
                .long     Reserved67_IRQHandler     // Reserved interrupt 67  
                .long     Reserved68_IRQHandler     // Reserved interrupt 68  
                .long     Reserved69_IRQHandler     // Reserved interrupt 69  
                .long     Reserved70_IRQHandler     // Reserved interrupt 70  
                .long     Reserved71_IRQHandler     // Reserved interrupt 71  
                .long     Reserved72_IRQHandler     // Reserved interrupt 72 
                .long     ADC0_IRQHandler   // ADC0 interrupt
                .long     ADC1_IRQHandler   // ADC1 interrupt
                .long     CMP0_IRQHandler   // CMP0 interrupt
                .long     CMP1_IRQHandler   // CMP1 interrupt
                .long     CMP2_IRQHandler   // CMP2 interrupt
                .long     FTM0_IRQHandler   // FTM0 fault, overflow and channels interrupt
                .long     FTM1_IRQHandler   // FTM1 fault, overflow and channels interrupt
                .long     FTM2_IRQHandler   // FTM2 fault, overflow and channels interrupt
                .long     CMT_IRQHandler    // CMT interrupt                
                .long     RTC_IRQHandler    // RTC interrupt
                .long     RTC_Seconds_IRQHandler    // RTC seconds interrupt
                .long     PIT0_IRQHandler   // PIT timer channel 0 interrupt
                .long     PIT1_IRQHandler   // PIT timer channel 1 interrupt
                .long     PIT2_IRQHandler   // PIT timer channel 2 interrupt
                .long     PIT3_IRQHandler   // PIT timer channel 3 interrupt
                .long     PDB0_IRQHandler   // PDB0 interrupt
                .long     USB0_IRQHandler   // USB0 interrupt
                .long     USBDCD_IRQHandler // USBDCD interrupt
                .long     Reserved91_IRQHandler     // Reserved interrupt 91
                .long     Reserved92_IRQHandler     // Reserved interrupt 92
                .long     Reserved93_IRQHandler     // Reserved interrupt 93
                .long     Reserved94_IRQHandler     // Reserved interrupt 94
                .long     Reserved95_IRQHandler     // Reserved interrupt 95
                .long     Reserved96_IRQHandler     // Reserved interrupt 96
                .long     DAC0_IRQHandler       // DAC0 interrupt
                .long     Reserved98_IRQHandler     // Reserved interrupt 98
                .long     TSI0_IRQHandler       // TSI0 interrupt                
                .long     MCG_IRQHandler        // MCG interrupt
                .long     LPTimer_IRQHandler    // LPTimer interrupt
                .long     Reserved102_IRQHandler    // Reserved interrupt 102
                .long     PORTA_IRQHandler      // Port A interrupt
                .long     PORTB_IRQHandler      // Port B interrupt
                .long     PORTC_IRQHandler      // Port C interrupt
                .long     PORTD_IRQHandler      // Port D interrupt
                .long     PORTE_IRQHandler      // Port E interrupt
                .long     Reserved108_IRQHandler    // Reserved interrupt 108
                .long     Reserved109_IRQHandler    // Reserved interrupt 109
                .long     SWI_IRQHandler        // Software interrupt                 
    
    .size    __isr_vector, . - __isr_vector

    .section .text.Reset_Handler
    .thumb
    .thumb_func
    .align 2
    .globl    Reset_Handler
    .type    Reset_Handler, %function
Reset_Handler:
/*
 *    Call SystemInit before loading the .data section to prevent the watchdog
 *    from resetting the board.
 */
    ldr    r0, =SystemInit
    blx    r0

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


                def_irq_default_handler  DMA0_IRQHandler 
                def_irq_default_handler  DMA1_IRQHandler 
                def_irq_default_handler  DMA2_IRQHandler 
                def_irq_default_handler  DMA3_IRQHandler 
                def_irq_default_handler  DMA4_IRQHandler                    
                def_irq_default_handler  DMA5_IRQHandler                    
                def_irq_default_handler  DMA6_IRQHandler                    
                def_irq_default_handler  DMA7_IRQHandler                    
                def_irq_default_handler  DMA8_IRQHandler                   
                def_irq_default_handler  DMA9_IRQHandler                    
                def_irq_default_handler  DMA10_IRQHandler                  
                def_irq_default_handler  DMA11_IRQHandler                      
                def_irq_default_handler  DMA12_IRQHandler                  
                def_irq_default_handler  DMA13_IRQHandler                      
                def_irq_default_handler  DMA14_IRQHandler                      
                def_irq_default_handler  DMA15_IRQHandler                        
                def_irq_default_handler  DMA_Error_IRQHandler    
                def_irq_default_handler  Reserved33_IRQHandler   
                def_irq_default_handler  FTFL_IRQHandler     
                def_irq_default_handler  Read_Collision_IRQHandler    
                def_irq_default_handler  LVD_LVW_IRQHandler     
                def_irq_default_handler  LLW_IRQHandler     
                def_irq_default_handler  Watchdog_IRQHandler    
                def_irq_default_handler  Reserved39_IRQHandler   
                def_irq_default_handler  I2C0_IRQHandler  
                def_irq_default_handler  I2C1_IRQHandler     
                def_irq_default_handler  SPI0_IRQHandler     
                def_irq_default_handler  SPI1_IRQHandler      
                def_irq_default_handler  Reserved44_IRQHandler     
                def_irq_default_handler  CAN0_ORed_Message_buffer_IRQHandler 
                def_irq_default_handler  CAN0_Bus_Off_IRQHandler    
                def_irq_default_handler  CAN0_Error_IRQHandler      
                def_irq_default_handler  CAN0_Tx_Warning_IRQHandler 
                def_irq_default_handler  CAN0_Rx_Warning_IRQHandler 
                def_irq_default_handler  CAN0_Wake_Up_IRQHandler  
                def_irq_default_handler  I2S0_Tx_IRQHandler     
                def_irq_default_handler  I2S0_Rx_IRQHandler     
                def_irq_default_handler  Reserved53_IRQHandler  
                def_irq_default_handler  Reserved54_IRQHandler    
                def_irq_default_handler  Reserved55_IRQHandler    
                def_irq_default_handler  Reserved56_IRQHandler    
                def_irq_default_handler  Reserved57_IRQHandler    
                def_irq_default_handler  Reserved58_IRQHandler    
                def_irq_default_handler  Reserved59_IRQHandler    
                def_irq_default_handler  UART0_LON_IRQHandler     
                def_irq_default_handler  UART0_RX_TX_IRQHandler   
                def_irq_default_handler  UART0_ERR_IRQHandler     
                def_irq_default_handler  UART1_RX_TX_IRQHandler   
                def_irq_default_handler  UART1_ERR_IRQHandler     
                def_irq_default_handler  UART2_RX_TX_IRQHandler   
                def_irq_default_handler  UART2_ERR_IRQHandler     
                def_irq_default_handler  Reserved67_IRQHandler    
                def_irq_default_handler  Reserved68_IRQHandler    
                def_irq_default_handler  Reserved69_IRQHandler    
                def_irq_default_handler  Reserved70_IRQHandler    
                def_irq_default_handler  Reserved71_IRQHandler    
                def_irq_default_handler  Reserved72_IRQHandler    
                def_irq_default_handler  ADC0_IRQHandler     
                def_irq_default_handler  ADC1_IRQHandler     
                def_irq_default_handler  CMP0_IRQHandler     
                def_irq_default_handler  CMP1_IRQHandler     
                def_irq_default_handler  CMP2_IRQHandler     
                def_irq_default_handler  FTM0_IRQHandler     
                def_irq_default_handler  FTM1_IRQHandler     
                def_irq_default_handler  FTM2_IRQHandler     
                def_irq_default_handler  CMT_IRQHandler     
                def_irq_default_handler  RTC_IRQHandler     
                def_irq_default_handler  RTC_Seconds_IRQHandler     
                def_irq_default_handler  PIT0_IRQHandler     
                def_irq_default_handler  PIT1_IRQHandler     
                def_irq_default_handler  PIT2_IRQHandler     
                def_irq_default_handler  PIT3_IRQHandler     
                def_irq_default_handler  PDB0_IRQHandler     
                def_irq_default_handler  USB0_IRQHandler     
                def_irq_default_handler  USBDCD_IRQHandler   
                def_irq_default_handler  Reserved91_IRQHandler 
                def_irq_default_handler  Reserved92_IRQHandler  
                def_irq_default_handler  Reserved93_IRQHandler     
                def_irq_default_handler  Reserved94_IRQHandler    
                def_irq_default_handler  Reserved95_IRQHandler     
                def_irq_default_handler  Reserved96_IRQHandler     
                def_irq_default_handler  DAC0_IRQHandler     
                def_irq_default_handler  Reserved98_IRQHandler    
                def_irq_default_handler  TSI0_IRQHandler   
                def_irq_default_handler  MCG_IRQHandler    
                def_irq_default_handler  LPTimer_IRQHandler   
                def_irq_default_handler  Reserved102_IRQHandler   
                def_irq_default_handler  PORTA_IRQHandler     
                def_irq_default_handler  PORTB_IRQHandler     
                def_irq_default_handler  PORTC_IRQHandler     
                def_irq_default_handler  PORTD_IRQHandler     
                def_irq_default_handler  PORTE_IRQHandler     
                def_irq_default_handler  Reserved108_IRQHandler    
                def_irq_default_handler  Reserved109_IRQHandler 
                def_irq_default_handler  SWI_IRQHandler  
                def_irq_default_handler  DefaultISR      

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
