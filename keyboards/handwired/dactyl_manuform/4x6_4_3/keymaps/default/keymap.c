// Copyright 2023 Adam Tombleson (@rekarnar)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

enum layer_names {
    _BASE,
    _RAISE,
    _LOWER
};

enum custom_keycodes {
    SELECT_LEFT = SAFE_RANGE,
    SELECT_RIGHT,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case SELECT_RIGHT:
        if (record->event.pressed) {
            register_code(KC_LSFT);
            register_code(KC_LCTL);
            register_code(KC_RIGHT);
        } else { 
            unregister_code(KC_RIGHT);
            unregister_code(KC_LCTL);
            unregister_code(KC_LSFT);
        }
        break;
    case SELECT_LEFT:
        if (record->event.pressed) {
            register_code(KC_LSFT);
            register_code(KC_LCTL);
            register_code(KC_LEFT);
        } else {
            unregister_code(KC_LEFT);
            unregister_code(KC_LCTL);
            unregister_code(KC_LSFT);
        }
        break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_ESC  , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                    KC_6   , KC_7    , KC_8    , KC_9    , KC_0    , KC_BSPC,
        KC_TAB  , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                    KC_Y   , KC_U    , KC_I    , KC_O    , KC_P    , KC_MINS,
        KC_CAPS , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                    KC_H   , KC_J    , KC_K    , KC_L    , KC_SCLN , KC_QUOT,
        KC_LSFT , KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,                    KC_N   , KC_M    , KC_COMM , KC_DOT  , KC_SLSH , KC_BSLS,
        KC_LCTL , KC_TAB , KC_LSFT, KC_LALT,                                      KC_COMMA,KC_DOT  , KC_LBRC , KC_RBRC ,
                                      LOWER, KC_SPC , KC_BSPC,                    RAISE  , KC_ENT  , KC_DEL
    ),
 
    [_LOWER] = LAYOUT(
        KC_ESC  , KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC,                    KC_CIRC, KC_AMPR , KC_ASTR , KC_LPRN , KC_RPRN , KC_DEL,
        QK_BOOT , _______, _______, _______, _______, _______,                    _______, _______ , _______ , _______ , KC_TILD , KC_PLUS,
        _______ , KC_HOME, KC_PGUP, KC_PGDN, KC_END , _______,                    _______, KC_LEFT , KC_UP   , KC_DOWN , KC_RGHT , KC_PIPE,
        _______ , _______, _______, _______, _______, _______,                    _______, _______ , _______ , _______ , KC_EQL  , KC_UNDS,
        _______ , _______, _______, _______,                                      _______, _______ , _______ , _______ ,
                              _______, KC_LGUI, LALT(KC_PSCR),                    SELECT_LEFT, KC_GRAVE, SELECT_RIGHT

    ),

    [_RAISE] = LAYOUT(
        KC_F12  , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                    KC_F6  , KC_F7   , KC_F8   , KC_F9   , KC_F10 , KC_F11 ,
        _______ , _______,_______ , _______, _______, _______,                    QK_BOOT, _______ , _______ , _______ , _______, _______,
        _______ , KC_LEFT, KC_UP  , KC_DOWN, KC_RGHT, _______,                    _______, KC_HOME , KC_PGUP , KC_PGDN , KC_END , _______,
        _______ , _______,_______ , _______, _______, _______,                    _______, _______ , _______ , _______ , KC_EQL , KC_UNDS,
        _______ , _______,_______ , _______,                                      _______, _______ , _______ , LALT(KC_TAB),
                                    KC_VOLD, KC_MUTE, KC_VOLU,                    _______, _______ , _______
    )
};
