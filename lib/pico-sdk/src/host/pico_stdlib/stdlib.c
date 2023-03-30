/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"

void setup_default_uart() {

}

void set_sys_clock_48mhz() {

}

bool check_sys_clock_khz(uint32_t freq_khz, uint *vco_out, uint *postdiv1_out, uint *postdiv2_out) {
    *vco_out = 1000000;
    *postdiv1_out = 0;
    *postdiv2_out = 0;
    return true;
}

void set_sys_clock_pll(__unused uint32_t vco_freq, __unused uint post_div1, __unused uint post_div2) {

}

