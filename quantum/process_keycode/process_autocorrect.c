// Copyright 2021 Google LLC
// Copyright 2021 @filterpaper
// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: Apache-2.0
// Original source: https://getreuer.info/posts/keyboards/autocorrection

#include "process_autocorrect.h"
#include <string.h>
#include "keycodes.h"
#include "quantum_keycodes.h"
#include "keycode_config.h"
#include "send_string.h"
#include "action_util.h"

#if __has_include("autocorrect_data.h")
#    include "autocorrect_data.h"
#else
#    pragma message "Autocorrect is using the default library."
#    include "autocorrect_data_default.h"
#endif

static uint8_t typo_buffer[AUTOCORRECT_MAX_LENGTH] = {KC_SPC};
static uint8_t typo_buffer_size                    = 1;

/**
 * @brief function for querying the enabled state of autocorrect
 *
 * @return true if enabled
 * @return false if disabled
 */
bool autocorrect_is_enabled(void) {
    return keymap_config.autocorrect_enable;
}

/**
 * @brief Enables autocorrect and saves state to eeprom
 *
 */
void autocorrect_enable(void) {
    keymap_config.autocorrect_enable = true;
    eeconfig_update_keymap(&keymap_config);
}

/**
 * @brief Disables autocorrect and saves state to eeprom
 *
 */
void autocorrect_disable(void) {
    keymap_config.autocorrect_enable = false;
    typo_buffer_size                 = 0;
    eeconfig_update_keymap(&keymap_config);
}

/**
 * @brief Toggles autocorrect's status and save state to eeprom
 *
 */
void autocorrect_toggle(void) {
    keymap_config.autocorrect_enable = !keymap_config.autocorrect_enable;
    typo_buffer_size                 = 0;
    eeconfig_update_keymap(&keymap_config);
}

/**
 * @brief handler for user to override whether autocorrect should process this keypress
 *
 * @param keycode Keycode registered by matrix press, per keymap
 * @param record keyrecord_t structure
 * @param typo_buffer_size passed along to allow resetting of autocorrect buffer
 * @param mods allow processing of mod status
 * @return true Allow autocorection
 * @return false Stop processing and escape from autocorrect.
 */
__attribute__((weak)) bool process_autocorrect_user(uint16_t *keycode, keyrecord_t *record, uint8_t *typo_buffer_size, uint8_t *mods) {
    return process_autocorrect_default_handler(keycode, record, typo_buffer_size, mods);
}

/**
 * @brief fallback handler for determining if autocorrect should process this keypress
 *        can be used by user callback to get the basic keycode being "wrapped"
 *
 * NOTE: These values may have been edited by user callback before getting here
 *
 * @param keycode Keycode registered by matrix press, per keymap
 * @param record keyrecord_t structure
 * @param typo_buffer_size passed along to allow resetting of autocorrect buffer
 * @param mods allow processing of mod status
 * @return true Allow autocorection
 * @return false Stop processing and escape from autocorrect.
 */
bool process_autocorrect_default_handler(uint16_t *keycode, keyrecord_t *record, uint8_t *typo_buffer_size, uint8_t *mods) {
    // See quantum_keycodes.h for reference on these matched ranges.
    switch (*keycode) {
        // Exclude these keycodes from processing.
        case KC_LSFT:
        case KC_RSFT:
        case KC_CAPS:
        case QK_TO ... QK_TO_MAX:
        case QK_MOMENTARY ... QK_MOMENTARY_MAX:
        case QK_DEF_LAYER ... QK_DEF_LAYER_MAX:
        case QK_PERSISTENT_DEF_LAYER ... QK_PERSISTENT_DEF_LAYER_MAX:
        case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX:
        case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
        case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
        case QK_LAYER_MOD ... QK_LAYER_MOD_MAX:
        case QK_ONE_SHOT_MOD ... QK_ONE_SHOT_MOD_MAX:
            return false;

        // Mask for base keycode from shifted keys.
        case QK_LSFT ... QK_LSFT + 255:
        case QK_RSFT ... QK_RSFT + 255:
            if (*keycode >= QK_LSFT && *keycode <= (QK_LSFT + 255)) {
                *mods |= MOD_LSFT;
            } else {
                *mods |= MOD_RSFT;
            }
            *keycode = QK_MODS_GET_BASIC_KEYCODE(*keycode); // Get the basic keycode.
            return true;
#ifndef NO_ACTION_TAPPING
        // Exclude tap-hold keys when they are held down
        // and mask for base keycode when they are tapped.
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
#    ifdef NO_ACTION_LAYER
            // Exclude Layer Tap, if layers are disabled
            // but action tapping is still enabled.
            return false;
#    else
            // Exclude hold keycode
            if (!record->tap.count) {
                return false;
            }
            *keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(*keycode);
            break;
#    endif
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            // Exclude hold keycode
            if (!record->tap.count) {
                return false;
            }
            *keycode = QK_MOD_TAP_GET_TAP_KEYCODE(*keycode);
            break;
#else
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            // Exclude if disabled
            return false;
#endif
        // Exclude swap hands keys when they are held down
        // and mask for base keycode when they are tapped.
        case QK_SWAP_HANDS ... QK_SWAP_HANDS_MAX:
#ifdef SWAP_HANDS_ENABLE
            // Note: IS_SWAP_HANDS_KEYCODE() actually tests for the special action keycodes like SH_TOGG, SH_TT, ...,
            // which currently overlap the SH_T(kc) range.
            if (IS_SWAP_HANDS_KEYCODE(*keycode)
#    ifndef NO_ACTION_TAPPING
                || !record->tap.count
#    endif // NO_ACTION_TAPPING
            ) {
                return false;
            }
            *keycode = QK_SWAP_HANDS_GET_TAP_KEYCODE(*keycode);
            break;
#else
            // Exclude if disabled
            return false;
#endif
    }

    // Disable autocorrect while a mod other than shift is active.
    if ((*mods & ~MOD_MASK_SHIFT) != 0) {
        *typo_buffer_size = 0;
        return false;
    }

    return true;
}

/**
 * @brief handling for when autocorrection has been triggered
 *
 * @param backspaces number of characters to remove
 * @param str pointer to PROGMEM string to replace mistyped seletion with
 * @param typo the wrong string that triggered a correction
 * @param correct what it would become after the changes
 * @return true apply correction
 * @return false user handled replacement
 */
__attribute__((weak)) bool apply_autocorrect(uint8_t backspaces, const char *str, char *typo, char *correct) {
    return true;
}

/**
 * @brief Process handler for autocorrect feature
 *
 * @param keycode Keycode registered by matrix press, per keymap
 * @param record keyrecord_t structure
 * @return true Continue processing keycodes, and send to host
 * @return false Stop processing keycodes, and don't send to host
 */
bool process_autocorrect(uint16_t keycode, keyrecord_t *record) {
    uint8_t mods = get_mods();
#ifndef NO_ACTION_ONESHOT
    mods |= get_oneshot_mods();
#endif

    if ((keycode >= QK_AUTOCORRECT_ON && keycode <= QK_AUTOCORRECT_TOGGLE) && record->event.pressed) {
        if (keycode == QK_AUTOCORRECT_ON) {
            autocorrect_enable();
        } else if (keycode == QK_AUTOCORRECT_OFF) {
            autocorrect_disable();
        } else if (keycode == QK_AUTOCORRECT_TOGGLE) {
            autocorrect_toggle();
        } else {
            return true;
        }

        return false;
    }

    if (!keymap_config.autocorrect_enable) {
        typo_buffer_size = 0;
        return true;
    }

    if (!record->event.pressed) {
        return true;
    }

    // autocorrect keycode verification and extraction
    if (!process_autocorrect_user(&keycode, record, &typo_buffer_size, &mods)) {
        return true;
    }

    // keycode buffer check
    switch (keycode) {
        case KC_A ... KC_Z:
            // process normally
            break;
        case KC_1 ... KC_0:
        case KC_TAB ... KC_SEMICOLON:
        case KC_GRAVE ... KC_SLASH:
            // Set a word boundary if space, period, digit, etc. is pressed.
            keycode = KC_SPC;
            break;
        case KC_ENTER:
            // Behave more conservatively for the enter key. Reset, so that enter
            // can't be used on a word ending.
            typo_buffer_size = 0;
            keycode          = KC_SPC;
            break;
        case KC_BSPC:
            // Remove last character from the buffer.
            if (typo_buffer_size > 0) {
                --typo_buffer_size;
            }
            return true;
        case KC_QUOTE:
            // Treat " (shifted ') as a word boundary.
            if ((mods & MOD_MASK_SHIFT) != 0) {
                keycode = KC_SPC;
            }
            break;
        default:
            // Clear state if some other non-alpha key is pressed.
            typo_buffer_size = 0;
            return true;
    }

    // Rotate oldest character if buffer is full.
    if (typo_buffer_size >= AUTOCORRECT_MAX_LENGTH) {
        memmove(typo_buffer, typo_buffer + 1, AUTOCORRECT_MAX_LENGTH - 1);
        typo_buffer_size = AUTOCORRECT_MAX_LENGTH - 1;
    }

    // Append `keycode` to buffer.
    typo_buffer[typo_buffer_size++] = keycode;
    // Return if buffer is smaller than the shortest word.
    if (typo_buffer_size < AUTOCORRECT_MIN_LENGTH) {
        return true;
    }

    // Check for typo in buffer using a trie stored in `autocorrect_data`.
    uint16_t state = 0;
    uint8_t  code  = pgm_read_byte(autocorrect_data + state);
    for (int8_t i = typo_buffer_size - 1; i >= 0; --i) {
        uint8_t const key_i = typo_buffer[i];

        if (code & 64) { // Check for match in node with multiple children.
            code &= 63;
            for (; code != key_i; code = pgm_read_byte(autocorrect_data + (state += 3))) {
                if (!code) return true;
            }
            // Follow link to child node.
            state = (pgm_read_byte(autocorrect_data + state + 1) | pgm_read_byte(autocorrect_data + state + 2) << 8);
            // Check for match in node with single child.
        } else if (code != key_i) {
            return true;
        } else if (!(code = pgm_read_byte(autocorrect_data + (++state)))) {
            ++state;
        }

        // Stop if `state` becomes an invalid index. This should not normally
        // happen, it is a safeguard in case of a bug, data corruption, etc.
        if (state >= DICTIONARY_SIZE) {
            return true;
        }

        code = pgm_read_byte(autocorrect_data + state);

        if (code & 128) { // A typo was found! Apply autocorrect.
            const uint8_t backspaces = (code & 63) + !record->event.pressed;
            const char *  changes    = (const char *)(autocorrect_data + state + 1);

            /* Gather info about the typo'd word
             *
             * Since buffer may contain several words, delimited by spaces, we
             * iterate from the end to find the start and length of the typo
             */
            char typo[AUTOCORRECT_MAX_LENGTH + 1] = {0}; // extra char for null terminator

            uint8_t typo_len   = 0;
            uint8_t typo_start = 0;
            bool    space_last = typo_buffer[typo_buffer_size - 1] == KC_SPC;
            for (uint8_t i = typo_buffer_size; i > 0; --i) {
                // stop counting after finding space (unless it is the last thing)
                if (typo_buffer[i - 1] == KC_SPC && i != typo_buffer_size) {
                    typo_start = i;
                    break;
                }

                ++typo_len;
            }

            // when detecting 'typo:', reduce the length of the string by one
            if (space_last) {
                --typo_len;
            }

            // convert buffer of keycodes into a string
            for (uint8_t i = 0; i < typo_len; ++i) {
                typo[i] = typo_buffer[typo_start + i] - KC_A + 'a';
            }

            /* Gather the corrected word
             *
             * A) Correction of 'typo:' -- Code takes into account
             * an extra backspace to delete the space (which we dont copy)
             * for this reason the offset is correct to "skip" the null terminator
             *
             * B) When correcting 'typo' -- Need extra offset for terminator
             */
            char correct[AUTOCORRECT_MAX_LENGTH + 10] = {0}; // let's hope this is big enough

            uint8_t offset = space_last ? backspaces : backspaces + 1;
            strcpy(correct, typo);
            strcpy_P(correct + typo_len - offset, changes);

            if (apply_autocorrect(backspaces, changes, typo, correct)) {
                for (uint8_t i = 0; i < backspaces; ++i) {
                    tap_code(KC_BSPC);
                }
                send_string_P(changes);
            }

            if (keycode == KC_SPC) {
                typo_buffer[0]   = KC_SPC;
                typo_buffer_size = 1;
                return true;
            } else {
                typo_buffer_size = 0;
                return false;
            }
        }
    }
    return true;
}
