// Copyright 2023 Anjheos (@Anjheos)
// SPDX-License-Identifier: GPL-2.0-or-later


#include QMK_KEYBOARD_H

enum layer_names {
    _QWERTY,
    _FN1,
    _FN2,
    _FN3

};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_225_1(
    QK_GESC,   KC_Q,     KC_W,      KC_E,      KC_R,      KC_T,      KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,      KC_BSPC,
    KC_TAB,    KC_A,     KC_S,      KC_D,      KC_F,      KC_G,      KC_H,      KC_J,      KC_K,      KC_L,      KC_SCLN,   KC_ENT,
    KC_LSFT,   KC_Z,     KC_X,      KC_C,      KC_V,      KC_B,      KC_N,      KC_M,      KC_COMMA,  KC_DOT,    KC_SLSH,   KC_UP,     UG_NEXT,
    KC_LCTL,   KC_LALT,  KC_LGUI,   MO(_FN1),             KC_SPC,    KC_SPC,    KC_RALT,   KC_RCTL,             KC_LEFT,   KC_DOWN,   KC_RIGHT
  ),
  [1] = LAYOUT_225_1(
    KC_F1,     KC_F2,    KC_F3,     KC_F4,     KC_F5,     KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,    KC_F12,
    KC_CAPS,   KC_1,     KC_2,      KC_3,      KC_4,      KC_5,      KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      KC_ENT,
    KC_SCRL,   KC_Z,     KC_X,      KC_C,      KC_V,      KC_B,      KC_N,      KC_M,      KC_COMMA,  KC_DOT,    CK_TOGG,   UG_SATU,   UG_TOGG,
    KC_NUM,    KC_LALT,  MO(_FN2),  _______,              KC_SPC,    KC_SPC,    KC_RALT,   KC_RCTL,             UG_HUED,   UG_SATD,   UG_HUEU
  ),
  [2] = LAYOUT_225_1(
    _______,   _______,  _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
    _______,   _______,  _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
    _______,   _______,  _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
    _______,   MO(_FN3), _______,   _______,              _______,   _______,   _______,   _______,              _______,   _______,   _______
  ),
  [3] = LAYOUT_225_1(
    _______,   _______,  _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
    _______,   _______,  _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
    _______,   _______,  _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
    _______,   _______,  _______,   _______,              _______,   _______,   _______,   _______,              _______,   _______,   _______
  )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_QWERTY] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_FN1] = { ENCODER_CCW_CW(UG_VALD, UG_VALU)},
    [_FN2] = { ENCODER_CCW_CW(MS_WHLD, MS_WHLU)},
    [_FN3] = { ENCODER_CCW_CW(KC_LEFT, KC_RIGHT)}
};
#endif

const rgblight_segment_t PROGMEM _caps_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 3, HSV_CYAN}
);

const rgblight_segment_t PROGMEM _fn1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0,1, HSV_RED}
);

const rgblight_segment_t PROGMEM _fn2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 1, HSV_PURPLE}
);

const rgblight_segment_t PROGMEM _fn3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {2, 1, HSV_YELLOW}
);

const rgblight_segment_t* const PROGMEM _rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    _caps_layer,
    _fn1_layer,
    _fn2_layer,
    _fn3_layer
);

void keyboard_post_init_user (void) {
    rgblight_layers = _rgb_layers;
    rgblight_sethsv_noeeprom(HSV_BLACK);
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, _FN1));
    rgblight_set_layer_state(2, layer_state_cmp(state, _FN2));
    rgblight_set_layer_state(3, layer_state_cmp(state, _FN3));
    return state;
}