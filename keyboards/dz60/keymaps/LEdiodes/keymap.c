#include QMK_KEYBOARD_H

#define _L0 0
#define _L1 1
#define _L2 2
#define _L3 3
#define _L4 4

#define _______ KC_TRNS

enum {
  TD_SPC_ENT = 0,
  TD_KC_LSFT_CAPS,
  TD_KC_RSFT_CAPS
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * template
 * [_L1] = LAYOUT(
 *      _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,    \
 *      _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        _______,        \
 *       _______,        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        _______,        \
 *      _______,        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,   \
 *       _______,_______,_______,        _______,_______,_______,                _______,_______,_______,_______,_______,
 *
 *
 *\

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 * Keymap _L0: (Layer 0 - Base Layer) This is the default layer
 * This layer has a key set to MO(_L1) which means when held down Layer 1 will become active, If Layer 1 does not have anything set for tat key is will revert to uing the key set at layer 0.
 * LT(_L1, KC_1) means that when the "1" key is long touched then it will activate the layer _L1 key(F1) but if the key is just tapped it will activate the "1" key.
 * KC_GESC = Escape when tapped, ` when pressed with Shift or GUI
 * KC_LSPO = Left Shift when held, ( when tapped
 * TD(LT(_L3,KC_SPACE)) = This is a test... hoping it will tap dance if double tapped it does enter if single tap it does space if long hold down it does _L3(Layer 3).
 * LT(_L3,KC_SPACE) = if tapped it does space, is long touch it does _L3(Layer 3)
 * BL_TOGG = Toggles the LEDs.
 * ,-----------------------------------------------------------------------------------------.
 * | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |Bkspc| Del |
 * |-----------------------------------------------------------------------------------------+
 * | Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |    \   |
 * |-----------------------------------------------------------------------------------------+
 * | _L4    |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter    |
 * |-----------------------------------------------------------------------------------------+
 * | Shift     |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  | RSh |  U  | _L1 |
 * |-----------------------------------------------------------------------------------------+
 * | Ctrl |  Win  |  Alt  |  _L3[Space]  |LEdiodes|      Space       |Win | _L2|  L |  D |  R |
 * `-----------------------------------------------------------------------------------------'
 */
[_L0] = LAYOUT(
      KC_GESC,              LT(_L1, KC_1),LT(_L1, KC_2),LT(_L1, KC_3),LT(_L1, KC_4),LT(_L1, KC_5),LT(_L1, KC_6),LT(_L1, KC_7),LT(_L1, KC_8),LT(_L1, KC_9),LT(_L1, KC_0),LT(_L1, KC_MINS),LT(_L1, KC_EQL),KC_BSPC,  KC_DEL,    \
      KC_TAB,              KC_Q,    KC_W,    KC_E,     KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,    KC_P,    KC_LBRC,  KC_RBRC,           KC_BSLS,   \
      KC_CAPS,             KC_A,    KC_S,    KC_D,     KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,    KC_SCLN, KC_QUOT,              KC_ENT,    \
      KC_LSPO,   KC_Z,    KC_X,     KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT, KC_UP,    TO(_L1), \
      KC_LCTL,             KC_LGUI, KC_LALT, LT(_L3,KC_SPACE),BL_TOGG,TD(TD_SPC_ENT),     KC_RGUI, TO(_L2), KC_LEFT,  KC_DOWN,  KC_RIGHT),

/* Keymap _L1: (Layer 1) This is function layer 1
 * This layer is activated while the Fn key is being held down.
 * ,-----------------------------------------------------------------------------------------.
 * | Reset |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 | F13| F14|
 * |-----------------------------------------------------------------------------------------+
 * |        |  WhUp|  U  | WhDn |    |    |     |     |     | PrtScr |     |    |    |       |
 * |-----------------------------------------------------------------------------------------+
 * |         |  L   |   D  |  R  |     |     | Home |     |     |     |     |      |         |
 * |-----------------------------------------------------------------------------------------+
 * |           |      |     |     |     |     |  End | VolDn|VolUp|Mute |    |   | PgUp|     |
 * |-----------------------------------------------------------------------------------------+
 * |      |       |      |          |       |                |      |      | Home| PgDn| End |
 * `-----------------------------------------------------------------------------------------'
 */
[_L1] = LAYOUT(
      RESET,   KC_F1,   KC_F2,   KC_F3,    KC_F4,   KC_F5,  KC_F6,    KC_F7,    KC_F8,    KC_F9,     KC_F10,   KC_F11,   KC_F12,  KC_F13,   KC_F14,              \
      _______, KC_WH_U, KC_UP,   KC_WH_D,  _______, _______,_______,  _______,  _______,  _______,   KC_PSCR, _______,  _______,                      _______,   \
      _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______, KC_HOME, _______,  _______,  _______,   KC_HOME, _______,                        _______,   \
      _______,           _______,  KC_APP,  BL_STEP,_______,  KC_END,   KC_VOLD,  KC_VOLU,   KC_MUTE, _______,  _______,  _______, KC_PGUP,   _______,   \
      _______, _______, _______,                                _______,_______,_______,                _______, _______,         KC_HOME, KC_PGDOWN, KC_END),

/* Keymap _L2: (Layer 2) This is function layer 2
 * This layer is activated while the Fn2 key is being held down.
 * LCA(KC_TAB) = Hold Left Control and Alt and press kc_tab which cycles trough open apps.
 * MEH(KC_TAB) = Hold Left Control, Shift and Alt and press kc_TAB to cycle backwards through apps.
 * ,-----------------------------------------------------------------------------------------.
 * |  |   |   |   |   |   |   |   |   |   |  |  |  | | LCA(KC_TAB)|
 * |-----------------------------------------------------------------------------------------+
 * |        |  |    |  |    |    |     |     |     |  |     |    |    |       |MEH(KC_TAB)
 * |-----------------------------------------------------------------------------------------+
 * |         |     |     |    |     |     | |     |     |     |     |      |         |
 * |-----------------------------------------------------------------------------------------+
 * |           |      |     |     |     |     |   | || |    |   | |     |
 * |-----------------------------------------------------------------------------------------+
 * |      |       |      |          |       |                |      |      | | |  |
 * `-----------------------------------------------------------------------------------------'
 */
[_L2] = LAYOUT(
      _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,LCA(KC_TAB),    \
      _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        MEH(KC_TAB),        \
      _______,        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,                \
      _______,        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,KC_MS_BTN1,KC_MS_UP,KC_MS_BTN2,   \
      _______,_______,_______,        _______,_______,_______,                _______,_______,KC_MS_LEFT,KC_MS_DOWN,KC_MS_RIGHT)

};

// Custom Actions
const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(1),  // to Fn overlay
};

// Macros
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {

  // MACRODOWN only works in this function
  switch(id) {
    case 0:
      if (record->event.pressed) { register_code(KC_RSFT); }
      else { unregister_code(KC_RSFT); }
      break;
  }

  return MACRO_NONE;
};

// Loop
void matrix_scan_user(void) {
  // Empty
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {

  //Tap once for space, tap twice for enter
  [TD_SPC_ENT]  = ACTION_TAP_DANCE_DOUBLE(KC_SPC, KC_ENT),
  //Tap once for Left Shift, twice for Caps Lock
  [TD_KC_LSFT_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
  //Tap once for Right Shift, twice for Caps Lock
  [TD_KC_RSFT_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_RSFT, KC_CAPS)

// Other declarations would go here, separated by commas, if you have them

};
