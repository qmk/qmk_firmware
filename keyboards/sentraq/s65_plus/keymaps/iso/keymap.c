#include QMK_KEYBOARD_H

#define _BL 0
#define _AL 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* 0: Main layer
   * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
   * │F1 │F2 │Esc│1 !│2 "│3 £│4 $│5 %│6 ^│7 &│8 *│9 (│0 )│- _│= +│Bksp   │Del│
   * ├───┼───┼───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
   * │F3 │F4 │Tab  │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │[ {│] }│Enter│End│
   * ├───┼───├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    ├───┤
   * │F5 │F6 │CapsLk│ A │ S │ D │ F │ G │ H │ J │ K │ L │; :│' @│# ~│    │PUp│
   * ├───┼───┼────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┼───┤
   * │F7 │F8 │Sft │\ |│ Z │ X │ C │ V │ B │ N │ M │, <│. >│/ ?│Shift │Up │PDn│
   * ├───┼───┼────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┤
   * │F9 │F10│Ctrl│GUI │Alt │Space                   │Alt│Fn │Ctl│Lft│Dwn│Rgt│
   * └───┴───┴────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┘
   */

  /* 0: ISO qwerty */
  [_BL] = LAYOUT_iso(
    KC_F1,   KC_F2,   KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,  \
    KC_F3,   KC_F4,   KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_PGUP, \
    KC_F5,   KC_F6,   KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,  KC_PGDN, \
    KC_F7,   KC_F8,   KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_END,  \
    KC_F9,   KC_F10,  KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT, MO(_AL), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT  \
  ),


  /* 1: LED layer
   * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
   * │   │   │RST│   │   │   │   │   │   │   │   │   │   │   │   │BLTog  │BSt│
   * ├───┼───┼───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
   * │   │   │     │   │   │   │   │   │   │   │   │   │   │   │   │     │   │
   * ├───┼───┼─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    ├───┤
   * │   │   │      │   │   │   │   │   │   │   │   │   │   │   │   │    │   │
   * ├───┼───┼────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┼───┤
   * │   │   │    │   │RTg│RMd│RH+│RH-│RS+│RS-│RV+│RV-│   │   │      │VUp│   │
   * ├───┼───┼────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┤
   * │   │   │    │    │    │                        │   │   │   │Prv│VDn│Nxt│
   * └───┴───┴────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┘
   */

  [_AL] = LAYOUT_iso(
    _______, _______, RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, BL_TOGG, BL_STEP, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, _______, KC_VOLU, _______, \
    _______, _______, _______, _______, _______,                   _______,                            _______, _______, _______, KC_MPRV, KC_VOLD, KC_MNXT  \
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}
