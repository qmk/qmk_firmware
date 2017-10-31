#include "satan.h"
#include "action_layer.h"

#define _DEFAULT 0
#define _FN 1
#define _MOUSE 2
#define _MOUSESHIFT 3

// Fillers to make layering more clear
#define ______ KC_TRNS

enum {
  SUPER_FN = 0,
  SINGLE_HOLD = 1,
  TRIPLE_HOLD = 2
};

typedef struct {
  bool is_press_action;
  int state;
} tap;

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1 && (state->interrupted == false || state->pressed)) return SINGLE_HOLD;
  else if (state->count == 3 && (state->interrupted == false || state->pressed)) return TRIPLE_HOLD;
  else return 3;
}

//instantiate an instance of 'tap' for the 'fn' tap dance.
static tap fn_tap_state = {
  .is_press_action  = true,
  .state = 0
};

void fn_finished (qk_tap_dance_state_t *state, void *user_data) {
  fn_tap_state.state = cur_dance(state);
  switch (fn_tap_state.state) {
    /* case SINGLE_HOLD: register_code(MO(_FN)); break; */
    case SINGLE_HOLD: layer_on(_FN); break;
    case TRIPLE_HOLD: layer_on(_MOUSE);
  }
}

void fn_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (fn_tap_state.state) {
    case SINGLE_HOLD: layer_off(_FN); break;
    case TRIPLE_HOLD: layer_off(_MOUSE);
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [SUPER_FN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, fn_finished, fn_reset)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty gui/alt/space/alt/gui
 * ,-----------------------------------------------------------------------------------------.
 * | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |  \  |  `  |
 * |-----------------------------------------------------------------------------------------+
 * | Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |  Bksp  |
 * |-----------------------------------------------------------------------------------------+
 * | Ctrl    |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter    |
 * |-----------------------------------------------------------------------------------------+
 * | Shift     |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  | RShift    | FN  |
 * |-----------------------------------------------------------------------------------------+
 *         |LGUI | LAlt  |               Space                | RAlt   |RGUI |
 *         `-----------------------------------------------------------------'
 * note: s/RESET/KC_RALT/
 */
  [_DEFAULT] = KEYMAP_HHKB( /* Basic QWERTY */
      KC_ESC,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,    KC_9,   KC_0,       KC_MINS,    KC_EQL, KC_BSLS,    KC_GRV, \
      KC_TAB,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,   KC_P,       KC_LBRC,    KC_RBRC,KC_BSPC,  \
      KC_LCTL,  KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,    KC_L,   KC_SCLN,    KC_QUOT,    KC_ENT,   \
      KC_LSFT,  KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT, KC_SLSH,    KC_RSFT,    TD(SUPER_FN), \
      ______,   KC_LGUI,KC_LALT,                KC_SPC,                          KC_RALT,KC_RGUI,    ______,     ______ \
      ),

/* FN Layer
 * ,-----------------------------------------------------------------------------------------.
 * |     | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | F11 | F12 | Ins | Del |
 * |-----------------------------------------------------------------------------------------+
 * |  CAPS  | BL- | BL+ | BL  |     |     |     |     | Psc | Slck| Paus| Up  |     |        |
 * |-----------------------------------------------------------------------------------------+
 * |         | Vol-| Vol+| Mute|     |     | *   | /   | Home| PgUp| Left|Right|             |
 * |-----------------------------------------------------------------------------------------+
 * |           | Prev| Play| Next|     |     | +   | -   | End  |PgDn| Down|           |     |
 * |-----------------------------------------------------------------------------------------+
 *         |       |       |                                 | Stop  |       |
 *         `-----------------------------------------------------------------'
 */
  [_FN] = KEYMAP_HHKB( /* Layer 1 */
      ______, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, KC_INS,  KC_DEL, \
      KC_CAPS,  ______, ______, ______, ______, ______, ______, ______, KC_PSCR, KC_SLCK, KC_PAUS, KC_UP,   ______, ______,  \
      ______,   KC_VOLD,KC_VOLU,KC_MUTE,______, ______, KC_PAST,KC_PSLS,KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT, ______,   \
      ______,   KC_MPRV,KC_MPLY,KC_MNXT,______, ______, KC_PPLS,KC_PMNS,KC_END,  KC_PGDN, KC_DOWN, ______,  ______,  \
      ______,   ______, ______,                 ______,                 KC_MSTP, ______,  ______,  ______ \
      ),

/* MOUSE Layer
 * ,-----------------------------------------------------------------------------------------.
 * |     |     |     |     |     |     |     |     |     |     |     |     |     |     |RESET|
 * |----------------------------------------------------------------------------------------- 
 * |        |     |     |     |     |     |     |     |     |     |     |UCurs|     |        |
 * |----------------------------------------------------------------------------------------- 
 * |         |     |     |     |     |     |     |     |     |     |LCurs|RCurs|             |
 * |----------------------------------------------------------------------------------------- 
 * | ScrollHold|     |     |     |     |     |     |     |      |    |DCurs| ScrollHold|     |
 * |-----------------------------------------------------------------------------------------+
 *         |       |       |                          LClick | MClick| RClick|
 *         `-----------------------------------------------------------------'
 */
  [_MOUSE] = KEYMAP_HHKB(
      ______,   ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,  RESET, \
      ______,   ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, KC_MS_UP, ______, ______,  \
      ______,   ______, ______, ______, ______, ______, ______, ______, ______, ______, KC_MS_LEFT, KC_MS_RIGHT, ______,   \
      MO(_MOUSESHIFT), ______, ______, ______, ______, ______, ______, ______, ______, ______, KC_MS_DOWN, MO(_MOUSESHIFT), ______,  \
      ______,   ______, ______,                 KC_MS_BTN1,                 KC_MS_BTN3, KC_MS_BTN2, ______, ______ \
      ),

/* MOUSESHIFT Layer
 * ,-----------------------------------------------------------------------------------------.
 * |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
 * |----------------------------------------------------------------------------------------- 
 * |        |     |     |     |     |     |     |     |     |     |     |UScrl|     |        |
 * |----------------------------------------------------------------------------------------- 
 * |         |     |     |     |     |     |     |     |     |     |LScrl|RScrl|             |
 * |----------------------------------------------------------------------------------------- 
 * |           |     |     |     |     |     |     |     |      |    |DScrl|           |     |
 * |-----------------------------------------------------------------------------------------+
 *         |       |       |                                 |       |       |
 *         `-----------------------------------------------------------------'
 */
  [_MOUSESHIFT] = KEYMAP_HHKB(
      ______,   ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, \
      ______,   ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, KC_MS_WH_UP, ______, ______,  \
      ______,   ______, ______, ______, ______, ______, ______, ______, ______, ______, KC_MS_WH_LEFT, KC_MS_WH_RIGHT, ______,   \
      ______,   ______, ______, ______, ______, ______, ______, ______, ______, ______, KC_MS_WH_DOWN, ______, ______,  \
      ______,   ______, ______,                 ______,                 ______, ______, ______, ______ \
      )
};
