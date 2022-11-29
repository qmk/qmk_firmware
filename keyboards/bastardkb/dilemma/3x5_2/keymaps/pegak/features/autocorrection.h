// Copyright 2021-2022 Google LLC
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
 * @file autocorrection.h
 * @brief Autocorrection on your keyboard.
 *
 * Overview
 * --------
 *
 * Some words are more prone to typos than others. This userspace QMK library
 * implements rudimentary autocorrection, automatically detecting and fixing
 * some misspellings.
 *
 * Features:
 *
 *  * It runs on your keyboard, so it is always active no matter what software.
 *  * Low resource cost.
 *  * It is case insensitive.
 *  * It works within words, useful for programming to catch typos within longer
 *    identifiers.
 *
 * Limitations:
 *
 *  * It is limited to alphabet characters a–z, apostrophes ', and word breaks.
 *    I'm sorry this probably isn't useful for languages besides English.
 *  * It does not follow mouse or hotkey driven cursor movement.
 *
 * Changing the autocorrection dictionary
 * --------------------------------------
 *
 * The file autocorrection_data.h encodes the typos to correct. While you could
 * simply use the version of this file provided above for a practical
 * configuration, you can make your own to personalize the autocorrection to
 * your most troublesome typos:
 *
 * Step 1: First, create an autocorrection dictionary autocorrection_dict.txt,
 * in a form like
 *
 *     :thier        -> their
 *     dosen't       -> doesn't
 *     fitler        -> filter
 *     ouput         -> output
 *     widht         -> width
 *
 * For a practical 71-entry example, see autocorrection_dict.txt. And for a yet
 * larger 400-entry example, see autocorrection_dict_extra.txt.
 *
 * The syntax is `typo -> correction`. Typos and corrections are case
 * insensitive, and any whitespace before or after the typo and correction is
 * ignored. The typo must be only the characters a–z, ', or the special
 * character : representing a word break. The correction may have just about any
 * printable ASCII characters.
 *
 * Step 2: Use the make_autocorrection_data.py Python script to process the
 * dictionary. Put autocorrection_dict.txt in the same directory as the Python
 * script and run
 *
 *     $ python3 make_autocorrection_data.py
 *     Processed 71 autocorrection entries to table with 1120 bytes.
 *
 * The script arranges the entries in autocorrection_dict.txt into a trie and
 * generates autocorrection_data.h with the serialized trie embedded as an
 * array. The .h file will be written in the same directory.
 *
 * Step 3: Finally, recompile and flash your keymap.
 *
 * For full documentation, see
 * <https://getreuer.info/posts/keyboards/autocorrection>
 *
 * @author Pascal Getreuer
 */

#pragma once

#include "quantum.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Handler function for autocorrection.
 *
 * Call this function in keymap.c from `process_record_user()` like
 *
 *     #include "features/autocorrection.h"
 *
 *     bool process_record_user(uint16_t keycode, keyrecord_t* record) {
 *       if (!process_autocorrection(keycode, record)) { return false; }
 *       // Your macros...
 *
 *       return true;
 *     }
 */
bool process_autocorrection(uint16_t keycode, keyrecord_t* record);

#ifdef __cplusplus
}
#endif
