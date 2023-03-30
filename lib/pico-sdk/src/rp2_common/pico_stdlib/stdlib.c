/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "hardware/pll.h"
#include "hardware/clocks.h"
#if LIB_PICO_STDIO_UART
#include "pico/stdio_uart.h"
#else
#include "pico/binary_info.h"
#endif

// everything running off the USB oscillator
void set_sys_clock_48mhz() {
    if (!running_on_fpga()) {
        // Change clk_sys to be 48MHz. The simplest way is to take this from PLL_USB
        // which has a source frequency of 48MHz
        clock_configure(clk_sys,
                        CLOCKS_CLK_SYS_CTRL_SRC_VALUE_CLKSRC_CLK_SYS_AUX,
                        CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB,
                        48 * MHZ,
                        48 * MHZ);

        // Turn off PLL sys for good measure
        pll_deinit(pll_sys);

        // CLK peri is clocked from clk_sys so need to change clk_peri's freq
        clock_configure(clk_peri,
                        0,
                        CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLK_SYS,
                        48 * MHZ,
                        48 * MHZ);
    }
}

void set_sys_clock_pll(uint32_t vco_freq, uint post_div1, uint post_div2) {
    if (!running_on_fpga()) {
        clock_configure(clk_sys,
                        CLOCKS_CLK_SYS_CTRL_SRC_VALUE_CLKSRC_CLK_SYS_AUX,
                        CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB,
                        48 * MHZ,
                        48 * MHZ);

        pll_init(pll_sys, 1, vco_freq, post_div1, post_div2);
        uint32_t freq = vco_freq / (post_div1 * post_div2);

        // Configure clocks
        // CLK_REF = XOSC (12MHz) / 1 = 12MHz
        clock_configure(clk_ref,
                        CLOCKS_CLK_REF_CTRL_SRC_VALUE_XOSC_CLKSRC,
                        0, // No aux mux
                        12 * MHZ,
                        12 * MHZ);

        // CLK SYS = PLL SYS (125MHz) / 1 = 125MHz
        clock_configure(clk_sys,
                        CLOCKS_CLK_SYS_CTRL_SRC_VALUE_CLKSRC_CLK_SYS_AUX,
                        CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS,
                        freq, freq);

        clock_configure(clk_peri,
                        0, // Only AUX mux on ADC
                        CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB,
                        48 * MHZ,
                        48 * MHZ);
    }
}

bool check_sys_clock_khz(uint32_t freq_khz, uint *vco_out, uint *postdiv1_out, uint *postdiv_out) {
    uint crystal_freq_khz = clock_get_hz(clk_ref) / 1000;
    for (uint fbdiv = 320; fbdiv >= 16; fbdiv--) {
        uint vco = fbdiv * crystal_freq_khz;
        if (vco < PICO_PLL_VCO_MIN_FREQ_MHZ * 1000  || vco > PICO_PLL_VCO_MAX_FREQ_MHZ * 1000) continue;
        for (uint postdiv1 = 7; postdiv1 >= 1; postdiv1--) {
            for (uint postdiv2 = postdiv1; postdiv2 >= 1; postdiv2--) {
                uint out = vco / (postdiv1 * postdiv2);
                if (out == freq_khz && !(vco % (postdiv1 * postdiv2))) {
                    *vco_out = vco * 1000;
                    *postdiv1_out = postdiv1;
                    *postdiv_out = postdiv2;
                    return true;
                }
            }
        }
    }
    return false;
}

void setup_default_uart() {
#if LIB_PICO_STDIO_UART
    stdio_uart_init();
#elif defined(PICO_DEFAULT_UART_BAUD_RATE) && defined(PICO_DEFAULT_UART_TX_PIN) && defined(PICO_DEFAULT_UART_RX_PIN)
    // this is mostly for backwards compatibility - stdio_uart_init is a bit more nuanced, and usually likely to be present
    uart_init(uart_default, PICO_DEFAULT_UART_BAUD_RATE);
    if (PICO_DEFAULT_UART_TX_PIN >= 0)
        gpio_set_function(PICO_DEFAULT_UART_TX_PIN, GPIO_FUNC_UART);
    if (PICO_DEFAULT_UART_RX_PIN >= 0)
        gpio_set_function(PICO_DEFAULT_UART_RX_PIN, GPIO_FUNC_UART);
    bi_decl_if_func_used(bi_2pins_with_func(PICO_DEFAULT_UART_RX_PIN, PICO_DEFAULT_UART_TX_PIN, GPIO_FUNC_UART));
#endif
}
