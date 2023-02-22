#include QMK_KEYBOARD_H


extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define BASE 0 // default layer
#define FLOCK 1 // symbols arrows and F keys on F held down
#define JLOCK 2 // same as Flock but with fall thru J and mapped to J held down

#define FLOCK_F LT(FLOCK, KC_F)
#define FLOCK_J LT(JLOCK, KC_J)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower | Bksp |Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[BASE] = LAYOUT ( \
  TD(1),         KC_2,       KC_3,         KC_4,     KC_5,         KC_MINS, KC_EQL,    KC_6,        KC_7,        KC_8,         KC_9,           KC_0,     \
  KC_Q,         KC_W,       KC_E,         KC_R,     KC_T,         KC_TAB,  KC_TAB,    KC_Y,        KC_U,        KC_I,         KC_O,           KC_P,    \
  SFT_T(KC_A),  ALT_T(KC_S),CTL_T(KC_D),  FLOCK_F,  GUI_T(KC_G),  KC_BSPC, KC_DELETE, GUI_T(KC_H), FLOCK_J,     CTL_T(KC_K),  ALT_T(KC_L),    SFT_T(KC_SCLN), \
  KC_Z,         KC_X,       KC_C,         KC_V,     KC_B,         KC_SPC,  KC_ENT,    KC_N,        KC_M,        KC_COMM,      KC_DOT,         KC_QUOTE
),
[FLOCK] = LAYOUT ( \
  KC_F1,      KC_F2,      KC_F3,       KC_F4,      KC_F5,      KC_F11,     KC_F12,     KC_F6,      KC_F7,      KC_F8,     KC_F9,    KC_F10, \
  KC_LBRC,    KC_GRV,     KC_TILDE,    S(KC_1),    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_HOME,    KC_PGUP,   XXXXXXX,  KC_RBRC, \
  S(KC_LBRC), _______,    _______,     _______,    _______,    XXXXXXX,    XXXXXXX,    KC_LEFT,    KC_DOWN,    KC_UP,     KC_RIGHT, S(KC_RBRC), \
  KC_BSLS,    KC_PIPE,    XXXXXXX,     XXXXXXX,    XXXXXXX,    KC_ESC,     KC_ESC,     XXXXXXX,    KC_END,     KC_PGDN,   KC_QUES,  KC_SLASH \
),
[JLOCK] = LAYOUT ( \
  KC_F1,      KC_F2,      KC_F3,       KC_F4,      KC_F5,      KC_F11,     KC_F12,     KC_F6,      KC_F7,      KC_F8,     KC_F9,    KC_F10, \
  KC_LBRC,    KC_GRV,     KC_TILDE,    S(KC_1),    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_HOME,    KC_PGUP,   XXXXXXX,  KC_RBRC, \
  S(KC_LBRC), _______,    _______,     _______,    _______,    XXXXXXX,    XXXXXXX,    KC_LEFT,    _______,    KC_UP,     KC_RIGHT, S(KC_RBRC), \
  KC_BSLS,    KC_PIPE,    XXXXXXX,     XXXXXXX,    XXXXXXX,    KC_ESC,     KC_ESC,     XXXXXXX,    KC_END,     KC_PGDN,   KC_QUES,  KC_SLASH \
)
};

#ifdef TAP_DANCE_ENABLE
void tap_1(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
  case 1:
    register_code (KC_1);
    unregister_code (KC_1);
    break;
  case 2:
    register_code (KC_ESC);
    unregister_code (KC_ESC);
    break;
  case 3:
    register_code (KC_LSFT);
    register_code (KC_1);
    unregister_code (KC_1);
    unregister_code (KC_LSFT);
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
	[0]  = ACTION_TAP_DANCE_DOUBLE(KC_1, KC_ESC),
  [1]  = ACTION_TAP_DANCE_FN(tap_1)
};
#endif
