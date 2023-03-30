/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

// For MHZ definitions etc
#include "hardware/clocks.h"
#include "hardware/pll.h"
#include "hardware/resets.h"

/// \tag::pll_init_calculations[]
void pll_init(PLL pll, uint refdiv, uint vco_freq, uint post_div1, uint post_div2) {
    uint32_t ref_mhz = XOSC_MHZ / refdiv;

    // Check vco freq is in an acceptable range
    assert(vco_freq >= (PICO_PLL_VCO_MIN_FREQ_MHZ * MHZ) && vco_freq <= (PICO_PLL_VCO_MAX_FREQ_MHZ * MHZ));

    // What are we multiplying the reference clock by to get the vco freq
    // (The regs are called div, because you divide the vco output and compare it to the refclk)
    uint32_t fbdiv = vco_freq / (ref_mhz * MHZ);
/// \end::pll_init_calculations[]

    // fbdiv
    assert(fbdiv >= 16 && fbdiv <= 320);

    // Check divider ranges
    assert((post_div1 >= 1 && post_div1 <= 7) && (post_div2 >= 1 && post_div2 <= 7));

    // post_div1 should be >= post_div2
    // from appnote page 11
    // postdiv1 is designed to operate with a higher input frequency than postdiv2

    // Check that reference frequency is no greater than vco / 16
    assert(ref_mhz <= (vco_freq / 16));

    // div1 feeds into div2 so if div1 is 5 and div2 is 2 then you get a divide by 10
    uint32_t pdiv = (post_div1 << PLL_PRIM_POSTDIV1_LSB) |
                    (post_div2 << PLL_PRIM_POSTDIV2_LSB);

/// \tag::pll_init_finish[]
    if ((pll->cs & PLL_CS_LOCK_BITS) &&
        (refdiv == (pll->cs & PLL_CS_REFDIV_BITS)) &&
        (fbdiv  == (pll->fbdiv_int & PLL_FBDIV_INT_BITS)) &&
        (pdiv   == (pll->prim & (PLL_PRIM_POSTDIV1_BITS | PLL_PRIM_POSTDIV2_BITS)))) {
        // do not disrupt PLL that is already correctly configured and operating
        return;
    }

    uint32_t pll_reset = (pll_usb_hw == pll) ? RESETS_RESET_PLL_USB_BITS : RESETS_RESET_PLL_SYS_BITS;
    reset_block(pll_reset);
    unreset_block_wait(pll_reset);

    // Load VCO-related dividers before starting VCO
    pll->cs = refdiv;
    pll->fbdiv_int = fbdiv;

    // Turn on PLL
    uint32_t power = PLL_PWR_PD_BITS | // Main power
                     PLL_PWR_VCOPD_BITS; // VCO Power

    hw_clear_bits(&pll->pwr, power);

    // Wait for PLL to lock
    while (!(pll->cs & PLL_CS_LOCK_BITS)) tight_loop_contents();

    // Set up post dividers
    pll->prim = pdiv;

    // Turn on post divider
    hw_clear_bits(&pll->pwr, PLL_PWR_POSTDIVPD_BITS);
/// \end::pll_init_finish[]
}

void pll_deinit(PLL pll) {
    // todo: Make sure there are no sources running from this pll?
    pll->pwr = PLL_PWR_BITS;
}
