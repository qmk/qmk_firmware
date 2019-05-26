#include QMK_KEYBOARD_H

#include "keymap_french_osx.h"
#include "keymap_bepo.h"
#include "sendstring_bepo.h"

extern keymap_config_t keymap_config;

#define _BEPO    0
#define _LOWER   1
#define _RAISE   2
#define _ADJUST 16

enum custom_keycodes {
  BEPO = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  ZO,
  ZI
};

#define KC_ KC_TRNS
#define _______ KC_TRNS

#define KC_LOWR LOWER
#define KC_RASE RAISE
#define KC_RST RESET
#define KC_BL_S BL_STEP
#define KC_DBUG DEBUG
#define KC_RTOG RGB_TOG
#define KC_RMOD RGB_MOD
#define KC_RHUI RGB_HUI
#define KC_RHUD RGB_HUD
#define KC_RSAI RGB_SAI
#define KC_RSAD RGB_SAD
#define KC_RVAI RGB_VAI
#define KC_RVAD RGB_VAD

#define KC_ZI    ZI
#define KC_ZO    ZO
#define COPY     RGUI(BP_C)
#define PASTE    RGUI(BP_V)
#define SAVE     RGUI(BP_S)
#define CTAB     RGUI(BP_TAB)
#define ALTSFT   RALT(KC_LSFT)
#define BP_TAB   KC_TAB
#define BP_RCTL  KC_RCTL
#define BP_RGUI  KC_RGUI
#define BP_LOWR  KC_LOWR
#define BP_BSPC  KC_BSPC
#define BP_ENT   KC_ENT
#define BP_RASE  KC_RASE
#define BP_SPC   KC_SPC
#define BP_RALT  KC_RALT
#define BP_WSH   MT(KC_LSHIFT, BP_W)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BEPO] = LAYOUT(
  //,------+--------+--------+--------+--------+--------.                    ,-------+--------+---------+--------+--------+---------.
    KC_ESC , BP_DQOT, BP_LGIL, BP_RGIL, BP_LPRN, BP_RPRN,                     BP_AT  , BP_PLUS, BP_MINUS, BP_SLSH, BP_ASTR, BP_EQUAL,
  //,------+--------+--------+--------+--------+--------.                    ,-------+--------+---------+--------+--------+---------.
    BP_TAB , BP_B   , BP_ECUT, BP_P   , BP_O   , BP_EGRV,                     BP_DCRC, BP_V   , BP_D    , BP_L   , BP_J   , BP_Z ,
  //,------+--------+--------+--------+--------+--------.                    ,-------+--------+---------+--------+--------+---------.
    BP_WSH , BP_A   , BP_U   , BP_I   , BP_E   , BP_COMM,                     BP_C   , BP_T   , BP_S    , BP_R   , BP_N   , BP_M,
  //,------+--------+--------+--------+--------+--------+---------. ,--------,-------+--------+---------+--------+--------+---------.
    KC_LSHIFT,BP_AGRV, BP_Y   , BP_X   , BP_DOT , BP_K   , BP_RASE,   BP_RCTL, BP_APOS, BP_Q   , BP_G    , BP_H   , BP_F   , BP_CCED,
  //,------+--------+--------+--------+--------+--------+---------. ,--------,-------+--------+---------+--------+--------+---------.
                                BP_RALT, BP_RASE, BP_LOWR,          RSFT(BP_SPC), BP_ENT , BP_BSPC
  ),

  [_LOWER] = LAYOUT(
  //,------+--------+--------+--------+--------+--------.                    ,-------+--------+---------+--------+--------+---------.
    _______, _______, _______, _______, _______, _______,                     _______, _______, _______  , _______, _______ , _______,
  //,------+--------+--------+--------+--------+--------.                    ,-------+--------+---------+--------+--------+---------.
    BP_DLR , BP_DQOT, BP_LGIL, BP_RGIL, BP_LPRN, BP_RPRN,                     BP_AT  , BP_PLUS, BP_MINUS, BP_SLSH, BP_ASTR, BP_EQUAL,
  //,------+--------+--------+--------+--------+--------.                    ,-------+--------+---------+--------+--------+---------.
    _______,_______ , _______ , _______ , KC_UP  ,_______  ,                  _______, _______ , _______ , _______, _______ ,BP_PERCENT,
  //,------+--------+--------+--------+--------+--------+---------. ,--------,-------+--------+---------+--------+--------+---------.
    _______, _______, _______ , KC_LEFT , KC_DOWN , KC_RIGHT,_______, _______,_______, _______ ,_______ , _______, _______ , _______,
  //,------+--------+--------+--------+--------+--------+---------. ,--------,-------+--------+---------+--------+--------+---------.
                                    BP_RALT, BP_RGUI, BP_LOWR,          SFT_T(BP_SPC), BP_ENT , BP_BSPC
  //                               +--------+-------+---------.       ,--------------+--------+--------                                
  ),

  [_LOWER] = KC_KEYMAP(
  //,----+----+----+----+----+----.                   ,----+----+----+----+----+----.
         ,    ,    ,    ,    ,LBRC,                    RBRC,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|                   |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,                        ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|                   |----+----+----+----+----+----|
         ,    , ZI , ZO , UP ,LCBR,                    RCBR,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----.         ,----|----+----+----+----+----+----|
         ,    ,    ,LEFT,DOWN,RIGHT,    ,             ,    ,    ,    ,    ,    ,    ,
  //`----+----+----+--+-+----+----+----/         \----+----+----+----+----+----+----'
                           ,SPC ,   ,              ESC ,    ,    
  //                  `----+----+----'             `----+----+----'
  ),

  [_RAISE] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                     _______, _______, _______  , _______, _______ , _______,
  //,------+--------+--------+--------+--------+--------.                    ,-------+--------+---------+--------+--------+---------.
    _______, _______, _______, _______, _______, _______,                     _______, _______, _______  , _______, _______ , _______,
  //,------+--------+--------+--------+--------+--------.                    ,-------+--------+---------+--------+--------+---------.
    _______, _______, SAVE   , COPY   , PASTE  , CTAB   ,                     _______, _______, _______  , _______, _______ , _______,
  //,------+--------+--------+--------+--------+--------+---------.  ,--------,-------+--------+---------+--------+--------+---------.
    _______, _______, _______, _______, BP_RALT, ALTSFT, _______,     _______, _______, _______ ,_______ , _______, _______ , _______,
  //,------+--------+--------+--------+--------+--------+---------.  ,--------,-------+--------+---------+--------+--------+---------.
                                    _______, _______, _______,         _______, _______, _______
  ),

  [_ADJUST] = LAYOUT(
    RESET  , _______, _______, _______, _______, _______,                     _______, _______, _______  , _______, _______ , _______,
  //,------+--------+--------+--------+--------+--------.                    ,-------+--------+---------+--------+--------+---------.
    _______, _______, _______, _______, _______, _______,                     _______, _______, _______  , _______, _______ , _______,
  //,------+--------+--------+--------+--------+--------.                    ,-------+--------+---------+--------+--------+---------.
    _______, _______, _______, _______, _______, _______,                     _______, _______, _______  , _______, _______ , _______,
  //,------+--------+--------+--------+--------+--------+---------.  ,--------,-------+--------+---------+--------+--------+---------.
    _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______ ,_______ , _______, _______ , _______,
  //,------+--------+--------+--------+--------+--------+---------.  ,--------,-------+--------+---------+--------+--------+---------.
                                    _______, _______, _______,         _______, _______, _______
  )

};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
    case BEPO:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_BEPO);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}

