
/****************************************************************************************************//**
 * @file     LPC15xx.h
 *
 * @brief    CMSIS Cortex-M3 Peripheral Access Layer Header File for
 *           LPC15xx from .
 *
 * @version  V0.3
 * @date     17. July 2013
 *
 * @note     Generated with SVDConv V2.80 
 *           from CMSIS SVD File 'H2_v0.3.svd' Version 0.3,
 *
 *                                                                                      modified by Keil
 *                                                                                      modified by ytsuboi
 *******************************************************************************************************/



/** @addtogroup (null)
  * @{
  */

/** @addtogroup LPC15xx
  * @{
  */

#ifndef LPC15XX_H
#define LPC15XX_H

#ifdef __cplusplus
extern "C" {
#endif


/* -------------------------  Interrupt Number Definition  ------------------------ */

typedef enum {
/* -------------------  Cortex-M3 Processor Exceptions Numbers  ------------------- */
  Reset_IRQn                    = -15,              /*!<   1  Reset Vector, invoked on Power up and warm reset                 */
  NonMaskableInt_IRQn           = -14,              /*!<   2  Non maskable Interrupt, cannot be stopped or preempted           */
  HardFault_IRQn                = -13,              /*!<   3  Hard Fault, all classes of Fault                                 */
  MemoryManagement_IRQn         = -12,              /*!<   4  Memory Management, MPU mismatch, including Access Violation
                                                              and No Match                                                     */
  BusFault_IRQn                 = -11,              /*!<   5  Bus Fault, Pre-Fetch-, Memory Access Fault, other address/memory
                                                              related Fault                                                    */
  UsageFault_IRQn               = -10,              /*!<   6  Usage Fault, i.e. Undef Instruction, Illegal State Transition    */
  SVCall_IRQn                   =  -5,              /*!<  11  System Service Call via SVC instruction                          */
  DebugMonitor_IRQn             =  -4,              /*!<  12  Debug Monitor                                                    */
  PendSV_IRQn                   =  -2,              /*!<  14  Pendable request for system service                              */
  SysTick_IRQn                  =  -1,              /*!<  15  System Tick Timer                                                */
/* ---------------------  LPC15xx Specific Interrupt Numbers  --------------------- */
  WDT_IRQn                      =   0,              /*!<   0  WDT                                                              */
  BOD_IRQn                      =   1,              /*!<   1  BOD                                                          */
  FLASH_IRQn                    =   2,              /*!<   2  FLASH                                                            */
  EE_IRQn                       =   3,              /*!<   3  EE                                                               */
  DMA_IRQn                      =   4,              /*!<   4  DMA                                                              */
  GINT0_IRQn                    =   5,              /*!<   5  GINT0                                                            */
  GINT1_IRQn                    =   6,              /*!<   6  GINT1                                                            */
  PIN_INT0_IRQn                 =   7,              /*!<   7  PIN_INT0                                                         */
  PIN_INT1_IRQn                 =   8,              /*!<   8  PIN_INT1                                                         */
  PIN_INT2_IRQn                 =   9,              /*!<   9  PIN_INT2                                                         */
  PIN_INT3_IRQn                 =  10,              /*!<  10  PIN_INT3                                                         */
  PIN_INT4_IRQn                 =  11,              /*!<  11  PIN_INT4                                                         */
  PIN_INT5_IRQn                 =  12,              /*!<  12  PIN_INT5                                                         */
  PIN_INT6_IRQn                 =  13,              /*!<  13  PIN_INT6                                                         */
  PIN_INT7_IRQn                 =  14,              /*!<  14  PIN_INT7                                                         */
  RIT_IRQn                      =  15,              /*!<  15  RIT                                                              */
  SCT0_IRQn                     =  16,              /*!<  16  SCT0                                                             */
  SCT1_IRQn                     =  17,              /*!<  17  SCT1                                                             */
  SCT2_IRQn                     =  18,              /*!<  18  SCT2                                                             */
  SCT3_IRQn                     =  19,              /*!<  19  SCT3                                                             */
  MRT_IRQn                      =  20,              /*!<  20  MRT                                                              */
  UART0_IRQn                    =  21,              /*!<  21  UART0                                                            */
  UART1_IRQn                    =  22,              /*!<  22  UART1                                                            */
  UART2_IRQn                    =  23,              /*!<  23  UART2                                                            */
  I2C0_IRQn                     =  24,              /*!<  24  I2C0                                                             */
  SPI0_IRQn                     =  25,              /*!<  25  SPI0                                                             */
  SPI1_IRQn                     =  26,              /*!<  26  SPI1                                                             */
  C_CAN0_IRQn                   =  27,              /*!<  27  C_CAN0                                                           */
  USB_IRQ_IRQn                  =  28,              /*!<  28  USB_IRQ                                                          */
  USB_FIQ_IRQn                  =  29,              /*!<  29  USB_FIQ                                                          */
  USBWAKEUP_IRQn                =  30,              /*!<  30  USBWAKEUP                                                        */
  ADC0_SEQA_IRQn                =  31,              /*!<  31  ADC0_SEQA                                                        */
  ADC0_SEQB_IRQn                =  32,              /*!<  32  ADC0_SEQB                                                        */
  ADC0_THCMP_IRQn               =  33,              /*!<  33  ADC0_THCMP                                                       */
  ADC0_OVR_IRQn                 =  34,              /*!<  34  ADC0_OVR                                                         */
  ADC1_SEQA_IRQn                =  35,              /*!<  35  ADC1_SEQA                                                        */
  ADC1_SEQB_IRQn                =  36,              /*!<  36  ADC1_SEQB                                                        */
  ADC1_THCMP_IRQn               =  37,              /*!<  37  ADC1_THCMP                                                       */
  ADC1_OVR_IRQn                 =  38,              /*!<  38  ADC1_OVR                                                         */
  DAC_IRQn                      =  39,              /*!<  39  DAC                                                              */
  CMP0_IRQn                     =  40,              /*!<  40  CMP0                                                             */
  CMP1_IRQn                     =  41,              /*!<  41  CMP1                                                             */
  CMP2_IRQn                     =  42,              /*!<  42  CMP2                                                             */
  CMP3_IRQn                     =  43,              /*!<  43  CMP3                                                             */
  QEI_IRQn                      =  44,              /*!<  44  QEI                                                              */
  RTC_ALARM_IRQn                =  45,              /*!<  45  RTC_ALARM                                                        */
  RTC_WAKE_IRQn                 =  46               /*!<  46  RTC_WAKE                                                         */
} IRQn_Type;


/** @addtogroup Configuration_of_CMSIS
  * @{
  */


/* ================================================================================ */
/* ================      Processor and Core Peripheral Section     ================ */
/* ================================================================================ */

/* ----------------Configuration of the Cortex-M3 Processor and Core Peripherals---------------- */
#define __CM3_REV                 0x0201            /*!< Cortex-M3 Core Revision                                               */
#define __MPU_PRESENT                  0            /*!< MPU present or not                                                    */
#define __NVIC_PRIO_BITS               3            /*!< Number of Bits used for Priority Levels                               */
#define __Vendor_SysTickConfig         0            /*!< Set to 1 if different SysTick Config is used                          */
/** @} */ /* End of group Configuration_of_CMSIS */

#include "core_cm3.h"                               /*!< Cortex-M3 processor and core peripherals                              */
#include "system_LPC15xx.h"                         /*!< LPC15xx System                                                        */


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
/* ================                    GPIO_PORT                   ================ */
/* ================================================================================ */


/**
  * @brief General Purpose I/O (GPIO)  (GPIO_PORT)
  */

typedef struct {                                    /*!< GPIO_PORT Structure                                                   */
  __IO uint8_t   B[76];                             /*!< Byte pin registers                                                    */
  __I  uint32_t  RESERVED0[45];
  __IO uint32_t  W[76];                             /*!< Word pin registers                                                    */
  __I  uint32_t  RESERVED1[1908];
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
/* ================                       DMA                      ================ */
/* ================================================================================ */


/**
  * @brief DMA controller (DMA)
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
  __I  uint32_t  RESERVED28;
  __IO uint32_t  CFG16;                             /*!< Configuration register for DMA channel 0.                             */
  __I  uint32_t  CTLSTAT16;                         /*!< Control and status register for DMA channel 0.                        */
  __IO uint32_t  XFERCFG16;                         /*!< Transfer configuration register for DMA channel 0.                    */
  __I  uint32_t  RESERVED29;
  __IO uint32_t  CFG17;                             /*!< Configuration register for DMA channel 0.                             */
  __I  uint32_t  CTLSTAT17;                         /*!< Control and status register for DMA channel 0.                        */
  __IO uint32_t  XFERCFG17;                         /*!< Transfer configuration register for DMA channel 0.                    */
} LPC_DMA_Type;


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
/* ================                      SCT0                      ================ */
/* ================================================================================ */


/**
  * @brief Large State Configurable Timers 0/1 (SCT0/1) (SCT0)
  */

typedef struct {                                    /*!< SCT0 Structure                                                        */
  __IO uint32_t  CONFIG;                            /*!< SCT configuration register                                            */
  __IO uint32_t  CTRL;                              /*!< SCT control register                                                  */
  __IO uint32_t  LIMIT;                             /*!< SCT limit register                                                    */
  __IO uint32_t  HALT;                              /*!< SCT halt condition register                                           */
  __IO uint32_t  STOP;                              /*!< SCT stop condition register                                           */
  __IO uint32_t  START;                             /*!< SCT start condition register                                          */
  __IO uint32_t  DITHER;                            /*!< SCT dither condition register                                         */
  __I  uint32_t  RESERVED0[9];
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
    __I  uint32_t  CAP0;                            /*!< SCT capture register of capture channel 0 to 15; REGMOD0 to
                                                         REGMODE15 = 1                                                         */
    __IO uint32_t  MATCH0;                          /*!< SCT match value register of match channels 0 to 15; REGMOD0
                                                         to REGMODE15 = 0                                                      */
  };
  
  union {
    __I  uint32_t  CAP1;                            /*!< SCT capture register of capture channel 0 to 15; REGMOD0 to
                                                         REGMODE15 = 1                                                         */
    __IO uint32_t  MATCH1;                          /*!< SCT match value register of match channels 0 to 15; REGMOD0
                                                         to REGMODE15 = 0                                                      */
  };
  
  union {
    __I  uint32_t  CAP2;                            /*!< SCT capture register of capture channel 0 to 15; REGMOD0 to
                                                         REGMODE15 = 1                                                         */
    __IO uint32_t  MATCH2;                          /*!< SCT match value register of match channels 0 to 15; REGMOD0
                                                         to REGMODE15 = 0                                                      */
  };
  
  union {
    __I  uint32_t  CAP3;                            /*!< SCT capture register of capture channel 0 to 15; REGMOD0 to
                                                         REGMODE15 = 1                                                         */
    __IO uint32_t  MATCH3;                          /*!< SCT match value register of match channels 0 to 15; REGMOD0
                                                         to REGMODE15 = 0                                                      */
  };
  
  union {
    __I  uint32_t  CAP4;                            /*!< SCT capture register of capture channel 0 to 15; REGMOD0 to
                                                         REGMODE15 = 1                                                         */
    __IO uint32_t  MATCH4;                          /*!< SCT match value register of match channels 0 to 15; REGMOD0
                                                         to REGMODE15 = 0                                                      */
  };
  
  union {
    __I  uint32_t  CAP5;                            /*!< SCT capture register of capture channel 0 to 15; REGMOD0 to
                                                         REGMODE15 = 1                                                         */
    __IO uint32_t  MATCH5;                          /*!< SCT match value register of match channels 0 to 15; REGMOD0
                                                         to REGMODE15 = 0                                                      */
  };
  
  union {
    __I  uint32_t  CAP6;                            /*!< SCT capture register of capture channel 0 to 15; REGMOD0 to
                                                         REGMODE15 = 1                                                         */
    __IO uint32_t  MATCH6;                          /*!< SCT match value register of match channels 0 to 15; REGMOD0
                                                         to REGMODE15 = 0                                                      */
  };
  
  union {
    __IO uint32_t  MATCH7;                          /*!< SCT match value register of match channels 0 to 15; REGMOD0
                                                         to REGMODE15 = 0                                                      */
    __I  uint32_t  CAP7;                            /*!< SCT capture register of capture channel 0 to 15; REGMOD0 to
                                                         REGMODE15 = 1                                                         */
  };
  
  union {
    __I  uint32_t  CAP8;                            /*!< SCT capture register of capture channel 0 to 15; REGMOD0 to
                                                         REGMODE15 = 1                                                         */
    __IO uint32_t  MATCH8;                          /*!< SCT match value register of match channels 0 to 15; REGMOD0
                                                         to REGMODE15 = 0                                                      */
  };
  
  union {
    __IO uint32_t  MATCH9;                          /*!< SCT match value register of match channels 0 to 15; REGMOD0
                                                         to REGMODE15 = 0                                                      */
    __I  uint32_t  CAP9;                            /*!< SCT capture register of capture channel 0 to 15; REGMOD0 to
                                                         REGMODE15 = 1                                                         */
  };
  
  union {
    __IO uint32_t  MATCH10;                         /*!< SCT match value register of match channels 0 to 15; REGMOD0
                                                         to REGMODE15 = 0                                                      */
    __I  uint32_t  CAP10;                           /*!< SCT capture register of capture channel 0 to 15; REGMOD0 to
                                                         REGMODE15 = 1                                                         */
  };
  
  union {
    __IO uint32_t  MATCH11;                         /*!< SCT match value register of match channels 0 to 15; REGMOD0
                                                         to REGMODE15 = 0                                                      */
    __I  uint32_t  CAP11;                           /*!< SCT capture register of capture channel 0 to 15; REGMOD0 to
                                                         REGMODE15 = 1                                                         */
  };
  
  union {
    __IO uint32_t  MATCH12;                         /*!< SCT match value register of match channels 0 to 15; REGMOD0
                                                         to REGMODE15 = 0                                                      */
    __I  uint32_t  CAP12;                           /*!< SCT capture register of capture channel 0 to 15; REGMOD0 to
                                                         REGMODE15 = 1                                                         */
  };
  
  union {
    __IO uint32_t  MATCH13;                         /*!< SCT match value register of match channels 0 to 15; REGMOD0
                                                         to REGMODE15 = 0                                                      */
    __I  uint32_t  CAP13;                           /*!< SCT capture register of capture channel 0 to 15; REGMOD0 to
                                                         REGMODE15 = 1                                                         */
  };
  
  union {
    __I  uint32_t  CAP14;                           /*!< SCT capture register of capture channel 0 to 15; REGMOD0 to
                                                         REGMODE15 = 1                                                         */
    __IO uint32_t  MATCH14;                         /*!< SCT match value register of match channels 0 to 15; REGMOD0
                                                         to REGMODE15 = 0                                                      */
  };
  
  union {
    __IO uint32_t  MATCH15;                         /*!< SCT match value register of match channels 0 to 15; REGMOD0
                                                         to REGMODE15 = 0                                                      */
    __I  uint32_t  CAP15;                           /*!< SCT capture register of capture channel 0 to 15; REGMOD0 to
                                                         REGMODE15 = 1                                                         */
  };
  __IO uint32_t  FRACMAT0;                          /*!< Fractional match registers 0 to 5 for SCT match value registers
                                                         0 to 5.                                                               */
  __IO uint32_t  FRACMAT1;                          /*!< Fractional match registers 0 to 5 for SCT match value registers
                                                         0 to 5.                                                               */
  __IO uint32_t  FRACMAT2;                          /*!< Fractional match registers 0 to 5 for SCT match value registers
                                                         0 to 5.                                                               */
  __IO uint32_t  FRACMAT3;                          /*!< Fractional match registers 0 to 5 for SCT match value registers
                                                         0 to 5.                                                               */
  __IO uint32_t  FRACMAT4;                          /*!< Fractional match registers 0 to 5 for SCT match value registers
                                                         0 to 5.                                                               */
  __IO uint32_t  FRACMAT5;                          /*!< Fractional match registers 0 to 5 for SCT match value registers
                                                         0 to 5.                                                               */
  __I  uint32_t  RESERVED2[42];
  
  union {
    __IO uint32_t  CAPCTRL0;                        /*!< SCT capture control register 0 to 15; REGMOD0 = 1 to REGMODE15
                                                         = 1                                                                   */
    __IO uint32_t  MATCHREL0;                       /*!< SCT match reload value register 0 to 15; REGMOD0 = 0 to REGMODE15
                                                         = 0                                                                   */
  };
  
  union {
    __IO uint32_t  MATCHREL1;                       /*!< SCT match reload value register 0 to 15; REGMOD0 = 0 to REGMODE15
                                                         = 0                                                                   */
    __IO uint32_t  CAPCTRL1;                        /*!< SCT capture control register 0 to 15; REGMOD0 = 1 to REGMODE15
                                                         = 1                                                                   */
  };
  
  union {
    __IO uint32_t  MATCHREL2;                       /*!< SCT match reload value register 0 to 15; REGMOD0 = 0 to REGMODE15
                                                         = 0                                                                   */
    __IO uint32_t  CAPCTRL2;                        /*!< SCT capture control register 0 to 15; REGMOD0 = 1 to REGMODE15
                                                         = 1                                                                   */
  };
  
  union {
    __IO uint32_t  CAPCTRL3;                        /*!< SCT capture control register 0 to 15; REGMOD0 = 1 to REGMODE15
                                                         = 1                                                                   */
    __IO uint32_t  MATCHREL3;                       /*!< SCT match reload value register 0 to 15; REGMOD0 = 0 to REGMODE15
                                                         = 0                                                                   */
  };
  
  union {
    __IO uint32_t  CAPCTRL4;                        /*!< SCT capture control register 0 to 15; REGMOD0 = 1 to REGMODE15
                                                         = 1                                                                   */
    __IO uint32_t  MATCHREL4;                       /*!< SCT match reload value register 0 to 15; REGMOD0 = 0 to REGMODE15
                                                         = 0                                                                   */
  };
  
  union {
    __IO uint32_t  CAPCTRL5;                        /*!< SCT capture control register 0 to 15; REGMOD0 = 1 to REGMODE15
                                                         = 1                                                                   */
    __IO uint32_t  MATCHREL5;                       /*!< SCT match reload value register 0 to 15; REGMOD0 = 0 to REGMODE15
                                                         = 0                                                                   */
  };
  
  union {
    __IO uint32_t  MATCHREL6;                       /*!< SCT match reload value register 0 to 15; REGMOD0 = 0 to REGMODE15
                                                         = 0                                                                   */
    __IO uint32_t  CAPCTRL6;                        /*!< SCT capture control register 0 to 15; REGMOD0 = 1 to REGMODE15
                                                         = 1                                                                   */
  };
  
  union {
    __IO uint32_t  MATCHREL7;                       /*!< SCT match reload value register 0 to 15; REGMOD0 = 0 to REGMODE15
                                                         = 0                                                                   */
    __IO uint32_t  CAPCTRL7;                        /*!< SCT capture control register 0 to 15; REGMOD0 = 1 to REGMODE15
                                                         = 1                                                                   */
  };
  
  union {
    __IO uint32_t  CAPCTRL8;                        /*!< SCT capture control register 0 to 15; REGMOD0 = 1 to REGMODE15
                                                         = 1                                                                   */
    __IO uint32_t  MATCHREL8;                       /*!< SCT match reload value register 0 to 15; REGMOD0 = 0 to REGMODE15
                                                         = 0                                                                   */
  };
  
  union {
    __IO uint32_t  CAPCTRL9;                        /*!< SCT capture control register 0 to 15; REGMOD0 = 1 to REGMODE15
                                                         = 1                                                                   */
    __IO uint32_t  MATCHREL9;                       /*!< SCT match reload value register 0 to 15; REGMOD0 = 0 to REGMODE15
                                                         = 0                                                                   */
  };
  
  union {
    __IO uint32_t  CAPCTRL10;                       /*!< SCT capture control register 0 to 15; REGMOD0 = 1 to REGMODE15
                                                         = 1                                                                   */
    __IO uint32_t  MATCHREL10;                      /*!< SCT match reload value register 0 to 15; REGMOD0 = 0 to REGMODE15
                                                         = 0                                                                   */
  };
  
  union {
    __IO uint32_t  CAPCTRL11;                       /*!< SCT capture control register 0 to 15; REGMOD0 = 1 to REGMODE15
                                                         = 1                                                                   */
    __IO uint32_t  MATCHREL11;                      /*!< SCT match reload value register 0 to 15; REGMOD0 = 0 to REGMODE15
                                                         = 0                                                                   */
  };
  
  union {
    __IO uint32_t  MATCHREL12;                      /*!< SCT match reload value register 0 to 15; REGMOD0 = 0 to REGMODE15
                                                         = 0                                                                   */
    __IO uint32_t  CAPCTRL12;                       /*!< SCT capture control register 0 to 15; REGMOD0 = 1 to REGMODE15
                                                         = 1                                                                   */
  };
  
  union {
    __IO uint32_t  MATCHREL13;                      /*!< SCT match reload value register 0 to 15; REGMOD0 = 0 to REGMODE15
                                                         = 0                                                                   */
    __IO uint32_t  CAPCTRL13;                       /*!< SCT capture control register 0 to 15; REGMOD0 = 1 to REGMODE15
                                                         = 1                                                                   */
  };
  
  union {
    __IO uint32_t  CAPCTRL14;                       /*!< SCT capture control register 0 to 15; REGMOD0 = 1 to REGMODE15
                                                         = 1                                                                   */
    __IO uint32_t  MATCHREL14;                      /*!< SCT match reload value register 0 to 15; REGMOD0 = 0 to REGMODE15
                                                         = 0                                                                   */
  };
  
  union {
    __IO uint32_t  CAPCTRL15;                       /*!< SCT capture control register 0 to 15; REGMOD0 = 1 to REGMODE15
                                                         = 1                                                                   */
    __IO uint32_t  MATCHREL15;                      /*!< SCT match reload value register 0 to 15; REGMOD0 = 0 to REGMODE15
                                                         = 0                                                                   */
  };
  __IO uint32_t  FRACMATREL0;                       /*!< Fractional match reload registers 0 to 5 for SCT match value
                                                         registers 0 to 5.                                                     */
  __IO uint32_t  FRACMATREL1;                       /*!< Fractional match reload registers 0 to 5 for SCT match value
                                                         registers 0 to 5.                                                     */
  __IO uint32_t  FRACMATREL2;                       /*!< Fractional match reload registers 0 to 5 for SCT match value
                                                         registers 0 to 5.                                                     */
  __IO uint32_t  FRACMATREL3;                       /*!< Fractional match reload registers 0 to 5 for SCT match value
                                                         registers 0 to 5.                                                     */
  __IO uint32_t  FRACMATREL4;                       /*!< Fractional match reload registers 0 to 5 for SCT match value
                                                         registers 0 to 5.                                                     */
  __IO uint32_t  FRACMATREL5;                       /*!< Fractional match reload registers 0 to 5 for SCT match value
                                                         registers 0 to 5.                                                     */
  __I  uint32_t  RESERVED3[42];
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
  __IO uint32_t  EV6_STATE;                         /*!< SCT event state register 0                                            */
  __IO uint32_t  EV6_CTRL;                          /*!< SCT event control register 0                                          */
  __IO uint32_t  EV7_STATE;                         /*!< SCT event state register 0                                            */
  __IO uint32_t  EV7_CTRL;                          /*!< SCT event control register 0                                          */
  __IO uint32_t  EV8_STATE;                         /*!< SCT event state register 0                                            */
  __IO uint32_t  EV8_CTRL;                          /*!< SCT event control register 0                                          */
  __IO uint32_t  EV9_STATE;                         /*!< SCT event state register 0                                            */
  __IO uint32_t  EV9_CTRL;                          /*!< SCT event control register 0                                          */
  __IO uint32_t  EV10_STATE;                        /*!< SCT event state register 0                                            */
  __IO uint32_t  EV10_CTRL;                         /*!< SCT event control register 0                                          */
  __IO uint32_t  EV11_STATE;                        /*!< SCT event state register 0                                            */
  __IO uint32_t  EV11_CTRL;                         /*!< SCT event control register 0                                          */
  __IO uint32_t  EV12_STATE;                        /*!< SCT event state register 0                                            */
  __IO uint32_t  EV12_CTRL;                         /*!< SCT event control register 0                                          */
  __IO uint32_t  EV13_STATE;                        /*!< SCT event state register 0                                            */
  __IO uint32_t  EV13_CTRL;                         /*!< SCT event control register 0                                          */
  __IO uint32_t  EV14_STATE;                        /*!< SCT event state register 0                                            */
  __IO uint32_t  EV14_CTRL;                         /*!< SCT event control register 0                                          */
  __IO uint32_t  EV15_STATE;                        /*!< SCT event state register 0                                            */
  __IO uint32_t  EV15_CTRL;                         /*!< SCT event control register 0                                          */
  __I  uint32_t  RESERVED4[96];
  __IO uint32_t  OUT0_SET;                          /*!< SCT output 0 set register                                             */
  __IO uint32_t  OUT0_CLR;                          /*!< SCT output 0 clear register                                           */
  __IO uint32_t  OUT1_SET;                          /*!< SCT output 0 set register                                             */
  __IO uint32_t  OUT1_CLR;                          /*!< SCT output 0 clear register                                           */
  __IO uint32_t  OUT2_SET;                          /*!< SCT output 0 set register                                             */
  __IO uint32_t  OUT2_CLR;                          /*!< SCT output 0 clear register                                           */
  __IO uint32_t  OUT3_SET;                          /*!< SCT output 0 set register                                             */
  __IO uint32_t  OUT3_CLR;                          /*!< SCT output 0 clear register                                           */
  __IO uint32_t  OUT4_SET;                          /*!< SCT output 0 set register                                             */
  __IO uint32_t  OUT4_CLR;                          /*!< SCT output 0 clear register                                           */
  __IO uint32_t  OUT5_SET;                          /*!< SCT output 0 set register                                             */
  __IO uint32_t  OUT5_CLR;                          /*!< SCT output 0 clear register                                           */
  __IO uint32_t  OUT6_SET;                          /*!< SCT output 0 set register                                             */
  __IO uint32_t  OUT6_CLR;                          /*!< SCT output 0 clear register                                           */
  __IO uint32_t  OUT7_SET;                          /*!< SCT output 0 set register                                             */
  __IO uint32_t  OUT7_CLR;                          /*!< SCT output 0 clear register                                           */
  __IO uint32_t  OUT8_SET;                          /*!< SCT output 0 set register                                             */
  __IO uint32_t  OUT8_CLR;                          /*!< SCT output 0 clear register                                           */
  __IO uint32_t  OUT9_SET;                          /*!< SCT output 0 set register                                             */
  __IO uint32_t  OUT9_CLR;                          /*!< SCT output 0 clear register                                           */
} LPC_SCT0_Type;


/* ================================================================================ */
/* ================                      SCT2                      ================ */
/* ================================================================================ */


/**
  * @brief Small State Configurable Timers 2/3 (SCT2/3)  (SCT2)
  */

typedef struct {                                    /*!< SCT2 Structure                                                        */
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
    __I  uint32_t  CAP0;                            /*!< SCT capture register of capture channel 0 to 7; REGMOD0 to REGMODE7
                                                         = 1                                                                   */
    __IO uint32_t  MATCH0;                          /*!< SCT match value register of match channels 0 to 7; REGMOD0 to
                                                         REGMODE7 = 0                                                          */
  };
  
  union {
    __I  uint32_t  CAP1;                            /*!< SCT capture register of capture channel 0 to 7; REGMOD0 to REGMODE7
                                                         = 1                                                                   */
    __IO uint32_t  MATCH1;                          /*!< SCT match value register of match channels 0 to 7; REGMOD0 to
                                                         REGMODE7 = 0                                                          */
  };
  
  union {
    __I  uint32_t  CAP2;                            /*!< SCT capture register of capture channel 0 to 7; REGMOD0 to REGMODE7
                                                         = 1                                                                   */
    __IO uint32_t  MATCH2;                          /*!< SCT match value register of match channels 0 to 7; REGMOD0 to
                                                         REGMODE7 = 0                                                          */
  };
  
  union {
    __IO uint32_t  MATCH3;                          /*!< SCT match value register of match channels 0 to 7; REGMOD0 to
                                                         REGMODE7 = 0                                                          */
    __I  uint32_t  CAP3;                            /*!< SCT capture register of capture channel 0 to 7; REGMOD0 to REGMODE7
                                                         = 1                                                                   */
  };
  
  union {
    __I  uint32_t  CAP4;                            /*!< SCT capture register of capture channel 0 to 7; REGMOD0 to REGMODE7
                                                         = 1                                                                   */
    __IO uint32_t  MATCH4;                          /*!< SCT match value register of match channels 0 to 7; REGMOD0 to
                                                         REGMODE7 = 0                                                          */
  };
  
  union {
    __IO uint32_t  MATCH5;                          /*!< SCT match value register of match channels 0 to 7; REGMOD0 to
                                                         REGMODE7 = 0                                                          */
    __I  uint32_t  CAP5;                            /*!< SCT capture register of capture channel 0 to 7; REGMOD0 to REGMODE7
                                                         = 1                                                                   */
  };
  
  union {
    __I  uint32_t  CAP6;                            /*!< SCT capture register of capture channel 0 to 7; REGMOD0 to REGMODE7
                                                         = 1                                                                   */
    __IO uint32_t  MATCH6;                          /*!< SCT match value register of match channels 0 to 7; REGMOD0 to
                                                         REGMODE7 = 0                                                          */
  };
  
  union {
    __I  uint32_t  CAP7;                            /*!< SCT capture register of capture channel 0 to 7; REGMOD0 to REGMODE7
                                                         = 1                                                                   */
    __IO uint32_t  MATCH7;                          /*!< SCT match value register of match channels 0 to 7; REGMOD0 to
                                                         REGMODE7 = 0                                                          */
  };
  __I  uint32_t  RESERVED2[56];
  
  union {
    __IO uint32_t  CAPCTRL0;                        /*!< SCT capture control register 0 to 7; REGMOD0 = 1 to REGMODE7
                                                         = 1                                                                   */
    __IO uint32_t  MATCHREL0;                       /*!< SCT match reload value register 0 to 7; REGMOD0 = 0 to REGMODE7
                                                         = 0                                                                   */
  };
  
  union {
    __IO uint32_t  CAPCTRL1;                        /*!< SCT capture control register 0 to 7; REGMOD0 = 1 to REGMODE7
                                                         = 1                                                                   */
    __IO uint32_t  MATCHREL1;                       /*!< SCT match reload value register 0 to 7; REGMOD0 = 0 to REGMODE7
                                                         = 0                                                                   */
  };
  
  union {
    __IO uint32_t  CAPCTRL2;                        /*!< SCT capture control register 0 to 7; REGMOD0 = 1 to REGMODE7
                                                         = 1                                                                   */
    __IO uint32_t  MATCHREL2;                       /*!< SCT match reload value register 0 to 7; REGMOD0 = 0 to REGMODE7
                                                         = 0                                                                   */
  };
  
  union {
    __IO uint32_t  MATCHREL3;                       /*!< SCT match reload value register 0 to 7; REGMOD0 = 0 to REGMODE7
                                                         = 0                                                                   */
    __IO uint32_t  CAPCTRL3;                        /*!< SCT capture control register 0 to 7; REGMOD0 = 1 to REGMODE7
                                                         = 1                                                                   */
  };
  
  union {
    __IO uint32_t  CAPCTRL4;                        /*!< SCT capture control register 0 to 7; REGMOD0 = 1 to REGMODE7
                                                         = 1                                                                   */
    __IO uint32_t  MATCHREL4;                       /*!< SCT match reload value register 0 to 7; REGMOD0 = 0 to REGMODE7
                                                         = 0                                                                   */
  };
  
  union {
    __IO uint32_t  MATCHREL5;                       /*!< SCT match reload value register 0 to 7; REGMOD0 = 0 to REGMODE7
                                                         = 0                                                                   */
    __IO uint32_t  CAPCTRL5;                        /*!< SCT capture control register 0 to 7; REGMOD0 = 1 to REGMODE7
                                                         = 1                                                                   */
  };
  
  union {
    __IO uint32_t  CAPCTRL6;                        /*!< SCT capture control register 0 to 7; REGMOD0 = 1 to REGMODE7
                                                         = 1                                                                   */
    __IO uint32_t  MATCHREL6;                       /*!< SCT match reload value register 0 to 7; REGMOD0 = 0 to REGMODE7
                                                         = 0                                                                   */
  };
  
  union {
    __IO uint32_t  CAPCTRL7;                        /*!< SCT capture control register 0 to 7; REGMOD0 = 1 to REGMODE7
                                                         = 1                                                                   */
    __IO uint32_t  MATCHREL7;                       /*!< SCT match reload value register 0 to 7; REGMOD0 = 0 to REGMODE7
                                                         = 0                                                                   */
  };
  __I  uint32_t  RESERVED3[56];
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
  __IO uint32_t  EV6_STATE;                         /*!< SCT event state register 0                                            */
  __IO uint32_t  EV6_CTRL;                          /*!< SCT event control register 0                                          */
  __IO uint32_t  EV7_STATE;                         /*!< SCT event state register 0                                            */
  __IO uint32_t  EV7_CTRL;                          /*!< SCT event control register 0                                          */
  __IO uint32_t  EV8_STATE;                         /*!< SCT event state register 0                                            */
  __IO uint32_t  EV8_CTRL;                          /*!< SCT event control register 0                                          */
  __IO uint32_t  EV9_STATE;                         /*!< SCT event state register 0                                            */
  __IO uint32_t  EV9_CTRL;                          /*!< SCT event control register 0                                          */
  __I  uint32_t  RESERVED4[108];
  __IO uint32_t  OUT0_SET;                          /*!< SCT output 0 set register                                             */
  __IO uint32_t  OUT0_CLR;                          /*!< SCT output 0 clear register                                           */
  __IO uint32_t  OUT1_SET;                          /*!< SCT output 0 set register                                             */
  __IO uint32_t  OUT1_CLR;                          /*!< SCT output 0 clear register                                           */
  __IO uint32_t  OUT2_SET;                          /*!< SCT output 0 set register                                             */
  __IO uint32_t  OUT2_CLR;                          /*!< SCT output 0 clear register                                           */
  __IO uint32_t  OUT3_SET;                          /*!< SCT output 0 set register                                             */
  __IO uint32_t  OUT3_CLR;                          /*!< SCT output 0 clear register                                           */
  __IO uint32_t  OUT4_SET;                          /*!< SCT output 0 set register                                             */
  __IO uint32_t  OUT4_CLR;                          /*!< SCT output 0 clear register                                           */
  __IO uint32_t  OUT5_SET;                          /*!< SCT output 0 set register                                             */
  __IO uint32_t  OUT5_CLR;                          /*!< SCT output 0 clear register                                           */
} LPC_SCT2_Type;


/* ================================================================================ */
/* ================                      ADC0                      ================ */
/* ================================================================================ */


/**
  * @brief 12-bit ADC controller ADC0/1  (ADC0)
  */

typedef struct {                                    /*!< ADC0 Structure                                                        */
  __IO uint32_t  CTRL;                              /*!< A/D Control Register. Contains the clock divide value, enable
                                                         bits for each sequence and the A/D power-down bit.                    */
  __IO uint32_t  INSEL;                             /*!< A/D Input Select Register: Selects between external pin and
                                                         internal source for various channels                                  */
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
  __I  uint32_t  RESERVED0[2];
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
} LPC_ADC0_Type;


/* ================================================================================ */
/* ================                       DAC                      ================ */
/* ================================================================================ */


/**
  * @brief 12-bit DAC Modification  (DAC)
  */

typedef struct {                                    /*!< DAC Structure                                                         */
  __IO uint32_t  VAL;                               /*!< D/A Converter Value Register. This register contains the digital
                                                         value to be converted to analog.                                      */
  __IO uint32_t  CTRL;                              /*!< DAC Control register. This register contains bits to configure
                                                         DAC operation and the interrupt/dma request flag.                     */
  __IO uint32_t  CNTVAL;                            /*!< DAC Counter Value register. This register contains the reload
                                                         value for the internal DAC DMA/Interrupt timer.                       */
} LPC_DAC_Type;


/* ================================================================================ */
/* ================                      ACMP                      ================ */
/* ================================================================================ */


/**
  * @brief Analog comparators ACMP0/1/2/3 (ACMP)
  */

typedef struct {                                    /*!< ACMP Structure                                                        */
  __IO uint32_t  CTRL;                              /*!< Comparator block control register                                     */
  __IO uint32_t  CMP0;                              /*!< Comparator 0 source control                                           */
  __IO uint32_t  CMPFILTR0;                         /*!< Comparator 0 pin filter set-up                                        */
  __IO uint32_t  CMP1;                              /*!< Comparator 1 source control                                           */
  __IO uint32_t  CMPFILTR1;                         /*!< Comparator 0 pin filter set-up                                        */
  __IO uint32_t  CMP2;                              /*!< Comparator 2 source control                                           */
  __IO uint32_t  CMPFILTR2;                         /*!< Comparator 0 pin filter set-up                                        */
  __IO uint32_t  CMP3;                              /*!< Comparator 3 source control                                           */
  __IO uint32_t  CMPFILTR3;                         /*!< Comparator 0 pin filter set-up                                        */
} LPC_ACMP_Type;


/* ================================================================================ */
/* ================                      INMUX                     ================ */
/* ================================================================================ */


/**
  * @brief Input multiplexing (INMUX)  (INMUX)
  */

typedef struct {                                    /*!< INMUX Structure                                                       */
  __IO uint32_t  SCT0_INMUX[7];                     /*!< Pinmux register for SCT0 input 0                                      */
  __I  uint32_t  RESERVED0;
  __IO uint32_t  SCT1_INMUX[7];                     /*!< Pinmux register for SCT1 input 0                                      */
  __I  uint32_t  RESERVED1;
  __IO uint32_t  SCT2_INMUX[3];                     /*!< Pinmux register for SCT2 input 0                                      */
  __I  uint32_t  RESERVED2[5];
  __IO uint32_t  SCT3_INMUX[3];                     /*!< Pinmux register for SCT3 input 0                                      */
  __I  uint32_t  RESERVED3[21];
  __IO uint32_t  PINTSEL[8];                        /*!< Pin interrupt select register 0                                       */
  __IO uint32_t  DMA_ITRIG_INMUX[18];               /*!< Trigger input for DMA channel 0 select register.                      */
  __I  uint32_t  RESERVED4[14];
  __IO uint32_t  FREQMEAS_REF;                      /*!< Clock selection for frequency measurement function reference
                                                         clock                                                                 */
  __IO uint32_t  FREQMEAS_TARGET;                   /*!< Clock selection for frequency measurement function target clock       */
} LPC_INMUX_Type;


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
  __I  uint32_t  RESERVED0;
  __IO uint32_t  WARNINT;                           /*!< Watchdog Warning Interrupt compare value.                             */
  __IO uint32_t  WINDOW;                            /*!< Watchdog Window compare value.                                        */
} LPC_WWDT_Type;


/* ================================================================================ */
/* ================                       SWM                      ================ */
/* ================================================================================ */


/**
  * @brief Switch Matrix (SWM) (SWM)
  */

typedef struct {                                    /*!< SWM Structure                                                         */
  union {
    __IO uint32_t PINASSIGN[16];
    struct {
	  __IO uint32_t  PINASSIGN0;                        /*!< Pin assign register 0. Assign movable functions U0_TXD, U0_RXD,
	                                                         U0_RTS, U0_CTS.                                                       */
	  __IO uint32_t  PINASSIGN1;                        /*!< Pin assign register 1. Assign movable functions U0_SCLK, U1_TXD,
	                                                         U1_RXD, U1_RTS.                                                       */
	  __IO uint32_t  PINASSIGN2;                        /*!< Pin assign register 2. Assign movable functions U1_CTS, U1_SCLK,
	                                                         U2_TXD, U2_RXD.                                                       */
	  __IO uint32_t  PINASSIGN3;                        /*!< Pin assign register 3. Assign movable function .                      */
	  __IO uint32_t  PINASSIGN4;                        /*!< Pin assign register 4. Assign movable functions                       */
	  __IO uint32_t  PINASSIGN5;                        /*!< Pin assign register 5. Assign movable functions                       */
	  __IO uint32_t  PINASSIGN6;                        /*!< Pin assign register 6. Assign movable functions                       */
	  __IO uint32_t  PINASSIGN7;                        /*!< Pin assign register 7. Assign movable functions                       */
	  __IO uint32_t  PINASSIGN8;                        /*!< Pin assign register 8. Assign movable functions                       */
	  __IO uint32_t  PINASSIGN9;                        /*!< Pin assign register 9. Assign movable functions                       */
	  __IO uint32_t  PINASSIGN10;                       /*!< Pin assign register 10. Assign movable functions                      */
	  __IO uint32_t  PINASSIGN11;                       /*!< Pin assign register 11. Assign movable functions                      */
	  __IO uint32_t  PINASSIGN12;                       /*!< Pin assign register 12. Assign movable functions                      */
	  __IO uint32_t  PINASSIGN13;                       /*!< Pin assign register 13. Assign movable functions                      */
	  __IO uint32_t  PINASSIGN14;                       /*!< Pin assign register 14. Assign movable functions                      */
	  __IO uint32_t  PINASSIGN15;                       /*!< Pin assign register 15. Assign movable functions                      */
    };
  };
  __I  uint32_t  RESERVED0[96];
  __IO uint32_t  PINENABLE0;                        /*!< Pin enable register 0. Enables fixed-pin functions                    */
  __IO uint32_t  PINENABLE1;                        /*!< Pin enable register 0. Enables fixed-pin functions                    */
} LPC_SWM_Type;


/* ================================================================================ */
/* ================                       PMU                      ================ */
/* ================================================================================ */


/**
  * @brief Power Management Unit (PMU) (PMU)
  */

typedef struct {                                    /*!< PMU Structure                                                         */
  __IO uint32_t  PCON;                              /*!< Power control register                                                */
  __IO uint32_t  GPREG0;                            /*!< General purpose register 0                                            */
  __IO uint32_t  GPREG1;                            /*!< General purpose register 0                                            */
  __IO uint32_t  GPREG2;                            /*!< General purpose register 0                                            */
  __IO uint32_t  GPREG3;                            /*!< General purpose register 0                                            */
  __IO uint32_t  DPDCTRL;                           /*!< Deep power-down control register                                      */
} LPC_PMU_Type;


/* ================================================================================ */
/* ================                     USART0                     ================ */
/* ================================================================================ */


/**
  * @brief USART0  (USART0)
  */

typedef struct {                                    /*!< USART0 Structure                                                      */
  __IO uint32_t  CFG;                               /*!< USART Configuration register. Basic USART configuration settings
                                                         that typically are not changed during operation.                      */
  __IO uint32_t  CTRL;                              /*!< USART Control register. USART control settings that are more
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
  __I  uint32_t  RXDATA;                            /*!< Receiver Data register. Contains the last character received.         */
  __I  uint32_t  RXDATASTAT;                        /*!< Receiver Data with Status register. Combines the last character
                                                         received with the current USART receive status. Allows DMA or
                                                          software to recover incoming data and status together.               */
  __IO uint32_t  TXDATA;                            /*!< Transmit Data register. Data to be transmitted is written here.       */
  __IO uint32_t  BRG;                               /*!< Baud Rate Generator register. 16-bit integer baud rate divisor
                                                         value.                                                                */
  __I  uint32_t  INTSTAT;                           /*!< Interrupt status register. Reflects interrupts that are currently
                                                         enabled.                                                              */
} LPC_USART0_Type;


/* ================================================================================ */
/* ================                      SPI0                      ================ */
/* ================================================================================ */


/**
  * @brief SPI0  (SPI0)
  */

typedef struct {                                    /*!< SPI0 Structure                                                        */
  __IO uint32_t  CFG;                               /*!< SPI Configuration register                                            */
  __IO uint32_t  DLY;                               /*!< SPI Delay register                                                    */
  __IO uint32_t  STAT;                              /*!< SPI Status. Some status flags can be cleared by writing a 1
                                                         to that bit position                                                  */
  __IO uint32_t  INTENSET;                          /*!< SPI Interrupt Enable read and Set. A complete value may be read
                                                         from this register. Writing a 1 to any implemented bit position
                                                          causes that bit to be set.                                           */
  __O  uint32_t  INTENCLR;                          /*!< SPI Interrupt Enable Clear. Writing a 1 to any implemented bit
                                                         position causes the corresponding bit in INTENSET to be cleared.      */
  __I  uint32_t  RXDAT;                             /*!< SPI Receive Data                                                      */
  __IO uint32_t  TXDATCTL;                          /*!< SPI Transmit Data with Control                                        */
  __IO uint32_t  TXDAT;                             /*!< SPI Transmit Data with Control                                        */
  __IO uint32_t  TXCTL;                             /*!< SPI Transmit Control                                                  */
  __IO uint32_t  DIV;                               /*!< SPI clock Divider                                                     */
  __I  uint32_t  INTSTAT;                           /*!< SPI Interrupt Status                                                  */
} LPC_SPI0_Type;


/* ================================================================================ */
/* ================                      I2C0                      ================ */
/* ================================================================================ */


/**
  * @brief I2C-bus interface  (I2C0)
  */

typedef struct {                                    /*!< I2C0 Structure                                                        */
  __IO uint32_t  CFG;                               /*!< Configuration for shared functions.                                   */
  __IO uint32_t  STAT;                              /*!< Status register for Master, Slave, and Monitor functions.             */
  __IO uint32_t  INTENSET;                          /*!< Interrupt Enable Set and read register.                               */
  __O  uint32_t  INTENCLR;                          /*!< Interrupt Enable Clear register.                                      */
  __IO uint32_t  TIMEOUT;                           /*!< Time-out value register.                                              */
  __IO uint32_t  DIV;                               /*!< Clock pre-divider for the entire I2C block. This determines
                                                         what time increments are used for the MSTTIME and SLVTIME registers.  */
  __I  uint32_t  INTSTAT;                           /*!< Interrupt Status register for Master, Slave, and Monitor functions.   */
  __I  uint32_t  RESERVED0;
  __IO uint32_t  MSTCTL;                            /*!< Master control register.                                              */
  __IO uint32_t  MSTTIME;                           /*!< Master timing configuration.                                          */
  __IO uint32_t  MSTDAT;                            /*!< Combined Master receiver and transmitter data register.               */
  __I  uint32_t  RESERVED1[5];
  __IO uint32_t  SLVCTL;                            /*!< Slave control register.                                               */
  __IO uint32_t  SLVDAT;                            /*!< Combined Slave receiver and transmitter data register.                */
  __IO uint32_t  SLVADR0;                           /*!< Slave address 0.                                                      */
  __IO uint32_t  SLVADR1;                           /*!< Slave address 0.                                                      */
  __IO uint32_t  SLVADR2;                           /*!< Slave address 0.                                                      */
  __IO uint32_t  SLVADR3;                           /*!< Slave address 0.                                                      */
  __IO uint32_t  SLVQUAL0;                          /*!< Slave Qualification for address 0.                                    */
  __I  uint32_t  RESERVED2[9];
  __I  uint32_t  MONRXDAT;                          /*!< Monitor receiver data register.                                       */
} LPC_I2C0_Type;


/* ================================================================================ */
/* ================                       QEI                      ================ */
/* ================================================================================ */


/**
  * @brief Quadrature Encoder Interface (QEI)  (QEI)
  */

typedef struct {                                    /*!< QEI Structure                                                         */
  __O  uint32_t  CON;                               /*!< Control register                                                      */
  __I  uint32_t  STAT;                              /*!< Encoder status register                                               */
  __IO uint32_t  CONF;                              /*!< Configuration register                                                */
  __I  uint32_t  POS;                               /*!< Position register                                                     */
  __IO uint32_t  MAXPOS;                            /*!< Maximum position register                                             */
  __IO uint32_t  CMPOS0;                            /*!< position compare register 0                                           */
  __IO uint32_t  CMPOS1;                            /*!< position compare register 1                                           */
  __IO uint32_t  CMPOS2;                            /*!< position compare register 2                                           */
  __I  uint32_t  INXCNT;                            /*!< Index count register                                                  */
  __IO uint32_t  INXCMP0;                           /*!< Index compare register 0                                              */
  __IO uint32_t  LOAD;                              /*!< Velocity timer reload register                                        */
  __I  uint32_t  TIME;                              /*!< Velocity timer register                                               */
  __I  uint32_t  VEL;                               /*!< Velocity counter register                                             */
  __I  uint32_t  CAP;                               /*!< Velocity capture register                                             */
  __IO uint32_t  VELCOMP;                           /*!< Velocity compare register                                             */
  __IO uint32_t  FILTERPHA;                         /*!< Digital filter register on input phase A (QEI_A)                      */
  __IO uint32_t  FILTERPHB;                         /*!< Digital filter register on input phase B (QEI_B)                      */
  __IO uint32_t  FILTERINX;                         /*!< Digital filter register on input index (QEI_IDX)                      */
  __IO uint32_t  WINDOW;                            /*!< Index acceptance window register                                      */
  __IO uint32_t  INXCMP1;                           /*!< Index compare register 1                                              */
  __IO uint32_t  INXCMP2;                           /*!< Index compare register 2                                              */
  __I  uint32_t  RESERVED0[993];
  __O  uint32_t  IEC;                               /*!< Interrupt enable clear register                                       */
  __O  uint32_t  IES;                               /*!< Interrupt enable set register                                         */
  __I  uint32_t  INTSTAT;                           /*!< Interrupt status register                                             */
  __O  uint32_t  IE;                                /*!< Interrupt enable clear register                                       */
  __O  uint32_t  CLR;                               /*!< Interrupt status clear register                                       */
  __O  uint32_t  SET;                               /*!< Interrupt status set register                                         */
} LPC_QEI_Type;


/* ================================================================================ */
/* ================                     SYSCON                     ================ */
/* ================================================================================ */


/**
  * @brief System configuration (SYSCON) (SYSCON)
  */

typedef struct {                                    /*!< SYSCON Structure                                                      */
  __IO uint32_t  SYSMEMREMAP;                       /*!< System memory remap                                                   */
  __I  uint32_t  RESERVED0[4];
  __IO uint32_t  SYSTCKCAL;                         /*!< System tick counter calibration                                       */
  __I  uint32_t  RESERVED1;
  __IO uint32_t  NMISRC;                            /*!< NMI Source Control                                                    */
  __I  uint32_t  RESERVED2[8];
  __IO uint32_t  SYSRSTSTAT;                        /*!< System reset status register                                          */
  __IO uint32_t  PRESETCTRL0;                       /*!< Peripheral reset control 0                                            */
  __IO uint32_t  PRESETCTRL1;                       /*!< Peripheral reset control 1                                            */
  __I  uint32_t  PIOPORCAP0;                        /*!< POR captured PIO status 0                                             */
  __I  uint32_t  PIOPORCAP1;                        /*!< POR captured PIO status 1                                             */
  __I  uint32_t  PIOPORCAP2;                        /*!< POR captured PIO status 2                                             */
  __I  uint32_t  RESERVED3[10];
  __IO uint32_t  MAINCLKSELA;                       /*!< Main clock source select A                                            */
  __IO uint32_t  MAINCLKSELB;                       /*!< Main clock source select B                                            */
  __IO uint32_t  USBCLKSEL;                         /*!< USB clock source select                                               */
  __IO uint32_t  ADCASYNCCLKSEL;                    /*!< ADC asynchronous clock source select                                  */
  __I  uint32_t  RESERVED4;
  __IO uint32_t  CLKOUTSELA;                        /*!< CLKOUT clock source select A                                          */
  __IO uint32_t  CLKOUTSELB;                        /*!< CLKOUT clock source select B                                          */
  __I  uint32_t  RESERVED5;
  __IO uint32_t  SYSPLLCLKSEL;                      /*!< System PLL clock source select                                        */
  __IO uint32_t  USBPLLCLKSEL;                      /*!< USB PLL clock source select                                           */
  __IO uint32_t  SCTPLLCLKSEL;                      /*!< SCT PLL clock source select                                           */
  __I  uint32_t  RESERVED6[5];
  __IO uint32_t  SYSAHBCLKDIV;                      /*!< System clock divider                                                  */
  __IO uint32_t  SYSAHBCLKCTRL0;                    /*!< System clock control 0                                                */
  __IO uint32_t  SYSAHBCLKCTRL1;                    /*!< System clock control 1                                                */
  __IO uint32_t  SYSTICKCLKDIV;                     /*!< SYSTICK clock divider                                                 */
  __IO uint32_t  UARTCLKDIV;                        /*!< USART clock divider. Clock divider for the USART fractional
                                                         baud rate generator.                                                  */
  __IO uint32_t  IOCONCLKDIV;                       /*!< Peripheral clock to the IOCON block for programmable glitch
                                                         filter                                                                */
  __IO uint32_t  TRACECLKDIV;                       /*!< ARM trace clock divider                                               */
  __I  uint32_t  RESERVED7[4];
  __IO uint32_t  USBCLKDIV;                         /*!< USB clock divider                                                     */
  __IO uint32_t  ADCASYNCCLKDIV;                    /*!< Asynchronous ADC clock divider                                        */
  __I  uint32_t  RESERVED8;
  __IO uint32_t  CLKOUTDIV;                         /*!< CLKOUT clock divider                                                  */
  __I  uint32_t  RESERVED9[11];
  __IO uint32_t  FRGCTRL;                           /*!< USART fractional baud rate generator control                          */
  __IO uint32_t  USBCLKCTRL;                        /*!< USB clock control                                                     */
  __IO uint32_t  USBCLKST;                          /*!< USB clock status                                                      */
  __I  uint32_t  RESERVED10[19];
  __IO uint32_t  BODCTRL;                           /*!< Brown-Out Detect                                                      */
  __I  uint32_t  RESERVED11;
  __IO uint32_t  SYSOSCCTRL;                        /*!< System oscillator control                                             */
  __I  uint32_t  RESERVED12;
  __IO uint32_t  RTCOSCCTRL;                        /*!< RTC oscillator control                                                */
  __I  uint32_t  RESERVED13;
  __IO uint32_t  SYSPLLCTRL;                        /*!< System PLL control                                                    */
  __I  uint32_t  SYSPLLSTAT;                        /*!< System PLL status                                                     */
  __IO uint32_t  USBPLLCTRL;                        /*!< USB PLL control                                                       */
  __I  uint32_t  USBPLLSTAT;                        /*!< USB PLL status                                                        */
  __IO uint32_t  SCTPLLCTRL;                        /*!< SCT PLL control                                                       */
  __I  uint32_t  SCTPLLSTAT;                        /*!< SCT PLL status                                                        */
  __I  uint32_t  RESERVED14[21];
  __IO uint32_t  PDAWAKECFG;                        /*!< Power-down states for wake-up from deep-sleep                         */
  __IO uint32_t  PDRUNCFG;                          /*!< Power configuration register                                          */
  __I  uint32_t  RESERVED15[3];
  __IO uint32_t  STARTERP0;                         /*!< Start logic 0 wake-up enable register                                 */
  __IO uint32_t  STARTERP1;                         /*!< Start logic 1 wake-up enable register                                 */
} LPC_SYSCON_Type;


/* ================================================================================ */
/* ================                       MRT                      ================ */
/* ================================================================================ */


/**
  * @brief Multi-Rate Timer (MRT)  (MRT)
  */

typedef struct {                                    /*!< MRT Structure                                                         */
  __IO uint32_t  INTVAL0;                           /*!< MRT0 Time interval value register. This value is loaded into
                                                         the TIMER0 register.                                                  */
  __I  uint32_t  TIMER0;                            /*!< MRT0 Timer register. This register reads the value of the down-counter. */
  __IO uint32_t  CTRL0;                             /*!< MRT0 Control register. This register controls the MRT0 modes.         */
  __IO uint32_t  STAT0;                             /*!< MRT0 Status register.                                                 */
  __IO uint32_t  INTVAL1;                           /*!< MRT0 Time interval value register. This value is loaded into
                                                         the TIMER0 register.                                                  */
  __I  uint32_t  TIMER1;                            /*!< MRT0 Timer register. This register reads the value of the down-counter. */
  __IO uint32_t  CTRL1;                             /*!< MRT0 Control register. This register controls the MRT0 modes.         */
  __IO uint32_t  STAT1;                             /*!< MRT0 Status register.                                                 */
  __IO uint32_t  INTVAL2;                           /*!< MRT0 Time interval value register. This value is loaded into
                                                         the TIMER0 register.                                                  */
  __I  uint32_t  TIMER2;                            /*!< MRT0 Timer register. This register reads the value of the down-counter. */
  __IO uint32_t  CTRL2;                             /*!< MRT0 Control register. This register controls the MRT0 modes.         */
  __IO uint32_t  STAT2;                             /*!< MRT0 Status register.                                                 */
  __IO uint32_t  INTVAL3;                           /*!< MRT0 Time interval value register. This value is loaded into
                                                         the TIMER0 register.                                                  */
  __I  uint32_t  TIMER3;                            /*!< MRT0 Timer register. This register reads the value of the down-counter. */
  __IO uint32_t  CTRL3;                             /*!< MRT0 Control register. This register controls the MRT0 modes.         */
  __IO uint32_t  STAT3;                             /*!< MRT0 Status register.                                                 */
  __I  uint32_t  RESERVED0[45];
  __I  uint32_t  IDLE_CH;                           /*!< Idle channel register. This register returns the number of the
                                                         first idle channel.                                                   */
  __IO uint32_t  IRQ_FLAG;                          /*!< Global interrupt flag register                                        */
} LPC_MRT_Type;


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


/* ================================================================================ */
/* ================                      GINT0                     ================ */
/* ================================================================================ */


/**
  * @brief Group interrupt 0/1 (GINT0/1)  (GINT0)
  */

typedef struct {                                    /*!< GINT0 Structure                                                       */
  __IO uint32_t  CTRL;                              /*!< GPIO grouped interrupt control register                               */
  __I  uint32_t  RESERVED0[7];
  __IO uint32_t  PORT_POL[3];                       /*!< GPIO grouped interrupt port 0 polarity register                       */
  __I  uint32_t  RESERVED1[5];
  __IO uint32_t  PORT_ENA[3];                       /*!< GPIO grouped interrupt port 0 enable register                         */
} LPC_GINT0_Type;


/* ================================================================================ */
/* ================                       RIT                      ================ */
/* ================================================================================ */


/**
  * @brief Repetitive Interrupt Timer (RIT)  (RIT)
  */

typedef struct {                                    /*!< RIT Structure                                                         */
  __IO uint32_t  COMPVAL;                           /*!< Compare value LSB register. Holds the 32 LSBs of the compare
                                                         value.                                                                */
  __IO uint32_t  MASK;                              /*!< Mask LSB register. This register holds the 32 LSB s of the mask
                                                         value. A 1 written to any bit will force a compare on the corresponding
                                                          bit of the counter and compare register.                             */
  __IO uint32_t  CTRL;                              /*!< Control register.                                                     */
  __IO uint32_t  COUNTER;                           /*!< Counter LSB register. 32 LSBs of the counter.                         */
  __IO uint32_t  COMPVAL_H;                         /*!< Compare value MSB register. Holds the 16 MSBs of the compare
                                                         value.                                                                */
  __IO uint32_t  MASK_H;                            /*!< Mask MSB register. This register holds the 16 MSBs of the mask
                                                         value. A 1 written to any bit will force a compare on the corresponding
                                                          bit of the counter and compare register.                             */
  __I  uint32_t  RESERVED0;
  __IO uint32_t  COUNTER_H;                         /*!< Counter MSB register. 16 MSBs of the counter.                         */
} LPC_RIT_Type;


/* ================================================================================ */
/* ================                     SCTIPU                     ================ */
/* ================================================================================ */


/**
  * @brief SCT Input Processing Unit (IPU)  (SCTIPU)
  */

typedef struct {                                    /*!< SCTIPU Structure                                                      */
  __IO uint32_t  SAMPLE_CTRL;                       /*!< SCT IPU sample control register. Contains the input mux selects,
                                                         latch/sample-enable mux selects, and sample overrride bits for
                                                          the SAMPLE module.                                                   */
  __I  uint32_t  RESERVED0[7];
  __IO uint32_t  ABORT_ENABLE0;                     /*!< SCT IPU abort enable register: Selects which input source contributes
                                                         to ORed Abort Output 0.                                               */
  __IO uint32_t  ABORT_SOURCE0;                     /*!< SCT IPU abort source register: Status register indicating which
                                                         input source caused abort output 0.                                   */
  __I  uint32_t  RESERVED1[6];
  __IO uint32_t  ABORT_ENABLE1;                     /*!< SCT IPU abort enable register: Selects which input source contributes
                                                         to ORed Abort Output 0.                                               */
  __IO uint32_t  ABORT_SOURCE1;                     /*!< SCT IPU abort source register: Status register indicating which
                                                         input source caused abort output 0.                                   */
  __I  uint32_t  RESERVED2[6];
  __IO uint32_t  ABORT_ENABLE2;                     /*!< SCT IPU abort enable register: Selects which input source contributes
                                                         to ORed Abort Output 0.                                               */
  __IO uint32_t  ABORT_SOURCE2;                     /*!< SCT IPU abort source register: Status register indicating which
                                                         input source caused abort output 0.                                   */
  __I  uint32_t  RESERVED3[6];
  __IO uint32_t  ABORT_ENABLE3;                     /*!< SCT IPU abort enable register: Selects which input source contributes
                                                         to ORed Abort Output 0.                                               */
  __IO uint32_t  ABORT_SOURCE3;                     /*!< SCT IPU abort source register: Status register indicating which
                                                         input source caused abort output 0.                                   */
} LPC_SCTIPU_Type;


/* ================================================================================ */
/* ================                    FLASHCTRL                   ================ */
/* ================================================================================ */


/**
  * @brief Flash controller  (FLASHCTRL)
  */

typedef struct {                                    /*!< FLASHCTRL Structure                                                   */
  __I  uint32_t  RESERVED0[8];
  __IO uint32_t  FMSSTART;                          /*!< Signature start address register                                      */
  __IO uint32_t  FMSSTOP;                           /*!< Signature stop-address register                                       */
  __I  uint32_t  RESERVED1;
  __I  uint32_t  FMSW0;                             /*!< Signature word                                                        */
} LPC_FLASHCTRL_Type;


/* ================================================================================ */
/* ================                     C_CAN0                     ================ */
/* ================================================================================ */


/**
  * @brief Controller Area Network C_CAN0  (C_CAN0)
  */

typedef struct {                                    /*!< C_CAN0 Structure                                                      */
  __IO uint32_t  CANCNTL;                           /*!< CAN control                                                           */
  __IO uint32_t  CANSTAT;                           /*!< Status register                                                       */
  __I  uint32_t  CANEC;                             /*!< Error counter                                                         */
  __IO uint32_t  CANBT;                             /*!< Bit timing register                                                   */
  __I  uint32_t  CANINT;                            /*!< Interrupt register                                                    */
  __IO uint32_t  CANTEST;                           /*!< Test register                                                         */
  __IO uint32_t  CANBRPE;                           /*!< Baud rate prescaler extension register                                */
  __I  uint32_t  RESERVED0;
  __IO uint32_t  CANIF1_CMDREQ;                     /*!< Message interface 1 command request                                   */
  
  union {
    __IO uint32_t  CANIF1_CMDMSK_R;                 /*!< Message interface 1 command mask (read direction)                     */
    __IO uint32_t  CANIF1_CMDMSK_W;                 /*!< Message interface 1 command mask (write direction)                    */
  };
  __IO uint32_t  CANIF1_MSK1;                       /*!< Message interface 1 mask 1                                            */
  __IO uint32_t  CANIF1_MSK2;                       /*!< Message interface 1 mask 2                                            */
  __IO uint32_t  CANIF1_ARB1;                       /*!< Message interface 1 arbitration 1                                     */
  __IO uint32_t  CANIF1_ARB2;                       /*!< Message interface 1 arbitration 2                                     */
  __IO uint32_t  CANIF1_MCTRL;                      /*!< Message interface 1 message control                                   */
  __IO uint32_t  CANIF1_DA1;                        /*!< Message interface 1 data A1                                           */
  __IO uint32_t  CANIF1_DA2;                        /*!< Message interface 1 data A2                                           */
  __IO uint32_t  CANIF1_DB1;                        /*!< Message interface 1 data B1                                           */
  __IO uint32_t  CANIF1_DB2;                        /*!< Message interface 1 data B2                                           */
  __I  uint32_t  RESERVED1[13];
  __IO uint32_t  CANIF2_CMDREQ;                     /*!< Message interface 1 command request                                   */
  
  union {
    __IO uint32_t  CANIF2_CMDMSK_W;                 /*!< Message interface 1 command mask (write direction)                    */
    __IO uint32_t  CANIF2_CMDMSK_R;                 /*!< Message interface 1 command mask (read direction)                     */
  };
  __IO uint32_t  CANIF2_MSK1;                       /*!< Message interface 1 mask 1                                            */
  __IO uint32_t  CANIF2_MSK2;                       /*!< Message interface 1 mask 2                                            */
  __IO uint32_t  CANIF2_ARB1;                       /*!< Message interface 1 arbitration 1                                     */
  __IO uint32_t  CANIF2_ARB2;                       /*!< Message interface 1 arbitration 2                                     */
  __IO uint32_t  CANIF2_MCTRL;                      /*!< Message interface 1 message control                                   */
  __IO uint32_t  CANIF2_DA1;                        /*!< Message interface 2 data A1                                           */
  __IO uint32_t  CANIF2_DA2;                        /*!< Message interface 2 data A2                                           */
  __IO uint32_t  CANIF2_DB1;                        /*!< Message interface 2 data B1                                           */
  __IO uint32_t  CANIF2_DB2;                        /*!< Message interface 2 data B2                                           */
  __I  uint32_t  RESERVED2[21];
  __I  uint32_t  CANTXREQ1;                         /*!< Transmission request 1                                                */
  __I  uint32_t  CANTXREQ2;                         /*!< Transmission request 2                                                */
  __I  uint32_t  RESERVED3[6];
  __I  uint32_t  CANND1;                            /*!< New data 1                                                            */
  __I  uint32_t  CANND2;                            /*!< New data 2                                                            */
  __I  uint32_t  RESERVED4[6];
  __I  uint32_t  CANIR1;                            /*!< Interrupt pending 1                                                   */
  __I  uint32_t  CANIR2;                            /*!< Interrupt pending 2                                                   */
  __I  uint32_t  RESERVED5[6];
  __I  uint32_t  CANMSGV1;                          /*!< Message valid 1                                                       */
  __I  uint32_t  CANMSGV2;                          /*!< Message valid 2                                                       */
  __I  uint32_t  RESERVED6[6];
  __IO uint32_t  CANCLKDIV;                         /*!< Can clock divider register                                            */
} LPC_C_CAN0_Type;


/* ================================================================================ */
/* ================                      IOCON                     ================ */
/* ================================================================================ */


/**
  * @brief I/O pin configuration (IOCON)  (IOCON)
  */

typedef struct {                                    /*!< IOCON Structure                                                       */
  __IO uint32_t  PIO0_0;                            /*!< Digital I/O control for port 0 pins PIO0_0 to PIO0_21.                */
  __IO uint32_t  PIO0_1;                            /*!< Digital I/O control for port 0 pins PIO0_0 to PIO0_21.                */
  __IO uint32_t  PIO0_2;                            /*!< Digital I/O control for port 0 pins PIO0_0 to PIO0_21.                */
  __IO uint32_t  PIO0_3;                            /*!< Digital I/O control for port 0 pins PIO0_0 to PIO0_21.                */
  __IO uint32_t  PIO0_4;                            /*!< Digital I/O control for port 0 pins PIO0_0 to PIO0_21.                */
  __IO uint32_t  PIO0_5;                            /*!< Digital I/O control for port 0 pins PIO0_0 to PIO0_21.                */
  __IO uint32_t  PIO0_6;                            /*!< Digital I/O control for port 0 pins PIO0_0 to PIO0_21.                */
  __IO uint32_t  PIO0_7;                            /*!< Digital I/O control for port 0 pins PIO0_0 to PIO0_21.                */
  __IO uint32_t  PIO0_8;                            /*!< Digital I/O control for port 0 pins PIO0_0 to PIO0_21.                */
  __IO uint32_t  PIO0_9;                            /*!< Digital I/O control for port 0 pins PIO0_0 to PIO0_21.                */
  __IO uint32_t  PIO0_10;                           /*!< Digital I/O control for port 0 pins PIO0_0 to PIO0_21.                */
  __IO uint32_t  PIO0_11;                           /*!< Digital I/O control for port 0 pins PIO0_0 to PIO0_21.                */
  __IO uint32_t  PIO0_12;                           /*!< Digital I/O control for port 0 pins PIO0_0 to PIO0_21.                */
  __IO uint32_t  PIO0_13;                           /*!< Digital I/O control for port 0 pins PIO0_0 to PIO0_21.                */
  __IO uint32_t  PIO0_14;                           /*!< Digital I/O control for port 0 pins PIO0_0 to PIO0_21.                */
  __IO uint32_t  PIO0_15;                           /*!< Digital I/O control for port 0 pins PIO0_0 to PIO0_21.                */
  __IO uint32_t  PIO0_16;                           /*!< Digital I/O control for port 0 pins PIO0_0 to PIO0_21.                */
  __IO uint32_t  PIO0_17;                           /*!< Digital I/O control for port 0 pins PIO0_0 to PIO0_21.                */
  __IO uint32_t  PIO0_18;                           /*!< Digital I/O control for port 0 pins PIO0_0 to PIO0_21.                */
  __IO uint32_t  PIO0_19;                           /*!< Digital I/O control for port 0 pins PIO0_0 to PIO0_21.                */
  __IO uint32_t  PIO0_20;                           /*!< Digital I/O control for port 0 pins PIO0_0 to PIO0_21.                */
  __IO uint32_t  PIO0_21;                           /*!< Digital I/O control for port 0 pins PIO0_0 to PIO0_21.                */
  __IO uint32_t  PIO0_22;                           /*!< I/O control for open-drain pin PIO0_22. This pin is used for
                                                         the I2C-bus SCL function.                                             */
  __IO uint32_t  PIO0_23;                           /*!< I/O control for open-drain pin PIO0_22. This pin is used for
                                                         the I2C-bus SCL function.                                             */
  __IO uint32_t  PIO0_24;                           /*!< Digital I/O control for port 0 pins PIO0_24 to PIO0_31.               */
  __IO uint32_t  PIO0_25;                           /*!< Digital I/O control for port 0 pins PIO0_24 to PIO0_31.               */
  __IO uint32_t  PIO0_26;                           /*!< Digital I/O control for port 0 pins PIO0_24 to PIO0_31.               */
  __IO uint32_t  PIO0_27;                           /*!< Digital I/O control for port 0 pins PIO0_24 to PIO0_31.               */
  __IO uint32_t  PIO0_28;                           /*!< Digital I/O control for port 0 pins PIO0_24 to PIO0_31.               */
  __IO uint32_t  PIO0_29;                           /*!< Digital I/O control for port 0 pins PIO0_24 to PIO0_31.               */
  __IO uint32_t  PIO0_30;                           /*!< Digital I/O control for port 0 pins PIO0_24 to PIO0_31.               */
  __IO uint32_t  PIO0_31;                           /*!< Digital I/O control for port 0 pins PIO0_24 to PIO0_31.               */
  __IO uint32_t  PIO1_0;                            /*!< Digital I/O control for port 1 pins PIO1_24 to PIO1_31.               */
  __IO uint32_t  PIO1_1;                            /*!< Digital I/O control for port 1 pins PIO1_24 to PIO1_31.               */
  __IO uint32_t  PIO1_2;                            /*!< Digital I/O control for port 1 pins PIO1_24 to PIO1_31.               */
  __IO uint32_t  PIO1_3;                            /*!< Digital I/O control for port 1 pins PIO1_24 to PIO1_31.               */
  __IO uint32_t  PIO1_4;                            /*!< Digital I/O control for port 1 pins PIO1_24 to PIO1_31.               */
  __IO uint32_t  PIO1_5;                            /*!< Digital I/O control for port 1 pins PIO1_24 to PIO1_31.               */
  __IO uint32_t  PIO1_6;                            /*!< Digital I/O control for port 1 pins PIO1_24 to PIO1_31.               */
  __IO uint32_t  PIO1_7;                            /*!< Digital I/O control for port 1 pins PIO1_24 to PIO1_31.               */
  __IO uint32_t  PIO1_8;                            /*!< Digital I/O control for port 1 pins PIO1_24 to PIO1_31.               */
  __IO uint32_t  PIO1_9;                            /*!< Digital I/O control for port 1 pins PIO1_24 to PIO1_31.               */
  __IO uint32_t  PIO1_10;                           /*!< Digital I/O control for port 1 pins PIO1_24 to PIO1_31.               */
  __IO uint32_t  PIO1_11;                           /*!< Digital I/O control for port 1 pins PIO1_24 to PIO1_31.               */
  __IO uint32_t  PIO1_12;                           /*!< Digital I/O control for port 1 pins PIO1_24 to PIO1_31.               */
  __IO uint32_t  PIO1_13;                           /*!< Digital I/O control for port 1 pins PIO1_24 to PIO1_31.               */
  __IO uint32_t  PIO1_14;                           /*!< Digital I/O control for port 1 pins PIO1_24 to PIO1_31.               */
  __IO uint32_t  PIO1_15;                           /*!< Digital I/O control for port 1 pins PIO1_24 to PIO1_31.               */
  __IO uint32_t  PIO1_16;                           /*!< Digital I/O control for port 1 pins PIO1_24 to PIO1_31.               */
  __IO uint32_t  PIO1_17;                           /*!< Digital I/O control for port 1 pins PIO1_24 to PIO1_31.               */
  __IO uint32_t  PIO1_18;                           /*!< Digital I/O control for port 1 pins PIO1_24 to PIO1_31.               */
  __IO uint32_t  PIO1_19;                           /*!< Digital I/O control for port 1 pins PIO1_24 to PIO1_31.               */
  __IO uint32_t  PIO1_20;                           /*!< Digital I/O control for port 1 pins PIO1_24 to PIO1_31.               */
  __IO uint32_t  PIO1_21;                           /*!< Digital I/O control for port 1 pins PIO1_24 to PIO1_31.               */
  __IO uint32_t  PIO1_22;                           /*!< Digital I/O control for port 1 pins PIO1_24 to PIO1_31.               */
  __IO uint32_t  PIO1_23;                           /*!< Digital I/O control for port 1 pins PIO1_24 to PIO1_31.               */
  __IO uint32_t  PIO1_24;                           /*!< Digital I/O control for port 1 pins PIO1_24 to PIO1_31.               */
  __IO uint32_t  PIO1_25;                           /*!< Digital I/O control for port 1 pins PIO1_24 to PIO1_31.               */
  __IO uint32_t  PIO1_26;                           /*!< Digital I/O control for port 1 pins PIO1_24 to PIO1_31.               */
  __IO uint32_t  PIO1_27;                           /*!< Digital I/O control for port 1 pins PIO1_24 to PIO1_31.               */
  __IO uint32_t  PIO1_28;                           /*!< Digital I/O control for port 1 pins PIO1_24 to PIO1_31.               */
  __IO uint32_t  PIO1_29;                           /*!< Digital I/O control for port 1 pins PIO1_24 to PIO1_31.               */
  __IO uint32_t  PIO1_30;                           /*!< Digital I/O control for port 1 pins PIO1_24 to PIO1_31.               */
  __IO uint32_t  PIO1_31;                           /*!< Digital I/O control for port 1 pins PIO1_24 to PIO1_31.               */
  __IO uint32_t  PIO2_0;                            /*!< Digital I/O control for port 2 pins PIO2_0 to PIO2_11.                */
  __IO uint32_t  PIO2_1;                            /*!< Digital I/O control for port 2 pins PIO2_0 to PIO2_11.                */
  __IO uint32_t  PIO2_2;                            /*!< Digital I/O control for port 2 pins PIO2_0 to PIO2_11.                */
  __IO uint32_t  PIO2_3;                            /*!< Digital I/O control for port 2 pins PIO2_0 to PIO2_11.                */
  __IO uint32_t  PIO2_4;                            /*!< Digital I/O control for port 2 pins PIO2_0 to PIO2_11.                */
  __IO uint32_t  PIO2_5;                            /*!< Digital I/O control for port 2 pins PIO2_0 to PIO2_11.                */
  __IO uint32_t  PIO2_6;                            /*!< Digital I/O control for port 2 pins PIO2_0 to PIO2_11.                */
  __IO uint32_t  PIO2_7;                            /*!< Digital I/O control for port 2 pins PIO2_0 to PIO2_11.                */
  __IO uint32_t  PIO2_8;                            /*!< Digital I/O control for port 2 pins PIO2_0 to PIO2_11.                */
  __IO uint32_t  PIO2_9;                            /*!< Digital I/O control for port 2 pins PIO2_0 to PIO2_11.                */
  __IO uint32_t  PIO2_10;                           /*!< Digital I/O control for port 2 pins PIO2_0 to PIO2_11.                */
  __IO uint32_t  PIO2_11;                           /*!< Digital I/O control for port 2 pins PIO2_0 to PIO2_11.                */
} LPC_IOCON_Type;


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

#define LPC_GPIO_PORT_BASE              0x1C000000UL
#define LPC_DMA_BASE                    0x1C004000UL
#define LPC_USB_BASE                    0x1C00C000UL
#define LPC_CRC_BASE                    0x1C010000UL
#define LPC_SCT0_BASE                   0x1C018000UL
#define LPC_SCT1_BASE                   0x1C01C000UL
#define LPC_SCT2_BASE                   0x1C020000UL
#define LPC_SCT3_BASE                   0x1C024000UL
#define LPC_ADC0_BASE                   0x40000000UL
#define LPC_DAC_BASE                    0x40004000UL
#define LPC_ACMP_BASE                   0x40008000UL
#define LPC_INMUX_BASE                  0x40014000UL
#define LPC_RTC_BASE                    0x40028000UL
#define LPC_WWDT_BASE                   0x4002C000UL
#define LPC_SWM_BASE                    0x40038000UL
#define LPC_PMU_BASE                    0x4003C000UL
#define LPC_USART0_BASE                 0x40040000UL
#define LPC_USART1_BASE                 0x40044000UL
#define LPC_SPI0_BASE                   0x40048000UL
#define LPC_SPI1_BASE                   0x4004C000UL
#define LPC_I2C0_BASE                   0x40050000UL
#define LPC_QEI_BASE                    0x40058000UL
#define LPC_SYSCON_BASE                 0x40074000UL
#define LPC_ADC1_BASE                   0x40080000UL
#define LPC_MRT_BASE                    0x400A0000UL
#define LPC_PINT_BASE                   0x400A4000UL
#define LPC_GINT0_BASE                  0x400A8000UL
#define LPC_GINT1_BASE                  0x400AC000UL
#define LPC_RIT_BASE                    0x400B4000UL
#define LPC_SCTIPU_BASE                 0x400B8000UL
#define LPC_FLASHCTRL_BASE              0x400BC000UL
#define LPC_USART2_BASE                 0x400C0000UL
#define LPC_C_CAN0_BASE                 0x400F0000UL
#define LPC_IOCON_BASE                  0x400F8000UL


/* ================================================================================ */
/* ================             Peripheral declaration             ================ */
/* ================================================================================ */

#define LPC_GPIO_PORT                   ((LPC_GPIO_PORT_Type      *) LPC_GPIO_PORT_BASE)
#define LPC_DMA                         ((LPC_DMA_Type            *) LPC_DMA_BASE)
#define LPC_USB                         ((LPC_USB_Type            *) LPC_USB_BASE)
#define LPC_CRC                         ((LPC_CRC_Type            *) LPC_CRC_BASE)
#define LPC_SCT0                        ((LPC_SCT0_Type           *) LPC_SCT0_BASE)
#define LPC_SCT1                        ((LPC_SCT0_Type           *) LPC_SCT1_BASE)
#define LPC_SCT2                        ((LPC_SCT2_Type           *) LPC_SCT2_BASE)
#define LPC_SCT3                        ((LPC_SCT2_Type           *) LPC_SCT3_BASE)
#define LPC_ADC0                        ((LPC_ADC0_Type           *) LPC_ADC0_BASE)
#define LPC_DAC                         ((LPC_DAC_Type            *) LPC_DAC_BASE)
#define LPC_ACMP                        ((LPC_ACMP_Type           *) LPC_ACMP_BASE)
#define LPC_INMUX                       ((LPC_INMUX_Type          *) LPC_INMUX_BASE)
#define LPC_RTC                         ((LPC_RTC_Type            *) LPC_RTC_BASE)
#define LPC_WWDT                        ((LPC_WWDT_Type           *) LPC_WWDT_BASE)
#define LPC_SWM                         ((LPC_SWM_Type            *) LPC_SWM_BASE)
#define LPC_PMU                         ((LPC_PMU_Type            *) LPC_PMU_BASE)
#define LPC_USART0                      ((LPC_USART0_Type         *) LPC_USART0_BASE)
#define LPC_USART1                      ((LPC_USART0_Type         *) LPC_USART1_BASE)
#define LPC_SPI0                        ((LPC_SPI0_Type           *) LPC_SPI0_BASE)
#define LPC_SPI1                        ((LPC_SPI0_Type           *) LPC_SPI1_BASE)
#define LPC_I2C0                        ((LPC_I2C0_Type           *) LPC_I2C0_BASE)
#define LPC_QEI                         ((LPC_QEI_Type            *) LPC_QEI_BASE)
#define LPC_SYSCON                      ((LPC_SYSCON_Type         *) LPC_SYSCON_BASE)
#define LPC_ADC1                        ((LPC_ADC0_Type           *) LPC_ADC1_BASE)
#define LPC_MRT                         ((LPC_MRT_Type            *) LPC_MRT_BASE)
#define LPC_PINT                        ((LPC_PINT_Type           *) LPC_PINT_BASE)
#define LPC_GINT0                       ((LPC_GINT0_Type          *) LPC_GINT0_BASE)
#define LPC_GINT1                       ((LPC_GINT0_Type          *) LPC_GINT1_BASE)
#define LPC_RIT                         ((LPC_RIT_Type            *) LPC_RIT_BASE)
#define LPC_SCTIPU                      ((LPC_SCTIPU_Type         *) LPC_SCTIPU_BASE)
#define LPC_FLASHCTRL                   ((LPC_FLASHCTRL_Type      *) LPC_FLASHCTRL_BASE)
#define LPC_USART2                      ((LPC_USART0_Type         *) LPC_USART2_BASE)
#define LPC_C_CAN0                      ((LPC_C_CAN0_Type         *) LPC_C_CAN0_BASE)
#define LPC_IOCON                       ((LPC_IOCON_Type          *) LPC_IOCON_BASE)


/** @} */ /* End of group Device_Peripheral_Registers */
/** @} */ /* End of group LPC15xx */
/** @} */ /* End of group (null) */

#ifdef __cplusplus
}
#endif


#endif  /* LPC15XX_H */

