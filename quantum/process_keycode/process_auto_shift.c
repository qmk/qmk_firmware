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

// Stores the last Auto Shift key's up or down time, for evaluation or keyrepeat.
static uint16_t autoshift_time    = 0;
static uint16_t autoshift_timeout = AUTO_SHIFT_TIMEOUT;
static uint16_t autoshift_lastkey = KC_NO;
#    ifdef RETRO_SHIFT
#define IS_LT(kc) ((kc) >= QK_LAYER_TAP && (kc) <= QK_LAYER_TAP_MAX)
#define IS_RETRO(kc) (((kc) >= QK_MOD_TAP && (kc) <= QK_MOD_TAP_MAX) || IS_LT(kc))
#    endif
// Keys take 8 bits if modifiers are excluded. This records the shift state
// when pressed for each key, so that can be passed to the release function
// and it knows which key needs to be released (if shifted is different base).
static bool autoshift_shift_states[256];
static struct {
    // Whether autoshift is enabled.
    bool enabled : 1;
    // Whether the last auto-shifted key was released after the timeout.  This
    // is used to replicate the last key for a tap-then-hold.
    bool lastshifted : 1;
    // Whether an auto-shiftable key has been pressed but not processed.
    bool in_progress : 1;
    // Whether the auto-shifted keypress has been registered.
    bool holding_shift : 1;
    // Whether the user is holding a shift and we removed it.
    bool cancelling_lshift : 1;
    bool cancelling_rshift : 1;
} autoshift_flags = {true, false, false, false, false, false};

// Called on physical press, returns whether is autoshift key.
__attribute__((weak)) bool autoshift_is_custom(uint16_t keycode) {
    return false;
}

// Called when an autoshift key needs to be pressed.
__attribute__((weak)) void autoshift_press_user(uint16_t keycode, bool shifted) {
    if (shifted) { add_weak_mods(MOD_BIT(KC_LSFT)); }
    register_code(keycode & 0xFF);
}

// Called when an autoshift key needs to be released.
__attribute__((weak)) void autoshift_release_user(uint16_t keycode, bool shifted) {
    unregister_code(keycode & 0xFF);
}

/** \brief Releases the shift key if it was held by autoshift */
static void autoshift_flush_shift(void) {
    autoshift_flags.holding_shift = false;
    del_weak_mods(MOD_BIT(KC_LSFT));
    if (autoshift_flags.cancelling_lshift) {
        autoshift_flags.cancelling_lshift = false;
        add_mods(MOD_BIT(KC_LSFT));
    }
    if (autoshift_flags.cancelling_rshift) {
        autoshift_flags.cancelling_rshift = false;
        add_mods(MOD_BIT(KC_RSFT));
    }
    send_keyboard_report();
}

/** \brief Record the press of an autoshiftable key
 *
 *  \return Whether the record should be further processed.
 */
static bool autoshift_press(uint16_t keycode, uint16_t now, keyrecord_t *record) {
    if (!autoshift_flags.enabled) {
        return true;
    }

#    ifndef AUTO_SHIFT_MODIFIERS
    if (get_mods()) {
        return true;
    }
#    endif
#    ifdef AUTO_SHIFT_REPEAT
    const uint16_t elapsed = TIMER_DIFF_16(now, autoshift_time);
#        ifndef AUTO_SHIFT_NO_AUTO_REPEAT
    if (!autoshift_flags.lastshifted) {
#        endif
        if (elapsed < TAPPING_TERM && keycode == autoshift_lastkey) {
            // Allow a tap-then-hold for keyrepeat.
            if (get_mods() & MOD_BIT(KC_LSFT)) {
                autoshift_flags.cancelling_lshift = true;
                del_mods(MOD_BIT(KC_LSFT));
            }
            if (get_mods() & MOD_BIT(KC_RSFT)) {
                autoshift_flags.cancelling_rshift = true;
                del_mods(MOD_BIT(KC_RSFT));
            }
            // autoshift_shift_state doesn't need to be changed.
            autoshift_press_user(autoshift_lastkey, autoshift_flags.lastshifted);
            return false;
        }
#        ifndef AUTO_SHIFT_NO_AUTO_REPEAT
    }
#        endif
#    endif

    // Record the keycode so we can simulate it later.
    autoshift_flags.lastshifted = get_mods() & MOD_BIT(KC_LSFT);
    autoshift_lastkey           = keycode;
    autoshift_time              = now;
    autoshift_flags.in_progress = true;

#    if !defined(NO_ACTION_ONESHOT) && !defined(NO_ACTION_TAPPING)
    clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
#    endif
    return false;
}

/** \brief Registers an autoshiftable key under the right conditions
 *
 * If the autoshift delay has elapsed, register a shift and the key.
 *
 * If the autoshift key is released before the delay has elapsed, register the
 * key without a shift.
 */
static void autoshift_end(uint16_t keycode, uint16_t now, bool matrix_trigger) {
    // Called on key down with KC_NO, auto-shifted key up, and timeout.
    if (autoshift_flags.in_progress && (keycode == autoshift_lastkey || keycode == KC_NO)) {
        // Process the auto-shiftable key.
        autoshift_flags.in_progress = false;

        // Time since the initial press was recorded.
        const uint16_t elapsed                           = TIMER_DIFF_16(now, autoshift_time);
        autoshift_flags.lastshifted                      = !(elapsed < autoshift_timeout) || autoshift_flags.lastshifted;
        autoshift_shift_states[autoshift_lastkey & 0xFF] = autoshift_flags.lastshifted;
        if (get_mods() & MOD_BIT(KC_LSFT)) {
            autoshift_flags.cancelling_lshift = true;
            del_mods(MOD_BIT(KC_LSFT));
        }
        if (get_mods() & MOD_BIT(KC_RSFT)) {
            autoshift_flags.cancelling_rshift = true;
            del_mods(MOD_BIT(KC_RSFT));
        }
        autoshift_press_user(autoshift_lastkey, autoshift_flags.lastshifted);
#    if defined(AUTO_SHIFT_REPEAT) && !defined(AUTO_SHIFT_NO_AUTO_REPEAT)
            if (matrix_trigger) {
                // Prevents release.
                return;
            }
#    endif

#    if TAP_CODE_DELAY > 0
        wait_ms(TAP_CODE_DELAY);
#    endif
        autoshift_release_user(autoshift_lastkey, autoshift_shift_states[autoshift_lastkey & 0xFF]);
        autoshift_flush_shift();
    } else {
        // Release after keyrepeat.
        autoshift_release_user(keycode, autoshift_shift_states[keycode & 0xFF]);
        if (keycode == autoshift_lastkey) {
            // This will only fire when the key was the last auto-shiftable
            // pressed. That prevents 'aaaaBBBB' then releasing a from unshifting
            // later 'B's (if 'B' wasn't auto-shiftable).
            autoshift_flush_shift();
        }
    }
    // Roll the autoshift_time forward for detecting tap-and-hold.
    autoshift_time = now;
}

/** \brief Simulates auto-shifted key releases when timeout is hit
 *
 *  Can be called from \c matrix_scan_user so that auto-shifted keys are sent
 *  immediately after the timeout has expired, rather than waiting for the key
 *  to be released.
 */
void autoshift_matrix_scan(void) {
    if (autoshift_flags.in_progress) {
        const uint16_t now = timer_read();
        if (TIMER_DIFF_16(now, autoshift_time) >= autoshift_timeout) {
            autoshift_end(autoshift_lastkey, now, true);
        }
    }
}

void autoshift_toggle(void) {
    autoshift_flags.enabled = !autoshift_flags.enabled;
    autoshift_flush_shift();
}

void autoshift_enable(void) { autoshift_flags.enabled = true; }

void autoshift_disable(void) {
    autoshift_flags.enabled = false;
    autoshift_flush_shift();
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
    // Note that record->event.time isn't reliable, see:
    // https://github.com/qmk/qmk_firmware/pull/9826#issuecomment-733559550
    const uint16_t now =
#    ifndef RETRO_SHIFT
        timer_read()
#    else
        (record->event.pressed) ? autoshift_time : timer_read()
#    endif
    ;

    if (record->event.pressed) {
        if (autoshift_flags.in_progress) {
            // Evaluate previous key if there is one.
            autoshift_end(KC_NO, now, false);
        }

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
        }
#    ifdef RETRO_SHIFT
        if (IS_RETRO(keycode) && (record->tap.count == 0 || (record->tap.interrupted && ((IS_LT(keycode))
#        ifdef HOLD_ON_OTHER_KEYPRESS
            ? true
#        else
            ? false
#        endif
#        ifndef IGNORE_MOD_TAP_INTERRUPT
            : true
#        else
            : false
#        endif
        )))) {
            return true;
        }
#    endif
    } else {
        if (keycode == KC_LSFT) {
            autoshift_flags.cancelling_lshift = false;
        } else if (keycode == KC_RSFT) {
            autoshift_flags.cancelling_rshift = false;
        }
#    ifdef RETRO_SHIFT
        if (IS_RETRO(keycode) && record->tap.count == 0) {
            return true;
        }
#    endif
    }

    // TODO: Check for retro tapping per key here
    switch (keycode & 0xFF) {
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
            if (record->event.pressed) {
                return autoshift_press(keycode, now, record);
            } else {
                autoshift_end(keycode, now, false);
                return false;
            }
    }
    if (autoshift_is_custom(keycode)) {
        if (record->event.pressed) {
            return autoshift_press(keycode, now, record);
        } else {
            autoshift_end(keycode, now, false);
            return false;
        }
    }
    // Prevent keyrepeating of older keys.
    autoshift_lastkey = KC_NO;
    return true;
}

#    ifdef RETRO_SHIFT
void retro_shift_set_time(keyevent_t *event) {
    autoshift_time = timer_read();
}
#    endif
#endif
