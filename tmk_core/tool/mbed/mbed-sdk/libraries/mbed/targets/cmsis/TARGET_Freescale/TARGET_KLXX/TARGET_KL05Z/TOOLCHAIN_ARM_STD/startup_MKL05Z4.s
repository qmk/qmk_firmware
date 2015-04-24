;/*****************************************************************************
; * @file:    startup_MKL25Z4.s
; * @purpose: CMSIS Cortex-M0plus Core Device Startup File for the
; *           MKL05Z4
; * @version: 1.1
; * @date:    2012-6-21
; *
; * Copyright: 1997 - 2012 Freescale Semiconductor, Inc. All Rights Reserved.
;*
; *------- <<< Use Configuration Wizard in Context Menu >>> ------------------
; *
; *****************************************************************************/


__initial_sp        EQU     0x20000C00  ; Top of RAM

                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp  ; Top of Stack
                DCD     Reset_Handler  ; Reset Handler
                DCD     NMI_Handler  ; NMI Handler
                DCD     HardFault_Handler  ; Hard Fault Handler
                DCD     0  ; Reserved
                DCD     0  ; Reserved
                DCD     0  ; Reserved
                DCD     0  ; Reserved
                DCD     0  ; Reserved
                DCD     0  ; Reserved
                DCD     0  ; Reserved
                DCD     SVC_Handler  ; SVCall Handler
                DCD     0  ; Reserved
                DCD     0  ; Reserved
                DCD     PendSV_Handler  ; PendSV Handler
                DCD     SysTick_Handler  ; SysTick Handler

                ; External Interrupts
                DCD     DMA0_IRQHandler  ; DMA channel 0 transfer complete/error interrupt
                DCD     DMA1_IRQHandler  ; DMA channel 1 transfer complete/error interrupt
                DCD     DMA2_IRQHandler  ; DMA channel 2 transfer complete/error interrupt
                DCD     DMA3_IRQHandler  ; DMA channel 3 transfer complete/error interrupt
                DCD     Reserved20_IRQHandler  ; Reserved interrupt 20
                DCD     FTFA_IRQHandler  ; FTFA command complete/read collision interrupt
                DCD     LVD_LVW_IRQHandler  ; Low Voltage Detect, Low Voltage Warning
                DCD     LLW_IRQHandler  ; Low Leakage Wakeup
                DCD     I2C0_IRQHandler  ; I2C0 interrupt
                DCD     Reserved_25_IRQHandler  ; Reserved interrupt 25
                DCD     SPI0_IRQHandler  ; SPI0 interrupt
                DCD     Reserved_27_IRQHandler  ; Reserved interrupt 27
                DCD     UART0_IRQHandler  ; UART0 status and error interrupt
                DCD     Reserved_29_IRQHandler  ; Reserved interrupt 29
                DCD     Reserved_30_IRQHandler  ; Reserved interrupt 30
                DCD     ADC0_IRQHandler  ; ADC0 interrupt
                DCD     CMP0_IRQHandler  ; CMP0 interrupt
                DCD     TPM0_IRQHandler  ; TPM0 fault, overflow and channels interrupt
                DCD     TPM1_IRQHandler  ; TPM1 fault, overflow and channels interrupt
                DCD     Reserved_35_IRQHandler  ; Reserved interrupt 35
                DCD     RTC_IRQHandler  ; RTC interrupt
                DCD     RTC_Seconds_IRQHandler  ; RTC seconds interrupt
                DCD     PIT_IRQHandler  ; PIT timer channel 0 interrupt
                DCD     Reserved_39_IRQHandler  ; Reserved interrupt 39
                DCD     Reserved_40_IRQHandler  ; Reserved interrupt 40
                DCD     DAC0_IRQHandler  ; DAC0 interrupt
                DCD     TSI0_IRQHandler  ; TSI0 interrupt
                DCD     MCG_IRQHandler  ; MCG interrupt
                DCD     LPTimer_IRQHandler  ; LPTimer interrupt
                DCD     Reserved_45_IRQHandler  ; Reserved interrupt 45
                DCD     PORTA_IRQHandler  ; Port A interrupt
                DCD     PORTB_IRQHandler  ; Port B interrupt
__Vectors_End

__Vectors_Size 	EQU     __Vectors_End - __Vectors

; <h> Flash Configuration
;   <i> 16-byte flash configuration field that stores default protection settings (loaded on reset)
;   <i> and security information that allows the MCU to restrict acces to the FTFL module.
;   <h> Backdoor Comparison Key
;     <o0>  Backdoor Key 0  <0x0-0xFF:2>
;     <o1>  Backdoor Key 1  <0x0-0xFF:2>
;     <o2>  Backdoor Key 2  <0x0-0xFF:2>
;     <o3>  Backdoor Key 3  <0x0-0xFF:2>
;     <o4>  Backdoor Key 4  <0x0-0xFF:2>
;     <o5>  Backdoor Key 5  <0x0-0xFF:2>
;     <o6>  Backdoor Key 6  <0x0-0xFF:2>
;     <o7>  Backdoor Key 7  <0x0-0xFF:2>
BackDoorK0      EQU     0xFF
BackDoorK1      EQU     0xFF
BackDoorK2      EQU     0xFF
BackDoorK3      EQU     0xFF
BackDoorK4      EQU     0xFF
BackDoorK5      EQU     0xFF
BackDoorK6      EQU     0xFF
BackDoorK7      EQU     0xFF
;   </h>
;   <h> Program flash protection bytes (FPROT)
;     <i> Each program flash region can be protected from program and erase operation by setting the associated PROT bit.
;     <i> Each bit protects a 1/32 region of the program flash memory.
;     <h> FPROT0
;       <i> Program flash protection bytes
;       <i> 1/32 - 8/32 region
;       <o.0>   FPROT0.0
;       <o.1>   FPROT0.1
;       <o.2>   FPROT0.2
;       <o.3>   FPROT0.3
;       <o.4>   FPROT0.4
;       <o.5>   FPROT0.5
;       <o.6>   FPROT0.6
;       <o.7>   FPROT0.7
nFPROT0         EQU     0x00
FPROT0          EQU     nFPROT0:EOR:0xFF
;     </h>
;     <h> FPROT1
;       <i> Program Flash Region Protect Register 1
;       <i> 9/32 - 16/32 region
;       <o.0>   FPROT1.0
;       <o.1>   FPROT1.1
;       <o.2>   FPROT1.2
;       <o.3>   FPROT1.3
;       <o.4>   FPROT1.4
;       <o.5>   FPROT1.5
;       <o.6>   FPROT1.6
;       <o.7>   FPROT1.7
nFPROT1         EQU     0x00
FPROT1          EQU     nFPROT1:EOR:0xFF
;     </h>
;     <h> FPROT2
;       <i> Program Flash Region Protect Register 2
;       <i> 17/32 - 24/32 region
;       <o.0>   FPROT2.0
;       <o.1>   FPROT2.1
;       <o.2>   FPROT2.2
;       <o.3>   FPROT2.3
;       <o.4>   FPROT2.4
;       <o.5>   FPROT2.5
;       <o.6>   FPROT2.6
;       <o.7>   FPROT2.7
nFPROT2         EQU     0x00
FPROT2          EQU     nFPROT2:EOR:0xFF
;     </h>
;     <h> FPROT3
;       <i> Program Flash Region Protect Register 3
;       <i> 25/32 - 32/32 region
;       <o.0>   FPROT3.0
;       <o.1>   FPROT3.1
;       <o.2>   FPROT3.2
;       <o.3>   FPROT3.3
;       <o.4>   FPROT3.4
;       <o.5>   FPROT3.5
;       <o.6>   FPROT3.6
;       <o.7>   FPROT3.7
nFPROT3         EQU     0x00
FPROT3          EQU     nFPROT3:EOR:0xFF
;     </h>
;   </h>
;   </h>
;   <h> Flash nonvolatile option byte (FOPT)
;     <i> Allows the user to customize the operation of the MCU at boot time.
;     <o.0>  LPBOOT0
;       <0=> Core and system clock divider (OUTDIV1) is 0x7 (divide by 8) or 0x3 (divide by 4)
;       <1=> Core and system clock divider (OUTDIV1) is 0x1 (divide by 2) or 0x0 (divide by 1)
;     <o.4>  LPBOOT1
;       <0=> Core and system clock divider (OUTDIV1) is 0x7 (divide by 8) or 0x1 (divide by 2)
;       <1=> Core and system clock divider (OUTDIV1) is 0x3 (divide by 4) or 0x0 (divide by 1)
;     <o.2>  NMI_DIS
;       <0=> NMI interrupts are always blocked
;       <1=> NMI pin/interrupts reset default to enabled
;     <o.3>  RESET_PIN_CFG
;       <0=> RESET pin is disabled following a POR and cannot be enabled as RESET function
;       <1=> RESET pin is dedicated
;     <o.3>  FAST_INIT
;       <0=> Slower initialization
;       <1=> Fast Initialization
FOPT            EQU     0xFF
;   </h>
;   <h> Flash security byte (FSEC)
;     <i> WARNING: If SEC field is configured as "MCU security status is secure" and MEEN field is configured as "Mass erase is disabled",
;     <i> MCU's security status cannot be set back to unsecure state since Mass erase via the debugger is blocked !!!
;     <o.0..1> SEC
;       <2=> MCU security status is unsecure
;       <3=> MCU security status is secure
;         <i> Flash Security
;         <i> This bits define the security state of the MCU.
;     <o.2..3> FSLACC
;       <2=> Freescale factory access denied
;       <3=> Freescale factory access granted
;         <i> Freescale Failure Analysis Access Code
;         <i> This bits define the security state of the MCU.
;     <o.4..5> MEEN
;       <2=> Mass erase is disabled
;       <3=> Mass erase is enabled
;         <i> Mass Erase Enable Bits
;         <i> Enables and disables mass erase capability of the FTFL module
;     <o.6..7> KEYEN
;       <2=> Backdoor key access enabled
;       <3=> Backdoor key access disabled
;         <i> Backdoor key Security Enable
;         <i> These bits enable and disable backdoor key access to the FTFL module.
FSEC            EQU     0xFE
;   </h>

                IF      :LNOT::DEF:RAM_TARGET
                AREA    |.ARM.__at_0x400|, CODE, READONLY
                DCB     BackDoorK0, BackDoorK1, BackDoorK2, BackDoorK3
                DCB     BackDoorK4, BackDoorK5, BackDoorK6, BackDoorK7
                DCB     FPROT0,     FPROT1,     FPROT2,     FPROT3
                DCB     FSEC,       FOPT,       0xFF,     0xFF
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
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
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
                EXPORT  DMA0_IRQHandler     [WEAK]
                EXPORT  DMA1_IRQHandler     [WEAK]
                EXPORT  DMA2_IRQHandler     [WEAK]
                EXPORT  DMA3_IRQHandler     [WEAK]
                EXPORT  Reserved20_IRQHandler     [WEAK]
                EXPORT  FTFA_IRQHandler     [WEAK]
                EXPORT  LVD_LVW_IRQHandler     [WEAK]
                EXPORT  LLW_IRQHandler     [WEAK]
                EXPORT  I2C0_IRQHandler     [WEAK]
                EXPORT  Reserved_25_IRQHandler     [WEAK]
                EXPORT  SPI0_IRQHandler     [WEAK]
                EXPORT  Reserved_27_IRQHandler     [WEAK]
                EXPORT  UART0_IRQHandler     [WEAK]
                EXPORT  Reserved_29_IRQHandler     [WEAK]
                EXPORT  Reserved_30_IRQHandler     [WEAK]
                EXPORT  ADC0_IRQHandler     [WEAK]
                EXPORT  CMP0_IRQHandler     [WEAK]
                EXPORT  TPM0_IRQHandler     [WEAK]
                EXPORT  TPM1_IRQHandler     [WEAK]
                EXPORT  Reserved_35_IRQHandler     [WEAK]
                EXPORT  RTC_IRQHandler     [WEAK]
                EXPORT  RTC_Seconds_IRQHandler     [WEAK]
                EXPORT  PIT_IRQHandler     [WEAK]
                EXPORT  Reserved_39_IRQHandler     [WEAK]
                EXPORT  Reserved_40_IRQHandler     [WEAK]
                EXPORT  DAC0_IRQHandler     [WEAK]
                EXPORT  TSI0_IRQHandler     [WEAK]
                EXPORT  MCG_IRQHandler     [WEAK]
                EXPORT  LPTimer_IRQHandler     [WEAK]
                EXPORT  Reserved_45_IRQHandler     [WEAK]
                EXPORT  PORTA_IRQHandler     [WEAK]
                EXPORT  PORTB_IRQHandler     [WEAK]
                EXPORT  DefaultISR                      [WEAK]

DMA0_IRQHandler
DMA1_IRQHandler
DMA2_IRQHandler
DMA3_IRQHandler
Reserved20_IRQHandler
FTFA_IRQHandler
LVD_LVW_IRQHandler
LLW_IRQHandler
I2C0_IRQHandler
Reserved_25_IRQHandler
SPI0_IRQHandler
Reserved_27_IRQHandler
UART0_IRQHandler
Reserved_29_IRQHandler
Reserved_30_IRQHandler
ADC0_IRQHandler
CMP0_IRQHandler
TPM0_IRQHandler
TPM1_IRQHandler
Reserved_35_IRQHandler
RTC_IRQHandler
RTC_Seconds_IRQHandler
PIT_IRQHandler
Reserved_39_IRQHandler
Reserved_40_IRQHandler
DAC0_IRQHandler
TSI0_IRQHandler
MCG_IRQHandler
LPTimer_IRQHandler
Reserved_45_IRQHandler
PORTA_IRQHandler
PORTB_IRQHandler
DefaultISR

                B       .

                ENDP


                ALIGN
                END
