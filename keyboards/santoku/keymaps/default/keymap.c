/* Copyright 2021 Tye (@tyetye)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum santoku_layers {
    _QWERTY,
    _SYMBOL,
    _NAVIGATION,
    _FUNC,
};

enum santoku_keycodes {
	QWERTY = SAFE_RANGE,
	SYMBOL,
	NAVIGATION,
	FUNC,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_QWERTY] = { /*QWERTY*/
		/*
		   SWITCH TO THIS FORMAT/SHORTCUT????:  KC_A,      L(MOUSE,KC_S), L(MIDDLE,KC_D), GUI(KC_F),       CTL(KC_G),
https://docs.qmk.fm/#/faq_keymap?id=arrow-on-right-modifier-keys-with-dual-role <-- User VIM nav arrow key without layer??? Tap and hold?
*/
		{KC_TAB,              KC_Q,              KC_W,     KC_E,    KC_R,     KC_T,   KC_Y,         KC_U,       KC_I,    KC_O,   KC_P,                  KC_BSLS },
		{MT(MOD_LGUI,KC_ESC), MT(MOD_LCTL,KC_A), KC_S,     KC_D,    KC_F,     KC_G,   KC_H,         KC_J,       KC_K,    KC_L,   MT(MOD_RCTL,KC_SCLN),  MT(MOD_RGUI,KC_QUOT)},
		{KC_LSFT,             MT(MOD_LALT,KC_Z), KC_X,     KC_C,    KC_V,     KC_B,   KC_N,         KC_M,       KC_COMM, KC_DOT, MT(MOD_RALT,KC_SLSH),  KC_RSFT },
		{XXXXXXX,             XXXXXXX,           XXXXXXX,  LT(_FUNC,KC_BSPC), KC_SPC, KC_LCTL,      TT(_NAVIGATION), TT(_SYMBOL),  KC_ENT, XXXXXXX,    XXXXXXX,   XXXXXXX }
	},

	[_SYMBOL] = {/*SYMBOL*/
		{KC_GRV,               KC_EXLM,              KC_AT,   KC_HASH, KC_DLR,  KC_PERC,  KC_CIRC,  KC_AMPR, KC_ASTR,    KC_LPRN, KC_RPRN,              KC_MINS },
		{MT(MOD_LGUI,KC_ESC),  MT(MOD_LCTL,KC_1),    KC_2,    KC_3,    KC_4,    KC_5,     KC_6,     KC_7,    KC_8,       KC_9,    MT(MOD_RCTL,KC_0),    MT(MOD_RGUI,KC_EQL) },
		{KC_LSFT,              MT(MOD_LALT,KC_BSLS), KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR,  KC_LBRC,  KC_RBRC, KC_COMM,    KC_DOT,  MT(MOD_RALT,KC_SLSH), KC_RSFT },
		{XXXXXXX,              XXXXXXX,              XXXXXXX, KC_BSPC, KC_SPC,  XXXXXXX,  _______,  _______, KC_ENT,    XXXXXXX, XXXXXXX,              XXXXXXX }
	},

	[_NAVIGATION] = {/*NAVIGATION*/
		{KC_TAB,              XXXXXXX,  RCTL(KC_RGHT),  XXXXXXX,  XXXXXXX,     XXXXXXX,       KC_HOME,       KC_PGDN,      KC_PGUP,  KC_END,   RCTL(KC_TAB), XXXXXXX  },
		{MT(MOD_LGUI,KC_ESC), KC_LCTL,  XXXXXXX,        XXXXXXX,  KC_MS_WH_DOWN,     XXXXXXX,      KC_LEFT,       KC_DOWN,      KC_UP,    KC_RGHT,  KC_RCTL,      KC_RGUI  },
		{KC_LSFT,             KC_LALT,  XXXXXXX,        XXXXXXX,  KC_MS_WH_UP,       RCTL(KC_LEFT), LGUI(KC_LBRC), LGUI(KC_RBRC),LGUI(LSFT(KC_EQL)),  LGUI(LSFT(KC_MINS)),  KC_RALT,      KC_RSFT  },
		{XXXXXXX,             XXXXXXX,  XXXXXXX,        KC_DEL,   KC_SPC,      _______,      _______,       _______,      KC_ENT,  XXXXXXX,  XXXXXXX,      XXXXXXX  }
	},

	[_FUNC] = {/*FUNCTION*/
		{XXXXXXX, XXXXXXX,            XXXXXXX, XXXXXXX, KC_F11,  KC_F12,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,               XXXXXXX  },
		{MT(MOD_LGUI,KC_ESC), MT(MOD_LCTL,KC_F1), KC_F2,   KC_F3,   KC_F4,   KC_F5,    KC_F6,   KC_F7,   KC_F8,   KC_F9,   MT(MOD_RCTL,KC_F10),   MT(MOD_RGUI,KC_ESC)  },
		{MT(KC_LSFT,KC_CAPS), MT(MOD_LALT,KC_F6), KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,  KC_F12,  XXXXXXX, XXXXXXX, KC_LALT,               KC_RSFT  },
		{XXXXXXX, XXXXXXX,            XXXXXXX, XXXXXXX,KC_SPC ,  XXXXXXX,  XXXXXXX, XXXXXXX, RESET,   XXXXXXX, XXXXXXX,               XXXXXXX  }
	}

};

void keyboard_post_init_user(void) {
	// Customise these values to desired behaviour
	debug_enable=false;
	debug_matrix=false;
	debug_keyboard=false;
	debug_mouse=false;
	//ps2_mouse_set_remote_mode();
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case RESET:
			//oled_write_ln_P(PSTR("RESETORFLASH"), true);
			_delay_ms(1000);
			break;
	}
	return true;
}


void matrix_init_user(void) {
#ifdef USE_I2C
	i2c_master_init();
#ifdef SSD1306OLED
	// calls code for the SSD1306 OLED
	_delay_ms(400);
	TWI_Init(TWI_BIT_PRESCALE_1, TWI_BITLENGTH_FROM_FREQ(1, 800000));
	iota_gfx_init();   // turns on the display
#endif
#endif
}

//#ifdef OLED_DRIVER_ENABLE
#ifdef OLED_ENABLE
void oled_task_user(void) {
	// Vanity Text
	static bool show_vanity_text = true;
	if (show_vanity_text) {
		oled_write_ln_P(PSTR("  Santoku Keyboard"), false);
		oled_write_ln_P(PSTR("       by Tye"), false);
		oled_write_ln_P(PSTR(""), false);
		oled_write_ln_P(PSTR("    Hello, world."), false);
		if (timer_read() > 7500) {
			show_vanity_text = false;
		}
	}
	else {
		uint8_t wpm = get_current_wpm();
		if (wpm < 20) {
			oled_write("CrOS  ", false);
		}
		else {
			char wpm_display[9];
			sprintf(wpm_display, "WPM:%d ", get_current_wpm());
			oled_write(wpm_display, false);
		}

		// Host Keyboard Layer Status
		switch (get_highest_layer(layer_state)) {
			case _QWERTY:
				oled_write_P(PSTR("QWERTY\n"), false);
				oled_write_ln_P(PSTR(""), false);
				oled_write_ln_P(PSTR("TB  qwert | yuiop\\"), false);
				oled_write_ln_P(PSTR("ES  asdfg | hjkl;'"), false);
				oled_write_ln_P(PSTR("SH  zxcvb | nm,./"), false);
				break;
			case _SYMBOL:
				oled_write_P(PSTR("   Symbol   \n"), true);
				oled_write_ln_P(PSTR(""), false);
				oled_write_ln_P(PSTR(" `  !@#$% | ^&*()-"), false);
				oled_write_ln_P(PSTR("ES  12345 | 67890="), false);
				oled_write_ln_P(PSTR("SH  \\_+{} | [],./"), false);
				break;
			case _NAVIGATION:
				oled_write_P(PSTR(" Navigation \n"), true);
				oled_write_ln_P(PSTR(""), false);
				oled_write_ln_P(PSTR("   | HM PD PU EN NT"), false);
				oled_write_ln_P(PSTR("   | << vv ^^ >>"), false);
				oled_write_ln_P(PSTR("ov | D[ D] D+ D-"), false);
				break;
			case _FUNC:
				oled_write_P(PSTR("  Function  \n"), true);
				oled_write_ln_P(PSTR(""), false);
				oled_write_ln_P(PSTR("          |"), false);
				oled_write_ln_P(PSTR("ES F12345 | 67890"), false);
				oled_write_ln_P(PSTR("CP F      | ab"), false);
				break;
			default:
				oled_write_ln_P(PSTR("Undefined"), false);
		}
	}

	/*
	// Host Keyboard LED Status
	led_t led_state = host_keyboard_led_state();
	oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
	oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
	oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
	*/
}
#endif

