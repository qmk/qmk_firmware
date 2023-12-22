/*
Copyright 2023 kevin (@itskevin-zz)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

enum layer_names {
    _BASE,
    _FUNC
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┐     
     * │ e │NUM│ / │ * │ - │
     * ├───┼───┼───┼───┼───┤
     * │   │ 7 │ 8 │ 9 │   │
     * │   ├───┼───┼───┤ + │
     * │   │ 4 │ 5 │ 6 │   │
     * │   ├───┼───┼───┼───┤
     * │   │ 1 │ 2 │ 3 │   │
     * ├───┼───┴───┼───┤ ← │
     * │ D │   0   │ . │   │
     * └───┴───────┴───┴───┘
     */
    [0] = LAYOUT_numpad_5x5(
        KC_MUTE, KC_NUM, KC_PSLS, KC_PAST,  KC_PMNS,
        KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_P4,   KC_P5,   KC_P6,
        KC_P1,   KC_P2,   KC_P3, 
        TO(1), KC_P0,   KC_PDOT,  KC_PENT
    ),
    [1] = LAYOUT_numpad_5x5(
        _______,   _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,
        _______,   KC_W,   _______,
        KC_A,   KC_S,   KC_D, 
        TO(0),   KC_K,   _______,   _______
    )
};


#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [1] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) }
};
#endif

/* oled images */

static void render_base_layer(void) {
    static const char PROGMEM raw_base_layer[] = {
        0,  0,  0,  0,  0,  0,  0,  0,128,192,192,224,224,240,240,248,248,248,240,224,224,192,192,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,134,134,207, 79,127, 63, 63,127,127,255,255,255,255,255,255,127,127, 63, 63,127, 79,207,134,134,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  2,  6, 12, 12, 24, 16, 48, 97, 97, 97, 48, 48, 24, 24, 12,  4,  6,  3,  3,  1,  1,  0,  0,  0,  0,
    };

    oled_write_raw_P(raw_base_layer, sizeof(raw_base_layer));
}

static void render_func_layer(void) {
    static const char PROGMEM raw_func_layer[] = {
        0,  0,  0,  0,  0,  0,  0,  0,128,128,192, 96, 96, 48, 16, 24, 24, 24, 48, 32, 96,192,192,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,134,134,207,201,249,240,240,224,224,192,128,128,128,128,192,224,224,240,240,249,205,207,134,134,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  3,  7, 15, 15, 31, 31, 63,127,127,127, 63, 63, 31, 31, 15, 15,  7,  3,  3,  1,  1,  0,  0,  0,  0,
    };

    oled_write_raw_P(raw_func_layer, sizeof(raw_func_layer));
}



/* cat closed mouth image; image from https://github.com/codeyfrommars/Gamepad */
static void render_cat(void) {
    static const char PROGMEM raw_cat[] = {
        0,  0,  0,248,  6,242,242,244,228,216, 48,112,192,192,192, 64, 96, 16, 16, 16, 16, 16,  8,  4,  2,121,125,  2,252,  0,  0,  0,  0,  0,  0,  0,  3, 12, 51,199,143,159,135,193,224, 32,  4,  4, 14,138,132,128,  0,  0,  0, 32, 34,133,130,  0,  7,  8, 16,224,  0,  0,  0,  0,  0,  0,  0,  1,143,127,127,103, 48,  0,  0,  0,  0,129,192,192,224,224,224,225,225,240,240,  8,228, 16, 14,  1,  0,  0,  0,  0,128, 96, 24,  6,  1,  0,  0,  0,  0,  0, 60,254,255,255,255,255,255,255,255,255,255,255,255,254,193, 62,192,  0,
        0,240, 12,  2,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,255,255,255,255,255,255,255,255,255,255,255,255,240,255,  0,
    };

    oled_write_raw_P(raw_cat, sizeof(raw_cat));
}

/* cat yawn mouth image; image from https://github.com/codeyfrommars/Gamepad */
static void render_cat_yawn(void) {
    static const char PROGMEM raw_cat_yawn[] = {
        0, 56,228,  4,228,228,232,200, 16, 32, 32, 64, 64, 64, 32, 32, 16, 16, 16, 16, 16, 24, 28, 26, 69,193, 14,240,  0,  0,  0,  0,  0,  0,  3, 14, 17,231,143,159,159,192,  0,  0,  0,  2,131,225,241,240,248,252,253,253,252,252,252,252,248,240,225,194, 12,240,  0,  0,  0,  0,  0,  0,  1, 15,255, 57,  0,  0,  0,  0, 15, 31, 63, 63,127,255,255,255,255,255,255,127,127, 63, 15,131,112, 15,  0,  0,  0,128, 96, 24,  6,  1,  0,  0,  0,  0,  0,  0, 14, 30,252,252,252,252,252,252,252,252,252,252,130,126,193,  0,  0, 
        0,192, 56,  6,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 31,255,255,255,255,255,255,255,255,255,255,254,193,254,  0,  0,
    };

    oled_write_raw_P(raw_cat_yawn, sizeof(raw_cat_yawn));
}


#if defined(OLED_ENABLE)

/* oled fix for 'cold boot' */
void keyboard_post_init_user(void) {
    wait_ms(2000);
    oled_init(OLED_ROTATION_0);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_90;  
}

/* change image on keypress tracker */
bool oled_tracker = false;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        oled_tracker ^= 1;
    }
    return true;
}

bool oled_task_user(void) {

    oled_set_cursor(0,0);
    switch (get_highest_layer(layer_state)) {
        case _BASE:
            render_base_layer();
            oled_write_ln_P(PSTR("Base"), false);
            break;
        case _FUNC:
            render_func_layer();
            oled_write_ln_P(PSTR("Func"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    oled_set_cursor(0,11);
    if (oled_tracker) {
        render_cat();
    } else {
        render_cat_yawn();
    }

    return false;
}
#endif