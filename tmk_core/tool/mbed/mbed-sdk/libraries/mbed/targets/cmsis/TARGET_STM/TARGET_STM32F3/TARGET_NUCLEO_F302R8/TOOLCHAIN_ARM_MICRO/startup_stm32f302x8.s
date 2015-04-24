;******************** (C) COPYRIGHT 2014 STMicroelectronics ********************
;* File Name          : startup_stm32f302x8.s
; STM32F302x8 Devices vector table for MDK ARM_MICRO toolchain
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Copyright (c) 2014, STMicroelectronics
; All rights reserved.
;
; Redistribution and use in source and binary forms, with or without
; modification, are permitted provided that the following conditions are met:
;
; 1. Redistributions of source code must retain the above copyright notice,
;     this list of conditions and the following disclaimer.
; 2. Redistributions in binary form must reproduce the above copyright notice,
;    this list of conditions and the following disclaimer in the documentation
;    and/or other materials provided with the distribution.
; 3. Neither the name of STMicroelectronics nor the names of its contributors
;    may be used to endorse or promote products derived from this software
;    without specific prior written permission.
;
; THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
; IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
; DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
; FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
; DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
; SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
; CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
; OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
; OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Amount of memory (in bytes) allocated for Stack
; Tailor this value to your application needs
; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
                EXPORT  __initial_sp
                
Stack_Mem       SPACE   Stack_Size
__initial_sp    EQU     0x20004000 ; Top of RAM


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000400

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
                EXPORT  __heap_base
                EXPORT  __heap_limit
                
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit    EQU (__initial_sp - Stack_Size)

                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp               ; Top of Stack
                DCD     Reset_Handler              ; Reset Handler
                DCD     NMI_Handler                ; NMI Handler
                DCD     HardFault_Handler          ; Hard Fault Handler
                DCD     MemManage_Handler          ; MPU Fault Handler
                DCD     BusFault_Handler           ; Bus Fault Handler
                DCD     UsageFault_Handler         ; Usage Fault Handler
                DCD     0                          ; Reserved
                DCD     0                          ; Reserved
                DCD     0                          ; Reserved
                DCD     0                          ; Reserved
                DCD     SVC_Handler                ; SVCall Handler
                DCD     DebugMon_Handler           ; Debug Monitor Handler
                DCD     0                          ; Reserved
                DCD     PendSV_Handler             ; PendSV Handler
                DCD     SysTick_Handler            ; SysTick Handler

                ; External Interrupts
                DCD     WWDG_IRQHandler                   ; Window WatchDog
                DCD     PVD_IRQHandler                    ; PVD through EXTI Line detection
                DCD     TAMP_STAMP_IRQHandler             ; Tamper and TimeStamps through the EXTI line
                DCD     RTC_WKUP_IRQHandler               ; RTC Wakeup through the EXTI line
                DCD     FLASH_IRQHandler                  ; FLASH
                DCD     RCC_IRQHandler                    ; RCC
                DCD     EXTI0_IRQHandler                  ; EXTI Line0
                DCD     EXTI1_IRQHandler                  ; EXTI Line1
                DCD     EXTI2_TSC_IRQHandler              ; EXTI Line2 and Touch Sense controller
                DCD     EXTI3_IRQHandler                  ; EXTI Line3
                DCD     EXTI4_IRQHandler                  ; EXTI Line4
                DCD     DMA1_Channel1_IRQHandler          ; DMA1 Channel 1
                DCD     DMA1_Channel2_IRQHandler          ; DMA1 Channel 2
                DCD     DMA1_Channel3_IRQHandler          ; DMA1 Channel 3
                DCD     DMA1_Channel4_IRQHandler          ; DMA1 Channel 4
                DCD     DMA1_Channel5_IRQHandler          ; DMA1 Channel 5
                DCD     DMA1_Channel6_IRQHandler          ; DMA1 Channel 6
                DCD     DMA1_Channel7_IRQHandler          ; DMA1 Channel 7
                DCD     ADC1_IRQHandler                   ; ADC1
                DCD     USB_HP_CAN_TX_IRQHandler          ; USB Device High Priority or CAN TX
                DCD     USB_LP_CAN_RX0_IRQHandler         ; USB Device Low Priority or CAN RX0
                DCD     CAN_RX1_IRQHandler                ; CAN RX1
                DCD     CAN_SCE_IRQHandler                ; CAN SCE
                DCD     EXTI9_5_IRQHandler                ; External Line[9:5]s
                DCD     TIM1_BRK_TIM15_IRQHandler         ; TIM1 Break and TIM15
                DCD     TIM1_UP_TIM16_IRQHandler          ; TIM1 Update and TIM16
                DCD     TIM1_TRG_COM_TIM17_IRQHandler     ; TIM1 Trigger and Commutation and TIM17
                DCD     TIM1_CC_IRQHandler                ; TIM1 Capture Compare
                DCD     TIM2_IRQHandler                   ; TIM2
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     I2C1_EV_IRQHandler                ; I2C1 Event
                DCD     I2C1_ER_IRQHandler                ; I2C1 Error
                DCD     I2C2_EV_IRQHandler                ; I2C2 Event
                DCD     I2C2_ER_IRQHandler                ; I2C2 Error
                DCD     0                                 ; Reserved
                DCD     SPI2_IRQHandler                   ; SPI2
                DCD     USART1_IRQHandler                 ; USART1
                DCD     USART2_IRQHandler                 ; USART2
                DCD     USART3_IRQHandler                 ; USART3
                DCD     EXTI15_10_IRQHandler              ; External Line[15:10]s
                DCD     RTC_Alarm_IRQHandler              ; RTC Alarm (A and B) through EXTI Line
                DCD     USBWakeUp_IRQHandler              ; USB Wakeup through EXTI line
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     SPI3_IRQHandler                   ; SPI3
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     TIM6_DAC_IRQHandler               ; TIM6 and DAC1&2 underrun errors
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     COMP2_IRQHandler                  ; COMP2
                DCD     COMP4_6_IRQHandler                ; COMP4 and COMP6
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     I2C3_EV_IRQHandler                ; I2C3 Event
                DCD     I2C3_ER_IRQHandler                ; I2C3 Error
                DCD     USB_HP_IRQHandler                 ; USB High Priority remap
                DCD     USB_LP_IRQHandler                 ; USB Low Priority remap
                DCD     USBWakeUp_RMP_IRQHandler          ; USB Wakeup remap through EXTI
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     FPU_IRQHandler                    ; FPU

__Vectors_End

__Vectors_Size  EQU  __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

; Reset handler
Reset_Handler    PROC
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
                EXPORT  NMI_Handler                [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler          [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler          [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler           [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler         [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler                [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler           [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler             [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler            [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  WWDG_IRQHandler                   [WEAK]
                EXPORT  PVD_IRQHandler                    [WEAK]
                EXPORT  TAMP_STAMP_IRQHandler             [WEAK]
                EXPORT  RTC_WKUP_IRQHandler               [WEAK]
                EXPORT  FLASH_IRQHandler                  [WEAK]
                EXPORT  RCC_IRQHandler                    [WEAK]
                EXPORT  EXTI0_IRQHandler                  [WEAK]
                EXPORT  EXTI1_IRQHandler                  [WEAK]
                EXPORT  EXTI2_TSC_IRQHandler              [WEAK]
                EXPORT  EXTI3_IRQHandler                  [WEAK]
                EXPORT  EXTI4_IRQHandler                  [WEAK]
                EXPORT  DMA1_Channel1_IRQHandler          [WEAK]
                EXPORT  DMA1_Channel2_IRQHandler          [WEAK]
                EXPORT  DMA1_Channel3_IRQHandler          [WEAK]
                EXPORT  DMA1_Channel4_IRQHandler          [WEAK]
                EXPORT  DMA1_Channel5_IRQHandler          [WEAK]
                EXPORT  DMA1_Channel6_IRQHandler          [WEAK]
                EXPORT  DMA1_Channel7_IRQHandler          [WEAK]
                EXPORT  ADC1_IRQHandler                   [WEAK]
                EXPORT  USB_HP_CAN_TX_IRQHandler          [WEAK]
                EXPORT  USB_LP_CAN_RX0_IRQHandler         [WEAK]
                EXPORT  CAN_RX1_IRQHandler                [WEAK]
                EXPORT  CAN_SCE_IRQHandler                [WEAK]
                EXPORT  EXTI9_5_IRQHandler                [WEAK]
                EXPORT  TIM1_BRK_TIM15_IRQHandler         [WEAK]
                EXPORT  TIM1_UP_TIM16_IRQHandler          [WEAK]
                EXPORT  TIM1_TRG_COM_TIM17_IRQHandler     [WEAK]
                EXPORT  TIM1_CC_IRQHandler                [WEAK]
                EXPORT  TIM2_IRQHandler                   [WEAK]
                EXPORT  I2C1_EV_IRQHandler                [WEAK]
                EXPORT  I2C1_ER_IRQHandler                [WEAK]
                EXPORT  I2C2_EV_IRQHandler                [WEAK]
                EXPORT  I2C2_ER_IRQHandler                [WEAK]
                EXPORT  SPI2_IRQHandler                   [WEAK]
                EXPORT  USART1_IRQHandler                 [WEAK]
                EXPORT  USART2_IRQHandler                 [WEAK]
                EXPORT  USART3_IRQHandler                 [WEAK]
                EXPORT  EXTI15_10_IRQHandler              [WEAK]
                EXPORT  RTC_Alarm_IRQHandler              [WEAK]
                EXPORT  USBWakeUp_IRQHandler              [WEAK]
                EXPORT  SPI3_IRQHandler                   [WEAK]
                EXPORT  TIM6_DAC_IRQHandler               [WEAK]
                EXPORT  COMP2_IRQHandler              [WEAK]
                EXPORT  COMP4_6_IRQHandler              [WEAK]
                EXPORT  I2C3_EV_IRQHandler                [WEAK]
                EXPORT  I2C3_ER_IRQHandler                [WEAK]
                EXPORT  USB_HP_IRQHandler                 [WEAK]
                EXPORT  USB_LP_IRQHandler                 [WEAK]
                EXPORT  USBWakeUp_RMP_IRQHandler              [WEAK]
                EXPORT  FPU_IRQHandler                    [WEAK]

WWDG_IRQHandler
PVD_IRQHandler
TAMP_STAMP_IRQHandler
RTC_WKUP_IRQHandler
FLASH_IRQHandler
RCC_IRQHandler
EXTI0_IRQHandler
EXTI1_IRQHandler
EXTI2_TSC_IRQHandler
EXTI3_IRQHandler
EXTI4_IRQHandler
DMA1_Channel1_IRQHandler
DMA1_Channel2_IRQHandler
DMA1_Channel3_IRQHandler
DMA1_Channel4_IRQHandler
DMA1_Channel5_IRQHandler
DMA1_Channel6_IRQHandler
DMA1_Channel7_IRQHandler
ADC1_IRQHandler
USB_HP_CAN_TX_IRQHandler
USB_LP_CAN_RX0_IRQHandler
CAN_RX1_IRQHandler
CAN_SCE_IRQHandler
EXTI9_5_IRQHandler
TIM1_BRK_TIM15_IRQHandler
TIM1_UP_TIM16_IRQHandler
TIM1_TRG_COM_TIM17_IRQHandler
TIM1_CC_IRQHandler
TIM2_IRQHandler
I2C1_EV_IRQHandler
I2C1_ER_IRQHandler
I2C2_EV_IRQHandler
I2C2_ER_IRQHandler
SPI2_IRQHandler
USART1_IRQHandler
USART2_IRQHandler
USART3_IRQHandler
EXTI15_10_IRQHandler
RTC_Alarm_IRQHandler
USBWakeUp_IRQHandler
SPI3_IRQHandler
TIM6_DAC_IRQHandler
COMP2_IRQHandler
COMP4_6_IRQHandler
I2C3_EV_IRQHandler
I2C3_ER_IRQHandler
USB_HP_IRQHandler
USB_LP_IRQHandler
USBWakeUp_RMP_IRQHandler
FPU_IRQHandler

                B       .

                ENDP

                ALIGN
                END
