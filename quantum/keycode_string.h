// Copyright 2024-2025 Google LLC
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

#pragma once

#include <stdint.h>

#if KEYCODE_STRING_ENABLE

/**
 * @brief Formats a QMK keycode as a human-readable string.
 *
 * Given a keycode, like `KC_A`, this function returns a formatted string, like
 * "KC_A". This is useful for debugging and diagnostics so that keys are more
 * easily identified than they would be by raw numerical codes.
 *
 * @note The returned char* string should be used right away. The string memory
 * is reused and will be overwritten by the next call to `keycode_string()`.
 *
 * Many common QMK keycodes are understood by this function, but not all.
 * Recognized keycodes include:
 *
 *  - Most basic keycodes, including letters `KC_A` - `KC_Z`, digits `KC_0` -
 *    `KC_9`, function keys `KC_F1` - `KC_F24`, and modifiers like `KC_LSFT`.
 *
 *  - Modified basic keycodes, like `S(KC_1)` (Shift + 1 = !).
 *
 *  - `MO`, `TO`, `TG`, `OSL`, `LM(layer,mod)`, `LT(layer,kc)` layer switches.
 *
 *  - One-shot mod `OSM(mod)` keycodes.
 *
 *  - Mod-tap `MT(mod, kc)` keycodes.
 *
 *  - Tap dance keycodes `TD(i)`.
 *
 *  - Swap hands keycodes `SH_T(kc)`, `SH_TOGG`, etc.
 *
 *  - Joystick keycodes `JS_n`.
 *
 *  - Programmable button keycodes `PB_n`.
 *
 *  - Unicode `UC(codepoint)` and Unicode Map `UM(i)` and `UP(i,j)` keycodes.
 *
 *  - Keyboard range keycodes `QK_KB_*`.
 *
 *  - User range (SAFE_RANGE) keycodes `QK_USER_*`.
 *
 * Keycodes involving mods like `OSM`, `LM`, `MT` are fully supported only where
 * a single mod is applied.
 *
 * Unrecognized keycodes are printed numerically as hex values like `0x1ABC`.
 *
 * Optionally, use `keycode_string_names_user` or `keycode_string_names_kb` to
 * define names for additional keycodes or override how any of the above are
 * formatted.
 *
 * @param keycode  QMK keycode.
 * @return         Stringified keycode.
 */
const char* get_keycode_string(uint16_t keycode);

/** Defines a human-readable name for a keycode. */
typedef struct {
    uint16_t    keycode;
    const char* name;
} keycode_string_name_t;

// clang-format off
/**
 * @brief Defines names for additional keycodes for `get_keycode_string()`.
 *
 * Define `KEYCODE_STRING_NAMES_USER` in your keymap.c to add names for
 * additional keycodes to `keycode_string()`. This table may also be used to
 * override how `keycode_string()` formats a keycode. For example, supposing
 * keymap.c defines `MYMACRO1` and `MYMACRO2` as custom keycodes:
 *
 *     KEYCODE_STRING_NAMES_USER(
 *         KEYCODE_STRING_NAME(MYMACRO1),
 *         KEYCODE_STRING_NAME(MYMACRO2),
 *         KEYCODE_STRING_NAME(KC_EXLM),
 *     );
 *
 * The above defines names for `MYMACRO1` and `MYMACRO2`, and overrides
 * `KC_EXLM` to format as "KC_EXLM" instead of the default "S(KC_1)".
 */
#    define KEYCODE_STRING_NAMES_USER(...)                                          \
    static const keycode_string_name_t keycode_string_names_user[] = {__VA_ARGS__}; \
    uint16_t keycode_string_names_size_user =                                       \
        sizeof(keycode_string_names_user) / sizeof(keycode_string_name_t);          \
    const keycode_string_name_t* keycode_string_names_data_user =                   \
        keycode_string_names_user

/** Same as above, but defines keycode string names at the keyboard level. */
#    define KEYCODE_STRING_NAMES_KB(...)                                            \
    static const keycode_string_name_t keycode_string_names_kb[] = {__VA_ARGS__};   \
    uint16_t keycode_string_names_size_kb =                                         \
        sizeof(keycode_string_names_kb) / sizeof(keycode_string_name_t);            \
    const keycode_string_name_t* keycode_string_names_data_kb =                     \
        keycode_string_names_kb

/** Helper to define a keycode_string_name_t. */
#    define KEYCODE_STRING_NAME(kc) \
        { (kc), #kc }
// clang-format on

extern const keycode_string_name_t* keycode_string_names_data_user;
extern uint16_t                     keycode_string_names_size_user;
extern const keycode_string_name_t* keycode_string_names_data_kb;
extern uint16_t                     keycode_string_names_size_kb;

#else

// When keycode_string is disabled, fall back to printing keycodes numerically
// as decimal values, using get_u16_str() from quantum.c.
#    define get_keycode_string(kc) get_u16_str(kc, ' ')

const char* get_u16_str(uint16_t curr_num, char curr_pad);

#    define KEYCODE_STRING_NAMES_USER(...)
#    define KEYCODE_STRING_NAMES_KB(...)
#    define KEYCODE_STRING_NAME(kc)

#endif // KEYCODE_STRING_ENABLE
