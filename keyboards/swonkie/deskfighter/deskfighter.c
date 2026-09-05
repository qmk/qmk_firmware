// Copyright 2026 Swonkie swonkie@pm.me
// SPDX-License-Identifier: GPL-3.0-or-later

#include "quantum.h"

#define NUM_LED_PIN A3
#define CAPS_LED_PIN B9

void keyboard_pre_init_kb(void) {
    // Disable dead battery check to avoid pull-down on B6.
    // See page 62, footnote 5:
    // https://www.st.com/resource/en/datasheet/stm32g491ce.pdf#page=62
    PWR->CR3 |= PWR_CR3_UCPD_DBDIS;

    gpio_set_pin_output(NUM_LED_PIN);
    gpio_set_pin_output(CAPS_LED_PIN);

    keyboard_pre_init_user();
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    // Make the num LED reflect the state of the numbers layer.
    // This layer is like a numeric keypad, but overlayed on the
    // right hand position, similar to some laptop keyboards.
    gpio_write_pin(NUM_LED_PIN, IS_LAYER_ON_STATE(state, 1));

    return state;
}
