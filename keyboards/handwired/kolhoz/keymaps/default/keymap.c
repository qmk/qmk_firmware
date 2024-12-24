// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    LDEF,
    LSYM,
    LNUM,
    LNAV
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LDEF] = LAYOUT_split_2_3x5_4_3(
        KC_TAB,            KC_Q,            KC_W,            KC_E,            KC_R,        KC_T,                                                                                   KC_Y,            KC_U,           KC_I,            KC_O,            KC_P,        KC_BSPC,
        KC_ESC,            KC_A,            KC_S,            KC_D,            KC_F,        KC_G,                                                                                   KC_H,            KC_J,           KC_K,            KC_L,         KC_SCLN,       KC_ENTER,
                           KC_Z,            KC_X,            KC_C,            KC_V,        KC_B,                                                                                   KC_N,            KC_M,       KC_COMMA,          KC_DOT,        KC_QUOTE,
                  OSM(MOD_LSFT),   OSM(MOD_LCTL),   OSM(MOD_LGUI),   OSM(MOD_LALT),   OSL(LNUM),   LT(LNAV,KC_SPC),   OSL(LSYM),            OSL(LSYM),   LT(LNAV,KC_SPC),         KC_NO,   OSM(MOD_RALT),  OSM(MOD_RGUI),   OSM(MOD_RCTL),   OSM(MOD_RSFT)
    ),
    [LSYM] = LAYOUT_split_2_3x5_4_3(
        KC_NO,       KC_TILDE,        KC_GRV,         KC_NO,       KC_SLASH,     KC_BSLS,                                            KC_PEQL,      KC_LBRC,       KC_RBRC,       KC_QUES,         KC_NO,       KC_TRNS,
        KC_NO,          KC_AT,       KC_HASH,     KC_DOLLAR,     KC_PERCENT,     KC_CIRC,                                            KC_AMPR,      KC_ASTR,       KC_LPRN,       KC_RPRN,      KC_COLON,       KC_TRNS,
                   KC_EXCLAIM, KC_UNDERSCORE,      KC_MINUS,        KC_PLUS,     KC_PIPE,                                            KC_LCBR,      KC_RCBR,         KC_LT,         KC_GT,       KC_DQUO,
                      KC_TRNS,       KC_TRNS,       KC_TRNS,        KC_TRNS,       KC_NO,     KC_NO,    KC_NO,       KC_NO,   KC_NO,   KC_NO,      KC_TRNS,       KC_TRNS,       KC_TRNS,       KC_TRNS
    ),
    [LNUM] = LAYOUT_split_2_3x5_4_3(
        KC_NO,          KC_F1,         KC_F2,         KC_F3,          KC_F4,     KC_PSCR,                                              KC_NO,         KC_1,          KC_2,          KC_3,         KC_NO,       KC_TRNS,
        KC_NO,          KC_F5,         KC_F6,         KC_F7,          KC_F8,     CW_TOGG,                                              KC_NO,         KC_4,          KC_5,          KC_6,          KC_0,       KC_TRNS,
                        KC_F9,        KC_F10,        KC_F11,         KC_F12,       KC_NO,                                              KC_NO,         KC_7,          KC_8,          KC_9,         KC_NO,
                      KC_TRNS,       KC_TRNS,       KC_TRNS,        KC_TRNS,       KC_NO,     KC_NO,    KC_NO,       KC_NO,   KC_NO,   KC_NO,      KC_TRNS,       KC_TRNS,       KC_TRNS,       KC_TRNS
    ),
    [LNAV] = LAYOUT_split_2_3x5_4_3(
        KC_NO,          KC_NO,         KC_NO,         KC_NO,         KC_NO,        KC_NO,                                            KC_HOME,      KC_PGDN,       KC_PGUP,        KC_END,        KC_DEL,       KC_TRNS,
        KC_NO,          KC_NO,       MS_BTN2,       MS_BTN3,       MS_BTN1,        KC_NO,                                            KC_LEFT,      KC_DOWN,         KC_UP,      KC_RIGHT,         KC_NO,       KC_TRNS,
                        KC_NO,         KC_NO,         KC_NO,         KC_NO,        KC_NO,                                      RCTL(KC_LEFT),        KC_NO,         KC_NO, RCTL(KC_RIGHT),        KC_NO,
                        KC_NO,         KC_NO,         KC_NO,         KC_NO,     TO(LDEF),  TO(LDEF), TO(LDEF),       KC_NO,   KC_NO,   KC_NO,      KC_TRNS,       KC_TRNS,       KC_TRNS,       KC_TRNS
    )
};

const key_override_t delete_key_override1 = ko_make_basic(MOD_MASK_GUI, KC_BSPC, KC_DEL);
const key_override_t delete_key_override2 = ko_make_basic(MOD_MASK_ALT, KC_BSPC, KC_DEL);

const key_override_t *key_overrides[] = {
	&delete_key_override1,
	&delete_key_override2,
};

const uint16_t PROGMEM mouse_layer_enable_combo[] = {KC_S, KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM mouse_layer_disable_combo[] = {MS_BTN2, MS_BTN3, MS_BTN1, COMBO_END};
combo_t key_combos[] = {
    COMBO(mouse_layer_enable_combo, TG(LNAV)),
    COMBO(mouse_layer_disable_combo, TG(LNAV)),
};

const rgblight_segment_t PROGMEM rgb_layer_0[] = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_OFF});
const rgblight_segment_t PROGMEM rgb_layer_1[] = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_GREEN});
const rgblight_segment_t PROGMEM rgb_layer_2[] = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_RED});
const rgblight_segment_t PROGMEM rgb_layer_3[] = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_BLUE});
const rgblight_segment_t PROGMEM rgb_layer_4[] = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_SPRINGGREEN});
const rgblight_segment_t PROGMEM rgb_layer_5[] = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_CHARTREUSE});
const rgblight_segment_t PROGMEM rgb_layer_6[] = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_PINK});
const rgblight_segment_t PROGMEM rgb_layer_7[] = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_CYAN});

const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    rgb_layer_0,
    rgb_layer_1,
    rgb_layer_2,
    rgb_layer_3,
    rgb_layer_4,
    rgb_layer_5,
    rgb_layer_6,
    rgb_layer_7
);

const uint16_t MOD_BLINK_DELAY = 50;
const uint8_t MOD_BLINK_COUNT = 4;

void oneshot_mods_changed_user(uint8_t mods) {
    if(mods & MOD_MASK_CTRL) {
        rgblight_blink_layer_repeat(4, MOD_BLINK_DELAY, MOD_BLINK_COUNT);
    }
    else {
        rgblight_unblink_layer(4);
    }
    if(mods & MOD_MASK_SHIFT) {
        rgblight_blink_layer_repeat(5, MOD_BLINK_DELAY, MOD_BLINK_COUNT);
    }
    else {
        rgblight_unblink_layer(5);
    }
    if(mods & MOD_MASK_GUI) {
        rgblight_blink_layer_repeat(6, MOD_BLINK_DELAY, MOD_BLINK_COUNT);
    }
    else {
        rgblight_unblink_layer(6);
    }
    if(mods & MOD_MASK_ALT) {
        rgblight_blink_layer_repeat(7, MOD_BLINK_DELAY, MOD_BLINK_COUNT);
    }
    else {
        rgblight_unblink_layer(7);
    }
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, LDEF));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, LSYM));
    rgblight_set_layer_state(2, layer_state_cmp(state, LNUM));
    rgblight_set_layer_state(3, layer_state_cmp(state, LNAV));
    return state;
}

void keyboard_post_init_user(void) {
    rgblight_layers = rgb_layers;
}
