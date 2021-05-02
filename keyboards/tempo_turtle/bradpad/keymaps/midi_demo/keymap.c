#include QMK_KEYBOARD_H

#define _NATURAL 0
#define _SHARP 1
#define _FLAT 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_NATURAL] = LAYOUT( 
		MI_C, MI_BENDD, MI_BENDU, MI_G, \
		MI_D, MI_VELD,  MI_VELU,  MI_A, \
		MI_E, MI_TRNSD, MI_TRNSU, MI_B, \
		MI_F, MI_OCTD,  MI_OCTU,  MI_C,\
		     MO(_SHARP), MO(_FLAT)),
    [_SHARP] = LAYOUT( 
		MI_Cs, KC_TRNS, KC_TRNS, MI_Gs, \
		MI_Ds, KC_TRNS, KC_TRNS, MI_As, \
		MI_F , KC_TRNS, KC_TRNS, MI_C , \
		MI_Fs, KC_TRNS, KC_TRNS, MI_Cs,\
		     KC_TRNS, KC_TRNS),
    [_FLAT] = LAYOUT( 
		MI_B , KC_TRNS, KC_TRNS, MI_Gb, \
		MI_Db, KC_TRNS, KC_TRNS, MI_Ab, \
		MI_Eb, KC_TRNS, KC_TRNS, MI_Bb, \
		MI_E , KC_TRNS, KC_TRNS, MI_B,\
		     KC_TRNS, KC_TRNS),
};
