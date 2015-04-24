;; Copyright (c) 2009 Nordic Semiconductor. All Rights Reserved.
;; The information contained herein is confidential property of Nordic
;; Semiconductor ASA.Terms and conditions of usage are described in detail
;; in NORDIC SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
;; Licensees are granted free, non-transferable use of the information. NO
;; WARRANTY of ANY KIND is provided. This heading must NOT be removed from
;; the file.

;; Description message

        MODULE  ?cstartup

        ;; Stack size default : 1024
        ;; Heap size default : 2048

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  SystemInit
        PUBLIC  __vector_table
        PUBLIC  __Vectors
        PUBLIC  __Vectors_End
        PUBLIC  __Vectors_Size

        DATA

__vector_table
        DCD     sfe(CSTACK)
        DCD     Reset_Handler
        DCD     NMI_Handler
        DCD     HardFault_Handler
        DCD     0
        DCD     0
        DCD     0
;__vector_table_0x1c
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     SVC_Handler
        DCD     0
        DCD     0
        DCD     PendSV_Handler
        DCD     SysTick_Handler

        ; External Interrupts
        DCD      POWER_CLOCK_IRQHandler ;POWER_CLOCK
        DCD      RADIO_IRQHandler ;RADIO
        DCD      UART0_IRQHandler ;UART0
        DCD      SPI0_TWI0_IRQHandler ;SPI0_TWI0
        DCD      SPI1_TWI1_IRQHandler ;SPI1_TWI1
        DCD      0 ;Reserved
        DCD      GPIOTE_IRQHandler ;GPIOTE
        DCD      ADC_IRQHandler ;ADC
        DCD      TIMER0_IRQHandler ;TIMER0
        DCD      TIMER1_IRQHandler ;TIMER1
        DCD      TIMER2_IRQHandler ;TIMER2
        DCD      RTC0_IRQHandler ;RTC0
        DCD      TEMP_IRQHandler ;TEMP
        DCD      RNG_IRQHandler ;RNG
        DCD      ECB_IRQHandler ;ECB
        DCD      CCM_AAR_IRQHandler ;CCM_AAR
        DCD      WDT_IRQHandler ;WDT
        DCD      RTC1_IRQHandler ;RTC1
        DCD      QDEC_IRQHandler ;QDEC
        DCD      LPCOMP_COMP_IRQHandler ;LPCOMP_COMP
        DCD      SWI0_IRQHandler ;SWI0
        DCD      SWI1_IRQHandler ;SWI1
        DCD      SWI2_IRQHandler ;SWI2
        DCD      SWI3_IRQHandler ;SWI3
        DCD      SWI4_IRQHandler ;SWI4
        DCD      SWI5_IRQHandler ;SWI5
        DCD      0 ;Reserved
        DCD      0 ;Reserved
        DCD      0 ;Reserved
        DCD      0 ;Reserved
        DCD      0 ;Reserved
        DCD      0 ;Reserved


__Vectors_End
__Vectors                           EQU   __vector_table
__Vectors_Size                      EQU   __Vectors_End - __Vectors
NRF_POWER_RAMON_ADDRESS             EQU   0x40000524  ; NRF_POWER->RAMON address
NRF_POWER_RAMON_RAMxON_ONMODE_Msk   EQU   0xF         ; All RAM blocks on in onmode bit mask

; Default handlers.
        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reset_Handler
        LDR     R0, =NRF_POWER_RAMON_ADDRESS
        LDR     R2, [R0]
        MOVS    R1, #NRF_POWER_RAMON_RAMxON_ONMODE_Msk
        ORRS    R2, R2, R1
        STR     R2, [R0]
        LDR     R0, =SystemInit
        BLX     R0
        LDR     R0, =__iar_program_start
        BX      R0

        ; Dummy exception handlers

        PUBWEAK NMI_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
NMI_Handler
        B .

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
HardFault_Handler
        B .

        PUBWEAK SVC_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SVC_Handler
        B .

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
PendSV_Handler
        B .

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SysTick_Handler
        B .

       ; Dummy interrupt handlers

        PUBWEAK  POWER_CLOCK_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
POWER_CLOCK_IRQHandler
        B .
        PUBWEAK  RADIO_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
RADIO_IRQHandler
        B .
        PUBWEAK  UART0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
UART0_IRQHandler
        B .
        PUBWEAK  SPI0_TWI0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI0_TWI0_IRQHandler
        B .
        PUBWEAK  SPI1_TWI1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI1_TWI1_IRQHandler
        B .
        PUBWEAK  GPIOTE_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOTE_IRQHandler
        B .
        PUBWEAK  ADC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ADC_IRQHandler
        B .
        PUBWEAK  TIMER0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIMER0_IRQHandler
        B .
        PUBWEAK  TIMER1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIMER1_IRQHandler
        B .
        PUBWEAK  TIMER2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIMER2_IRQHandler
        B .
        PUBWEAK  RTC0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
RTC0_IRQHandler
        B .
        PUBWEAK  TEMP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TEMP_IRQHandler
        B .
        PUBWEAK  RNG_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
RNG_IRQHandler
        B .
        PUBWEAK  ECB_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ECB_IRQHandler
        B .
        PUBWEAK  CCM_AAR_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
CCM_AAR_IRQHandler
        B .
        PUBWEAK  WDT_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
WDT_IRQHandler
        B .
        PUBWEAK  RTC1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
RTC1_IRQHandler
        B .
        PUBWEAK  QDEC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
QDEC_IRQHandler
        B .
        PUBWEAK  LPCOMP_COMP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
LPCOMP_COMP_IRQHandler
        B .
        PUBWEAK  SWI0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SWI0_IRQHandler
        B .
        PUBWEAK  SWI1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SWI1_IRQHandler
        B .
        PUBWEAK  SWI2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SWI2_IRQHandler
        B .
        PUBWEAK  SWI3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SWI3_IRQHandler
        B .
        PUBWEAK  SWI4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SWI4_IRQHandler
        B .
        PUBWEAK  SWI5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SWI5_IRQHandler
        B .


        END