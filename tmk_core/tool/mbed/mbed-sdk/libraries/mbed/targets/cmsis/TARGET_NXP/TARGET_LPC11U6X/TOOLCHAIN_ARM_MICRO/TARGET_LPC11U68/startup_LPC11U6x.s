;/**************************************************************************//**
; * @file     startup_LPC11U6x.s
; * @brief    CMSIS Cortex-M0+ Core Device Startup File for
; *           NXP LPC11U6x Device Series
; * @version  V1.00
; * @date     22. October 2013
; *
; * @note
; * Copyright (C) 2013 ARM Limited. All rights reserved.
; *
; * @par
; * ARM Limited (ARM) is supplying this software for use with Cortex-M
; * processor based microcontrollers.  This file can be freely distributed
; * within development tools that are supporting such ARM based processors.
; *
; * @par
; * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
; * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
; * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
; * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
; *
; ******************************************************************************/

; *------- <<< Use Configuration Wizard in Context Menu >>> ------------------

; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
                EXPORT  __initial_sp

__initial_sp        EQU     0x10008000  ; Top of RAM from LPC1U68


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000000

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors

__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; External Interrupts
                DCD     PIN_INT0_IRQHandler       ; 16+ 0  GPIO pin interrupt 0
                DCD     PIN_INT1_IRQHandler       ; 16+ 1  GPIO pin interrupt 1
                DCD     PIN_INT2_IRQHandler       ; 16+ 2  GPIO pin interrupt 2
                DCD     PIN_INT3_IRQHandler       ; 16+ 3  GPIO pin interrupt 3
                DCD     PIN_INT4_IRQHandler       ; 16+ 4  GPIO pin interrupt 4
                DCD     PIN_INT5_IRQHandler       ; 16+ 5  GPIO pin interrupt 5
                DCD     PIN_INT6_IRQHandler       ; 16+ 6  GPIO pin interrupt 6
                DCD     PIN_INT7_IRQHandler       ; 16+ 7  GPIO pin interrupt 7
                DCD     GINT0_IRQHandler          ; 16+ 8  GPIO GROUP0 interrupt
                DCD     GINT1_IRQHandler          ; 16+ 9  GPIO GROUP1 interrupt
                DCD     I2C1_IRQHandler           ; 16+10  I2C1 interrupt
                DCD     USART1_4_IRQHandler       ; 16+11  Combined USART1 and USART4 interrupts
                DCD     USART2_3_IRQHandler       ; 16+12  Combined USART2 and USART3 interrupts
                DCD     SCT0_1_IRQHandler         ; 16+13  Combined SCT0 and SCT1 interrupts
                DCD     SSP1_IRQHandler           ; 16+14  SSP1 interrupt
                DCD     I2C0_IRQHandler           ; 16+15  I2C0 interrupt
                DCD     CT16B0_IRQHandler         ; 16+16  CT16B0 interrupt
                DCD     CT16B1_IRQHandler         ; 16+17  CT16B1 interrupt
                DCD     CT32B0_IRQHandler         ; 16+18  CT32B0 interrupt
                DCD     CT32B1_IRQHandler         ; 16+19  CT32B1 interrupt
                DCD     SSP0_IRQHandler           ; 16+20  SSP0 interrupt
                DCD     USART0_IRQHandler         ; 16+21  USART0 interrupt
                DCD     USB_IRQHandler            ; 16+22  USB interrupt
                DCD     USB_FIQ_IRQHandler        ; 16+23  USB_FIQ interrupt
                DCD     ADC_A_IRQHandler          ; 16+24  Combined ADC_A end-of-sequence A and threshold crossing interrupts
                DCD     RTC_IRQHandler            ; 16+25  RTC interrupt
                DCD     BOD_WDT_IRQHandler        ; 16+26  Combined BOD and WWDT interrupt
                DCD     FLASH_IRQHandler          ; 16+27  Combined flash and EEPROM controller interrupts
                DCD     DMA_IRQHandler            ; 16+28  DMA interrupt
                DCD     ADC_B_IRQHandler          ; 16+29  Combined ADC_A end-of-sequence A and threshold crossing interrupts
                DCD     USBWAKEUP_IRQHandler      ; 16+30  USB_WAKEUP interrupt
                DCD     0                         ; 16+31  Reserved

; <h> Code Read Protection
;   <o> Code Read Protection  <0xFFFFFFFF=>CRP Disabled
;                             <0x12345678=>CRP Level 1
;                             <0x87654321=>CRP Level 2
;                             <0x43218765=>CRP Level 3 (ARE YOU SURE?)
;                             <0x4E697370=>NO ISP (ARE YOU SURE?)
; </h>
                IF      :LNOT::DEF:NO_CRP
                AREA    |.ARM.__at_0x02FC|, CODE, READONLY
                DCD     0xFFFFFFFF
                ENDIF

                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP
Reserved_IRQHandler PROC
                EXPORT  Reserved_IRQHandler       [WEAK]
                B       .
                ENDP

Default_Handler PROC
                EXPORT  PIN_INT0_IRQHandler       [WEAK]
                EXPORT  PIN_INT1_IRQHandler       [WEAK]
                EXPORT  PIN_INT2_IRQHandler       [WEAK]
                EXPORT  PIN_INT3_IRQHandler       [WEAK]
                EXPORT  PIN_INT4_IRQHandler       [WEAK]
                EXPORT  PIN_INT5_IRQHandler       [WEAK]
                EXPORT  PIN_INT6_IRQHandler       [WEAK]
                EXPORT  PIN_INT7_IRQHandler       [WEAK]
                EXPORT  GINT0_IRQHandler          [WEAK]
                EXPORT  GINT1_IRQHandler          [WEAK]
                EXPORT  I2C1_IRQHandler           [WEAK]
                EXPORT  USART1_4_IRQHandler       [WEAK]
                EXPORT  USART2_3_IRQHandler       [WEAK]
                EXPORT  SCT0_1_IRQHandler         [WEAK]
                EXPORT  SSP1_IRQHandler           [WEAK]
                EXPORT  I2C0_IRQHandler           [WEAK]
                EXPORT  CT16B0_IRQHandler         [WEAK]
                EXPORT  CT16B1_IRQHandler         [WEAK]
                EXPORT  CT32B0_IRQHandler         [WEAK]
                EXPORT  CT32B1_IRQHandler         [WEAK]
                EXPORT  SSP0_IRQHandler           [WEAK]
                EXPORT  USART0_IRQHandler         [WEAK]
                EXPORT  USB_IRQHandler            [WEAK]
                EXPORT  USB_FIQ_IRQHandler        [WEAK]
                EXPORT  ADC_A_IRQHandler          [WEAK]
                EXPORT  RTC_IRQHandler            [WEAK]
                EXPORT  BOD_WDT_IRQHandler        [WEAK]
                EXPORT  FLASH_IRQHandler          [WEAK]
                EXPORT  DMA_IRQHandler            [WEAK]
                EXPORT  ADC_B_IRQHandler          [WEAK]
                EXPORT  USBWAKEUP_IRQHandler      [WEAK]

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
USBWAKEUP_IRQHandler

                B       .

                ENDP


                ALIGN


; User Initial Stack & Heap

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                END
