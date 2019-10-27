/* Good on you for modifying your layout! if you don't have
 * time to read the QMK docs, a list of keycodes can be found at
 *
 * https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md
 *
 * There's also a template for adding new layers at the bottom of this file!
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

uint32_t processQwerty(bool lookup) {
	P(GRP, 				SEND(KC_A));
	P(GRR, 				SEND(KC_S));
	P(GRM, 				SEND(KC_D));
	P(GRI, 				SEND(KC_F));
	P(GRT, 				SEND(KC_G));
	P(GLT, 				SEND(KC_H));
	P(GLI, 				SEND(KC_J));
	P(GLM, 				SEND(KC_K));
	P(GLR, 				SEND(KC_L));
	P(GLP, 				SEND(KC_SCLN));
	return 0;
}
// Blank template at the bottom
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT_ginny(
		STN_S1, STN_S2, STN_TL, STN_KL, STN_PL, STN_WL, STN_HL, STN_RL, STN_ST1, STN_ST2
)};

// Don't fuck with this, thanks.
size_t keymapsCount  = sizeof(keymaps)/sizeof(keymaps[0]);
