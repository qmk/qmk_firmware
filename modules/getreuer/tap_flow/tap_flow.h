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
 * @note Tap Flow is now a core QMK feature! See
 * <https://docs.qmk.fm/tap_hold#flow-tap>
 *
 * This module is an implementation of "global quick tap" (GQT), aka "require
 * prior idle," for tap-hold keys. It is particularly useful for home row mods
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
 * Optional callback to customize where Tap Flow is enabled.
 *
 * Tap Flow is constrained to certain keys by the following rule: this callback
 * is called for both the tap-hold key *and* the key press immediately preceding
 * it. If the callback returns true for both keycodes, Tap Flow may apply.
 *
 * The default implementation of this callback corresponds to
 *
 *     bool is_tap_flow_key(uint16_t keycode) {
 *       switch (keycode) {
 *         case QK_MOD_TAP ... QK_MOD_TAP_MAX:
 *           keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
 *           break;
 *         case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
 *           keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
 *           break;
 *       }
 *       switch (keycode) {
 *         case KC_SPC:
 *         case KC_A ... KC_Z:
 *         case KC_DOT:
 *         case KC_COMM:
 *         case KC_SCLN:
 *         case KC_SLSH:
 *           return true;
 *       }
 *       return false;
 *     }
 *
 * @param keycode Keycode of the key.
 * @return Whether to enable Tap Flow for this key.
 */
bool is_tap_flow_key(uint16_t keycode);

/**
 * Optional callback to customize filtering.
 *
 * Tap Flow acts only when key events are closer together than this time.
 *
 * Return a time of 0 to disable filtering. In this way, Tap Flow may be
 * disabled for certain tap-hold keys, or when following certain previous keys.
 *
 * The default implementation of this callback is
 *
 *     uint16_t get_tap_flow_term(uint16_t keycode, keyrecord_t* record,
 *                                uint16_t prev_keycode) {
 *       if (is_tap_flow_key(keycode) && is_tap_flow_key(prev_keycode)) {
 *         return g_tap_flow_term;
 *       }
 *       return 0;
 *     }
 *
 * NOTE: If both `is_tap_flow_key()` and `get_tap_flow_term()` are defined, then
 * `get_tap_flow_term()` takes precedence.
 *
 * @param keycode Keycode of the tap-hold key.
 * @param record keyrecord_t of the tap-hold event.
 * @param prev_keycode Keycode of the previously pressed key.
 * @return Timeout in milliseconds.
 */
uint16_t get_tap_flow_term(uint16_t keycode, keyrecord_t* record,
                           uint16_t prev_keycode);

/** @deprecated Use `get_tap_flow_term()` instead. */
uint16_t get_tap_flow(uint16_t keycode, keyrecord_t* record,
                      uint16_t prev_keycode);

extern uint16_t g_tap_flow_term;

#ifdef __cplusplus
}
#endif

