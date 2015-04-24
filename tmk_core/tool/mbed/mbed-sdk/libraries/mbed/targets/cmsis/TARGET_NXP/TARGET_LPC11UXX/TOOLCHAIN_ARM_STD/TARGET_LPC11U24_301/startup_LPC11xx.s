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

__initial_sp        EQU     0x10001800  ; Top of RAM from LPC11U

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
				; for LPC11Uxx (With USB)
                DCD     FLEX_INT0_IRQHandler      ; All GPIO pin can be routed to FLEX_INTx
                DCD     FLEX_INT1_IRQHandler          
                DCD     FLEX_INT2_IRQHandler                       
                DCD     FLEX_INT3_IRQHandler                         
                DCD     FLEX_INT4_IRQHandler                        
                DCD     FLEX_INT5_IRQHandler
                DCD     FLEX_INT6_IRQHandler
                DCD     FLEX_INT7_IRQHandler                       
                DCD     GINT0_IRQHandler                         
                DCD     GINT1_IRQHandler          ; PIO0 (0:7)              
                DCD     Reserved_IRQHandler	      ; Reserved
                DCD     Reserved_IRQHandler
                DCD     Reserved_IRQHandler       
                DCD     Reserved_IRQHandler                       
                DCD     SSP1_IRQHandler           ; SSP1               
                DCD     I2C_IRQHandler            ; I2C
                DCD     TIMER16_0_IRQHandler      ; 16-bit Timer0
                DCD     TIMER16_1_IRQHandler      ; 16-bit Timer1
                DCD     TIMER32_0_IRQHandler      ; 32-bit Timer0
                DCD     TIMER32_1_IRQHandler      ; 32-bit Timer1
                DCD     SSP0_IRQHandler           ; SSP0
                DCD     UART_IRQHandler           ; UART
                DCD     USB_IRQHandler            ; USB IRQ
                DCD     USB_FIQHandler            ; USB FIQ
                DCD     ADC_IRQHandler            ; A/D Converter
                DCD     WDT_IRQHandler            ; Watchdog timer
                DCD     BOD_IRQHandler            ; Brown Out Detect
                DCD     FMC_IRQHandler            ; IP2111 Flash Memory Controller
                DCD     Reserved_IRQHandler	    ; Reserved
                DCD     Reserved_IRQHandler       ; Reserved
                DCD     USBWakeup_IRQHandler      ; USB wake up
                DCD     Reserved_IRQHandler       ; Reserved
	
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
;NMI_Handler     PROC
;                EXPORT  NMI_Handler               [WEAK]
;                B       .
;                ENDP
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
Reserved_IRQHandler PROC
                EXPORT  Reserved_IRQHandler       [WEAK]
                B       .
                ENDP

Default_Handler PROC
; for LPC11Uxx (With USB)
                EXPORT  NMI_Handler               [WEAK]
                EXPORT  FLEX_INT0_IRQHandler      [WEAK]
                EXPORT  FLEX_INT1_IRQHandler      [WEAK]
                EXPORT  FLEX_INT2_IRQHandler      [WEAK]
                EXPORT  FLEX_INT3_IRQHandler      [WEAK]
                EXPORT  FLEX_INT4_IRQHandler      [WEAK]
                EXPORT  FLEX_INT5_IRQHandler      [WEAK]
                EXPORT  FLEX_INT6_IRQHandler      [WEAK]
                EXPORT  FLEX_INT7_IRQHandler      [WEAK]
                EXPORT  GINT0_IRQHandler          [WEAK]
                EXPORT  GINT1_IRQHandler          [WEAK]
                EXPORT  SSP1_IRQHandler           [WEAK]
                EXPORT  I2C_IRQHandler            [WEAK]
                EXPORT  TIMER16_0_IRQHandler      [WEAK]
                EXPORT  TIMER16_1_IRQHandler      [WEAK]
                EXPORT  TIMER32_0_IRQHandler      [WEAK]
                EXPORT  TIMER32_1_IRQHandler      [WEAK]
                EXPORT  SSP0_IRQHandler           [WEAK]
                EXPORT  UART_IRQHandler           [WEAK]

                EXPORT  USB_IRQHandler            [WEAK]
                EXPORT  USB_FIQHandler            [WEAK]
                EXPORT  ADC_IRQHandler            [WEAK]
                EXPORT  WDT_IRQHandler            [WEAK]
                EXPORT  BOD_IRQHandler            [WEAK]
                EXPORT  FMC_IRQHandler            [WEAK]
                EXPORT	USBWakeup_IRQHandler      [WEAK]

NMI_Handler
FLEX_INT0_IRQHandler
FLEX_INT1_IRQHandler
FLEX_INT2_IRQHandler
FLEX_INT3_IRQHandler
FLEX_INT4_IRQHandler
FLEX_INT5_IRQHandler
FLEX_INT6_IRQHandler
FLEX_INT7_IRQHandler
GINT0_IRQHandler
GINT1_IRQHandler
SSP1_IRQHandler
I2C_IRQHandler
TIMER16_0_IRQHandler
TIMER16_1_IRQHandler
TIMER32_0_IRQHandler
TIMER32_1_IRQHandler
SSP0_IRQHandler
UART_IRQHandler
USB_IRQHandler
USB_FIQHandler
ADC_IRQHandler
WDT_IRQHandler
BOD_IRQHandler
FMC_IRQHandler
USBWakeup_IRQHandler

                B       .

                ENDP

                ALIGN
                END
