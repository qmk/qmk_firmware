#include QMK_KEYBOARD_H

enum layers {
	_BASE,
	_LIST
};

enum my_keycodes {
	MYRGB_TG = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT(
    KC_MPLY,	KC_PSLS,	KC_PAST,	KC_ESC,		KC_F1,		KC_F2,		KC_F3,		KC_F4,		KC_F5,			KC_F6,		KC_F7,		KC_F8,		KC_F9,		KC_F10,		KC_F11,		KC_F12,		MYRGB_TG,	KC_PGUP,
	KC_MUTE,	KC_PPLS,	KC_PMNS,	KC_GRV,		KC_1,		KC_2,		KC_3,		KC_4,		KC_5,			KC_6,		KC_7,		KC_8,		KC_9,		KC_0,		KC_MINS,	KC_EQL,		KC_DEL,		KC_PGDN,
	KC_P7,		KC_P8,		KC_P9,		KC_TAB,		KC_Q,		KC_W,		KC_E,		KC_R,		KC_T,			KC_Y,		KC_U,		KC_I,		KC_O,		KC_P,		KC_LBRC,	KC_RBRC,	KC_BSLS,	KC_HOME,
	KC_P4,		KC_P5,		KC_P6,		KC_BSPC,	KC_A,		KC_S,		KC_D,		KC_F,		KC_G,			KC_H,		KC_J,		KC_K,		KC_L,		KC_SCLN,	KC_QUOT,	KC_ENT,		XXXXXXX,	KC_PSCR,
	KC_P1,		KC_P2,		KC_P3,		KC_LSFT,	KC_Z,		KC_X,		KC_C,		KC_V,		KC_B,			KC_N,		KC_M,		KC_COMM,	KC_DOT,		KC_SLSH,	KC_RSFT,	KC_UP,		KC_CAPS,	KC_INS,
	KC_P0,		KC_PDOT,	KC_PENT,	KC_LCTL,	TO(_LIST),	KC_LGUI,	KC_LALT,	XXXXXXX,	KC_SPC,			KC_SPC,		XXXXXXX,	KC_RALT,	KC_RGUI,	KC_RCTL,	KC_LEFT,	KC_DOWN,	KC_RGHT,	KC_NUM
),

[_LIST] = LAYOUT(
	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,			_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,
	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,			_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,
	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,			_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,
	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,			_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,
	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,			_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,
	_______,	_______,	_______,	_______,	TO(_BASE),	_______,	_______,	_______,	_______,			_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______
)

};

bool rgbinit = true;
bool rgbon = true;

const uint8_t RGBLED_RAINBOW_SWIRL_INTERVALS[] PROGMEM = {1,5,5}; //only using the first one

void matrix_post_init_user(void) {
  rgblight_enable_noeeprom();
  led_set_user(host_keyboard_leds());
}

layer_state_t layer_state_set_user(layer_state_t state) {
  switch (get_highest_layer(state)) {
    case _LIST:
      rgblight_sethsv_noeeprom(0,255,255);
      rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL);
      break;
    default: //_BASE
      rgblight_sethsv_noeeprom(0,0,255);
      rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
      break;
  }

  return state;
}

void led_set_user(uint8_t usb_led) {
  if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
    rgblight_mode_noeeprom(RGBLIGHT_MODE_ALTERNATING);
  } else {
    layer_state_set_user(layer_state);
  }
}

void myrgb_toggle(void) {
  if (rgbon) {
    rgblight_disable_noeeprom();
    rgbon = false;
  } else {
    rgblight_enable_noeeprom();
    layer_state_set_user(layer_state);
    led_set_user(host_keyboard_leds());
    rgbon = true;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case MYRGB_TG:
      if (record->event.pressed) {
        myrgb_toggle();
      }
      return false;
    default:
      return true;
  }
}
