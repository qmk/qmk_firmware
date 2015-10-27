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

#include "cmsis.h"
#include "gpio_regs.h"
#include "clkman_regs.h"

/* Application developer should override where necessary with different external HFX source */
#ifndef __SYSTEM_HFX
#define __SYSTEM_HFX 24000000
#endif

//******************************************************************************
// This function will get called early in system initialization
void low_level_init(void)
{
    /* wait for the RO to stabilize */
    while (!(MXC_CLKMAN->intfl & MXC_F_CLKMAN_INTFL_RING_STABLE));

    /* Configure and enable the oscillator */
    if (!(MXC_CLKMAN->clk_config & MXC_F_CLKMAN_CLK_CONFIG_HFX_ENABLE)) {

        MXC_CLKMAN->clk_config = (0x4 << MXC_F_CLKMAN_CLK_CONFIG_HFX_GM_ADJUST_POS);

        /* Enable the external crystal */
        MXC_CLKMAN->clk_config |= MXC_F_CLKMAN_CLK_CONFIG_HFX_ENABLE;
    }

    /* Wait for external crystal to stabilize */
    for (volatile int waitcnt = 0; waitcnt < 0x4000; waitcnt++);    // 0x4000 ~10ms 0x10000 ~35ms, 0x20000 ~75ms

    /* Configure the PLL */
    uint32_t clk_config = MXC_CLKMAN->clk_config;
    clk_config  = (clk_config & ~MXC_F_CLKMAN_CLK_CONFIG_PLL_INPUT_SELECT) | (MXC_E_CLKMAN_PLL_INPUT_SELECT_HFX << MXC_F_CLKMAN_CLK_CONFIG_PLL_INPUT_SELECT_POS);

#if (__SYSTEM_HFX == 8000000)
    clk_config  = (clk_config & ~MXC_F_CLKMAN_CLK_CONFIG_PLL_DIVISOR_SELECT) | (MXC_E_CLKMAN_PLL_DIVISOR_SELECT_8MHZ << MXC_F_CLKMAN_CLK_CONFIG_PLL_DIVISOR_SELECT_POS);
#elif (__SYSTEM_HFX == 12000000)
    clk_config  = (clk_config & ~MXC_F_CLKMAN_CLK_CONFIG_PLL_DIVISOR_SELECT) | (MXC_E_CLKMAN_PLL_DIVISOR_SELECT_12MHZ << MXC_F_CLKMAN_CLK_CONFIG_PLL_DIVISOR_SELECT_POS);
#elif (__SYSTEM_HFX == 24000000)
    clk_config  = (clk_config & ~MXC_F_CLKMAN_CLK_CONFIG_PLL_DIVISOR_SELECT) | (MXC_E_CLKMAN_PLL_DIVISOR_SELECT_24MHZ << MXC_F_CLKMAN_CLK_CONFIG_PLL_DIVISOR_SELECT_POS);
#else
#error Invalid __SYSTEM_HFX setting
#endif

    clk_config |=  MXC_F_CLKMAN_CLK_CONFIG_PLL_8MHZ_ENABLE;
    clk_config &= ~MXC_F_CLKMAN_CLK_CONFIG_PLL_BYPASS;
    clk_config  = (clk_config & ~MXC_F_CLKMAN_CLK_CONFIG_PLL_STABILITY_COUNT) | (MXC_E_CLKMAN_STABILITY_COUNT_2_13_CLKS << MXC_F_CLKMAN_CLK_CONFIG_PLL_STABILITY_COUNT_POS);
    MXC_CLKMAN->clk_config = clk_config;

    /* Enable the PLL and wait for stable */
    MXC_CLKMAN->clk_config |= (MXC_F_CLKMAN_CLK_CONFIG_PLL_ENABLE | MXC_F_CLKMAN_CLK_CONFIG_PLL_RESET_N);
    while (!(MXC_CLKMAN->intfl & MXC_F_CLKMAN_INTFL_PLL_STABLE));

    /* Switch to the PLL */
    MXC_CLKMAN->clk_ctrl = (MXC_CLKMAN->clk_ctrl & ~MXC_F_CLKMAN_CLK_CTRL_SYSTEM_SOURCE_SELECT) |
                           ((MXC_E_CLKMAN_SYSTEM_SOURCE_SELECT_PLL_48MHZ_DIV_2 << MXC_F_CLKMAN_CLK_CTRL_SYSTEM_SOURCE_SELECT_POS));
}
