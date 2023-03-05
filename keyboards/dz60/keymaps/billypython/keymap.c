#include QMK_KEYBOARD_H
#include "billypython.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Base layer
   * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
   * │Esc│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ \ │ ` │
   * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
   * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │Bspc │
   * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
   * │FnCaps│ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │ Enter  │
   * ├──────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬───┬───┤
   * │LShift │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │RSC│ ↑ │Del│
   * ├────┬──┴─┬─┴──┬┴───┴───┴───┴───┴───┴───┼───┼───┼───┼───┼───┤
   * │LCtl│LGui│LAlt│         Space          │RAl│FnL│ ← │ ↓ │ → │
   * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┘
  */
  [L_BASE] = LAYOUT_directional(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
    FN_CAPS,          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
    KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSF_RCT, KC_UP,   KC_DEL,
    KC_LCTL, KC_LGUI,          KC_LALT, XXXXXXX,          KC_SPC,           XXXXXXX,          KC_RALT, FN_FNLK, KC_LEFT, KC_DOWN, KC_RGHT
  ),

  /* Function layer
   * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
   * │   │F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│   │PSc│
   * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
   * │ M4  │M2 │M↑ │M1 │M3 │M5 │   │PgU│ ↑ │PgD│Ply│Prv│Nxt│Clear│
   * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
   * │      │M← │M↓ │M→ │MW↑│   │Hom│ ← │ ↓ │ → │End│   │        │
   * ├──────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬───┬───┤
   * │       │MA0│MA2│MW←│MW→│   │   │   │Vo-│Vo+│Mut│App│PgU│Ins│
   * ├────┬──┴─┬─┴──┬┴───┴───┴───┴───┴───┴───┼───┼───┼───┼───┼───┤
   * │    │    │    │          MW↓           │   │   │Hom│PgD│End│
   * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┘
  */
  [L_FN] = LAYOUT_directional(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_PSCR,
    KC_BTN4, KC_BTN2, KC_MS_U, KC_BTN1, KC_BTN3, KC_BTN5, _______, KC_PGUP, KC_UP,   KC_PGDN, KC_MPLY, KC_MPRV, KC_MNXT, CLEAR,
    _______,          KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_U, _______, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  _______, _______,
    _______,          KC_ACL0, KC_ACL2, KC_WH_L, KC_WH_R, _______, _______, _______, KC_VOLD, KC_VOLU, KC_MUTE, KC_APP,  KC_PGUP, KC_INS,
    _______, _______,          _______, XXXXXXX,          KC_WH_D,          XXXXXXX,          _______, _______, KC_HOME, KC_PGDN, KC_END
  ),
};
