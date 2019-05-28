#include QMK_KEYBOARD_H
#include "../../../../../quantum/rgblight_list.h"

#define base 0
#define raise 1 
#define lower 2
#define game 3

//Tap Dance Declarations
enum {
  TD_SEMI_QUOT = 0,
  TD_COMM_MINUS = 1,
  TD_DOT_EQUAL = 2,
  TD_SLASH_BACKSLASH = 3,
  TBL_FLP = SAFE_RANGE,
  RST
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for ;, twice for ' -not used anymore
  [TD_SEMI_QUOT]  = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_QUOT),
  //Tap once for , twice for -
  [TD_COMM_MINUS]  = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_MINUS),
  //Tap once for . twice for =
  [TD_DOT_EQUAL]  = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_EQUAL),
  //Tap once for / twice for '\'
  [TD_SLASH_BACKSLASH]  = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_BSLS)
};

#define MODS_CTRL_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[base] = LAYOUT_2u_space_ortho(
		KC_TAB,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
		KC_ESC,     KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_ENT,
		KC_LSPO,    KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     TD(1),    TD(2),    TD(3),    KC_RSPC,
		KC_LCTL,    _______,  KC_LALT,  KC_LGUI,  MO(1),        KC_SPC,         MO(2),    KC_VOLD,  KC_MPLY,  KC_VOLU,  KC_GRV),

	[raise] = LAYOUT_2u_space_ortho(
		_______,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_DEL,
		_______,    _______,  _______,  _______,  _______,  _______,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RIGHT, KC_QUOT,  _______,
		_______,    KC_HOME,  KC_END,   _______,  _______,  _______,  _______,  _______,  KC_LBRC,  KC_RBRC,  _______,  _______,  
		_______,    _______,  _______,  _______,  _______,      _______,        _______,  KC_MPRV,  _______,  KC_MNXT,  RST),

	[lower] = LAYOUT_2u_space_ortho(
		_______,    KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     _______,
		_______,    RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_VAD,  _______,  _______,  KC_4,     KC_5,     KC_6,   KC_KP_PLUS, _______,
		_______,    RGB_SAI,  RGB_SAD,  RGB_HUI,  RGB_HUD,  _______,  _______,  KC_1,     KC_2,     KC_3,  KC_KP_MINUS, _______,
		_______,    _______,  _______,  _______,  _______,      _______,        _______,  KC_0,     _______,  _______,  _______),


	[game] = LAYOUT_2u_space_ortho(
		KC_TAB,     KC_Q,     KC_W,     KC_UP,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
		KC_ESC,     KC_A,     KC_LEFT,  KC_DOWN,   KC_RIGHT, KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     TD(0),    KC_ENT,
		KC_LSFT,    KC_Z,     KC_X,     KC_C,      KC_V,     KC_B,     KC_N,     KC_M,     TD(1),    TD(2),    TD(3),    KC_RSFT,
		KC_LCTL,    _______,  KC_LALT,  KC_LGUI,   _______,       KC_SPC,        _______,  KC_VOLD,  KC_MPLY,  KC_VOLU,  KC_GRV),
};

//change colors and rgb modes on layer change
uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
    case raise:
        rgblight_mode(1);
        rgblight_setrgb_purple ();
        break;
    case lower:
        rgblight_mode(1);
        rgblight_setrgb(0x00, 0xa3, 0x0d);
        break;
    case game:
        rgblight_mode(1);
        rgblight_setrgb_red ();
        break;
    default: // for any other layers, or the default layer
        rgblight_mode(5);
        rgblight_setrgb(0xFF, 0xB6, 0x00);
        break;
    }
  return state;
};

enum function_id {
    SHIFT_ESC,
};

//I think this is to cancel space cadet stuff
const uint16_t PROGMEM fn_actions[] = {
  [0]  = ACTION_FUNCTION(SHIFT_ESC),
};

//Macros
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case TBL_FLP:
      if (record->event.pressed) {
        // when keycode tableflip is pressed
        send_unicode_hex_string("0028 30CE 0CA0 75CA 0CA0 0029 30CE 5F61 253B 2501 253B");
      } else {
        // when keycode tableflip is released
      }
      break;
    case RST:
      if (record->event.pressed) {
        // when keycode reset is pressed
        eeconfig_init();
        SEND_STRING("resetting");
      } else {
        // when keycode reset is released
      }
      break;

  }
  return true;
};
