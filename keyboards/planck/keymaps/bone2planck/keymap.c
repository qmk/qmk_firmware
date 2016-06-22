
#include "planck.h"
#ifdef BACKLIGHT_ENABLE
#include "backlight.h"
#endif
#include "keymap_german.h"

/* This Layout tries to emulate the Bone2 Variant of Neo2, and is intended to be used with a German QWERTZ Softwarelayout.
   It has Umlauts and "ß" as it is optimized for a mix of German & English.
   My favourite features are the placement of the special characters often used for programming right on the home row 
   and the number & navigation block combo, so you never have to move your hands from their home position.
   
   Bone2 wiki page: http://wiki.neo-layout.org/wiki/Bone
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	/* Bone2
	* ,-----------------------------------------------------------------------------------.
	* | Q	 |   J  |   D  |   U  |   A  |   X  |   P  |   H  |   L  |   M  |   W  |  ẞ   |
	* |------+------+------+------+------+-------------+------+------+------+------+------|
	* | M1   |   C  |   T  |   I  |   E  |   O  |   B  |   N  |   R  |   S  |   G  |  M1  |
	* |------+------+------+------+------+------|------+------+------+------+------+------|
	* | Shift|   F  |   V  |   Ü  |   Ä  |   Ö  |   Y  |   Z  |   ,  |   .  |   K  |Shift |
	* |------+------+------+------+------+------+------+------+------+------+------+------|
	* | Ctrl | GUI  | Alt  |  M3  |  M2  |    Space    |  M2  |  M3  |  Esc |  Tab |Enter |
	* `-----------------------------------------------------------------------------------'
	*/
	[0] = {
		{ DE_Q,	   DE_J,	DE_D,    DE_U,    DE_A,    DE_X,    DE_P,    DE_H,    DE_L,    DE_M,    DE_W,    DE_SS  },
		{ MO(1),   DE_C,    DE_T,    DE_I,    DE_E,    DE_O,    DE_B,    DE_N,    DE_R,    DE_S,    DE_G,    MO(1)  },
		{ DE_S,	   DE_F,    DE_V,    DE_UE,   DE_AE,   DE_OE,   DE_Y,    DE_Z,    DE_COMM, DE_DOT,  DE_K,    DE_S   },
		{ KC_LCTL, KC_LGUI, KC_LALT, MO(3),   MO(2),   KC_SPC,  KC_SPC,  MO(2),   MO(3),   KC_ESC,  KC_TAB,  KC_ENT }
	},

	/* M1 Special Characters
	* ,-----------------------------------------------------------------------------------.
	* | °    |   @  |   _  |   [  |   ]  |   ^  |   !  |   <  |   >  |   =  |   &  |      |
	* |------+------+------+------+------+-------------+------+------+------+------+------|
	* | M1   |   \  |   /  |   {  |   }  |   *  |   ?  |   (  |   )  |   -  |   :  |  M1  |
	* |------+------+------+------+------+------|------+------+------+------+------+------|
	* |      |   #  |   $  |   |  |   ~  |   €  |   +  |   %  |   "  |   '  |   ;  |      |
	* |------+------+------+------+------+------+------+------+------+------+------+------|
	* | Ctrl | GUI  | Alt  |  M3  |  M2  |    Space    |  M2  |  M3  |  Esc |  Tab |Enter |
	* `-----------------------------------------------------------------------------------'
	*/
	[1] = {
		{ DE_RING, DE_AT,   DE_UNDS, DE_LBRC, DE_RBRC, DE_CIRC, DE_EXLM, DE_LESS, DE_MORE, DE_EQL,  DE_AMPR, KC_NO   },
		{ KC_TRNS, DE_BSLS, DE_SLSH, DE_LCBR, DE_RCBR, DE_ASTR, DE_QST,  DE_LPRN, DE_RPRN, DE_MINS, DE_COLN, KC_TRNS },
		{ KC_NO  , DE_HASH, DE_DLR,  DE_PIPE, DE_TILD, DE_EURO, DE_PLUS, DE_PERC, DE_DQOT, DE_QUOT, DE_SCLN, KC_NO   },
		{ KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS }
	},

	/* Navigation & Number Blocks
	* ,-----------------------------------------------------------------------------------.
	* |      | PgUp | Bksp |  Up  |  DEL | PgDn |      |   7  |   8  |   9  |      |      |
	* |------+------+------+------+------+-------------+------+------+------+------+------|
	* |      | Home |  Lft | Down | Right| End  |   .  |   4  |   5  |   6  |   ,  |      |
	* |------+------+------+------+------+------|------+------+------+------+------+------|
	* | Shift|      |  Tab | Ins  | Enter|      |   0  |   1  |   2  |   3  |   ;  |Shift |
	* |------+------+------+------+------+------+------+------+------+------+------+------|
	* | Ctrl | GUI  | Alt  |  M3  |  M2  |    Space    |  M2  |  M3  |  Esc |  Tab |Enter |
	* `-----------------------------------------------------------------------------------'
	*/
	[2] = {
		{ KC_NO,   KC_PGUP, KC_BSPC, KC_UP,   KC_DEL,  KC_PGDN, KC_NO,   DE_7,    DE_8,    DE_9,    KC_NO,   KC_NO   },
		{ KC_NO,   KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  DE_DOT,  DE_4,    DE_5,    DE_6,    DE_COMM, KC_NO   },
		{ DE_S,    KC_NO,   KC_TAB,  KC_INS,  KC_ENT,  KC_NO,   KC_0,    DE_1,    DE_2,    DE_3,    DE_SCLN, DE_S    },
		{ KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS }
	},

	/* Function & Media Keys
	* ,-----------------------------------------------------------------------------------.
	* |      |      | Print|Scroll|Pause |      |      |  F7  |  F8  |  F9  |  F12 |      |
	* |------+------+------+------+------+-------------+------+------+------+------+------|
	* |      |      | Mute | Vol- | Vol+ |      |   ³  |  F4  |  F5  |  F6  |  F11 |      |
	* |------+------+------+------+------+------|------+------+------+------+------+------|
	* | Shift|      | Prev | Play | Next |      |   ²  |  F1  |  F2  |  F3  |  F10 |Shift |
	* |------+------+------+------+------+------+------+------+------+------+------+------|
	* | Ctrl | GUI  | Alt  |  M3  |      |    Space    |      |  M3  |  Esc |  Tab |Enter |
	* `-----------------------------------------------------------------------------------'
	*/
	[3] = {
		{ KC_NO,   KC_NO,   KC_PSCR, KC_SLCK, KC_PAUS, KC_NO,   KC_NO,   KC_F7,   KC_F8,   KC_F9,   KC_F12,  KC_NO	},
		{ KC_NO,   KC_NO,   KC_MUTE, KC_VOLD, KC_VOLU, KC_NO,   DE_SQ3,  KC_F4,   KC_F5,   KC_F6,   KC_F11,  KC_NO  },
		{ KC_TRNS, KC_NO,   KC_MPRV, KC_MPLY, KC_MNXT, KC_NO,   DE_SQ2,  KC_F1,   KC_F2,   KC_F3,   KC_F10,  KC_TRNS},
		{ KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,   KC_TRNS, KC_TRNS, KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS}
	}
};

const uint16_t PROGMEM fn_actions[] = {

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
	// MACRODOWN only works in this function
	switch (id) {
	case 0:
		if (record->event.pressed) {
			register_code(KC_RSFT);
#ifdef BACKLIGHT_ENABLE
			backlight_step();
#endif
		}
		else {
			unregister_code(KC_RSFT);
		}
		break;
	}
	return MACRO_NONE;
};
