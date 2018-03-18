#include "nano.h"

#define _MAIN 0
#define _FN 1

#define KC_ KC_TRNS
#define KC_X0 LT(_FN, KC_ESC)
#define KC_RTOG RGB_TOG
#define KC_RMOD RGB_MOD
#define KC_RHUI RGB_HUI
#define KC_RHUD RGB_HUD

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_MAIN] = KC_KEYMAP(
     VOLU,MPLY,MPRV,PGUP,
     VOLD,MUTE,MNXT,PGDN
  ),

  [_FN] = KC_KEYMAP(
      F  ,    ,RHUI,    ,
     RTOG,RMOD,RHUD,    
  )
};
