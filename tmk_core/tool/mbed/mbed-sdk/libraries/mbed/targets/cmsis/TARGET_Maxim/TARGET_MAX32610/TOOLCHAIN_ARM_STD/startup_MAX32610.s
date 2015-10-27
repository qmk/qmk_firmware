;*******************************************************************************
; Copyright (C) 2015 Maxim Integrated Products, Inc., All Rights Reserved.
;
; Permission is hereby granted, free of charge, to any person obtaining a
; copy of this software and associated documentation files (the "Software"),
; to deal in the Software without restriction, including without limitation
; the rights to use, copy, modify, merge, publish, distribute, sublicense,
; and/or sell copies of the Software, and to permit persons to whom the
; Software is furnished to do so, subject to the following conditions:
;
; The above copyright notice and this permission notice shall be included
; in all copies or substantial portions of the Software.
;
; THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
; OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
; MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
; IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
; OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
; ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
; OTHER DEALINGS IN THE SOFTWARE.
;
; Except as contained in this notice, the name of Maxim Integrated
; Products, Inc. shall not be used except as stated in the Maxim Integrated
; Products, Inc. Branding Policy.
;
; The mere transfer of this software does not imply any licenses
; of trade secrets, proprietary technology, copyrights, patents,
; trademarks, maskwork rights, or any other form of intellectual
; property whatsoever. Maxim Integrated Products, Inc. retains all
; ownership rights.
;*******************************************************************************

__initial_sp        EQU     0x20008000  ; Top of RAM

                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp              ; Top of Stack 
                DCD     Reset_Handler             ; Reset Handler 
                DCD     NMI_Handler               ; NMI Handler 
                DCD     HardFault_Handler         ; Hard Fault Handler 
                DCD     DefaultIRQ_Handler        ; MPU Fault Handler 
                DCD     DefaultIRQ_Handler        ; Bus Fault Handler 
                DCD     DefaultIRQ_Handler        ; Usage Fault Handler 
                DCD     0                         ; Reserved 
                DCD     0                         ; Reserved 
                DCD     0                         ; Reserved 
                DCD     0                         ; Reserved 
                DCD     DefaultIRQ_Handler        ; SVCall Handler 
                DCD     DebugMon_Handler          ; Debug Monitor Handler 
                DCD     0                         ; Reserved 
                DCD     DefaultIRQ_Handler        ; PendSV Handler 
                DCD     SysTick_IRQHandler        ; SysTick Handler 

                ; Maxim 32610 Externals interrupts 
                DCD     UART0_IRQHandler          ; 16: 1 UART0 
                DCD     UART1_IRQHandler          ; 17: 2 UART1 
                DCD     I2CM0_IRQHandler          ; 18: 3 I2C Master 0 
                DCD     I2CS_IRQHandler           ; 19: 4 I2C Slave 
                DCD     USB_IRQHandler            ; 20: 5 USB 
                DCD     PMU_IRQHandler            ; 21: 6 DMA 
                DCD     AFE_IRQHandler            ; 22: 7 AFE 
                DCD     MAA_IRQHandler            ; 23: 8 MAA 
                DCD     AES_IRQHandler            ; 24: 9 AES 
                DCD     SPI0_IRQHandler           ; 25:10 SPI0 
                DCD     SPI1_IRQHandler           ; 26:11 SPI1 
                DCD     SPI2_IRQHandler           ; 27:12 SPI2 
                DCD     TMR0_IRQHandler           ; 28:13 Timer32-0 
                DCD     TMR1_IRQHandler           ; 29:14 Timer32-1 
                DCD     TMR2_IRQHandler           ; 30:15 Timer32-1 
                DCD     TMR3_IRQHandler           ; 31:16 Timer32-2 
                DCD     RSVD0_IRQHandler          ; 32:17 RSVD 
                DCD     RSVD1_IRQHandler          ; 33:18 RSVD 
                DCD     DAC0_IRQHandler           ; 34:19 DAC0  (12-bit DAC)   
                DCD     DAC1_IRQHandler           ; 35:20 DAC1  (12-bit DAC)   
                DCD     DAC2_IRQHandler           ; 36:21 DAC2  (8-bit DAC) 
                DCD     DAC3_IRQHandler           ; 37:22 DAC3  (8-bit DAC) 
                DCD     ADC_IRQHandler            ; 38:23 ADC 
                DCD     FLC_IRQHandler            ; 39:24 Flash Controller 
                DCD     PWRMAN_IRQHandler         ; 40:25 PWRMAN 
                DCD     CLKMAN_IRQHandler         ; 41:26 CLKMAN 
                DCD     RTC0_IRQHandler           ; 42:27 RTC INT0 
                DCD     RTC1_IRQHandler           ; 43:28 RTC INT1 
                DCD     RTC2_IRQHandler           ; 44:29 RTC INT2 
                DCD     RTC3_IRQHandler           ; 45:30 RTC INT3 
                DCD     WDT0_IRQHandler           ; 46:31 WATCHDOG0 
                DCD     WDT0_P_IRQHandler         ; 47:32 WATCHDOG0 PRE-WINDOW 
                DCD     WDT1_IRQHandler           ; 48:33 WATCHDOG1 
                DCD     WDT1_P_IRQHandler         ; 49:34 WATCHDOG1 PRE-WINDOW 
                DCD     GPIO_P0_IRQHandler        ; 50:35 GPIO Port 0  
                DCD     GPIO_P1_IRQHandler        ; 51:36 GPIO Port 1  
                DCD     GPIO_P2_IRQHandler        ; 52:37 GPIO Port 2  
                DCD     GPIO_P3_IRQHandler        ; 53:38 GPIO Port 3  
                DCD     GPIO_P4_IRQHandler        ; 54:39 GPIO Port 4  
                DCD     GPIO_P5_IRQHandler        ; 55:40 GPIO Port 5  
                DCD     GPIO_P6_IRQHandler        ; 56:41 GPIO Port 6  
                DCD     GPIO_P7_IRQHandler        ; 57:42 GPIO Port 7  
                DCD     TMR16_0_IRQHandler        ; 58:43 Timer16-s0 
                DCD     TMR16_1_IRQHandler        ; 59:44 Timer16-s1 
                DCD     TMR16_2_IRQHandler        ; 60:45 Timer16-s2 
                DCD     TMR16_3_IRQHandler        ; 61:46 Timer16-s3 
                DCD     I2CM1_IRQHandler          ; 62:47 I2C Master 1 
__Vectors_End

__Vectors_Size  EQU  __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

Reset_Handler   PROC
                EXPORT Reset_Handler                    [WEAK]
                IMPORT SystemInit
                IMPORT __main
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP

; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler             PROC
                        EXPORT NMI_Handler                      [WEAK]     
                        B       NMI_Handler
                        ENDP

HardFault_Handler       PROC
                        EXPORT HardFault_Handler                [WEAK]             
                        B       HardFault_Handler
                        ENDP

DefaultIRQ_Handler      PROC
                        EXPORT DefaultIRQ_Handler               [WEAK]             
                        B       DefaultIRQ_Handler
                        ENDP

DebugMon_Handler        PROC
                        EXPORT DebugMon_Handler                 [WEAK]             
                        B       DebugMon_Handler
                        ENDP

SysTick_IRQHandler      PROC
                        EXPORT SysTick_IRQHandler               [WEAK]             
                        B       SysTick_IRQHandler
                        ENDP

Default_Handler PROC

        EXPORT UART0_IRQHandler                         [WEAK]                              
        EXPORT UART1_IRQHandler                         [WEAK]                              
        EXPORT I2CM0_IRQHandler                         [WEAK]                              
        EXPORT I2CS_IRQHandler                          [WEAK]                             
        EXPORT USB_IRQHandler                           [WEAK]             
        EXPORT PMU_IRQHandler                           [WEAK]             
        EXPORT AFE_IRQHandler                           [WEAK]                            
        EXPORT MAA_IRQHandler                           [WEAK]                            
        EXPORT AES_IRQHandler                           [WEAK]                            
        EXPORT SPI0_IRQHandler                          [WEAK]                             
        EXPORT SPI1_IRQHandler                          [WEAK]                             
        EXPORT SPI2_IRQHandler                          [WEAK]                             
        EXPORT TMR0_IRQHandler                          [WEAK]                             
        EXPORT TMR1_IRQHandler                          [WEAK]                             
        EXPORT TMR2_IRQHandler                          [WEAK]                             
        EXPORT TMR3_IRQHandler                          [WEAK]                             
        EXPORT RSVD0_IRQHandler                         [WEAK]                              
        EXPORT RSVD1_IRQHandler                         [WEAK]                              
        EXPORT DAC0_IRQHandler                          [WEAK]                             
        EXPORT DAC1_IRQHandler                          [WEAK]                             
        EXPORT DAC2_IRQHandler                          [WEAK]                             
        EXPORT DAC3_IRQHandler                          [WEAK]                             
        EXPORT ADC_IRQHandler                           [WEAK]             
        EXPORT FLC_IRQHandler                           [WEAK]             
        EXPORT PWRMAN_IRQHandler                        [WEAK]                               
        EXPORT CLKMAN_IRQHandler                        [WEAK]                               
        EXPORT RTC0_IRQHandler                          [WEAK]                             
        EXPORT RTC1_IRQHandler                          [WEAK]                             
        EXPORT RTC2_IRQHandler                          [WEAK]                             
        EXPORT RTC3_IRQHandler                          [WEAK]                             
        EXPORT WDT0_IRQHandler                          [WEAK]                             
        EXPORT WDT0_P_IRQHandler                        [WEAK]                               
        EXPORT WDT1_IRQHandler                          [WEAK]                             
        EXPORT WDT1_P_IRQHandler                        [WEAK]                               
        EXPORT GPIO_P0_IRQHandler                       [WEAK]                                
        EXPORT GPIO_P1_IRQHandler                       [WEAK]                                
        EXPORT GPIO_P2_IRQHandler                       [WEAK]                                
        EXPORT GPIO_P3_IRQHandler                       [WEAK]                                
        EXPORT GPIO_P4_IRQHandler                       [WEAK]                                
        EXPORT GPIO_P5_IRQHandler                       [WEAK]                                
        EXPORT GPIO_P6_IRQHandler                       [WEAK]                                
        EXPORT GPIO_P7_IRQHandler                       [WEAK]                                
        EXPORT TMR16_0_IRQHandler                       [WEAK]                                
        EXPORT TMR16_1_IRQHandler                       [WEAK]                                
        EXPORT TMR16_2_IRQHandler                       [WEAK]                                
        EXPORT TMR16_3_IRQHandler                       [WEAK]                                
        EXPORT I2CM1_IRQHandler                         [WEAK]               

UART0_IRQHandler
UART1_IRQHandler               
I2CM0_IRQHandler
I2CS_IRQHandler
USB_IRQHandler
PMU_IRQHandler
AFE_IRQHandler
MAA_IRQHandler
AES_IRQHandler
SPI0_IRQHandler
SPI1_IRQHandler
SPI2_IRQHandler
TMR0_IRQHandler
TMR1_IRQHandler
TMR2_IRQHandler
TMR3_IRQHandler
RSVD0_IRQHandler
RSVD1_IRQHandler
DAC0_IRQHandler
DAC1_IRQHandler
DAC2_IRQHandler
DAC3_IRQHandler
ADC_IRQHandler
FLC_IRQHandler
PWRMAN_IRQHandler
CLKMAN_IRQHandler
RTC0_IRQHandler
RTC1_IRQHandler
RTC2_IRQHandler
RTC3_IRQHandler
WDT0_IRQHandler
WDT0_P_IRQHandler
WDT1_IRQHandler
WDT1_P_IRQHandler
GPIO_P0_IRQHandler
GPIO_P1_IRQHandler
GPIO_P2_IRQHandler
GPIO_P3_IRQHandler
GPIO_P4_IRQHandler
GPIO_P5_IRQHandler
GPIO_P6_IRQHandler
GPIO_P7_IRQHandler
TMR16_0_IRQHandler
TMR16_1_IRQHandler
TMR16_2_IRQHandler
TMR16_3_IRQHandler
I2CM1_IRQHandler

        B .
        ENDP
        ALIGN
        END
