/**************************************************
 *
 * Part one of the system initialization code, contains low-level
 * initialization, plain thumb variant.
 *
 * Copyright 2012 IAR Systems. All rights reserved.
 *
 * $Revision: 1106 $
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
        DCD     sfe(CSTACK)                 ; Top of Stack
        DCD     Reset_Handler         ; Reset Handler
        DCD     NMI_Handler                 ; NMI Handler
        DCD     HardFault_Handler           ; Hard Fault Handler
        DCD     MemManage_Handler           ; MPU Fault Handler
        DCD     BusFault_Handler            ; Bus Fault Handler
        DCD     UsageFault_Handler          ; Usage Fault Handler
__vector_table_0x1c
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     SVC_Handler                 ; SVCall Handler
        DCD     DebugMon_Handler            ; Debug Monitor Handler
        DCD     0                           ; Reserved
        DCD     PendSV_Handler              ; PendSV Handler
        DCD     SysTick_Handler             ; SysTick Handler
        DCD     FLEX_INT0_IRQHandler        ; GPIO pin interrupt 0       
        DCD     FLEX_INT1_IRQHandler        ; GPIO pin interrupt 1       
        DCD     FLEX_INT2_IRQHandler        ; GPIO pin interrupt 2       
        DCD     FLEX_INT3_IRQHandler        ; GPIO pin interrupt 3       
        DCD     FLEX_INT4_IRQHandler        ; GPIO pin interrupt 4       
        DCD     FLEX_INT5_IRQHandler        ; GPIO pin interrupt 5       
        DCD     FLEX_INT6_IRQHandler        ; GPIO pin interrupt 6       
        DCD     FLEX_INT7_IRQHandler        ; GPIO pin interrupt 7       
        DCD     GINT0_IRQHandler            ; GPIO GROUP0 interrupt      
        DCD     GINT1_IRQHandler            ; GPIO GROUP1 interrupt      
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     SSP1_IRQHandler             ; SSP1 interrupt             
        DCD     I2C_IRQHandler              ; I2C interrupt              
        DCD     CT16B0_IRQHandler           ; CT16B0 Match 0-3, Capture 0
        DCD     CT16B1_IRQHandler           ; CT16B1 Match 0-3, Capture 0
        DCD     CT32B0_IRQHandler           ; CT32B0 Match 0-3, Capture 0
        DCD     CT32B1_IRQHandler           ; CT32B1 Match 0-3, Capture 0
        DCD     SSP0_IRQHandler             ; SSP0 interrupt             
        DCD     USART_IRQHandler            ; USART interrupt            
        DCD     USB_IRQHandler              ; USB_IRQ interrupt          
        DCD     USB_FIQHandler              ; USB_FIQ interrupt          
        DCD     ADC_IRQHandler              ; ADC interrupt              
        DCD     WWDT_IRQHandler             ; WWDT interrupt             
        DCD     BOD_IRQHandler              ; BOD interrupt              
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     USBWakeup_IRQHandler        ; USB_WAKEUP interrupt       
        
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
      PUBWEAK CT16B0_IRQHandler   
      PUBWEAK CT16B1_IRQHandler   
      PUBWEAK CT32B0_IRQHandler   
      PUBWEAK CT32B1_IRQHandler   
      PUBWEAK SSP0_IRQHandler     
      PUBWEAK USART_IRQHandler    
      PUBWEAK USB_IRQHandler  
      PUBWEAK USB_FIQHandler  
      PUBWEAK ADC_IRQHandler      
      PUBWEAK WWDT_IRQHandler     
      PUBWEAK BOD_IRQHandler      
      PUBWEAK USBWakeup_IRQHandler    

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
FLEX_INT0_IRQHandler 
FLEX_INT1_IRQHandler 
FLEX_INT2_IRQHandler 
FLEX_INT3_IRQHandler 
FLEX_INT4_IRQHandler 
FLEX_INT5_IRQHandler 
FLEX_INT6_IRQHandler 
FLEX_INT7_IRQHandler 
GINT0_IRQHandler    
GINT1_IRQHandler    
SSP1_IRQHandler     
I2C_IRQHandler      
CT16B0_IRQHandler   
CT16B1_IRQHandler   
CT32B0_IRQHandler   
CT32B1_IRQHandler   
SSP0_IRQHandler     
USART_IRQHandler    
USB_IRQHandler  
USB_FIQHandler  
ADC_IRQHandler      
WWDT_IRQHandler     
BOD_IRQHandler      
USBWakeup_IRQHandler
Default_Handler          
        B Default_Handler 

        END
