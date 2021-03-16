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
static keyrecord_t autoshift_lastrecord;
#define IS_LT(kc) ((kc) >= QK_LAYER_TAP && (kc) <= QK_LAYER_TAP_MAX)
#define IS_RETRO(kc) (((kc) >= QK_MOD_TAP && (kc) <= QK_MOD_TAP_MAX) || IS_LT(kc))
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
__attribute__((weak)) bool autoshift_is_custom(uint16_t keycode, keyrecord_t *record) { return false; }

// Called when an autoshift key needs to be pressed.
__attribute__((weak)) void autoshift_press_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
    if (shifted) { add_weak_mods(MOD_BIT(KC_LSFT)); }
    register_code(keycode & 0xFF);
}

// Called when an autoshift key needs to be released.
__attribute__((weak)) void autoshift_release_user(uint16_t keycode, bool shifted, keyrecord_t *record) { unregister_code(keycode & 0xFF); }

/** \brief Restores the shift key if it was cancelled by autoshift */
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
    if ((get_mods()
#    if !defined(NO_ACTION_ONESHOT) && !defined(NO_ACTION_TAPPING)
        | get_oneshot_mods()
#    endif
    ) & (~MOD_BIT(KC_LSFT))) {
        // Prevents keyrepeating unshifted value of key after using it in a key combo.
        autoshift_lastkey = KC_NO;
#    ifndef AUTO_SHIFT_MODIFIERS
        // We can't return true here anymore because custom unshifted values are
        // possible and there's no good way to tell whether the press returned
        // true upon release.
        autoshift_shift_states[keycode & 0xFF] = false;
        autoshift_press_user(keycode, false, record);
        return false;
#    endif
    }

    // Store record to be sent to user functions if there's no release record then.
    autoshift_lastrecord = *record;
    autoshift_lastrecord.event.pressed = false;
    autoshift_lastrecord.event.time = 0;
#    ifdef AUTO_SHIFT_REPEAT
#        ifndef AUTO_SHIFT_NO_AUTO_REPEAT
    if (!autoshift_flags.lastshifted) {
#        endif
        if (TIMER_DIFF_16(now, autoshift_time) < TAPPING_TERM && keycode == autoshift_lastkey) {
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
            autoshift_press_user(autoshift_lastkey, autoshift_flags.lastshifted, record);
            return false;
        }
#        ifndef AUTO_SHIFT_NO_AUTO_REPEAT
    }
#        endif
#    endif

    // Use physical shift state of press event to be more like normal typing.
#    if !defined(NO_ACTION_ONESHOT) && !defined(NO_ACTION_TAPPING)
    autoshift_flags.lastshifted = (get_mods() | get_oneshot_mods()) & MOD_BIT(KC_LSFT);
    set_oneshot_mods(get_oneshot_mods() & (~MOD_BIT(KC_LSFT)));
#    else
    autoshift_flags.lastshifted = get_mods() & MOD_BIT(KC_LSFT);
#    endif
    // Record the keycode so we can simulate it later.
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
 *
 * Called on key down with keycode=KC_NO, auto-shifted key up, and timeout.
 */
static void autoshift_end(uint16_t keycode, uint16_t now, bool matrix_trigger, keyrecord_t *record) {
    if (autoshift_flags.in_progress && (keycode == autoshift_lastkey || keycode == KC_NO)) {
        // Process the auto-shiftable key.
        autoshift_flags.in_progress                      = false;
        autoshift_flags.lastshifted                      = !(TIMER_DIFF_16(now, autoshift_time) < autoshift_timeout) || autoshift_flags.lastshifted;
        autoshift_shift_states[autoshift_lastkey & 0xFF] = autoshift_flags.lastshifted;
        if (get_mods() & MOD_BIT(KC_LSFT)) {
            autoshift_flags.cancelling_lshift = true;
            del_mods(MOD_BIT(KC_LSFT));
        }
        if (get_mods() & MOD_BIT(KC_RSFT)) {
            autoshift_flags.cancelling_rshift = true;
            del_mods(MOD_BIT(KC_RSFT));
        }
        autoshift_press_user(autoshift_lastkey, autoshift_flags.lastshifted, record);
#    if defined(AUTO_SHIFT_REPEAT) && !defined(AUTO_SHIFT_NO_AUTO_REPEAT)
            if (matrix_trigger) {
                // Prevents release.
                return;
            }
#    endif

#    if TAP_CODE_DELAY > 0
        wait_ms(TAP_CODE_DELAY);
#    endif
        autoshift_release_user(autoshift_lastkey, autoshift_shift_states[autoshift_lastkey & 0xFF], record);
        autoshift_flush_shift();
    } else {
        // Release after keyrepeat.
        autoshift_release_user(keycode, autoshift_shift_states[keycode & 0xFF], record);
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
            autoshift_end(autoshift_lastkey, now, true, &autoshift_lastrecord);
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
#    if !defined(RETRO_SHIFT) || defined(NO_ACTION_TAPPING)
        timer_read()
#    else
        (record->event.pressed) ? autoshift_time : timer_read()
#    endif
    ;

    if (record->event.pressed) {
        if (autoshift_flags.in_progress) {
            // Evaluate previous key if there is one.
            autoshift_end(KC_NO, now, false, &autoshift_lastrecord);
        }

        switch (keycode) {
            case KC_ASTG:
                autoshift_toggle();
                break;
            case KC_ASON:
                autoshift_enable();
                break;
            case KC_ASOFF:
                autoshift_disable();
                break;

#    ifndef AUTO_SHIFT_NO_SETUP
            case KC_ASUP:
                autoshift_timeout += 5;
                break;
            case KC_ASDN:
                autoshift_timeout -= 5;
                break;
            case KC_ASRP:
                autoshift_timer_report();
                break;
#    endif
        }
        // If Retro Shift is disabled, possible custom actions shouldn't happen.
        if (IS_RETRO(keycode)
#    if defined(RETRO_SHIFT) && !defined(NO_ACTION_TAPPING)
            // Not tapped or #defines mean that rolls should use hold action.
            && (record->tap.count == 0 || (record->tap.interrupted && (IS_LT(keycode)
#        if defined(HOLD_ON_OTHER_KEY_PRESS) || defined(HOLD_ON_OTHER_KEY_PRESS_PER_KEY)
#            ifdef HOLD_ON_OTHER_KEY_PRESS_PER_KEY
                ? get_hold_on_other_key_press(keycode, record)
#            else
                ? true
#            endif
#        else
                ? false
#        endif
#        if defined(IGNORE_MOD_TAP_INTERRUPT) || defined(IGNORE_MOD_TAP_INTERRUPT_PER_KEY)
#            ifdef IGNORE_MOD_TAP_INTERRUPT_PER_KEY
                : !get_ignore_mod_tap_interrupt(keycode, record)
#            else
                : false
#            endif
#        else
                : true
#        endif
            )))
#    endif
        ) {
            autoshift_lastkey = KC_NO;
            return true;
        }
    } else {
        if (keycode == KC_LSFT) {
            autoshift_flags.cancelling_lshift = false;
        } else if (keycode == KC_RSFT) {
            autoshift_flags.cancelling_rshift = false;
        }
        // Same as above (for pressed), additional checks are not needed because
        // tap.count gets set to 0 in process_action
        else if (IS_RETRO(keycode)
#    if defined(RETRO_SHIFT) && !defined(NO_ACTION_TAPPING)
            && record->tap.count == 0
#    endif
        ) {
            return true;
        }
    }

    if (!autoshift_flags.enabled) {
        return true;
    }

#    if defined(RETRO_TAPPING_PER_KEY) && defined(RETRO_SHIFT) && !defined(NO_ACTION_TAPPING)
    if (IS_RETRO(keycode) && !get_retro_tapping(keycode, record)) {
        if (record->event.pressed) {
            autoshift_lastkey = KC_NO;
        }
        return true;
    }
#    endif

    // Tap Holds return before this if RETRO_SHIFT is disabled, & 0xFF is safe.
    switch (keycode & 0xFF) {
        default:
            if (!autoshift_is_custom(keycode, record)) {
                break;
            }
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
                autoshift_end(keycode, now, false, record);
                return false;
            }
    }

    // Prevent keyrepeating of older keys upon non-AS key event.
    // Not commented at above returns but they serve the same function.
    if (record->event.pressed) {
        autoshift_lastkey = KC_NO;
    }
    return true;
}

#    if defined(RETRO_SHIFT) && !defined(NO_ACTION_TAPPING)
// Called to record time before possible delays by action_tapping_process.
void retro_shift_set_time(keyevent_t *event) {
    autoshift_time = timer_read();
}
#    endif
#endif
