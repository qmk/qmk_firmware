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

#include "max32600.h"
#include "clkman_regs.h"
#include "pwrman_regs.h"
#include "ioman_regs.h"
#include "trim_regs.h"
#include "flc_regs.h"
#include "pwrseq_regs.h"
#include "dac_regs.h"
#include "icc_regs.h"

/* Application developer should override where necessary with different external HFX source */
#ifndef __SYSTEM_HFX
#define __SYSTEM_HFX 8000000
#endif

uint32_t SystemCoreClock = 24000000;

void SystemCoreClockUpdate(void)
{
    switch ((MXC_CLKMAN->clk_ctrl & MXC_F_CLKMAN_CLK_CTRL_SYSTEM_SOURCE_SELECT) >> MXC_F_CLKMAN_CLK_CTRL_SYSTEM_SOURCE_SELECT_POS) {
        case MXC_E_CLKMAN_SYSTEM_SOURCE_SELECT_24MHZ_RO_DIV_8:
            SystemCoreClock = 3000000;
            break;
        case MXC_E_CLKMAN_SYSTEM_SOURCE_SELECT_24MHZ_RO:
        case MXC_E_CLKMAN_SYSTEM_SOURCE_SELECT_PLL_48MHZ_DIV_2:
            SystemCoreClock = 24000000;
            break;
        case MXC_E_CLKMAN_SYSTEM_SOURCE_SELECT_HFX:
            SystemCoreClock = __SYSTEM_HFX;
            break;
    }

    uint32_t shift = MXC_CLKMAN->clk_ctrl_0_system;
    if (shift) {
        SystemCoreClock = SystemCoreClock >> (shift - 1);
    }
}

/* power seq registers */
static void set_pwr_regs(void)
{
    uint32_t dac2trim =  MXC_DAC2->reg & 0xff00ffff;
    uint32_t dac3trim =  MXC_DAC3->reg & 0xff00ffff;
    dac2trim = dac2trim + MXC_TRIM->trim_reg_36;
    dac3trim = dac3trim + MXC_TRIM->trim_reg_37;
    MXC_PWRSEQ->reg5 = MXC_TRIM->trim_reg_13;
    MXC_PWRSEQ->reg6 = MXC_TRIM->trim_reg_14;
    MXC_DAC0->trm = MXC_TRIM->trim_reg_34;
    MXC_DAC1->trm = MXC_TRIM->trim_reg_35;
    MXC_DAC2->reg = dac2trim;
    MXC_DAC3->reg = dac3trim;
}

void ICC_Enable(void)
{
    /* clock gater must be 'on' not 'dynamic' for cache control */
    uint32_t temp = MXC_CLKMAN->clk_gate_ctrl0;
    temp &= ~MXC_F_CLKMAN_CLK_GATE_CTRL0_ICACHE_CLK_GATER;
    temp |= (MXC_E_CLKMAN_CLK_GATE_ON << MXC_F_CLKMAN_CLK_GATE_CTRL0_ICACHE_CLK_GATER_POS);
    MXC_CLKMAN->clk_gate_ctrl0 = temp;


    /* invalidate, wait, enable */
    MXC_ICC->invdt_all = 0xFFFF;
    while(!(MXC_ICC->ctrl_stat & MXC_F_ICC_CTRL_STAT_READY));
    MXC_ICC->ctrl_stat |= MXC_F_ICC_CTRL_STAT_ENABLE;

    /* must invalidate a second time for proper use */
    MXC_ICC->invdt_all = 1;

    /* clock gater 'dynamic' safe again */
    temp = MXC_CLKMAN->clk_gate_ctrl0;
    temp &= ~MXC_F_CLKMAN_CLK_GATE_CTRL0_ICACHE_CLK_GATER;
    temp |= (MXC_E_CLKMAN_CLK_GATE_DYNAMIC << MXC_F_CLKMAN_CLK_GATE_CTRL0_ICACHE_CLK_GATER_POS);
    MXC_CLKMAN->clk_gate_ctrl0 = temp;
}

// This function to be implemented by the hal
extern void low_level_init(void);

void SystemInit(void)
{
    set_pwr_regs();

    // enable instruction cache
    ICC_Enable();

    low_level_init();

    // Clear IO Active
    MXC_PWRMAN->pwr_rst_ctrl = (MXC_F_PWRMAN_PWR_RST_CTRL_FLASH_ACTIVE |
                                MXC_F_PWRMAN_PWR_RST_CTRL_SRAM_ACTIVE);

    // Set WUD Clear
    MXC_PWRMAN->pwr_rst_ctrl = (MXC_F_PWRMAN_PWR_RST_CTRL_FLASH_ACTIVE |
                                MXC_F_PWRMAN_PWR_RST_CTRL_SRAM_ACTIVE |
                                MXC_F_PWRMAN_PWR_RST_CTRL_WUD_CLEAR);

    // Set IO Active
    MXC_PWRMAN->pwr_rst_ctrl = (MXC_F_PWRMAN_PWR_RST_CTRL_FLASH_ACTIVE |
                                MXC_F_PWRMAN_PWR_RST_CTRL_SRAM_ACTIVE |
                                MXC_F_PWRMAN_PWR_RST_CTRL_IO_ACTIVE |
                                MXC_F_PWRMAN_PWR_RST_CTRL_PULLUPS_ENABLED);

    MXC_PWRSEQ->reg0 |= MXC_F_PWRSEQ_REG0_PWR_CHZYEN_RUN;

    // set systick to the RTC input 32.768kHz clock, not system clock; this is needed to keep JTAG alive during sleep
    MXC_CLKMAN->clk_ctrl |= MXC_F_CLKMAN_CLK_CTRL_RTOS_MODE;

    SystemCoreClockUpdate();
}
