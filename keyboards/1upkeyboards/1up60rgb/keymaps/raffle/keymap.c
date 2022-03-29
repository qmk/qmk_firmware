//****************************************************************************//
// raffle's keymap for the 1up60rgb.                                          //
//   emulates my pok3r layout and adds RGB control + firmware reset/debug     //
//   layers                                                                   //
//****************************************************************************//

//************************ dependencies + definitions ************************//
#include QMK_KEYBOARD_H

// create names for layers
enum layers {
  _typing,
  _raise,
  _rgb,
  _adjust
};

// define layer mods
#define RAISE MO(_raise)
#define RGB MO(_rgb)

// define mod masks for making multi-key macros
#define MODS_SHIFT_MASK  (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT))
#define MODS_CTRL_MASK  (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTRL))
#define MODS_ALT_MASK  (MOD_BIT(KC_LALT) | MOD_BIT(KC_RALT))

//********************************** Layers **********************************//
// define layers
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // typing layer to handle basic typing
  [_typing] = LAYOUT_all
  (
   KC_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_BSPC,
   KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
   KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_ENT,
   KC_LSFT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_RSFT,
   RAISE, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, KC_RGUI, RGB, KC_RCTL
   ),
  // raise layer to handle function & nav keys
    [_raise] = LAYOUT_all
  (
   KC_GRV,  KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL, KC_DEL,
   KC_TRNS, KC_MPRV, KC_MPLY, KC_MNXT, KC_TRNS, KC_TRNS, KC_CALC, KC_PGUP, KC_UP, KC_PGDN, KC_PSCR, KC_LSCR, KC_PAUSE, KC_TRNS,
   KC_TRNS, KC_TRNS, KC_VOLD, KC_VOLU, KC_MUTE, KC_TRNS, KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT, KC_INS, KC_DEL, KC_TRNS, KC_TRNS,
   KC_TRNS, KC_TRNS, KC_APP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_END, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
   ),
  // rgb layer for pretty backlight colors
  [_rgb] = LAYOUT_all
  (
   RGB_TOG, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, RGB_M_K, RGB_M_X, RGB_M_G, RGB_M_T, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_HUI, RGB_VAI, RGB_HUD, KC_NO, KC_NO, KC_NO, KC_NO,
   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_MOD, RGB_SAI, RGB_VAD,RGB_SAD, KC_NO, KC_NO, KC_NO, KC_NO,
   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_RMOD, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
   ),
  // adjust to handle firmware debug + reset mode
  [_adjust] = LAYOUT_all
  (
   RESET, DEBUG, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
   )
};

//***************************** Function bodies  *****************************//
// enable tri-layer state for _raise + _rgb = _adjust
layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _raise, _rgb, _adjust);
}


// scan matrix
void matrix_scan_user(void) {
}

// support for standard mod state keys (caps lock, scroll lock, etc.)
void led_set_user(uint8_t usb_led) {

  if (usb_led & (1 << USB_LED_NUM_LOCK)) {

  } else {

  }

  if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
    DDRB |= (1 << 2); PORTB &= ~(1 << 2);
  } else {
    DDRB &= ~(1 << 2); PORTB &= ~(1 << 2);
  }

  if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {

  } else {

  }

  if (usb_led & (1 << USB_LED_COMPOSE)) {

  } else {

  }

  if (usb_led & (1 << USB_LED_KANA)) {

  } else {

  }

}
