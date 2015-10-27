/**************************************************
 *
 * Copyright 2012 IAR Systems. All rights reserved.
 *
 * $Revision: 16 $
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

        SECTION .intvec:CODE:ROOT(2)

        EXTERN  __iar_program_start
        EXTERN  SystemInit
        PUBLIC  __vector_table

        DATA
__vector_table
        DCD     sfe(CSTACK)               ; Top of Stack
        DCD     Reset_Handler       ; Reset Handler
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
        DCD     DMA0_IRQHandler  ; DMA Channel 0 Transfer Complete
        DCD     DMA1_IRQHandler  ; DMA Channel 1 Transfer Complete
        DCD     DMA2_IRQHandler  ; DMA Channel 2 Transfer Complete
        DCD     DMA3_IRQHandler  ; DMA Channel 3 Transfer Complete
        DCD     DMA4_IRQHandler  ; DMA Channel 4 Transfer Complete
        DCD     DMA5_IRQHandler  ; DMA Channel 5 Transfer Complete
        DCD     DMA6_IRQHandler  ; DMA Channel 6 Transfer Complete
        DCD     DMA7_IRQHandler  ; DMA Channel 7 Transfer Complete
        DCD     DMA8_IRQHandler  ; DMA Channel 8 Transfer Complete
        DCD     DMA9_IRQHandler  ; DMA Channel 9 Transfer Complete
        DCD     DMA10_IRQHandler  ; DMA Channel 10 Transfer Complete
        DCD     DMA11_IRQHandler  ; DMA Channel 11 Transfer Complete
        DCD     DMA12_IRQHandler  ; DMA Channel 12 Transfer Complete
        DCD     DMA13_IRQHandler  ; DMA Channel 13 Transfer Complete
        DCD     DMA14_IRQHandler  ; DMA Channel 14 Transfer Complete
        DCD     DMA15_IRQHandler  ; DMA Channel 15 Transfer Complete
        DCD     DMA_Error_IRQHandler  ; DMA Error Interrupt
        DCD     MCM_IRQHandler  ; Normal Interrupt
        DCD     FTFE_IRQHandler  ; FTFE Command complete interrupt
        DCD     Read_Collision_IRQHandler  ; Read Collision Interrupt
        DCD     LVD_LVW_IRQHandler  ; Low Voltage Detect, Low Voltage Warning
        DCD     LLW_IRQHandler  ; Low Leakage Wakeup
        DCD     Watchdog_IRQHandler  ; WDOG Interrupt
        DCD     0                   ; Reserved
        DCD     I2C0_IRQHandler  ; I2C0 interrupt
        DCD     I2C1_IRQHandler  ; I2C1 interrupt
        DCD     SPI0_IRQHandler  ; SPI0 Interrupt
        DCD     SPI1_IRQHandler  ; SPI1 Interrupt
        DCD     I2S0_Tx_IRQHandler  ; I2S0 transmit interrupt
        DCD     I2S0_Rx_IRQHandler  ; I2S0 receive interrupt
        DCD     UART0_LON_IRQHandler  ; UART0 LON interrupt
        DCD     UART0_RX_TX_IRQHandler  ; UART0 Receive/Transmit interrupt
        DCD     UART0_ERR_IRQHandler  ; UART0 Error interrupt
        DCD     UART1_RX_TX_IRQHandler  ; UART1 Receive/Transmit interrupt
        DCD     UART1_ERR_IRQHandler  ; UART1 Error interrupt
        DCD     UART2_RX_TX_IRQHandler  ; UART2 Receive/Transmit interrupt
        DCD     UART2_ERR_IRQHandler  ; UART2 Error interrupt
        DCD     UART3_RX_TX_IRQHandler  ; UART3 Receive/Transmit interrupt
        DCD     UART3_ERR_IRQHandler  ; UART3 Error interrupt
        DCD     ADC0_IRQHandler  ; ADC0 interrupt
        DCD     CMP0_IRQHandler  ; CMP0 interrupt
        DCD     CMP1_IRQHandler  ; CMP1 interrupt
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
        DCD     PDB0_IRQHandler  ; PDB0 Interrupt
        DCD     USB0_IRQHandler  ; USB0 interrupt
        DCD     USBDCD_IRQHandler  ; USBDCD Interrupt
        DCD     0                           ; Reserved
        DCD     DAC0_IRQHandler  ; DAC0 interrupt
        DCD     MCG_IRQHandler  ; MCG Interrupt
        DCD     LPTimer_IRQHandler  ; LPTimer interrupt
        DCD     PORTA_IRQHandler  ; Port A interrupt
        DCD     PORTB_IRQHandler  ; Port B interrupt
        DCD     PORTC_IRQHandler  ; Port C interrupt
        DCD     PORTD_IRQHandler  ; Port D interrupt
        DCD     PORTE_IRQHandler  ; Port E interrupt
        DCD     SWI_IRQHandler  ; Software interrupt
        DCD     SPI2_IRQHandler  ; SPI2 Interrupt
        DCD     UART4_RX_TX_IRQHandler  ; UART4 Receive/Transmit interrupt
        DCD     UART4_ERR_IRQHandler  ; UART4 Error interrupt
        DCD     UART5_RX_TX_IRQHandler  ; UART5 Receive/Transmit interrupt
        DCD     UART5_ERR_IRQHandler  ; UART5 Error interrupt
        DCD     CMP2_IRQHandler  ; CMP2 interrupt
        DCD     FTM3_IRQHandler  ; FTM3 fault, overflow and channels interrupt
        DCD     DAC1_IRQHandler  ; DAC1 interrupt
        DCD     ADC1_IRQHandler  ; ADC1 interrupt
        DCD     I2C2_IRQHandler  ; I2C2 interrupt
        DCD     CAN0_ORed_Message_buffer_IRQHandler  ; CAN0 OR'd message buffers interrupt
        DCD     CAN0_Bus_Off_IRQHandler  ; CAN0 bus off interrupt
        DCD     CAN0_Error_IRQHandler  ; CAN0 error interrupt
        DCD     CAN0_Tx_Warning_IRQHandler  ; CAN0 Tx warning interrupt
        DCD     CAN0_Rx_Warning_IRQHandler  ; CAN0 Rx warning interrupt
        DCD     CAN0_Wake_Up_IRQHandler  ; CAN0 wake up interrupt
        DCD     SDHC_IRQHandler  ; SDHC interrupt
        DCD     Default_Handler  ; 98
        DCD     Default_Handler  ; 99
        DCD     Default_Handler  ; 100
        DCD     Default_Handler  ; 101
        DCD     Default_Handler  ; 102
        DCD     Default_Handler  ; 103
        DCD     Default_Handler  ; 104
        DCD     Default_Handler  ; 105
        DCD     Default_Handler  ; 106
        DCD     Default_Handler  ; 107
        DCD     Default_Handler  ; 108
        DCD     Default_Handler  ; 109
        DCD     Default_Handler  ; 110
        DCD     Default_Handler  ; 111
        DCD     Default_Handler  ; 112
        DCD     Default_Handler  ; 113
        DCD     Default_Handler  ; 114
        DCD     Default_Handler  ; 115
        DCD     Default_Handler  ; 116
        DCD     Default_Handler  ; 117
        DCD     Default_Handler  ; 118
        DCD     Default_Handler  ; 119
        DCD     Default_Handler  ; 120
        DCD     Default_Handler  ; 121
        DCD     Default_Handler  ; 122
        DCD     Default_Handler  ; 123
        DCD     Default_Handler  ; 124
        DCD     Default_Handler  ; 125
        DCD     Default_Handler  ; 126
        DCD     Default_Handler  ; 127
        DCD     Default_Handler  ; 128
        DCD     Default_Handler  ; 129
        DCD     Default_Handler  ; 130
        DCD     Default_Handler  ; 131
        DCD     Default_Handler  ; 132
        DCD     Default_Handler  ; 133
        DCD     Default_Handler  ; 134
        DCD     Default_Handler  ; 135
        DCD     Default_Handler  ; 136
        DCD     Default_Handler  ; 137
        DCD     Default_Handler  ; 138
        DCD     Default_Handler  ; 139
        DCD     Default_Handler  ; 140
        DCD     Default_Handler  ; 141
        DCD     Default_Handler  ; 142
        DCD     Default_Handler  ; 143
        DCD     Default_Handler  ; 144
        DCD     Default_Handler  ; 145
        DCD     Default_Handler  ; 146
        DCD     Default_Handler  ; 147
        DCD     Default_Handler  ; 148
        DCD     Default_Handler  ; 149
        DCD     Default_Handler  ; 150
        DCD     Default_Handler  ; 151
        DCD     Default_Handler  ; 152
        DCD     Default_Handler  ; 153
        DCD     Default_Handler  ; 154
        DCD     Default_Handler  ; 155
        DCD     Default_Handler  ; 156
        DCD     Default_Handler  ; 157
        DCD     Default_Handler  ; 158
        DCD     Default_Handler  ; 159
        DCD     Default_Handler  ; 160
        DCD     Default_Handler  ; 161
        DCD     Default_Handler  ; 162
        DCD     Default_Handler  ; 163
        DCD     Default_Handler  ; 164
        DCD     Default_Handler  ; 165
        DCD     Default_Handler  ; 166
        DCD     Default_Handler  ; 167
        DCD     Default_Handler  ; 168
        DCD     Default_Handler  ; 169
        DCD     Default_Handler  ; 170
        DCD     Default_Handler  ; 171
        DCD     Default_Handler  ; 172
        DCD     Default_Handler  ; 173
        DCD     Default_Handler  ; 174
        DCD     Default_Handler  ; 175
        DCD     Default_Handler  ; 176
        DCD     Default_Handler  ; 177
        DCD     Default_Handler  ; 178
        DCD     Default_Handler  ; 179
        DCD     Default_Handler  ; 180
        DCD     Default_Handler  ; 181
        DCD     Default_Handler  ; 182
        DCD     Default_Handler  ; 183
        DCD     Default_Handler  ; 184
        DCD     Default_Handler  ; 185
        DCD     Default_Handler  ; 186
        DCD     Default_Handler  ; 187
        DCD     Default_Handler  ; 188
        DCD     Default_Handler  ; 189
        DCD     Default_Handler  ; 190
        DCD     Default_Handler  ; 191
        DCD     Default_Handler  ; 192
        DCD     Default_Handler  ; 193
        DCD     Default_Handler  ; 194
        DCD     Default_Handler  ; 195
        DCD     Default_Handler  ; 196
        DCD     Default_Handler  ; 197
        DCD     Default_Handler  ; 198
        DCD     Default_Handler  ; 199
        DCD     Default_Handler  ; 200
        DCD     Default_Handler  ; 201
        DCD     Default_Handler  ; 202
        DCD     Default_Handler  ; 203
        DCD     Default_Handler  ; 204
        DCD     Default_Handler  ; 205
        DCD     Default_Handler  ; 206
        DCD     Default_Handler  ; 207
        DCD     Default_Handler  ; 208
        DCD     Default_Handler  ; 209
        DCD     Default_Handler  ; 210
        DCD     Default_Handler  ; 211
        DCD     Default_Handler  ; 212
        DCD     Default_Handler  ; 213
        DCD     Default_Handler  ; 214
        DCD     Default_Handler  ; 215
        DCD     Default_Handler  ; 216
        DCD     Default_Handler  ; 217
        DCD     Default_Handler  ; 218
        DCD     Default_Handler  ; 219
        DCD     Default_Handler  ; 220
        DCD     Default_Handler  ; 221
        DCD     Default_Handler  ; 222
        DCD     Default_Handler  ; 223
        DCD     Default_Handler  ; 224
        DCD     Default_Handler  ; 225
        DCD     Default_Handler  ; 226
        DCD     Default_Handler  ; 227
        DCD     Default_Handler  ; 228
        DCD     Default_Handler  ; 229
        DCD     Default_Handler  ; 230
        DCD     Default_Handler  ; 231
        DCD     Default_Handler  ; 232
        DCD     Default_Handler  ; 233
        DCD     Default_Handler  ; 234
        DCD     Default_Handler  ; 235
        DCD     Default_Handler  ; 236
        DCD     Default_Handler  ; 237
        DCD     Default_Handler  ; 238
        DCD     Default_Handler  ; 239
        DCD     Default_Handler  ; 240
        DCD     Default_Handler  ; 241
        DCD     Default_Handler  ; 242
        DCD     Default_Handler  ; 243
        DCD     Default_Handler  ; 244
        DCD     Default_Handler  ; 245
        DCD     Default_Handler  ; 246
        DCD     Default_Handler  ; 247
        DCD     Default_Handler  ; 248
        DCD     Default_Handler  ; 249
        DCD     Default_Handler  ; 250
        DCD     Default_Handler  ; 251
        DCD     Default_Handler  ; 252
        DCD     Default_Handler  ; 253
        DCD     Default_Handler  ; 254
        DCD     Default_Handler  ; 255
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;Flash Configuration
;;16-byte flash configuration field that stores default protection settings (loaded on reset)
;;and security information that allows the MCU to restrict acces to the FTFL module.

BackDoorK0      EQU     0xFF
BackDoorK1      EQU     0xFF
BackDoorK2      EQU     0xFF
BackDoorK3      EQU     0xFF
BackDoorK4      EQU     0xFF
BackDoorK5      EQU     0xFF
BackDoorK6      EQU     0xFF
BackDoorK7      EQU     0xFF

nFPROT0         EQU     0x00
FPROT0          EQU     nFPROT0^0xFF

nFPROT1         EQU     0x00
FPROT1          EQU     nFPROT1^0xFF

nFPROT2         EQU     0x00
FPROT2          EQU     nFPROT2^0xFF

nFPROT3         EQU     0x00
FPROT3          EQU     nFPROT3^0xFF

nFEPROT         EQU     0x00
FEPROT          EQU     nFEPROT^0xFF

nFDPROT         EQU     0x00
FDPROT          EQU     nFDPROT^0xFF

FOPT            EQU     0xFF        

FSEC            EQU     0xFE        
        SECTION FlashConfig:CONST:REORDER:ROOT(2)
Config:
        DATA
        DCB     BackDoorK0, BackDoorK1, BackDoorK2, BackDoorK3
        DCB     BackDoorK4, BackDoorK5, BackDoorK6, BackDoorK7
        DCB     FPROT0,     FPROT1,     FPROT2,     FPROT3
        DCB     FSEC,       FOPT,       FEPROT,     FDPROT        
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
      PUBWEAK DMA0_IRQHandler
      PUBWEAK DMA1_IRQHandler
      PUBWEAK DMA2_IRQHandler
      PUBWEAK DMA3_IRQHandler
      PUBWEAK DMA4_IRQHandler
      PUBWEAK DMA5_IRQHandler
      PUBWEAK DMA6_IRQHandler
      PUBWEAK DMA7_IRQHandler
      PUBWEAK DMA8_IRQHandler
      PUBWEAK DMA9_IRQHandler
      PUBWEAK DMA10_IRQHandler
      PUBWEAK DMA11_IRQHandler
      PUBWEAK DMA12_IRQHandler
      PUBWEAK DMA13_IRQHandler
      PUBWEAK DMA14_IRQHandler
      PUBWEAK DMA15_IRQHandler
      PUBWEAK DMA_Error_IRQHandler
      PUBWEAK MCM_IRQHandler
      PUBWEAK FTFE_IRQHandler
      PUBWEAK Read_Collision_IRQHandler
      PUBWEAK LVD_LVW_IRQHandler
      PUBWEAK LLW_IRQHandler
      PUBWEAK Watchdog_IRQHandler
      PUBWEAK I2C0_IRQHandler
      PUBWEAK I2C1_IRQHandler
      PUBWEAK SPI0_IRQHandler
      PUBWEAK SPI1_IRQHandler
      PUBWEAK I2S0_Tx_IRQHandler
      PUBWEAK I2S0_Rx_IRQHandler
      PUBWEAK UART0_LON_IRQHandler
      PUBWEAK UART0_RX_TX_IRQHandler
      PUBWEAK UART0_ERR_IRQHandler
      PUBWEAK UART1_RX_TX_IRQHandler
      PUBWEAK UART1_ERR_IRQHandler
      PUBWEAK UART2_RX_TX_IRQHandler
      PUBWEAK UART2_ERR_IRQHandler
      PUBWEAK UART3_RX_TX_IRQHandler
      PUBWEAK UART3_ERR_IRQHandler
      PUBWEAK ADC0_IRQHandler
      PUBWEAK CMP0_IRQHandler
      PUBWEAK CMP1_IRQHandler
      PUBWEAK FTM0_IRQHandler
      PUBWEAK FTM1_IRQHandler
      PUBWEAK FTM2_IRQHandler
      PUBWEAK CMT_IRQHandler
      PUBWEAK RTC_IRQHandler
      PUBWEAK RTC_Seconds_IRQHandler
      PUBWEAK PIT0_IRQHandler
      PUBWEAK PIT1_IRQHandler
      PUBWEAK PIT2_IRQHandler
      PUBWEAK PIT3_IRQHandler
      PUBWEAK PDB0_IRQHandler
      PUBWEAK USB0_IRQHandler
      PUBWEAK USBDCD_IRQHandler
      PUBWEAK DAC0_IRQHandler
      PUBWEAK MCG_IRQHandler
      PUBWEAK LPTimer_IRQHandler
      PUBWEAK PORTA_IRQHandler
      PUBWEAK PORTB_IRQHandler
      PUBWEAK PORTC_IRQHandler
      PUBWEAK PORTD_IRQHandler
      PUBWEAK PORTE_IRQHandler
      PUBWEAK SWI_IRQHandler
      PUBWEAK SPI2_IRQHandler
      PUBWEAK UART4_RX_TX_IRQHandler
      PUBWEAK UART4_ERR_IRQHandler
      PUBWEAK UART5_RX_TX_IRQHandler
      PUBWEAK UART5_ERR_IRQHandler
      PUBWEAK CMP2_IRQHandler
      PUBWEAK FTM3_IRQHandler
      PUBWEAK DAC1_IRQHandler
      PUBWEAK ADC1_IRQHandler
      PUBWEAK I2C2_IRQHandler
      PUBWEAK CAN0_ORed_Message_buffer_IRQHandler
      PUBWEAK CAN0_Bus_Off_IRQHandler
      PUBWEAK CAN0_Error_IRQHandler
      PUBWEAK CAN0_Tx_Warning_IRQHandler
      PUBWEAK CAN0_Rx_Warning_IRQHandler
      PUBWEAK CAN0_Wake_Up_IRQHandler
      PUBWEAK SDHC_IRQHandler

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
MCM_IRQHandler
FTFE_IRQHandler
Read_Collision_IRQHandler
LVD_LVW_IRQHandler
LLW_IRQHandler
Watchdog_IRQHandler
I2C0_IRQHandler
I2C1_IRQHandler
SPI0_IRQHandler
SPI1_IRQHandler
I2S0_Tx_IRQHandler
I2S0_Rx_IRQHandler
UART0_LON_IRQHandler
UART0_RX_TX_IRQHandler
UART0_ERR_IRQHandler
UART1_RX_TX_IRQHandler
UART1_ERR_IRQHandler
UART2_RX_TX_IRQHandler
UART2_ERR_IRQHandler
UART3_RX_TX_IRQHandler
UART3_ERR_IRQHandler
ADC0_IRQHandler
CMP0_IRQHandler
CMP1_IRQHandler
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
DAC0_IRQHandler
MCG_IRQHandler
LPTimer_IRQHandler
PORTA_IRQHandler
PORTB_IRQHandler
PORTC_IRQHandler
PORTD_IRQHandler
PORTE_IRQHandler
SWI_IRQHandler
SPI2_IRQHandler
UART4_RX_TX_IRQHandler
UART4_ERR_IRQHandler
UART5_RX_TX_IRQHandler
UART5_ERR_IRQHandler
CMP2_IRQHandler
FTM3_IRQHandler
DAC1_IRQHandler
ADC1_IRQHandler
I2C2_IRQHandler
CAN0_ORed_Message_buffer_IRQHandler
CAN0_Bus_Off_IRQHandler
CAN0_Error_IRQHandler
CAN0_Tx_Warning_IRQHandler
CAN0_Rx_Warning_IRQHandler
CAN0_Wake_Up_IRQHandler
SDHC_IRQHandler
Default_Handler

        B Default_Handler
        END
