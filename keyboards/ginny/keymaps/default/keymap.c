/* Good on you for modifying your layout! if you don't have
 * time to read the QMK docs, a list of keycodes can be found at
 * https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md
 */

#include QMK_KEYBOARD_H
#include "sten.h"

// "Layer" aliases
#define LNUM GRT
#define LQWE GRM
#define LZXC GRR
#define LSYM GRI

#define RNUM GLT
#define RQWE GLM
#define RASD GLR
#define RSYM GRI

//Fingers are named, Ginny Left Pinky, Ginny Right Middle, etc
// Chords are done with bitwise OR
// P(GRP | GLP,  SEND(KC_A));
uint32_t processQwerty(bool lookup) {
	P(GLP, 				SEND(KC_A));
	P(GLR, 				SEND(KC_S));
	P(GLM, 				SEND(KC_D));
	P(GLI, 				SEND(KC_F));
	P(GLT, 				SEND(KC_G));
	P(GRT, 				SEND(KC_H));
	P(GRI, 				SEND(KC_J));
	P(GRM, 				SEND(KC_K));
	P(GRR, 				SEND(KC_L));
	P(GRP, 				SEND(KC_SCLN));
	return 0;
}
// Blank template at the bottom
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT_ginny(
		STN_S1, STN_S2, STN_TL, STN_KL, STN_PL, STN_WL, STN_HL, STN_RL, STN_ST1, STN_ST2
)};

/*[0] = LAYOUT_ginny(
		KC_A, KC_B, KC_C, KC_D, KC_E, KC_0, KC_1, KC_2, KC_3, KC_4 
)};*/

// Don't fuck with this, thanks.
size_t keymapsCount  = sizeof(keymaps)/sizeof(keymaps[0]);
