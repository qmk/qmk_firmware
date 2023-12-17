// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// layer names
enum layer_names {
    _BASE,
    _MACROS
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
        KC_MUTE, KC_COMM, KC_PSLS, KC_PAST,  KC_PMNS,
        KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_P4,   KC_P5,   KC_P6,
        KC_P1,   KC_P2,   KC_P3, 
        TO(1), KC_P0,   KC_PDOT,  KC_PENT
    ),
    [1] = LAYOUT_numpad_5x5(
        _______,   _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,
        _______,   _______,   _______,
        _______,   _______,   _______, 
        TO(0),   _______,   _______,   _______
    )
};

// rotary encoder
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [1] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) }
};
#endif

// oled image

// cat closed mouth image
static void render_cat(void) {
    static const char PROGMEM raw_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192, 64, 64,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64, 32,160, 64,128,  0,  0,  0,  0,  0,  0, 31, 96,158,126,254,252,251,230, 46, 24, 24,152,136,204, 66,130,  2,  2,  2,  1,  0, 64,175, 79,  0,255,  0,  0,  0,  0,  0,  0,  0,  0,  1,  6, 56,241,243,240,248, 28,  4,  0,  0,  1, 49, 16, 16,  0,  0,  0, 36, 36, 16, 16,  0,128,  1,194, 60, 
        0,  0,  0,  0,  0,  0,  0,192, 49, 15, 15, 12,  6,  0,128,192,224,240,248,248,252,252,252,252,252,254,254,193, 60,194,  1,  0,  0,  0,128, 64, 48, 12,  3,  0,  0,  0,  0,  0,  0,  0,  7, 31,127,255,255,255,255,255,255,255,255,255,255,255,248,  7,248,  0,224, 30,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,255,255,255,255,255,255,255,255,255,255,255,254,255,  0,
    };

    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

// cat yawn mouth image
static void render_cat_yawn(void) {
    static const char PROGMEM raw_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64,160, 32,192,  0,  0,  0,  0,  0,  0,  7,124,192, 60,252,253,249,226,  4,  4,  8,  8, 72,100, 36, 34,  2,  2,130,162,163,131,131,136,152,  1, 30, 32, 64,128,  0,  0,  0,  0,  1,  2, 28, 49,243,243, 56,  0,  0,  0,  0,240,252,254,254,255,255,255,255,255,255,255,255,255,254,252,120,  1,254, 
        0,  0,  0,  0,  0,  0,192, 33, 31,  7,  0,  0,  0,  0,193,195,135,135,143,159,159,159,159,159,159,143, 79,199, 33, 16, 14,  1,  0,  0,192, 48, 12,  3,  0,  0,  0,  0,  0,  0,  0,  0,  1,  3,255,255,255,255,255,255,255,255,255,255,240,207, 56,192,  0,  0,248,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,255,255,255,255,255,255,255,255,255,255,255,248,255,  0,  0,
    };

    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

// oled
#if defined(OLED_ENABLE)

// oled fix for 'cold boot' not turning on
void keyboard_post_init_user(void) {
    wait_ms(2000);
    oled_init(OLED_ROTATION_0);
}

// rotate oled
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_90;  
}

// change image on keypress tracker
bool oled_tracker = false;
bool process_record_user(uint16_tkeycode, keyrecord_t *record) {
    if (record->event.pressed) {
        oled_tracker ^= 1;
    }
    return true;
}

bool oled_task_user(void) {

    // Host Keyboard Layer Status
    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_ln_P(PSTR("Base"), false);
            break;
        case _MACROS:
            oled_write_ln_P(PSTR("Func"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    // render cat and cat_yawn on keypress
    if (oled_tracker) {
        oled_write_P(render_cat();, false);
    } else {
        oled_write_P(render_cat_yawn();, false);
    }

    return false;
}
#endif