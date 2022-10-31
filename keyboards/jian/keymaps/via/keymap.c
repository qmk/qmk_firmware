#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT(
  KC_LGUI, KC_GRV,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,         RGUI_T(KC_RBRC),
           KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, RCTL_T(KC_QUOT),
           KC_LALT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RALT_T(KC_BSLS),
                LT(2, KC_TAB), LSFT_T(KC_SPC), LT(1, KC_ENT),      LT(1, KC_ESC), RSFT_T(KC_BSPC), LT(2, KC_DEL)
),
[1] = LAYOUT(
  _______, KC_UNDS,         KC_F1,   KC_F2, KC_F3,   KC_F4,   KC_F5,        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,          RGUI_T(KC_F12),
           LCTL_T(KC_EQL),  KC_EXLM, KC_AT, KC_HASH, KC_DLR,  KC_PERC,      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, RCTL_T(KC_MINS),
           LALT_T(KC_PPLS), KC_1,    KC_2,  KC_3,    KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
                                      LT(3, KC_TAB), _______, _______,      _______, _______, LT(3, KC_DEL)
),
[2] = LAYOUT(
  _______, KC_NUM,          KC_PSLS, KC_P7,   KC_P8,   KC_P9,   KC_PMNS,      KC_VOLU, KC_HOME, KC_PSCR, KC_PGUP, KC_SCRL, KC_CAPS,        _______,
           LCTL_T(KC_EQL),  KC_PAST, KC_P4,   KC_P5,   KC_P6,   KC_PPLS,      KC_MUTE, KC_LEFT, KC_UP,   KC_RGHT, KC_INS,  RCTL_T(KC_APP),
           _______,         KC_P0,   KC_P1,   KC_P2,   KC_P3,   KC_PCMM,      KC_VOLD, KC_END,  KC_DOWN, KC_PGDN, KC_PAUS, _______,
                                        _______, _______, LT(3, KC_ENT),      LT(3, KC_ESC), _______, _______
),
[3] = LAYOUT_symmetric(
  QK_BOOT, DB_TOGG, XXXXXXX, BL_INC,  RGB_VAI, RGB_HUD, RGB_HUI,
           XXXXXXX, XXXXXXX, BL_DEC,  RGB_VAD, RGB_SAD, RGB_SAI,
           XXXXXXX, BL_BRTG, BL_TOGG, RGB_TOG, RGB_RMOD,RGB_MOD,
                                      _______, SH_TG,   _______
)
};
