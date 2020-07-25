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

#    include <stdbool.h>
#    include <stdio.h>

#    include "process_auto_shift.h"

static uint16_t autoshift_time    = 0;
static uint16_t autoshift_timeout = AUTO_SHIFT_TIMEOUT;
static uint16_t autoshift_lastkey = KC_NO;
static struct {
    // Whether autoshift is enabled.
    bool enabled : 1;
    // Whether the last autoshifted key was released after the timeout.  This
    // is used to replicate the last key for a tap-then-hold.
    bool lastshifted : 1;
    // Whether an auto-shiftable key is currently being pressed.
    bool in_progress : 1;
    // Whether the auto-shifted keypress has been registered.
    bool registered : 1;
    // Whether autoshift is currently "holding" the shift key.
    bool holding_shift : 1;
} autoshift_flags = {true, false, false, false, false};

/** \brief Resets the autoshift state and releases the shift key */
static void autoshift_flush(uint16_t now) {
    if (autoshift_flags.holding_shift) {
        // Release the shift key if it was simulated.
        unregister_code(KC_LSFT);
    }
    // Roll the autoshift_time forward for detecting tap-and-hold.
    autoshift_time                = now;
    autoshift_flags.in_progress   = false;
    autoshift_flags.holding_shift = false;
    autoshift_flags.registered    = false;
}

/** \brief Record the press of an autoshiftable key
 *
 *  \return Whether the record should be further processed.
 */
static bool autoshift_press(uint16_t keycode, keyrecord_t *record) {
    if (!autoshift_flags.enabled) {
        return true;
    }

    autoshift_flush(record->event.time);

#    ifndef AUTO_SHIFT_MODIFIERS
    if (get_mods()) {
        return true;
    }
#    endif

    const uint16_t elapsed = TIMER_DIFF_16(record->event.time, autoshift_time);

#    ifndef TAPPING_FORCE_HOLD
    if (elapsed < TAPPING_TERM && keycode == autoshift_lastkey && !autoshift_flags.lastshifted) {
        // Allow a tap-then-hold to hold the unshifted key.
        autoshift_lastkey = KC_NO;
        return true;
    }
#    endif

    // Record the keycode so we can simulate it later.
    autoshift_time              = record->event.time;
    autoshift_lastkey           = keycode;
    autoshift_flags.in_progress = true;

#    if !defined(NO_ACTION_ONESHOT) && !defined(NO_ACTION_TAPPING)
    clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
#    endif
    return false;
}

/** \brief Registers an autoshiftable key under the right conditions
 *
 * If the autoshift delay has elapsed and no shift has already been registered,
 * register a shift and the key.
 */
void autoshift_check_timeout(uint16_t now) {
    const uint16_t elapsed = TIMER_DIFF_16(now, autoshift_time);
    if (elapsed >= autoshift_timeout) {
        // The timeout has expired, so simulate the keypress.
        if (!(get_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)))) {
            // Simulate pressing the shift key.
            register_code(KC_LSFT);
            autoshift_flags.lastshifted   = true;
            autoshift_flags.holding_shift = true;
        }
        register_code(autoshift_lastkey);
        autoshift_flags.registered = true;

#    if TAP_CODE_DELAY > 0
        wait_ms(TAP_CODE_DELAY);
#    endif
    }
}

/** \brief Registers an autoshiftable key under the right conditions
 *
 * If the autoshift delay has elapsed and no shift has already been registered,
 * register a shift and the key.
 *
 * If the autoshift key is released before the delay has elapsed, register the
 * key without a shift.
 */
static void autoshift_check_record(uint16_t keycode, keyrecord_t *record) {
    if (!autoshift_flags.in_progress) {
        return;
    }

    // Process the release of the autoshiftable key.
    if (keycode == autoshift_lastkey && !record->event.pressed) {
        // Time since the initial press was recorded.
        const uint16_t elapsed = TIMER_DIFF_16(record->event.time, autoshift_time);
        if (elapsed < autoshift_timeout) {
            autoshift_flags.lastshifted = false;
            // Auto-shiftable key is being released before the shift timeout;
            // simulate the original press then let the usual processing take
            // care of the release.
            register_code(keycode);
#    if TAP_CODE_DELAY > 0
            wait_ms(TAP_CODE_DELAY);
#    endif
        }
        autoshift_flush(record->event.time);
    } else if (keycode == KC_LSFT && record->event.pressed) {
        // If the user presses shift, auto-shift will not hold shift for
        // them.
        autoshift_flags.holding_shift = false;
    } else {
        // Use an unrelated event as an opportunity to check if the autoshift
        // timeout has expired.
        autoshift_check_timeout(record->event.time);
    }
}

/** \brief Simulates auto-shifted key presses
 *
 *  Can be called from \c matrix_scan_user so that auto-shifted keys are sent
 *  immediately after the timeout has expired, rather than waiting for the key
 *  to be released.
 */
void autoshift_matrix_scan(void) {
    if (!autoshift_flags.in_progress || autoshift_flags.registered) {
        return;
    }

    autoshift_check_timeout(timer_read());
}

void autoshift_toggle(void) {
    if (autoshift_flags.enabled) {
        autoshift_flags.enabled = false;
        autoshift_flush(0);
    } else {
        autoshift_flags.enabled = true;
    }
}

void autoshift_enable(void) {
    autoshift_flags.enabled = true;
    autoshift_flush(0);
}

void autoshift_disable(void) {
    autoshift_flags.enabled = false;
    autoshift_flush(0);
}

#    ifndef AUTO_SHIFT_NO_SETUP
void autoshift_timer_report(void) {
    char display[8];

    snprintf(display, 8, "\n%d\n", autoshift_timeout);

    send_string((const char *)display);
}
#    endif

bool get_autoshift_state(void) { return autoshift_flags.enabled; }

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
                return autoshift_press(keycode, record);

            default:
                break;
        }
    }

    autoshift_check_record(keycode, record);
    return true;
}

#endif
