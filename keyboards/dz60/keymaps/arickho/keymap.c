#include "dz60.h"
#include "action_layer.h"

extern keymap_config_t keymap_config;

// Fillers to make layering more clear
#define _______ KC_TRNS
#define _DEAD_ KC_TRNS
#define XXXXXXX KC_NO

#define _DL 0     // DEFAULT
#define _UTIL 1   // Utility layer
#define _MOUSE 2  // Mouse layer
#define _LIGHTS 3 // Lights layer
#define _TEST 21  // Test layer

enum custom_keycodes
{
  DEFAULT_LAYER = SAFE_RANGE,
  ONE_PASSWORD, // Trigger 1Password Helper
  SCREENSHOT,   // Take a Screenshot
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Default
    * ,-----------------------------------------------------------------------------------------.
    * | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |  n/a  | Bck |
    * |-----------------------------------------------------------------------------------------+
    * | Tab   |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |    \    |
    * |-----------------------------------------------------------------------------------------+
    * | Caps    |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter    |
    * |-----------------------------------------------------------------------------------------+
    * | Left Shft|  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .| Rht Shft| Up | Rht Shft  |
    * |-----------------------------------------------------------------------------------------+
    * | Ctrl  |  Alt |  GUI |   Space   |  FN2 |  Space   | FN2 | FN3 | Left |  Down  |  Right  |
    * `-----------------------------------------------------------------------------------------'
    */

    [_DL] = KEYMAP_2_SHIFTS(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, _DEAD_, KC_BSPC,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
        MO(_UTIL), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSHIFT, _DEAD_, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSHIFT, MT(MOD_RSFT, KC_UP), KC_RSHIFT,
        KC_LCTL, KC_LALT, KC_LGUI, KC_SPC, MO(_LIGHTS), KC_SPC, MO(_MOUSE), MO(_LIGHTS), KC_LEFT, KC_DOWN, KC_RGHT),

    /* Utility Layer
    * ,-----------------------------------------------------------------------------------------.
    * | ` | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  |  F10  |     |     |  | DELETE |
    * |-----------------------------------------------------------------------------------------+
    * | CAPSLOCK  | REWIND | PLAY/PAUSE |  FORWARD  | |    |    |    |  UP  |  |    |  |   |    |
    * |-----------------------------------------------------------------------------------------+
    * |    |    |  VOL DWN  |  VOL UP  |  MUTE  |    |     | LFT | DWN | RHT |    |    |        |
    * |-----------------------------------------------------------------------------------------+
    * |    | SCREENSHOT |  1Pass  |     |     |     |     |     |     |      |        |    |    |
    * |-----------------------------------------------------------------------------------------+
    * |     |       |       |          |         |          |       |   |      |       |        |
    * `-----------------------------------------------------------------------------------------'
    */

    [_UTIL] = KEYMAP_2_SHIFTS(
        KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, _DEAD_, KC_DEL,
        KC_LCAP, KC_MRWD, KC_MPLY, KC_MFFD, _______, _______, _______, _______, KC_UP, _______, _______, _______, KC_PWR, RESET,
        _______, _______, KC_VOLD, KC_VOLU, KC_MUTE, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______,
        _______, _DEAD_, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, SCREENSHOT, ONE_PASSWORD, _______, _______, _______),

    /* Mouse Layer
    * ,-----------------------------------------------------------------------------------------.
    * | ACCEL 1 | ACCEL 2  | ACCEL 3  |   |   |  |   |   |   |   |    |     |     |  |          |
    * |-----------------------------------------------------------------------------------------+
    * |   | LEFT CLICK | MOUSE UP | RIGHT CLICK  |  |    |    |    |   |    |    |    |    |    |
    * |-----------------------------------------------------------------------------------------+
    * |    |  MOUSE LFT  |  MOUSE DWN  |  MOUSE RGHT  |    |    |     |  |  |  |    |    |      |
    * |-----------------------------------------------------------------------------------------+
    * |     |  |                  |     |     |     |     |     |     |      |        |    |    |
    * |-----------------------------------------------------------------------------------------+
    * |     |       |       |          |         |          |       |   |      |       |        |
    * `-----------------------------------------------------------------------------------------'
    */

    [_MOUSE] = KEYMAP_2_SHIFTS(
        KC_ACL0, KC_ACL1, KC_ACL2, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _DEAD_, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),

    /* Light Layer
    * ,-----------------------------------------------------------------------------------------.
    * |   |  |                        |   |   |  |   |   |   |   |    |     |     |  |          |
    * |-----------------------------------------------------------------------------------------+
    * |   | LIGHT TOGGL | NEXT ANIM | REV ANIM  |  |    |    |    |   |    |    |    |    |    |
    * |-----------------------------------------------------------------------------------------+
    * |    |  INCRES HUE  |  DEC HUE  | INC SAT  | DEC SAT   |    |     |  |  |  |    |    |      |
    * |-----------------------------------------------------------------------------------------+
    * |     | INCRE BRIGHT |   DEC BRIGHT   |  |     |     |     |     |     |      |  |    |    |
    * |-----------------------------------------------------------------------------------------+
    * |     |       |       |          |         |          |       |   |      |       |        |
    * `-----------------------------------------------------------------------------------------'
    */

    [_LIGHTS] = KEYMAP_2_SHIFTS(
        RGB_MODE_PLAIN, RGB_MODE_BREATHE, RGB_MODE_RAINBOW, RGB_MODE_SWIRL, RGB_MODE_SNAKE, RGB_MODE_KNIGHT, RGB_MODE_XMAS, RGB_MODE_GRADIENT, _______, _______, _______, _______, _______, _______, _______,
        _______, RGB_TOG, RGB_MODE_FORWARD, RGB_MODE_REVERSE, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, _______, _______, _______, _______,
        _______, _DEAD_, _______, _______, _______, BL_TOGG, BL_INC, BL_DEC, BL_BRTG, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  switch (keycode)
  {
  case ONE_PASSWORD:
    if (record->event.pressed)
    {
      SEND_STRING(SS_LGUI("\\"));
    }
    return false;
    break;
  case SCREENSHOT:
    if (record->event.pressed)
    {
      SEND_STRING(SS_LGUI(SS_LSFT("4")));
    }
    return false;
    break;
  case DEFAULT_LAYER:
    if (record->event.pressed)
    {
      print("mode just switched to default layer\n");
      set_single_persistent_default_layer(_DL);
    }
    return false;
    break;
  }
  return true;
};
