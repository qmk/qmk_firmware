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
#    include "process_auto_shift.h"

#    ifndef AUTO_SHIFT_DISABLED_AT_STARTUP
#        define AUTO_SHIFT_STARTUP_STATE true /* enabled */
#    else
#        define AUTO_SHIFT_STARTUP_STATE false /* disabled */
#    endif

// Stores the last Auto Shift key's up or down time, for evaluation or keyrepeat.
static uint16_t autoshift_time = 0;
#    if defined(RETRO_SHIFT) && !defined(NO_ACTION_TAPPING)
// Stores the last key's up or down time, to replace autoshift_time so that Tap Hold times are accurate.
static uint16_t retroshift_time = 0;
// Stores a possibly Retro Shift key's up or down time, as retroshift_time needs
// to be set before the Retro Shift key is evaluated if it is interrupted by an
// Auto Shifted key.
static uint16_t last_retroshift_time;
#    endif
static uint16_t    autoshift_timeout = AUTO_SHIFT_TIMEOUT;
static uint16_t    autoshift_lastkey = KC_NO;
static keyrecord_t autoshift_lastrecord;
// Keys take 8 bits if modifiers are excluded. This records the shift state
// when pressed for each key, so that can be passed to the release function
// and it knows which key needs to be released (if shifted is different base).
static uint16_t autoshift_shift_states[((1 << 8) + 15) / 16];
static struct {
    // Whether Auto Shift is enabled.
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
    // clang-format wants to remove the true for some reason.
    // clang-format off
} autoshift_flags = {AUTO_SHIFT_STARTUP_STATE, false, false, false, false, false};
// clang-format on

/** \brief Called on physical press, returns whether key should be added to Auto Shift */
__attribute__((weak)) bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    return false;
}

/** \brief Called on physical press, returns whether is Auto Shift key */
__attribute__((weak)) bool get_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
#    ifndef NO_AUTO_SHIFT_ALPHA
        case AUTO_SHIFT_ALPHA:
#    endif
#    ifndef NO_AUTO_SHIFT_NUMERIC
        case AUTO_SHIFT_NUMERIC:
#    endif
#    ifndef NO_AUTO_SHIFT_SPECIAL
        case AUTO_SHIFT_SPECIAL:
#    endif
            return true;
    }
    return get_custom_auto_shifted_key(keycode, record);
}

/** \brief Called to check whether defines should apply if PER_KEY is set for it */
__attribute__((weak)) bool get_auto_shift_repeat(uint16_t keycode, keyrecord_t *record) {
    return true;
}
__attribute__((weak)) bool get_auto_shift_no_auto_repeat(uint16_t keycode, keyrecord_t *record) {
    return true;
}

/** \brief Called when an Auto Shift key needs to be pressed */
__attribute__((weak)) void autoshift_press_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
    if (shifted) {
        add_weak_mods(MOD_BIT(KC_LSFT));
    }
    register_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode);
}

/** \brief Called when an Auto Shift key needs to be released */
__attribute__((weak)) void autoshift_release_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
    unregister_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode);
}

/** \brief Sets the shift state to use when keyrepeating, required by custom shifts */
void set_autoshift_shift_state(uint16_t keycode, bool shifted) {
    keycode = keycode & 0xFF;
    if (shifted) {
        autoshift_shift_states[keycode / 16] |= (uint16_t)1 << keycode % 16;
    } else {
        autoshift_shift_states[keycode / 16] &= ~((uint16_t)1 << keycode % 16);
    }
}

/** \brief Gets the shift state to use when keyrepeating, required by custom shifts */
bool get_autoshift_shift_state(uint16_t keycode) {
    keycode = keycode & 0xFF;
    return (autoshift_shift_states[keycode / 16] & (uint16_t)1 << keycode % 16) != (uint16_t)0;
}

/** \brief Restores the shift key if it was cancelled by Auto Shift */
static void autoshift_flush_shift(void) {
    autoshift_flags.holding_shift = false;
#    ifdef CAPS_WORD_ENABLE
    if (!is_caps_word_on())
#    endif // CAPS_WORD_ENABLE
    {
        del_weak_mods(MOD_BIT(KC_LSFT));
    }
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
    // clang-format off
    if ((get_mods()
#    if !defined(NO_ACTION_ONESHOT) && !defined(NO_ACTION_TAPPING)
            | get_oneshot_mods()
#    endif
        ) & (~MOD_BIT(KC_LSFT))
    ) {
        // clang-format on
        // Prevents keyrepeating unshifted value of key after using it in a key combo.
        autoshift_lastkey = KC_NO;
#    ifndef AUTO_SHIFT_MODIFIERS
        // We can't return true here anymore because custom unshifted values are
        // possible and there's no good way to tell whether the press returned
        // true upon release.
        set_autoshift_shift_state(keycode, false);
        autoshift_press_user(keycode, false, record);
#        if !defined(NO_ACTION_ONESHOT) && !defined(NO_ACTION_TAPPING)
        set_oneshot_mods(get_oneshot_mods() & (~MOD_BIT(KC_LSFT)));
        clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
#        endif
        return false;
#    endif
    }

    // Store record to be sent to user functions if there's no release record then.
    autoshift_lastrecord               = *record;
    autoshift_lastrecord.event.pressed = false;
    autoshift_lastrecord.event.time    = 0;
    // clang-format off
#    if defined(AUTO_SHIFT_REPEAT) || defined(AUTO_SHIFT_REPEAT_PER_KEY)
    if (keycode == autoshift_lastkey &&
#        ifdef AUTO_SHIFT_REPEAT_PER_KEY
        get_auto_shift_repeat(autoshift_lastkey, record) &&
#        endif
#        if !defined(AUTO_SHIFT_NO_AUTO_REPEAT) || defined(AUTO_SHIFT_NO_AUTO_REPEAT_PER_KEY)
        (
            !autoshift_flags.lastshifted
#            ifdef AUTO_SHIFT_NO_AUTO_REPEAT_PER_KEY
            || get_auto_shift_no_auto_repeat(autoshift_lastkey, record)
#            endif
        ) &&
#        endif
        TIMER_DIFF_16(now, autoshift_time) < GET_TAPPING_TERM(autoshift_lastkey, record)
    ) {
        // clang-format on
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
 * If autoshift_timeout has elapsed, register a shift and the key.
 *
 * If the Auto Shift key is released before the delay has elapsed, register the
 * key without a shift.
 *
 * Called on key down with keycode=KC_NO, auto-shifted key up, and timeout.
 */
static void autoshift_end(uint16_t keycode, uint16_t now, bool matrix_trigger, keyrecord_t *record) {
    if (autoshift_flags.in_progress && (keycode == autoshift_lastkey || keycode == KC_NO)) {
        // Process the auto-shiftable key.
        autoshift_flags.in_progress = false;
        // clang-format off
        autoshift_flags.lastshifted =
            autoshift_flags.lastshifted
            || TIMER_DIFF_16(now, autoshift_time) >=
#    ifdef AUTO_SHIFT_TIMEOUT_PER_KEY
                get_autoshift_timeout(autoshift_lastkey, record)
#    else
                autoshift_timeout
#    endif
        ;
        // clang-format on
        set_autoshift_shift_state(autoshift_lastkey, autoshift_flags.lastshifted);
        if (get_mods() & MOD_BIT(KC_LSFT)) {
            autoshift_flags.cancelling_lshift = true;
            del_mods(MOD_BIT(KC_LSFT));
        }
        if (get_mods() & MOD_BIT(KC_RSFT)) {
            autoshift_flags.cancelling_rshift = true;
            del_mods(MOD_BIT(KC_RSFT));
        }
        autoshift_press_user(autoshift_lastkey, autoshift_flags.lastshifted, record);

        // clang-format off
#    if (defined(AUTO_SHIFT_REPEAT) || defined(AUTO_SHIFT_REPEAT_PER_KEY)) && (!defined(AUTO_SHIFT_NO_AUTO_REPEAT) || defined(AUTO_SHIFT_NO_AUTO_REPEAT_PER_KEY))
        if (matrix_trigger
#        ifdef AUTO_SHIFT_REPEAT_PER_KEY
            && get_auto_shift_repeat(autoshift_lastkey, record)
#        endif
#        ifdef AUTO_SHIFT_NO_AUTO_REPEAT_PER_KEY
            && !get_auto_shift_no_auto_repeat(autoshift_lastkey, record)
#        endif
        ) {
            // Prevents release.
            return;
        }
#    endif
        // clang-format on
#    if TAP_CODE_DELAY > 0
        wait_ms(TAP_CODE_DELAY);
#    endif

        autoshift_release_user(autoshift_lastkey, autoshift_flags.lastshifted, record);
        autoshift_flush_shift();
    } else {
        // Release after keyrepeat.
        autoshift_release_user(keycode, get_autoshift_shift_state(keycode), record);
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
        if (TIMER_DIFF_16(now, autoshift_time) >=
#    ifdef AUTO_SHIFT_TIMEOUT_PER_KEY
            get_autoshift_timeout(autoshift_lastkey, &autoshift_lastrecord)
#    else
            autoshift_timeout
#    endif
        ) {
            autoshift_end(autoshift_lastkey, now, true, &autoshift_lastrecord);
        }
    }
}

void autoshift_toggle(void) {
    autoshift_flags.enabled = !autoshift_flags.enabled;
    autoshift_flush_shift();
}

void autoshift_enable(void) {
    autoshift_flags.enabled = true;
}

void autoshift_disable(void) {
    autoshift_flags.enabled = false;
    autoshift_flush_shift();
}

#    ifndef AUTO_SHIFT_NO_SETUP
void autoshift_timer_report(void) {
#        ifdef SEND_STRING_ENABLE
    const char *autoshift_timeout_str = get_u16_str(autoshift_timeout, ' ');
    // Skip padding spaces
    while (*autoshift_timeout_str == ' ') {
        autoshift_timeout_str++;
    }
    send_string(autoshift_timeout_str);
#        endif
}
#    endif

bool get_autoshift_state(void) {
    return autoshift_flags.enabled;
}

uint16_t get_generic_autoshift_timeout() {
    return autoshift_timeout;
}
__attribute__((weak)) uint16_t get_autoshift_timeout(uint16_t keycode, keyrecord_t *record) {
    return autoshift_timeout;
}

void set_autoshift_timeout(uint16_t timeout) {
    autoshift_timeout = timeout;
}

bool process_auto_shift(uint16_t keycode, keyrecord_t *record) {
    // Note that record->event.time isn't reliable, see:
    // https://github.com/qmk/qmk_firmware/pull/9826#issuecomment-733559550
    // clang-format off
    const uint16_t now =
#    if !defined(RETRO_SHIFT) || defined(NO_ACTION_TAPPING)
        timer_read()
#    else
        (record->event.pressed) ? retroshift_time : timer_read()
#    endif
    ;
    // clang-format on

    if (record->event.pressed) {
        if (autoshift_flags.in_progress) {
            // Evaluate previous key if there is one.
            autoshift_end(KC_NO, now, false, &autoshift_lastrecord);
        }

        switch (keycode) {
            case AS_TOGG:
                autoshift_toggle();
                break;
            case AS_ON:
                autoshift_enable();
                break;
            case AS_OFF:
                autoshift_disable();
                break;

#    ifndef AUTO_SHIFT_NO_SETUP
            case AS_UP:
                autoshift_timeout += 5;
                break;
            case AS_DOWN:
                autoshift_timeout -= 5;
                break;
            case AS_RPT:
                autoshift_timer_report();
                break;
#    endif
        }
        // If Retro Shift is disabled, possible custom actions shouldn't happen.
        // clang-format off
        if (IS_RETRO(keycode)
#    if defined(RETRO_SHIFT) && !defined(NO_ACTION_TAPPING)
            // Not tapped or #defines mean that rolls should use hold action.
            && (
                record->tap.count == 0
#        ifdef RETRO_TAPPING_PER_KEY
                || !get_retro_tapping(keycode, record)
#        endif
                || (record->tap.interrupted && (IS_LT(keycode)
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
                ))
            )
#    endif
        ) {
            // clang-format on
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
        // clang-format off
        else if (IS_RETRO(keycode)
#    if defined(RETRO_SHIFT) && !defined(NO_ACTION_TAPPING)
            && (
                record->tap.count == 0
#        ifdef RETRO_TAPPING_PER_KEY
                || !get_retro_tapping(keycode, record)
#        endif
            )
#    endif
        ) {
            // Fixes modifiers not being applied to rolls with AUTO_SHIFT_MODIFIERS set.
#    if !defined(IGNORE_MOD_TAP_INTERRUPT) || defined(IGNORE_MOD_TAP_INTERRUPT_PER_KEY)
            if (autoshift_flags.in_progress
#        ifdef IGNORE_MOD_TAP_INTERRUPT_PER_KEY
                && !get_ignore_mod_tap_interrupt(keycode, record)
#        endif
            ) {
                autoshift_end(KC_NO, now, false, &autoshift_lastrecord);
            }
#    endif
            // clang-format on
            return true;
        }
    }

    if (!autoshift_flags.enabled) {
        return true;
    }
    if (get_auto_shifted_key(keycode, record)) {
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
void retroshift_poll_time(keyevent_t *event) {
    last_retroshift_time = retroshift_time;
    retroshift_time      = timer_read();
}
// Used to swap the times of Retro Shifted key and Auto Shift key that interrupted it.
void retroshift_swap_times() {
    if (last_retroshift_time != 0 && autoshift_flags.in_progress) {
        uint16_t temp        = retroshift_time;
        retroshift_time      = last_retroshift_time;
        last_retroshift_time = temp;
    }
}
#    endif

#endif
