;/***********************************************************************
; * @brief: LPC18xx/43xx M3/M4 startup code
; *
; * @note
; * Copyright(C) NXP Semiconductors, 2012
; * All rights reserved.
; *
; * @par
; * Software that is described herein is for illustrative purposes only
; * which provides customers with programming information regarding the
; * LPC products.  This software is supplied "AS IS" without any warranties of
; * any kind, and NXP Semiconductors and its licensor disclaim any and
; * all warranties, express or implied, including all implied warranties of
; * merchantability, fitness for a particular purpose and non-infringement of
; * intellectual property rights.  NXP Semiconductors assumes no responsibility
; * or liability for the use of the software, conveys no license or rights under any
; * patent, copyright, mask work right, or any other intellectual property rights in
; * or to any products. NXP Semiconductors reserves the right to make changes
; * in the software without notification. NXP Semiconductors also makes no
; * representation or warranty that such application will be suitable for the
; * specified use without further testing or modification.
; *
; * @par
; * Permission to use, copy, modify, and distribute this software and its
; * documentation is hereby granted, under NXP Semiconductors' and its
; * licensor's relevant copyrights in the software, without fee, provided that it
; * is used in conjunction with NXP Semiconductors microcontrollers.  This
; * copyright, permission, and disclaimer notice must appear in all copies of
; * this code.
; */

;__initial_sp    EQU     0x1008A000  ; Top of 2nd RAM segment for LPC4337
__initial_sp    EQU     0x10008000  ; Top of 1st RAM segment for LPC4337

                PRESERVE8
                THUMB

; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors

Sign_Value      EQU     0x5A5A5A5A

__Vectors   DCD __initial_sp                ; 0 Top of Stack
            DCD Reset_Handler               ; 1 Reset Handler
            DCD NMI_Handler                 ; 2 NMI Handler
            DCD HardFault_Handler           ; 3 Hard Fault Handler
            DCD MemManage_Handler           ; 4 MPU Fault Handler
            DCD BusFault_Handler            ; 5 Bus Fault Handler
            DCD UsageFault_Handler          ; 6 Usage Fault Handler
            DCD Sign_Value                  ; 7 Reserved
            DCD UnHandled_Vector            ; 8 Reserved
            DCD UnHandled_Vector            ; 9 Reserved
            DCD UnHandled_Vector            ; 10 Reserved
            DCD SVC_Handler                 ; 11 SVCall Handler
            DCD DebugMon_Handler            ; 12 Debug Monitor Handler
            DCD UnHandled_Vector            ; 13 Reserved
            DCD PendSV_Handler              ; 14 PendSV Handler
            DCD SysTick_Handler             ; 15 SysTick Handler

        ; External Interrupts
            DCD DAC_IRQHandler              ; 16 D/A Converter
            DCD MX_CORE_IRQHandler          ; 17 M0/M4 IRQ handler (LPC43XX ONLY)
            DCD DMA_IRQHandler              ; 18 General Purpose DMA
            DCD UnHandled_Vector            ; 19 Reserved
            DCD FLASHEEPROM_IRQHandler      ; 20 ORed flash bank A, flash bank B, EEPROM interrupts
            DCD ETH_IRQHandler              ; 21 Ethernet
            DCD SDIO_IRQHandler             ; 22 SD/MMC
            DCD LCD_IRQHandler              ; 23 LCD
            DCD USB0_IRQHandler             ; 24 USB0
            DCD USB1_IRQHandler             ; 25 USB1
            DCD SCT_IRQHandler              ; 26 State Configurable Timer
            DCD RIT_IRQHandler              ; 27 Repetitive Interrupt Timer
            DCD TIMER0_IRQHandler           ; 28 Timer0
            DCD TIMER1_IRQHandler           ; 29 Timer1
            DCD TIMER2_IRQHandler           ; 30 Timer2
            DCD TIMER3_IRQHandler           ; 31 Timer3
            DCD MCPWM_IRQHandler            ; 32 Motor Control PWM
            DCD ADC0_IRQHandler             ; 33 A/D Converter 0
            DCD I2C0_IRQHandler             ; 34 I2C0
            DCD I2C1_IRQHandler             ; 35 I2C1
            DCD SPI_IRQHandler              ; 36 SPI (LPC43XX ONLY)
            DCD ADC1_IRQHandler             ; 37 A/D Converter 1
            DCD SSP0_IRQHandler             ; 38 SSP0
            DCD SSP1_IRQHandler             ; 39 SSP1
            DCD UART0_IRQHandler            ; 40 UART0
            DCD UART1_IRQHandler            ; 41 UART1
            DCD UART2_IRQHandler            ; 42 UART2
            DCD UART3_IRQHandler            ; 43 UART3
            DCD I2S0_IRQHandler             ; 44 I2S0
            DCD I2S1_IRQHandler             ; 45 I2S1
            DCD SPIFI_IRQHandler            ; 46 SPI Flash Interface
            DCD SGPIO_IRQHandler            ; 47 SGPIO (LPC43XX ONLY)
            DCD GPIO0_IRQHandler            ; 48 GPIO0
            DCD GPIO1_IRQHandler            ; 49 GPIO1
            DCD GPIO2_IRQHandler            ; 50 GPIO2
            DCD GPIO3_IRQHandler            ; 51 GPIO3
            DCD GPIO4_IRQHandler            ; 52 GPIO4
            DCD GPIO5_IRQHandler            ; 53 GPIO5
            DCD GPIO6_IRQHandler            ; 54 GPIO6
            DCD GPIO7_IRQHandler            ; 55 GPIO7
            DCD GINT0_IRQHandler            ; 56 GINT0
            DCD GINT1_IRQHandler            ; 57 GINT1
            DCD EVRT_IRQHandler             ; 58 Event Router
            DCD CAN1_IRQHandler             ; 59 C_CAN1
            DCD UnHandled_Vector            ; 60 Reserved
            DCD VADC_IRQHandler             ; 61 VADC
            DCD ATIMER_IRQHandler           ; 62 ATIMER
            DCD RTC_IRQHandler              ; 63 RTC
            DCD UnHandled_Vector            ; 64 Reserved
            DCD WDT_IRQHandler              ; 65 WDT
            DCD UnHandled_Vector            ; 66 M0s
            DCD CAN0_IRQHandler             ; 67 C_CAN0
            DCD QEI_IRQHandler              ; 68 QEI

;                IF      :LNOT::DEF:NO_CRP
;                AREA    |.ARM.__at_0x02FC|, CODE, READONLY
;CRP_Key         DCD     0xFFFFFFFF
;                ENDIF

                AREA    |.text|, CODE, READONLY

; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler           [WEAK]
                IMPORT  __main
                IMPORT  SystemInit
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP

; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler             [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler       [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler       [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler        [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler      [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler             [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler        [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler          [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler         [WEAK]
                B       .
                ENDP
UnHandled_Vector    PROC
                EXPORT  UnHandled_Vector        [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT DAC_IRQHandler           [WEAK]
                EXPORT MX_CORE_IRQHandler       [WEAK]
                EXPORT DMA_IRQHandler           [WEAK]
                EXPORT FLASHEEPROM_IRQHandler   [WEAK]
                EXPORT ETH_IRQHandler           [WEAK]
                EXPORT SDIO_IRQHandler          [WEAK]
                EXPORT LCD_IRQHandler           [WEAK]
                EXPORT USB0_IRQHandler          [WEAK]
                EXPORT USB1_IRQHandler          [WEAK]
                EXPORT SCT_IRQHandler           [WEAK]
                EXPORT RIT_IRQHandler           [WEAK]
                EXPORT TIMER0_IRQHandler        [WEAK]
                EXPORT TIMER1_IRQHandler        [WEAK]
                EXPORT TIMER2_IRQHandler        [WEAK]
                EXPORT TIMER3_IRQHandler        [WEAK]
                EXPORT MCPWM_IRQHandler         [WEAK]
                EXPORT ADC0_IRQHandler          [WEAK]
                EXPORT I2C0_IRQHandler          [WEAK]
                EXPORT I2C1_IRQHandler          [WEAK]
                EXPORT SPI_IRQHandler           [WEAK]
                EXPORT ADC1_IRQHandler          [WEAK]
                EXPORT SSP0_IRQHandler          [WEAK]
                EXPORT SSP1_IRQHandler          [WEAK]
                EXPORT UART0_IRQHandler         [WEAK]
                EXPORT UART1_IRQHandler         [WEAK]
                EXPORT UART2_IRQHandler         [WEAK]
                EXPORT UART3_IRQHandler         [WEAK]
                EXPORT I2S0_IRQHandler          [WEAK]
                EXPORT I2S1_IRQHandler          [WEAK]
                EXPORT SPIFI_IRQHandler         [WEAK]
                EXPORT SGPIO_IRQHandler         [WEAK]
                EXPORT GPIO0_IRQHandler         [WEAK]
                EXPORT GPIO1_IRQHandler         [WEAK]
                EXPORT GPIO2_IRQHandler         [WEAK]
                EXPORT GPIO3_IRQHandler         [WEAK]
                EXPORT GPIO4_IRQHandler         [WEAK]
                EXPORT GPIO5_IRQHandler         [WEAK]
                EXPORT GPIO6_IRQHandler         [WEAK]
                EXPORT GPIO7_IRQHandler         [WEAK]
                EXPORT GINT0_IRQHandler         [WEAK]
                EXPORT GINT1_IRQHandler         [WEAK]
                EXPORT EVRT_IRQHandler          [WEAK]
                EXPORT CAN1_IRQHandler          [WEAK]
                EXPORT VADC_IRQHandler          [WEAK]
                EXPORT ATIMER_IRQHandler        [WEAK]
                EXPORT RTC_IRQHandler           [WEAK]
                EXPORT WDT_IRQHandler           [WEAK]
                EXPORT CAN0_IRQHandler          [WEAK]
                EXPORT QEI_IRQHandler           [WEAK]

DAC_IRQHandler
MX_CORE_IRQHandler
DMA_IRQHandler
FLASHEEPROM_IRQHandler
ETH_IRQHandler
SDIO_IRQHandler
LCD_IRQHandler
USB0_IRQHandler
USB1_IRQHandler
SCT_IRQHandler
RIT_IRQHandler
TIMER0_IRQHandler
TIMER1_IRQHandler
TIMER2_IRQHandler
TIMER3_IRQHandler
MCPWM_IRQHandler
ADC0_IRQHandler
I2C0_IRQHandler
I2C1_IRQHandler
SPI_IRQHandler
ADC1_IRQHandler
SSP0_IRQHandler
SSP1_IRQHandler
UART0_IRQHandler
UART1_IRQHandler
UART2_IRQHandler
UART3_IRQHandler
I2S0_IRQHandler
I2S1_IRQHandler
SPIFI_IRQHandler
SGPIO_IRQHandler
GPIO0_IRQHandler
GPIO1_IRQHandler
GPIO2_IRQHandler
GPIO3_IRQHandler
GPIO4_IRQHandler
GPIO5_IRQHandler
GPIO6_IRQHandler
GPIO7_IRQHandler
GINT0_IRQHandler
GINT1_IRQHandler
EVRT_IRQHandler
CAN1_IRQHandler
VADC_IRQHandler
ATIMER_IRQHandler
RTC_IRQHandler
WDT_IRQHandler
CAN0_IRQHandler
QEI_IRQHandler

                B       .

                ENDP
                
                ALIGN
                END
