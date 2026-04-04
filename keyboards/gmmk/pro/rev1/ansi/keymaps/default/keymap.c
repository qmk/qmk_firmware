/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12      Prt           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)      BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      CapsWrd  A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right

    [0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,          KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGDN,
        CW_TOGG, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_END,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_DEL,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [1] = LAYOUT(
        _______, KC_MYCM, KC_WHOM, KC_CALC, KC_MSEL, KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______,          QK_BOOT,
        _______, RM_TOGG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, RM_VALU, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, RM_VALD, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, RM_HUEU, _______, _______, _______, NK_TOGG, _______, _______, _______, _______,          QK_REP,  RM_NEXT, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, RM_SPDD, RM_PREV, RM_SPDU
    ),

};
// clang-format on

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) }
};
#endif

#ifdef RGB_MATRIX_ENABLE

// Side LEDs: left column l01-l08, right column l11-l18
static const uint8_t PROGMEM side_leds[] = {
    67, 70, 73, 76, 80, 83, 87, 91,  // left side
    68, 71, 74, 77, 81, 84, 88, 92   // right side
};

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
// Scale full-brightness colors down to RGB_MATRIX_MAXIMUM_BRIGHTNESS
#define INDICATOR_AMBER RGB_MATRIX_MAXIMUM_BRIGHTNESS, (RGB_MATRIX_MAXIMUM_BRIGHTNESS * 160 / 255), 0
#define INDICATOR_RED   RGB_MATRIX_MAXIMUM_BRIGHTNESS, 0, 0
#define INDICATOR_CYAN  0, RGB_MATRIX_MAXIMUM_BRIGHTNESS, RGB_MATRIX_MAXIMUM_BRIGHTNESS

    if (is_caps_word_on()) {
        // Caps Word active: amber on Caps Lock key + all side LEDs
        rgb_matrix_set_color(3, INDICATOR_AMBER);
        for (uint8_t i = 0; i < sizeof(side_leds); i++) {
            rgb_matrix_set_color(pgm_read_byte(&side_leds[i]), INDICATOR_AMBER);
        }
    } else if (host_keyboard_led_state().caps_lock) {
        // Caps Lock active: red on Caps Lock key + all side LEDs
        rgb_matrix_set_color(3, INDICATOR_RED);
        for (uint8_t i = 0; i < sizeof(side_leds); i++) {
            rgb_matrix_set_color(pgm_read_byte(&side_leds[i]), INDICATOR_RED);
        }
    }

    // FN key LED (index 55): cyan while layer 1 is held
    if (get_highest_layer(layer_state) > 0) {
        rgb_matrix_set_color(55, INDICATOR_CYAN);

        // All 16 side LEDs: cyan while layer 1 is active
        for (uint8_t i = 0; i < sizeof(side_leds); i++) {
            rgb_matrix_set_color(pgm_read_byte(&side_leds[i]), INDICATOR_CYAN);
        }
    }

    return false;
}
#endif
