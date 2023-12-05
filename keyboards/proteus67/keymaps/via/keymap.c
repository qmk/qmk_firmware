// Copyright 2023 James Gzowski
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

enum custom_layer {
    _QWERTY,
    _ADJUST,
    _RAISE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_ortho_5x14(
        KC_ESC , KC_1  ,KC_2   ,KC_3   , KC_4  , KC_5  , KC_MINUS  , 			KC_EQL  , KC_6   , KC_7    , KC_8    , KC_9   , KC_0   , KC_GRV ,
        KC_TAB , KC_Q  ,KC_W   ,KC_E   , KC_R  , KC_T  , KC_END  , 			KC_HOME  , KC_Y   , KC_U    , KC_I    , KC_O   , KC_P   ,KC_MINUS,
        KC_LCTL, KC_A  ,KC_S   ,KC_D   , KC_F  , KC_G  , KC_PGDN  , 			KC_PGUP  , KC_H   , KC_J    , KC_K    , KC_L   , KC_SCLN,KC_QUOT ,
        KC_LSFT, KC_Z  ,KC_X   ,KC_C   , KC_V  , KC_B  , KC_LBRC, 			KC_RBRC, KC_N   , KC_M    , KC_COMM , KC_DOT , KC_SLSH, KC_RSFT,
             KC_NO  , MO(_ADJUST) ,KC_LGUI,KC_LALT,       KC_SPC ,		KC_MUTE,            KC_ENT ,		KC_BSPC , MO(_RAISE) , KC_INS , KC_DEL
),
    [_ADJUST] = LAYOUT_ortho_5x14(
        RGB_TOG , RGB_HUD  ,RGB_HUI   ,RGB_SAD   , RGB_SAI  , RGB_VAD  , RGB_VAI  ,                       RGB_M_P  , RGB_M_B   , RGB_M_R    , RGB_M_SW    , RGB_M_K   , RGB_M_TW   , RGB_M_G ,
        KC_TRNS , KC_TRNS, KC_TRNS   ,KC_TRNS   , KC_TRNS  , KC_TRNS  , KC_TRNS  ,              KC_TRNS  , KC_TRNS , KC_BTN1    , KC_MS_U    , KC_BTN2   , KC_TRNS   ,KC_TRNS,
        KC_TRNS, KC_TRNS  ,KC_TRNS   ,KC_TRNS   , KC_TRNS  , KC_TRNS  , KC_TRNS  ,              KC_TRNS  , KC_TRNS , KC_MS_L    , KC_MS_D , KC_MS_R , KC_SCLN,KC_QUOT ,
        KC_TRNS, KC_TRNS  ,KC_TRNS   ,KC_TRNS   , KC_TRNS  , KC_TRNS  , KC_TRNS ,               KC_TRNS  , KC_TRNS , KC_TRNS    , KC_TRNS , KC_TRNS , KC_NUBS, KC_TRNS,
             KC_TRNS  , KC_TRNS ,KC_TRNS,KC_TRNS,  KC_TRNS ,                       RGB_RMOD,      KC_TRNS  , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS
),
    [_RAISE] = LAYOUT_ortho_5x14(
        KC_TRNS , KC_F1  ,KC_F2   ,KC_F3   , KC_F4  , KC_F5  , KC_TRNS  ,                       KC_TRNS  , KC_F6   , KC_F7    , KC_F8    , KC_F9   , KC_F10   , KC_GRV ,
        KC_TRNS , KC_TRNS, KC_TRNS   ,KC_TRNS   , KC_TRNS  , KC_TRNS  , KC_TRNS  ,              KC_TRNS  , KC_TRNS , KC_TRNS    , KC_UP    , KC_TRNS   , KC_TRNS   ,KC_TRNS,
        KC_TRNS, KC_TRNS  ,KC_TRNS   ,KC_TRNS   , KC_TRNS  , KC_TRNS  , KC_TRNS  ,              KC_TRNS  , KC_TRNS , KC_LEFT    , KC_DOWN , KC_RIGHT , KC_SCLN,KC_QUOT ,
        KC_TRNS, KC_TRNS  ,KC_TRNS   ,KC_TRNS   , KC_TRNS  , KC_TRNS  , KC_TRNS ,               KC_TRNS  , KC_TRNS , KC_TRNS    , KC_TRNS , KC_TRNS , KC_NUBS, KC_TRNS,
             KC_TRNS  , KC_TRNS ,KC_TRNS,KC_TRNS,  KC_TRNS ,                       RGB_MOD,      KC_TRNS  , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS
)
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_QWERTY] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_ADJUST] =  { ENCODER_CCW_CW(RGB_HUD, RGB_HUI)},
    [_RAISE] =  { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)}
};
#endif

// MO(_ADJUST)
const rgblight_segment_t PROGMEM backlight_layer_adjust[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 4, HSV_GOLD}
);
// MO(_RAISE)
const rgblight_segment_t PROGMEM backlight_layer_raise[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 4, HSV_CYAN}
);
const rgblight_segment_t PROGMEM backlight_layer_qwerty[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 4, HSV_BLACK}
);

const rgblight_segment_t* const PROGMEM set_backlight_mode[] = RGBLIGHT_LAYERS_LIST(
    backlight_layer_adjust,
    backlight_layer_raise,
    backlight_layer_qwerty
);

layer_state_t default_layer_state_set_user(layer_state_t state) {
return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _ADJUST));
    rgblight_set_layer_state(1, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(2, layer_state_cmp(state, _QWERTY));
    return state;
}
void keyboard_post_init_user(void) {
    rgblight_set_effect_range(4, 17);
    rgblight_sethsv_range(HSV_BLACK, 0, 4);
    rgblight_layers = set_backlight_mode;
}
