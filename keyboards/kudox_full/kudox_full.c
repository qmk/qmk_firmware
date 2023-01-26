// Copyright 2021 Kumao Kobo (@kumaokobo)
// SPDX-License-Identifier: GPL-2.0+

#include "kudox_full.h"

#ifdef RGBLIGHT_ENABLE
void eeconfig_init_kb(void) {
    rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL);
};
#endif

#ifdef OLED_ENABLE
bool oled_task_kb(void) {
    if (!oled_task_user()) { return false; }
    // Host Keyboard Layer Status
    oled_write_ln_P(PSTR("Kudox Keyboard"), false);
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_ln_P(PSTR("\n"), false);
            break;
        case 1:
            oled_write_ln_P(PSTR("\nLayer: Symbol"), false);
            break;
        case 2:
            oled_write_ln_P(PSTR("\nLayer: Function"), false);
            break;
        case 3:
            oled_write_ln_P(PSTR("\nLayer: Light"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("\nLayer: Undefined"), false);
    }
    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
    return true;
}
#endif
