/* Copyright 2021 Koobaczech
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "zeuspad.h"

// 21 characters max
#ifdef OLED_ENABLE
bool oled_task_kb(void) {
    if (oled_task_user()) {
        return false;
    }
    oled_write_P(PSTR("ZEUSPAD BY KOOBACZECH"), false);
    // Keyboard Layer Status
    oled_write_P(PSTR("LAYER: "), false);

    switch (get_highest_layer(layer_state)) {
        case 1:
            oled_write_ln_P(PSTR("FN"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Default"), false);
    }
    // Keyboard Locking Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.caps_lock ? PSTR("CAPS  ") : PSTR("      "), false);
    oled_write_P(led_state.num_lock ? PSTR("NUM  ") : PSTR("     "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR  ") : PSTR("     "), false);

    switch (rgblight_is_enabled() ? 1 : 2) {
        case 1:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_P(PSTR("RGB"), false);
            static char led_buf[30];
            snprintf(led_buf, sizeof(led_buf) - 1, "\nMODE:%2d BRIGHT:%2d/10", (uint8_t)(rgblight_get_mode()), (uint8_t)(rgblight_get_val() / 25.5));
            oled_write(led_buf, false);
            break;
        default:
            oled_write_ln_P(PSTR(""), false);
            oled_write_P(PSTR("\n"), false);
    }

    return true;
}
#endif
