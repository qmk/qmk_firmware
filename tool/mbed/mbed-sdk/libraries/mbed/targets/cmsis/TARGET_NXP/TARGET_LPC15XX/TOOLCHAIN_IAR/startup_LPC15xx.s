/**************************************************
 *
 * Part one of the system initialization code, contains low-level
 * initialization, plain thumb variant.
 *
 * Copyright 2009 IAR Systems. All rights reserved.
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
        PUBLIC  __Vectors
        PUBLIC  __Vectors_End
        PUBLIC  __Vectors_Size
        
        DATA
        
__vector_table
        DCD     sfe(CSTACK)                 ; Top of Stack
        DCD     Reset_Handler         ; Reset Handler
        DCD     NMI_Handler                 ; NMI Handler
        DCD     HardFault_Handler           ; Hard Fault Handler
        DCD     MemManage_Handler         ; MPU Fault Handler
        DCD     BusFault_Handler          ; Bus Fault Handler
        DCD     UsageFault_Handler        ; Usage Fault Handler
__vector_table_0x1c
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     SVC_Handler                 ; SVCall Handler
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     PendSV_Handler              ; PendSV Handler
        DCD     SysTick_Handler             ; SysTick Handler


; External Interrupts
        DCD     WDT_IRQHandler            ; Watchdog timer
        DCD     BOD_IRQHandler            ; Brown Out Detect
        DCD     FLASH_IRQHandler          ; NVMC Flash Controller
        DCD     EE_IRQHandler             ; NVMC EE Controller
        DCD     DMA_IRQHandler            ; DMA Controller
        DCD     GINT0_IRQHandler                         
        DCD     GINT1_IRQHandler          ; PIO0 (0:7)   
        DCD     PIN_INT0_IRQHandler       ; 16+ 7 Pin interrupt 0 or pattern match engine slice 0 interrupt
        DCD     PIN_INT1_IRQHandler       ; 16+ 8 Pin interrupt 1 or pattern match engine slice 1 interrupt
        DCD     PIN_INT2_IRQHandler       ; 16+ 9 Pin interrupt 2 or pattern match engine slice 2 interrupt
        DCD     PIN_INT3_IRQHandler       ; 16+10 Pin interrupt 3 or pattern match engine slice 3 interrupt
        DCD     PIN_INT4_IRQHandler       ; 16+11 Pin interrupt 4 or pattern match engine slice 4 interrupt
        DCD     PIN_INT5_IRQHandler       ; 16+12 Pin interrupt 5 or pattern match engine slice 5 interrupt
        DCD     PIN_INT6_IRQHandler       ; 16+13 Pin interrupt 6 or pattern match engine slice 6 interrupt
        DCD     PIN_INT7_IRQHandler       ; 16+14 Pin interrupt 7 or pattern match engine slice 7 interrupt
        DCD     RIT_IRQHandler            ; RIT Timer
        DCD     SCT0_IRQHandler           ; SCT Timer0
        DCD     SCT1_IRQHandler           ; SCT Timer1
        DCD     SCT2_IRQHandler           ; SCT Timer2
        DCD     SCT3_IRQHandler           ; SCT Timer3              
        DCD     MRT_IRQHandler            ; MRT timer
        DCD     UART0_IRQHandler          ; MIN UART0
        DCD     UART1_IRQHandler          ; MIN UART1
        DCD     UART2_IRQHandler          ; MIN UART2
        DCD     I2C0_IRQHandler            ; BI2C
        DCD     SPI0_IRQHandler           ; LSPI0 
        DCD     SPI1_IRQHandler           ; LSPI1 
        DCD     C_CAN0_IRQHandler            ; CAN 
        DCD     USB_IRQ_IRQHandler            ; USB IRQ
        DCD     USB_FIQ_IRQHandler            ; USB FIQ
        DCD     USBWakeup_IRQHandler      ; USB wake up
        DCD     ADC0_SEQA_IRQHandler      ; ADC0 SEQA
        DCD     ADC0_SEQB_IRQHandler      ; ADC0 SEQB
        DCD     ADC0_THCMP_IRQHandler     ; ADC0 THCMP
        DCD     ADC0_OVR_IRQHandler       ; ADC0 OVR
        DCD     ADC1_SEQA_IRQHandler      ; ADC1 SEQA
        DCD     ADC1_SEQB_IRQHandler      ; ADC1 SEQB
        DCD     ADC1_THCMP_IRQHandler     ; ADC1 THCMP
        DCD     ADC1_OVR_IRQHandler       ; ADC1 OVR
        DCD     DAC_IRQHandler            ; D/A Converter
        DCD     CMP0_IRQHandler          ; Comparator 0
        DCD     CMP1_IRQHandler          ; Comparator 1
        DCD     CMP2_IRQHandler          ; Comparator 2
        DCD     CMP3_IRQHandler          ; Comparator 3
        DCD     QEI_IRQHandler            ; QEI 
        DCD     RTC_ALARM_IRQHandler      ; RTC Alarm 
        DCD     RTC_WAKE_IRQHandler       ; RTC Wake
        
__Vectors_End

__Vectors       EQU   __vector_table
__Vectors_Size 	EQU 	__Vectors_End - __Vectors

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
        PUBWEAK  WDT_IRQHandler            
        PUBWEAK  BOD_IRQHandler            
        PUBWEAK  FLASH_IRQHandler          
        PUBWEAK  EE_IRQHandler             
        PUBWEAK  DMA_IRQHandler            
        PUBWEAK  GINT0_IRQHandler          
        PUBWEAK  GINT1_IRQHandler          
        PUBWEAK  PIN_INT0_IRQHandler       
        PUBWEAK  PIN_INT1_IRQHandler       
        PUBWEAK  PIN_INT2_IRQHandler       
        PUBWEAK  PIN_INT3_IRQHandler       
        PUBWEAK  PIN_INT4_IRQHandler       
        PUBWEAK  PIN_INT5_IRQHandler       
        PUBWEAK  PIN_INT6_IRQHandler      
        PUBWEAK  PIN_INT7_IRQHandler       
        PUBWEAK  RIT_IRQHandler            
        PUBWEAK  SCT0_IRQHandler           
        PUBWEAK  SCT1_IRQHandler           
        PUBWEAK  SCT2_IRQHandler           
        PUBWEAK  SCT3_IRQHandler           
        PUBWEAK  MRT_IRQHandler            
        PUBWEAK  UART0_IRQHandler          
        PUBWEAK  UART1_IRQHandler          
        PUBWEAK  UART2_IRQHandler          
        PUBWEAK  I2C0_IRQHandler            
        PUBWEAK  SPI0_IRQHandler           
        PUBWEAK  SPI1_IRQHandler           
        PUBWEAK  C_CAN0_IRQHandler            
        PUBWEAK  USB_IRQ_IRQHandler            
        PUBWEAK  USB_FIQ_IRQHandler            
        PUBWEAK  USBWakeup_IRQHandler      
        PUBWEAK  ADC0_SEQA_IRQHandler      
        PUBWEAK  ADC0_SEQB_IRQHandler      
        PUBWEAK  ADC0_THCMP_IRQHandler     
        PUBWEAK  ADC0_OVR_IRQHandler       
        PUBWEAK  ADC1_SEQA_IRQHandler      
        PUBWEAK  ADC1_SEQB_IRQHandler      
        PUBWEAK  ADC1_THCMP_IRQHandler     
        PUBWEAK  ADC1_OVR_IRQHandler       
        PUBWEAK  DAC_IRQHandler             
        PUBWEAK  CMP0_IRQHandler           
        PUBWEAK  CMP1_IRQHandler           
        PUBWEAK  CMP2_IRQHandler           
        PUBWEAK  CMP3_IRQHandler           
        PUBWEAK  QEI_IRQHandler             
        PUBWEAK  RTC_ALARM_IRQHandler       
        PUBWEAK  RTC_WAKE_IRQHandler        

      SECTION .text:CODE:REORDER:NOROOT(1)
      THUMB

NMI_Handler
HardFault_Handler
MemManage_Handler
BusFault_Handler
UsageFault_Handler
SVC_Handler
DebugMon_Handler
PendSV_Handler
SysTick_Handler
WDT_IRQHandler
BOD_IRQHandler
FLASH_IRQHandler
EE_IRQHandler
DMA_IRQHandler
GINT0_IRQHandler
GINT1_IRQHandler
PIN_INT0_IRQHandler
PIN_INT1_IRQHandler
PIN_INT2_IRQHandler
PIN_INT3_IRQHandler
PIN_INT4_IRQHandler
PIN_INT5_IRQHandler
PIN_INT6_IRQHandler
PIN_INT7_IRQHandler
RIT_IRQHandler
SCT0_IRQHandler
SCT1_IRQHandler
SCT2_IRQHandler
SCT3_IRQHandler
MRT_IRQHandler
UART0_IRQHandler
UART1_IRQHandler
UART2_IRQHandler
I2C0_IRQHandler
SPI0_IRQHandler
SPI1_IRQHandler
C_CAN0_IRQHandler
USB_IRQ_IRQHandler
USB_FIQ_IRQHandler
USBWakeup_IRQHandler
ADC0_SEQA_IRQHandler
ADC0_SEQB_IRQHandler
ADC0_THCMP_IRQHandler
ADC0_OVR_IRQHandler
ADC1_SEQA_IRQHandler
ADC1_SEQB_IRQHandler
ADC1_THCMP_IRQHandler
ADC1_OVR_IRQHandler
DAC_IRQHandler
CMP0_IRQHandler
CMP1_IRQHandler
CMP2_IRQHandler
CMP3_IRQHandler
QEI_IRQHandler
RTC_ALARM_IRQHandler
RTC_WAKE_IRQHandler         
Default_Handler
        B Default_Handler
        
        
        SECTION .crp:CODE:ROOT(2)
        DATA
/* Code Read Protection
CRP1    0x12345678 - Write to RAM command can not access RAM below 0x10000200.
                   - Read Memory command: disabled.
                   - Copy RAM to Flash command: cannot write to Sector 0.
                   - "Go" command: disabled.
                   - Erase sector(s) command: can erase any individual sector except 
                   	 sector 0 only, or can erase all sectors at once.
                   - Compare command: disabled
CRP2    0x87654321 - Write to RAM command: disabled.
                   - Copy RAM to Flash: disabled.
                   - Erase command: only allows erase of all sectors.
CRP3    0x43218765 - Access to chip via the SWD pins is disabled. ISP entry
                     by pulling PIO0_1 LOW is disabled if a valid user code is
                     present in flash sector 0.
Caution: If CRP3 is selected, no future factory testing can be
performed on the device.
*/
	DCD	0xFFFFFFFF


        END
