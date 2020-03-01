#include QMK_KEYBOARD_H

//Tap Dance Declarations
enum {
  TD_DOT_COMMAS = 0
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_DOT_COMMAS]  = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_COMMA)
// Other declarations would go here, separated by commas, if you have them
};

//In Layer declaration, add tap dance item in place of a key code



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*
   * ,-------------------.
   * |bcsp| /  | *  | -  |
   * |----|----|----|----|
   * | 7  | 8  | 9  |    |
   * |----|----|----| +  |
   * | 4  | 5  | 6  |    |
   * |----|----|----|----|
   * | 1  | 2  | 3  |    |
   * |----|----|----| En |
   * |   FN/0  | .  |    |
   * `-------------------'
   */

  [0] = LAYOUT_numpad_5x4(
    KC_BSPC, KC_PSLS, KC_PAST, KC_PMNS, 
    KC_P7,   KC_P8,   KC_P9,   
    KC_P4,   KC_P5,   KC_P6,   KC_PPLS, 
    KC_P1,   KC_P2,   KC_P3,   
    LT(1, KC_P0), TD(TD_DOT_COMMAS),  KC_PENT  
  ),
  /*
   * ,-------------------.
   * | F10| F11| F12| -  |
   * |----|----|----|----|
   * | F7 | F8 | F9 |    |
   * |----|----|----| vol|
   * | F4 | F5 | F6 |  + |
   * |----|----|----|----|
   * | F1 | F2 | F3 | vol|
   * |----|----|----|  - |
   * |    FN   | .  |    |
   * `-------------------'
   */
  [1] = LAYOUT_numpad_5x4(
    KC_F10, KC_F11, KC_F12, KC_NO, 
    KC_F7,   KC_F8,   KC_F9,   
    KC_F4,   KC_F5,   KC_F6, KC_VOLU, 
    KC_F1,   KC_F2,   KC_F3,   
    KC_NO, KC_PDOT,  KC_VOLD  
  )
};
