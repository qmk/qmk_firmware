#include "dz60.h"

#define MODS_CTRL_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

#define ______ KC_TRNS

const uint8_t RGBLED_RAINBOW_SWIRL_INTERVALS[] PROGMEM = {10, 5, 5};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------------.
 * | ` ~ |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |  \  |  `  |
 * |-----------------------------------------------------------------------------------------+
 * | Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |    \   |
 * |-----------------------------------------------------------------------------------------+
 * | Caps    |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter    |
 * |-----------------------------------------------------------------------------------------+
 * | Shift     |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |    RSh    | FN  |
 * |-----------------------------------------------------------------------------------------+
 * | Ctrl |  Alt  |  Cmd  |                   Space                    | Cmd | RAlt |  Ctrl  |
 * `-----------------------------------------------------------------------------------------'
 */

  LAYOUT_60_tsangan_hhkb(
      KC_GESC,               KC_1,    KC_2,    KC_3,   KC_4,   KC_5,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,
      KC_TAB,                KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
      MT(MOD_LCTL, KC_CAPS), KC_A,    KC_S,    KC_D,   KC_F,   KC_G,   KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,       KC_ENT    ,
      KC_LSFT,               KC_Z,    KC_X,   KC_C,   KC_V,   KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(1),
   		KC_LCTL, KC_LALT, KC_LGUI, KC_SPC, KC_RGUI, KC_RALT, KC_RCTL
      ),

/* FN Layer
 * ,-----------------------------------------------------------------------------------------.
 * | Esc | BL- | BL+ | BL  |     |     |     |RESET|     |     |     |     |     |           |
 * |-----------------------------------------------------------------------------------------+
 * |        |RBGM |     |     |     |     |     |     |     |     |     | Val+ | Val- |RBGTOG|
 * |-----------------------------------------------------------------------------------------+
 * |         | Hue+| Hue-| Sat+| Sat-|     |     |     |     |     |     |     |             |
 * |-----------------------------------------------------------------------------------------+
 * |           |     |     |     |     |     |     |     |     |     |     |     | Ctrl|     |
 * |-----------------------------------------------------------------------------------------+
 * |      |       |       |                                   |     |      |     |     |     |
 * `-----------------------------------------------------------------------------------------'
 */

  LAYOUT_60_tsangan_hhkb(
      KC_GRV, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, KC_F11, KC_F12, ______, ______,
      ______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, RGB_M_SW, ______, KC_UP, ______, RESET,
      ______, KC_MUTE, KC_VOLD, KC_VOLU, ______, ______, ______, ______, ______, ______, KC_LEFT, KC_RIGHT, ______,
      ______, KC_PSCR, KC_SLCK, ______, ______, ______, ______, ______, ______, ______, KC_DOWN, ______, ______,
		  ______, ______, ______, ______, ______, ______, ______
      ),
};

enum function_id {
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
