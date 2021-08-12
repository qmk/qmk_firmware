/*
  Copyright 2020 Joel Elkins <joel@elkins.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "jdelkins.h"
#include "version.h"

#ifdef DO_SECRETS
#  include "secrets.h"
#else
#  ifndef NO_SECRETS
#    pragma message("Warning: secrets.h not found")
#  endif
#endif

user_config_t user_config;

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}

void send_secret_string(uint8_t n) {
#ifdef DO_SECRETS
    send_string(secret[n]);
#else
    SEND_STRING("");
#endif
}

#ifdef TAP_DANCE_ENABLE

// To activate SINGLE_HOLD, you will need to hold for 200ms first.
// This tap dance favors keys that are used frequently in typing like 'f'
int cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        // If count = 1, and it has been interrupted - it doesn't matter if it
        // is pressed or not: Send SINGLE_TAP
        if (state->interrupted) {
            //     if (!state->pressed) return SINGLE_TAP;
            // need "permissive hold" here.
            //     else return SINsGLE_HOLD;
            // If the interrupting key is released before the tap-dance key,
            // then it is a single HOLD However, if the tap-dance key is
            // released first, then it is a single TAP But how to get access to
            // the state of the interrupting key????
            return SINGLE_TAP;
        } else {
            if (!state->pressed)
                return SINGLE_TAP;
            else
                return SINGLE_HOLD;
        }
    }
    // If count = 2, and it has been interrupted - assume that user is trying to
    // type the letter associated with single tap.
    else if (state->count == 2) {
        if (state->interrupted)
            return DOUBLE_SINGLE_TAP;
        else if (state->pressed)
            return DOUBLE_HOLD;
        else
            return DOUBLE_TAP;
    } else if ((state->count == 3) && ((state->interrupted) || (!state->pressed)))
        return TRIPLE_TAP;
    else if (state->count == 3)
        return TRIPLE_HOLD;
    else
        return 8;  // magic number. At some point this method will expand to work for more presses
}

// This works well if you want this key to work as a "fast modifier". It favors
// being held over being tapped.
int hold_cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted) {
            if (!state->pressed)
                return SINGLE_TAP;
            else
                return SINGLE_HOLD;
        } else {
            if (!state->pressed)
                return SINGLE_TAP;
            else
                return SINGLE_HOLD;
        }
    }
    // If count = 2, and it has been interrupted - assume that user is trying to
    // type the letter associated with single tap.
    else if (state->count == 2) {
        if (state->pressed)
            return DOUBLE_HOLD;
        else
            return DOUBLE_TAP;
    } else if (state->count == 3) {
        if (!state->pressed)
            return TRIPLE_TAP;
        else
            return TRIPLE_HOLD;
    } else
        return 8;  // magic number. At some point this method will expand to work for more presses
}

#endif // TAP_DANCE_ENABLE

__attribute__ ((weak))
void keyboard_post_init_keymap(void) {
}

void keyboard_post_init_user(void) {
    user_config.raw = eeconfig_read_user();
    keyboard_post_init_keymap();
}

void eeconfig_init_user(void) {
    user_config.raw = 0;
    user_config.system_mac = false;
    eeconfig_update_user(user_config.raw);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t boot_timer;

    if (!process_record_keymap(keycode, record)) {
        return false;
    }

    switch (keycode) {
        case FW_WRD:
            do_mac_key(LCTL(KC_RIGHT), ROPT(KC_RIGHT), record);
            break;

        case BK_WRD:
            do_mac_key(LCTL(KC_LEFT), ROPT(KC_LEFT), record);
            break;

        case KB_BOL:
            do_mac_key(KC_HOME, RCMD(KC_LEFT), record);
            break;

        case KB_EOL:
            do_mac_key(KC_END, RCMD(KC_RIGHT), record);
            break;

        case TG_SYS:
            if (record->event.pressed) {
                user_config.system_mac ^= 1;
                eeconfig_update_user(user_config.raw);
            }
            break;

        case KB_COPY:
            do_mac_key(LCTL(KC_INS), RCMD(KC_C), record);
            break;

        case KB_PASTE:
            do_mac_key(LSFT(KC_INS), RCMD(KC_V), record);
            break;

        case MY_GUI:
            do_mac_key(KC_LGUI, KC_LOPT, record);
            break;

        case MY_ALT:
            do_mac_key(KC_LALT, KC_LCMD, record);
            break;

        case MY_RGUI:
            do_mac_key(KC_RGUI, KC_ROPT, record);
            break;

        case MY_RALT:
            do_mac_key(KC_RALT, KC_RCMD, record);
            break;

        case MY_CALC:
            do_mac_key(KC_CALC, KC_F14, record);
            break;

        case KB_MAKE:
            if (!get_mods()) {
                if (!record->event.pressed)
                    SEND_STRING("make " QMK_KEYBOARD ":" QMK_KEYMAP SS_TAP(X_ENTER));
                return false;
            }
            break;

        case KB_VRSN:
            if (!get_mods()) {
                if (!record->event.pressed) {
                    if (user_config.system_mac) {
                        SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION " (mac mode)");
                    } else {
                        SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION " (non-mac mode)");
                    }
                }
                return false;
            }
            break;

        case KB_BOOT:
            if (!get_mods()) {
                if (record->event.pressed) {
                    boot_timer = timer_read32();
                } else {
                    if (timer_elapsed32(boot_timer) >= 500) {
                        reset_keyboard();
                    }
                }
                return false;
            }
            break;

        case KB_FLSH:
            if (!get_mods()) {
                if (!record->event.pressed) {
                    SEND_STRING("make " QMK_KEYBOARD ":" QMK_KEYMAP ":flash\n");
                    reset_keyboard();
                }
                return false;
            }
            break;

#ifdef DO_SECRETS
        case KC_SECRET_1 ... KC_SECRET_5: // Secrets!  Externally defined strings, not stored in repo
            if (!record->event.pressed) {
                clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
                send_secret_string(keycode - KC_SECRET_1);
            }
            return false;
            break;
#endif
    }

    return true;
}

__attribute__ ((weak))
void matrix_init_keymap(void) {
}

void matrix_init_user(void) {
    matrix_init_keymap();
}

__attribute__ ((weak))
void matrix_scan_keymap(void) {
}

void matrix_scan_user(void) {
    matrix_scan_keymap();
}

__attribute__ ((weak))
layer_state_t layer_state_set_keymap(layer_state_t state) {
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return layer_state_set_keymap(state);
}
