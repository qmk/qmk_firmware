// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.
//
//Dropped the Dvorak layer and added two my layer buttons.  Both Raise and lower can be accessed from either side now.

#include "planck.h"
#ifdef BACKLIGHT_ENABLE
  #include "backlight.h"
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QW 0
#define _NM 1
#define _FN 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |Ctrl/Tab| A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Alt  | GUI  | GUI  |  Num |    Space    |  FN  |  GUI |  Alt | Ctrl | Enter|
 * `-----------------------------------------------------------------------------------'
 */
[_QW] = {
  {KC_ESC,        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
  {CTL_T(KC_TAB), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {KC_LSFT,       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT},
  {KC_LCTL,       KC_LALT, KC_LGUI, KC_LGUI, MO(_NM), KC_SPC,  KC_SPC,  MO(_FN), KC_RGUI, KC_RALT, KC_RCTL, KC_ENT}
},
/* Number
 * ,-----------------------------------------------------------------------------------.
 * |  ___ |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | ____ |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Ctrl |   `  |  [   |  {   |  (   |  /   |  \   |   )  |   }  |   ]  |   -  |  =   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | ____ |   !  |  @   |  #   |  $   |  %   |  ^   |  &   |  *   |   _  |   +  | ____ |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | ____ | ___  | ___  | ___  | XXXX |    ______   | ____ | ____ | ____ |  __  | ____ |
 * `-----------------------------------------------------------------------------------'
 */
[_NM] = {
  {KC_TRNS, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_TRNS},
  {KC_LCTL, KC_GRV,  KC_LBRC, KC_LCBR, KC_LPRN, KC_SLSH, KC_BSLS, KC_RPRN, KC_RCBR, KC_RBRC, KC_MINS, KC_EQL},
  {KC_TRNS, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_UNDS, KC_PLUS, KC_TRNS},
  {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS}
},
/* Function
 * ,-----------------------------------------------------------------------------------.
 * | ____ |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | ____ |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | ____ |Shift | Ctrl |  Alt |  GUI | ____ | Left | Down |  Up  |Right | Del  | ____ |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | ____ | ____ | ____ | Vol- | Prev | Play | Mute | Next | Vol+ | ____ | ____ | ____ |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | ____ | ____ | ____ | ____ | ____ |    _____    | XXXX | ____ | ____ | ____ | ____ |
 * `-----------------------------------------------------------------------------------'
 */
[_FN] = {
  {KC_TRNS, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_TRNS},
  {KC_TRNS, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, KC_TRNS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_DEL,  KC_TRNS},
  {KC_TRNS, M(0),    KC_TRNS, KC_VOLD, KC_MPRV, KC_MPLY, KC_MUTE, KC_MNXT, KC_VOLU, KC_TRNS, KC_TRNS, KC_TRNS},
  {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS}
}
};

const uint16_t PROGMEM fn_actions[] = {

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      }
    return MACRO_NONE;
};
