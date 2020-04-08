/* Copyright 2015-2017 Jack Humbert
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

/*                                   _
 *  ___   _ __     ___   __      __ | | __  _   _   _ __ ___     __ _
 * / __| | '_ \   / _ \  \ \ /\ / / | |/ / | | | | | '_ ` _ \   / _` |
 * \__ \ | | | | | (_) |  \ V  V /  |   <  | |_| | | | | | | | | (_| |
 * |___/ |_| |_|  \___/    \_/\_/   |_|\_\  \__,_| |_| |_| |_|  \__,_|
 *
 * https://github.com/snowkuma
 *
 * version 0.2
 */

#include QMK_KEYBOARD_H
#include "muse.h"
#include "custom_keycodes.h"
#include "my_strings.h"

extern keymap_config_t keymap_config;

enum planck_layers {
	_COLEMAK = 0,
	_NAV,
	_SYMBOL,
	_NUMBER,
	_ARRANGE,
	_FUNCTION,
	_MOUSE,
	_THUMB
};

enum planck_keycodes {
	EMAIL = SAFE_RANGE,
	EMOJI,
	EXT_PLV,
	ITERM,
	KRAKEN,
	LESSON,
	TYPE_FU,
	VS_CODE,
	SPOTIFY
};


// Tap Dance Declarations
enum {
	TD_RESET = 0,
	TD_TILD,
	COPYCUT
};

// Tap Dance Definitions
void safe_reset(qk_tap_dance_state_t *state, void *user_data) {
	if (state->count >=3) {
		// Reset the keyboard if you tap the key more than three times
		reset_keyboard();
		reset_tap_dance(state);
	} else {
		SEND_STRING(SS_LGUI(" "));
		SEND_STRING("GitKraken.app" SS_TAP(X_ENTER));
	}
};

void copy_cut(qk_tap_dance_state_t *state, void *user_data) {
	if (state->count >= 2) {
		register_code(KC_LGUI);
		register_code(KC_X);
		unregister_code(KC_X);
		unregister_code(KC_LGUI);
	} else {
		register_code(KC_LGUI);
		register_code(KC_C);
		unregister_code(KC_C);
		unregister_code(KC_LGUI);
	}
};

void tilde_home(qk_tap_dance_state_t *state, void *user_data) {
	if (state->count > 2) {
		register_code(KC_LSFT);
		register_code(KC_GRV);
	}
	else {
		register_code(KC_LSFT);
		register_code(KC_GRV);
		if (state->count > 1) {
			// Outputs ~/ if tilde tapped twice
			unregister_code(KC_GRV);
			unregister_code(KC_LSFT);
			register_code(KC_SLSH);
		}
	}
} 

void tilde_reset(qk_tap_dance_state_t *state, void *user_data)
{
	if (state->count == 2) {
		unregister_code(KC_SLSH);
	} else {
		unregister_code(KC_GRV);
		unregister_code(KC_LSFT);
	}
}


qk_tap_dance_action_t tap_dance_actions[] = {
	[TD_RESET] = ACTION_TAP_DANCE_FN (safe_reset),
	[TD_TILD] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, tilde_home, tilde_reset),
	[COPYCUT] = ACTION_TAP_DANCE_FN (copy_cut)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	/* COLEMAK
	 *
	 * Base layer
	 * ,-----------------------------------------------------------------------------------------------------------.
	 * |   q    |   w    |   f    |   p    |   g    |        |        |   j    |   l    |   u    |   y    |   ;    |
	 * |  CTRL  |  ALT   |  GUI   |        |        |        |        |        |        |  GUI   |  ALT   |  CTRL  |
	 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
	 * |   a    |   r    |   s    |   t    |   d    |        |        |   h    |   n    |   e    |   i    |   o    |
	 * |        |        |        | Shift  |        |        |        |        | Shift  |        |        |        |
	 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
	 * |   z    |   x    |   c    |   v    |   b    |        |        |   k    |   m    |   ,    |   .    |   '    |
	 * |        |        |        |        |        |        |        |        |        |        |        |        |
	 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
	 * |        |        |        |  Esc   | BkSp   |   TAB  |   -    | Space  | Enter  |        |        |
	 * |        |        |        |  Num   | Symbol |  Shift | Arrange|  Nav   | Thumb  |        |        |        |
	 * `--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------'
	 */
	[_COLEMAK] = LAYOUT_planck_grid(
			Q_CTL,   W_ALT,   F_GUI,   KC_P,    KC_G,    _______, _______, KC_J,    KC_L,    U_GUI,   Y_ALT,   SCL_CTL,
			KC_A,    KC_R,    KC_S,    T_SFT,   KC_D,    _______, _______, KC_H,    N_SFT,   KC_E,    KC_I,    KC_O,
			KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    _______, _______, KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_QUOT,
			_______, _______, _______, ESC_NUM, BSP_SYM, TAB_SFT, MIN_ARR, SPC_NAV, ENT_THU, _______, _______, _______
			),

	/* NAV
	 * ,-----------------------------------------------------------------------------------------------------------.
	 * |   !    |   @    |   €    |   &    |   |    |        |        |        |  Home  |   Up   |  End   |  PgUp  |
	 * |        |        |        |        |        |        |        |        |        |        |        |        |
	 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
	 * |   ~    |   <    |   %    |   >    |   +    |        |        |        |  Left  |  Down  | Right  |  PgDn  |
	 * | 2x ~/  |        |        |        |        |        |        |        |        |        |        |        |
	 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
	 * |   `    |        |   £    |   =    |   -    |        |        |        |        |        |        |        |
	 * |        |        |        |        |        |        |        |        |        |        |        |        |
	 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
	 * |        |        |        |   _    |  Del   |   -    |        |  f()   |        |        |        |        |
	 * |        |        |        |        | Mouse  |        |        |  Nav   |Function|        |        |        |
	 * `--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------'
	 */
	[_NAV] = LAYOUT_planck_grid(
			KC_EXLM, KC_AT,   EURO,    KC_AMPR, KC_PIPE,  _______, _______, _______, KC_HOME, KC_UP,   KC_END, KC_PGUP,
			TD(TD_TILD), KC_LT, KC_PERC, KC_GT, KC_PLUS,  _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,
			KC_GRV,  _______, GBP,     KC_EQL,  KC_MINS,  _______, _______, _______, _______, _______, _______, _______,
			_______, _______, _______, _______, DEL_SYM,  _______, _______, _______, _______, _______, _______, _______
			),

	/* SYMBOL
	 * ,-----------------------------------------------------------------------------------------------------------.
	 * |   !    |   @    |   €    |   &    |   |    |        |        |   *    |   [    |   ^    |    ]   |   :    |
	 * |        |        |        |        |        |        |        |        |        |        |        |        |
	 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
	 * |   ~    |   <    |   %    |   >    |   +    |        |        |   ?    |   (    |   $    |    )   |   /    |
	 * |  2x ~/ |        |        |        |        |        |        |        |        |        |        |        |
	 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
	 * |   `    |        |   £    |   =    |   -    |        |        |   |    |   {    |   #    |    }   |   \    |
	 * |        |        |        |        |        |        |        |        |        |        |        |        |
	 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
	 * |        |        |        |        |   f()  |        |        | Space  |        |        |        |
	 * |        |        |        |        | Symbol |        |        | Mouse  |  Enter |        |        |        |
	 * `--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------'
	 */
	[_SYMBOL] = LAYOUT_planck_grid(
			KC_EXLM, KC_AT,   EURO,    KC_AMPR, KC_PIPE, _______, _______, KC_ASTR, KC_LBRC, KC_CIRC, KC_RBRC, KC_COLN,
			TD(TD_TILD), KC_LT, KC_PERC, KC_GT, KC_PLUS, _______, _______, KC_QUES, KC_LPRN, KC_DLR,  KC_RPRN, KC_SLSH,
			KC_GRV,  _______, GBP,     KC_EQL,  KC_MINS, _______, _______, KC_PIPE, KC_LCBR, KC_HASH, KC_RCBR, KC_BSLS,
			_______, _______, _______, _______, _______, _______, _______,  _______, KC_ENT,  _______, _______, _______
			),

	/* Number Layer
	 * ,-----------------------------------------------------------------------------------------------------------.
	 * |   :    |        |        |        |        |        |        |   *    |   7    |   8    |   9    |   0    | 
	 * |        |        |        |        |        |        |        |        |        |        |        |        |
	 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
	 * |   #    |        | CopyCut| Paste  |   +    |        |        |   .    |   4    |   5    |   6    |   /    |
	 * |        |        |        |        |        |        |        |        |        |        |        |        |
	 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
	 * |   €    |   x    |   £    |   =    |   -    |        |        |   ,    |   1    |   2    |   3    |   \    |
	 * |        |        |        |        |        |        |        |        |        |        |        |        |
	 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
	 * |        |        |        |  f()   |        |        |        |        |        |        |        |        |
	 * |        |        |        | Number |        |        |        |        |        |        |        |        |
	 * `--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------'
	 *
	 */
	[_NUMBER] = LAYOUT_planck_grid(
			KC_COLN, S(KC_F), S(KC_E), S(KC_D), S(KC_G), _______, _______, KC_ASTR, KC_7,    KC_8,    KC_9,    KC_0,
			KC_HASH, S(KC_C), TD(COPYCUT), PASTE, KC_PLUS, _______, _______, KC_DOT,  KC_4,    KC_5,    KC_6,    KC_SLSH,
			EURO,    KC_X,    GBP,     KC_EQL,  KC_MINS, _______, _______, KC_COMM, KC_1,    KC_2,    KC_3,    KC_BSLS,
			_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
			),

	/* Mouse Layer
	 * ,-----------------------------------------------------------------------------------------------------------.
	 * |  Ctrl  |  Alt   |  GUI   |        |        |        |        |        | Left   |   Up   | Right  |  wUp   |
	 * |        |        |        |        |        |        |        |        | scrl   |        | scrl   |        |
	 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
	 * |  Btn3  |  Btn2  |  Btn1  | Shift  |        |        |        |        | Left   |  Down  | Right  |  wDn   |
	 * |        |        |        |        |        |        |        |        |        |        |        |        |
	 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
	 * |        |        |        |        |        |        |        |        |        |        |        |        |
	 * |        |        |        |        |        |        |        |        |        |        |        |        |
	 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
	 * |        |        |        |        |  f()   |        |        |  f()   |        |        |        |
	 * |        |        |        |        | Mouse  |        |        | Mouse  |        |        |        |        |
	 * `--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------'
	 */
	[_MOUSE] = LAYOUT_planck_grid(
			KC_LCTL, KC_LALT, KC_LGUI, _______, _______, _______, _______, _______, KC_WH_L, KC_MS_U, KC_WH_R, KC_WH_U,
			KC_BTN3, KC_BTN2, KC_BTN1, KC_LSFT, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D,
			_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
			_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
			),

	/* Thumb Layer
	 * ,-----------------------------------------------------------------------------------------------------------.
	 * | Vol +  |        | SC_CAPF| SC_CAPP|        | KRAKEN |        |        |Input L |        |        | CMD +  |
	 * |        |        |        |        | MUTE   |Reset(3x|        |        |        |        |        |        |
	 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
	 * | Vol -  |        |        | TypeFu | VOL +  |        |        |        | Caps   | emoji  | iterm  | CMD -  |
	 * |        |        |        |        |        |        |        |        | Lock   |        |        |        |
	 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
	 * | Mute   |        | VS_Code|  Vim   | VOL -  |        |        |        |        |        |        |        |
	 * |        |        |        |        |        |        |        |        |        |        |        |        |
	 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
	 * |        |        |        |        |        |        |        |        |  f()   |        |        |        |
	 * |        |        |        |        |        |        |        |        | Thumb  |        |        |        |
	 * `--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------'
	 */
	[_THUMB] = LAYOUT_planck_grid(
			KC__VOLUP, _______, SC_CAPF, SC_CAPP, _______, TD(TD_RESET), _______, _______, INPUT_L, _______, _______, TXT_PLS,
			KC__VOLDOWN, _______, SPOTIFY, TYPE_FU, _______,   _______, _______, _______, KC_CAPS, EMOJI,   ITERM,   TXT_MIN,
			KC__MUTE, _______, VS_CODE, _______, _______, _______, _______, _______, _______, _______, _______, _______,
			_______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______
			),

	/* Arrange Layer
	 * ,-----------------------------------------------------------------------------------------------------------.
	 * | 1/6th  | 2/6th  |  Full  |  5/6th |  6/6th | Restore|        |        | Top L  |  Top   | Top R  |        |
	 * |        |        | Screen |        |        |        |        |        |        |        |        |
	 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
	 * |  L 1/3 | L 2/3  | C 1/3  | R 2/3  | R 1/3  |        |        | Prev   | Left   | Bottom | Right  | Next   |
	 * |        |        |        |        |        |        |        |        |        |        |        |
	 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
	 * | L 5/6th| 3/6th  |        | 4/6th  | R 5/6th|        |        |        | Bottom | Center | Bottom |        |
	 * |        |        |        |        |        |        |        |        |  Left  |        | Right  |
	 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
	 * |        |        |        |        |        |        |  f()   |        |        |        |        |        |
	 * |        |        |        |        |        |        | Arrange|        |        |        |        |        |
	 * `--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------'
	 */
	[_ARRANGE] = LAYOUT_planck_grid(
			M_1_6,   M_2_6,   M_MAX,   M_5_6,   M_6_6,   M_REST,  _______, _______, M_TOPL,  M_TOP,   M_TOPR,  _______,
			M_L13,   M_L23,   M_C13,   M_R23,   M_R13,   _______, _______, M_PREV,  M_LEFT,  M_BOTT,  M_RGHT,  M_NEXT,
			M_L_56,   M_3_6,  _______,   M_4_6, M_R_56,  _______, _______, _______, M_BOTL,  M_CEN,   M_BOTR,  _______,
			_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
			),

	/* Function Layer
	 * ,-----------------------------------------------------------------------------------------------------------.
	 * | Ctrl   | Alt    |  GUI   |        |        |        |        |        |  F7    |  F8    |  F9    |  F10   |
	 * |        |        |        |        |        |        |        |        |        |        |        |
	 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
	 * |        |        |        | Shift  |        |        |        |        |  F4    |  F5    |  F6    |  F11   |
	 * |        |        |        |        |        |        |        |        |        |        |        |
	 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
	 * |        |        |        |        |        |        |        |        |  F1    |  F2    |  F3    |  F12   |
	 * |        |        |        |        |        |        |        |        |        |        |        |
	 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
	 * |        |        |        |        |        |        |        |  f()   |  f()   |        |        |        |
	 * |        |        |        |        |        |        |        |Function|Function|        |        |        |
	 * `--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------'
	 */
	[_FUNCTION] = LAYOUT_planck_grid(
			KC_LCTL, KC_LALT, KC_LGUI, _______, _______, _______, _______, KC_F13,  KC_F7,   KC_F8,   KC_F9,   KC_F10,
			_______, _______, _______, KC_LSFT, _______, _______, _______, KC_F14,  KC_F4,   KC_F5,   KC_F6,   KC_F11,
			_______, _______, _______, _______, _______, _______, _______, KC_F15,  KC_F1,   KC_F2,   KC_F3,   KC_F12,
			_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
			)

};

#ifdef AUDIO_ENABLE
float plover_song[][2]     = SONG(PLOVER_SOUND);
float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

uint32_t layer_state_set_user(uint32_t state) {
	state = update_tri_layer_state(state, _NAV, _THUMB, _FUNCTION);
	state = update_tri_layer_state(state, _SYMBOL, _NAV, _MOUSE);
	return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case EMAIL:
			if (record->event.pressed) {
				SEND_STRING(MY_EMAIL);
			}
			return false;
			break;
		case ITERM:
			if (record->event.pressed) {
				SEND_STRING(SS_LGUI(" "));
				SEND_STRING("iterm" SS_TAP(X_ENTER));
			}
			return false;
			break;
		case TYPE_FU:
			if (record->event.pressed) {
				SEND_STRING(SS_LGUI(" "));
				SEND_STRING("type fu" SS_TAP(X_ENTER));
			}
			return false;
			break;
		case VS_CODE:
			if (record->event.pressed) {
				SEND_STRING(SS_LGUI(" "));
				SEND_STRING("visual studio code" SS_TAP(X_ENTER));
			}
			return false;
			break;
		case EMOJI:
			if (record->event.pressed) {
				register_code(KC_LGUI);
				register_code(KC_LCTL);
				register_code(KC_SPC);
				unregister_code(KC_LGUI);
				unregister_code(KC_LCTL);
				unregister_code(KC_SPC);
			}
			return false;
			break;
		case SPOTIFY:
			if (record->event.pressed) {
				SEND_STRING(SS_LGUI(" "));
				SEND_STRING("spotify.app" SS_TAP(X_ENTER));
			}
			return false;
			break;
	}
	return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
	if (muse_mode) {
		if (muse_counter == 0) {
			uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
			if (muse_note != last_muse_note) {
				stop_note(compute_freq_for_midi_note(last_muse_note));
				play_note(compute_freq_for_midi_note(muse_note), 0xF);
				last_muse_note = muse_note;
			}
		}
		muse_counter = (muse_counter + 1) % muse_tempo;
	}
#endif
}

void matrix_init_user(void) {
	set_unicode_input_mode(UC_OSX);
}
