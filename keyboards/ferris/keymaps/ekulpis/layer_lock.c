// Copyright 2022 Google LLC
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
//
//
// For full documentation, see
// https://getreuer.info/posts/keyboards/layer-lock

#include "layer_lock.h"

// The current lock state. The kth bit is on if layer k is locked.
static layer_state_t locked_layers = 0;

// Layer Lock timer to disable layer lock after X seconds inactivity
#if LAYER_LOCK_IDLE_TIMEOUT > 0

    static uint32_t layer_lock_timer = 0;

    void layer_lock_task(void) {
        if (locked_layers && timer_elapsed32(layer_lock_timer) > LAYER_LOCK_IDLE_TIMEOUT) {
            layer_lock_all_off();
            layer_lock_timer = timer_read32();
        }
    }

     void layer_lock_all_off(void) {
         layer_and(~locked_layers);
         locked_layers = 0;
     }

#endif // End of layer lock idle timeout functions

bool process_layer_lock(uint16_t keycode, keyrecord_t* record,
                        uint16_t lock_keycode) {

    #if LAYER_LOCK_IDLE_TIMEOUT > 0
      layer_lock_timer = timer_read32();
    #endif

  // The intention is that locked layers remain on. If something outside of
  // this feature turned any locked layers off, unlock them.
  if ((locked_layers & ~layer_state) != 0) {
    layer_lock_set_user(locked_layers &= layer_state);
  }

  if (keycode == lock_keycode) {
    if (record->event.pressed) {  // The layer lock key was pressed.
      layer_lock_invert(get_highest_layer(layer_state));
    }
    return false;
  }

  switch (keycode) {
    case QK_MOMENTARY ... QK_MOMENTARY_MAX:  // `MO(layer)` keys.
    case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX: {  // `TT(layer)`.
      const uint8_t layer = keycode & 255;
      if (is_layer_locked(layer)) {
        // Event on `MO` or `TT` key where layer is locked.
        if (record->event.pressed) {  // On press, unlock the layer.
          layer_lock_invert(layer);
        }
        return false;  // Skip default handling.
      }
    } break;

#ifndef NO_ACTION_TAPPING
    case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:  // `LT(layer, key)` keys.
      if (record->tap.count == 0 && !record->event.pressed &&
          is_layer_locked((keycode >> 8) & 15)) {
        // Release event on a held layer-tap key where the layer is locked.
        return false;  // Skip default handling so that layer stays on.
      }
      break;
#endif  // NO_ACTION_TAPPING
  }

  return true;
}

bool is_layer_locked(uint8_t layer) {
  return locked_layers & ((layer_state_t)1 << layer);
}

void layer_lock_invert(uint8_t layer) {
  const layer_state_t mask = (layer_state_t)1 << layer;
  if ((locked_layers & mask) == 0) {  // Layer is being locked.
#ifndef NO_ACTION_ONESHOT
    if (layer == get_oneshot_layer()) {
      reset_oneshot_layer();  // Reset so that OSL doesn't turn layer off.
    }
#endif  // NO_ACTION_ONESHOT
    layer_on(layer);
    #if LAYER_LOCK_IDLE_TIMEOUT > 0
        layer_lock_timer = timer_read32();
    #endif
  } else {  // Layer is being unlocked.
    layer_off(layer);
  }
  layer_lock_set_user(locked_layers ^= mask);
}

// Implement layer_lock_on/off by deferring to layer_lock_invert.
void layer_lock_on(uint8_t layer) {
  if (!is_layer_locked(layer)) { layer_lock_invert(layer); }
}

void layer_lock_off(uint8_t layer) {
  if (is_layer_locked(layer)) { layer_lock_invert(layer); }
}

__attribute__((weak)) void layer_lock_set_user(layer_state_t locked_layers) {}
