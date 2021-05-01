/* Copyright 2017 Fredric Silberberg
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

#include <inttypes.h>
#include <stdint.h>
#include "process_key_lock.h"

#define BV_64(shift) (((uint64_t)1) << (shift))
#define GET_KEY_ARRAY(code) (((code) < 0x40) ? key_state[0] : ((code) < 0x80) ? key_state[1] : ((code) < 0xC0) ? key_state[2] : key_state[3])
#define GET_CODE_INDEX(code) (((code) < 0x40) ? (code) : ((code) < 0x80) ? (code)-0x40 : ((code) < 0xC0) ? (code)-0x80 : (code)-0xC0)
#define KEY_STATE(code) (GET_KEY_ARRAY(code) & BV_64(GET_CODE_INDEX(code))) == BV_64(GET_CODE_INDEX(code))
#define SET_KEY_ARRAY_STATE(code, val) \
    do {                               \
        switch (code) {                \
            case 0x00 ... 0x3F:        \
                key_state[0] = (val);  \
                break;                 \
            case 0x40 ... 0x7F:        \
                key_state[1] = (val);  \
                break;                 \
            case 0x80 ... 0xBF:        \
                key_state[2] = (val);  \
                break;                 \
            case 0xC0 ... 0xFF:        \
                key_state[3] = (val);  \
                break;                 \
        }                              \
    } while (0)
#define SET_KEY_STATE(code) SET_KEY_ARRAY_STATE(code, (GET_KEY_ARRAY(code) | BV_64(GET_CODE_INDEX(code))))
#define UNSET_KEY_STATE(code) SET_KEY_ARRAY_STATE(code, (GET_KEY_ARRAY(code)) & ~(BV_64(GET_CODE_INDEX(code))))
#define IS_STANDARD_KEYCODE(code) ((code) <= 0xFF)

// Locked key state. This is an array of 256 bits, one for each of the standard keys supported qmk.
uint64_t key_state[4] = {0x0, 0x0, 0x0, 0x0};
bool     watching     = false;

// Translate any OSM keycodes back to their unmasked versions.
static inline uint16_t translate_keycode(uint16_t keycode) {
    if (keycode > QK_ONE_SHOT_MOD && keycode <= QK_ONE_SHOT_MOD_MAX) {
        return keycode ^ QK_ONE_SHOT_MOD;
    } else {
        return keycode;
    }
}

bool process_key_lock(uint16_t *keycode, keyrecord_t *record) {
    // We start by categorizing the keypress event. In the event of a down
    // event, there are several possibilities:
    // 1. The key is not being locked, and we are not watching for new keys.
    //    In this case, we bail immediately. This is the common case for down events.
    // 2. The key was locked, and we need to unlock it. In this case, we will
    //    reset the state in our map and return false. When the user releases the
    //    key, the up event will no longer be masked and the OS will observe the
    //    released key.
    // 3. KC_LOCK was just pressed. In this case, we set up the state machine
    //    to watch for the next key down event, and finish processing
    // 4. The keycode is below 0xFF, and we are watching for new keys. In this case,
    //    we will send the key down event to the os, and set the key_state for that
    //    key to mask the up event.
    // 5. The keycode is above 0xFF, and we're wathing for new keys. In this case,
    //    the user pressed a key that we cannot "lock", as it's a series of keys,
    //    or a macro invocation, or a layer transition, or a custom-defined key, or
    //    or some other arbitrary code. In this case, we bail immediately, reset
    //    our watch state, and return true.
    //
    // In the event of an up event, there are these possibilities:
    // 1. The key is not being locked. In this case, we return true and bail
    //    immediately. This is the common case.
    // 2. The key is being locked. In this case, we will mask the up event
    //    by returning false, so the OS never sees that the key was released
    //    until the user pressed the key again.

    // We translate any OSM keycodes back to their original keycodes, so that if the key being
    // one-shot modded is a standard keycode, we can handle it. This is the only set of special
    // keys that we handle
    uint16_t translated_keycode = translate_keycode(*keycode);

    if (record->event.pressed) {
        // Non-standard keycode, reset and return
        if (!(IS_STANDARD_KEYCODE(translated_keycode) || translated_keycode == KC_LOCK)) {
            watching = false;
            return true;
        }

        // If we're already watching, turn off the watch.
        if (translated_keycode == KC_LOCK) {
            watching = !watching;
            return false;
        }

        if (IS_STANDARD_KEYCODE(translated_keycode)) {
            // We check watching first. This is so that in the following scenario, we continue to
            // hold the key: KC_LOCK, KC_F, KC_LOCK, KC_F
            // If we checked in reverse order, we'd end up holding the key pressed after the second
            // KC_F press is registered, when the user likely meant to hold F
            if (watching) {
                watching = false;
                SET_KEY_STATE(translated_keycode);
                // We need to set the keycode passed in to be the translated keycode, in case we
                // translated a OSM back to the original keycode.
                *keycode = translated_keycode;
                // Let the standard keymap send the keycode down event. The up event will be masked.
                return true;
            }

            if (KEY_STATE(translated_keycode)) {
                UNSET_KEY_STATE(translated_keycode);
                // The key is already held, stop this process. The up event will be sent when the user
                // releases the key.
                return false;
            }
        }

        // Either the key isn't a standard key, or we need to send the down event. Continue standard
        // processing
        return true;
    } else {
        // Stop processing if it's a standard key and we're masking up.
        return !(IS_STANDARD_KEYCODE(translated_keycode) && KEY_STATE(translated_keycode));
    }
}
