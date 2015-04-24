;/*****************************************************************************
; * @file:    startup_MK20DX256.s
; * @purpose: CMSIS Cortex-M4 Core Device Startup File for the
; *           MK20DX256
; * @version: 1.0
; * @date:    2011-12-15
; *
; * Copyright: 1997 - 2015 Freescale Semiconductor, Inc. All Rights Reserved.
;*
; *------- <<< Use Configuration Wizard in Context Menu >>> ------------------
; *
; *****************************************************************************/


__initial_sp        EQU     0x20008000  ; Top of RAM

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
                DCD     MemManage_Handler  ; MPU Fault Handler
                DCD     BusFault_Handler  ; Bus Fault Handler
                DCD     UsageFault_Handler  ; Usage Fault Handler
                DCD     0  ; Reserved
                DCD     0  ; Reserved
                DCD     0  ; Reserved
                DCD     0  ; Reserved
                DCD     SVC_Handler  ; SVCall Handler
                DCD     DebugMon_Handler  ; Debug Monitor Handler
                DCD     0  ; Reserved
                DCD     PendSV_Handler  ; PendSV Handler
                DCD     SysTick_Handler  ; SysTick Handler

                ; External Interrupts                 
                DCD     DMA0_IRQHandler  ; DMA channel 0 transfer complete interrupt
                DCD     DMA1_IRQHandler  ; DMA channel 1 transfer complete interrupt
                DCD     DMA2_IRQHandler  ; DMA channel 2 transfer complete interrupt
                DCD     DMA3_IRQHandler  ; DMA channel 3 transfer complete interrupt
                DCD     DMA4_IRQHandler  ; DMA channel 4 transfer complete interrupt                      
				DCD     DMA5_IRQHandler  ; DMA channel 5 transfer complete interrupt
				DCD     DMA6_IRQHandler  ; DMA channel 6 transfer complete interrupt
				DCD     DMA7_IRQHandler  ; DMA channel 7 transfer complete interrupt
				DCD     DMA8_IRQHandler  ; DMA channel 8 transfer complete interrupt
				DCD     DMA9_IRQHandler  ; DMA channel 9 transfer complete interrupt
				DCD     DMA10_IRQHandler ; DMA channel 10 transfer complete interrupt
				DCD     DMA11_IRQHandler ; DMA channel 11 transfer complete interrupt
				DCD     DMA12_IRQHandler ; DMA channel 12 transfer complete interrupt
				DCD     DMA13_IRQHandler ; DMA channel 13 transfer complete interrupt
				DCD     DMA14_IRQHandler ; DMA channel 14 transfer complete interrupt
				DCD     DMA15_IRQHandler ; DMA channel 15 transfer complete interrupt
                DCD     DMA_Error_IRQHandler  ; DMA error interrupt
                DCD     Reserved33_IRQHandler  ; Reserved interrupt 33
                DCD     FTFL_IRQHandler  ; FTFL interrupt
                DCD     Read_Collision_IRQHandler  ; Read collision interrupt
                DCD     LVD_LVW_IRQHandler  ; Low Voltage Detect, Low Voltage Warning
                DCD     LLW_IRQHandler  ; Low Leakage Wakeup
                DCD     Watchdog_IRQHandler  ; WDOG interrupt                
                DCD     Reserved39_IRQHandler  ; Reserved interrupt 39			
                DCD     I2C0_IRQHandler  ; I2C0 interrupt
                DCD     I2C1_IRQHandler  ; I2C1 interrupt
                DCD     SPI0_IRQHandler  ; SPI0 interrupt
                DCD     SPI1_IRQHandler  ; SPI1 interrupt
                DCD     Reserved44_IRQHandler ; Reserved interrupt 44
                DCD     CAN0_ORed_Message_buffer_IRQHandler  ; CAN0 OR'd message buffers interrupt
                DCD     CAN0_Bus_Off_IRQHandler  ; CAN0 bus off interrupt
                DCD     CAN0_Error_IRQHandler  ; CAN0 error interrupt
                DCD     CAN0_Tx_Warning_IRQHandler  ; CAN0 Tx warning interrupt
                DCD     CAN0_Rx_Warning_IRQHandler  ; CAN0 Rx warning interrupt
                DCD     CAN0_Wake_Up_IRQHandler  ; CAN0 wake up interrupt                
                DCD     I2S0_Tx_IRQHandler  ; I2S0 transmit interrupt
                DCD     I2S0_Rx_IRQHandler  ; I2S0 receive interrupt                
                DCD     Reserved53_IRQHandler ; Reserved interrupt 53 
				DCD     Reserved54_IRQHandler ; Reserved interrupt 54
				DCD     Reserved55_IRQHandler ; Reserved interrupt 55
				DCD     Reserved56_IRQHandler ; Reserved interrupt 56
				DCD     Reserved57_IRQHandler ; Reserved interrupt 57
				DCD     Reserved58_IRQHandler ; Reserved interrupt 58
				DCD     Reserved59_IRQHandler ; Reserved interrupt 59                
                DCD     UART0_LON_IRQHandler  ; UART0 LON interrupt
                DCD     UART0_RX_TX_IRQHandler  ; UART0 receive/transmit interrupt
                DCD     UART0_ERR_IRQHandler  ; UART0 error interrupt
                DCD     UART1_RX_TX_IRQHandler  ; UART1 receive/transmit interrupt
                DCD     UART1_ERR_IRQHandler  ; UART1 error interrupt
                DCD     UART2_RX_TX_IRQHandler  ; UART2 receive/transmit interrupt
                DCD     UART2_ERR_IRQHandler  ; UART2 error interrupt                
                DCD     Reserved67_IRQHandler ; Reserved interrupt 67  
				DCD     Reserved68_IRQHandler ; Reserved interrupt 68  
				DCD     Reserved69_IRQHandler ; Reserved interrupt 69  
				DCD     Reserved70_IRQHandler ; Reserved interrupt 70  
				DCD     Reserved71_IRQHandler ; Reserved interrupt 71  
				DCD     Reserved72_IRQHandler ; Reserved interrupt 72 
                DCD     ADC0_IRQHandler  ; ADC0 interrupt
                DCD     ADC1_IRQHandler  ; ADC1 interrupt
                DCD     CMP0_IRQHandler  ; CMP0 interrupt
                DCD     CMP1_IRQHandler  ; CMP1 interrupt
                DCD     CMP2_IRQHandler  ; CMP2 interrupt
                DCD     FTM0_IRQHandler  ; FTM0 fault, overflow and channels interrupt
                DCD     FTM1_IRQHandler  ; FTM1 fault, overflow and channels interrupt
                DCD     FTM2_IRQHandler  ; FTM2 fault, overflow and channels interrupt
                DCD     CMT_IRQHandler  ; CMT interrupt                
                DCD     RTC_IRQHandler  ; RTC interrupt
                DCD     RTC_Seconds_IRQHandler  ; RTC seconds interrupt
                DCD     PIT0_IRQHandler  ; PIT timer channel 0 interrupt
                DCD     PIT1_IRQHandler  ; PIT timer channel 1 interrupt
                DCD     PIT2_IRQHandler  ; PIT timer channel 2 interrupt
                DCD     PIT3_IRQHandler  ; PIT timer channel 3 interrupt
                DCD     PDB0_IRQHandler  ; PDB0 interrupt
                DCD     USB0_IRQHandler  ; USB0 interrupt
                DCD     USBDCD_IRQHandler  ; USBDCD interrupt
                DCD     Reserved91_IRQHandler  ; Reserved interrupt 91
				DCD     Reserved92_IRQHandler  ; Reserved interrupt 92
				DCD     Reserved93_IRQHandler  ; Reserved interrupt 93
				DCD     Reserved94_IRQHandler  ; Reserved interrupt 94
				DCD     Reserved95_IRQHandler  ; Reserved interrupt 95
				DCD     Reserved96_IRQHandler  ; Reserved interrupt 96
				DCD     DAC0_IRQHandler  ; DAC0 interrupt
				DCD     Reserved98_IRQHandler  ; Reserved interrupt 98
                DCD     TSI0_IRQHandler  ; TSI0 interrupt                
                DCD     MCG_IRQHandler  ; MCG interrupt
                DCD     LPTimer_IRQHandler  ; LPTimer interrupt
                DCD     Reserved102_IRQHandler  ; Reserved interrupt 102
                DCD     PORTA_IRQHandler  ; Port A interrupt
                DCD     PORTB_IRQHandler  ; Port B interrupt
                DCD     PORTC_IRQHandler  ; Port C interrupt
                DCD     PORTD_IRQHandler  ; Port D interrupt
                DCD     PORTE_IRQHandler  ; Port E interrupt
                DCD     Reserved108_IRQHandler ; Reserved interrupt 108
				DCD     Reserved109_IRQHandler ; Reserved interrupt 109
                DCD     SWI_IRQHandler  ; Software interrupt
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
;   <h> Data flash protection byte (FDPROT)
;     <i> Each bit protects a 1/8 region of the data flash memory.
;     <i> (Program flash only devices: Reserved)
;     <o.0>   FDPROT.0
;     <o.1>   FDPROT.1
;     <o.2>   FDPROT.2
;     <o.3>   FDPROT.3
;     <o.4>   FDPROT.4
;     <o.5>   FDPROT.5
;     <o.6>   FDPROT.6
;     <o.7>   FDPROT.7
nFDPROT         EQU     0x00
FDPROT          EQU     nFDPROT:EOR:0xFF
;   </h>
;   <h> EEPROM protection byte (FEPROT)
;     <i> FlexNVM devices: Each bit protects a 1/8 region of the EEPROM.
;     <i> (Program flash only devices: Reserved)
;     <o.0>   FEPROT.0
;     <o.1>   FEPROT.1
;     <o.2>   FEPROT.2
;     <o.3>   FEPROT.3
;     <o.4>   FEPROT.4
;     <o.5>   FEPROT.5
;     <o.6>   FEPROT.6
;     <o.7>   FEPROT.7
nFEPROT         EQU     0x00
FEPROT          EQU     nFEPROT:EOR:0xFF
;   </h>
;   <h> Flash nonvolatile option byte (FOPT)
;     <i> Allows the user to customize the operation of the MCU at boot time.
;     <o.0>  LPBOOT
;       <0=> Low-power boot
;       <1=> normal boot
;     <o.1>  EZPORT_DIS
;       <0=> EzPort operation is enabled
;       <1=> EzPort operation is disabled
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
; </h>
                IF      :LNOT::DEF:RAM_TARGET
                AREA    |.ARM.__at_0x400|, CODE, READONLY
                DCB     BackDoorK0, BackDoorK1, BackDoorK2, BackDoorK3
                DCB     BackDoorK4, BackDoorK5, BackDoorK6, BackDoorK7
                DCB     FPROT0,     FPROT1,     FPROT2,     FPROT3
                DCB     FSEC,       FOPT,       FEPROT,     FDPROT
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
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler         [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler          [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler        [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler          [WEAK]
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
                EXPORT  DMA4_IRQHandler     [WEAK]                   
  				EXPORT  DMA5_IRQHandler     [WEAK]                   
  				EXPORT  DMA6_IRQHandler     [WEAK]                   
  				EXPORT  DMA7_IRQHandler     [WEAK]                   
  				EXPORT  DMA8_IRQHandler     [WEAK]                  
  				EXPORT  DMA9_IRQHandler     [WEAK]                   
  				EXPORT  DMA10_IRQHandler     [WEAK]                  
  				EXPORT  DMA11_IRQHandler     [WEAK]                  
  				EXPORT  DMA12_IRQHandler     [WEAK]              
  				EXPORT  DMA13_IRQHandler     [WEAK]                  
  				EXPORT  DMA14_IRQHandler     [WEAK]                  
  				EXPORT  DMA15_IRQHandler     [WEAK]                    
                EXPORT  DMA_Error_IRQHandler     [WEAK]
                EXPORT  Reserved33_IRQHandler     [WEAK]
                EXPORT  FTFL_IRQHandler     [WEAK]
                EXPORT  Read_Collision_IRQHandler     [WEAK]
                EXPORT  LVD_LVW_IRQHandler     [WEAK]
                EXPORT  LLW_IRQHandler     [WEAK]
                EXPORT  Watchdog_IRQHandler     [WEAK]
                EXPORT  Reserved39_IRQHandler     [WEAK] 
                EXPORT  I2C0_IRQHandler     [WEAK]
                EXPORT  I2C1_IRQHandler     [WEAK]
                EXPORT  SPI0_IRQHandler     [WEAK]
                EXPORT  SPI1_IRQHandler     [WEAK] 
  				EXPORT  Reserved44_IRQHandler     [WEAK] 
  				EXPORT  CAN0_ORed_Message_buffer_IRQHandler   [WEAK]
                EXPORT  CAN0_Bus_Off_IRQHandler      [WEAK]
                EXPORT  CAN0_Error_IRQHandler      [WEAK]
                EXPORT  CAN0_Tx_Warning_IRQHandler  [WEAK]
                EXPORT  CAN0_Rx_Warning_IRQHandler  [WEAK]
                EXPORT  CAN0_Wake_Up_IRQHandler  [WEAK]
                EXPORT  I2S0_Tx_IRQHandler     [WEAK]
                EXPORT  I2S0_Rx_IRQHandler     [WEAK]
                EXPORT  Reserved53_IRQHandler     [WEAK]
  				EXPORT  Reserved54_IRQHandler     [WEAK]
  				EXPORT  Reserved55_IRQHandler     [WEAK]
  				EXPORT  Reserved56_IRQHandler     [WEAK]
  				EXPORT  Reserved57_IRQHandler     [WEAK]
  				EXPORT  Reserved58_IRQHandler     [WEAK]
  				EXPORT  Reserved59_IRQHandler     [WEAK]
                EXPORT  UART0_LON_IRQHandler     [WEAK]
                EXPORT  UART0_RX_TX_IRQHandler     [WEAK]
                EXPORT  UART0_ERR_IRQHandler     [WEAK]
                EXPORT  UART1_RX_TX_IRQHandler     [WEAK]
                EXPORT  UART1_ERR_IRQHandler     [WEAK]
                EXPORT  UART2_RX_TX_IRQHandler     [WEAK]
                EXPORT  UART2_ERR_IRQHandler     [WEAK]
                EXPORT  Reserved67_IRQHandler     [WEAK]
  				EXPORT  Reserved68_IRQHandler     [WEAK]
  				EXPORT  Reserved69_IRQHandler     [WEAK]
  				EXPORT  Reserved70_IRQHandler     [WEAK]
  				EXPORT  Reserved71_IRQHandler     [WEAK]
  				EXPORT  Reserved72_IRQHandler     [WEAK]
                EXPORT  ADC0_IRQHandler     [WEAK]
                EXPORT  ADC1_IRQHandler     [WEAK]
                EXPORT  CMP0_IRQHandler     [WEAK]
                EXPORT  CMP1_IRQHandler     [WEAK]
                EXPORT  CMP2_IRQHandler     [WEAK]
                EXPORT  FTM0_IRQHandler     [WEAK]
                EXPORT  FTM1_IRQHandler     [WEAK]
                EXPORT  FTM2_IRQHandler     [WEAK]
                EXPORT  CMT_IRQHandler     [WEAK]
                EXPORT  RTC_IRQHandler     [WEAK]
                EXPORT  RTC_Seconds_IRQHandler     [WEAK]
                EXPORT  PIT0_IRQHandler     [WEAK]
                EXPORT  PIT1_IRQHandler     [WEAK]
                EXPORT  PIT2_IRQHandler     [WEAK]
                EXPORT  PIT3_IRQHandler     [WEAK]
                EXPORT  PDB0_IRQHandler     [WEAK]
                EXPORT  USB0_IRQHandler     [WEAK]
                EXPORT  USBDCD_IRQHandler     [WEAK]
                EXPORT  Reserved91_IRQHandler     [WEAK]
  				EXPORT  Reserved92_IRQHandler     [WEAK]
  				EXPORT  Reserved93_IRQHandler     [WEAK]
  				EXPORT  Reserved94_IRQHandler     [WEAK]
  				EXPORT  Reserved95_IRQHandler     [WEAK]
  				EXPORT  Reserved96_IRQHandler     [WEAK]
  				EXPORT  DAC0_IRQHandler     [WEAK]
  				EXPORT  Reserved98_IRQHandler     [WEAK]
                EXPORT  TSI0_IRQHandler     [WEAK]
                EXPORT  MCG_IRQHandler     [WEAK]
                EXPORT  LPTimer_IRQHandler     [WEAK]
                EXPORT  Reserved102_IRQHandler     [WEAK]
                EXPORT  PORTA_IRQHandler     [WEAK]
                EXPORT  PORTB_IRQHandler     [WEAK]
                EXPORT  PORTC_IRQHandler     [WEAK]
                EXPORT  PORTD_IRQHandler     [WEAK]
                EXPORT  PORTE_IRQHandler     [WEAK]
                EXPORT  Reserved108_IRQHandler     [WEAK]
  				EXPORT  Reserved109_IRQHandler     [WEAK]
                EXPORT  SWI_IRQHandler     [WEAK]
                EXPORT  DefaultISR                      [WEAK]

DMA0_IRQHandler     
DMA1_IRQHandler     
DMA2_IRQHandler     
DMA3_IRQHandler     
DMA4_IRQHandler                        
DMA5_IRQHandler                       
DMA6_IRQHandler                        
DMA7_IRQHandler                        
DMA8_IRQHandler                       
DMA9_IRQHandler                        
DMA10_IRQHandler                      
DMA11_IRQHandler                      
DMA12_IRQHandler                  
DMA13_IRQHandler                      
DMA14_IRQHandler                      
DMA15_IRQHandler                        
DMA_Error_IRQHandler
Reserved33_IRQHandler 
FTFL_IRQHandler     
Read_Collision_IRQHandler
LVD_LVW_IRQHandler     
LLW_IRQHandler     
Watchdog_IRQHandler
Reserved39_IRQHandler 
I2C0_IRQHandler     
I2C1_IRQHandler     
SPI0_IRQHandler     
SPI1_IRQHandler      
Reserved44_IRQHandler
CAN0_ORed_Message_buffer_IRQHandler   
CAN0_Bus_Off_IRQHandler      
CAN0_Error_IRQHandler      
CAN0_Tx_Warning_IRQHandler 
CAN0_Rx_Warning_IRQHandler 
CAN0_Wake_Up_IRQHandler  
I2S0_Tx_IRQHandler    
I2S0_Rx_IRQHandler    
Reserved53_IRQHandler 
Reserved54_IRQHandler 
Reserved55_IRQHandler 
Reserved56_IRQHandler 
Reserved57_IRQHandler 
Reserved58_IRQHandler 
Reserved59_IRQHandler 
UART0_LON_IRQHandler  
UART0_RX_TX_IRQHandler 
UART0_ERR_IRQHandler   
UART1_RX_TX_IRQHandler 
UART1_ERR_IRQHandler   
UART2_RX_TX_IRQHandler 
UART2_ERR_IRQHandler   
Reserved67_IRQHandler  
Reserved68_IRQHandler  
Reserved69_IRQHandler  
Reserved70_IRQHandler  
Reserved71_IRQHandler  
Reserved72_IRQHandler  
ADC0_IRQHandler     
ADC1_IRQHandler     
CMP0_IRQHandler     
CMP1_IRQHandler     
CMP2_IRQHandler     
FTM0_IRQHandler     
FTM1_IRQHandler     
FTM2_IRQHandler     
CMT_IRQHandler     
RTC_IRQHandler     
RTC_Seconds_IRQHandler 
PIT0_IRQHandler     
PIT1_IRQHandler     
PIT2_IRQHandler     
PIT3_IRQHandler     
PDB0_IRQHandler     
USB0_IRQHandler     
USBDCD_IRQHandler   
Reserved91_IRQHandler
Reserved92_IRQHandler
Reserved93_IRQHandler
Reserved94_IRQHandler
Reserved95_IRQHandler
Reserved96_IRQHandler
DAC0_IRQHandler     
Reserved98_IRQHandler 
TSI0_IRQHandler     
MCG_IRQHandler     
LPTimer_IRQHandler     
Reserved102_IRQHandler 
PORTA_IRQHandler     
PORTB_IRQHandler     
PORTC_IRQHandler     
PORTD_IRQHandler     
PORTE_IRQHandler     
Reserved108_IRQHandler 
Reserved109_IRQHandler 
SWI_IRQHandler 
DefaultISR  

                B       .

                ENDP


                ALIGN
                END
