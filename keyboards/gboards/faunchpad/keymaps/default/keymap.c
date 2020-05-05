#include QMK_KEYBOARD_H
// Chord Prefixes
#define MEDIA 	( FP11 | FP12 )
#define MOVE		( FP01 | FP11 )
#define NUM			( FP04 | FP14 )

#include "g/keymap_engine.h"

/* 	 	
 *  .---------------------------.
 *	| FP01 | FP02 | FP03 | FP04 | 
 *  |---------------------------|
 *	| FP11 | FP12 | FP13 | FP14 | 
 *  '---------------------------'
 */

// Don't edit your keymap here! Do it in your dicts/ !
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_faunch( 	KC_1,  KC_2,  KC_3,  KC_4,
  										  KC_5,  KC_6,  KC_7,  KC_8)
};

// Don't fuck with this, thanks.
size_t keymapsCount  = sizeof(keymaps)/sizeof(keymaps[0]);
