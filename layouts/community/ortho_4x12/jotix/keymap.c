#include QMK_KEYBOARD_H
#include "unicode.c"

enum layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _UNI_LCK
};

#define LOWER   MO(_LOWER)
#define RAISE   MO(_RAISE)
#define UNI_LCK MO(_UNI_LCK)
#define TGLOWER TG(_LOWER)
#define TGRAISE TG(_RAISE)
#define SHRAISE LM(_RAISE, MOD_LSFT)

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
    KC_LCTL,KC_LGUI,KC_LALT,UNI_LCK, LOWER , KC_SPC, KC_SPC, RAISE ,SHRAISE,KC_LEFT,KC_DOWN,KC_RGHT
// └───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┘
), 

[_LOWER] = LAYOUT_ortho_4x12 (
// ┌───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┐
    _______, KC_F1 , KC_F2 , KC_F3 , KC_F4 ,_______, KC_INS, KC_P7 , KC_P8 , KC_P9 ,KC_PMNS,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    _______, KC_F5 , KC_F6 , KC_F7 , KC_F8 ,KC_HOME,KC_PGUP, KC_P4 , KC_P5 , KC_P6 ,KC_PPLS,KC_PENT,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    _______, KC_F9 , KC_F10, KC_F11, KC_F12, KC_END,KC_PGDN, KC_P1 , KC_P2 , KC_P3 ,KC_PAST,KC_PSLS,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    _______,_______,_______,_______,_______,_______,_______,_______, KC_P0 ,KC_PDOT,KC_LPRN,KC_RPRN     
// └───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┘
),

[_RAISE] = LAYOUT_ortho_4x12 (
// ┌───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┐
     KC_GRV,  KC_1 ,  KC_2 ,  KC_3 ,  KC_4 ,  KC_5 ,  KC_6 ,  KC_7 ,  KC_8 ,  KC_9 ,  KC_0 , KC_DEL,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    KC_CAPS,_______,_______,_______,_______,_______,KC_LBRC,KC_RBRC,KC_BSLS,KC_QUOT,_______,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    _______,_______,_______,_______,_______,_______,KC_MINS, KC_EQL,_______,_______,KC_VOLU,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,KC_VOLD,KC_MUTE
// └───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┘
),

[_UNI_LCK] = LAYOUT_ortho_4x12 (
// ┌───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┐
     UN_ESC, UN_Q  , UN_W  , UN_E  , UN_R  , UN_T  , UN_Y  , UN_U  , UN_I  , UN_O  , UN_P  ,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    _______, UN_A  , UN_S  , UN_D  , UN_F  , UN_G  , UN_H  , UN_J  , UN_K  , UN_L  ,UN_SCLN,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    _______, UN_Z  , UN_X  , UN_C  , UN_V  , UN_B  , UN_N  , UN_M  ,UN_COMM, UN_DOT, UN_UP ,UN_SLSH,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    UC_M_LN,UC_M_WI,UC_M_OS,_______,TGLOWER,_______,_______,TGRAISE,_______,UN_LEFT,UN_DOWN,UN_RGHT
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
  case _UNI_LCK:
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

void led_set_user(uint8_t usb_led) {
  if (!(IS_LED_ON(usb_led, USB_LED_NUM_LOCK))) {
    tap_code(KC_NUMLOCK);
  }
}

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
