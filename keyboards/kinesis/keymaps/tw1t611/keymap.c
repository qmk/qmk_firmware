#include QMK_KEYBOARD_H
#include "keymap_german.h"

#define QWERTZ 0
#define MOD 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[QWERTZ] = LAYOUT(
           _______,KC_F1  ,KC_F2  ,KC_F3  ,KC_F4  ,KC_F5  ,KC_F6  ,KC_F7  ,KC_F8,
           _______,KC_1   ,KC_2   ,KC_3   ,KC_4   ,KC_5   ,
           KC_ESC ,KC_Q   ,KC_W   ,KC_E   ,KC_R   ,KC_T   ,
           KC_TAB ,KC_A   ,KC_S   ,KC_D   ,KC_F   ,KC_G   ,
           DE_PIPE,KC_Z   ,KC_X   ,KC_C   ,KC_V   ,KC_B   ,
           _______,_______,_______,_______,
                   KC_RCTL,KC_LALT,
                   KC_HOME,
                   KC_SPC ,KC_LSFT,KC_BSPC ,
           KC_F9  ,KC_F10 ,KC_F11 ,KC_F12 ,KC_PSCR,KC_SLCK,KC_PAUS,KC_NO ,QK_BOOT,
           KC_6   ,KC_7   ,KC_8   ,KC_9   ,KC_0   ,DE_SS  ,
           KC_Y   ,KC_U   ,KC_I   ,KC_O   ,KC_P   ,DE_ADIA,
           KC_H   ,KC_J   ,KC_K   ,KC_L   ,DE_SLSH,DE_ODIA,
           KC_N   ,KC_M   ,DE_COMM,DE_DOT ,DE_MINS,DE_UDIA,
           _______,_______,_______,_______,
                   KC_LGUI,KC_LCTL,
                   KC_END ,
                   KC_DEL,MO(MOD),KC_ENTER
    ),
[MOD] = LAYOUT(
           _______,_______,_______,_______,_______,_______,_______,_______,_______,
           _______,_______,_______,_______,_______,_______,
           DE_CIRC,DE_QUOT,DE_DQUO,DE_LCBR,DE_RCBR,DE_GRV ,
           DE_TILD,DE_EXLM,DE_DLR ,DE_LPRN,DE_RPRN,DE_AMPR,
           DE_BSLS,DE_HASH,DE_LABK,DE_LBRC,DE_RBRC,DE_RABK,
           _______,_______,_______,_______,
                   _______,_______,
                   _______,
                   _______,_______,_______,
           _______,_______,_______,_______,_______,_______,_______,_______,_______,
           _______,_______,_______,_______,_______,_______,
           KC_HOME,KC_PGDN,KC_PGUP,KC_END ,DE_EQL ,DE_PERC,
           KC_LEFT,KC_DOWN,KC_UP  ,KC_RGHT,DE_QUES,DE_ASTR,
           DE_AT  ,DE_EURO,DE_SCLN,DE_COLN,DE_UNDS,DE_PLUS,
           _______,_______,_______,_______,
                   _______,_______,
                   _______,
                   _______,_______ ,_______
    )
};

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void led_set_user(uint8_t usb_led) {

}
