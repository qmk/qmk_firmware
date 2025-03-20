// Copyright 2022-2025 Google LLC
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
 * @file achordion.h
 * @brief Achordion community module: Customizing the tap-hold decision.
 *
 * Overview
 * --------
 *
 * This module customizes when tap-hold keys are considered held vs. tapped
 * based on the next pressed key, like Manna Harbour's Bilateral Combinations or
 * ZMK's positional hold. The library works on top of QMK's existing tap-hold
 * implementation. You define mod-tap and layer-tap keys as usual and use
 * Achordion to fine-tune the behavior.
 *
 * When QMK settles a tap-hold key as held, Achordion intercepts the event.
 * Achordion then revises the event as a tap or passes it along as a hold:
 *
 *  * Chord condition: On the next key press, a customizable `achordion_chord()`
 *    function is called, which takes the tap-hold key and the next key pressed
 *    as args. When the function returns true, the tap-hold key is settled as
 *    held, and otherwise as tapped.
 *
 *  * Timeout: If no other key press occurs within a timeout, the tap-hold key
 *    is settled as held. This is customizable with `achordion_timeout()`.
 *
 * Achordion only changes the behavior when QMK considered the key held. It
 * changes some would-be holds to taps, but no taps to holds.
 *
 * @note Some QMK features handle events before the point where Achordion can
 * intercept them, particularly: Combos, Key Lock, and Dynamic Macros. It's
 * still possible to use these features and Achordion in your keymap, but beware
 * they might behave poorly when used simultaneously with tap-hold keys.
 *
 *
 * For full documentation, see
 * <https://getreuer.info/posts/keyboards/achordion>
 */

#pragma once

#include "quantum.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Optional callback to customize which key chords are considered "held".
 *
 * In your keymap.c, define the callback
 *
 *     bool achordion_chord(uint16_t tap_hold_keycode,
 *                          keyrecord_t* tap_hold_record,
 *                          uint16_t other_keycode,
 *                          keyrecord_t* other_record) {
 *        // Conditions...
 *     }
 *
 * This callback is called if while `tap_hold_keycode` is pressed,
 * `other_keycode` is pressed. Return true if the tap-hold key should be
 * considered held, or false to consider it tapped.
 *
 * @param tap_hold_keycode Keycode of the tap-hold key.
 * @param tap_hold_record keyrecord_t from the tap-hold press event.
 * @param other_keycode Keycode of the other key.
 * @param other_record keyrecord_t from the other key's press event.
 * @return True if the tap-hold key should be considered held.
 */
bool achordion_chord(uint16_t tap_hold_keycode, keyrecord_t* tap_hold_record,
                     uint16_t other_keycode, keyrecord_t* other_record);

/**
 * Optional callback to define a timeout duration per keycode.
 *
 * In your keymap.c, define the callback
 *
 *     uint16_t achordion_timeout(uint16_t tap_hold_keycode) {
 *       // ...
 *     }
 *
 * The callback determines Achordion's timeout duration for `tap_hold_keycode`
 * in units of milliseconds. The timeout be in the range 0 to 32767 ms (upper
 * bound is due to 16-bit timer limitations). Use a timeout of 0 to bypass
 * Achordion.
 *
 * @param tap_hold_keycode Keycode of the tap-hold key.
 * @return Timeout duration in milliseconds in the range 0 to 32767.
 */
uint16_t achordion_timeout(uint16_t tap_hold_keycode);

/**
 * Optional callback defining which mods are "eagerly" applied.
 *
 * This callback defines  which mods are "eagerly" applied while a mod-tap
 * key is still being settled. This is helpful to reduce delay particularly when
 * using mod-tap keys with an external mouse.
 *
 * Define this callback in your keymap.c. The default callback is eager for
 * Shift and Ctrl, and not for Alt and GUI:
 *
 *     bool achordion_eager_mod(uint8_t mod) {
 *       return (mod & (MOD_LALT | MOD_LGUI)) == 0;
 *     }
 *
 * @note `mod` should be compared with `MOD_` prefixed codes, not `KC_` codes,
 * described at <https://docs.qmk.fm/mod_tap>.
 *
 * @param mod Modifier `MOD_` code.
 * @return True if the modifier should be eagerly applied.
 */
bool achordion_eager_mod(uint8_t mod);

/**
 * Returns true if the args come from keys on opposite hands.
 *
 * @param tap_hold_record keyrecord_t from the tap-hold key's event.
 * @param other_record keyrecord_t from the other key's event.
 * @return True if the keys are on opposite hands.
 */
bool achordion_opposite_hands(const keyrecord_t* tap_hold_record,
                              const keyrecord_t* other_record);

/**
 * Suppress tap-hold mods within a *typing streak* by defining
 * ACHORDION_STREAK. This can help preventing accidental mod
 * activation when performing a fast tapping sequence.
 * This is inspired by
 * https://sunaku.github.io/home-row-mods.html#typing-streaks
 *
 * Enable with:
 *
 *    #define ACHORDION_STREAK
 *
 * Adjust the maximum time between key events before modifiers can be enabled
 * by defining the following callback in your keymap.c:
 *
 *    uint16_t achordion_streak_chord_timeout(
 *        uint16_t tap_hold_keycode, uint16_t next_keycode) {
 *      return 200;  // Default of 200 ms.
 *    }
 */
#ifdef ACHORDION_STREAK
uint16_t achordion_streak_chord_timeout(uint16_t tap_hold_keycode,
                                        uint16_t next_keycode);

bool achordion_streak_continue(uint16_t keycode);

/** @deprecated Use `achordion_streak_chord_timeout()` instead. */
uint16_t achordion_streak_timeout(uint16_t tap_hold_keycode);
#endif

#ifdef __cplusplus
}
#endif
