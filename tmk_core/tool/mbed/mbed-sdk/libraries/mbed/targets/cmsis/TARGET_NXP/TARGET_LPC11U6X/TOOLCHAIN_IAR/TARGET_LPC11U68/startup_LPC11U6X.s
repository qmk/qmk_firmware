;/*****************************************************************************
; * @file:    startup_LPC11u6x.s
; * @purpose: CMSIS Cortex-M0PLUS Core Device Startup File
; *           for the NXP LPC11u6x Device Series (manually edited)
; * @version: V1.00
; * @date:    19. October 2009
; *----------------------------------------------------------------------------
; *
; * Copyright (C) 2009 ARM Limited. All rights reserved.
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
        DCD     0
        DCD     0
        DCD     0
__vector_table_0x1c
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     SVC_Handler
        DCD     0
        DCD     0
        DCD     PendSV_Handler
        DCD     SysTick_Handler

        DCD PIN_INT0_IRQHandler           ; Pin interrupt 0
        DCD PIN_INT1_IRQHandler           ; Pin interrupt 1
        DCD PIN_INT2_IRQHandler           ; Pin interrupt 2
        DCD PIN_INT3_IRQHandler           ; Pin interrupt 3
        DCD PIN_INT4_IRQHandler           ; Pin interrupt 4
        DCD PIN_INT5_IRQHandler           ; Pin interrupt 5
        DCD PIN_INT6_IRQHandler           ; Pin interrupt 6
        DCD PIN_INT7_IRQHandler           ; Pin interrupt 7
        DCD GINT0_IRQHandler              ; Port interrupt group 0
        DCD GINT1_IRQHandler              ; Port interrupt group 1
        DCD I2C1_IRQHandler               ; I2C1 interrupt
        DCD USART1_4_IRQHandler           ; USARTS 1 and 4 shared interrupt
        DCD USART2_3_IRQHandler           ; USARTS 2 and 3 shared interrupt
        DCD SCT0_1_IRQHandler             ; SCT 0 and 1 shared interrupt
        DCD SSP1_IRQHandler               ; SSP1 interrupt
        DCD I2C0_IRQHandler               ; I2C0 interrupt
        DCD CT16B0_IRQHandler          ; CT16B0 (16-bit Timer 0)
        DCD CT16B1_IRQHandler          ; CT16B1 (16-bit Timer 1)
        DCD CT32B0_IRQHandler          ; CT32B0 (32-bit Timer 0)
        DCD CT32B1_IRQHandler          ; CT32B0 (32-bit Timer 1)
        DCD SSP0_IRQHandler               ; SSP0 interrupt interrupt
        DCD USART0_IRQHandler             ; USART 0 interrupt interrupt
        DCD USB_IRQHandler                ; USB IRQ interrupt
        DCD USB_FIQ_IRQHandler                ; USB FIQ interrupt
        DCD ADC_A_IRQHandler               ; ADC A sequence (A/D Converter) interrupt
        DCD RTC_IRQHandler                ; RTC interrupt
        DCD BOD_WDT_IRQHandler            ; Shared BOD (Brownout Detect) and WDT interrupts
        DCD FLASH_IRQHandler                ; Flash Memory Controller interrupt
        DCD DMA_IRQHandler                ; DMA Controller interrupt
        DCD ADC_B_IRQHandler               ; ADC B sequence interrupt
        DCD USBWakeup_IRQHandler          ; USB wake-up interrupt
        DCD Reserved_IRQHandler

__Vectors_End

__Vectors       EQU   __vector_table
__Vectors_Size 	EQU 	__Vectors_End - __Vectors


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB
        PUBWEAK Reset_Handler
        SECTION .text:CODE:NOROOT:REORDER(2)
Reset_Handler
        LDR     R0, =SystemInit
        BLX     R0
        LDR     R0, =__iar_program_start
        BX      R0

        PUBWEAK NMI_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
NMI_Handler
        B .

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
HardFault_Handler
        B .

        PUBWEAK SVC_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SVC_Handler
        B .

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
PendSV_Handler
        B .

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SysTick_Handler
        B .

	PUBWEAK Reserved_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
Reserved_IRQHandler
        B .
        
        
		PUBWEAK  PIN_INT0_IRQHandler
		PUBWEAK  PIN_INT1_IRQHandler
		PUBWEAK  PIN_INT2_IRQHandler
		PUBWEAK  PIN_INT3_IRQHandler
		PUBWEAK  PIN_INT4_IRQHandler
		PUBWEAK  PIN_INT5_IRQHandler
		PUBWEAK  PIN_INT6_IRQHandler
		PUBWEAK  PIN_INT7_IRQHandler
		PUBWEAK  GINT0_IRQHandler
		PUBWEAK  GINT1_IRQHandler
		PUBWEAK  I2C1_IRQHandler
		PUBWEAK	USART1_4_IRQHandler
		PUBWEAK	USART2_3_IRQHandler
		PUBWEAK  SCT0_1_IRQHandler
		PUBWEAK  SSP1_IRQHandler
		PUBWEAK  I2C0_IRQHandler
		PUBWEAK	CT16B0_IRQHandler
		PUBWEAK	CT16B1_IRQHandler
		PUBWEAK	CT32B0_IRQHandler
		PUBWEAK	CT32B1_IRQHandler
		PUBWEAK	SSP0_IRQHandler
		PUBWEAK	USART0_IRQHandler
		PUBWEAK	USB_IRQHandler
		PUBWEAK	USB_FIQ_IRQHandler
		PUBWEAK	ADC_A_IRQHandler
		PUBWEAK	RTC_IRQHandler
		PUBWEAK	BOD_WDT_IRQHandler
		PUBWEAK	FLASH_IRQHandler
		PUBWEAK	DMA_IRQHandler
		PUBWEAK	ADC_B_IRQHandler
		PUBWEAK	USBWakeup_IRQHandler

        SECTION .text:CODE:REORDER:NOROOT(1)
        THUMB    
    
PIN_INT0_IRQHandler
PIN_INT1_IRQHandler
PIN_INT2_IRQHandler
PIN_INT3_IRQHandler
PIN_INT4_IRQHandler
PIN_INT5_IRQHandler
PIN_INT6_IRQHandler
PIN_INT7_IRQHandler
GINT0_IRQHandler
GINT1_IRQHandler
I2C1_IRQHandler
USART1_4_IRQHandler
USART2_3_IRQHandler
SCT0_1_IRQHandler
SSP1_IRQHandler
I2C0_IRQHandler
CT16B0_IRQHandler
CT16B1_IRQHandler
CT32B0_IRQHandler
CT32B1_IRQHandler
SSP0_IRQHandler
USART0_IRQHandler
USB_IRQHandler
USB_FIQ_IRQHandler
ADC_A_IRQHandler
RTC_IRQHandler
BOD_WDT_IRQHandler
FLASH_IRQHandler
DMA_IRQHandler
ADC_B_IRQHandler
USBWakeup_IRQHandler
Default_Handler
        B Default_Handler

        SECTION .crp:CODE:ROOT(2)
        DATA
/* Code Read Protection
NO_ISP  0x4E697370 -  Prevents sampling of pin PIO0_1 for entering ISP mode
CRP1    0x12345678 - Write to RAM command cannot access RAM below 0x10000300.
                   - Copy RAM to flash command can not write to Sector 0.
                   - Erase command can erase Sector 0 only when all sectors
                     are selected for erase.
                   - Compare command is disabled.
                   - Read Memory command is disabled.
CRP2    0x87654321 - Read Memory is disabled.
                   - Write to RAM is disabled.
                   - "Go" command is disabled.
                   - Copy RAM to flash is disabled.
                   - Compare is disabled.
CRP3    0x43218765 - Access to chip via the SWD pins is disabled. ISP entry
                     by pulling PIO0_1 LOW is disabled if a valid user code is
                     present in flash sector 0.
Caution: If CRP3 is selected, no future factory testing can be
performed on the device.
*/
        DCD     0xFFFFFFFF        
        
        END
