#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BL 0
#define _MAC 1
#define _FUNC 2
#define _MOUSE 3

#define MAC_TOG TG(_MAC)

enum {
  FUN_LAY = SAFE_RANGE,
  MOU_TOG,
  WIN_LCK,
  WIN_KEY,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: (Base Layer) Default Layer
   * ,----------------------------------------------------------------.
   * |Esc`| 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |~ ` |
   * |----------------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |Del |
   * |----------------------------------------------------------------|
   * |CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |PgUp|
   * |----------------------------------------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift | Up|PgDn|
   * |----------------------------------------------------------------|
   * |Ctrl|Win |Alt |        Space          |Alt| FN|Ctrl|Lef|Dow|Rig |
   * `----------------------------------------------------------------'
   */
[_BL] = LAYOUT_ansi(
  QK_GESC,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,KC_MINS, KC_EQL,KC_BSPC, KC_GRV,
   KC_TAB,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,KC_LBRC,KC_RBRC,KC_BSLS, KC_DEL,
  KC_CAPS,   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,KC_SCLN,KC_QUOT,         KC_ENT,KC_PGUP,
          KC_LSFT,   KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,KC_COMM, KC_DOT,KC_SLSH,KC_RSFT,  KC_UP,KC_PGDN,
  KC_LCTL,WIN_KEY,KC_LALT,                         KC_SPC,                KC_RALT,FUN_LAY,KC_RCTL,KC_LEFT,KC_DOWN,KC_RGHT),

  /* Keymap _MAC: Mac Layer
   * ,----------------------------------------------------------------.
   * |   |   |   |   |   |   |   |   |   |   |   |   |   |       |    |
   * |----------------------------------------------------------------|
   * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |    |
   * |----------------------------------------------------------------|
   * |      |   |   |   |   |   |   |   |   |   |   |   |        |    |
   * |----------------------------------------------------------------|
   * |        |   |   |   |   |   |   |   |   |   |   |      |   |    |
   * |----------------------------------------------------------------|
   * |Win |Alt |Ctrl|                       |Ctrl|   |Win|   |   |    |
   * `----------------------------------------------------------------'
   */
[_MAC] = LAYOUT_ansi(
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        _______,_______,
          _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
  KC_LGUI,KC_LALT,KC_LCTL,                        _______,                KC_RCTL,_______,KC_RGUI,_______,_______,_______),


  /* Keymap _FUNC: Function Layer
   * ,----------------------------------------------------------------.
   * |   |F1 |F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|  Del  |HPg |
   * |----------------------------------------------------------------|
   * |     |   |   |   |   |   |   |   |Mac|   |PSc|ScL|PsB| Calc|Ins |
   * |----------------------------------------------------------------|
   * |      |   |   |   |   |   |   |   |Stp|Ply|PTr|NTr|        |Hme |
   * |----------------------------------------------------------------|
   * |        |BL |Bl-|Bl+|   |   |   |Mou|MUT|VU-|VU+|      |PgU|End |
   * |----------------------------------------------------------------|
   * |    |WnLc|    |                       |   |   |    |Hme|PgD|End |
   * `----------------------------------------------------------------'
   */
[_FUNC] = LAYOUT_ansi(
  _______,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL,KC_WHOM,
  _______,_______,_______,_______,_______,_______,_______,_______,MAC_TOG,_______,KC_PSCR,KC_SCRL,KC_PAUS,KC_CALC, KC_INS,
  _______,_______,_______,_______,_______,_______,_______,_______,KC_MSTP,KC_MPLY,KC_MPRV,KC_MNXT,        _______,KC_HOME,
          _______,BL_TOGG, BL_DOWN,BL_UP, _______,_______,_______,MOU_TOG,KC_MUTE,KC_VOLD,KC_VOLU,_______,KC_PGUP,KC_END ,
  _______,WIN_LCK,_______,                        _______,                _______,_______,_______,KC_HOME,KC_PGDN,KC_END),

  /* Keymap _MOUSE: Mouse Navigation Layer
   * ,----------------------------------------------------------------.
   * |   |   |   |   |   |   |   |   |   |   |   |   |   |       |    |
   * |----------------------------------------------------------------|
   * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |    |
   * |----------------------------------------------------------------|
   * |      |   |   |   |   |   |   |   |   |   |   |   |   McR  |    |
   * |----------------------------------------------------------------|
   * |        |   |   |   |   |   |   |   |   |   |   |  McL |MsU|    |
   * |----------------------------------------------------------------|
   * |    |    |    |                       |   |   |    |MsL|MsD|MsR |
   * `----------------------------------------------------------------'
   */
[_MOUSE] = LAYOUT_ansi(
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        KC_BTN2,_______,
          _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,KC_BTN1,KC_MS_U,_______,
  _______,_______,_______,                        _______,                _______,_______,_______,KC_MS_L,KC_MS_D,KC_MS_R),

};

#define SET_BIT(var, pos) (var |= (1UL << pos))
#define CLEAR_BIT(var, pos) (var &= ~(1UL << pos))
#define TOGGLE_BIT(var, pos) (var ^= (1UL << pos))
#define CHECK_BIT(var, pos) (var & (1U << pos)) 

static uint8_t keyboard_state = 0;
// bit 0 = function layer status (on/off)
// bit 1 = mouse navigation layer state
// bit 2 = windows key lock state

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    // acts like a momentary function layer press
    case FUN_LAY:
      if (record->event.pressed) { 
        layer_on(_FUNC);
        if (CHECK_BIT(keyboard_state, 1)) {
          layer_on(_MOUSE);
        } 
        else {
          layer_off(_MOUSE);
        }
        // turns on function layer status
        SET_BIT(keyboard_state, 0);
      }
      // key released
      else {
        layer_off(_FUNC);
        layer_off(_MOUSE);
        // turns off function layer status
        CLEAR_BIT(keyboard_state, 0);
      }
      break;

    case MOU_TOG:
      if(record->event.pressed) {
        // toggles navigation layer state
        TOGGLE_BIT(keyboard_state, 1);

        // if FN is pressed down while hitting this key, the correct layer will be updated,
        // so that the FN key doesn't need to be pressed down again to start using the functionality
        if (CHECK_BIT(keyboard_state, 0)) {
          if (CHECK_BIT(keyboard_state, 1)) {
            layer_on(_MOUSE);
          }
          else {
            layer_off(_MOUSE);
          } 
        }
      }
      break;

    case WIN_LCK:
      if (record->event.pressed) {
        // toggles windows key lock state
        TOGGLE_BIT(keyboard_state, 2);
      }
      break;

    // uses seperate WIN_KEY so that WIN_LCK does not affect Mac Layer's KC_LGUI
    case WIN_KEY:
      // checks if windows key lock is off to allow key to be pressed
      if (!CHECK_BIT(keyboard_state, 2)) {
        if (record->event.pressed) {
          SEND_STRING(SS_DOWN(X_LGUI));
          return false;
        }
        // key released
        else { 
          SEND_STRING(SS_UP(X_LGUI));
          return false;
        }
      }
      break;
  }
  return true;
};
