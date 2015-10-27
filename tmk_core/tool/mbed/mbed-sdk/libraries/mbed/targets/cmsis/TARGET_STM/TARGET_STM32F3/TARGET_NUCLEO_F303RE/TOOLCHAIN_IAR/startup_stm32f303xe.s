;/******************** (C) COPYRIGHT 2014 STMicroelectronics ********************
;* File Name          : startup_stm32f303xe.s
;* Author             : MCD Application Team
;* Version            : V2.1.0
;* Date               : 12-Sept-2014
;* Description        : STM32F303RE/STM32F303VE/STM32F303ZE devices vector table 
;*                      for EWARM toolchain.
;*                      This module performs:
;*                      - Set the initial SP
;*                      - Set the initial PC == _iar_program_start,
;*                      - Set the vector table entries with the exceptions ISR
;*                        address.
;*                      - Branches to main in the C library (which eventually
;*                        calls main()).
;*                      After Reset the Cortex-M4 processor is in Thread mode,
;*                      priority is Privileged, and the Stack is set to Main.
;********************************************************************************
;*
;* <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
;*
;* Redistribution and use in source and binary forms, with or without modification,
;* are permitted provided that the following conditions are met:
;*   1. Redistributions of source code must retain the above copyright notice,
;*      this list of conditions and the following disclaimer.
;*   2. Redistributions in binary form must reproduce the above copyright notice,
;*      this list of conditions and the following disclaimer in the documentation
;*      and/or other materials provided with the distribution.
;*   3. Neither the name of STMicroelectronics nor the names of its contributors
;*      may be used to endorse or promote products derived from this software
;*      without specific prior written permission.
;*
;* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
;* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
;* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
;* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
;* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
;* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
;* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
;* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
;* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
;* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
;*
;*******************************************************************************
;
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

        DATA
__vector_table
        DCD     sfe(CSTACK)
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
        DCD     WWDG_IRQHandler                   ; 0: Window WatchDog
        DCD     PVD_IRQHandler                    ; 1: PVD through EXTI Line detection
        DCD     TAMP_STAMP_IRQHandler             ; 2: Tamper and TimeStamps through the EXTI line
        DCD     RTC_WKUP_IRQHandler               ; 3: RTC Wakeup through the EXTI line
        DCD     FLASH_IRQHandler                  ; 4: FLASH
        DCD     RCC_IRQHandler                    ; 5: RCC
        DCD     EXTI0_IRQHandler                  ; 6: EXTI Line0
        DCD     EXTI1_IRQHandler                  ; 7: EXTI Line1
        DCD     EXTI2_TSC_IRQHandler              ; 8: EXTI Line2 and Touch Sense controller
        DCD     EXTI3_IRQHandler                  ; 9: EXTI Line3
        DCD     EXTI4_IRQHandler                  ; 10: EXTI Line4
        DCD     DMA1_Channel1_IRQHandler          ; 11: DMA1 Channel 1
        DCD     DMA1_Channel2_IRQHandler          ; 12: DMA1 Channel 2
        DCD     DMA1_Channel3_IRQHandler          ; 13: DMA1 Channel 3
        DCD     DMA1_Channel4_IRQHandler          ; 14: DMA1 Channel 4
        DCD     DMA1_Channel5_IRQHandler          ; 15: DMA1 Channel 5
        DCD     DMA1_Channel6_IRQHandler          ; 16: DMA1 Channel 6
        DCD     DMA1_Channel7_IRQHandler          ; 17: DMA1 Channel 7
        DCD     ADC1_2_IRQHandler                 ; 18: ADC1 and ADC2
        DCD     USB_HP_CAN_TX_IRQHandler          ; 19: USB Device High Priority or CAN TX
        DCD     USB_LP_CAN_RX0_IRQHandler         ; 20: USB Device Low Priority or CAN RX0
        DCD     CAN_RX1_IRQHandler                ; 21: CAN RX1
        DCD     CAN_SCE_IRQHandler                ; 22: CAN SCE
        DCD     EXTI9_5_IRQHandler                ; 23: External Line[9:5]s
        DCD     TIM1_BRK_TIM15_IRQHandler         ; 24: TIM1 Break and TIM15
        DCD     TIM1_UP_TIM16_IRQHandler          ; 25: TIM1 Update and TIM16
        DCD     TIM1_TRG_COM_TIM17_IRQHandler     ; 26: TIM1 Trigger and Commutation and TIM17
        DCD     TIM1_CC_IRQHandler                ; 27: TIM1 Capture Compare
        DCD     TIM2_IRQHandler                   ; 28: TIM2
        DCD     TIM3_IRQHandler                   ; 29: TIM3
        DCD     TIM4_IRQHandler                   ; 30: TIM4
        DCD     I2C1_EV_IRQHandler                ; 31: I2C1 Event
        DCD     I2C1_ER_IRQHandler                ; 32: I2C1 Error
        DCD     I2C2_EV_IRQHandler                ; 33: I2C2 Event
        DCD     I2C2_ER_IRQHandler                ; 34: I2C2 Error
        DCD     SPI1_IRQHandler                   ; 35: SPI1
        DCD     SPI2_IRQHandler                   ; 36: SPI2
        DCD     USART1_IRQHandler                 ; 37: USART1
        DCD     USART2_IRQHandler                 ; 38: USART2
        DCD     USART3_IRQHandler                 ; 39: USART3
        DCD     EXTI15_10_IRQHandler              ; 40: External Line[15:10]s
        DCD     RTC_Alarm_IRQHandler              ; 41: RTC Alarm (A and B) through EXTI Line
        DCD     USBWakeUp_IRQHandler              ; 42: USB Wakeup through EXTI line
        DCD     TIM8_BRK_IRQHandler               ; 43: TIM8 Break
        DCD     TIM8_UP_IRQHandler                ; 44: TIM8 Update
        DCD     TIM8_TRG_COM_IRQHandler           ; 45: TIM8 Trigger and Commutation
        DCD     TIM8_CC_IRQHandler                ; 46: TIM8 Capture Compare
        DCD     ADC3_IRQHandler                   ; 47: ADC3
        DCD     FMC_IRQHandler                    ; 48: FMC
        DCD     0                                 ; 49: Reserved
        DCD     0                                 ; 50: Reserved
        DCD     SPI3_IRQHandler                   ; 51: SPI3
        DCD     UART4_IRQHandler                  ; 52: UART4
        DCD     UART5_IRQHandler                  ; 53: UART5
        DCD     TIM6_DAC_IRQHandler               ; 54: TIM6 and DAC1&2 underrun errors
        DCD     TIM7_IRQHandler                   ; 55: TIM7
        DCD     DMA2_Channel1_IRQHandler          ; 56: DMA2 Channel 1
        DCD     DMA2_Channel2_IRQHandler          ; 57: DMA2 Channel 2
        DCD     DMA2_Channel3_IRQHandler          ; 58: DMA2 Channel 3
        DCD     DMA2_Channel4_IRQHandler          ; 59: DMA2 Channel 4
        DCD     DMA2_Channel5_IRQHandler          ; 60: DMA2 Channel 5
        DCD     ADC4_IRQHandler                   ; 61: ADC4
        DCD     0                                 ; 62: Reserved
        DCD     0                                 ; 63: Reserved
        DCD     COMP1_2_3_IRQHandler              ; 64: COMP1, COMP2 and COMP3
        DCD     COMP4_5_6_IRQHandler              ; 65: COMP4, COMP5 and COMP6
        DCD     COMP7_IRQHandler                  ; 66: COMP7
        DCD     0                                 ; 67: Reserved
        DCD     0                                 ; 68: Reserved
        DCD     0                                 ; 69: Reserved
        DCD     0                                 ; 70: Reserved
        DCD     0                                 ; 71: Reserved
        DCD     I2C3_EV_IRQHandler                ; 72: I2C3 Event
        DCD     I2C3_ER_IRQHandler                ; 73: I2C3 Error
        DCD     USB_HP_IRQHandler                 ; 74: USB High Priority remap
        DCD     USB_LP_IRQHandler                 ; 75: USB Low Priority remap
        DCD     USBWakeUp_RMP_IRQHandler          ; 76: USB Wakeup remap through EXTI
        DCD     TIM20_BRK_IRQHandler              ; 77: TIM20 Break
        DCD     TIM20_UP_IRQHandler               ; 78: TIM20 Update
        DCD     TIM20_TRG_COM_IRQHandler          ; 79: TIM20 Trigger and Commutation
        DCD     TIM20_CC_IRQHandler               ; 80: TIM20 Capture Compare
        DCD     FPU_IRQHandler                    ; 81: FPU
        DCD     0                                 ; 82: Reserved
        DCD     0                                 ; 83: Reserved
        DCD     SPI4_IRQHandler                   ; 84: SPI4

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
        SECTION .text:CODE:NOROOT:REORDER(1)
NMI_Handler
        B NMI_Handler

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
HardFault_Handler
        B HardFault_Handler

        PUBWEAK MemManage_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
MemManage_Handler
        B MemManage_Handler

        PUBWEAK BusFault_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
BusFault_Handler
        B BusFault_Handler

        PUBWEAK UsageFault_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
UsageFault_Handler
        B UsageFault_Handler

        PUBWEAK SVC_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SVC_Handler
        B SVC_Handler

        PUBWEAK DebugMon_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
DebugMon_Handler
        B DebugMon_Handler

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
PendSV_Handler
        B PendSV_Handler

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SysTick_Handler
        B SysTick_Handler

        PUBWEAK WWDG_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
WWDG_IRQHandler
        B WWDG_IRQHandler

        PUBWEAK PVD_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
PVD_IRQHandler
        B PVD_IRQHandler

        PUBWEAK TAMP_STAMP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TAMP_STAMP_IRQHandler
        B TAMP_STAMP_IRQHandler

        PUBWEAK RTC_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RTC_WKUP_IRQHandler
        B RTC_WKUP_IRQHandler

        PUBWEAK FLASH_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FLASH_IRQHandler
        B FLASH_IRQHandler

        PUBWEAK RCC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RCC_IRQHandler
        B RCC_IRQHandler

        PUBWEAK EXTI0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI0_IRQHandler
        B EXTI0_IRQHandler

        PUBWEAK EXTI1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI1_IRQHandler
        B EXTI1_IRQHandler

        PUBWEAK EXTI2_TSC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI2_TSC_IRQHandler
        B EXTI2_TSC_IRQHandler

        PUBWEAK EXTI3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI3_IRQHandler
        B EXTI3_IRQHandler

        PUBWEAK EXTI4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI4_IRQHandler
        B EXTI4_IRQHandler

        PUBWEAK DMA1_Channel1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel1_IRQHandler
        B DMA1_Channel1_IRQHandler

        PUBWEAK DMA1_Channel2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel2_IRQHandler
        B DMA1_Channel2_IRQHandler

        PUBWEAK DMA1_Channel3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel3_IRQHandler
        B DMA1_Channel3_IRQHandler

        PUBWEAK DMA1_Channel4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel4_IRQHandler
        B DMA1_Channel4_IRQHandler

        PUBWEAK DMA1_Channel5_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel5_IRQHandler
        B DMA1_Channel5_IRQHandler

        PUBWEAK DMA1_Channel6_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel6_IRQHandler
        B DMA1_Channel6_IRQHandler

        PUBWEAK DMA1_Channel7_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel7_IRQHandler
        B DMA1_Channel7_IRQHandler

        PUBWEAK ADC1_2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ADC1_2_IRQHandler
        B ADC1_2_IRQHandler

        PUBWEAK USB_HP_CAN_TX_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USB_HP_CAN_TX_IRQHandler
        B USB_HP_CAN_TX_IRQHandler

        PUBWEAK USB_LP_CAN_RX0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USB_LP_CAN_RX0_IRQHandler
        B USB_LP_CAN_RX0_IRQHandler

        PUBWEAK CAN_RX1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN_RX1_IRQHandler
        B CAN_RX1_IRQHandler

        PUBWEAK CAN_SCE_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN_SCE_IRQHandler
        B CAN_SCE_IRQHandler

        PUBWEAK EXTI9_5_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI9_5_IRQHandler
        B EXTI9_5_IRQHandler

        PUBWEAK TIM1_BRK_TIM15_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM1_BRK_TIM15_IRQHandler
        B TIM1_BRK_TIM15_IRQHandler

        PUBWEAK TIM1_UP_TIM16_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM1_UP_TIM16_IRQHandler
        B TIM1_UP_TIM16_IRQHandler

        PUBWEAK TIM1_TRG_COM_TIM17_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM1_TRG_COM_TIM17_IRQHandler
        B TIM1_TRG_COM_TIM17_IRQHandler

        PUBWEAK TIM1_CC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM1_CC_IRQHandler
        B TIM1_CC_IRQHandler

        PUBWEAK TIM2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM2_IRQHandler
        B TIM2_IRQHandler

        PUBWEAK TIM3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM3_IRQHandler
        B TIM3_IRQHandler

        PUBWEAK TIM4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM4_IRQHandler
        B TIM4_IRQHandler

        PUBWEAK I2C1_EV_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C1_EV_IRQHandler
        B I2C1_EV_IRQHandler

        PUBWEAK I2C1_ER_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C1_ER_IRQHandler
        B I2C1_ER_IRQHandler

        PUBWEAK I2C2_EV_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C2_EV_IRQHandler
        B I2C2_EV_IRQHandler

        PUBWEAK I2C2_ER_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C2_ER_IRQHandler
        B I2C2_ER_IRQHandler

        PUBWEAK SPI1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI1_IRQHandler
        B SPI1_IRQHandler

        PUBWEAK SPI2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI2_IRQHandler
        B SPI2_IRQHandler

        PUBWEAK USART1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART1_IRQHandler
        B USART1_IRQHandler

        PUBWEAK USART2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART2_IRQHandler
        B USART2_IRQHandler

        PUBWEAK USART3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART3_IRQHandler
        B USART3_IRQHandler

        PUBWEAK EXTI15_10_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI15_10_IRQHandler
        B EXTI15_10_IRQHandler

        PUBWEAK RTC_Alarm_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RTC_Alarm_IRQHandler
        B RTC_Alarm_IRQHandler

        PUBWEAK USBWakeUp_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USBWakeUp_IRQHandler
        B USBWakeUp_IRQHandler

        PUBWEAK TIM8_BRK_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM8_BRK_IRQHandler
        B TIM8_BRK_IRQHandler

        PUBWEAK TIM8_UP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM8_UP_IRQHandler
        B TIM8_UP_IRQHandler

        PUBWEAK TIM8_TRG_COM_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM8_TRG_COM_IRQHandler
        B TIM8_TRG_COM_IRQHandler

        PUBWEAK TIM8_CC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM8_CC_IRQHandler
        B TIM8_CC_IRQHandler

        PUBWEAK ADC3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ADC3_IRQHandler
        B ADC3_IRQHandler
        
        PUBWEAK FMC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FMC_IRQHandler
        B FMC_IRQHandler        

        PUBWEAK SPI3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI3_IRQHandler
        B SPI3_IRQHandler

        PUBWEAK UART4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART4_IRQHandler
        B UART4_IRQHandler

        PUBWEAK UART5_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART5_IRQHandler
        B UART5_IRQHandler

        PUBWEAK TIM6_DAC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM6_DAC_IRQHandler
        B TIM6_DAC_IRQHandler

        PUBWEAK TIM7_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM7_IRQHandler
        B TIM7_IRQHandler

        PUBWEAK DMA2_Channel1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA2_Channel1_IRQHandler
        B DMA2_Channel1_IRQHandler

        PUBWEAK DMA2_Channel2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA2_Channel2_IRQHandler
        B DMA2_Channel2_IRQHandler

        PUBWEAK DMA2_Channel3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA2_Channel3_IRQHandler
        B DMA2_Channel3_IRQHandler

        PUBWEAK DMA2_Channel4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA2_Channel4_IRQHandler
        B DMA2_Channel4_IRQHandler

        PUBWEAK DMA2_Channel5_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA2_Channel5_IRQHandler
        B DMA2_Channel5_IRQHandler


        PUBWEAK ADC4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ADC4_IRQHandler
        B ADC4_IRQHandler

        PUBWEAK COMP1_2_3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
COMP1_2_3_IRQHandler
        B COMP1_2_3_IRQHandler

        PUBWEAK COMP4_5_6_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
COMP4_5_6_IRQHandler
        B COMP4_5_6_IRQHandler

        PUBWEAK COMP7_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
COMP7_IRQHandler
        B COMP7_IRQHandler

        PUBWEAK I2C3_EV_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C3_EV_IRQHandler
        B I2C3_EV_IRQHandler

        PUBWEAK I2C3_ER_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C3_ER_IRQHandler
        B I2C3_ER_IRQHandler

        PUBWEAK USB_HP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USB_HP_IRQHandler
        B USB_HP_IRQHandler

        PUBWEAK USB_LP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USB_LP_IRQHandler
        B USB_LP_IRQHandler

        PUBWEAK USBWakeUp_RMP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USBWakeUp_RMP_IRQHandler
        B USBWakeUp_RMP_IRQHandler

        PUBWEAK TIM20_BRK_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM20_BRK_IRQHandler
        B TIM20_BRK_IRQHandler

        PUBWEAK TIM20_UP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM20_UP_IRQHandler
        B TIM20_UP_IRQHandler

        PUBWEAK TIM20_TRG_COM_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM20_TRG_COM_IRQHandler
        B TIM20_TRG_COM_IRQHandler

        PUBWEAK TIM20_CC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM20_CC_IRQHandler
        B TIM20_CC_IRQHandler

        PUBWEAK FPU_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FPU_IRQHandler
        B FPU_IRQHandler

        PUBWEAK SPI4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI4_IRQHandler
        B SPI4_IRQHandler
        
        END
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
