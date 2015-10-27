
/****************************************************************************************************//**
 * @file     LPC11U6x.h
 *
 * @brief    CMSIS Cortex-M0PLUS Peripheral Access Layer Header File for
 *           LPC11U6x from .
 *
 * @version  V0.4
 * @date     22. October 2013
 *
 * @note     Generated with SVDConv V2.81a 
 *           from CMSIS SVD File 'LPC11U6x.svd' Version 0.4,
 *
 *                                                                                      modified by Keil
 *******************************************************************************************************/



/** @addtogroup (null)
  * @{
  */

/** @addtogroup LPC11U6x
  * @{
  */

#ifndef LPC11U6X_H
#define LPC11U6X_H

#ifdef __cplusplus
extern "C" {
#endif


/* -------------------------  Interrupt Number Definition  ------------------------ */

typedef enum {
/* -----------------  Cortex-M0PLUS Processor Exceptions Numbers  ----------------- */
  Reset_IRQn                    = -15,              /*!<   1  Reset Vector, invoked on Power up and warm reset                 */
  NonMaskableInt_IRQn           = -14,              /*!<   2  Non maskable Interrupt, cannot be stopped or preempted           */
  HardFault_IRQn                = -13,              /*!<   3  Hard Fault, all classes of Fault                                 */



  SVCall_IRQn                   =  -5,              /*!<  11  System Service Call via SVC instruction                          */

  
  PendSV_IRQn                   =  -2,              /*!<  14  Pendable request for system service                              */
  SysTick_IRQn                  =  -1,              /*!<  15  System Tick Timer                                                */
/* ---------------------  LPC11U6x Specific Interrupt Numbers  -------------------- */
  PIN_INT0_IRQn                 =   0,              /*!<   0  PIN_INT0                                                         */
  PIN_INT1_IRQn                 =   1,              /*!<   1  PIN_INT1                                                         */
  PIN_INT2_IRQn                 =   2,              /*!<   2  PIN_INT2                                                         */
  PIN_INT3_IRQn                 =   3,              /*!<   3  PIN_INT3                                                         */
  PIN_INT4_IRQn                 =   4,              /*!<   4  PIN_INT4                                                         */
  PIN_INT5_IRQn                 =   5,              /*!<   5  PIN_INT5                                                         */
  PIN_INT6_IRQn                 =   6,              /*!<   6  PIN_INT6                                                         */
  PIN_INT7_IRQn                 =   7,              /*!<   7  PIN_INT7                                                         */
  GINT0_IRQn                    =   8,              /*!<   8  GINT0                                                            */
  GINT1_IRQn                    =   9,              /*!<   9  GINT1                                                            */
  I2C1_IRQn                     =  10,              /*!<  10  I2C1                                                             */
  USART1_4_IRQn                 =  11,              /*!<  11  USART1_4                                                         */
  USART2_3_IRQn                 =  12,              /*!<  12  USART2_3                                                         */
  SCT0_1_IRQn                   =  13,              /*!<  13  SCT0_1                                                           */
  SSP1_IRQn                     =  14,              /*!<  14  SSP1                                                             */
  I2C0_IRQn                     =  15,              /*!<  15  I2C0                                                             */
  CT16B0_IRQn                   =  16,              /*!<  16  CT16B0                                                           */
  CT16B1_IRQn                   =  17,              /*!<  17  CT16B1                                                           */
  CT32B0_IRQn                   =  18,              /*!<  18  CT32B0                                                           */
  CT32B1_IRQn                   =  19,              /*!<  19  CT32B1                                                           */
  SSP0_IRQn                     =  20,              /*!<  20  SSP0                                                             */
  USART0_IRQn                   =  21,              /*!<  21  USART0                                                           */
  USB_IRQn                      =  22,              /*!<  22  USB                                                              */
  USB_FIQ_IRQn                  =  23,              /*!<  23  USB_FIQ                                                          */
  ADC_A_IRQn                    =  24,              /*!<  24  ADC_A                                                            */
  RTC_IRQn                      =  25,              /*!<  25  RTC                                                              */
  BOD_WDT_IRQn                  =  26,              /*!<  26  BOD_WDT                                                          */
  FLASH_IRQn                    =  27,              /*!<  27  FLASH                                                            */
  DMA_IRQn                      =  28,              /*!<  28  DMA                                                              */
  ADC_B_IRQn                    =  29,              /*!<  29  ADC_B                                                            */
  USBWAKEUP_IRQn                =  30               /*!<  30  USBWAKEUP                                                        */
} IRQn_Type;


/** @addtogroup Configuration_of_CMSIS
  * @{
  */


/* ================================================================================ */
/* ================      Processor and Core Peripheral Section     ================ */
/* ================================================================================ */

/* ----------------Configuration of the Cortex-M0PLUS Processor and Core Peripherals---------------- */
#define __CM0PLUS_REV                 0x0000        /*!< Cortex-M0PLUS Core Revision                                           */
#define __MPU_PRESENT                  0            /*!< MPU present or not                                                    */
#define __NVIC_PRIO_BITS               2            /*!< Number of Bits used for Priority Levels                               */
#define __Vendor_SysTickConfig         0            /*!< Set to 1 if different SysTick Config is used                          */
#define __VTOR_PRESENT                 1            /*!< Set to 1 if CPU supports Vector Table Offset Register                 */
/** @} */ /* End of group Configuration_of_CMSIS */

#include "core_cm0plus.h"                           /*!< Cortex-M0PLUS processor and core peripherals                          */
#include "system_LPC11U6x.h"                        /*!< LPC11U6x System                                                       */


/* ================================================================================ */
/* ================       Device Specific Peripheral Section       ================ */
/* ================================================================================ */


/** @addtogroup Device_Peripheral_Registers
  * @{
  */


/* -------------------  Start of section using anonymous unions  ------------------ */
#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__ICCARM__)
  #pragma language=extended
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__TMS470__)
/* anonymous unions are enabled by default */
#elif defined(__TASKING__)
  #pragma warning 586
#else
  #warning Not supported compiler type
#endif



/* ================================================================================ */
/* ================                      I2C0                      ================ */
/* ================================================================================ */


/**
  * @brief I2C-bus controller (I2C0)
  */

typedef struct {                                    /*!< I2C0 Structure                                                        */
  __IO uint32_t  CONSET;                            /*!< I2C Control Set Register. When a one is written to a bit of
                                                         this register, the corresponding bit in the I2C control register
                                                          is set. Writing a zero has no effect on the corresponding bit
                                                          in the I2C control register.                                         */
  __I  uint32_t  STAT;                              /*!< I2C Status Register. During I2C operation, this register provides
                                                         detailed status codes that allow software to determine the next
                                                          action needed.                                                       */
  __IO uint32_t  DAT;                               /*!< I2C Data Register. During master or slave transmit mode, data
                                                         to be transmitted is written to this register. During master
                                                          or slave receive mode, data that has been received may be read
                                                          from this register.                                                  */
  __IO uint32_t  ADR0;                              /*!< I2C Slave Address Register 0. Contains the 7-bit slave address
                                                         for operation of the I2C interface in slave mode, and is not
                                                          used in master mode. The least significant bit determines whether
                                                          a slave responds to the General Call address.                        */
  __IO uint32_t  SCLH;                              /*!< SCH Duty Cycle Register High Half Word. Determines the high
                                                         time of the I2C clock.                                                */
  __IO uint32_t  SCLL;                              /*!< SCL Duty Cycle Register Low Half Word. Determines the low time
                                                         of the I2C clock. I2nSCLL and I2nSCLH together determine the
                                                          clock frequency generated by an I2C master and certain times
                                                          used in slave mode.                                                  */
  __O  uint32_t  CONCLR;                            /*!< I2C Control Clear Register. When a one is written to a bit of
                                                         this register, the corresponding bit in the I2C control register
                                                          is cleared. Writing a zero has no effect on the corresponding
                                                          bit in the I2C control register.                                     */
  __IO uint32_t  MMCTRL;                            /*!< Monitor mode control register.                                        */
  __IO uint32_t  ADR1;                              /*!< I2C Slave Address Register. Contains the 7-bit slave address
                                                         for operation of the I2C interface in slave mode, and is not
                                                          used in master mode. The least significant bit determines whether
                                                          a slave responds to the General Call address.                        */
  __IO uint32_t  ADR2;                              /*!< I2C Slave Address Register. Contains the 7-bit slave address
                                                         for operation of the I2C interface in slave mode, and is not
                                                          used in master mode. The least significant bit determines whether
                                                          a slave responds to the General Call address.                        */
  __IO uint32_t  ADR3;                              /*!< I2C Slave Address Register. Contains the 7-bit slave address
                                                         for operation of the I2C interface in slave mode, and is not
                                                          used in master mode. The least significant bit determines whether
                                                          a slave responds to the General Call address.                        */
  __I  uint32_t  DATA_BUFFER;                       /*!< Data buffer register. The contents of the 8 MSBs of the I2DAT
                                                         shift register will be transferred to the DATA_BUFFER automatically
                                                          after every nine bits (8 bits of data plus ACK or NACK) has
                                                          been received on the bus.                                            */
  __IO uint32_t  MASK0;                             /*!< I2C Slave address mask register. This mask register is associated
                                                         with I2ADR0 to determine an address match. The mask register
                                                          has no effect when comparing to the General Call address (0000000).  */
  __IO uint32_t  MASK1;                             /*!< I2C Slave address mask register. This mask register is associated
                                                         with I2ADR0 to determine an address match. The mask register
                                                          has no effect when comparing to the General Call address (0000000).  */
  __IO uint32_t  MASK2;                             /*!< I2C Slave address mask register. This mask register is associated
                                                         with I2ADR0 to determine an address match. The mask register
                                                          has no effect when comparing to the General Call address (0000000).  */
  __IO uint32_t  MASK3;                             /*!< I2C Slave address mask register. This mask register is associated
                                                         with I2ADR0 to determine an address match. The mask register
                                                          has no effect when comparing to the General Call address (0000000).  */
} LPC_I2C0_Type;


/* ================================================================================ */
/* ================                      WWDT                      ================ */
/* ================================================================================ */


/**
  * @brief Windowed Watchdog Timer (WWDT) (WWDT)
  */

typedef struct {                                    /*!< WWDT Structure                                                        */
  __IO uint32_t  MOD;                               /*!< Watchdog mode register. This register contains the basic mode
                                                         and status of the Watchdog Timer.                                     */
  __IO uint32_t  TC;                                /*!< Watchdog timer constant register. This 24-bit register determines
                                                         the time-out value.                                                   */
  __O  uint32_t  FEED;                              /*!< Watchdog feed sequence register. Writing 0xAA followed by 0x55
                                                         to this register reloads the Watchdog timer with the value contained
                                                          in WDTC.                                                             */
  __I  uint32_t  TV;                                /*!< Watchdog timer value register. This 24-bit register reads out
                                                         the current value of the Watchdog timer.                              */
  __IO uint32_t  CLKSEL;                            /*!< Watchdog clock select register.                                       */
  __IO uint32_t  WARNINT;                           /*!< Watchdog Warning Interrupt compare value.                             */
  __IO uint32_t  WINDOW;                            /*!< Watchdog Window compare value.                                        */
} LPC_WWDT_Type;


/* ================================================================================ */
/* ================                     USART0                     ================ */
/* ================================================================================ */


/**
  * @brief USART0 (USART0)
  */

typedef struct {                                    /*!< USART0 Structure                                                      */
  
  union {
    __IO uint32_t  DLL;                             /*!< Divisor Latch LSB. Least significant byte of the baud rate divisor
                                                         value. The full divisor is used to generate a baud rate from
                                                          the fractional rate divider. (DLAB=1)                                */
    __O  uint32_t  THR;                             /*!< Transmit Holding Register. The next character to be transmitted
                                                         is written here. (DLAB=0)                                             */
    __I  uint32_t  RBR;                             /*!< Receiver Buffer Register. Contains the next received character
                                                         to be read. (DLAB=0)                                                  */
  };
  
  union {
    __IO uint32_t  IER;                             /*!< Interrupt Enable Register. Contains individual interrupt enable
                                                         bits for the 7 potential USART interrupts. (DLAB=0)                   */
    __IO uint32_t  DLM;                             /*!< Divisor Latch MSB. Most significant byte of the baud rate divisor
                                                         value. The full divisor is used to generate a baud rate from
                                                          the fractional rate divider. (DLAB=1)                                */
  };
  
  union {
    __O  uint32_t  FCR;                             /*!< FIFO Control Register. Controls USART FIFO usage and modes.           */
    __I  uint32_t  IIR;                             /*!< Interrupt ID Register. Identifies which interrupt(s) are pending.     */
  };
  __IO uint32_t  LCR;                               /*!< Line Control Register. Contains controls for frame formatting
                                                         and break generation.                                                 */
  __IO uint32_t  MCR;                               /*!< Modem Control Register.                                               */
  __I  uint32_t  LSR;                               /*!< Line Status Register. Contains flags for transmit and receive
                                                         status, including line errors.                                        */
  __I  uint32_t  MSR;                               /*!< Modem Status Register.                                                */
  __IO uint32_t  SCR;                               /*!< Scratch Pad Register. Eight-bit temporary storage for software.       */
  __IO uint32_t  ACR;                               /*!< Auto-baud Control Register. Contains controls for the auto-baud
                                                         feature.                                                              */
  __IO uint32_t  ICR;                               /*!< IrDA Control Register. Enables and configures the IrDA (remote
                                                         control) mode.                                                        */
  __IO uint32_t  FDR;                               /*!< Fractional Divider Register. Generates a clock input for the
                                                         baud rate divider.                                                    */
  __IO uint32_t  OSR;                               /*!< Oversampling Register. Controls the degree of oversampling during
                                                         each bit time.                                                        */
  __IO uint32_t  TER;                               /*!< Transmit Enable Register. Turns off USART transmitter for use
                                                         with software flow control.                                           */
  __I  uint32_t  RESERVED0[3];
  __IO uint32_t  HDEN;                              /*!< Half duplex enable register.                                          */
  __I  uint32_t  RESERVED1;
  __IO uint32_t  SCICTRL;                           /*!< Smart Card Interface Control register. Enables and configures
                                                         the Smart Card Interface feature.                                     */
  __IO uint32_t  RS485CTRL;                         /*!< RS-485/EIA-485 Control. Contains controls to configure various
                                                         aspects of RS-485/EIA-485 modes.                                      */
  __IO uint32_t  RS485ADRMATCH;                     /*!< RS-485/EIA-485 address match. Contains the address match value
                                                         for RS-485/EIA-485 mode.                                              */
  __IO uint32_t  RS485DLY;                          /*!< RS-485/EIA-485 direction control delay.                               */
  __IO uint32_t  SYNCCTRL;                          /*!< Synchronous mode control register.                                    */
} LPC_USART0_Type;


/* ================================================================================ */
/* ================                     CT16B0                     ================ */
/* ================================================================================ */


/**
  * @brief 16-bit counter/timers CT16B0 (CT16B0)
  */

typedef struct {                                    /*!< CT16B0 Structure                                                      */
  __IO uint32_t  IR;                                /*!< Interrupt Register. The IR can be written to clear interrupts.
                                                         The IR can be read to identify which of eight possible interrupt
                                                          sources are pending.                                                 */
  __IO uint32_t  TCR;                               /*!< Timer Control Register. The TCR is used to control the Timer
                                                         Counter functions. The Timer Counter can be disabled or reset
                                                          through the TCR.                                                     */
  __IO uint32_t  TC;                                /*!< Timer Counter. The 16-bit TC is incremented every PR+1 cycles
                                                         of PCLK. The TC is controlled through the TCR.                        */
  __IO uint32_t  PR;                                /*!< Prescale Register. When the Prescale Counter (below) is equal
                                                         to this value, the next clock increments the TC and clears the
                                                          PC.                                                                  */
  __IO uint32_t  PC;                                /*!< Prescale Counter. The 16-bit PC is a counter which is incremented
                                                         to the value stored in PR. When the value in PR is reached,
                                                          the TC is incremented and the PC is cleared. The PC is observable
                                                          and controllable through the bus interface.                          */
  __IO uint32_t  MCR;                               /*!< Match Control Register. The MCR is used to control if an interrupt
                                                         is generated and if the TC is reset when a Match occurs.              */
  __IO uint32_t  MR0;                               /*!< Match Register. MR can be enabled through the MCR to reset the
                                                         TC, stop both the TC and PC, and/or generate an interrupt every
                                                          time MR0 matches the TC.                                             */
  __IO uint32_t  MR1;                               /*!< Match Register. MR can be enabled through the MCR to reset the
                                                         TC, stop both the TC and PC, and/or generate an interrupt every
                                                          time MR0 matches the TC.                                             */
  __IO uint32_t  MR2;                               /*!< Match Register. MR can be enabled through the MCR to reset the
                                                         TC, stop both the TC and PC, and/or generate an interrupt every
                                                          time MR0 matches the TC.                                             */
  __IO uint32_t  MR3;                               /*!< Match Register. MR can be enabled through the MCR to reset the
                                                         TC, stop both the TC and PC, and/or generate an interrupt every
                                                          time MR0 matches the TC.                                             */
  __IO uint32_t  CCR;                               /*!< Capture Control Register. The CCR controls which edges of the
                                                         capture inputs are used to load the Capture Registers and whether
                                                          or not an interrupt is generated when a capture takes place.         */
  __I  uint32_t  CR0;                               /*!< Capture Register. CR is loaded with the value of TC when there
                                                         is an event on the CAP input.                                         */
  __I  uint32_t  CR1;                               /*!< Capture Register. CR is loaded with the value of TC when there
                                                         is an event on the CAP input.                                         */
  __I  uint32_t  CR2;                               /*!< Capture Register. CR is loaded with the value of TC when there
                                                         is an event on the CAP input.                                         */
  __I  uint32_t  RESERVED0;
  __IO uint32_t  EMR;                               /*!< External Match Register. The EMR controls the match function
                                                         and the external match pins CT16B0_MAT[1:0] and CT16B1_MAT[1:0].      */
  __I  uint32_t  RESERVED1[12];
  __IO uint32_t  CTCR;                              /*!< Count Control Register. The CTCR selects between Timer and Counter
                                                         mode, and in Counter mode selects the signal and edge(s) for
                                                          counting.                                                            */
  __IO uint32_t  PWMC;                              /*!< PWM Control Register. The PWMCON enables PWM mode for the external
                                                         match pins CT16B0_MAT[1:0] and CT16B1_MAT[1:0].                       */
} LPC_CT16B0_Type;


/* ================================================================================ */
/* ================                     CT32B0                     ================ */
/* ================================================================================ */


/**
  * @brief 32-bit counter/timers CT32B0 (CT32B0)
  */

typedef struct {                                    /*!< CT32B0 Structure                                                      */
  __IO uint32_t  IR;                                /*!< Interrupt Register. The IR can be written to clear interrupts.
                                                         The IR can be read to identify which of eight possible interrupt
                                                          sources are pending.                                                 */
  __IO uint32_t  TCR;                               /*!< Timer Control Register. The TCR is used to control the Timer
                                                         Counter functions. The Timer Counter can be disabled or reset
                                                          through the TCR.                                                     */
  __IO uint32_t  TC;                                /*!< Timer Counter. The 32-bit TC is incremented every PR+1 cycles
                                                         of PCLK. The TC is controlled through the TCR.                        */
  __IO uint32_t  PR;                                /*!< Prescale Register. When the Prescale Counter (below) is equal
                                                         to this value, the next clock increments the TC and clears the
                                                          PC.                                                                  */
  __IO uint32_t  PC;                                /*!< Prescale Counter. The 32-bit PC is a counter which is incremented
                                                         to the value stored in PR. When the value in PR is reached,
                                                          the TC is incremented and the PC is cleared. The PC is observable
                                                          and controllable through the bus interface.                          */
  __IO uint32_t  MCR;                               /*!< Match Control Register. The MCR is used to control if an interrupt
                                                         is generated and if the TC is reset when a Match occurs.              */
  __IO uint32_t  MR0;                               /*!< Match Register. MR can be enabled through the MCR to reset the
                                                         TC, stop both the TC and PC, and/or generate an interrupt every
                                                          time MR0 matches the TC.                                             */
  __IO uint32_t  MR1;                               /*!< Match Register. MR can be enabled through the MCR to reset the
                                                         TC, stop both the TC and PC, and/or generate an interrupt every
                                                          time MR0 matches the TC.                                             */
  __IO uint32_t  MR2;                               /*!< Match Register. MR can be enabled through the MCR to reset the
                                                         TC, stop both the TC and PC, and/or generate an interrupt every
                                                          time MR0 matches the TC.                                             */
  __IO uint32_t  MR3;                               /*!< Match Register. MR can be enabled through the MCR to reset the
                                                         TC, stop both the TC and PC, and/or generate an interrupt every
                                                          time MR0 matches the TC.                                             */
  __IO uint32_t  CCR;                               /*!< Capture Control Register. The CCR controls which edges of the
                                                         capture inputs are used to load the Capture Registers and whether
                                                          or not an interrupt is generated when a capture takes place.         */
  __I  uint32_t  CR0;                               /*!< Capture Register. CR is loaded with the value of TC when there
                                                         is an event on the CAP input.                                         */
  __I  uint32_t  CR1;                               /*!< Capture Register. CR is loaded with the value of TC when there
                                                         is an event on the CAP input.                                         */
  __I  uint32_t  CR2;                               /*!< Capture Register. CR is loaded with the value of TC when there
                                                         is an event on the CAP input.                                         */
  __I  uint32_t  RESERVED0;
  __IO uint32_t  EMR;                               /*!< External Match Register. The EMR controls the match function
                                                         and the external match pins CT32Bn_MAT[3:0].                          */
  __I  uint32_t  RESERVED1[12];
  __IO uint32_t  CTCR;                              /*!< Count Control Register. The CTCR selects between Timer and Counter
                                                         mode, and in Counter mode selects the signal and edge(s) for
                                                          counting.                                                            */
  __IO uint32_t  PWMC;                              /*!< PWM Control Register. The PWMCON enables PWM mode for the external
                                                         match pins CT32Bn_MAT[3:0].                                           */
} LPC_CT32B0_Type;


/* ================================================================================ */
/* ================                       ADC                      ================ */
/* ================================================================================ */


/**
  * @brief Product name title=Kylin UM Chapter title=Kylin12-bit Analog-to-Digital Converter (ADC) Modification date=5/13/2013 Major revision=0 Minor revision=1  (ADC)
  */

typedef struct {                                    /*!< ADC Structure                                                         */
  __IO uint32_t  CTRL;                              /*!< A/D Control Register. Contains the clock divide value, enable
                                                         bits for each sequence and the A/D power-down bit.                    */
  __I  uint32_t  RESERVED0;
  __IO uint32_t  SEQA_CTRL;                         /*!< A/D Conversion Sequence-A control Register: Controls triggering
                                                         and channel selection for conversion sequence-A. Also specifies
                                                          interrupt mode for sequence-A.                                       */
  __IO uint32_t  SEQB_CTRL;                         /*!< A/D Conversion Sequence-B Control Register: Controls triggering
                                                         and channel selection for conversion sequence-B. Also specifies
                                                          interrupt mode for sequence-B.                                       */
  __IO uint32_t  SEQA_GDAT;                         /*!< A/D Sequence-A Global Data Register. This register contains
                                                         the result of the most recent A/D conversion performed under
                                                          sequence-A                                                           */
  __IO uint32_t  SEQB_GDAT;                         /*!< A/D Sequence-B Global Data Register. This register contains
                                                         the result of the most recent A/D conversion performed under
                                                          sequence-B                                                           */
  __I  uint32_t  RESERVED1[2];
  __I  uint32_t  DAT[12];                           /*!< A/D Channel 0 Data Register. This register contains the result
                                                         of the most recent conversion completed on channel 0.                 */
  __IO uint32_t  THR0_LOW;                          /*!< A/D Low Compare Threshold Register 0 : Contains the lower threshold
                                                         level for automatic threshold comparison for any channels linked
                                                          to threshold pair 0.                                                 */
  __IO uint32_t  THR1_LOW;                          /*!< A/D Low Compare Threshold Register 1: Contains the lower threshold
                                                         level for automatic threshold comparison for any channels linked
                                                          to threshold pair 1.                                                 */
  __IO uint32_t  THR0_HIGH;                         /*!< A/D High Compare Threshold Register 0: Contains the upper threshold
                                                         level for automatic threshold comparison for any channels linked
                                                          to threshold pair 0.                                                 */
  __IO uint32_t  THR1_HIGH;                         /*!< A/D High Compare Threshold Register 1: Contains the upper threshold
                                                         level for automatic threshold comparison for any channels linked
                                                          to threshold pair 1.                                                 */
  __I  uint32_t  CHAN_THRSEL;                       /*!< A/D Channel-Threshold Select Register. Specifies which set of
                                                         threshold compare registers are to be used for each channel           */
  __IO uint32_t  INTEN;                             /*!< A/D Interrupt Enable Register. This register contains enable
                                                         bits that enable the sequence-A, sequence-B, threshold compare
                                                          and data overrun interrupts to be generated.                         */
  __I  uint32_t  FLAGS;                             /*!< A/D Flags Register. Contains the four interrupt request flags
                                                         and the individual component overrun and threshold-compare flags.
                                                          (The overrun bits replicate information stored in the result
                                                          registers).                                                          */
  __IO uint32_t  TRM;                               /*!< ADC trim register.                                                    */
} LPC_ADC_Type;


/* ================================================================================ */
/* ================                       RTC                      ================ */
/* ================================================================================ */


/**
  * @brief Real-Time Clock (RTC) (RTC)
  */

typedef struct {                                    /*!< RTC Structure                                                         */
  __IO uint32_t  CTRL;                              /*!< RTC control register                                                  */
  __IO uint32_t  MATCH;                             /*!< RTC match register                                                    */
  __IO uint32_t  COUNT;                             /*!< RTC counter register                                                  */
  __IO uint32_t  WAKE;                              /*!< RTC high-resolution/wake-up timer control register                    */
} LPC_RTC_Type;


/* ================================================================================ */
/* ================                   DMATRIGMUX                   ================ */
/* ================================================================================ */


/**
  * @brief Product name title=Kylin UM Chapter title=KylinDMA controller Modification date=5/13/2013 Major revision=0 Minor revision=1  (DMATRIGMUX)
  */

typedef struct {                                    /*!< DMATRIGMUX Structure                                                  */
  __IO uint32_t  DMA_ITRIG_PINMUX[16];              /*!< Trigger input select register for DMA channel 0.                      */
} LPC_DMATRIGMUX_Type;


/* ================================================================================ */
/* ================                       PMU                      ================ */
/* ================================================================================ */


/**
  * @brief Product name title=Kylin UM Chapter title=KylinPower Management Unit (PMU) Modification date=5/13/2013 Major revision=0 Minor revision=1  (PMU)
  */

typedef struct {                                    /*!< PMU Structure                                                         */
  __IO uint32_t  PCON;                              /*!< Power control register                                                */
  __IO uint32_t  GPREG0;                            /*!< General purpose register 0                                            */
  __IO uint32_t  GPREG1;                            /*!< General purpose register 0                                            */
  __IO uint32_t  GPREG2;                            /*!< General purpose register 0                                            */
  __IO uint32_t  GPREG3;                            /*!< General purpose register 0                                            */
  __IO uint32_t  DPDCTRL;                           /*!< Deep power down control register                                      */
} LPC_PMU_Type;


/* ================================================================================ */
/* ================                    FLASHCTRL                   ================ */
/* ================================================================================ */


/**
  * @brief Flash controller  (FLASHCTRL)
  */

typedef struct {                                    /*!< FLASHCTRL Structure                                                   */
  __I  uint32_t  RESERVED0[4];
  __IO uint32_t  FLASHCFG;                          /*!< Flash configuration register                                          */
  __I  uint32_t  RESERVED1[3];
  __IO uint32_t  FMSSTART;                          /*!< Signature start address register                                      */
  __IO uint32_t  FMSSTOP;                           /*!< Signature stop-address register                                       */
  __I  uint32_t  RESERVED2;
  __I  uint32_t  FMSW0;                             /*!< Signature Word                                                        */
} LPC_FLASHCTRL_Type;


/* ================================================================================ */
/* ================                      SSP0                      ================ */
/* ================================================================================ */


/**
  * @brief SSP/SPI  (SSP0)
  */

typedef struct {                                    /*!< SSP0 Structure                                                        */
  __IO uint32_t  CR0;                               /*!< Control Register 0. Selects the serial clock rate, bus type,
                                                         and data size.                                                        */
  __IO uint32_t  CR1;                               /*!< Control Register 1. Selects master/slave and other modes.             */
  __IO uint32_t  DR;                                /*!< Data Register. Writes fill the transmit FIFO, and reads empty
                                                         the receive FIFO.                                                     */
  __I  uint32_t  SR;                                /*!< Status Register                                                       */
  __IO uint32_t  CPSR;                              /*!< Clock Prescale Register                                               */
  __IO uint32_t  IMSC;                              /*!< Interrupt Mask Set and Clear Register                                 */
  __I  uint32_t  RIS;                               /*!< Raw Interrupt Status Register                                         */
  __I  uint32_t  MIS;                               /*!< Masked Interrupt Status Register                                      */
  __O  uint32_t  ICR;                               /*!< SSPICR Interrupt Clear Register                                       */
} LPC_SSP0_Type;


/* ================================================================================ */
/* ================                      IOCON                     ================ */
/* ================================================================================ */


/**
  * @brief Product name title=Kylin UM Chapter title=KylinI/O control (IOCON) Modification date=5/13/2013 Major revision=0 Minor revision=1  (IOCON)
  */

typedef struct {                                    /*!< IOCON Structure                                                       */
  __IO uint32_t  PIO0_0;                            /*!< I/O configuration for port PIO0                                       */
  __IO uint32_t  PIO0_1;                            /*!< I/O configuration for port PIO0                                       */
  __IO uint32_t  PIO0_2;                            /*!< I/O configuration for port PIO0                                       */
  __IO uint32_t  PIO0_3;                            /*!< I/O configuration for port PIO0                                       */
  __IO uint32_t  PIO0_4;                            /*!< I/O configuration for port PIO0                                       */
  __IO uint32_t  PIO0_5;                            /*!< I/O configuration for port PIO0                                       */
  __IO uint32_t  PIO0_6;                            /*!< I/O configuration for port PIO0                                       */
  __IO uint32_t  PIO0_7;                            /*!< I/O configuration for port PIO0                                       */
  __IO uint32_t  PIO0_8;                            /*!< I/O configuration for port PIO0                                       */
  __IO uint32_t  PIO0_9;                            /*!< I/O configuration for port PIO0                                       */
  __IO uint32_t  PIO0_10;                           /*!< I/O configuration for port PIO0                                       */
  __IO uint32_t  PIO0_11;                           /*!< I/O configuration for port PIO0                                       */
  __IO uint32_t  PIO0_12;                           /*!< I/O configuration for port PIO0                                       */
  __IO uint32_t  PIO0_13;                           /*!< I/O configuration for port PIO0                                       */
  __IO uint32_t  PIO0_14;                           /*!< I/O configuration for port PIO0                                       */
  __IO uint32_t  PIO0_15;                           /*!< I/O configuration for port PIO0                                       */
  __IO uint32_t  PIO0_16;                           /*!< I/O configuration for port PIO0                                       */
  __IO uint32_t  PIO0_17;                           /*!< I/O configuration for port PIO0                                       */
  __IO uint32_t  PIO0_18;                           /*!< I/O configuration for port PIO0                                       */
  __IO uint32_t  PIO0_19;                           /*!< I/O configuration for port PIO0                                       */
  __IO uint32_t  PIO0_20;                           /*!< I/O configuration for port PIO0                                       */
  __IO uint32_t  PIO0_21;                           /*!< I/O configuration for port PIO0                                       */
  __IO uint32_t  PIO0_22;                           /*!< I/O configuration for port PIO0                                       */
  __IO uint32_t  PIO0_23;                           /*!< I/O configuration for port PIO0                                       */
  __IO uint32_t  PIO1_0;                            /*!< I/O configuration for port PIO1                                       */
  __IO uint32_t  PIO1_1;                            /*!< I/O configuration for port PIO1                                       */
  __IO uint32_t  PIO1_2;                            /*!< I/O configuration for port PIO1                                       */
  __IO uint32_t  PIO1_3;                            /*!< I/O configuration for port PIO1                                       */
  __IO uint32_t  PIO1_4;                            /*!< I/O configuration for port PIO1                                       */
  __IO uint32_t  PIO1_5;                            /*!< I/O configuration for port PIO1                                       */
  __IO uint32_t  PIO1_6;                            /*!< I/O configuration for port PIO1                                       */
  __IO uint32_t  PIO1_7;                            /*!< I/O configuration for port PIO1                                       */
  __IO uint32_t  PIO1_8;                            /*!< I/O configuration for port PIO1                                       */
  __IO uint32_t  PIO1_9;                            /*!< I/O configuration for port PIO1                                       */
  __IO uint32_t  PIO1_10;                           /*!< I/O configuration for port PIO1                                       */
  __IO uint32_t  PIO1_11;                           /*!< I/O configuration for port PIO1                                       */
  __IO uint32_t  PIO1_12;                           /*!< I/O configuration for port PIO1                                       */
  __IO uint32_t  PIO1_13;                           /*!< I/O configuration for port PIO1                                       */
  __IO uint32_t  PIO1_14;                           /*!< I/O configuration for port PIO1                                       */
  __IO uint32_t  PIO1_15;                           /*!< I/O configuration for port PIO1                                       */
  __IO uint32_t  PIO1_16;                           /*!< I/O configuration for port PIO1                                       */
  __IO uint32_t  PIO1_17;                           /*!< I/O configuration for port PIO1                                       */
  __IO uint32_t  PIO1_18;                           /*!< I/O configuration for port PIO1                                       */
  __IO uint32_t  PIO1_19;                           /*!< I/O configuration for port PIO1                                       */
  __IO uint32_t  PIO1_20;                           /*!< I/O configuration for port PIO1                                       */
  __IO uint32_t  PIO1_21;                           /*!< I/O configuration for port PIO1                                       */
  __IO uint32_t  PIO1_22;                           /*!< I/O configuration for port PIO1                                       */
  __IO uint32_t  PIO1_23;                           /*!< I/O configuration for port PIO1                                       */
  __IO uint32_t  PIO1_24;                           /*!< I/O configuration for port PIO1                                       */
  __IO uint32_t  PIO1_25;                           /*!< I/O configuration for port PIO1                                       */
  __IO uint32_t  PIO1_26;                           /*!< I/O configuration for port PIO1                                       */
  __IO uint32_t  PIO1_27;                           /*!< I/O configuration for port PIO1                                       */
  __IO uint32_t  PIO1_28;                           /*!< I/O configuration for port PIO1                                       */
  __IO uint32_t  PIO1_29;                           /*!< I/O configuration for port PIO1                                       */
  __IO uint32_t  PIO1_30;                           /*!< I/O configuration for port PIO1                                       */
  __IO uint32_t  PIO1_31;                           /*!< I/O configuration for port PIO1                                       */
  __I  uint32_t  RESERVED0[4];
  __IO uint32_t  PIO2_0;                            /*!< I/O configuration for port PIO2                                       */
  __IO uint32_t  PIO2_1;                            /*!< I/O configuration for port PIO2                                       */
  __I  uint32_t  RESERVED1;
  __IO uint32_t  PIO2_2;                            /*!< I/O configuration for port PIO2                                       */
  __IO uint32_t  PIO2_3;                            /*!< I/O configuration for port PIO2                                       */
  __IO uint32_t  PIO2_4;                            /*!< I/O configuration for port PIO2                                       */
  __IO uint32_t  PIO2_5;                            /*!< I/O configuration for port PIO2                                       */
  __IO uint32_t  PIO2_6;                            /*!< I/O configuration for port PIO2                                       */
  __IO uint32_t  PIO2_7;                            /*!< I/O configuration for port PIO2                                       */
  __IO uint32_t  PIO2_8;                            /*!< I/O configuration for port PIO2                                       */
  __IO uint32_t  PIO2_9;                            /*!< I/O configuration for port PIO2                                       */
  __IO uint32_t  PIO2_10;                           /*!< I/O configuration for port PIO2                                       */
  __IO uint32_t  PIO2_11;                           /*!< I/O configuration for port PIO2                                       */
  __IO uint32_t  PIO2_12;                           /*!< I/O configuration for port PIO2                                       */
  __IO uint32_t  PIO2_13;                           /*!< I/O configuration for port PIO2                                       */
  __IO uint32_t  PIO2_14;                           /*!< I/O configuration for port PIO2                                       */
  __IO uint32_t  PIO2_15;                           /*!< I/O configuration for port PIO2                                       */
  __IO uint32_t  PIO2_16;                           /*!< I/O configuration for port PIO2                                       */
  __IO uint32_t  PIO2_17;                           /*!< I/O configuration for port PIO2                                       */
  __IO uint32_t  PIO2_18;                           /*!< I/O configuration for port PIO2                                       */
  __IO uint32_t  PIO2_19;                           /*!< I/O configuration for port PIO2                                       */
  __IO uint32_t  PIO2_20;                           /*!< I/O configuration for port PIO2                                       */
  __IO uint32_t  PIO2_21;                           /*!< I/O configuration for port PIO2                                       */
  __IO uint32_t  PIO2_22;                           /*!< I/O configuration for port PIO2                                       */
  __IO uint32_t  PIO2_23;                           /*!< I/O configuration for port PIO2                                       */
} LPC_IOCON_Type;


/* ================================================================================ */
/* ================                     SYSCON                     ================ */
/* ================================================================================ */


/**
  * @brief Product name title=Kylin UM Chapter title=KylinSystem configuration (SYSCON) Modification date=5/13/2013 Major revision=0 Minor revision=1  (SYSCON)
  */

typedef struct {                                    /*!< SYSCON Structure                                                      */
  __IO uint32_t  SYSMEMREMAP;                       /*!< System memory remap                                                   */
  __IO uint32_t  PRESETCTRL;                        /*!< Peripheral reset control                                              */
  __IO uint32_t  SYSPLLCTRL;                        /*!< System PLL control                                                    */
  __I  uint32_t  SYSPLLSTAT;                        /*!< System PLL status                                                     */
  __IO uint32_t  USBPLLCTRL;                        /*!< USB PLL control                                                       */
  __I  uint32_t  USBPLLSTAT;                        /*!< USB PLL status                                                        */
  __I  uint32_t  RESERVED0;
  __IO uint32_t  RTCOSCCTRL;                        /*!< RTC oscillator 32 kHz output control                                  */
  __IO uint32_t  SYSOSCCTRL;                        /*!< System oscillator control                                             */
  __IO uint32_t  WDTOSCCTRL;                        /*!< Watchdog oscillator control                                           */
  __I  uint32_t  RESERVED1[2];
  __IO uint32_t  SYSRSTSTAT;                        /*!< System reset status register                                          */
  __I  uint32_t  RESERVED2[3];
  __IO uint32_t  SYSPLLCLKSEL;                      /*!< System PLL clock source select                                        */
  __IO uint32_t  SYSPLLCLKUEN;                      /*!< System PLL clock source update enable                                 */
  __IO uint32_t  USBPLLCLKSEL;                      /*!< USB PLL clock source select                                           */
  __IO uint32_t  USBPLLCLKUEN;                      /*!< USB PLL clock source update enable                                    */
  __I  uint32_t  RESERVED3[8];
  __IO uint32_t  MAINCLKSEL;                        /*!< Main clock source select                                              */
  __IO uint32_t  MAINCLKUEN;                        /*!< Main clock source update enable                                       */
  __IO uint32_t  SYSAHBCLKDIV;                      /*!< System clock divider                                                  */
  __I  uint32_t  RESERVED4;
  __IO uint32_t  SYSAHBCLKCTRL;                     /*!< System clock control                                                  */
  __I  uint32_t  RESERVED5[4];
  __IO uint32_t  SSP0CLKDIV;                        /*!< SSP0 clock divider                                                    */
  __IO uint32_t  USART0CLKDIV;                      /*!< USART0 clock divider                                                  */
  __IO uint32_t  SSP1CLKDIV;                        /*!< SSP1 clock divider                                                    */
  __IO uint32_t  FRGCLKDIV;                         /*!< Clock divider for the common fractional baud rate generator
                                                         of USART1 to USART4                                                   */
  __I  uint32_t  RESERVED6[7];
  __IO uint32_t  USBCLKSEL;                         /*!< USB clock source select                                               */
  __IO uint32_t  USBCLKUEN;                         /*!< USB clock source update enable                                        */
  __IO uint32_t  USBCLKDIV;                         /*!< USB clock source divider                                              */
  __I  uint32_t  RESERVED7[5];
  __IO uint32_t  CLKOUTSEL;                         /*!< CLKOUT clock source select                                            */
  __IO uint32_t  CLKOUTUEN;                         /*!< CLKOUT clock source update enable                                     */
  __IO uint32_t  CLKOUTDIV;                         /*!< CLKOUT clock divider                                                  */
  __I  uint32_t  RESERVED8;
  __IO uint32_t  UARTFRGDIV;                        /*!< USART fractional generator divider value                              */
  __IO uint32_t  UARTFRGMULT;                       /*!< USART fractional generator multiplier value                           */
  __I  uint32_t  RESERVED9;
  __IO uint32_t  EXTTRACECMD;                       /*!< External trace buffer command register                                */
  __I  uint32_t  PIOPORCAP0;                        /*!< POR captured PIO status 0                                             */
  __I  uint32_t  PIOPORCAP1;                        /*!< POR captured PIO status 1                                             */
  __I  uint32_t  PIOPORCAP2;                        /*!< POR captured PIO status 1                                             */
  __I  uint32_t  RESERVED10[10];
  __IO uint32_t  IOCONCLKDIV6;                      /*!< Peripheral clock 6 to the IOCON block for programmable glitch
                                                         filter                                                                */
  __IO uint32_t  IOCONCLKDIV5;                      /*!< Peripheral clock 5 to the IOCON block for programmable glitch
                                                         filter                                                                */
  __IO uint32_t  IOCONCLKDIV4;                      /*!< Peripheral clock 4 to the IOCON block for programmable glitch
                                                         filter                                                                */
  __IO uint32_t  IOCONCLKDIV3;                      /*!< Peripheral clock 3 to the IOCON block for programmable glitch
                                                         filter                                                                */
  __IO uint32_t  IOCONCLKDIV2;                      /*!< Peripheral clock 2 to the IOCON block for programmable glitch
                                                         filter                                                                */
  __IO uint32_t  IOCONCLKDIV1;                      /*!< Peripheral clock 1 to the IOCON block for programmable glitch
                                                         filter                                                                */
  __IO uint32_t  IOCONCLKDIV0;                      /*!< Peripheral clock 0 to the IOCON block for programmable glitch
                                                         filter                                                                */
  __IO uint32_t  BODCTRL;                           /*!< Brown-Out Detect                                                      */
  __IO uint32_t  SYSTCKCAL;                         /*!< System tick counter calibration                                       */
  __IO uint32_t  AHBMATRIXPRIO;                     /*!< AHB matrix priority configuration                                     */
  __I  uint32_t  RESERVED11[5];
  __IO uint32_t  IRQLATENCY;                        /*!< IRQ delay. Allows trade-off between interrupt latency and determinism. */
  __IO uint32_t  NMISRC;                            /*!< NMI Source Control                                                    */
  union {
  __IO uint32_t  PINTSEL[8];
    struct {
    __IO uint32_t  PINTSEL0;                        /*!< GPIO Pin Interrupt Select register 0                                  */
    __IO uint32_t  PINTSEL1;                        /*!< GPIO Pin Interrupt Select register 0                                  */
    __IO uint32_t  PINTSEL2;                        /*!< GPIO Pin Interrupt Select register 0                                  */
    __IO uint32_t  PINTSEL3;                        /*!< GPIO Pin Interrupt Select register 0                                  */
    __IO uint32_t  PINTSEL4;                        /*!< GPIO Pin Interrupt Select register 0                                  */
    __IO uint32_t  PINTSEL5;                        /*!< GPIO Pin Interrupt Select register 0                                  */
    __IO uint32_t  PINTSEL6;                        /*!< GPIO Pin Interrupt Select register 0                                  */
    __IO uint32_t  PINTSEL7;                        /*!< GPIO Pin Interrupt Select register 0                                  */
    };
  };
  __IO uint32_t  USBCLKCTRL;                        /*!< USB clock control                                                     */
  __I  uint32_t  USBCLKST;                          /*!< USB clock status                                                      */
  __I  uint32_t  RESERVED12[25];
  __IO uint32_t  STARTERP0;                         /*!< Start logic 0 interrupt wake-up enable register 0                     */
  __I  uint32_t  RESERVED13[3];
  __IO uint32_t  STARTERP1;                         /*!< Start logic 1 interrupt wake-up enable register 1                     */
  __I  uint32_t  RESERVED14[6];
  __IO uint32_t  PDSLEEPCFG;                        /*!< Power-down states in deep-sleep mode                                  */
  __IO uint32_t  PDAWAKECFG;                        /*!< Power-down states for wake-up from deep-sleep                         */
  __IO uint32_t  PDRUNCFG;                          /*!< Power configuration register                                          */
  __I  uint32_t  RESERVED15[110];
  __I  uint32_t  DEVICE_ID;                         /*!< Device ID                                                             */
} LPC_SYSCON_Type;


/* ================================================================================ */
/* ================                     USART4                     ================ */
/* ================================================================================ */


/**
  * @brief USART4  (USART4)
  */

typedef struct {                                    /*!< USART4 Structure                                                      */
  __IO uint32_t  CFG;                               /*!< USART Configuration register. Basic USART configuration settings
                                                         that typically are not changed during operation.                      */
  __IO uint32_t  CTL;                               /*!< USART Control register. USART control settings that are more
                                                         likely to change during operation.                                    */
  __IO uint32_t  STAT;                              /*!< USART Status register. The complete status value can be read
                                                         here. Writing ones clears some bits in the register. Some bits
                                                          can be cleared by writing a 1 to them.                               */
  __IO uint32_t  INTENSET;                          /*!< Interrupt Enable read and Set register. Contains an individual
                                                         interrupt enable bit for each potential USART interrupt. A complete
                                                          value may be read from this register. Writing a 1 to any implemented
                                                          bit position causes that bit to be set.                              */
  __O  uint32_t  INTENCLR;                          /*!< Interrupt Enable Clear register. Allows clearing any combination
                                                         of bits in the INTENSET register. Writing a 1 to any implemented
                                                          bit position causes the corresponding bit to be cleared.             */
  __I  uint32_t  RXDAT;                             /*!< Receiver Data register. Contains the last character received.         */
  __I  uint32_t  RXDATSTAT;                         /*!< Receiver Data with Status register. Combines the last character
                                                         received with the current USART receive status. Allows DMA or
                                                          software to recover incoming data and status together.               */
  __IO uint32_t  TXDAT;                             /*!< Transmit Data register. Data to be transmitted is written here.       */
  __IO uint32_t  BRG;                               /*!< Baud Rate Generator register. 16-bit integer baud rate divisor
                                                         value.                                                                */
  __I  uint32_t  INTSTAT;                           /*!< Interrupt status register. Reflects interrupts that are currently
                                                         enabled.                                                              */
  __IO uint32_t  OSR;                               /*!< Oversample selection register for asynchronous communication.         */
  __IO uint32_t  ADDR;                              /*!< Address register for automatic address matching.                      */
} LPC_USART4_Type;


/* ================================================================================ */
/* ================                      GINT0                     ================ */
/* ================================================================================ */


/**
  * @brief GPIO group interrupt 0 (GINT0)
  */

typedef struct {                                    /*!< GINT0 Structure                                                       */
  __IO uint32_t  CTRL;                              /*!< GPIO grouped interrupt control register                               */
  __I  uint32_t  RESERVED0[7];
  __IO uint32_t  PORT_POL[3];                       /*!< GPIO grouped interrupt port 0 polarity register                       */
  __I  uint32_t  RESERVED1[5];
  __IO uint32_t  PORT_ENA[3];                       /*!< GPIO grouped interrupt port enable register                           */
} LPC_GINT0_Type;


/* ================================================================================ */
/* ================                       USB                      ================ */
/* ================================================================================ */


/**
  * @brief USB device controller (USB)
  */

typedef struct {                                    /*!< USB Structure                                                         */
  __IO uint32_t  DEVCMDSTAT;                        /*!< USB Device Command/Status register                                    */
  __IO uint32_t  INFO;                              /*!< USB Info register                                                     */
  __IO uint32_t  EPLISTSTART;                       /*!< USB EP Command/Status List start address                              */
  __IO uint32_t  DATABUFSTART;                      /*!< USB Data buffer start address                                         */
  __IO uint32_t  LPM;                               /*!< Link Power Management register                                        */
  __IO uint32_t  EPSKIP;                            /*!< USB Endpoint skip                                                     */
  __IO uint32_t  EPINUSE;                           /*!< USB Endpoint Buffer in use                                            */
  __IO uint32_t  EPBUFCFG;                          /*!< USB Endpoint Buffer Configuration register                            */
  __IO uint32_t  INTSTAT;                           /*!< USB interrupt status register                                         */
  __IO uint32_t  INTEN;                             /*!< USB interrupt enable register                                         */
  __IO uint32_t  INTSETSTAT;                        /*!< USB set interrupt status register                                     */
  __IO uint32_t  INTROUTING;                        /*!< USB interrupt routing register                                        */
  __I  uint32_t  RESERVED0;
  __I  uint32_t  EPTOGGLE;                          /*!< USB Endpoint toggle register                                          */
} LPC_USB_Type;


/* ================================================================================ */
/* ================                       CRC                      ================ */
/* ================================================================================ */


/**
  * @brief Cyclic Redundancy Check (CRC) engine (CRC)
  */

typedef struct {                                    /*!< CRC Structure                                                         */
  __IO uint32_t  MODE;                              /*!< CRC mode register                                                     */
  __IO uint32_t  SEED;                              /*!< CRC seed register                                                     */
  
  union {
    __O  uint32_t  WR_DATA;                         /*!< CRC data register                                                     */
    __I  uint32_t  SUM;                             /*!< CRC checksum register                                                 */
  };
} LPC_CRC_Type;


/* ================================================================================ */
/* ================                       DMA                      ================ */
/* ================================================================================ */


/**
  * @brief Product name title=Kylin UM Chapter title=KylinDMA controller Modification date=5/13/2013 Major revision=0 Minor revision=1  (DMA)
  */

typedef struct {                                    /*!< DMA Structure                                                         */
  __IO uint32_t  CTRL;                              /*!< DMA control.                                                          */
  __I  uint32_t  INTSTAT;                           /*!< Interrupt status.                                                     */
  __IO uint32_t  SRAMBASE;                          /*!< SRAM address of the channel configuration table.                      */
  __I  uint32_t  RESERVED0[5];
  __IO uint32_t  ENABLESET0;                        /*!< Channel Enable read and Set for all DMA channels.                     */
  __I  uint32_t  RESERVED1;
  __O  uint32_t  ENABLECLR0;                        /*!< Channel Enable Clear for all DMA channels.                            */
  __I  uint32_t  RESERVED2;
  __I  uint32_t  ACTIVE0;                           /*!< Channel Active status for all DMA channels.                           */
  __I  uint32_t  RESERVED3;
  __I  uint32_t  BUSY0;                             /*!< Channel Busy status for all DMA channels.                             */
  __I  uint32_t  RESERVED4;
  __IO uint32_t  ERRINT0;                           /*!< Error Interrupt status for all DMA channels.                          */
  __I  uint32_t  RESERVED5;
  __IO uint32_t  INTENSET0;                         /*!< Interrupt Enable read and Set for all DMA channels.                   */
  __I  uint32_t  RESERVED6;
  __O  uint32_t  INTENCLR0;                         /*!< Interrupt Enable Clear for all DMA channels.                          */
  __I  uint32_t  RESERVED7;
  __IO uint32_t  INTA0;                             /*!< Interrupt A status for all DMA channels.                              */
  __I  uint32_t  RESERVED8;
  __IO uint32_t  INTB0;                             /*!< Interrupt B status for all DMA channels.                              */
  __I  uint32_t  RESERVED9;
  __O  uint32_t  SETVALID0;                         /*!< Set ValidPending control bits for all DMA channels.                   */
  __I  uint32_t  RESERVED10;
  __O  uint32_t  SETTRIG0;                          /*!< Set Trigger control bits for all DMA channels.                        */
  __I  uint32_t  RESERVED11;
  __O  uint32_t  ABORT0;                            /*!< Channel Abort control for all DMA channels.                           */
  __I  uint32_t  RESERVED12[225];
  __IO uint32_t  CFG0;                              /*!< Configuration register for DMA channel 0.                             */
  __I  uint32_t  CTLSTAT0;                          /*!< Control and status register for DMA channel 0.                        */
  __IO uint32_t  XFERCFG0;                          /*!< Transfer configuration register for DMA channel 0.                    */
  __I  uint32_t  RESERVED13;
  __IO uint32_t  CFG1;                              /*!< Configuration register for DMA channel 0.                             */
  __I  uint32_t  CTLSTAT1;                          /*!< Control and status register for DMA channel 0.                        */
  __IO uint32_t  XFERCFG1;                          /*!< Transfer configuration register for DMA channel 0.                    */
  __I  uint32_t  RESERVED14;
  __IO uint32_t  CFG2;                              /*!< Configuration register for DMA channel 0.                             */
  __I  uint32_t  CTLSTAT2;                          /*!< Control and status register for DMA channel 0.                        */
  __IO uint32_t  XFERCFG2;                          /*!< Transfer configuration register for DMA channel 0.                    */
  __I  uint32_t  RESERVED15;
  __IO uint32_t  CFG3;                              /*!< Configuration register for DMA channel 0.                             */
  __I  uint32_t  CTLSTAT3;                          /*!< Control and status register for DMA channel 0.                        */
  __IO uint32_t  XFERCFG3;                          /*!< Transfer configuration register for DMA channel 0.                    */
  __I  uint32_t  RESERVED16;
  __IO uint32_t  CFG4;                              /*!< Configuration register for DMA channel 0.                             */
  __I  uint32_t  CTLSTAT4;                          /*!< Control and status register for DMA channel 0.                        */
  __IO uint32_t  XFERCFG4;                          /*!< Transfer configuration register for DMA channel 0.                    */
  __I  uint32_t  RESERVED17;
  __IO uint32_t  CFG5;                              /*!< Configuration register for DMA channel 0.                             */
  __I  uint32_t  CTLSTAT5;                          /*!< Control and status register for DMA channel 0.                        */
  __IO uint32_t  XFERCFG5;                          /*!< Transfer configuration register for DMA channel 0.                    */
  __I  uint32_t  RESERVED18;
  __IO uint32_t  CFG6;                              /*!< Configuration register for DMA channel 0.                             */
  __I  uint32_t  CTLSTAT6;                          /*!< Control and status register for DMA channel 0.                        */
  __IO uint32_t  XFERCFG6;                          /*!< Transfer configuration register for DMA channel 0.                    */
  __I  uint32_t  RESERVED19;
  __IO uint32_t  CFG7;                              /*!< Configuration register for DMA channel 0.                             */
  __I  uint32_t  CTLSTAT7;                          /*!< Control and status register for DMA channel 0.                        */
  __IO uint32_t  XFERCFG7;                          /*!< Transfer configuration register for DMA channel 0.                    */
  __I  uint32_t  RESERVED20;
  __IO uint32_t  CFG8;                              /*!< Configuration register for DMA channel 0.                             */
  __I  uint32_t  CTLSTAT8;                          /*!< Control and status register for DMA channel 0.                        */
  __IO uint32_t  XFERCFG8;                          /*!< Transfer configuration register for DMA channel 0.                    */
  __I  uint32_t  RESERVED21;
  __IO uint32_t  CFG9;                              /*!< Configuration register for DMA channel 0.                             */
  __I  uint32_t  CTLSTAT9;                          /*!< Control and status register for DMA channel 0.                        */
  __IO uint32_t  XFERCFG9;                          /*!< Transfer configuration register for DMA channel 0.                    */
  __I  uint32_t  RESERVED22;
  __IO uint32_t  CFG10;                             /*!< Configuration register for DMA channel 0.                             */
  __I  uint32_t  CTLSTAT10;                         /*!< Control and status register for DMA channel 0.                        */
  __IO uint32_t  XFERCFG10;                         /*!< Transfer configuration register for DMA channel 0.                    */
  __I  uint32_t  RESERVED23;
  __IO uint32_t  CFG11;                             /*!< Configuration register for DMA channel 0.                             */
  __I  uint32_t  CTLSTAT11;                         /*!< Control and status register for DMA channel 0.                        */
  __IO uint32_t  XFERCFG11;                         /*!< Transfer configuration register for DMA channel 0.                    */
  __I  uint32_t  RESERVED24;
  __IO uint32_t  CFG12;                             /*!< Configuration register for DMA channel 0.                             */
  __I  uint32_t  CTLSTAT12;                         /*!< Control and status register for DMA channel 0.                        */
  __IO uint32_t  XFERCFG12;                         /*!< Transfer configuration register for DMA channel 0.                    */
  __I  uint32_t  RESERVED25;
  __IO uint32_t  CFG13;                             /*!< Configuration register for DMA channel 0.                             */
  __I  uint32_t  CTLSTAT13;                         /*!< Control and status register for DMA channel 0.                        */
  __IO uint32_t  XFERCFG13;                         /*!< Transfer configuration register for DMA channel 0.                    */
  __I  uint32_t  RESERVED26;
  __IO uint32_t  CFG14;                             /*!< Configuration register for DMA channel 0.                             */
  __I  uint32_t  CTLSTAT14;                         /*!< Control and status register for DMA channel 0.                        */
  __IO uint32_t  XFERCFG14;                         /*!< Transfer configuration register for DMA channel 0.                    */
  __I  uint32_t  RESERVED27;
  __IO uint32_t  CFG15;                             /*!< Configuration register for DMA channel 0.                             */
  __I  uint32_t  CTLSTAT15;                         /*!< Control and status register for DMA channel 0.                        */
  __IO uint32_t  XFERCFG15;                         /*!< Transfer configuration register for DMA channel 0.                    */
} LPC_DMA_Type;


/* ================================================================================ */
/* ================                      SCT0                      ================ */
/* ================================================================================ */


/**
  * @brief Product name title=Kylin UM Chapter title=KylinState Configurable Timers (SCT0/1) Modification date=5/14/2013 Major revision=0 Minor revision=1  (SCT0)
  */

typedef struct {                                    /*!< SCT0 Structure                                                        */
  __IO uint32_t  CONFIG;                            /*!< SCT configuration register                                            */
  __IO uint32_t  CTRL;                              /*!< SCT control register                                                  */
  __IO uint32_t  LIMIT;                             /*!< SCT limit register                                                    */
  __IO uint32_t  HALT;                              /*!< SCT halt condition register                                           */
  __IO uint32_t  STOP;                              /*!< SCT stop condition register                                           */
  __IO uint32_t  START;                             /*!< SCT start condition register                                          */
  __I  uint32_t  RESERVED0[10];
  __IO uint32_t  COUNT;                             /*!< SCT counter register                                                  */
  __IO uint32_t  STATE;                             /*!< SCT state register                                                    */
  __I  uint32_t  INPUT;                             /*!< SCT input register                                                    */
  __IO uint32_t  REGMODE;                           /*!< SCT match/capture registers mode register                             */
  __IO uint32_t  OUTPUT;                            /*!< SCT output register                                                   */
  __IO uint32_t  OUTPUTDIRCTRL;                     /*!< SCT output counter direction control register                         */
  __IO uint32_t  RES;                               /*!< SCT conflict resolution register                                      */
  __IO uint32_t  DMAREQ0;                           /*!< SCT DMA request 0 register                                            */
  __IO uint32_t  DMAREQ1;                           /*!< SCT DMA request 1 register                                            */
  __I  uint32_t  RESERVED1[35];
  __IO uint32_t  EVEN;                              /*!< SCT event enable register                                             */
  __IO uint32_t  EVFLAG;                            /*!< SCT event flag register                                               */
  __IO uint32_t  CONEN;                             /*!< SCT conflict enable register                                          */
  __IO uint32_t  CONFLAG;                           /*!< SCT conflict flag register                                            */
  
  union {
    __IO uint32_t  CAP0;                            /*!< SCT capture register of capture channel 0 to 4; REGMOD0 to REGMODE4
                                                         = 1                                                                   */
    __IO uint32_t  MATCH0;                          /*!< SCT match value register of match channels 0 to 4; REGMOD0 to
                                                         REGMODE4 = 0                                                          */
  };
  
  union {
    __IO uint32_t  CAP1;                            /*!< SCT capture register of capture channel 0 to 4; REGMOD0 to REGMODE4
                                                         = 1                                                                   */
    __IO uint32_t  MATCH1;                          /*!< SCT match value register of match channels 0 to 4; REGMOD0 to
                                                         REGMODE4 = 0                                                          */
  };
  
  union {
    __IO uint32_t  MATCH2;                          /*!< SCT match value register of match channels 0 to 4; REGMOD0 to
                                                         REGMODE4 = 0                                                          */
    __IO uint32_t  CAP2;                            /*!< SCT capture register of capture channel 0 to 4; REGMOD0 to REGMODE4
                                                         = 1                                                                   */
  };
  
  union {
    __IO uint32_t  CAP3;                            /*!< SCT capture register of capture channel 0 to 4; REGMOD0 to REGMODE4
                                                         = 1                                                                   */
    __IO uint32_t  MATCH3;                          /*!< SCT match value register of match channels 0 to 4; REGMOD0 to
                                                         REGMODE4 = 0                                                          */
  };
  
  union {
    __IO uint32_t  CAP4;                            /*!< SCT capture register of capture channel 0 to 4; REGMOD0 to REGMODE4
                                                         = 1                                                                   */
    __IO uint32_t  MATCH4;                          /*!< SCT match value register of match channels 0 to 4; REGMOD0 to
                                                         REGMODE4 = 0                                                          */
  };
  __I  uint32_t  RESERVED2[59];
  
  union {
    __IO uint32_t  CAPCTRL0;                        /*!< SCT capture control register 0 to 4; REGMOD0 = 1 to REGMODE4
                                                         = 1                                                                   */
    __IO uint32_t  MATCHREL0;                       /*!< SCT match reload value register 0 to 4; REGMOD0 = 0 to REGMODE4
                                                         = 0                                                                   */
  };
  
  union {
    __IO uint32_t  MATCHREL1;                       /*!< SCT match reload value register 0 to 4; REGMOD0 = 0 to REGMODE4
                                                         = 0                                                                   */
    __IO uint32_t  CAPCTRL1;                        /*!< SCT capture control register 0 to 4; REGMOD0 = 1 to REGMODE4
                                                         = 1                                                                   */
  };
  
  union {
    __IO uint32_t  MATCHREL2;                       /*!< SCT match reload value register 0 to 4; REGMOD0 = 0 to REGMODE4
                                                         = 0                                                                   */
    __IO uint32_t  CAPCTRL2;                        /*!< SCT capture control register 0 to 4; REGMOD0 = 1 to REGMODE4
                                                         = 1                                                                   */
  };
  
  union {
    __IO uint32_t  CAPCTRL3;                        /*!< SCT capture control register 0 to 4; REGMOD0 = 1 to REGMODE4
                                                         = 1                                                                   */
    __IO uint32_t  MATCHREL3;                       /*!< SCT match reload value register 0 to 4; REGMOD0 = 0 to REGMODE4
                                                         = 0                                                                   */
  };
  
  union {
    __IO uint32_t  CAPCTRL4;                        /*!< SCT capture control register 0 to 4; REGMOD0 = 1 to REGMODE4
                                                         = 1                                                                   */
    __IO uint32_t  MATCHREL4;                       /*!< SCT match reload value register 0 to 4; REGMOD0 = 0 to REGMODE4
                                                         = 0                                                                   */
  };
  __I  uint32_t  RESERVED3[59];
  __IO uint32_t  EV0_STATE;                         /*!< SCT event state register 0                                            */
  __IO uint32_t  EV0_CTRL;                          /*!< SCT event control register 0                                          */
  __IO uint32_t  EV1_STATE;                         /*!< SCT event state register 0                                            */
  __IO uint32_t  EV1_CTRL;                          /*!< SCT event control register 0                                          */
  __IO uint32_t  EV2_STATE;                         /*!< SCT event state register 0                                            */
  __IO uint32_t  EV2_CTRL;                          /*!< SCT event control register 0                                          */
  __IO uint32_t  EV3_STATE;                         /*!< SCT event state register 0                                            */
  __IO uint32_t  EV3_CTRL;                          /*!< SCT event control register 0                                          */
  __IO uint32_t  EV4_STATE;                         /*!< SCT event state register 0                                            */
  __IO uint32_t  EV4_CTRL;                          /*!< SCT event control register 0                                          */
  __IO uint32_t  EV5_STATE;                         /*!< SCT event state register 0                                            */
  __IO uint32_t  EV5_CTRL;                          /*!< SCT event control register 0                                          */
  __I  uint32_t  RESERVED4[116];
  __IO uint32_t  OUT0_SET;                          /*!< SCT output 0 set register                                             */
  __IO uint32_t  OUT0_CLR;                          /*!< SCT output 0 clear register                                           */
  __IO uint32_t  OUT1_SET;                          /*!< SCT output 0 set register                                             */
  __IO uint32_t  OUT1_CLR;                          /*!< SCT output 0 clear register                                           */
  __IO uint32_t  OUT2_SET;                          /*!< SCT output 0 set register                                             */
  __IO uint32_t  OUT2_CLR;                          /*!< SCT output 0 clear register                                           */
  __IO uint32_t  OUT3_SET;                          /*!< SCT output 0 set register                                             */
  __IO uint32_t  OUT3_CLR;                          /*!< SCT output 0 clear register                                           */
} LPC_SCT0_Type;


/* ================================================================================ */
/* ================                    GPIO_PORT                   ================ */
/* ================================================================================ */


/**
  * @brief General Purpose I/O (GPIO)  (GPIO_PORT)
  */

typedef struct {                                    /*!< GPIO_PORT Structure                                                   */
  __IO uint8_t   B[88];                             /*!< Byte pin registers                                                    */
  __I  uint32_t  RESERVED0[42];
  __IO uint32_t  W[88];                             /*!< Word pin registers                                                    */
  __I  uint32_t  RESERVED1[1896];
  __IO uint32_t  DIR[3];                            /*!< Port Direction registers                                              */
  __I  uint32_t  RESERVED2[29];
  __IO uint32_t  MASK[3];                           /*!< Port Mask register                                                    */
  __I  uint32_t  RESERVED3[29];
  __IO uint32_t  PIN[3];                            /*!< Port pin register                                                     */
  __I  uint32_t  RESERVED4[29];
  __IO uint32_t  MPIN[3];                           /*!< Masked port register                                                  */
  __I  uint32_t  RESERVED5[29];
  __IO uint32_t  SET[3];                            /*!< Write: Set port register Read: port output bits                       */
  __I  uint32_t  RESERVED6[29];
  __O  uint32_t  CLR[3];                            /*!< Clear port                                                            */
  __I  uint32_t  RESERVED7[29];
  __O  uint32_t  NOT[3];                            /*!< Toggle port                                                           */
} LPC_GPIO_PORT_Type;


/* ================================================================================ */
/* ================                      PINT                      ================ */
/* ================================================================================ */


/**
  * @brief Pin interruptand pattern match (PINT)  (PINT)
  */

typedef struct {                                    /*!< PINT Structure                                                        */
  __IO uint32_t  ISEL;                              /*!< Pin Interrupt Mode register                                           */
  __IO uint32_t  IENR;                              /*!< Pin interrupt level or rising edge interrupt enable register          */
  __O  uint32_t  SIENR;                             /*!< Pin interrupt level or rising edge interrupt set register             */
  __O  uint32_t  CIENR;                             /*!< Pin interrupt level (rising edge interrupt) clear register            */
  __IO uint32_t  IENF;                              /*!< Pin interrupt active level or falling edge interrupt enable
                                                         register                                                              */
  __O  uint32_t  SIENF;                             /*!< Pin interrupt active level or falling edge interrupt set register     */
  __O  uint32_t  CIENF;                             /*!< Pin interrupt active level or falling edge interrupt clear register   */
  __IO uint32_t  RISE;                              /*!< Pin interrupt rising edge register                                    */
  __IO uint32_t  FALL;                              /*!< Pin interrupt falling edge register                                   */
  __IO uint32_t  IST;                               /*!< Pin interrupt status register                                         */
  __IO uint32_t  PMCTRL;                            /*!< Pattern match interrupt control register                              */
  __IO uint32_t  PMSRC;                             /*!< Pattern match interrupt bit-slice source register                     */
  __IO uint32_t  PMCFG;                             /*!< Pattern match interrupt bit slice configuration register              */
} LPC_PINT_Type;


/* --------------------  End of section using anonymous unions  ------------------- */
#if defined(__CC_ARM)
  #pragma pop
#elif defined(__ICCARM__)
  /* leave anonymous unions enabled */
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined(__TASKING__)
  #pragma warning restore
#else
  #warning Not supported compiler type
#endif




/* ================================================================================ */
/* ================              Peripheral memory map             ================ */
/* ================================================================================ */

#define LPC_I2C0_BASE                   0x40000000UL
#define LPC_WWDT_BASE                   0x40004000UL
#define LPC_USART0_BASE                 0x40008000UL
#define LPC_CT16B0_BASE                 0x4000C000UL
#define LPC_CT16B1_BASE                 0x40010000UL
#define LPC_CT32B0_BASE                 0x40014000UL
#define LPC_CT32B1_BASE                 0x40018000UL
#define LPC_ADC_BASE                    0x4001C000UL
#define LPC_I2C1_BASE                   0x40020000UL
#define LPC_RTC_BASE                    0x40024000UL
#define LPC_DMATRIGMUX_BASE             0x40028000UL
#define LPC_PMU_BASE                    0x40038000UL
#define LPC_FLASHCTRL_BASE              0x4003C000UL
#define LPC_SSP0_BASE                   0x40040000UL
#define LPC_IOCON_BASE                  0x40044000UL
#define LPC_SYSCON_BASE                 0x40048000UL
#define LPC_USART4_BASE                 0x4004C000UL
#define LPC_SSP1_BASE                   0x40058000UL
#define LPC_GINT0_BASE                  0x4005C000UL
#define LPC_GINT1_BASE                  0x40060000UL
#define LPC_USART1_BASE                 0x4006C000UL
#define LPC_USART2_BASE                 0x40070000UL
#define LPC_USART3_BASE                 0x40074000UL
#define LPC_USB_BASE                    0x40080000UL
#define LPC_CRC_BASE                    0x50000000UL
#define LPC_DMA_BASE                    0x50004000UL
#define LPC_SCT0_BASE                   0x5000C000UL
#define LPC_SCT1_BASE                   0x5000E000UL
#define LPC_GPIO_PORT_BASE              0xA0000000UL
#define LPC_PINT_BASE                   0xA0004000UL


/* ================================================================================ */
/* ================             Peripheral declaration             ================ */
/* ================================================================================ */

#define LPC_I2C0                        ((LPC_I2C0_Type           *) LPC_I2C0_BASE)
#define LPC_WWDT                        ((LPC_WWDT_Type           *) LPC_WWDT_BASE)
#define LPC_USART0                      ((LPC_USART0_Type         *) LPC_USART0_BASE)
#define LPC_CT16B0                      ((LPC_CT16B0_Type         *) LPC_CT16B0_BASE)
#define LPC_CT16B1                      ((LPC_CT16B0_Type         *) LPC_CT16B1_BASE)
#define LPC_CT32B0                      ((LPC_CT32B0_Type         *) LPC_CT32B0_BASE)
#define LPC_CT32B1                      ((LPC_CT32B0_Type         *) LPC_CT32B1_BASE)
#define LPC_ADC                         ((LPC_ADC_Type            *) LPC_ADC_BASE)
#define LPC_I2C1                        ((LPC_I2C0_Type           *) LPC_I2C1_BASE)
#define LPC_RTC                         ((LPC_RTC_Type            *) LPC_RTC_BASE)
#define LPC_DMATRIGMUX                  ((LPC_DMATRIGMUX_Type     *) LPC_DMATRIGMUX_BASE)
#define LPC_PMU                         ((LPC_PMU_Type            *) LPC_PMU_BASE)
#define LPC_FLASHCTRL                   ((LPC_FLASHCTRL_Type      *) LPC_FLASHCTRL_BASE)
#define LPC_SSP0                        ((LPC_SSP0_Type           *) LPC_SSP0_BASE)
#define LPC_IOCON                       ((LPC_IOCON_Type          *) LPC_IOCON_BASE)
#define LPC_SYSCON                      ((LPC_SYSCON_Type         *) LPC_SYSCON_BASE)
#define LPC_USART4                      ((LPC_USART4_Type         *) LPC_USART4_BASE)
#define LPC_SSP1                        ((LPC_SSP0_Type           *) LPC_SSP1_BASE)
#define LPC_GINT0                       ((LPC_GINT0_Type          *) LPC_GINT0_BASE)
#define LPC_GINT1                       ((LPC_GINT0_Type          *) LPC_GINT1_BASE)
#define LPC_USART1                      ((LPC_USART4_Type         *) LPC_USART1_BASE)
#define LPC_USART2                      ((LPC_USART4_Type         *) LPC_USART2_BASE)
#define LPC_USART3                      ((LPC_USART4_Type         *) LPC_USART3_BASE)
#define LPC_USB                         ((LPC_USB_Type            *) LPC_USB_BASE)
#define LPC_CRC                         ((LPC_CRC_Type            *) LPC_CRC_BASE)
#define LPC_DMA                         ((LPC_DMA_Type            *) LPC_DMA_BASE)
#define LPC_SCT0                        ((LPC_SCT0_Type           *) LPC_SCT0_BASE)
#define LPC_SCT1                        ((LPC_SCT0_Type           *) LPC_SCT1_BASE)
#define LPC_GPIO_PORT                   ((LPC_GPIO_PORT_Type      *) LPC_GPIO_PORT_BASE)
#define LPC_PINT                        ((LPC_PINT_Type           *) LPC_PINT_BASE)


/** @} */ /* End of group Device_Peripheral_Registers */
/** @} */ /* End of group LPC11U6x */
/** @} */ /* End of group (null) */

#ifdef __cplusplus
}
#endif


#endif  /* LPC11U6x_H */

