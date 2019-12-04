#include QMK_KEYBOARD_H

#define _QWERTY 0
#define _FN1 1
#define _FN2 2
#define X0 LT(_FN2, KC_CAPS)
#define X1 MO(_FN1)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 /* Default layer */
  [_QWERTY] = LAYOUT_68_ansi(
    KC_GESC, KC_1  , KC_2  , KC_3  , KC_4  , KC_5  , KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_MINS, KC_EQL, KC_BSPC,      KC_INS ,KC_PGUP,
    KC_TAB , KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  , KC_Y  , KC_U  , KC_I  , KC_O  , KC_P  ,KC_LBRC,KC_RBRC, KC_BSLS,      KC_DEL ,KC_PGDN,
    X0     , KC_A  , KC_S  , KC_D  , KC_F  , KC_G  , KC_H  , KC_J  , KC_K  , KC_L  ,KC_SCLN,KC_QUOT,    KC_ENTER,
    KC_LSFT     , KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  , KC_N  , KC_M  ,KC_COMM,KC_DOT ,KC_SLSH,       KC_RSFT,            KC_UP ,
    KC_LCTL ,KC_LALT ,KC_LGUI ,            KC_SPACE                     ,  X1   ,KC_RALT ,KC_RCTL ,                KC_LEFT,KC_DOWN,KC_RGHT
  ),
 /* FN Layer */
  [_FN1] = LAYOUT_68_ansi(
    KC_GRV , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 , KC_F6 , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 ,KC_F12 ,  KC_BSPC,     KC_VOLU,KC_HOME,
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,KC_PSCR,KC_SLCK,KC_PAUS,_______,       KC_VOLD,KC_END,
     X0    ,_______,_______,_______,_______,_______,_______,_______,_______,_______,KC_MRWD,KC_MFFD,    _______,
   _______      ,_______,_______,KC_MSTP,KC_MPRV,KC_MNXT,KC_MPLY,KC_VOLD,KC_VOLU,KC_MUTE,_______,       _______,           _______,
   _______ ,_______ ,_______ ,             _______,                      _______,_______,_______,                  _______,_______,_______
  ),

 /* CAPS LOCK layer */
  [_FN2] = LAYOUT_68_ansi(
    KC_GRV , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 , KC_F6 , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 ,KC_F12 , KC_BSPC,      KC_VOLU,KC_HOME,
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______, _______,      KC_VOLD,KC_END,
    _______,_______,_______,_______,_______,_______,KC_LEFT,KC_DOWN, KC_UP ,KC_RGHT,_______,_______,    _______,
    _______     ,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,       _______,           _______,
    _______ ,_______ ,_______ ,            _______,                      _______,_______,_______,                  _______,_______,_______
  )
};



void led_set_user(uint8_t usb_led){
    //turn on the Pro Micro's on board LEDs for CAPS LOCK
    if(IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)){
        //set led pins to low
        setPinOutput(B0);
        writePinLow(B0);
        setPinOutput(D5);
        writePinLow(D5);
    } else {
        //set to Hi-Z
        setPinInput(B0);
        writePinLow(B0);
        setPinInput(D5);
        writePinLow(D5);
    }
}
