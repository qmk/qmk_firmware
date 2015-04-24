/**************************************************
 *
 * Part one of the system initialization code, contains low-level
 * initialization, plain thumb variant.
 *
 * Copyright 2011 IAR Systems. All rights reserved.
 *
 * $Revision: 47876 $
 *
 **************************************************/

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
        PUBLIC  __vector_table_0x1c
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
__vector_table_0x1c
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
        DCD     PININT1_IRQHandler         ; PIO INT1
        DCD     PININT2_IRQHandler         ; PIO INT2
        DCD     PININT3_IRQHandler         ; PIO INT3
        DCD     PININT4_IRQHandler         ; PIO INT4
        DCD     PININT5_IRQHandler         ; PIO INT5
        DCD     PININT6_IRQHandler         ; PIO INT6
        DCD     PININT7_IRQHandler         ; PIO INT7
__Vectors_End

__Vectors       EQU   __vector_table
__Vectors_Size 	EQU   __Vectors_End - __Vectors

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

        THUMB
        PUBWEAK Reset_Handler
        SECTION .text:CODE:NOROOT:REORDER(2)
Reset_Handler
        LDR     R0, =SystemInit
        BLX     R0
        LDR     R0, =__iar_program_start
        BX      R0
  
        PUBWEAK NMI_Handler
        PUBWEAK HardFault_Handler
        PUBWEAK SVC_Handler
        PUBWEAK PendSV_Handler
        PUBWEAK SysTick_Handler
        PUBWEAK SPI0_IRQHandler
        PUBWEAK SPI1_IRQHandler
        PUBWEAK UART0_IRQHandler
        PUBWEAK UART1_IRQHandler
        PUBWEAK UART2_IRQHandler
        PUBWEAK I2C1_IRQHandler
        PUBWEAK I2C0_IRQHandler
        PUBWEAK SCT_IRQHandler
        PUBWEAK MRT_IRQHandler
        PUBWEAK CMP_IRQHandler
        PUBWEAK WDT_IRQHandler
        PUBWEAK BOD_IRQHandler
        PUBWEAK Flash_IRQHandler
        PUBWEAK WKT_IRQHandler
        PUBWEAK ADC_SEQA_IRQHandler
        PUBWEAK ADC_SEQB_IRQHandler
        PUBWEAK ADC_THCMP_IRQHandler
        PUBWEAK ADC_OVR_IRQHandler
        PUBWEAK DMA__RQHandler
        PUBWEAK I2C2_IRQHandler
        PUBWEAK I2C3_IRQHandler
        PUBWEAK PININT0_IRQHandler
        PUBWEAK PININT1_IRQHandler
        PUBWEAK PININT2_IRQHandler
        PUBWEAK PININT3_IRQHandler
        PUBWEAK PININT4_IRQHandler
        PUBWEAK PININT5_IRQHandler
        PUBWEAK PININT6_IRQHandler
        PUBWEAK PININT7_IRQHandler
        
      SECTION .text:CODE:REORDER:NOROOT(1)
      THUMB
                
NMI_Handler
HardFault_Handler
SVC_Handler
PendSV_Handler
SysTick_Handler
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
Default_IRQHandler
        B Default_IRQHandler

        SECTION .crp:CODE:ROOT(2)
        DATA
/* Code Read Protection
NO_ISP  0x4E697370 -  Prevents sampling of pin PIO0_1 for entering ISP mode
CRP1    0x12345678 - Write to RAM command cannot access RAM below 0x10000300.
                   - Copy RAM to flash command can not write to Sector 0.
                   - Erase command can erase Sector 0 only when all sectors
                     are selected for erase.
                   - Compare command is disabled.
                   - Read Memory command is disabled.
CRP2    0x87654321 - Read Memory is disabled.
                   - Write to RAM is disabled.
                   - "Go" command is disabled.
                   - Copy RAM to flash is disabled.
                   - Compare is disabled.
CRP3    0x43218765 - Access to chip via the SWD pins is disabled. ISP entry
                     by pulling PIO0_1 LOW is disabled if a valid user code is
                     present in flash sector 0.
Caution: If CRP3 is selected, no future factory testing can be
performed on the device.
*/
	    DCD	0xFFFFFFFF

        END
