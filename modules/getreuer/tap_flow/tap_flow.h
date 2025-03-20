// Copyright 2025 Google LLC
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

/**
 * @file tap_flow.h
 * @brief Tap Flow module: disable HRMs during fast typing
 *
 * This module is an implementation of "global quick tap" (GQT), aka "require
 * priori idle," for tap-hold keys. It is particularly useful for home row mods
 * to avoid accidental mod triggers in fast typing.
 *
 * Tap Flow modifies the tap-hold decision such that when a tap-hold key is
 * pressed within a short timeout of the preceding key, the tapping function is
 * used. The assumption is that during fast typing, only the tap function of
 * tap-hold keys is desired (though perhaps with an exception for Shift or
 * AltGr, noted below), whereas the hold functions (mods and layers) are
 * used in isolation, or at least with a brief pause preceding the tap-hold key
 * press.
 *
 * Optionally, the feature can be customized with the `get_tap_flow()` callback.
 * In this way, exceptions may be made for Shift and AltGr (or whatever you
 * wish) to use a shorter time or to disable filtering for those keys entirely.
 *
 *
 * For full documentation, see
 * <https://getreuer.info/posts/keyboards/tap-flow>
 */

#pragma once
#include "quantum.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef TAP_FLOW_TERM
#  define TAP_FLOW_TERM  150
#endif  // TAP_FLOW_TERM

/**
 * Optional callback to customize filtering.
 *
 * Tap Flow acts only when key events are closer together than this time.
 *
 * Return a time of 0 to disable filtering. In this way, Tap Flow may be
 * disabled for certain tap-hold keys, or when following certain previous keys.
 *
 * @param keycode Keycode of the tap-hold key.
 * @param record keyrecord_t of the tap-hold event.
 * @param prev_keycode Keycode of the previously pressed key.
 * @return Time in milliseconds.
 */
uint16_t get_tap_flow(uint16_t keycode, keyrecord_t* record,
                      uint16_t prev_keycode);

extern uint16_t g_tap_flow_term;

#ifdef __cplusplus
}
#endif

