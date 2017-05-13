#include "S60RGB.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _FUNCTION 1
#define _ADJUST 10

//Define readable names for layers in macro functions
#define QWERTY M(_QWERTY)
#define FUNCTION M(_FUNCTION)
#define ADJUST M(_ADJUST)

// Define some shortcuts to tap mods
#define KC_OSLS OSM(MOD_LSFT)
#define KC_OSRS OSM(MOD_RSFT)
#define KC_OSLC OSM(MOD_LCTL)
#define KC_OSRC OSM(MOD_RCTL)
#define KC_OSLA OSM(MOD_LALT)
#define KC_OSRA OSM(MOD_RALT)
#define KC_OSLG OSM(MOD_LGUI)
#define KC_OSRG OSM(MOD_RGUI)
#define KC_OSFN OSL(_FUNCTION)
#define KC_MOAD MO(_ADJUST)

//Custom CAPSGUIFN key
#define KC_FGUI LT(FUNCTION, KC_GUI)

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

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
   * |Ctrl|Gui |Alt |      Space            |Alt |Gui |FN  |Ctrl |
   * `-----------------------------------------------------------'
   */
[_QWERTY] = KEYMAP(
  KC_ESC,    KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,  KC_EQL,   XXXXXXX, KC_BSPC, \
  KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,  KC_RBRC,  KC_BSLS, \
  KC_OSFN,   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,            KC_ENT,  \
  KC_OSLS,         KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,            KC_OSRS,  \
  KC_OSLC, KC_OSLG ,KC_OSLA,                        KC_SPC,                     KC_OSRA,  KC_RGUI, KC_MOAD,  KC_OSRC),

  /* Keymap ADJUST
   * ,-----------------------------------------------------------.
   * |   |   |   |   |   |   |   |   |   |   |   |   |   |       |
   * |-----------------------------------------------------------|
   * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |
   * |-----------------------------------------------------------|
   * |      |   |   |   |   |   |   |       |   |   |   |        |
   * |-----------------------------------------------------------|
   * |        |   |   |   |   |   |   |   |  |   |   |           |
   * |-----------------------------------------------------------|
   * |    |    |    |                        |    |    |    |    |
   * `-----------------------------------------------------------'
   */
[_ADJUST] = KEYMAP(
  KC_GRV,   _______,  _______,  _______,  _______,  _______,  _______,  _______, _______,  _______,   _______,  _______,  RESET,  XXXXXXX,  _______,  \
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______, _______,  _______,   _______,  BL_DEC,   BL_INC,   BL_TOGG, \
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______, _______,  _______,   _______,  _______,  _______, \
  _______,  RGB_TOG,  RGB_MOD,  RGB_HUI,  RGB_HUD,  RGB_SAI,  RGB_SAD,  RGB_VAI, RGB_VAD,  _______,   _______,  _______,  \
  _______,  _______,  _______,                  _______,                _______, _______,  _______,   _______),

  /* Keymap FUNCTION
   * ,-----------------------------------------------------------.
   * |   |   |   |   |   |   |   |   |   |   |   |   |   |       |
   * |-----------------------------------------------------------|
   * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |
   * |-----------------------------------------------------------|
   * |      |   |   |   |   |   |   |       |   |   |   |        |
   * |-----------------------------------------------------------|
   * |        |   |   |   |   |   |   |   |  |   |   |           |
   * |-----------------------------------------------------------|
   * |    |    |    |                        |    |    |    |    |
   * `-----------------------------------------------------------'
   */
[_FUNCTION] = KEYMAP(
  KC_GRV,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   XXXXXXX,  _______,  \
  _______,  KC_PGDN,  KC_UP,    KC_PGUP,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_DEL, \
  _______,  KC_LEFT,  KC_DOWN,  KC_RIGHT, _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______, \
  _______,  KC_MNXT,  KC_VOLD,  KC_VOLU,  KC_MPLY,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  \
  _______,  _______,  _______,                  _______,                _______,  _______,  _______,  _______),
};

const uint16_t PROGMEM fn_actions[] = {

};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {

}
