// Copyright 2021 JZ-Skyloong (@JZ-Skyloong)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layer_names {
    _WIN,
    _MAC,
    _WIN_INDEX,
    _MAC_INDEX
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │Esc│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │Bsp│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Tab│ Q │ W │ E | R │ T │ Y │ U │ I │ O │ P │ [ │ ] │ \ │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Cap│ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │   |Ent│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Sft│ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │   |Sft|   │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Ctl│GUI│Alt│   │Spc│Spc│Mut│   |Spc|Alt│App│Ctl│   │Mox|
     * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
     */
    [_WIN] = LAYOUT_all(
         KC_ESC,     KC_1,     KC_2,     KC_3,     KC_4,     KC_5,        KC_6,     KC_7,        KC_8,      KC_9,        KC_0,     KC_MINS,    KC_EQL,         KC_BSPC,
         KC_TAB,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,        KC_Y,     KC_U,        KC_I,      KC_O,        KC_P,     KC_LBRC,   KC_RBRC,         KC_BSLS,
        KC_CAPS,     KC_A,     KC_S,     KC_D,     KC_F,     KC_G,        KC_H,     KC_J,        KC_K,      KC_L,     KC_SCLN,     KC_QUOT,                     KC_ENT,
        KC_LSFT,     KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,        KC_N,     KC_M,     KC_COMM,    KC_DOT,     KC_SLSH,                KC_RSFT,
        KC_LCTL,  KC_LGUI,  KC_LALT,             KC_SPC,   KC_SPC,     KC_MUTE,                KC_SPC,   KC_RALT,      KC_APP,     KC_RCTL,              MO(_WIN_INDEX)
    ),

     [_MAC] = LAYOUT_all(
        _______,  _______,  _______,  _______,  _______,  _______,     _______,  _______,     _______,   _______,     _______,     _______,   _______,         _______,
        _______,  _______,  _______,  _______,  _______,  _______,     _______,  _______,     _______,   _______,     _______,     _______,   _______,         _______,
        _______,  _______,  _______,  _______,  _______,  _______,     _______,  _______,     _______,   _______,     _______,     _______,                    _______,
        _______,  _______,  _______,  _______,  _______,  _______,     _______,  _______,     _______,   _______,     _______,                _______,
        _______,  KC_LALT,  KC_LGUI,            _______,  _______,     _______,               _______,   KC_RGUI,     KC_RALT,     _______,              MO(_MAC_INDEX)
    ),

    [_WIN_INDEX] =  LAYOUT_all(
        KC_GRV ,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,       KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DEL,
        _______,  _______,    TO(0),    TO(1),  _______,  _______,     _______,  _______,  _______,  _______,  RGB_M_P,  RGB_RMOD, RGB_RMOD, RGB_TOG,
        _______,  _______,  _______,  _______,  _______,  _______,     _______,  _______,  _______,  _______,  RGB_SPD,  RGB_SPI,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,     _______,  _______,  RGB_VAD,  RGB_VAI,  KC_UP,              _______,
        _______,  _______,  _______,            _______,  _______,     _______,            _______,  KC_LEFT,  KC_DOWN,  KC_RIGHT,           _______
    ),

    [_MAC_INDEX] = LAYOUT_all(
        KC_GRV ,   KC_F14,   KC_F15,  C(KC_UP),  G(KC_D),  G(KC_SPC),   LSG(KC_4),  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,   KC_VOLD,  KC_VOLU,  KC_DEL,
        _______,  _______,    TO(0),     TO(1),  _______,    _______,     _______,  _______,  _______,  _______,  RGB_M_P,  RGB_RMOD, RGB_RMOD, RGB_TOG,
        _______,  _______,  _______,   _______,  _______,    _______,     _______,  _______,  _______,  _______,  RGB_SPD,   RGB_SPI,           _______,
        _______,  _______,  _______,   _______,  _______,    _______,     _______,  _______,  RGB_VAD,  RGB_VAI,  KC_UP,              _______,
        _______,  _______,  _______,             _______,    _______,     _______,            _______,  KC_LEFT,  KC_DOWN,  KC_RIGHT,           _______
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_WIN] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_MAC] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_WIN_INDEX] = { ENCODER_CCW_CW(RGB_HUD, RGB_HUI) },
    [_MAC_INDEX] = { ENCODER_CCW_CW(RGB_HUD, RGB_HUI) }
};
#endif

