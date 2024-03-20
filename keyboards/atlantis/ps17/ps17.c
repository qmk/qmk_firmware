// Copyright 2023 mjbogusz (@mjbogusz)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

layer_state_t layer_state_set_kb(layer_state_t state) {
    /* Display current layer using indicator LEDs */
    writePin(LED_INDICATOR_0_PIN, !IS_LAYER_ON_STATE(state, 1));
    writePin(LED_INDICATOR_1_PIN, !IS_LAYER_ON_STATE(state, 2));
    writePin(LED_INDICATOR_2_PIN, !IS_LAYER_ON_STATE(state, 3));
    return layer_state_set_user(state);
}

void keyboard_pre_init_kb(void) {
    /* Set indicator LEDs as outputs */
    setPinOutput(LED_INDICATOR_0_PIN);
    setPinOutput(LED_INDICATOR_1_PIN);
    setPinOutput(LED_INDICATOR_2_PIN);
    keyboard_pre_init_user();
}

#if defined(ENCODER_ENABLE)
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
        /* Don't process further events if user function exists and returns false */
        return false;
    }

    /* Ignore index - only one encoder on this board */
    if (clockwise) {
        tap_code_delay(KC_VOLU, 10);
    } else {
        tap_code_delay(KC_VOLD, 10);
    }
    return false;
}
#endif

#ifdef RGB_MATRIX_ENABLE
void suspend_power_down_kb(void) {
    /* Disable indicator LEDs when going to sleep */
    writePin(LED_INDICATOR_0_PIN, 1);
    writePin(LED_INDICATOR_1_PIN, 1);
    writePin(LED_INDICATOR_2_PIN, 1);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    /* Restore indicator LEDs state */
    layer_state_set_kb(layer_state);
    suspend_wakeup_init_user();
}
#endif
