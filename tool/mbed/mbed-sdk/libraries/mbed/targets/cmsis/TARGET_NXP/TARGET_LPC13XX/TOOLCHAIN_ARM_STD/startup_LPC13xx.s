;/*****************************************************************************
; * @file:    startup_LPC13xx.s
; * @purpose: CMSIS Cortex-M3 Core Device Startup File 
; *           for the NXP LPC13xx Device Series 
; * @version: V1.02, modified for mbed
; * @date:    27. July 2009, modified 3rd Aug 2009
; *------- <<< Use Configuration Wizard in Context Menu >>> ------------------
; *
; * Copyright (C) 2009 ARM Limited. All rights reserved.
; * ARM Limited (ARM) is supplying this software for use with Cortex-M3 
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

__initial_sp        EQU     0x10002000  ; Top of RAM from LPC1347

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

                DCD    PIN_INT0_Handler      ; All GPIO pin can be routed to PIN_INTx
                DCD    PIN_INT1_Handler
                DCD    PIN_INT2_Handler
                DCD    PIN_INT3_Handler
                DCD    PIN_INT4_Handler
                DCD    PIN_INT5_Handler
                DCD    PIN_INT6_Handler
                DCD    PIN_INT7_Handler
                DCD    GINT0_Handler
                DCD    GINT1_Handler         ; PIO0 (0:7) 
                DCD    0
                DCD    0
                DCD    OSTIMER_Handler
                DCD    0
                DCD    SSP1_Handler          ; SSP1 
                DCD    I2C_Handler           ; I2C 
                DCD    CT16B0_Handler        ; 16-bit Timer0 
                DCD    CT16B1_Handler        ; 16-bit Timer1 
                DCD    CT32B0_Handler        ; 32-bit Timer0 
                DCD    CT32B1_Handler        ; 32-bit Timer1 
                DCD    SSP0_Handler          ; SSP0 
                DCD    USART_Handler         ; USART 
                DCD    USB_Handler           ; USB IRQ 
                DCD    USB_FIQHandler        ; USB FIQ 
                DCD    ADC_Handler           ; A/D Converter 
                DCD    WDT_Handler           ; Watchdog timer 
                DCD    BOD_Handler           ; Brown Out Detect 
                DCD    FMC_Handler           ; IP2111 Flash Memory Controller 
                DCD    OSCFAIL_Handler       ; OSC FAIL 
                DCD    PVTCIRCUIT_Handler    ; PVT CIRCUIT 
                DCD    USBWakeup_Handler     ; USB wake up 
                DCD    0

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

                EXPORT  PIN_INT0_Handler          [WEAK]
                EXPORT  PIN_INT1_Handler          [WEAK]
                EXPORT  PIN_INT2_Handler          [WEAK]
                EXPORT  PIN_INT3_Handler          [WEAK]
                EXPORT  PIN_INT4_Handler          [WEAK]
                EXPORT  PIN_INT5_Handler          [WEAK]
                EXPORT  PIN_INT6_Handler          [WEAK]
                EXPORT  PIN_INT7_Handler          [WEAK]
                EXPORT  GINT0_Handler             [WEAK]
                EXPORT  GINT1_Handler             [WEAK]
                EXPORT  OSTIMER_Handler           [WEAK]
                EXPORT  SSP1_Handler              [WEAK]
                EXPORT  I2C_Handler               [WEAK]
                EXPORT  CT16B0_Handler            [WEAK]
                EXPORT  CT16B1_Handler            [WEAK]
                EXPORT  CT32B0_Handler            [WEAK]
                EXPORT  CT32B1_Handler            [WEAK]
                EXPORT  SSP0_Handler              [WEAK]
                EXPORT  USART_Handler             [WEAK]
                EXPORT  USB_Handler               [WEAK]
                EXPORT  USB_FIQHandler            [WEAK]
                EXPORT  ADC_Handler               [WEAK]
                EXPORT  WDT_Handler               [WEAK]
                EXPORT  BOD_Handler               [WEAK]
                EXPORT  FMC_Handler               [WEAK]
                EXPORT  OSCFAIL_Handler           [WEAK]
                EXPORT  PVTCIRCUIT_Handler        [WEAK]
                EXPORT  USBWakeup_Handler         [WEAK]
  
PIN_INT0_Handler
PIN_INT1_Handler
PIN_INT2_Handler
PIN_INT3_Handler
PIN_INT4_Handler
PIN_INT5_Handler
PIN_INT6_Handler
PIN_INT7_Handler
GINT0_Handler
GINT1_Handler
OSTIMER_Handler
SSP1_Handler
I2C_Handler
CT16B0_Handler
CT16B1_Handler
CT32B0_Handler
CT32B1_Handler
SSP0_Handler
USART_Handler
USB_Handler
USB_FIQHandler
ADC_Handler
WDT_Handler
BOD_Handler
FMC_Handler
OSCFAIL_Handler
PVTCIRCUIT_Handler
USBWakeup_Handler

                B       .

                ENDP
                
                ALIGN
                END
