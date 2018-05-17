#include QMK_KEYBOARD_H

#define _MAIN 0
#define _FN 1

#define KC_ KC_TRNS

#define KC_CAPW LGUI(LSFT(KC_3))        // Capture whole screen
#define KC_CPYW LGUI(LSFT(LCTL(KC_3)))  // Copy whole screen
#define KC_CAPP LGUI(LSFT(KC_4))        // Capture portion of screen
#define KC_CPYP LGUI(LSFT(LCTL(KC_4)))  // Copy portion of screen
#define KC_X0 LT(_FN, KC_ESC)
#define KC_RTOG RGB_TOG
#define KC_RMOD RGB_MOD
#define KC_RHUI RGB_HUI
#define KC_RHUD RGB_HUD

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_MAIN] = LAYOUT_kc(
      F  , X0 ,LCTL,
      R  , D  , M  
  ),

  [_FN] = LAYOUT_kc(
      F  ,    ,RHUI,
     RTOG,RMOD,RHUD
  )
};
