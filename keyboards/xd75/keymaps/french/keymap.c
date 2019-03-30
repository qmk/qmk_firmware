#include "keymap_french.c"
#include QMK_KEYBOARD_H


// Layer shorthand
#define _AZ 0
#define _FN 1


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* AZERTY
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | &      | é      | "      | '      | (      | -      | è      | _      | ç      | à      | )      | =      | INSERT | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | a      | z      | e      | r      | t      | y      | u      | i      | o      | p      | ^      | $      | ENTER  | PG UP  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | CAP LK | q      | s      | d      | f      | g      | h      | j      | k      | l      | m      | ù      | *      | ENTER  | PG DN  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | LSHIFT | w      | x      | c      | v      | b      | n      | ,      | ;      | :      | !      | <      | LSHIFT | UP     | DEL    |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | LCTRL  | CMD    | ALT    | FN     | SPACE  | SPACE  | SPACE  | SPACE  | ALGR   | MENU   | HOME   | END    | LEFT   | DOWN   | RIGHT  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_AZ] = { /* AZERTY */
  { FR_ESC,  	FR_AMP, 	FR_EACU, 	FR_QUOT, 	FR_APOS,  	FR_LPAR, 	FR_MINS, 	FR_EGRV,  	FR_UNDS,  	FR_CCED,  	FR_AGRV,  	FR_RPAR,  	FR_EQUA,  	FR_INST,  	FR_BSPC },
  { FR_TAB,  	FR_A,   	FR_Z,    	FR_E,    	FR_R,     	FR_T,    	FR_Y,    	FR_U,     	FR_I,     	FR_O,		FR_P,     	FR_HAT,   	FR_DLR,   	FR_ENTR,  	FR_PGUP },
  { FR_CAPL, 	FR_Q,   	FR_S,    	FR_D,    	FR_F,     	FR_G,    	FR_H,    	FR_J,     	FR_K,     	FR_L,     	FR_M,     	FR_UGRV,  	FR_AST,   	FR_ENTR,  	FR_PGDN },
  { FR_LSFT, 	FR_W,    	FR_X,    	FR_C,    	FR_V,     	FR_B,    	FR_N,    	FR_COMM,  	FR_SCLN,  	FR_COLN,  	FR_EXCL,  	FR_LESS,      	FR_RSFT,  	FR_UP,    	FR_DEL  },
  { FR_LCTR, 	FR_LCMD, 	FR_LALT, 	MO(_FN),	FR_SPAC,  	FR_SPAC, 	FR_SPAC, 	FR_SPAC,  	FR_ALGR,  	FR_MENU,  	FR_HOME,  	FR_END,   	FR_LEFT,  	FR_DOWN,  	FR_RIGT },
 },


/* FUNCTION
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        | F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     | F10    | F11    | F12    | PRINT  | LED    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | PREV   | PLAY   | NEXT   |        |        |        |        | NUM LCK| 7      | 8      | 9      | *      |        | LED+   |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | VOL-   | MUTE   | VOL+   |        |        |        |        |        | 4      | 5      | 6      | -      |        | LED-   |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        | 1      | 2      | 3      | +      |        | LEDMAX |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | RESET  |        |        | FN     |        |        |        |        |        |        | 0      | .      | PENT   |        | LEDLVL |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */
 
 [_FN] = { /* FUNCTION */
  { FR_EMPT,	FR_F1,		FR_F2,		FR_F3,		FR_F4,		FR_F5,		FR_F6,  	FR_F7,		FR_F8,    	FR_F9,		FR_F10, 	FR_F11,  	FR_F12,   	FR_PSCR,	BL_TOGG },
  { FR_EMPT,	FR_MPRV,	FR_MPLY,	FR_MNXT,	FR_EMPT,	FR_EMPT,	FR_EMPT,	FR_EMPT,	FR_NUML,  	FR_7,     	FR_8,   	FR_9,    	FR_MULT,  	FR_EMPT,	BL_INC	},
  { FR_EMPT,	FR_MVDN,	FR_MUTE,	FR_MVUP,	FR_EMPT,	FR_EMPT,	FR_EMPT,	FR_EMPT,	FR_EMPT,  	FR_4,     	FR_5,   	FR_6,    	FR_MOIN,  	FR_EMPT,	BL_DEC	},
  { FR_EMPT,	FR_EMPT,	FR_EMPT,	FR_EMPT,	FR_EMPT,	FR_EMPT,	FR_EMPT,	FR_EMPT,  	FR_EMPT,  	FR_1,     	FR_2,   	FR_3,    	FR_PLUS,  	FR_EMPT,	BL_ON 	},
  { RESET,	FR_EMPT,	FR_EMPT,	FR_TRANS,	FR_EMPT,	FR_EMPT,	FR_EMPT,	FR_EMPT,  	FR_EMPT,  	FR_EMPT,  	FR_0,   	FR_DOT,  	FR_ENTK,  	FR_EMPT,	BL_STEP	},
 },
};
