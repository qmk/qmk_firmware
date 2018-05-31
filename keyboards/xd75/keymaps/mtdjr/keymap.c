#include QMK_KEYBOARD_H
#include "mtdjr.h"

#define KC_LOCK TD(TD_ENDLOCK)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 [_QWERTY] = KC_KEYMAP(
//  .--------------------------------------------------------------------------.
      EXC, 1  , 2  , 3  , 4  , 5  ,PGUP,xxxx,PGDN, 6  , 7  , 8  , 9  , 0  ,BSPC,
//  |----+----+----+----+----+----+----+----+----+----+----+----+----+----+----|
      TAB, Q  , W  ,  E , R  , T  , INS,BSLS, DEL, Y  , U  , I  , O  , P  ,QUOT,
//  |----+----+----+----+----+----+----+----+----+----+----+----+----+----+----|
     LCTL, A  , S  ,  D , F  , G  ,HOME,PLUS,LOCK, H  , J  , K  , L  ,SCLN, ENT,
//  |----+----+----+----+----+----+----+----+----+----+----+----+----+----+----|
     LSFT, Z  , X  ,  C , V  , B  ,LBRC,MINS,RBRC, N  , M  ,COMM, DOT,SLSH,RSFT,
//  |----+----+----+----+----+----+----+----+----+----+----+----+----+----+----|
     LOWR,LCTL,LALT,LGUI,xxxx, SPC, SPC,RASE,SPC, SPC,xxxx,LEFT,DOWN,UP  ,RGHT
//  '----+----+----+----+----+----+----+----+----+----+----+----+----+----+----'
),

 [_LOWER] = KC_KEYMAP(
//  .--------------------------------------------------------------------------.
     xxxx,  F1,  F2,  F3,  F4,  F5,  F6,xxxx,  F7,  F8,  F9, F10, F11, F12, DEL,
//  |----+----+----+----+----+----+----+----+----+----+----+----+----+----+----|
     xxxx,ROOT,PPLY,PSEF,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,
//  |----+----+----+----+----+----+----+----+----+----+----+----+----+----+----|
     xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,
//  |----+----+----+----+----+----+----+----+----+----+----+----+----+----+----|
     xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,MUTE,
//  |----+----+----+----+----+----+----+----+----+----+----+----+----+----+----|
         ,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,    ,xxxx,MPLY,xxxx,MPRV,VOLD,VOLU,MNXT
//  '----+----+----+----+----+----+----+----+----+----+----+----+----+----+----'
),

[_RAISE] = KC_KEYMAP(
//  .--------------------------------------------------------------------------.
     xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,
//  |----+----+----+----+----+----+----+----+----+----+----+----+----+----+----|
     xxxx,xxxx,xxxx,xxxx, RST,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,
//  |----+----+----+----+----+----+----+----+----+----+----+----+----+----+----|
     CAPS,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx, BLI,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,
//  |----+----+----+----+----+----+----+----+----+----+----+----+----+----+----|
      RGB,RHUI,RHUD,RSAI,RSAD,RVAI,RVAD, BLD,xxxx,xxxx,xxxx,xxxx,BTN1,BTN2,xxxx,
//  |----+----+----+----+----+----+----+----+----+----+----+----+----+----+----|
         ,xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,    ,xxxx,xxxx,xxxx,MS_L,MS_D,MS_U,MS_R
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
