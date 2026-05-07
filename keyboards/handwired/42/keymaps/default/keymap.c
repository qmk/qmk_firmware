#include QMK_KEYBOARD_H

// MOD_KC
#define CTL_ESC MT(MOD_LCTL, KC_ESCAPE)
#define CTL_ENT MT(MOD_LCTL, KC_ENTER)
#define ALT_Z   MT(MOD_LALT, KC_Z)
#define ALT_SLS MT(MOD_LALT, KC_SLASH)
#define SU_QUOT MT(MOD_LGUI, KC_QUOTE)
#define SU_BSLS MT(MOD_LGUI, KC_BSLS)
#define SFT_DEL MT(MOD_LSFT, KC_DELETE)

// LAYER_KC
#define L3_SPC  LT(3, KC_SPC)
#define L2_SPC  LT(2, KC_SPC)
#define L1_LBRC LT(1, KC_LBRC)
#define L1_RBRC LT(1, KC_RBRC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Default Layer
  LAYOUT(
    KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,       KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSPC,
    CTL_ESC, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,       KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, CTL_ENT,
    KC_LSFT, ALT_Z  , KC_X   , KC_C   , KC_V   , KC_B   ,       KC_N   , KC_M   , KC_COMM, KC_DOT , ALT_SLS, SFT_DEL,
                               L1_LBRC, L3_SPC , SU_QUOT,       SU_BSLS, L2_SPC , L1_RBRC
  ),
  // Symbols Layer
  LAYOUT(
    KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,       KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_EQL ,
    KC_INS , S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5),       S(KC_6), S(KC_7), S(KC_8), S(KC_9), S(KC_0), KC_MINS,
    KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  ,       KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 ,
                               KC_CAPS, OU_USB , OU_BT  ,       _______, _______, _______
  ),
  // Navigation Layer
  LAYOUT(
    _______, _______, _______, KC_PGUP, _______, _______,       KC_BRIU, _______, KC_UP  , _______, _______, _______,
    _______, _______, KC_HOME, KC_PGDN, KC_END , _______,       _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
    _______, _______, _______, _______, _______, _______,       KC_BRID, KC_VOLD, KC_MUTE, KC_VOLU, _______, _______,
                               _______, _______, _______,       _______, _______, _______
  ),
  // Mouse Layer
  LAYOUT(
    _______, _______, KC_WREF, MS_WHLU, KC_WSCH, _______,       _______, MS_BTN1, MS_UP,   MS_BTN2, _______, _______,
    _______, _______, MS_WHLL, MS_WHLD, MS_WHLR, _______,       _______, MS_LEFT, MS_DOWN, MS_RGHT, _______, _______,
    _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______,       _______, _______, _______, _______, _______, _______,
                               _______, _______, _______,       _______, _______, _______
  )
};
