/* mbed Microcontroller Library - LPC23xx CMSIS-like structs
 * Copyright (C) 2009 ARM Limited. All rights reserved.
 * 
 * An LPC23xx header file, based on the CMSIS LPC17xx.h and old LPC23xx.h
 */

#ifndef __LPC23xx_H
#define __LPC23xx_H

#ifdef __cplusplus
 extern "C" {
#endif 

/*
 * ==========================================================================
 * ---------- Interrupt Number Definition -----------------------------------
 * ==========================================================================
 */

typedef enum IRQn
{
/******  LPC23xx Specific Interrupt Numbers *******************************************************/
  WDT_IRQn                      = 0,        /*!< Watchdog Timer Interrupt                         */

  TIMER0_IRQn                   = 4,        /*!< Timer0 Interrupt                                 */
  TIMER1_IRQn                   = 5,        /*!< Timer1 Interrupt                                 */
  UART0_IRQn                    = 6,        /*!< UART0 Interrupt                                  */
  UART1_IRQn                    = 7,        /*!< UART1 Interrupt                                  */
  PWM1_IRQn                     = 8,        /*!< PWM1 Interrupt                                   */
  I2C0_IRQn                     = 9,        /*!< I2C0 Interrupt                                   */
  SPI_IRQn                      = 10,       /*!< SPI Interrupt                                    */
  SSP0_IRQn                     = 10,       /*!< SSP0 Interrupt                                   */
  SSP1_IRQn                     = 11,       /*!< SSP1 Interrupt                                   */
  PLL0_IRQn                     = 12,       /*!< PLL0 Lock (Main PLL) Interrupt                   */
  RTC_IRQn                      = 13,       /*!< Real Time Clock Interrupt                        */
  EINT0_IRQn                    = 14,       /*!< External Interrupt 0 Interrupt                   */
  EINT1_IRQn                    = 15,       /*!< External Interrupt 1 Interrupt                   */
  EINT2_IRQn                    = 16,       /*!< External Interrupt 2 Interrupt                   */
  EINT3_IRQn                    = 17,       /*!< External Interrupt 3 Interrupt                   */
  ADC_IRQn                      = 18,       /*!< A/D Converter Interrupt                          */
  I2C1_IRQn                     = 19,       /*!< I2C1 Interrupt                                   */
  BOD_IRQn                      = 20,       /*!< Brown-Out Detect Interrupt                       */
  ENET_IRQn                     = 21,       /*!< Ethernet Interrupt                               */
  USB_IRQn                      = 22,       /*!< USB Interrupt                                    */
  CAN_IRQn                      = 23,       /*!< CAN Interrupt                                    */
  MIC_IRQn                      = 24,       /*!< Multimedia Interface Controler                   */
  DMA_IRQn                      = 25,       /*!< General Purpose DMA Interrupt                    */
  TIMER2_IRQn                   = 26,       /*!< Timer2 Interrupt                                 */
  TIMER3_IRQn                   = 27,       /*!< Timer3 Interrupt                                 */
  UART2_IRQn                    = 28,       /*!< UART2 Interrupt                                  */
  UART3_IRQn                    = 29,       /*!< UART3 Interrupt                                  */
  I2C2_IRQn                     = 30,       /*!< I2C2 Interrupt                                   */
  I2S_IRQn                      = 31,       /*!< I2S Interrupt                                    */
} IRQn_Type;

/*
 * ==========================================================================
 * ----------- Processor and Core Peripheral Section ------------------------
 * ==========================================================================
 */

/* Configuration of the ARM7 Processor and Core Peripherals */
#define __MPU_PRESENT             0         /*!< MPU present or not                               */
#define __NVIC_PRIO_BITS          4         /*!< Number of Bits used for Priority Levels          */
#define __Vendor_SysTickConfig    0         /*!< Set to 1 if different SysTick Config is used     */


#include <core_arm7.h>
#include "system_LPC23xx.h"                 /* System Header                                      */


/******************************************************************************/
/*                Device Specific Peripheral registers structures             */
/******************************************************************************/
#if defined ( __CC_ARM   )
  #pragma anon_unions
#endif

/*------------- Vector Interupt Controler (VIC) ------------------------------*/
typedef struct
{
  __I  uint32_t IRQStatus;
  __I  uint32_t FIQStatus;
  __I  uint32_t RawIntr;
  __IO uint32_t IntSelect;
  __IO uint32_t IntEnable;
  __O  uint32_t IntEnClr;
  __IO uint32_t SoftInt;
  __O  uint32_t SoftIntClr;
  __IO uint32_t Protection;
  __IO uint32_t SWPriorityMask;
  __IO uint32_t RESERVED0[54];
  __IO uint32_t VectAddr[32];
  __IO uint32_t RESERVED1[32];
  __IO uint32_t VectPriority[32];
  __IO uint32_t RESERVED2[800];
  __IO uint32_t Address;
} LPC_VIC_TypeDef;

/*------------- System Control (SC) ------------------------------------------*/
typedef struct
{
  __IO uint32_t MAMCR;
  __IO uint32_t MAMTIM;
       uint32_t RESERVED0[14];
  __IO uint32_t MEMMAP;
       uint32_t RESERVED1[15];
  __IO uint32_t PLL0CON;                /* Clocking and Power Control         */
  __IO uint32_t PLL0CFG;
  __I  uint32_t PLL0STAT;
  __O  uint32_t PLL0FEED;
       uint32_t RESERVED2[12];
  __IO uint32_t PCON;
  __IO uint32_t PCONP;
       uint32_t RESERVED3[15];
  __IO uint32_t CCLKCFG;
  __IO uint32_t USBCLKCFG;
  __IO uint32_t CLKSRCSEL;
       uint32_t RESERVED4[12];
  __IO uint32_t EXTINT;                 /* External Interrupts                */
  __IO uint32_t INTWAKE;
  __IO uint32_t EXTMODE;
  __IO uint32_t EXTPOLAR;
       uint32_t RESERVED6[12];
  __IO uint32_t RSID;                   /* Reset                              */
  __IO uint32_t CSPR;
  __IO uint32_t AHBCFG1;
  __IO uint32_t AHBCFG2;
       uint32_t RESERVED7[4];
  __IO uint32_t SCS;                    /* Syscon Miscellaneous Registers     */
  __IO uint32_t IRCTRIM;                /* Clock Dividers                     */
  __IO uint32_t PCLKSEL0;
  __IO uint32_t PCLKSEL1;
       uint32_t RESERVED8[4];
  __IO uint32_t USBIntSt;               /* USB Device/OTG Interrupt Register  */
       uint32_t RESERVED9;
//  __IO uint32_t CLKOUTCFG;              /* Clock Output Configuration         */
 } LPC_SC_TypeDef;

/*------------- Pin Connect Block (PINCON) -----------------------------------*/
typedef struct
{
  __IO uint32_t PINSEL0;
  __IO uint32_t PINSEL1;
  __IO uint32_t PINSEL2;
  __IO uint32_t PINSEL3;
  __IO uint32_t PINSEL4;
  __IO uint32_t PINSEL5;
  __IO uint32_t PINSEL6;
  __IO uint32_t PINSEL7;
  __IO uint32_t PINSEL8;
  __IO uint32_t PINSEL9;
  __IO uint32_t PINSEL10;
       uint32_t RESERVED0[5];
  __IO uint32_t PINMODE0;
  __IO uint32_t PINMODE1;
  __IO uint32_t PINMODE2;
  __IO uint32_t PINMODE3;
  __IO uint32_t PINMODE4;
  __IO uint32_t PINMODE5;
  __IO uint32_t PINMODE6;
  __IO uint32_t PINMODE7;
  __IO uint32_t PINMODE8;
  __IO uint32_t PINMODE9;
  __IO uint32_t PINMODE_OD0;
  __IO uint32_t PINMODE_OD1;
  __IO uint32_t PINMODE_OD2;
  __IO uint32_t PINMODE_OD3;
  __IO uint32_t PINMODE_OD4;
} LPC_PINCON_TypeDef;

/*------------- General Purpose Input/Output (GPIO) --------------------------*/
typedef struct
{
  __IO uint32_t FIODIR;
       uint32_t RESERVED0[3];
  __IO uint32_t FIOMASK;
  __IO uint32_t FIOPIN;
  __IO uint32_t FIOSET;
  __O  uint32_t FIOCLR;
} LPC_GPIO_TypeDef;

typedef struct
{
  __I  uint32_t IntStatus;
  __I  uint32_t IO0IntStatR;
  __I  uint32_t IO0IntStatF;
  __O  uint32_t IO0IntClr;
  __IO uint32_t IO0IntEnR;
  __IO uint32_t IO0IntEnF;
       uint32_t RESERVED0[3];
  __I  uint32_t IO2IntStatR;
  __I  uint32_t IO2IntStatF;
  __O  uint32_t IO2IntClr;
  __IO uint32_t IO2IntEnR;
  __IO uint32_t IO2IntEnF;
} LPC_GPIOINT_TypeDef;

/*------------- Timer (TIM) --------------------------------------------------*/
typedef struct
{
  __IO uint32_t IR;
  __IO uint32_t TCR;
  __IO uint32_t TC;
  __IO uint32_t PR;
  __IO uint32_t PC;
  __IO uint32_t MCR;
  __IO uint32_t MR0;
  __IO uint32_t MR1;
  __IO uint32_t MR2;
  __IO uint32_t MR3;
  __IO uint32_t CCR;
  __I  uint32_t CR0;
  __I  uint32_t CR1;
       uint32_t RESERVED0[2];
  __IO uint32_t EMR;
       uint32_t RESERVED1[12];
  __IO uint32_t CTCR;
} LPC_TIM_TypeDef;

/*------------- Pulse-Width Modulation (PWM) ---------------------------------*/
typedef struct
{
  __IO uint32_t IR;
  __IO uint32_t TCR;
  __IO uint32_t TC;
  __IO uint32_t PR;
  __IO uint32_t PC;
  __IO uint32_t MCR;
  __IO uint32_t MR0;
  __IO uint32_t MR1;
  __IO uint32_t MR2;
  __IO uint32_t MR3;
  __IO uint32_t CCR;
  __I  uint32_t CR0;
  __I  uint32_t CR1;
  __I  uint32_t CR2;
  __I  uint32_t CR3;
       uint32_t RESERVED0;
  __IO uint32_t MR4;
  __IO uint32_t MR5;
  __IO uint32_t MR6;
  __IO uint32_t PCR;
  __IO uint32_t LER;
       uint32_t RESERVED1[7];
  __IO uint32_t CTCR;
} LPC_PWM_TypeDef;

/*------------- Universal Asynchronous Receiver Transmitter (UART) -----------*/
typedef struct
{
  union {
  __I  uint8_t  RBR;
  __O  uint8_t  THR;
  __IO uint8_t  DLL;
       uint32_t RESERVED0;
  };
  union {
  __IO uint8_t  DLM;
  __IO uint32_t IER;
  };
  union {
  __I  uint32_t IIR;
  __O  uint8_t  FCR;
  };
  __IO uint8_t  LCR;
       uint8_t  RESERVED1[7];
  __IO uint8_t  LSR;
       uint8_t  RESERVED2[7];
  __IO uint8_t  SCR;
       uint8_t  RESERVED3[3];
  __IO uint32_t ACR;
  __IO uint8_t  ICR;
       uint8_t  RESERVED4[3];
  __IO uint8_t  FDR;
       uint8_t  RESERVED5[7];
  __IO uint8_t  TER;
       uint8_t  RESERVED6[27];
  __IO uint8_t  RS485CTRL;
       uint8_t  RESERVED7[3];
  __IO uint8_t  ADRMATCH;
} LPC_UART_TypeDef;

typedef struct
{
  union {
  __I  uint8_t  RBR;
  __O  uint8_t  THR;
  __IO uint8_t  DLL;
       uint32_t RESERVED0;
  };
  union {
  __IO uint8_t  DLM;
  __IO uint32_t IER;
  };
  union {
  __I  uint32_t IIR;
  __O  uint8_t  FCR;
  };
  __IO uint8_t  LCR;
       uint8_t  RESERVED1[3];
  __IO uint8_t  MCR;
       uint8_t  RESERVED2[3];
  __IO uint8_t  LSR;
       uint8_t  RESERVED3[3];
  __IO uint8_t  MSR;
       uint8_t  RESERVED4[3];
  __IO uint8_t  SCR;
       uint8_t  RESERVED5[3];
  __IO uint32_t ACR;
       uint32_t RESERVED6;
  __IO uint32_t FDR;
       uint32_t RESERVED7;
  __IO uint8_t  TER;
       uint8_t  RESERVED8[27];
  __IO uint8_t  RS485CTRL;
       uint8_t  RESERVED9[3];
  __IO uint8_t  ADRMATCH;
       uint8_t  RESERVED10[3];
  __IO uint8_t  RS485DLY;
} LPC_UART1_TypeDef;

/*------------- Serial Peripheral Interface (SPI) ----------------------------*/
typedef struct
{
  __IO uint32_t SPCR;
  __I  uint32_t SPSR;
  __IO uint32_t SPDR;
  __IO uint32_t SPCCR;
       uint32_t RESERVED0[3];
  __IO uint32_t SPINT;
} LPC_SPI_TypeDef;

/*------------- Synchronous Serial Communication (SSP) -----------------------*/
typedef struct
{
  __IO uint32_t CR0;
  __IO uint32_t CR1;
  __IO uint32_t DR;
  __I  uint32_t SR;
  __IO uint32_t CPSR;
  __IO uint32_t IMSC;
  __IO uint32_t RIS;
  __IO uint32_t MIS;
  __IO uint32_t ICR;
  __IO uint32_t DMACR;
} LPC_SSP_TypeDef;

/*------------- Inter-Integrated Circuit (I2C) -------------------------------*/
typedef struct
{
  __IO uint32_t I2CONSET;
  __I  uint32_t I2STAT;
  __IO uint32_t I2DAT;
  __IO uint32_t I2ADR0;
  __IO uint32_t I2SCLH;
  __IO uint32_t I2SCLL;
  __O  uint32_t I2CONCLR;
  __IO uint32_t MMCTRL;
  __IO uint32_t I2ADR1;
  __IO uint32_t I2ADR2;
  __IO uint32_t I2ADR3;
  __I  uint32_t I2DATA_BUFFER;
  __IO uint32_t I2MASK0;
  __IO uint32_t I2MASK1;
  __IO uint32_t I2MASK2;
  __IO uint32_t I2MASK3;
} LPC_I2C_TypeDef;

/*------------- Inter IC Sound (I2S) -----------------------------------------*/
typedef struct
{
  __IO uint32_t I2SDAO;
  __I  uint32_t I2SDAI;
  __O  uint32_t I2STXFIFO;
  __I  uint32_t I2SRXFIFO;
  __I  uint32_t I2SSTATE;
  __IO uint32_t I2SDMA1;
  __IO uint32_t I2SDMA2;
  __IO uint32_t I2SIRQ;
  __IO uint32_t I2STXRATE;
  __IO uint32_t I2SRXRATE;
  __IO uint32_t I2STXBITRATE;
  __IO uint32_t I2SRXBITRATE;
  __IO uint32_t I2STXMODE;
  __IO uint32_t I2SRXMODE;
} LPC_I2S_TypeDef;

/*------------- Real-Time Clock (RTC) ----------------------------------------*/
typedef struct
{
  __IO uint8_t  ILR;
       uint8_t  RESERVED0[3];
  __IO uint8_t  CTC;
       uint8_t  RESERVED1[3];
  __IO uint8_t  CCR;
       uint8_t  RESERVED2[3];
  __IO uint8_t  CIIR;
       uint8_t  RESERVED3[3];
  __IO uint8_t  AMR;
       uint8_t  RESERVED4[3];
  __I  uint32_t CTIME0;
  __I  uint32_t CTIME1;
  __I  uint32_t CTIME2;
  __IO uint8_t  SEC;
       uint8_t  RESERVED5[3];
  __IO uint8_t  MIN;
       uint8_t  RESERVED6[3];
  __IO uint8_t  HOUR;
       uint8_t  RESERVED7[3];
  __IO uint8_t  DOM;
       uint8_t  RESERVED8[3];
  __IO uint8_t  DOW;
       uint8_t  RESERVED9[3];
  __IO uint16_t DOY;
       uint16_t RESERVED10;
  __IO uint8_t  MONTH;
       uint8_t  RESERVED11[3];
  __IO uint16_t YEAR;
       uint16_t RESERVED12;
  __IO uint32_t CALIBRATION;
  __IO uint32_t GPREG0;
  __IO uint32_t GPREG1;
  __IO uint32_t GPREG2;
  __IO uint32_t GPREG3;
  __IO uint32_t GPREG4;
  __IO uint8_t  WAKEUPDIS;
       uint8_t  RESERVED13[3];
  __IO uint8_t  PWRCTRL;
       uint8_t  RESERVED14[3];
  __IO uint8_t  ALSEC;
       uint8_t  RESERVED15[3];
  __IO uint8_t  ALMIN;
       uint8_t  RESERVED16[3];
  __IO uint8_t  ALHOUR;
       uint8_t  RESERVED17[3];
  __IO uint8_t  ALDOM;
       uint8_t  RESERVED18[3];
  __IO uint8_t  ALDOW;
       uint8_t  RESERVED19[3];
  __IO uint16_t ALDOY;
       uint16_t RESERVED20;
  __IO uint8_t  ALMON;
       uint8_t  RESERVED21[3];
  __IO uint16_t ALYEAR;
       uint16_t RESERVED22;
} LPC_RTC_TypeDef;

/*------------- Watchdog Timer (WDT) -----------------------------------------*/
typedef struct
{
  __IO uint8_t  WDMOD;
       uint8_t  RESERVED0[3];
  __IO uint32_t WDTC;
  __O  uint8_t  WDFEED;
       uint8_t  RESERVED1[3];
  __I  uint32_t WDTV;
  __IO uint32_t WDCLKSEL;
} LPC_WDT_TypeDef;

/*------------- Analog-to-Digital Converter (ADC) ----------------------------*/
typedef struct
{
  __IO uint32_t ADCR;
  __IO uint32_t ADGDR;
       uint32_t RESERVED0;
  __IO uint32_t ADINTEN;
  __I  uint32_t ADDR0;
  __I  uint32_t ADDR1;
  __I  uint32_t ADDR2;
  __I  uint32_t ADDR3;
  __I  uint32_t ADDR4;
  __I  uint32_t ADDR5;
  __I  uint32_t ADDR6;
  __I  uint32_t ADDR7;
  __I  uint32_t ADSTAT;
  __IO uint32_t ADTRM;
} LPC_ADC_TypeDef;

/*------------- Digital-to-Analog Converter (DAC) ----------------------------*/
typedef struct
{
  __IO uint32_t DACR;
  __IO uint32_t DACCTRL;
  __IO uint16_t DACCNTVAL;
} LPC_DAC_TypeDef;

/*------------- Multimedia Card Interface (MCI) ------------------------------*/
typedef struct
{
  __IO uint32_t MCIPower;               /* Power control                      */
  __IO uint32_t MCIClock;               /* Clock control                      */
  __IO uint32_t MCIArgument;
  __IO uint32_t MMCCommand;
  __I  uint32_t MCIRespCmd;
  __I  uint32_t MCIResponse0;
  __I  uint32_t MCIResponse1;
  __I  uint32_t MCIResponse2;
  __I  uint32_t MCIResponse3;
  __IO uint32_t MCIDataTimer;
  __IO uint32_t MCIDataLength;
  __IO uint32_t MCIDataCtrl;
  __I  uint32_t MCIDataCnt;
} LPC_MCI_TypeDef;

/*------------- Controller Area Network (CAN) --------------------------------*/
typedef struct
{
  __IO uint32_t mask[512];              /* ID Masks                           */
} LPC_CANAF_RAM_TypeDef;

typedef struct                          /* Acceptance Filter Registers        */
{
  __IO uint32_t AFMR;
  __IO uint32_t SFF_sa;
  __IO uint32_t SFF_GRP_sa;
  __IO uint32_t EFF_sa;
  __IO uint32_t EFF_GRP_sa;
  __IO uint32_t ENDofTable;
  __I  uint32_t LUTerrAd;
  __I  uint32_t LUTerr;
} LPC_CANAF_TypeDef;

typedef struct                          /* Central Registers                  */
{
  __I  uint32_t CANTxSR;
  __I  uint32_t CANRxSR;
  __I  uint32_t CANMSR;
} LPC_CANCR_TypeDef;

typedef struct                          /* Controller Registers               */
{
  __IO uint32_t MOD;
  __O  uint32_t CMR;
  __IO uint32_t GSR;
  __I  uint32_t ICR;
  __IO uint32_t IER;
  __IO uint32_t BTR;
  __IO uint32_t EWL;
  __I  uint32_t SR;
  __IO uint32_t RFS;
  __IO uint32_t RID;
  __IO uint32_t RDA;
  __IO uint32_t RDB;
  __IO uint32_t TFI1;
  __IO uint32_t TID1;
  __IO uint32_t TDA1;
  __IO uint32_t TDB1;
  __IO uint32_t TFI2;
  __IO uint32_t TID2;
  __IO uint32_t TDA2;
  __IO uint32_t TDB2;
  __IO uint32_t TFI3;
  __IO uint32_t TID3;
  __IO uint32_t TDA3;
  __IO uint32_t TDB3;
} LPC_CAN_TypeDef;

/*------------- General Purpose Direct Memory Access (GPDMA) -----------------*/
typedef struct                          /* Common Registers                   */
{
  __I  uint32_t DMACIntStat;
  __I  uint32_t DMACIntTCStat;
  __O  uint32_t DMACIntTCClear;
  __I  uint32_t DMACIntErrStat;
  __O  uint32_t DMACIntErrClr;
  __I  uint32_t DMACRawIntTCStat;
  __I  uint32_t DMACRawIntErrStat;
  __I  uint32_t DMACEnbldChns;
  __IO uint32_t DMACSoftBReq;
  __IO uint32_t DMACSoftSReq;
  __IO uint32_t DMACSoftLBReq;
  __IO uint32_t DMACSoftLSReq;
  __IO uint32_t DMACConfig;
  __IO uint32_t DMACSync;
} LPC_GPDMA_TypeDef;

typedef struct                          /* Channel Registers                  */
{
  __IO uint32_t DMACCSrcAddr;
  __IO uint32_t DMACCDestAddr;
  __IO uint32_t DMACCLLI;
  __IO uint32_t DMACCControl;
  __IO uint32_t DMACCConfig;
} LPC_GPDMACH_TypeDef;

/*------------- Universal Serial Bus (USB) -----------------------------------*/
typedef struct
{
  __I  uint32_t HcRevision;             /* USB Host Registers                 */
  __IO uint32_t HcControl;
  __IO uint32_t HcCommandStatus;
  __IO uint32_t HcInterruptStatus;
  __IO uint32_t HcInterruptEnable;
  __IO uint32_t HcInterruptDisable;
  __IO uint32_t HcHCCA;
  __I  uint32_t HcPeriodCurrentED;
  __IO uint32_t HcControlHeadED;
  __IO uint32_t HcControlCurrentED;
  __IO uint32_t HcBulkHeadED;
  __IO uint32_t HcBulkCurrentED;
  __I  uint32_t HcDoneHead;
  __IO uint32_t HcFmInterval;
  __I  uint32_t HcFmRemaining;
  __I  uint32_t HcFmNumber;
  __IO uint32_t HcPeriodicStart;
  __IO uint32_t HcLSTreshold;
  __IO uint32_t HcRhDescriptorA;
  __IO uint32_t HcRhDescriptorB;
  __IO uint32_t HcRhStatus;
  __IO uint32_t HcRhPortStatus1;
  __IO uint32_t HcRhPortStatus2;
       uint32_t RESERVED0[40];
  __I  uint32_t Module_ID;

  __I  uint32_t OTGIntSt;               /* USB On-The-Go Registers            */
  __IO uint32_t OTGIntEn;
  __O  uint32_t OTGIntSet;
  __O  uint32_t OTGIntClr;
  __IO uint32_t OTGStCtrl;
  __IO uint32_t OTGTmr;
       uint32_t RESERVED1[58];

  __I  uint32_t USBDevIntSt;            /* USB Device Interrupt Registers     */
  __IO uint32_t USBDevIntEn;
  __O  uint32_t USBDevIntClr;
  __O  uint32_t USBDevIntSet;

  __O  uint32_t USBCmdCode;             /* USB Device SIE Command Registers   */
  __I  uint32_t USBCmdData;

  __I  uint32_t USBRxData;              /* USB Device Transfer Registers      */
  __O  uint32_t USBTxData;
  __I  uint32_t USBRxPLen;
  __O  uint32_t USBTxPLen;
  __IO uint32_t USBCtrl;
  __O  uint32_t USBDevIntPri;

  __I  uint32_t USBEpIntSt;             /* USB Device Endpoint Interrupt Regs */
  __IO uint32_t USBEpIntEn;
  __O  uint32_t USBEpIntClr;
  __O  uint32_t USBEpIntSet;
  __O  uint32_t USBEpIntPri;

  __IO uint32_t USBReEp;                /* USB Device Endpoint Realization Reg*/
  __O  uint32_t USBEpInd;
  __IO uint32_t USBMaxPSize;

  __I  uint32_t USBDMARSt;              /* USB Device DMA Registers           */
  __O  uint32_t USBDMARClr;
  __O  uint32_t USBDMARSet;
       uint32_t RESERVED2[9];
  __IO uint32_t USBUDCAH;
  __I  uint32_t USBEpDMASt;
  __O  uint32_t USBEpDMAEn;
  __O  uint32_t USBEpDMADis;
  __I  uint32_t USBDMAIntSt;
  __IO uint32_t USBDMAIntEn;
       uint32_t RESERVED3[2];
  __I  uint32_t USBEoTIntSt;
  __O  uint32_t USBEoTIntClr;
  __O  uint32_t USBEoTIntSet;
  __I  uint32_t USBNDDRIntSt;
  __O  uint32_t USBNDDRIntClr;
  __O  uint32_t USBNDDRIntSet;
  __I  uint32_t USBSysErrIntSt;
  __O  uint32_t USBSysErrIntClr;
  __O  uint32_t USBSysErrIntSet;
       uint32_t RESERVED4[15];

  __I  uint32_t I2C_RX;                 /* USB OTG I2C Registers              */
  __O  uint32_t I2C_WO;
  __I  uint32_t I2C_STS;
  __IO uint32_t I2C_CTL;
  __IO uint32_t I2C_CLKHI;
  __O  uint32_t I2C_CLKLO;
       uint32_t RESERVED5[823];

  union {
  __IO uint32_t USBClkCtrl;             /* USB Clock Control Registers        */
  __IO uint32_t OTGClkCtrl;
  };
  union {
  __I  uint32_t USBClkSt;
  __I  uint32_t OTGClkSt;
  };
} LPC_USB_TypeDef;

/*------------- Ethernet Media Access Controller (EMAC) ----------------------*/
typedef struct
{
  __IO uint32_t MAC1;                   /* MAC Registers                      */
  __IO uint32_t MAC2;
  __IO uint32_t IPGT;
  __IO uint32_t IPGR;
  __IO uint32_t CLRT;
  __IO uint32_t MAXF;
  __IO uint32_t SUPP;
  __IO uint32_t TEST;
  __IO uint32_t MCFG;
  __IO uint32_t MCMD;
  __IO uint32_t MADR;
  __O  uint32_t MWTD;
  __I  uint32_t MRDD;
  __I  uint32_t MIND;
       uint32_t RESERVED0[2];
  __IO uint32_t SA0;
  __IO uint32_t SA1;
  __IO uint32_t SA2;
       uint32_t RESERVED1[45];
  __IO uint32_t Command;                /* Control Registers                  */
  __I  uint32_t Status;
  __IO uint32_t RxDescriptor;
  __IO uint32_t RxStatus;
  __IO uint32_t RxDescriptorNumber;
  __I  uint32_t RxProduceIndex;
  __IO uint32_t RxConsumeIndex;
  __IO uint32_t TxDescriptor;
  __IO uint32_t TxStatus;
  __IO uint32_t TxDescriptorNumber;
  __IO uint32_t TxProduceIndex;
  __I  uint32_t TxConsumeIndex;
       uint32_t RESERVED2[10];
  __I  uint32_t TSV0;
  __I  uint32_t TSV1;
  __I  uint32_t RSV;
       uint32_t RESERVED3[3];
  __IO uint32_t FlowControlCounter;
  __I  uint32_t FlowControlStatus;
       uint32_t RESERVED4[34];
  __IO uint32_t RxFilterCtrl;           /* Rx Filter Registers                */
  __IO uint32_t RxFilterWoLStatus;
  __IO uint32_t RxFilterWoLClear;
       uint32_t RESERVED5;
  __IO uint32_t HashFilterL;
  __IO uint32_t HashFilterH;
       uint32_t RESERVED6[882];
  __I  uint32_t IntStatus;              /* Module Control Registers           */
  __IO uint32_t IntEnable;
  __O  uint32_t IntClear;
  __O  uint32_t IntSet;
       uint32_t RESERVED7;
  __IO uint32_t PowerDown;
       uint32_t RESERVED8;
  __IO uint32_t Module_ID;
} LPC_EMAC_TypeDef;

#if defined ( __CC_ARM   )
  #pragma no_anon_unions
#endif

/******************************************************************************/
/*                         Peripheral memory map                              */
/******************************************************************************/
/* Base addresses                                                             */

/* AHB Peripheral # 0 */

/*
#define FLASH_BASE            (0x00000000UL)
#define RAM_BASE              (0x10000000UL)
#define GPIO_BASE             (0x2009C000UL)
#define APB0_BASE             (0x40000000UL)
#define APB1_BASE             (0x40080000UL)
#define AHB_BASE              (0x50000000UL)
#define CM3_BASE              (0xE0000000UL)
*/

// TODO - #define VIC_BASE_ADDR	0xFFFFF000

#define LPC_WDT_BASE              (0xE0000000)
#define LPC_TIM0_BASE             (0xE0004000)
#define LPC_TIM1_BASE             (0xE0008000)
#define LPC_UART0_BASE            (0xE000C000)
#define LPC_UART1_BASE            (0xE0010000)
#define LPC_PWM1_BASE             (0xE0018000)
#define LPC_I2C0_BASE             (0xE001C000)
#define LPC_SPI_BASE              (0xE0020000)
#define LPC_RTC_BASE              (0xE0024000)
#define LPC_GPIOINT_BASE          (0xE0028080)
#define LPC_PINCON_BASE           (0xE002C000)
#define LPC_SSP1_BASE             (0xE0030000)
#define LPC_ADC_BASE              (0xE0034000)
#define LPC_CANAF_RAM_BASE        (0xE0038000)
#define LPC_CANAF_BASE            (0xE003C000)
#define LPC_CANCR_BASE            (0xE0040000)
#define LPC_CAN1_BASE             (0xE0044000)
#define LPC_CAN2_BASE             (0xE0048000)
#define LPC_I2C1_BASE             (0xE005C000)
#define LPC_SSP0_BASE             (0xE0068000)
#define LPC_DAC_BASE              (0xE006C000)
#define LPC_TIM2_BASE             (0xE0070000)
#define LPC_TIM3_BASE             (0xE0074000)
#define LPC_UART2_BASE            (0xE0078000)
#define LPC_UART3_BASE            (0xE007C000)
#define LPC_I2C2_BASE             (0xE0080000)
#define LPC_I2S_BASE              (0xE0088000)
#define LPC_MCI_BASE              (0xE008C000)
#define LPC_SC_BASE               (0xE01FC000)
#define LPC_EMAC_BASE             (0xFFE00000)
#define LPC_GPDMA_BASE            (0xFFE04000)
#define LPC_GPDMACH0_BASE         (0xFFE04100)
#define LPC_GPDMACH1_BASE         (0xFFE04120)
#define LPC_USB_BASE              (0xFFE0C000)
#define LPC_VIC_BASE              (0xFFFFF000)

/* GPIOs                                                                      */
#define LPC_GPIO0_BASE            (0x3FFFC000)
#define LPC_GPIO1_BASE            (0x3FFFC020)
#define LPC_GPIO2_BASE            (0x3FFFC040)
#define LPC_GPIO3_BASE            (0x3FFFC060)
#define LPC_GPIO4_BASE            (0x3FFFC080)


/******************************************************************************/
/*                         Peripheral declaration                             */
/******************************************************************************/
#define LPC_SC                    ((       LPC_SC_TypeDef *)        LPC_SC_BASE)
#define LPC_GPIO0                 ((     LPC_GPIO_TypeDef *)     LPC_GPIO0_BASE)
#define LPC_GPIO1                 ((     LPC_GPIO_TypeDef *)     LPC_GPIO1_BASE)
#define LPC_GPIO2                 ((     LPC_GPIO_TypeDef *)     LPC_GPIO2_BASE)
#define LPC_GPIO3                 ((     LPC_GPIO_TypeDef *)     LPC_GPIO3_BASE)
#define LPC_GPIO4                 ((     LPC_GPIO_TypeDef *)     LPC_GPIO4_BASE)
#define LPC_WDT                   ((      LPC_WDT_TypeDef *)       LPC_WDT_BASE)
#define LPC_TIM0                  ((      LPC_TIM_TypeDef *)      LPC_TIM0_BASE)
#define LPC_TIM1                  ((      LPC_TIM_TypeDef *)      LPC_TIM1_BASE)
#define LPC_TIM2                  ((      LPC_TIM_TypeDef *)      LPC_TIM2_BASE)
#define LPC_TIM3                  ((      LPC_TIM_TypeDef *)      LPC_TIM3_BASE)
#define LPC_UART0                 ((     LPC_UART_TypeDef *)     LPC_UART0_BASE)
#define LPC_UART1                 ((    LPC_UART1_TypeDef *)     LPC_UART1_BASE)
#define LPC_UART2                 ((     LPC_UART_TypeDef *)     LPC_UART2_BASE)
#define LPC_UART3                 ((     LPC_UART_TypeDef *)     LPC_UART3_BASE)
#define LPC_PWM1                  ((      LPC_PWM_TypeDef *)      LPC_PWM1_BASE)
#define LPC_I2C0                  ((      LPC_I2C_TypeDef *)      LPC_I2C0_BASE)
#define LPC_I2C1                  ((      LPC_I2C_TypeDef *)      LPC_I2C1_BASE)
#define LPC_I2C2                  ((      LPC_I2C_TypeDef *)      LPC_I2C2_BASE)
#define LPC_I2S                   ((      LPC_I2S_TypeDef *)       LPC_I2S_BASE)
#define LPC_SPI                   ((      LPC_SPI_TypeDef *)       LPC_SPI_BASE)
#define LPC_RTC                   ((      LPC_RTC_TypeDef *)       LPC_RTC_BASE)
#define LPC_GPIOINT               ((  LPC_GPIOINT_TypeDef *)   LPC_GPIOINT_BASE)
#define LPC_PINCON                ((   LPC_PINCON_TypeDef *)    LPC_PINCON_BASE)
#define LPC_SSP0                  ((      LPC_SSP_TypeDef *)      LPC_SSP0_BASE)
#define LPC_SSP1                  ((      LPC_SSP_TypeDef *)      LPC_SSP1_BASE)
#define LPC_ADC                   ((      LPC_ADC_TypeDef *)       LPC_ADC_BASE)
#define LPC_DAC                   ((      LPC_DAC_TypeDef *)       LPC_DAC_BASE)
#define LPC_CANAF_RAM             ((LPC_CANAF_RAM_TypeDef *) LPC_CANAF_RAM_BASE)
#define LPC_CANAF                 ((    LPC_CANAF_TypeDef *)     LPC_CANAF_BASE)
#define LPC_CANCR                 ((    LPC_CANCR_TypeDef *)     LPC_CANCR_BASE)
#define LPC_CAN1                  ((      LPC_CAN_TypeDef *)      LPC_CAN1_BASE)
#define LPC_CAN2                  ((      LPC_CAN_TypeDef *)      LPC_CAN2_BASE)
#define LPC_MCI                   ((      LPC_MCI_TypeDef *)       LPC_MCI_BASE)
#define LPC_EMAC                  ((     LPC_EMAC_TypeDef *)      LPC_EMAC_BASE)
#define LPC_GPDMA                 ((    LPC_GPDMA_TypeDef *)     LPC_GPDMA_BASE)
#define LPC_GPDMACH0              ((  LPC_GPDMACH_TypeDef *)  LPC_GPDMACH0_BASE)
#define LPC_GPDMACH1              ((  LPC_GPDMACH_TypeDef *)  LPC_GPDMACH1_BASE)
#define LPC_USB                   ((      LPC_USB_TypeDef *)       LPC_USB_BASE)
#define LPC_VIC                   ((      LPC_VIC_TypeDef *)       LPC_VIC_BASE)

#ifdef __cplusplus
 }
#endif 

#endif  // __LPC23xx_H

