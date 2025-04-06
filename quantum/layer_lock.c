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

#include "layer_lock.h"
#include "quantum_keycodes.h"

#ifndef NO_ACTION_LAYER
// The current lock state. The kth bit is on if layer k is locked.
layer_state_t locked_layers = 0;

// Layer Lock timer to disable layer lock after X seconds inactivity
#    if defined(LAYER_LOCK_IDLE_TIMEOUT) && LAYER_LOCK_IDLE_TIMEOUT > 0
uint32_t layer_lock_timer = 0;

void layer_lock_timeout_task(void) {
    if (locked_layers && timer_elapsed32(layer_lock_timer) > LAYER_LOCK_IDLE_TIMEOUT) {
        layer_lock_all_off();
        layer_lock_timer = timer_read32();
    }
}
void layer_lock_activity_trigger(void) {
    layer_lock_timer = timer_read32();
}
#    else
void layer_lock_timeout_task(void) {}
void layer_lock_activity_trigger(void) {}
#    endif // LAYER_LOCK_IDLE_TIMEOUT > 0

bool is_layer_locked(uint8_t layer) {
    return locked_layers & ((layer_state_t)1 << layer);
}

void layer_lock_invert(uint8_t layer) {
    const layer_state_t mask = (layer_state_t)1 << layer;
    if ((locked_layers & mask) == 0) { // Layer is being locked.
#    ifndef NO_ACTION_ONESHOT
        if (layer == get_oneshot_layer()) {
            reset_oneshot_layer(); // Reset so that OSL doesn't turn layer off.
        }
#    endif // NO_ACTION_ONESHOT
        layer_on(layer);
        layer_lock_activity_trigger();
    } else { // Layer is being unlocked.
        layer_off(layer);
    }
    layer_lock_set_kb(locked_layers ^= mask);
}

// Implement layer_lock_on/off by deferring to layer_lock_invert.
void layer_lock_on(uint8_t layer) {
    if (!is_layer_locked(layer)) {
        layer_lock_invert(layer);
    }
}

void layer_lock_off(uint8_t layer) {
    if (is_layer_locked(layer)) {
        layer_lock_invert(layer);
    }
}

void layer_lock_all_off(void) {
    layer_and(~locked_layers);
    locked_layers = 0;
    layer_lock_set_kb(locked_layers);
}

#else  // NO_ACTION_LAYER
bool is_layer_locked(uint8_t layer) {
    return false;
}
void layer_lock_on(uint8_t layer) {}
void layer_lock_off(uint8_t layer) {}
void layer_lock_all_off(void) {}
void layer_lock_invert(uint8_t layer) {}
void layer_lock_timeout_task(void) {}
void layer_lock_activity_trigger(void) {}
#endif // NO_ACTION_LAYER

__attribute__((weak)) bool layer_lock_set_kb(layer_state_t locked_layers) {
    return layer_lock_set_user(locked_layers);
}
__attribute__((weak)) bool layer_lock_set_user(layer_state_t locked_layers) {
    return true;
}

void layer_lock_task(void) {
    layer_lock_timeout_task();
}
