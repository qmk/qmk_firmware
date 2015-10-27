/*******************************************************************************
 * Copyright (C) 2015 Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *******************************************************************************
 */

                MODULE  ?cstartup

                ;; Forward declaration of sections.
                SECTION CSTACK:DATA:NOROOT(3)

                SECTION .intvec:CODE:NOROOT(2)

                EXTERN  __iar_program_start
                EXTERN  SystemInit
                PUBLIC  __vector_table

                DATA
__vector_table  DCD     sfe(CSTACK)               /* Top of Stack */
                DCD     Reset_Handler             /* Reset Handler */
                DCD     NMI_Handler               /* NMI Handler */
                DCD     HardFault_Handler         /* Hard Fault Handler */
                DCD     DefaultIRQ_Handler        /* MPU Fault Handler */
                DCD     DefaultIRQ_Handler        /* Bus Fault Handler */
                DCD     DefaultIRQ_Handler        /* Usage Fault Handler */
                DCD     0                         /* Reserved */
                DCD     0                         /* Reserved */
                DCD     0                         /* Reserved */
                DCD     0                         /* Reserved */
                DCD     DefaultIRQ_Handler        /* SVCall Handler */
                DCD     DebugMon_Handler          /* Debug Monitor Handler */
                DCD     0                         /* Reserved */
                DCD     DefaultIRQ_Handler        /* PendSV Handler */
                DCD     SysTick_IRQHandler        /* SysTick Handler */

                /* Maxim 32600 Externals interrupts */
                DCD     UART0_IRQHandler          /* 16: 1 UART0 */
                DCD     UART1_IRQHandler          /* 17: 2 UART1 */
                DCD     I2CM0_IRQHandler          /* 18: 3 I2C Master 0 */
                DCD     I2CS_IRQHandler           /* 19: 4 I2C Slave */
                DCD     USB_IRQHandler            /* 20: 5 USB */
                DCD     PMU_IRQHandler            /* 21: 6 DMA */
                DCD     AFE_IRQHandler            /* 22: 7 AFE */
                DCD     MAA_IRQHandler            /* 23: 8 MAA */
                DCD     AES_IRQHandler            /* 24: 9 AES */
                DCD     SPI0_IRQHandler           /* 25:10 SPI0 */
                DCD     SPI1_IRQHandler           /* 26:11 SPI1 */
                DCD     SPI2_IRQHandler           /* 27:12 SPI2 */
                DCD     TMR0_IRQHandler           /* 28:13 Timer32-0 */
                DCD     TMR1_IRQHandler           /* 29:14 Timer32-1 */
                DCD     TMR2_IRQHandler           /* 30:15 Timer32-1 */
                DCD     TMR3_IRQHandler           /* 31:16 Timer32-2 */
                DCD     RSVD0_IRQHandler          /* 32:17 RSVD */
                DCD     RSVD1_IRQHandler          /* 33:18 RSVD */
                DCD     DAC0_IRQHandler           /* 34:19 DAC0  (12-bit DAC) */  
                DCD     DAC1_IRQHandler           /* 35:20 DAC1  (12-bit DAC) */  
                DCD     DAC2_IRQHandler           /* 36:21 DAC2  (8-bit DAC) */
                DCD     DAC3_IRQHandler           /* 37:22 DAC3  (8-bit DAC) */
                DCD     ADC_IRQHandler            /* 38:23 ADC */
                DCD     FLC_IRQHandler            /* 39:24 Flash Controller */
                DCD     PWRMAN_IRQHandler         /* 40:25 PWRMAN */
                DCD     CLKMAN_IRQHandler         /* 41:26 CLKMAN */
                DCD     RTC0_IRQHandler           /* 42:27 RTC INT0 */
                DCD     RTC1_IRQHandler           /* 43:28 RTC INT1 */
                DCD     RTC2_IRQHandler           /* 44:29 RTC INT2 */
                DCD     RTC3_IRQHandler           /* 45:30 RTC INT3 */
                DCD     WDT0_IRQHandler           /* 46:31 WATCHDOG0 */
                DCD     WDT0_P_IRQHandler         /* 47:32 WATCHDOG0 PRE-WINDOW */
                DCD     WDT1_IRQHandler           /* 48:33 WATCHDOG1 */
                DCD     WDT1_P_IRQHandler         /* 49:34 WATCHDOG1 PRE-WINDOW */
                DCD     GPIO_P0_IRQHandler        /* 50:35 GPIO Port 0  */
                DCD     GPIO_P1_IRQHandler        /* 51:36 GPIO Port 1  */
                DCD     GPIO_P2_IRQHandler        /* 52:37 GPIO Port 2  */
                DCD     GPIO_P3_IRQHandler        /* 53:38 GPIO Port 3  */
                DCD     GPIO_P4_IRQHandler        /* 54:39 GPIO Port 4  */
                DCD     GPIO_P5_IRQHandler        /* 55:40 GPIO Port 5  */
                DCD     GPIO_P6_IRQHandler        /* 56:41 GPIO Port 6  */
                DCD     GPIO_P7_IRQHandler        /* 57:42 GPIO Port 7  */
                DCD     TMR16_0_IRQHandler        /* 58:43 Timer16-s0 */
                DCD     TMR16_1_IRQHandler        /* 59:44 Timer16-s1 */
                DCD     TMR16_2_IRQHandler        /* 60:45 Timer16-s2 */
                DCD     TMR16_3_IRQHandler        /* 61:46 Timer16-s3 */
                DCD     I2CM1_IRQHandler          /* 62:47 I2C Master 1 */

                THUMB
; Dummy Exception Handlers (infinite loops which can be modified)

                PUBWEAK Reset_Handler
                SECTION .text:CODE:REORDER:NOROOT(2)
Reset_Handler
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__iar_program_start
                BX      R0
	
                PUBWEAK NMI_Handler
                SECTION .text:CODE:REORDER:NOROOT(1)
NMI_Handler
                B       NMI_Handler

                PUBWEAK HardFault_Handler
                SECTION .text:CODE:REORDER:NOROOT(1)
HardFault_Handler
                B       HardFault_Handler

                PUBWEAK DefaultIRQ_Handler
                SECTION .text:CODE:REORDER:NOROOT(1)
DefaultIRQ_Handler
                B       DefaultIRQ_Handler
                   
                PUBWEAK DebugMon_Handler
                SECTION .text:CODE:REORDER:NOROOT(1)
DebugMon_Handler
                B       DebugMon_Handler

                PUBWEAK SysTick_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
SysTick_IRQHandler
                B       SysTick_IRQHandler
      
                PUBWEAK UART0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
UART0_IRQHandler
                B       UART0_IRQHandler
    
                PUBWEAK UART1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
UART1_IRQHandler
                B       UART1_IRQHandler
    
                PUBWEAK I2CM0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
I2CM0_IRQHandler
                B       I2CM0_IRQHandler
    
                PUBWEAK I2CS_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
I2CS_IRQHandler
                B       I2CS_IRQHandler
     
                PUBWEAK USB_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
USB_IRQHandler
                B       USB_IRQHandler
      
                PUBWEAK PMU_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
PMU_IRQHandler
                B       PMU_IRQHandler
      
                PUBWEAK AFE_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
AFE_IRQHandler
                B       AFE_IRQHandler
      
                PUBWEAK MAA_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
MAA_IRQHandler
                B       MAA_IRQHandler
      
                PUBWEAK AES_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
AES_IRQHandler
                B       AES_IRQHandler
      
                PUBWEAK SPI0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
SPI0_IRQHandler
                B       SPI0_IRQHandler
     
                PUBWEAK SPI1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
SPI1_IRQHandler
                B       SPI1_IRQHandler
     
                PUBWEAK SPI2_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
SPI2_IRQHandler
                B       SPI2_IRQHandler
     
                PUBWEAK TMR0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
TMR0_IRQHandler
                B       TMR0_IRQHandler
     
                PUBWEAK TMR1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
TMR1_IRQHandler
                B       TMR1_IRQHandler
     
                PUBWEAK TMR2_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
TMR2_IRQHandler
                B       TMR2_IRQHandler
     
                PUBWEAK TMR3_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
TMR3_IRQHandler
                B       TMR3_IRQHandler
     
                PUBWEAK RSVD0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
RSVD0_IRQHandler
                B       RSVD0_IRQHandler
    
                PUBWEAK RSVD1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
RSVD1_IRQHandler
                B       RSVD1_IRQHandler
    
                PUBWEAK DAC0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
DAC0_IRQHandler
                B       DAC0_IRQHandler
     
                PUBWEAK DAC1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
DAC1_IRQHandler
                B       DAC1_IRQHandler
     
                PUBWEAK DAC2_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
DAC2_IRQHandler
                B       DAC2_IRQHandler
     
                PUBWEAK DAC3_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
DAC3_IRQHandler
                B       DAC3_IRQHandler
     
                PUBWEAK ADC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
ADC_IRQHandler
                B       ADC_IRQHandler
      
                PUBWEAK FLC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
FLC_IRQHandler
                B       FLC_IRQHandler
    
                PUBWEAK PWRMAN_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
PWRMAN_IRQHandler
                B       PWRMAN_IRQHandler
 
                PUBWEAK CLKMAN_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
CLKMAN_IRQHandler
                B       CLKMAN_IRQHandler
 
                PUBWEAK RTC0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
RTC0_IRQHandler
                B       RTC0_IRQHandler
   
                PUBWEAK RTC1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
RTC1_IRQHandler
                B       RTC1_IRQHandler
   
                PUBWEAK RTC2_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
RTC2_IRQHandler
                B       RTC2_IRQHandler
   
                PUBWEAK RTC3_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
RTC3_IRQHandler
                B       RTC3_IRQHandler
   
                PUBWEAK WDT0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
WDT0_IRQHandler
                B       WDT0_IRQHandler
   
                PUBWEAK WDT0_P_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
WDT0_P_IRQHandler
                B       WDT0_P_IRQHandler
 
                PUBWEAK WDT1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
WDT1_IRQHandler
                B       WDT1_IRQHandler
   
                PUBWEAK WDT1_P_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
WDT1_P_IRQHandler
                B       WDT1_P_IRQHandler
 
                PUBWEAK GPIO_P0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
GPIO_P0_IRQHandler
                B       GPIO_P0_IRQHandler

                PUBWEAK GPIO_P1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
GPIO_P1_IRQHandler
                B       GPIO_P1_IRQHandler

                PUBWEAK GPIO_P2_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
GPIO_P2_IRQHandler
                B       GPIO_P2_IRQHandler

                PUBWEAK GPIO_P3_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
GPIO_P3_IRQHandler
                B       GPIO_P3_IRQHandler

                PUBWEAK GPIO_P4_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
GPIO_P4_IRQHandler
                B       GPIO_P4_IRQHandler

                PUBWEAK GPIO_P5_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
GPIO_P5_IRQHandler
                B       GPIO_P5_IRQHandler

                PUBWEAK GPIO_P6_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
GPIO_P6_IRQHandler
                B       GPIO_P6_IRQHandler

                PUBWEAK GPIO_P7_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
GPIO_P7_IRQHandler
                B       GPIO_P7_IRQHandler

                PUBWEAK TMR16_0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
TMR16_0_IRQHandler
                B       TMR16_0_IRQHandler

                PUBWEAK TMR16_1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
TMR16_1_IRQHandler
                B       TMR16_1_IRQHandler

                PUBWEAK TMR16_2_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
TMR16_2_IRQHandler
                B       TMR16_2_IRQHandler

                PUBWEAK TMR16_3_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
TMR16_3_IRQHandler
                B       TMR16_3_IRQHandler

                PUBWEAK I2CM1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
I2CM1_IRQHandler
                B       I2CM1_IRQHandler  
	
                END
