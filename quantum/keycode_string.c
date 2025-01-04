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

#include "keycode_string.h"

#include <string.h>
#include "bitwise.h"
#include "keycode.h"
#include "progmem.h"
#include "quantum_keycodes.h"

typedef int_fast8_t index_t;

// clang-format off
/** Names of some common keycodes. */
static const keycode_string_name_t keycode_names[] = {
    KEYCODE_STRING_NAME(KC_ENT),
    KEYCODE_STRING_NAME(KC_ESC),
    KEYCODE_STRING_NAME(KC_BSPC),
    KEYCODE_STRING_NAME(KC_TAB),
    KEYCODE_STRING_NAME(KC_SPC),
    KEYCODE_STRING_NAME(KC_MINS),
    KEYCODE_STRING_NAME(KC_EQL),
    KEYCODE_STRING_NAME(KC_LBRC),
    KEYCODE_STRING_NAME(KC_RBRC),
    KEYCODE_STRING_NAME(KC_BSLS),
    KEYCODE_STRING_NAME(KC_SCLN),
    KEYCODE_STRING_NAME(KC_QUOT),
    KEYCODE_STRING_NAME(KC_GRV),
    KEYCODE_STRING_NAME(KC_COMM),
    KEYCODE_STRING_NAME(KC_DOT),
    KEYCODE_STRING_NAME(KC_SLSH),
    KEYCODE_STRING_NAME(KC_INS),
    KEYCODE_STRING_NAME(KC_HOME),
    KEYCODE_STRING_NAME(KC_PGUP),
    KEYCODE_STRING_NAME(KC_DEL),
    KEYCODE_STRING_NAME(KC_END),
    KEYCODE_STRING_NAME(KC_PGDN),
    KEYCODE_STRING_NAME(KC_RGHT),
    KEYCODE_STRING_NAME(KC_LEFT),
    KEYCODE_STRING_NAME(KC_DOWN),
    KEYCODE_STRING_NAME(KC_UP),
    KEYCODE_STRING_NAME(KC_TRNS),
#ifdef EXTRAKEY_ENABLE
    KEYCODE_STRING_NAME(KC_WBAK),
    KEYCODE_STRING_NAME(KC_WFWD),
    KEYCODE_STRING_NAME(KC_WREF),
    KEYCODE_STRING_NAME(KC_MNXT),
    KEYCODE_STRING_NAME(KC_MPRV),
    KEYCODE_STRING_NAME(KC_MPLY),
    KEYCODE_STRING_NAME(KC_VOLU),
    KEYCODE_STRING_NAME(KC_VOLD),
#endif  // EXTRAKEY_ENABLE
#ifdef MOUSEKEY_ENABLE
    KEYCODE_STRING_NAME(MS_LEFT),
    KEYCODE_STRING_NAME(MS_RGHT),
    KEYCODE_STRING_NAME(MS_UP),
    KEYCODE_STRING_NAME(MS_DOWN),
    KEYCODE_STRING_NAME(MS_WHLL),
    KEYCODE_STRING_NAME(MS_WHLR),
    KEYCODE_STRING_NAME(MS_WHLU),
    KEYCODE_STRING_NAME(MS_WHLD),
#endif  // MOUSEKEY_ENABLE
#ifdef TRI_LAYER_ENABLE
    KEYCODE_STRING_NAME(TL_LOWR),
    KEYCODE_STRING_NAME(TL_UPPR),
#endif // TRI_LAYER_ENABLE
#ifdef GRAVE_ESC_ENABLE
    KEYCODE_STRING_NAME(QK_GESC),
#endif // GRAVE_ESC_ENABLE
#ifdef CAPS_WORD_ENABLE
    KEYCODE_STRING_NAME(CW_TOGG),
#endif // CAPS_WORD_ENABLE
#ifdef LAYER_LOCK_ENABLE
    KEYCODE_STRING_NAME(QK_LLCK),
#endif // LAYER_LOCK_ENABLE
    KEYCODE_STRING_NAME(DB_TOGG),
    KEYCODE_STRING_NAMES_END
};
// clang-format on
/** Users can override this to define names of additional keycodes. */
__attribute__((weak)) const keycode_string_name_t custom_keycode_names[] = {KEYCODE_STRING_NAMES_END};
/** Names of the 4 mods on each hand. */
static const char* mod_names[4] = {PSTR("CTL"), PSTR("SFT"), PSTR("ALT"), PSTR("GUI")};
/** Internal buffer for holding a stringified keycode. */
static char buffer[32];
#define BUFFER_MAX_LEN (sizeof(buffer) - 1)
static index_t buffer_len;

/**
 * @brief Finds the name of a keycode in `table` or returns NULL.
 *
 * The last entry of the table must be `KEYCODE_STRING_NAMES_END`.
 *
 * @param table   A table of keycode_string_name_t to be searched.
 * @return Name string for the keycode, or NULL if not found.
 */
static const char* find_keycode_name(const keycode_string_name_t* table, uint16_t keycode) {
    for (; table->keycode; ++table) {
        if (table->keycode == keycode) {
            return table->name;
        }
    }
    return NULL;
}

/** Formats `number` in `base`, either 10 or 16. */
static char* number_string(uint16_t number, int8_t base) {
    static char result[7];
    result[sizeof(result) - 1] = '\0';
    index_t i                  = sizeof(result) - 1;
    do {
        const uint8_t digit = number % base;
        number /= base;
        result[--i] = (digit < 10) ? (char)(digit + UINT8_C('0')) : (char)(digit + (UINT8_C('A') - 10));
    } while (number > 0 && i > 0);

    if (base == 16 && i >= 2) {
        result[--i] = 'x';
        result[--i] = '0';
    }
    return result + i;
}

/** Appends `str` to `buffer`, truncating if the result would overflow. */
static void append(const char* str) {
    char*   dest = buffer + buffer_len;
    index_t i;
    for (i = 0; buffer_len + i < BUFFER_MAX_LEN && str[i]; ++i) {
        dest[i] = str[i];
    }
    buffer_len += i;
    buffer[buffer_len] = '\0';
}

/** Same as append(), but where `str` is a PROGMEM string. */
static void append_P(const char* str) {
    char*   dest = buffer + buffer_len;
    index_t i;
    for (i = 0; buffer_len + i < BUFFER_MAX_LEN; ++i) {
        const char c = pgm_read_byte(&str[i]);
        if (c == '\0') {
            break;
        }
        dest[i] = c;
    }
    buffer_len += i;
    buffer[buffer_len] = '\0';
}

/** Appends a single char to `buffer` if there is space. */
static void append_char(char c) {
    if (buffer_len < BUFFER_MAX_LEN) {
        buffer[buffer_len]   = c;
        buffer[++buffer_len] = '\0';
    }
}

/** Formats `number` in `base`, either 10 or 16, and appends it to `buffer`. */
static void append_number(uint16_t number, int8_t base) {
    append(number_string(number, base));
}

/** Stringifies 5-bit mods and appends it to `buffer`. */
static void append_5_bit_mods(uint8_t mods) {
    const bool is_rhs = mods > 15;
    mods &= 15;
    if (mods != 0 && (mods & (mods - 1)) == 0) { // One mod is set.
        append_P(PSTR("MOD_"));
        append_char(is_rhs ? 'R' : 'L');
        append_P(mod_names[biton(mods)]);
    } else { // Fallback: write the mod as a hex value.
        append_number(mods, 16);
    }
}

/**
 * @brief Writes a keycode of the format `name` + "(" + `param` + ")".
 * @note `name` is a PROGMEM string, `param` is not.
 */
static void append_unary_keycode(const char* name, const char* param) {
    append_P(name);
    append_char('(');
    append(param);
    append_char(')');
}

/** Stringifies `keycode` and appends it to `buffer`. */
static void append_keycode(uint16_t keycode) {
    // Search the `custom_keycode_names` table first so that it is possible to
    // override how any keycode would be formatted otherwise.
    const char* keycode_name = find_keycode_name(custom_keycode_names, keycode);
    if (keycode_name) {
        append_P(keycode_name);
        return;
    }
    // Search the `keycode_names` table.
    keycode_name = find_keycode_name(keycode_names, keycode);
    if (keycode_name) {
        append_P(keycode_name);
        return;
    }

    if (keycode <= 255) { // Basic keycodes.
        switch (keycode) {
            // Modifiers KC_LSFT, KC_RCTL, etc.
            case MODIFIER_KEYCODE_RANGE: {
                const uint8_t i      = keycode - KC_LCTL;
                const bool    is_rhs = i > 3;
                append_P(PSTR("KC_"));
                append_char(is_rhs ? 'R' : 'L');
                append_P(mod_names[i & 3]);
            }
                return;

            // Letters A-Z.
            case KC_A ... KC_Z:
                append_P(PSTR("KC_"));
                append_char((char)(keycode + (UINT8_C('A') - KC_A)));
                return;

            // Digits 0-9 (NOTE: Unlike the ASCII order, KC_0 comes *after* KC_9.)
            case KC_1 ... KC_0:
                append_P(PSTR("KC_"));
                append_char('0' + (char)((keycode - (KC_1 - 1)) % 10));
                return;

            // Keypad digits.
            case KC_KP_1 ... KC_KP_0:
                append_P(PSTR("KC_KP_"));
                append_char('0' + (char)((keycode - (KC_KP_1 - 1)) % 10));
                return;

            // Function keys. F1-F12 and F13-F24 are coded in separate ranges.
            case KC_F1 ... KC_F12:
                append_P(PSTR("KC_F"));
                append_number(keycode - (KC_F1 - 1), 10);
                return;

            case KC_F13 ... KC_F24:
                append_P(PSTR("KC_F"));
                append_number(keycode - (KC_F13 - 13), 10);
                return;
        }
    }

    // clang-format off
    switch (keycode) {
        // A modified keycode, like S(KC_1) for Shift + 1 = !. This implementation
        // only covers modified keycodes where one modifier is applied, e.g. a
        // Ctrl + Shift + kc or Hyper + kc keycode is not formatted.
        case QK_MODS ... QK_MODS_MAX: {
            uint8_t mods = QK_MODS_GET_MODS(keycode);
            const bool is_rhs = mods > 15;
            mods &= 15;
            if (mods != 0 && (mods & (mods - 1)) == 0) {  // One mod is set.
                const char* name = mod_names[biton(mods)];
                if (is_rhs) {
                    append_char('R');
                    append_P(name);
                } else {
                    append_char(pgm_read_byte(&name[0]));
                }
                append_char('(');
                append_keycode(QK_MODS_GET_BASIC_KEYCODE(keycode));
                append_char(')');
                return;
            }
        } break;

        // One-shot mod OSM(mod) key.
        case QK_ONE_SHOT_MOD ... QK_ONE_SHOT_MOD_MAX:
            append_P(PSTR("OSM("));
            append_5_bit_mods(QK_ONE_SHOT_MOD_GET_MODS(keycode));
            append_char(')');
            return;

        // Various layer switch keys.
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:  // Layer-tap LT(layer,kc) key.
            append_P(PSTR("LT("));
            append_number(QK_LAYER_TAP_GET_LAYER(keycode), 10);
            append_char(',');
            append_keycode(QK_LAYER_TAP_GET_TAP_KEYCODE(keycode));
            append_char(')');
            return;

        case QK_LAYER_MOD ... QK_LAYER_MOD_MAX:  // LM(layer,mod) key.
            append_P(PSTR("LM("));
            append_number(QK_LAYER_MOD_GET_LAYER(keycode), 10);
            append_char(',');
            append_5_bit_mods(QK_LAYER_MOD_GET_MODS(keycode));
            append_char(')');
            return;

        case QK_TO ... QK_TO_MAX:  // TO(layer) key.
            append_unary_keycode(PSTR("TO"), number_string(QK_TO_GET_LAYER(keycode), 10));
            return;

        case QK_MOMENTARY ... QK_MOMENTARY_MAX:  // MO(layer) key.
            append_unary_keycode(PSTR("MO"), number_string(QK_MOMENTARY_GET_LAYER(keycode), 10));
            return;

        case QK_DEF_LAYER ... QK_DEF_LAYER_MAX:  // DF(layer) key.
            append_unary_keycode(PSTR("DF"), number_string(QK_DEF_LAYER_GET_LAYER(keycode), 10));
            return;

        case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX:  // TG(layer) key.
            append_unary_keycode(PSTR("TG"), number_string(QK_TOGGLE_LAYER_GET_LAYER(keycode), 10));
            return;

        case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:  // OSL(layer) key.
            append_unary_keycode(PSTR("OSL"), number_string(QK_ONE_SHOT_LAYER_GET_LAYER(keycode), 10));
            return;

        case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:  // TT(layer) key.
            append_unary_keycode(PSTR("TT"), number_string(QK_LAYER_TAP_TOGGLE_GET_LAYER(keycode), 10));
            return;

        case QK_PERSISTENT_DEF_LAYER ... QK_PERSISTENT_DEF_LAYER_MAX:  // PDF(layer) key.
            append_unary_keycode(PSTR("PDF"), number_string(QK_PERSISTENT_DEF_LAYER_GET_LAYER(keycode), 10));
            return;

        // Mod-tap MT(mod,kc) key. This implementation formats the MT keys where
        // one modifier is applied. For MT keys with multiple modifiers, the mod
        // arg is written numerically as a hex code.
        case QK_MOD_TAP ... QK_MOD_TAP_MAX: {
            uint8_t mods = QK_MOD_TAP_GET_MODS(keycode);
            const bool is_rhs = mods > 15;
            mods &= 15;
            if (mods != 0 && (mods & (mods - 1)) == 0) {  // One mod is set.
                append_char(is_rhs ? 'R' : 'L');
                append_P(mod_names[biton(mods)]);
                append_P(PSTR("_T("));
            } else {
                append_P(PSTR("MT("));
                append_number(mods, 16);
                append_char(',');
            }
            append_keycode(QK_MOD_TAP_GET_TAP_KEYCODE(keycode));
            append_char(')');
        }   return;

        case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:  // Tap dance TD(i) key.
            append_unary_keycode(PSTR("TD"), number_string(QK_TAP_DANCE_GET_INDEX(keycode), 10));
            return;

#ifdef UNICODE_ENABLE
        case QK_UNICODE ... QK_UNICODE_MAX:  // Unicode UC(codepoint) key.
            append_unary_keycode(PSTR("UC"), number_string(QK_UNICODE_GET_CODE_POINT(keycode), 16));
            return;
#elif defined(UNICODEMAP_ENABLE)
        case QK_UNICODEMAP ... QK_UNICODEMAP_MAX:  // Unicode Map UM(i) key.
            append_unary_keycode(PSTR("UM"), number_string(QK_UNICODEMAP_GET_INDEX(keycode), 10));
            return;

        case QK_UNICODEMAP_PAIR ... QK_UNICODEMAP_PAIR_MAX: {  // UP(i,j) key.
            const uint8_t i = QK_UNICODEMAP_PAIR_GET_UNSHIFTED_INDEX(keycode);
            const uint8_t j = QK_UNICODEMAP_PAIR_GET_SHIFTED_INDEX(keycode);
            append_P(PSTR("UP("));
            append_number(i, 10);
            append_char(',');
            append_number(j, 10);
            append_char(')');
        }   return dest;
#endif
#ifdef MOUSEKEY_ENABLE
        case MS_BTN1 ... MS_BTN8:  // Mouse button keycode.
            append_P(PSTR("MS_BTN"));
            append_number(keycode - (MS_BTN1 - 1), 10);
            return;
#endif  // MOUSEKEY_ENABLE

        case KB_KEYCODE_RANGE:  // Keyboard range keycode.
            append_P(PSTR("QK_KB_"));
            append_number(keycode - QK_KB_0, 10);
            return;

        case USER_KEYCODE_RANGE:  // User range keycode.
            append_P(PSTR("QK_USER_"));
            append_number(keycode - QK_USER_0, 10);
            return;
    }
    // clang-format on

    append_number(keycode, 16); // Fallback: write keycode as hex value.
}

const char* keycode_string(uint16_t keycode) {
    buffer_len = 0;
    buffer[0]  = '\0';
    append_keycode(keycode);
    return buffer;
}
