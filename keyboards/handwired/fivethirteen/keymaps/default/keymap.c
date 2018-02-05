#include "fivethirteen.h"

#define _______ KC_TRNS

#define HDN 1
#define OSY 2
#define MOS 3
#define CTL_ESC CTL_T(KC_ESC)
#define SFT_BSP SFT_T(KC_BSPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = KEYMAP(
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, \
  CTL_ESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_UP,   KC_BSLS, \
  MO(MOS), KC_LCTL, KC_LALT, KC_LGUI, MO(HDN),    KC_SPC    ,    SFT_BSP, MO(OSY), MO(HDN), KC_LEFT, KC_DOWN, KC_RGHT  \
),
[HDN] = KEYMAP(
  _______,  KC_F1,  KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
  _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______, _______, \
  _______, KC_TILD, KC_GRV,  KC_BSLS, KC_PIPE, KC_MINS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TILD, KC_GRV,  _______, \
  _______, _______, _______, _______, _______, _______, _______, KC_ENT,  _______, _______, _______, KC_PGUP, _______, \
  _______, _______, _______, _______, _______,      KC_UNDS    , KC_DEL,  _______, _______, KC_HOME, KC_PGDN, KC_END   \
),
[OSY] = KEYMAP(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, KC_VOLD, KC_VOLU, KC_MUTE, KC_PWR,  _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______,      _______,     _______, _______, _______, _______, _______, _______  \
),
[MOS] = KEYMAP(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, KC_BTN1, KC_BTN2, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, KC_WH_D, KC_WH_U, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______,      _______,     _______, _______, _______, _______, _______, _______  \
)
};


const uint16_t PROGMEM fn_actions[] = {

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  return MACRO_NONE;
};
