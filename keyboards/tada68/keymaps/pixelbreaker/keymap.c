#include QMK_KEYBOARD_H

#define _MA 0
#define _FL 1
#define _CL 2
#define _LO 3
#define _UL 4

#define ___ KC_TRNS // transparent key
#define xxx KC_NO // noop
// #define trigger_time 400

// enum custom_keycodes {
//   STR_POUND = SAFE_RANGE
// };

#define CAPS LT(_CL, KC_CAPS)

// static uint16_t key_timer;

// Tap dance declarations (These must go above the keymaps)
enum {
  TD_PGUP = 0,
  TD_PGDN
  // TD_F1 = 0,
  // TD_F2,
  // TD_F3,
  // TD_F4,
  // TD_F5,
  // TD_F6,
  // TD_F7,
  // TD_F8,
  // TD_F9,
  // TD_F10,
  // TD_F11,
  // TD_F12,
  // TD_Z
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _MA: Main Layer, Default
   * ,----------------------------------------------------------------.
   * |Esc |1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp  | Del|
   * |----------------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  | ~` |
   * |----------------------------------------------------------------|
   * |CAPS    | A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |PgUp|
   * |----------------------------------------------------------------|
   * |Shft    |Z/~|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift | Up|PgDn|
   * |----------------------------------------------------------------|
   * |Ctrl|Alt |Apple|       Space          |Alt|Ctrl| FN|Lef|Dow|Rig |
   * `----------------------------------------------------------------'
   */
[_MA] = LAYOUT_ansi(
  KC_GESC,	KC_1, 		KC_2, 		KC_3, 		KC_4, 		KC_5, 		KC_6, 		KC_7, 		KC_8, 		KC_9, 		KC_0, 		KC_MINS,	KC_EQL,		KC_BSPC,	KC_DEL, \
  KC_TAB,	KC_Q, 		KC_W, 		KC_E, 		KC_R, 		KC_T, 		KC_Y, 		KC_U, 		KC_I,  		KC_O,  		KC_P, 		KC_LBRC,	KC_RBRC,	KC_BSLS,	KC_GRV, \
  CAPS,		KC_A, 		KC_S,   	KC_D, 		KC_F, 		KC_G, 		KC_H, 		KC_J, 		KC_K,  		KC_L,  		KC_SCLN, 	KC_QUOT,  				KC_ENT,		TD(TD_PGUP), \
  KC_LSPO,		KC_Z, 		KC_X,   	KC_C, 		KC_V, 		KC_B, 		KC_N, 		KC_M, 		KC_COMM, 	KC_DOT,		KC_SLSH, 	KC_RSPC,    KC_UP,		TD(TD_PGDN), \
  KC_LCTL, 	KC_LALT,	KC_LGUI,						KC_SPC,											KC_RALT,	KC_RCTRL, 	MO(_FL),	KC_LEFT, 	KC_DOWN, 	KC_RGHT),


  /* Keymap _FL: Function Layer
   * ,----------------------------------------------------------------.
   * |~` | F1|F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|Prsc   |_LO |
   * |----------------------------------------------------------------|
   * |     |MbL|MsU|MbR|   |   |   |   |   |  |  |BrgtD|BrgtU|   |    |
   * |----------------------------------------------------------------|
   * |      |MsL|MsD|MsR|   |   |   |   |   |   |   |   |        |Hme |
   * |----------------------------------------------------------------|
   * |       |Prev|Next |P/P |  |  |  |  |VoU|VoD|Mut|      |MwU |End |
   * |----------------------------------------------------------------|
   * |    |    |    |                       |   |   |    |MwL|MwD|MwR |
   * `----------------------------------------------------------------'
   */
[_FL] = LAYOUT_ansi(
  KC_GRV,	KC_F1,		KC_F2,  	KC_F3,  	KC_F4,  	KC_F5,		KC_F6,		KC_F7, 		KC_F8,		KC_F9,		KC_F10,  	KC_F11,		KC_F12,		KC_PSCR,  TO(_LO), \
  ___, 	KC_BTN1,	KC_MS_U,  	KC_BTN2, 	___, 		___, 		___,		___, 		___, 		___, 		___, 		KC_F23,	KC_F24,	___,		___, \
  ___, 	KC_MS_L,	KC_MS_D, 	KC_MS_R,	___,		___,	___,		___,		___,		___,		___,		___,					___,		KC_HOME, \
  ___,		KC_MRWD,		KC_MFFD,		KC_MPLY,	 	___, 		___, 		___,		___,		KC_VOLD,	KC_VOLU,	KC_MUTE,	___,		KC_WH_U,	KC_END, \
  ___, 	___, 		___,								___,											___,		___,		___,   	KC_WH_L,	KC_WH_D, 	KC_WH_R),

  /* Keymap _CL: Caps Layer
   * ,----------------------------------------------------------------.
   * |~`|BrgtD|BrgtU|  |  | F5 |  |Prev|P/P|Next|Mut|VoD|VoU| Del| PWR|
   * |----------------------------------------------------------------|
   * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |    |
   * |----------------------------------------------------------------|
   * |      |   |   |   |   |   |Lft|Dwn| Up|Rgt|   |   |        |    |
   * |----------------------------------------------------------------|
   * |        |BlDn|BlUp|  |  |   |   |   |   |   |   |      |MwU|    |
   * |----------------------------------------------------------------|
   * |    |    |    |                       |   |   |    |MwL|MwD|MwR |
   * `----------------------------------------------------------------'
   */
[_CL] = LAYOUT_ansi(
 KC_GRV,	___,		___,   ___,  	___,  	KC_F5,		___,		KC_MPRV, 		KC_MPLY,		KC_MNXT,		KC_MUTE,  	KC_VOLD,		KC_VOLU,		KC_DEL,		KC_POWER, \
  ___,		___, 		___, 		___, 		___, 		___, 		___, 		___, 		___,  		___,  		___, 		___,		___,		___,		___, \
  ___,		KC_GRV, 		___,   	___, 		___, 		___, 		KC_LEFT, 	KC_DOWN, 	KC_UP,  	KC_RGHT,  	___, 		___, 	 				___,		KC_HOME, \
  KC_LSPO,		   	BL_DEC,			BL_TOGG,			BL_INC,		___,	 	___, 		___, 		___, 		___, 		___,		___, 		___,   	KC_WH_U,		KC_END, \
  KC_LCTL, 	KC_LALT,	KC_LGUI,								___,											___,		___, 		___,		KC_WH_L,	KC_WH_D, 	KC_WH_R),

  /* Keymap _UL: Unlock layer
   * ,----------------------------------------------------------------.
   * |   |   |   |   |   |   |   |   |   |   |   |   |   |       |_MA |
   * |----------------------------------------------------------------|
   * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |    |
   * |----------------------------------------------------------------|
   * |      |   |   |   |   |   |   |   |   |   |   |   |        |    |
   * |----------------------------------------------------------------|
   * |        |   |   |   |   |   |   |   |   |   |   |      |   |    |
   * |----------------------------------------------------------------|
   * |    |    |    |                       |   |   |    |   |   |    |
   * `----------------------------------------------------------------'
   */
[_UL] = LAYOUT_ansi(
  xxx,	xxx, 		xxx, 		xxx, 		xxx, 		xxx, 		xxx, 		xxx,  	xxx, 		xxx, 		xxx,  	xxx, 		xxx, 		xxx, 		TO(_MA), \
  xxx, 	xxx, 		xxx, 		xxx, 		xxx, 		xxx, 		xxx, 		xxx, 		xxx, 		xxx, 		xxx,  	xxx, 		xxx,  	xxx, 		xxx, \
  xxx, 	xxx, 		xxx, 		xxx, 		xxx, 		xxx, 		xxx, 		xxx, 		xxx, 		xxx, 		xxx, 		xxx, 					xxx, 		xxx, \
  xxx,	 		xxx, 		xxx, 		xxx, 		xxx, 		xxx, 		xxx, 		xxx, 		xxx, 		xxx, 		xxx, 		xxx, 		xxx, 		xxx, \
  xxx, 	xxx, 		xxx,    							xxx,											xxx, 		xxx, 		___, 		xxx, 		xxx, 		xxx),

  /* Keymap _LO: Lock layer
   * ,----------------------------------------------------------------.
   * |   |   |   |   |   |   |   |   |   |   |   |   |   |       |    |
   * |----------------------------------------------------------------|
   * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |    |
   * |----------------------------------------------------------------|
   * |      |   |   |   |   |   |   |   |   |   |   |   |        |    |
   * |----------------------------------------------------------------|
   * |        |   |   |   |   |   |   |   |   |   |   |      |   |    |
   * |----------------------------------------------------------------|
   * |    |    |    |                      |   |   | _UL |   |   |    |
   * `----------------------------------------------------------------'
   */
[_LO] = LAYOUT_ansi(
  xxx,	xxx, 		xxx, 		xxx, 		xxx, 		xxx, 		xxx, 		xxx,  	xxx, 		xxx, 		xxx,  	xxx, 		xxx, 		xxx, 		xxx, \
  xxx, 	xxx, 		xxx, 		xxx, 		xxx, 		xxx, 		xxx, 		xxx, 		xxx, 		xxx, 		xxx,  	xxx, 		xxx,  	xxx, 		xxx, \
  xxx, 	xxx, 		xxx, 		xxx, 		xxx, 		xxx, 		xxx, 		xxx, 		xxx, 		xxx, 		xxx, 		xxx, 					xxx, 		xxx, \
  xxx,	 		xxx, 		xxx, 		xxx, 		xxx, 		xxx, 		xxx, 		xxx, 		xxx, 		xxx, 		xxx, 		xxx, 		xxx, 		xxx, \
  xxx, 	xxx, 		xxx,    							xxx,											xxx, 		xxx, 		MO(_UL), 	xxx, 		xxx, 		xxx),
};

void tap(uint16_t keycode){
	register_code(keycode);
	unregister_code(keycode);
};

void led_set_user(uint8_t usb_led) {
	if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        // Turn capslock on
        PORTB |= (1<<6);
    } else {
        // Turn capslock off
        PORTB &= ~(1<<6);
    }
}

// Tapdance definitions. Tap Dance F Keys.
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_PGUP] = ACTION_TAP_DANCE_DOUBLE(KC_PGUP, KC_HOME),
  [TD_PGDN] = ACTION_TAP_DANCE_DOUBLE(KC_PGDN, KC_END)
};
