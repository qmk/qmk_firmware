;/*****************************************************************************
; * @file:    startup_LPC8xx.s
; * @purpose: CMSIS Cortex-M0+ Core Device Startup File
; *           for the NXP LPC8xx Device Series
; * @version: V1.0
; * @date:    16. Aug. 2012
; *------- <<< Use Configuration Wizard in Context Menu >>> ------------------
; *
; * Copyright (C) 2012 ARM Limited. All rights reserved.
; * ARM Limited (ARM) is supplying this software for use with Cortex-M0+
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


; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
                EXPORT  __initial_sp

__initial_sp            EQU     0x10002000


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

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

                ; External Interrupts
                DCD     SPI0_IRQHandler             ; SPI0 controller
                DCD     SPI1_IRQHandler             ; SPI1 controller
                DCD     0                           ; Reserved
                DCD     UART0_IRQHandler            ; UART0
                DCD     UART1_IRQHandler            ; UART1
                DCD     UART2_IRQHandler            ; UART2
                DCD     0                           ; Reserved
                DCD     I2C1_IRQHandler             ; I2C1 controller
                DCD     I2C0_IRQHandler             ; I2C0 controller
                DCD     SCT_IRQHandler              ; Smart Counter Timer
                DCD     MRT_IRQHandler              ; Multi-Rate Timer
                DCD     CMP_IRQHandler              ; Comparator
                DCD     WDT_IRQHandler              ; PIO1 (0:11)
                DCD     BOD_IRQHandler              ; Brown Out Detect
                DCD     Flash_IRQHandler            ; Flash interrupt
                DCD     WKT_IRQHandler              ; Wakeup timer
                DCD     ADC_SEQA_IRQHandler         ; ADC sequence A completion
                DCD     ADC_SEQB_IRQHandler         ; ADC sequence B completion
                DCD     ADC_THCMP_IRQHandler        ; ADC threshold compare
                DCD     ADC_OVR_IRQHandler          ; ADC overrun
                DCD     DMA__RQHandler              ; DMA interrupt
                DCD     I2C2_IRQHandler             ; I2C2 controller
                DCD     I2C3_IRQHandler             ; I2C3 controller
                DCD     0                           ; Reserved
                DCD     PININT0_IRQHandler          ; PIO INT0
                DCD     PININT1_IRQHandler          ; PIO INT1
                DCD     PININT2_IRQHandler          ; PIO INT2
                DCD     PININT3_IRQHandler          ; PIO INT3
                DCD     PININT4_IRQHandler          ; PIO INT4
                DCD     PININT5_IRQHandler          ; PIO INT5
                DCD     PININT6_IRQHandler          ; PIO INT6
                DCD     PININT7_IRQHandler          ; PIO INT7


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

Default_Handler PROC

                EXPORT  NMI_Handler               [WEAK]
                EXPORT  SPI0_IRQHandler           [WEAK]
                EXPORT  SPI1_IRQHandler           [WEAK]
                EXPORT  UART0_IRQHandler          [WEAK]
                EXPORT  UART1_IRQHandler          [WEAK]
                EXPORT  UART2_IRQHandler          [WEAK]
                EXPORT  I2C1_IRQHandler           [WEAK]
                EXPORT  I2C0_IRQHandler           [WEAK]
                EXPORT  SCT_IRQHandler            [WEAK]
                EXPORT  MRT_IRQHandler            [WEAK]
                EXPORT  CMP_IRQHandler            [WEAK]
                EXPORT  WDT_IRQHandler            [WEAK]
                EXPORT  BOD_IRQHandler            [WEAK]
                EXPORT  Flash_IRQHandler          [WEAK]
                EXPORT  WKT_IRQHandler            [WEAK]
                EXPORT  ADC_SEQA_IRQHandler       [WEAK]
                EXPORT  ADC_SEQB_IRQHandler       [WEAK]
                EXPORT  ADC_THCMP_IRQHandler      [WEAK]
                EXPORT  ADC_OVR_IRQHandler        [WEAK]
                EXPORT  DMA__RQHandler            [WEAK]
                EXPORT  I2C2_IRQHandler           [WEAK]
                EXPORT  I2C3_IRQHandler           [WEAK]
                EXPORT  PININT0_IRQHandler        [WEAK]
                EXPORT  PININT1_IRQHandler        [WEAK]
                EXPORT  PININT2_IRQHandler        [WEAK]
                EXPORT  PININT3_IRQHandler        [WEAK]
                EXPORT  PININT4_IRQHandler        [WEAK]
                EXPORT  PININT5_IRQHandler        [WEAK]
                EXPORT  PININT6_IRQHandler        [WEAK]
                EXPORT  PININT7_IRQHandler        [WEAK]

NMI_Handler
SPI0_IRQHandler
SPI1_IRQHandler
UART0_IRQHandler
UART1_IRQHandler
UART2_IRQHandler
I2C1_IRQHandler
I2C0_IRQHandler
SCT_IRQHandler
MRT_IRQHandler
CMP_IRQHandler
WDT_IRQHandler
BOD_IRQHandler
Flash_IRQHandler
WKT_IRQHandler
ADC_SEQA_IRQHandler
ADC_SEQB_IRQHandler
ADC_THCMP_IRQHandler
ADC_OVR_IRQHandler
DMA__RQHandler
I2C2_IRQHandler
I2C3_IRQHandler
PININT0_IRQHandler
PININT1_IRQHandler
PININT2_IRQHandler
PININT3_IRQHandler
PININT4_IRQHandler
PININT5_IRQHandler
PININT6_IRQHandler
PININT7_IRQHandler

                B       .

                ENDP

                ALIGN
                END
