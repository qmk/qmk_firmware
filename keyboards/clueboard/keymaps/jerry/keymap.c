#include "clueboard.h"

// Helpful defines
#define GRAVE_MODS (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT) | MOD_BIT(KC_LCTRL))
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _WL 0
#define _ML 1
#define _FL 2
#define _RL 3

#define CAPS_FN LT(_RL, KC_CAPS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _WL: Windows Layer (Default)
   */
[_WL] = KEYMAP(
  F(0),    KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSLS, KC_GRV,           KC_INS,  \
  KC_TAB,  KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,    KC_P,     KC_LBRC,  KC_RBRC,  KC_BSPC,                   KC_DEL,  \
  KC_LCTL, KC_A,    KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,    KC_SCLN,  KC_QUOT,  XXXXXXX,  KC_ENT,                             \
  KC_LSFT, XXXXXXX, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,   KC_SLSH,  XXXXXXX,  KC_RSFT,          KC_UP,            \
  CAPS_FN, KC_LGUI, KC_LALT,XXXXXXX,                XXXXXXX,KC_SPC,                  XXXXXXX,  KC_RALT,  KC_RCTL,  MO(_FL), KC_LEFT, KC_DOWN, KC_RGHT),

  /* Keymap _ML: Mac Layer
   */
[_ML] = KEYMAP(
  _______, _______, _______,_______,_______,_______,_______,_______,_______,_______, _______,  _______,  _______,  _______, _______,          _______, \
  _______, _______, _______,_______,_______,_______,_______,_______,_______,_______, _______,  _______,  _______,  _______,                   _______, \
  _______, _______, _______,_______,_______,_______,_______,_______,_______,_______, _______,  _______,  XXXXXXX,  _______,                            \
  _______, XXXXXXX, _______,_______,_______,_______,_______,_______,_______,_______, _______,  _______,  XXXXXXX,  _______,          _______,          \
  _______, KC_LALT, KC_LGUI,XXXXXXX,                XXXXXXX,_______,                 XXXXXXX,  KC_RGUI,  KC_RALT,  _______, _______, _______, _______),

  /* Keymap _FL: Function Layer
   */
[_FL] = KEYMAP(
  KC_GRV,  KC_F1,   KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,   KC_F10,   KC_F11,   F(1),     KC_F13 , KC_F14,           KC_F15,  \
  _______, _______, _______,_______,_______,_______,_______,_______,KC_PSCR,KC_SLCK, KC_PAUS,  KC_VOLD,  KC_VOLU,  KC_MUTE,                   F(4),    \
  _______, _______, _______,_______,_______,_______,_______,_______,_______,_______, _______,  _______,  XXXXXXX,  KC_MPLY,                            \
  _______, XXXXXXX, _______,_______,_______,_______,_______,_______,_______,_______, _______,  _______,  XXXXXXX,  _______,          KC_PGUP,          \
  _______, _______, _______,XXXXXXX,                XXXXXXX,_______,                 XXXXXXX,  _______,  KC_APP,   _______, KC_HOME, KC_PGDN, KC_END),

  /* Keymap _RL: RGB layer
   */
[_RL] = KEYMAP(
  _______, _______, _______,_______,_______,_______,_______,_______,_______,_______, _______,  _______,  _______,  _______, RGB_TOG,          RGB_VAI, \
  _______, _______, _______,_______,_______,_______,_______,_______,_______,_______, _______,  _______,  _______,  _______,                   RGB_VAD, \
  _______, _______, _______,_______,_______,_______,_______,_______,_______,_______, _______,  _______,  XXXXXXX,  _______,                            \
  _______, XXXXXXX, _______,_______,_______,_______,_______,_______,_______,_______, _______,  _______,  XXXXXXX,  _______,          RGB_SAI,          \
  _______, F(2),    F(3),   XXXXXXX,                XXXXXXX,RGB_MOD,                 XXXXXXX,  _______,  _______,  _______, RGB_HUD, RGB_SAD, RGB_HUI),
};

/* This is a list of user defined functions. F(N) corresponds to item N
   of this list.
 */
const uint16_t PROGMEM fn_actions[] = {
  [0] = ACTION_FUNCTION(0),
  [1] = ACTION_FUNCTION(1),
  [2] = ACTION_FUNCTION(2), // Swap to Windows mode
  [3] = ACTION_FUNCTION(3), // Swap to Mac mode
  [4] = ACTION_MODS_KEY(MOD_LCTL | MOD_LSFT, KC_ESC), // Task Manager
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  static uint8_t mods_pressed;
  static bool mod_flag;
  switch (id) {
    case 0:
      /* Handle the combined Grave/Esc key
       */
      mods_pressed = get_mods() & GRAVE_MODS; // Check to see what mods are pressed

      if (record->event.pressed) {
        /* The key is being pressed.
         */
        if (mods_pressed) {
          mod_flag = true;
          add_key(KC_GRV);
          send_keyboard_report();
        } else {
          add_key(KC_ESC);
          send_keyboard_report();
        }
      } else {
        /* The key is being released.
         */
        if (mod_flag) {
          mod_flag = false;
          del_key(KC_GRV);
          send_keyboard_report();
        } else {
          del_key(KC_ESC);
          send_keyboard_report();
        }
      }
      break;
    case 1:
      /* Set to Mac layer if F12 was used within 15 seconds of powering on
       */
      if (timer_read32() < 15000) {
        default_layer_set(1 << _ML);
      }
      if (record->event.pressed) {
        add_key(KC_F12);
        send_keyboard_report();
      } else {
        del_key(KC_F12);
        send_keyboard_report();
      }
      break;
    case 2:
      default_layer_set(1 << _WL);
      break;
    case 3:
      default_layer_set(1 << _ML);
      break;
  }
}
