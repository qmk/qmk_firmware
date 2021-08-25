#include "C64.h"

// Fillers to make layering more clear
#define _______ KC_TRNS
#define ___T___ KC_TRNS
#define XXXXXXX KC_NO

// Layer shorthand
#define _QW 	0
#define _ALT 	1
#define _SHFT 	2

// CHANGED 0603 DW TO EXPERIMENT WITH JOYSTICK
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
*|	1		  |	3		  |	5	|	7	|	9	|	+	|	£		  |	DEL		|		    	|																			
*|	<   	|	W		  |	R	|	Y	|	I	|	P	|	*		  |	ENT		|		    	|																		
*|	CTRL	|	A		  |	D	|	G	|	J	|	L	|	;		  |	RIGHT	|		    	|																			
*|	PAUSE	|	LSFT	|	X	|	V	|	N	|	,	|	/		  |	DOWN	|		    	|																			
*|	SPACE	|	Z		  |	C	|	B	|	M	|	.	|	RSFT	|	F1		|		  	  |																			
*|	WIN		|	S		  |	F	|	H	|	K	|	:	|	=		  |	F3		|			    |																			
*|	Q		  |	E		  |	T	|	U	|	O	|	@	|	^		  |	F5		|			    |																			
*|	2		  |	4		  |	6	|	8	|	0	|	-	|	HOME	|	F7		|			    |																			
*|			  |			  |		|		|		|		|			  |			  |	RESTO?	|
*/ 
	
[_QW] = { /* QWERTY */
  { KC_1,    	    KC_3,    	  KC_5,    KC_7,    	KC_9,    KC_PLUS, 	KC_HASH, 	KC_DEL,   KC_UP 	  },
  { KC_KP_1, 	    KC_W,    	  KC_R,    KC_Y,    	KC_I,    KC_P,    	KC_ASTR, 	KC_ENT,   KC_DOWN 	},
  { KC_LCTL, 	    KC_A,    	  KC_D,    KC_G,    	KC_J,    KC_L,    	KC_SCLN, 	KC_RIGHT, KC_LEFT 	},
  { KC_ESC,  	    MO(_SHFT),  KC_X,    KC_V,    	KC_N,    KC_COMM, 	KC_SLSH, 	KC_DOWN,  KC_RIGHT 	},
  { KC_SPC,  	    KC_Z,    	  KC_C,    KC_B,    	KC_M,    KC_DOT,  	KC_LSFT, 	KC_F1,    KC_SPC 	  },
  { KC_LGUI, 	    KC_S,    	  KC_F,    KC_H,    	KC_K,    S(KC_SCLN),KC_EQL,		KC_F3,    KC_ENT 	  },
  { KC_Q,    	    KC_E,    	  KC_T,    KC_U,    	KC_O,    S(KC_QUOT),KC_CIRC, 	KC_F5,    _______ 	},
  { KC_2,    	    KC_4,    	  KC_6,    KC_8,    	KC_0,    KC_MINS, 	KC_HOME, 	KC_F7,    _______ 	},
  { KC_UP, 		    KC_DOWN, 	  KC_LEFT, KC_RIGHT, 	KC_SPC,  KC_ENT, 	  _______, 	_______,  KC_TAB  	}
 },


 
 [_SHFT] = { /* SHIFT */
  { S(KC_1), 	      KC_NUHS, 	S(KC_5), KC_QUOT, S(KC_0), KC_KP_MINUS, 	  _______, 	  KC_LOPT   , _______ },
  { S(KC_COMM), 	  S(KC_W), 	S(KC_R), S(KC_Y), S(KC_I), S(KC_P), 	      _______, 	  _______   , _______ },
  { _______, 	      S(KC_A), 	S(KC_D), S(KC_G),	S(KC_J), S(KC_L),   	    KC_RBRC, 	  KC_LEFT   , _______ },
  { S(KC_ESC),	    _______, 	S(KC_X), S(KC_V),	S(KC_N), S(KC_COMM),      S(KC_SLSH), KC_UP     , _______ },
  { _______, 	      S(KC_Z), 	S(KC_C), S(KC_B),	S(KC_M), S(KC_DOT),       _______, 	  KC_F2     , _______ },
  { S(KC_LGUI),     S(KC_S), 	S(KC_F), S(KC_H),	S(KC_K), KC_LBRC, 	      _______, 	  KC_F4     , _______ },
  { S(KC_Q), 	      S(KC_E), 	S(KC_T), S(KC_U),	S(KC_O), _______, 	      _______, 	  KC_F6     , _______ },
  { S(KC_2), 	      S(KC_4), 	S(KC_7), S(KC_9),	_______, _______, 	      S(KC_HOME), KC_F8     , _______ },
  { S(KC_UP),     	_______, 	_______, _______,	_______, _______, 	      _______, 	  _______   , _______ }
 },
 
 
 [_ALT] = { /* ALT SHIFT */
  { _______, _______, _______, _______, _______, _______, _______, _______ , _______ },
  { _______, _______, _______, _______, _______, _______, _______, _______ , _______ },
  { _______, _______, _______, _______, _______, _______, _______, _______ , _______ },
  { _______, _______, _______, _______, _______, _______, _______, _______ , _______ },
  { _______, _______, _______, _______, _______, _______, _______, _______ , _______ },
  { _______, _______, _______, _______, _______, _______, _______, _______ , _______ },
  { _______, _______, _______, _______, _______, _______, _______, _______ , _______ },
  { _______, _______, _______, _______, _______, _______, _______, _______ , _______ },
  { _______, _______, _______, _______, _______, _______, _______, _______ , _______ }
 },
 
 
 /*  [C64] = KEYMAP(
* KC_1,     	KC_GRV,    KC_TAB,	KC_ESC,		KC_SPC,		LM(CBM,MOD_LCTL),	  KC_Q,		KC_2,                    
*  KC_3,     	KC_W,      KC_A,	  KC_LSFT,	KC_Z,		  KC_S,               KC_E,		KC_4,                       	
* KC_5,     	KC_R,      KC_D,	  KC_X,		  KC_C,		  KC_F,              	KC_T,		KC_6,                     	
*	KC_7,     	KC_Y,      KC_G,	  KC_V,		  KC_B,		  KC_H,              	KC_U,		KC_8,        	KC_P7,  	
*	KC_9,     	KC_I,      KC_J,	  KC_N,		  KC_M,		  KC_K,              	KC_O,		KC_0,        	KC_P3,  	
*	KC_MINS,  	KC_P,      KC_L,	  KC_COMM,	KC_DOT,		KC_SCLN,           	KC_LBRC,	KC_EQL,			KC_P1,  	
*	KC_INS,   	KC_RBRC,   KC_QUOT,	KC_SLSH,	KC_RSFT,	KC_BSLS,           	KC_DEL,		KC_HOME,     	KC_P9,  	
*	KC_BSPC,  	KC_ENT,    KC_RGHT,	KC_DOWN,	KC_F1,		KC_F3,             	KC_F5,		KC_F7,       	KC_PDOT,	
*	KC_P8,    	KC_P2,     KC_P4,	  KC_P6,		KC_P0,														KC_PGUP),
*
},*/

/* SHIFT
 * .-----------------------------------------------------------------------.
 * | 1      | LEFT   | CTRL   | PAUSE  | SPACE  | WIN    | Q      | 2      |
 * |--------+--------+--------+--------+--------+--------+--------+--------|
 * | 3      | W      | A      | LSFT   | Z      | S      | E      | 4      |
 * |--------+--------+--------+--------+--------+--------+--------+--------|
 * | 5      | R      | D      | X      | C      | F      | T      | 6      |
 * |--------+--------+--------+--------+--------+--------+--------+--------|
 * | 7      | Y      | G      | V      | B      | H      | U      | 8      |
 * |--------+--------+--------+--------+--------+--------+--------+--------|
 * | 9      | I      | J      | N      | M      | K      | O      | 0      |
 * |--------+--------+--------+--------+--------+--------+--------+--------|
 * | +      | P      | L      | ,      | .      | :      | @      | "      |
 * |--------+--------+--------+--------+--------+--------+--------+--------|
 * | £      | *      | ;      | /      | RSFT   | =      | ^      | HOME   |
 * |--------+--------+--------+--------+--------+-----------------+--------|
 * | DEL    | ENT    | RIGHT  | DOWN   | F1     | F3     | F5     | F7     |
 * '-----------------------------------------------------------------------'
 */
 
 
};

const uint16_t PROGMEM fn_actions[] = {

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
          } else {
            unregister_code(KC_RSFT);
          }
        case 3: // this would trigger when you hit a key mapped as M(3)
          if (record->event.pressed) {
			return MACRO( I(255), D(LALT), T(P1), T(P5), T(P6), U(LALT), END );
          }
          break;
      }
    return MACRO_NONE;
};
