// Copyright 2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

void bootloader_jump(void) {
    // TODO: Work out how to jump to LDROM, for now just reset the board.
    NVIC_SystemReset();
}

#if defined(RGB_MATRIX_ENABLE) && defined(CAPS_LOCK_LED_INDEX)
bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(CAPS_LOCK_LED_INDEX, 0xFF, 0xFF, 0xFF);
    }
    return true;
}
#endif
