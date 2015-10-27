/*
 * @brief LPC43xx System Initialization
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
 * @par
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
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 *
 * Modified by Micromint USA <support@micromint.com>
 */
#include "LPC43xx.h"

#define COUNT_OF(a) (sizeof(a)/sizeof(a[0]))

/* Clock variables */
#if (CLOCK_SETUP)
uint32_t SystemCoreClock = MAX_CLOCK_FREQ;
#else
uint32_t SystemCoreClock = CRYSTAL_MAIN_FREQ_IN;
#endif

#if !defined(CORE_M0)
/* SCU pin definitions for pin muxing */
typedef struct {
    __IO uint32_t *reg; /* SCU register address */
    uint16_t mode;      /* SCU pin mode and function */
} PINMUX_GRP_T;

/* Pins to initialize before clocks are configured */
static const PINMUX_GRP_T pre_clock_mux[] = {
    /* SPIFI pins */
    {SCU_REG(0x3, 3), (SCU_PINIO_FAST | 0x3)},  /* P3_3 SPIFI CLK */
    {SCU_REG(0x3, 4), (SCU_PINIO_FAST | 0x3)},  /* P3_4 SPIFI D3  */
    {SCU_REG(0x3, 5), (SCU_PINIO_FAST | 0x3)},  /* P3_5 SPIFI D2  */
    {SCU_REG(0x3, 6), (SCU_PINIO_FAST | 0x3)},  /* P3_6 SPIFI D1  */
    {SCU_REG(0x3, 7), (SCU_PINIO_FAST | 0x3)},  /* P3_7 SPIFI D0  */
    {SCU_REG(0x3, 8), (SCU_PINIO_FAST | 0x3)}   /* P3_8 SPIFI CS/SSEL */
};

/* Pins to initialize after clocks are configured */
static const PINMUX_GRP_T post_clock_mux[] = {
    /* Boot pins */
    {SCU_REG(0x1, 1), (SCU_PINIO_FAST | 0x0)},  /* P1_1  BOOT0 */
    {SCU_REG(0x1, 2), (SCU_PINIO_FAST | 0x0)},  /* P1_2  BOOT1 */
    {SCU_REG(0x2, 8), (SCU_PINIO_FAST | 0x0)},  /* P2_8  BOOT2 */
    {SCU_REG(0x2, 9), (SCU_PINIO_FAST | 0x0)},  /* P2_9  BOOT3 */
    /* Micromint Bambino 200/210 */
    {SCU_REG(0x6, 11), (SCU_PINIO_FAST | 0x0)}, /* P6_11 LED1 */
    {SCU_REG(0x2, 5), (SCU_PINIO_FAST | 0x0)},  /* P2_5  LED2 */
    {SCU_REG(0x2, 7), (SCU_PINIO_FAST | 0x0)},  /* P2_7  BTN1 */
    /* Micromint Bambino 210 */
    {SCU_REG(0x6, 1), (SCU_PINIO_FAST | 0x0)},  /* P6_1  LED3 */
    {SCU_REG(0x6, 2), (SCU_PINIO_FAST | 0x0)},  /* P6_2  LED4 */
};

#if (CLOCK_SETUP)
/* Structure for initial base clock states */
struct CLK_BASE_STATES {
    CGU_BASE_CLK_T clk; /* Base clock */
    CGU_CLKIN_T clkin;  /* Base clock source */
    uint8_t powerdn;    /* Set to 1 if base clock is initially powered down */
};

/* Initial base clock states are mostly on */
static const struct CLK_BASE_STATES clock_states[] = {
    {CLK_BASE_SAFE, CLKIN_IRC, 0},
    {CLK_BASE_APB1, CLKIN_MAINPLL, 0},
    {CLK_BASE_APB3, CLKIN_MAINPLL, 0},
    {CLK_BASE_USB0, CLKIN_USBPLL, 1},
    {CLK_BASE_PERIPH, CLKIN_MAINPLL, 0},
    {CLK_BASE_SPI, CLKIN_MAINPLL, 0},
    {CLK_BASE_PHY_TX, CLKIN_ENET_TX, 0},
#if defined(USE_RMII)
    {CLK_BASE_PHY_RX, CLKIN_ENET_TX, 0},
#else
    {CLK_BASE_PHY_RX, CLKIN_ENET_RX, 0},
#endif
    {CLK_BASE_SDIO, CLKIN_MAINPLL, 0},
    {CLK_BASE_SSP0, CLKIN_IDIVC, 0},
    {CLK_BASE_SSP1, CLKIN_IDIVC, 0},
    {CLK_BASE_UART0, CLKIN_MAINPLL, 0},
    {CLK_BASE_UART1, CLKIN_MAINPLL, 0},
    {CLK_BASE_UART2, CLKIN_MAINPLL, 0},
    {CLK_BASE_UART3, CLKIN_MAINPLL, 0},
    {CLK_BASE_OUT, CLKINPUT_PD, 0},
    {CLK_BASE_APLL, CLKINPUT_PD, 0},
    {CLK_BASE_CGU_OUT0, CLKINPUT_PD, 0},
    {CLK_BASE_CGU_OUT1, CLKINPUT_PD, 0},

    /* Clocks derived from dividers */
    {CLK_BASE_LCD, CLKIN_IDIVC, 0},
    {CLK_BASE_USB1, CLKIN_IDIVD, 1}
};
#endif /* defined(CLOCK_SETUP) */

/* Local functions */
static uint32_t SystemGetMainPLLHz(void);
static void SystemSetupClock(void);
static void SystemSetupPins(const PINMUX_GRP_T *mux, uint32_t n);
static void SystemSetupMemory(void);
static void WaitUs(uint32_t us);

#endif /* !defined(CORE_M0) */

/*
 * SystemInit() - Initialize the system
 */
void SystemInit(void)
{
#if !defined(CORE_M0)

    /* Initialize vector table in flash */
#if defined(__ARMCC_VERSION)
    extern void *__Vectors;

    SCB->VTOR = (unsigned int) &__Vectors;
#elif defined(__IAR_SYSTEMS_ICC__)
    extern void *__vector_table;

    SCB->VTOR = (unsigned int) &__vector_table;
#elif defined(TOOLCHAIN_GCC_ARM)
    extern void *__isr_vector;

    SCB->VTOR = (unsigned int) &__isr_vector;
#else /* defined(__GNUC__) and others */
    extern void *g_pfnVectors;

    SCB->VTOR = (unsigned int) &g_pfnVectors;
#endif

#if defined(__FPU_PRESENT) && __FPU_PRESENT == 1
    /* Initialize floating point */
    fpuInit();
#endif

    SystemSetupPins(pre_clock_mux, COUNT_OF(pre_clock_mux)); /* Configure pins */
    SystemSetupClock();   /* Configure processor and peripheral clocks */
    SystemSetupPins(post_clock_mux, COUNT_OF(post_clock_mux)); /* Configure pins */
    SystemSetupMemory();  /* Configure external memory */
#endif /* !defined(CORE_M0) */

    SystemCoreClockUpdate(); /* Update SystemCoreClock variable */
}

/*
 * SystemCoreClockUpdate() - Update SystemCoreClock variable
 */
void SystemCoreClockUpdate(void)
{
    uint32_t reg, div, rate;

    /* Get main PLL rate */
    rate = SystemGetMainPLLHz();

    /* Get clock divider */
    reg = LPC_CCU1->CLKCCU[CLK_MX_MXCORE].CFG;
    if (((reg >> 5) & 0x7) == 0) {
        div = 1;
    }
    else {
        div = 2;
    }
    rate = rate / div;

    SystemCoreClock = rate;
}

/* Returns the frequency of the main PLL */
uint32_t SystemGetMainPLLHz(void)
{
    uint32_t PLLReg = LPC_CGU->PLL1_CTRL;
    uint32_t freq = CRYSTAL_MAIN_FREQ_IN;
    uint32_t msel, nsel, psel, direct, fbsel;
    uint32_t m, n, p;
    const uint8_t ptab[] = {1, 2, 4, 8};

    msel = (PLLReg >> 16) & 0xFF;
    nsel = (PLLReg >> 12) & 0x3;
    psel = (PLLReg >> 8) & 0x3;
    direct = (PLLReg >> 7) & 0x1;
    fbsel = (PLLReg >> 6) & 0x1;

    m = msel + 1;
    n = nsel + 1;
    p = ptab[psel];

    if (direct || fbsel) {
        return m * (freq / n);
    }

    return (m / (2 * p)) * (freq / n);
}

#if !defined(CORE_M0)
/*
 * SystemSetupClock() - Set processor and peripheral clocks
 *
 *    Clock       Frequency    Source
 * CLK_BASE_MX     204 MHz    CLKIN_MAINPLL            (CLKIN_PLL1)
 * CLK_BASE_SPIFI  102 MHz    CLKIN_IDIVE
 * CLK_BASE_USB0   480 MHz    CLKIN_USBPLL  (Disabled) (CLKIN_PLL0USB)
 * CLK_BASE_USB1    60 MHz    CLKIN_IDIVE   (Disabled)
 *                 120 MHz    CLKIN_IDIVD   (Disabled)
 *
 *                  12 MHz    CLKIN_IDIVB
 *                  12 MHz    CLKIN_IDIVC
 *
 */
void SystemSetupClock(void)
{
#if (CLOCK_SETUP)
    uint32_t i;

    /* Switch main clock to Internal RC (IRC) while setting up PLL1 */
    LPC_CGU->BASE_CLK[CLK_BASE_MX] = (1 << 11) | (CLKIN_IRC << 24);
    /* Set prescaler/divider on SSP1 assuming 204 MHz clock */
    LPC_SSP1->CR1 &= ~(1 << 1);
    LPC_SSP1->CPSR = 0x0002;
    LPC_SSP1->CR0 = 0x00006507;
    LPC_SSP1->CR1 |= (1 << 1);

    /* Enable the oscillator and wait 100 us */
    LPC_CGU->XTAL_OSC_CTRL = 0;
    WaitUs(100);

#if (SPIFI_INIT)
    /* Setup SPIFI control register and no-opcode mode */
    LPC_SPIFI->CTRL = (0x100 << 0) | (1 << 16) | (1 << 29) | (1 << 30);
    LPC_SPIFI->IDATA = 0xA5;
    /* Switch IDIVE clock to IRC and connect to SPIFI clock */
    LPC_CGU->IDIV_CTRL[CLK_IDIV_E] = ((1 << 11) | (CLKIN_IRC << 24));
    LPC_CGU->BASE_CLK[CLK_BASE_SPIFI] = ((1 << 11) | (CLKIN_IDIVE << 24));
#endif /* SPIFI_INIT */

    /* Configure PLL1 (MAINPLL) for main clock */
    LPC_CGU->PLL1_CTRL |= 1; /* Power down PLL1 */

    /* Change PLL1 to 108 Mhz (msel=9, 12 MHz*9=108 MHz) */
    LPC_CGU->PLL1_CTRL = (1 << 7) | (0 << 8) | (1 << 11) | (0 << 12) | (8 << 16)
                         | (CLKIN_MAINPLL << 24);
    while (!(LPC_CGU->PLL1_STAT & 1)); /* Wait for PLL1 to lock */
    WaitUs(100);

    /* Change PLL1 to 204 Mhz (msel=17, 12 MHz*17=204 MHz) */
    LPC_CGU->PLL1_CTRL = (1 << 7) | (0 << 8) | (1 << 11) | (0 << 12) | (16 << 16)
                         | (CLKIN_MAINPLL << 24);
    while (!(LPC_CGU->PLL1_STAT & 1)); /* Wait for PLL1 to lock */

    /* Connect main clock to PLL1 */
    LPC_CGU->BASE_CLK[CLK_BASE_MX] = (1 << 11) | (CLKIN_MAINPLL << 24);

    /* Set USB PLL dividers for 480 MHz (for USB0) */
    LPC_CGU->PLL[CGU_USB_PLL].PLL_MDIV = 0x06167FFA;
    LPC_CGU->PLL[CGU_USB_PLL].PLL_NP_DIV = 0x00302062;
    LPC_CGU->PLL[CGU_USB_PLL].PLL_CTRL = 0x0000081D | (CLKIN_CRYSTAL << 24);

    /* Set IDIVE clock to PLL1/2 = 102 MHz */
    LPC_CGU->IDIV_CTRL[CLK_IDIV_E] = (1 << 2) | (1 << 11) | (CLKIN_MAINPLL << 24); /* PLL1/2 */

    /* Set IDIVD clock to ((USBPLL/4) / 2) = 60 MHz (for USB1) */
    LPC_CGU->IDIV_CTRL[CLK_IDIV_A] = (3 << 2) | (1 << 11) | (CLKIN_USBPLL << 24); /* USBPLL/4 */
    LPC_CGU->IDIV_CTRL[CLK_IDIV_D] = (1 << 2) | (1 << 11) | (CLKIN_IDIVA << 24); /* IDIVA/2 */

    /* Configure remaining integer dividers */
    LPC_CGU->IDIV_CTRL[CLK_IDIV_B] = (0 << 2) | (1 << 11) | (CLKIN_IRC << 24); /* IRC */
    LPC_CGU->IDIV_CTRL[CLK_IDIV_C] = (1 << 2) | (1 << 11) | (CLKIN_MAINPLL << 24); /* PLL1/2 */

    /* Connect base clocks */
    for (i = 0; i < COUNT_OF(clock_states); i++) {
        LPC_CGU->BASE_CLK[clock_states[i].clk] =
                         ( clock_states[i].powerdn << 0)
                         | (1 << 11) | (clock_states[i].clkin << 24);
    }
#endif /* CLOCK_SETUP */
    /* Reset peripherals */
    LPC_RGU->RESET_CTRL0 = 0x105F0000;
    LPC_RGU->RESET_CTRL1 = 0x01DFF7FF;
}

/*
 * SystemSetupPins() - Configure MCU pins
 */
void SystemSetupPins(const PINMUX_GRP_T *mux, uint32_t n)
{
    uint32_t i;

    for (i = 0; i < n; i++) {
        *(mux[i].reg) = mux[i].mode;
    }
}

/*
 * SystemSetupMemory() - Configure external memory
 */
void SystemSetupMemory(void)
{
#if (MEMORY_SETUP)
    /* None required for boards without external memory */
#endif /* MEMORY_SETUP */
}

#if defined(__FPU_PRESENT) && __FPU_PRESENT == 1
/*
 * fpuInit() - Early initialization of the FPU
 */
void fpuInit(void)
{
   /*
    * from ARM TRM manual:
    *   ; CPACR is located at address 0xE000ED88
    *   LDR.W R0, =0xE000ED88
    *   ; Read CPACR
    *   LDR R1, [R0]
    *   ; Set bits 20-23 to enable CP10 and CP11 coprocessors
    *   ORR R1, R1, #(0xF << 20)
    *   ; Write back the modified value to the CPACR
    *   STR R1, [R0]
    */

    volatile uint32_t *regCpacr = (uint32_t *) LPC_CPACR;
    volatile uint32_t *regMvfr0 = (uint32_t *) SCB_MVFR0;
    volatile uint32_t *regMvfr1 = (uint32_t *) SCB_MVFR1;
    volatile uint32_t Cpacr;
    volatile uint32_t Mvfr0;
    volatile uint32_t Mvfr1;
    char vfpPresent = 0;

    Mvfr0 = *regMvfr0;
    Mvfr1 = *regMvfr1;

    vfpPresent = ((SCB_MVFR0_RESET == Mvfr0) && (SCB_MVFR1_RESET == Mvfr1));

    if (vfpPresent) {
        Cpacr = *regCpacr;
        Cpacr |= (0xF << 20);
        *regCpacr = Cpacr;  /* enable CP10 and CP11 for full access */
    }
}
#endif /* defined(__FPU_PRESENT) && __FPU_PRESENT == 1 */

/* Approximate delay function */
#define CPU_NANOSEC(x)  (((uint64_t) (x) * SystemCoreClock) / 1000000000)

static void WaitUs(uint32_t us)
{
    volatile uint32_t  cyc = us * CPU_NANOSEC(1000) / 4;
    while (cyc--)
        ;
}

#endif /* !defined(CORE_M0) */
