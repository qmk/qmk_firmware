/* Copyright 2024 XD Boards <copyright@xdboards.xyz>
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
oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
   return OLED_ROTATION_180;
}

bool oled_task_kb(void) {
    if (!oled_task_user()) {
       return false;
    }
    if (is_keyboard_master()) {
        // Host Keyboard Layer Status
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state | default_layer_state)) {
            case 0:
                oled_write_P(PSTR("QWERTY\n"), false);
                break;
            case 1:
                oled_write_P(PSTR("Symbols\n"), false);
                break;
            case 2:
                oled_write_P(PSTR("Numbers\n"), false);
                break;
            case 3:
                oled_write_P(PSTR("Function\n"), false);
                break;
            case 4:
                oled_write_P(PSTR("RGB\n"), false);
                break;
            default:
                oled_write_P(PSTR("Undefined\n"), false);
        }
        // Host Keyboard LED Status
        led_t led_usb_state = host_keyboard_led_state();
        oled_write_P(PSTR("CAPSLCK"), led_usb_state.caps_lock);
        oled_write_P(PSTR(" "), false);
        oled_write_P(PSTR("NUMLCK"), led_usb_state.num_lock);
        oled_write_P(PSTR(" "), false);
        oled_write_P(PSTR("SCRLCK"), led_usb_state.scroll_lock);
        oled_write_P(PSTR("\n"), false);

        oled_write_P(PSTR("\n"), false);

        static const char PROGMEM qmk_logo[] = {
            0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
            0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
            0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
        };

        oled_write_P(qmk_logo, false);

    } else {
        // clang-format off
        static const char PROGMEM recon_logo[] = {
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,254,254,254,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,224,240,240,248,252,124,126, 62, 62, 31, 31, 31,  0,  0,  0,255,255,255,  0,  0, 31, 31, 31, 62, 62, 62,124,252,248,248,240,224,192,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,128,224,248,252,255,127, 31, 15,  7,  3,  1,  0,  0,  0,  0,128,192,224,224,240,240,240,115,115,115,240,240,224,224,192,192,128,  0,  0,  0,  0,  1,  3,  7, 15, 63,255,254,252,240,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
          192,192,192,192,192,192,192,204,207,207,207,207,193,192,192,192,192,  0,  0,224,248,254,255, 15,  7,  3,  1,  0,192,224,224,224,224,192,  0,  1,  1,  3,  7, 63,255,252,240,  0,  0,192,192,192,192,192,199,207,207,207,207,192,192,192,192,192,192,192,128,  0,254,254,254,254,254,  0,134,254,254,252,124, 48,  0,  0,254,254,254,254,254,252,134,230,222, 62,  0,224,248,252,252,254,  6,  2,  6, 14, 62,126,  0,224,248,252,254,254,  6,  6,254,254,252,248,240,  0,  6,238,254,126,254,254,252,240,224,134,254, 14,  6,  0,
            3,  3,  3,  3,  3,  3,  3, 51,243,243,243,243,131,  3,  3,  3,  3,  0,  0,  7, 31,127,255,240,224,192,128,  0,  1,  7,  7,  7,  7,  3,  0,128,128,192,224,252,255, 63, 15,  0,  0,  3,  3,  3,  3,  3,227,243,243,243,243,  3,  3,  3,  3,  3,  3,  3,  1, 64,127,127,127,127,127, 97,  3,127,127,127,126,120, 48,  0,127,127,127,127,127, 63, 97,103,119,124, 48, 15, 31, 63,127,127, 96, 64, 96, 96, 48, 24,  0, 15, 31, 63,127,127, 64, 64,127,127, 63, 63, 15,  0, 64,127,127, 96,  1,  7, 15, 63,127,127,127,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  1,  7, 31, 63,255,254,248,240,224,192,128,  0,  0,  0,  0,  1,  3,  7,  7,  7, 15, 15,207,206,207, 15, 15,  7,  7,  3,  3,  1,  0,  0,  0,  0,128,192,224,248,252,255,127, 63, 15,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  3,  7, 15, 15, 31, 63, 62,126,124,124,248,248,248,  0,  0,  0,255,255,255,  0,  0,248,248,248,124,124,124, 62, 63, 31, 15, 15,  7,  3,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,127,127,127,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        };
        // clang-format on
        oled_write_raw_P(recon_logo, sizeof(recon_logo));
    }
    return false;
}
#endif
#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
       return false;
    }

    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
       // Page up/Page down
        if (clockwise) {
#ifdef MOUSEKEY_ENABLE
            tap_code(MS_WHLU);
#else
            tap_code(KC_PGUP);
#endif
        } else {
#ifdef MOUSEKEY_ENABLE
            tap_code(MS_WHLD);
#else
            tap_code(KC_PGDN);
#endif
        }
    }
    return true;
}
#endif