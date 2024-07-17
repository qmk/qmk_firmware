/* Copyright 2024 Harrison Chan (@xelus22)
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

#include "process_key_cancellation.h"
#include <string.h>
#include "keycodes.h"
#include "keycode_config.h"
#include "action_util.h"
#include "keymap_introspection.h"

/**
 * @brief function for querying the enabled state of key cancellation
 *
 * @return true if enabled
 * @return false if disabled
 */
bool key_cancellation_is_enabled(void) {
    return keymap_config.key_cancellation_enable;
}

/**
 * @brief Enables key cancellation and saves state to eeprom
 *
 */
void key_cancellation_enable(void) {
    keymap_config.key_cancellation_enable = true;
    eeconfig_update_keymap(keymap_config.raw);
}

/**
 * @brief Disables key cancellation and saves state to eeprom
 *
 */
void key_cancellation_disable(void) {
    keymap_config.key_cancellation_enable = false;
    eeconfig_update_keymap(keymap_config.raw);
}

/**
 * @brief Toggles key cancellation's status and save state to eeprom
 *
 */
void key_cancellation_toggle(void) {
    keymap_config.key_cancellation_enable = !keymap_config.key_cancellation_enable;
    eeconfig_update_keymap(keymap_config.raw);
}

/**
 * @brief handler for user to override whether autocorrect should process this keypress
 *
 * @param keycode Keycode registered by matrix press, per keymap
 * @param record keyrecord_t structure
 * @return true Allow key cancellation
 * @return false Stop processing and escape from key cancellation
 */
__attribute__((weak)) bool process_key_cancellation_user(uint16_t keycode, keyrecord_t *record) {
    return true;
}

/**
 * @brief Process handler for key_cancellation feature
 *
 * @param keycode Keycode registered by matrix press, per keymap
 * @param record keyrecord_t structure
 * @return true Continue processing keycodes, and send to host
 * @return false Stop processing keycodes, and don't send to host
 */
bool process_key_cancellation(uint16_t keycode, keyrecord_t *record) {
    if ((keycode >= QK_KEY_CANCELLATION_ON && keycode <= QK_KEY_CANCELLATION_TOGGLE) && record->event.pressed) {
        if (keycode == QK_KEY_CANCELLATION_ON) {
            key_cancellation_enable();
        } else if (keycode == QK_KEY_CANCELLATION_OFF) {
            key_cancellation_disable();
        } else if (keycode == QK_KEY_CANCELLATION_TOGGLE) {
            key_cancellation_toggle();
        } else {
            return true;
        }

        return false;
    }

    if (!keymap_config.key_cancellation_enable) {
        return true;
    }

    if (!record->event.pressed) {
        return true;
    }

    // only supports basic keycodes
    if (!IS_BASIC_KEYCODE(keycode)) {
        return true;
    }

    if (!process_key_cancellation_user(keycode, record)) {
        return true;
    }

    // loop through all the keyup and keydown events
    for (int i = 0; i < key_cancellation_count(); i++) {
        key_cancellation_t key_cancellation = key_cancellation_get(i);
        if (keycode == key_cancellation.press) {
            del_key(key_cancellation.unpress);
        }
    }

    return true;
}
