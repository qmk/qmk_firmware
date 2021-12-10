#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum custom_layers {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum custom_keycodes {
  LOWER = SAFE_RANGE,
  RAISE,
};

// Custom macros
#define CTL_ESC     CTL_T(KC_ESC)               // Tap for Esc, hold for Ctrl
#define CTL_TTAB    CTL_T(KC_TAB)               // Tap for Esc, hold for Ctrl
#define CTL_ENT     CTL_T(KC_ENT)               // Tap for Enter, hold for Ctrl
#define SFT_ENT     SFT_T(KC_ENT)               // Tap for Enter, hold for Shift
// Requires KC_TRNS/_______ for the trigger key in the destination layer
#define LT_MC(kc)   LT(_MOUSECURSOR, kc)        // L-ayer T-ap M-ouse C-ursor
#define LT_RAI(kc)  LT(_RAISE, kc)              // L-ayer T-ap to Raise


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Base
 * ,------.
 * | Esc  | 
 * |------+------+-------------.
 * |   :  |   7  |   8  |   9  | 
 * |------+------+------+------|
 * | RAISE|   4  |   5  |   6  | 
 * |------+------+------+------|
 * | LOWER|   1  |   2  |   3  |
 * `---------------------------'
 */
[_BASE] = LAYOUT(
  KC_ESC,
  KC_COLN, KC_P7,  KC_P8,  KC_P9,
  RAISE,   KC_P4,  KC_P5,  KC_P6,
  LOWER,   KC_P1,  KC_P2,  KC_P3
),

/* Lower
 * ,------.
 * | Nmlk | 
 * |------+------+-------------.
 * |  :   |   /  |   *  |   -  | 
 * |------+------+------+------|
 * |      |      |   =  |   +  | 
 * |------+------+------+------|
 * |      |  0   |   .  |  ENT |
 * `---------------------------'
 */
[_LOWER] = LAYOUT(
  KC_NLCK,
  KC_COLN,  KC_PSLS, KC_PAST, KC_PMNS,
  _______,  XXXXXXX, KC_EQL,  KC_PPLS,
  _______,  KC_P0,   KC_PDOT, KC_PENT
),

/* Raise
 * ,------.
 * | Esc  | 
 * |------+------+-------------.
 * |RGB TG|RGB M+|RGB M-|      |
 * |------+------+------+------|
 * |      |RGB H+|RGB S+|RGB V+| 
 * |------+------+------+------|
 * |  `   |RGB H-|RGB S-|RGB V-|
 * `---------------------------'
 */
[_RAISE] = LAYOUT(
  KC_NLCK,
  RGB_TOG, RGB_MOD, RGB_RMOD, XXXXXXX,
  _______, RGB_HUI, RGB_SAI,  RGB_VAI,
  _______, RGB_HUD, RGB_SAD,  RGB_VAD

),

/* Adjust
 * ,------.
 * | DFU  | 
 * |------+------+-------------.
 * |HPT TG|HPT FB|HPT RS| BKSP | 
 * |------+------+------+------|
 * |      |HPT M+|      |      | 
 * |------+------+------+------|
 * |      |HPT M-|Clk TG| Del  |
 * `---------------------------'
 */
[_ADJUST] = LAYOUT(
  RESET,
  HPT_TOG, HPT_FBK,  HPT_RST, KC_BSPC,
  _______, HPT_MODI, XXXXXXX, XXXXXXX,
  _______, HPT_MODD, CK_TOGG, KC_DEL
),


};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
          //not sure how to have keyboard check mode and set it to a variable, so my work around
          //uses another variable that would be set to true after the first time a reactive key is pressed.
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        //not sure how to have keyboard check mode and set it to a variable, so my work around
        //uses another variable that would be set to true after the first time a reactive key is pressed.
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      return false;
      break;
  }
  return true;
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}
