/*
 * LPC43xx/LPC18xx MCU header
 *
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 *
 * Simplified version of NXP LPCOPEN LPC43XX/LPC18XX headers
 * 05/15/13  Micromint USA <support@micromint.com>
 */

#ifndef __LPC43XX_H
#define __LPC43XX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Treat __CORE_Mx as CORE_Mx */
#if defined(__CORTEX_M0) && !defined(CORE_M0)
  #define CORE_M0
#endif
#if defined(__CORTEX_M3) && !defined(CORE_M3)
  #define CORE_M3
#endif
/* Default to M4 core if no core explicitly declared */
#if !defined(CORE_M0) && !defined(CORE_M3)
  #define CORE_M4
#endif

/* Define LPC18XX or LPC43XX according to core type */
#if (defined(CORE_M4) || defined(CORE_M0)) && !defined(__LPC43XX__)
  #define __LPC43XX__
#endif
#if defined(CORE_M3) && !defined(__LPC18XX__)
  #define __LPC18XX__
#endif

/* Start of section using anonymous unions */
#if defined(__ARMCC_VERSION)
// Kill warning "#pragma push with no matching #pragma pop"
  #pragma diag_suppress 2525
  #pragma push
  #pragma anon_unions
#elif defined(__CWCC__)
  #pragma push
  #pragma cpp_extensions on
#elif defined(__IAR_SYSTEMS_ICC__)
  //#pragma push // FIXME not usable for IAR
  #pragma language=extended
#else /* defined(__GNUC__) and others */
  /* Assume anonymous unions are enabled by default */
#endif

#if defined(CORE_M4)
/* ---------------------------------------------------------------------------
 * LPC43xx (M4 Core) Cortex CMSIS definitions
 */

#define __CM4_REV              0x0000   /* Cortex-M4 Core Revision               */
#define __MPU_PRESENT             1     /* MPU present or not                    */
#define __NVIC_PRIO_BITS          3     /* Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig    0     /* Set to 1 if different SysTick Config is used */
#define __FPU_PRESENT             1     /* FPU present or not                    */
#define CHIP_LPC43XX                    /* LPCOPEN compatibility                 */

/* ---------------------------------------------------------------------------
 * LPC43xx peripheral interrupt numbers
 */

typedef enum {
    /* ---------------  Cortex-M4 Processor Exceptions Numbers  ------------------- */
    Reset_IRQn                    = -15,/*   1  Reset Vector, invoked on Power up and warm reset */
    NonMaskableInt_IRQn           = -14,/*   2  Non maskable Interrupt, cannot be stopped or preempted */
    HardFault_IRQn                = -13,/*   3  Hard Fault, all classes of Fault */
    MemoryManagement_IRQn         = -12,/*   4  Memory Management, MPU mismatch, including Access Violation and No Match */
    BusFault_IRQn                 = -11,/*   5  Bus Fault, Pre-Fetch-, Memory Access Fault, other address/memory related Fault */
    UsageFault_IRQn               = -10,/*   6  Usage Fault, i.e. Undef Instruction, Illegal State Transition */
    SVCall_IRQn                   =  -5,/*  11  System Service Call via SVC instruction */
    DebugMonitor_IRQn             =  -4,/*  12  Debug Monitor                    */
    PendSV_IRQn                   =  -2,/*  14  Pendable request for system service */
    SysTick_IRQn                  =  -1,/*  15  System Tick Timer                */

    /* -----------------  LPC18xx/43xx Specific Interrupt Numbers  --------------------- */
    DAC_IRQn                      =   0,/*   0  DAC                              */
    M0CORE_IRQn                   =   1,/*   1  M0a                              */
    DMA_IRQn                      =   2,/*   2  DMA                              */
    RESERVED1_IRQn                =   3,/*   3  EZH/EDM                          */
    RESERVED2_IRQn                =   4,
    ETHERNET_IRQn                 =   5,/*   5  ETHERNET                         */
    SDIO_IRQn                     =   6,/*   6  SDIO                             */
    LCD_IRQn                      =   7,/*   7  LCD                              */
    USB0_IRQn                     =   8,/*   8  USB0                             */
    USB1_IRQn                     =   9,/*   9  USB1                             */
    SCT_IRQn                      =  10,/*  10  SCT                              */
    RITIMER_IRQn                  =  11,/*  11  RITIMER                          */
    TIMER0_IRQn                   =  12,/*  12  TIMER0                           */
    TIMER1_IRQn                   =  13,/*  13  TIMER1                           */
    TIMER2_IRQn                   =  14,/*  14  TIMER2                           */
    TIMER3_IRQn                   =  15,/*  15  TIMER3                           */
    MCPWM_IRQn                    =  16,/*  16  MCPWM                            */
    ADC0_IRQn                     =  17,/*  17  ADC0                             */
    I2C0_IRQn                     =  18,/*  18  I2C0                             */
    I2C1_IRQn                     =  19,/*  19  I2C1                             */
    SPI_INT_IRQn                  =  20,/*  20  SPI_INT                          */
    ADC1_IRQn                     =  21,/*  21  ADC1                             */
    SSP0_IRQn                     =  22,/*  22  SSP0                             */
    SSP1_IRQn                     =  23,/*  23  SSP1                             */
    USART0_IRQn                   =  24,/*  24  USART0                           */
    UART1_IRQn                    =  25,/*  25  UART1                            */
    USART2_IRQn                   =  26,/*  26  USART2                           */
    USART3_IRQn                   =  27,/*  27  USART3                           */
    I2S0_IRQn                     =  28,/*  28  I2S0                             */
    I2S1_IRQn                     =  29,/*  29  I2S1                             */
    RESERVED4_IRQn                =  30,
    SGPIO_INT_IRQn                =  31,/*  31  SGPIO_IINT                       */
    PIN_INT0_IRQn                 =  32,/*  32  PIN_INT0                         */
    PIN_INT1_IRQn                 =  33,/*  33  PIN_INT1                         */
    PIN_INT2_IRQn                 =  34,/*  34  PIN_INT2                         */
    PIN_INT3_IRQn                 =  35,/*  35  PIN_INT3                         */
    PIN_INT4_IRQn                 =  36,/*  36  PIN_INT4                         */
    PIN_INT5_IRQn                 =  37,/*  37  PIN_INT5                         */
    PIN_INT6_IRQn                 =  38,/*  38  PIN_INT6                         */
    PIN_INT7_IRQn                 =  39,/*  39  PIN_INT7                         */
    GINT0_IRQn                    =  40,/*  40  GINT0                            */
    GINT1_IRQn                    =  41,/*  41  GINT1                            */
    EVENTROUTER_IRQn              =  42,/*  42  EVENTROUTER                      */
    C_CAN1_IRQn                   =  43,/*  43  C_CAN1                           */
    RESERVED6_IRQn                =  44,
    RESERVED7_IRQn                =  45,/*  45  VADC                             */
    ATIMER_IRQn                   =  46,/*  46  ATIMER                           */
    RTC_IRQn                      =  47,/*  47  RTC                              */
    RESERVED8_IRQn                =  48,
    WWDT_IRQn                     =  49,/*  49  WWDT                             */
    RESERVED9_IRQn                =  50,
    C_CAN0_IRQn                   =  51,/*  51  C_CAN0                           */
    QEI_IRQn                      =  52,/*  52  QEI                              */
} IRQn_Type;

#include "core_cm4.h"                        /* Cortex-M4 processor and core peripherals */

#elif defined(CORE_M3)
/* ---------------------------------------------------------------------------
 * LPC18xx (M3 Core) Cortex CMSIS definitions
 */
#define __MPU_PRESENT             1     /* MPU present or not                    */
#define __NVIC_PRIO_BITS          3     /* Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig    0     /* Set to 1 if different SysTick Config is used */
#define __FPU_PRESENT             0     /* FPU present or not                    */
#define CHIP_LPC18XX                    /* LPCOPEN compatibility                 */

/* ---------------------------------------------------------------------------
 * LPC18xx peripheral interrupt numbers
 */

typedef enum {
    /* ---------------  Cortex-M3 Processor Exceptions Numbers  ------------------- */
    Reset_IRQn                    = -15,/*   1  Reset Vector, invoked on Power up and warm reset */
    NonMaskableInt_IRQn           = -14,/*   2  Non maskable Interrupt, cannot be stopped or preempted */
    HardFault_IRQn                = -13,/*   3  Hard Fault, all classes of Fault */
    MemoryManagement_IRQn         = -12,/*   4  Memory Management, MPU mismatch, including Access Violation and No Match */
    BusFault_IRQn                 = -11,/*   5  Bus Fault, Pre-Fetch-, Memory Access Fault, other address/memory related Fault */
    UsageFault_IRQn               = -10,/*   6  Usage Fault, i.e. Undef Instruction, Illegal State Transition */
    SVCall_IRQn                   =  -5,/*  11  System Service Call via SVC instruction */
    DebugMonitor_IRQn             =  -4,/*  12  Debug Monitor                    */
    PendSV_IRQn                   =  -2,/*  14  Pendable request for system service */
    SysTick_IRQn                  =  -1,/*  15  System Tick Timer                */

    /* -----------------  LPC18xx/43xx Specific Interrupt Numbers  --------------------- */
    DAC_IRQn                      =   0,/*   0  DAC                              */
    RESERVED0_IRQn                =   1,
    DMA_IRQn                      =   2,/*   2  DMA                              */
    RESERVED1_IRQn                =   3,/*   3  EZH/EDM                          */
    RESERVED2_IRQn                =   4,
    ETHERNET_IRQn                 =   5,/*   5  ETHERNET                         */
    SDIO_IRQn                     =   6,/*   6  SDIO                             */
    LCD_IRQn                      =   7,/*   7  LCD                              */
    USB0_IRQn                     =   8,/*   8  USB0                             */
    USB1_IRQn                     =   9,/*   9  USB1                             */
    SCT_IRQn                      =  10,/*  10  SCT                              */
    RITIMER_IRQn                  =  11,/*  11  RITIMER                          */
    TIMER0_IRQn                   =  12,/*  12  TIMER0                           */
    TIMER1_IRQn                   =  13,/*  13  TIMER1                           */
    TIMER2_IRQn                   =  14,/*  14  TIMER2                           */
    TIMER3_IRQn                   =  15,/*  15  TIMER3                           */
    MCPWM_IRQn                    =  16,/*  16  MCPWM                            */
    ADC0_IRQn                     =  17,/*  17  ADC0                             */
    I2C0_IRQn                     =  18,/*  18  I2C0                             */
    I2C1_IRQn                     =  19,/*  19  I2C1                             */
    RESERVED3_IRQn                =  20,
    ADC1_IRQn                     =  21,/*  21  ADC1                             */
    SSP0_IRQn                     =  22,/*  22  SSP0                             */
    SSP1_IRQn                     =  23,/*  23  SSP1                             */
    USART0_IRQn                   =  24,/*  24  USART0                           */
    UART1_IRQn                    =  25,/*  25  UART1                            */
    USART2_IRQn                   =  26,/*  26  USART2                           */
    USART3_IRQn                   =  27,/*  27  USART3                           */
    I2S0_IRQn                     =  28,/*  28  I2S0                             */
    I2S1_IRQn                     =  29,/*  29  I2S1                             */
    RESERVED4_IRQn                =  30,
    RESERVED5_IRQn                =  31,
    PIN_INT0_IRQn                 =  32,/*  32  PIN_INT0                         */
    PIN_INT1_IRQn                 =  33,/*  33  PIN_INT1                         */
    PIN_INT2_IRQn                 =  34,/*  34  PIN_INT2                         */
    PIN_INT3_IRQn                 =  35,/*  35  PIN_INT3                         */
    PIN_INT4_IRQn                 =  36,/*  36  PIN_INT4                         */
    PIN_INT5_IRQn                 =  37,/*  37  PIN_INT5                         */
    PIN_INT6_IRQn                 =  38,/*  38  PIN_INT6                         */
    PIN_INT7_IRQn                 =  39,/*  39  PIN_INT7                         */
    GINT0_IRQn                    =  40,/*  40  GINT0                            */
    GINT1_IRQn                    =  41,/*  41  GINT1                            */
    EVENTROUTER_IRQn              =  42,/*  42  EVENTROUTER                      */
    C_CAN1_IRQn                   =  43,/*  43  C_CAN1                           */
    RESERVED6_IRQn                =  44,
    RESERVED7_IRQn                =  45,/*  45  VADC                             */
    ATIMER_IRQn                   =  46,/*  46  ATIMER                           */
    RTC_IRQn                      =  47,/*  47  RTC                              */
    RESERVED8_IRQn                =  48,
    WWDT_IRQn                     =  49,/*  49  WWDT                             */
    RESERVED9_IRQn                =  50,
    C_CAN0_IRQn                   =  51,/*  51  C_CAN0                           */
    QEI_IRQn                      =  52,/*  52  QEI                              */
} IRQn_Type;

#include "core_cm3.h"                        /* Cortex-M3 processor and core peripherals */

#elif defined(CORE_M0)
/* ---------------------------------------------------------------------------
 * LPC43xx (M0 Core) Cortex CMSIS definitions
 */

#define __MPU_PRESENT             0     /* MPU present or not                    */
#define __NVIC_PRIO_BITS          2     /* Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig    0     /* Set to 1 if different SysTick Config is used */
#define __FPU_PRESENT             0     /* FPU present or not                    */
#define CHIP_LPC43XX                    /* LPCOPEN compatibility                 */

/* ---------------------------------------------------------------------------
 * LPC43xx (M0 Core) peripheral interrupt numbers
 */

typedef enum {
    /* ---------------  Cortex-M0 Processor Exceptions Numbers  ------------------- */
    Reset_IRQn                    = -15,/*   1  Reset Vector, invoked on Power up and warm reset */
    NonMaskableInt_IRQn           = -14,/*   2  Non maskable Interrupt, cannot be stopped or preempted */
    HardFault_IRQn                = -13,/*   3  Hard Fault, all classes of Fault */
    SVCall_IRQn                   =  -5,/*  11  System Service Call via SVC instruction */
    DebugMonitor_IRQn             =  -4,/*  12  Debug Monitor                    */
    PendSV_IRQn                   =  -2,/*  14  Pendable request for system service */
    SysTick_IRQn                  =  -1,/*  15  System Tick Timer           */

    /* -----------------  LPC18xx/43xx Specific Interrupt Numbers  --------------------- */
    DAC_IRQn                      =   0,/*   0  DAC                              */
    M0_M4CORE_IRQn                =   1,/*   1  M0a                              */
    DMA_IRQn                      =   2,/*   2  DMA  r                            */
    RESERVED1_IRQn                =   3,/*   3  EZH/EDM                          */
    FLASHEEPROM_IRQn              =   4,/*   4  ORed Flash EEPROM Bank A, B, EEPROM   */
    ETHERNET_IRQn                 =   5,/*   5  ETHERNET                         */
    SDIO_IRQn                     =   6,/*   6  SDIO                             */
    LCD_IRQn                      =   7,/*   7  LCD                              */
    USB0_IRQn                     =   8,/*   8  USB0                             */
    USB1_IRQn                     =   9,/*   9  USB1                             */
    SCT_IRQn                      =  10,/*  10  SCT                              */
    RITIMER_IRQn                  =  11,/*  11  ORed RITIMER, WDT                */
    TIMER0_IRQn                   =  12,/*  12  TIMER0                           */
    GINT1_IRQn                    =  13,/*  13  GINT1                            */
    PIN_INT4_IRQn                 =  14,/*  14  GPIO 4                           */
    TIMER3_IRQn                   =  15,/*  15  TIMER3                           */
    MCPWM_IRQn                    =  16,/*  16  MCPWM                            */
    ADC0_IRQn                     =  17,/*  17  ADC0                             */
    I2C0_IRQn                     =  18,/*  18  ORed I2C0, I2C1                  */
    SGPIO_INT_IRQn                =  19,/*  19  SGPIO                            */
    SPI_INT_IRQn                  =  20,/*  20  SPI_INT                          */
    ADC1_IRQn                     =  21,/*  21  ADC1                             */
    SSP0_IRQn                     =  22,/*  22  ORed SSP0, SSP1                  */
    EVENTROUTER_IRQn              =  23,/*  23  EVENTROUTER                      */
    USART0_IRQn                   =  24,/*  24  USART0                           */
    UART1_IRQn                    =  25,/*  25  UART1                            */
    USART2_IRQn                   =  26,/*  26  USART2                           */
    USART3_IRQn                   =  27,/*  27  USART3                           */
    I2S0_IRQn                     =  28,/*  28  ORed I2S0, I2S1                  */
    C_CAN0_IRQn                   =  29,/*  29  C_CAN0                           */
    I2S1_IRQn                     =  29,/*  29  I2S1                             */
    RESERVED2_IRQn                =  30,
    RESERVED3_IRQn                =  31,
} IRQn_Type;

#include "core_cm0.h"                        /* Cortex-M4 processor and core peripherals */
#else
#error Please #define CORE_M0, CORE_M3 or CORE_M4
#endif

#include "system_LPC43xx.h"

/* ---------------------------------------------------------------------------
 * State Configurable Timer register block structure
 */
#define LPC_SCT_BASE              0x40000000
#define CONFIG_SCT_nEV   (16)           /* Number of events */
#define CONFIG_SCT_nRG   (16)           /* Number of match/compare registers */
#define CONFIG_SCT_nOU   (16)           /* Number of outputs */

typedef struct {
    __IO  uint32_t CONFIG;              /* Configuration Register */
    union {
        __IO uint32_t CTRL_U;           /* Control Register */
        struct {
            __IO uint16_t CTRL_L;       /* Low control register */
            __IO uint16_t CTRL_H;       /* High control register */
        };

    };

    __IO uint16_t LIMIT_L;              /* limit register for counter L */
    __IO uint16_t LIMIT_H;              /* limit register for counter H */
    __IO uint16_t HALT_L;               /* halt register for counter L */
    __IO uint16_t HALT_H;               /* halt register for counter H */
    __IO uint16_t STOP_L;               /* stop register for counter L */
    __IO uint16_t STOP_H;               /* stop register for counter H */
    __IO uint16_t START_L;              /* start register for counter L */
    __IO uint16_t START_H;              /* start register for counter H */
    uint32_t RESERVED1[10];             /* 0x03C reserved */
    union {
        __IO uint32_t COUNT_U;          /* counter register */
        struct {
            __IO uint16_t COUNT_L;      /* counter register for counter L */
            __IO uint16_t COUNT_H;      /* counter register for counter H */
        };

    };

    __IO uint16_t STATE_L;              /* state register for counter L */
    __IO uint16_t STATE_H;              /* state register for counter H */
    __I  uint32_t INPUT;                /* input register */
    __IO uint16_t REGMODE_L;            /* match - capture registers mode register L */
    __IO uint16_t REGMODE_H;            /* match - capture registers mode register H */
    __IO uint32_t OUTPUT;               /* output register */
    __IO uint32_t OUTPUTDIRCTRL;        /* output counter direction Control Register */
    __IO uint32_t RES;                  /* conflict resolution register */
    __IO uint32_t DMA0REQUEST;          /* DMA0 Request Register */
    __IO uint32_t DMA1REQUEST;          /* DMA1 Request Register */
    uint32_t RESERVED2[35];
    __IO uint32_t EVEN;                 /* event enable register */
    __IO uint32_t EVFLAG;               /* event flag register */
    __IO uint32_t CONEN;                /* conflict enable register */
    __IO uint32_t CONFLAG;              /* conflict flag register */
    union {
        __IO union {                    /* ... Match / Capture value */
            uint32_t U;                 /*       SCTMATCH[i].U  Unified 32-bit register */
            struct {
                uint16_t L;             /*       SCTMATCH[i].L  Access to L value */
                uint16_t H;             /*       SCTMATCH[i].H  Access to H value */
            };

        } MATCH[CONFIG_SCT_nRG];

        __I union {
            uint32_t U;                 /*       SCTCAP[i].U  Unified 32-bit register */
            struct {
                uint16_t L;             /*       SCTCAP[i].L  Access to L value */
                uint16_t H;             /*       SCTCAP[i].H  Access to H value */
            };

        } CAP[CONFIG_SCT_nRG];

    };

    uint32_t RESERVED3[32 - CONFIG_SCT_nRG];    /* ...-0x17C reserved */
    union {
        __IO uint16_t MATCH_L[CONFIG_SCT_nRG];  /* 0x180-... Match Value L counter */
        __I  uint16_t CAP_L[CONFIG_SCT_nRG];    /* 0x180-... Capture Value L counter */
    };

    uint16_t RESERVED4[32 - CONFIG_SCT_nRG];    /* ...-0x1BE reserved */
    union {
        __IO uint16_t MATCH_H[CONFIG_SCT_nRG];  /* 0x1C0-... Match Value H counter */
        __I  uint16_t CAP_H[CONFIG_SCT_nRG];    /* 0x1C0-... Capture Value H counter */
    };

    uint16_t RESERVED5[32 - CONFIG_SCT_nRG];    /* ...-0x1FE reserved */
    union {
        __IO union {                    /* 0x200-... Match Reload / Capture Control value */
            uint32_t U;                 /*       SCTMATCHREL[i].U  Unified 32-bit register */
            struct {
                uint16_t L;             /*       SCTMATCHREL[i].L  Access to L value */
                uint16_t H;             /*       SCTMATCHREL[i].H  Access to H value */
            };

        } MATCHREL[CONFIG_SCT_nRG];

        __IO union {
            uint32_t U;                 /*       SCTCAPCTRL[i].U  Unified 32-bit register */
            struct {
                uint16_t L;             /*       SCTCAPCTRL[i].L  Access to L value */
                uint16_t H;             /*       SCTCAPCTRL[i].H  Access to H value */
            };

        } CAPCTRL[CONFIG_SCT_nRG];

    };

    uint32_t RESERVED6[32 - CONFIG_SCT_nRG];    /* ...-0x27C reserved */
    union {
        __IO uint16_t MATCHREL_L[CONFIG_SCT_nRG]; /* 0x280-... Match Reload value L counter */
        __IO uint16_t CAPCTRL_L[CONFIG_SCT_nRG];  /* 0x280-... Capture Control value L counter */
    };

    uint16_t RESERVED7[32 - CONFIG_SCT_nRG];    /* ...-0x2BE reserved */
    union {
        __IO uint16_t MATCHREL_H[CONFIG_SCT_nRG]; /* 0x2C0-... Match Reload value H counter */
        __IO uint16_t CAPCTRL_H[CONFIG_SCT_nRG];  /* 0x2C0-... Capture Control value H counter */
    };

    uint16_t RESERVED8[32 - CONFIG_SCT_nRG];    /* ...-0x2FE reserved */
    __IO struct {                       /* 0x300-0x3FC  SCTEVENT[i].STATE / SCTEVENT[i].CTRL*/
        uint32_t STATE;                 /* Event State Register */
        uint32_t CTRL;                  /* Event Control Register */
    } EVENT[CONFIG_SCT_nEV];

    uint32_t RESERVED9[128 - 2 * CONFIG_SCT_nEV]; /* ...-0x4FC reserved */
    __IO struct {                       /* 0x500-0x57C  SCTOUT[i].SET / SCTOUT[i].CLR */
        uint32_t SET;                   /* Output n Set Register */
        uint32_t CLR;                   /* Output n Clear Register */
    } OUT[CONFIG_SCT_nOU];

    uint32_t RESERVED10[191 - 2 * CONFIG_SCT_nOU];  /* ...-0x7F8 reserved */
    __I  uint32_t MODULECONTENT;        /* 0x7FC Module Content */
} LPC_SCT_T;

/* Macro defines for SCT configuration register */
#define SCT_CONFIG_16BIT_COUNTER        0x00000000    /* Operate as 2 16-bit counters */
#define SCT_CONFIG_32BIT_COUNTER        0x00000001    /* Operate as 1 32-bit counter */

#define SCT_CONFIG_CLKMODE_BUSCLK       (0x0 << 1)    /* Bus clock */
#define SCT_CONFIG_CLKMODE_SCTCLK       (0x1 << 1)    /* SCT clock */
#define SCT_CONFIG_CLKMODE_INCLK        (0x2 << 1)    /* Input clock selected in CLKSEL field */
#define SCT_CONFIG_CLKMODE_INEDGECLK    (0x3 << 1)    /* Input clock edge selected in CLKSEL field */

#define SCT_CONFIG_NORELOADL_U          (0x1 << 7)    /* Operate as 1 32-bit counter */
#define SCT_CONFIG_NORELOADH            (0x1 << 8)    /* Operate as 1 32-bit counter */

/* Macro defines for SCT control register */
#define COUNTUP_TO_LIMIT_THEN_CLEAR_TO_ZERO     0     /* Direction for low or unified counter */
#define COUNTUP_TO LIMIT_THEN_COUNTDOWN_TO_ZERO 1

#define SCT_CTRL_STOP_L                 (1 << 1)      /* Stop low counter */
#define SCT_CTRL_HALT_L                 (1 << 2)      /* Halt low counter */
#define SCT_CTRL_CLRCTR_L               (1 << 3)      /* Clear low or unified counter */
#define SCT_CTRL_BIDIR_L(x)             (((x) & 0x01) << 4) /* Bidirectional bit */
#define SCT_CTRL_PRE_L(x)               (((x) & 0xFF) << 5) /* Prescale clock for low or unified counter */

#define COUNTUP_TO_LIMIT_THEN_CLEAR_TO_ZERO     0     /* Direction for high counter */
#define COUNTUP_TO LIMIT_THEN_COUNTDOWN_TO_ZERO 1
#define SCT_CTRL_STOP_H                 (1 << 17)     /* Stop high counter */
#define SCT_CTRL_HALT_H                 (1 << 18)     /* Halt high counter */
#define SCT_CTRL_CLRCTR_H               (1 << 19)     /* Clear high counter */
#define SCT_CTRL_BIDIR_H(x)             (((x) & 0x01) << 20)
#define SCT_CTRL_PRE_H(x)               (((x) & 0xFF) << 21) /* Prescale clock for high counter */

/* Macro defines for SCT Conflict resolution register */
#define SCT_RES_NOCHANGE                (0)
#define SCT_RES_SET_OUTPUT              (1)
#define SCT_RES_CLEAR_OUTPUT            (2)
#define SCT_RES_TOGGLE_OUTPUT           (3)

/* ---------------------------------------------------------------------------
 * GPDMA Channel register block structure
 */
#define LPC_GPDMA_BASE            0x40002000

typedef struct {
    __IO uint32_t  SRCADDR;             /* DMA Channel Source Address Register */
    __IO uint32_t  DESTADDR;            /* DMA Channel Destination Address Register */
    __IO uint32_t  LLI;                 /* DMA Channel Linked List Item Register */
    __IO uint32_t  CONTROL;             /* DMA Channel Control Register */
    __IO uint32_t  CONFIG;              /* DMA Channel Configuration Register */
    __I  uint32_t  RESERVED1[3];
} LPC_GPDMA_CH_T;

#define GPDMA_CHANNELS 8

/* ---------------------------------------------------------------------------
 * GPDMA register block
 */
typedef struct {                        /* GPDMA Structure */
    __I  uint32_t  INTSTAT;             /* DMA Interrupt Status Register */
    __I  uint32_t  INTTCSTAT;           /* DMA Interrupt Terminal Count Request Status Register */
    __O  uint32_t  INTTCCLEAR;          /* DMA Interrupt Terminal Count Request Clear Register */
    __I  uint32_t  INTERRSTAT;          /* DMA Interrupt Error Status Register */
    __O  uint32_t  INTERRCLR;           /* DMA Interrupt Error Clear Register */
    __I  uint32_t  RAWINTTCSTAT;        /* DMA Raw Interrupt Terminal Count Status Register */
    __I  uint32_t  RAWINTERRSTAT;       /* DMA Raw Error Interrupt Status Register */
    __I  uint32_t  ENBLDCHNS;           /* DMA Enabled Channel Register */
    __IO uint32_t  SOFTBREQ;            /* DMA Software Burst Request Register */
    __IO uint32_t  SOFTSREQ;            /* DMA Software Single Request Register */
    __IO uint32_t  SOFTLBREQ;           /* DMA Software Last Burst Request Register */
    __IO uint32_t  SOFTLSREQ;           /* DMA Software Last Single Request Register */
    __IO uint32_t  CONFIG;              /* DMA Configuration Register */
    __IO uint32_t  SYNC;                /* DMA Synchronization Register */
    __I  uint32_t  RESERVED0[50];
    LPC_GPDMA_CH_T CH[GPDMA_CHANNELS];
} LPC_GPDMA_T;

/* ---------------------------------------------------------------------------
 * SPIFI register block structure
 */
#define LPC_SPIFI_BASE            0x40003000

typedef struct {           /* SPIFI Structure */
    __IO uint32_t CTRL;    /* Control register */
    __IO uint32_t CMD;     /* Command register */
    __IO uint32_t ADDR;    /* Address register */
    __IO uint32_t IDATA;   /* Intermediate data register */
    __IO uint32_t CLIMIT;  /* Cache limit register */
    union {
        __IO  uint32_t DATA;
        __IO  uint16_t DATA_HWORD;
        __IO  uint8_t  DATA_BYTE;
    };                     /* Data register */
    __IO uint32_t MCMD;    /* Memory command register */
    __IO uint32_t STAT;    /* Status register */
} LPC_SPIFI_T;

/* ---------------------------------------------------------------------------
 * SD/MMC & SDIO register block structure
 */
#define LPC_SDMMC_BASE            0x40004000

typedef struct {                /* SDMMC Structure        */
    __IO uint32_t  CTRL;        /* Control Register       */
    __IO uint32_t  PWREN;       /* Power Enable Register  */
    __IO uint32_t  CLKDIV;      /* Clock Divider Register */
    __IO uint32_t  CLKSRC;      /* SD Clock Source Register */
    __IO uint32_t  CLKENA;      /* Clock Enable Register  */
    __IO uint32_t  TMOUT;       /* Timeout Register       */
    __IO uint32_t  CTYPE;       /* Card Type Register     */
    __IO uint32_t  BLKSIZ;      /* Block Size Register    */
    __IO uint32_t  BYTCNT;      /* Byte Count Register    */
    __IO uint32_t  INTMASK;     /* Interrupt Mask Register */
    __IO uint32_t  CMDARG;      /* Command Argument Register */
    __IO uint32_t  CMD;         /* Command Register       */
    __I  uint32_t  RESP0;       /* Response Register 0    */
    __I  uint32_t  RESP1;       /* Response Register 1    */
    __I  uint32_t  RESP2;       /* Response Register 2    */
    __I  uint32_t  RESP3;       /* Response Register 3    */
    __I  uint32_t  MINTSTS;     /* Masked Interrupt Status Register */
    __IO uint32_t  RINTSTS;     /* Raw Interrupt Status Register */
    __I  uint32_t  STATUS;      /* Status Register        */
    __IO uint32_t  FIFOTH;      /* FIFO Threshold Watermark Register */
    __I  uint32_t  CDETECT;     /* Card Detect Register   */
    __I  uint32_t  WRTPRT;      /* Write Protect Register */
    __IO uint32_t  GPIO;        /* General Purpose Input/Output Register */
    __I  uint32_t  TCBCNT;      /* Transferred CIU Card Byte Count Register */
    __I  uint32_t  TBBCNT;      /* Transferred Host to BIU-FIFO Byte Count Register */
    __IO uint32_t  DEBNCE;      /* Debounce Count Register */
    __IO uint32_t  USRID;       /* User ID Register       */
    __I  uint32_t  VERID;       /* Version ID Register    */
    __I  uint32_t  RESERVED0;
    __IO uint32_t  UHS_REG;     /* UHS-1 Register         */
    __IO uint32_t  RST_N;       /* Hardware Reset         */
    __I  uint32_t  RESERVED1;
    __IO uint32_t  BMOD;        /* Bus Mode Register      */
    __O  uint32_t  PLDMND;      /* Poll Demand Register   */
    __IO uint32_t  DBADDR;      /* Descriptor List Base Address Register */
    __IO uint32_t  IDSTS;       /* Internal DMAC Status Register */
    __IO uint32_t  IDINTEN;     /* Internal DMAC Interrupt Enable Register */
    __I  uint32_t  DSCADDR;     /* Current Host Descriptor Address Register */
    __I  uint32_t  BUFADDR;     /* Current Buffer Descriptor Address Register */
} LPC_SDMMC_T;

/* ---------------------------------------------------------------------------
 * External Memory Controller (EMC) register block structure
 */
#define LPC_EMC_BASE              0x40005000

typedef struct {                        /* EMC Structure          */
    __IO uint32_t  CONTROL;             /* Controls operation of the memory controller. */
    __I  uint32_t  STATUS;              /* Provides EMC status information. */
    __IO uint32_t  CONFIG;              /* Configures operation of the memory controller. */
    __I  uint32_t  RESERVED0[5];
    __IO uint32_t  DYNAMICCONTROL;      /* Controls dynamic memory operation. */
    __IO uint32_t  DYNAMICREFRESH;      /* Configures dynamic memory refresh operation. */
    __IO uint32_t  DYNAMICREADCONFIG;   /* Configures the dynamic memory read strategy. */
    __I  uint32_t  RESERVED1;
    __IO uint32_t  DYNAMICRP;           /* Selects the precharge command period. */
    __IO uint32_t  DYNAMICRAS;          /* Selects the active to precharge command period. */
    __IO uint32_t  DYNAMICSREX;         /* Selects the self-refresh exit time. */
    __IO uint32_t  DYNAMICAPR;          /* Selects the last-data-out to active command time. */
    __IO uint32_t  DYNAMICDAL;          /* Selects the data-in to active command time. */
    __IO uint32_t  DYNAMICWR;           /* Selects the write recovery time. */
    __IO uint32_t  DYNAMICRC;           /* Selects the active to active command period. */
    __IO uint32_t  DYNAMICRFC;          /* Selects the auto-refresh period. */
    __IO uint32_t  DYNAMICXSR;          /* Selects the exit self-refresh to active command time. */
    __IO uint32_t  DYNAMICRRD;          /* Selects the active bank A to active bank B latency. */
    __IO uint32_t  DYNAMICMRD;          /* Selects the load mode register to active command time. */
    __I  uint32_t  RESERVED2[9];
    __IO uint32_t  STATICEXTENDEDWAIT;  /* Selects time for long static memory read and write transfers. */
    __I  uint32_t  RESERVED3[31];
    __IO uint32_t  DYNAMICCONFIG0;      /* Selects the configuration information for dynamic memory chip select n. */
    __IO uint32_t  DYNAMICRASCAS0;      /* Selects the RAS and CAS latencies for dynamic memory chip select n. */
    __I  uint32_t  RESERVED4[6];
    __IO uint32_t  DYNAMICCONFIG1;      /* Selects the configuration information for dynamic memory chip select n. */
    __IO uint32_t  DYNAMICRASCAS1;      /* Selects the RAS and CAS latencies for dynamic memory chip select n. */
    __I  uint32_t  RESERVED5[6];
    __IO uint32_t  DYNAMICCONFIG2;      /* Selects the configuration information for dynamic memory chip select n. */
    __IO uint32_t  DYNAMICRASCAS2;      /* Selects the RAS and CAS latencies for dynamic memory chip select n. */
    __I  uint32_t  RESERVED6[6];
    __IO uint32_t  DYNAMICCONFIG3;      /* Selects the configuration information for dynamic memory chip select n. */
    __IO uint32_t  DYNAMICRASCAS3;      /* Selects the RAS and CAS latencies for dynamic memory chip select n. */
    __I  uint32_t  RESERVED7[38];
    __IO uint32_t  STATICCONFIG0;       /* Selects the memory configuration for static chip select n. */
    __IO uint32_t  STATICWAITWEN0;      /* Selects the delay from chip select n to write enable. */
    __IO uint32_t  STATICWAITOEN0;      /* Selects the delay from chip select n or address change, whichever is later, to output enable. */
    __IO uint32_t  STATICWAITRD0;       /* Selects the delay from chip select n to a read access. */
    __IO uint32_t  STATICWAITPAG0;      /* Selects the delay for asynchronous page mode sequential accesses for chip select n. */
    __IO uint32_t  STATICWAITWR0;       /* Selects the delay from chip select n to a write access. */
    __IO uint32_t  STATICWAITTURN0;     /* Selects bus turnaround cycles */
    __I  uint32_t  RESERVED8;
    __IO uint32_t  STATICCONFIG1;       /* Selects the memory configuration for static chip select n. */
    __IO uint32_t  STATICWAITWEN1;      /* Selects the delay from chip select n to write enable. */
    __IO uint32_t  STATICWAITOEN1;      /* Selects the delay from chip select n or address change, whichever is later, to output enable. */
    __IO uint32_t  STATICWAITRD1;       /* Selects the delay from chip select n to a read access. */
    __IO uint32_t  STATICWAITPAG1;      /* Selects the delay for asynchronous page mode sequential accesses for chip select n. */
    __IO uint32_t  STATICWAITWR1;       /* Selects the delay from chip select n to a write access. */
    __IO uint32_t  STATICWAITTURN1;     /* Selects bus turnaround cycles */
    __I  uint32_t  RESERVED9;
    __IO uint32_t  STATICCONFIG2;       /* Selects the memory configuration for static chip select n. */
    __IO uint32_t  STATICWAITWEN2;      /* Selects the delay from chip select n to write enable. */
    __IO uint32_t  STATICWAITOEN2;      /* Selects the delay from chip select n or address change, whichever is later, to output enable. */
    __IO uint32_t  STATICWAITRD2;       /* Selects the delay from chip select n to a read access. */
    __IO uint32_t  STATICWAITPAG2;      /* Selects the delay for asynchronous page mode sequential accesses for chip select n. */
    __IO uint32_t  STATICWAITWR2;       /* Selects the delay from chip select n to a write access. */
    __IO uint32_t  STATICWAITTURN2;     /* Selects bus turnaround cycles */
    __I  uint32_t  RESERVED10;
    __IO uint32_t  STATICCONFIG3;       /* Selects the memory configuration for static chip select n. */
    __IO uint32_t  STATICWAITWEN3;      /* Selects the delay from chip select n to write enable. */
    __IO uint32_t  STATICWAITOEN3;      /* Selects the delay from chip select n or address change, whichever is later, to output enable. */
    __IO uint32_t  STATICWAITRD3;       /* Selects the delay from chip select n to a read access. */
    __IO uint32_t  STATICWAITPAG3;      /* Selects the delay for asynchronous page mode sequential accesses for chip select n. */
    __IO uint32_t  STATICWAITWR3;       /* Selects the delay from chip select n to a write access. */
    __IO uint32_t  STATICWAITTURN3;     /* Selects bus turnaround cycles */
} LPC_EMC_T;

/* ---------------------------------------------------------------------------
 * USB High-Speed register block structure
 */
#define LPC_USB0_BASE             0x40006000
#define LPC_USB1_BASE             0x40007000

typedef struct {                        /* USB Structure         */
    __I  uint32_t  RESERVED0[64];
    __I  uint32_t  CAPLENGTH;           /* Capability register length */
    __I  uint32_t  HCSPARAMS;           /* Host controller structural parameters */
    __I  uint32_t  HCCPARAMS;           /* Host controller capability parameters */
    __I  uint32_t  RESERVED1[5];
    __I  uint32_t  DCIVERSION;          /* Device interface version number */
    __I  uint32_t  RESERVED2[7];
    union {
        __IO uint32_t  USBCMD_H;        /* USB command (host mode) */
        __IO uint32_t  USBCMD_D;        /* USB command (device mode) */
    };

    union {
        __IO uint32_t  USBSTS_H;        /* USB status (host mode) */
        __IO uint32_t  USBSTS_D;        /* USB status (device mode) */
    };

    union {
        __IO uint32_t  USBINTR_H;       /* USB interrupt enable (host mode) */
        __IO uint32_t  USBINTR_D;       /* USB interrupt enable (device mode) */
    };

    union {
        __IO uint32_t  FRINDEX_H;       /* USB frame index (host mode) */
        __I  uint32_t  FRINDEX_D;       /* USB frame index (device mode) */
    };

    __I  uint32_t  RESERVED3;
    union {
        __IO uint32_t  PERIODICLISTBASE; /* Frame list base address */
        __IO uint32_t  DEVICEADDR;      /* USB device address     */
    };

    union {
        __IO uint32_t  ASYNCLISTADDR;   /* Address of endpoint list in memory (host mode) */
        __IO uint32_t  ENDPOINTLISTADDR; /* Address of endpoint list in memory (device mode) */
    };

    __IO uint32_t  TTCTRL;              /* Asynchronous buffer status for embedded TT (host mode) */
    __IO uint32_t  BURSTSIZE;           /* Programmable burst size */
    __IO uint32_t  TXFILLTUNING;        /* Host transmit pre-buffer packet tuning (host mode) */
    __I  uint32_t  RESERVED4[2];
    __IO uint32_t  ULPIVIEWPORT;        /* ULPI viewport          */
    __IO uint32_t  BINTERVAL;           /* Length of virtual frame */
    __IO uint32_t  ENDPTNAK;            /* Endpoint NAK (device mode) */
    __IO uint32_t  ENDPTNAKEN;          /* Endpoint NAK Enable (device mode) */
    __I  uint32_t  RESERVED5;
    union {
        __IO uint32_t  PORTSC1_H;       /* Port 1 status/control (host mode) */
        __IO uint32_t  PORTSC1_D;       /* Port 1 status/control (device mode) */
    };

    __I  uint32_t  RESERVED6[7];
    __IO uint32_t  OTGSC;               /* OTG status and control */
    union {
        __IO uint32_t  USBMODE_H;       /* USB mode (host mode)   */
        __IO uint32_t  USBMODE_D;       /* USB mode (device mode) */
    };

    __IO uint32_t  ENDPTSETUPSTAT;      /* Endpoint setup status  */
    __IO uint32_t  ENDPTPRIME;          /* Endpoint initialization */
    __IO uint32_t  ENDPTFLUSH;          /* Endpoint de-initialization */
    __I  uint32_t  ENDPTSTAT;           /* Endpoint status        */
    __IO uint32_t  ENDPTCOMPLETE;       /* Endpoint complete      */
    __IO uint32_t  ENDPTCTRL[6];        /* Endpoint control 0     */
} LPC_USBHS_T;

/* ---------------------------------------------------------------------------
 * LCD Controller register block structure
 */
#define LPC_LCD_BASE              0x40008000

typedef struct {                /* LCD Structure          */
    __IO uint32_t  TIMH;        /* Horizontal Timing Control register */
    __IO uint32_t  TIMV;        /* Vertical Timing Control register */
    __IO uint32_t  POL;         /* Clock and Signal Polarity Control register */
    __IO uint32_t  LE;          /* Line End Control register */
    __IO uint32_t  UPBASE;      /* Upper Panel Frame Base Address register */
    __IO uint32_t  LPBASE;      /* Lower Panel Frame Base Address register */
    __IO uint32_t  CTRL;        /* LCD Control register   */
    __IO uint32_t  INTMSK;      /* Interrupt Mask register */
    __I  uint32_t  INTRAW;      /* Raw Interrupt Status register */
    __I  uint32_t  INTSTAT;     /* Masked Interrupt Status register */
    __O  uint32_t  INTCLR;      /* Interrupt Clear register */
    __I  uint32_t  UPCURR;      /* Upper Panel Current Address Value register */
    __I  uint32_t  LPCURR;      /* Lower Panel Current Address Value register */
    __I  uint32_t  RESERVED0[115];
    __IO uint16_t PAL[256];     /* 256x16-bit Color Palette registers */
    __I  uint32_t  RESERVED1[256];
    __IO uint32_t CRSR_IMG[256];/* Cursor Image registers */
    __IO uint32_t  CRSR_CTRL;   /* Cursor Control register */
    __IO uint32_t  CRSR_CFG;    /* Cursor Configuration register */
    __IO uint32_t  CRSR_PAL0;   /* Cursor Palette register 0 */
    __IO uint32_t  CRSR_PAL1;   /* Cursor Palette register 1 */
    __IO uint32_t  CRSR_XY;     /* Cursor XY Position register */
    __IO uint32_t  CRSR_CLIP;   /* Cursor Clip Position register */
    __I  uint32_t  RESERVED2[2];
    __IO uint32_t  CRSR_INTMSK; /* Cursor Interrupt Mask register */
    __O  uint32_t  CRSR_INTCLR; /* Cursor Interrupt Clear register */
    __I  uint32_t  CRSR_INTRAW; /* Cursor Raw Interrupt Status register */
    __I  uint32_t  CRSR_INTSTAT;/* Cursor Masked Interrupt Status register */
} LPC_LCD_T;

/* ---------------------------------------------------------------------------
 * EEPROM register block structure
 */
#define LPC_EEPROM_BASE           0x4000E000

typedef struct {                /* EEPROM Structure */
    __IO uint32_t CMD;          /* EEPROM command register */
    uint32_t RESERVED0;
    __IO uint32_t RWSTATE;      /* EEPROM read wait state register */
    __IO uint32_t AUTOPROG;     /* EEPROM auto programming register */
    __IO uint32_t WSTATE;       /* EEPROM wait state register */
    __IO uint32_t CLKDIV;       /* EEPROM clock divider register */
    __IO uint32_t PWRDWN;       /* EEPROM power-down register */
    uint32_t RESERVED2[1007];
    __O  uint32_t INTENCLR;     /* EEPROM interrupt enable clear */
    __O  uint32_t INTENSET;     /* EEPROM interrupt enable set */
    __I  uint32_t INTSTAT;      /* EEPROM interrupt status */
    __I  uint32_t INTEN;        /* EEPROM interrupt enable */
    __O  uint32_t INTSTATCLR;   /* EEPROM interrupt status clear */
    __O  uint32_t INTSTATSET;   /* EEPROM interrupt status set */
} LPC_EEPROM_T;

/* ---------------------------------------------------------------------------
 * 10/100 MII & RMII Ethernet with timestamping register block structure
 */
#define LPC_ETHERNET_BASE         0x40010000

typedef struct {                        /* ETHERNET Structure */
    __IO uint32_t  MAC_CONFIG;          /* MAC configuration register */
    __IO uint32_t  MAC_FRAME_FILTER;    /* MAC frame filter */
    __IO uint32_t  MAC_HASHTABLE_HIGH;  /* Hash table high register */
    __IO uint32_t  MAC_HASHTABLE_LOW;   /* Hash table low register */
    __IO uint32_t  MAC_MII_ADDR;        /* MII address register */
    __IO uint32_t  MAC_MII_DATA;        /* MII data register */
    __IO uint32_t  MAC_FLOW_CTRL;       /* Flow control register */
    __IO uint32_t  MAC_VLAN_TAG;        /* VLAN tag register */
    __I  uint32_t  RESERVED0;
    __I  uint32_t  MAC_DEBUG;           /* Debug register */
    __IO uint32_t  MAC_RWAKE_FRFLT;     /* Remote wake-up frame filter */
    __IO uint32_t  MAC_PMT_CTRL_STAT;   /* PMT control and status */
    __I  uint32_t  RESERVED1[2];
    __I  uint32_t  MAC_INTR;            /* Interrupt status register */
    __IO uint32_t  MAC_INTR_MASK;       /* Interrupt mask register */
    __IO uint32_t  MAC_ADDR0_HIGH;      /* MAC address 0 high register */
    __IO uint32_t  MAC_ADDR0_LOW;       /* MAC address 0 low register */
    __I  uint32_t  RESERVED2[430];
    __IO uint32_t  MAC_TIMESTP_CTRL;    /* Time stamp control register */
    __IO uint32_t  SUBSECOND_INCR;      /* Sub-second increment register */
    __I  uint32_t  SECONDS;             /* System time seconds register */
    __I  uint32_t  NANOSECONDS;         /* System time nanoseconds register */
    __IO uint32_t  SECONDSUPDATE;       /* System time seconds update register */
    __IO uint32_t  NANOSECONDSUPDATE;   /* System time nanoseconds update register */
    __IO uint32_t  ADDEND;              /* Time stamp addend register */
    __IO uint32_t  TARGETSECONDS;       /* Target time seconds register */
    __IO uint32_t  TARGETNANOSECONDS;   /* Target time nanoseconds register */
    __IO uint32_t  HIGHWORD;            /* System time higher word seconds register */
    __I  uint32_t  TIMESTAMPSTAT;       /* Time stamp status register */
    __IO uint32_t  PPSCTRL;             /* PPS control register */
    __I  uint32_t  AUXNANOSECONDS;      /* Auxiliary time stamp nanoseconds register */
    __I  uint32_t  AUXSECONDS;          /* Auxiliary time stamp seconds register */
    __I  uint32_t  RESERVED3[562];
    __IO uint32_t  DMA_BUS_MODE;        /* Bus Mode Register      */
    __IO uint32_t  DMA_TRANS_POLL_DEMAND; /* Transmit poll demand register */
    __IO uint32_t  DMA_REC_POLL_DEMAND; /* Receive poll demand register */
    __IO uint32_t  DMA_REC_DES_ADDR;    /* Receive descriptor list address register */
    __IO uint32_t  DMA_TRANS_DES_ADDR;  /* Transmit descriptor list address register */
    __IO uint32_t  DMA_STAT;            /* Status register */
    __IO uint32_t  DMA_OP_MODE;         /* Operation mode register */
    __IO uint32_t  DMA_INT_EN;          /* Interrupt enable register */
    __I  uint32_t  DMA_MFRM_BUFOF;      /* Missed frame and buffer overflow register */
    __IO uint32_t  DMA_REC_INT_WDT;     /* Receive interrupt watchdog timer register */
    __I  uint32_t  RESERVED4[8];
    __I  uint32_t  DMA_CURHOST_TRANS_DES; /* Current host transmit descriptor register */
    __I  uint32_t  DMA_CURHOST_REC_DES; /* Current host receive descriptor register */
    __I  uint32_t  DMA_CURHOST_TRANS_BUF; /* Current host transmit buffer address register */
    __I  uint32_t  DMA_CURHOST_REC_BUF; /* Current host receive buffer address register */
} LPC_ENET_T;

/* ---------------------------------------------------------------------------
 * Alarm Timer register block structure
 */
#define LPC_ATIMER_BASE           0x40040000

typedef struct {                /* ATIMER Structure       */
    __IO uint32_t DOWNCOUNTER;  /* Downcounter register   */
    __IO uint32_t PRESET;       /* Preset value register  */
    __I  uint32_t RESERVED0[1012];
    __O  uint32_t CLR_EN;       /* Interrupt clear enable register */
    __O  uint32_t SET_EN;       /* Interrupt set enable register */
    __I  uint32_t STATUS;       /* Status register        */
    __I  uint32_t ENABLE;       /* Enable register        */
    __O  uint32_t CLR_STAT;     /* Clear register         */
    __O  uint32_t SET_STAT;     /* Set register           */
} LPC_ATIMER_T;

/* ---------------------------------------------------------------------------
 * Register File register block structure
 */
#define LPC_REGFILE_BASE          0x40041000

typedef struct {
    __IO uint32_t REGFILE[64];  /* General purpose storage register */
} LPC_REGFILE_T;

/* ---------------------------------------------------------------------------
 * Power Management Controller register block structure
 */
#define LPC_PMC_BASE              0x40042000

typedef struct {                        /* PMC Structure          */
    __IO uint32_t  PD0_SLEEP0_HW_ENA;   /* Hardware sleep event enable register */
    __I  uint32_t  RESERVED0[6];
    __IO uint32_t  PD0_SLEEP0_MODE;     /* Sleep power mode register */
} LPC_PMC_T;

/* ---------------------------------------------------------------------------
 * CREG Register Block
 */
#define LPC_CREG_BASE             0x40043000

typedef struct {                        /* CREG Structure         */
    __I  uint32_t  RESERVED0;
    __IO uint32_t  CREG0;               /* Chip configuration register 32 kHz oscillator output and BOD control register. */
    __I  uint32_t  RESERVED1[62];
    __IO uint32_t  MXMEMMAP;            /* ARM Cortex-M3/M4 memory mapping */
#if defined(CHIP_LPC18XX)
    __I  uint32_t  RESERVED2[5];
#else
    __I  uint32_t  RESERVED2;
    __I  uint32_t  CREG1;               /* Configuration Register 1 */
    __I  uint32_t  CREG2;               /* Configuration Register 2 */
    __I  uint32_t  CREG3;               /* Configuration Register 3 */
    __I  uint32_t  CREG4;               /* Configuration Register 4 */
#endif
    __IO uint32_t  CREG5;               /* Chip configuration register 5. Controls JTAG access. */
    __IO uint32_t  DMAMUX;              /* DMA muxing control     */
    __IO uint32_t  FLASHCFGA;           /* Flash accelerator configuration register for flash bank A */
    __IO uint32_t  FLASHCFGB;           /* Flash accelerator configuration register for flash bank B */
    __IO uint32_t  ETBCFG;              /* ETB RAM configuration  */
    __IO uint32_t  CREG6;               /* Chip configuration register 6. */
#if defined(CHIP_LPC18XX)
    __I  uint32_t  RESERVED4[52];
#else
    __IO uint32_t  M4TXEVENT;           /* M4 IPC event register */
    __I  uint32_t  RESERVED4[51];
#endif
    __I  uint32_t  CHIPID;              /* Part ID                */
#if defined(CHIP_LPC18XX)
    __I  uint32_t  RESERVED5[191];
#else
    __I  uint32_t  RESERVED5[127];
    __IO uint32_t  M0TXEVENT;           /* M0 IPC Event register */
    __IO uint32_t  M0APPMEMMAP;         /* ARM Cortex M0 memory mapping */
    __I  uint32_t  RESERVED6[62];
#endif
    __IO uint32_t  USB0FLADJ;           /* USB0 frame length adjust register */
    __I  uint32_t  RESERVED7[63];
    __IO uint32_t  USB1FLADJ;           /* USB1 frame length adjust register */
} LPC_CREG_T;

/* ---------------------------------------------------------------------------
 * Event Router register structure
 */
#define LPC_EVRT_BASE             0x40044000

typedef struct {                        /* EVENTROUTER Structure  */
    __IO uint32_t HILO;                 /* Level configuration register */
    __IO uint32_t EDGE;                 /* Edge configuration     */
    __I  uint32_t RESERVED0[1012];
    __O  uint32_t CLR_EN;               /* Event clear enable register */
    __O  uint32_t SET_EN;               /* Event set enable register */
    __I  uint32_t STATUS;               /* Status register        */
    __I  uint32_t ENABLE;               /* Enable register        */
    __O  uint32_t CLR_STAT;             /* Clear register         */
    __O  uint32_t SET_STAT;             /* Set register           */
} LPC_EVRT_T;

/* ---------------------------------------------------------------------------
 * Real Time Clock register block structure
 */
#define LPC_RTC_BASE              0x40046000
#define RTC_EV_SUPPORT      1           /* Event Monitor/Recorder support */

typedef enum RTC_TIMEINDEX {
    RTC_TIMETYPE_SECOND,        /* Second */
    RTC_TIMETYPE_MINUTE,        /* Month */
    RTC_TIMETYPE_HOUR,          /* Hour */
    RTC_TIMETYPE_DAYOFMONTH,    /* Day of month */
    RTC_TIMETYPE_DAYOFWEEK,     /* Day of week */
    RTC_TIMETYPE_DAYOFYEAR,     /* Day of year */
    RTC_TIMETYPE_MONTH,         /* Month */
    RTC_TIMETYPE_YEAR,          /* Year */
    RTC_TIMETYPE_LAST
} RTC_TIMEINDEX_T;

#if RTC_EV_SUPPORT
typedef enum LPC_RTC_EV_CHANNEL {
    RTC_EV_CHANNEL_1 = 0,
    RTC_EV_CHANNEL_2,
    RTC_EV_CHANNEL_3,
    RTC_EV_CHANNEL_NUM,
} LPC_RTC_EV_CHANNEL_T;
#endif /*RTC_EV_SUPPORT*/

typedef struct {                        /* RTC Structure          */
    __IO uint32_t  ILR;                 /* Interrupt Location Register */
    __I  uint32_t  RESERVED0;
    __IO uint32_t  CCR;                 /* Clock Control Register */
    __IO uint32_t  CIIR;                /* Counter Increment Interrupt Register */
    __IO uint32_t  AMR;                 /* Alarm Mask Register    */
    __I  uint32_t  CTIME[3];            /* Consolidated Time Register 0,1,2 */
    __IO uint32_t  TIME[RTC_TIMETYPE_LAST]; /* Timer field registers */
    __IO uint32_t  CALIBRATION;         /* Calibration Value Register */
    __I  uint32_t  RESERVED1[7];
    __IO uint32_t  ALRM[RTC_TIMETYPE_LAST]; /* Alarm field registers */
#if RTC_EV_SUPPORT
    __IO uint32_t ERSTATUS;             /* Event Monitor/Recorder Status register*/
    __IO uint32_t ERCONTROL;            /* Event Monitor/Recorder Control register*/
    __I  uint32_t ERCOUNTERS;           /* Event Monitor/Recorder Counters register*/
    __I  uint32_t RESERVED2;
    __I  uint32_t ERFIRSTSTAMP[RTC_EV_CHANNEL_NUM]; /* Event Monitor/Recorder First Stamp registers*/
    __I  uint32_t RESERVED3;
    __I  uint32_t ERLASTSTAMP[RTC_EV_CHANNEL_NUM];  /* Event Monitor/Recorder Last Stamp registers*/
#endif /*RTC_EV_SUPPORT*/
} LPC_RTC_T;

/* ---------------------------------------------------------------------------
 * LPC18XX/43XX CGU register block structure
 */
#define LPC_CGU_BASE              0x40050000
#define LPC_CCU1_BASE             0x40051000
#define LPC_CCU2_BASE             0x40052000
/*
 * Input clocks for the CGU and can come from both external (crystal) and
 * internal (PLL) sources. Can be routed to the base clocks.
 */
typedef enum CGU_CLKIN {
    CLKIN_32K,      /* External 32KHz input */
    CLKIN_IRC,      /* Internal IRC (12MHz) input */
    CLKIN_ENET_RX,  /* External ENET_RX pin input */
    CLKIN_ENET_TX,  /* External ENET_TX pin input */
    CLKIN_CLKIN,    /* External GPCLKIN pin input */
    CLKIN_RESERVED1,
    CLKIN_CRYSTAL,  /* External (main) crystal pin input */
    CLKIN_USBPLL,   /* Internal USB PLL input */
    CLKIN_AUDIOPLL, /* Internal Audio PLL input */
    CLKIN_MAINPLL,  /* Internal Main PLL input */
    CLKIN_RESERVED2,
    CLKIN_RESERVED3,
    CLKIN_IDIVA,    /* Internal divider A input */
    CLKIN_IDIVB,    /* Internal divider B input */
    CLKIN_IDIVC,    /* Internal divider C input */
    CLKIN_IDIVD,    /* Internal divider D input */
    CLKIN_IDIVE,    /* Internal divider E input */
    CLKINPUT_PD     /* External 32KHz input */
} CGU_CLKIN_T;

#define CLKIN_PLL0USB    CLKIN_USBPLL
#define CLKIN_PLL0AUDIO  CLKIN_AUDIOPLL
#define CLKIN_PLL1       CLKIN_MAINPLL

/*
 * CGU base clocks are clocks that are associated with a single input clock
 * and are routed out to 1 or more peripherals. For example, the CLK_BASE_PERIPH
 * clock can be configured to use the CLKIN_MAINPLL input clock, which will in
 * turn route that clock to the CLK_PERIPH_BUS, CLK_PERIPH_CORE, and
 * CLK_PERIPH_SGPIO periphral clocks.
 */
typedef enum CGU_BASE_CLK {
    CLK_BASE_SAFE,        /* Base clock for WDT oscillator, IRC input only */
    CLK_BASE_USB0,        /* Base USB clock for USB0, USB PLL input only */
#if defined(CHIP_LPC43XX)
    CLK_BASE_PERIPH,      /* Base clock for SGPIO */
#else
    CLK_BASE_RESERVED1,
#endif
    CLK_BASE_USB1,        /* Base USB clock for USB1 */
    CLK_BASE_MX,          /* Base clock for CPU core */
    CLK_BASE_SPIFI,       /* Base clock for SPIFI */
#if defined(CHIP_LPC43XX)
    CLK_BASE_SPI,         /* Base clock for SPI */
#else
    CLK_BASE_RESERVED2,
#endif
    CLK_BASE_PHY_RX,      /* Base clock for PHY RX */
    CLK_BASE_PHY_TX,      /* Base clock for PHY TX */
    CLK_BASE_APB1,        /* Base clock for APB1 group */
    CLK_BASE_APB3,        /* Base clock for APB3 group */
    CLK_BASE_LCD,         /* Base clock for LCD pixel clock */
#if defined(CHIP_LPC43XX)
    CLK_BASE_VADC,        /* Base clock for VADC */
#else
    CLK_BASE_RESERVED3,
#endif
    CLK_BASE_SDIO,        /* Base clock for SDIO */
    CLK_BASE_SSP0,        /* Base clock for SSP0 */
    CLK_BASE_SSP1,        /* Base clock for SSP1 */
    CLK_BASE_UART0,       /* Base clock for UART0 */
    CLK_BASE_UART1,       /* Base clock for UART1 */
    CLK_BASE_UART2,       /* Base clock for UART2 */
    CLK_BASE_UART3,       /* Base clock for UART3 */
    CLK_BASE_OUT,         /* Base clock for CLKOUT pin */
    CLK_BASE_RESERVED4,
    CLK_BASE_RESERVED5,
    CLK_BASE_RESERVED6,
    CLK_BASE_RESERVED7,
    CLK_BASE_APLL,        /* Base clock for audio PLL */
    CLK_BASE_CGU_OUT0,    /* Base clock for CGUOUT0 pin */
    CLK_BASE_CGU_OUT1,    /* Base clock for CGUOUT1 pin */
    CLK_BASE_LAST,
    CLK_BASE_NONE = CLK_BASE_LAST
} CGU_BASE_CLK_T;

/*
 * CGU dividers provide an extra clock state where a specific clock can be
 * divided before being routed to a peripheral group. A divider accepts an
 * input clock and then divides it. To use the divided clock for a base clock
 * group, use the divider as the input clock for the base clock (for example,
 * use CLKIN_IDIVB, where CLKIN_MAINPLL might be the input into the divider).
 */
typedef enum CGU_IDIV {
    CLK_IDIV_A,       /* CGU clock divider A */
    CLK_IDIV_B,       /* CGU clock divider B */
    CLK_IDIV_C,       /* CGU clock divider A */
    CLK_IDIV_D,       /* CGU clock divider D */
    CLK_IDIV_E,       /* CGU clock divider E */
    CLK_IDIV_LAST
} CGU_IDIV_T;

/*
 * Peripheral clocks are individual clocks routed to peripherals. Although
 * multiple peripherals may share a same base clock, each peripheral's clock
 * can be enabled or disabled individually. Some peripheral clocks also have
 * additional dividers associated with them.
 */
typedef enum CCU_CLK {
    /* CCU1 clocks */
    CLK_APB3_BUS,     /* APB3 bus clock from base clock CLK_BASE_APB3 */
    CLK_APB3_I2C1,    /* I2C1 register/perigheral clock from base clock CLK_BASE_APB3 */
    CLK_APB3_DAC,     /* DAC peripheral clock from base clock CLK_BASE_APB3 */
    CLK_APB3_ADC0,    /* ADC0 register/perigheral clock from base clock CLK_BASE_APB3 */
    CLK_APB3_ADC1,    /* ADC1 register/perigheral clock from base clock CLK_BASE_APB3 */
    CLK_APB3_CAN0,    /* CAN0 register/perigheral clock from base clock CLK_BASE_APB3 */
    CLK_APB1_BUS = 32, /* APB1 bus clock clock from base clock CLK_BASE_APB1 */
    CLK_APB1_MOTOCON, /* Motor controller register/perigheral clock from base clock CLK_BASE_APB1 */
    CLK_APB1_I2C0,    /* I2C0 register/perigheral clock from base clock CLK_BASE_APB1 */
    CLK_APB1_I2S,     /* I2S register/perigheral clock from base clock CLK_BASE_APB1 */
    CLK_APB1_CAN1,    /* CAN1 register/perigheral clock from base clock CLK_BASE_APB1 */
    CLK_SPIFI = 64,   /* SPIFI SCKI input clock from base clock CLK_BASE_SPIFI */
    CLK_MX_BUS = 96,  /* M3/M4 BUS core clock from base clock CLK_BASE_MX */
    CLK_MX_SPIFI,     /* SPIFI register clock from base clock CLK_BASE_MX */
    CLK_MX_GPIO,      /* GPIO register clock from base clock CLK_BASE_MX */
    CLK_MX_LCD,       /* LCD register clock from base clock CLK_BASE_MX */
    CLK_MX_ETHERNET,  /* ETHERNET register clock from base clock CLK_BASE_MX */
    CLK_MX_USB0,      /* USB0 register clock from base clock CLK_BASE_MX */
    CLK_MX_EMC,       /* EMC clock from base clock CLK_BASE_MX */
    CLK_MX_SDIO,      /* SDIO register clock from base clock CLK_BASE_MX */
    CLK_MX_DMA,       /* DMA register clock from base clock CLK_BASE_MX */
    CLK_MX_MXCORE,    /* M3/M4 CPU core clock from base clock CLK_BASE_MX */
    RESERVED_ALIGN = CLK_MX_MXCORE + 3,
    CLK_MX_SCT,       /* SCT register clock from base clock CLK_BASE_MX */
    CLK_MX_USB1,      /* USB1 register clock from base clock CLK_BASE_MX */
    CLK_MX_EMC_DIV,   /* ENC divider clock from base clock CLK_BASE_MX */
    CLK_MX_FLASHA,    /* FLASHA bank clock from base clock CLK_BASE_MX */
    CLK_MX_FLASHB,    /* FLASHB bank clock from base clock CLK_BASE_MX */
#if defined(CHIP_LPC43XX)
    CLK_M4_M0APP,     /* M0 app CPU core clock from base clock CLK_BASE_MX */
    CLK_MX_VADC,      /* VADC clock from base clock CLK_BASE_MX */
#else
    CLK_RESERVED1,
    CLK_RESERVED2,
#endif
    CLK_MX_EEPROM,    /* EEPROM clock from base clock CLK_BASE_MX */
    CLK_MX_WWDT = 128, /* WWDT register clock from base clock CLK_BASE_MX */
    CLK_MX_UART0,     /* UART0 register clock from base clock CLK_BASE_MX */
    CLK_MX_UART1,     /* UART1 register clock from base clock CLK_BASE_MX */
    CLK_MX_SSP0,      /* SSP0 register clock from base clock CLK_BASE_MX */
    CLK_MX_TIMER0,    /* TIMER0 register/perigheral clock from base clock CLK_BASE_MX */
    CLK_MX_TIMER1,    /* TIMER1 register/perigheral clock from base clock CLK_BASE_MX */
    CLK_MX_SCU,       /* SCU register/perigheral clock from base clock CLK_BASE_MX */
    CLK_MX_CREG,      /* CREG clock from base clock CLK_BASE_MX */
    CLK_MX_RITIMER = 160, /* RITIMER register/perigheral clock from base clock CLK_BASE_MX */
    CLK_MX_UART2,     /* UART3 register clock from base clock CLK_BASE_MX */
    CLK_MX_UART3,     /* UART4 register clock from base clock CLK_BASE_MX */
    CLK_MX_TIMER2,    /* TIMER2 register/perigheral clock from base clock CLK_BASE_MX */
    CLK_MX_TIMER3,    /* TIMER3 register/perigheral clock from base clock CLK_BASE_MX */
    CLK_MX_SSP1,      /* SSP1 register clock from base clock CLK_BASE_MX */
    CLK_MX_QEI,       /* QEI register/perigheral clock from base clock CLK_BASE_MX */
#if defined(CHIP_LPC43XX)
    CLK_PERIPH_BUS = 192, /* Peripheral bus clock from base clock CLK_BASE_PERIPH */
    CLK_RESERVED3,
    CLK_PERIPH_CORE,  /* Peripheral core clock from base clock CLK_BASE_PERIPH */
    CLK_PERIPH_SGPIO, /* SGPIO clock from base clock CLK_BASE_PERIPH */
#else
    CLK_RESERVED3 = 192,
    CLK_RESERVED3A,
    CLK_RESERVED4,
    CLK_RESERVED5,
#endif
    CLK_USB0 = 224,   /* USB0 clock from base clock CLK_BASE_USB0 */
    CLK_USB1 = 256,   /* USB1 clock from base clock CLK_BASE_USB1 */
#if defined(CHIP_LPC43XX)
    CLK_SPI = 288,    /* SPI clock from base clock CLK_BASE_SPI */
    CLK_VADC,         /* VADC clock from base clock CLK_BASE_VADC */
#else
    CLK_RESERVED7 = 320,
    CLK_RESERVED8,
#endif
    CLK_CCU1_LAST,

    /* CCU2 clocks */
    CLK_CCU2_START,
    CLK_APLL = CLK_CCU2_START, /* Audio PLL clock from base clock CLK_BASE_APLL */
    RESERVED_ALIGNB = CLK_CCU2_START + 31,
    CLK_APB2_UART3,            /* UART3 clock from base clock CLK_BASE_UART3 */
    RESERVED_ALIGNC = CLK_CCU2_START + 63,
    CLK_APB2_UART2,            /* UART2 clock from base clock CLK_BASE_UART2 */
    RESERVED_ALIGND = CLK_CCU2_START + 95,
    CLK_APB0_UART1,            /* UART1 clock from base clock CLK_BASE_UART1 */
    RESERVED_ALIGNE = CLK_CCU2_START + 127,
    CLK_APB0_UART0,            /* UART0 clock from base clock CLK_BASE_UART0 */
    RESERVED_ALIGNF = CLK_CCU2_START + 159,
    CLK_APB2_SSP1,            /* SSP1 clock from base clock CLK_BASE_SSP1 */
    RESERVED_ALIGNG = CLK_CCU2_START + 191,
    CLK_APB0_SSP0,            /* SSP0 clock from base clock CLK_BASE_SSP0 */
    RESERVED_ALIGNH = CLK_CCU2_START + 223,
    CLK_APB2_SDIO,            /* SDIO clock from base clock CLK_BASE_SDIO */
    CLK_CCU2_LAST
} CCU_CLK_T;

/*
 * Audio or USB PLL selection
 */
typedef enum CGU_USB_AUDIO_PLL {
    CGU_USB_PLL,
    CGU_AUDIO_PLL
} CGU_USB_AUDIO_PLL_T;

/*
 * PLL register block
 */
typedef struct {
    __I  uint32_t  PLL_STAT;            /* PLL status register */
    __IO uint32_t  PLL_CTRL;            /* PLL control register */
    __IO uint32_t  PLL_MDIV;            /* PLL M-divider register */
    __IO uint32_t  PLL_NP_DIV;          /* PLL N/P-divider register */
} CGU_PLL_REG_T;

typedef struct {                        /* (@ 0x40050000) CGU Structure          */
    __I  uint32_t  RESERVED0[5];
    __IO uint32_t  FREQ_MON;            /* (@ 0x40050014) Frequency monitor register */
    __IO uint32_t  XTAL_OSC_CTRL;       /* (@ 0x40050018) Crystal oscillator control register */
    CGU_PLL_REG_T  PLL[CGU_AUDIO_PLL + 1]; /* (@ 0x4005001C) USB and audio PLL blocks */
    __IO uint32_t  PLL0AUDIO_FRAC;      /* (@ 0x4005003C) PLL0 (audio)           */
    __I  uint32_t  PLL1_STAT;           /* (@ 0x40050040) PLL1 status register   */
    __IO uint32_t  PLL1_CTRL;           /* (@ 0x40050044) PLL1 control register  */
    __IO uint32_t  IDIV_CTRL[CLK_IDIV_LAST];/* (@ 0x40050048) Integer divider A-E control registers */
    __IO uint32_t  BASE_CLK[CLK_BASE_LAST]; /* (@ 0x4005005C) Start of base clock registers */
} LPC_CGU_T;

/* ---------------------------------------------------------------------------
 * CCU clock config/status register pair
 */
typedef struct {
    __IO uint32_t  CFG;                 /* CCU clock configuration register */
    __I  uint32_t  STAT;                /* CCU clock status register */
} CCU_CFGSTAT_T;

/* ---------------------------------------------------------------------------
 * CCU1 register block structure
 */
typedef struct {                        /* (@ 0x40051000) CCU1 Structure         */
    __IO uint32_t  PM;                  /* (@ 0x40051000) CCU1 power mode register */
    __I  uint32_t  BASE_STAT;           /* (@ 0x40051004) CCU1 base clocks status register */
    __I  uint32_t  RESERVED0[62];
    CCU_CFGSTAT_T  CLKCCU[CLK_CCU1_LAST]; /* (@ 0x40051100) Start of CCU1 clock registers */
} LPC_CCU1_T;

/* ---------------------------------------------------------------------------
 * CCU2 register block structure
 */
typedef struct {                        /* (@ 0x40052000) CCU2 Structure         */
    __IO uint32_t  PM;                  /* (@ 0x40052000) Power mode register    */
    __I  uint32_t  BASE_STAT;           /* (@ 0x40052004) CCU base clocks status register */
    __I  uint32_t  RESERVED0[62];
    CCU_CFGSTAT_T  CLKCCU[CLK_CCU2_LAST - CLK_CCU1_LAST]; /* (@ 0x40052100) Start of CCU2 clock registers */
} LPC_CCU2_T;

/* ---------------------------------------------------------------------------
 * RGU register structure
 */
#define LPC_RGU_BASE              0x40053000

typedef enum RGU_RST {
    RGU_CORE_RST,
    RGU_PERIPH_RST,
    RGU_MASTER_RST,
    RGU_WWDT_RST = 4,
    RGU_CREG_RST,
    RGU_BUS_RST = 8,
    RGU_SCU_RST,
    RGU_M3_RST = 13,
    RGU_LCD_RST = 16,
    RGU_USB0_RST,
    RGU_USB1_RST,
    RGU_DMA_RST,
    RGU_SDIO_RST,
    RGU_EMC_RST,
    RGU_ETHERNET_RST,
    RGU_FLASHA_RST = 25,
    RGU_EEPROM_RST = 27,
    RGU_GPIO_RST,
    RGU_FLASHB_RST,
    RGU_TIMER0_RST = 32,
    RGU_TIMER1_RST,
    RGU_TIMER2_RST,
    RGU_TIMER3_RST,
    RGU_RITIMER_RST,
    RGU_SCT_RST,
    RGU_MOTOCONPWM_RST,
    RGU_QEI_RST,
    RGU_ADC0_RST,
    RGU_ADC1_RST,
    RGU_DAC_RST,
    RGU_UART0_RST = 44,
    RGU_UART1_RST,
    RGU_UART2_RST,
    RGU_UART3_RST,
    RGU_I2C0_RST,
    RGU_I2C1_RST,
    RGU_SSP0_RST,
    RGU_SSP1_RST,
    RGU_I2S_RST,
    RGU_SPIFI_RST,
    RGU_CAN1_RST,
    RGU_CAN0_RST,
#ifdef CHIP_LPC43XX
    RGU_M0APP_RST,
    RGU_SGPIO_RST,
    RGU_SPI_RST,
#endif
    RGU_LAST_RST = 63,
} RGU_RST_T;

typedef struct {                        /* RGU Structure          */
    __I  uint32_t  RESERVED0[64];
    __O  uint32_t  RESET_CTRL0;         /* Reset control register 0 */
    __O  uint32_t  RESET_CTRL1;         /* Reset control register 1 */
    __I  uint32_t  RESERVED1[2];
    __IO uint32_t  RESET_STATUS0;       /* Reset status register 0 */
    __IO uint32_t  RESET_STATUS1;       /* Reset status register 1 */
    __IO uint32_t  RESET_STATUS2;       /* Reset status register 2 */
    __IO uint32_t  RESET_STATUS3;       /* Reset status register 3 */
    __I  uint32_t  RESERVED2[12];
    __I  uint32_t  RESET_ACTIVE_STATUS0;/* Reset active status register 0 */
    __I  uint32_t  RESET_ACTIVE_STATUS1;/* Reset active status register 1 */
    __I  uint32_t  RESERVED3[170];
    __IO uint32_t  RESET_EXT_STAT[RGU_LAST_RST + 1];/* Reset external status registers */
} LPC_RGU_T;

/* ---------------------------------------------------------------------------
 * Windowed Watchdog register block structure
 */
#define LPC_WWDT_BASE             0x40080000

typedef struct {                /* WWDT Structure         */
    __IO uint32_t  MOD;         /* Watchdog mode register. This register contains the basic mode and status of the Watchdog Timer. */
    __IO uint32_t  TC;          /* Watchdog timer constant register. This register determines the time-out value. */
    __O  uint32_t  FEED;        /* Watchdog feed sequence register. Writing 0xAA followed by 0x55 to this register reloads the Watchdog timer with the value contained in WDTC. */
    __I  uint32_t  TV;          /* Watchdog timer value register. This register reads out the current value of the Watchdog timer. */
#ifdef WATCHDOG_CLKSEL_SUPPORT
    __IO uint32_t CLKSEL;       /* Watchdog clock select register. */
#else
    __I  uint32_t  RESERVED0;
#endif
#ifdef WATCHDOG_WINDOW_SUPPORT
    __IO uint32_t  WARNINT;     /* Watchdog warning interrupt register. This register contains the Watchdog warning interrupt compare value. */
    __IO uint32_t  WINDOW;      /* Watchdog timer window register. This register contains the Watchdog window value. */
#endif
} LPC_WWDT_T;

/* ---------------------------------------------------------------------------
 * USART register block structure
 */
#define LPC_USART0_BASE           0x40081000
#define LPC_UART1_BASE            0x40082000
#define LPC_USART2_BASE           0x400C1000
#define LPC_USART3_BASE           0x400C2000

typedef struct {                /* USARTn Structure       */

    union {
        __IO uint32_t  DLL;     /* Divisor Latch LSB. Least significant byte of the baud rate divisor value. The full divisor is used to generate a baud rate from the fractional rate divider (DLAB = 1). */
        __O  uint32_t  THR;     /* Transmit Holding Register. The next character to be transmitted is written here (DLAB = 0). */
        __I  uint32_t  RBR;     /* Receiver Buffer Register. Contains the next received character to be read (DLAB = 0). */
    };

    union {
        __IO uint32_t IER;      /* Interrupt Enable Register. Contains individual interrupt enable bits for the 7 potential UART interrupts (DLAB = 0). */
        __IO uint32_t DLM;      /* Divisor Latch MSB. Most significant byte of the baud rate divisor value. The full divisor is used to generate a baud rate from the fractional rate divider (DLAB = 1). */
    };

    union {
        __O  uint32_t FCR;      /* FIFO Control Register. Controls UART FIFO usage and modes. */
        __I  uint32_t IIR;      /* Interrupt ID Register. Identifies which interrupt(s) are pending. */
    };

    __IO uint32_t LCR;          /* Line Control Register. Contains controls for frame formatting and break generation. */
    __IO uint32_t MCR;          /* Modem Control Register. Only present on USART ports with full modem support. */
    __I  uint32_t LSR;          /* Line Status Register. Contains flags for transmit and receive status, including line errors. */
    __I  uint32_t MSR;          /* Modem Status Register. Only present on USART ports with full modem support. */
    __IO uint32_t SCR;          /* Scratch Pad Register. Eight-bit temporary storage for software. */
    __IO uint32_t ACR;          /* Auto-baud Control Register. Contains controls for the auto-baud feature. */
    __IO uint32_t ICR;          /* IrDA control register (not all UARTS) */
    __IO uint32_t FDR;          /* Fractional Divider Register. Generates a clock input for the baud rate divider. */
    __IO uint32_t OSR;          /* Oversampling Register. Controls the degree of oversampling during each bit time. Only on some UARTS. */
    __IO uint32_t TER1;         /* Transmit Enable Register. Turns off USART transmitter for use with software flow control. */
    uint32_t  RESERVED0[3];
    __IO uint32_t HDEN;         /* Half-duplex enable Register- only on some UARTs */
    __I  uint32_t RESERVED1[1];
    __IO uint32_t SCICTRL;      /* Smart card interface control register- only on some UARTs */
    __IO uint32_t RS485CTRL;    /* RS-485/EIA-485 Control. Contains controls to configure various aspects of RS-485/EIA-485 modes. */
    __IO uint32_t RS485ADRMATCH; /* RS-485/EIA-485 address match. Contains the address match value for RS-485/EIA-485 mode. */
    __IO uint32_t RS485DLY;     /* RS-485/EIA-485 direction control delay. */
    union {
        __IO uint32_t SYNCCTRL; /* Synchronous mode control register. Only on USARTs. */
        __I  uint32_t FIFOLVL;  /* FIFO Level register. Provides the current fill levels of the transmit and receive FIFOs. */
    };

    __IO uint32_t TER2;         /* Transmit Enable Register. Only on LPC177X_8X UART4 and LPC18XX/43XX USART0/2/3. */
} LPC_USART_T;

/* ---------------------------------------------------------------------------
 * SSP register block structure
 */
#define LPC_SSP0_BASE             0x40083000
#define LPC_SSP1_BASE             0x400C5000

typedef struct {            /* SSPn Structure         */
    __IO uint32_t CR0;      /* Control Register 0. Selects the serial clock rate, bus type, and data size. */
    __IO uint32_t CR1;      /* Control Register 1. Selects master/slave and other modes. */
    __IO uint32_t DR;       /* Data Register. Writes fill the transmit FIFO, and reads empty the receive FIFO. */
    __I  uint32_t SR;       /* Status Register        */
    __IO uint32_t CPSR;     /* Clock Prescale Register */
    __IO uint32_t IMSC;     /* Interrupt Mask Set and Clear Register */
    __I  uint32_t RIS;      /* Raw Interrupt Status Register */
    __I  uint32_t MIS;      /* Masked Interrupt Status Register */
    __O  uint32_t ICR;      /* SSPICR Interrupt Clear Register */
    __IO uint32_t DMACR;    /* SSPn DMA control register */
} LPC_SSP_T;

/* ---------------------------------------------------------------------------
 * 32-bit Standard timer register block structure
 */
#define LPC_TIMER0_BASE           0x40084000
#define LPC_TIMER1_BASE           0x40085000
#define LPC_TIMER2_BASE           0x400C3000
#define LPC_TIMER3_BASE           0x400C4000

typedef struct {            /* TIMERn Structure       */
    __IO uint32_t IR;       /* Interrupt Register. The IR can be written to clear interrupts. The IR can be read to identify which of eight possible interrupt sources are pending. */
    __IO uint32_t TCR;      /* Timer Control Register. The TCR is used to control the Timer Counter functions. The Timer Counter can be disabled or reset through the TCR. */
    __IO uint32_t TC;       /* Timer Counter. The 32 bit TC is incremented every PR+1 cycles of PCLK. The TC is controlled through the TCR. */
    __IO uint32_t PR;       /* Prescale Register. The Prescale Counter (below) is equal to this value, the next clock increments the TC and clears the PC. */
    __IO uint32_t PC;       /* Prescale Counter. The 32 bit PC is a counter which is incremented to the value stored in PR. When the value in PR is reached, the TC is incremented and the PC is cleared. The PC is observable and controllable through the bus interface. */
    __IO uint32_t MCR;      /* Match Control Register. The MCR is used to control if an interrupt is generated and if the TC is reset when a Match occurs. */
    __IO uint32_t MR[4];    /* Match Register. MR can be enabled through the MCR to reset the TC, stop both the TC and PC, and/or generate an interrupt every time MR matches the TC. */
    __IO uint32_t CCR;      /* Capture Control Register. The CCR controls which edges of the capture inputs are used to load the Capture Registers and whether or not an interrupt is generated when a capture takes place. */
    __IO uint32_t CR[4];    /* Capture Register. CR is loaded with the value of TC when there is an event on the CAPn.0 input. */
    __IO uint32_t EMR;      /* External Match Register. The EMR controls the external match pins MATn.0-3 (MAT0.0-3 and MAT1.0-3 respectively). */
    __I  uint32_t RESERVED0[12];
    __IO uint32_t CTCR;     /* Count Control Register. The CTCR selects between Timer and Counter mode, and in Counter mode selects the signal and edge(s) for counting. */
} LPC_TIMER_T;

/* ---------------------------------------------------------------------------
 * System Control Unit register block
 */
#define LPC_SCU_BASE              0x40086000

typedef struct {
    __IO uint32_t  SFSP[16][32];
    __I  uint32_t  RESERVED0[256];
    __IO uint32_t  SFSCLK[4];           /* Pin configuration register for pins CLK0-3 */
    __I  uint32_t  RESERVED16[28];
    __IO uint32_t  SFSUSB;              /* Pin configuration register for USB */
    __IO uint32_t  SFSI2C0;             /* Pin configuration register for I2C0-bus pins */
    __IO uint32_t  ENAIO[3];            /* Analog function select registers */
    __I  uint32_t  RESERVED17[27];
    __IO uint32_t  EMCDELAYCLK;         /* EMC clock delay register */
    __I  uint32_t  RESERVED18[63];
    __IO uint32_t  PINTSEL0;            /* Pin interrupt select register for pin interrupts 0 to 3. */
    __IO uint32_t  PINTSEL1;            /* Pin interrupt select register for pin interrupts 4 to 7. */
} LPC_SCU_T;

/*
 * SCU function and mode selection definitions
 * See the User Manual for specific modes and functions supoprted by the
 * various LPC18xx/43xx devices. Functionality can vary per device.
 */
#define SCU_MODE_PULLUP            (0x0 << 3)   /* Enable pull-up resistor at pad */
#define SCU_MODE_REPEATER          (0x1 << 3)   /* Enable pull-down and pull-up resistor at resistor at pad (repeater mode) */
#define SCU_MODE_INACT             (0x2 << 3)   /* Disable pull-down and pull-up resistor at resistor at pad */
#define SCU_MODE_PULLDOWN          (0x3 << 3)   /* Enable pull-down resistor at pad */
#define SCU_MODE_HIGHSPEEDSLEW_EN  (0x1 << 5)   /* Enable high-speed slew */
#define SCU_MODE_INBUFF_EN         (0x1 << 6)   /* Enable Input buffer */
#define SCU_MODE_ZIF_DIS           (0x1 << 7)   /* Disable input glitch filter */
#define SCU_MODE_4MA_DRIVESTR      (0x0 << 8)   /* Normal drive: 4mA drive strength */
#define SCU_MODE_8MA_DRIVESTR      (0x1 << 8)   /* Medium drive: 8mA drive strength */
#define SCU_MODE_14MA_DRIVESTR     (0x2 << 8)   /* High drive: 14mA drive strength */
#define SCU_MODE_20MA_DRIVESTR     (0x3 << 8)   /* Ultra high- drive: 20mA drive strength */

#define SCU_MODE_FUNC0             0x0          /* Selects pin function 0 */
#define SCU_MODE_FUNC1             0x1          /* Selects pin function 1 */
#define SCU_MODE_FUNC2             0x2          /* Selects pin function 2 */
#define SCU_MODE_FUNC3             0x3          /* Selects pin function 3 */
#define SCU_MODE_FUNC4             0x4          /* Selects pin function 4 */
#define SCU_MODE_FUNC5             0x5          /* Selects pin function 5 */
#define SCU_MODE_FUNC6             0x6          /* Selects pin function 6 */
#define SCU_MODE_FUNC7             0x7          /* Selects pin function 7 */

/* Common SCU configurations */
#define SCU_PINIO_FAST             (SCU_MODE_INACT | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS)
#define SCU_PINIO_PULLUP           (SCU_MODE_INBUFF_EN)
#define SCU_PINIO_PULLDOWN         (SCU_MODE_PULLDOWN | SCU_MODE_INACT | SCU_MODE_INBUFF_EN)
#define SCU_PINIO_PULLNONE         (SCU_MODE_INACT | SCU_MODE_INBUFF_EN)

/* Calculate SCU offset and register address from group and pin number */
#define SCU_OFF(group, num)        ((group << 7) + (num << 2))
#define SCU_REG(group, num)        ((__IO uint32_t *)(LPC_SCU_BASE + SCU_OFF(group, num)))

/**
 * SCU function and mode selection definitions (old)
 * For backwards compatibility.
 */
#define MD_PUP                     (0x0 << 3)   /* Enable pull-up resistor at pad */
#define MD_BUK                     (0x1 << 3)   /* Enable pull-down and pull-up resistor at resistor at pad (repeater mode) */
#define MD_PLN                     (0x2 << 3)   /* Disable pull-down and pull-up resistor at resistor at pad */
#define MD_PDN                     (0x3 << 3)   /* Enable pull-down resistor at pad */
#define MD_EHS                     (0x1 << 5)   /* Enable fast slew rate */
#define MD_EZI                     (0x1 << 6)   /* Input buffer enable */
#define MD_ZI                      (0x1 << 7)   /* Disable input glitch filter */
#define MD_EHD0                    (0x1 << 8)   /* EHD driver strength low bit */
#define MD_EHD1                    (0x1 << 8)   /* EHD driver strength high bit */
#define MD_PLN_FAST                (MD_PLN | MD_EZI | MD_ZI | MD_EHS)
#define I2C0_STANDARD_FAST_MODE    (1 << 3 | 1 << 11)    /* Pin configuration for STANDARD/FAST mode I2C */
#define I2C0_FAST_MODE_PLUS        (2 << 1 | 1 << 3 | 1 << 7 | 1 << 10 | 1 << 11)    /* Pin configuration for Fast-mode Plus I2C */

#define FUNC0                      0x0          /* Pin function 0 */
#define FUNC1                      0x1          /* Pin function 1 */
#define FUNC2                      0x2          /* Pin function 2 */
#define FUNC3                      0x3          /* Pin function 3 */
#define FUNC4                      0x4          /* Pin function 4 */
#define FUNC5                      0x5          /* Pin function 5 */
#define FUNC6                      0x6          /* Pin function 6 */
#define FUNC7                      0x7          /* Pin function 7 */

#define PORT_OFFSET                0x80         /* Port offset definition */
#define PIN_OFFSET                 0x04         /* Pin offset definition */

/* Returns the SFSP register address in the SCU for a pin and port,
   recommend using (*(volatile int *) &LPC_SCU->SFSP[po][pi];) */
#define LPC_SCU_PIN(LPC_SCU_BASE, po, pi) \
                                   (*(volatile int *) ((LPC_SCU_BASE) + ((po) * 0x80) + ((pi) * 0x4))

/* Returns the address in the SCU for a SFSCLK clock register,
   recommend using (*(volatile int *) &LPC_SCU->SFSCLK[c];) */
#define LPC_SCU_CLK(LPC_SCU_BASE, c) \
                                   (*(volatile int *) ((LPC_SCU_BASE) +0xC00 + ((c) * 0x4)))

/* ---------------------------------------------------------------------------
 * GPIO pin interrupt register block structure
 */
#define LPC_GPIO_PIN_INT_BASE     0x40087000

typedef struct {                /* GPIO_PIN_INT Structure */
    __IO uint32_t  ISEL;        /* Pin Interrupt Mode register */
    __IO uint32_t  IENR;        /* Pin Interrupt Enable (Rising) register */
    __O  uint32_t  SIENR;       /* Set Pin Interrupt Enable (Rising) register */
    __O  uint32_t  CIENR;       /* Clear Pin Interrupt Enable (Rising) register */
    __IO uint32_t  IENF;        /* Pin Interrupt Enable Falling Edge / Active Level register */
    __O  uint32_t  SIENF;       /* Set Pin Interrupt Enable Falling Edge / Active Level register */
    __O  uint32_t  CIENF;       /* Clear Pin Interrupt Enable Falling Edge / Active Level address */
    __IO uint32_t  RISE;        /* Pin Interrupt Rising Edge register */
    __IO uint32_t  FALL;        /* Pin Interrupt Falling Edge register */
    __IO uint32_t  IST;         /* Pin Interrupt Status register */
} LPC_GPIOPININT_T;

typedef enum LPC_GPIOPININT_MODE {
    GPIOPININT_RISING_EDGE = 0x01,
    GPIOPININT_FALLING_EDGE = 0x02,
    GPIOPININT_ACTIVE_HIGH_LEVEL = 0x04,
    GPIOPININT_ACTIVE_LOW_LEVEL = 0x08
} LPC_GPIOPININT_MODE_T;

/* ---------------------------------------------------------------------------
 * GPIO grouped interrupt register block structure
 */
#define LPC_GPIO_GROUP_INT0_BASE  0x40088000
#define LPC_GPIO_GROUP_INT1_BASE  0x40089000

typedef struct {                /* GPIO_GROUP_INTn Structure */
    __IO uint32_t  CTRL;        /* GPIO grouped interrupt control register */
    __I  uint32_t  RESERVED0[7];
    __IO uint32_t  PORT_POL[8]; /* GPIO grouped interrupt port polarity register */
    __IO uint32_t  PORT_ENA[8]; /* GPIO grouped interrupt port m enable register */
} LPC_GPIOGROUPINT_T;

/* ---------------------------------------------------------------------------
 * Motor Control PWM register block structure
 */
#define LPC_MCPWM_BASE            0x400A0000

typedef struct {                /* MCPWM Structure        */
    __I  uint32_t  CON;         /* PWM Control read address */
    __O  uint32_t  CON_SET;     /* PWM Control set address */
    __O  uint32_t  CON_CLR;     /* PWM Control clear address */
    __I  uint32_t  CAPCON;      /* Capture Control read address */
    __O  uint32_t  CAPCON_SET;  /* Capture Control set address */
    __O  uint32_t  CAPCON_CLR;  /* Event Control clear address */
    __IO uint32_t TC[3];        /* Timer Counter register */
    __IO uint32_t LIM[3];       /* Limit register         */
    __IO uint32_t MAT[3];       /* Match register         */
    __IO uint32_t  DT;          /* Dead time register     */
    __IO uint32_t  CCP;         /* Communication Pattern register */
    __I  uint32_t CAP[3];       /* Capture register       */
    __I  uint32_t  INTEN;       /* Interrupt Enable read address */
    __O  uint32_t  INTEN_SET;   /* Interrupt Enable set address */
    __O  uint32_t  INTEN_CLR;   /* Interrupt Enable clear address */
    __I  uint32_t  CNTCON;      /* Count Control read address */
    __O  uint32_t  CNTCON_SET;  /* Count Control set address */
    __O  uint32_t  CNTCON_CLR;  /* Count Control clear address */
    __I  uint32_t  INTF;        /* Interrupt flags read address */
    __O  uint32_t  INTF_SET;    /* Interrupt flags set address */
    __O  uint32_t  INTF_CLR;    /* Interrupt flags clear address */
    __O  uint32_t  CAP_CLR;     /* Capture clear address  */
} LPC_MCPWM_T;

/* ---------------------------------------------------------------------------
 * I2C register block structure
 */
#define LPC_I2C0_BASE             0x400A1000
#define LPC_I2C1_BASE             0x400E0000

typedef struct {                /* I2C0 Structure         */
    __IO uint32_t CONSET;       /* I2C Control Set Register. When a one is written to a bit of this register, the corresponding bit in the I2C control register is set. Writing a zero has no effect on the corresponding bit in the I2C control register. */
    __I  uint32_t STAT;         /* I2C Status Register. During I2C operation, this register provides detailed status codes that allow software to determine the next action needed. */
    __IO uint32_t DAT;          /* I2C Data Register. During master or slave transmit mode, data to be transmitted is written to this register. During master or slave receive mode, data that has been received may be read from this register. */
    __IO uint32_t ADR0;         /* I2C Slave Address Register 0. Contains the 7-bit slave address for operation of the I2C interface in slave mode, and is not used in master mode. The least significant bit determines whether a slave responds to the General Call address. */
    __IO uint32_t SCLH;         /* SCH Duty Cycle Register High Half Word. Determines the high time of the I2C clock. */
    __IO uint32_t SCLL;         /* SCL Duty Cycle Register Low Half Word. Determines the low time of the I2C clock. SCLL and SCLH together determine the clock frequency generated by an I2C master and certain times used in slave mode. */
    __O  uint32_t CONCLR;       /* I2C Control Clear Register. When a one is written to a bit of this register, the corresponding bit in the I2C control register is cleared. Writing a zero has no effect on the corresponding bit in the I2C control register. */
    __IO uint32_t MMCTRL;       /* Monitor mode control register. */
    __IO uint32_t ADR1;         /* I2C Slave Address Register. Contains the 7-bit slave address for operation of the I2C interface in slave mode, and is not used in master mode. The least significant bit determines whether a slave responds to the General Call address. */
    __IO uint32_t ADR2;         /* I2C Slave Address Register. Contains the 7-bit slave address for operation of the I2C interface in slave mode, and is not used in master mode. The least significant bit determines whether a slave responds to the General Call address. */
    __IO uint32_t ADR3;         /* I2C Slave Address Register. Contains the 7-bit slave address for operation of the I2C interface in slave mode, and is not used in master mode. The least significant bit determines whether a slave responds to the General Call address. */
    __I  uint32_t DATA_BUFFER;  /* Data buffer register. The contents of the 8 MSBs of the DAT shift register will be transferred to the DATA_BUFFER automatically after every nine bits (8 bits of data plus ACK or NACK) has been received on the bus. */
    __IO uint32_t MASK[4];      /* I2C Slave address mask register */
} LPC_I2C_T;

/* ---------------------------------------------------------------------------
 * I2S register block structure
 */
#define LPC_I2S0_BASE             0x400A2000
#define LPC_I2S1_BASE             0x400A3000

typedef struct {                /* I2S Structure */
    __IO uint32_t DAO;          /* I2S Digital Audio Output Register. Contains control bits for the I2S transmit channel */
    __IO uint32_t DAI;          /* I2S Digital Audio Input Register. Contains control bits for the I2S receive channel */
    __O uint32_t TXFIFO;        /* I2S Transmit FIFO. Access register for the 8 x 32-bit transmitter FIFO */
    __I uint32_t RXFIFO;        /* I2S Receive FIFO. Access register for the 8 x 32-bit receiver FIFO */
    __I uint32_t STATE;         /* I2S Status Feedback Register. Contains status information about the I2S interface */
    __IO uint32_t DMA1;         /* I2S DMA Configuration Register 1. Contains control information for DMA request 1 */
    __IO uint32_t DMA2;         /* I2S DMA Configuration Register 2. Contains control information for DMA request 2 */
    __IO uint32_t IRQ;          /* I2S Interrupt Request Control Register. Contains bits that control how the I2S interrupt request is generated */
    __IO uint32_t TXRATE;       /* I2S Transmit MCLK divider. This register determines the I2S TX MCLK rate by specifying the value to divide PCLK by in order to produce MCLK */
    __IO uint32_t RXRATE;       /* I2S Receive MCLK divider. This register determines the I2S RX MCLK rate by specifying the value to divide PCLK by in order to produce MCLK */
    __IO uint32_t TXBITRATE;    /* I2S Transmit bit rate divider. This register determines the I2S transmit bit rate by specifying the value to divide TX_MCLK by in order to produce the transmit bit clock */
    __IO uint32_t RXBITRATE;    /* I2S Receive bit rate divider. This register determines the I2S receive bit rate by specifying the value to divide RX_MCLK by in order to produce the receive bit clock */
    __IO uint32_t TXMODE;       /* I2S Transmit mode control */
    __IO uint32_t RXMODE;       /* I2S Receive mode control */
} LPC_I2S_T;

/* ---------------------------------------------------------------------------
 * CCAN Controller Area Network register block structure
 */
#define LPC_C_CAN1_BASE           0x400A4000
#define LPC_C_CAN0_BASE           0x400E2000

typedef struct {    /* C_CAN message interface Structure       */
    __IO uint32_t IF_CMDREQ;    /* Message interface command request  */
    union {
        __IO uint32_t IF_CMDMSK_R; /* Message interface command mask (read direction) */
        __IO uint32_t IF_CMDMSK_W; /* Message interface command mask (write direction) */
    };

    __IO uint32_t IF_MSK1;      /* Message interface mask 1 */
    __IO uint32_t IF_MSK2;      /* Message interface mask 2 */
    __IO uint32_t IF_ARB1;      /* Message interface arbitration 1 */
    __IO uint32_t IF_ARB2;      /* Message interface arbitration 2 */
    __IO uint32_t IF_MCTRL;     /* Message interface message control */
    __IO uint32_t IF_DA1;       /* Message interface data A1 */
    __IO uint32_t IF_DA2;       /* Message interface data A2 */
    __IO uint32_t IF_DB1;       /* Message interface data B1 */
    __IO uint32_t IF_DB2;       /* Message interface data B2 */
    __I  uint32_t  RESERVED[13];
} LPC_CCAN_IF_T;

typedef struct {                /* C_CAN Structure       */
    __IO uint32_t CNTL;         /* CAN control            */
    __IO uint32_t STAT;         /* Status register        */
    __I  uint32_t EC;           /* Error counter          */
    __IO uint32_t BT;           /* Bit timing register    */
    __I  uint32_t INT;          /* Interrupt register     */
    __IO uint32_t TEST;         /* Test register          */
    __IO uint32_t BRPE;         /* Baud rate prescaler extension register */
    __I  uint32_t  RESERVED0;
    LPC_CCAN_IF_T IF[2];
    __I  uint32_t  RESERVED2[8];
    __I  uint32_t TXREQ1;       /* Transmission request 1 */
    __I  uint32_t TXREQ2;       /* Transmission request 2 */
    __I  uint32_t  RESERVED3[6];
    __I  uint32_t ND1;          /* New data 1             */
    __I  uint32_t ND2;          /* New data 2             */
    __I  uint32_t  RESERVED4[6];
    __I  uint32_t IR1;          /* Interrupt pending 1    */
    __I  uint32_t IR2;          /* Interrupt pending 2    */
    __I  uint32_t  RESERVED5[6];
    __I  uint32_t MSGV1;        /* Message valid 1        */
    __I  uint32_t MSGV2;        /* Message valid 2        */
    __I  uint32_t  RESERVED6[6];
    __IO uint32_t CLKDIV;       /* CAN clock divider register */
} LPC_CCAN_T;

/* ---------------------------------------------------------------------------
 * Repetitive Interrupt Timer register block structure
 */
#define LPC_RITIMER_BASE          0x400C0000

typedef struct {                /* RITIMER Structure      */
    __IO uint32_t  COMPVAL;     /* Compare register       */
    __IO uint32_t  MASK;        /* Mask register. This register holds the 32-bit mask value. A 1 written to any bit will force a compare on the corresponding bit of the counter and compare register. */
    __IO uint32_t  CTRL;        /* Control register.      */
    __IO uint32_t  COUNTER;     /* 32-bit counter         */
} LPC_RITIMER_T;

/* ---------------------------------------------------------------------------
 * Quadrature Encoder Interface register block structure
 */
#define LPC_QEI_BASE              0x400C6000

typedef struct {                /* QEI Structure          */
    __O  uint32_t  CON;         /* Control register       */
    __I  uint32_t  STAT;        /* Encoder status register */
    __IO uint32_t  CONF;        /* Configuration register */
    __I  uint32_t  POS;         /* Position register      */
    __IO uint32_t  MAXPOS;      /* Maximum position register */
    __IO uint32_t  CMPOS0;      /* position compare register 0 */
    __IO uint32_t  CMPOS1;      /* position compare register 1 */
    __IO uint32_t  CMPOS2;      /* position compare register 2 */
    __I  uint32_t  INXCNT;      /* Index count register   */
    __IO uint32_t  INXCMP0;     /* Index compare register 0 */
    __IO uint32_t  LOAD;        /* Velocity timer reload register */
    __I  uint32_t  TIME;        /* Velocity timer register */
    __I  uint32_t  VEL;         /* Velocity counter register */
    __I  uint32_t  CAP;         /* Velocity capture register */
    __IO uint32_t  VELCOMP;     /* Velocity compare register */
    __IO uint32_t  FILTERPHA;   /* Digital filter register on input phase A (QEI_A) */
    __IO uint32_t  FILTERPHB;   /* Digital filter register on input phase B (QEI_B) */
    __IO uint32_t  FILTERINX;   /* Digital filter register on input index (QEI_IDX) */
    __IO uint32_t  WINDOW;      /* Index acceptance window register */
    __IO uint32_t  INXCMP1;     /* Index compare register 1 */
    __IO uint32_t  INXCMP2;     /* Index compare register 2 */
    __I  uint32_t  RESERVED0[993];
    __O  uint32_t  IEC;         /* Interrupt enable clear register */
    __O  uint32_t  IES;         /* Interrupt enable set register */
    __I  uint32_t  INTSTAT;     /* Interrupt status register */
    __I  uint32_t  IE;          /* Interrupt enable register */
    __O  uint32_t  CLR;         /* Interrupt status clear register */
    __O  uint32_t  SET;         /* Interrupt status set register */
} LPC_QEI_T;

/* ---------------------------------------------------------------------------
 * Global Input Multiplexer Array (GIMA) register block structure
 */
#define LPC_GIMA_BASE             0x400C7000

typedef struct {                        /* GIMA Structure */
    __IO uint32_t  CAP0_IN[4][4];       /* Timer x CAP0_y capture input multiplexer (GIMA output ((x*4)+y)) */
    __IO uint32_t  CTIN_IN[8];          /* SCT CTIN_x capture input multiplexer (GIMA output (16+x)) */
    __IO uint32_t  VADC_TRIGGER_IN;     /* VADC trigger input multiplexer (GIMA output 24) */
    __IO uint32_t  EVENTROUTER_13_IN;   /* Event router input 13 multiplexer (GIMA output 25) */
    __IO uint32_t  EVENTROUTER_14_IN;   /* Event router input 14 multiplexer (GIMA output 26) */
    __IO uint32_t  EVENTROUTER_16_IN;   /* Event router input 16 multiplexer (GIMA output 27) */
    __IO uint32_t  ADCSTART0_IN;        /* ADC start0 input multiplexer (GIMA output 28) */
    __IO uint32_t  ADCSTART1_IN;        /* ADC start1 input multiplexer (GIMA output 29) */
} LPC_GIMA_T;

/* ---------------------------------------------------------------------------
 * DAC register block structure
 */
#define LPC_DAC_BASE              0x400E1000

typedef struct {            /* DAC Structure          */
    __IO uint32_t  CR;      /* DAC register. Holds the conversion data. */
    __IO uint32_t  CTRL;    /* DAC control register.  */
    __IO uint32_t  CNTVAL;  /* DAC counter value register. */
} LPC_DAC_T;

/* After the selected settling time after this field is written with a
 * new VALUE, the voltage on the AOUT pin (with respect to VSSA)
 * is VALUE/1024 ? VREF
 */
#define DAC_RANGE           0x3FF
#define DAC_SET(n)          ((uint32_t) ((n & DAC_RANGE) << 6))
#define DAC_GET(n)          ((uint32_t) ((n >> 6) & DAC_RANGE))
#define DAC_VALUE(n)        DAC_SET(n)
/* If this bit = 0: The settling time of the DAC is 1 microsecond max,
 * and the maximum current is 700 microAmpere
 * If this bit = 1: The settling time of the DAC is 2.5 microsecond
 * and the maximum current is 350 microAmpere
 */
#define DAC_BIAS_EN         ((uint32_t) (1 << 16))
/* Value to reload interrupt DMA counter */
#define DAC_CCNT_VALUE(n)   ((uint32_t) (n & 0xffff))

#define DAC_DBLBUF_ENA      ((uint32_t) (1 << 1))
#define DAC_CNT_ENA         ((uint32_t) (1 << 2))
#define DAC_DMA_ENA         ((uint32_t) (1 << 3))
#define DAC_DACCTRL_MASK    ((uint32_t) (0x0F))

/* Current option in DAC configuration option */
typedef enum DAC_CURRENT_OPT {
    DAC_MAX_UPDATE_RATE_1MHz = 0,    /* Shorter settling times and higher power consumption;
                                        allows for a maximum update rate of 1 MHz */
    DAC_MAX_UPDATE_RATE_400kHz        /* Longer settling times and lower power consumption;
                                        allows for a maximum update rate of 400 kHz */
} DAC_CURRENT_OPT_T;

/* ---------------------------------------------------------------------------
 * ADC register block structure
 */
#define LPC_ADC0_BASE             0x400E3000
#define LPC_ADC1_BASE             0x400E4000
#define ADC_ACC_10BITS

/* ---------------------------------------------------------------------------
 * 10 or 12-bit ADC register block structure
 */
typedef struct {                    /* ADCn Structure */
    __IO uint32_t CR;                /* A/D Control Register. The AD0CR register must be written to select the operating mode before A/D conversion can occur. */
    __I  uint32_t GDR;                /* A/D Global Data Register. Contains the result of the most recent A/D conversion. */
    __I  uint32_t RESERVED0;
    __IO uint32_t INTEN;            /* A/D Interrupt Enable Register. This register contains enable bits that allow the DONE flag of each A/D channel to be included or excluded from contributing to the generation of an A/D interrupt. */
    __I  uint32_t DR[8];            /* A/D Channel Data Register. This register contains the result of the most recent conversion completed on channel n. */
    __I  uint32_t STAT;                /* A/D Status Register. This register contains DONE and OVERRUN flags for all of the A/D channels, as well as the A/D interrupt flag. */
} LPC_ADC_T;

/* ADC register support bitfields and mask */
#define ADC_RANGE               0x3FF
#define ADC_DR_RESULT(n)        ((((n) >> 6) & 0x3FF))   /* Mask for getting the 10 bits ADC data read value */
#define ADC_CR_BITACC(n)        ((((n) & 0x7) << 17))    /* Number of ADC accuracy bits */
#define ADC_DR_DONE(n)          (((n) >> 31))            /* Mask for reading the ADC done status */
#define ADC_DR_OVERRUN(n)       ((((n) >> 30) & (1UL)))  /* Mask for reading the ADC overrun status */
#define ADC_CR_CH_SEL(n)        ((1UL << (n)))           /* Selects which of the AD0.0:7 pins is (are) to be sampled and converted */
#define ADC_CR_CLKDIV(n)        ((((n) & 0xFF) << 8))    /* The APB clock (PCLK) is divided by (this value plus one) to produce the clock for the A/D */
#define ADC_CR_BURST            ((1UL << 16))            /* Repeated conversions A/D enable bit */
#define ADC_CR_PDN              ((1UL << 21))            /* ADC convert is operational */
#define ADC_CR_START_MASK       ((7UL << 24))            /* ADC start mask bits */
#define ADC_CR_START_MODE_SEL(SEL)  ((SEL << 24))        /* Select Start Mode */
#define ADC_CR_START_NOW        ((1UL << 24))            /* Start conversion now */
#define ADC_CR_START_CTOUT15    ((2UL << 24))            /* Start conversion when the edge selected by bit 27 occurs on CTOUT_15 */
#define ADC_CR_START_CTOUT8     ((3UL << 24))            /* Start conversion when the edge selected by bit 27 occurs on CTOUT_8 */
#define ADC_CR_START_ADCTRIG0   ((4UL << 24))            /* Start conversion when the edge selected by bit 27 occurs on ADCTRIG0 */
#define ADC_CR_START_ADCTRIG1   ((5UL << 24))            /* Start conversion when the edge selected by bit 27 occurs on ADCTRIG1 */
#define ADC_CR_START_MCOA2      ((6UL << 24))            /* Start conversion when the edge selected by bit 27 occurs on Motocon PWM output MCOA2 */
#define ADC_CR_EDGE             ((1UL << 27))            /* Start conversion on a falling edge on the selected CAP/MAT signal */
#define ADC_CONFIG_MASK         (ADC_CR_CLKDIV(0xFF) | ADC_CR_BITACC(0x07) | ADC_CR_PDN)

/*    ADC status register used for IP drivers */
typedef enum ADC_STATUS {
    ADC_DR_DONE_STAT,   /* ADC data register staus */
    ADC_DR_OVERRUN_STAT,/* ADC data overrun staus */
    ADC_DR_ADINT_STAT   /* ADC interrupt status */
} ADC_STATUS_T;

/** Start mode, which controls the start of an A/D conversion when the BURST bit is 0. */
typedef enum ADC_START_MODE {
    ADC_NO_START = 0,
    ADC_START_NOW,          /* Start conversion now */
    ADC_START_ON_CTOUT15,   /* Start conversion when the edge selected by bit 27 occurs on CTOUT_15 */
    ADC_START_ON_CTOUT8,    /* Start conversion when the edge selected by bit 27 occurs on CTOUT_8 */
    ADC_START_ON_ADCTRIG0,  /* Start conversion when the edge selected by bit 27 occurs on ADCTRIG0 */
    ADC_START_ON_ADCTRIG1,  /* Start conversion when the edge selected by bit 27 occurs on ADCTRIG1 */
    ADC_START_ON_MCOA2      /* Start conversion when the edge selected by bit 27 occurs on Motocon PWM output MCOA2 */
} ADC_START_MODE_T;

/* ---------------------------------------------------------------------------
 * GPIO port register block structure
 */
#define LPC_GPIO_PORT_BASE        0x400F4000
#define LPC_GPIO0_BASE            (LPC_GPIO_PORT_BASE)
#define LPC_GPIO1_BASE            (LPC_GPIO_PORT_BASE + 0x04)
#define LPC_GPIO2_BASE            (LPC_GPIO_PORT_BASE + 0x08)
#define LPC_GPIO3_BASE            (LPC_GPIO_PORT_BASE + 0x0C)
#define LPC_GPIO4_BASE            (LPC_GPIO_PORT_BASE + 0x10)
#define LPC_GPIO5_BASE            (LPC_GPIO_PORT_BASE + 0x14)
#define LPC_GPIO6_BASE            (LPC_GPIO_PORT_BASE + 0x18)
#define LPC_GPIO7_BASE            (LPC_GPIO_PORT_BASE + 0x1C)

typedef struct {                /* GPIO_PORT Structure */
    __IO uint8_t B[128][32];    /* Offset 0x0000: Byte pin registers ports 0 to n; pins PIOn_0 to PIOn_31 */
    __IO uint32_t W[32][32];    /* Offset 0x1000: Word pin registers port 0 to n */
    __IO uint32_t DIR[32];      /* Offset 0x2000: Direction registers port n */
    __IO uint32_t MASK[32];     /* Offset 0x2080: Mask register port n */
    __IO uint32_t PIN[32];      /* Offset 0x2100: Portpin register port n */
    __IO uint32_t MPIN[32];     /* Offset 0x2180: Masked port register port n */
    __IO uint32_t SET[32];      /* Offset 0x2200: Write: Set register for port n Read: output bits for port n */
    __O  uint32_t CLR[32];      /* Offset 0x2280: Clear port n */
    __O  uint32_t NOT[32];      /* Offset 0x2300: Toggle port n */
} LPC_GPIO_T;

/* Calculate GPIO offset and port register address from group and pin number */
#define GPIO_OFF(port, pin)        ((port << 5) + pin)
#define GPIO_REG(port, pin)        ((__IO uint32_t *)(LPC_GPIO_PORT_BASE + 0x2000 + GPIO_OFF(port, pin)))

/* ---------------------------------------------------------------------------
 * SPI register block structure
 */
#define LPC_SPI_BASE              0x40100000

typedef struct {                /* SPI Structure          */
    __IO uint32_t  CR;          /* SPI Control Register. This register controls the operation of the SPI. */
    __I  uint32_t  SR;          /* SPI Status Register. This register shows the status of the SPI. */
    __IO uint32_t  DR;          /* SPI Data Register. This bi-directional register provides the transmit and receive data for the SPI. */
    __IO uint32_t  CCR;         /* SPI Clock Counter Register. This register controls the frequency of a master's SCK0. */
    __I  uint32_t  RESERVED0[3];
    __IO uint32_t  INT;         /* SPI Interrupt Flag. This register contains the interrupt flag for the SPI interface. */
} LPC_SPI_T;

/* SPI CFG Register BitMask */
#define SPI_CR_BITMASK       ((uint32_t) 0xFFC)
/* Enable of controlling the number of bits per transfer  */
#define SPI_CR_BIT_EN         ((uint32_t) (1 << 2))
/* Mask of field of bit controlling */
#define SPI_CR_BITS_MASK      ((uint32_t) 0xF00)
/* Set the number of bits per a transfer */
#define SPI_CR_BITS(n)        ((uint32_t) ((n << 8) & 0xF00))    /* n is in range 8-16 */
/* SPI Clock Phase Select*/
#define SPI_CR_CPHA_FIRST     ((uint32_t) (0))    /*Capture data on the first edge, Change data on the following edge*/
#define SPI_CR_CPHA_SECOND    ((uint32_t) (1 << 3))  /* Change data on the first edge, Capture data on the following edge*/
/* SPI Clock Polarity Select*/
#define SPI_CR_CPOL_LO        ((uint32_t) (0))    /* The rest state of the clock (between frames) is low.*/
#define SPI_CR_CPOL_HI        ((uint32_t) (1 << 4))  /* The rest state of the clock (between frames) is high.*/
/* SPI Slave Mode Select */
#define SPI_CR_SLAVE_EN       ((uint32_t) 0)
/* SPI Master Mode Select */
#define SPI_CR_MASTER_EN      ((uint32_t) (1 << 5))
/* SPI MSB First mode enable */
#define SPI_CR_MSB_FIRST_EN   ((uint32_t) 0)      /* Data will be transmitted and received in standard order (MSB first).*/
/* SPI LSB First mode enable */
#define SPI_CR_LSB_FIRST_EN   ((uint32_t) (1 << 6)) /* Data will be transmitted and received in reverse order (LSB first).*/
/* SPI interrupt enable */
#define SPI_CR_INT_EN         ((uint32_t) (1 << 7))
/* SPI STAT Register BitMask */
#define SPI_SR_BITMASK        ((uint32_t) 0xF8)
/* Slave abort Flag */
#define SPI_SR_ABRT           ((uint32_t) (1 << 3)) /* When 1, this bit indicates that a slave abort has occurred. */
/* Mode fault Flag */
#define SPI_SR_MODF           ((uint32_t) (1 << 4)) /* when 1, this bit indicates that a Mode fault error has occurred. */
/* Read overrun flag*/
#define SPI_SR_ROVR           ((uint32_t) (1 << 5)) /* When 1, this bit indicates that a read overrun has occurred. */
/* Write collision flag. */
#define SPI_SR_WCOL           ((uint32_t) (1 << 6)) /* When 1, this bit indicates that a write collision has occurred.. */
/* SPI transfer complete flag. */
#define SPI_SR_SPIF           ((uint32_t) (1 << 7)) /* When 1, this bit indicates when a SPI data transfer is complete.. */
/* SPI error flag */
#define SPI_SR_ERROR          (SPI_SR_ABRT | SPI_SR_MODF | SPI_SR_ROVR | SPI_SR_WCOL)
/* Enable SPI Test Mode */
#define SPI_TCR_TEST(n)       ((uint32_t) ((n & 0x3F) << 1))
/* SPI interrupt flag */
#define SPI_INT_SPIF          ((uint32_t) (1 << 0))
/* Receiver Data  */
#define SPI_DR_DATA(n)        ((uint32_t) ((n) & 0xFFFF))

/* SPI Mode*/
typedef enum LPC_SPI_MODE {
    SPI_MODE_MASTER = SPI_CR_MASTER_EN, /* Master Mode */
    SPI_MODE_SLAVE = SPI_CR_SLAVE_EN,   /* Slave Mode */
} LPC_SPI_MODE_T;

/* SPI Clock Mode*/
typedef enum LPC_SPI_CLOCK_MODE {
    SPI_CLOCK_CPHA0_CPOL0 = SPI_CR_CPOL_LO | SPI_CR_CPHA_FIRST,     /* CPHA = 0, CPOL = 0 */
    SPI_CLOCK_CPHA0_CPOL1 = SPI_CR_CPOL_HI | SPI_CR_CPHA_FIRST,     /* CPHA = 0, CPOL = 1 */
    SPI_CLOCK_CPHA1_CPOL0 = SPI_CR_CPOL_LO | SPI_CR_CPHA_SECOND,    /* CPHA = 1, CPOL = 0 */
    SPI_CLOCK_CPHA1_CPOL1 = SPI_CR_CPOL_HI | SPI_CR_CPHA_SECOND,    /* CPHA = 1, CPOL = 1 */
    SPI_CLOCK_MODE0 = SPI_CLOCK_CPHA0_CPOL0, /* alias */
    SPI_CLOCK_MODE1 = SPI_CLOCK_CPHA1_CPOL0, /* alias */
    SPI_CLOCK_MODE2 = SPI_CLOCK_CPHA0_CPOL1, /* alias */
    SPI_CLOCK_MODE3 = SPI_CLOCK_CPHA1_CPOL1, /* alias */
} LPC_SPI_CLOCK_MODE_T;

/* SPI Data Order Mode*/
typedef enum LPC_SPI_DATA_ORDER {
    SPI_DATA_MSB_FIRST = SPI_CR_MSB_FIRST_EN,     /* Standard Order */
    SPI_DATA_LSB_FIRST = SPI_CR_LSB_FIRST_EN,     /* Reverse Order */
} LPC_SPI_DATA_ORDER_T;

/* ---------------------------------------------------------------------------
 * Serial GPIO register block structure
 */
#define LPC_SGPIO_BASE            0x40101000

typedef struct {                        /* SGPIO Structure        */
    __IO uint32_t  OUT_MUX_CFG[16];     /* Pin multiplexer configurationregisters. */
    __IO uint32_t  SGPIO_MUX_CFG[16];   /* SGPIO multiplexer configuration registers. */
    __IO uint32_t  SLICE_MUX_CFG[16];   /* Slice multiplexer configuration registers. */
    __IO uint32_t  REG[16];             /* Slice data registers. Eachtime COUNT0 reaches 0x0 the register shifts loading bit 31 withdata captured from DIN(n). DOUT(n) is set to REG(0) */
    __IO uint32_t  REG_SS[16];          /* Slice data shadow registers. Each time POSreaches 0x0 the contents of REG_SS is exchanged with the contentof REG */
    __IO uint32_t  PRESET[16];          /* Reload valueof COUNT0, loaded when COUNT0 reaches 0x0 */
    __IO uint32_t  COUNT[16];           /* Down counter, counts down each clock cycle. */
    __IO uint32_t  POS[16];             /* Each time COUNT0 reaches 0x0 */
    __IO uint32_t  MASK_A;              /* Mask for pattern match function of slice A */
    __IO uint32_t  MASK_H;              /* Mask for pattern match function of slice H */
    __IO uint32_t  MASK_I;              /* Mask for pattern match function of slice I */
    __IO uint32_t  MASK_P;              /* Mask for pattern match function of slice P */
    __I  uint32_t  GPIO_INREG;          /* GPIO input status register */
    __IO uint32_t  GPIO_OUTREG;         /* GPIO output control register */
    __IO uint32_t  GPIO_OENREG;         /* GPIO OE control register */
    __IO uint32_t  CTRL_ENABLED;        /* Enables the slice COUNT counter */
    __IO uint32_t  CTRL_DISABLED;       /* Disables the slice COUNT counter */
    __I  uint32_t  RESERVED0[823];
    __O  uint32_t  CLR_EN_0;            /* Shift clock interrupt clear mask */
    __O  uint32_t  SET_EN_0;            /* Shift clock interrupt set mask */
    __I  uint32_t  ENABLE_0;            /* Shift clock interrupt enable */
    __I  uint32_t  STATUS_0;            /* Shift clock interrupt status */
    __O  uint32_t  CTR_STATUS_0;        /* Shift clock interrupt clear status */
    __O  uint32_t  SET_STATUS_0;        /* Shift clock interrupt set status */
    __I  uint32_t  RESERVED1[2];
    __O  uint32_t  CLR_EN_1;            /* Capture clock interrupt clear mask */
    __O  uint32_t  SET_EN_1;            /* Capture clock interrupt set mask */
    __I  uint32_t  ENABLE_1;            /* Capture clock interrupt enable */
    __I  uint32_t  STATUS_1;            /* Capture clock interrupt status */
    __O  uint32_t  CTR_STATUS_1;        /* Capture clock interrupt clear status */
    __O  uint32_t  SET_STATUS_1;        /* Capture clock interrupt set status */
    __I  uint32_t  RESERVED2[2];
    __O  uint32_t  CLR_EN_2;            /* Pattern match interrupt clear mask */
    __O  uint32_t  SET_EN_2;            /* Pattern match interrupt set mask */
    __I  uint32_t  ENABLE_2;            /* Pattern match interrupt enable */
    __I  uint32_t  STATUS_2;            /* Pattern match interrupt status */
    __O  uint32_t  CTR_STATUS_2;        /* Pattern match interrupt clear status */
    __O  uint32_t  SET_STATUS_2;        /* Pattern match interrupt set status */
    __I  uint32_t  RESERVED3[2];
    __O  uint32_t  CLR_EN_3;            /* Input interrupt clear mask */
    __O  uint32_t  SET_EN_3;            /* Input bit match interrupt set mask */
    __I  uint32_t  ENABLE_3;            /* Input bit match interrupt enable */
    __I  uint32_t  STATUS_3;            /* Input bit match interrupt status */
    __O  uint32_t  CTR_STATUS_3;        /* Input bit match interrupt clear status */
    __O  uint32_t  SET_STATUS_3;        /* Shift clock interrupt set status */
} LPC_SGPIO_T;

/* End of section using anonymous unions */
#if defined(__ARMCC_VERSION)
  #pragma pop
#elif defined(__CWCC__)
  #pragma pop
#elif defined(__IAR_SYSTEMS_ICC__)
  //#pragma pop // FIXME not usable for IAR
#else /* defined(__GNUC__) and others */
  /* Leave anonymous unions enabled */
#endif

/* ---------------------------------------------------------------------------
 * LPC43xx Peripheral register set declarations
 */
#define LPC_SCT               ((LPC_SCT_T           *) LPC_SCT_BASE)
#define LPC_GPDMA             ((LPC_GPDMA_T         *) LPC_GPDMA_BASE)
#define LPC_SPIFI             ((LPC_SPIFI_T         *) LPC_SPIFI_BASE)
#define LPC_SDMMC             ((LPC_SDMMC_T         *) LPC_SDMMC_BASE)
#define LPC_EMC               ((LPC_EMC_T           *) LPC_EMC_BASE)
#define LPC_USB0              ((LPC_USBHS_T         *) LPC_USB0_BASE)
#define LPC_USB1              ((LPC_USBHS_T         *) LPC_USB1_BASE)
#define LPC_LCD               ((LPC_LCD_T           *) LPC_LCD_BASE)
#define LPC_EEPROM            ((LPC_EEPROM_T        *) LPC_EEPROM_BASE)
#define LPC_ETHERNET          ((LPC_ENET_T          *) LPC_ETHERNET_BASE)
#define LPC_ATIMER            ((LPC_ATIMER_T        *) LPC_ATIMER_BASE)
#define LPC_REGFILE           ((LPC_REGFILE_T       *) LPC_REGFILE_BASE)
#define LPC_PMC               ((LPC_PMC_T           *) LPC_PMC_BASE)
#define LPC_CREG              ((LPC_CREG_T          *) LPC_CREG_BASE)
#define LPC_EVRT              ((LPC_EVRT_T          *) LPC_EVRT_BASE)
#define LPC_RTC               ((LPC_RTC_T           *) LPC_RTC_BASE)
#define LPC_CGU               ((LPC_CGU_T           *) LPC_CGU_BASE)
#define LPC_CCU1              ((LPC_CCU1_T          *) LPC_CCU1_BASE)
#define LPC_CCU2              ((LPC_CCU2_T          *) LPC_CCU2_BASE)
#define LPC_RGU               ((LPC_RGU_T           *) LPC_RGU_BASE)
#define LPC_WWDT              ((LPC_WWDT_T          *) LPC_WWDT_BASE)
#define LPC_USART0            ((LPC_USART_T         *) LPC_USART0_BASE)
#define LPC_USART2            ((LPC_USART_T         *) LPC_USART2_BASE)
#define LPC_USART3            ((LPC_USART_T         *) LPC_USART3_BASE)
#define LPC_UART1             ((LPC_USART_T         *) LPC_UART1_BASE)
#define LPC_SSP0              ((LPC_SSP_T           *) LPC_SSP0_BASE)
#define LPC_SSP1              ((LPC_SSP_T           *) LPC_SSP1_BASE)
#define LPC_TIMER0            ((LPC_TIMER_T         *) LPC_TIMER0_BASE)
#define LPC_TIMER1            ((LPC_TIMER_T         *) LPC_TIMER1_BASE)
#define LPC_TIMER2            ((LPC_TIMER_T         *) LPC_TIMER2_BASE)
#define LPC_TIMER3            ((LPC_TIMER_T         *) LPC_TIMER3_BASE)
#define LPC_SCU               ((LPC_SCU_T           *) LPC_SCU_BASE)
#define LPC_GPIO_PIN_INT      ((LPC_GPIOPININT_T    *) LPC_GPIO_PIN_INT_BASE)
#define LPC_GPIO_GROUP_INT0   ((IP_GPIOGROUPINT_T   *) LPC_GPIO_GROUP_INT0_BASE)
#define LPC_GPIO_GROUP_INT1   ((IP_GPIOGROUPINT_T   *) LPC_GPIO_GROUP_INT1_BASE)
#define LPC_MCPWM             ((LPC_MCPWM_T         *) LPC_MCPWM_BASE)
#define LPC_I2C0              ((LPC_I2C_T           *) LPC_I2C0_BASE)
#define LPC_I2C1              ((LPC_I2C_T           *) LPC_I2C1_BASE)
#define LPC_I2S0              ((LPC_I2S_T           *) LPC_I2S0_BASE)
#define LPC_I2S1              ((LPC_I2S_T           *) LPC_I2S1_BASE)
#define LPC_C_CAN1            ((LPC_CCAN_T          *) LPC_C_CAN1_BASE)
#define LPC_RITIMER           ((LPC_RITIMER_T       *) LPC_RITIMER_BASE)
#define LPC_QEI               ((LPC_QEI_T           *) LPC_QEI_BASE)
#define LPC_GIMA              ((LPC_GIMA_T          *) LPC_GIMA_BASE)
#define LPC_DAC               ((LPC_DAC_T           *) LPC_DAC_BASE)
#define LPC_C_CAN0            ((LPC_CCAN_T          *) LPC_C_CAN0_BASE)
#define LPC_ADC0              ((LPC_ADC_T           *) LPC_ADC0_BASE)
#define LPC_ADC1              ((LPC_ADC_T           *) LPC_ADC1_BASE)
#define LPC_GPIO_PORT         ((LPC_GPIO_T          *) LPC_GPIO_PORT_BASE)
#define LPC_GPIO0             ((LPC_GPIO_T          *) LPC_GPIO0_BASE)
#define LPC_GPIO1             ((LPC_GPIO_T          *) LPC_GPIO1_BASE)
#define LPC_GPIO2             ((LPC_GPIO_T          *) LPC_GPIO2_BASE)
#define LPC_GPIO3             ((LPC_GPIO_T          *) LPC_GPIO3_BASE)
#define LPC_GPIO4             ((LPC_GPIO_T          *) LPC_GPIO4_BASE)
#define LPC_GPIO5             ((LPC_GPIO_T          *) LPC_GPIO5_BASE)
#define LPC_GPIO6             ((LPC_GPIO_T          *) LPC_GPIO6_BASE)
#define LPC_GPIO7             ((LPC_GPIO_T          *) LPC_GPIO7_BASE)
#define LPC_SPI               ((LPC_SPI_T           *) LPC_SPI_BASE)
#define LPC_SGPIO             ((LPC_SGPIO_T         *) LPC_SGPIO_BASE)

#ifdef __cplusplus
}
#endif

#endif /* __LPC43XX_H */
