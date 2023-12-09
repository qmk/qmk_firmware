#include QMK_KEYBOARD_H

// Mod-Tap keys for cleaner code
#define ESC_CTL LCTL_T(KC_ESC)
#define SPC_LW LT(2, KC_SPC)
#define ENT_FN LT(4, KC_ENT)

#define _QW 0
#define _DV 1
#define _LW 2
#define _RS 3
#define _FN 4

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QW] = LAYOUT( /* Base */
  KC_ESC,  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    TG(1),   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_PLUS,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC,          KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  ESC_CTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_HOME,          KC_PGUP, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_END,  KC_DEL,  KC_PGDN, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
  KC_LCTL, KC_HYPR, KC_LALT, KC_LGUI,                   SPC_LW,  ENT_FN,  KC_SPC,           MO(3),   KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT
    ),
[_DV] = LAYOUT(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    _______,          _______, KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    _______,
  _______, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    _______,          _______, KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH,
  _______, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    _______, _______, _______, KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    _______,
  _______, _______, _______, _______,                   _______, _______, _______,          _______, _______, _______, _______, _______
    ),
[_LW] = LAYOUT(
  _______, _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______,          _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,            _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, KC_PGDN, KC_PGUP, KC_HOME, KC_END , KC_MUTE,
  _______, _______, _______, _______,                   _______, _______, _______,          _______, _______, _______, _______, _______
    ),
[_RS] = LAYOUT(
  _______, _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______,          _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,            _______, _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, KC_PGDN, KC_PGUP, KC_HOME, KC_END , KC_MUTE,
  _______, _______, _______, _______,                   _______, _______, _______,          _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT
    ),
[_FN] = LAYOUT(
  _______, _______, _______, _______, _______, _______, _______, QK_BOOT, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, KC_UP,   _______, KC_PSCR, _______,
  _______, _______, _______, _______, _______, _______, _______,          _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______,                   _______, _______, _______,          _______, _______, _______, _______, _______
    )
};
