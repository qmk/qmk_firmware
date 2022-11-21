/* Copyright 2021 JasonRen(biu)
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
#include "nz64.h"

#ifdef RGB_MATRIX_ENABLE

typedef union {
    uint32_t raw;
    uint8_t underground_rgb_sw :8;
} kb_cums_t;
kb_cums_t kb_cums;

led_config_t g_led_config = {
    {
        { 65,  64,  63,  62,  61,  60,  59,  58,  57,  56,  55,  54,  53,  52 },
        { 51,  50,  49,  48,  47,  46,  45,  44,  43,  42,  41,  40,  39,  38 },
        { 37,  36,  35,  34,  33,  32,  31,  30,  29,  28,  27,  26, NO_LED,  25 },
        { 24,  23,  22,  21,  20,  19,  18,  17,  16,  15,  14,  13,  12,     11 },
        { 10,  9,  8,  NO_LED,  NO_LED,  6,  NO_LED,  NO_LED,  NO_LED,  4,  3,  2,  1,  0 }
    },
    {
        /* LED Index to Physical Position */
        {224,64},{207,64},{190,64},{172,64},{155,64}, {121,64}, {86,64}, {52,64}, {34,64},{17,64},{0,64},
        {224,48},{207,48},{190,48},{172,48},{155,48},{138,48},{121,48},{103,48},{86,48},{69,48},{52,48},{34,48},{17,48},{0,48},
        {224,32},{190,32},{172,32},{155,32},{138,32},{121,32},{103,32},{86,32},{69,32},{52,32},{34,32},{17,32},{0,32},
        {224,16},{207,16},{190,16},{172,16},{155,16},{138,16},{121,16},{103,16},{86,16},{69,16},{52,16},{34,16},{17,16},{0,16},
        {224,0},{207,0},{190,0},{172,0},{155,0},{138,0},{121,0},{103,0},{86,0},{69,0},{52,0},{34,0},{17,0},{0,0},
        {0,0},{37,0},{75,0},{112,0},{149,0},{187,0},{224,0},
        {0,32},
        {224,64},{187,64},{149,64},{112,64},{75,64},{37,64},{0,64},
        {224,32}
    },
    {
      /* LED Index to Flag */
      4,4,4,4,4, 4,4,4,4,4,
      4,4,4,4,4, 4,4,4,4,4,
      4,4,4,4,4, 4,4,4,4,4,
      4,4,4,4,4, 4,4,4,4,4,
      4,4,4,4,4, 4,4,4,4,4,
      4,4,4,4,4, 4,4,4,4,4,
      4,4,4,4,4, 4,
      2,2,2,2,2, 2,2,2,2,2,
      2,2,2,2,2, 2
    }
};

void rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
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
}

void eeconfig_init_kb(void) {
    kb_cums.raw = 0;
    eeconfig_update_kb(kb_cums.raw);
}

void keyboard_post_init_kb(void) {
    kb_cums.underground_rgb_sw = eeconfig_read_kb();
}

#endif

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
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
        case LOCK_GUI:
            process_magic(GUI_TOG, record);
            return false;
        default:
            return true;
    }
    return true;
}
