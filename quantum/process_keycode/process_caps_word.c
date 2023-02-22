// Copyright 2021-2022 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "process_caps_word.h"

bool process_caps_word(uint16_t keycode, keyrecord_t* record) {
    if (keycode == QK_CAPS_WORD_TOGGLE) {
        if (record->event.pressed) {
            caps_word_toggle();
        }
        return false;
    }

#ifndef NO_ACTION_ONESHOT
    const uint8_t mods = get_mods() | get_oneshot_mods();
#else
    const uint8_t mods = get_mods();
#endif // NO_ACTION_ONESHOT

    if (!is_caps_word_on()) {
        // The following optionally turns on Caps Word by holding left and
        // right shifts or by double tapping left shift. This way Caps Word
        // may be used without needing a dedicated key and also without
        // needing combos or tap dance.

#ifdef BOTH_SHIFTS_TURNS_ON_CAPS_WORD
        // Many keyboards enable the Command feature by default, which also
        // uses left+right shift. It can be configured to use a different
        // key combination by defining IS_COMMAND(). We make a non-fatal
        // warning if Command is enabled but IS_COMMAND() is *not* defined.
#    if defined(COMMAND_ENABLE) && !defined(IS_COMMAND)
#        pragma message "BOTH_SHIFTS_TURNS_ON_CAPS_WORD and Command should not be enabled at the same time, since both use the Left Shift + Right Shift key combination. Please disable Command, or ensure that `IS_COMMAND` is not set to (get_mods() == MOD_MASK_SHIFT)."
#    else
        if (mods == MOD_MASK_SHIFT
#        ifdef COMMAND_ENABLE
            // Don't activate Caps Word at the same time as Command.
            && !(IS_COMMAND())
#        endif // COMMAND_ENABLE
        ) {
            caps_word_on();
        }
#    endif     // defined(COMMAND_ENABLE) && !defined(IS_COMMAND)
#endif         // BOTH_SHIFTS_TURNS_ON_CAPS_WORD

#ifdef DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD
        // Double tapping left shift turns on Caps Word.
        //
        // NOTE: This works with KC_LSFT and one-shot left shift. It
        // wouldn't make sense with mod-tap or Space Cadet shift since
        // double tapping would of course trigger the tapping action.
        if (record->event.pressed) {
            static bool     tapped = false;
            static uint16_t timer  = 0;
            if (keycode == KC_LSFT || keycode == OSM(MOD_LSFT)) {
                if (tapped && !timer_expired(record->event.time, timer)) {
                    // Left shift was double tapped, activate Caps Word.
                    caps_word_on();
                }
                tapped = true;
                timer  = record->event.time + GET_TAPPING_TERM(keycode, record);
            } else {
                tapped = false; // Reset when any other key is pressed.
            }
        }
#endif // DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD

        return true;
    }

#if CAPS_WORD_IDLE_TIMEOUT > 0
    caps_word_reset_idle_timer();
#endif // CAPS_WORD_IDLE_TIMEOUT > 0

    // From here on, we only take action on press events.
    if (!record->event.pressed) {
        return true;
    }

    if (!(mods & ~(MOD_MASK_SHIFT | MOD_BIT(KC_RALT)))) {
        switch (keycode) {
            // Ignore MO, TO, TG, TT, and OSL layer switch keys.
            case QK_MOMENTARY ... QK_MOMENTARY_MAX:
            case QK_TO ... QK_TO_MAX:
            case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX:
            case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
            case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
            // Ignore AltGr.
            case KC_RALT:
            case OSM(MOD_RALT):
                return true;

#ifndef NO_ACTION_TAPPING
            // Corresponding to mod keys above, a held mod-tap is handled as:
            // * For shift mods, pass KC_LSFT or KC_RSFT to
            //   caps_word_press_user() to determine whether to continue.
            // * For Shift + AltGr (MOD_RSFT | MOD_RALT), pass RSFT(KC_RALT).
            // * AltGr (MOD_RALT) is ignored.
            // * Otherwise stop Caps Word.
            case QK_MOD_TAP ... QK_MOD_TAP_MAX:
                if (record->tap.count == 0) { // Mod-tap key is held.
                    const uint8_t mods = QK_MOD_TAP_GET_MODS(keycode);
                    switch (mods) {
                        case MOD_LSFT:
                            keycode = KC_LSFT;
                            break;
                        case MOD_RSFT:
                            keycode = KC_RSFT;
                            break;
                        case MOD_RSFT | MOD_RALT:
                            keycode = RSFT(KC_RALT);
                            break;
                        case MOD_RALT:
                            return true;
                        default:
                            caps_word_off();
                            return true;
                    }
                } else {
                    keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
                }
                break;

#    ifndef NO_ACTION_LAYER
            case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
#    endif // NO_ACTION_LAYER
                if (record->tap.count == 0) {
                    return true;
                }
                keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
                break;
#endif // NO_ACTION_TAPPING

#ifdef SWAP_HANDS_ENABLE
            case QK_SWAP_HANDS ... QK_SWAP_HANDS_MAX:
                // Note: IS_SWAP_HANDS_KEYCODE() actually tests for the special action keycodes like SH_TG, SH_TT, ...,
                // which currently overlap the SH_T(kc) range.
                if (IS_SWAP_HANDS_KEYCODE(keycode) || record->tap.count == 0) {
                    return true;
                }
                keycode = QK_SWAP_HANDS_GET_TAP_KEYCODE(keycode);
                break;
#endif // SWAP_HANDS_ENABLE
        }

#ifdef AUTO_SHIFT_ENABLE
        del_weak_mods(get_autoshift_state() ? ~MOD_BIT(KC_LSFT) : 0xff);
#else
        clear_weak_mods();
#endif // AUTO_SHIFT_ENABLE
        if (caps_word_press_user(keycode)) {
            send_keyboard_report();
            return true;
        }
    }

    caps_word_off();
    return true;
}

__attribute__((weak)) bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case KC_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT)); // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;

        default:
            return false; // Deactivate Caps Word.
    }
}
