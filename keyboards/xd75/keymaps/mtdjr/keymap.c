#include QMK_KEYBOARD_H
#include "mtdjr.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 [_QWERTY] = LAYOUT_kc(
//  .--------------------------------------------------------------------------.
      EXC, 1  , 2  , 3  , 4  , 5  ,PGUP,MPNT,PGDN, 6  , 7  , 8  , 9  , 0  ,BSPC,
//  |----+----+----+----+----+----+----+----+----+----+----+----+----+----+----|
      TAB, Q  , W  ,  E , R  , T  , INS,HOME, DEL, Y  , U  , I  , O  , P  ,QUOT,
//  |----+----+----+----+----+----+----+----+----+----+----+----+----+----+----|
     LCTL, A  , S  ,  D , F  , G  , EQL,ELCK,MINS, H  , J  , K  , L  ,SCLN, ENT,
//  |----+----+----+----+----+----+----+----+----+----+----+----+----+----+----|
     LSFT, Z  , X  ,  C , V  , B  ,LBRC,BSLS,RBRC, N  , M  ,COMM, DOT,SLSH,ELCK,
//  |----+----+----+----+----+----+----+----+----+----+----+----+----+----+----|
     LOWR,LCTL,LALT,LGUI,xxxx, SPC,LOWR,RASE,xxxx, SPC, APP,LEFT,DOWN,  UP,RGHT
//  '----+----+----+----+----+----+----+----+----+----+----+----+----+----+----'
),

 [_LOWER] = LAYOUT_kc(
//  .--------------------------------------------------------------------------.
     xxxx, F1 , F2 , F3 , F4 , F5 , F6 ,xxxx, F7 , F8 , F9 , F10, F11, F12, DEL,
//  |----+----+----+----+----+----+----+----+----+----+----+----+----+----+----|
     xxxx,ROOT,PPLY,PSEF,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,
//  |----+----+----+----+----+----+----+----+----+----+----+----+----+----+----|
     xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,CALC,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,
//  |----+----+----+----+----+----+----+----+----+----+----+----+----+----+----|
     xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,MUTE,
//  |----+----+----+----+----+----+----+----+----+----+----+----+----+----+----|
         ,xxxx,xxxx,xxxx,xxxx,xxxx,    ,    ,xxxx,MPLY,xxxx,MNXT,VOLD,VOLU,MNXT
//  '----+----+----+----+----+----+----+----+----+----+----+----+----+----+----'
),

[_RAISE] = LAYOUT_kc(
//  .--------------------------------------------------------------------------.
     xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,
//  |----+----+----+----+----+----+----+----+----+----+----+----+----+----+----|
     xxxx,xxxx,xxxx,xxxx, RST,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,
//  |----+----+----+----+----+----+----+----+----+----+----+----+----+----+----|
     CAPS,xxxx,xxxx,xxxx,xxxx,xxxx, BLI,xxxx, BLD,xxxx,xxxx,xxxx,XLCK,xxxx,xxxx,
//  |----+----+----+----+----+----+----+----+----+----+----+----+----+----+----|
      RGB,RHUI,RHUD,RSAI,RSAD,RVAI,RVAD,xxxx,xxxx,xxxx,xxxx,xxxx,BTN1,MS_U,BTN2,
//  |----+----+----+----+----+----+----+----+----+----+----+----+----+----+----|
         ,xxxx,xxxx,xxxx,xxxx,xxxx,    ,    ,xxxx,xxxx,xxxx,xxxx,MS_L,MS_D,MS_R
//  '----+----+----+----+----+----+----+----+----+----+----+----+----+----+----'
)
};

void led_set_user(uint8_t usb_led) {
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        capslock_led_on();
    } else {
        capslock_led_off();
    }
}
