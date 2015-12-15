#include "keymap_common.h"
#include "planck.h"
#include "backlight.h"

#define _QW 0
#define _LW 1
#define _RS 2

// This layout tries to imitate the Atreus keyboard

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QW] = { /* Qwerty */
  {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
  {KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, MO(_LW)},
  {KC_TRNS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_TRNS},
  {M(0),    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_SPC,  KC_SPC,  MO(_RS), KC_MINS, KC_QUOT, KC_ENT,  KC_TRNS}
},
[_RS] = { /* RAISE */
  {KC_TRNS, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE, KC_PGUP, KC_7,    KC_8,    KC_9, KC_ASTR, KC_TRNS},
  {KC_TRNS, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,  KC_PGDN, KC_4,    KC_5,    KC_6, KC_PLUS, KC_TRNS},
  {KC_TRNS, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, KC_AMPR, KC_1,    KC_2,    KC_3, KC_BSLS, KC_TRNS},
  {KC_TRNS, KC_TRNS, KC_INS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_0, KC_EQL,  KC_TRNS}
},
[_LW] = { /* LOWER */
  {KC_TRNS, KC_INS,    KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_TRNS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_TRNS},
  {KC_TRNS, KC_DELETE, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_TRNS, KC_F4,   KC_F5,   KC_F6,   KC_F11,  KC_TRNS},
  {KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F12,  KC_TRNS},
  {KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLD, KC_VOLU, KC_MNXT, KC_MPLY, KC_TRNS}
}
};

const uint16_t PROGMEM fn_actions[] = {

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            backlight_step();
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      }
    return MACRO_NONE;
};

