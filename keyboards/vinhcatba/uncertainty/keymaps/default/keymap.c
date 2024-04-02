// Copyright 2023 Vinh Le (@vinhcatba)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] =    {

    /* 0
    *        ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐
    *        │ Esc  │  F1  │  F2  │  F3  │  F4  │  F5  │  F6  │  F7  │  F8  │  F9  │  F10 │  F11 │  F12 │PrtScn│  Del │ Home │  End │ PgUp │ PgDn │
    *        ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┴──────┼──────┼──────┼──────┼──────┤
    *        │   `  │   1  │   2  │   3  │   4  │   5  │   6  │   7  │   8  │   9  │   0  │  -   │  =   │    Bksp     │ # Lk │   /  │   *  │  -   │
    * ┌──────┼──────┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬─────────┼──────┼──────┼──────┼──────┤
    * │ Mute │   Tab    │   Q  │   W  │   E  │   R  │   T  │   Y  │   U  │   I  │   O  │   P  │  [   │  ]   │    \    │  7   │  8   │  9   │      │
    * ├──────┼──────────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─────────┼──────┼──────┼──────┤  +   |
    * │ Null │   Caps     │   A  │   S  │   D  │   F  │   G  │   H  │   J  │   K  │   L  │   ;  │   '  │    Enter     │  4   │  5   │  6   │      |
    * ├──────┼────────────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴───────┬──────┼──────┤──────┼──────┼──────┤
    * │ Null │     Shft     │   Z  │   X  │   C  │   V  │   B  │   N  │   M  │   ,  │   .  │   /  │    Shft    │  Up  │  1   │  2   │  3   │      │
    * ├──────┼───────┬──────┴┬─────┴─┬────┴──────┴──────┴──────┴──────┴──────┴─────┬┴─────┬┴─────┬┴─────┬──────┼──────┼──────┼──────┼──────┤ Entr |
    * │ Null │ Ctrl  │ Gui   │ Alt   │                  Space                      │ Alt  │  Fn  │ Ctrl │ Left │ Down │ Right│  0   │   .  │      │
    * └──────┴───────┴───────┴───────┴─────────────────────────────────────────────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┘
    */
    [0] = LAYOUT(
                 KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,  KC_DEL,  KC_HOME, KC_END,  KC_PGUP, KC_PGDN,
                 KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,            KC_BSPC, KC_NUM, KC_PSLS,  KC_PAST, KC_PMNS,
        KC_MUTE, KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,           KC_BSLS, KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_CALC, KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,                    KC_ENT,  KC_P4,   KC_P5,   KC_P6,
        C(KC_V), KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,           KC_RSFT, KC_UP,   KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        C(KC_C), KC_LCTL, KC_LGUI, KC_LALT,                    KC_SPC                                    , KC_RALT, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT, KC_P0,   KC_PDOT
    ),
    [1] = LAYOUT(
                 QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_INS , KC_SCRL, _______, _______, EE_CLR ,
                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,
        OLED_TOG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,
        RGB_TOG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______,
        _______, _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, RGB_VAI, _______, _______, _______, _______,
        _______, _______, _______, _______,                    _______                                   , _______, _______, _______,RGB_RMOD, RGB_VAD, RGB_MOD, _______, _______
    )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(KC_BRID, KC_BRIU) }
};
#endif // endif ENCODER_MAP_ENABLE

#ifdef RGBLIGHT_ENABLE
#    define HSV_PASTEL_BLUE 150, 155, 51

const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_PASTEL_BLUE}       // Light 1 LED, starting with LED 0
);

const rgblight_segment_t PROGMEM my_numlock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 1, HSV_PASTEL_BLUE}       // Light 1 LED, starting with LED 1
);

const rgblight_segment_t PROGMEM indicators_off_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 2, HSV_OFF}       // Turn off 2 LEDs, starting with LED 0
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    indicators_off_layer,
    my_capslock_layer,
    my_numlock_layer
);

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(1, led_state.caps_lock);
    rgblight_set_layer_state(2, led_state.num_lock);
    return true;
}

void keyboard_post_init_user(void) {
    // debug_enable=true;
    // debug_matrix=true;

    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
    rgblight_set_layer_state(0, 1);
    rgblight_set_effect_range(2, 12);
    rgblight_enable();
}
#endif // endif RGBLIGHT_ENABLE


