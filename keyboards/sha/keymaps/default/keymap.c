// Copyright 2023 Steven Karrmann
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layer_names {
    _QWERTY,
    _COLEMAK,
    _SYMBOL,
    _FUNCTION
};

#define SYM_TAB LT(_SYMBOL, KC_TAB)
#define FUN_SPC LT(_FUNCTION, KC_SPC)
#define QWERTY DF(_QWERTY)
#define COLEMAK DF(_COLEMAK)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        KC_GRV , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                   KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_MINS,
        KC_EQL , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                   KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,                   KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
        KC_LCTL, KC_LALT, KC_LGUI, KC_APP , KC_DEL , SYM_TAB, KC_ESC , KC_ENT , FUN_SPC, KC_BSPC, KC_APP , KC_RGUI, KC_RALT, KC_RCTL
    ),
    [_COLEMAK] = LAYOUT(
        KC_GRV , KC_Q   , KC_W   , KC_F   , KC_P   , KC_G   ,                   KC_J   , KC_L   , KC_U   , KC_Y   , KC_SCLN, KC_MINS,
        KC_EQL , KC_A   , KC_R   , KC_S   , KC_T   , KC_D   ,                   KC_H   , KC_N   , KC_E   , KC_I   , KC_O   , KC_QUOT,
        KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,                   KC_K   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
        KC_LCTL, KC_LALT, KC_LGUI, KC_APP , KC_DEL , SYM_TAB, KC_ESC , KC_ENT , FUN_SPC, KC_BSPC, KC_APP , KC_RGUI, KC_RALT, KC_RCTL
    ),
    [_SYMBOL] = LAYOUT(
        KC_TILD, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                   KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_UNDS,
        KC_PLUS, KC_EXLM, KC_LPRN, KC_RPRN, KC_DLR , KC_AMPR,                   KC_PIPE, KC_HASH, KC_LCBR, KC_RCBR, KC_COLN, KC_DQUO,
        _______, KC_AT  , KC_LBRC, KC_RBRC, KC_BSLS, KC_PERC,                   KC_CIRC, KC_ASTR, KC_LABK, KC_RABK, KC_QUES, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_FUNCTION] = LAYOUT(
        QK_BOOT, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_PSCR,                   KC_SCRL, KC_HOME, KC_PGDN, KC_PGUP, KC_END , QWERTY ,
        _______, KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_INS ,                   KC_CAPS, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, COLEMAK,
        _______, KC_F9  , KC_F10 , KC_F11 , KC_F12 , RGB_TOG,                   KC_NUM , KC_MUTE, KC_VOLD, KC_VOLU, KC_PAUS, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )
};

const rgblight_segment_t PROGMEM rgb_scroll_lock[] = RGBLIGHT_LAYER_SEGMENTS(
    {6, 3, HSV_BLUE}
);
const rgblight_segment_t PROGMEM rgb_caps_lock[] = RGBLIGHT_LAYER_SEGMENTS(
    {11, 3, HSV_GREEN}
);
const rgblight_segment_t PROGMEM rgb_num_lock[] = RGBLIGHT_LAYER_SEGMENTS(
    {16, 3, HSV_RED}
);
const rgblight_segment_t PROGMEM rgb_qwerty[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 6,  HSV_YELLOW},
    {9, 2,  HSV_YELLOW},
    {14, 2, HSV_YELLOW},
    {19, 6, HSV_YELLOW}
);
const rgblight_segment_t PROGMEM rgb_colemak[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 6,  HSV_CYAN},
    {9, 2,  HSV_CYAN},
    {14, 2, HSV_CYAN},
    {19, 6, HSV_CYAN}
);

const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    rgb_scroll_lock,
    rgb_caps_lock,
    rgb_num_lock,
    rgb_qwerty,
    rgb_colemak
);

void keyboard_post_init_user(void) {
    rgblight_layers = rgb_layers;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.scroll_lock);
    rgblight_set_layer_state(1, led_state.caps_lock);
    rgblight_set_layer_state(2, led_state.num_lock);
    return true;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(3, layer_state_cmp(state, _QWERTY));
    rgblight_set_layer_state(4, layer_state_cmp(state, _COLEMAK));
    return state;
}