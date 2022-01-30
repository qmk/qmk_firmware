
#include QMK_KEYBOARD_H


/* uint16_t copy_paste_timer; */

enum layers {
  DVORAK = 0,
  QWERTY,
  LAYERS,
  NUMSYM,
  AUDCON,
};

// Future Layers
/*
  NAVKEYPAD,
  FKEYS,
  FEMACROS,
  GITMACROS
*/

/* Future custom keycodes
enum custom_keycodes {
    KC_LBR = SAFE_RANGE,
    KC_RBR
};
*/


// Future Macros
// enum {
//   HIGHLIGHT_WORD_HOME,
//   HIGHLIGHT_WORD_LEFT,
//   HIGHLIGHT_WORD_RIGHT,
//   HIGHLIGHT_WORD_END
// };

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//   switch (keycode) {
//     case KC_LBR: {
//       if (record->event.pressed) {
//         switch(keycode) {
//           case HIGHLIGHT_WORD_HOME:
//             SEND_STRING("commands");
//             return false; break;
//         }
//       }
//     }
//   }
// };



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * Base Layer: DVORAK
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  ESC   |  ' " | , <  |   .  |   P  |   Y  |                              |   F  |   G  |   C  |   R  |   L  |L_Qwerty|
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  Tab   |   A  |   O  |   E  |   U  |   I  |                              |   D  |   H  |   T  |   N  |   S  |L_Layers|
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift | :  ; |   Q  |   J  |   K  |   X  |      |L_NumS|  |  Win |Audcon|   B  |   M  |   W  |   V  |   Z  | RShift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'	
 *                        | Left |Right | LCtrl| Space| Bksp |  |R_Alt | ENTER|  Del |  Up  | Down |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
  [DVORAK] = LAYOUT(
    KC_ESC,  KC_QUOT, KC_COMM,KC_DOT ,KC_P,    KC_Y,                                                KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    DF(QWERTY),
    KC_TAB,  KC_A,    KC_O,   KC_E,   KC_U,    KC_I,                                                KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    DF(LAYERS),
    KC_LSFT, KC_SCLN, KC_Q,   KC_J,   KC_K,    KC_X,  XXXXXXX,  MO(NUMSYM),  KC_LWIN,    MO(AUDCON),    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT,
                          KC_LEFT,   KC_RGHT, KC_LCTL,  KC_SPC,   KC_BSPC,  KC_RALT,    KC_ENT,     KC_DEL,  KC_UP,  KC_DOWN
  ),





/*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  ESC   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |L_Dvorak|
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  Tab   |   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |L_Layers|
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |L_NumS|  |  Win |Audcon|   N  |   M  | ,  < | . >  | /  ? | RShift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'	
 *                        | Left |Right | LCtrl| Space| Bksp |  | RAlt | ENTER|  Del |  Up  | Down |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [QWERTY] = LAYOUT(
      KC_ESC,  KC_Q,   KC_W,   KC_E,   KC_R,    KC_T,                                                KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    DF(DVORAK),
      KC_TAB,  KC_A,   KC_S,   KC_D,   KC_F,    KC_G,                                                KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, DF(LAYERS),
      KC_LSFT, KC_Z,   KC_X,   KC_C,   KC_V,    KC_B,  XXXXXXX, MO(NUMSYM),    KC_LWIN,  MO(AUDCON),     KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                            KC_LEFT,   KC_RGHT, KC_LCTL, KC_SPC,  KC_BSPC,    KC_RALT,  KC_ENT,     KC_DEL,  KC_UP,  KC_DOWN
    ),





/*
 * Sym Layer: Numbers and symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |    `   |  1   |  2   |  3   |  4   |  5   |                              |   6  |  7   |  8   |  9   |  0   |   =    |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |    ~   |  !   |  @   |  #   |  $   |  %   |                              |   ^  |  &   |  *   |  (   |  )   |   +    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |    |   |   \  |  :   |  ;   |  -   |  [   |  {   |      |  |      |   }  |   ]  |  _   |  ,   |  .   |  /   |   ?    |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |Dvorak|Dvorak|Dvorak|Dvorak|Dvorak|  |Dvorak|Dvorak|Dvorak|Dvorak|Dvorak|
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [NUMSYM] = LAYOUT(
      KC_GRV ,   KC_1 ,   KC_2 ,   KC_3 ,   KC_4 ,   KC_5 ,                                       KC_6 ,   KC_7 ,   KC_8 ,   KC_9 ,   KC_0 , KC_EQL ,
      KC_TILD , KC_EXLM,  KC_AT , KC_HASH,  KC_DLR, KC_PERC,                                     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PLUS,
      KC_PIPE , KC_BSLS, KC_COLN, KC_SCLN, KC_MINS, KC_LBRC, KC_LCBR, _______, _______, KC_RCBR, KC_RBRC, KC_UNDS, KC_COMM,  KC_DOT, KC_SLSH, KC_QUES,
                                 DF(DVORAK), DF(DVORAK), DF(DVORAK), DF(DVORAK), DF(DVORAK), DF(DVORAK), DF(DVORAK), DF(DVORAK), DF(DVORAK), DF(DVORAK)
    ),




  /*
   * Volume controls
   *
   * ,-------------------------------------------.                              ,-------------------------------------------.
   * |        |      |      |      |      |      |                              |      |      |VOL UP|      |      |        |
   * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
   * |        |      | MUTE |      |      |      |                              |      |      |VOL DOWN|      |      |        |
   * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
   * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
   * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
   *                        |      |      |      |      |      |  |      |      |      |      |      |
   *                        |      |      |      |      |      |  |      |      |      |      |      |
   *                        `----------------------------------'  `----------------------------------'
 */
    [AUDCON] = LAYOUT(
      KC_MUTE, KC_MUTE, KC_MUTE, KC_MUTE, KC_MUTE, KC_MUTE,                                     KC_VOLU, KC_VOLU, KC_VOLU, KC_VOLU, KC_VOLU, DF(DVORAK),
      KC_MUTE, KC_MUTE, KC_MUTE, KC_MUTE, KC_MUTE, KC_MUTE,                                     KC_VOLD, KC_VOLD, KC_VOLD, KC_VOLD, KC_VOLD, DF(LAYERS),
      KC_MUTE, KC_MUTE, KC_MUTE, KC_MUTE, KC_MUTE, KC_MUTE, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),





/*
 * Base Layer: f_keys
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |                              |  F6  |  F7  |  F8  |  F9  |  F10 |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      | RShift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'	
 *                        |      |      | DEL  | Space| TAB  |  | Bksp | ENTER|      |      |      |
 *                        |      | LCTR |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'

  [FKEYS] = LAYOUT(
    KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,    KC_T,                                                KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_RCTL,
    KC_LCTL, KC_A,   KC_S,   KC_D,   KC_F,    KC_G,                                                KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,   KC_X,   KC_C,   KC_V,    KC_B,    KC_DEL,  MO(RAISE), MO(ADJUST), KC_ESC,     KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_LSFT,
                          XXXXXXX,   KC_LALT, XXXXXXX, KC_BSPC, MO(LOWER), KC_ENT,     KC_SPC,     KC_LBR,  KC_RBR,  XXXXXXX
  ),
 */




/*
 * Base Layer: fe_macros
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  ESC   |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      | RShift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'	
 *                        |      |      | DEL  | Space| TAB  |  | Bksp | ENTER|      |      |      |
 *                        |      | LCTR |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 
  [FEMACROS] = LAYOUT(
    KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,    KC_T,                                                KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_RCTL,
    KC_LCTL, KC_A,   KC_S,   KC_D,   KC_F,    KC_G,                                                KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,   KC_X,   KC_C,   KC_V,    KC_B,    KC_DEL,  MO(RAISE), MO(ADJUST), KC_ESC,     KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_LSFT,
                          XXXXXXX,   KC_LALT, XXXXXXX, KC_BSPC, MO(LOWER), KC_ENT,     KC_SPC,     KC_LBR,  KC_RBR,  XXXXXXX
  ),

*/




/*
 * Base Layer: git_macros
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  ESC   |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      | RShift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'	
 *                        |      |      | DEL  | Space| TAB  |  | Bksp | ENTER|      |      |      |
 *                        |      | LCTR |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'

  [GITMACROS] = LAYOUT(
    KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,    KC_T,                                                KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_RCTL,
    KC_LCTL, KC_A,   KC_S,   KC_D,   KC_F,    KC_G,                                                KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,   KC_X,   KC_C,   KC_V,    KC_B,    KC_DEL,  MO(RAISE), MO(ADJUST), KC_ESC,     KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_LSFT,
                          XXXXXXX,   KC_LALT, XXXXXXX, KC_BSPC, MO(LOWER), KC_ENT,     KC_SPC,     KC_LBR,  KC_RBR,  XXXXXXX
  ),
 */



/*
 * Adjust Layer: Layer index
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |      |      |      |      |L_Dvorak|
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |Dvorak|QWERTY|NUMSYM|      |      |                              |      |      |      |      |      |L_Layers|
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [LAYERS] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                    _______, _______, _______, _______,  _______, DF(DVORAK),
      _______, DF(DVORAK), DF(QWERTY), DF(NUMSYM), DF(AUDCON), _______,                           _______, _______, _______, _______,  _______, DF(LAYERS),
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),



// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),

};

// END LAYERS





///////////////////////////
// OLED Display settings
#ifdef OLED_ENABLE


oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}


static void render_keymap(void) {

  // Host Keyboard Layer Status
  oled_write_P(PSTR("Layer: "), false);
  switch (get_highest_layer(default_layer_state)) {
      case DVORAK:
          oled_write_P(PSTR("Dvorak\n\n"), false);
          oled_write_P(PSTR("' , . p y   f g c r l \n"), false);
          oled_write_P(PSTR("a o e i u   d h t n s \n"), false);
          oled_write_P(PSTR("; q j k x   b m w v z \n"), false);
          break;
      case QWERTY:
          oled_write_P(PSTR("Qwerty\n\n"), false);
          oled_write_P(PSTR("q w e r t   y u i o p \n"), false);
          oled_write_P(PSTR("a s d f g   h j k l ; \n"), false);
          oled_write_P(PSTR("z x c v b   n m , . / \n"), false);
          break;
      case LAYERS:
          oled_write_P(PSTR("Index Layer\n\n"), false);
          oled_write_P(PSTR("- - - - - | - - - - - \n"), false);
          oled_write_P(PSTR("- D Q N S | - - - - - \n"), false);
          oled_write_P(PSTR("- - - - - | - - - - - \n"), false);
          break;
      case NUMSYM:
          oled_write_P(PSTR("Numbers & Symbols\n\n"), false);
          oled_write_P(PSTR("` 1 2 3 4 5 6 7 8 9 0 =\n"), false);
          oled_write_P(PSTR("~ ! @ # $ P ^ & * ( ) +\n"), false);
          oled_write_P(PSTR("| \\ : ; - [{}] _ , . / ?\n"), false);
          break;
      case AUDCON:
          oled_write_P(PSTR("Audio Controls\n\n"), false);
          oled_write_P(PSTR("MUTE | Volume Up\n"), false);
          oled_write_P(PSTR("MUTE | Volume Down \n"), false);
          oled_write_P(PSTR("MUTE |   \n"), false);
          break;
      default:
          oled_write_P(PSTR("ERR No Layer!\n"), false);
  }
}


// Host Keyboard LED Status
static void render_indicator_status(void) {
  led_t led_state = host_keyboard_led_state();
  oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("       "), false);
  oled_write_P(led_state.caps_lock ? PSTR("CAPS ") : PSTR("       "), false);
  oled_write_P(led_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);
}


bool oled_task_user(void) {
  if (is_keyboard_master()) {
    render_keymap();
  } else {
    render_indicator_status();
    oled_write_P(PSTR("       Kyria rev1.4\n\n"), false);
  }
  return false;
}
#endif