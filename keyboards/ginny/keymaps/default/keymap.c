/* Welcome to ASETNIOP
 *
 * This is a very different layout based off this table
 * http://asetniop.com/combinations
 *
 * Unlike standard Asetniop there are a few concessions that must be
 * made. Namely we don't do partials and if a chord has multiple left/
 * right words we go with the most common of the two.
 *
 * Also note, All Combos _must_ be done through Command Mode! If you
 * use a combo enough add it to your dictionary in the USR section!
 *
 * Two 'layers' are avalible, CMD and USR. Just add these into a chord. 
 * You'll enter/exit these layers with SET_STICKY(CMD) and SET_STICKY(0)
 *
 * Note: The engine optimizes for the longest chord it can find, every
 * now and again this makes conflicts! If you have a better dictionary
 * or come up with improvements, please submit a PR!
 */

#define LANG en

#include QMK_KEYBOARD_H
#include "sten.h"

// Asetniop aliases, to Ginny Fingers
#define AA		GLP
#define AS		GLR
#define AE		GLM
#define AT		GLI
#define AN		GRI
#define AI		GRM
#define AO		GRR
#define AP		GRP

#define AL		GLT							// Left/Right thumbs
#define AR		GRT

#define NUM		RES1						// Sticky Layer 1
#define USR   RES2						// Sticky Layer 2
#define CMD		RES2 | RES1			// Sticky Layer 3

// Asetniop layout see above link
uint32_t processQwerty(bool lookup) {
	// These three are needed for numbers, commands and layering
	// These must be included before any other maps
	#include "gen/aset/layer-keymap.c"
	#include "gen/aset/cmd-keymap.c"
	#include "gen/aset/num-keymap.c"

	// ASETNIOP supports various languages, define the one you wish to include here
	// da, de, en, en-colemak, en-dvorak, es, fn, fr, hu, it, nl, nw, pl, pt, ro, sv, tr
	#include "gen/aset/en-keymap.c"

	// User defs
	P(USR | AA,											SEND_STRING("undefined User "));
	P(USR | AS,											SEND_STRING("undefined User "));
	P(USR | AE,											SEND_STRING("undefined User "));
	P(USR | AT,											SEND_STRING("undefined User "));
	P(USR | AN,											SEND_STRING("undefined User "));
	P(USR | AI,											SEND_STRING("undefined User "));
	P(USR | AO,											SEND_STRING("undefined User "));
	P(USR | AP,											SEND_STRING("undefined User "));
	P(USR | AR,											SEND_STRING("undefined User "));
	P(USR | AL,											SEND_STRING("undefined User "));

	// Quick Fires
	P(AR | AA | AS,									SEND_STRING("Undefined Quick Fire"));
	P(AR | AS | AE,									SEND_STRING("Undefined Quick Fire"));
	P(AR | AE | AT,									SEND_STRING("Undefined Quick Fire"));
	P(AR | AT | AN,									SEND_STRING("Undefined Quick Fire"));
	P(AR | AN | AI,									SEND_STRING("Undefined Quick Fire"));
	P(AR | AI | AO,									SEND_STRING("Undefined Quick Fire"));
	P(AR | AO | AP,									SEND_STRING("Undefined Quick Fire"));

	return 0;
}

// QMK layout, Make all your changesw in processQwerty!
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT_ginny(
		STN_S1, STN_S2, STN_TL, STN_KL, STN_PL, STN_WL, STN_HL, STN_RL, STN_ST1, STN_ST2
)};

// Don't fuck with this, thanks.
size_t keymapsCount  = sizeof(keymaps)/sizeof(keymaps[0]);
