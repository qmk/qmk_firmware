#include QMK_KEYBOARD_H

#define TOP     LCTL(KC_HOME)
#define BOTTOM  LCTL(KC_END)

#define FN      MO(L_FN)
#define FN_CAPS LT(L_FN, KC_CAPS)
#define FN_FNLK TT(L_FN)

#define COMMA   UC(0x002C)
#define L_PAREN UC(0x0028)
#define R_PAREN UC(0x0029)
#define EQUALS  UC(0x003D)
#define TIMES   UC(0x00D7)
#define DIVIDE  UC(0x00F7)
#define MINUS   UC(0x2212)

void eeconfig_init_user(void) {
  set_unicode_input_mode(UNICODE_MODE_LINUX);
}

enum layers {
  L_BASE,
  L_FN,
  L_NUMPAD,
};

enum custom_keycodes {
  CLEAR = SAFE_RANGE,
  NUMPAD,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case CLEAR:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTL("a") SS_TAP(X_DELETE));
    }
    return false;

  case NUMPAD:
    if (record->event.pressed) {
      layer_invert(L_NUMPAD);
      bool num_lock = host_keyboard_leds() & 1<<USB_LED_NUM_LOCK;
      if (num_lock != (bool)IS_LAYER_ON(L_NUMPAD)) {
        tap_code(KC_NUM_LOCK); // Toggle Num Lock to match layer state.
      }
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
   * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
   * │Tab│ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │Bsp│Del│
   * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
   * │FnC│ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │Ent│Ent│PgU│
   * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
   * │LSf│ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │RSf│RSf│ ↑ │PgD│
   * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
   * │LCt│LGu│LAl│Spc│Spc│Spc│Spc│Spc│Spc│RAl│FnL│RCt│ ← │ ↓ │ → │
   * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
   */
  [L_BASE] = LAYOUT_ortho_5x15( \
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,  \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC, KC_DEL,  \
    FN_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_ENT,  KC_PGUP, \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_RSFT, KC_UP,   KC_PGDN, \
    KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,  KC_RALT, FN_FNLK, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT  \
  ),

  /* Base layer
   * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
   * │   │F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│Num│Scr│
   * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
   * │M4 │M2 │M↑ │M1 │M3 │M5 │   │PgU│ ↑ │PgD│Ply│Prv│Nxt│Clr│Ins│
   * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
   * │   │M← │M↓ │M→ │MW↑│   │Hom│ ← │ ↓ │ → │End│   │   │   │Top│
   * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
   * │   │MA0│MA2│MW←│MW→│   │   │   │VoD│VoU│Mut│   │   │PgU│Btm│
   * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
   * │   │   │   │MW↓│MW↓│MW↓│   │   │   │   │   │App│Hom│PgD│End│
   * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
   */
  [L_FN] = LAYOUT_ortho_5x15( \
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  NUMPAD,  KC_PSCR, \
    KC_BTN4, KC_BTN2, KC_MS_U, KC_BTN1, KC_BTN3, KC_BTN5, _______, KC_PGUP, KC_UP,   KC_PGDN, KC_MPLY, KC_MPRV, KC_MNXT, CLEAR,   KC_INS,  \
    _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_U, _______, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  _______, _______, _______, TOP,     \
    _______, KC_ACL0, KC_ACL2, KC_WH_L, KC_WH_R, _______, _______, _______, KC_VOLD, KC_VOLU, KC_MUTE, _______, _______, KC_PGUP, BOTTOM,  \
    _______, _______, _______, KC_WH_D, KC_WH_D, KC_WH_D, _______, _______, _______, _______, _______, KC_APP,  KC_HOME, KC_PGDN, KC_END   \
  ),

  /* Numpad layer
   * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
   * │Num│   │   │   │   │   │   │P7 │P8 │P9 │P- │ − │ = │Num│   │
   * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
   * │   │   │   │   │   │   │   │P4 │P5 │P6 │P+ │ ( │ ) │   │   │
   * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
   * │   │   │   │   │   │   │   │P1 │P2 │P3 │P* │ × │PEn│PEn│   │
   * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
   * │   │   │   │   │   │   │   │P0 │ , │P. │P/ │ ÷ │   │   │   │
   * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
   * │   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │
   * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
   */
  [L_NUMPAD] = LAYOUT_ortho_5x15( \
    NUMPAD,  _______, _______, _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   KC_PMNS, MINUS,   EQUALS,  NUMPAD,  _______, \
    _______, _______, _______, _______, _______, _______, _______, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, L_PAREN, R_PAREN, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, KC_P1,   KC_P2,   KC_P3,   KC_PAST, TIMES,   KC_PENT, KC_PENT, _______, \
    _______, _______, _______, _______, _______, _______, _______, KC_P0,   COMMA,   KC_PDOT, KC_PSLS, DIVIDE,  _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
  ),
};
