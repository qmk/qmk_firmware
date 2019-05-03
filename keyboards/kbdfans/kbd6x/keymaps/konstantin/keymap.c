#include QMK_KEYBOARD_H
#include "konstantin.h"

enum keycodes_keymap {
  RCTRL = RANGE_KEYMAP,
};

enum layers_keymap {
  L_RCTRL = L_RANGE_KEYMAP,
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case RCTRL:
    if (record->event.pressed) {
      layer_on(L_RCTRL);
      register_code(KC_RCTRL);
    } else {
      layer_off(L_RCTRL);
      unregister_code(KC_RCTRL);
    }
    return false;

  default:
    return true;
  }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Base layer
   * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
   * │Esc│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ \ │ ` │
   * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
   * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │Bspc │
   * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
   * │LCtCps│ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │ Enter  │
   * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
   * │LShiftFn│ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │RShift│FnL│
   * └─────┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴───┴──┬┴───┴┬───┬─┴───┘
   *       │LGu│LAlt │           Space           │RAlGu│RCt│
   *       └───┴─────┴───────────────────────────┴─────┴───┘
   */
  [L_BASE] = LAYOUT(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
    LCT_CPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
    LSFT_FN, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, FN_FNLK,
    XXXXXXX, KC_LGUI, KC_LALT,                   KC_SPC,                    RAL_RGU, RCTRL,   XXXXXXX
  ),

  /* Function layer
   * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
   * │   │F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│PSc│Ins│
   * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
   * │     │Hom│ ↑ │End│PgU│   │   │   │   │M1 │M↑ │M2 │M3 │ Del │
   * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
   * │      │ ← │ ↓ │ → │PgD│   │   │   │MW↑│M← │M↓ │M→ │        │
   * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
   * │        │Mut│Vo-│Vo+│Ply│Prv│Nxt│MW←│MW→│M4 │M5 │      │   │
   * └─────┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴───┴──┬┴───┴┬───┬─┴───┘
   *       │DPR│DstNA│            MW↓            │MAcl2│   │
   *       └───┴─────┴───────────────────────────┴─────┴───┘
   */
  [L_FN] = LAYOUT(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_INS,
    _______, KC_HOME, KC_UP,   KC_END,  KC_PGUP, _______, _______, _______, _______, KC_BTN1, KC_MS_U, KC_BTN2, KC_BTN3, KC_DEL,
    _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______, _______, _______, KC_WH_U, KC_MS_L, KC_MS_D, KC_MS_R, _______,
    _______, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPLY, KC_MPRV, KC_MNXT, KC_WH_L, KC_WH_R, KC_BTN4, KC_BTN5, _______, _______,
    XXXXXXX, DST_P_R, DST_N_A,                   KC_WH_D,                   KC_ACL2, _______, XXXXXXX
  ),

  /* RCtrl layer
   * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
   * │   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │
   * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
   * │     │Top│Mv↑│Btm│PrT│   │   │   │   │   │   │   │   │Clear│
   * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
   * │      │Mv←│Mv↓│Mv→│NxT│   │   │   │   │   │   │   │        │
   * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
   * │        │   │   │   │   │   │   │   │   │   │   │      │   │
   * └─────┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴───┴──┬┴───┴┬───┬─┴───┘
   *       │DtR│DstA │                           │     │   │
   *       └───┴─────┴───────────────────────────┴─────┴───┘
   */
  [L_RCTRL] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, TOP,     MV_UP,   BOTTOM,  PRV_TAB, _______, _______, _______, _______, _______, _______, _______, _______, CLEAR,
    _______, MV_LEFT, MV_DOWN, MV_RGHT, NXT_TAB, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    XXXXXXX, DST_REM, DST_ADD,                   _______,                   _______, _______, XXXXXXX
  ),
};
