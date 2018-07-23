#include QMK_KEYBOARD_H

#define _MAIN 0
#define _FN 1

#define _______ KC_TRNS
#define KC_X0 LT(_FN, KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
<<<<<<< HEAD
  [_MAIN] = KC_KEYMAP(
     VOLU,MPLY,MPRV,PGUP,
     VOLD,MUTE,MNXT,PGDN
  ),

  [_FN] = KC_KEYMAP(
      F  ,    ,RHUI,    ,
     RTOG,RMOD,RHUD,    
=======
  [_MAIN] = LAYOUT(
     KC_VOLU, KC_MPLY, KC_MPRV, KC_PGUP,
     KC_VOLD, KC_MUTE, KC_MNXT, KC_PGDN
  ),

  [_FN] = LAYOUT(
     KC_F,    _______, RGB_HUI, _______,
     RGB_TOG, RGB_MOD, RGB_HUD, _______
>>>>>>> 1225120b92411f4fa1a9dc79af2fd85bd5aa6dcc
  )
};
