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
#include "keymap_steno.h"
#define IGNORE_MOD_TAP_INTERRUPT

// Steno Layers
#define FUNCT	( LSD | LK | LP | LH )
#define MEDIA	( LSD | LK | LW | LR )
#define MOVE	( LSD | LK )
#define NUM		( PWR )
#define SYM		( RZ )

// Keys and chords that, once they appear, are added to every subsequent partial chord
// until the whole thing is sent.
uint32_t stenoLayers[] = {NUM, SYM, MOVE, MEDIA, FUNCT};

// QMK Layers
#define STENO_LAYER   0
#define GAMING		  1
#define GAMING_2	  2

/* Keyboard Layout
 * ,---------------------------------.	  ,------------------------------.
 * | FN  | LSU | LFT | LP | LH | ST1 |	  | ST3 | RF | RP | RL | RT | RD |
 * |-----+-----+-----+----+----|-----|	  |-----|----+----+----+----+----|
 * | PWR | LSD | LK  | LW | LR | ST2 |	  | ST4 | RR | RB | RG | RS | RZ |
 * `---------------------------------'	  `------------------------------'
 *					 ,---------------,	  .---------------.
 *					 | LNO | LA | LO |	  | RE | RU | RNO |
 *					 `---------------'	  `---------------'
 */

// Note: You can only use basic keycodes here!
//
// P() is just a wrapper to make your life easier.
// PC() applies the mapping to all of the StenoLayers. For overloading, define these last.
//
// FN is unavailable. That is reserved for system use.
// Chords containing PWR are always available, even in steno mode.
//
// http://docs.gboards.ca
uint32_t processQwerty(bool lookup) {
	// Special keys
	P( RT  | RS  | RD  | RZ | LNO,		SEND_STRING(VERSION); SEND_STRING(__DATE__));
	P( LFT | LK  | LP  | LW,			REPEAT());

	// Mouse Keys
	/* P( LO  | LSD | LK,	CLICK_MOUSE(KC_MS_BTN2)); */
	/* P( LO  | LR  | LW,	CLICK_MOUSE(KC_MS_BTN1)); */


/* Function layer
 * ,-----------------------------------,    ,-----------------------------------,
 * |     |     |     | NCTFUNCTF |     |    |     | F1  | F2  | F3  | F4  |     |
 * |     +     +     +     +     +     |    |     + F5  + F6  + F7  + F8  +     |
 * |     | FUNCTFUNC |     |     |     |    |     | F9  | F10 | F11 | F12 |     |
 * `-----+-----+-----+-----+-----+-----'    `-----+-----+-----+-----+-----+-----'
*/
	P( FUNCT | RF,			SEND(KC_F1));
	P( FUNCT | RP,			SEND(KC_F2));
	P( FUNCT | RL,			SEND(KC_F3));
	P( FUNCT | RT,			SEND(KC_F4));

	P( FUNCT | RF | RR,		SEND(KC_F5));
	P( FUNCT | RP | RB,		SEND(KC_F6));
	P( FUNCT | RL | RG,		SEND(KC_F7));
	P( FUNCT | RT | RS,		SEND(KC_F8));

	P( FUNCT | RR,			SEND(KC_F9));
	P( FUNCT | RG,			SEND(KC_F10));
	P( FUNCT | RB,			SEND(KC_F11));
	P( FUNCT | RS,			SEND(KC_F12));


/* Movement layer
 * ,-----------------------------------,    ,-----------------------------------,
 * |     |     |     |     |     |     |    |     | <-  |  ↓  |  ↑  | ->  |     |
 * |     +     +     +     +     +     |    |     +     +     +     +     +     |
 * |     | MOVEMOVEM |     |     |     |    |     | Hm  | PgD | PgU | End |     |
 * `-----+-----+-----+-----+-----+-----'    `-----+-----+-----+-----+-----+-----'
*/
	P( MOVE | RF,			SEND(KC_LEFT));
	P( MOVE | RP,			SEND(KC_DOWN));
	P( MOVE | RL,			SEND(KC_UP));
	P( MOVE | RT,			SEND(KC_RIGHT));

	P( MOVE | RR,			SEND(KC_HOME));
	P( MOVE | RB,			SEND(KC_PGDN));
	P( MOVE | RG,			SEND(KC_PGUP));
	P( MOVE | RS,			SEND(KC_END));


/* Media Layer
 * ,-----------------------------------,    ,-----------------------------------,
 * |     |     |     |     |     |     |    |     |Prev |Play | PLY |Next | VolU|
 * |     +     +     +     +     +     |    |     +     +     +     +     +     |
 * |     | MEDIAMEDIAMEDIAMEDIAM |     |    |     |     |     |     |Mute | VolD|
 * `-----+-----+-----+-----+-----+-----'    `-----+-----+-----+-----+-----+-----'
*/
	P( MEDIA | RF,			SEND(KC_MPRV));
	P( MEDIA | RP,			SEND(KC_MPLY));
	P( MEDIA | RL,			SEND(KC_MPLY));
	P( MEDIA | RT,			SEND(KC_MNXT));
	P( MEDIA | RD,			SEND(KC_VOLU));

	P( MEDIA | RS,			SEND(KC_MUTE));
	P( MEDIA | RZ,			SEND(KC_VOLD));


/* Numbers
 * ,-----------------------------------,    ,-----------------------------------,
 * |     |     |  a  |  b  |  c  |     |    |  :  |  1  |  2  |  3  |  .  |     |
 * |     +     +  d  +  e  +  f  +     |    |  0  +  4  +  5  +  6  +  -  +     |
 * | NUM |     |     |     |     |     |    |     |  7  |  8  |  9  |  0  |     |
 * `-----+-----+-----+-----+-----+-----'    `-----+-----+-----+-----+-----+-----'
*/
	P( NUM | LFT,			SEND(KC_A));
	P( NUM | LP,			SEND(KC_B));
	P( NUM | LH,			SEND(KC_C));
	P( NUM | LK,			SEND(KC_D));
	P( NUM | LW,			SEND(KC_E));
	P( NUM | LR,			SEND(KC_F));

	// Right hand
	P( NUM | ST3,			SEND_STRING(":"));
	P( NUM | RF,			SEND(KC_1));
	P( NUM | RP,			SEND(KC_2));
	P( NUM | RL,			SEND(KC_3));
	P( NUM | RT,			SEND(KC_DOT));

	P( NUM | ST3 | ST4,		SEND(KC_0));
	P( NUM | RF  | RR,		SEND(KC_4));
	P( NUM | RP  | RB,		SEND(KC_5));
	P( NUM | RG  | RL,		SEND(KC_6));
	P( NUM | RT  | RS,		SEND(KC_MINUS));

	P( NUM | RR,			SEND(KC_7));
	P( NUM | RB,			SEND(KC_8));
	P( NUM | RG,			SEND(KC_9));
	P( NUM | RS,			SEND(KC_0));


/* Symbols
 * ,-----------------------------------,    ,-----------------------------------,
 * |     |  `  |  [  |  {  |  (  |  <  |    |  >  |  )  |  }  |  ]  |  ?  |     |
 * |     +  ~  +  -  +  '  +  :  +  _  |    |  \  +  =  +  "  +  +  +  ?  +     |
 * |     |  !  |  @  |  #  |  $  |  %  |    |  |  |  ^  |  &  |  *  |  ?  | SYM |
 * `-----+-----+-----+-----+-----+-----'    `-----+-----+-----+-----+-----+-----'
*/
	// Left hand
	P( SYM | LSU,			SEND(KC_GRV));
	P( SYM | LFT,			SEND(KC_LBRC));
	P( SYM | LP,			SEND_STRING("{"));
	P( SYM | LH,			SEND_STRING("("));
	P( SYM | ST1,			SEND_STRING("<"));

	P( SYM | LSU | LSD,		SEND_STRING("~"));
	P( SYM | LFT | LK,		SEND(KC_MINS));
	P( SYM | LP  | LW,		SEND(KC_QUOTE));
	P( SYM | LH  | LR,		SEND_STRING(":"));
	P( SYM | ST1 | ST2,		SEND_STRING("_"));

	P( SYM | LSD,			SEND_STRING("!"));
	P( SYM | LK,			SEND_STRING("@"));
	P( SYM | LW,			SEND_STRING("#"));
	P( SYM | LR,			SEND_STRING("$"));
	P( SYM | ST2,			SEND_STRING("%"));

	// Right hand
	P( SYM | ST3,			SEND_STRING(">"));
	P( SYM | RF,			SEND_STRING(")"));
	P( SYM | RP,			SEND_STRING("}"));
	P( SYM | RL,			SEND_STRING("]"));
	P( SYM | RT,			SEND_STRING("?"));

	P( SYM | ST3 | ST4,		SEND(KC_BACKSLASH));
	P( SYM | RF  | RR,		SEND(KC_EQUAL));
	P( SYM | RP  | RB,		SEND_STRING("\""));
	P( SYM | RG  | RL,		SEND_STRING("+"));
	P( SYM | RT  | RS,		SEND_STRING("?"));

	P( SYM | ST4,			SEND_STRING("|"));
	P( SYM | RR,			SEND_STRING("^"));
	P( SYM | RB,			SEND_STRING("&"));
	P( SYM | RG,			SEND_STRING("*"));
	P( SYM | RS,			SEND_STRING("?"));


/* Letters
 * ,-----------------------------------,    ,-----------------------------------,
 * |     |  Q  |  W  |  F  |  P  |  B  |    |  J  |  L  |  U  |  Y  |  ;  | ctl |
 * +-----+- A -+- R -+- S -+- T -+- G -|    |- M -+- N -+- E -+- I -+- O -+-----|
 * | bsp |  Z  |  X  |  C  |  D  |  V  |    |  K  |  H  |  ,  |  .  |  /  | del |
 * `-----+-----+-----+-----+-----+-----'    `-----+-----+-----+-----+-----+-----'
 *					   ,---------------,    .---------------.
 *					   | alt | ent|shfr|    | spc| gui| alt |
 *					   `---------------'    `---------------'
*/
	// Left hand
	P( LSU,					SEND(KC_Q));
	P( LFT,					SEND(KC_W));
	P( LP,					SEND(KC_F));
	P( LH,					SEND(KC_P));
	P( ST1,					SEND(KC_B));

	P( LSU | LSD,			SEND(KC_A));
	P( LFT | LK,			SEND(KC_R));
	P( LP  | LW,			SEND(KC_S));
	P( LH  | LR,			SEND(KC_T));
	P( ST1 | ST2,			SEND(KC_G));

	P( LSD,					SEND(KC_Z));
	P( LK,					SEND(KC_X));
	P( LW,					SEND(KC_C));
	P( LR,					SEND(KC_D));
	P( ST2,					SEND(KC_V));

	// Right hand
	P( ST3,					SEND(KC_J));
	P( RF,					SEND(KC_L));
	P( RP,					SEND(KC_U));
	P( RL,					SEND(KC_Y));
	P( RT,					SEND(KC_SCLN));

	P( ST3 | ST4,			SEND(KC_M));
	P( RF  | RR,			SEND(KC_N));
	P( RP  | RB,			SEND(KC_E));
	P( RG  | RL,			SEND(KC_I));
	P( RT  | RS,			SEND(KC_O));

	P( ST4,					SEND(KC_K));
	P( RR,					SEND(KC_H));
	P( RB,					SEND(KC_COMM));
	P( RG,					SEND(KC_DOT));
	P( RS,					SEND(KC_SLSH));

	// Thumb Chords and modifiers
	//
	PC( LNO | RNO | LA | RU,		SEND(KC_LCTL); SEND(KC_LSFT));
	PC( LNO | LA  | RE,				SEND(KC_LCTL); SEND(KC_LSFT); SEND(KC_LALT));

	// overrides
	P( PWR | LO,			SEND(KC_LSFT); SEND(KC_BSPC));
	P( PWR | RD,			SEND(KC_LCTL); SEND(KC_BSPC));
	P( RZ | RD,				SEND(KC_LCTL); SEND(KC_DEL));

	PC( LNO | LA | LO,		SEND(KC_LSFT); SEND(KC_ESC));
	PC( LA | LO,			SEND(KC_ESC));
	PC( LNO,				SEND(KC_LALT));
	PC( LA,					SEND(KC_ENT));
	PC( LO,					SEND(KC_LSFT));

	PC( RNO,				SEND(KC_RALT));
	PC( RE | RU,			SEND(KC_TAB));
	PC( RE,					SEND(KC_SPC));
	PC( RU,					SEND(KC_LGUI));
   
	PC( PWR,				SEND(KC_BSPC));
	PC( RD,					SEND(KC_LCTL));
	P( RZ,					SEND(KC_DEL));

	return 0;
}

// "Layers"
// Steno layer should be first in your map.
// When PWR | FN | ST3 | ST4 is pressed, the layer is increased to the next map. You must return to STENO_LAYER at the end.
// If you need more space for chords, remove the two gaming layers.
// Note: If using NO_ACTION_TAPPING, LT will not work!

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	// Main layer, everything goes through here
	[STENO_LAYER] = LAYOUT_georgi(
			STN_FN,  STN_S1,  STN_TL,  STN_PL,	STN_HL,  STN_ST1,		STN_ST3, STN_FR,  STN_PR,  STN_LR,	STN_TR,  STN_DR,
			STN_PWR, STN_S2,  STN_KL,  STN_WL,	STN_RL,  STN_ST2,		STN_ST4, STN_RR,  STN_BR,  STN_GR,	STN_SR,  STN_ZR,
								   STN_N1,		STN_A,	 STN_O,			STN_E,	 STN_U,   STN_N7
	),
	// Gaming layer with Numpad, Very limited
	[GAMING] = LAYOUT_georgi(
		KC_LSFT, KC_Q,	  KC_W,    KC_E,	KC_R,	 KC_T,						 KC_Y,	  KC_U,    KC_I,	KC_O,	 KC_P,	  KC_ENT,
		KC_LCTL, KC_A,	  KC_S,    KC_D,	KC_F,	 KC_G,						 KC_H,	  KC_J,    KC_K,	KC_L,	 KC_SCLN, KC_DQUO,
								   KC_LALT, KC_SPC,  LT(GAMING_2, KC_ENT),		 KC_DEL,  KC_ASTR, TO(STENO_LAYER)
	),

	[GAMING_2] = LAYOUT_georgi(
		KC_LSFT, KC_1,	  KC_2,    KC_3,	KC_4,	 KC_5,			KC_6,	 KC_7,	  KC_8,    KC_9,	KC_0,	 KC_MINS,
		KC_LCTL, KC_Z,	  KC_X,    KC_C,	KC_V,	 KC_B,			KC_N,	 KC_M,	  KC_LT,   KC_GT,	KC_QUES, KC_RSFT,
								   KC_LALT, KC_SPC,  KC_ENT,		KC_DEL,  KC_ASTR, TO(STENO_LAYER)
	)
};

// Don't fuck with this, thanks.
size_t keymapsCount  = ARRAY_SIZE(keymaps);
size_t stenoLayerCount = ARRAY_SIZE(stenoLayers);
