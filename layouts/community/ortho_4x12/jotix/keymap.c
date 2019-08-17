#include QMK_KEYBOARD_H
#include "unicode.c"

enum layers {
  _QWERTY,
  _FN,
  _LOWER,
  _RAISE,
  _UNICODE
};

#define FN      MO(_FN)
#define LOWER   MO(_LOWER)
#define RAISE   MO(_RAISE)
#define UNICODE MO(_UNICODE)
#define TGLOWER TG(_LOWER)
#define TGRAISE TG(_RAISE)

static bool is_ctl_pressed;
static bool is_esc_pressed;
static bool is_bspc_pressed;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_ortho_4x12 (
// ┌───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┐
     KC_ESC, KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  , KC_Y  , KC_U  , KC_I  , KC_O  , KC_P  ,KC_BSPC,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
     KC_TAB, KC_A  , KC_S  , KC_D  , KC_F  , KC_G  , KC_H  , KC_J  , KC_K  , KC_L  ,KC_SCLN, KC_ENT,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    KC_LSFT, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  , KC_N  , KC_M  ,KC_COMM, KC_DOT, KC_UP ,KC_SLSH,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    KC_LCTL,KC_LGUI,KC_LALT,   FN  , LOWER , KC_SPC, KC_SPC, RAISE ,UNICODE,KC_LEFT,KC_DOWN,KC_RGHT
// └───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┘
), 

[_FN] = LAYOUT_ortho_4x12 (
// ┌───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┐
    _______, KC_F1 , KC_F2 , KC_F3 , KC_F4 ,_______,_______,_______,_______,_______,_______,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    _______, KC_F5 , KC_F6 , KC_F7 , KC_F8 ,_______,_______,_______,_______,_______,_______,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    _______, KC_F9 , KC_F10, KC_F11, KC_F12,_______,_______,_______,_______,_______,KC_PGUP,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    _______,_______,_______,_______,TGLOWER,_______,_______,TGRAISE,_______,KC_HOME,KC_PGDN, KC_END
// └───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┘
),

[_LOWER] = LAYOUT_ortho_4x12 (
// ┌───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┐
    _______,  KC_1 ,  KC_2 ,  KC_3 ,  KC_4 ,  KC_5 ,  KC_6 ,  KC_7 ,  KC_8 ,  KC_9 ,  KC_0 ,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    _______,KC_VOLD,KC_MUTE,KC_VOLU,KC_HOME,KC_PGUP,KC_LBRC,KC_RBRC,KC_BSLS,KC_QUOT,_______,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    _______,KC_MPRV,KC_MPLY,KC_MNXT, KC_END,KC_PGDN,KC_MINS, KC_EQL,_______,_______,_______,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
// └───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┘
),

[_RAISE] = LAYOUT_ortho_4x12 (
// ┌───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┐
     KC_GRV,  KC_1 ,  KC_2 ,  KC_3 ,  KC_4 ,  KC_5 ,  KC_6 ,  KC_7 ,  KC_8 ,  KC_9 ,  KC_0 , KC_DEL,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    _______,_______,_______,_______,_______,_______,KC_LBRC,KC_RBRC,KC_BSLS,KC_QUOT,_______,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    _______,_______,_______,_______,_______,_______,KC_MINS, KC_EQL,_______,_______,KC_VOLU,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,KC_VOLD,KC_MUTE
// └───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┘
),

[_UNICODE] = LAYOUT_ortho_4x12 (
// ┌───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┐
     UN_ESC, UN_Q  , UN_W  , UN_E  , UN_R  , UN_T  , UN_Y  , UN_U  , UN_I  , UN_O  , UN_P  ,UN_BSPC,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
     UN_TAB, UN_A  , UN_S  , UN_D  , UN_F  , UN_G  , UN_H  , UN_J  , UN_K  , UN_L  ,UN_SCLN, UN_ENT,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    _______, UN_Z  , UN_X  , UN_C  , UN_V  , UN_B  , UN_N  , UN_M  ,UN_COMM, UN_DOT, UN_UP ,UN_SLSH,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    UC_M_LN,UC_M_WI,UC_M_OS,_______,_______,_______,_______,_______,_______,UN_DOWN, UN_UP ,UN_RGHT
// └───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┘
),

};

uint32_t layer_state_set_user(uint32_t state) {
  #ifdef JOTANCK_LEDS
  switch (biton32(state)) {
  case _LOWER:
    writePinHigh(JOTANCK_LED1);
    writePinLow(JOTANCK_LED2);
    break;
  case _RAISE:
    writePinLow(JOTANCK_LED1);
    writePinHigh(JOTANCK_LED2);
    break;
  case _FN:
    writePinHigh(JOTANCK_LED1);
    writePinHigh(JOTANCK_LED2);
    break;
  default:
    writePinLow(JOTANCK_LED1);
    writePinLow(JOTANCK_LED2);
    break; 
  };
  #endif
  return state;
}

/*  
void led_set_user(uint8_t usb_led) {
  if (!(IS_LED_ON(usb_led, USB_LED_NUM_LOCK))) {
    tap_code(KC_NUMLOCK);
  }
}
*/

void keyboard_post_init_user(void) {
    set_unicode_input_mode(UC_LNX);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_LCTL:
      is_ctl_pressed = record->event.pressed;
      break;
    case KC_ESC:
      is_esc_pressed = record->event.pressed;
      break;
    case KC_BSPC:
      is_bspc_pressed = record->event.pressed;
      break;
  };
  return true;
}

void matrix_scan_user(void) {
  if (is_ctl_pressed && is_esc_pressed && is_bspc_pressed) {
    reset_keyboard();
  }
}
