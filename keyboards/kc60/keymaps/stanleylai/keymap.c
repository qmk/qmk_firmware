
#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BL   0
#define _FL   1
#define _RGBL 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// See base_layer.png and rgb_layer.png for layout reference

// Base Default Layer
// Mac Modifier Layout. Use BootMagic to toggle GUI and ALT positions.
[_BL] = LAYOUT(
  F(0),             KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,  KC_EQL,   KC_BSPC, \
  KC_TAB,           KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,  KC_RBRC,  KC_BSLS, \
  LT(_FL, KC_CAPS), KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,  KC_NO,    KC_ENT,  \
  KC_LSFT, KC_NO,   KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,  MO(_FL),  KC_UP,   \
  KC_LCTL, KC_LALT, KC_LGUI,                KC_SPC,                         KC_NO,  KC_RGUI,KC_LEFT,  KC_DOWN,  KC_RGHT),

// Function layer
[_FL] = LAYOUT(
  KC_GRV, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11,   KC_F12,   KC_DEL, \
  KC_NO,  KC_MPRV,KC_UP,  KC_MNXT,KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_PSCR,KC_SLCK,  KC_PAUS,  KC_INS, \
  KC_TRNS,KC_LEFT,KC_DOWN,KC_RGHT,KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_NO,    KC_NO,  \
  KC_TRNS,KC_NO,  KC_MUTE,KC_VOLD,KC_VOLU,KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_TRNS,  LT(_RGBL, KC_PGUP),\
  KC_TRNS,KC_TRNS,KC_TRNS,                KC_MPLY,                        KC_NO,  KC_TRNS,KC_HOME,  KC_PGDN,  KC_END),

// RGB Layer
[_RGBL] = LAYOUT(
  #ifdef RGBLIGHT_ENABLE
  RESET,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_NO,    KC_NO, \
  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_NO,    KC_NO, \
  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_NO,    KC_NO,  \
  KC_TRNS,KC_NO,  RGB_TOG,RGB_MOD,RGB_HUI,RGB_HUD,RGB_SAI,RGB_SAD,RGB_VAI,RGB_VAD,BL_STEP,BL_TOGG,  KC_TRNS,  KC_TRNS,\
  KC_TRNS,KC_TRNS,KC_TRNS,                KC_TRNS,                        KC_NO,  KC_TRNS,KC_TRNS,  KC_TRNS,  KC_TRNS),
  #else
  RESET,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_NO,    KC_NO, \
  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_NO,    KC_NO, \
  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_NO,    KC_NO,  \
  KC_TRNS,KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  BL_STEP,BL_TOGG,  KC_TRNS,  KC_TRNS,\
  KC_TRNS,KC_TRNS,KC_TRNS,                KC_TRNS,                        KC_NO,  KC_TRNS,KC_TRNS,  KC_TRNS,  KC_TRNS),
  #endif
};


enum function_id {
    SHIFT_ESC,
};

const uint16_t PROGMEM fn_actions[] = {
  [0]  = ACTION_FUNCTION(SHIFT_ESC),
};

#define MODS_CTRL_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))
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
