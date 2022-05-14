// Copyright 2022 Kevin Goldberg @kevkevco <hello@kevkev.co>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "caps_word.h"
#include "print.h" // For debugging purposes
#include "layers.h"
#include "keycodes.h"
#include "tap_dances.h"

bool caps_word_active = false; // kevkevco removed static keyword at beginning of line in order to use get_caps_word() in keymap.c

#if CAPS_WORD_IDLE_TIMEOUT > 0
#    if CAPS_WORD_IDLE_TIMEOUT < 100 || CAPS_WORD_IDLE_TIMEOUT > 30000
// Constrain timeout to a sensible range. With the 16-bit timer, the longest
// representable timeout is 32768 ms, rounded here to 30000 ms = half a minute.
#        error "caps_word: CAPS_WORD_IDLE_TIMEOUT must be between 100 and 30000 ms"
#    endif

static uint16_t idle_timer = 0;

void caps_word_task(void) {
    if (caps_word_active && timer_expired(timer_read(), idle_timer)) {
        caps_word_set(false);
    }
}
#endif // CAPS_WORD_IDLE_TIMEOUT > 0

bool process_caps_word(uint16_t keycode, keyrecord_t* record) {
#ifndef NO_ACTION_ONESHOT
    const uint8_t mods = get_mods() | get_oneshot_mods();
#else
    const uint8_t mods = get_mods();
#endif // NO_ACTION_ONESHOT

    if (!caps_word_active) {
        // Pressing both shift keys at the same time enables caps word.
        if ((mods & MOD_MASK_SHIFT) == MOD_MASK_SHIFT) {
            caps_word_set(true); // Activate Caps Word.
            return false;
        }
        return true;
    } else {
#if CAPS_WORD_IDLE_TIMEOUT > 0
        idle_timer = record->event.time + CAPS_WORD_IDLE_TIMEOUT;
#endif // CAPS_WORD_IDLE_TIMEOUT > 0
    }

    if (!record->event.pressed) {
        return true;
    }

    if (!(mods & ~MOD_MASK_SHIFT)) {
        dprintf("\nkeycode is %x", keycode);

        // Custom section to tweak Caps Word behavior on select keys
        switch (keycode) {
            case TD(GVES):
                process_tap_dance(GVES, record);
                caps_word_set(false);
            case TD(ISPT): //
                process_caps_word(KC_I, record);
                return true;
            case SFT_T(KC_DEL):
                process_caps_word(KC_DEL, record);
                return true;
            case GUI_T(KC_BSPC):
                clear_mods();
                dprintf("get mods is %x", get_mods());
                tap_code(KC_LNUM); // Dummy keypress to get rid of lingering shift modifier
                process_caps_word(KC_BSPC, record);
                dprintf("after sending kc_bspc caps word . get mods is %x", get_mods());
                return true;
            case TD(LPINKY):
                clear_mods();
                process_tap_dance(LPINKY, record);
                return true;
            case RGUI_T(KC_SPC):
                clear_mods();
                // SEND_STRING(SS_DELAY(300));
                if (IS_LAYER_ON(_SYMBOLS)) {
                    process_caps_word(KC_UNDS, record);
                    return true;
                } else {
                    caps_word_set(false);
                    return true;
                }
        }

        switch (keycode) {
            // Ignore MO, TO, TG, TT, and OSL layer switch keys.
            case QK_MOMENTARY ... QK_MOMENTARY_MAX:
            case QK_TO ... QK_TO_MAX:
            case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX:
            case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
            case QK_TAP_DANCE ... QK_TAP_DANCE_MAX: // Added by kevkevco to ignore tap dance keys
            case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
               dprint("\nignore section?");
                return true;

#ifndef NO_ACTION_TAPPING
            case QK_MOD_TAP ... QK_MOD_TAP_MAX:
               dprint("\nmodtap section?");
                if (record->tap.count == 0) {
                   dprint("\ncancelling modtap section?");
                    // Deactivate if a mod becomes active through holding a mod-tap key.
                    caps_word_set(false);
                    return true;
                }
                keycode &= 0xff;
                break;

#    ifndef NO_ACTION_LAYER
            case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
               dprint("\nlayer tap section?");

#    endif // NO_ACTION_LAYER
                if (record->tap.count == 0) {
                    return true;
                }
                keycode &= 0xff;
                break;
#endif // NO_ACTION_TAPPING

#ifdef SWAP_HANDS_ENABLE
            case QK_SWAP_HANDS ... QK_SWAP_HANDS_MAX:
                if (keycode > 0x56F0 || record->tap.count == 0) {
                    return true;
                }
                keycode &= 0xff;
                break;
#endif // SWAP_HANDS_ENABLE
        }

        if (caps_word_press_user(keycode)) {
            return true;
        }
    }

    caps_word_set(false); // Deactivate Caps Word.
    return true;
}

void caps_word_set(bool active) {
    if (active != caps_word_active) {
        if (active) {
            clear_mods();
#ifndef NO_ACTION_ONESHOT
            clear_oneshot_mods();
#endif // NO_ACTION_ONESHOT
#if CAPS_WORD_IDLE_TIMEOUT > 0
            idle_timer = timer_read() + CAPS_WORD_IDLE_TIMEOUT;
#endif // CAPS_WORD_IDLE_TIMEOUT > 0
        } else if ((get_weak_mods() & MOD_BIT(KC_LSFT)) != 0) {
            // If the weak shift mod is still on, turn it off and send an update to
            // the host computer.
            del_weak_mods(MOD_BIT(KC_LSFT));
            send_keyboard_report();
        }

        caps_word_active = active;
        caps_word_set_user(active);
    }
}

bool caps_word_get(void) {
    return caps_word_active;
}

__attribute__((weak)) void caps_word_set_user(bool active) {}

__attribute__((weak)) bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT)); // Apply shift to the next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_MINS:
        case KC_UNDS:
            return true;

        default:
            return false; // Deactivate Caps Word.
    }
}
