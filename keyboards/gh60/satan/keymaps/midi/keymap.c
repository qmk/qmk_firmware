#include QMK_KEYBOARD_H


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BL 0
#define _ML 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: (Base Layer) Default Layer
   * ,-----------------------------------------------------------.
   * |Esc | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |
   * |-----------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |
   * |-----------------------------------------------------------|
   * |CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |
   * |-----------------------------------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |
   * |-----------------------------------------------------------|
   * |Ctrl|Gui |Alt |      Space            |Alt |Gui |Midi|Ctrl |
   * `-----------------------------------------------------------'
   */
  [_BL] = LAYOUT_60_ansi(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
    KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,
    KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                                      KC_RALT, KC_RGUI, TG(_ML), KC_RCTL
  ),

  #if defined(MIDI_ENABLE) && defined(MIDI_ADVANCED)
  /* Keymap _ML: MIDI Layer (Advanced)
   * ,------------------------------------------------------------------------.
   * | Exit |    |    |    |    |    |    |    |    |    |    |    |    |     |
   * |------------------------------------------------------------------------|
   * |  Ch+ |    | C# | D# |    | F# | G# | A# |    | C# | D# |    |    |     |
   * |------------------------------------------------------------------------|
   * |  Mod  | C  | D  | E  | F  | G  | A  | B  | C  | D  | E  | F  |         |
   * |------------------------------------------------------------------------|
   * | Sustain |Oct-|Oct+|Mod-|Mod+|    |    |    |Tns-|Tns+|Tns0|   Sustain  |
   * |------------------------------------------------------------------------|
   * |     |     |     |         All notes off        |     |     |     |     |
   * `------------------------------------------------------------------------'
   */
  [_ML] = LAYOUT_60_ansi(
    TG(_ML), MI_VL1,   MI_VL2,   MI_VL3,    MI_VL4,   MI_VL5,   MI_VL6,   MI_VL7,   MI_VL8,   MI_VL9,   MI_VL10,   XXXXXXX,   XXXXXXX, XXXXXXX,
    MI_CHNU, XXXXXXX,  MI_Cs,    MI_Ds,     XXXXXXX,  MI_Fs,    MI_Gs,    MI_As,    XXXXXXX,  MI_Cs1,  MI_Ds1,   XXXXXXX,   XXXXXXX, XXXXXXX,
    MI_MOD,  MI_C,     MI_D,     MI_E,      MI_F,     MI_G,     MI_A,     MI_B,     MI_C1,   MI_D1,   MI_E1,    MI_F1,             _______,
    MI_SUST,           MI_OCTD,  MI_OCTU,   MI_MODD,  MI_MODU,  XXXXXXX,  XXXXXXX,  XXXXXXX,  MI_TRSD,  MI_TRSU,   MI_TR0,             MI_SUST,
    _______, _______,  _______,                       MI_AOFF,                                          _______,   _______,   _______, _______
  ),
  #elif defined(MIDI_ENABLE) && defined(MIDI_BASIC)
  /* Keymap _ML: MIDI Layer (Advanced)
   * ,------------------------------------------------------------------------.
   * | Exit |    |    |    |    |    |    |    |    |    |    |    |    |     |
   * |------------------------------------------------------------------------|
   * |      |    |    |    |    |    |    |    |    |    |    |    |    |     |
   * |------------------------------------------------------------------------|
   * |       |    |    |    |    |    |    |    |    |    |    |    |         |
   * |------------------------------------------------------------------------|
   * |         |MuOn|MuOf|MiOn|MiOf|    |    |    |    |    |    |            |
   * |------------------------------------------------------------------------|
   * |     |     |     |                              |     |     |     |     |
   * `------------------------------------------------------------------------'
   */

  [_ML] = LAYOUT_60_ansi(
    TG(_ML), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
    _______,          MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______, _______,          _______,
    _______, _______, _______,                   _______,                                     _______, _______, _______, _______
  ),
  #endif
};
