#include QMK_KEYBOARD_H


enum layer_names {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
     KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
     KC_GRV,  KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,                    KC_BSPC, RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
                                                  KC_PGUP, KC_HOME, KC_END , KC_PGDN
  ),

  [_LOWER] = LAYOUT(
     BL_STEP, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
     UG_TOGG, UG_NEXT, UG_HUEU, UG_SATU, UG_VALU, KC_LBRC,                   KC_RBRC, KC_P4,   KC_P5,   KC_P6,   KC_PLUS, KC_PIPE,
     QK_BOOT, _______, UG_HUED, UG_SATD, UG_VALD, KC_LCBR,                   KC_RCBR, KC_P1,   KC_P2,   KC_P3,   KC_SLSH, _______,
     KC_GRV,  _______, _______, _______, _______, KC_DEL,                    _______, _______, KC_P0,   KC_PDOT, _______, _______,
                                                  _______, _______, _______, _______
  ),

  [_RAISE] = LAYOUT(
     KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
     KC_DEL,  KC_MPRV, KC_MNXT, KC_VOLU, _______, KC_UNDS,                   KC_EQL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_BSLS,
     KC_MUTE, KC_MSTP, KC_MPLY, KC_VOLD, _______, KC_MINS,                   KC_PLUS, KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,
     _______, _______, _______, _______, _______, _______,                   _______, _______, KC_F10,  KC_F11,  KC_F12,  _______,
                                                  _______, _______, _______, _______
  ),
};
