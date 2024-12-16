// Copyright 2024 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"


void board_init(void) {

    gpio_set_pin_output(A15);
    gpio_write_pin_high(A15); // Activate D+ pullup

    gpio_set_pin_output(OPTICAL_SW_PWR);
    gpio_write_pin_low(OPTICAL_SW_PWR); // Enable power for optical switches

}

