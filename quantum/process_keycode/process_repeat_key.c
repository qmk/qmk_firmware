// Copyright 2022-2023 Google LLC
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

#include "process_repeat_key.h"

bool process_repeat_key(uint16_t keycode, keyrecord_t* record) {
    if (get_repeat_key_count()) {
        return true;
    }

    if (keycode == QK_REPEAT_KEY) {
        repeat_key_invoke(&record->event);
        return false;
#ifndef NO_ALT_REPEAT_KEY
    } else if (keycode == QK_ALT_REPEAT_KEY) {
        alt_repeat_key_invoke(&record->event);
        return false;
#endif // NO_ALT_REPEAT_KEY
    } else if (record->event.pressed && get_repeat_key_eligible(keycode, record)) {
        set_repeat_key_record(keycode, record);
        set_repeat_key_mods(get_mods() | get_weak_mods()
#ifndef NO_ACTION_ONESHOT
                            | get_oneshot_mods()
#endif // NO_ACTION_ONESHOT
        );
    }

    return true;
}

// Default implementation of get_repeat_key_eligible().
__attribute__((weak)) bool get_repeat_key_eligible(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        // Ignore MO, TO, TG, TT, and TL layer switch keys.
        case QK_TRI_LAYER_LOWER:
        case QK_TRI_LAYER_UPPER:
        case QK_MOMENTARY ... QK_MOMENTARY_MAX:
        case QK_TO ... QK_TO_MAX:
        case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX:
        case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
        // Ignore mod keys.
        case KC_LCTL ... KC_RGUI:
        case KC_HYPR:
        case KC_MEH:
            // Ignore one-shot keys.
#ifndef NO_ACTION_ONESHOT
        case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
        case QK_ONE_SHOT_MOD ... QK_ONE_SHOT_MOD_MAX:
#endif // NO_ACTION_ONESHOT
            return false;

            // Ignore hold events on tap-hold keys.
#ifndef NO_ACTION_TAPPING
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
#    ifndef NO_ACTION_LAYER
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
#    endif // NO_ACTION_LAYER
            if (record->tap.count == 0) {
                return false;
            }
            break;
#endif // NO_ACTION_TAPPING

#ifdef SWAP_HANDS_ENABLE
        case QK_SWAP_HANDS ... QK_SWAP_HANDS_MAX:
            if (IS_SWAP_HANDS_KEYCODE(keycode) || record->tap.count == 0) {
                return false;
            }
            break;
#endif // SWAP_HANDS_ENABLE
    }

    return true;
}
