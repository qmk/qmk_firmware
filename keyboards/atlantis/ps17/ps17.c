// Copyright 2023 mjbogusz (@mjbogusz)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

layer_state_t layer_state_set_kb(layer_state_t state) {
    /* Display current layer using indicator LEDs */
    gpio_write_pin(LED_INDICATOR_0_PIN, !IS_LAYER_ON_STATE(state, 1));
    gpio_write_pin(LED_INDICATOR_1_PIN, !IS_LAYER_ON_STATE(state, 2));
    gpio_write_pin(LED_INDICATOR_2_PIN, !IS_LAYER_ON_STATE(state, 3));
    return layer_state_set_user(state);
}

void keyboard_pre_init_kb(void) {
    /* Set indicator LEDs as outputs */
    gpio_set_pin_output(LED_INDICATOR_0_PIN);
    gpio_set_pin_output(LED_INDICATOR_1_PIN);
    gpio_set_pin_output(LED_INDICATOR_2_PIN);
    keyboard_pre_init_user();
}

#ifdef RGB_MATRIX_ENABLE
void suspend_power_down_kb(void) {
    /* Disable indicator LEDs when going to sleep */
    gpio_write_pin(LED_INDICATOR_0_PIN, 1);
    gpio_write_pin(LED_INDICATOR_1_PIN, 1);
    gpio_write_pin(LED_INDICATOR_2_PIN, 1);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    /* Restore indicator LEDs state */
    layer_state_set_kb(layer_state);
    suspend_wakeup_init_user();
}
#endif
