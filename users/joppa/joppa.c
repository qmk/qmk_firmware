/* Copyright 2023 Jon Arne Viksås (@craftsmandigital)
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

#include "joppa.h"
#include "keyboard-layout.h" // Layout has its own file



uint16_t my_key_pressed_timer = 0;



// --------------------------------------------------------------------------------
// combos stuff
enum combo_events {
  JK_ESC,
  DF_TAB,
  NAV_TOGLE,
  SYM_TOGLE,
  NUM_TOGLE,
  MOUSE_TOGLE,
  GUI_NUM,
};

// combos stuff
const uint16_t PROGMEM jk_combo[] =  {LSFT_T(KC_J),		LCTL_T(KC_K),	COMBO_END};
const uint16_t PROGMEM df_combo[] =  {LSFT_T(KC_F), 	LCTL_T(KC_D),	COMBO_END};
const uint16_t PROGMEM nav_combo[] = {LT(NAV, KC_SPC),	LSFT_T(KC_J),	COMBO_END};
const uint16_t PROGMEM sym_combo[] = {LSFT_T(KC_F),		OSL(SYM),		COMBO_END};
const uint16_t PROGMEM num_combo[] = {LSFT_T(KC_F),		LT(NUM, KC_BSPC), COMBO_END};
const uint16_t PROGMEM mouse_combo[] = {LT(MOUSE, KC_DOT),LSFT_T(KC_J), COMBO_END};
const uint16_t PROGMEM gui_num_combo[] = {LCTL_T(KC_K), LALT_T(KC_L), COMBO_END};


combo_t key_combos[] = {
  [JK_ESC] = COMBO(jk_combo, KC_ESC),
  [DF_TAB] = COMBO(df_combo, KC_TAB),
  [NAV_TOGLE] = COMBO(nav_combo, TG(NAV)),
  [SYM_TOGLE] = COMBO(sym_combo, TG(SYM)),
  [NUM_TOGLE] = COMBO(num_combo, TG(NUM)),
  [GUI_NUM] = COMBO(gui_num_combo, MY_GUI_NUM),
  [MOUSE_TOGLE] = COMBO(mouse_combo, TG(MOUSE)),
  // [QW_SFT] = COMBO(qw_combo, KC_LSFT)
  // [SD_LAYER] = COMBO(layer_combo, MO(_LAYER)),
};

// --------------------------------------------------------------------------------
// Leadr key stuff


void leader_start_user(void) {
    // Do something when the leader key is pressed
}

void leader_end_user(void) {
    if (leader_sequence_one_key(KC_X)) {
	    register_code(KC_LCTL);
        register_code(KC_F4);
        unregister_code(KC_F4);
        unregister_code(KC_LCTL);
        // SEND_STRING(SS_DOWN(KC_LCTL)SS_TAP(KC_F4)SS_UP(KC_LCTL));
    } else if (leader_sequence_one_key(KC_Q)) {
	    register_code(KC_LALT);
        register_code(KC_F4);
        unregister_code(KC_F4);
        unregister_code(KC_LALT);
    } else if (leader_sequence_two_keys(KC_X, KC_X)) {
        SEND_STRING(SS_LCTL(SS_LSFT("t")));
	}
/*---------------------------------------------------------------*/		


/*---------------------------------------------------------------*/
}


// --------------------------------------------------------------------------------
// Macro stuff
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	

    switch (keycode) {
    case PAREN:
        if (record->event.pressed) {
            // when key ( is pressed
            SEND_STRING("()"SS_TAP(X_LEFT));
        }
        break;
    case BRACKET:
        if (record->event.pressed) {
			// when key [ is pressed
            SEND_STRING("[]"SS_TAP(X_LEFT));
        }
        break;
    case CURLEY:
        if (record->event.pressed) {
            // when key { is pressed
            SEND_STRING("{}"SS_TAP(X_LEFT));
        }
        break;
    case QUOT:
        if (record->event.pressed) {
            // when key ' is pressed
            SEND_STRING("''"SS_TAP(X_LEFT));
        }
        break;
    case DQUOT:
        if (record->event.pressed) {
            // when key " is pressed
            SEND_STRING("\"\""SS_TAP(X_LEFT));
        }
        break;
	// The four next keys goes to their extremes on long tapp
	// and do shorter travel on short press
    case MY_END:
        if (record->event.pressed) {
            my_key_pressed_timer = timer_read();
        } else {
			// goes by word to the right when short pressed.
			if (timer_elapsed(my_key_pressed_timer) < LEADER_TIMEOUT) {
				register_code(KC_LCTL);
				tap_code(KC_RGHT);
				unregister_code(KC_LCTL);
			} else {
				// goes to end of line on long press
				tap_code(KC_END);
			}
		}
        break;
		case MY_HOME:
        if (record->event.pressed) {
            my_key_pressed_timer = timer_read();
        } else {
			if (timer_elapsed(my_key_pressed_timer) < LEADER_TIMEOUT) {
				register_code(KC_LCTL);
				tap_code(KC_LEFT);
				unregister_code(KC_LCTL);
			} else {
				tap_code(KC_HOME);
			}
		}
        break;
		case MY_COPY:
        if (record->event.pressed) {
            my_key_pressed_timer = timer_read();
        } else {
			if (timer_elapsed(my_key_pressed_timer) < LEADER_TIMEOUT) {
				register_code(KC_LCTL);
				tap_code(KC_C);
				unregister_code(KC_LCTL);
			} else {
				register_code(KC_LCTL);
				tap_code(KC_A);
				unregister_code(KC_LCTL);
			}
		}
		break;
		case MY_UNDRDO:
        if (record->event.pressed) {
            my_key_pressed_timer = timer_read();
        } else {
			if (timer_elapsed(my_key_pressed_timer) < LEADER_TIMEOUT) {
				register_code(KC_LCTL);
				tap_code(KC_Z);
				unregister_code(KC_LCTL);
			} else {
				register_code(KC_LCTL);
				tap_code(KC_Y);
				unregister_code(KC_LCTL);
			}
		}
        break;
		case MY_PASTE:
        if (record->event.pressed) {
            my_key_pressed_timer = timer_read();
        } else {
			register_code(KC_LCTL);
			if (timer_elapsed(my_key_pressed_timer) < LEADER_TIMEOUT) {
				register_code(KC_LSFT);
				tap_code(KC_V);
				unregister_code(KC_LSFT);
			} else {
				tap_code(KC_V);
			}
			unregister_code(KC_LCTL);
		}
        break;
		case MY_PGDN:
        if (record->event.pressed) {
            my_key_pressed_timer = timer_read();
        } else {
			if (timer_elapsed(my_key_pressed_timer) < LEADER_TIMEOUT) {
				tap_code(KC_PGDN);
			} else {
				register_code(KC_LCTL);
				tap_code(KC_END);
				unregister_code(KC_LCTL);
				
			}
		}
        break;
		case MY_PGUP:
        if (record->event.pressed) {
            my_key_pressed_timer = timer_read();
        } else {
			if (timer_elapsed(my_key_pressed_timer) < LEADER_TIMEOUT) {
				tap_code(KC_PGUP);
			} else {
				register_code(KC_LCTL);
				tap_code(KC_HOME);
				unregister_code(KC_LCTL);
				
			}
		}
		break;
		// Nordic caracter stuff is dependent of autohotkey
		// https://www.thenickmay.com/how-to-expand-text-for-free-with-autohotkey/
		// When keypress is shifted then keypress is different the char "-" becoms a "_"
		// auto hotkey schipt handles this and expand the right nordic character
		case _AA	:	// å Å
		if (record->event.pressed) {
				SEND_STRING("-&a");  // Becomes _&a when shifted
		}
		break;
		case _AE	:	// æ Æ
		if (record->event.pressed) {
				SEND_STRING("-&e");  // Becomes _&e when shifted
		}
		break;
		// case _OE	:	// ø Ø
		// if (record->event.pressed) {
				// SEND_STRING("-&o");  // Becomes _&o when shifted
		// }
		// break;
		case RGUI_T(_OE)	:	// ø Ø
		// This was extremely difficult to program, because of the nature of GUI modifier
		// It is also triggered on tap. luckyly the solution was quite easy. The solution was found on website under:
		// https://github.com/qmk/qmk_firmware/blob/master/docs/mod_tap.md#changing-tap-function.
		// The moust obious solution was something like the website under. 
		// But doestnt work because of the nature of the GUI modifier
		// https://thomasbaart.nl/2018/12/09/qmk-basics-tap-and-hold-actions/#a-workaround-for-mod-tap
		
		if (record->tap.count && record->event.pressed) {
			SEND_STRING("-&o"); // Send KC_DQUO on tap
			return false;        // Return false to ignore further processing of key
		}
		break;

    }
    return true;
};

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
    case MY_GUI_NUM:
	// This is a oneshotlayer and oneshot modifier at the same time
	// SYM layer and GUI modifier at once.
	// This makes it easy to switch apps in the taskbar in windows 10. 
	// The state before next key pressed is num layer and gui modifier.
	// When user press a nuber key, then it triggers to open or switching to that app in taskbar
        if (record->event.pressed) {
            // layer_on(NUM);
            set_oneshot_layer(NUM, ONESHOT_START);
            clear_oneshot_layer_state(ONESHOT_PRESSED);
			
			set_oneshot_mods(MOD_RGUI);
        } else {
			// clear_oneshot_layer_state(ONESHOT_PRESSED);
		}
        break;

    }

};
