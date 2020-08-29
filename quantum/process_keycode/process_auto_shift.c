/* Copyright 2017 Jeremy Cowgar
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

#ifdef AUTO_SHIFT_ENABLE

#    include <stdio.h>

#    include "process_auto_shift.h"

static bool     autoshift_enabled = true;
static uint16_t autoshift_time    = 0;
static uint16_t autoshift_timeout = AUTO_SHIFT_TIMEOUT;
static uint16_t autoshift_lastkey = KC_NO;

void autoshift_flush(void) {
    if (autoshift_lastkey != KC_NO) {
        uint16_t elapsed = timer_elapsed(autoshift_time);

        if (elapsed > autoshift_timeout) {
            tap_code16(LSFT(autoshift_lastkey));
        } else {
            tap_code(autoshift_lastkey);
        }

        autoshift_time    = 0;
        autoshift_lastkey = KC_NO;
    }
}

void autoshift_on(uint16_t keycode) {
    autoshift_time    = timer_read();
    autoshift_lastkey = keycode;
}

void autoshift_toggle(void) {
    if (autoshift_enabled) {
        autoshift_enabled = false;
        autoshift_flush();
    } else {
        autoshift_enabled = true;
    }
}

void autoshift_enable(void) { autoshift_enabled = true; }
void autoshift_disable(void) {
    autoshift_enabled = false;
    autoshift_flush();
}

#    ifndef AUTO_SHIFT_NO_SETUP
void autoshift_timer_report(void) {
    char display[8];

    snprintf(display, 8, "\n%d\n", autoshift_timeout);

    send_string((const char *)display);
}
#    endif

bool get_autoshift_state(void) { return autoshift_enabled; }

uint16_t get_autoshift_timeout(void) { return autoshift_timeout; }

void set_autoshift_timeout(uint16_t timeout) { autoshift_timeout = timeout; }

bool process_auto_shift(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case KC_ASTG:
                autoshift_toggle();
                return true;

            case KC_ASON:
                autoshift_enable();
                return true;
            case KC_ASOFF:
                autoshift_disable();
                return true;

#    ifndef AUTO_SHIFT_NO_SETUP
            case KC_ASUP:
                autoshift_timeout += 5;
                return true;
            case KC_ASDN:
                autoshift_timeout -= 5;
                return true;

            case KC_ASRP:
                autoshift_timer_report();
                return true;
#    endif
#    ifndef NO_AUTO_SHIFT_ALPHA
            case KC_A ... KC_Z:
#    endif
#    ifndef NO_AUTO_SHIFT_NUMERIC
            case KC_1 ... KC_0:
#    endif
#    ifndef NO_AUTO_SHIFT_SPECIAL
            case KC_TAB:
            case KC_MINUS ... KC_SLASH:
            case KC_NONUS_BSLASH:
#    endif
                autoshift_flush();
                if (!autoshift_enabled) return true;

#    ifndef AUTO_SHIFT_MODIFIERS
                if (get_mods()) {
                    return true;
                }
#    endif
                autoshift_on(keycode);

                // We need some extra handling here for OSL edge cases
#    if !defined(NO_ACTION_ONESHOT) && !defined(NO_ACTION_TAPPING)
                clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
#    endif
                return false;

            default:
                autoshift_flush();
                return true;
        }
    } else {
        autoshift_flush();
    }

    return true;
}

#endif
