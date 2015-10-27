
/****************************************************************************************************//**
 * @file     LPC82x.h
 *
 * @brief    CMSIS Cortex-M0PLUS Peripheral Access Layer Header File for
 *           LPC82x from .
 *
 * @version  V0.4
 * @date     17. June 2014
 *
 * @note     Generated with SVDConv V2.80 
 *           from CMSIS SVD File 'LPC82x.svd' Version 0.4,
 *******************************************************************************************************/



/** @addtogroup (null)
  * @{
  */

/** @addtogroup LPC82x
  * @{
  */

#ifndef LPC82X_H
#define LPC82X_H

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
  DebugMonitor_IRQn             =  -4,              /*!<  12  Debug Monitor                                                    */
  PendSV_IRQn                   =  -2,              /*!<  14  Pendable request for system service                              */
  SysTick_IRQn                  =  -1,              /*!<  15  System Tick Timer                                                */
/* ----------------------  LPC82x Specific Interrupt Numbers  --------------------- */
  SPI0_IRQn                     =   0,              /*!<   0  SPI0                                                             */
  SPI1_IRQn                     =   1,              /*!<   1  SPI1                                                             */
  UART0_IRQn                    =   3,              /*!<   3  UART0                                                            */
  UART1_IRQn                    =   4,              /*!<   4  UART1                                                            */
  UART2_IRQn                    =   5,              /*!<   5  UART2                                                            */
  I2C1_IRQn                     =   7,              /*!<   7  I2C1                                                             */
  I2C0_IRQn                     =   8,              /*!<   8  I2C0                                                             */
  SCT_IRQn                      =   9,              /*!<   9  SCT                                                              */
  MRT_IRQn                      =  10,              /*!<  10  MRT                                                              */
  CMP_IRQn                      =  11,              /*!<  11  CMP                                                              */
  WDT_IRQn                      =  12,              /*!<  12  WDT                                                              */
  BOD_IRQn                      =  13,              /*!<  13  BOD                                                              */
  FLASH_IRQn                    =  14,              /*!<  14  FLASH                                                            */
  WKT_IRQn                      =  15,              /*!<  15  WKT                                                              */
  ADC_SEQA_IRQn                 =  16,              /*!<  16  ADC_SEQA                                                         */
  ADC_SEQB_IRQn                 =  17,              /*!<  17  ADC_SEQB                                                         */
  ADC_THCMP_IRQn                =  18,              /*!<  18  ADC_THCMP                                                        */
  ADC_OVR_IRQn                  =  19,              /*!<  19  ADC_OVR                                                          */
  DMA_IRQn                      =  20,              /*!<  20  DMA                                                              */
  I2C2_IRQn                     =  21,              /*!<  21  I2C2                                                             */
  I2C3_IRQn                     =  22,              /*!<  22  I2C3                                                             */
  PIN_INT0_IRQn                 =  24,              /*!<  24  PIN_INT0                                                         */
  PIN_INT1_IRQn                 =  25,              /*!<  25  PIN_INT1                                                         */
  PIN_INT2_IRQn                 =  26,              /*!<  26  PIN_INT2                                                         */
  PIN_INT3_IRQn                 =  27,              /*!<  27  PIN_INT3                                                         */
  PIN_INT4_IRQn                 =  28,              /*!<  28  PIN_INT4                                                         */
  PIN_INT5_IRQn                 =  29,              /*!<  29  PIN_INT5                                                         */
  PIN_INT6_IRQn                 =  30,              /*!<  30  PIN_INT6                                                         */
  PIN_INT7_IRQn                 =  31               /*!<  31  PIN_INT7                                                         */
} IRQn_Type;


/** @addtogroup Configuration_of_CMSIS
  * @{
  */


/* ================================================================================ */
/* ================      Processor and Core Peripheral Section     ================ */
/* ================================================================================ */

/* ----------------Configuration of the Cortex-M0PLUS Processor and Core Peripherals---------------- */
#define __CM0PLUS_REV                 0x0001        /*!< Cortex-M0PLUS Core Revision                                           */
#define __MPU_PRESENT                  0            /*!< MPU present or not                                                    */
#define __NVIC_PRIO_BITS               2            /*!< Number of Bits used for Priority Levels                               */
#define __Vendor_SysTickConfig         0            /*!< Set to 1 if different SysTick Config is used                          */
#define __VTOR_PRESENT                 1            /*!< Set to 1 if CPU supports Vector Table Offset Register                 */
/** @} */ /* End of group Configuration_of_CMSIS */

#include "core_cm0plus.h"                           /*!< Cortex-M0PLUS processor and core peripherals                          */
#include "system_LPC82x.h"                          /*!< LPC82x System                                                         */


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
/* ================                      WWDT                      ================ */
/* ================================================================================ */


/**
  * @brief Windowed Watchdog Timer (WWDT) (WWDT)
  */

typedef struct {                                    /*!< (@ 0x40000000) WWDT Structure                                         */
  __IO uint32_t  MOD;                               /*!< (@ 0x40000000) Watchdog mode register. This register contains
                                                         the basic mode and status of the Watchdog Timer.                      */
  __IO uint32_t  TC;                                /*!< (@ 0x40000004) Watchdog timer constant register. This 24-bit
                                                         register determines the time-out value.                               */
  __O  uint32_t  FEED;                              /*!< (@ 0x40000008) Watchdog feed sequence register. Writing 0xAA
                                                         followed by 0x55 to this register reloads the Watchdog timer
                                                          with the value contained in WDTC.                                    */
  __I  uint32_t  TV;                                /*!< (@ 0x4000000C) Watchdog timer value register. This 24-bit register
                                                         reads out the current value of the Watchdog timer.                    */
  __I  uint32_t  RESERVED0;
  __IO uint32_t  WARNINT;                           /*!< (@ 0x40000014) Watchdog Warning Interrupt compare value.              */
  __IO uint32_t  WINDOW;                            /*!< (@ 0x40000018) Watchdog Window compare value.                         */
} LPC_WWDT_Type;


/* ================================================================================ */
/* ================                       MRT                      ================ */
/* ================================================================================ */


/**
  * @brief Multi-Rate Timer (MRT) (MRT)
  */

typedef struct {                                    /*!< (@ 0x40004000) MRT Structure                                          */
  __IO uint32_t  INTVAL0;                           /*!< (@ 0x40004000) MRT0 Time interval value register. This value
                                                         is loaded into the TIMER0 register.                                   */
  __I  uint32_t  TIMER0;                            /*!< (@ 0x40004004) MRT0 Timer register. This register reads the
                                                         value of the down-counter.                                            */
  __IO uint32_t  CTRL0;                             /*!< (@ 0x40004008) MRT0 Control register. This register controls
                                                         the MRT0 modes.                                                       */
  __IO uint32_t  STAT0;                             /*!< (@ 0x4000400C) MRT0 Status register.                                  */
  __IO uint32_t  INTVAL1;                           /*!< (@ 0x40004010) MRT0 Time interval value register. This value
                                                         is loaded into the TIMER0 register.                                   */
  __I  uint32_t  TIMER1;                            /*!< (@ 0x40004014) MRT0 Timer register. This register reads the
                                                         value of the down-counter.                                            */
  __IO uint32_t  CTRL1;                             /*!< (@ 0x40004018) MRT0 Control register. This register controls
                                                         the MRT0 modes.                                                       */
  __IO uint32_t  STAT1;                             /*!< (@ 0x4000401C) MRT0 Status register.                                  */
  __IO uint32_t  INTVAL2;                           /*!< (@ 0x40004020) MRT0 Time interval value register. This value
                                                         is loaded into the TIMER0 register.                                   */
  __I  uint32_t  TIMER2;                            /*!< (@ 0x40004024) MRT0 Timer register. This register reads the
                                                         value of the down-counter.                                            */
  __IO uint32_t  CTRL2;                             /*!< (@ 0x40004028) MRT0 Control register. This register controls
                                                         the MRT0 modes.                                                       */
  __IO uint32_t  STAT2;                             /*!< (@ 0x4000402C) MRT0 Status register.                                  */
  __IO uint32_t  INTVAL3;                           /*!< (@ 0x40004030) MRT0 Time interval value register. This value
                                                         is loaded into the TIMER0 register.                                   */
  __I  uint32_t  TIMER3;                            /*!< (@ 0x40004034) MRT0 Timer register. This register reads the
                                                         value of the down-counter.                                            */
  __IO uint32_t  CTRL3;                             /*!< (@ 0x40004038) MRT0 Control register. This register controls
                                                         the MRT0 modes.                                                       */
  __IO uint32_t  STAT3;                             /*!< (@ 0x4000403C) MRT0 Status register.                                  */
  __I  uint32_t  RESERVED0[45];
  __I  uint32_t  IDLE_CH;                           /*!< (@ 0x400040F4) Idle channel register. This register returns
                                                         the number of the first idle channel.                                 */
  __IO uint32_t  IRQ_FLAG;                          /*!< (@ 0x400040F8) Global interrupt flag register                         */
} LPC_MRT_Type;


/* ================================================================================ */
/* ================                       WKT                      ================ */
/* ================================================================================ */


/**
  * @brief Self wake-up timer (WKT) (WKT)
  */

typedef struct {                                    /*!< (@ 0x40008000) WKT Structure                                          */
  __IO uint32_t  CTRL;                              /*!< (@ 0x40008000) Self wake-up timer control register.                   */
  __I  uint32_t  RESERVED0[2];
  __IO uint32_t  COUNT;                             /*!< (@ 0x4000800C) Counter register.                                      */
} LPC_WKT_Type;


/* ================================================================================ */
/* ================                       SWM                      ================ */
/* ================================================================================ */


/**
  * @brief Switch matrix (SWM) (SWM)
  */

typedef struct {                                    /*!< (@ 0x4000C000) SWM Structure                                          */
  union {
    __IO uint32_t PINASSIGN[12];
    struct {
      __IO uint32_t  PINASSIGN0;                    /*!< (@ 0x4000C000) Pin assign register 0. Assign movable functions
                                                         U0_TXD, U0_RXD, U0_RTS, U0_CTS.                                       */
      __IO uint32_t  PINASSIGN1;                    /*!< (@ 0x4000C004) Pin assign register 1. Assign movable functions
                                                         U0_SCLK, U1_TXD, U1_RXD, U1_RTS.                                      */
      __IO uint32_t  PINASSIGN2;                    /*!< (@ 0x4000C008) Pin assign register 2. Assign movable functions
                                                         U1_CTS, U1_SCLK, U2_TXD, U2_RXD.                                      */
      __IO uint32_t  PINASSIGN3;                    /*!< (@ 0x4000C00C) Pin assign register 3. Assign movable function
                                                         U2_RTS, U2_CTS, U2_SCLK, SPI0_SCK.                                    */
      __IO uint32_t  PINASSIGN4;                    /*!< (@ 0x4000C010) Pin assign register 4. Assign movable functions
                                                         SPI0_MOSI, SPI0_MISO, SPI0_SSEL0, SPI0_SSEL1.                         */
      __IO uint32_t  PINASSIGN5;                    /*!< (@ 0x4000C014) Pin assign register 5. Assign movable functions
                                                         SPI0_SSEL2, SPI0_SSEL3, SPI1_SCK, SPI1_MOSI                           */
      __IO uint32_t  PINASSIGN6;                    /*!< (@ 0x4000C018) Pin assign register 6. Assign movable functions
                                                         SPI1_MISO, SPI1_SSEL0, SPI1_SSEL1, SCT0_IN0.                          */
      __IO uint32_t  PINASSIGN7;                    /*!< (@ 0x4000C01C) Pin assign register 7. Assign movable functions
                                                         SCT_IN1, SCT_IN2, SCT_IN3, SCT_OUT0.                                  */
      __IO uint32_t  PINASSIGN8;                    /*!< (@ 0x4000C020) Pin assign register 8. Assign movable functions
                                                         SCT_OUT1, SCT_OUT2, SCT_OUT3, SCT_OUT4.                               */
      __IO uint32_t  PINASSIGN9;                    /*!< (@ 0x4000C024) Pin assign register 9. Assign movable functions
                                                         SCT_OUT5, I2C1_SDA, I2C1_SCL, I2C2_SDA.                               */
      __IO uint32_t  PINASSIGN10;                   /*!< (@ 0x4000C028) Pin assign register 10. Assign movable functions
                                                         I2C2_SCL, I2C3_SDA, I2C3_SCL, ADC_PINTRIG0.                           */
      __IO uint32_t  PINASSIGN11;                   /*!< (@ 0x4000C02C) Pin assign register 11. Assign movable functions
                                                         ADC_PINTRIG1, ACMP_O, CLKOUT, GPIO_INT_BMAT                           */
    };
  };
  __I  uint32_t  RESERVED0[100];
  __IO uint32_t  PINENABLE0;                        /*!< (@ 0x4000C1C0) Pin enable register 0. Enables fixed-pin functions
                                                         ACMP_I0, ACMP_I1, SWCLK, SWDIO, XTALIN, XTALOUT, RESET, CLKIN,
                                                          VDDCMP.                                                              */
} LPC_SWM_Type;


/* ================================================================================ */
/* ================                       ADC                      ================ */
/* ================================================================================ */


/**
  * @brief 12-bit Analog-to-Digital Converter (ADC) (ADC)
  */

typedef struct {                                    /*!< (@ 0x4001C000) ADC Structure                                          */
  __IO uint32_t  CTRL;                              /*!< (@ 0x4001C000) A/D Control Register. Contains the clock divide
                                                         value, enable bits for each sequence and the A/D power-down
                                                          bit.                                                                 */
  __I  uint32_t  RESERVED0;
  __IO uint32_t  SEQA_CTRL;                         /*!< (@ 0x4001C008) A/D Conversion Sequence-A control Register: Controls
                                                         triggering and channel selection for conversion sequence-A.
                                                          Also specifies interrupt mode for sequence-A.                        */
  __IO uint32_t  SEQB_CTRL;                         /*!< (@ 0x4001C00C) A/D Conversion Sequence-B Control Register: Controls
                                                         triggering and channel selection for conversion sequence-B.
                                                          Also specifies interrupt mode for sequence-B.                        */
  __IO uint32_t  SEQA_GDAT;                         /*!< (@ 0x4001C010) A/D Sequence-A Global Data Register. This register
                                                         contains the result of the most recent A/D conversion performed
                                                          under sequence-A                                                     */
  __IO uint32_t  SEQB_GDAT;                         /*!< (@ 0x4001C014) A/D Sequence-B Global Data Register. This register
                                                         contains the result of the most recent A/D conversion performed
                                                          under sequence-B                                                     */
  __I  uint32_t  RESERVED1[2];
  __I  uint32_t  DAT0;                              /*!< (@ 0x4001C020) A/D Channel 0 Data Register. This register contains
                                                         the result of the most recent conversion completed on channel
                                                          0.                                                                   */
  __I  uint32_t  DAT1;                              /*!< (@ 0x4001C024) A/D Channel 0 Data Register. This register contains
                                                         the result of the most recent conversion completed on channel
                                                          0.                                                                   */
  __I  uint32_t  DAT2;                              /*!< (@ 0x4001C028) A/D Channel 0 Data Register. This register contains
                                                         the result of the most recent conversion completed on channel
                                                          0.                                                                   */
  __I  uint32_t  DAT3;                              /*!< (@ 0x4001C02C) A/D Channel 0 Data Register. This register contains
                                                         the result of the most recent conversion completed on channel
                                                          0.                                                                   */
  __I  uint32_t  DAT4;                              /*!< (@ 0x4001C030) A/D Channel 0 Data Register. This register contains
                                                         the result of the most recent conversion completed on channel
                                                          0.                                                                   */
  __I  uint32_t  DAT5;                              /*!< (@ 0x4001C034) A/D Channel 0 Data Register. This register contains
                                                         the result of the most recent conversion completed on channel
                                                          0.                                                                   */
  __I  uint32_t  DAT6;                              /*!< (@ 0x4001C038) A/D Channel 0 Data Register. This register contains
                                                         the result of the most recent conversion completed on channel
                                                          0.                                                                   */
  __I  uint32_t  DAT7;                              /*!< (@ 0x4001C03C) A/D Channel 0 Data Register. This register contains
                                                         the result of the most recent conversion completed on channel
                                                          0.                                                                   */
  __I  uint32_t  DAT8;                              /*!< (@ 0x4001C040) A/D Channel 0 Data Register. This register contains
                                                         the result of the most recent conversion completed on channel
                                                          0.                                                                   */
  __I  uint32_t  DAT9;                              /*!< (@ 0x4001C044) A/D Channel 0 Data Register. This register contains
                                                         the result of the most recent conversion completed on channel
                                                          0.                                                                   */
  __I  uint32_t  DAT10;                             /*!< (@ 0x4001C048) A/D Channel 0 Data Register. This register contains
                                                         the result of the most recent conversion completed on channel
                                                          0.                                                                   */
  __I  uint32_t  DAT11;                             /*!< (@ 0x4001C04C) A/D Channel 0 Data Register. This register contains
                                                         the result of the most recent conversion completed on channel
                                                          0.                                                                   */
  __IO uint32_t  THR0_LOW;                          /*!< (@ 0x4001C050) A/D Low Compare Threshold Register 0 : Contains
                                                         the lower threshold level for automatic threshold comparison
                                                          for any channels linked to threshold pair 0.                         */
  __IO uint32_t  THR1_LOW;                          /*!< (@ 0x4001C054) A/D Low Compare Threshold Register 1: Contains
                                                         the lower threshold level for automatic threshold comparison
                                                          for any channels linked to threshold pair 1.                         */
  __IO uint32_t  THR0_HIGH;                         /*!< (@ 0x4001C058) A/D High Compare Threshold Register 0: Contains
                                                         the upper threshold level for automatic threshold comparison
                                                          for any channels linked to threshold pair 0.                         */
  __IO uint32_t  THR1_HIGH;                         /*!< (@ 0x4001C05C) A/D High Compare Threshold Register 1: Contains
                                                         the upper threshold level for automatic threshold comparison
                                                          for any channels linked to threshold pair 1.                         */
  __IO uint32_t  CHAN_THRSEL;                       /*!< (@ 0x4001C060) A/D Channel-Threshold Select Register. Specifies
                                                         which set of threshold compare registers are to be used for
                                                          each channel                                                         */
  __IO uint32_t  INTEN;                             /*!< (@ 0x4001C064) A/D Interrupt Enable Register. This register
                                                         contains enable bits that enable the sequence-A, sequence-B,
                                                          threshold compare and data overrun interrupts to be generated.       */
  __IO uint32_t  FLAGS;                             /*!< (@ 0x4001C068) A/D Flags Register. Contains the four interrupt
                                                         request flags and the individual component overrun and threshold-compare
                                                          flags. (The overrun bits replicate information stored in the
                                                          result registers).                                                   */
  __IO uint32_t  TRM;                               /*!< (@ 0x4001C06C) ADC trim register.                                     */
} LPC_ADC_Type;


/* ================================================================================ */
/* ================                       PMU                      ================ */
/* ================================================================================ */


/**
  * @brief Power Management Unit (PMU) (PMU)
  */

typedef struct {                                    /*!< (@ 0x40020000) PMU Structure                                          */
  __IO uint32_t  PCON;                              /*!< (@ 0x40020000) Power control register                                 */
  __IO uint32_t  GPREG0;                            /*!< (@ 0x40020004) General purpose register 0                             */
  __IO uint32_t  GPREG1;                            /*!< (@ 0x40020008) General purpose register 0                             */
  __IO uint32_t  GPREG2;                            /*!< (@ 0x4002000C) General purpose register 0                             */
  __IO uint32_t  GPREG3;                            /*!< (@ 0x40020010) General purpose register 0                             */
  __IO uint32_t  DPDCTRL;                           /*!< (@ 0x40020014) Deep power-down control register. Also includes
                                                         bits for general purpose storage.                                     */
} LPC_PMU_Type;


/* ================================================================================ */
/* ================                       CMP                      ================ */
/* ================================================================================ */


/**
  * @brief Analog comparator (CMP)
  */

typedef struct {                                    /*!< (@ 0x40024000) CMP Structure                                          */
  __IO uint32_t  CTRL;                              /*!< (@ 0x40024000) Comparator control register                            */
  __IO uint32_t  LAD;                               /*!< (@ 0x40024004) Voltage ladder register                                */
} LPC_CMP_Type;


/* ================================================================================ */
/* ================                   DMATRIGMUX                   ================ */
/* ================================================================================ */


/**
  * @brief DMA trigger mux (DMATRIGMUX)
  */

typedef struct {                                    /*!< (@ 0x40028000) DMATRIGMUX Structure                                   */
  __IO uint32_t  DMA_ITRIG_INMUX0;                  /*!< (@ 0x40028000) Input mux register for trigger inputs 0 to 23
                                                         connected to DMA channel 0. Selects from ADC, SCT, ACMP, pin
                                                          interrupts, and DMA requests.                                        */
  __IO uint32_t  DMA_ITRIG_INMUX1;                  /*!< (@ 0x40028004) Input mux register for trigger inputs 0 to 23
                                                         connected to DMA channel 0. Selects from ADC, SCT, ACMP, pin
                                                          interrupts, and DMA requests.                                        */
  __IO uint32_t  DMA_ITRIG_INMUX2;                  /*!< (@ 0x40028008) Input mux register for trigger inputs 0 to 23
                                                         connected to DMA channel 0. Selects from ADC, SCT, ACMP, pin
                                                          interrupts, and DMA requests.                                        */
  __IO uint32_t  DMA_ITRIG_INMUX3;                  /*!< (@ 0x4002800C) Input mux register for trigger inputs 0 to 23
                                                         connected to DMA channel 0. Selects from ADC, SCT, ACMP, pin
                                                          interrupts, and DMA requests.                                        */
  __IO uint32_t  DMA_ITRIG_INMUX4;                  /*!< (@ 0x40028010) Input mux register for trigger inputs 0 to 23
                                                         connected to DMA channel 0. Selects from ADC, SCT, ACMP, pin
                                                          interrupts, and DMA requests.                                        */
  __IO uint32_t  DMA_ITRIG_INMUX5;                  /*!< (@ 0x40028014) Input mux register for trigger inputs 0 to 23
                                                         connected to DMA channel 0. Selects from ADC, SCT, ACMP, pin
                                                          interrupts, and DMA requests.                                        */
  __IO uint32_t  DMA_ITRIG_INMUX6;                  /*!< (@ 0x40028018) Input mux register for trigger inputs 0 to 23
                                                         connected to DMA channel 0. Selects from ADC, SCT, ACMP, pin
                                                          interrupts, and DMA requests.                                        */
  __IO uint32_t  DMA_ITRIG_INMUX7;                  /*!< (@ 0x4002801C) Input mux register for trigger inputs 0 to 23
                                                         connected to DMA channel 0. Selects from ADC, SCT, ACMP, pin
                                                          interrupts, and DMA requests.                                        */
  __IO uint32_t  DMA_ITRIG_INMUX8;                  /*!< (@ 0x40028020) Input mux register for trigger inputs 0 to 23
                                                         connected to DMA channel 0. Selects from ADC, SCT, ACMP, pin
                                                          interrupts, and DMA requests.                                        */
  __IO uint32_t  DMA_ITRIG_INMUX9;                  /*!< (@ 0x40028024) Input mux register for trigger inputs 0 to 23
                                                         connected to DMA channel 0. Selects from ADC, SCT, ACMP, pin
                                                          interrupts, and DMA requests.                                        */
  __IO uint32_t  DMA_ITRIG_INMUX10;                 /*!< (@ 0x40028028) Input mux register for trigger inputs 0 to 23
                                                         connected to DMA channel 0. Selects from ADC, SCT, ACMP, pin
                                                          interrupts, and DMA requests.                                        */
  __IO uint32_t  DMA_ITRIG_INMUX11;                 /*!< (@ 0x4002802C) Input mux register for trigger inputs 0 to 23
                                                         connected to DMA channel 0. Selects from ADC, SCT, ACMP, pin
                                                          interrupts, and DMA requests.                                        */
  __IO uint32_t  DMA_ITRIG_INMUX12;                 /*!< (@ 0x40028030) Input mux register for trigger inputs 0 to 23
                                                         connected to DMA channel 0. Selects from ADC, SCT, ACMP, pin
                                                          interrupts, and DMA requests.                                        */
  __IO uint32_t  DMA_ITRIG_INMUX13;                 /*!< (@ 0x40028034) Input mux register for trigger inputs 0 to 23
                                                         connected to DMA channel 0. Selects from ADC, SCT, ACMP, pin
                                                          interrupts, and DMA requests.                                        */
  __IO uint32_t  DMA_ITRIG_INMUX14;                 /*!< (@ 0x40028038) Input mux register for trigger inputs 0 to 23
                                                         connected to DMA channel 0. Selects from ADC, SCT, ACMP, pin
                                                          interrupts, and DMA requests.                                        */
  __IO uint32_t  DMA_ITRIG_INMUX15;                 /*!< (@ 0x4002803C) Input mux register for trigger inputs 0 to 23
                                                         connected to DMA channel 0. Selects from ADC, SCT, ACMP, pin
                                                          interrupts, and DMA requests.                                        */
  __IO uint32_t  DMA_ITRIG_INMUX16;                 /*!< (@ 0x40028040) Input mux register for trigger inputs 0 to 23
                                                         connected to DMA channel 0. Selects from ADC, SCT, ACMP, pin
                                                          interrupts, and DMA requests.                                        */
  __IO uint32_t  DMA_ITRIG_INMUX17;                 /*!< (@ 0x40028044) Input mux register for trigger inputs 0 to 23
                                                         connected to DMA channel 0. Selects from ADC, SCT, ACMP, pin
                                                          interrupts, and DMA requests.                                        */
} LPC_DMATRIGMUX_Type;


/* ================================================================================ */
/* ================                    INPUTMUX                    ================ */
/* ================================================================================ */


/**
  * @brief Input multiplexing  (INPUTMUX)
  */

typedef struct {                                    /*!< (@ 0x4002C000) INPUTMUX Structure                                     */
  __IO uint32_t  DMA_INMUX_INMUX0;                  /*!< (@ 0x4002C000) Input mux register for DMA trigger input 20.
                                                         Selects from 18 DMA trigger outputs.                                  */
  __IO uint32_t  DMA_INMUX_INMUX1;                  /*!< (@ 0x4002C004) Input mux register for DMA trigger input 20.
                                                         Selects from 18 DMA trigger outputs.                                  */
  __I  uint32_t  RESERVED0[6];
  __IO uint32_t  SCT0_INMUX0;                       /*!< (@ 0x4002C020) Input mux register for SCT input 0                     */
  __IO uint32_t  SCT0_INMUX1;                       /*!< (@ 0x4002C024) Input mux register for SCT input 0                     */
  __IO uint32_t  SCT0_INMUX2;                       /*!< (@ 0x4002C028) Input mux register for SCT input 0                     */
  __IO uint32_t  SCT0_INMUX3;                       /*!< (@ 0x4002C02C) Input mux register for SCT input 0                     */
} LPC_INPUTMUX_Type;


/* ================================================================================ */
/* ================                    FLASHCTRL                   ================ */
/* ================================================================================ */


/**
  * @brief Flash controller  (FLASHCTRL)
  */

typedef struct {                                    /*!< (@ 0x40040000) FLASHCTRL Structure                                    */
  __I  uint32_t  RESERVED0[4];
  __IO uint32_t  FLASHCFG;                          /*!< (@ 0x40040010) Flash configuration register                           */
  __I  uint32_t  RESERVED1[3];
  __IO uint32_t  FMSSTART;                          /*!< (@ 0x40040020) Signature start address register                       */
  __IO uint32_t  FMSSTOP;                           /*!< (@ 0x40040024) Signature stop-address register                        */
  __I  uint32_t  RESERVED2;
  __I  uint32_t  FMSW0;                             /*!< (@ 0x4004002C) Signature Word                                         */
} LPC_FLASHCTRL_Type;


/* ================================================================================ */
/* ================                      IOCON                     ================ */
/* ================================================================================ */


/**
  * @brief I/O configuration (IOCON) (IOCON)
  */

typedef struct {                                    /*!< (@ 0x40044000) IOCON Structure                                        */
  __IO uint32_t  PIO0_17;                           /*!< (@ 0x40044000) I/O configuration for pin PIO0_17                      */
  __IO uint32_t  PIO0_13;                           /*!< (@ 0x40044004) I/O configuration for pin PIO0_13                      */
  __IO uint32_t  PIO0_12;                           /*!< (@ 0x40044008) I/O configuration for pin PIO0_12                      */
  __IO uint32_t  PIO0_5;                            /*!< (@ 0x4004400C) I/O configuration for pin PIO0_5/RESET                 */
  __IO uint32_t  PIO0_4;                            /*!< (@ 0x40044010) I/O configuration for pin PIO0_4                       */
  __IO uint32_t  PIO0_3;                            /*!< (@ 0x40044014) I/O configuration for pin PIO0_3/SWCLK                 */
  __IO uint32_t  PIO0_2;                            /*!< (@ 0x40044018) I/O configuration for pin PIO0_2/SWDIO                 */
  __IO uint32_t  PIO0_11;                           /*!< (@ 0x4004401C) I/O configuration for pin PIO0_11. This is the
                                                         pin configuration for the true open-drain pin.                        */
  __IO uint32_t  PIO0_10;                           /*!< (@ 0x40044020) I/O configuration for pin PIO0_10. This is the
                                                         pin configuration for the true open-drain pin.                        */
  __IO uint32_t  PIO0_16;                           /*!< (@ 0x40044024) I/O configuration for pin PIO0_16                      */
  __IO uint32_t  PIO0_15;                           /*!< (@ 0x40044028) I/O configuration for pin PIO0_15                      */
  __IO uint32_t  PIO0_1;                            /*!< (@ 0x4004402C) I/O configuration for pin PIO0_17                      */
  __I  uint32_t  RESERVED0;
  __IO uint32_t  PIO0_9;                            /*!< (@ 0x40044034) I/O configuration for pin PIO0_9/XTALOUT               */
  __IO uint32_t  PIO0_8;                            /*!< (@ 0x40044038) I/O configuration for pin PIO0_8/XTALIN                */
  __IO uint32_t  PIO0_7;                            /*!< (@ 0x4004403C) I/O configuration for pin PIO0_7                       */
  __IO uint32_t  PIO0_6;                            /*!< (@ 0x40044040) I/O configuration for pin PIO0_6/VDDCMP                */
  __IO uint32_t  PIO0_0;                            /*!< (@ 0x40044044) I/O configuration for pin PIO0_0/ACMP_I0               */
  __IO uint32_t  PIO0_14;                           /*!< (@ 0x40044048) I/O configuration for pin PIO0_14                      */
  __I  uint32_t  RESERVED1;
  __IO uint32_t  PIO0_28;                           /*!< (@ 0x40044050) I/O configuration for pin PIO0_28                      */
  __IO uint32_t  PIO0_27;                           /*!< (@ 0x40044054) I/O configuration for pin PIO0_27                      */
  __IO uint32_t  PIO0_26;                           /*!< (@ 0x40044058) I/O configuration for pin PIO0_26                      */
  __IO uint32_t  PIO0_25;                           /*!< (@ 0x4004405C) I/O configuration for pin PIO0_25                      */
  __IO uint32_t  PIO0_24;                           /*!< (@ 0x40044060) I/O configuration for pin PIO0_24                      */
  __IO uint32_t  PIO0_23;                           /*!< (@ 0x40044064) I/O configuration for pin PIO0_23/ADC_3                */
  __IO uint32_t  PIO0_22;                           /*!< (@ 0x40044068) I/O configuration for pin PIO0_22/ADC_4                */
  __IO uint32_t  PIO0_21;                           /*!< (@ 0x4004406C) I/O configuration for pin PIO0_21/ACMP_I4/ADC_5        */
  __IO uint32_t  PIO0_20;                           /*!< (@ 0x40044070) I/O configuration for pin PIO0_20/ADC_6                */
  __IO uint32_t  PIO0_19;                           /*!< (@ 0x40044074) I/O configuration for pin PIO0_19/ADC_7                */
  __IO uint32_t  PIO0_18;                           /*!< (@ 0x40044078) I/O configuration for pin PIO0_18/ADC_8                */
} LPC_IOCON_Type;


/* ================================================================================ */
/* ================                     SYSCON                     ================ */
/* ================================================================================ */


/**
  * @brief System configuration (SYSCON) (SYSCON)
  */

typedef struct {                                    /*!< (@ 0x40048000) SYSCON Structure                                       */
  __IO uint32_t  SYSMEMREMAP;                       /*!< (@ 0x40048000) System memory remap                                    */
  __IO uint32_t  PRESETCTRL;                        /*!< (@ 0x40048004) Peripheral reset control                               */
  __IO uint32_t  SYSPLLCTRL;                        /*!< (@ 0x40048008) System PLL control                                     */
  __I  uint32_t  SYSPLLSTAT;                        /*!< (@ 0x4004800C) System PLL status                                      */
  __I  uint32_t  RESERVED0[4];
  __IO uint32_t  SYSOSCCTRL;                        /*!< (@ 0x40048020) System oscillator control                              */
  __IO uint32_t  WDTOSCCTRL;                        /*!< (@ 0x40048024) Watchdog oscillator control                            */
  __IO uint32_t  IRCCTRL;                           /*!< (@ 0x40048028) IRC control                                            */
  __I  uint32_t  RESERVED1;
  __IO uint32_t  SYSRSTSTAT;                        /*!< (@ 0x40048030) System reset status register                           */
  __I  uint32_t  RESERVED2[3];
  __IO uint32_t  SYSPLLCLKSEL;                      /*!< (@ 0x40048040) System PLL clock source select                         */
  __IO uint32_t  SYSPLLCLKUEN;                      /*!< (@ 0x40048044) System PLL clock source update enable                  */
  __I  uint32_t  RESERVED3[10];
  __IO uint32_t  MAINCLKSEL;                        /*!< (@ 0x40048070) Main clock source select                               */
  __IO uint32_t  MAINCLKUEN;                        /*!< (@ 0x40048074) Main clock source update enable                        */
  __IO uint32_t  SYSAHBCLKDIV;                      /*!< (@ 0x40048078) System clock divider                                   */
  __I  uint32_t  RESERVED4;
  __IO uint32_t  SYSAHBCLKCTRL;                     /*!< (@ 0x40048080) System clock control                                   */
  __I  uint32_t  RESERVED5[4];
  __IO uint32_t  UARTCLKDIV;                        /*!< (@ 0x40048094) USART clock divider                                    */
  __I  uint32_t  RESERVED6[18];
  __IO uint32_t  CLKOUTSEL;                         /*!< (@ 0x400480E0) CLKOUT clock source select                             */
  __IO uint32_t  CLKOUTUEN;                         /*!< (@ 0x400480E4) CLKOUT clock source update enable                      */
  __IO uint32_t  CLKOUTDIV;                         /*!< (@ 0x400480E8) CLKOUT clock divider                                   */
  __I  uint32_t  RESERVED7;
  __IO uint32_t  UARTFRGDIV;                        /*!< (@ 0x400480F0) USART1 to USART4 common fractional generator
                                                         divider value                                                         */
  __IO uint32_t  UARTFRGMULT;                       /*!< (@ 0x400480F4) USART1 to USART4 common fractional generator
                                                         multiplier value                                                      */
  __I  uint32_t  RESERVED8;
  __IO uint32_t  EXTTRACECMD;                       /*!< (@ 0x400480FC) External trace buffer command register                 */
  __I  uint32_t  PIOPORCAP0;                        /*!< (@ 0x40048100) POR captured PIO status 0                              */
  __I  uint32_t  RESERVED9[12];
  __IO uint32_t  IOCONCLKDIV6;                      /*!< (@ 0x40048134) Peripheral clock 6 to the IOCON block for programmable
                                                         glitch filter                                                         */
  __I  uint32_t  RESERVED10[6];
  __IO uint32_t  BODCTRL;                           /*!< (@ 0x40048150) Brown-Out Detect                                       */
  __IO uint32_t  SYSTCKCAL;                         /*!< (@ 0x40048154) System tick counter calibration                        */
  __I  uint32_t  RESERVED11[6];
  __IO uint32_t  IRQLATENCY;                        /*!< (@ 0x40048170) IQR delay. Allows trade-off between interrupt
                                                         latency and determinism.                                              */
  __IO uint32_t  NMISRC;                            /*!< (@ 0x40048174) NMI Source Control                                     */
  union {
    __IO uint32_t  PINTSEL[8];
  struct {
  __IO uint32_t  PINTSEL0;                          /*!< (@ 0x40048178) GPIO Pin Interrupt Select register 0                   */
  __IO uint32_t  PINTSEL1;                          /*!< (@ 0x4004817C) GPIO Pin Interrupt Select register 0                   */
  __IO uint32_t  PINTSEL2;                          /*!< (@ 0x40048180) GPIO Pin Interrupt Select register 0                   */
  __IO uint32_t  PINTSEL3;                          /*!< (@ 0x40048184) GPIO Pin Interrupt Select register 0                   */
  __IO uint32_t  PINTSEL4;                          /*!< (@ 0x40048188) GPIO Pin Interrupt Select register 0                   */
  __IO uint32_t  PINTSEL5;                          /*!< (@ 0x4004818C) GPIO Pin Interrupt Select register 0                   */
  __IO uint32_t  PINTSEL6;                          /*!< (@ 0x40048190) GPIO Pin Interrupt Select register 0                   */
  __IO uint32_t  PINTSEL7;                          /*!< (@ 0x40048194) GPIO Pin Interrupt Select register 0                   */
  };
  };
  __I  uint32_t  RESERVED12[27];
  __IO uint32_t  STARTERP0;                         /*!< (@ 0x40048204) Start logic 0 pin wake-up enable register              */
  __I  uint32_t  RESERVED13[3];
  __IO uint32_t  STARTERP1;                         /*!< (@ 0x40048214) Start logic 1 interrupt wake-up enable register        */
  __I  uint32_t  RESERVED14[6];
  __IO uint32_t  PDSLEEPCFG;                        /*!< (@ 0x40048230) Power-down states in deep-sleep mode                   */
  __IO uint32_t  PDAWAKECFG;                        /*!< (@ 0x40048234) Power-down states for wake-up from deep-sleep          */
  __IO uint32_t  PDRUNCFG;                          /*!< (@ 0x40048238) Power configuration register                           */
  __I  uint32_t  RESERVED15[111];
  __I  uint32_t  DEVICE_ID;                         /*!< (@ 0x400483F8) Device ID                                              */
} LPC_SYSCON_Type;


/* ================================================================================ */
/* ================                      I2C0                      ================ */
/* ================================================================================ */


/**
  * @brief I2C0-bus interface (I2C0)
  */

typedef struct {                                    /*!< (@ 0x40050000) I2C0 Structure                                         */
  __IO uint32_t  CFG;                               /*!< (@ 0x40050000) Configuration for shared functions.                    */
  __IO uint32_t  STAT;                              /*!< (@ 0x40050004) Status register for Master, Slave, and Monitor
                                                         functions.                                                            */
  __IO uint32_t  INTENSET;                          /*!< (@ 0x40050008) Interrupt Enable Set and read register.                */
  __O  uint32_t  INTENCLR;                          /*!< (@ 0x4005000C) Interrupt Enable Clear register.                       */
  __IO uint32_t  TIMEOUT;                           /*!< (@ 0x40050010) Time-out value register.                               */
  __IO uint32_t  CLKDIV;                            /*!< (@ 0x40050014) Clock pre-divider for the entire I2C block. This
                                                         determines what time increments are used for the MSTTIME and
                                                          SLVTIME registers.                                                   */
  __I  uint32_t  INTSTAT;                           /*!< (@ 0x40050018) Interrupt Status register for Master, Slave,
                                                         and Monitor functions.                                                */
  __I  uint32_t  RESERVED0;
  __IO uint32_t  MSTCTL;                            /*!< (@ 0x40050020) Master control register.                               */
  __IO uint32_t  MSTTIME;                           /*!< (@ 0x40050024) Master timing configuration.                           */
  __IO uint32_t  MSTDAT;                            /*!< (@ 0x40050028) Combined Master receiver and transmitter data
                                                         register.                                                             */
  __I  uint32_t  RESERVED1[5];
  __IO uint32_t  SLVCTL;                            /*!< (@ 0x40050040) Slave control register.                                */
  __IO uint32_t  SLVDAT;                            /*!< (@ 0x40050044) Combined Slave receiver and transmitter data
                                                         register.                                                             */
  union {
    __IO uint32_t SLVADR[4];
    struct {
  __IO uint32_t  SLVADR0;                           /*!< (@ 0x40050048) Slave address 0.                                       */
  __IO uint32_t  SLVADR1;                           /*!< (@ 0x4005004C) Slave address 0.                                       */
  __IO uint32_t  SLVADR2;                           /*!< (@ 0x40050050) Slave address 0.                                       */
  __IO uint32_t  SLVADR3;                           /*!< (@ 0x40050054) Slave address 0.                                       */
    };
  };
  __IO uint32_t  SLVQUAL0;                          /*!< (@ 0x40050058) Slave Qualification for address 0.                     */
  __I  uint32_t  RESERVED2[9];
  __I  uint32_t  MONRXDAT;                          /*!< (@ 0x40050080) Monitor receiver data register.                        */
} LPC_I2C0_Type;


/* ================================================================================ */
/* ================                      SPI0                      ================ */
/* ================================================================================ */


/**
  * @brief SPI0 (SPI0)
  */

typedef struct {                                    /*!< (@ 0x40058000) SPI0 Structure                                         */
  __IO uint32_t  CFG;                               /*!< (@ 0x40058000) SPI Configuration register                             */
  __IO uint32_t  DLY;                               /*!< (@ 0x40058004) SPI Delay register                                     */
  __IO uint32_t  STAT;                              /*!< (@ 0x40058008) SPI Status. Some status flags can be cleared
                                                         by writing a 1 to that bit position                                   */
  __IO uint32_t  INTENSET;                          /*!< (@ 0x4005800C) SPI Interrupt Enable read and Set. A complete
                                                         value may be read from this register. Writing a 1 to any implemented
                                                          bit position causes that bit to be set.                              */
  __O  uint32_t  INTENCLR;                          /*!< (@ 0x40058010) SPI Interrupt Enable Clear. Writing a 1 to any
                                                         implemented bit position causes the corresponding bit in INTENSET
                                                          to be cleared.                                                       */
  __I  uint32_t  RXDAT;                             /*!< (@ 0x40058014) SPI Receive Data                                       */
  __IO uint32_t  TXDATCTL;                          /*!< (@ 0x40058018) SPI Transmit Data with Control                         */
  __IO uint32_t  TXDAT;                             /*!< (@ 0x4005801C) SPI Transmit Data                                      */
  __IO uint32_t  TXCTL;                             /*!< (@ 0x40058020) SPI Transmit Control                                   */
  __IO uint32_t  DIV;                               /*!< (@ 0x40058024) SPI clock Divider                                      */
  __I  uint32_t  INTSTAT;                           /*!< (@ 0x40058028) SPI Interrupt Status                                   */
} LPC_SPI0_Type;


/* ================================================================================ */
/* ================                     USART0                     ================ */
/* ================================================================================ */


/**
  * @brief USART0 (USART0)
  */

typedef struct {                                    /*!< (@ 0x40064000) USART0 Structure                                       */
  __IO uint32_t  CFG;                               /*!< (@ 0x40064000) USART Configuration register. Basic USART configuration
                                                         settings that typically are not changed during operation.             */
  __IO uint32_t  CTL;                               /*!< (@ 0x40064004) USART Control register. USART control settings
                                                         that are more likely to change during operation.                      */
  __IO uint32_t  STAT;                              /*!< (@ 0x40064008) USART Status register. The complete status value
                                                         can be read here. Writing ones clears some bits in the register.
                                                          Some bits can be cleared by writing a 1 to them.                     */
  __IO uint32_t  INTENSET;                          /*!< (@ 0x4006400C) Interrupt Enable read and Set register. Contains
                                                         an individual interrupt enable bit for each potential USART
                                                          interrupt. A complete value may be read from this register.
                                                          Writing a 1 to any implemented bit position causes that bit
                                                          to be set.                                                           */
  __O  uint32_t  INTENCLR;                          /*!< (@ 0x40064010) Interrupt Enable Clear register. Allows clearing
                                                         any combination of bits in the INTENSET register. Writing a
                                                          1 to any implemented bit position causes the corresponding bit
                                                          to be cleared.                                                       */
  __I  uint32_t  RXDAT;                             /*!< (@ 0x40064014) Receiver Data register. Contains the last character
                                                         received.                                                             */
  __I  uint32_t  RXDATSTAT;                         /*!< (@ 0x40064018) Receiver Data with Status register. Combines
                                                         the last character received with the current USART receive status.
                                                          Allows DMA or software to recover incoming data and status together. */
  __IO uint32_t  TXDAT;                             /*!< (@ 0x4006401C) Transmit Data register. Data to be transmitted
                                                         is written here.                                                      */
  __IO uint32_t  BRG;                               /*!< (@ 0x40064020) Baud Rate Generator register. 16-bit integer
                                                         baud rate divisor value.                                              */
  __I  uint32_t  INTSTAT;                           /*!< (@ 0x40064024) Interrupt status register. Reflects interrupts
                                                         that are currently enabled.                                           */
  __IO uint32_t  OSR;                               /*!< (@ 0x40064028) Oversample selection register for asynchronous
                                                         communication.                                                        */
  __IO uint32_t  ADDR;                              /*!< (@ 0x4006402C) Address register for automatic address matching.       */
} LPC_USART0_Type;


/* ================================================================================ */
/* ================                       CRC                      ================ */
/* ================================================================================ */


/**
  * @brief Cyclic Redundancy Check (CRC) engine (CRC)
  */

typedef struct {                                    /*!< (@ 0x50000000) CRC Structure                                          */
  __IO uint32_t  MODE;                              /*!< (@ 0x50000000) CRC mode register                                      */
  __IO uint32_t  SEED;                              /*!< (@ 0x50000004) CRC seed register                                      */
  
  union {
    __O  uint32_t  WR_DATA;                         /*!< (@ 0x50000008) CRC data register                                      */
    __I  uint32_t  SUM;                             /*!< (@ 0x50000008) CRC checksum register                                  */
  };
} LPC_CRC_Type;


/* ================================================================================ */
/* ================                       SCT                      ================ */
/* ================================================================================ */


/**
  * @brief State Configurable Timer (SCT) (SCT)
  */

typedef struct {                                    /*!< (@ 0x50004000) SCT Structure                                          */
  __IO uint32_t  CONFIG;                            /*!< (@ 0x50004000) SCT configuration register                             */
  __IO uint32_t  CTRL;                              /*!< (@ 0x50004004) SCT control register                                   */
  __IO uint32_t  LIMIT;                             /*!< (@ 0x50004008) SCT limit register                                     */
  __IO uint32_t  HALT;                              /*!< (@ 0x5000400C) SCT halt condition register                            */
  __IO uint32_t  STOP;                              /*!< (@ 0x50004010) SCT stop condition register                            */
  __IO uint32_t  START;                             /*!< (@ 0x50004014) SCT start condition register                           */
  __I  uint32_t  RESERVED0[10];
  __IO uint32_t  COUNT;                             /*!< (@ 0x50004040) SCT counter register                                   */
  __IO uint32_t  STATE;                             /*!< (@ 0x50004044) SCT state register                                     */
  __I  uint32_t  INPUT;                             /*!< (@ 0x50004048) SCT input register                                     */
  __IO uint32_t  REGMODE;                           /*!< (@ 0x5000404C) SCT match/capture registers mode register              */
  __IO uint32_t  OUTPUT;                            /*!< (@ 0x50004050) SCT output register                                    */
  __IO uint32_t  OUTPUTDIRCTRL;                     /*!< (@ 0x50004054) SCT output counter direction control register          */
  __IO uint32_t  RES;                               /*!< (@ 0x50004058) SCT conflict resolution register                       */
  __IO uint32_t  DMAREQ0;                           /*!< (@ 0x5000405C) SCT DMA request 0 register                             */
  __IO uint32_t  DMAREQ1;                           /*!< (@ 0x50004060) SCT DMA request 1 register                             */
  __I  uint32_t  RESERVED1[35];
  __IO uint32_t  EVEN;                              /*!< (@ 0x500040F0) SCT event enable register                              */
  __IO uint32_t  EVFLAG;                            /*!< (@ 0x500040F4) SCT event flag register                                */
  __IO uint32_t  CONEN;                             /*!< (@ 0x500040F8) SCT conflict enable register                           */
  __IO uint32_t  CONFLAG;                           /*!< (@ 0x500040FC) SCT conflict flag register                             */
  
union {
  union {
    __IO uint32_t  CAP0;                            /*!< (@ 0x50004100) SCT capture register of capture channel 0 to
                                                         7; REGMOD0 to REGMODE7 = 1                                            */
    __IO uint32_t  MATCH0;                          /*!< (@ 0x50004100) SCT match value register of match channels 0
                                                         to 7; REGMOD0 to REGMODE7 = 0                                         */
  };
  
  union {
    __IO uint32_t  CAP1;                            /*!< (@ 0x50004104) SCT capture register of capture channel 0 to
                                                         7; REGMOD0 to REGMODE7 = 1                                            */
    __IO uint32_t  MATCH1;                          /*!< (@ 0x50004104) SCT match value register of match channels 0
                                                         to 7; REGMOD0 to REGMODE7 = 0                                         */
  };
  
  union {
    __IO uint32_t  CAP2;                            /*!< (@ 0x50004108) SCT capture register of capture channel 0 to
                                                         7; REGMOD0 to REGMODE7 = 1                                            */
    __IO uint32_t  MATCH2;                          /*!< (@ 0x50004108) SCT match value register of match channels 0
                                                         to 7; REGMOD0 to REGMODE7 = 0                                         */
  };
  
  union {
    __IO uint32_t  MATCH3;                          /*!< (@ 0x5000410C) SCT match value register of match channels 0
                                                         to 7; REGMOD0 to REGMODE7 = 0                                         */
    __IO uint32_t  CAP3;                            /*!< (@ 0x5000410C) SCT capture register of capture channel 0 to
                                                         7; REGMOD0 to REGMODE7 = 1                                            */
  };
  
  union {
    __IO uint32_t  CAP4;                            /*!< (@ 0x50004110) SCT capture register of capture channel 0 to
                                                         7; REGMOD0 to REGMODE7 = 1                                            */
    __IO uint32_t  MATCH4;                          /*!< (@ 0x50004110) SCT match value register of match channels 0
                                                         to 7; REGMOD0 to REGMODE7 = 0                                         */
  };
  
  union {
    __IO uint32_t  MATCH5;                          /*!< (@ 0x50004114) SCT match value register of match channels 0
                                                         to 7; REGMOD0 to REGMODE7 = 0                                         */
    __IO uint32_t  CAP5;                            /*!< (@ 0x50004114) SCT capture register of capture channel 0 to
                                                         7; REGMOD0 to REGMODE7 = 1                                            */
  };
  
  union {
    __IO uint32_t  CAP6;                            /*!< (@ 0x50004118) SCT capture register of capture channel 0 to
                                                         7; REGMOD0 to REGMODE7 = 1                                            */
    __IO uint32_t  MATCH6;                          /*!< (@ 0x50004118) SCT match value register of match channels 0
                                                         to 7; REGMOD0 to REGMODE7 = 0                                         */
  };
  
  union {
    __IO uint32_t  CAP7;                            /*!< (@ 0x5000411C) SCT capture register of capture channel 0 to
                                                         7; REGMOD0 to REGMODE7 = 1                                            */
    __IO uint32_t  MATCH7;                          /*!< (@ 0x5000411C) SCT match value register of match channels 0
                                                         to 7; REGMOD0 to REGMODE7 = 0                                         */
  };
  __IO uint32_t CAP[8];
  __IO uint32_t MATCH[8];
};
  __I  uint32_t  RESERVED2[56];
  
  union {
    struct {
  union {
    __IO uint32_t  CAPCTRL0;                        /*!< (@ 0x50004200) SCT capture control register 0 to 7; REGMOD0
                                                         = 1 to REGMODE7 = 1                                                   */
    __IO uint32_t  MATCHREL0;                       /*!< (@ 0x50004200) SCT match reload value register 0 to 7; REGMOD0
                                                         = 0 to REGMODE7 = 0                                                   */
  };
  
  union {
    __IO uint32_t  CAPCTRL1;                        /*!< (@ 0x50004204) SCT capture control register 0 to 7; REGMOD0
                                                         = 1 to REGMODE7 = 1                                                   */
    __IO uint32_t  MATCHREL1;                       /*!< (@ 0x50004204) SCT match reload value register 0 to 7; REGMOD0
                                                         = 0 to REGMODE7 = 0                                                   */
  };
  
  union {
    __IO uint32_t  CAPCTRL2;                        /*!< (@ 0x50004208) SCT capture control register 0 to 7; REGMOD0
                                                         = 1 to REGMODE7 = 1                                                   */
    __IO uint32_t  MATCHREL2;                       /*!< (@ 0x50004208) SCT match reload value register 0 to 7; REGMOD0
                                                         = 0 to REGMODE7 = 0                                                   */
  };
  
  union {
    __IO uint32_t  MATCHREL3;                       /*!< (@ 0x5000420C) SCT match reload value register 0 to 7; REGMOD0
                                                         = 0 to REGMODE7 = 0                                                   */
    __IO uint32_t  CAPCTRL3;                        /*!< (@ 0x5000420C) SCT capture control register 0 to 7; REGMOD0
                                                         = 1 to REGMODE7 = 1                                                   */
  };
  
  union {
    __IO uint32_t  CAPCTRL4;                        /*!< (@ 0x50004210) SCT capture control register 0 to 7; REGMOD0
                                                         = 1 to REGMODE7 = 1                                                   */
    __IO uint32_t  MATCHREL4;                       /*!< (@ 0x50004210) SCT match reload value register 0 to 7; REGMOD0
                                                         = 0 to REGMODE7 = 0                                                   */
  };
  
  union {
    __IO uint32_t  CAPCTRL5;                        /*!< (@ 0x50004214) SCT capture control register 0 to 7; REGMOD0
                                                         = 1 to REGMODE7 = 1                                                   */
    __IO uint32_t  MATCHREL5;                       /*!< (@ 0x50004214) SCT match reload value register 0 to 7; REGMOD0
                                                         = 0 to REGMODE7 = 0                                                   */
  };
  
  union {
    __IO uint32_t  CAPCTRL6;                        /*!< (@ 0x50004218) SCT capture control register 0 to 7; REGMOD0
                                                         = 1 to REGMODE7 = 1                                                   */
    __IO uint32_t  MATCHREL6;                       /*!< (@ 0x50004218) SCT match reload value register 0 to 7; REGMOD0
                                                         = 0 to REGMODE7 = 0                                                   */
  };
  
  union {
    __IO uint32_t  CAPCTRL7;                        /*!< (@ 0x5000421C) SCT capture control register 0 to 7; REGMOD0
                                                         = 1 to REGMODE7 = 1                                                   */
    __IO uint32_t  MATCHREL7;                       /*!< (@ 0x5000421C) SCT match reload value register 0 to 7; REGMOD0
                                                         = 0 to REGMODE7 = 0                                                   */
  };
  };
    __IO uint32_t  MATCHREL[8];
  };
  __I  uint32_t  RESERVED3[56];

  union {
    struct {
  __IO uint32_t  EV0_STATE;                         /*!< (@ 0x50004300) SCT event state register 0                             */
  __IO uint32_t  EV0_CTRL;                          /*!< (@ 0x50004304) SCT event control register 0                           */
  __IO uint32_t  EV1_STATE;                         /*!< (@ 0x50004308) SCT event state register 0                             */
  __IO uint32_t  EV1_CTRL;                          /*!< (@ 0x5000430C) SCT event control register 0                           */
  __IO uint32_t  EV2_STATE;                         /*!< (@ 0x50004310) SCT event state register 0                             */
  __IO uint32_t  EV2_CTRL;                          /*!< (@ 0x50004314) SCT event control register 0                           */
  __IO uint32_t  EV3_STATE;                         /*!< (@ 0x50004318) SCT event state register 0                             */
  __IO uint32_t  EV3_CTRL;                          /*!< (@ 0x5000431C) SCT event control register 0                           */
  __IO uint32_t  EV4_STATE;                         /*!< (@ 0x50004320) SCT event state register 0                             */
  __IO uint32_t  EV4_CTRL;                          /*!< (@ 0x50004324) SCT event control register 0                           */
  __IO uint32_t  EV5_STATE;                         /*!< (@ 0x50004328) SCT event state register 0                             */
  __IO uint32_t  EV5_CTRL;                          /*!< (@ 0x5000432C) SCT event control register 0                           */
  __IO uint32_t  EV6_STATE;                         /*!< (@ 0x50004330) SCT event state register 0                             */
  __IO uint32_t  EV6_CTRL;                          /*!< (@ 0x50004334) SCT event control register 0                           */
  __IO uint32_t  EV7_STATE;                         /*!< (@ 0x50004338) SCT event state register 0                             */
  __IO uint32_t  EV7_CTRL;                          /*!< (@ 0x5000433C) SCT event control register 0                           */
    };
    __IO struct {
        uint32_t STATE;
        uint32_t CTRL;
    } EVENT[8];
  };

  __I  uint32_t  RESERVED4[112];

  union {
    struct {
  __IO uint32_t  OUT0_SET;                          /*!< (@ 0x50004500) SCT output 0 set register                              */
  __IO uint32_t  OUT0_CLR;                          /*!< (@ 0x50004504) SCT output 0 clear register                            */
  __IO uint32_t  OUT1_SET;                          /*!< (@ 0x50004508) SCT output 0 set register                              */
  __IO uint32_t  OUT1_CLR;                          /*!< (@ 0x5000450C) SCT output 0 clear register                            */
  __IO uint32_t  OUT2_SET;                          /*!< (@ 0x50004510) SCT output 0 set register                              */
  __IO uint32_t  OUT2_CLR;                          /*!< (@ 0x50004514) SCT output 0 clear register                            */
  __IO uint32_t  OUT3_SET;                          /*!< (@ 0x50004518) SCT output 0 set register                              */
  __IO uint32_t  OUT3_CLR;                          /*!< (@ 0x5000451C) SCT output 0 clear register                            */
  __IO uint32_t  OUT4_SET;                          /*!< (@ 0x50004520) SCT output 0 set register                              */
  __IO uint32_t  OUT4_CLR;                          /*!< (@ 0x50004524) SCT output 0 clear register                            */
  __IO uint32_t  OUT5_SET;                          /*!< (@ 0x50004528) SCT output 0 set register                              */
  __IO uint32_t  OUT5_CLR;                          /*!< (@ 0x5000452C) SCT output 0 clear register                            */
    };
    __IO struct {
        uint32_t SET;
        uint32_t CLR;
    } OUT[6];
};

} LPC_SCT_Type;


/* ================================================================================ */
/* ================                       DMA                      ================ */
/* ================================================================================ */


/**
  * @brief DMA controller  (DMA)
  */

typedef struct {                                    /*!< (@ 0x50008000) DMA Structure                                          */
  __IO uint32_t  CTRL;                              /*!< (@ 0x50008000) DMA control.                                           */
  __I  uint32_t  INTSTAT;                           /*!< (@ 0x50008004) Interrupt status.                                      */
  __IO uint32_t  SRAMBASE;                          /*!< (@ 0x50008008) SRAM address of the channel configuration table.       */
  __I  uint32_t  RESERVED0[5];
  __IO uint32_t  ENABLESET0;                        /*!< (@ 0x50008020) Channel Enable read and Set for all DMA channels.      */
  __I  uint32_t  RESERVED1;
  __O  uint32_t  ENABLECLR0;                        /*!< (@ 0x50008028) Channel Enable Clear for all DMA channels.             */
  __I  uint32_t  RESERVED2;
  __I  uint32_t  ACTIVE0;                           /*!< (@ 0x50008030) Channel Active status for all DMA channels.            */
  __I  uint32_t  RESERVED3;
  __I  uint32_t  BUSY0;                             /*!< (@ 0x50008038) Channel Busy status for all DMA channels.              */
  __I  uint32_t  RESERVED4;
  __IO uint32_t  ERRINT0;                           /*!< (@ 0x50008040) Error Interrupt status for all DMA channels.           */
  __I  uint32_t  RESERVED5;
  __IO uint32_t  INTENSET0;                         /*!< (@ 0x50008048) Interrupt Enable read and Set for all DMA channels.    */
  __I  uint32_t  RESERVED6;
  __O  uint32_t  INTENCLR0;                         /*!< (@ 0x50008050) Interrupt Enable Clear for all DMA channels.           */
  __I  uint32_t  RESERVED7;
  __IO uint32_t  INTA0;                             /*!< (@ 0x50008058) Interrupt A status for all DMA channels.               */
  __I  uint32_t  RESERVED8;
  __IO uint32_t  INTB0;                             /*!< (@ 0x50008060) Interrupt B status for all DMA channels.               */
  __I  uint32_t  RESERVED9;
  __O  uint32_t  SETVALID0;                         /*!< (@ 0x50008068) Set ValidPending control bits for all DMA channels.    */
  __I  uint32_t  RESERVED10;
  __O  uint32_t  SETTRIG0;                          /*!< (@ 0x50008070) Set Trigger control bits for all DMA channels.         */
  __I  uint32_t  RESERVED11;
  __O  uint32_t  ABORT0;                            /*!< (@ 0x50008078) Channel Abort control for all DMA channels.            */
  __I  uint32_t  RESERVED12[225];
  __IO uint32_t  CFG0;                              /*!< (@ 0x50008400) Configuration register for DMA channel 0.              */
  __I  uint32_t  CTLSTAT0;                          /*!< (@ 0x50008404) Control and status register for DMA channel 0.         */
  __IO uint32_t  XFERCFG0;                          /*!< (@ 0x50008408) Transfer configuration register for DMA channel
                                                         0.                                                                    */
  __I  uint32_t  RESERVED13;
  __IO uint32_t  CFG1;                              /*!< (@ 0x50008410) Configuration register for DMA channel 0.              */
  __I  uint32_t  CTLSTAT1;                          /*!< (@ 0x50008414) Control and status register for DMA channel 0.         */
  __IO uint32_t  XFERCFG1;                          /*!< (@ 0x50008418) Transfer configuration register for DMA channel
                                                         0.                                                                    */
  __I  uint32_t  RESERVED14;
  __IO uint32_t  CFG2;                              /*!< (@ 0x50008420) Configuration register for DMA channel 0.              */
  __I  uint32_t  CTLSTAT2;                          /*!< (@ 0x50008424) Control and status register for DMA channel 0.         */
  __IO uint32_t  XFERCFG2;                          /*!< (@ 0x50008428) Transfer configuration register for DMA channel
                                                         0.                                                                    */
  __I  uint32_t  RESERVED15;
  __IO uint32_t  CFG3;                              /*!< (@ 0x50008430) Configuration register for DMA channel 0.              */
  __I  uint32_t  CTLSTAT3;                          /*!< (@ 0x50008434) Control and status register for DMA channel 0.         */
  __IO uint32_t  XFERCFG3;                          /*!< (@ 0x50008438) Transfer configuration register for DMA channel
                                                         0.                                                                    */
  __I  uint32_t  RESERVED16;
  __IO uint32_t  CFG4;                              /*!< (@ 0x50008440) Configuration register for DMA channel 0.              */
  __I  uint32_t  CTLSTAT4;                          /*!< (@ 0x50008444) Control and status register for DMA channel 0.         */
  __IO uint32_t  XFERCFG4;                          /*!< (@ 0x50008448) Transfer configuration register for DMA channel
                                                         0.                                                                    */
  __I  uint32_t  RESERVED17;
  __IO uint32_t  CFG5;                              /*!< (@ 0x50008450) Configuration register for DMA channel 0.              */
  __I  uint32_t  CTLSTAT5;                          /*!< (@ 0x50008454) Control and status register for DMA channel 0.         */
  __IO uint32_t  XFERCFG5;                          /*!< (@ 0x50008458) Transfer configuration register for DMA channel
                                                         0.                                                                    */
  __I  uint32_t  RESERVED18;
  __IO uint32_t  CFG6;                              /*!< (@ 0x50008460) Configuration register for DMA channel 0.              */
  __I  uint32_t  CTLSTAT6;                          /*!< (@ 0x50008464) Control and status register for DMA channel 0.         */
  __IO uint32_t  XFERCFG6;                          /*!< (@ 0x50008468) Transfer configuration register for DMA channel
                                                         0.                                                                    */
  __I  uint32_t  RESERVED19;
  __IO uint32_t  CFG7;                              /*!< (@ 0x50008470) Configuration register for DMA channel 0.              */
  __I  uint32_t  CTLSTAT7;                          /*!< (@ 0x50008474) Control and status register for DMA channel 0.         */
  __IO uint32_t  XFERCFG7;                          /*!< (@ 0x50008478) Transfer configuration register for DMA channel
                                                         0.                                                                    */
  __I  uint32_t  RESERVED20;
  __IO uint32_t  CFG8;                              /*!< (@ 0x50008480) Configuration register for DMA channel 0.              */
  __I  uint32_t  CTLSTAT8;                          /*!< (@ 0x50008484) Control and status register for DMA channel 0.         */
  __IO uint32_t  XFERCFG8;                          /*!< (@ 0x50008488) Transfer configuration register for DMA channel
                                                         0.                                                                    */
  __I  uint32_t  RESERVED21;
  __IO uint32_t  CFG9;                              /*!< (@ 0x50008490) Configuration register for DMA channel 0.              */
  __I  uint32_t  CTLSTAT9;                          /*!< (@ 0x50008494) Control and status register for DMA channel 0.         */
  __IO uint32_t  XFERCFG9;                          /*!< (@ 0x50008498) Transfer configuration register for DMA channel
                                                         0.                                                                    */
  __I  uint32_t  RESERVED22;
  __IO uint32_t  CFG10;                             /*!< (@ 0x500084A0) Configuration register for DMA channel 0.              */
  __I  uint32_t  CTLSTAT10;                         /*!< (@ 0x500084A4) Control and status register for DMA channel 0.         */
  __IO uint32_t  XFERCFG10;                         /*!< (@ 0x500084A8) Transfer configuration register for DMA channel
                                                         0.                                                                    */
  __I  uint32_t  RESERVED23;
  __IO uint32_t  CFG11;                             /*!< (@ 0x500084B0) Configuration register for DMA channel 0.              */
  __I  uint32_t  CTLSTAT11;                         /*!< (@ 0x500084B4) Control and status register for DMA channel 0.         */
  __IO uint32_t  XFERCFG11;                         /*!< (@ 0x500084B8) Transfer configuration register for DMA channel
                                                         0.                                                                    */
  __I  uint32_t  RESERVED24;
  __IO uint32_t  CFG12;                             /*!< (@ 0x500084C0) Configuration register for DMA channel 0.              */
  __I  uint32_t  CTLSTAT12;                         /*!< (@ 0x500084C4) Control and status register for DMA channel 0.         */
  __IO uint32_t  XFERCFG12;                         /*!< (@ 0x500084C8) Transfer configuration register for DMA channel
                                                         0.                                                                    */
  __I  uint32_t  RESERVED25;
  __IO uint32_t  CFG13;                             /*!< (@ 0x500084D0) Configuration register for DMA channel 0.              */
  __I  uint32_t  CTLSTAT13;                         /*!< (@ 0x500084D4) Control and status register for DMA channel 0.         */
  __IO uint32_t  XFERCFG13;                         /*!< (@ 0x500084D8) Transfer configuration register for DMA channel
                                                         0.                                                                    */
  __I  uint32_t  RESERVED26;
  __IO uint32_t  CFG14;                             /*!< (@ 0x500084E0) Configuration register for DMA channel 0.              */
  __I  uint32_t  CTLSTAT14;                         /*!< (@ 0x500084E4) Control and status register for DMA channel 0.         */
  __IO uint32_t  XFERCFG14;                         /*!< (@ 0x500084E8) Transfer configuration register for DMA channel
                                                         0.                                                                    */
  __I  uint32_t  RESERVED27;
  __IO uint32_t  CFG15;                             /*!< (@ 0x500084F0) Configuration register for DMA channel 0.              */
  __I  uint32_t  CTLSTAT15;                         /*!< (@ 0x500084F4) Control and status register for DMA channel 0.         */
  __IO uint32_t  XFERCFG15;                         /*!< (@ 0x500084F8) Transfer configuration register for DMA channel
                                                         0.                                                                    */
  __I  uint32_t  RESERVED28;
  __IO uint32_t  CFG16;                             /*!< (@ 0x50008500) Configuration register for DMA channel 0.              */
  __I  uint32_t  CTLSTAT16;                         /*!< (@ 0x50008504) Control and status register for DMA channel 0.         */
  __IO uint32_t  XFERCFG16;                         /*!< (@ 0x50008508) Transfer configuration register for DMA channel
                                                         0.                                                                    */
  __I  uint32_t  RESERVED29;
  __IO uint32_t  CFG17;                             /*!< (@ 0x50008510) Configuration register for DMA channel 0.              */
  __I  uint32_t  CTLSTAT17;                         /*!< (@ 0x50008514) Control and status register for DMA channel 0.         */
  __IO uint32_t  XFERCFG17;                         /*!< (@ 0x50008518) Transfer configuration register for DMA channel
                                                         0.                                                                    */
} LPC_DMA_Type;


/* ================================================================================ */
/* ================                    GPIO_PORT                   ================ */
/* ================================================================================ */


/**
  * @brief General Purpose I/O port (GPIO) (GPIO_PORT)
  */

typedef struct {                                    /*!< (@ 0xA0000000) GPIO_PORT Structure                                    */
  __IO uint8_t   B0;                                /*!< (@ 0xA0000000) Byte pin registers port 0; pins PIO0_0 to PIO0_28      */
  __IO uint8_t   B1;                                /*!< (@ 0xA0000001) Byte pin registers port 0; pins PIO0_0 to PIO0_28      */
  __IO uint8_t   B2;                                /*!< (@ 0xA0000002) Byte pin registers port 0; pins PIO0_0 to PIO0_28      */
  __IO uint8_t   B3;                                /*!< (@ 0xA0000003) Byte pin registers port 0; pins PIO0_0 to PIO0_28      */
  __IO uint8_t   B4;                                /*!< (@ 0xA0000004) Byte pin registers port 0; pins PIO0_0 to PIO0_28      */
  __IO uint8_t   B5;                                /*!< (@ 0xA0000005) Byte pin registers port 0; pins PIO0_0 to PIO0_28      */
  __IO uint8_t   B6;                                /*!< (@ 0xA0000006) Byte pin registers port 0; pins PIO0_0 to PIO0_28      */
  __IO uint8_t   B7;                                /*!< (@ 0xA0000007) Byte pin registers port 0; pins PIO0_0 to PIO0_28      */
  __IO uint8_t   B8;                                /*!< (@ 0xA0000008) Byte pin registers port 0; pins PIO0_0 to PIO0_28      */
  __IO uint8_t   B9;                                /*!< (@ 0xA0000009) Byte pin registers port 0; pins PIO0_0 to PIO0_28      */
  __IO uint8_t   B10;                               /*!< (@ 0xA000000A) Byte pin registers port 0; pins PIO0_0 to PIO0_28      */
  __IO uint8_t   B11;                               /*!< (@ 0xA000000B) Byte pin registers port 0; pins PIO0_0 to PIO0_28      */
  __IO uint8_t   B12;                               /*!< (@ 0xA000000C) Byte pin registers port 0; pins PIO0_0 to PIO0_28      */
  __IO uint8_t   B13;                               /*!< (@ 0xA000000D) Byte pin registers port 0; pins PIO0_0 to PIO0_28      */
  __IO uint8_t   B14;                               /*!< (@ 0xA000000E) Byte pin registers port 0; pins PIO0_0 to PIO0_28      */
  __IO uint8_t   B15;                               /*!< (@ 0xA000000F) Byte pin registers port 0; pins PIO0_0 to PIO0_28      */
  __IO uint8_t   B16;                               /*!< (@ 0xA0000010) Byte pin registers port 0; pins PIO0_0 to PIO0_28      */
  __IO uint8_t   B17;                               /*!< (@ 0xA0000011) Byte pin registers port 0; pins PIO0_0 to PIO0_28      */
  __IO uint8_t   B18;                               /*!< (@ 0xA0000012) Byte pin registers port 0; pins PIO0_0 to PIO0_28      */
  __IO uint8_t   B19;                               /*!< (@ 0xA0000013) Byte pin registers port 0; pins PIO0_0 to PIO0_28      */
  __IO uint8_t   B20;                               /*!< (@ 0xA0000014) Byte pin registers port 0; pins PIO0_0 to PIO0_28      */
  __IO uint8_t   B21;                               /*!< (@ 0xA0000015) Byte pin registers port 0; pins PIO0_0 to PIO0_28      */
  __IO uint8_t   B22;                               /*!< (@ 0xA0000016) Byte pin registers port 0; pins PIO0_0 to PIO0_28      */
  __IO uint8_t   B23;                               /*!< (@ 0xA0000017) Byte pin registers port 0; pins PIO0_0 to PIO0_28      */
  __IO uint8_t   B24;                               /*!< (@ 0xA0000018) Byte pin registers port 0; pins PIO0_0 to PIO0_28      */
  __IO uint8_t   B25;                               /*!< (@ 0xA0000019) Byte pin registers port 0; pins PIO0_0 to PIO0_28      */
  __IO uint8_t   B26;                               /*!< (@ 0xA000001A) Byte pin registers port 0; pins PIO0_0 to PIO0_28      */
  __IO uint8_t   B27;                               /*!< (@ 0xA000001B) Byte pin registers port 0; pins PIO0_0 to PIO0_28      */
  __IO uint8_t   B28;                               /*!< (@ 0xA000001C) Byte pin registers port 0; pins PIO0_0 to PIO0_28      */
  __I  uint8_t   RESERVED0[4067];
  __IO uint32_t  W0;                                /*!< (@ 0xA0001000) Word pin registers port 0                              */
  __IO uint32_t  W1;                                /*!< (@ 0xA0001004) Word pin registers port 0                              */
  __IO uint32_t  W2;                                /*!< (@ 0xA0001008) Word pin registers port 0                              */
  __IO uint32_t  W3;                                /*!< (@ 0xA000100C) Word pin registers port 0                              */
  __IO uint32_t  W4;                                /*!< (@ 0xA0001010) Word pin registers port 0                              */
  __IO uint32_t  W5;                                /*!< (@ 0xA0001014) Word pin registers port 0                              */
  __IO uint32_t  W6;                                /*!< (@ 0xA0001018) Word pin registers port 0                              */
  __IO uint32_t  W7;                                /*!< (@ 0xA000101C) Word pin registers port 0                              */
  __IO uint32_t  W8;                                /*!< (@ 0xA0001020) Word pin registers port 0                              */
  __IO uint32_t  W9;                                /*!< (@ 0xA0001024) Word pin registers port 0                              */
  __IO uint32_t  W10;                               /*!< (@ 0xA0001028) Word pin registers port 0                              */
  __IO uint32_t  W11;                               /*!< (@ 0xA000102C) Word pin registers port 0                              */
  __IO uint32_t  W12;                               /*!< (@ 0xA0001030) Word pin registers port 0                              */
  __IO uint32_t  W13;                               /*!< (@ 0xA0001034) Word pin registers port 0                              */
  __IO uint32_t  W14;                               /*!< (@ 0xA0001038) Word pin registers port 0                              */
  __IO uint32_t  W15;                               /*!< (@ 0xA000103C) Word pin registers port 0                              */
  __IO uint32_t  W16;                               /*!< (@ 0xA0001040) Word pin registers port 0                              */
  __IO uint32_t  W17;                               /*!< (@ 0xA0001044) Word pin registers port 0                              */
  __IO uint32_t  W18;                               /*!< (@ 0xA0001048) Word pin registers port 0                              */
  __IO uint32_t  W19;                               /*!< (@ 0xA000104C) Word pin registers port 0                              */
  __IO uint32_t  W20;                               /*!< (@ 0xA0001050) Word pin registers port 0                              */
  __IO uint32_t  W21;                               /*!< (@ 0xA0001054) Word pin registers port 0                              */
  __IO uint32_t  W22;                               /*!< (@ 0xA0001058) Word pin registers port 0                              */
  __IO uint32_t  W23;                               /*!< (@ 0xA000105C) Word pin registers port 0                              */
  __IO uint32_t  W24;                               /*!< (@ 0xA0001060) Word pin registers port 0                              */
  __IO uint32_t  W25;                               /*!< (@ 0xA0001064) Word pin registers port 0                              */
  __IO uint32_t  W26;                               /*!< (@ 0xA0001068) Word pin registers port 0                              */
  __IO uint32_t  W27;                               /*!< (@ 0xA000106C) Word pin registers port 0                              */
  __IO uint32_t  W28;                               /*!< (@ 0xA0001070) Word pin registers port 0                              */
  __I  uint32_t  RESERVED1[995];
  __IO uint32_t  DIR0;                              /*!< (@ 0xA0002000) Direction registers port 0                             */
  __I  uint32_t  RESERVED2[31];
  __IO uint32_t  MASK0;                             /*!< (@ 0xA0002080) Mask register port 0                                   */
  __I  uint32_t  RESERVED3[31];
  __IO uint32_t  PIN0;                              /*!< (@ 0xA0002100) Port pin register port 0                               */
  __I  uint32_t  RESERVED4[31];
  __IO uint32_t  MPIN0;                             /*!< (@ 0xA0002180) Masked port register port 0                            */
  __I  uint32_t  RESERVED5[31];
  __IO uint32_t  SET0;                              /*!< (@ 0xA0002200) Write: Set register for port 0 Read: output bits
                                                         for port 0                                                            */
  __I  uint32_t  RESERVED6[31];
  __O  uint32_t  CLR0;                              /*!< (@ 0xA0002280) Clear port 0                                           */
  __I  uint32_t  RESERVED7[31];
  __O  uint32_t  NOT0;                              /*!< (@ 0xA0002300) Toggle port 0                                          */
  __I  uint32_t  RESERVED8[31];
  __O  uint32_t  DIRSET0;                           /*!< (@ 0xA0002380) Set pin direction bits for port 0.                     */
  __I  uint32_t  RESERVED9[31];
  __O  uint32_t  DIRCLR0;                           /*!< (@ 0xA0002400) Clear pin direction bits for port 0.                   */
  __I  uint32_t  RESERVED10[31];
  __O  uint32_t  DIRNOT0;                           /*!< (@ 0xA0002480) Toggle pin direction bits for port 0.                  */
} LPC_GPIO_PORT_Type;


/* ================================================================================ */
/* ================                     PIN_INT                    ================ */
/* ================================================================================ */


/**
  * @brief Pin interrupt and pattern match engine (PIN_INT)
  */

typedef struct {                                    /*!< (@ 0xA0004000) PIN_INT Structure                                      */
  __IO uint32_t  ISEL;                              /*!< (@ 0xA0004000) Pin Interrupt Mode register                            */
  __IO uint32_t  IENR;                              /*!< (@ 0xA0004004) Pin interrupt level or rising edge interrupt
                                                         enable register                                                       */
  __O  uint32_t  SIENR;                             /*!< (@ 0xA0004008) Pin interrupt level (rising edge) interrupt set
                                                         register                                                              */
  __O  uint32_t  CIENR;                             /*!< (@ 0xA000400C) Pin interrupt level or rising edge interrupt
                                                         clear register                                                        */
  __IO uint32_t  IENF;                              /*!< (@ 0xA0004010) Pin interrupt active level or falling edge interrupt
                                                         enable register                                                       */
  __O  uint32_t  SIENF;                             /*!< (@ 0xA0004014) Pin interrupt active level or falling edge interrupt
                                                         set register                                                          */
  __O  uint32_t  CIENF;                             /*!< (@ 0xA0004018) Pin interrupt active level (falling edge) interrupt
                                                         clear register                                                        */
  __IO uint32_t  RISE;                              /*!< (@ 0xA000401C) Pin interrupt rising edge register                     */
  __IO uint32_t  FALL;                              /*!< (@ 0xA0004020) Pin interrupt falling edge register                    */
  __IO uint32_t  IST;                               /*!< (@ 0xA0004024) Pin interrupt status register                          */
  __IO uint32_t  PMCTRL;                            /*!< (@ 0xA0004028) GPIO pattern match interrupt control register          */
  __IO uint32_t  PMSRC;                             /*!< (@ 0xA000402C) GPIO pattern match interrupt bit-slice source
                                                         register                                                              */
  __IO uint32_t  PMCFG;                             /*!< (@ 0xA0004030) GPIO pattern match interrupt bit slice configuration
                                                         register                                                              */
} LPC_PIN_INT_Type;


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

#define LPC_WWDT_BASE                   0x40000000UL
#define LPC_MRT_BASE                    0x40004000UL
#define LPC_WKT_BASE                    0x40008000UL
#define LPC_SWM_BASE                    0x4000C000UL
#define LPC_ADC_BASE                    0x4001C000UL
#define LPC_PMU_BASE                    0x40020000UL
#define LPC_CMP_BASE                    0x40024000UL
#define LPC_DMATRIGMUX_BASE             0x40028000UL
#define LPC_INPUTMUX_BASE               0x4002C000UL
#define LPC_FLASHCTRL_BASE              0x40040000UL
#define LPC_IOCON_BASE                  0x40044000UL
#define LPC_SYSCON_BASE                 0x40048000UL
#define LPC_I2C0_BASE                   0x40050000UL
#define LPC_I2C1_BASE                   0x40054000UL
#define LPC_SPI0_BASE                   0x40058000UL
#define LPC_SPI1_BASE                   0x4005C000UL
#define LPC_USART0_BASE                 0x40064000UL
#define LPC_USART1_BASE                 0x40068000UL
#define LPC_USART2_BASE                 0x4006C000UL
#define LPC_I2C2_BASE                   0x40070000UL
#define LPC_I2C3_BASE                   0x40074000UL
#define LPC_CRC_BASE                    0x50000000UL
#define LPC_SCT_BASE                    0x50004000UL
#define LPC_DMA_BASE                    0x50008000UL
#define LPC_GPIO_PORT_BASE              0xA0000000UL
#define LPC_PIN_INT_BASE                0xA0004000UL


/* ================================================================================ */
/* ================             Peripheral declaration             ================ */
/* ================================================================================ */

#define LPC_WWDT                        ((LPC_WWDT_Type           *) LPC_WWDT_BASE)
#define LPC_MRT                         ((LPC_MRT_Type            *) LPC_MRT_BASE)
#define LPC_WKT                         ((LPC_WKT_Type            *) LPC_WKT_BASE)
#define LPC_SWM                         ((LPC_SWM_Type            *) LPC_SWM_BASE)
#define LPC_ADC                         ((LPC_ADC_Type            *) LPC_ADC_BASE)
#define LPC_PMU                         ((LPC_PMU_Type            *) LPC_PMU_BASE)
#define LPC_CMP                         ((LPC_CMP_Type            *) LPC_CMP_BASE)
#define LPC_DMATRIGMUX                  ((LPC_DMATRIGMUX_Type     *) LPC_DMATRIGMUX_BASE)
#define LPC_INPUTMUX                    ((LPC_INPUTMUX_Type       *) LPC_INPUTMUX_BASE)
#define LPC_FLASHCTRL                   ((LPC_FLASHCTRL_Type      *) LPC_FLASHCTRL_BASE)
#define LPC_IOCON                       ((LPC_IOCON_Type          *) LPC_IOCON_BASE)
#define LPC_SYSCON                      ((LPC_SYSCON_Type         *) LPC_SYSCON_BASE)
#define LPC_I2C0                        ((LPC_I2C0_Type           *) LPC_I2C0_BASE)
#define LPC_I2C1                        ((LPC_I2C0_Type           *) LPC_I2C1_BASE)
#define LPC_SPI0                        ((LPC_SPI0_Type           *) LPC_SPI0_BASE)
#define LPC_SPI1                        ((LPC_SPI0_Type           *) LPC_SPI1_BASE)
#define LPC_USART0                      ((LPC_USART0_Type         *) LPC_USART0_BASE)
#define LPC_USART1                      ((LPC_USART0_Type         *) LPC_USART1_BASE)
#define LPC_USART2                      ((LPC_USART0_Type         *) LPC_USART2_BASE)
#define LPC_I2C2                        ((LPC_I2C0_Type           *) LPC_I2C2_BASE)
#define LPC_I2C3                        ((LPC_I2C0_Type           *) LPC_I2C3_BASE)
#define LPC_CRC                         ((LPC_CRC_Type            *) LPC_CRC_BASE)
#define LPC_SCT                         ((LPC_SCT_Type            *) LPC_SCT_BASE)
#define LPC_DMA                         ((LPC_DMA_Type            *) LPC_DMA_BASE)
#define LPC_GPIO_PORT                   ((LPC_GPIO_PORT_Type      *) LPC_GPIO_PORT_BASE)
#define LPC_PIN_INT                     ((LPC_PIN_INT_Type        *) LPC_PIN_INT_BASE)


/** @} */ /* End of group Device_Peripheral_Registers */
/** @} */ /* End of group LPC82x */
/** @} */ /* End of group (null) */

#ifdef __cplusplus
}
#endif


#endif  /* LPC82x_H */

