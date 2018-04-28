#include "dz60.h"

#define MODS_CTRL_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

#define ______ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------------.
 * | ESC |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |   Bkspc   |
 * |-----------------------------------------------------------------------------------------+
 * | Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |    \   |
 * |-----------------------------------------------------------------------------------------+
 * | FN      |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter    |
 * |-----------------------------------------------------------------------------------------+
 * | Shift     |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |       RSh |  U  | Del |
 * |-----------------------------------------------------------------------------------------+
 * | Ctrl |  Cmd  |  Alt  |              Space                |  /  |  FN  |  L  |  D  |  R  |
 * `-----------------------------------------------------------------------------------------'
 */

  KEYMAP_DIRECTIONAL(
      KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, ______, KC_BSPC,
      KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
      MO(1), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
      KC_LSFT, ______, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_RSFT, KC_UP, KC_DELETE,
      KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_SPC, KC_SPC, KC_SLSH, MO(1), KC_LEFT, KC_DOWN, KC_RIGHT
      ),

/* FN Layer
 * ,-----------------------------------------------------------------------------------------.
 * |  ~  | F1  | F2  | F3  | F4  | F5  | F6  | f7  | F8  | F9  | F10 | F11 | F12 |   CALC    |
 * |-----------------------------------------------------------------------------------------+
 * |Num_Lock| NP1 |     |     |     |     |     |     |     |     | NP0 |VolD |VolU |Mute    |
 * |-----------------------------------------------------------------------------------------+
 * |         | AA  | AE  | AI  | AO  | AU  | AN  |     |     |     |     |     |    Menu     |
 * |-----------------------------------------------------------------------------------------+
 * |Shift      | Cyc+| Cyc-| Val+| Val-| Hue+| Hue-| Sat+| Sat-| TOG |     RSh   | Pup | Ins |
 * |-----------------------------------------------------------------------------------------+
 * | Ctrl |  Cmd   |  Alt |                                   | Alt |      | Home| Pdn | End |
 * `-----------------------------------------------------------------------------------------'
 */

  KEYMAP_DIRECTIONAL(
      KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, ______, KC_CALC,
      RESET, F(1), F(2), F(3), F(4), F(5), F(6), F(7), F(8), F(9), F(0),  KC_VOLD, KC_VOLU, KC_MUTE,
      ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, KC_APP,
      KC_LSFT, ______, RGB_MOD, RGB_RMOD, RGB_VAI, RGB_VAD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_TOG, KC_RSFT, KC_PGUP, KC_INSERT,
      KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_SPC, KC_SPC, KC_RALT, ______, KC_HOME, KC_PGDOWN, KC_END
      ),
};

enum function_id
{
    NUM_0,
    NUM_1,
    NUM_2,
    NUM_3,
    NUM_4,
    NUM_5,
    NUM_6,
    NUM_7,
    NUM_8,
    NUM_9,
    //SHIFT_ESC
};

const uint16_t PROGMEM fn_actions[] = {
  //[10] = ACTION_FUNCTION(SHIFT_ESC),
  [0] = ACTION_FUNCTION(NUM_0),
  [1] = ACTION_FUNCTION(NUM_1),
  [2] = ACTION_FUNCTION(NUM_2),
  [3] = ACTION_FUNCTION(NUM_3),
  [4] = ACTION_FUNCTION(NUM_4),
  [5] = ACTION_FUNCTION(NUM_5),
  [6] = ACTION_FUNCTION(NUM_6),
  [7] = ACTION_FUNCTION(NUM_7),
  [8] = ACTION_FUNCTION(NUM_8),
  [9] = ACTION_FUNCTION(NUM_9)
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  //static uint8_t shift_esc_shift_mask;
  bool numpadKeyPressed = false;

  static short numpad[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  switch(id)
  {
    case NUM_0:
      if(record->event.pressed)
      {
        numpad[0] = 1;
        numpadKeyPressed = true;
      }
      else
      {
        numpad[0] = -1;
      }
      break;
    case NUM_1:
      if (record->event.pressed)
      {
        numpad[1] = 1;
        numpadKeyPressed = true;
      }
      else
      {
        numpad[1] = -1;
      }
      break;
    case NUM_2:
      if (record->event.pressed)
      {
        numpad[2] = 1;
        numpadKeyPressed = true;
      }
      else
      {
        numpad[2] = -1;
      }
      break;
    case NUM_3:
      if (record->event.pressed)
      {
        numpad[3] = 1;
        numpadKeyPressed = true;
      }
      else
      {
        numpad[3] = -1;
      }
      break;
    case NUM_4:
      if (record->event.pressed)
      {
        numpad[4] = 1;
        numpadKeyPressed = true;
      }
      else
      {
        numpad[4] = -1;
      }
      break;
    case NUM_5:
      if (record->event.pressed)
      {
        numpad[5] = 1;
        numpadKeyPressed = true;
      }
      else
      {
        numpad[5] = -1;
      }
      break;
    case NUM_6:
      if (record->event.pressed)
      {
        numpad[6] = 1;
        numpadKeyPressed = true;
      }
      else
      {
        numpad[6] = -1;
      }
      break;
    case NUM_7:
      if (record->event.pressed)
      {
        numpad[7] = 1;
        numpadKeyPressed = true;
      }
      else
      {
        numpad[7] = -1;
      }
      break;
    case NUM_8:
      if (record->event.pressed)
      {
        numpad[8] = 1;
        numpadKeyPressed = true;
      }
      else
      {
        numpad[8] = -1;
      }
      break;
    case NUM_9:
      if (record->event.pressed)
      {
        numpad[9] = 1;
        numpadKeyPressed = true;
      }
      else
      {
        numpad[9] = -1;
      }
      break;
  }

  if(numpadKeyPressed)
  {
    if(host_keyboard_leds() & (1 << USB_LED_NUM_LOCK))
    {
      
    }
    else
    {
      add_key(KC_NLCK);

      send_keyboard_report();
    }
  }
  if (numpad[0] == 1) { add_key(KC_P0); }
  else if (numpad[0] == -1) { del_key(KC_P0); }
  if (numpad[1] == 1) { add_key(KC_P1); }
  else if (numpad[1] == -1) { del_key(KC_P1); }
  if (numpad[2] == 1) { add_key(KC_P2); }
  else if (numpad[2] == -1) { del_key(KC_P2); }
  if (numpad[3] == 1) { add_key(KC_P3); }
  else if (numpad[3] == -1) { del_key(KC_P3); }
  if (numpad[4] == 1) { add_key(KC_P4); }
  else if (numpad[4] == -1) { del_key(KC_P4); }
  if (numpad[5] == 1) { add_key(KC_P5); }
  else if (numpad[5] == -1) { del_key(KC_P5); }
  if (numpad[6] == 1) { add_key(KC_P6); }
  else if (numpad[6] == -1) { del_key(KC_P6); }
  if (numpad[7] == 1) { add_key(KC_P7); }
  else if (numpad[7] == -1) { del_key(KC_P7); }
  if (numpad[8] == 1) { add_key(KC_P8); }
  else if (numpad[8] == -1) { del_key(KC_P8); }
  if (numpad[9] == 1) { add_key(KC_P9); }
  else if (numpad[9] == -1) { del_key(KC_P9); }
  send_keyboard_report();
}

/*case SHIFT_ESC:
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
break;*/
