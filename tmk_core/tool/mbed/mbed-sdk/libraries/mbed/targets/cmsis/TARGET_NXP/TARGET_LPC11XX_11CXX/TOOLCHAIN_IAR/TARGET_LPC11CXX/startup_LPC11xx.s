/**************************************************
 *
 * Part one of the system initialization code, contains low-level
 * initialization, plain thumb variant.
 *
 * Copyright 2012 IAR Systems. All rights reserved.
 *
 * $Revision: 28 $
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
        DATA


__vector_table
                DCD     sfe(CSTACK)               ; Top of Stack
                DCD     Reset_Handler       ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
__vector_table_0x1c
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
                DCD     PIO_3_IRQHandler          ; GPIO interrupt status of port 3
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
        PUBWEAK HardFault_Handler
        PUBWEAK SVC_Handler
        PUBWEAK PendSV_Handler
        PUBWEAK SysTick_Handler
        PUBWEAK Reserved_IRQHandler           
        PUBWEAK SLWU_INT0_IRQHandler
        PUBWEAK SLWU_INT1_IRQHandler
        PUBWEAK SLWU_INT2_IRQHandler
        PUBWEAK SLWU_INT3_IRQHandler
        PUBWEAK SLWU_INT4_IRQHandler
        PUBWEAK SLWU_INT5_IRQHandler
        PUBWEAK SLWU_INT6_IRQHandler
        PUBWEAK SLWU_INT7_IRQHandler
        PUBWEAK SLWU_INT8_IRQHandler
        PUBWEAK SLWU_INT9_IRQHandler
        PUBWEAK SLWU_INT10_IRQHandler
        PUBWEAK SLWU_INT11_IRQHandler
        PUBWEAK SLWU_INT12_IRQHandler
        PUBWEAK C_CAN_IRQHandler
        PUBWEAK SSP1_IRQHandler
        PUBWEAK I2C_IRQHandler
        PUBWEAK TIMER16_0_IRQHandler
        PUBWEAK TIMER16_1_IRQHandler
        PUBWEAK TIMER32_0_IRQHandler
        PUBWEAK TIMER32_1_IRQHandler
        PUBWEAK SSP0_IRQHandler
        PUBWEAK UART_IRQHandler
        PUBWEAK ADC_IRQHandler
        PUBWEAK WDT_IRQHandler
        PUBWEAK BOD_IRQHandler
        PUBWEAK PIO_3_IRQHandler
        PUBWEAK PIO_2_IRQHandler
        PUBWEAK PIO_1_IRQHandler
        PUBWEAK PIO_0_IRQHandler

        SECTION .text:CODE:REORDER:NOROOT(1)
        THUMB
        
NMI_Handler
HardFault_Handler
SVC_Handler
PendSV_Handler
SysTick_Handler
Reserved_IRQHandler           
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
Default_Handler
        B Default_Handler

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
        DCD     0xFFFFFFFF

        END
