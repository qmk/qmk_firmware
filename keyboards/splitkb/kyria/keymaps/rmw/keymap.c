/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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
#include "rmw.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [QWERTY] = LAYOUT_stack(
        KC_TAB   , KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,
        OSL(EDIT), KC_A, LT(NUMPAD,KC_S), KC_D, LT(FSYM,KC_F), KC_G,
        TD(FRBK2)  , KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,  TO(EDIT), KC_ESCAPE,
                            TO(ADJUST), TD(SGCA), TD(AGC), KC_BSPACE, TD(SHNTC),

                                KC_Y,    KC_U,       KC_I, KC_O,      KC_P,        KC_BSLS,
                                KC_H, LT(JSYM,KC_J), KC_K, KC_L, LT(EDIT,KC_SCLN), KC_QUOT,
            KC_DEL, TO(NUMPAD),  KC_N, KC_M,     KC_COMM, KC_DOT, LT(MEDIA,KC_SLSH), KC_MS_BTN1,
            SFTENT,  KC_SPC,   TD(GCA), TD(CTLALL), KC_CAPS
    ),

    [MINIMAK4] = LAYOUT_stack(
        KC_TAB   , KC_Q,   KC_W,   KC_D,   KC_R,   KC_K,
        OSL(EDIT), KC_A, LT(NUMPAD,KC_S), KC_T, LT(FSYM,KC_F), KC_G,
        OSM(MOD_LSFT)  , KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,  TO(EDIT), KC_ESCAPE,
                                _______, TO(ADJUST), TD(SGCA), KC_BSPACE, TD(SHNTC),

                                KC_Y,    KC_U,       KC_I, KC_O,      KC_P,        KC_PIPE,
                                KC_H, LT(JSYM,KC_J), KC_E, KC_L, LT(EDIT,KC_SCLN), KC_QUOT,
                KC_DEL, TO(NUMPAD),   KC_N, KC_M,     KC_COMM, KC_DOT, LT(MEDIA,KC_SLSH), KC_MINS,
                SFTENT,  KC_SPC,   TD(GCA), TD(CTLALL), _______
    ),

    [NUMPAD] = LAYOUT_stack(
        _______, _______, _______,  _______, _______, _______,
        _______, _______, _______,  _______, _______, _______,
        _______, _______, _______,  _______, _______, _______, TO(QWERTY), _______,
                                    _______, _______, _______,  _______  , _______,

                                    _______, KC_7,     KC_8,    KC_9,  KC_KP_MINUS, _______,
                                    _______, KC_4,     KC_5,    KC_6,  KC_KP_PLUS , _______,
                _______, TO(EDIT), _______, KC_1,  KC_2,  KC_3, KC_KP_SLASH, LCTL(KC_RIGHT),
                _______,  _______, KC_0, KC_DOT, _______
    ),

    [EDIT] = LAYOUT_stack(
        _______, TASK_MAN, _______, SELW_LEFT, SELW_RIGHT, _______,
        _______, _______ , LGUI(KC_GRV), MVW_LEFT,  MVW_RIGHT , _______,
        LCTL(KC_LEFT), R_UNDO, R_CUT  , R_COPY , R_PASTE, R_REDO , TO(NUMPAD), FORM_GET,
                                            _______, _______, _______, DEL_WRD, _______,

                                    NEW_TAB , KC_PGUP, KC_UP, KC_PGDOWN, KC_PSCREEN, _______,
                                    R_HOME  , KC_LEFT, KC_DOWN, KC_RIGHT, R_END, _______,
                FORM_PUT, TO(QWERTY), SEL_HOME, S(KC_LEFT), S(KC_DOWN), S(KC_RIGHT), SEL_END, _______,
                _______, _______, _______, _______, _______
    ),

    [ADJUST] = LAYOUT_stack(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,  KC_F6,
        TO(QWERTY), TO(EDIT), TO(NUMPAD), TO(JSYM), TO(FSYM), TO(MEDIA),
        DF(MINIMAK4), DF(QWERTY), RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD,_______, _______,
                                           _______, _______, _______, _______, _______,

                                KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, KC_F12,
                                _______, _______, _______, _______, _______,  _______,
                _______, _______, _______, _______, _______, _______, _______, _______,
                _______, _______, _______, _______, _______
    ),

    [FSYM] = LAYOUT_stack(
        _______, _______, _______, _______, _______, _______,
        _______, _______, KC_TILD, KC_EXLM, _______, _______,
        LCTL(KC_RIGHT), _______, TO(QWERTY), _______, _______, _______, _______, _______,
                                            _______, _______, _______, _______, _______,

                                KC_CIRC,  KC_AMPR , KC_ASTR, KC_GRV ,  _______, _______,
                                KC_EQUAL, KC_MINUS, KC_UNDS, KC_PIPE, KC_COLON, KC_DQT,
                _______, _______, _______, KC_PLUS,  KC_BSLS, KC_SLSH, _______, _______,
                _______, _______, _______, _______, _______
    ),

    [JSYM] = LAYOUT_stack(
        _______, KC_GRV,  KC_AT  , KC_LCBR,     KC_RCBR,     _______,
        _______, KC_HASH, KC_DLR , KC_LPRN,     KC_RPRN,     KC_LEFT,
        _______, KC_PERC, KC_CIRC, KC_LBRACKET, KC_RBRACKET, _______, _______, _______,
                                                _______, _______, _______, _______, _______,

                                _______, _______, _______, _______,  _______, _______,
                                _______, _______, KC_QUES, KC_SLSH, KC_COLON, _______,
                _______, _______, _______, _______, _______, TO(QWERTY), _______, LCTL(KC_LEFT),
                _______, _______, _______, _______, _______
    ),

    [MEDIA] = LAYOUT_stack(
        _______, KC_WH_U, KC_WH_L, KC_MS_UP, KC_WH_R, _______,
        _______, KC_WH_D, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, _______,
        _______, _______, KC_ACL0, KC_ACL1, KC_ACL2, _______, _______, _______,
                                                _______, _______, _______, _______, _______,

                                _______, _______, _______, _______,  _______, _______,
                                _______, _______, _______, _______, _______, _______,
                _______, _______, _______, _______, KC_VOLD, KC_MUTE, KC_VOLU, _______,
                KC_MS_BTN1, KC_MEDIA_PLAY_PAUSE, KC_MRWD, KC_MFFD, _______
    )
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case FORM_GET:
            if (record->event.pressed) {
                tap_code(KC_BTN1);
                tap_code16(G(KC_A));
                tap_code16(G(KC_C));
            }
        return false;
        case FORM_PUT:
            if (record->event.pressed) {
                tap_code16(KC_MS_BTN1);
                tap_code16(G(KC_A));
                tap_code16(G(KC_V));
            }
        return false;
    }
    return true;
}

#ifdef ENCODER_ENABLE
bool encoder_update_keymap(uint8_t index, bool clockwise) {
    if (index == 0) {
        switch (get_highest_layer(layer_state)) {
            case EDIT:
                enc_move_words(clockwise);
                break;
            case QWERTY:
                enc_move_desktop(clockwise);
            default:
                enc_history_scrubbing(clockwise);
                break;
        }
    } else if (index == 1) {
        switch (get_highest_layer(layer_state)) {
            case QWERTY:
                enc_scrolling(clockwise);
                break;
            case FSYM:
                enc_zoom(clockwise);
                break;
            default:
                enc_volume_knob(clockwise);
                break;
        }
    }
    return true;
}
#endif

#ifdef RGBLIGHT_ENABLE  // include mods, as well as layers
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case QWERTY:
            rgblight_setrgb (0x00,  0x00, 0x00);
            break;
        case MINIMAK4:
            rgblight_setrgb (0x20,  0x20, 0x20);
            break;
        case NUMPAD:
            rgblight_setrgb (0xFF,  0x00, 0x00);
            break;
        case EDIT:
            rgblight_setrgb (0x00,  0xFF, 0x00);
            break;
        case FSYM:
            rgblight_setrgb (0x7A,  0x7A, 0x00);
            break;
        case JSYM:
            rgblight_setrgb (0x7A,  0x00, 0x7A);
            break;
        case MEDIA:
            rgblight_setrgb (0x00,  0x7A, 0x7A);
            break;
        case ADJUST:
            rgblight_setrgb (0x7A,  0x7A, 0x7A);
            break;
        default:
            rgblight_setrgb (0x00,  0x00, 0x00);
    }
    return state;
}
#endif
