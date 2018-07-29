#include "chocopad.h"

#define _BASE 0
#define _FN1 1
#define _FN2 2

// Fillers to make layering more clear
#define KC_ KC_TRNS
#define KC_XX KC_NO

#define KC_L1 LT(1, KC_P0)
#define KC_L2 LT(2, KC_SPC)
#define KC_RST RESET
#define KC_BSTP BL_STEP
#define KC_RTOG RGB_TOG
#define KC_RMOD RGB_MOD
#define KC_RHUI RGB_HUI
#define KC_RHUD RGB_HUD
#define KC_RSAI RGB_SAI
#define KC_RSAD RGB_SAD
#define KC_RVAI RGB_VAI
#define KC_RVAD RGB_VAD
#define KC_MAC1 ADMIN
#define KC_MAC2 SMSPC
#define KC_M192 M192
#define KC_M255 M255

enum custom_keycodes {
  NUMPAD = SAFE_RANGE,
  ADMIN,
  SMSPC,
  M192,
  M255
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = KC_KEYMAP(
  //,----+----+----+----.
      P7 , P8 , P9 ,BSPC,
  //|----+----+----+----|
      P4 , P5 , P6 ,TAB ,
  //|----+----+----+----|
      P1 , P2 , P3 ,PENT,
  //|----+----+----+----|
      L1 , L2 ,PDOT,PSLS
  //`----+----+----+----'
  ),

  [_FN1] = KC_KEYMAP(
  //,----+----+----+----.
     ESC ,MAC1,MAC2,DEL ,
  //|----+----+----+----|
     LEFT,DOWN, UP ,RGHT,
  //|----+----+----+----|
     M192,M255, XX , XX ,
  //|----+----+----+----|
         , XX ,    , XX
  //`----+----+----+----'
  ),

  [_FN2] = KC_KEYMAP(
  //,----+----+----+----.
     RST , XX , XX , XX ,
  //|----+----+----+----|
     RTOG,RHUI,RSAI,RVAI,
  //|----+----+----+----|
     RMOD,RHUD,RSAD,RVAD,
  //|----+----+----+----|
     BSTP,    , XX , XX
  //`----+----+----+----'
  )

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ADMIN:
      if (record->event.pressed) {
	SEND_STRING("Administrator");
      }
      return false;
      break;
    case SMSPC:
      if (record->event.pressed) {
	SEND_STRING("Simspace1!");
      }
      return false;
      break;
    case M192:
      if (record->event.pressed) {
	SEND_STRING("192.168.");
      }
      return false;
      break;
    case M255:
      if (record->event.pressed) {
	SEND_STRING("255");
      }
      return false;
      break;
  }
  return true;
};
