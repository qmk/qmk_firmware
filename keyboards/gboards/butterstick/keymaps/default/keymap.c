#include QMK_KEYBOARD_H

/* 	 	
 *  Key names are inherited from steno machines
 *  .-------------------------------------------------.
 *	| KQ | KW | KE | KR | KT | KY | KU | KI | KO | KP |
 *  |-------------------------------------------------|
 *	| KA | KS | KD | KF | KG | KH | KJ | KK | KL | KC |
 *  '-------------------------------------------------'
 */

// Function prefixes
#define MEDIA 	(KA | KS | KD | KF)
#define FUNCT 	(KA | KS | KE | KR)
#define MOVE	  (KQ | KW | KE | KR)
#define SYMB	  (KP | KC)
#define NUMA    (KD | KF)	
#define NUMB    (KJ | KK)	

#include "g/keymap_engine.h"


// Do not change QMK Layer 0! This is your main keyboard.
// Make your QMK modifications to the later layers, to add 
// keys/customize on the first layer modify processQwerty():
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_butter(
    KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P,
    KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_C
  ),
};


// Don't fuck with this, thanks.
size_t keymapsCount  = sizeof(keymaps)/sizeof(keymaps[0]);
