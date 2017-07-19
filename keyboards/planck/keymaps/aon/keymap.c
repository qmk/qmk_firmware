// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.

#include "planck.h"
#include "action_layer.h"
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum planck_layers {
  _DVORAK,
  _NUMBER,
  _MOVE,
  _FUNC,
  _NUMP
};

enum planck_keycodes {
  DVORAK
};

// Unicode map
const uint32_t PROGMEM unicode_map[] = {
  0x2013
};

//set_unicode_mode(UC_LNX)

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * | `    |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | !    |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | /    |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  -   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | \    |   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |  ?   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | TAB  | Time | Game | Esc  |Space | Del  | Bksp | Enter| Menu |      | FUNC |Move  |
 * |      | NUMP |      |      |Shift | Alt  | Ctrl | Num  |(comp)|      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

[_DVORAK] = {
  {KC_GRAVE,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_EXLM},
  {KC_SLSH,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINUS},
  {KC_BSLASH, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_QUES},
  {LT(_NUMBER,KC_TAB), LGUI(KC_QUOT), XXXXXXX, GUI_T(KC_ESC), SFT_T(KC_SPC), ALT_T(KC_DEL), CTL_T(KC_BSPC), LT(_NUMBER,KC_ENTER), KC_APP, XXXXXXX, MO(_FUNC), MO(_MOVE)}
},

/* Numbers layer
 * ,-----------------------------------------------------------------------------------.
 * |      | *    |  ^   |  $   |  @   |  /   |  =   |  ♥   |   #  |  %   |  &   |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   0  |  8   |  6   |  4   |  2   |  -   |  +   |  1   |   3  |   5  |  7   |  9   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |   {  |  [   |  <   |  (   |  ,   |  _   |  °   |  .   |   )  |   >  |  ]   |  }   |
 * |-----------------------------------------------------------------------------------|
 * |      | Time | Game |      |Space | Del  | Bksp | Enter| Menu |      |      |      |
 * |      |      |      |      |Shift | Alt  | Ctrl | Num  |(comp)|      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

[_NUMBER] = {
  {XXXXXXX, KC_ASTR, KC_CIRC, KC_DLR, KC_AT, KC_SLSH, KC_EQL, UC(2665), KC_HASH, KC_PERC, KC_AMPR, XXXXXXX},
  {KC_0, KC_8, KC_6, KC_4,   KC_2,  KC_MINS, KC_PLUS, KC_1,  KC_3, KC_5,  KC_7,  KC_9},
  {KC_LCBR, KC_LBRC, KC_LABK, KC_LPRN, KC_COMM, KC_UNDS, XXXXXXX, KC_DOT, KC_RPRN, KC_RABK, KC_RBRC, KC_RCBR},
  {_______, _______, XXXXXXX, XXXXXXX, _______, _______, _______, _______, _______, _______, _______, XXXXXXX}
},

/* Movement layer
 * ,-----------------------------------------------------------------------------------.
 * |  ☽   | M1:1 |  M1:2|  M1:3|  M1:4| Moncl|      | Home |Pg Up |Pg Dwn| End  |Ins   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Close| M2:1 |  M2:2|  M2:3|  M2:4|Float |URXVT | ←    | ↑    |   ↓  |  →   |  MR  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Lock | M3:1 | M3:2 |  M3:3|  M3:4|Tile  |Rofi  | M←   |  M↑  |  M↓  |  M→  |  M↻  |
 * |-----------------------------------------------------------------------------------|
 * | Rld  | Time | Game |      |      | Alt  | Ctrl |      |      |      |      |Move  |
 * |      | Ctrl |      |      |Shift |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

[_MOVE] = {
  {KC_SLEP, LGUI(KC_1), LGUI(KC_2), LGUI(KC_3), LGUI(KC_4), LGUI(KC_M), XXXXXXX, KC_HOME, KC_PGUP, KC_PGDN, KC_END, KC_INS},
  {LGUI(KC_W), LGUI(KC_5), LGUI(KC_6), LGUI(KC_7), LGUI(KC_8), LGUI(KC_S), LGUI(KC_ENTER), KC_LEFT, KC_UP, KC_DOWN, KC_RIGHT, XXXXXXX},
  {LGUI(F1), LGUI(KC_9), LGUI(KC_0), XXXXXXX, XXXXXXX, LGUI(KC_T), LGUI(KC_SPACE), LGUI(KC_H), LGUI(KC_K), LGUI(KC_J), LGUI(KC_L), LGUI(KC_C)},
  {LGUI(KC_ESC), _______, XXXXXXX, KC_LGUI, KC_LSFT, KC_LALT, KC_LCTRL, XXXXXXX, XXXXXXX, _______, _______, _______}
},

/* Function layer
 * ,-----------------------------------------------------------------------------------.
 * |  ☽   | F1   |  F2  |  F3  |  F4  | Moncl|      | Home |Pg Up |Pg Dwn| End  |Ins   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Close| F5   |  F6  | F7   |  F8  |Float |URXVT | ←    | ↑    |   ↓  |  →   |  MR  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Lock | F9   |  F10 |  F11 |  F12 |Tile  |Rofi  | M←   |  M↑  |  M↓  |  M→  |  M↻  |
 * |-----------------------------------------------------------------------------------|
 * | Rld  | Time | Game |      |      | Alt  | Ctrl |      |      |      |FUNC  |NUMP  |
 * |      | Ctrl |      |      |Shift |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

[_FUNC] = {
  {KC_SLEP, KC_F1, KC_F2, KC_F3, KC_F4, LGUI(KC_M), XXXXXXX, KC_HOME, KC_PGUP, KC_PGDN, KC_END, KC_INS},
  {LGUI(KC_W), KC_F5, KC_F6, KC_F7, KC_F8, LGUI(KC_S), LGUI(KC_ENTER), KC_LEFT, KC_UP, KC_DOWN, KC_RIGHT, XXXXXXX},
  {LGUI(F1), KC_F9, KC_F10, KC_F11, KC_F12, LGUI(KC_T), LGUI(KC_SPACE), LGUI(KC_H), LGUI(KC_K), LGUI(KC_J), LGUI(KC_L), LGUI(KC_C)},
  {LGUI(KC_ESC), _______, XXXXXXX, KC_LGUI, KC_LSFT, KC_LALT, KC_LCTRL, XXXXXXX, XXXXXXX, _______, _______, TO(_NUMP)}
},

/* Numpad layer
 * ,-----------------------------------------------------------------------------------.
 * |  ☽   | F1   |  F2  |  F3  |  F4  | Moncl| NUMLK| NUM7 |NUM8  |NUM9  | End  |Ins   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Close| F5   |  F6  | F7   |  F8  |Float |URXVT | NUM4 | NUM5 |NUM6  |  →   |  MR  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Lock | F9   |  F10 |  F11 |  F12 |Tile  |Rofi  | NUM1 | NUM2 |NUM3  |  M→  |  M↻  |
 * |-----------------------------------------------------------------------------------|
 * | TAB  | Time | Game | ESC  |Space | Alt  | Ctrl | NUM0 |RETURN|      |FUNC  |DVOR  |
 * |      | Ctrl |      | GUI  |Shift | Del  | Bkspc|      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

[_NUMP] = {
  {KC_SLEP, KC_F1, KC_F2, KC_F3, KC_F4, LGUI(KC_M), KC_NLCK, KC_P7, KC_P8, KC_P9, KC_END, KC_INS},
  {LGUI(KC_W), KC_F5, KC_F6, KC_F7, KC_F8, LGUI(KC_S), LGUI(KC_ENTER), KC_P4, KC_P5, KC_P6, KC_RIGHT, XXXXXXX},
  {LGUI(F1), KC_F9, KC_F10, KC_F11, KC_F12, LGUI(KC_T), LGUI(KC_SPACE), KC_P1, KC_P2, KC_P3, LGUI(KC_L), LGUI(KC_C)},
  {LT(_NUMBER,KC_TAB), _______, XXXXXXX, GUI_T(KC_ESC), SFT_T(KC_SPC), ALT_T(KC_DEL), CTL_T(KC_BSPC), KC_P0, KC_PENT, _______, _______, TO(_DVORAK)}
}
};
