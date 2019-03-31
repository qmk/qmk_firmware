/* auth: domonkos */

#include "dactyl_manuform.h"
#include "mousekey.h"

#define NO_ACTION_LAYER

extern keymap_config_t keymap_config;

enum dactyl_keycodes {
	SRST = SAFE_RANGE,
};

#define COPY LCTL(KC_INS)
#define PASTE LSFT(KC_INS)
#define PASTEV LSFT(LALT(KC_V))

#include "dvorak_kombo.h"
kombo_t key_kombos[] = {
	{ CC_O|CC_E|CC_U,              KC_SLSH, nested },
	{ CC_O|CC_E|CC_I,              KC_LABK, nested },
	{ CC_A|CC_O|CC_E|CC_U,         KC_LPRN, nested },
	{ CC_A|CC_O|CC_E,              KC_LCBR, nested },
	{ CC_A|CC_O|CC_U,              KC_LBRC, nested },

	{ CC_N|CC_T|CC_H,              KC_ENT,  nested },
	{ CC_D|CC_T|CC_N,              KC_RABK, nested },
	{ CC_H|CC_T|CC_N|CC_S,         KC_RPRN, nested },
	{ CC_T|CC_N|CC_S,              KC_RCBR, nested },
	{ CC_H|CC_N|CC_S,              KC_RBRC, nested },

	{ CC_A|CC_O|CC_D,              KC_RALT, instant },
	{ CC_A|CC_O|CC_H,              KC_LCTL, instant },
	{ CC_A|CC_O|CC_T,              KC_LSFT, instant },
	{ CC_A|CC_O|CC_N,              KC_LGUI, instant },
	{ CC_A|CC_O|CC_S,              KC_LALT, instant },

	{ CC_A|CC_U|CC_H,              KC_EQL,  nested },
	{ CC_A|CC_U|CC_T,              KC_PLUS, nested },
	{ CC_A|CC_U|CC_N,              KC_ASTR, nested },
	{ CC_A|CC_U|CC_S,              KC_HASH, nested },

	{ CC_O|CC_U|CC_H,              KC_GRV,  nested },
	{ CC_O|CC_U|CC_T,              KC_UNDS, nested },
	{ CC_O|CC_U|CC_N,              KC_PERC, nested },

	{ CC_O|CC_E|CC_H,              KC_COLN, nested },
	{ CC_O|CC_E|CC_T,              KC_MINS, nested },
	{ CC_O|CC_E|CC_N,              KC_PIPE, nested },
	{ CC_O|CC_E|CC_S,              KC_AMPR, nested },

	{ CC_E|CC_U|CC_H,              KC_CIRC, nested },
	{ CC_E|CC_U|CC_S,              KC_DLR,  nested },
	{ CC_E|CC_U|CC_T,              KC_QUES, nested },
	{ CC_E|CC_U|CC_N,              KC_EXLM, nested },

	{ CC_O|CC_E,                   KC_SPC,  nested },
	{ CC_H|CC_N,                   KC_BSPC, nested },
	{ CC_A|CC_O|CC_H,              KC_DEL,  nested },
	{ CC_E|CC_U,                   KC_TAB,  nested },

	{ CC_T|CC_N|CC_A,              KC_DQUO, nested },
	{ CC_T|CC_N|CC_O,              KC_BSLS, nested },
	{ CC_T|CC_N|CC_E,              KC_TILD, nested },
	{ CC_T|CC_N|CC_U,              KC_AT,   nested },

	{ CC_Q|CC_V,                   COPY,    nested },
	{ CC_J|CC_W,                   PASTE,   nested },
	{ CC_K|CC_M,                   PASTEV,  nested },

	{ CC_T|CC_H|CC_K,              KC_K,    instant },
	{ CC_T|CC_H|CC_J,              KC_J,    instant },
	{ CC_T|CC_N|CC_K,              KC_PGUP, instant },
	{ CC_T|CC_N|CC_J,              KC_PGDN, instant },

	{ CC_COMM|CC_DOT|CC_R,         KC_END,  instant },
	{ CC_COMM|CC_DOT|CC_G,         KC_HOME, instant },
	{ CC_COMM|CC_DOT|CC_C,         KC_UP,   instant },
	{ CC_COMM|CC_DOT|CC_N,         KC_RGHT, instant },
	{ CC_COMM|CC_DOT|CC_T,         KC_DOWN, instant },
	{ CC_COMM|CC_DOT|CC_H,         KC_LEFT, instant },
	{ CC_COMM|CC_DOT|CC_W,         KC_ESC,  instant },
	{ CC_COMM|CC_DOT|CC_M,         KC_ENT,  instant },

	{ CC_DOT|CC_P|CC_S,            KC_0,    instant },
	{ CC_DOT|CC_P|CC_M,            KC_1,    instant },
	{ CC_DOT|CC_P|CC_W,            KC_2,    instant },
	{ CC_DOT|CC_P|CC_V,            KC_3,    instant },
	{ CC_DOT|CC_P|CC_H,            KC_4,    instant },
	{ CC_DOT|CC_P|CC_T,            KC_5,    instant },
	{ CC_DOT|CC_P|CC_N,            KC_6,    instant },
	{ CC_DOT|CC_P|CC_G,            KC_7,    instant },
	{ CC_DOT|CC_P|CC_C,            KC_8,    instant },
	{ CC_DOT|CC_P|CC_R,            KC_9,    instant },
	{ CC_DOT|CC_P|CC_L,            KC_PLUS, instant },
	{ CC_DOT|CC_P|CC_Z,            KC_MINS, instant },
	{ CC_DOT|CC_P|CC_F,            KC_ASTR, instant },
	{ CC_DOT|CC_P|CC_B,            KC_SLSH, instant },
	{ CC_DOT|CC_P|CC_D,            KC_DOT,  instant },
	{ CC_DOT|CC_P|CC_RCBR,         KC_LPRN, instant },
	{ CC_DOT|CC_P|CC_RBRC,         KC_RPRN, instant },
	{ CC_DOT|CC_P|CC_SPC,          KC_SPC,  instant },
	{ CC_DOT|CC_P|CC_BSPC,         KC_BSPC, instant },

	{ CC_COMM|CC_P|CC_G,           KC_F1,   instant },
	{ CC_COMM|CC_P|CC_C,           KC_F2,   instant },
	{ CC_COMM|CC_P|CC_R,           KC_F3,   instant },
	{ CC_COMM|CC_P|CC_L,           KC_F4,   instant },
	{ CC_COMM|CC_P|CC_H,           KC_F5,   instant },
	{ CC_COMM|CC_P|CC_T,           KC_F6,   instant },
	{ CC_COMM|CC_P|CC_N,           KC_F7,   instant },
	{ CC_COMM|CC_P|CC_S,           KC_F8,   instant },
	{ CC_COMM|CC_P|CC_M,           KC_F9,   instant },
	{ CC_COMM|CC_P|CC_W,           KC_F10,  instant },
	{ CC_COMM|CC_P|CC_V,           KC_F11,  instant },
	{ CC_COMM|CC_P|CC_Z,           KC_F12,  instant },

	{ CC_DOT|CC_J,                 KC_MPLY, nested },
	{ CC_DOT|CC_E,                 KC_MNXT, nested },
	{ CC_E|CC_J,                   KC_MPRV, nested },
	{ CC_P|CC_K,                   KC_MUTE, nested },
	{ CC_P|CC_U,                   KC_VOLU, nested },
	{ CC_U|CC_K,                   KC_VOLD, nested },

	{ CC_COMM|CC_DOT|CC_P|CC_C,    KC_MS_U, instant},
	{ CC_COMM|CC_DOT|CC_P|CC_T,    KC_MS_D, instant},
	{ CC_COMM|CC_DOT|CC_P|CC_H,    KC_MS_L, instant},
	{ CC_COMM|CC_DOT|CC_P|CC_N,    KC_MS_R, instant},
	{ CC_COMM|CC_DOT|CC_P|CC_L,    KC_WH_U, instant},
	{ CC_COMM|CC_DOT|CC_P|CC_S,    KC_WH_D, instant},
	{ CC_COMM|CC_DOT|CC_P|CC_G,    KC_BTN1, instant},
	{ CC_COMM|CC_DOT|CC_P|CC_R,    KC_BTN2, instant},
	{ CC_COMM|CC_DOT|CC_P|CC_F,    KC_BTN3, instant},
	{ CC_COMM|CC_DOT|CC_P|CC_D,    KC_BTN4, instant},
	{ CC_COMM|CC_DOT|CC_P|CC_B,    KC_BTN5, instant},

	{ CC_SCLN|CC_A|CC_QUOT,        SRST,    instant },
	{ CC_Y|CC_I|CC_X,              KC_CCOFF,instant },
	{ 0,                           KC_NO,   nested },
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	/*
	,--------------------------------------------.                   ,--------------------------------------------.
	|   ;    |   ,    |   .    |   p    |   y    |                   |   f    |   g    |   c    |   r    |   l    |
	|--------+--------+--------+--------+--------|                   |--------+--------+--------+--------+--------|
	|   a    |   o    |   e    |   u    |   i    |                   |   d    |   h    |   t    |   n    |   s    |
	|--------+--------+--------+--------+--------|                   |--------+--------+--------+--------+--------|
	|   '    |   q    |   j    |   k    |   x    |                   |   b    |   m    |   w    |   v    |   z    |
	`--------+--------+--------+-----------------'                   `-----------------+--------+--------+--------'
	         |   [    |   {    |                                                       |   }    |   ]    |
	         `-----------------+-----------------.                   ,--------+--------+-----------------'
	                           |  TAB   | SPACE  |                   |   BS   |  ESC   |
	                           `--------+--------+--------. ,--------+--------+--------'
	                                    |   (    |  CTRL  | | SHIFT  |   )    |
	                                    |--------+--------| |--------+--------|
	                                    |LEFT ALT|LEFT GUI| |   \    |  RALT  |
	                                    `-----------------' `-----------------'
	*/
	LAYOUT(                                                                                                        \
	 KC_SCLN, KC_COMM, KC_DOT,  KC_P,    KC_Y,                        KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    \
	 KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                        KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    \
	 KC_QUOT, KC_Q,    KC_J,    KC_K,    KC_X,                        KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    \
	          KC_LBRC, KC_LCBR,                                                         KC_RCBR, KC_RBRC,          \
	                   KC_TAB,  KC_SPC,                                        KC_BSPC, KC_ESC,                    \
	                            KC_LPRN, KC_LCTL,                     KC_LSFT, KC_RPRN,                            \
	                                     KC_LALT, KC_LGUI,   KC_BSLS, KC_RALT                                      \
	)
};

bool
process_record_user(uint16_t keycode, keyrecord_t *record) {
	uint8_t static n_keys = 0;
	record->event.pressed ? n_keys++ : n_keys--;
	if (n_keys >= 8) {
		kombo_enable();
		n_keys = 0;
		clear_keyboard();
	}

        switch (keycode) {
		case SRST:
			if (record->event.pressed) {
				matrix_init_user();
			}
			return false;
	}

	return true;
}

bool
process_kombo_event(size_t kombo_index, keypos_t pos) {
	uint16_t const keycode = key_kombos[kombo_index].keycode;

	if (keycode == KC_CCOFF) {
		kombo_disable();
		return false;
	}

	if (IS_MOD(keycode)) {
		set_oneshot_mods(MOD_BIT((uint8_t)keycode) | get_oneshot_mods());
		return false;
	}

	return true;
}

void matrix_init_user(void) {
	clear_keyboard();
}
