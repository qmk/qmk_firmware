#include QMK_KEYBOARD_H

enum layer_names {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum custom_keycodes {
  LOWER = SAFE_RANGE,
  RAISE,
  ADJUST,
  GUSR,
  HGRP,
  CHUS,
};

#define KC_ KC_TRNS

#define KC_CAPW LGUI(LSFT(KC_3))        // Capture whole screen
#define KC_CPYW LGUI(LSFT(LCTL(KC_3)))  // Copy whole screen
#define KC_CAPP LGUI(LSFT(KC_4))        // Capture portion of screen
#define KC_CPYP LGUI(LSFT(LCTL(KC_4)))  // Copy portion of screen
#define KC_ESCC MT(MOD_LCTL, KC_ESC)
#define KC_LOWR LOWER
#define KC_RASE RAISE
#define KC_RST RESET
#define KC_BL_S BL_STEP

// Left and right shift as mot-tap square braces
#define KC_LSBR MT(MOD_LSFT, KC_LBRC)
#define KC_RSBR MT(MOD_RSFT, KC_RBRC)

// mod-tap shift/minus
#define KC_SMIN MT(MOD_LSFT, KC_MINS)

// Tap-toggle layers
#define KC_TT_L TT(1)
#define KC_TT_R TT(2)

#define KC_RGBM RGB_MOD
#define KC_RGBT RGB_TOG

#define KC_SLOK LGUI(LCTL(KC_Q)) // mojave lock screen
#define KC_GUSR GUSR // "gam info user" macro
#define KC_HGRP HGRP // "history | grep" macro
#define KC_CHUS CHUS // "thisisunsafe" chrome browser macro

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     GRV , 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,BSPC,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     TAB , Q  , W  , E  , R  , T  ,                Y  , U  , I  , O  , P  ,BSLS,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     ESC , A  , S  , D  , F  , G  ,                H  , J  , K  , L  ,SCLN,QUOT,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     LSBR, Z  , X  , C  , V  , B  ,TT_L,     TT_R, N  , M  ,COMM,DOT ,SLSH,RSBR,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       LCTL,SMIN,LGUI,         ENT ,SPC ,LALT
  //                  `----+----+----'        `----+----+----'
  ),

  [_LOWER] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     TILD,EXLM, AT ,HASH,DLR ,PERC,               CIRC,AMPR,ASTR,MINS,EQL ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,SLOK,    , UP ,    ,RGBT,                P7 , P8 , P9 , E  , F  ,LPRN,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     DEL ,    ,LEFT,DOWN,RGHT,GUSR,                P4 , P5 , P6 , C  , D  ,RPRN,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     BL_S,    ,    ,    ,HGRP,CHUS,    ,         , P1 , P2 , P3 , A  , B  ,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,         DOT , P0 ,COLN
  //                  `----+----+----'        `----+----+----'
  ),

  [_RAISE] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     F12 , F1 , F2 , F3 , F4 , F5 ,                F6 , F7 , F8 , F9 ,F10 ,F11 ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,RGBT,RGBM,    ,    ,    ,                   ,AMPR,MUTE,    ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,CAPW,CPYW,CAPP,CPYP,PGUP,               EQL ,HOME,VOLU,MRWD,MFFD,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,    ,    ,    ,    ,PGDN,    ,         ,PLUS,END ,VOLD,MPLY,MSTP,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             ,    ,
  //                  `----+----+----'        `----+----+----'
  ),

  [_ADJUST] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------.                          ,--------+--------+--------+--------+--------+--------.
      _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, _______,                            _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
      RESET  , DEBUG  , RGB_HUD, RGB_SAD, RGB_VAD, _______,                            _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------.        ,--------|--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
  //`--------+--------+--------+----+---+--------+--------+--------/        \--------+--------+--------+---+----+--------+--------+--------'
                                      _______, _______, _______,                  _______, _______, _______
  //                                `--------+--------+--------'                `--------+--------+--------'
  )

};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
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
    case GUSR:
      if (record->event.pressed) {
        SEND_STRING("gam info user ");
      }
      break;
    case HGRP:
      if (record->event.pressed) {
        SEND_STRING("history|grep ");
      }
      break;
    case CHUS:
      if (record->event.pressed) {
	SEND_STRING("thisisunsafe");
      }
      break;
  }
  return true;
}
