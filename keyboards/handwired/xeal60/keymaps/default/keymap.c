#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _NUMPAD 1
#define _RAISE 4

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  NUMPAD, 
  RAISE
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
   * ,-----------------------------------------------------------.
   * |Esc~| 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |
   * |-----------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |
   * |-----------------------------------------------------------|
   * |FN     |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |
   * |-----------------------------------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /| Shift    |
   * |-----------------------------------------------------------|
   * |Ctrl|Gui |Alt | NUM | Space |  Space |Alt |FN  |Menu |Ctrl |
   * `-----------------------------------------------------------'
   */
  /* Layer 0: Qwerty */
  [_QWERTY] = LAYOUT_split60( \
    KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, \
    KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, \
    RAISE,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  \
    KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   KC_RSFT,   \
    KC_LCTL,  KC_LGUI, KC_LALT, NUMPAD,           KC_SPC,                             KC_SPC,  KC_RALT, RAISE,   KC_MENU, KC_RCTL  \
  ),

/*
   * ,-----------------------------------------------------------.
   * |    |  |   |   |   |   |   |   |  /|  *|  -|   |   |       |
   * |-----------------------------------------------------------|
   * |     |   |   |   |   |   |   |  7|  8|  9|  +|   |   |     |
   * |-----------------------------------------------------------|
   * |      |   |   |   |   |   |   |  4|  5|  6|Bspc|   |Return |
   * |-----------------------------------------------------------|
   * |        |   |   |   |   |   |   |  1|  2|  3|  .|          |
   * |-----------------------------------------------------------|
   * |    |    |    | QWE |       |      0 | .  |     |    |     |
   * `-----------------------------------------------------------'
   */

  /* Layer 1: Numpad */
  [_NUMPAD] = LAYOUT_split60( \
    _______,  _______,  _______, _______,  _______,  _______,  _______,  _______,    KC_PSLS,  KC_PAST,    KC_MINUS,  _______, _______,  KC_BSPC, \
    _______,  _______,  _______, _______,  _______,  _______,  _______,     KC_7,    KC_8,        KC_9,    KC_PLUS,  _______, _______,   KC_BSLS, \
    _______,  _______,  _______, _______,  _______,  _______,  _______,     KC_4,    KC_5,        KC_6,    KC_BSPC, _______,          _______,  \
    _______,  _______,  _______, _______,  _______,  _______,  _______,     KC_1,    KC_2,        KC_3,    KC_DOT,                   _______,   \
    _______,  _______,  _______,  QWERTY,           KC_SPC,                 KC_0,  KC_DOT,       RAISE,    _______, _______  \
  ),

/*
   * ,-----------------------------------------------------------.
   * |    |  |   |   |   |   |   |   |   |   |   |   |   |       |
   * |-----------------------------------------------------------|
   * |     |   | ^ |   |   |   |   |pUp| ^ |pDn|   |   |   |     |
   * |-----------------------------------------------------------|
   * |      | < | v | > |   |   |Hom| < | v | > |    |   |       |
   * |-----------------------------------------------------------|
   * |        |   |   |   |   |   |End|   |   |   |   |          |
   * |-----------------------------------------------------------|
   * |    |    |    |     |       |        |    |     |    |     |
   * `-----------------------------------------------------------'
   */

  /* Layer 2: RAISE */
  [_RAISE] = LAYOUT_split60( \
    _______,  _______,  _______, _______,  _______,  _______,  _______,  _______,    _______,  _______,    _______,  _______, _______,  _______, \
    _______,  _______,  _______, _______,  _______,  _______,  _______,  _______,    _______,  _______,    _______,  _______, _______,   _______, \
    _______,  _______,  _______, _______,  _______,  _______,  _______,  _______,    _______,  _______,    _______, _______,          _______,  \
    _______,  _______,  _______, _______,  _______,  _______,  _______,  _______,    _______,  _______,    _______,                   _______,   \
    _______,  _______,  _______, _______,           _______,             _______,    _______,  _______,    _______, _______  \
  )

};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_numpad[][2]     = SONG(DVORAK_SOUND);
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case NUMPAD:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_numpad);
        #endif
        default_layer_set(1UL<<_NUMPAD);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      return false;
      break;
  }
  return true;
}
