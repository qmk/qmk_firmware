#include "reddot.h"
#include "../../../../../quantum/keymap_extras/keymap_french.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = KEYMAP(
 KC_ESC,    KC_F1,    KC_F2,    KC_F3,     KC_F4,    KC_F5,   KC_TAB,  KC_CAPS,    KC_F6,    KC_F7,    KC_F8,    KC_F9,        KC_F10,  KC_F11,    KC_F12,   KC_FN0, KC_KP_SLASH, KC_KP_ASTERISK, KC_KP_MINUS,\
 KC_LALT,    FR_AMP, FR_EACU,  FR_QUOT, FR_APOS,    FR_LPRN,  KC_BSPACE,   KC_DELETE, FR_MINS,  FR_EGRV, FR_UNDS,  FR_CCED,       FR_AGRV,    FR_RPRN,  FR_EQL,       KC_INSERT,    KC_HOME,    KC_PGUP,\
 KC_LGUI,    FR_A,     FR_Z,     KC_E,      KC_R,     KC_T,  KC_LSFT,   KC_ENT,     KC_Y,     KC_U,     KC_I,     KC_O,          KC_P,    FR_CIRC,      FR_DLR,       KC_DELETE,    KC_END,    KC_PGDOWN, KC_KP_PLUS,\
 KC_LCTL,    FR_Q,     KC_S,     KC_D,      KC_F,     KC_G,   KC_ENT,            KC_H,     KC_J,     KC_K,     KC_L,          FR_M,  FR_UGRV,  FR_ASTR,       KC_KP_1,    KC_UP,    KC_KP_3,\
 FR_LESS, FR_W,     KC_X,     KC_C,      KC_V,     KC_B,   KC_SPACE,          KC_SPACE,     KC_N, FR_COMM,   FR_SCLN,  FR_COLN,     FR_EXLM,  NO_ALGR,    KC_LEFT,    KC_DOWN, KC_RIGHT, KC_KP_ENTER),

 [1] = KEYMAP(
  KC_ESC,    KC_F1,    KC_F2,    KC_F3,     KC_F4,    KC_F5,   KC_TAB,  KC_CAPS,    KC_F6,    KC_F7,    KC_F8,    KC_F9,        KC_F10,  KC_F11,    KC_F12,   KC_FN0, KC_KP_SLASH, KC_KP_ASTERISK, KC_KP_MINUS,\
  KC_LALT,    FR_AMP, FR_EACU,  FR_QUOT, FR_APOS,    FR_LPRN,  KC_BSPACE,   KC_DELETE, FR_MINS,  FR_EGRV, FR_UNDS,  FR_CCED,       FR_AGRV,    FR_RPRN,  FR_EQL,       KC_7,    KC_8,    KC_9,\
  KC_LGUI,    FR_A,     FR_Z,     KC_E,      KC_R,     KC_T,  KC_LSFT,   KC_ENT,     KC_Y,     KC_U,     KC_I,     KC_O,          KC_P,    FR_CIRC,      FR_DLR,       KC_4,    KC_5,    KC_6, KC_KP_PLUS,\
  KC_LCTL,    FR_Q,     KC_S,     KC_D,      KC_F,     KC_G,   KC_ENT,            KC_H,     KC_J,     KC_K,     KC_L,          FR_M,  FR_UGRV,  FR_ASTR,       KC_1,    KC_2,    KC_3,\
  FR_LESS, FR_W,     KC_X,     KC_C,      KC_V,     KC_B,   KC_SPACE,          KC_SPACE,     KC_N, FR_COMM,   FR_SCLN,  FR_COLN,     FR_EXLM,  NO_ALGR,    KC_LEFT,    KC_DOWN, KC_RIGHT, KC_KP_ENTER),
};


const uint16_t PROGMEM fn_actions[] = {
  ACTION_LAYER_TOGGLE(1),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  return MACRO_NONE;
};

