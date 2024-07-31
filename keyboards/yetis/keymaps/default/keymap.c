/*
 * Copyright 2023 Norbert Pocs (norbertpocs0@gmail.com, jogme)
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include QMK_KEYBOARD_H

#define LA_SYM MO(LAYER_SYM)
#define LA_NAV MO(LAYER_NAV)
#define LA_RGB TG(LAYER_GAM_LED)

#define ALT OSM(MOD_LALT)
#define SHIFT OSM(MOD_LSFT)
#define CTRL OSM(MOD_LCTL)
#define WIN OSM(MOD_LGUI)

enum layers {
    LAYER_COLMAC,
    LAYER_SYM,
    LAYER_NAV,
    LAYER_NUM,
    LAYER_GAM_LED
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_COLMAC] = LAYOUT(
                      KC_W,    KC_F,    KC_P,    KC_G,      KC_J,    KC_L,    KC_U,    KC_Y,
    KC_Q,    KC_A,    KC_R,    KC_S,    KC_T,    KC_D,      KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
             KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,      KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_ENT,
                                        LA_NAV,  KC_ESC,    KC_SPC,  LA_SYM),
    [LAYER_SYM] = LAYOUT(
                      KC_LBRC, KC_LCBR, KC_LPRN, KC_TILD,   KC_HASH, KC_RPRN, KC_RCBR, KC_RBRC,
    KC_PLUS, KC_EQL,  KC_ASTR, KC_MINS, KC_UNDS, KC_DLR,    KC_CIRC, KC_SCLN, KC_WH_D, KC_WH_U, KC_SLSH, KC_GRV,
             KC_BSLS, KC_PIPE, KC_AT,   KC_AMPR, KC_PERC,   KC_EXLM, KC_LT,   KC_GT,   KC_COLN, KC_QUES,
                                        _______, _______,   _______, _______),
    [LAYER_NAV] = LAYOUT(
                      ALT,     KC_BRID, KC_BRIU, KC_VOLU,   KC_NO,   KC_HOME, KC_PGDN, KC_PGUP,
    KC_NO,   SHIFT,   CTRL,    KC_TAB,  WIN,     KC_VOLD,   KC_DEL,  KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT, KC_END,
             KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_PSCR,   LA_RGB,  KC_CAPS, KC_BTN1, KC_BTN2, KC_BSPC,
                                        _______, _______,   _______, _______),
    [LAYER_NUM] = LAYOUT(
                      KC_5,    KC_3,    KC_1,    KC_9,      KC_8,    KC_0,    KC_2,    KC_4,
    KC_7,    SHIFT,   KC_NO,   KC_NO,   WIN,     KC_F11,    KC_F10,  KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_6,
             KC_F7,   KC_F5,   KC_F3,   KC_F1,   KC_F9,     KC_F8,   KC_F12,  KC_F2,   KC_F4,   KC_F6,
                                        _______, _______,   _______, _______),
    [LAYER_GAM_LED] = LAYOUT(
                      KC_1,    KC_2,    KC_3,    KC_4,      _______, RGB_SAD, RGB_SAI, _______,
    KC_0,    KC_P,    KC_A,    KC_W,    KC_D,    KC_R,      RGB_HUD, RGB_VAD, RGB_VAI, RGB_HUI, _______, _______,
             KC_LCTL, KC_Q,    KC_S,    KC_E,    KC_F,      LA_RGB,  RGB_TOG, RGB_M_B, RGB_M_P, RGB_M_K,
                                        KC_LALT, KC_B,      _______, _______),
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, LAYER_SYM, LAYER_NAV, LAYER_NUM);
}
