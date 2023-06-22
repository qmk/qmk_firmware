/* Copyright 2022 Kyle McCreery
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

#include "quantum.h"

#ifdef OLED_ENABLE
static const char PROGMEM mw_logo[] = {
    0x8A, 0x8B, 0x8C, 0x8D, '\r',
    0xAA, 0xAB, 0xAC, 0xAD, 0xAE,
    0xCA, 0xCB, 0xCC, 0xCD, '\r',
    0x20, 0x8E, 0x8F, 0x90, 0x00};

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return OLED_ROTATION_270;       // flips the display 270 degrees
}

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }

    oled_write_P(mw_logo, false);     // Render MechWild "MW" Logo
    oled_set_cursor(0,6);

    oled_write_ln_P(PSTR("Layer"), false);

    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_ln_P(PSTR("Base"), false);
            break;
        case 1:
            oled_write_ln_P(PSTR("FN 1"), false);
            break;
        case 2:
            oled_write_ln_P(PSTR("FN 2"), false);
            break;
        case 3:
            oled_write_ln_P(PSTR("FN 3"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
    oled_write_ln_P(PSTR(""), false);
    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_ln_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_ln_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_ln_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);

    return true;
}
#endif
