#include "planck.h"
#ifdef BACKLIGHT_ENABLE
#include "backlight.h"
#endif
#include "keymap_german.h"

// for intellisense, has to be commented for building
/*
#include "..\..\..\..\quantum\keymap_extras\keymap_german.h"
#include "..\..\..\..\tmk_core\common\keycode.h"
*/


#define _______ KC_TRNS
#define XXXXXXX KC_NO

/* This Layout tries to emulate the Bone2 Variant of Neo2, and is intended to be used with a German QWERTZ Softwarelayout.
It has "üäöß" as it is optimized for a mix of German & English.
My favourite features are the placement of the special characters often used for programming right on the home row
and the number & navigation block combo, so you never have to move your hands from their home position.

Bone2 wiki page: http://wiki.neo-layout.org/wiki/Bone
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Bone2 (adapted)
* ,-----------------------------------------------------------------------------------.
* | ß    |   J  |   D  |   U  |   A  |   X  |   P  |   H  |   L  |   M  |   W  |  Q   |
* |------+------+------+------+------+-------------+------+------+------+------+------|
* |  M1  |   C  |   T  |   I  |   E  |   O  |   B  |   N  |   R  |   S  |   G  |M1/Ent|  //hold for M1, tap for Enter
* |------+------+------+------+------+------|------+------+------+------+------+------|
* | Shift|   F  |   V  |   Ü  |   Ä  |   Ö  |   Y  |   Z  |   ,  |   .  |   K  |Shift |
* |------+------+------+------+------+------+------+------+------+------+------+------|
* | Ctrl | GUI  | Alt  |  M4  |  M2  |    Space    |  M2  |  M4  | Alt  | Esc  | Ctrl |
* `-----------------------------------------------------------------------------------'
*/
[0] = {
	{ DE_SS,        DE_J,    DE_D,    DE_U,  DE_A,  DE_X,   DE_P,   DE_H,  DE_L,    DE_M,    DE_W,    DE_Q         },
	//{ LT(1,KC_TAB), DE_C,    DE_T,    DE_I,  DE_E,  DE_O,   DE_B,   DE_N,  DE_R,    DE_S,    DE_G,    LT(1,KC_ENT) },
	{ MO(1),        DE_C,    DE_T,    DE_I,  DE_E,  DE_O,   DE_B,   DE_N,  DE_R,    DE_S,    DE_G,    LT(1,KC_ENT) },
	{ KC_LSFT,      DE_F,    DE_V,    DE_UE, DE_AE, DE_OE,  DE_Y,   DE_Z,  DE_COMM, DE_DOT,  DE_K,    KC_LSFT      },
	{ KC_LCTL,      KC_RGUI, KC_LALT, MO(4), MO(2), KC_SPC, KC_SPC, MO(2), MO(4),   KC_RALT, KC_ESC,  KC_RCTL      }
},

/* M1 Special Characters
*  very ergonomic placement for coding
* ,-----------------------------------------------------------------------------------.
* | °    |   @  |   _  |   [  |   ]  |   ^  |   !  |   <  |   >  |   =  |   &  |  ´   |
* |------+------+------+------+------+-------------+------+------+------+------+------|
* |  M1  |   \  |   /  |   {  |   }  |   *  |   ?  |   (  |   )  |   -  |   :  |M1/Ent|  //hold for M1, tap for Enter
* |------+------+------+------+------+------|------+------+------+------+------+------|
* | Shift|   #  |   ~  |   |  |   $  |   €  |   +  |   %  |   "  |   '  |   ;  |Shift |
* |------+------+------+------+------+------+------+------+------+------+------+------|
* | Ctrl | GUI  | Alt  |  M4  |  M2  |    Space    |  M2  |  M4  | Alt  | Esc  | Ctrl |
* `-----------------------------------------------------------------------------------'
*/
[1] = {
	{ DE_RING, DE_AT,   DE_UNDS, DE_LBRC, DE_RBRC, DE_CIRC, DE_EXLM, DE_LESS, DE_MORE, DE_EQL,  DE_AMPR, DE_ACUT },
	{ _______, DE_BSLS, DE_SLSH, DE_LCBR, DE_RCBR, DE_ASTR, DE_QST,  DE_LPRN, DE_RPRN, DE_MINS, DE_COLN, _______ },
	{ _______, DE_HASH, DE_TILD, DE_PIPE, DE_DLR,  DE_EURO, DE_PLUS, DE_PERC, DE_DQOT, DE_QUOT, DE_SCLN, _______ },
	{ _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ }
},

/* M2 Navigation & Number Blocks
*  very easy to get used to & intuituve placement
* ,-----------------------------------------------------------------------------------.
* |      | PgUp | Bksp |  Up  |  DEL | PgDn |      |   7  |   8  |   9  |      | Ins  |
* |------+------+------+------+------+-------------+------+------+------+------+------|
* |  Tab | Home |  Lft | Down | Right| End  |      |   4  |   5  |   6  |   .  | Enter|
* |------+------+------+------+------+------|------+------+------+------+------+------|
* | Shift|      |  Tab |      | Enter|      |   0  |   1  |   2  |   3  |   ,  |Shift |
* |------+------+------+------+------+------+------+------+------+------+------+------|
* | Ctrl | GUI  | Alt  |  M3  |  M2  |    Space    |  M2  |  M3  | Alt  | Esc  | Ctrl |
* `-----------------------------------------------------------------------------------'
*/
[2] = {
	{ XXXXXXX, KC_PGUP, KC_BSPC, KC_UP,   KC_DEL,  KC_PGDN, XXXXXXX, DE_7,    DE_8,  DE_9,    XXXXXXX, KC_INS  },
	{ KC_TAB,  KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  XXXXXXX, DE_4,    DE_5,  DE_6,    DE_DOT,  KC_ENT  },
	{ _______, XXXXXXX, KC_TAB,  XXXXXXX, KC_ENT,  XXXXXXX, DE_0,    DE_1,    DE_2,  DE_3,    DE_COMM, _______ },
	{ _______, _______, _______, MO(3),   _______, _______, _______, _______, MO(3), _______, _______, _______ }
},

/* M3 Switched Navigation & Number Blocks for one handed use
*  accessed by sliding from M2 to M3 with thumb
* ,-----------------------------------------------------------------------------------.
* |  Ins |      |  7   |  8   |  9   |      | PgUp | Bksp |  Up  |  DEL | PgDn |      |
* |------+------+------+------+------+-------------+------+------+------+------+------|
* |  Tab |      |  4   |  5   |  6   |   .  | Home | Left | Down | Right| End  | Enter|
* |------+------+------+------+------+------|------+------+------+------+------+------|
* | Shift|  0   |  1   |  2   |  3   |   ,  |      | Tab  |      | Enter|      |Shift |
* |------+------+------+------+------+------+------+------+------+------+------+------|
* | Ctrl | GUI  | Alt  |  M3  |      |    Space    |      |  M3  | Alt  | Esc  | Ctrl |
* `-----------------------------------------------------------------------------------'
*/

[3] = {
	{ KC_INS,  XXXXXXX, DE_7,    DE_8,    DE_9,    XXXXXXX, KC_PGUP, KC_BSPC, KC_UP,   KC_DEL,  KC_PGDN, XXXXXXX },
	{ _______, XXXXXXX, DE_4,    DE_5,    DE_6,    DE_DOT,  KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  _______ },
	{ _______, DE_0,    DE_1,    DE_2,    DE_3,    DE_COMM, XXXXXXX, KC_TAB,  XXXXXXX, KC_ENT,  XXXXXXX, _______ },
	{ _______, _______, _______, _______, XXXXXXX, _______, _______, XXXXXXX, _______, _______, _______, _______ }
},


/* M4 Function & Media Keys
* ,-----------------------------------------------------------------------------------.
* |      |      | Print|Scroll|Pause |      |      |  F7  |  F8  |  F9  |  F12 |      |
* |------+------+------+------+------+-------------+------+------+------+------+------|
* | Tab  |      | Mute | Vol- | Vol+ |      |   ³  |  F4  |  F5  |  F6  |  F11 | Enter|
* |------+------+------+------+------+------|------+------+------+------+------+------|
* | Shift|      | Prev | Play | Next |      |   ²  |  F1  |  F2  |  F3  |  F10 |Shift |
* |------+------+------+------+------+------+------+------+------+------+------+------|
* | Ctrl | GUI  | Alt  |  M4  |  M5  |    Space    |  M5  |  M4  | Alt  | Esc  | Ctrl |
* `-----------------------------------------------------------------------------------'
*/
[4] = {
	{ XXXXXXX, XXXXXXX, KC_PSCR, KC_SLCK, KC_PAUS, XXXXXXX, XXXXXXX, KC_F7, KC_F8,   KC_F9,   KC_F12,  XXXXXXX },
	{ KC_TAB,  XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX, DE_SQ3,  KC_F4, KC_F5,   KC_F6,   KC_F11,  KC_ENT  },
	{ _______, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, DE_SQ2,  KC_F1, KC_F2,   KC_F3,   KC_F10,  _______ },
	{ _______, _______, _______, _______, MO(5),   _______, _______, MO(5), _______, _______, _______, _______ }
},


/* M5 Switched Function & Media Keys|
*  accessed by sliding from M4 to M5 with thumb
* ,-----------------------------------------------------------------------------------.
* |      |      |  F7  |  F8  |  F9  |  F12 |      | Print|Scroll| Pause|      |      |
* |------+------+------+------+------+-------------+------+------+------+------+------|
* | Tab  |  ³   |  F4  |  F5  |  F6  |  F11 |      | Mute | Vol- | Vol+ |      | Enter|
* |------+------+------+------+------+------|------+------+------+------+------+------|
* | Shift|  ²   |  F1  |  F2  |  F3  |  F10 |      | Prev | Play | Next |      |Shift |
* |------+------+------+------+------+------+------+------+------+------+------+------|
* | Ctrl | GUI  | Alt  |      |  M5  |    Space    |  M5  |      | Alt  | Esc  | Ctrl |
* `-----------------------------------------------------------------------------------'
*/
[5] = {
	{ XXXXXXX, XXXXXXX, KC_F7,   KC_F8,   KC_F9,   KC_F12,  XXXXXXX, KC_PSCR, KC_SLCK, KC_PAUS, XXXXXXX, XXXXXXX },
	{ _______, DE_SQ3,  KC_F4,   KC_F5,   KC_F6,   KC_F11,  XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX, _______ },
	{ _______, DE_SQ2,  KC_F1,   KC_F2,   KC_F3,   KC_F10,  XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, _______ },
	{ _______, _______, _______, XXXXXXX, _______, _______, _______, _______, XXXXXXX, _______, _______, _______ }
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
