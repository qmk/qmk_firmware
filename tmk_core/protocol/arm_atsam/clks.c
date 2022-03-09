/*
Copyright 2018 Massdrop Inc.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "arm_atsam_protocol.h"

#include <string.h>

volatile clk_t    system_clks;
volatile uint64_t ms_clk;
uint32_t          usec_delay_mult;
#define USEC_DELAY_LOOP_CYCLES 3 // Sum of instruction cycles in us delay loop

const uint32_t sercom_apbbase[] = {(uint32_t)SERCOM0, (uint32_t)SERCOM1, (uint32_t)SERCOM2, (uint32_t)SERCOM3, (uint32_t)SERCOM4, (uint32_t)SERCOM5};
const uint8_t  sercom_pchan[]   = {7, 8, 23, 24, 34, 35};

#define USE_DPLL_IND 0
#define USE_DPLL_DEF GCLK_SOURCE_DPLL0

void CLK_oscctrl_init(void) {
    Oscctrl *posctrl = OSCCTRL;
    Gclk *   pgclk   = GCLK;

    DBGC(DC_CLK_OSC_INIT_BEGIN);

    // default setup on por
    system_clks.freq_dfll    = FREQ_DFLL_DEFAULT;
    system_clks.freq_gclk[0] = system_clks.freq_dfll;

    // configure and startup 16MHz xosc0
    posctrl->XOSCCTRL[0].bit.ENABLE   = 0;
    posctrl->XOSCCTRL[0].bit.STARTUP  = 0xD;
    posctrl->XOSCCTRL[0].bit.ENALC    = 1;
    posctrl->XOSCCTRL[0].bit.IMULT    = 5;
    posctrl->XOSCCTRL[0].bit.IPTAT    = 3;
    posctrl->XOSCCTRL[0].bit.ONDEMAND = 0;
    posctrl->XOSCCTRL[0].bit.XTALEN   = 1;
    posctrl->XOSCCTRL[0].bit.ENABLE   = 1;
    while (posctrl->STATUS.bit.XOSCRDY0 == 0) {
        DBGC(DC_CLK_OSC_INIT_XOSC0_SYNC);
    }
    system_clks.freq_xosc0 = FREQ_XOSC0;

    // configure and startup DPLL
    posctrl->Dpll[USE_DPLL_IND].DPLLCTRLA.bit.ENABLE = 0;
    while (posctrl->Dpll[USE_DPLL_IND].DPLLSYNCBUSY.bit.ENABLE) {
        DBGC(DC_CLK_OSC_INIT_DPLL_SYNC_DISABLE);
    }
    posctrl->Dpll[USE_DPLL_IND].DPLLCTRLB.bit.REFCLK = 2;         // select XOSC0 (16MHz)
    posctrl->Dpll[USE_DPLL_IND].DPLLCTRLB.bit.DIV    = 7;         // 16 MHz / (2 * (7 + 1)) = 1 MHz
    posctrl->Dpll[USE_DPLL_IND].DPLLRATIO.bit.LDR    = PLL_RATIO; // 1 MHz * (PLL_RATIO(47) + 1) = 48MHz
    while (posctrl->Dpll[USE_DPLL_IND].DPLLSYNCBUSY.bit.DPLLRATIO) {
        DBGC(DC_CLK_OSC_INIT_DPLL_SYNC_RATIO);
    }
    posctrl->Dpll[USE_DPLL_IND].DPLLCTRLA.bit.ONDEMAND = 0;
    posctrl->Dpll[USE_DPLL_IND].DPLLCTRLA.bit.ENABLE   = 1;
    while (posctrl->Dpll[USE_DPLL_IND].DPLLSYNCBUSY.bit.ENABLE) {
        DBGC(DC_CLK_OSC_INIT_DPLL_SYNC_ENABLE);
    }
    while (posctrl->Dpll[USE_DPLL_IND].DPLLSTATUS.bit.LOCK == 0) {
        DBGC(DC_CLK_OSC_INIT_DPLL_WAIT_LOCK);
    }
    while (posctrl->Dpll[USE_DPLL_IND].DPLLSTATUS.bit.CLKRDY == 0) {
        DBGC(DC_CLK_OSC_INIT_DPLL_WAIT_CLKRDY);
    }
    system_clks.freq_dpll[0] = (system_clks.freq_xosc0 / 2 / (posctrl->Dpll[USE_DPLL_IND].DPLLCTRLB.bit.DIV + 1)) * (posctrl->Dpll[USE_DPLL_IND].DPLLRATIO.bit.LDR + 1);

    // change gclk0 to DPLL
    pgclk->GENCTRL[GEN_DPLL0].bit.SRC = USE_DPLL_DEF;
    while (pgclk->SYNCBUSY.bit.GENCTRL0) {
        DBGC(DC_CLK_OSC_INIT_GCLK_SYNC_GENCTRL0);
    }

    system_clks.freq_gclk[0] = system_clks.freq_dpll[0];

    usec_delay_mult = system_clks.freq_gclk[0] / (USEC_DELAY_LOOP_CYCLES * 1000000);
    if (usec_delay_mult < 1) usec_delay_mult = 1; // Never allow a multiplier of zero

    DBGC(DC_CLK_OSC_INIT_COMPLETE);
}

// configure for 1MHz (1 usec timebase)
// call CLK_set_gclk_freq(GEN_TC45, FREQ_TC45_DEFAULT);
uint32_t CLK_set_gclk_freq(uint8_t gclkn, uint32_t freq) {
    Gclk *pgclk = GCLK;

    DBGC(DC_CLK_SET_GCLK_FREQ_BEGIN);

    while (pgclk->SYNCBUSY.vec.GENCTRL) {
        DBGC(DC_CLK_SET_GCLK_FREQ_SYNC_1);
    }
    pgclk->GENCTRL[gclkn].bit.SRC = USE_DPLL_DEF;
    while (pgclk->SYNCBUSY.vec.GENCTRL) {
        DBGC(DC_CLK_SET_GCLK_FREQ_SYNC_2);
    }
    pgclk->GENCTRL[gclkn].bit.DIV = (uint8_t)(system_clks.freq_dpll[0] / freq);
    while (pgclk->SYNCBUSY.vec.GENCTRL) {
        DBGC(DC_CLK_SET_GCLK_FREQ_SYNC_3);
    }
    pgclk->GENCTRL[gclkn].bit.DIVSEL = 0;
    while (pgclk->SYNCBUSY.vec.GENCTRL) {
        DBGC(DC_CLK_SET_GCLK_FREQ_SYNC_4);
    }
    pgclk->GENCTRL[gclkn].bit.GENEN = 1;
    while (pgclk->SYNCBUSY.vec.GENCTRL) {
        DBGC(DC_CLK_SET_GCLK_FREQ_SYNC_5);
    }
    system_clks.freq_gclk[gclkn] = system_clks.freq_dpll[0] / pgclk->GENCTRL[gclkn].bit.DIV;

    DBGC(DC_CLK_SET_GCLK_FREQ_COMPLETE);

    return system_clks.freq_gclk[gclkn];
}

void CLK_init_osc(void) {
    uint8_t gclkn = GEN_OSC0;
    Gclk *  pgclk = GCLK;

    DBGC(DC_CLK_INIT_OSC_BEGIN);

    while (pgclk->SYNCBUSY.vec.GENCTRL) {
        DBGC(DC_CLK_INIT_OSC_SYNC_1);
    }
    pgclk->GENCTRL[gclkn].bit.SRC = GCLK_SOURCE_XOSC0;
    while (pgclk->SYNCBUSY.vec.GENCTRL) {
        DBGC(DC_CLK_INIT_OSC_SYNC_2);
    }
    pgclk->GENCTRL[gclkn].bit.DIV = 1;
    while (pgclk->SYNCBUSY.vec.GENCTRL) {
        DBGC(DC_CLK_INIT_OSC_SYNC_3);
    }
    pgclk->GENCTRL[gclkn].bit.DIVSEL = 0;
    while (pgclk->SYNCBUSY.vec.GENCTRL) {
        DBGC(DC_CLK_INIT_OSC_SYNC_4);
    }
    pgclk->GENCTRL[gclkn].bit.GENEN = 1;
    while (pgclk->SYNCBUSY.vec.GENCTRL) {
        DBGC(DC_CLK_INIT_OSC_SYNC_5);
    }
    system_clks.freq_gclk[gclkn] = system_clks.freq_xosc0;

    DBGC(DC_CLK_INIT_OSC_COMPLETE);
}

void CLK_reset_time(void) {
    Tc *ptc4 = TC4;
    Tc *ptc0 = TC0;

    ms_clk = 0;

    DBGC(DC_CLK_RESET_TIME_BEGIN);

    // stop counters
    ptc4->COUNT16.CTRLA.bit.ENABLE = 0;
    while (ptc4->COUNT16.SYNCBUSY.bit.ENABLE) {
    }
    ptc0->COUNT32.CTRLA.bit.ENABLE = 0;
    while (ptc0->COUNT32.SYNCBUSY.bit.ENABLE) {
    }
    // zero counters
    ptc4->COUNT16.COUNT.reg = 0;
    while (ptc4->COUNT16.SYNCBUSY.bit.COUNT) {
    }
    ptc0->COUNT32.COUNT.reg = 0;
    while (ptc0->COUNT32.SYNCBUSY.bit.COUNT) {
    }
    // start counters
    ptc0->COUNT32.CTRLA.bit.ENABLE = 1;
    while (ptc0->COUNT32.SYNCBUSY.bit.ENABLE) {
    }
    ptc4->COUNT16.CTRLA.bit.ENABLE = 1;
    while (ptc4->COUNT16.SYNCBUSY.bit.ENABLE) {
    }

    DBGC(DC_CLK_RESET_TIME_COMPLETE);
}

void TC4_Handler() {
    if (TC4->COUNT16.INTFLAG.bit.MC0) {
        TC4->COUNT16.INTFLAG.reg = TC_INTENCLR_MC0;
        ms_clk++;
    }
}

uint32_t CLK_enable_timebase(void) {
    Gclk * pgclk  = GCLK;
    Mclk * pmclk  = MCLK;
    Tc *   ptc4   = TC4;
    Tc *   ptc0   = TC0;
    Evsys *pevsys = EVSYS;

    DBGC(DC_CLK_ENABLE_TIMEBASE_BEGIN);

    // gclk2  highspeed time base
    CLK_set_gclk_freq(GEN_TC45, FREQ_TC45_DEFAULT);
    CLK_init_osc();

    // unmask TC4, sourcegclk2 to TC4
    pmclk->APBCMASK.bit.TC4_             = 1;
    pgclk->PCHCTRL[TC4_GCLK_ID].bit.GEN  = GEN_TC45;
    pgclk->PCHCTRL[TC4_GCLK_ID].bit.CHEN = 1;

    // configure TC4
    DBGC(DC_CLK_ENABLE_TIMEBASE_TC4_BEGIN);
    ptc4->COUNT16.CTRLA.bit.ENABLE = 0;
    while (ptc4->COUNT16.SYNCBUSY.bit.ENABLE) {
        DBGC(DC_CLK_ENABLE_TIMEBASE_TC4_SYNC_DISABLE);
    }
    ptc4->COUNT16.CTRLA.bit.SWRST = 1;
    while (ptc4->COUNT16.SYNCBUSY.bit.SWRST) {
        DBGC(DC_CLK_ENABLE_TIMEBASE_TC4_SYNC_SWRST_1);
    }
    while (ptc4->COUNT16.CTRLA.bit.SWRST) {
        DBGC(DC_CLK_ENABLE_TIMEBASE_TC4_SYNC_SWRST_2);
    }

    // CTRLA defaults
    // CTRLB as default, counting up
    ptc4->COUNT16.CTRLBCLR.reg = 5;
    while (ptc4->COUNT16.SYNCBUSY.bit.CTRLB) {
        DBGC(DC_CLK_ENABLE_TIMEBASE_TC4_SYNC_CLTRB);
    }
    ptc4->COUNT16.CC[0].reg = 999;
    while (ptc4->COUNT16.SYNCBUSY.bit.CC0) {
        DBGC(DC_CLK_ENABLE_TIMEBASE_TC4_SYNC_CC0);
    }
    // ptc4->COUNT16.DBGCTRL.bit.DBGRUN = 1;

    // wave mode
    ptc4->COUNT16.WAVE.bit.WAVEGEN = 1; // MFRQ match frequency mode, toggle each CC match
    // generate event for next stage
    ptc4->COUNT16.EVCTRL.bit.MCEO0 = 1;

    NVIC_EnableIRQ(TC4_IRQn);
    ptc4->COUNT16.INTENSET.bit.MC0 = 1;

    DBGC(DC_CLK_ENABLE_TIMEBASE_TC4_COMPLETE);

    // unmask TC0,1, sourcegclk2 to TC0,1
    pmclk->APBAMASK.bit.TC0_             = 1;
    pgclk->PCHCTRL[TC0_GCLK_ID].bit.GEN  = GEN_TC45;
    pgclk->PCHCTRL[TC0_GCLK_ID].bit.CHEN = 1;

    pmclk->APBAMASK.bit.TC1_             = 1;
    pgclk->PCHCTRL[TC1_GCLK_ID].bit.GEN  = GEN_TC45;
    pgclk->PCHCTRL[TC1_GCLK_ID].bit.CHEN = 1;

    // configure TC0
    DBGC(DC_CLK_ENABLE_TIMEBASE_TC0_BEGIN);
    ptc0->COUNT32.CTRLA.bit.ENABLE = 0;
    while (ptc0->COUNT32.SYNCBUSY.bit.ENABLE) {
        DBGC(DC_CLK_ENABLE_TIMEBASE_TC0_SYNC_DISABLE);
    }
    ptc0->COUNT32.CTRLA.bit.SWRST = 1;
    while (ptc0->COUNT32.SYNCBUSY.bit.SWRST) {
        DBGC(DC_CLK_ENABLE_TIMEBASE_TC0_SYNC_SWRST_1);
    }
    while (ptc0->COUNT32.CTRLA.bit.SWRST) {
        DBGC(DC_CLK_ENABLE_TIMEBASE_TC0_SYNC_SWRST_2);
    }
    // CTRLA as default
    ptc0->COUNT32.CTRLA.bit.MODE   = 2; // 32 bit mode
    ptc0->COUNT32.EVCTRL.bit.TCEI  = 1; // enable incoming events
    ptc0->COUNT32.EVCTRL.bit.EVACT = 2; // count events

    DBGC(DC_CLK_ENABLE_TIMEBASE_TC0_COMPLETE);

    DBGC(DC_CLK_ENABLE_TIMEBASE_EVSYS_BEGIN);

    // configure event system
    pmclk->APBBMASK.bit.EVSYS_               = 1;
    pgclk->PCHCTRL[EVSYS_GCLK_ID_0].bit.GEN  = GEN_TC45;
    pgclk->PCHCTRL[EVSYS_GCLK_ID_0].bit.CHEN = 1;
    pevsys->USER[44].reg                     = EVSYS_ID_USER_PORT_EV_0;              // TC0 will get event channel 0
    pevsys->Channel[0].CHANNEL.bit.EDGSEL    = EVSYS_CHANNEL_EDGSEL_RISING_EDGE_Val; // Rising edge
    pevsys->Channel[0].CHANNEL.bit.PATH      = EVSYS_CHANNEL_PATH_SYNCHRONOUS_Val;   // Synchronous
    pevsys->Channel[0].CHANNEL.bit.EVGEN     = EVSYS_ID_GEN_TC4_MCX_0;               // TC4 MC0

    DBGC(DC_CLK_ENABLE_TIMEBASE_EVSYS_COMPLETE);

    CLK_reset_time();

    ADC0_clock_init();

    DBGC(DC_CLK_ENABLE_TIMEBASE_COMPLETE);

    return 0;
}

void CLK_delay_us(uint32_t usec) {
    asm("CBZ R0, return\n\t" // If usec == 0, branch to return label
    );
    asm("MULS R0, %0\n\t"       // Multiply R0(usec) by usec_delay_mult and store in R0
        ".balign 16\n\t"        // Ensure loop is aligned for fastest performance
        "loop: SUBS R0, #1\n\t" // Subtract 1 from R0 and update flags (1 cycle)
        "BNE loop\n\t"          // Branch if non-zero to loop label (2 cycles)  NOTE: USEC_DELAY_LOOP_CYCLES is the sum of loop cycles
        "return:\n\t"           // Return label
        :                       // No output registers
        : "r"(usec_delay_mult)  // For %0
    );
    // Note: BX LR generated
}

void CLK_delay_ms(uint64_t msec) {
    msec += timer_read64();
    while (msec > timer_read64()) {
    }
}

void clk_enable_sercom_apbmask(int sercomn) {
    Mclk *pmclk = MCLK;
    switch (sercomn) {
        case 0:
            pmclk->APBAMASK.bit.SERCOM0_ = 1;
            break;
        case 1:
            pmclk->APBAMASK.bit.SERCOM1_ = 1;
            break;
        case 2:
            pmclk->APBBMASK.bit.SERCOM2_ = 1;
            break;
        case 3:
            pmclk->APBBMASK.bit.SERCOM3_ = 1;
            break;
        default:
            break;
    }
}

// call CLK_oscctrl_init first
// call CLK_set_spi_freq(CHAN_SERCOM_SPI, FREQ_SPI_DEFAULT);
uint32_t CLK_set_spi_freq(uint8_t sercomn, uint32_t freq) {
    DBGC(DC_CLK_SET_SPI_FREQ_BEGIN);

    Gclk *  pgclk   = GCLK;
    Sercom *psercom = (Sercom *)sercom_apbbase[sercomn];
    clk_enable_sercom_apbmask(sercomn);

    // all gclk0 for now
    pgclk->PCHCTRL[sercom_pchan[sercomn]].bit.GEN  = 0;
    pgclk->PCHCTRL[sercom_pchan[sercomn]].bit.CHEN = 1;

    psercom->I2CM.CTRLA.bit.SWRST = 1;
    while (psercom->I2CM.SYNCBUSY.bit.SWRST) {
    }
    while (psercom->I2CM.CTRLA.bit.SWRST) {
    }

    psercom->SPI.BAUD.reg            = (uint8_t)(system_clks.freq_gclk[0] / 2 / freq - 1);
    system_clks.freq_spi             = system_clks.freq_gclk[0] / 2 / (psercom->SPI.BAUD.reg + 1);
    system_clks.freq_sercom[sercomn] = system_clks.freq_spi;

    DBGC(DC_CLK_SET_SPI_FREQ_COMPLETE);

    return system_clks.freq_spi;
}

// call CLK_oscctrl_init first
// call CLK_set_i2c0_freq(CHAN_SERCOM_I2C0, FREQ_I2C0_DEFAULT);
uint32_t CLK_set_i2c0_freq(uint8_t sercomn, uint32_t freq) {
    DBGC(DC_CLK_SET_I2C0_FREQ_BEGIN);

    Gclk *  pgclk   = GCLK;
    Sercom *psercom = (Sercom *)sercom_apbbase[sercomn];
    clk_enable_sercom_apbmask(sercomn);

    // all gclk0 for now
    pgclk->PCHCTRL[sercom_pchan[sercomn]].bit.GEN  = 0;
    pgclk->PCHCTRL[sercom_pchan[sercomn]].bit.CHEN = 1;

    psercom->I2CM.CTRLA.bit.SWRST = 1;
    while (psercom->I2CM.SYNCBUSY.bit.SWRST) {
    }
    while (psercom->I2CM.CTRLA.bit.SWRST) {
    }

    psercom->I2CM.BAUD.bit.BAUD      = (uint8_t)(system_clks.freq_gclk[0] / 2 / freq - 1);
    system_clks.freq_i2c0            = system_clks.freq_gclk[0] / 2 / (psercom->I2CM.BAUD.bit.BAUD + 1);
    system_clks.freq_sercom[sercomn] = system_clks.freq_i2c0;

    DBGC(DC_CLK_SET_I2C0_FREQ_COMPLETE);

    return system_clks.freq_i2c0;
}

// call CLK_oscctrl_init first
// call CLK_set_i2c1_freq(CHAN_SERCOM_I2C1, FREQ_I2C1_DEFAULT);
uint32_t CLK_set_i2c1_freq(uint8_t sercomn, uint32_t freq) {
    DBGC(DC_CLK_SET_I2C1_FREQ_BEGIN);

    Gclk *  pgclk   = GCLK;
    Sercom *psercom = (Sercom *)sercom_apbbase[sercomn];
    clk_enable_sercom_apbmask(sercomn);

    // all gclk0 for now
    pgclk->PCHCTRL[sercom_pchan[sercomn]].bit.GEN  = 0;
    pgclk->PCHCTRL[sercom_pchan[sercomn]].bit.CHEN = 1;

    psercom->I2CM.CTRLA.bit.SWRST = 1;
    while (psercom->I2CM.SYNCBUSY.bit.SWRST) {
    }
    while (psercom->I2CM.CTRLA.bit.SWRST) {
    }

    psercom->I2CM.BAUD.bit.BAUD      = (uint8_t)(system_clks.freq_gclk[0] / 2 / freq - 10);
    system_clks.freq_i2c1            = system_clks.freq_gclk[0] / 2 / (psercom->I2CM.BAUD.bit.BAUD + 10);
    system_clks.freq_sercom[sercomn] = system_clks.freq_i2c1;

    DBGC(DC_CLK_SET_I2C1_FREQ_COMPLETE);

    return system_clks.freq_i2c1;
}

void CLK_init(void) {
    DBGC(DC_CLK_INIT_BEGIN);

    memset((void *)&system_clks, 0, sizeof(system_clks));

    CLK_oscctrl_init();
    CLK_enable_timebase();

    DBGC(DC_CLK_INIT_COMPLETE);
}
