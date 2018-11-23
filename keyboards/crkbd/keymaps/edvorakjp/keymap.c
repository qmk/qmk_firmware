#include QMK_KEYBOARD_H
#ifdef PROTOCOL_LUFA
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "oled.h"
#endif

#include "edvorakjp.h"

/*
 * enum custom_keycodes {
 *   KC_LOCK = NEW_SAFE_RANGE,
 * };
 */

#define KC_ KC_TRNS

#define KC_TMB1 LGUI_T(KC_TAB)
#define KC_TMB2 LSFT_T(KC_SPC)
#define KC_TMB3 TD(TD_LOWER) // act as LOWER when hold, as KC_LANG2(=English) when tapped
#define KC_TMB4 TD(TD_RAISE) // act as RAISE when hold, as KC_LANG1(=Japanese) when tapped
#define KC_TMB5 RCTL_T(KC_BSPC)
#define KC_TMB6 RALT_T(KC_ENT)
#define KC_TMB7 KC_DEL
#define KC_TMB8 RALT(KC_ENT)
#define KC_TMB9 LGUI(KC_TAB)

#define KC_RST  RESET
#define KC_DBUG DEBUG
#define KC_RTOG RGB_TOG
#define KC_EDJP EDVORAK
#define KC_QWER QWERTY

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_EDVORAK] = LAYOUT_kc(
  //|----+----+----+----+----+----|           |----+----+----+----+----+----|
     ESC ,QUOT,COMM,DOT , Y  , P  ,             F  , G  , R  , W  , Q  ,BSLS,
  //|----+----+----+----+----+----|           |----+----+----+----+----+----|
     EQL , A  , O  , E  , I  , U  ,             D  , T  , N  , S  , M  ,MINS,
  //|----+----+----+----+----+----|           |----+----+----+----+----+----|
     GRV ,SCLN, X  , C  , V  , Z  ,             B  , H  , J  , K  , L  ,SLSH,
  //`----+----+----+----+----+----+----| |----+----+----+----+----+----+----'
                         TMB1,TMB2,TMB3,  TMB4,TMB5,TMB6
  //                    `----+----+----' `----+----+----'
  ),

  [_EDVORAKJ1] = LAYOUT_kc(
  //|----+----+----+----+----+----|           |----+----+----+----+----+----|
         , AI , OU , EI ,    ,    ,                ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|           |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,                ,    ,    , Y  ,    ,    ,
  //|----+----+----+----+----+----|           |----+----+----+----+----+----|
         ,ANN ,ONN ,ENN ,INN ,UNN ,                ,    ,    ,    ,    ,    ,
  //`----+----+----+----+----+----+----| |----+----+----+----+----+----+----'
                             ,    ,    ,      ,    ,
  //                    `----+----+----' `----+----+----'
  ),

  [_EDVORAKJ2] = LAYOUT_kc(
  //|----+----+----+----+----+----|           |----+----+----+----+----+----|
         , AI , OU , EI ,    ,    ,                ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|           |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,                , Y  ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|           |----+----+----+----+----+----|
         ,ANN ,ONN ,ENN ,INN ,UNN ,                ,    ,    ,    ,    ,    ,
  //`----+----+----+----+----+----+----| |----+----+----+----+----+----+----'
                             ,    ,    ,      ,    ,
  //                    `----+----+----' `----+----+----'
  ),

  [_QWERTY] = LAYOUT_kc(
  //|----+----+----+----+----+----|           |----+----+----+----+----+----|
     TAB , Q  , W  , E  , R  , T  ,             Y  , U  , I  , O  , P  ,MINS,
  //|----+----+----+----+----+----|           |----+----+----+----+----+----|
     EQL , A  , S  , D  , F  , G  ,             H  , J  , K  , L  ,SCLN,QUOT,
  //|----+----+----+----+----+----|           |----+----+----+----+----+----|
     GRV , Z  , X  , C  , V  , B  ,             N  , M  ,COMM,DOT ,SLSH,BSLS,
  //`----+----+----+----+----+----+----| |----+----+----+----+----+----+----'
                             ,    ,    ,      ,    ,
  //                    `----+----+----' `----+----+----'
  ),

  [_LOWER] = LAYOUT_kc(
  //|----+----+----+----+----+----|           |----+----+----+----+----+----|
         ,    , 2  , 3  , 4  , 5  ,             6  , 7  , 8  , 9  ,    ,    ,
  //|----+----+----+----+----+----|           |----+----+----+----+----+----|
         , 1  ,EXLM, AT ,HASH,DLR ,            PERC,CIRC,AMPR,ASTR, 0  ,    ,
  //|----+----+----+----+----+----|           |----+----+----+----+----+----|
         ,    , LT ,LCBR,LPRN,LBRC,            RBRC,RPRN,RCBR, GT ,    ,    ,
  //`----+----+----+----+----+----+----| |----+----+----+----+----+----+----'
                             ,    ,    ,      ,TMB7,TMB8
  //                    `----+----+----' `----+----+----'
  ),

  [_RAISE] = LAYOUT_kc(
  //|----+----+----+----+----+----|           |----+----+----+----+----+----|
         , F1 , F2 , F3 , F4 , F5 ,             F6 , F7 , F8 , F9 ,F10 ,    ,
  //|----+----+----+----+----+----|           |----+----+----+----+----+----|
         ,F11 ,F12 ,PSCR,SLCK,PAUS,                ,HOME,PGDN,PGUP,END ,    ,
  //|----+----+----+----+----+----|           |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,                ,LEFT,DOWN, UP ,RGHT,    ,
  //|----+----+----+----+----+----+----| |----+----+----+----+----+----+----'
                         TMB9,    ,    ,      ,    ,
  //                    `----+----+----' `----+----+----'
  ),

  [_ADJUST] = LAYOUT_kc(
  //|----+----+----+----+----+----|           |----+----+----+----+----+----|
         ,    ,    ,   ,EXTOFF,   ,                ,EXTON,   ,    ,    ,    ,
  //|----+----+----+----+----+----|           |----+----+----+----+----+----|
         ,    ,    ,QWER,WIN ,RST ,            RTOG,MAC ,EDJP,    ,    ,    ,
  //|----+----+----+----+----+----|           |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,                ,    ,    ,    ,    ,    ,
  //`----+----+----+----+----+----+----| |----+----+----+----+----+----+----'
                             ,    ,    ,      ,    ,
  //                    `----+----+----' `----+----+----'
  )
};

#ifdef SSD1306OLED
void matrix_init_keymap(void) {
  //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
  iota_gfx_init(!has_usb());   // turns on the display
}

void matrix_scan_user(void) {
  iota_gfx_task();  // this is what updates the display continuously
}
#endif

#ifdef RGBLIGHT_EFFECT_STATIC_GRADIENT
uint32_t layer_state_set_keymap(uint32_t state) {
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
  switch (biton32(state)) {
    case _EDVORAKJ1:
    case _EDVORAKJ2:
      // _EDVORAKJ1 & J2 are same colored
      rgblight_sethsv_noeeprom_white();
      break;
    case _LOWER:
      rgblight_sethsv_noeeprom_red();
      break;
    case _RAISE:
      rgblight_sethsv_noeeprom_blue();
      break;
    case _ADJUST:
      rgblight_sethsv_noeeprom_green();
      break;
    default: //  for any other layers, or the default layer
      rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_GRADIENT + 3);
      rgblight_sethsv_noeeprom_red();
      break;
  }
  return state;
}
#endif
