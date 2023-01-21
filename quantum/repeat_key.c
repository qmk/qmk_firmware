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

#include "repeat_key.h"

// Variables saving the state of the last key press.
static keyrecord_t last_record = {0};
static uint8_t     last_mods   = 0;

// Number of times the last key has been repeated.
static uint8_t repeat_count = 0;
// Same as `repeat_count`, but set to zero outside of reprocess_last_key() so
// that this variable is nonzero only while a repeated key is being processed.
static uint8_t reprocessing_repeat_count = 0;

uint8_t get_repeat_key_count(void) {
    return reprocessing_repeat_count;
}

uint16_t get_repeat_key_keycode(void) {
    return last_record.keycode;
}

uint8_t get_repeat_key_mods(void) {
    return last_mods;
}

void set_repeat_key_keycode(uint16_t keycode) {
    set_repeat_key_record(keycode, &(keyrecord_t){
#ifndef NO_ACTION_TAPPING
                                       .tap.interrupted = false,
                                       .tap.count       = 1,
#endif
                                   });
}

void set_repeat_key_mods(uint8_t mods) {
    last_mods = mods;
}

void set_repeat_key_record(uint16_t keycode, keyrecord_t* record) {
    last_record         = *record;
    last_record.keycode = keycode;
    repeat_count        = 0;
}

void repeat_key_invoke(keyevent_t event) {
    // Since this function calls process_record(), it may recursively call itself.
    // We return early if `reprocessing_repeat_count` is nonzero to prevent
    // infinite recursion.
    if (reprocessing_repeat_count || !last_record.keycode) {
        return;
    }

    if (event.pressed) {
        if (repeat_count < 255) {
            ++repeat_count;
        }

        // On press, apply the last mods state, stacking on top of current mods.
        register_weak_mods(last_mods);
    }

    // Generate an event and plumb it into the event pipeline.
    last_record.event         = event;
    reprocessing_repeat_count = repeat_count;
    process_record(&last_record);
    reprocessing_repeat_count = 0;

    // On release, restore the mods state.
    if (!event.pressed) {
        unregister_weak_mods(last_mods);
    }
}
