;/**************************************************************************//**
; * @file     startup_LPC15xx.s
; * @brief    CMSIS Cortex-M3 Core Device Startup File for
; *           NXP LPC15xx Device Series
; * @version  V1.00
; * @date     17. July 2013
; *
; * @note
; * Copyright (C) 2009-2013 ARM Limited. All rights reserved.
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

Stack_Size      EQU     0x00000200

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
                EXPORT  __initial_sp

__initial_sp        EQU     0x02009000  ; Top of RAM from LPC1549


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
                DCD     MemManage_Handler         ; MPU Fault Handler
                DCD     BusFault_Handler          ; Bus Fault Handler
                DCD     UsageFault_Handler        ; Usage Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     DebugMon_Handler          ; Debug Monitor Handler
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; External Interrupts
                DCD     WDT_IRQHandler            ; 16+ 0 Windowed watchdog timer interrupt
                DCD     BOD_IRQHandler            ; 16+ 1 BOD interrupt
                DCD     FLASH_IRQHandler          ; 16+ 2 Flash controller interrupt
                DCD     EE_IRQHandler             ; 16+ 3 EEPROM controller interrupt
                DCD     DMA_IRQHandler            ; 16+ 4 DMA interrupt
                DCD     GINT0_IRQHandler          ; 16+ 5 GPIO group0 interrupt
                DCD     GINT1_IRQHandler          ; 16+ 6 GPIO group1 interrupt
                DCD     PIN_INT0_IRQHandler       ; 16+ 7 Pin interrupt 0 or pattern match engine slice 0 interrupt
                DCD     PIN_INT1_IRQHandler       ; 16+ 8 Pin interrupt 1 or pattern match engine slice 1 interrupt
                DCD     PIN_INT2_IRQHandler       ; 16+ 9 Pin interrupt 2 or pattern match engine slice 2 interrupt
                DCD     PIN_INT3_IRQHandler       ; 16+10 Pin interrupt 3 or pattern match engine slice 3 interrupt
                DCD     PIN_INT4_IRQHandler       ; 16+11 Pin interrupt 4 or pattern match engine slice 4 interrupt
                DCD     PIN_INT5_IRQHandler       ; 16+12 Pin interrupt 5 or pattern match engine slice 5 interrupt
                DCD     PIN_INT6_IRQHandler       ; 16+13 Pin interrupt 6 or pattern match engine slice 6 interrupt
                DCD     PIN_INT7_IRQHandler       ; 16+14 Pin interrupt 7 or pattern match engine slice 7 interrupt
                DCD     RIT_IRQHandler            ; 16+15 RIT interrupt
                DCD     SCT0_IRQHandler           ; 16+16 State configurable timer interrupt
                DCD     SCT1_IRQHandler           ; 16+17 State configurable timer interrupt
                DCD     SCT2_IRQHandler           ; 16+18 State configurable timer interrupt
                DCD     SCT3_IRQHandler           ; 16+19 State configurable timer interrupt
                DCD     MRT_IRQHandler            ; 16+20 Multi-rate timer interrupt
                DCD     UART0_IRQHandler          ; 16+21 USART0 interrupt
                DCD     UART1_IRQHandler          ; 16+22 USART1 interrupt
                DCD     UART2_IRQHandler          ; 16+23 USART2 interrupt
                DCD     I2C0_IRQHandler           ; 16+24 I2C0 interrupt
                DCD     SPI0_IRQHandler           ; 16+25 SPI0 interrupt
                DCD     SPI1_IRQHandler           ; 16+26 SPI1 interrupt
                DCD     C_CAN0_IRQHandler         ; 16+27 C_CAN0 interrupt
                DCD     USB_IRQ_IRQHandler        ; 16+28 USB interrupt
                DCD     USB_FIQ_IRQHandler        ; 16+29 USB interrupt
                DCD     USBWAKEUP_IRQHandler      ; 16+30 USB wake-up interrupt
                DCD     ADC0_SEQA_IRQHandler      ; 16+31 ADC0 sequence A completion.
                DCD     ADC0_SEQB_IRQHandler      ; 16+32 ADC0 sequence B completion.
                DCD     ADC0_THCMP_IRQHandler     ; 16+33 ADC0 threshold compare
                DCD     ADC0_OVR_IRQHandler       ; 16+34 ADC0 overrun
                DCD     ADC1_SEQA_IRQHandler      ; 16+35 ADC1 sequence A completion.
                DCD     ADC1_SEQB_IRQHandler      ; 16+36 ADC1 sequence B completion.
                DCD     ADC1_THCMP_IRQHandler     ; 16+37 ADC1 threshold compare
                DCD     ADC1_OVR_IRQHandler       ; 16+38 ADC1 overrun
                DCD     DAC_IRQHandler            ; 16+39 DAC interrupt
                DCD     CMP0_IRQHandler           ; 16+40 Analog comparator 0 interrupt (ACMP0)
                DCD     CMP1_IRQHandler           ; 16+41 Analog comparator 1 interrupt (ACMP1)
                DCD     CMP2_IRQHandler           ; 16+42 Analog comparator 2 interrupt (ACMP2)
                DCD     CMP3_IRQHandler           ; 16+43 Analog comparator 3 interrupt (ACMP3)
                DCD     QEI_IRQHandler            ; 16+44 QEI interrupt
                DCD     RTC_ALARM_IRQHandler      ; 16+45 RTC alarm interrupt
                DCD     RTC_WAKE_IRQHandler       ; 16+46 RTC wake-up interrut

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

;--- enable SRAM1 and SRAM2 memory
                LDR     R0, =0x400740C4   ; SYSAHBCLKCTRL0 register addr
                LDR     R2, [R0]          ; read SYSAHBCLKCTRL0
                ORR     R2, R2, #0x18     ; enable SRAM1, SRAM2
                STR     R2, [R0]          ; store SYSAHBCLKCTRL0
;---                
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
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler         [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler          [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler        [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler          [WEAK]
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

Default_Handler PROC

                EXPORT  WDT_IRQHandler            [WEAK]
                EXPORT  BOD_IRQHandler            [WEAK]
                EXPORT  FLASH_IRQHandler          [WEAK]
                EXPORT  EE_IRQHandler             [WEAK]
                EXPORT  DMA_IRQHandler            [WEAK]
                EXPORT  GINT0_IRQHandler          [WEAK]
                EXPORT  GINT1_IRQHandler          [WEAK]
                EXPORT  PIN_INT0_IRQHandler       [WEAK]
                EXPORT  PIN_INT1_IRQHandler       [WEAK]
                EXPORT  PIN_INT2_IRQHandler       [WEAK]
                EXPORT  PIN_INT3_IRQHandler       [WEAK]
                EXPORT  PIN_INT4_IRQHandler       [WEAK]
                EXPORT  PIN_INT5_IRQHandler       [WEAK]
                EXPORT  PIN_INT6_IRQHandler       [WEAK]
                EXPORT  PIN_INT7_IRQHandler       [WEAK]
                EXPORT  RIT_IRQHandler            [WEAK]
                EXPORT  SCT0_IRQHandler           [WEAK]
                EXPORT  SCT1_IRQHandler           [WEAK]
                EXPORT  SCT2_IRQHandler           [WEAK]
                EXPORT  SCT3_IRQHandler           [WEAK]
                EXPORT  MRT_IRQHandler            [WEAK]
                EXPORT  UART0_IRQHandler          [WEAK]
                EXPORT  UART1_IRQHandler          [WEAK]
                EXPORT  UART2_IRQHandler          [WEAK]
                EXPORT  I2C0_IRQHandler           [WEAK]
                EXPORT  SPI0_IRQHandler           [WEAK]
                EXPORT  SPI1_IRQHandler           [WEAK]
                EXPORT  C_CAN0_IRQHandler         [WEAK]
                EXPORT  USB_IRQ_IRQHandler        [WEAK]
                EXPORT  USB_FIQ_IRQHandler        [WEAK]
                EXPORT  USBWAKEUP_IRQHandler      [WEAK]
                EXPORT  ADC0_SEQA_IRQHandler      [WEAK]
                EXPORT  ADC0_SEQB_IRQHandler      [WEAK]
                EXPORT  ADC0_THCMP_IRQHandler     [WEAK]
                EXPORT  ADC0_OVR_IRQHandler       [WEAK]
                EXPORT  ADC1_SEQA_IRQHandler      [WEAK]
                EXPORT  ADC1_SEQB_IRQHandler      [WEAK]
                EXPORT  ADC1_THCMP_IRQHandler     [WEAK]
                EXPORT  ADC1_OVR_IRQHandler       [WEAK]
                EXPORT  DAC_IRQHandler            [WEAK]
                EXPORT  CMP0_IRQHandler           [WEAK]
                EXPORT  CMP1_IRQHandler           [WEAK]
                EXPORT  CMP2_IRQHandler           [WEAK]
                EXPORT  CMP3_IRQHandler           [WEAK]
                EXPORT  QEI_IRQHandler            [WEAK]
                EXPORT  RTC_ALARM_IRQHandler      [WEAK]
                EXPORT  RTC_WAKE_IRQHandler       [WEAK]

WDT_IRQHandler
BOD_IRQHandler
FLASH_IRQHandler
EE_IRQHandler
DMA_IRQHandler
GINT0_IRQHandler
GINT1_IRQHandler
PIN_INT0_IRQHandler
PIN_INT1_IRQHandler
PIN_INT2_IRQHandler
PIN_INT3_IRQHandler
PIN_INT4_IRQHandler
PIN_INT5_IRQHandler
PIN_INT6_IRQHandler
PIN_INT7_IRQHandler
RIT_IRQHandler
SCT0_IRQHandler
SCT1_IRQHandler
SCT2_IRQHandler
SCT3_IRQHandler
MRT_IRQHandler
UART0_IRQHandler
UART1_IRQHandler
UART2_IRQHandler
I2C0_IRQHandler
SPI0_IRQHandler
SPI1_IRQHandler
C_CAN0_IRQHandler
USB_IRQ_IRQHandler
USB_FIQ_IRQHandler
USBWAKEUP_IRQHandler
ADC0_SEQA_IRQHandler
ADC0_SEQB_IRQHandler
ADC0_THCMP_IRQHandler
ADC0_OVR_IRQHandler
ADC1_SEQA_IRQHandler
ADC1_SEQB_IRQHandler
ADC1_THCMP_IRQHandler
ADC1_OVR_IRQHandler
DAC_IRQHandler
CMP0_IRQHandler
CMP1_IRQHandler
CMP2_IRQHandler
CMP3_IRQHandler
QEI_IRQHandler
RTC_ALARM_IRQHandler
RTC_WAKE_IRQHandler

                B       .

                ENDP


                ALIGN


; User Initial Stack & Heap

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                END
