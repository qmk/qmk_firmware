/* Good on you for modifying your layout! if you don't have
 * time to read the QMK docs, a list of keycodes can be found at
 * https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md
 *
 * This is a very different layout based off this table
 * http://asetniop.com/combinations
 *
 * Unlike standard Asetniop there are a few concessions that must be
 * made. Namely we don't do partials and if a chord has multiple left/
 * right words we go with the most common of the two.
 *
 * Also note, All Combos _must_ be done through Command Mode! If you
 * use a combo enough add it to your dictionary!
 *
 * Two 'layers' are avalible, CMD and USR. Just add these into a chord. 
 * You'll enter/exit these layers with SET_STICKY(CMD) and SET_STICKY(0)
 *
 * Note: The engine optimizes for the longest chord it can find, every
 * now and again this makes conflicts! If you have a better dictionary
 * or come up with improvements, please submit a PR!
 */


#include QMK_KEYBOARD_H
#include "sten.h"

// If this define is removed, word based completion will
// be disabled! If you need more space this is a good place to starj
#define USE_COMMON

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
	// Layer Switches 
	P(AA | AT | AN | AP,																SET_STICKY(NUM));
	P(AS | AE | AI | AO,																SET_STICKY(CMD));
	P(AA | AT | AN | AP | AS | AE | AI | AO,						SET_STICKY(USR));
	P(AA | AT | AN | AP | AS | AE | AI | AO | AL | AR,	SET_STICKY(USR));

	// Base defs
	P(AL,									SEND(KC_LSFT));
	P(AR,									SEND(KC_SPC));

	P(AA,									SEND(KC_A));
	P(AS,									SEND(KC_S));
	P(AE,									SEND(KC_E));
	P(AT,									SEND(KC_T));
	P(AN,									SEND(KC_N));
	P(AI,									SEND(KC_I));
	P(AO,									SEND(KC_O));
	P(AP,									SEND(KC_P));

	P(AT | AN,						SEND(KC_B));
	P(AA | AN,						SEND(KC_Q));
	P(AI | AP,						SEND(KC_LSFT); SEND(KC_1)); // !
	P(AS | AE,						SEND(KC_D));
	P(AT | AO,						SEND(KC_G));
	P(AA | AT,						SEND(KC_F));
	P(AN | AP,						SEND(KC_M));
	P(AS | AI,						SEND(KC_K));
	P(AS | AN,						SEND(KC_J));
	P(AI | AO,						SEND(KC_L));
	P(AA | AS,						SEND(KC_W));
	P(AE | AP,						SEND(KC_QUOT));
	P(AE | AT,						SEND(KC_R));
	P(AN | AI,						SEND(KC_R));
	P(AS | AT,						SEND(KC_C));
	P(AN | AO,						SEND(KC_U));
	P(AA | AE,						SEND(KC_X));
	P(AT | AP,						SEND(KC_BSPC));
	P(AT | AI,						SEND(KC_V));
	P(AE | AN,						SEND(KC_Y));
	P(AA | AI,						SEND(KC_Z));
	P(AO | AP,						SEND(KC_SCLN));
	P(AE | AI,						SEND(KC_COMM));
	P(AS | AO,						SEND(KC_DOT));
	P(AA | AP,						SEND(KC_SLSH));
	P(AA | AO,						SEND(KC_LSFT); SEND(KC_9)); // (
	P(AS | AP,						SEND(KC_LSFT); SEND(KC_0)); // (
	P(AE | AO,						SEND(KC_MINS));
	P(AA | AS | AE | AT,  SEND(KC_TAB));
	P(AN | AI | AO | AP,  SEND(KC_ENT));

	// Num Defs
	P(NUM | AA | AT | AN | AP,  SET_STICKY(0));
	P(NUM | AL,									SEND(KC_LSFT));
	P(NUM | AR,									SEND(KC_SPC));

	P(NUM | AA,									SEND(KC_1));
	P(NUM | AS,									SEND(KC_2));
	P(NUM | AE,									SEND(KC_3));
	P(NUM | AT,									SEND(KC_4));
	P(NUM | AN,									SEND(KC_7));
	P(NUM | AI,									SEND(KC_8));
	P(NUM | AO,									SEND(KC_9));
	P(NUM | AP,									SEND(KC_0));

	P(NUM | AE | AT,						SEND(KC_5));
	P(NUM | AT | AI,						SEND(KC_6));
	P(NUM | AA | AN,						SEND(KC_GRV));
	P(NUM | AT | AO,						SEND_STRING("<b>"));
	P(NUM | AA | AT,						SEND(KC_LBRC)); // {
	P(NUM | AN | AP,						SEND(KC_RBRC)); // {
	P(NUM | AS | AN,						SEND_STRING("<bq>"));
	P(NUM | AE | AP,						SEND(KC_QUOT));
	P(NUM | AE | AN,						SEND(KC_EQL));
	P(NUM | AS | AT,						SEND_STRING("<a>"));
	P(NUM | AN | AO,						SEND_STRING("<u>"));
	P(NUM | AT | AP,						SEND(KC_BSPC));
	P(NUM | AT | AI,						SEND_STRING("<i>"));
	P(NUM | AE | AN,						SEND_STRING("<p>"));
	P(NUM | AA | AI,						SEND(KC_BSLS));
	P(NUM | AI | AP,						SEND(KC_SCLN));
	P(NUM | AE | AI,						SEND(KC_COMM));
	P(NUM | AS | AO,						SEND(KC_DOT));
	P(NUM | AA | AP,						SEND(KC_SLSH));
	P(NUM | AA | AO,						SEND(KC_LBRC));
	P(NUM | AS | AP,						SEND(KC_RBRC));
	P(NUM | AE | AO,						SEND(KC_MINS));
	P(NUM | AA | AS | AE | AT,	SEND(KC_TAB));
	P(NUM | AN | AI | AO | AP,	SEND(KC_ENT));

	// Command defs
	
	// User defs

#ifdef USE_COMMON
	// Word Defs
	P(AA | AS | AE,									SEND_STRING("we "));
	P(AA | AE | AT,									SEND_STRING("are "));
	P(AA | AS | AE | AT,						SEND_STRING("were "));
	P(AA | AS | AN,									SEND_STRING("any "));
	P(AA | AS | AE | AN,						SEND_STRING("and "));
	P(AA | AS | AT | AN,						SEND_STRING("can "));
	P(AE | AT | AN,									SEND_STRING("be "));
	P(AS | AE | AI,									SEND_STRING("did "));
	P(AA | AS | AE | AI,						SEND_STRING("said "));
	P(AA | AS | AE | AT | AI,				SEND_STRING("first "));
	P(AS | AE | AN | AI,						SEND_STRING("she "));
	P(AA | AS | AE | AN | AI,				SEND_STRING("had "));
	P(AA | AT | AN | AI,						SEND_STRING("that "));
	P(AS | AT | AN | AI,						SEND_STRING("this "));
	P(AA | AE | AT | AN | AI,				SEND_STRING("with "));
	P(AE | AT | AN | AI,						SEND_STRING("the "));
	P(AA | AS | AT | AN | AI,				SEND_STRING("have "));
	P(AS | AE | AT | AN | AI,				SEND_STRING("these "));
	P(AA | AS | AE | AT | AN | AI,	SEND_STRING("where "));
	P(AS | AE | AO,									SEND_STRING("do "));
	P(AA | AT | AO,									SEND_STRING("of "));
	P(AA | AS | AT | AO,						SEND_STRING("two "));
	P(AE | AT | AO,									SEND_STRING("or "));
	P(AA | AE | AT | AO,						SEND_STRING("for "));
	P(AS | AE | AT | AO,						SEND_STRING("good "));
	P(AE | AN | AO,									SEND_STRING("us "));
	P(AA | AS | AN | AO,						SEND_STRING("now "));
	P(AE | AN | AO,									SEND_STRING("you "));
	P(AA | AS | AE | AN | AO,				SEND_STRING("down "));
	P(AT | AN | AO,									SEND_STRING("but "));
	P(AA | AT | AN | AO,						SEND_STRING("about "));
	P(AS | AT | AN | AO,						SEND_STRING("just "));
	P(AE | AT | AN | AO,						SEND_STRING("your "));
	P(AA | AE | AT | AN | AO,				SEND_STRING("before "));
	P(AA | AS | AE | AT | AN | AO,	SEND_STRING("because "));
	P(AO | AP ,											SEND_STRING("I "));
	P(AA | AI | AN ,								SEND_STRING("all "));
	P(AA | AS | AI | AO,						SEND_STRING("will "));
	P(AS | AE | AI | AO,						SEND_STRING("like "));
	P(AA | AS | AE | AI | AO,				SEND_STRING("well "));
	P(AE | AT | AI | AO,						SEND_STRING("over "));
	P(AA | AS | AN | AO | AI,				SEND_STRING("how "));
	P(AE | AN | AI | AO,						SEND_STRING("only "));
	P(AA | AS | AE | AN | AI | AO,	SEND_STRING("would "));
	P(AT | AN | AI | AO,						SEND_STRING("into "));
	P(AE | AT | AN | AI | AO,				SEND_STRING("other "));
	P(AS | AE | AT | AN | AI | AO,	SEND_STRING("could "));
	P(AA | AN | AP,									SEND_STRING("man "));
	P(AE | AN | AP,									SEND_STRING("my "));
	P(AA | AS | AE | AN | AP,				SEND_STRING("made "));
	P(AN | AI | AP,									SEND_STRING("him "));
	P(AA | AS | AE | AN | AI | AP,	SEND_STRING("make "));
	P(AE | AT | AN | AI | AP,				SEND_STRING("them "));
	P(AN | AO | AP,									SEND_STRING("up "));
#endif

	// Extras
	//P(AS | AE | AT,							SEND_STRING("set "));
	//P(AA | AS | AT,							SEND_STRING("fact "));
	//P(AA | AS | AN,							SEND_STRING("san "));
	//P(AS | AE | AN,							SEND_STRING("need "));
	return 0;
}

// QMK layout, Make all your changesw in processQwerty!
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT_ginny(
		STN_S1, STN_S2, STN_TL, STN_KL, STN_PL, STN_WL, STN_HL, STN_RL, STN_ST1, STN_ST2
)};

// Don't fuck with this, thanks.
size_t keymapsCount  = sizeof(keymaps)/sizeof(keymaps[0]);
