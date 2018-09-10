#include QMK_KEYBOARD_H

//@mechanical keyboard DZ60 keymap
//@author:  Cristian Mitul aka rundeploy
//@updated: 08/09/2018
//Layout for - 2u Left Shift and 1u right shift and split space 2.25 1.25 2.75 and Mac OS shortcuts

#define MODS_CTRL_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

enum custom_keycodes {
    EM1 = SAFE_RANGE,
    EM2, PS1, PS2, NNM,
};

#define _QWERTY   0 //Base layer
#define _FUNCTION 1 //Function layer
#define _MACRO    2 //Macro layer

#define DEL_OSX LGUI(KC_BSPC) //Command + Backspace = Delete on OSX

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Keymap 0: (Base Layer) Default Layer
   * ,----------------------------------------------------------------.
   * |Esc | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =| ~ ` |Backsp|
   * |----------------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \     |
   * |----------------------------------------------------------------|
   * |CTRL   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|    Return  |
   * |----------------------------------------------------------------|
   * | { Shift|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|}Sh|  Up | Del |
   * |----------------------------------------------------------------|
   * |CAPS| Cmd | Alt|  Enter | Fn2|  Space   |FN |CTL|Lft| Dwn | Rght|
   * `----------------------------------------------------------------'
   * Left Shift when held, { when tapped
   * Right Shift when held, } when tapped
   */
  [_QWERTY] = LAYOUT_all(
    F(0), KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_GRV, KC_BSPC,
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
    KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_NO,
    LSFT_T(KC_LCBR), KC_NO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, RSFT_T(KC_RCBR), KC_UP, DEL_OSX,
    KC_CAPS, KC_LGUI, KC_LALT, KC_ENT, MO(2), KC_SPC, MO(1), KC_RCTRL, KC_LEFT, KC_DOWN, KC_RIGHT),


  /* MO(1): Function Layer
   * ,----------------------------------------------------------------.
   * |~ ` |F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12| MBack| MFwd|
   * |----------------------------------------------------------------|
   * |     |   |   |   |   |   |   |   |   |   |   |V- |V+ | MPlayPse |
   * |----------------------------------------------------------------|
   * |       |   |   |   |   |   |   |   |   |NNM|EM1|EM2|            |
   * |----------------------------------------------------------------|
   * |        |   |   |   |   |   |   |   |   |PS1|PS2|   | PgUp|     |
   * |----------------------------------------------------------------|
   * |    |     |    |        |    |          |   |   |HME| PgDw| END |
   * `----------------------------------------------------------------'
   */
  [_FUNCTION] = LAYOUT_all(
    KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_MRWD, KC_MFFD,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP, KC_MPLY,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, NNM, EM1, EM2, KC_TRNS, KC_NO,
    KC_TRNS, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, PS1, PS2, KC_TRNS, KC_PGUP, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDOWN, KC_END),


  /* MO(2): Macro Layer
   * ,----------------------------------------------------------------.
   * |SysO|  |   |   |   |   |   |   |   |   |   |   |   |     |FrwDel|
   * |----------------------------------------------------------------|
   * |     |TOG|MOD|HUI|HUD|SAI|SAD|VAI|VAD|   |   |   |   |   DFU    |
   * |----------------------------------------------------------------|
   * |       |PLN|BRT|RNB|SWR|SNK|KNG|XMS|GRD|   |   |   |            |
   * |----------------------------------------------------------------|
   * |        |   |   |BL-| BL|BL+|BLS|   |   |   |   |   |     |     |
   * |----------------------------------------------------------------|
   * |    |     |    |        |    |          |   |   |   |     |     |
   * `----------------------------------------------------------------'
   */
  [_MACRO] = LAYOUT_all(
    KC_POWER, M(1), M(2), M(3), M(4), M(5), M(6), M(7), M(8), M(9), M(10), M(11), M(12), KC_TRNS, KC_DEL,
    KC_TRNS, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET,
    KC_TRNS, RGB_MODE_PLAIN, RGB_MODE_BREATHE, RGB_MODE_RAINBOW, RGB_MODE_SWIRL, RGB_MODE_SNAKE, RGB_MODE_KNIGHT, RGB_MODE_XMAS, RGB_MODE_GRADIENT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,
    KC_TRNS, KC_NO, KC_TRNS, KC_TRNS, BL_DEC, BL_TOGG, BL_INC, BL_STEP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
};

/*----------------------------------MACRO------------------------------------*/

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case EM1:
      if (record->event.pressed) {
        SEND_STRING("mail1@gmail.com"); //change to your email
      }
    return false;
    break;

    case EM2:
      if (record->event.pressed) {
        SEND_STRING("mail2@gmail.com"); //change to your email
      }
    return false;
    break;

    case PS1:
      if (record->event.pressed) {
        SEND_STRING("pass1"); //change to your pass
      }
    return false;
    break;

    case PS2:
      if (record->event.pressed) {
        SEND_STRING("pass2"); //change to your pass
      }
    return false;
    break;

    case NNM:
      if (record->event.pressed) {
        SEND_STRING("pass2"); //change to your nickname
      }
    return false;
    break;
  }
  return true;
};

/*----------------------------------------------------------------------------------*/
enum function_id{
    SHIFT_ESC,
};

const uint16_t PROGMEM fn_actions[] = {
  [0]  = ACTION_FUNCTION(SHIFT_ESC),
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  static uint8_t shift_esc_shift_mask;
  switch (id) {
    case SHIFT_ESC:
      shift_esc_shift_mask = get_mods()&MODS_CTRL_MASK;
      if (record->event.pressed) {
        if (shift_esc_shift_mask) {
          add_key(KC_GRV);
          send_keyboard_report();
        } else {
          add_key(KC_ESC);
          send_keyboard_report();
        }
      } else {
        if (shift_esc_shift_mask) {
          del_key(KC_GRV);
          send_keyboard_report();
        } else {
          del_key(KC_ESC);
          send_keyboard_report();
        }
      }
      break;
  }
}


/* Empty layer
   * ,----------------------------------------------------------------.
   * |    |  |   |   |   |   |   |   |   |   |   |   |   |      |     |
   * |----------------------------------------------------------------|
   * |     |   |   |   |   |   |   |   |   |   |   |   |   |          |
   * |----------------------------------------------------------------|
   * |       |   |   |   |   |   |   |   |   |   |   |   |            |
   * |----------------------------------------------------------------|
   * |        |   |   |   |   |   |   |   |   |   |   |   |     |     |
   * |----------------------------------------------------------------|
   * |    |     |    |        |    |          |   |   |   |     |     |
   * `----------------------------------------------------------------'
   */
