#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
*
* |ESC | F1 | F2 | F3 | F4 | F5 | F6 | f7 | F8 | F9 | F10| F11| F12|Vol-|Vol+|Mute|
*  -------------------------------------------------------------------------------'
* |  ~ |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |  0 |  - |  = |Bakspace| Del |
* --------------------------------------------------------------------------
* | tab  |  q |  w |  e |  r |  t |  y |  u |  i |  o |  p |  [ |  ] |  \   |     |
*  -------------------------------------------------------------------------------'
* | caps  |  a |  s |  d |  f |  g |  h |  j |  k |  l |  ; |  ' | enter     |PgUp|
* --------------------------------------------------------------------------------
* |Lsft    |  z |  x |  c |  v |  b |  n |  m |  , |  . |  / |      Rsft| Up| PgDn|
* ---------------------------------------------------------------------------------
* |Lctl   |Lgui  |Lalt |       Space          |Ralt  |  FN |  Rctl |Left|Down|Rght|
* ---------------------------------------------------------------------------------
*/

  [0] = MATRIX_TESTING_LAYOUT( \
  KC_A,  KC_B,   KC_C,   KC_D,   KC_E,   KC_F,   KC_G,   KC_H,   KC_I,   KC_J,   KC_K,   KC_L,   KC_M,   KC_N,   KC_O,   KC_P,      KC_Q,   KC_R,\
  KC_A,  KC_B,   KC_C,   KC_D,   KC_E,   KC_F,   KC_G,   KC_H,   KC_I,   KC_J,   KC_K,   KC_L,   KC_M,   KC_N,   KC_O,   KC_P,      KC_Q,   KC_R,\
  KC_A,  KC_B,   KC_C,   KC_D,   KC_E,   KC_F,   KC_G,   KC_H,   KC_I,   KC_J,   KC_K,   KC_L,   KC_M,   KC_N,   KC_O,   KC_P,      KC_Q,   KC_R,\
  KC_A,  KC_B,   KC_C,   KC_D,   KC_E,   KC_F,   KC_G,   KC_H,   KC_I,   KC_J,   KC_K,   KC_L,   KC_M,   KC_N,   KC_O,   KC_P,      KC_Q,   KC_R,\
  KC_A,  KC_B,   KC_C,   KC_D,   KC_E,   KC_F,   KC_G,   KC_H,   KC_I,   KC_J,   KC_K,   KC_L,   KC_M,   KC_N,   KC_O,   KC_P,      KC_Q,   KC_R,\
  KC_A,  KC_B,   KC_C,   KC_D,   KC_E,   KC_F,   KC_G,   KC_H,   KC_I,   KC_J,   KC_K,   KC_L,   KC_M,   KC_N,   KC_O,   KC_P,      KC_Q,   KC_R,\
  KC_A,  KC_B,   KC_C,   KC_D,   KC_E,   KC_F,   KC_G,   KC_H,   KC_I,   KC_J,   KC_K,   KC_L,   KC_M,   KC_N,   KC_O,   KC_P,      KC_Q,   KC_R,\
  KC_A,  KC_B,   KC_C,   KC_D,   KC_E,   KC_F,   KC_G,   KC_H,   KC_I,   KC_J,   KC_K,   KC_L,   KC_M,   KC_N,   KC_O,   KC_P,      KC_Q,   KC_R\
  )\
};

void keyboard_post_init_user(void) {
// Customise these values to desired behaviour
    debug_enable=true;
    debug_matrix=true;
    debug_keyboard=true;
    //debug_mouse=true;
}
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif 
    return true;
}
