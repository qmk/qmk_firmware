// Copyright 2024 zvecr <git@zvecr.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

void keyboard_pre_init_kb(void) {
    // Workaround for reversible pcb/mcu
    gpio_set_pin_output_open_drain(C13);
    gpio_set_pin_output_open_drain(B9);
    gpio_set_pin_output_open_drain(B8);

    keyboard_pre_init_user();
}

void board_init(void) {
    AFIO->MAPR |= AFIO_MAPR_USART1_REMAP | AFIO_MAPR_TIM3_REMAP_PARTIALREMAP;
}
