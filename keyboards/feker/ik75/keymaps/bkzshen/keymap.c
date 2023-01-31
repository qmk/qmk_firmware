/* Copyright 2022 Feker
 * Copyright 2022 HorrorTroll <https://github.com/HorrorTroll>
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

#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum layer_names {
    _BASE,
    _FN,
    _FN1,
    _FN2,
};

// enum layer_keycodes { };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
       ┌───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐┌───┐ ┌───┐
       │Esc││F1 │F2 │F3 │F4 ││F5 │F6 │F7 │F8 ││F9 │F10│F11│F12││Del│ │Mut│
       └───┘└───┴───┴───┴───┘└───┴───┴───┴───┘└───┴───┴───┴───┘└───┘ └───┘
       ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┐
       │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ Bckspc│ │Hom│
       ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┤
       │ Tab │ q │ w │ e │ r │ t │ y │ u │ i │ o │ p │ [ │ ] │  \  │ │End│
       ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ ├───┤
       │ Caps │ a │ s │ d │ f │ g │ h │ j │ k │ l │ ; │ ' │  Enter │ │PgU│
       ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┘ ├───┤
       │ LShift │ z │ x │ c │ v │ b │ n │ m │ , │ . │ / │ RSft │┌───┐│PgD│
       ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┘│ ↑ │└───┘
       │LCrl│GUI │LAlt│         Space          │RAt│Fn │Rcl│┌───┼───┼───┐
       └────┴────┴────┴────────────────────────┴───┴───┴───┘│ ← │ ↓ │ → │
                                                            └───┴───┴───┘
       ┌───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐┌───┐ ┌───┐
       │   ││   │   │   │   ││   │   │   │   ││   │   │   │   ││   │ │   │
       └───┘└───┴───┴───┴───┘└───┴───┴───┴───┘└───┴───┴───┴───┘└───┘ └───┘
       ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┐
       │   │ ! │ @ │ # │ $ │ % │ ^ │ & │ * │ ( │ ) │ _ │ + │       │ │   │
       ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┤
       │     │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ { │ } │  |  │ │   │
       ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ ├───┤
       │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ : │ " │        │ │   │
       ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┘ ├───┤
       │ LShift │ Z │ X │ C │ V │ B │ N │ M │ < │ > │ ? │ RSft │┌───┐│   │
       ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┘│   │└───┘
       │    │    │    │                        │   │   │   │┌───┼───┼───┐
       └────┴────┴────┴────────────────────────┴───┴───┴───┘│   │   │   │
                                                            └───┴───┴───┘
*/
    /*  Row:    0        1        2        3      4      5      6       7      8      9        10       11       12       13       14       15     */
    [_BASE] = LAYOUT(
                KC_ESC,  KC_F1,   KC_F2,   KC_F3, KC_F4, KC_F5, KC_F6,  KC_F7, KC_F8, KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,           KC_MUTE,
                KC_GRV,  KC_1,    KC_2,    KC_3,  KC_4,  KC_5,  KC_6,   KC_7,  KC_8,  KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_HOME,
                KC_TAB,  KC_Q,    KC_W,    KC_E,  KC_R,  KC_T,  KC_Y,   KC_U,  KC_I,  KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_END,
                KC_CAPS, KC_A,    KC_S,    KC_D,  KC_F,  KC_G,  KC_H,   KC_J,  KC_K,  KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP,
                KC_LSFT,          KC_Z,    KC_X,  KC_C,  KC_V,  KC_B,   KC_N,  KC_M,  KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_PGDN,
                KC_LCTL, KC_LGUI, KC_LALT,                      KC_SPC,               KC_RALT, MO(_FN),          KC_RCTL, KC_LEFT, KC_DOWN, KC_RIGHT
            ),

/*
       ┌───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐┌───┐ ┌───┐
       │Rst││Mcm│Hom│Cal│Sel││Prv│Nxt│Ply│Stp││Mut│VoD│VoU│Mai││Ins│ │Tog│
       └───┘└───┴───┴───┴───┘└───┴───┴───┴───┘└───┴───┴───┴───┘└───┘ └───┘
       ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┐
       │NKO│   │   │   │   │   │   │   │   │   │   │Spd│Spi│       │ │Mod│
       ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┤
       │     │   │   │   │   │   │   │   │   │   │Prt│   │   │     │ │Hui│
       ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ ├───┤
       │      │   │Scr│   │   │   │   │   │   │   │   │   │        │ │Sai│
       ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┘ ├───┤
       │        │   │   │   │   │   │Num│   │   │   │   │      │┌───┐│Sad│
       ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─────┘│Vai│└───┘
       │    │GTog│    │                        │    │    │  ┌───┼───┼───┐
       └────┴────┴────┴────────────────────────┴────┴────┘  │   │Vad│   │
                                                            └───┴───┴───┘
*/
    /*  Row:    0        1        2        3        4        5        6        7        8        9        10       11       12       13       14       15     */
    [_FN] = LAYOUT(
                QK_BOOT, KC_MYCM, KC_WHOM, KC_CALC, KC_SLCT, KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP, KC_MUTE, KC_VOLD, KC_VOLU, KC_MAIL, KC_INS,           RGB_TOG,
                NK_TOGG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_SPD, RGB_SPI, _______,          RGB_MOD,
                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PSCR, _______, _______, _______,          RGB_HUI,
                _______, _______, KC_SCRL, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, RGB_SAI,
                _______,          _______, _______, _______, _______, _______, KC_NUM,  _______, _______, _______, _______,          _______, RGB_VAI, RGB_SAD,
                _______, GUI_TOG, _______,                            _______,                   _______, _______,          _______, _______, RGB_VAD, _______
            ),

/*
       ┌───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐┌───┐ ┌───┐
       │   ││   │   │   │   ││   │   │   │   ││   │   │   │   ││   │ │   │
       └───┘└───┴───┴───┴───┘└───┴───┴───┴───┘└───┴───┴───┴───┘└───┘ └───┘
       ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┐
       │   │   │   │   │   │   │   │   │   │   │   │   │   │       │ │   │
       ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┤
       │     │   │   │   │   │   │   │   │   │   │   │   │   │     │ │   │
       ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ ├───┤
       │      │   │   │   │   │   │   │   │   │   │   │   │        │ │   │
       ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┘ ├───┤
       │        │   │   │   │   │   │   │   │   │   │   │      │┌───┐│   │
       ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─────┘│   │└───┘
       │    │    │    │                        │    │    │  ┌───┼───┼───┐
       └────┴────┴────┴────────────────────────┴────┴────┘  │   │   │   │
                                                            └───┴───┴───┘
*/
    /*  Row:    0        1        2        3        4        5        6        7        8        9        10       11       12       13       14       15     */
    [_FN1] = LAYOUT(
                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
                _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
                _______, _______, _______,                            _______,                   _______, _______,          _______, _______, _______, _______
            ),

/*
       ┌───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐┌───┐ ┌───┐
       │   ││   │   │   │   ││   │   │   │   ││   │   │   │   ││   │ │   │
       └───┘└───┴───┴───┴───┘└───┴───┴───┴───┘└───┴───┴───┴───┘└───┘ └───┘
       ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┐
       │   │   │   │   │   │   │   │   │   │   │   │   │   │       │ │   │
       ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┤
       │     │   │   │   │   │   │   │   │   │   │   │   │   │     │ │   │
       ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ ├───┤
       │      │   │   │   │   │   │   │   │   │   │   │   │        │ │   │
       ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┘ ├───┤
       │        │   │   │   │   │   │   │   │   │   │   │      │┌───┐│   │
       ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─────┘│   │└───┘
       │    │    │    │                        │    │    │  ┌───┼───┼───┐
       └────┴────┴────┴────────────────────────┴────┴────┘  │   │   │   │
                                                            └───┴───┴───┘
*/
    /*  Row:    0        1        2        3        4        5        6        7        8        9        10       11       12       13       14       15     */
    [_FN2] = LAYOUT(
                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
                _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
                _______, _______, _______,                            _______,                   _______, _______,          _______, _______, _______, _______
            ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RGB_TOG:
            if (record->event.pressed) {
                switch (rgb_matrix_get_flags()) {
                    case LED_FLAG_ALL: {
                        rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
                        rgb_matrix_set_color_all(0, 0, 0);
                    }
                    break;
                    case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR): {
                        rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                        rgb_matrix_set_color_all(0, 0, 0);
                    }
                    break;
                    case (LED_FLAG_UNDERGLOW): {
                        rgb_matrix_set_flags(LED_FLAG_NONE);
                        rgb_matrix_set_color_all(0, 0, 0);
                    }
                    break;
                    default: {
                        rgb_matrix_set_flags(LED_FLAG_ALL);
                        rgb_matrix_enable_noeeprom();
                    }
                    break;
                }
            }
            return false;
	}

    return true;
}

void rgb_matrix_indicators_user(void) {
    rgb_matrix_set_color(46, 0, 0, 0);
    rgb_matrix_set_color(104, 0, 0, 0);

    uint8_t red = host_keyboard_led_state().caps_lock ? 255 : 0;
    uint8_t green = host_keyboard_led_state().scroll_lock ? 255 : 0;
    uint8_t blue = keymap_config.no_gui ? 255 : 0;


    if ((rgb_matrix_get_flags() & LED_FLAG_KEYLIGHT)) {
        if (host_keyboard_led_state().num_lock) {
            rgb_matrix_set_color(46, 255, 0, 0);
        }
        rgb_matrix_set_color(104, red, green, blue);
    } else {
        if (host_keyboard_led_state().num_lock) {
            rgb_matrix_set_color(46, 255, 0, 0);
        } else {
            rgb_matrix_set_color(46, 0, 0, 0);
        }
        rgb_matrix_set_color(104, red, green, blue);
    }
}

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_FN]   = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_FN1]  = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_FN2]  = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
};
#endif
