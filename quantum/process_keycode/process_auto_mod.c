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

#ifdef AUTO_MOD_ENABLE

#    include <stdbool.h>
#    include <stdio.h>
#    include "process_auto_mod.h"

#    ifndef AUTO_MOD_DISABLED_AT_STARTUP
#        define AUTO_MOD_STARTUP_STATE true /* enabled */
#    else
#        define AUTO_MOD_STARTUP_STATE false /* disabled */
#    endif

#ifdef AUTO_MOD_KEY_L
    #undef AUTO_MOD_KEY_L
#endif
#ifdef AUTO_MOD_KEY_R
    #undef AUTO_MOD_KEY_R
#endif

#if defined(AUTO_MOD_CTRL)
    #define AUTO_MOD_KEY_L KC_LCTL
    #define AUTO_MOD_KEY_R KC_RCTL
#elif defined(AUTO_MOD_ALT)
    #define AUTO_MOD_KEY_L KC_LALT
    #define AUTO_MOD_KEY_R KC_RALT
#elif defined(AUTO_MOD_GUI)
    #define AUTO_MOD_KEY_L KC_LGUI
    #define AUTO_MOD_KEY_R KC_RGUI
#else
    #define AUTO_MOD_KEY_L KC_LSFT
    #define AUTO_MOD_KEY_R KC_RSFT
#endif

// Stores the last Auto Mod key's up or down time, for evaluation or keyrepeat.
static uint16_t automod_time = 0;
#    if defined(RETRO_MOD) && !defined(NO_ACTION_TAPPING)
// Stores the last key's up or down time, to replace automod_time so that Tap Hold times are accurate.
static uint16_t retromod_time = 0;
// Stores a possibly Retro Mod key's up or down time, as retromod_time needs
// to be set before the Retro Mod key is evaluated if it is interrupted by an
// Auto Modded key.
static uint16_t last_retromod_time;
#    endif
static uint16_t    automod_timeout = AUTO_MOD_TIMEOUT;
static uint16_t    automod_lastkey = KC_NO;
static keyrecord_t automod_lastrecord;
// Keys take 8 bits if modifiers are excluded. This records the mod state
// when pressed for each key, so that can be passed to the release function
// and it knows which key needs to be released (if modded is different base).
static uint16_t automod_mod_states[((1 << 8) + 15) / 16];
static struct {
    // Whether Auto Mod is enabled.
    bool enabled : 1;
    // Whether the last auto-modded key was released after the timeout.  This
    // is used to replicate the last key for a tap-then-hold.
    bool lastmodded : 1;
    // Whether an auto-modable key has been pressed but not processed.
    bool in_progress : 1;
    // Whether the auto-modded keypress has been registered.
    bool holding_mod : 1;
    // Whether the user is holding a mod and we removed it.
    bool cancelling_lmod : 1;
    bool cancelling_rmod : 1;
    // clang-format wants to remove the true for some reason.
    // clang-format off
} automod_flags = {AUTO_MOD_STARTUP_STATE, false, false, false, false, false};
// clang-format on

/** \brief Called on physical press, returns whether key should be added to Auto Mod */
__attribute__((weak)) bool get_custom_auto_modded_key(uint16_t keycode, keyrecord_t *record) { return false; }

/** \brief Called on physical press, returns whether is Auto Mod key */
__attribute__((weak)) bool get_auto_modded_key(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
#    ifndef NO_AUTO_MOD_ALPHA
        case AUTO_MOD_ALPHA:
#    endif
#    ifndef NO_AUTO_MOD_NUMERIC
        case AUTO_MOD_NUMERIC:
#    endif
#    ifndef NO_AUTO_MOD_SPECIAL
        case AUTO_MOD_SPECIAL:
#    endif
            return true;
    }
    return get_custom_auto_modded_key(keycode, record);
}

/** \brief Called to check whether defines should apply if PER_KEY is set for it */
__attribute__((weak)) bool get_auto_mod_repeat(uint16_t keycode, keyrecord_t *record) { return true; }
__attribute__((weak)) bool get_auto_mod_no_auto_repeat(uint16_t keycode, keyrecord_t *record) { return true; }

/** \brief Called when an Auto Mod key needs to be pressed */
__attribute__((weak)) void automod_press_user(uint16_t keycode, bool modded, keyrecord_t *record) {
    if (modded) {
        add_weak_mods(MOD_BIT(AUTO_MOD_KEY_L));
    }
    register_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode);
}

/** \brief Called when an Auto Mod key needs to be released */
__attribute__((weak)) void automod_release_user(uint16_t keycode, bool modded, keyrecord_t *record) { unregister_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode); }

/** \brief Sets the mod state to use when keyrepeating, required by custom mods */
void set_automod_mod_state(uint16_t keycode, bool modded) {
    keycode = keycode & 0xFF;
    if (modded) {
        automod_mod_states[keycode / 16] |= (uint16_t)1 << keycode % 16;
    } else {
        automod_mod_states[keycode / 16] &= ~((uint16_t)1 << keycode % 16);
    }
}

/** \brief Gets the mod state to use when keyrepeating, required by custom mods */
bool get_automod_mod_state(uint16_t keycode) {
    keycode = keycode & 0xFF;
    return (automod_mod_states[keycode / 16] & (uint16_t)1 << keycode % 16) != (uint16_t)0;
}

/** \brief Restores the mod key if it was cancelled by Auto Mod */
static void automod_flush_mod(void) {
    automod_flags.holding_mod = false;
    del_weak_mods(MOD_BIT(AUTO_MOD_KEY_L));
    if (automod_flags.cancelling_lmod) {
        automod_flags.cancelling_lmod = false;
        add_mods(MOD_BIT(AUTO_MOD_KEY_L));
    }
    if (automod_flags.cancelling_rmod) {
        automod_flags.cancelling_rmod = false;
        add_mods(MOD_BIT(AUTO_MOD_KEY_R));
    }
    send_keyboard_report();
}

/** \brief Record the press of an automodable key
 *
 *  \return Whether the record should be further processed.
 */
static bool automod_press(uint16_t keycode, uint16_t now, keyrecord_t *record) {
    // clang-format off
    if ((get_mods()
#    if !defined(NO_ACTION_ONESHOT) && !defined(NO_ACTION_TAPPING)
            | get_oneshot_mods()
#    endif
        ) & (~MOD_BIT(AUTO_MOD_KEY_L))
    ) {
        // clang-format on
        // Prevents keyrepeating unmodded value of key after using it in a key combo.
        automod_lastkey = KC_NO;
#    ifndef AUTO_MOD_MODIFIERS
        // We can't return true here anymore because custom unmodded values are
        // possible and there's no good way to tell whether the press returned
        // true upon release.
        set_automod_mod_state(keycode, false);
        automod_press_user(keycode, false, record);
#        if !defined(NO_ACTION_ONESHOT) && !defined(NO_ACTION_TAPPING)
        set_oneshot_mods(get_oneshot_mods() & (~MOD_BIT(AUTO_MOD_KEY_L)));
        clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
#        endif
        return false;
#    endif
    }

    // Store record to be sent to user functions if there's no release record then.
    automod_lastrecord               = *record;
    automod_lastrecord.event.pressed = false;
    automod_lastrecord.event.time    = 0;
    // clang-format off
#    if defined(AUTO_MOD_REPEAT) || defined(AUTO_MOD_REPEAT_PER_KEY)
    if (keycode == automod_lastkey &&
#        ifdef AUTO_MOD_REPEAT_PER_KEY
        get_auto_mod_repeat(automod_lastkey, record) &&
#        endif
#        if !defined(AUTO_MOD_NO_AUTO_REPEAT) || defined(AUTO_MOD_NO_AUTO_REPEAT_PER_KEY)
        (
            !automod_flags.lastmodded
#            ifdef AUTO_MOD_NO_AUTO_REPEAT_PER_KEY
            || get_auto_mod_no_auto_repeat(automod_lastkey, record)
#            endif
        ) &&
#        endif
        TIMER_DIFF_16(now, automod_time) <
#        ifdef TAPPING_TERM_PER_KEY
        get_tapping_term(automod_lastkey, record)
#        else
        TAPPING_TERM
#        endif
    ) {
        // clang-format on
        // Allow a tap-then-hold for keyrepeat.
        if (get_mods() & MOD_BIT(AUTO_MOD_KEY_L)) {
            automod_flags.cancelling_lmod = true;
            del_mods(MOD_BIT(AUTO_MOD_KEY_L));
        }
        if (get_mods() & MOD_BIT(AUTO_MOD_KEY_R)) {
            automod_flags.cancelling_rmod = true;
            del_mods(MOD_BIT(AUTO_MOD_KEY_R));
        }
        // automod_mod_state doesn't need to be changed.
        automod_press_user(automod_lastkey, automod_flags.lastmodded, record);
        return false;
    }
#    endif

    // Use physical mod state of press event to be more like normal typing.
#    if !defined(NO_ACTION_ONESHOT) && !defined(NO_ACTION_TAPPING)
    automod_flags.lastmodded = (get_mods() | get_oneshot_mods()) & MOD_BIT(AUTO_MOD_KEY_L);
    set_oneshot_mods(get_oneshot_mods() & (~MOD_BIT(AUTO_MOD_KEY_L)));
#    else
    automod_flags.lastmodded = get_mods() & MOD_BIT(AUTO_MOD_KEY_L);
#    endif
    // Record the keycode so we can simulate it later.
    automod_lastkey           = keycode;
    automod_time              = now;
    automod_flags.in_progress = true;

#    if !defined(NO_ACTION_ONESHOT) && !defined(NO_ACTION_TAPPING)
    clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
#    endif
    return false;
}

/** \brief Registers an automodable key under the right conditions
 *
 * If automod_timeout has elapsed, register a mod and the key.
 *
 * If the Auto Mod key is released before the delay has elapsed, register the
 * key without a mod.
 *
 * Called on key down with keycode=KC_NO, auto-modded key up, and timeout.
 */
static void automod_end(uint16_t keycode, uint16_t now, bool matrix_trigger, keyrecord_t *record) {
    if (automod_flags.in_progress && (keycode == automod_lastkey || keycode == KC_NO)) {
        // Process the auto-modable key.
        automod_flags.in_progress = false;
        // clang-format off
        automod_flags.lastmodded =
            automod_flags.lastmodded
            || TIMER_DIFF_16(now, automod_time) >=
#    ifdef AUTO_MOD_TIMEOUT_PER_KEY
                get_automod_timeout(automod_lastkey, record)
#    else
                automod_timeout
#    endif
        ;
        // clang-format on
        set_automod_mod_state(automod_lastkey, automod_flags.lastmodded);
        if (get_mods() & MOD_BIT(AUTO_MOD_KEY_L)) {
            automod_flags.cancelling_lmod = true;
            del_mods(MOD_BIT(AUTO_MOD_KEY_L));
        }
        if (get_mods() & MOD_BIT(AUTO_MOD_KEY_R)) {
            automod_flags.cancelling_rmod = true;
            del_mods(MOD_BIT(AUTO_MOD_KEY_R));
        }
        automod_press_user(automod_lastkey, automod_flags.lastmodded, record);

        // clang-format off
#    if (defined(AUTO_MOD_REPEAT) || defined(AUTO_MOD_REPEAT_PER_KEY)) && (!defined(AUTO_MOD_NO_AUTO_REPEAT) || defined(AUTO_MOD_NO_AUTO_REPEAT_PER_KEY))
        if (matrix_trigger
#        ifdef AUTO_MOD_REPEAT_PER_KEY
            && get_auto_mod_repeat(automod_lastkey, record)
#        endif
#        ifdef AUTO_MOD_NO_AUTO_REPEAT_PER_KEY
            && !get_auto_mod_no_auto_repeat(automod_lastkey, record)
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

        automod_release_user(automod_lastkey, automod_flags.lastmodded, record);
        automod_flush_mod();
    } else {
        // Release after keyrepeat.
        automod_release_user(keycode, get_automod_mod_state(keycode), record);
        if (keycode == automod_lastkey) {
            // This will only fire when the key was the last auto-modable
            // pressed. That prevents 'aaaaBBBB' then releasing a from unmodding
            // later 'B's (if 'B' wasn't auto-modable).
            automod_flush_mod();
        }
    }
    // Roll the automod_time forward for detecting tap-and-hold.
    automod_time = now;
}

/** \brief Simulates auto-modded key releases when timeout is hit
 *
 *  Can be called from \c matrix_scan_user so that auto-modded keys are sent
 *  immediately after the timeout has expired, rather than waiting for the key
 *  to be released.
 */
void automod_matrix_scan(void) {
    if (automod_flags.in_progress) {
        const uint16_t now = timer_read();
        if (TIMER_DIFF_16(now, automod_time) >=
#    ifdef AUTO_MOD_TIMEOUT_PER_KEY
            get_automod_timeout(automod_lastkey, &automod_lastrecord)
#    else
            automod_timeout
#    endif
        ) {
            automod_end(automod_lastkey, now, true, &automod_lastrecord);
        }
    }
}

void automod_toggle(void) {
    automod_flags.enabled = !automod_flags.enabled;
    automod_flush_mod();
}

void automod_enable(void) { automod_flags.enabled = true; }

void automod_disable(void) {
    automod_flags.enabled = false;
    automod_flush_mod();
}

#    ifndef AUTO_MOD_NO_SETUP
void automod_timer_report(void) {
    char display[8];

    snprintf(display, 8, "\n%d\n", automod_timeout);

    send_string((const char *)display);
}
#    endif

bool get_automod_state(void) { return automod_flags.enabled; }

uint16_t                       get_generic_automod_timeout() { return automod_timeout; }
__attribute__((weak)) uint16_t get_automod_timeout(uint16_t keycode, keyrecord_t *record) { return automod_timeout; }

void set_automod_timeout(uint16_t timeout) { automod_timeout = timeout; }

bool process_auto_mod(uint16_t keycode, keyrecord_t *record) {
    // Note that record->event.time isn't reliable, see:
    // https://github.com/qmk/qmk_firmware/pull/9826#issuecomment-733559550
    // clang-format off
    const uint16_t now =
#    if !defined(RETRO_MOD) || defined(NO_ACTION_TAPPING)
        timer_read()
#    else
        (record->event.pressed) ? retromod_time : timer_read()
#    endif
    ;
    // clang-format on

    if (record->event.pressed) {
        if (automod_flags.in_progress) {
            // Evaluate previous key if there is one.
            automod_end(KC_NO, now, false, &automod_lastrecord);
        }

        switch (keycode) {
            case KC_AMTG:
                automod_toggle();
                break;
            case KC_AMON:
                automod_enable();
                break;
            case KC_AMOFF:
                automod_disable();
                break;

#    ifndef AUTO_MOD_NO_SETUP
            case KC_AMUP:
                automod_timeout += 5;
                break;
            case KC_AMDN:
                automod_timeout -= 5;
                break;
            case KC_AMRP:
                automod_timer_report();
                break;
#    endif
        }
        // If Retro Mod is disabled, possible custom actions shouldn't happen.
        // clang-format off
        if (IS_RETRO(keycode)
#    if defined(RETRO_MOD) && !defined(NO_ACTION_TAPPING)
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
            automod_lastkey = KC_NO;
            return true;
        }
    } else {
        if (keycode == AUTO_MOD_KEY_L) {
            automod_flags.cancelling_lmod = false;
        } else if (keycode == AUTO_MOD_KEY_R) {
            automod_flags.cancelling_rmod = false;
        }
        // Same as above (for pressed), additional checks are not needed because
        // tap.count gets set to 0 in process_action
        // clang-format off
        else if (IS_RETRO(keycode)
#    if defined(RETRO_MOD) && !defined(NO_ACTION_TAPPING)
            && (
                record->tap.count == 0
#        ifdef RETRO_TAPPING_PER_KEY
                || !get_retro_tapping(keycode, record)
#        endif
            )
#    endif
        ) {
            // Fixes modifiers not being applied to rolls with AUTO_MOD_MODIFIERS set.
#    if !defined(IGNORE_MOD_TAP_INTERRUPT) || defined(IGNORE_MOD_TAP_INTERRUPT_PER_KEY)
            if (automod_flags.in_progress
#        ifdef IGNORE_MOD_TAP_INTERRUPT_PER_KEY
                && !get_ignore_mod_tap_interrupt(keycode, record)
#        endif
            ) {
                automod_end(KC_NO, now, false, &automod_lastrecord);
            }
#    endif
            // clang-format on
            return true;
        }
    }

    if (!automod_flags.enabled) {
        return true;
    }
    if (get_auto_modded_key(keycode, record)) {
        if (record->event.pressed) {
            return automod_press(keycode, now, record);
        } else {
            automod_end(keycode, now, false, record);
            return false;
        }
    }

    // Prevent keyrepeating of older keys upon non-AM key event.
    // Not commented at above returns but they serve the same function.
    if (record->event.pressed) {
        automod_lastkey = KC_NO;
    }
    return true;
}

#    if defined(RETRO_MOD) && !defined(NO_ACTION_TAPPING)
// Called to record time before possible delays by action_tapping_process.
void retromod_poll_time(keyevent_t *event) {
    last_retromod_time = retromod_time;
    retromod_time      = timer_read();
}
// Used to swap the times of Retro Modded key and Auto Mod key that interrupted it.
void retromod_swap_times() {
    if (last_retromod_time != 0 && automod_flags.in_progress) {
        uint16_t temp      = retromod_time;
        retromod_time      = last_retromod_time;
        last_retromod_time = temp;
    }
}
#    endif

#endif
