
/****************************************************************************************************//**
 * @file     LPC13Uxx.h
 *
 * 
 *
 * @brief    CMSIS Cortex-M3 Core Peripheral Access Layer Header File for
 *           default LPC13Uxx Device Series
 *
 * @version  V0.1
 * @date     18. Jan 2012
 *
 * @note     Generated with SFDGen V2.6 Build 4f  on Tuesday, 17.01.2012 13:39:52
 *
 *           from CMSIS SVD File 'LPC13uxx_svd_v0.1.xml' Version 0.1,
 *           created on Thurs, 01.19.2012 15:13:15, last modified on Thurs, 01.19.2012 15:53:09
 *
 *******************************************************************************************************/

/** @addtogroup NXP
  * @{
  */

/** @addtogroup LPC13Uxx
  * @{
  */

#ifndef __LPC13UXX_H__
#define __LPC13UXX_H__

#ifdef __cplusplus
extern "C" {
#endif 


#if defined ( __CC_ARM   )
  #pragma anon_unions
#endif

 /* Interrupt Number Definition */

typedef enum {
// -------------------------  Cortex-M3 Processor Exceptions Numbers  -----------------------------
  Reset_IRQn                        = -15,  /*!<   1  Reset Vector, invoked on Power up and warm reset */
  NonMaskableInt_IRQn               = -14,  /*!<   2  Non maskable Interrupt, cannot be stopped or preempted */
  HardFault_IRQn                    = -13,  /*!<   3  Hard Fault, all classes of Fault */
  MemoryManagement_IRQn             = -12,  /*!<   4  Memory Management, MPU mismatch, including Access Violation and No Match */
  BusFault_IRQn                     = -11,  /*!<   5  Bus Fault, Pre-Fetch-, Memory Access Fault, other address/memory related Fault */
  UsageFault_IRQn                   = -10,  /*!<   6  Usage Fault, i.e. Undef Instruction, Illegal State Transition */
  SVCall_IRQn                       = -5,   /*!<  11  System Service Call via SVC instruction */
  DebugMonitor_IRQn                 = -4,   /*!<  12  Debug Monitor                    */
  PendSV_IRQn                       = -2,   /*!<  14  Pendable request for system service */
  SysTick_IRQn                      = -1,   /*!<  15  System Tick Timer                */
// ----------------------------  LPC13Uxx Specific Interrupt Numbers  --------------------------------
  PIN_INT0_IRQn                     = 0,    /*!<   0  PIN_INT0                         */
  PIN_INT1_IRQn                     = 1,    /*!<   1  PIN_INT1                         */
  PIN_INT2_IRQn                     = 2,    /*!<   2  PIN_INT2                         */
  PIN_INT3_IRQn                     = 3,    /*!<   3  PIN_INT3                         */
  PIN_INT4_IRQn                     = 4,    /*!<   4  PIN_INT4                         */
  PIN_INT5_IRQn                     = 5,    /*!<   5  PIN_INT5                         */
  PIN_INT6_IRQn                     = 6,    /*!<   6  PIN_INT6                         */
  PIN_INT7_IRQn                     = 7,    /*!<   7  PIN_INT7                         */
  GINT0_IRQn                        = 8,    /*!<   8  GINT0                            */
  GINT1_IRQn                        = 9,    /*!<   9  GINT1                            */
  Reserved0_IRQn                    = 10,   /*!<  10  Reserved Interrupt               */
  Reserved1_IRQn                    = 11,   /*!<  11  Reserved Interrupt               */
  RIT_IRQn                          = 12,   /*!<  12  Repetitive Interrupt Timer       */
  Reserved2_IRQn                    = 13,   /*!<  13  Reserved Interrupt               */
  SSP1_IRQn                         = 14,   /*!<  14  SSP1                             */
  I2C_IRQn                          = 15,   /*!<  15  I2C                              */
  CT16B0_IRQn                       = 16,   /*!<  16  CT16B0                           */
  CT16B1_IRQn                       = 17,   /*!<  17  CT16B1                           */
  CT32B0_IRQn                       = 18,   /*!<  18  CT32B0                           */
  CT32B1_IRQn                       = 19,   /*!<  19  CT32B1                           */
  SSP0_IRQn                         = 20,   /*!<  20  SSP0                             */
  USART_IRQn                        = 21,   /*!<  21  USART                            */
  USB_IRQ_IRQn                      = 22,   /*!<  22  USB_IRQ                          */
  USB_FIQ_IRQn                      = 23,   /*!<  23  USB_FIQ                          */
  ADC_IRQn                          = 24,   /*!<  24  ADC                              */
  WDT_IRQn                          = 25,   /*!<  25  WDT                              */
  BOD_IRQn                          = 26,   /*!<  26  BOD                              */
  FMC_IRQn                          = 27,   /*!<  27  FMC                              */
  Reserved3_IRQn                    = 28,   /*!<  28  Reserved Interrupt               */
  Reserved4_IRQn                    = 29,   /*!<  29  Reserved Interrupt               */
  USBWAKEUP_IRQn                    = 30,   /*!<  30  USBWAKEUP                        */
  Reserved5_IRQn                    = 31,   /*!<  31  Reserved Interrupt               */
} IRQn_Type;


/** @addtogroup Configuration_of_CMSIS
  * @{
  */

/* Processor and Core Peripheral Section */ /* Configuration of the Cortex-M3 Processor and Core Peripherals */

#define __CM3_REV              0x0000       /*!< Cortex-M3 Core Revision               */
#define __MPU_PRESENT             0         /*!< MPU present or not                    */
#define __NVIC_PRIO_BITS          3         /*!< Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig    0         /*!< Set to 1 if different SysTick Config is used */
/** @} */ /* End of group Configuration_of_CMSIS */

#include <core_cm3.h>                       /*!< Cortex-M3 processor and core peripherals */
#include "system_LPC13Uxx.h"                /*!< LPC13Uxx System                          */

/** @addtogroup Device_Peripheral_Registers
  * @{
  */


// ------------------------------------------------------------------------------------------------
// -----                                          I2C                                         -----
// ------------------------------------------------------------------------------------------------



typedef struct {                            /*!< (@ 0x40000000) I2C Structure          */
  __IO uint32_t CONSET;                     /*!< (@ 0x40000000) I2C Control Set Register. When a one is written to a bit of this register, the corresponding bit in the I2C control register is set. Writing a zero has no effect on the corresponding bit in the I2C control register. */
  __I  uint32_t STAT;                       /*!< (@ 0x40000004) I2C Status Register. During I2C operation, this register provides detailed status codes that allow software to determine the next action needed. */
  __IO uint32_t DAT;                        /*!< (@ 0x40000008) I2C Data Register. During master or slave transmit mode, data to be transmitted is written to this register. During master or slave receive mode, data that has been received may be read from this register. */
  __IO uint32_t ADR0;                       /*!< (@ 0x4000000C) I2C Slave Address Register 0. Contains the 7-bit slave address for operation of the I2C interface in slave mode, and is not used in master mode. The least significant bit determines whether a slave responds to the General Call address. */
  __IO uint32_t SCLH;                       /*!< (@ 0x40000010) SCH Duty Cycle Register High Half Word. Determines the high time of the I2C clock. */
  __IO uint32_t SCLL;                       /*!< (@ 0x40000014) SCL Duty Cycle Register Low Half Word. Determines the low time of the I2C clock. I2nSCLL and I2nSCLH together determine the clock frequency generated by an I2C master and certain times used in slave mode. */
  __O  uint32_t CONCLR;                     /*!< (@ 0x40000018) I2C Control Clear Register. When a one is written to a bit of this register, the corresponding bit in the I2C control register is cleared. Writing a zero has no effect on the corresponding bit in the I2C control register. */
  __IO uint32_t MMCTRL;                     /*!< (@ 0x4000001C) Monitor mode control register. */
  union{
  __IO uint32_t ADR[3];                     /*!< (@ 0x40000020) I2C Slave Address Register. Contains the 7-bit slave address for operation of the I2C interface in slave mode, and is not used in master mode. The least significant bit determines whether a slave responds to the General Call address. */
  struct{
  __IO uint32_t ADR1;
  __IO uint32_t ADR2;
  __IO uint32_t ADR3;
  };
  };
  __I  uint32_t DATA_BUFFER;                /*!< (@ 0x4000002C) Data buffer register. The contents of the 8 MSBs of the I2DAT shift register will be transferred to the DATA_BUFFER automatically after every nine bits (8 bits of data plus ACK or NACK) has been received on the bus. */
  union{
  __IO uint32_t MASK[4];                    /*!< (@ 0x40000030) I2C Slave address mask register. This mask register is associated with I2ADR0 to determine an address match. The mask register has no effect when comparing to the General Call address (0000000). */
  struct{
  __IO uint32_t MASK0;
  __IO uint32_t MASK1;
  __IO uint32_t MASK2;
  __IO uint32_t MASK3;
  };
  };
} LPC_I2C_Type;


// ------------------------------------------------------------------------------------------------
// -----                                         WWDT                                         -----
// ------------------------------------------------------------------------------------------------


typedef struct {                            /*!< (@ 0x40004000) WWDT Structure         */
  __IO uint32_t MOD;                        /*!< (@ 0x40004000) Watchdog mode register. This register contains the basic mode and status of the Watchdog Timer. */
  __IO uint32_t TC;                         /*!< (@ 0x40004004) Watchdog timer constant register. This 24-bit register determines the time-out value. */
  __O  uint32_t FEED;                       /*!< (@ 0x40004008) Watchdog feed sequence register. Writing 0xAA followed by 0x55 to this register reloads the Watchdog timer with the value contained in WDTC. */
  __I  uint32_t TV;                         /*!< (@ 0x4000400C) Watchdog timer value register. This 24-bit register reads out the current value of the Watchdog timer. */
  __IO uint32_t CLKSEL;                     /*!< (@ 0x40004010) Watchdog clock select register. */
  __IO uint32_t WARNINT;                    /*!< (@ 0x40004014) Watchdog Warning Interrupt compare value. */
  __IO uint32_t WINDOW;                     /*!< (@ 0x40004018) Watchdog Window compare value. */
} LPC_WWDT_Type;


// ------------------------------------------------------------------------------------------------
// -----                                         USART                                        -----
// ------------------------------------------------------------------------------------------------


typedef struct {                            /*!< (@ 0x40008000) USART Structure        */
  
  union {
    __IO uint32_t DLL;                      /*!< (@ 0x40008000) Divisor Latch LSB. Least significant byte of the baud rate divisor value. The full divisor is used to generate a baud rate from the fractional rate divider. (DLAB=1) */
    __O  uint32_t THR;                      /*!< (@ 0x40008000) Transmit Holding Register. The next character to be transmitted is written here. (DLAB=0) */
    __I  uint32_t RBR;                      /*!< (@ 0x40008000) Receiver Buffer Register. Contains the next received character to be read. (DLAB=0) */
  };
  
  union {
    __IO uint32_t IER;                      /*!< (@ 0x40008004) Interrupt Enable Register. Contains individual interrupt enable bits for the 7 potential USART interrupts. (DLAB=0) */
    __IO uint32_t DLM;                      /*!< (@ 0x40008004) Divisor Latch MSB. Most significant byte of the baud rate divisor value. The full divisor is used to generate a baud rate from the fractional rate divider. (DLAB=1) */
  };
  
  union {
    __O  uint32_t FCR;                      /*!< (@ 0x40008008) FIFO Control Register. Controls USART FIFO usage and modes. */
    __I  uint32_t IIR;                      /*!< (@ 0x40008008) Interrupt ID Register. Identifies which interrupt(s) are pending. */
  };
  __IO uint32_t LCR;                        /*!< (@ 0x4000800C) Line Control Register. Contains controls for frame formatting and break generation. */
  __IO uint32_t MCR;                        /*!< (@ 0x40008010) Modem Control Register. */
  __I  uint32_t LSR;                        /*!< (@ 0x40008014) Line Status Register. Contains flags for transmit and receive status, including line errors. */
  __I  uint32_t MSR;                        /*!< (@ 0x40008018) Modem Status Register. */
  __IO uint32_t SCR;                        /*!< (@ 0x4000801C) Scratch Pad Register. Eight-bit temporary storage for software. */
  __IO uint32_t ACR;                        /*!< (@ 0x40008020) Auto-baud Control Register. Contains controls for the auto-baud feature. */
  __IO uint32_t ICR;                        /*!< (@ 0x40008024) IrDA Control Register. Enables and configures the IrDA (remote control) mode. */
  __IO uint32_t FDR;                        /*!< (@ 0x40008028) Fractional Divider Register. Generates a clock input for the baud rate divider. */
  __IO uint32_t OSR;                        /*!< (@ 0x4000802C) Oversampling Register. Controls the degree of oversampling during each bit time. */
  __IO uint32_t TER;                        /*!< (@ 0x40008030) Transmit Enable Register. Turns off USART transmitter for use with software flow control. */
  __I  uint32_t RESERVED0[3];
  __IO uint32_t HDEN;                       /*!< (@ 0x40008040) Half duplex enable register. */
  __I  uint32_t RESERVED1;
  __IO uint32_t SCICTRL;                    /*!< (@ 0x40008048) Smart Card Interface Control register. Enables and configures the Smart Card Interface feature. */
  __IO uint32_t RS485CTRL;                  /*!< (@ 0x4000804C) RS-485/EIA-485 Control. Contains controls to configure various aspects of RS-485/EIA-485 modes. */
  __IO uint32_t RS485ADRMATCH;              /*!< (@ 0x40008050) RS-485/EIA-485 address match. Contains the address match value for RS-485/EIA-485 mode. */
  __IO uint32_t RS485DLY;                   /*!< (@ 0x40008054) RS-485/EIA-485 direction control delay. */
  __IO uint32_t SYNCCTRL;                   /*!< (@ 0x40008058) Synchronous mode control register. */
} LPC_USART_Type;


// ------------------------------------------------------------------------------------------------
// -----                                        CT16B0                                        -----
// ------------------------------------------------------------------------------------------------

typedef struct {                            /*!< (@ 0x4000C000) LPC_CTxxBx_Type Structure       */
  __IO uint32_t IR;                         /*!< (@ 0x4000C000) Interrupt Register. The IR can be written to clear interrupts. The IR can be read to identify which of eight possible interrupt sources are pending. */
  __IO uint32_t TCR;                        /*!< (@ 0x4000C004) Timer Control Register. The TCR is used to control the Timer Counter functions. The Timer Counter can be disabled or reset through the TCR. */
  __IO uint32_t TC;                         /*!< (@ 0x4000C008) Timer Counter. The 16-bit TC is incremented every PR+1 cycles of PCLK. The TC is controlled through the TCR. */
  __IO uint32_t PR;                         /*!< (@ 0x4000C00C) Prescale Register. When the Prescale Counter (below) is equal to this value, the next clock increments the TC and clears the PC. */
  __IO uint32_t PC;                         /*!< (@ 0x4000C010) Prescale Counter. The 16-bit PC is a counter which is incremented to the value stored in PR. When the value in PR is reached, the TC is incremented and the PC is cleared. The PC is observable and controllable through the bus interface. */
  __IO uint32_t MCR;                        /*!< (@ 0x4000C014) Match Control Register. The MCR is used to control if an interrupt is generated and if the TC is reset when a Match occurs. */
  union {
  __IO uint32_t MR[4];                      /*!< (@ 0x4000C018) Match Register. MR can be enabled through the MCR to reset the TC, stop both the TC and PC, and/or generate an interrupt every time MR matches the TC. */
  struct{
  __IO uint32_t MR0;                        /*!< (@ 0x4000C018) Match Register. MR0 */
  __IO uint32_t MR1;                        /*!< (@ 0x4000C01C) Match Register. MR1 */
  __IO uint32_t MR2;                        /*!< (@ 0x4000C020) Match Register. MR2 */
  __IO uint32_t MR3;                        /*!< (@ 0x4000C024) Match Register. MR3 */
  };
  };
  __IO uint32_t CCR;                        /*!< (@ 0x4000C028) Capture Control Register. The CCR controls which edges of the capture inputs are used to load the Capture Registers and whether or not an interrupt is generated when a capture takes place. */
  union{
  __I  uint32_t CR[4];                      /*!< (@ 0x4000C02C) Capture Register. CR is loaded with the value of TC when there is an event on the CT16B0_CAP input. */
    struct{
  __I  uint32_t CR0;                        /*!< (@ 0x4000C02C) Capture Register. CR 0 */
  __I  uint32_t CR1;                        /*!< (@ 0x4000C030) Capture Register. CR 1 */
  __I  uint32_t CR2;                        /*!< (@ 0x4000C034) Capture Register. CR 2 */
  __I  uint32_t CR3;                        /*!< (@ 0x4000C038) Capture Register. CR 3 */
  };
  };
  __IO uint32_t EMR;                        /*!< (@ 0x4000C03C) External Match Register. The EMR controls the match function and the external match pins  */
  __I  uint32_t RESERVED0[12];
  __IO uint32_t CTCR;                       /*!< (@ 0x4000C070) Count Control Register. The CTCR selects between Timer and Counter mode, and in Counter mode selects the signal and edge(s) for counting. */
  __IO uint32_t PWMC;                       /*!< (@ 0x4000C074) PWM Control Register. The PWMCON enables PWM mode for the external match pins CT16B0_MAT[1:0] and CT16B1_MAT[1:0]. */
} LPC_CTxxBx_Type;

typedef struct {                            /*!< (@ 0x4000C000) CT16B0 Structure       */
  __IO uint32_t IR;                         /*!< (@ 0x4000C000) Interrupt Register. The IR can be written to clear interrupts. The IR can be read to identify which of eight possible interrupt sources are pending. */
  __IO uint32_t TCR;                        /*!< (@ 0x4000C004) Timer Control Register. The TCR is used to control the Timer Counter functions. The Timer Counter can be disabled or reset through the TCR. */
  __IO uint32_t TC;                         /*!< (@ 0x4000C008) Timer Counter. The 16-bit TC is incremented every PR+1 cycles of PCLK. The TC is controlled through the TCR. */
  __IO uint32_t PR;                         /*!< (@ 0x4000C00C) Prescale Register. When the Prescale Counter (below) is equal to this value, the next clock increments the TC and clears the PC. */
  __IO uint32_t PC;                         /*!< (@ 0x4000C010) Prescale Counter. The 16-bit PC is a counter which is incremented to the value stored in PR. When the value in PR is reached, the TC is incremented and the PC is cleared. The PC is observable and controllable through the bus interface. */
  __IO uint32_t MCR;                        /*!< (@ 0x4000C014) Match Control Register. The MCR is used to control if an interrupt is generated and if the TC is reset when a Match occurs. */
  union {
  __IO uint32_t MR[4];                      /*!< (@ 0x4000C018) Match Register. MR can be enabled through the MCR to reset the TC, stop both the TC and PC, and/or generate an interrupt every time MR matches the TC. */
  struct{
  __IO uint32_t MR0;                        /*!< (@ 0x4000C018) Match Register. MR0 */
  __IO uint32_t MR1;                        /*!< (@ 0x4000C01C) Match Register. MR1 */
  __IO uint32_t MR2;                        /*!< (@ 0x4000C020) Match Register. MR2 */
  __IO uint32_t MR3;                        /*!< (@ 0x4000C024) Match Register. MR3 */
  };
  };
  __IO uint32_t CCR;                        /*!< (@ 0x4000C028) Capture Control Register. The CCR controls which edges of the capture inputs are used to load the Capture Registers and whether or not an interrupt is generated when a capture takes place. */
  union{
  __I  uint32_t CR[4];                      /*!< (@ 0x4000C02C) Capture Register. CR is loaded with the value of TC when there is an event on the CT16B0_CAP input. */
    struct{
  __I  uint32_t CR0;			            /*!< (@ 0x4000C02C) Capture Register. CR 0 */
  __I  uint32_t CR1;			            /*!< (@ 0x4000C030) Capture Register. CR 1 */
  __I  uint32_t CR2;			            /*!< (@ 0x4000C034) Capture Register. CR 2 */
  __I  uint32_t CR3;			            /*!< (@ 0x4000C038) Capture Register. CR 3 */
  };
  };
  __IO uint32_t EMR;                        /*!< (@ 0x4000C03C) External Match Register. The EMR controls the match function and the external match pins  */
  __I  uint32_t RESERVED0[12];
  __IO uint32_t CTCR;                       /*!< (@ 0x4000C070) Count Control Register. The CTCR selects between Timer and Counter mode, and in Counter mode selects the signal and edge(s) for counting. */
  __IO uint32_t PWMC;                       /*!< (@ 0x4000C074) PWM Control Register. The PWMCON enables PWM mode for the external match pins CT16B0_MAT[1:0] and CT16B1_MAT[1:0]. */
} LPC_CT16B0_Type;


// ------------------------------------------------------------------------------------------------
// -----                                        CT16B1                                        -----
// ------------------------------------------------------------------------------------------------

typedef struct {                            /*!< (@ 0x40010000) CT16B1 Structure       */
  __IO uint32_t IR;                         /*!< (@ 0x40010000) Interrupt Register. The IR can be written to clear interrupts. The IR can be read to identify which of eight possible interrupt sources are pending. */
  __IO uint32_t TCR;                        /*!< (@ 0x40010004) Timer Control Register. The TCR is used to control the Timer Counter functions. The Timer Counter can be disabled or reset through the TCR. */
  __IO uint32_t TC;                         /*!< (@ 0x40010008) Timer Counter. The 16-bit TC is incremented every PR+1 cycles of PCLK. The TC is controlled through the TCR. */
  __IO uint32_t PR;                         /*!< (@ 0x4001000C) Prescale Register. When the Prescale Counter (below) is equal to this value, the next clock increments the TC and clears the PC. */
  __IO uint32_t PC;                         /*!< (@ 0x40010010) Prescale Counter. The 16-bit PC is a counter which is incremented to the value stored in PR. When the value in PR is reached, the TC is incremented and the PC is cleared. The PC is observable and controllable through the bus interface. */
  __IO uint32_t MCR;                        /*!< (@ 0x40010014) Match Control Register. The MCR is used to control if an interrupt is generated and if the TC is reset when a Match occurs. */
  union {
  __IO uint32_t MR[4];                      /*!< (@ 0x40010018) Match Register. MR can be enabled through the MCR to reset the TC, stop both the TC and PC, and/or generate an interrupt every time MR matches the TC. */
  struct{
  __IO uint32_t MR0;                        /*!< (@ 0x40010018) Match Register. MR0 */
  __IO uint32_t MR1;                        /*!< (@ 0x4001001C) Match Register. MR1 */
  __IO uint32_t MR2;                        /*!< (@ 0x40010020) Match Register. MR2 */
  __IO uint32_t MR3;                        /*!< (@ 0x40010024) Match Register. MR3 */
  };
  };
  __IO uint32_t CCR;                        /*!< (@ 0x40010028) Capture Control Register. The CCR controls which edges of the capture inputs are used to load the Capture Registers and whether or not an interrupt is generated when a capture takes place. */
  union{
  __I  uint32_t CR[4];                      /*!< (@ 0x4001002C) Capture Register. CR is loaded with the value of TC when there is an event on the CT16B0_CAP input. */
    struct{
  __I  uint32_t CR0;			            /*!< (@ 0x4001002C) Capture Register. CR 0 */
  __I  uint32_t CR1;			            /*!< (@ 0x40010030) Capture Register. CR 1 */
  __I  uint32_t CR2;			            /*!< (@ 0x40010034) Capture Register. CR 2 */
  __I  uint32_t CR3;			            /*!< (@ 0x40010038) Capture Register. CR 3 */
  };
  };
  __IO uint32_t EMR;                        /*!< (@ 0x4001003C) External Match Register. The EMR controls the match function and the external match pins  */
  __I  uint32_t RESERVED0[12];
  __IO uint32_t CTCR;                       /*!< (@ 0x40010070) Count Control Register. The CTCR selects between Timer and Counter mode, and in Counter mode selects the signal and edge(s) for counting. */
  __IO uint32_t PWMC;                       /*!< (@ 0x40010074) PWM Control Register. The PWMCON enables PWM mode for the external match pins CT16B0_MAT[1:0] and CT16B1_MAT[1:0]. */
} LPC_CT16B1_Type;


// ------------------------------------------------------------------------------------------------
// -----                                        CT32B0                                        -----
// ------------------------------------------------------------------------------------------------
typedef struct {                            /*!< (@ 0x40014000) CT32B0 Structure       */
  __IO uint32_t IR;                         /*!< (@ 0x40014000) Interrupt Register. The IR can be written to clear interrupts. The IR can be read to identify which of eight possible interrupt sources are pending. */
  __IO uint32_t TCR;                        /*!< (@ 0x40014004) Timer Control Register. The TCR is used to control the Timer Counter functions. The Timer Counter can be disabled or reset through the TCR. */
  __IO uint32_t TC;                         /*!< (@ 0x40014008) Timer Counter. The 32-bit TC is incremented every PR+1 cycles of PCLK. The TC is controlled through the TCR. */
  __IO uint32_t PR;                         /*!< (@ 0x4001400C) Prescale Register. When the Prescale Counter (below) is equal to this value, the next clock increments the TC and clears the PC. */
  __IO uint32_t PC;                         /*!< (@ 0x40014010) Prescale Counter. The 32-bit PC is a counter which is incremented to the value stored in PR. When the value in PR is reached, the TC is incremented and the PC is cleared. The PC is observable and controllable through the bus interface. */
  __IO uint32_t MCR;                        /*!< (@ 0x40014014) Match Control Register. The MCR is used to control if an interrupt is generated and if the TC is reset when a Match occurs. */
  union {
  __IO uint32_t MR[4];                      /*!< (@ 0x40014018) Match Register. MR can be enabled through the MCR to reset the TC, stop both the TC and PC, and/or generate an interrupt every time MR matches the TC. */
  struct{
  __IO uint32_t MR0;                        /*!< (@ 0x40014018) Match Register. MR0 */
  __IO uint32_t MR1;                        /*!< (@ 0x4001401C) Match Register. MR1 */
  __IO uint32_t MR2;                        /*!< (@ 0x40014020) Match Register. MR2 */
  __IO uint32_t MR3;                        /*!< (@ 0x40014024) Match Register. MR3 */
  };
  };
  __IO uint32_t CCR;                        /*!< (@ 0x40014028) Capture Control Register. The CCR controls which edges of the capture inputs are used to load the Capture Registers and whether or not an interrupt is generated when a capture takes place. */
  union{
  __I  uint32_t CR[4];                      /*!< (@ 0x4001402C) Capture Register. CR is loaded with the value of TC when there is an event on the CT32B_CAP0 input. */
    struct{
  __I  uint32_t CR0;			            /*!< (@ 0x4001402C) Capture Register. CR 0 */
  __I  uint32_t CR1;			            /*!< (@ 0x40014030) Capture Register. CR 1 */
  __I  uint32_t CR2;			            /*!< (@ 0x40014034) Capture Register. CR 2 */
  __I  uint32_t CR3;			            /*!< (@ 0x40014038) Capture Register. CR 3 */
  };
  };
  __IO uint32_t EMR;                        /*!< (@ 0x4001403C) External Match Register. The EMR controls the match function and the external match pins CT32Bn_MAT[3:0]. */
  __I  uint32_t RESERVED0[12];
  __IO uint32_t CTCR;                       /*!< (@ 0x40014070) Count Control Register. The CTCR selects between Timer and Counter mode, and in Counter mode selects the signal and edge(s) for counting. */
  __IO uint32_t PWMC;                       /*!< (@ 0x40014074) PWM Control Register. The PWMCON enables PWM mode for the external match pins CT32Bn_MAT[3:0]. */
} LPC_CT32B0_Type;


// ------------------------------------------------------------------------------------------------
// -----                                        CT32B1                                        -----
// ------------------------------------------------------------------------------------------------
typedef struct {                            /*!< (@ 0x40018000) CT32B1 Structure       */
  __IO uint32_t IR;                         /*!< (@ 0x40018000) Interrupt Register. The IR can be written to clear interrupts. The IR can be read to identify which of eight possible interrupt sources are pending. */
  __IO uint32_t TCR;                        /*!< (@ 0x40018004) Timer Control Register. The TCR is used to control the Timer Counter functions. The Timer Counter can be disabled or reset through the TCR. */
  __IO uint32_t TC;                         /*!< (@ 0x40018008) Timer Counter. The 32-bit TC is incremented every PR+1 cycles of PCLK. The TC is controlled through the TCR. */
  __IO uint32_t PR;                         /*!< (@ 0x4001800C) Prescale Register. When the Prescale Counter (below) is equal to this value, the next clock increments the TC and clears the PC. */
  __IO uint32_t PC;                         /*!< (@ 0x40018010) Prescale Counter. The 32-bit PC is a counter which is incremented to the value stored in PR. When the value in PR is reached, the TC is incremented and the PC is cleared. The PC is observable and controllable through the bus interface. */
  __IO uint32_t MCR;                        /*!< (@ 0x40018014) Match Control Register. The MCR is used to control if an interrupt is generated and if the TC is reset when a Match occurs. */
  union {
  __IO uint32_t MR[4];                      /*!< (@ 0x40018018) Match Register. MR can be enabled through the MCR to reset the TC, stop both the TC and PC, and/or generate an interrupt every time MR matches the TC. */
  struct{
  __IO uint32_t MR0;                        /*!< (@ 0x40018018) Match Register. MR0 */
  __IO uint32_t MR1;                        /*!< (@ 0x4001801C) Match Register. MR1 */
  __IO uint32_t MR2;                        /*!< (@ 0x40018020) Match Register. MR2 */
  __IO uint32_t MR3;                        /*!< (@ 0x40018024) Match Register. MR3 */
  };
  };
  __IO uint32_t CCR;                        /*!< (@ 0x40018028) Capture Control Register. The CCR controls which edges of the capture inputs are used to load the Capture Registers and whether or not an interrupt is generated when a capture takes place. */
  union{
  __I  uint32_t CR[4];                      /*!< (@ 0x4001802C) Capture Register. CR is loaded with the value of TC when there is an event on the CT32B_CAP0 input. */
    struct{
  __I  uint32_t CR0;			            /*!< (@ 0x4001802C) Capture Register. CR 0 */
  __I  uint32_t CR1;			            /*!< (@ 0x40018030) Capture Register. CR 1 */
  __I  uint32_t CR2;			            /*!< (@ 0x40018034) Capture Register. CR 2 */
  __I  uint32_t CR3;			            /*!< (@ 0x40018038) Capture Register. CR 3 */
  };
  };
  __IO uint32_t EMR;                        /*!< (@ 0x4001803C) External Match Register. The EMR controls the match function and the external match pins CT32Bn_MAT[3:0]. */
  __I  uint32_t RESERVED0[12];
  __IO uint32_t CTCR;                       /*!< (@ 0x40018070) Count Control Register. The CTCR selects between Timer and Counter mode, and in Counter mode selects the signal and edge(s) for counting. */
  __IO uint32_t PWMC;                       /*!< (@ 0x40018074) PWM Control Register. The PWMCON enables PWM mode for the external match pins CT32Bn_MAT[3:0]. */
} LPC_CT32B1_Type;


// ------------------------------------------------------------------------------------------------
// -----                                          ADC                                         -----
// ------------------------------------------------------------------------------------------------
typedef struct {                            /*!< (@ 0x4001C000) ADC Structure          */
  __IO uint32_t CR;                         /*!< (@ 0x4001C000) A/D Control Register. The CR register must be written to select the operating mode before A/D conversion can occur. */
  __IO uint32_t GDR;                        /*!< (@ 0x4001C004) A/D Global Data Register. Contains the result of the most recent A/D conversion. */
  __I  uint32_t RESERVED0[1];
  __IO uint32_t INTEN;                      /*!< (@ 0x4001C00C) A/D Interrupt Enable Register. This register contains enable bits that allow the DONE flag of each A/D channel to be included or excluded from contributing to the generation of an A/D interrupt. */
  union{
  __I  uint32_t DR[8];                      /*!< (@ 0x4001C010) A/D Channel Data Register*/
    struct{
  __I  uint32_t DR0;                      	/*!< (@ 0x4001C010) A/D Channel Data Register 0*/
  __I  uint32_t DR1;                      	/*!< (@ 0x4001C014) A/D Channel Data Register 1*/
  __I  uint32_t DR2;                      	/*!< (@ 0x4001C018) A/D Channel Data Register 2*/
  __I  uint32_t DR3;                      	/*!< (@ 0x4001C01C) A/D Channel Data Register 3*/
  __I  uint32_t DR4;                      	/*!< (@ 0x4001C020) A/D Channel Data Register 4*/
  __I  uint32_t DR5;                      	/*!< (@ 0x4001C024) A/D Channel Data Register 5*/
  __I  uint32_t DR6;                      	/*!< (@ 0x4001C028) A/D Channel Data Register 6*/
  __I  uint32_t DR7;                      	/*!< (@ 0x4001C02C) A/D Channel Data Register 7*/
  };
  };
  __I  uint32_t STAT;                       /*!< (@ 0x4001C030) A/D Status Register. This register contains DONE and OVERRUN flags for all of the A/D channels, as well as the A/D interrupt flag. */
} LPC_ADC_Type;


// ------------------------------------------------------------------------------------------------
// -----                                          PMU                                         -----
// ------------------------------------------------------------------------------------------------

typedef struct {                            /*!< (@ 0x40038000) PMU Structure          */
  __IO uint32_t PCON;                       /*!< (@ 0x40038000) Power control register */
  union{
  __IO uint32_t GPREG[4];                   /*!< (@ 0x40038004) General purpose register 0 */
  struct{
  __IO uint32_t GPREG0;                   	/*!< (@ 0x40038004) General purpose register 0 */
  __IO uint32_t GPREG1;                   	/*!< (@ 0x40038008) General purpose register 1 */
  __IO uint32_t GPREG2;                   	/*!< (@ 0x4003800C) General purpose register 2 */
  __IO uint32_t GPREG3;                   	/*!< (@ 0x40038010) General purpose register 3 */
  };
  };
  __IO uint32_t GPREG4;                     /*!< (@ 0x40038014) General purpose register 4 */
} LPC_PMU_Type;


// ------------------------------------------------------------------------------------------------
// -----                                       FLASHCTRL                                      -----
// ------------------------------------------------------------------------------------------------

typedef struct {                            /*!< (@ 0x4003C000) FLASHCTRL Structure    */
  __I  uint32_t RESERVED0[4];
  __IO uint32_t FLASHCFG;                   /*!< (@ 0x4003C010) Flash memory access time configuration register */
  __I  uint32_t RESERVED1[3];
  __IO uint32_t FMSSTART;                   /*!< (@ 0x4003C020) Signature start address register */
  __IO uint32_t FMSSTOP;                    /*!< (@ 0x4003C024) Signature stop-address register */
  __I  uint32_t RESERVED2[1];
  __I  uint32_t FMSW0;                      /*!< (@ 0x4003C02C) Word 0 [31:0]          */
  __I  uint32_t FMSW1;                      /*!< (@ 0x4003C030) Word 1 [63:32]         */
  __I  uint32_t FMSW2;                      /*!< (@ 0x4003C034) Word 2 [95:64]         */
  __I  uint32_t FMSW3;                      /*!< (@ 0x4003C038) Word 3 [127:96]        */
  __I  uint32_t RESERVED3[1001];
  __I  uint32_t FMSTAT;                     /*!< (@ 0x4003CFE0) Signature generation status register */
  __I  uint32_t RESERVED4[1];
  __O  uint32_t FMSTATCLR;                  /*!< (@ 0x4003CFE8) Signature generation status clear register */
} LPC_FLASHCTRL_Type;


// ------------------------------------------------------------------------------------------------
// -----                                         SSP                                          -----
// ------------------------------------------------------------------------------------------------
typedef struct {                            /*!< (@ 0x40040000) SSP0 Structure         */
  __IO uint32_t CR0;                        /*!< (@ 0x40040000) Control Register 0. Selects the serial clock rate, bus type, and data size. */
  __IO uint32_t CR1;                        /*!< (@ 0x40040004) Control Register 1. Selects master/slave and other modes. */
  __IO uint32_t DR;                         /*!< (@ 0x40040008) Data Register. Writes fill the transmit FIFO, and reads empty the receive FIFO. */
  __I  uint32_t SR;                         /*!< (@ 0x4004000C) Status Register        */
  __IO uint32_t CPSR;                       /*!< (@ 0x40040010) Clock Prescale Register */
  __IO uint32_t IMSC;                       /*!< (@ 0x40040014) Interrupt Mask Set and Clear Register */
  __I  uint32_t RIS;                        /*!< (@ 0x40040018) Raw Interrupt Status Register */
  __I  uint32_t MIS;                        /*!< (@ 0x4004001C) Masked Interrupt Status Register */
  __O  uint32_t ICR;                        /*!< (@ 0x40040020) SSPICR Interrupt Clear Register */
} LPC_SSPx_Type;


// ------------------------------------------------------------------------------------------------
// -----                                         IOCON                                        -----
// ------------------------------------------------------------------------------------------------
typedef struct {                            /*!< (@ 0x40044000) IOCON Structure        */
  __IO uint32_t RESET_PIO0_0;               /*!< (@ 0x40044000) I/O configuration for pin RESET/PIO0_0 */
  __IO uint32_t PIO0_1;                     /*!< (@ 0x40044004) I/O configuration for pin PIO0_1/CLKOUT/CT32B0_MAT2/USB_FTOGGLE */
  __IO uint32_t PIO0_2;                     /*!< (@ 0x40044008) I/O configuration for pin PIO0_2/SSEL0/CT16B0_CAP0 */
  __IO uint32_t PIO0_3;                     /*!< (@ 0x4004400C) I/O configuration for pin PIO0_3/USB_VBUS */
  __IO uint32_t PIO0_4;                     /*!< (@ 0x40044010) I/O configuration for pin PIO0_4/SCL */
  __IO uint32_t PIO0_5;                     /*!< (@ 0x40044014) I/O configuration for pin PIO0_5/SDA */
  __IO uint32_t PIO0_6;                     /*!< (@ 0x40044018) I/O configuration for pin PIO0_6/USB_CONNECT/SCK0 */
  __IO uint32_t PIO0_7;                     /*!< (@ 0x4004401C) I/O configuration for pin PIO0_7/CTS */
  __IO uint32_t PIO0_8;                     /*!< (@ 0x40044020) I/O configuration for pin PIO0_8/MISO0/CT16B0_MAT0/SWO */
  __IO uint32_t PIO0_9;                     /*!< (@ 0x40044024) I/O configuration for pin PIO0_9/MOSI0/CT16B0_MAT1/TRACECLK */
  __IO uint32_t SWCLK_PIO0_10;              /*!< (@ 0x40044028) I/O configuration for pin SWCLK/PIO0_10/ SCK0/CT16B0_MAT2 */
  __IO uint32_t TDI_PIO0_11;                /*!< (@ 0x4004402C) I/O configuration for pin TDI/PIO0_11/AD0/CT32B0_MAT3 */
  __IO uint32_t TMS_PIO0_12;                /*!< (@ 0x40044030) I/O configuration for pin TMS/PIO0_12/AD1/CT32B1_CAP0 */
  __IO uint32_t TDO_PIO0_13;                /*!< (@ 0x40044034) I/O configuration for pin TDO/PIO0_13/AD2/CT32B1_MAT0 */
  __IO uint32_t TRST_PIO0_14;               /*!< (@ 0x40044038) I/O configuration for pin TRST/PIO0_14/AD3/CT32B1_MAT1 */
  __IO uint32_t SWDIO_PIO0_15;              /*!< (@ 0x4004403C) I/O configuration for pin SWDIO/PIO0_15/AD4/CT32B1_MAT2 */
  __IO uint32_t PIO0_16;                    /*!< (@ 0x40044040) I/O configuration for pin PIO0_16/AD5/CT32B1_MAT3/ WAKEUP */
  __IO uint32_t PIO0_17;                    /*!< (@ 0x40044044) I/O configuration for pin PIO0_17/RTS/CT32B0_CAP0/SCLK */
  __IO uint32_t PIO0_18;                    /*!< (@ 0x40044048) I/O configuration for pin PIO0_18/RXD/CT32B0_MAT0 */
  __IO uint32_t PIO0_19;                    /*!< (@ 0x4004404C) I/O configuration for pin PIO0_19/TXD/CT32B0_MAT1 */
  __IO uint32_t PIO0_20;                    /*!< (@ 0x40044050) I/O configuration for pin PIO0_20/CT16B1_CAP0 */
  __IO uint32_t PIO0_21;                    /*!< (@ 0x40044054) I/O configuration for pin PIO0_21/CT16B1_MAT0/MOSI1 */
  __IO uint32_t PIO0_22;                    /*!< (@ 0x40044058) I/O configuration for pin PIO0_22/AD6/CT16B1_MAT1/MISO1 */
  __IO uint32_t PIO0_23;                    /*!< (@ 0x4004405C) I/O configuration for pin PIO0_23/AD7 */
  __IO uint32_t PIO1_0;                     /*!< (@ 0x40044060) I/O configuration for pin PIO1_0/CT32B1_MAT0 */
  __IO uint32_t PIO1_1;                     /*!< (@ 0x40044064) I/O configuration for pin PIO1_1/CT32B1_MAT1 */
  __IO uint32_t PIO1_2;                     /*!< (@ 0x40044068) I/O configuration for pin PIO1_2/CT32B1_MAT2 */
  __IO uint32_t PIO1_3;                     /*!< (@ 0x4004406C) I/O configuration for pin PIO1_3/CT32B1_MAT3 */
  __IO uint32_t PIO1_4;                     /*!< (@ 0x40044070) I/O configuration for pin PIO1_4/CT32B1_CAP0 */
  __IO uint32_t PIO1_5;                     /*!< (@ 0x40044074) I/O configuration for pin PIO1_5/CT32B1_CAP1 */
  __IO uint32_t PIO1_6;                     /*!< (@ 0x40044078) I/O configuration for pin PIO1_6 */
  __IO uint32_t PIO1_7;                     /*!< (@ 0x4004407C) I/O configuration for pin PIO1_7 */
  __IO uint32_t PIO1_8;                     /*!< (@ 0x40044080) I/O configuration for pin PIO1_8 */
  __IO uint32_t PIO1_9;                     /*!< (@ 0x40044084) I/O configuration for pin PIO1_9 */
  __IO uint32_t PIO1_10;                    /*!< (@ 0x40044088) I/O configuration for pin PIO1_10 */
  __IO uint32_t PIO1_11;                    /*!< (@ 0x4004408C) I/O configuration for pin PIO1_11 */
  __IO uint32_t PIO1_12;                    /*!< (@ 0x40044090) I/O configuration for pin PIO1_12 */
  __IO uint32_t PIO1_13;                    /*!< (@ 0x40044094) I/O configuration for PIO1_13/DTR/CT16B0_MAT0/TXD */
  __IO uint32_t PIO1_14;                    /*!< (@ 0x40044098) I/O configuration for PIO1_14/DSR/CT16B0_MAT1/RXD */
  __IO uint32_t PIO1_15;                    /*!< (@ 0x4004409C) I/O configuration for pin PIO1_15/DCD/ CT16B0_MAT2/SCK1 */
  __IO uint32_t PIO1_16;                    /*!< (@ 0x400440A0) I/O configuration for pin PIO1_16/RI/CT16B0_CAP0 */
  __IO uint32_t PIO1_17;                    /*!< (@ 0x400440A4) I/O configuration for PIO1_17/CT16B0_CAP1/RXD */
  __IO uint32_t PIO1_18;                    /*!< (@ 0x400440A8) I/O configuration for PIO1_18/CT16B1_CAP1/TXD */
  __IO uint32_t PIO1_19;                    /*!< (@ 0x400440AC) I/O configuration for pin PIO1_19/DTR/SSEL1 */
  __IO uint32_t PIO1_20;                    /*!< (@ 0x400440B0) I/O configuration for pin PIO1_20/DSR/SCK1 */
  __IO uint32_t PIO1_21;                    /*!< (@ 0x400440B4) I/O configuration for pin PIO1_21/DCD/MISO1 */
  __IO uint32_t PIO1_22;                    /*!< (@ 0x400440B8) I/O configuration for pin PIO1_22/RI/MOSI1 */
  __IO uint32_t PIO1_23;                    /*!< (@ 0x400440BC) I/O configuration for pin PIO1_23/CT16B1_MAT1/SSEL1 */
  __IO uint32_t PIO1_24;                    /*!< (@ 0x400440C0) I/O configuration for pin PIO1_24/ CT32B0_MAT0 */
  __IO uint32_t PIO1_25;                    /*!< (@ 0x400440C4) I/O configuration for pin PIO1_25/CT32B0_MAT1 */
  __IO uint32_t PIO1_26;                    /*!< (@ 0x400440C8) I/O configuration for pin PIO1_26/CT32B0_MAT2/ RXD */
  __IO uint32_t PIO1_27;                    /*!< (@ 0x400440CC) I/O configuration for pin PIO1_27/CT32B0_MAT3/ TXD */
  __IO uint32_t PIO1_28;                    /*!< (@ 0x400440D0) I/O configuration for pin PIO1_28/CT32B0_CAP0/ SCLK */
  __IO uint32_t PIO1_29;                    /*!< (@ 0x400440D4) I/O configuration for pin PIO1_29/SCK0/ CT32B0_CAP1 */
  __IO uint32_t PIO1_30;                    /*!< (@ 0x400440D8) I/O configuration for pin PIO1_30 */
  __IO uint32_t PIO1_31;                    /*!< (@ 0x400440DC) I/O configuration for pin PIO1_31 */
} LPC_IOCON_Type;


// ------------------------------------------------------------------------------------------------
// -----                                        SYSCON                                        -----
// ------------------------------------------------------------------------------------------------

typedef struct {                            /*!< (@ 0x40048000) SYSCON Structure       */
  __IO uint32_t SYSMEMREMAP;                /*!< (@ 0x40048000) System memory remap    */
  __IO uint32_t PRESETCTRL;                 /*!< (@ 0x40048004) Peripheral reset control */
  __IO uint32_t SYSPLLCTRL;                 /*!< (@ 0x40048008) System PLL control     */
  __I  uint32_t SYSPLLSTAT;                 /*!< (@ 0x4004800C) System PLL status      */
  __IO uint32_t USBPLLCTRL;                 /*!< (@ 0x40048010) USB PLL control        */
  __I  uint32_t USBPLLSTAT;                 /*!< (@ 0x40048014) USB PLL status         */
  __I  uint32_t RESERVED0[2];
  __IO uint32_t SYSOSCCTRL;                 /*!< (@ 0x40048020) System oscillator control */
  __IO uint32_t WDTOSCCTRL;                 /*!< (@ 0x40048024) Watchdog oscillator control */
  __I  uint32_t RESERVED1[2];
  __IO uint32_t SYSRSTSTAT;                 /*!< (@ 0x40048030) System reset status register */
  __I  uint32_t RESERVED2[3];
  __IO uint32_t SYSPLLCLKSEL;               /*!< (@ 0x40048040) System PLL clock source select */
  __I  uint32_t RESERVED3;
  __IO uint32_t USBPLLCLKSEL;               /*!< (@ 0x40048048) USB PLL clock source select */
  __I  uint32_t RESERVED4[9];
  __IO uint32_t MAINCLKSEL;                 /*!< (@ 0x40048070) Main clock source select */
  __I  uint32_t RESERVED5;
  __IO uint32_t SYSAHBCLKDIV;               /*!< (@ 0x40048078) System clock divider   */
  __I  uint32_t RESERVED6;
  __IO uint32_t SYSAHBCLKCTRL;              /*!< (@ 0x40048080) System clock control   */
  __I  uint32_t RESERVED7[4];
  __IO uint32_t SSP0CLKDIV;                 /*!< (@ 0x40048094) SSP0 clock divider     */
  __IO uint32_t UARTCLKDIV;                 /*!< (@ 0x40048098) UART clock divider     */
  __IO uint32_t SSP1CLKDIV;                 /*!< (@ 0x4004809C) SSP1 clock divider     */
  __I  uint32_t RESERVED8[3];
  __IO uint32_t TRACECLKDIV;                /*!< (@ 0x400480AC) ARM trace clock divider */
  __IO uint32_t SYSTICKCLKDIV;              /*!< (@ 0x400480B0) SYSTICK clock divder   */
  __I  uint32_t RESERVED9[3];
  __IO uint32_t USBCLKSEL;                  /*!< (@ 0x400480C0) USB clock source select */
  __I  uint32_t RESERVED10;
  __IO uint32_t USBCLKDIV;                  /*!< (@ 0x400480C8) USB clock source divider */
  __I  uint32_t RESERVED11[5];
  __IO uint32_t CLKOUTSEL;                  /*!< (@ 0x400480E0) CLKOUT clock source select */
  __I  uint32_t RESERVED12;
  __IO uint32_t CLKOUTDIV;                  /*!< (@ 0x400480E8) CLKOUT clock divider   */
  __I  uint32_t RESERVED13[5];
  __I  uint32_t PIOPORCAP0;                 /*!< (@ 0x40048100) POR captured PIO status 0 */
  __I  uint32_t PIOPORCAP1;                 /*!< (@ 0x40048104) POR captured PIO status 1 */
  __I  uint32_t RESERVED14[18];
  __IO uint32_t BODCTRL;                    /*!< (@ 0x40048150) Brown-Out Detect       */
  __IO uint32_t SYSTCKCAL;                  /*!< (@ 0x40048154) System tick counter calibration */
  __I  uint32_t RESERVED15[6];
  __IO uint32_t IRQLATENCY;                 /*!< (@ 0x40048170) IQR delay. Allows trade-off between interrupt latency and determinism. */
  __IO uint32_t NMISRC;                     /*!< (@ 0x40048174) NMI Source Control     */
  __IO uint32_t PINSEL[8];                  /*!< (@ 0x40048178) GPIO Pin Interrupt Select register */
  __IO uint32_t USBCLKCTRL;                 /*!< (@ 0x40048198) USB clock control      */
  __I  uint32_t USBCLKST;                   /*!< (@ 0x4004819C) USB clock status       */
  __I  uint32_t RESERVED16[25];
  __IO uint32_t STARTERP0;                  /*!< (@ 0x40048204) Start logic 0 interrupt wake-up enable register 0 */
  __I  uint32_t RESERVED17[3];
  __IO uint32_t STARTERP1;                  /*!< (@ 0x40048214) Start logic 1 interrupt wake-up enable register 1 */
  __I  uint32_t RESERVED18[6];
  __IO uint32_t PDSLEEPCFG;                 /*!< (@ 0x40048230) Power-down states in deep-sleep mode */
  __IO uint32_t PDAWAKECFG;                 /*!< (@ 0x40048234) Power-down states for wake-up from deep-sleep */
  __IO uint32_t PDRUNCFG;                   /*!< (@ 0x40048238) Power configuration register */
  __I  uint32_t RESERVED19[111];
  __I  uint32_t DEVICE_ID;                  /*!< (@ 0x400483F8) Device ID              */
} LPC_SYSCON_Type;


// ------------------------------------------------------------------------------------------------
// -----                                     GPIO_PIN_INT                                     -----
// ------------------------------------------------------------------------------------------------
typedef struct {                            /*!< (@ 0x4004C000) GPIO_PIN_INT Structure */
  __IO uint32_t ISEL;                       /*!< (@ 0x4004C000) Pin Interrupt Mode register */
  __IO uint32_t IENR;                       /*!< (@ 0x4004C004) Pin Interrupt Enable (Rising) register */
  __O  uint32_t SIENR;                      /*!< (@ 0x4004C008) Set Pin Interrupt Enable (Rising) register */
  __O  uint32_t CIENR;                      /*!< (@ 0x4004C00C) Clear Pin Interrupt Enable (Rising) register */
  __IO uint32_t IENF;                       /*!< (@ 0x4004C010) Pin Interrupt Enable Falling Edge / Active Level register */
  __O  uint32_t SIENF;                      /*!< (@ 0x4004C014) Set Pin Interrupt Enable Falling Edge / Active Level register */
  __O  uint32_t CIENF;                      /*!< (@ 0x4004C018) Clear Pin Interrupt Enable Falling Edge / Active Level address */
  __IO uint32_t RISE;                       /*!< (@ 0x4004C01C) Pin Interrupt Rising Edge register */
  __IO uint32_t FALL;                       /*!< (@ 0x4004C020) Pin Interrupt Falling Edge register */
  __IO uint32_t IST;                        /*!< (@ 0x4004C024) Pin Interrupt Status register */
} LPC_GPIO_PIN_INT_Type;


// ------------------------------------------------------------------------------------------------
// -----                                    GPIO_GROUP_INT0                                   -----
// ------------------------------------------------------------------------------------------------
typedef struct {                            /*!< (@ 0x4005C000) GPIO_GROUP_INT0 Structure */
  __IO uint32_t CTRL;                       /*!< (@ 0x4005C000) GPIO grouped interrupt control register */
  __I  uint32_t RESERVED0[7];
  __IO uint32_t PORT_POL[2];                /*!< (@ 0x4005C020) GPIO grouped interrupt port 0 polarity register */
  __I  uint32_t RESERVED1[6];
  __IO uint32_t PORT_ENA[2];                /*!< (@ 0x4005C040) GPIO grouped interrupt port 0/1 enable register */
} LPC_GPIO_GROUP_INT0_Type;


// ------------------------------------------------------------------------------------------------
// -----                                    GPIO_GROUP_INT1                                   -----
// ------------------------------------------------------------------------------------------------

typedef struct {                            /*!< (@ 0x40060000) GPIO_GROUP_INT1 Structure */
  __IO uint32_t CTRL;                       /*!< (@ 0x40060000) GPIO grouped interrupt control register */
  __I  uint32_t RESERVED0[7];
  __IO uint32_t PORT_POL[2];                /*!< (@ 0x40060020) GPIO grouped interrupt port 0 polarity register */
  __I  uint32_t RESERVED1[6];
  __IO uint32_t PORT_ENA[2];                /*!< (@ 0x40060040) GPIO grouped interrupt port 0/1 enable register */
} LPC_GPIO_GROUP_INT1_Type;


// ------------------------------------------------------------------------------------------------
// -----                          Repetitive Interrupt Timer (RIT)                            -----
// ------------------------------------------------------------------------------------------------

typedef struct {                            /*!< (@ 0x40064000) RITIMER Structure */
  __IO uint32_t COMPVAL;                    /*!< (@ 0x40064000) RITIMER compare register */
  __IO uint32_t MASK;                       /*!< (@ 0x40064004) RITIMER mask register */
  __IO uint32_t CTRL;                       /*!< (@ 0x40064008) RITIMER control register */
  __IO uint32_t COUNTER;                    /*!< (@ 0x4006400C) RITIMER counter register */
  __IO uint32_t COMPVAL_H;                  /*!< (@ 0x40064010) RITIMER compare upper register */
  __IO uint32_t MASK_H;                     /*!< (@ 0x40064014) RITIMER mask upper register */
  __I  uint32_t RESERVED0[1];
  __IO uint32_t COUNTER_H;                  /*!< (@ 0x4006401C) RITIMER counter upper register */
} LPC_RITIMER_Type;


// ------------------------------------------------------------------------------------------------
// -----                                          USB                                         -----
// ------------------------------------------------------------------------------------------------
typedef struct {                            /*!< (@ 0x40020000) USB Structure          */
  __IO uint32_t DEVCMDSTAT;                 /*!< (@ 0x40020000) USB Device Command/Status register */
  __IO uint32_t INFO;                       /*!< (@ 0x40020004) USB Info register      */
  __IO uint32_t EPLISTSTART;                /*!< (@ 0x40020008) USB EP Command/Status List start address */
  __IO uint32_t DATABUFSTART;               /*!< (@ 0x4002000C) USB Data buffer start address */
  __IO uint32_t LPM;                        /*!< (@ 0x40020010) Link Power Management register */
  __IO uint32_t EPSKIP;                     /*!< (@ 0x40020014) USB Endpoint skip      */
  __IO uint32_t EPINUSE;                    /*!< (@ 0x40020018) USB Endpoint Buffer in use */
  __IO uint32_t EPBUFCFG;                   /*!< (@ 0x4002001C) USB Endpoint Buffer Configuration register */
  __IO uint32_t INTSTAT;                    /*!< (@ 0x40020020) USB interrupt status register */
  __IO uint32_t INTEN;                      /*!< (@ 0x40020024) USB interrupt enable register */
  __IO uint32_t INTSETSTAT;                 /*!< (@ 0x40020028) USB set interrupt status register */
  __IO uint32_t INTROUTING;                 /*!< (@ 0x4002002C) USB interrupt routing register */
  __I  uint32_t RESERVED0[1];
  __I  uint32_t EPTOGGLE;                   /*!< (@ 0x40020034) USB Endpoint toggle register */
} LPC_USB_Type;


// ------------------------------------------------------------------------------------------------
// -----                                       GPIO_PORT                                      -----
// ------------------------------------------------------------------------------------------------

typedef struct {                            /*!< (@ 0x50000000) GPIO_PORT Structure    */
  union {
    struct {
      __IO uint8_t B0[32];                  /*!< (@ 0x50000000) Byte pin registers port 0; pins PIO0_0 to PIO0_31 */
      __IO uint8_t B1[32];                  /*!< (@ 0x50000020) Byte pin registers port 1 */
    };
    __IO uint8_t B[64];                     /*!< (@ 0x50000000) Byte pin registers port 0/1 */
  };
  __I  uint32_t RESERVED0[1008];
  union {
    struct {
      __IO uint32_t W0[32];                 /*!< (@ 0x50001000) Word pin registers port 0 */
      __IO uint32_t W1[32];                 /*!< (@ 0x50001080) Word pin registers port 1 */
    };
    __IO uint32_t W[64];                    /*!< (@ 0x50001000) Word pin registers port 0/1 */
  };
  __I  uint32_t RESERVED1[960];
  __IO uint32_t DIR[2];                     /*!< (@ 0x50002000) Direction registers port 0/1 */
  __I  uint32_t RESERVED2[30];
  __IO uint32_t MASK[2];                    /*!< (@ 0x50002080) Mask register port 0/1 */
  __I  uint32_t RESERVED3[30];
  __IO uint32_t PIN[2];                     /*!< (@ 0x50002100) Portpin register port 0 */
  __I  uint32_t RESERVED4[30];
  __IO uint32_t MPIN[2];                    /*!< (@ 0x50002180) Masked port register port 0/1 */
  __I  uint32_t RESERVED5[30];
  __IO uint32_t SET[2];                     /*!< (@ 0x50002200) Write: Set register for port 0/1 Read: output bits for port 0/1 */
  __I  uint32_t RESERVED6[30];
  __O  uint32_t CLR[2];                     /*!< (@ 0x50002280) Clear port 0/1         */
  __I  uint32_t RESERVED7[30];
  __O  uint32_t NOT[2];                     /*!< (@ 0x50002300) Toggle port 0/1        */
} LPC_GPIO_Type;


#if defined ( __CC_ARM   )
  #pragma no_anon_unions
#endif


// ------------------------------------------------------------------------------------------------
// -----                                 Peripheral memory map                                -----
// ------------------------------------------------------------------------------------------------

#define LPC_I2C_BASE              (0x40000000)
#define LPC_WWDT_BASE             (0x40004000)
#define LPC_USART_BASE            (0x40008000)
#define LPC_CT16B0_BASE           (0x4000C000)
#define LPC_CT16B1_BASE           (0x40010000)
#define LPC_CT32B0_BASE           (0x40014000)
#define LPC_CT32B1_BASE           (0x40018000)
#define LPC_ADC_BASE              (0x4001C000)
#define LPC_PMU_BASE              (0x40038000)
#define LPC_FLASHCTRL_BASE        (0x4003C000)
#define LPC_SSP0_BASE             (0x40040000)
#define LPC_IOCON_BASE            (0x40044000)
#define LPC_SYSCON_BASE           (0x40048000)
#define LPC_GPIO_PIN_INT_BASE     (0x4004C000)
#define LPC_SSP1_BASE             (0x40058000)
#define LPC_GPIO_GROUP_INT0_BASE  (0x4005C000)
#define LPC_GPIO_GROUP_INT1_BASE  (0x40060000)
#define LPC_RITIMER_BASE          (0x40064000)
#define LPC_USB_BASE              (0x40080000)
#define LPC_GPIO_BASE             (0x50000000)


// ------------------------------------------------------------------------------------------------
// -----                                Peripheral declaration                                -----
// ------------------------------------------------------------------------------------------------

#define LPC_I2C                   ((LPC_I2C_Type            *) LPC_I2C_BASE)
#define LPC_WWDT                  ((LPC_WWDT_Type           *) LPC_WWDT_BASE)
#define LPC_USART                 ((LPC_USART_Type          *) LPC_USART_BASE)
#define LPC_CT16B0                ((LPC_CTxxBx_Type         *) LPC_CT16B0_BASE)
#define LPC_CT16B1                ((LPC_CTxxBx_Type         *) LPC_CT16B1_BASE)
#define LPC_CT32B0                ((LPC_CTxxBx_Type         *) LPC_CT32B0_BASE)
#define LPC_CT32B1                ((LPC_CTxxBx_Type         *) LPC_CT32B1_BASE)
#define LPC_ADC                   ((LPC_ADC_Type            *) LPC_ADC_BASE)
#define LPC_PMU                   ((LPC_PMU_Type            *) LPC_PMU_BASE)
#define LPC_FLASHCTRL             ((LPC_FLASHCTRL_Type      *) LPC_FLASHCTRL_BASE)
#define LPC_SSP0                  ((LPC_SSPx_Type           *) LPC_SSP0_BASE)
#define LPC_SSP1                  ((LPC_SSPx_Type           *) LPC_SSP1_BASE)
#define LPC_IOCON                 ((LPC_IOCON_Type          *) LPC_IOCON_BASE)
#define LPC_SYSCON                ((LPC_SYSCON_Type         *) LPC_SYSCON_BASE)
#define LPC_GPIO_PIN_INT          ((LPC_GPIO_PIN_INT_Type   *) LPC_GPIO_PIN_INT_BASE)
#define LPC_GPIO_GROUP_INT0       ((LPC_GPIO_GROUP_INT0_Type*) LPC_GPIO_GROUP_INT0_BASE)
#define LPC_GPIO_GROUP_INT1       ((LPC_GPIO_GROUP_INT1_Type*) LPC_GPIO_GROUP_INT1_BASE)
#define LPC_RITIMER               ((LPC_RITIMER_Type        *) LPC_RITIMER_BASE)
#define LPC_USB                   ((LPC_USB_Type            *) LPC_USB_BASE)
#define LPC_GPIO                  ((LPC_GPIO_Type           *) LPC_GPIO_BASE)


/** @} */ /* End of group Device_Peripheral_Registers */
/** @} */ /* End of group (null) */
/** @} */ /* End of group h1usf */

#ifdef __cplusplus
}
#endif 


#endif  // __LPC13UXX_H__
