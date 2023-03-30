/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico.h"
#include "hardware/regs/clocks.h"
#include "hardware/platform_defs.h"
#include "hardware/clocks.h"
#include "hardware/watchdog.h"
#include "hardware/pll.h"
#include "hardware/xosc.h"
#include "hardware/irq.h"
#include "hardware/gpio.h"

check_hw_layout(clocks_hw_t, clk[clk_adc].selected, CLOCKS_CLK_ADC_SELECTED_OFFSET);
check_hw_layout(clocks_hw_t, fc0.result, CLOCKS_FC0_RESULT_OFFSET);
check_hw_layout(clocks_hw_t, ints, CLOCKS_INTS_OFFSET);

static uint32_t configured_freq[CLK_COUNT];

static resus_callback_t _resus_callback;

// Clock muxing consists of two components:
// - A glitchless mux, which can be switched freely, but whose inputs must be
//   free-running
// - An auxiliary (glitchy) mux, whose output glitches when switched, but has
//   no constraints on its inputs
// Not all clocks have both types of mux.
static inline bool has_glitchless_mux(enum clock_index clk_index) {
    return clk_index == clk_sys || clk_index == clk_ref;
}

void clock_stop(enum clock_index clk_index) {
    clock_hw_t *clock = &clocks_hw->clk[clk_index];
    hw_clear_bits(&clock->ctrl, CLOCKS_CLK_USB_CTRL_ENABLE_BITS);
    configured_freq[clk_index] = 0;
}

/// \tag::clock_configure[]
bool clock_configure(enum clock_index clk_index, uint32_t src, uint32_t auxsrc, uint32_t src_freq, uint32_t freq) {
    uint32_t div;

    assert(src_freq >= freq);

    if (freq > src_freq)
        return false;

    // Div register is 24.8 int.frac divider so multiply by 2^8 (left shift by 8)
    div = (uint32_t) (((uint64_t) src_freq << 8) / freq);

    clock_hw_t *clock = &clocks_hw->clk[clk_index];

    // If increasing divisor, set divisor before source. Otherwise set source
    // before divisor. This avoids a momentary overspeed when e.g. switching
    // to a faster source and increasing divisor to compensate.
    if (div > clock->div)
        clock->div = div;

    // If switching a glitchless slice (ref or sys) to an aux source, switch
    // away from aux *first* to avoid passing glitches when changing aux mux.
    // Assume (!!!) glitchless source 0 is no faster than the aux source.
    if (has_glitchless_mux(clk_index) && src == CLOCKS_CLK_SYS_CTRL_SRC_VALUE_CLKSRC_CLK_SYS_AUX) {
        hw_clear_bits(&clock->ctrl, CLOCKS_CLK_REF_CTRL_SRC_BITS);
        while (!(clock->selected & 1u))
            tight_loop_contents();
    }
    // If no glitchless mux, cleanly stop the clock to avoid glitches
    // propagating when changing aux mux. Note it would be a really bad idea
    // to do this on one of the glitchless clocks (clk_sys, clk_ref).
    else {
        // Disable clock. On clk_ref and clk_sys this does nothing,
        // all other clocks have the ENABLE bit in the same position.
        hw_clear_bits(&clock->ctrl, CLOCKS_CLK_GPOUT0_CTRL_ENABLE_BITS);
        if (configured_freq[clk_index] > 0) {
            // Delay for 3 cycles of the target clock, for ENABLE propagation.
            // Note XOSC_COUNT is not helpful here because XOSC is not
            // necessarily running, nor is timer... so, 3 cycles per loop:
            uint delay_cyc = configured_freq[clk_sys] / configured_freq[clk_index] + 1;
            asm volatile (
                ".syntax unified \n\t"
                "1: \n\t"
                "subs %0, #1 \n\t"
                "bne 1b"
                : "+r" (delay_cyc)
            );
        }
    }

    // Set aux mux first, and then glitchless mux if this clock has one
    hw_write_masked(&clock->ctrl,
        (auxsrc << CLOCKS_CLK_SYS_CTRL_AUXSRC_LSB),
        CLOCKS_CLK_SYS_CTRL_AUXSRC_BITS
    );

    if (has_glitchless_mux(clk_index)) {
        hw_write_masked(&clock->ctrl,
            src << CLOCKS_CLK_REF_CTRL_SRC_LSB,
            CLOCKS_CLK_REF_CTRL_SRC_BITS
        );
        while (!(clock->selected & (1u << src)))
            tight_loop_contents();
    }

    // Enable clock. On clk_ref and clk_sys this does nothing,
    // all other clocks have the ENABLE bit in the same position.
    hw_set_bits(&clock->ctrl, CLOCKS_CLK_GPOUT0_CTRL_ENABLE_BITS);

    // Now that the source is configured, we can trust that the user-supplied
    // divisor is a safe value.
    clock->div = div;

    // Store the configured frequency
    configured_freq[clk_index] = (uint32_t)(((uint64_t) src_freq << 8) / div);

    return true;
}
/// \end::clock_configure[]

void clocks_init(void) {
    // Start tick in watchdog
    watchdog_start_tick(XOSC_MHZ);

    // Everything is 48MHz on FPGA apart from RTC. Otherwise set to 0 and will be set in clock configure
    if (running_on_fpga()) {
        for (uint i = 0; i < CLK_COUNT; i++) {
            configured_freq[i] = 48 * MHZ;
        }
        configured_freq[clk_rtc] = 46875;
        return;
    }

    // Disable resus that may be enabled from previous software
    clocks_hw->resus.ctrl = 0;

    // Enable the xosc
    xosc_init();

    // Before we touch PLLs, switch sys and ref cleanly away from their aux sources.
    hw_clear_bits(&clocks_hw->clk[clk_sys].ctrl, CLOCKS_CLK_SYS_CTRL_SRC_BITS);
    while (clocks_hw->clk[clk_sys].selected != 0x1)
        tight_loop_contents();
    hw_clear_bits(&clocks_hw->clk[clk_ref].ctrl, CLOCKS_CLK_REF_CTRL_SRC_BITS);
    while (clocks_hw->clk[clk_ref].selected != 0x1)
        tight_loop_contents();

    /// \tag::pll_settings[]
    // Configure PLLs
    //                   REF     FBDIV VCO            POSTDIV
    // PLL SYS: 12 / 1 = 12MHz * 125 = 1500MHz / 6 / 2 = 125MHz
    // PLL USB: 12 / 1 = 12MHz * 100 = 1200MHz / 5 / 5 =  48MHz
    /// \end::pll_settings[]

    /// \tag::pll_init[]
    pll_init(pll_sys, 1, 1500 * MHZ, 6, 2);
    pll_init(pll_usb, 1, 1200 * MHZ, 5, 5);
    /// \end::pll_init[]

    // Configure clocks
    // CLK_REF = XOSC (12MHz) / 1 = 12MHz
    clock_configure(clk_ref,
                    CLOCKS_CLK_REF_CTRL_SRC_VALUE_XOSC_CLKSRC,
                    0, // No aux mux
                    12 * MHZ,
                    12 * MHZ);

    /// \tag::configure_clk_sys[]
    // CLK SYS = PLL SYS (125MHz) / 1 = 125MHz
    clock_configure(clk_sys,
                    CLOCKS_CLK_SYS_CTRL_SRC_VALUE_CLKSRC_CLK_SYS_AUX,
                    CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS,
                    125 * MHZ,
                    125 * MHZ);
    /// \end::configure_clk_sys[]

    // CLK USB = PLL USB (48MHz) / 1 = 48MHz
    clock_configure(clk_usb,
                    0, // No GLMUX
                    CLOCKS_CLK_USB_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB,
                    48 * MHZ,
                    48 * MHZ);

    // CLK ADC = PLL USB (48MHZ) / 1 = 48MHz
    clock_configure(clk_adc,
                    0, // No GLMUX
                    CLOCKS_CLK_ADC_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB,
                    48 * MHZ,
                    48 * MHZ);

    // CLK RTC = PLL USB (48MHz) / 1024 = 46875Hz
    clock_configure(clk_rtc,
                    0, // No GLMUX
                    CLOCKS_CLK_RTC_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB,
                    48 * MHZ,
                    46875);

    // CLK PERI = clk_sys. Used as reference clock for Peripherals. No dividers so just select and enable
    // Normally choose clk_sys or clk_usb
    clock_configure(clk_peri,
                    0,
                    CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLK_SYS,
                    125 * MHZ,
                    125 * MHZ);
}

/// \tag::clock_get_hz[]
uint32_t clock_get_hz(enum clock_index clk_index) {
    return configured_freq[clk_index];
}
/// \end::clock_get_hz[]

void clock_set_reported_hz(enum clock_index clk_index, uint hz) {
    configured_freq[clk_index] = hz;
}

/// \tag::frequency_count_khz[]
uint32_t frequency_count_khz(uint src) {
    fc_hw_t *fc = &clocks_hw->fc0;

    // If frequency counter is running need to wait for it. It runs even if the source is NULL
    while(fc->status & CLOCKS_FC0_STATUS_RUNNING_BITS) {
        tight_loop_contents();
    }

    // Set reference freq
    fc->ref_khz = clock_get_hz(clk_ref) / 1000;

    // FIXME: Don't pick random interval. Use best interval
    fc->interval = 10;

    // No min or max
    fc->min_khz = 0;
    fc->max_khz = 0xffffffff;

    // Set SRC which automatically starts the measurement
    fc->src = src;

    while(!(fc->status & CLOCKS_FC0_STATUS_DONE_BITS)) {
        tight_loop_contents();
    }

    // Return the result
    return fc->result >> CLOCKS_FC0_RESULT_KHZ_LSB;
}
/// \end::frequency_count_khz[]

static void clocks_handle_resus(void) {
    // Set clk_sys back to the ref clock rather than it being forced to clk_ref
    // by resus. Call the user's resus callback if they have set one

    // CLK SYS = CLK_REF. Must be running for this code to be running
    uint clk_ref_freq = clock_get_hz(clk_ref);
    clock_configure(clk_sys,
                    CLOCKS_CLK_SYS_CTRL_SRC_VALUE_CLK_REF,
                    0,
                    clk_ref_freq,
                    clk_ref_freq);

    // Assert we have been resussed
    assert(clocks_hw->resus.status & CLOCKS_CLK_SYS_RESUS_STATUS_RESUSSED_BITS);

    // Now we have fixed clk_sys we can safely remove the resus
    hw_set_bits(&clocks_hw->resus.ctrl, CLOCKS_CLK_SYS_RESUS_CTRL_CLEAR_BITS);
    hw_clear_bits(&clocks_hw->resus.ctrl, CLOCKS_CLK_SYS_RESUS_CTRL_CLEAR_BITS);

    // Now we should no longer be resussed
    assert(!(clocks_hw->resus.status & CLOCKS_CLK_SYS_RESUS_STATUS_RESUSSED_BITS));

    // Call the user's callback to notify them of the resus event
    if (_resus_callback) {
        _resus_callback();
    }
}

static void clocks_irq_handler(void) {
    // Clocks interrupt handler. Only resus but handle irq
    // defensively just in case.
    uint32_t ints = clocks_hw->ints;

    if (ints & CLOCKS_INTE_CLK_SYS_RESUS_BITS) {
        ints &= ~CLOCKS_INTE_CLK_SYS_RESUS_BITS;
        clocks_handle_resus();
    }

#ifndef NDEBUG
    if (ints) {
        panic("Unexpected clocks irq\n");
    }
#endif
}

void clocks_enable_resus(resus_callback_t resus_callback) {
    // Restart clk_sys if it is stopped by forcing it
    // to the default source of clk_ref. If clk_ref stops running this will
    // not work.

    // Store user's resus callback
    _resus_callback = resus_callback;

    irq_set_exclusive_handler(CLOCKS_IRQ, clocks_irq_handler);

    // Enable the resus interrupt in clocks
    clocks_hw->inte = CLOCKS_INTE_CLK_SYS_RESUS_BITS;

    // Enable the clocks irq
    irq_set_enabled(CLOCKS_IRQ, true);

    // 2 * clk_ref freq / clk_sys_min_freq;
    // assume clk_ref is 3MHz and we want clk_sys to be no lower than 1MHz
    uint timeout = 2 * 3 * 1;

    // Enable resus with the maximum timeout
    clocks_hw->resus.ctrl = CLOCKS_CLK_SYS_RESUS_CTRL_ENABLE_BITS | timeout;
}

void clock_gpio_init_int_frac(uint gpio, uint src, uint32_t div_int, uint8_t div_frac) {
    // Bit messy but it's as much code to loop through a lookup
    // table. The sources for each gpout generators are the same
    // so just call with the sources from GP0
    uint gpclk = 0;
    if      (gpio == 21) gpclk = clk_gpout0;
    else if (gpio == 23) gpclk = clk_gpout1;
    else if (gpio == 24) gpclk = clk_gpout2;
    else if (gpio == 25) gpclk = clk_gpout3;
    else {
        invalid_params_if(CLOCKS, true);
    }

    // Set up the gpclk generator
    clocks_hw->clk[gpclk].ctrl = (src << CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_LSB) |
                                 CLOCKS_CLK_GPOUT0_CTRL_ENABLE_BITS;
    clocks_hw->clk[gpclk].div = (div_int << CLOCKS_CLK_GPOUT0_DIV_INT_LSB) | div_frac;

    // Set gpio pin to gpclock function
    gpio_set_function(gpio, GPIO_FUNC_GPCK);
}

static const uint8_t gpin0_src[CLK_COUNT] = {
    CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0, // CLK_GPOUT0
    CLOCKS_CLK_GPOUT1_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0, // CLK_GPOUT1
    CLOCKS_CLK_GPOUT2_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0, // CLK_GPOUT2
    CLOCKS_CLK_GPOUT3_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0, // CLK_GPOUT3
    CLOCKS_CLK_REF_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0,    // CLK_REF
    CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0,    // CLK_SYS
    CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0,   // CLK_PERI
    CLOCKS_CLK_USB_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0,    // CLK_USB
    CLOCKS_CLK_ADC_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0,    // CLK_ADC
    CLOCKS_CLK_RTC_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0,    // CLK_RTC
};

// Assert GPIN1 is GPIN0 + 1
static_assert(CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_CLKSRC_GPIN1 == (CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0 + 1), "hw mismatch");
static_assert(CLOCKS_CLK_GPOUT1_CTRL_AUXSRC_VALUE_CLKSRC_GPIN1 == (CLOCKS_CLK_GPOUT1_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0 + 1), "hw mismatch");
static_assert(CLOCKS_CLK_GPOUT2_CTRL_AUXSRC_VALUE_CLKSRC_GPIN1 == (CLOCKS_CLK_GPOUT2_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0 + 1), "hw mismatch");
static_assert(CLOCKS_CLK_GPOUT3_CTRL_AUXSRC_VALUE_CLKSRC_GPIN1 == (CLOCKS_CLK_GPOUT3_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0 + 1), "hw mismatch");
static_assert(CLOCKS_CLK_REF_CTRL_AUXSRC_VALUE_CLKSRC_GPIN1    == (CLOCKS_CLK_REF_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0    + 1), "hw mismatch");
static_assert(CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_CLKSRC_GPIN1    == (CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0    + 1), "hw mismatch");
static_assert(CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLKSRC_GPIN1   == (CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0   + 1), "hw mismatch");
static_assert(CLOCKS_CLK_USB_CTRL_AUXSRC_VALUE_CLKSRC_GPIN1    == (CLOCKS_CLK_USB_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0    + 1), "hw mismatch");
static_assert(CLOCKS_CLK_ADC_CTRL_AUXSRC_VALUE_CLKSRC_GPIN1    == (CLOCKS_CLK_ADC_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0    + 1), "hw mismatch");
static_assert(CLOCKS_CLK_RTC_CTRL_AUXSRC_VALUE_CLKSRC_GPIN1    == (CLOCKS_CLK_RTC_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0    + 1), "hw mismatch");

bool clock_configure_gpin(enum clock_index clk_index, uint gpio, uint32_t src_freq, uint32_t freq) {
    // Configure a clock to run from a GPIO input
    uint gpin = 0;
    if      (gpio == 20) gpin = 0;
    else if (gpio == 22) gpin = 1;
    else {
        invalid_params_if(CLOCKS, true);
    }

    // Work out sources. GPIN is always an auxsrc
    uint src = 0;

    // GPIN1 == GPIN0 + 1
    uint auxsrc = gpin0_src[clk_index] + gpin;

    if (has_glitchless_mux(clk_index)) {
        // AUX src is always 1
        src = 1;
    }

    // Set the GPIO function
    gpio_set_function(gpio, GPIO_FUNC_GPCK);

    // Now we have the src, auxsrc, and configured the gpio input
    // call clock configure to run the clock from a gpio
    return clock_configure(clk_index, src, auxsrc, src_freq, freq);
}
