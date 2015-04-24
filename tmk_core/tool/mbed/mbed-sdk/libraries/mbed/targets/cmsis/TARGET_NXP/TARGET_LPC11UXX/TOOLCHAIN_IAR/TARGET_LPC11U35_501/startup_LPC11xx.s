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
                DCD     MemManage_Handler         ; MPU Fault Handler
                DCD     BusFault_Handler          ; Bus Fault Handler
                DCD     UsageFault_Handler        ; Usage Fault Handler
__vector_table_0x1c
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
                DCD     Reserved_IRQHandler       ; Reserved
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
                DCD     Reserved_IRQHandler       ; Reserved
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
        PUBWEAK MemManage_Handler
        PUBWEAK BusFault_Handler
        PUBWEAK UsageFault_Handler
        PUBWEAK SVC_Handler
        PUBWEAK DebugMon_Handler
        PUBWEAK PendSV_Handler
        PUBWEAK SysTick_Handler
        PUBWEAK FLEX_INT0_IRQHandler
        PUBWEAK FLEX_INT1_IRQHandler
        PUBWEAK FLEX_INT2_IRQHandler
        PUBWEAK FLEX_INT3_IRQHandler
        PUBWEAK FLEX_INT4_IRQHandler
        PUBWEAK FLEX_INT5_IRQHandler
        PUBWEAK FLEX_INT6_IRQHandler
        PUBWEAK FLEX_INT7_IRQHandler
        PUBWEAK GINT0_IRQHandler
        PUBWEAK GINT1_IRQHandler
        PUBWEAK SSP1_IRQHandler
        PUBWEAK I2C_IRQHandler
        PUBWEAK TIMER16_0_IRQHandler
        PUBWEAK TIMER16_1_IRQHandler
        PUBWEAK TIMER32_0_IRQHandler
        PUBWEAK TIMER32_1_IRQHandler
        PUBWEAK SSP0_IRQHandler
        PUBWEAK UART_IRQHandler
        PUBWEAK USB_IRQHandler
        PUBWEAK USB_FIQHandler
        PUBWEAK ADC_IRQHandler
        PUBWEAK WDT_IRQHandler
        PUBWEAK BOD_IRQHandler
        PUBWEAK FMC_IRQHandler
        PUBWEAK USBWakeup_IRQHandler
        PUBWEAK Reserved_IRQHandler

      SECTION .text:CODE:REORDER:NOROOT(1)
      THUMB        
NMI_Handler:
        B .
HardFault_Handler:
        B .
MemManage_Handler:
        B .
BusFault_Handler:
        B .
UsageFault_Handler:
        B .
SVC_Handler:
        B .
DebugMon_Handler:
        B .
PendSV_Handler:
        B .
SysTick_Handler:
        B .
FLEX_INT0_IRQHandler:
        B .
FLEX_INT1_IRQHandler:
        B .
FLEX_INT2_IRQHandler:
        B .
FLEX_INT3_IRQHandler:
        B .
FLEX_INT4_IRQHandler:
        B .
FLEX_INT5_IRQHandler:
        B .
FLEX_INT6_IRQHandler:
        B .
FLEX_INT7_IRQHandler:
        B .
GINT0_IRQHandler:
        B .
GINT1_IRQHandler:
        B .
SSP1_IRQHandler:
        B .
I2C_IRQHandler:
        B .
TIMER16_0_IRQHandler:
        B .
TIMER16_1_IRQHandler:
        B .
TIMER32_0_IRQHandler:
        B .
TIMER32_1_IRQHandler:
        B .
SSP0_IRQHandler:
        B .
UART_IRQHandler:
        B .
USB_IRQHandler:
        B .
USB_FIQHandler:
        B .
ADC_IRQHandler:
        B .
WDT_IRQHandler:
        B .
BOD_IRQHandler:
        B .
FMC_IRQHandler:
        B .
USBWakeup_IRQHandler:
        B .
Reserved_IRQHandler:
        B .
Default_Handler:
        B .

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
