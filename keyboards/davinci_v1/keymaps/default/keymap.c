#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _SYMB 1
#define _NAV 2
#define _ADJUST 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  NAV,
};

#define KC_NAV MO(_NAV)
#define KC_ADJ MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
     KC_ESC  ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_F6    , XXXXXXX, XXXXXXX,                XXXXXXX ,KC_F7   ,KC_F8    ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,XXXXXXX, XXXXXXX, 
     KC_GRV  ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,KC_6     , KC_7   , XXXXXXX,                KC_6    ,KC_7    ,KC_8     ,KC_9    ,KC_0    ,KC_MINS ,KC_EQL  ,KC_BSPC, XXXXXXX, 
     KC_TAB  ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,KC_Y     , XXXXXXX, XXXXXXX,                KC_T    ,KC_Y    ,KC_U     ,KC_I    ,KC_O    ,KC_P    ,KC_LBRC ,KC_RBRC, KC_BSLS, 
     KC_CAPS  ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,KC_H     , XXXXXXX, XXXXXXX,                KC_G    ,KC_H    ,KC_J     ,KC_K    ,KC_L    ,KC_SCLN ,KC_QUOT ,KC_ENT , XXXXXXX, 
     KC_LSFT ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,KC_N     , XXXXXXX, XXXXXXX,                KC_B    ,KC_N    ,KC_M     ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_UP   ,KC_RSFT, XXXXXXX, 
     KC_LCTL ,KC_LGUI ,KC_LALT ,KC_LALT ,KC_SPC  ,KC_BSPC ,XXXXXXX  , XXXXXXX, XXXXXXX,                KC_ENT  ,KC_SPC  ,KC_ENT  ,KC_RALT ,KC_LEFT ,KC_DOWN ,KC_RGHT, XXXXXXX, XXXXXXX 
  ),


//   [_NAV] = LAYOUT(
//      KC_ESC , KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   , KC_F6,                 KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
//      _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,               _______ ,_______  ,_______ ,_______ ,_______ ,_______ ,_______ ,
//      XXXXXXX ,KC_ESC ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,               _______ ,KC_WH_U  ,KC_HOME ,KC_END  ,XXXXXXX ,XXXXXXX ,XXXXXXX , XXXXXXX,
//      XXXXXXX ,XXXXXXX ,KC_BTN3 ,KC_BTN2 ,KC_BTN1 ,XXXXXXX ,_______ ,               KC_MS_L ,KC_MS_D  ,KC_MS_U ,KC_MS_R, XXXXXXX ,XXXXXXX ,XXXXXXX ,
//      XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,               KC_WH_D ,KC_WH_L  ,KC_WH_R ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
//      XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_ACL0 ,KC_ACL0 ,KC_ACL1 ,KC_ACL2 ,               KC_BTN2 ,KC_BTN1  ,KC_BTN3 ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX 
//   ),
  
//   [_ADJUST] = LAYOUT(
//      KC_ESC  ,KC_F1   ,KC_F2   ,KC_F3   ,A(KC_F4),KC_F5   , KC_F6,                 KC_MUTE, KC_VOLD, KC_VOLU, KC_BRID, KC_BRIU, KC_PWR,
//     C(KC_GRV),C(KC_1) ,C(KC_2) ,C(KC_3) ,C(KC_4) ,C(KC_5) ,C(KC_6) ,               _______ ,_______  ,_______ ,_______ ,_______ ,_______ ,KC_DEL  ,
//     A(KC_TAB),C(KC_Q) ,C(KC_W) ,C(KC_E) ,C(KC_R) ,C(KC_T) ,C(KC_Y) ,              _______ ,KC_PGUP  ,KC_HOME ,KC_END  ,XXXXXXX ,XXXXXXX ,XXXXXXX , XXXXXXX,
//      KC_CAPS ,C(KC_A) ,C(KC_S) ,KC_LGUI ,C(KC_F) ,C(KC_G) ,C(KC_H) ,               KC_LEFT ,KC_DOWN  ,KC_UP   ,KC_RGHT ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
//      KC_LSFT ,C(KC_Z) ,C(KC_X) ,C(KC_C) ,C(KC_V) ,C(KC_B) ,C(KC_N) ,               KC_PGDN ,KC_PGDN  ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
//      XXXXXXX ,XXXXXXX ,KC_LALT ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,               _______ ,_______  ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX 
//   ),
};