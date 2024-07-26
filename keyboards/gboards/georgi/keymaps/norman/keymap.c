/*
 * Good on you for modifying your layout, this is the most nonQMK layout you will come across
 * There are three modes, Steno (the default), QWERTY (Toggleable) and a Momentary symbol layer
 *
 * Don't modify the steno layer directly, instead add chords using the keycodes and macros
 * from sten.h to the layout you want to modify.
 *
 * Observe the comment above processQWERTY!
 *
 * http://docs.gboards.ca
 */

#include QMK_KEYBOARD_H
#include "sten.h"

// Proper Layers
#define FUNCT   (LSD | LK | LP | LH)
#define MEDIA   (LSD | LK | LW | LR)
#define MOVE    (LH | ST2)

/* Keyboard Layout
 * ,---------------------------------.    ,------------------------------.
 * | FN  | LSU | LFT | LP | LH | ST1 |    | ST3 | RF | RP | RL | RT | RD |
 * |-----+-----+-----+----+----|-----|    |-----|----+----+----+----+----|
 * | PWR | LSD | LK  | LW | LR | ST2 |    | ST4 | RR | RB | RG | RS | RZ |
 * `---------------------------------'    `------------------------------'
 *                   ,---------------,    .---------------.
 *                   | LNO | LA | LO |    | RE | RU | RNO |
 *                   `---------------'    `---------------'
 */

// YOU MUST ORDER THIS!
// Order your chords from longest to shortest!
// You can only use basic keycodes here!
//
// P() is just a wrapper to make your life easier.
//
// http://docs.gboards.ca
uint32_t processQwerty(bool lookup) {
	// Specials
	P( RT  | RS  | RD  | RZ | LNO,		SEND_STRING(VERSION); SEND_STRING(__DATE__));
	P( LNO | LA  | LO  | RE | RU,		SEND(KC_MPLY));
	P( ST1 | ST2 | ST3 | ST4,			SEND(KC_BSPC));

	// Thumb Chords
	P(  LA  | LO  | RE  | RU,			SEND(KC_CAPS));
	P(  LA  | RU,						SEND(KC_ESC));
	P( LO  | RE,						SEND(KC_LCTL));
	P( LNO | LA | RU,					SEND(KC_LCTL); SEND(KC_LSFT));
	P( LNO | LA | RE,					SEND(KC_LCTL); SEND(KC_LSFT); SEND(KC_LALT));

	// Mods
	P( RT | RD | RS | RZ,				SEND(KC_LGUI));
	P( RT | RD,						SEND(KC_LCTL));
	P( RS | RZ,						SEND(KC_LALT));
	P( LA | LNO,						SEND(KC_LCTL));
	P( LA | LO,						SEND(KC_LALT));
	P( LO,								SEND(KC_LSFT));

	// Function Layer
	P( FUNCT | RF | RR,					SEND(KC_F6));
	P( FUNCT | RP | RB,					SEND(KC_F7));
	P( FUNCT | RL | RG,					SEND(KC_F8));
	P( FUNCT | ST3 | ST4,				SEND(KC_F5));
  P( FUNCT| ST3,              SEND(KC_F1));
  P( FUNCT| ST4,              SEND(KC_F9));
	P( FUNCT | RF,						SEND(KC_F2));
	P( FUNCT | RP,						SEND(KC_F3));
	P( FUNCT | RL,						SEND(KC_F4));
	P( FUNCT | RR,						SEND(KC_F10));
	P( FUNCT | RG,						SEND(KC_F12));
	P( FUNCT | RB,						SEND(KC_F11));
  P( FUNCT | RD,            SEND(KC_RALT); SEND(KC_T); SEND(KC_H); SEND(KC_U); SEND(KC_P));
  P( FUNCT | RZ,            SEND(KC_RALT); SEND(KC_T); SEND(KC_H); SEND(KC_D); SEND(KC_N));
  P( FUNCT | RT,            SEND(KC_RALT); SEND(KC_S); SEND(KC_F));
  P( FUNCT | RS,            SEND(KC_LALT); SEND(KC_SPC));
  P( FUNCT | RE,            SEND(KC_LCTL); SEND(KC_LSFT); SEND(KC_ESC));
  P( FUNCT | RU,            SEND(KC_LCTL); SEND(KC_LSFT); SEND(KC_0));

	// Movement Layer
	P( MOVE | RF,						 SEND(KC_LGUI); SEND(KC_LSFT); SEND(KC_LEFT));
	P( MOVE | RP,						SEND(KC_UP));
	P( MOVE | RL,						SEND(KC_LGUI); SEND(KC_LSFT); SEND(KC_RGHT));
	P( MOVE | RT,						SEND(KC_LALT); SEND(KC_LCTL); SEND(KC_LGUI); SEND(KC_C));
	P( MOVE | ST3,						SEND(KC_PGUP));
	P( MOVE | ST4,						SEND(KC_PGDN));
  P( MOVE | RD,           SEND(KC_HOME));
  P( MOVE | RZ,           SEND(KC_END));
  P( MOVE | RG,            SEND(KC_RIGHT));
  P( MOVE | RB,            SEND(KC_DOWN));
  P( MOVE | RR,            SEND(KC_LEFT));
  P( MOVE | RS,            SEND(KC_LSFT); SEND(KC_LCTL); SEND(KC_LGUI); SEND(KC_T));
  P( MOVE | RE,            SEND(KC_LSFT); SEND(KC_LALT); SEND(KC_LGUI); SEND(KC_S));
  P( MOVE | RU,            SEND(KC_LSFT); SEND(KC_LCTL); SEND(KC_1));


	// Media Layer
	P( MEDIA | RF,						SEND(KC_MEDIA_PREV_TRACK));
	P( MEDIA | RP,						SEND(KC_MPLY));
	P( MEDIA | RL,						SEND(KC_MPLY));
	P( MEDIA | RT,						SEND(KC_MEDIA_NEXT_TRACK));
	P( MEDIA | RD,						SEND(KC_VOLU));
	P( MEDIA | RZ,						SEND(KC_VOLD));
	P( MEDIA | RS,						SEND(KC_MUTE));
  P( MEDIA | ST3,           SEND(KC_LALT); SEND(KC_LCTL); SEND(KC_LGUI); SEND(KC_4));
  P( MEDIA | ST4,           SEND(KC_LALT); SEND(KC_LCTL); SEND(KC_LGUI); SEND(KC_2));
  P( MEDIA | RR,            SEND(KC_LALT); SEND(KC_LCTL); SEND(KC_LGUI); SEND(KC_3));
  P( MEDIA | RB,            SEND(KC_LCTL); SEND(KC_LSFT); SEND(KC_GRV));
  P( MEDIA | RG,            SEND(KC_LCTL); SEND(KC_LSFT); SEND(KC_8));
  P( MEDIA | RE,            SEND(KC_RALT); SEND(KC_F); SEND(KC_I); SEND(KC_R); SEND(KC_E));
  P( MEDIA | RU,            SEND(KC_RALT); SEND(KC_T); SEND(KC_A); SEND(KC_D));

	// Mouse Keys and Printscreen
	P( LFT | LH,							CLICK_MOUSE(KC_MS_BTN1));
	P( LK | LR,							CLICK_MOUSE(KC_MS_BTN2));
	P( RF | RT,							SEND(KC_PSCR););

	// Number Row Left
	P( LNO | LSU,						SEND(KC_1));
	P( LNO | LFT,						SEND(KC_2));
	P( LNO | LP,						SEND(KC_3));
	P( LNO | LH,						SEND(KC_4));
	P( LNO | ST1,						SEND(KC_5));
	P( LNO | ST3,						SEND(KC_6));
	P( LNO | RF,						SEND(KC_7));
	P( LNO | RP,						SEND(KC_8));
	P( LNO | RL,						SEND(KC_9));
	P( LNO | RT,						SEND(KC_0));
	P( LNO | LA,						SEND(KC_5));
	P( LNO | RT,						SEND(KC_0));

  // Number Row Right
	P( RNO | LSU,						SEND(KC_1));
	P( RNO | LFT,						SEND(KC_2));
	P( RNO | LP,						SEND(KC_3));
	P( RNO | LH,						SEND(KC_4));
	P( RNO | ST1,						SEND(KC_5));
	P( RNO | ST3,						SEND(KC_6));
	P( RNO | RF,						SEND(KC_7));
	P( RNO | RP,						SEND(KC_8));
	P( RNO | RL,						SEND(KC_9));
	P( RNO | RT,						SEND(KC_0));
	P( RNO | LA,						SEND(KC_5));
	P( RNO | RT,						SEND(KC_0));

	// Specials
	P( LA | LNO,						SEND(KC_ESC));
	P( RU | RNO,						SEND(KC_TAB));
	P( RE | RU,							SEND(KC_LSFT); SEND(KC_SLSH));
	P( RD | RZ,							SEND(KC_ENT));
	P( RE,								SEND(KC_ENT));
	//P( RD,								SEND(KC_BSPC));
	P( LNO,								SEND(KC_BSPC));
  P( RD,								SEND(KC_DEL));
	P( LA,								SEND(KC_SPC));
	P( RU,								SEND(KC_SPC));
	P( RZ,								SEND(KC_ESC));
  //P( RNO,               REPEAT());

	// Letters
	P( LSU | LSD,						SEND(KC_A));
	P( LFT | LK,						SEND(KC_S));
	P( LP  | LW,						SEND(KC_E));
	P( LH  | LR,						SEND(KC_T));
	P( ST1 | ST2,						SEND(KC_G));
	P( ST3 | ST4,						SEND(KC_Y));
	P( RF  | RR,						SEND(KC_N));
	P( RT  | RS,						SEND(KC_H))
	P( RG  | RL,						SEND(KC_O));
	P( RP  | RB,						SEND(KC_I));
	P( LSU,								SEND(KC_Q));
	P( LSD,								SEND(KC_Z));
	P( LFT,								SEND(KC_W));
	P( LK,								SEND(KC_X));
	P( LP,								SEND(KC_D));
	P( LW,								SEND(KC_C));
	P( LH,								SEND(KC_F));
	P( LR,								SEND(KC_V));
	P( ST1,								SEND(KC_K));
	P( ST2,								SEND(KC_B));
	P( ST3,								SEND(KC_J));
	P( ST4,								SEND(KC_P));
	P( RF,								SEND(KC_U));
	P( RR,								SEND(KC_M));
	P( RP,								SEND(KC_R));
	P( RB,								SEND(KC_COMM));
	P( RL,								SEND(KC_L));
	P( RG,								SEND(KC_DOT));
	P( RT,								SEND(KC_SCLN));
	P( RS,								SEND(KC_SLSH));

	// Symbols and Numbers
	P( PWR | RE | RU,					SEND(KC_ENT));
	P( PWR | LA | LO,					SEND(KC_SPC));
	P( PWR | LP | LW,					SEND(KC_LSFT); SEND(KC_9));			// (
	P( PWR | LH | LR,					SEND(KC_LSFT); SEND(KC_0));			// )
	P( PWR | ST1 | ST2,					SEND(KC_GRV));						// `
	P( PWR | RD | RZ,					SEND(KC_ESC));
	P( PWR | LSU | LSD,					SEND(KC_LSFT); SEND(KC_3));			// #
	P( PWR | LFT | LK,					SEND(KC_LSFT); SEND(KC_4));			// $
	P( PWR | LSU,						SEND(KC_LSFT); SEND(KC_1));			// !
	P( PWR | LSD,						SEND(KC_LSFT); SEND(KC_5));			// %
	P( PWR | LFT,						SEND(KC_LSFT); SEND(KC_2));			// @
	P( PWR | LK,						SEND(KC_LSFT); SEND(KC_6));			// ^
	P( PWR | LP,						SEND(KC_LSFT); SEND(KC_LBRC));		// {
	P( PWR | LW,						SEND(KC_LBRC));
	P( PWR | LH,						SEND(KC_LSFT); SEND(KC_RBRC));		// }
	P( PWR | LR,						SEND(KC_RBRC));
	P( PWR | ST1,						SEND(KC_LSFT); SEND(KC_BSLS));		// |
	P( PWR | ST2,						SEND(KC_LSFT); SEND(KC_GRV));		// ~
	P( PWR | ST3,						SEND(KC_QUOT));
	P( PWR | ST4,						SEND(KC_LSFT); SEND(KC_QUOT));		// "
	P( PWR | RF,						SEND(KC_KP_PLUS));
	P( PWR | RR,						SEND(KC_LSFT); SEND(KC_7));			// &
	P( PWR | RP,						SEND(KC_MINS));
	P( PWR | RB,						SEND(KC_EQL));
	P( PWR | RL,						SEND(KC_SLSH));
	P( PWR | RG,						SEND(KC_LSFT); SEND(KC_MINS));
	P( PWR | RT,						SEND(KC_PAST));
	P( PWR | RS,						SEND(KC_DOT));
	P( PWR | RD,						SEND(KC_TAB));
	P( PWR | LA,						SEND(KC_LSFT); SEND(KC_SCLN));
	P( PWR | LO,						SEND(KC_BSLS));
	P( PWR | RE,						SEND(KC_SCLN));
	P( PWR | RU,						SEND(KC_BSLS));
  P( PWR | RZ,						SEND(KC_LSFT));

	return 0;
}

#define STENO_LAYER		0
#define GAMING			1
#define GAMING_2		2
#define MOVEMENT    3

// "Layers"
// Steno layer should be first in your map.
// When PWR | FN | ST3 | ST4 is pressed, the layer is increased to the next map. You must return to STENO_LAYER at the end.
// If you need more space for chords, remove the two gaming layers.

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// Main layer, everything goes through here
[STENO_LAYER] = LAYOUT_georgi(
STN_FN,  STN_S1, STN_TL, STN_PL, STN_HL, STN_ST1,       STN_ST3, STN_FR, STN_PR, STN_LR, STN_TR, STN_DR,
STN_PWR, STN_S2, STN_KL, STN_WL, STN_RL, STN_ST2,       STN_ST4, STN_RR, STN_BR, STN_GR, STN_SR, STN_ZR,
						 STN_N1, STN_A,  STN_O,			STN_E,   STN_U,  STN_N7)
,
// Gaming layer with Numpad, Very limited
[GAMING] = LAYOUT_georgi(
KC_LSFT, KC_Q, KC_W, KC_E, KC_R, KC_T,       KC_Y,   KC_U, KC_I, KC_O, KC_P,    KC_ENT,
KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G,       KC_H,   KC_J, KC_K, KC_L, KC_SCLN, KC_DQUO,
KC_LALT, KC_SPC, LT(GAMING_2, KC_ENT),	     KC_DEL, KC_ASTR,  TO(STENO_LAYER)),

[GAMING_2] = LAYOUT_georgi(
KC_LSFT, KC_1, KC_2, KC_3, KC_4, KC_5,       KC_6, KC_7, KC_8,  KC_9,  KC_0, KC_MINS,
KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B,       KC_N, KC_M, KC_LT, KC_GT, KC_QUES, KC_RSFT,
			  KC_LALT, KC_SPC, KC_NO,	             KC_DEL, KC_ASTR,  TO(STENO_LAYER)),

[MOVEMENT] = LAYOUT_georgi(
KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,KC_TRNS,       KC_PGUP, KC_TRNS, KC_UP,   KC_TRNS,  KC_TRNS, KC_HOME,
KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_PGDN, KC_LEFT, KC_DOWN, KC_RIGHT, KC_TRNS, KC_END,
			  KC_TRNS, KC_TRNS, KC_TRNS,	                        KC_TRNS, KC_TRNS, KC_TRNS)
};
// Don't fuck with this, thanks.
size_t keymapsCount  = ARRAY_SIZE(keymaps);
