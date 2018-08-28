#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _NUMPAD 1
#define _FN 2

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define FN MO(_FN)

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
        FN,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  \
    KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   KC_RSFT,   \
    KC_LCTL,  KC_LGUI, KC_LALT, DF(_NUMPAD),          KC_SPC,                             KC_SPC,  KC_RALT,     FN,   KC_APP,  KC_RCTL  \
  ),

/*
   * ,-----------------------------------------------------------.
   * |    |  |   |   |   |   |   |Nlck|  /|  *|  -|   |   |      |
   * |-----------------------------------------------------------|
   * |     |   |   |   |   |   |   |  7|  8|  9|  +|   |   |     |
   * |-----------------------------------------------------------|
   * |      |   |   |   |   |   |   |  4|  5|  6|Bspc|   |Return |
   * |-----------------------------------------------------------|
   * |        |   |   |   |   |   |   |  1|  2|  3|  .|          |
   * |-----------------------------------------------------------|
   * |    |    |    | QWE |       |      0 | .  |A_ON |A_OFF|    |
   * `-----------------------------------------------------------'
   */

  /* Layer 1: Numpad */
  [_NUMPAD] = LAYOUT_split60( \
    _______,  _______,  _______, _______,  _______,  _______,  _______,   KC_NLCK,  KC_PSLS,  KC_PAST,    KC_MINUS,  _______, _______,  KC_BSPC, \
    _______,  _______,  _______, _______,  _______,  _______,  _______,     KC_P7,  KC_P8,        KC_P9,    KC_PLUS,  _______, _______,   KC_BSLS, \
    _______,  _______,  _______, _______,  _______,  _______,  _______,     KC_P4,  KC_P5,        KC_P6,    KC_BSPC, _______,          _______,  \
    _______,  _______,  _______, _______,  _______,  _______,  _______,     KC_P1,  KC_P2,        KC_P3,    KC_DOT,                   _______,   \
    _______,  _______,  _______,DF(_QWERTY),          _______,                 KC_P0,  KC_PDOT,      AU_ON,    AU_OFF, _______  \
  ),

/*
   * ,-----------------------------------------------------------.
   * |  ` |F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12| Delete|
   * |-----------------------------------------------------------|
   * | Caps|pUp| ^ |pDn|   |   |   |pUp| ^ |pDn|PSR|SLK|Pau|     |
   * |-----------------------------------------------------------|
   * |      | < | v | > |   |Hom|Hom| < | v | > |INS| DEL|       |
   * |-----------------------------------------------------------|
   * |        |   |   |   |   |End|End|   |Vo-|Vo+|VoX|          |
   * |-----------------------------------------------------------|
   * |    |    |    |     |       |        |    |     |    |     |
   * `-----------------------------------------------------------'
   */

  /* Layer 2: RAISE */
  [_FN] = LAYOUT_split60( \
     KC_GRV,    KC_F1,    KC_F2,   KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,  KC_F11,   KC_F12,   KC_DEL, \
    KC_CAPS,  KC_PGUP,    KC_UP, KC_PGDN,  _______,  _______,  _______,  KC_PGUP,    KC_UP,  KC_PGDN,    KC_PSCR, KC_SLCK,  KC_PAUS,  _______, \
    _______,  KC_LEFT,  KC_DOWN,KC_RIGHT,  _______,  KC_HOME,  KC_HOME,  KC_LEFT,  KC_DOWN, KC_RIGHT,    KC_INS,  KC_DEL,             _______,  \
    _______,  _______,  _______, _______,  _______,  KC_END,   KC_END,   AU_TOG,  KC_VOLD,  KC_VOLU,    KC_MUTE,                     _______,   \
    _______,  _______,  _______, _______,           _______,             _______,  _______,              _______, _______,  _______  \
  )

};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = TONE_QWERTY;
float tone_numpad[][2]     = TONE_NUMPAD;

uint32_t default_layer_state_set_kb(uint32_t state) {
    if (state == 1UL<<_QWERTY) {
      PLAY_SONG(tone_qwerty);
    } else if (state == 1UL<<_NUMPAD) {
      PLAY_SONG(tone_numpad);
    }    
    return state;
}
#endif

void led_set_keymap(uint8_t usb_led) {  
}
