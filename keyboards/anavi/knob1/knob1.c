// Copyright 2022 Leon Anavi <leon@anavi.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include <stdio.h>

void keyboard_post_init_kb(void) {
    // Enable RGB LED
    setPinOutput(GP11);
    writePinHigh(GP11);
    rgblight_enable();

    // Offload to the user func
    keyboard_post_init_user();
}

#ifdef OLED_ENABLE

bool oled_task_kb(void) {

    if (!oled_task_user()) {
        return false;
    }

    // Host Keyboard Layer Status
    oled_write_ln_P(PSTR("ANAVI Knob 1"), false);
    oled_write_ln_P(PSTR("Keymap: Default"), false);

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(PSTR("Num Lock: "), false);
    oled_write_ln_P(led_state.num_lock ? PSTR("On") : PSTR("Off"), false);
    oled_write_P(PSTR("Caps Lock: "), false);
    oled_write_ln_P(led_state.caps_lock ? PSTR("On") : PSTR("Off"), false);
    oled_write_P(PSTR("Scroll Lock: "), false);
    oled_write_ln_P(led_state.scroll_lock ? PSTR("On") : PSTR("Off"), false);
#ifdef RGBLIGHT_ENABLE
    static char rgbStatusLine1[26] = {0};
    snprintf(rgbStatusLine1, sizeof(rgbStatusLine1), "RGB Mode: %d", rgblight_get_mode());
    oled_write_ln(rgbStatusLine1, false);
    static char rgbStatusLine2[26] = {0};
    snprintf(rgbStatusLine2, sizeof(rgbStatusLine2), "h:%d s:%d v:%d", rgblight_get_hue(), rgblight_get_sat(), rgblight_get_val());
    oled_write_ln(rgbStatusLine2, false);
#endif
    return false;
}
#endif
