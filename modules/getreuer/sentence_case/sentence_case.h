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
 * @file sentence_case.h
 * @brief Sentence Case community module: automatic sentence capitalization.
 *
 * This module automatically capitalizes the first letter of sentences, reducing
 * the need to explicitly use shift. To use it, you simply type as usual but
 * without shifting at the start of sentences. The feature detects when new
 * sentences begin and capitalizes automatically.
 *
 * Sentence Case matches patterns like
 *
 *   "a. a"
 *   "a.  a"
 *   "a? a"
 *   "a!' 'a"
 *
 * but not
 *
 *   "a... a"
 *   "a.a. a"
 *
 * Additionally by default, abbreviations "vs." and "etc." are exceptionally
 * detected as not real sentence endings. You can use the callback
 * `sentence_case_check_ending()` to define other exceptions.
 *
 * @note One-shot keys must be enabled.
 *
 * For full documentation, see
 * <https://getreuer.info/posts/keyboards/sentence-case>
 */

#pragma once

#include "quantum.h"

#ifdef __cplusplus
extern "C" {
#endif

// The size of the keycode buffer for `sentence_case_check_ending()`. It must be
// at least as large as the longest pattern checked. If less than 2, buffering
// is disabled and the callback is not called.
#ifndef SENTENCE_CASE_BUFFER_SIZE
#define SENTENCE_CASE_BUFFER_SIZE 8
#endif  // SENTENCE_CASE_BUFFER_SIZE

void sentence_case_on(void); /**< Enables Sentence Case. */
void sentence_case_off(void); /**< Disables Sentence Case. */
void sentence_case_toggle(void); /**< Toggles Sentence Case. */
bool is_sentence_case_on(void); /**< Gets whether currently enabled. */
bool is_sentence_case_primed(void); /**< Whether currently primed. */
void sentence_case_clear(void); /**< Clears Sentence Case to initial state. */

/**
 * Optional callback to indicate primed state.
 *
 * This callback gets called when Sentence Case changes to or from a "primed"
 * state, useful to indicate with an LED or otherwise that the next letter typed
 * will be capitalized.
 */
void sentence_case_primed(bool primed);

/**
 * Optional callback to determine whether there is a real sentence ending.
 *
 * When a sentence-ending punctuation key is typed, this callback is called to
 * determine whether it is a real sentence ending, meaning the first letter of
 * the following word should be capitalized. For instance, abbreviations like
 * "vs." are usually not real sentence endings. The input argument is a buffer
 * of the last SENTENCE_CASE_BUFFER_SIZE keycodes. Returning true means it is a
 * real sentence ending; returning false means it is not.
 *
 * The default implementation checks for the abbreviations "vs." and "etc.":
 *
 *     bool sentence_case_check_ending(const uint16_t* buffer) {
 *       // Don't consider "vs." and "etc." to end the sentence.
 *       if (SENTENCE_CASE_JUST_TYPED(KC_SPC, KC_V, KC_S, KC_DOT) ||
 *           SENTENCE_CASE_JUST_TYPED(KC_SPC, KC_E, KC_T, KC_C, KC_DOT)) {
 *         return false;  // Not a real sentence ending.
 *       }
 *       return true;  // Real sentence ending; capitalize next letter.
 *     }
 *
 * @note This callback is used only if `SENTENCE_CASE_BUFFER_SIZE >= 2`.
 *       Otherwise it has no effect.
 *
 * @param buffer Buffer of the last `SENTENCE_CASE_BUFFER_SIZE` keycodes.
 * @return whether there is a real sentence ending.
 */
bool sentence_case_check_ending(const uint16_t* buffer);

/**
 * Macro to be used in `sentence_case_check_ending()`.
 *
 * Returns true if a given pattern of keys was just typed by comparing with the
 * keycode buffer. This is useful for defining exceptions in
 * `sentence_case_check_ending()`.
 *
 * For example, `SENTENCE_CASE_JUST_TYPED(KC_SPC, KC_V, KC_S, KC_DOT)` returns
 * true if " vs." were the last four keys typed.
 *
 * @note The pattern must be no longer than `SENTENCE_CASE_BUFFER_SIZE`.
 */
#define SENTENCE_CASE_JUST_TYPED(...)                               \
  ({                                                                \
    static const uint16_t PROGMEM pattern[] = {__VA_ARGS__};        \
    sentence_case_just_typed_P(buffer, pattern,                     \
                               sizeof(pattern) / sizeof(uint16_t)); \
  })
bool sentence_case_just_typed_P(const uint16_t* buffer, const uint16_t* pattern,
                                int8_t pattern_len);

/**
 * Optional callback defining which keys are letter, punctuation, etc.
 *
 * This callback may be useful if you type non-US letters or have customized the
 * shift behavior of the punctuation keys. The return value tells Sentence Case
 * how to interpret the key:
 *
 *   'a'  Key is a letter, by default KC_A to KC_Z. If occurring at the start of
 *        a sentence, Sentence Case applies shift to capitalize it.
 *
 *   '.'  Key is sentence-ending punctuation. Default: . ? !
 *
 *   '#'  Key types a backspaceable character that isn't part of a word.
 *        Default includes - = [ ] ; ' , < > / _ + @ # $ % ^ & * ( ) { } digits
 *
 *   ' '  Key is a space. Default: KC_SPC
 *
 *  '\''  Key is a quote or double quote character. Default: KC_QUOT.
 *
 *  '\0'  Sentence Case should ignore this key.
 *
 * If a hotkey or navigation key is pressed (or another key that performs an
 * action that backspace doesn't undo), then the callback should call
 * `sentence_case_clear()` to clear the state and then return '\0'.
 *
 * The default callback is:
 *
 *     char sentence_case_press_user(uint16_t keycode,
 *                                   keyrecord_t* record,
 *                                   uint8_t mods) {
 *       if ((mods & ~(MOD_MASK_SHIFT | MOD_BIT(KC_RALT))) == 0) {
 *         const bool shifted = mods & MOD_MASK_SHIFT;
 *         switch (keycode) {
 *           case KC_A ... KC_Z:
 *             return 'a';  // Letter key.
 *
 *           case KC_DOT:  // . is punctuation, Shift . is a symbol (>)
 *             return !shifted ? '.' : '#';
 *           case KC_1:
 *           case KC_SLSH:
 *             return shifted ? '.' : '#';
 *           case KC_EXLM:
 *           case KC_QUES:
 *             return '.';
 *           case KC_2 ... KC_0:  // 2 3 4 5 6 7 8 9 0
 *           case KC_AT ... KC_RPRN:  // @ # $ % ^ & * ( )
 *           case KC_MINS ... KC_SCLN:  // - = [ ] backslash ;
 *           case KC_UNDS ... KC_COLN:  // _ + { } | :
 *           case KC_GRV:
 *           case KC_COMM:
 *             return '#';  // Symbol key.
 *
 *           case KC_SPC:
 *             return ' ';  // Space key.
 *
 *           case KC_QUOT:
 *             return '\'';  // Quote key.
 *         }
 *       }
 *
 *       // Otherwise clear Sentence Case to initial state.
 *       sentence_case_clear();
 *       return '\0';
 *     }
 *
 * To customize, copy the above function into your keymap and add/remove
 * keycodes to the above cases.
 *
 * @param keycode Current keycode.
 * @param record record_t for the current press event.
 * @param mods equal to `get_mods() | get_weak_mods() | get_oneshot_mods()`
 * @return char code 'a', '.', '#', ' ', or '\0' indicating how the key is to be
 *         interpreted as described above.
 */
char sentence_case_press_user(uint16_t keycode, keyrecord_t* record,
                              uint8_t mods);

#ifdef __cplusplus
}
#endif
