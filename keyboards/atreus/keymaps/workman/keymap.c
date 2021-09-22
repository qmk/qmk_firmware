#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QW 0
#define _RS 1
#define _LW 2

#define OSM_SFT OSM(MOD_LSFT)

/* In your system, make sure Caps Lock acts as the Compose Key, also known as the Multi Key. If so, then the quote on
 * the lower layer acts as macro to enter ¨ */
enum custom_keycodes {
	DIAERESIS = SAFE_RANGE,
	EN_DASH
};

  /* Basic layer (L0)
   *  q      d      r      w      b        ||       j      f      u      p      ;
   *  a      s      h      t      g        ||       y      n      e      o      i
   *  z      x      m      c      v        ||       k      l      ,      .      /
   * esc    tab   super  shift  bksp  ctrl || alt  space   RS     LW     '     ret
   */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QW] = LAYOUT( /* Workman */
    KC_Q,    KC_D,    KC_R,    KC_W,    KC_B,                      KC_J,    KC_F,    KC_U,    KC_P,    KC_SCLN,
    KC_A,    KC_S,    KC_H,    KC_T,    KC_G,                      KC_Y,    KC_N,    KC_E,    KC_O,    KC_I,
    KC_Z,    KC_X,    KC_M,    KC_C,    KC_V,                      KC_K,    KC_L,    KC_COMM, KC_DOT,  KC_SLSH,
    KC_ESC, KC_TAB, KC_LGUI,  OSM_SFT, KC_BSPC,  KC_LCTL, KC_LALT, KC_SPC,  MO(_RS), MO(_LW), KC_QUOT, KC_ENT
  ),

  /* Raised layer (RS)
   *  !       @     {      }      |        ||       -      7      8      9      *
   *  #       $     (      )      `        ||       .      4      5      6      +
   *  %       ^     [      ]      ~        ||       &      1      2      3      \
   * menu    caps   <      >     del       ||       _                    0      =
   */

  [_RS] = LAYOUT( /* [> RAISE <] */
    KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE,                   KC_MINS, KC_7,    KC_8,    KC_9, KC_ASTR,
    KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,                    KC_DOT,  KC_4,    KC_5,    KC_6, KC_PLUS,
    KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD,                   KC_AMPR, KC_1,    KC_2,    KC_3, KC_BSLS,
    KC_MENU, KC_CAPS, KC_LT,   KC_GT,   KC_DEL,  KC_TRNS, KC_TRNS, KC_UNDS, KC_TRNS, KC_TRNS,  KC_0, KC_EQL ),

  /* Lower layer (LW)
   * insert  home   up    end    pgup      ||      vol+    F7     F8     F9    F10
   *  del    left  down  right   pgdn      ||      vol-    F4     F5     F6    F11
   *                                       ||      mute    F1     F2     F3    F12
   *                                       ||        –                    ¨    reset
   */

  [_LW] = LAYOUT( /* [> LOWER <] */
    KC_INS,  KC_HOME, KC_UP,   KC_END,  KC_PGUP,                   KC_VOLU, KC_F7,   KC_F8,   KC_F9,   KC_F10,
    KC_DELT, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,                   KC_VOLD, KC_F4,   KC_F5,   KC_F6,   KC_F11,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_MUTE, KC_F1,   KC_F2,   KC_F3,   KC_F12,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, EN_DASH, KC_TRNS, KC_TRNS, DIAERESIS, RESET  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch(keycode) {
		case DIAERESIS:
			// assuming KC_CAPS is your Multi Key
			SEND_STRING(SS_TAP(X_CAPSLOCK)"\"");
			return false;
		case EN_DASH:
			// assuming KC_CAPS is your Multi Key
			SEND_STRING(SS_TAP(X_CAPSLOCK)"--.");
			return false;
        }
    }
    return true;
};
