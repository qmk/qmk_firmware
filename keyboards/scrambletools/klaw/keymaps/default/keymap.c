// Copyright 2026 Scramble Tools
// SPDX-License-Identifier: GPL-3.0-or-later
#include QMK_KEYBOARD_H

enum klaw_layers {
    _BASE,
    _NAV,
    _NUM,
    _SYM,
};

// Home row mods, GUI / Alt / Ctrl / Shift from the pinky inward
#define HM_A LGUI_T(KC_A)
#define HM_S LALT_T(KC_S)
#define HM_D LCTL_T(KC_D)
#define HM_F LSFT_T(KC_F)
#define HM_J RSFT_T(KC_J)
#define HM_K RCTL_T(KC_K)
#define HM_L LALT_T(KC_L)
#define HM_SCLN RGUI_T(KC_SCLN)

#define NAV_TAB LT(_NAV, KC_TAB)
#define NUM_SPC LT(_NUM, KC_SPC)
#define SYM_ENT LT(_SYM, KC_ENT)
#define SFT_BSP RSFT_T(KC_BSPC)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        HM_A,    HM_S,    HM_D,    HM_F,    KC_G,                        KC_H,    HM_J,    HM_K,    HM_L,    HM_SCLN,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                                   NAV_TAB, NUM_SPC, KC_MUTE,   KC_MPLY, SYM_ENT, SFT_BSP
    ),
    [_NAV] = LAYOUT(
        KC_ESC,  _______, _______, _______, _______,                     KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_DEL,
        KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,                     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_BSPC,
        _______, _______, _______, _______, _______,                     KC_INS,  KC_MPRV, KC_MNXT, KC_VOLD, KC_VOLU,
                                   _______, _______, RM_TOGG,   RM_NEXT, KC_ENT,  KC_DEL
    ),
    [_NUM] = LAYOUT(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_F11,                      KC_F12,  KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC,
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
                                   _______, _______, _______,   _______, KC_ENT,  KC_BSPC
    ),
    [_SYM] = LAYOUT(
        KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
        KC_GRV,  KC_TILD, KC_BSLS, KC_PIPE, KC_UNDS,                     KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_QUOT,
        QK_BOOT, _______, _______, _______, _______,                     KC_LCBR, KC_RCBR, KC_LT,   KC_GT,   KC_DQUO,
                                   _______, _______, _______,   _______, _______, _______
    ),
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(MS_WHLD, MS_WHLU) },
    [_NAV]  = { ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_PGDN, KC_PGUP) },
    [_NUM]  = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [_SYM]  = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
};
#endif
// clang-format on

#ifdef OLED_ENABLE
// Layer names shown on both OLEDs
const char *layer_name_klaw(uint8_t layer, bool left) {
    static const char *const names[] = {"BASE", "NAV", "NUM", "SYM"};
    return layer < ARRAY_SIZE(names) ? names[layer] : NULL;
}
#endif
