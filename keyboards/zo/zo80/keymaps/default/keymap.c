/* Copyright 2020 Sergey Vlasov <sigprof@gmail.com>
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

enum layer_names {
    _MAC_BASE,
    _WIN_BASE,
    _FN_LAYER,
};

enum custom_keycodes {
    LOCK = SAFE_RANGE,
    ILY,
    SWAP_OS,
    FOR_OS,
};

const rgblight_segment_t PROGMEM _mac_layer[] = RGBLIGHT_LAYER_SEGMENTS( {0, 20, HSV_WHITE} );
const rgblight_segment_t PROGMEM _win_layer[] = RGBLIGHT_LAYER_SEGMENTS( {0, 20, HSV_BLUE} );
const rgblight_segment_t PROGMEM _warn_layer[] = RGBLIGHT_LAYER_SEGMENTS( {0, 20, HSV_RED} );

const rgblight_segment_t* const PROGMEM _rgb_layers[] =
    RGBLIGHT_LAYERS_LIST( _mac_layer, _win_layer, _warn_layer );

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MAC_BASE] = LAYOUT_ansi(
        KC_ESC,    KC_F1,   KC_F2,   KC_F3,   KC_F4,     KC_F5,   KC_F6,   KC_F7,   KC_F8,     KC_F9,   KC_F10,  KC_F11,  KC_F12,     MO(2),     KC_DEL,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,            KC_HOME,
        KC_TAB,      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,        KC_END,
        KC_CAPS,       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT,            KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,
        KC_LCTL,   KC_LOPT,   KC_LCMD,                       KC_SPC,                              C(KC_UP),     C(KC_DOWN),    KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_WIN_BASE] = LAYOUT_ansi(
        KC_ESC,    KC_F1,   KC_F2,   KC_F3,   KC_F4,     KC_F5,   KC_F6,   KC_F7,   KC_F8,     KC_F9,   KC_F10,  KC_F11,  KC_F12,     MO(2),     KC_DEL,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,            KC_HOME,
        KC_TAB,      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,        KC_END,
        KC_CAPS,       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT,            KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,
        KC_LCTL,   KC_LWIN,   KC_LALT,                       KC_SPC,                              KC_RALT,     KC_RCTL,        KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_FN_LAYER] = LAYOUT_ansi(
        QK_BOOT,   _______, _______, _______, _______,   _______, _______, _______, _______,   _______, _______, _______, _______,    _______,   LOCK,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLD, KC_VOLU, KC_MUTE,            KC_PGUP,
        _______,     RGB_TOG, RGB_MOD, _______, RGB_M_R, RGB_M_T, _______, _______, _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______,        KC_PGDN,
        _______,       RGB_HUI, RGB_SAI, RGB_VAI, _______, _______, _______, _______, _______, ILY,     _______, _______, _______,
        _______,            RGB_HUD, RGB_SAD, RGB_VAD, _______, RGB_M_B, NK_TOGG, _______, _______, _______, FOR_OS,  _______,          _______,
        _______,   _______,   _______,                       SWAP_OS,                             _______,     _______,        _______, _______, _______
    ),
};

void keyboard_post_init_user(void) {
    rgblight_layers = _rgb_layers;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LOCK:
            if (record->event.pressed) {
                if (IS_LAYER_ON(0)) {
                    // MAC
                    register_code16(C(G(KC_Q)));
                } else {
                    // WINDOWS
                    register_code16(G(KC_L));
                };
            } else {
                unregister_code16(C(G(KC_Q)));
                unregister_code16(G(KC_L));
            };
            return false;
        case SWAP_OS:
            if (record->event.pressed) {
                if (IS_LAYER_ON(0)) {
                    // MAC is currently on
                    set_single_persistent_default_layer(_WIN_BASE);
                    layer_move(_WIN_BASE);
                } else {
                    // WINDOWS is currently on
                    set_single_persistent_default_layer(_MAC_BASE);
                    layer_move(_MAC_BASE);
                };
            };
            return false;
        case FOR_OS:
            if (record->event.pressed) {
                if (IS_LAYER_ON(0)) {
                    // MAC
                    SEND_STRING("macos");
                } else {
                    // WINDOWS
                    SEND_STRING("windows");
                };
            };
            return false;
        case ILY:
            if (record->event.pressed) {
                SEND_STRING("I love you!\n");
            };
            return false;
        default:
            return true;
    };
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    if (layer_state_cmp(state, _MAC_BASE)) {
        rgblight_blink_layer_repeat(0, 400, 2);
    } else  if (layer_state_cmp(state, _WIN_BASE)) {
        rgblight_blink_layer_repeat(1, 400, 2);
    } else {
        rgblight_blink_layer_repeat(2, 400, 2);
    }
    return state;
}
