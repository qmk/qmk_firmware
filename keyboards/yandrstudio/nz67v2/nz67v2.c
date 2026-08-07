/* Copyright 2022 JasonRen(biu)
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
#include "nz67v2.h"

#ifdef RGB_MATRIX_ENABLE

/* globol var store in eeprom for key and underground rgb switch */
typedef union {
    uint32_t raw;
    uint8_t underground_rgb_sw :8;
} kb_cums_t;
kb_cums_t kb_cums;

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }
    if (rgb_matrix_is_enabled()) {
        if (kb_cums.underground_rgb_sw == 1) {
            for (uint8_t i = led_min; i < led_max; ++i) {
                if ((g_led_config.flags[i] == 4)) {
                    rgb_matrix_set_color(i, 0, 0, 0);
                }
            }
        } else if (kb_cums.underground_rgb_sw == 2) {
            for (uint8_t i = led_min; i < led_max; ++i) {
                if ((g_led_config.flags[i] == 2)) {
                    rgb_matrix_set_color(i, 0, 0, 0);
                }
            }
        }
    } else {
        rgb_matrix_set_color_all(0,0,0);
    }
    if (host_keyboard_led_state().caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(25, rgblight_get_val(), rgblight_get_val(), rgblight_get_val());
    }
    return true;
}


void eeconfig_init_kb(void) {
    kb_cums.raw = 0;
    eeconfig_update_kb(kb_cums.raw);

    eeconfig_init_user();
}

void keyboard_post_init_kb(void) {
    kb_cums.underground_rgb_sw = eeconfig_read_kb();

    keyboard_post_init_user();
}

#endif



bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) { return false; }

    switch(keycode) {
#ifdef RGB_MATRIX_ENABLE
        case URGB_K:
            if (rgb_matrix_config.enable && record->event.pressed) {
                kb_cums.underground_rgb_sw += 1;
                kb_cums.underground_rgb_sw %= 3;
            }
            eeconfig_update_kb(kb_cums.raw);
            return false;
#endif
        default:
            break;
    }
    return true;
}

void board_init(void) {
    AFIO->MAPR |= AFIO_MAPR_TIM3_REMAP_PARTIALREMAP;
}
