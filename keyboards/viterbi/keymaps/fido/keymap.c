#include "viterbi.h"
#include "action_layer.h"
#include "eeconfig.h"
#ifdef RGBLIGHT_ENABLE
#include "rgblight.h"
#endif

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _FN 1

#define KC_ KC_TRNS
#define _______ KC_TRNS

#define KC_FN1 MO(_FN)
#define KC_WD_L LCTL(KC_LEFT)
#define KC_WD_R LCTL(KC_RGHT)
#define KC_RTOG RGB_TOG
#define KC_RMOD RGB_MOD
#define KC_RHUI RGB_HUI
#define KC_RHUD RGB_HUD
#define KC_RSAI RGB_SAI
#define KC_RSAD RGB_SAD
#define KC_RVAI RGB_VAI
#define KC_RVAD RGB_VAD
#define KC_RST RESET
#define KC_CTLZ LCTL(KC_Z)
#define KC_CTLX LCTL(KC_X)
#define KC_CTLC LCTL(KC_C)
#define KC_CTLV LCTL(KC_V)
#define KC_ATAB LALT(KC_TAB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(
  //,----+----+----+----+----+----+----.    ,----+----+----+----+----+----+----.
      1  , 2  , 3  , 4  , 5  , 6  ,ESC ,     DEL , 7  , 8  , 9  , 0  ,MINS,EQL ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     RBRC, Q  , W  , E  , R  , T  ,TAB ,     BSPC, Y  , U  , I  , O  , P  ,LBRC,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     GRV , A  , S  , D  , F  , G  ,LALT,     CAPS, H  , J  , K  , L  ,SCLN,QUOT,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     BSLS, Z  , X  , C  , V  , B  ,LSFT,     RSFT, N  , M  ,COMM,DOT ,SLSH,ENT ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     INS ,PSCR,MENU,LGUI,LCTL,SPC ,FN1 ,     FN1 ,SPC ,RCTL,RALT,    ,    ,
  //`----+----+----+----+----+----+----'    `----+----+----+----+----+----+----'
  ),

  [_FN] = LAYOUT_kc(
  //,----+----+----+----+----+----+----.    ,----+----+----+----+----+----+----.
      F1 , F2 , F3 , F4 , F5 , F6 ,    ,         , F7 , F8 , F9 ,F10 ,F11 ,F12 ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,PGUP,WD_L, UP ,WD_R,    ,ATAB,         ,RMOD,RHUI,RSAI,RVAI,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,HOME,LEFT,DOWN,RGHT,    ,    ,         ,    ,RHUD,RSAD,RVAD,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,CTLZ,CTLX,CTLC,CTLV,    ,    ,         ,MUTE,VOLD,VOLU,    ,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,
  //`----+----+----+----+----+----+----'    `----+----+----+----+----+----+----'
  )

};

void led_set_user(uint8_t usb_led) {
  #ifdef RGBLIGHT_ENABLE
  if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
    rgblight_enable();
  } else {
    rgblight_disable();
  }
  #endif //RGBLIGHT_ENABLE
}
