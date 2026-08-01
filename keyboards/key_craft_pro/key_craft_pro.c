// Copyright 2026 Anefecious
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

void keyboard_pre_init_kb(void) {
    gpio_set_pin_input_high(ENC_L_BTN_PIN);
    gpio_set_pin_input_high(ENC_R_BTN_PIN);
    keyboard_pre_init_user();
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    // Vertical SSD1306 — try OLED_ROTATION_90 if upside down.
    return OLED_ROTATION_270;
}
#endif
