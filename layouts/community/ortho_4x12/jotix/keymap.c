#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

enum layers {
  _QWERTY,
  _LOWER,
  _RAISE,
};

#define KC_LOWR MO(_LOWER)
#define KC_RAIS MO(_RAISE)
#define KC_TGLO TG(_LOWER)
#define KC_LMRA LM(_RAISE, MOD_LSFT)

static bool is_ctl_pressed;
static bool is_esc_pressed;
static bool is_bspc_pressed;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_kc_ortho_4x12 (
// ┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┐
     ESC, Q  , W  , E  , R  , T  , Y  , U  , I  , O  , P  ,BSPC,
// ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤
     TAB, A  , S  , D  , F  , G  , H  , J  , K  , L  ,SCLN, ENT,
// ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤
    LSFT, Z  , X  , C  , V  , B  , N  , M  ,COMM, DOT, UP, SLSH,
// ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤
    LCTL,LGUI,LALT,TGLO,LOWR, SPC, SPC,RAIS,LMRA,LEFT,DOWN,RGHT
// └────┴────┴────┴────┴────┴────┴────┴────┴────┴────┴────┴────┘
), 

[_LOWER] = LAYOUT_kc_ortho_4x12 (
// ┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┐
        , F1 , F2 , F3 , F4 , INS, NO , P7 , P8 , P9 ,PMNS,    ,
// ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤
        , F5 , F6 , F7 , F8 ,HOME,PGUP, P4 , P5 , P6 ,PPLS,PENT,
// ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤
        , F9 , F10, F11, F12, END,PGDN, P1 , P2 , P3 ,PAST,PSLS,
// ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤
        ,    ,    ,    ,    ,    ,    , NO , P0 ,PDOT,LPRN,RPRN     
// └────┴────┴────┴────┴────┴────┴────┴────┴────┴────┴────┴────┘
),

[_RAISE] = LAYOUT_kc_ortho_4x12 (
// ┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┐
     GRV, 1  , 2  , 3  , 4  , 5  , 6  , 7  , 8  , 9  , 0  , DEL,
// ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤
    CAPS,    ,    ,    ,    ,    ,LBRC,RBRC,BSLS,QUOT,    ,    ,
// ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤
        ,    ,    ,    ,    ,    ,MINS, EQL,    ,    ,VOLU,    ,
// ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤
        ,    ,    ,    ,    ,    ,    ,    ,    ,    ,VOLD,MUTE     
// └────┴────┴────┴────┴────┴────┴────┴────┴────┴────┴────┴────┘
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
  default:
    writePinLow(JOTANCK_LED1);
    writePinLow(JOTANCK_LED2);
    break; 
  };
  #endif
  return state;
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

void led_set_user(uint8_t usb_led) {
  if (!(IS_LED_ON(usb_led, USB_LED_NUM_LOCK))) {
    tap_code(KC_NUMLOCK);
    unregister_code(KC_NUMLOCK);
  }
}

void matrix_scan_user(void) {
  if (is_ctl_pressed && is_esc_pressed && is_bspc_pressed) {
    reset_keyboard();
  }
}
