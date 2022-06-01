/* Copyright 2020 Josef Adamcik
 * Modification for VIA support and RGB underglow by Jens Bonk-Wiltfang
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

// Setting up what encoder rotation does. If your encoder can be pressed as a button, that function can be set in Via.

#ifdef ENCODER_ENABLE

// enum layers { BASE, WIN, GAME, SYM, NAV, WINNAV};
bool reversed = false;  // ADD this near the begining of keymap.c

uint8_t encoder_mode = 0;
enum encoder_modes { ARROWS, TASKS, MUSIC, PAGES, WHEEL };

enum custom_keycodes { ALT_TAB = SAFE_RANGE, ENCODER_MODE, SELECT_COPY };

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
	switch (keycode) {               // This will do most of the grunt work with the keycodes.
		case ALT_TAB:
		if (record->event.pressed) {
			if (!is_alt_tab_active) {
			is_alt_tab_active = true;
			register_code(KC_LALT);
			}
			alt_tab_timer = timer_read();
			register_code(KC_TAB);
		} else {
			unregister_code(KC_TAB);
		}
		break;
	}
    switch (keycode) {
        case ENCODER_MODE:
            if (record->event.pressed) {
                encoder_mode = encoder_mode + 1;
                if (encoder_mode > WHEEL) {
                    encoder_mode = ARROWS;
                }
            }
            break;
        default:
            break;
    }
    return true;
}

//----------------------------------------------------------
// Sync
#    include <print.h>
#    include <string.h>
#    include <transactions.h>

void slave_encoder_mode_sync(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer, uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
	memcpy(&encoder_mode, initiator2target_buffer, sizeof(encoder_mode)); }

void user_state_sync(void) {
    if (is_keyboard_master()) {
        // Send to slave every 500ms
        static uint32_t last_sync = 0;
        if (timer_elapsed32(last_sync) > 500) {
            last_sync = timer_read32();
            transaction_rpc_send(RPC_ID_SYNC_ENUM, sizeof(encoder_mode), &encoder_mode);
        }
    }
}

void housekeeping_task_user(void) {
    // Data sync from master to slave
    user_state_sync();
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (encoder_mode == ARROWS) {  // on Nav layer controls window
        if (index == 0) {
            if (clockwise) {
                tap_code16(KC_UP);
            } else {
                tap_code16(KC_DOWN);
            }
        } else if (index == 1) {
            if (clockwise) {
                tap_code16(KC_LEFT);
            } else {
                tap_code16(KC_RIGHT);
            }
        }
    } else if (encoder_mode == TASKS) {  // on Nav layer controls window
        if (!IS_LAYER_ON(WIN)) {
            if (index == 0) {
                if (clockwise) {
                    tap_code16(C(KC_TAB));
                } else {
                    tap_code16(C(S(KC_TAB)));
                }

            } else if (index == 1) {
                if (clockwise) {
                    tap_code16(G(S(KC_GRV)));
                } else {
                    tap_code16(G(KC_GRV));
                }
            }
        } else {
            if (index == 0) {
                if (clockwise) {
                    tap_code16(C(KC_TAB));
                } else {
                    tap_code16(C(S(KC_TAB)));
                }

            } else if (index == 1) {
                if (clockwise) {
                    tap_code16(C(S(KC_GRV)));
                } else {
                    tap_code16(C(KC_GRV));
                }
            }
        }
    } else if (encoder_mode == MUSIC) {  // on Nav layer controls window
        if (index == 0) {
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
        } else if (index == 1) {
            if (clockwise) {
                tap_code(KC_MPRV);
            } else {
                tap_code(KC_MNXT);
            }
        }
    } else if (encoder_mode == WHEEL) {  // on Nav layer controls window
        if (index == 0) {
            if (clockwise) {
                tap_code16(KC_WH_D);
            } else {
                tap_code16(KC_WH_U);
            }
        } else if (index == 1) {
            if (clockwise) {
                tap_code16(KC_WH_R);
            } else {
                tap_code16(KC_WH_L);
            }
        }
    } else {
        if (index == 0) {
            if (!clockwise) {
                tap_code16(KC_PGDOWN);
            } else {
                tap_code16(KC_PGUP);
            }
        } else if (index == 1) {
            if (!clockwise) {
                tap_code16(A(KC_PGUP));
            } else {
                tap_code16(A(KC_PGDOWN));
            }
        }
    }
    return true;
}
#endif
