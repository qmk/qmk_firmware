// Copyright 2021 Google LLC
// Copyright 2021 @filterpaper
// SPDX-License-Identifier: Apache-2.0
// Original source: https://getreuer.info/posts/keyboards/autocorrection

#include "autocorrection.h"
#include <string.h>

#if __has_include("autocorrection_data.h")
#    pragma GCC push_options
#    pragma GCC optimize("O0")
#    include "autocorrection_data.h"
#    ifndef AUTOCORRECTION_MIN_LENGTH
#        define AUTOCORRECTION_MIN_LENGTH AUTOCORRECT_MIN_LENGTH
#    endif
#    ifndef AUTOCORRECTION_MAX_LENGTH
#        define AUTOCORRECTION_MAX_LENGTH AUTOCORRECT_MAX_LENGTH
#    endif
#    define autocorrection_data autocorrect_data
#    if AUTOCORRECTION_MIN_LENGTH < 4
#        error Minimum Length is too short and may cause overflows
#    endif
#    if DICTIONARY_SIZE > SIZE_MAX
#        error Dictionary size excees maximum size permitted
#    endif

static uint8_t typo_buffer[AUTOCORRECT_MAX_LENGTH] = {KC_SPC};
static uint8_t typo_buffer_size                    = 1;

/**
 * @brief function for querying the enabled state of autocorrect
 *
 * @return true if enabled
 * @return false if disabled
 */
bool autocorrect_is_enabled(void) {
    return userspace_config.autocorrection;
}

/**
 * @brief Enables autocorrect and saves state to eeprom
 *
 */
void autocorrect_enable(void) {
    userspace_config.autocorrection = true;
    eeconfig_update_user(userspace_config.raw);
}

/**
 * @brief Disables autocorrect and saves state to eeprom
 *
 */
void autocorrect_disable(void) {
    userspace_config.autocorrection = false;
    typo_buffer_size                = 0;
    eeconfig_update_user(userspace_config.raw);
}

/**
 * @brief Toggles autocorrect's status and save state to eeprom
 *
 */
void autocorrect_toggle(void) {
    userspace_config.autocorrection = !userspace_config.autocorrection;
    typo_buffer_size                = 0;
    eeconfig_update_user(userspace_config.raw);
}

/**
 * @brief handler for determining if autocorrect should process keypress
 *
 * @param keycode Keycode registered by matrix press, per keymap
 * @param record keyrecord_t structure
 * @param typo_buffer_size passed along to allow resetting of autocorrect buffer
 * @param mods allow processing of mod status
 * @return true Allow autocorection
 * @return false Stop processing and escape from autocorrect.
 */
__attribute__((weak)) bool process_autocorrect_user(uint16_t *keycode, keyrecord_t *record, uint8_t *typo_buffer_size, uint8_t *mods) {
    // See quantum_keycodes.h for reference on these matched ranges.
    switch (*keycode) {
        // Exclude these keycodes from processing.
        case KC_LSFT:
        case KC_RSFT:
        case KC_CAPS:
        case QK_TO ... QK_ONE_SHOT_LAYER_MAX:
        case QK_LAYER_TAP_TOGGLE ... QK_LAYER_MOD_MAX:
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
            *keycode &= 0xFF; // Get the basic keycode.
            return true;
#    ifndef NO_ACTION_TAPPING
        // Exclude tap-hold keys when they are held down
        // and mask for base keycode when they are tapped.
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
#        ifdef NO_ACTION_LAYER
            // Exclude Layer Tap, if layers are disabled
            // but action tapping is still enabled.
            return false;
#        endif
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            // Exclude hold keycode
            if (!record->tap.count) {
                return false;
            }
            *keycode &= 0xFF;
            break;
#    else
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            // Exclude if disabled
            return false;
#    endif
        // Exclude swap hands keys when they are held down
        // and mask for base keycode when they are tapped.
        case QK_SWAP_HANDS ... QK_SWAP_HANDS_MAX:
#    ifdef SWAP_HANDS_ENABLE
            if (*keycode >= 0x56F0 || !record->tap.count) {
                return false;
            }
            *keycode &= 0xFF;
            break;
#    else
            // Exclude if disabled
            return false;
#    endif
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
 * @return true apply correction
 * @return false user handled replacement
 */
__attribute__((weak)) bool apply_autocorrect(uint8_t backspaces, const char *str) {
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
bool process_autocorrection(uint16_t keycode, keyrecord_t *record) {
    uint8_t mods = get_mods();
#    ifndef NO_ACTION_ONESHOT
    mods |= get_oneshot_mods();
#    endif

    if ((keycode >= AUTOCORRECT_ON && keycode <= AUTOCORRECT_TOGGLE) && record->event.pressed) {
        if (keycode == AUTOCORRECT_ON) {
            autocorrect_enable();
        } else if (keycode == AUTOCORRECT_OFF) {
            autocorrect_disable();
        } else if (keycode == AUTOCORRECT_TOGGLE) {
            autocorrect_toggle();
        } else {
            return true;
        }

        return false;
    }

    if (!autocorrect_is_enabled()) {
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
            if (apply_autocorrect(backspaces, (char const *)(autocorrect_data + state + 1))) {
                for (uint8_t i = 0; i < backspaces; ++i) {
                    tap_code(KC_BSPC);
                }
                send_string_P((char const *)(autocorrect_data + state + 1));
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
#    pragma GCC pop_options
#else
#    pragma message "Warning!!! Autocorrect is not corretly setup!"
bool process_autocorrection(uint16_t keycode, keyrecord_t* record) {
    return true;
}
#endif
