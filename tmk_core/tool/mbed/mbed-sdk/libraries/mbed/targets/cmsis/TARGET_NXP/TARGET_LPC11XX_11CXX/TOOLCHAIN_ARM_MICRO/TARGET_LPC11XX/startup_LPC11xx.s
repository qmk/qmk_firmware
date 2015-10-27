;/*****************************************************************************
; * @file:    startup_LPC11xx.s
; * @purpose: CMSIS Cortex-M0 Core Device Startup File 
; *           for the NXP LPC11xx Device Series 
; * @version: V1.0
; * @date:    25. Nov. 2008
; *------- <<< Use Configuration Wizard in Context Menu >>> ------------------
; *
; * Copyright (C) 2008 ARM Limited. All rights reserved.
; * ARM Limited (ARM) is supplying this software for use with Cortex-M0 
; * processor based microcontrollers.  This file can be freely distributed 
; * within development tools that are supporting such ARM based processors. 
; *
; * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
; * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
; * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
; * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
; *
; *****************************************************************************/

Stack_Size      EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
                EXPORT  __initial_sp

Stack_Mem       SPACE   Stack_Size
__initial_sp        EQU     0x10001000  ; Top of RAM from LPC1114


Heap_Size       EQU     0x00000000

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
                EXPORT  __heap_base
                EXPORT  __heap_limit

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

                DCD     SLWU_INT0_IRQHandler      ; Start logic wake-up interrupt 0
                DCD     SLWU_INT1_IRQHandler      ; Start logic wake-up interrupt 1
                DCD     SLWU_INT2_IRQHandler      ; Start logic wake-up interrupt 2
                DCD     SLWU_INT3_IRQHandler      ; Start logic wake-up interrupt 3
                DCD     SLWU_INT4_IRQHandler      ; Start logic wake-up interrupt 4
                DCD     SLWU_INT5_IRQHandler      ; Start logic wake-up interrupt 5
                DCD     SLWU_INT6_IRQHandler      ; Start logic wake-up interrupt 6
                DCD     SLWU_INT7_IRQHandler      ; Start logic wake-up interrupt 7
                DCD     SLWU_INT8_IRQHandler      ; Start logic wake-up interrupt 8
                DCD     SLWU_INT9_IRQHandler      ; Start logic wake-up interrupt 9
                DCD     SLWU_INT10_IRQHandler     ; Start logic wake-up interrupt 10
                DCD     SLWU_INT11_IRQHandler     ; Start logic wake-up interrupt 11
                DCD     SLWU_INT12_IRQHandler     ; Start logic wake-up interrupt 12
                DCD     C_CAN_IRQHandler          ; C_CAN
                DCD     SSP1_IRQHandler           ; SSP1
                DCD     I2C_IRQHandler            ; I2C
                DCD     TIMER16_0_IRQHandler      ; 16-bit Timer0
                DCD     TIMER16_1_IRQHandler      ; 16-bit Timer1
                DCD     TIMER32_0_IRQHandler      ; 32-bit Timer0
                DCD     TIMER32_1_IRQHandler      ; 32-bit Timer1
                DCD     SSP0_IRQHandler           ; SSP0
                DCD     UART_IRQHandler           ; UART
                DCD     Reserved_IRQHandler       ; Reserved
                DCD     Reserved_IRQHandler       ; Reserved
                DCD     ADC_IRQHandler            ; A/D Converter
                DCD     WDT_IRQHandler            ; Watchdog timer
                DCD     BOD_IRQHandler            ; Brown Out Detect
                DCD     Reserved_IRQHandler       ; Reserved
                DCD     PIO_3_IRQHandler	  ; GPIO interrupt status of port 3
                DCD     PIO_2_IRQHandler          ; GPIO interrupt status of port 2
                DCD     PIO_1_IRQHandler          ; GPIO interrupt status of port 1
                DCD     PIO_0_IRQHandler          ; GPIO interrupt status of port 0
	
	;; 48 vector entries. We pad to 128 to fill the 0x0 - 0x1FF REMAP address space

                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill

        	DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill

        	DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill

        	DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill

        	DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill

        	DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill

        	DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill

        	DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill
                DCD     0xFFFFFFFF                ; Datafill

                IF      :LNOT::DEF:NO_CRP
                AREA    |.ARM.__at_0x02FC|, CODE, READONLY
CRP_Key         DCD     0xFFFFFFFF
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

; now, under COMMON NMI.c and NMI.h, a real NMI handler is created if NMI is enabled 
; for particular peripheral.
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
; for LPC1114
                EXPORT  NMI_Handler               [WEAK]
                EXPORT  SLWU_INT0_IRQHandler      [WEAK]
                EXPORT  SLWU_INT1_IRQHandler      [WEAK]
                EXPORT  SLWU_INT2_IRQHandler      [WEAK]
                EXPORT  SLWU_INT3_IRQHandler      [WEAK]
                EXPORT  SLWU_INT4_IRQHandler      [WEAK]
                EXPORT  SLWU_INT5_IRQHandler      [WEAK]
                EXPORT  SLWU_INT6_IRQHandler      [WEAK]
                EXPORT  SLWU_INT7_IRQHandler      [WEAK]
                EXPORT  SLWU_INT8_IRQHandler      [WEAK]
                EXPORT  SLWU_INT9_IRQHandler      [WEAK]
                EXPORT  SLWU_INT10_IRQHandler     [WEAK]
                EXPORT  SLWU_INT11_IRQHandler     [WEAK]
                EXPORT  SLWU_INT12_IRQHandler     [WEAK]
                EXPORT  C_CAN_IRQHandler          [WEAK]
                EXPORT  SSP1_IRQHandler           [WEAK]
                EXPORT  I2C_IRQHandler            [WEAK]
                EXPORT  TIMER16_0_IRQHandler      [WEAK]
                EXPORT  TIMER16_1_IRQHandler      [WEAK]
                EXPORT  TIMER32_0_IRQHandler      [WEAK]
                EXPORT  TIMER32_1_IRQHandler      [WEAK]
                EXPORT  SSP0_IRQHandler           [WEAK]
                EXPORT  UART_IRQHandler           [WEAK]
                EXPORT  ADC_IRQHandler            [WEAK]
                EXPORT  WDT_IRQHandler            [WEAK]
                EXPORT  BOD_IRQHandler            [WEAK]
                EXPORT  PIO_3_IRQHandler          [WEAK]
                EXPORT  PIO_2_IRQHandler          [WEAK]
                EXPORT  PIO_1_IRQHandler          [WEAK]
                EXPORT  PIO_0_IRQHandler          [WEAK]

NMI_Handler

SLWU_INT0_IRQHandler
SLWU_INT1_IRQHandler
SLWU_INT2_IRQHandler
SLWU_INT3_IRQHandler
SLWU_INT4_IRQHandler
SLWU_INT5_IRQHandler
SLWU_INT6_IRQHandler
SLWU_INT7_IRQHandler
SLWU_INT8_IRQHandler
SLWU_INT9_IRQHandler
SLWU_INT10_IRQHandler
SLWU_INT11_IRQHandler
SLWU_INT12_IRQHandler
C_CAN_IRQHandler
SSP1_IRQHandler
I2C_IRQHandler
TIMER16_0_IRQHandler
TIMER16_1_IRQHandler
TIMER32_0_IRQHandler
TIMER32_1_IRQHandler
SSP0_IRQHandler
UART_IRQHandler
ADC_IRQHandler
WDT_IRQHandler
BOD_IRQHandler
PIO_3_IRQHandler
PIO_2_IRQHandler
PIO_1_IRQHandler
PIO_0_IRQHandler

                B       .

                ENDP

                ALIGN
                END
