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
#include "bl75.h"

#ifdef RGB_MATRIX_ENABLE

led_config_t g_led_config = {
    {
        {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10,  11,  12,  13,  14},
        {29,  28,  27,  26,  25,  24,  23,  22,  21,  20,  19,  18,  17,  16,  15},
        {30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44},
        {58,  57,  56,  55,  54,  53,  52,  51,  50,  49,  48,  47,   NO_LED,  46,  45},
        {59,   NO_LED,  60,  61,  62,  63,  64,  65,  66,  67,  68,  69,  70,  71,  72},
        {83,  82,  81,   NO_LED,  80,   NO_LED,  79,   NO_LED,  78,   NO_LED,  77,  76,  75,  74,  73}
    },
    {
        {0,0},{16,0},{32,0},{48,0},{64,0},{80,0},{96,0},{112,0},{128,0},{144,0},{160,0},{176,0},{192,0},{208,0},{224,0},
        {224,13},{208,13},{192,13},{176,13},{160,13},{144,13},{128,13},{112,13},{96,13},{80,13},{64,13},{48,13},{32,13},{16,13},{0,13},
        {0,26},{16,26},{32,26},{48,26},{64,26},{80,26},{96,26},{112,26},{128,26},{144,26},{160,26},{176,26},{192,26},{208,26},{224,26},
        {224,38},{208,38},       {176,38},{160,38},{144,38},{128,38},{112,38},{96,38},{80,38},{64,38},{48,38},{32,38},{16,38},{0,38},
        {0,51},       {32,51},{48,51},{64,51},{80,51},{96,51},{112,51},{128,51},{144,51},{160,51},{176,51},{192,51},{208,51},{224,51},
        {224,64},{208,64},{192,64},{176,64},{160,64},   {128,64},             {96,64},    {64,64},             {32,64},{16,64},{0,64},
        {0,0},{15,0},{30,0},{45,0},{60,0},{75,0},{90,0},{105,0},{119,0},{134,0},{149,0},{164,0},{179,0},{194,0},{209,0},{224,0},
        {224,64},{209,64},{194,64},{179,64},{164,64},{149,64},{134,64},{119,64},{105,64},{90,64},{75,64},{60,64},{45,64},{30,64},{15,64},{0,64}
    },
    {
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4,
      2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
      2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
      2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
      2, 2
    }
};



bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }
    if (kb_config.underground_rgb_sw == 1) {
        for (uint8_t i = led_min; i < led_max; ++i) {
            if ((g_led_config.flags[i] == 4)) {
                rgb_matrix_set_color(i, 0, 0, 0);
            }
        }
    } else if (kb_config.underground_rgb_sw == 2) {
        for (uint8_t i = led_min; i < led_max; ++i) {
            if ((g_led_config.flags[i] == 2)) {
                rgb_matrix_set_color(i, 0, 0, 0);
            }
        }
    }
    return true;
}

void eeconfig_init_kb(void) {
    kb_config.raw = 0;
    eeconfig_update_kb(kb_config.raw);
    eeconfig_init_user();
}

void keyboard_post_init_kb(void) {
    kb_config.underground_rgb_sw = eeconfig_read_kb();
    rgb_matrix_reload_from_eeprom();
    keyboard_post_init_user();
}

#endif


bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    switch (keycode) {
#ifdef RGB_MATRIX_ENABLE
        case RGB_KG_T:
            if (rgb_matrix_is_enabled() && record->event.pressed) {
                kb_config.underground_rgb_sw += 1;
                kb_config.underground_rgb_sw %= 3;
                eeconfig_update_kb(kb_config.raw);
            }
            return false;
#endif
        case KC_LG:
            if (record->event.pressed) {
                process_magic(GUI_TOG, record);
            }
            return false;
        case KC_MACOS:
            if (record->event.pressed) {
                process_magic(CG_TOGG, record);
            }
            return false;
        case KC_MCTL:
            if (record->event.pressed) {
                host_consumer_send(0x29F);
            } else {
                host_consumer_send(0);
            }
            return false;
        case KC_LPAD:
            if (record->event.pressed) {
                host_consumer_send(0x2A0);
            } else {
                host_consumer_send(0);
            }
            return false;
        default:
            return true;
    }
    return true;
}

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) { return false; }
    if (index == 0) {
        if (clockwise) {
            tap_code_delay(KC_VOLU, 10);
        } else {
            tap_code_delay(KC_VOLD, 10);
        }
    }
    return true;
}
#endif
