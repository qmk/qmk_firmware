// Copyright 2023 Leon Anavi <leon@anavi.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#ifdef OLED_ENABLE

bool oled_task_kb(void) {

    if (!oled_task_user()) {
        return false;
    }

    // Host Keyboard Layer Status
    oled_write_ln_P(PSTR("ANAVI Arrows"), false);
    oled_write_ln_P(PSTR("Keymap: Default"), false);

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(PSTR("Num Lock: "), false);
    oled_write_ln_P(led_state.num_lock ? PSTR("On") : PSTR("Off"), false);
    oled_write_P(PSTR("Caps Lock: "), false);
    oled_write_ln_P(led_state.caps_lock ? PSTR("On") : PSTR("Off"), false);
    oled_write_P(PSTR("Scroll Lock: "), false);
    oled_write_ln_P(led_state.scroll_lock ? PSTR("On") : PSTR("Off"), false);
#   ifdef RGBLIGHT_ENABLE
        oled_write_P(PSTR("RGB Mode: "), false);
        oled_write_ln(get_u8_str(rgblight_get_mode(), ' '), false);
        oled_write_P(PSTR("h: "), false);
        oled_write(get_u8_str(rgblight_get_hue(), ' '), false);
        oled_write_P(PSTR("s: "), false);
        oled_write(get_u8_str(rgblight_get_sat(), ' '), false);
        oled_write_P(PSTR("v: "), false);
        oled_write_ln(get_u8_str(rgblight_get_val(), ' '), false);
#   endif
    return false;
}
#endif
