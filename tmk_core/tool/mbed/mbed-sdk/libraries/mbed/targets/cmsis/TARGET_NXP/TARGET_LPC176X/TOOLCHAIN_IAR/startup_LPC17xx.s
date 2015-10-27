;/*****************************************************************************
; * @file:    startup_LPC17xx.s
; * @purpose: CMSIS Cortex-M3 Core Device Startup File
; *           for the NXP LPC17xx Device Series
; * @version: V1.03
; * @date:    09. February 2010
; *----------------------------------------------------------------------------
; *
; * Copyright (C) 2010 ARM Limited. All rights reserved.
; *
; * ARM Limited (ARM) is supplying this software for use with Cortex-Mx
; * processor based microcontrollers.  This file can be freely distributed
; * within development tools that are supporting such ARM based processors.
; *
; * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
; * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
; * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
; * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
; *
; ******************************************************************************/


;
; The modules in this file are included in the libraries, and may be replaced
; by any user-defined modules that define the PUBLIC symbol _program_start or
; a user defined start symbol.
; To override the cstartup defined in the library, simply add your modified
; version to the workbench project.
;
; The vector table is normally located at address 0.
; When debugging in RAM, it can be located in RAM, aligned to at least 2^6.
; The name "__vector_table" has special meaning for C-SPY:
; it is where the SP start value is found, and the NVIC vector
; table register (VTOR) is initialized to this address if != 0.
;
; Cortex-M version
;

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  SystemInit
        PUBLIC  __vector_table
        PUBLIC  __vector_table_0x1c
        PUBLIC  __Vectors
        PUBLIC  __Vectors_End
        PUBLIC  __Vectors_Size

        DATA

__vector_table
        DCD     sfe(CSTACK)
        DCD     Reset_Handler

        DCD     NMI_Handler
        DCD     HardFault_Handler
        DCD     MemManage_Handler
        DCD     BusFault_Handler
        DCD     UsageFault_Handler
__vector_table_0x1c
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     SVC_Handler
        DCD     DebugMon_Handler
        DCD     0
        DCD     PendSV_Handler
        DCD     SysTick_Handler

        ; External Interrupts
        DCD     WDT_IRQHandler            ; 16: Watchdog Timer
        DCD     TIMER0_IRQHandler         ; 17: Timer0
        DCD     TIMER1_IRQHandler         ; 18: Timer1
        DCD     TIMER2_IRQHandler         ; 19: Timer2
        DCD     TIMER3_IRQHandler         ; 20: Timer3
        DCD     UART0_IRQHandler          ; 21: UART0
        DCD     UART1_IRQHandler          ; 22: UART1
        DCD     UART2_IRQHandler          ; 23: UART2
        DCD     UART3_IRQHandler          ; 24: UART3
        DCD     PWM1_IRQHandler           ; 25: PWM1
        DCD     I2C0_IRQHandler           ; 26: I2C0
        DCD     I2C1_IRQHandler           ; 27: I2C1
        DCD     I2C2_IRQHandler           ; 28: I2C2
        DCD     SPI_IRQHandler            ; 29: SPI
        DCD     SSP0_IRQHandler           ; 30: SSP0
        DCD     SSP1_IRQHandler           ; 31: SSP1
        DCD     PLL0_IRQHandler           ; 32: PLL0 Lock (Main PLL)
        DCD     RTC_IRQHandler            ; 33: Real Time Clock
        DCD     EINT0_IRQHandler          ; 34: External Interrupt 0
        DCD     EINT1_IRQHandler          ; 35: External Interrupt 1
        DCD     EINT2_IRQHandler          ; 36: External Interrupt 2
        DCD     EINT3_IRQHandler          ; 37: External Interrupt 3
        DCD     ADC_IRQHandler            ; 38: A/D Converter
        DCD     BOD_IRQHandler            ; 39: Brown-Out Detect
        DCD     USB_IRQHandler            ; 40: USB
        DCD     CAN_IRQHandler            ; 41: CAN
        DCD     DMA_IRQHandler            ; 42: General Purpose DMA
        DCD     I2S_IRQHandler            ; 43: I2S
        DCD     ENET_IRQHandler           ; 44: Ethernet
        DCD     RIT_IRQHandler            ; 45: Repetitive Interrupt Timer
        DCD     MCPWM_IRQHandler          ; 46: Motor Control PWM
        DCD     QEI_IRQHandler            ; 47: Quadrature Encoder Interface
        DCD     PLL1_IRQHandler           ; 48: PLL1 Lock (USB PLL)
        DCD			USBActivity_IRQHandler	  ; 49: USB Activity Interrupt
        DCD			CANActivity_IRQHandler	  ; 50: CAN Activity Interrupt
__Vectors_End

__Vectors       EQU   __vector_table
__Vectors_Size 	EQU 	__Vectors_End - __Vectors


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:REORDER(2)
Reset_Handler
        LDR     R0, =SystemInit
        BLX     R0
        LDR     R0, =__iar_program_start
        BX      R0

        PUBWEAK NMI_Handler
        SECTION .text:CODE:REORDER(1)
NMI_Handler
        B NMI_Handler

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:REORDER(1)
HardFault_Handler
        B HardFault_Handler

        PUBWEAK MemManage_Handler
        SECTION .text:CODE:REORDER(1)
MemManage_Handler
        B MemManage_Handler

        PUBWEAK BusFault_Handler
        SECTION .text:CODE:REORDER(1)
BusFault_Handler
        B BusFault_Handler

        PUBWEAK UsageFault_Handler
        SECTION .text:CODE:REORDER(1)
UsageFault_Handler
        B UsageFault_Handler

        PUBWEAK SVC_Handler
        SECTION .text:CODE:REORDER(1)
SVC_Handler
        B SVC_Handler

        PUBWEAK DebugMon_Handler
        SECTION .text:CODE:REORDER(1)
DebugMon_Handler
        B DebugMon_Handler

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:REORDER(1)
PendSV_Handler
        B PendSV_Handler

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:REORDER(1)
SysTick_Handler
        B SysTick_Handler

        PUBWEAK WDT_IRQHandler
        SECTION .text:CODE:REORDER(1)
WDT_IRQHandler
        B WDT_IRQHandler

        PUBWEAK TIMER0_IRQHandler
        SECTION .text:CODE:REORDER(1)
TIMER0_IRQHandler
        B TIMER0_IRQHandler

        PUBWEAK TIMER1_IRQHandler
        SECTION .text:CODE:REORDER(1)
TIMER1_IRQHandler
        B TIMER1_IRQHandler

        PUBWEAK TIMER2_IRQHandler
        SECTION .text:CODE:REORDER(1)
TIMER2_IRQHandler
        B TIMER2_IRQHandler

        PUBWEAK TIMER3_IRQHandler
        SECTION .text:CODE:REORDER(1)
TIMER3_IRQHandler
        B TIMER3_IRQHandler

        PUBWEAK UART0_IRQHandler
        SECTION .text:CODE:REORDER(1)
UART0_IRQHandler
        B UART0_IRQHandler

        PUBWEAK UART1_IRQHandler
        SECTION .text:CODE:REORDER(1)
UART1_IRQHandler
        B UART1_IRQHandler

        PUBWEAK UART2_IRQHandler
        SECTION .text:CODE:REORDER(1)
UART2_IRQHandler
        B UART2_IRQHandler

        PUBWEAK UART3_IRQHandler
        SECTION .text:CODE:REORDER(1)
UART3_IRQHandler
        B UART3_IRQHandler

        PUBWEAK PWM1_IRQHandler
        SECTION .text:CODE:REORDER(1)
PWM1_IRQHandler
        B PWM1_IRQHandler

        PUBWEAK I2C0_IRQHandler
        SECTION .text:CODE:REORDER(1)
I2C0_IRQHandler
        B I2C0_IRQHandler

        PUBWEAK I2C1_IRQHandler
        SECTION .text:CODE:REORDER(1)
I2C1_IRQHandler
        B I2C1_IRQHandler

        PUBWEAK I2C2_IRQHandler
        SECTION .text:CODE:REORDER(1)
I2C2_IRQHandler
        B I2C2_IRQHandler

        PUBWEAK SPI_IRQHandler
        SECTION .text:CODE:REORDER(1)
SPI_IRQHandler
        B SPI_IRQHandler

        PUBWEAK SSP0_IRQHandler
        SECTION .text:CODE:REORDER(1)
SSP0_IRQHandler
        B SSP0_IRQHandler

        PUBWEAK SSP1_IRQHandler
        SECTION .text:CODE:REORDER(1)
SSP1_IRQHandler
        B SSP1_IRQHandler

        PUBWEAK PLL0_IRQHandler
        SECTION .text:CODE:REORDER(1)
PLL0_IRQHandler
        B PLL0_IRQHandler

        PUBWEAK RTC_IRQHandler
        SECTION .text:CODE:REORDER(1)
RTC_IRQHandler
        B RTC_IRQHandler

        PUBWEAK EINT0_IRQHandler
        SECTION .text:CODE:REORDER(1)
EINT0_IRQHandler
        B EINT0_IRQHandler

        PUBWEAK EINT1_IRQHandler
        SECTION .text:CODE:REORDER(1)
EINT1_IRQHandler
        B EINT1_IRQHandler

        PUBWEAK EINT2_IRQHandler
        SECTION .text:CODE:REORDER(1)
EINT2_IRQHandler
        B EINT2_IRQHandler

        PUBWEAK EINT3_IRQHandler
        SECTION .text:CODE:REORDER(1)
EINT3_IRQHandler
        B EINT3_IRQHandler

        PUBWEAK ADC_IRQHandler
        SECTION .text:CODE:REORDER(1)
ADC_IRQHandler
        B ADC_IRQHandler

        PUBWEAK BOD_IRQHandler
        SECTION .text:CODE:REORDER(1)
BOD_IRQHandler
        B BOD_IRQHandler

        PUBWEAK USB_IRQHandler
        SECTION .text:CODE:REORDER(1)
USB_IRQHandler
        B USB_IRQHandler

        PUBWEAK CAN_IRQHandler
        SECTION .text:CODE:REORDER(1)
CAN_IRQHandler
        B CAN_IRQHandler

        PUBWEAK DMA_IRQHandler
        SECTION .text:CODE:REORDER(1)
DMA_IRQHandler
        B DMA_IRQHandler

        PUBWEAK I2S_IRQHandler
        SECTION .text:CODE:REORDER(1)
I2S_IRQHandler
        B I2S_IRQHandler

        PUBWEAK ENET_IRQHandler
        SECTION .text:CODE:REORDER(1)
ENET_IRQHandler
        B ENET_IRQHandler

        PUBWEAK RIT_IRQHandler
        SECTION .text:CODE:REORDER(1)
RIT_IRQHandler
        B RIT_IRQHandler

        PUBWEAK MCPWM_IRQHandler
        SECTION .text:CODE:REORDER(1)
MCPWM_IRQHandler
        B MCPWM_IRQHandler

        PUBWEAK QEI_IRQHandler
        SECTION .text:CODE:REORDER(1)
QEI_IRQHandler
        B QEI_IRQHandler

        PUBWEAK PLL1_IRQHandler
        SECTION .text:CODE:REORDER(1)
PLL1_IRQHandler
        B PLL1_IRQHandler

        PUBWEAK USBActivity_IRQHandler
        SECTION .text:CODE:REORDER(1)
USBActivity_IRQHandler
        B USBActivity_IRQHandler

        PUBWEAK CANActivity_IRQHandler
        SECTION .text:CODE:REORDER(1)
CANActivity_IRQHandler
        B CANActivity_IRQHandler

#ifndef SRAM
        SECTION .crp:CODE:ROOT(2)
        DATA
/* Code Read Protection
CRP1    0x12345678 - Write to RAM command can not access RAM below 0x10000200.
                   - Read Memory command: disabled.
                   - Copy RAM to Flash command: cannot write to Sector 0.
                   - "Go" command: disabled.
                   - Erase sector(s) command: can erase any individual sector except 
                   	 sector 0 only, or can erase all sectors at once.
                   - Compare command: disabled
CRP2    0x87654321 - Write to RAM command: disabled.
                   - Copy RAM to Flash: disabled.
                   - Erase command: only allows erase of all sectors.
CRP3    0x43218765 - Access to chip via the SWD pins is disabled. ISP entry
                     by pulling PIO0_1 LOW is disabled if a valid user code is
                     present in flash sector 0.
Caution: If CRP3 is selected, no future factory testing can be
performed on the device.
*/
	DCD	0xFFFFFFFF
#endif
        END
