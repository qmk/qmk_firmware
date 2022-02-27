/* Copyright 2022 mly32
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
 **/

#include "binds.c"

/*
Index values of keys

0   |6   |12  |18  |23  |28  |34  |39  |44  |50  |56  |61  |66  |69  |----|----|
1   |7   |13  |19  |24  |29  |35  |40  |45  |51  |57  |62  |78  |85  |----|72  |
2   |8   |14  |20  |25  |30  |36  |41  |46  |52  |58  |63  |89  |93  |----|75  |
3   |9   |15  |21  |26  |31  |37  |42  |47  |53  |59  |64  |----|96  |----|86  |
4   |----|10  |16  |22  |27  |32  |38  |43  |48  |54  |60  |----|90  |94  |82  |
5   |11  |17  |--------------|33  |--------------|49  |55  |65  |95  |97  |79  |

Index values of underglow keys

67,Side 01 | 68,Side 12
70,Side 02 | 71,Side 13
73,Side 03 | 74,Side 14
76,Side 04 | 77,Side 15
80,Side 05 | 81,Side 16
83,Side 06 | 84,Side 17
87,Side 07 | 88,Side 18
91,Side 08 | 92,Side 19
*/

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (get_mods() & MOD_MASK_CA && !(get_mods() & ~MOD_MASK_CA)) {
        /* only active mods are LCTRL, RCTRL, LALT, or RALT */
        tap_code16(clockwise ? KC_TAB : LSFT(KC_TAB));
    } else {
        tap_code16(clockwise ? KC_VOLU : KC_VOLD);
    }

    return false;
}
#endif

/* expects [0..255], [0..255], [0..255] */
RGB relative_hsv(uint8_t h, uint8_t s, uint8_t v) {
    uint8_t scaled_v = (uint16_t)v * rgb_matrix_get_val() / 255;
    return hsv_to_rgb((HSV){.h = h, .s = s, .v = scaled_v});
}

#ifdef RGB_MATRIX_ENABLE

/* rgb data tied to rgb_matrix_indicators_advanced_user evaluation */
typedef struct rgb_data {
    /* maps a key to is row and column position
     * [0, 98) -> {0..255, 0..255}
     * non 255-valued keys: 82 (88 - 6; 5 keys with no led and 1 rotary knob)
     **/
    led_point_t led_to_pos[DRIVER_LED_TOTAL];

    /* keys that will always have no rgb */
    uint8_t  dark_keys_sz;
    uint8_t* dark_keys;

    /* momentary layer keys */
    uint8_t  mo_keys_sz;
    uint8_t* mo_keys;

    /* color values */
    uint8_t dark_v;
    uint8_t white_v;
    uint8_t white_s;
    uint8_t nkro_h;
    uint8_t caps_h;
} rgb_data_t;

void init_rgb_data(rgb_data_t* t) {
    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
        t->led_to_pos[i] = (led_point_t){.x = 255, .y = 255};
    }
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        for (uint8_t j = 0; j < MATRIX_COLS; j++) {
            uint8_t idx = g_led_config.matrix_co[i][j];
            if (idx != NO_LED) {
                t->led_to_pos[idx] = (led_point_t){.x = i, .y = j};
            }
        }
    }

    uint8_t dark_keys[] = {33};
    t->dark_keys_sz     = sizeof(dark_keys) / sizeof(dark_keys[0]);
    t->dark_keys        = (uint8_t*)malloc(sizeof(dark_keys));
    for (uint8_t i = 0; i < t->dark_keys_sz; ++i) {
        t->dark_keys[i] = dark_keys[i];
    }

    uint8_t mo_keys[] = {49, 55};
    t->mo_keys_sz     = sizeof(mo_keys) / sizeof(mo_keys[0]);
    t->mo_keys        = (uint8_t*)malloc(sizeof(mo_keys));
    for (uint8_t i = 0; i < t->mo_keys_sz; ++i) {
        t->mo_keys[i]             = mo_keys[i];
        t->led_to_pos[mo_keys[i]] = (led_point_t){.x = 255, .y = 255};
    }

    t->dark_v  = 0x30;
    t->white_v = 0xFF;
    t->white_s = 0xFF;
    t->nkro_h  = 0x55;
    t->caps_h  = 0xAA;
}

rgb_data_t rgb;

void keyboard_post_init_user(void) { init_rgb_data(&rgb); }

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t l = get_highest_layer(layer_state);

    /* darken all dark keys (regardless of layer) */
    RGB dark = relative_hsv(0, 0, rgb.dark_v);
    for (uint8_t i = 0; i < rgb.dark_keys_sz; i++) {
        rgb_matrix_set_color(rgb.dark_keys[i], dark.r, dark.g, dark.b);
    }

    /* color non-default keys in non-default layers */
    RGB  gray     = relative_hsv(0, 0, rgb.white_v);
    bool nkro_off = !keymap_config.nkro;
    bool caps_on  = host_keyboard_led_state().caps_lock;
    if (nkro_off && caps_on) {
        gray = relative_hsv((rgb.nkro_h + rgb.caps_h) / 2, /* average hue */
                            rgb.white_s, rgb.white_v);
    } else if (nkro_off) {
        gray = relative_hsv(rgb.nkro_h, rgb.white_s, rgb.white_v);
    } else if (caps_on) {
        gray = relative_hsv(rgb.caps_h, rgb.white_s, rgb.white_v);
    }

    if (l != get_highest_layer(default_layer_state)) {
        for (uint8_t i = led_min; i <= led_max; i++) {
            led_point_t p = rgb.led_to_pos[i];
            if (p.x != 255 && keymaps[l][p.x][p.y] != KC_TRNS) {
                rgb_matrix_set_color(i, gray.r, gray.g, gray.b);
            }
        }
        for (uint8_t i = 0; i < rgb.mo_keys_sz; i++) {
            if (l == i + 1) {
                rgb_matrix_set_color(rgb.mo_keys[i], gray.r, gray.g, gray.b);
            }
        }
    }
}

#endif
