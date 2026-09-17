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
#include "util.h"

typedef int_fast8_t index_t;

// clang-format off
/** Packs a 7-char keycode name, ignoring the third char, as 3 words. */
#define KEYCODE_NAME7(c0, c1, unused_c2, c3, c4, c5, c6) \
    ((uint16_t)c0) | (((uint16_t)c1) << 8),              \
    ((uint16_t)c3) | (((uint16_t)c4) << 8),              \
    ((uint16_t)c5) | (((uint16_t)c6) << 8)

/**
 * @brief Names of some common keycodes.
 *
 * Each (keycode, name) entry is stored flat in 8 bytes in PROGMEM. Names in
 * this table must be at most 7 chars long and have an underscore '_' for the
 * third char. This underscore is assumed and not actually stored.
 *
 * To save memory, feature-specific key entries are ifdef'd to include them only
 * when their feature is enabled.
 */
static const uint16_t common_names[] PROGMEM = {
    KC_TRNS, KEYCODE_NAME7('K', 'C', '_', 'T', 'R', 'N', 'S'),
    KC_ENT , KEYCODE_NAME7('K', 'C', '_', 'E', 'N', 'T',  0 ),
    KC_ESC , KEYCODE_NAME7('K', 'C', '_', 'E', 'S', 'C',  0 ),
    KC_BSPC, KEYCODE_NAME7('K', 'C', '_', 'B', 'S', 'P', 'C'),
    KC_TAB , KEYCODE_NAME7('K', 'C', '_', 'T', 'A', 'B',  0 ),
    KC_SPC , KEYCODE_NAME7('K', 'C', '_', 'S', 'P', 'C',  0 ),
    KC_MINS, KEYCODE_NAME7('K', 'C', '_', 'M', 'I', 'N', 'S'),
    KC_EQL , KEYCODE_NAME7('K', 'C', '_', 'E', 'Q', 'L',  0 ),
    KC_LBRC, KEYCODE_NAME7('K', 'C', '_', 'L', 'B', 'R', 'C'),
    KC_RBRC, KEYCODE_NAME7('K', 'C', '_', 'R', 'B', 'R', 'C'),
    KC_BSLS, KEYCODE_NAME7('K', 'C', '_', 'B', 'S', 'L', 'S'),
    KC_NUHS, KEYCODE_NAME7('K', 'C', '_', 'N', 'U', 'H', 'S'),
    KC_SCLN, KEYCODE_NAME7('K', 'C', '_', 'S', 'C', 'L', 'N'),
    KC_QUOT, KEYCODE_NAME7('K', 'C', '_', 'Q', 'U', 'O', 'T'),
    KC_GRV , KEYCODE_NAME7('K', 'C', '_', 'G', 'R', 'V',  0 ),
    KC_COMM, KEYCODE_NAME7('K', 'C', '_', 'C', 'O', 'M', 'M'),
    KC_DOT , KEYCODE_NAME7('K', 'C', '_', 'D', 'O', 'T',  0 ),
    KC_SLSH, KEYCODE_NAME7('K', 'C', '_', 'S', 'L', 'S', 'H'),
    KC_CAPS, KEYCODE_NAME7('K', 'C', '_', 'C', 'A', 'P', 'S'),
    KC_PSCR, KEYCODE_NAME7('K', 'C', '_', 'P', 'S', 'C', 'R'),
    KC_PAUS, KEYCODE_NAME7('K', 'C', '_', 'P', 'A', 'U', 'S'),
    KC_INS , KEYCODE_NAME7('K', 'C', '_', 'I', 'N', 'S',  0 ),
    KC_HOME, KEYCODE_NAME7('K', 'C', '_', 'H', 'O', 'M', 'E'),
    KC_PGUP, KEYCODE_NAME7('K', 'C', '_', 'P', 'G', 'U', 'P'),
    KC_DEL , KEYCODE_NAME7('K', 'C', '_', 'D', 'E', 'L',  0 ),
    KC_END , KEYCODE_NAME7('K', 'C', '_', 'E', 'N', 'D',  0 ),
    KC_PGDN, KEYCODE_NAME7('K', 'C', '_', 'P', 'G', 'D', 'N'),
    KC_RGHT, KEYCODE_NAME7('K', 'C', '_', 'R', 'G', 'H', 'T'),
    KC_LEFT, KEYCODE_NAME7('K', 'C', '_', 'L', 'E', 'F', 'T'),
    KC_DOWN, KEYCODE_NAME7('K', 'C', '_', 'D', 'O', 'W', 'N'),
    KC_UP  , KEYCODE_NAME7('K', 'C', '_', 'U', 'P',  0 ,  0 ),
    KC_NUBS, KEYCODE_NAME7('K', 'C', '_', 'N', 'U', 'B', 'S'),
    KC_HYPR, KEYCODE_NAME7('K', 'C', '_', 'H', 'Y', 'P', 'R'),
    KC_MEH , KEYCODE_NAME7('K', 'C', '_', 'M', 'E', 'H',  0 ),
#ifdef EXTRAKEY_ENABLE
    KC_WHOM, KEYCODE_NAME7('K', 'C', '_', 'W', 'H', 'O', 'M'),
    KC_WBAK, KEYCODE_NAME7('K', 'C', '_', 'W', 'B', 'A', 'K'),
    KC_WFWD, KEYCODE_NAME7('K', 'C', '_', 'W', 'F', 'W', 'D'),
    KC_WSTP, KEYCODE_NAME7('K', 'C', '_', 'W', 'S', 'T', 'P'),
    KC_WREF, KEYCODE_NAME7('K', 'C', '_', 'W', 'R', 'E', 'F'),
    KC_MNXT, KEYCODE_NAME7('K', 'C', '_', 'M', 'N', 'X', 'T'),
    KC_MPRV, KEYCODE_NAME7('K', 'C', '_', 'M', 'P', 'R', 'V'),
    KC_MPLY, KEYCODE_NAME7('K', 'C', '_', 'M', 'P', 'L', 'Y'),
    KC_MUTE, KEYCODE_NAME7('K', 'C', '_', 'M', 'U', 'T', 'E'),
    KC_VOLU, KEYCODE_NAME7('K', 'C', '_', 'V', 'O', 'L', 'U'),
    KC_VOLD, KEYCODE_NAME7('K', 'C', '_', 'V', 'O', 'L', 'D'),
#endif // EXTRAKEY_ENABLE
#ifdef MOUSEKEY_ENABLE
    MS_LEFT, KEYCODE_NAME7('M', 'S', '_', 'L', 'E', 'F', 'T'),
    MS_RGHT, KEYCODE_NAME7('M', 'S', '_', 'R', 'G', 'H', 'T'),
    MS_UP  , KEYCODE_NAME7('M', 'S', '_', 'U', 'P',  0 ,  0 ),
    MS_DOWN, KEYCODE_NAME7('M', 'S', '_', 'D', 'O', 'W', 'N'),
    MS_WHLL, KEYCODE_NAME7('M', 'S', '_', 'W', 'H', 'L', 'L'),
    MS_WHLR, KEYCODE_NAME7('M', 'S', '_', 'W', 'H', 'L', 'R'),
    MS_WHLU, KEYCODE_NAME7('M', 'S', '_', 'W', 'H', 'L', 'U'),
    MS_WHLD, KEYCODE_NAME7('M', 'S', '_', 'W', 'H', 'L', 'D'),
#endif // MOUSEKEY_ENABLE
#ifdef SWAP_HANDS_ENABLE
    SH_ON  , KEYCODE_NAME7('S', 'H', '_', 'O', 'N',  0 ,  0 ),
    SH_OFF , KEYCODE_NAME7('S', 'H', '_', 'O', 'F', 'F',  0 ),
    SH_MON , KEYCODE_NAME7('S', 'H', '_', 'M', 'O', 'N',  0 ),
    SH_MOFF, KEYCODE_NAME7('S', 'H', '_', 'M', 'O', 'F', 'F'),
    SH_TOGG, KEYCODE_NAME7('S', 'H', '_', 'T', 'O', 'G', 'G'),
    SH_TT  , KEYCODE_NAME7('S', 'H', '_', 'T', 'T',  0 ,  0 ),
#    if !defined(NO_ACTION_ONESHOT)
    SH_OS  , KEYCODE_NAME7('S', 'H', '_', 'O', 'S',  0 ,  0 ),
#    endif // !defined(NO_ACTION_ONESHOT)
#endif // SWAP_HANDS_ENABLE
#ifdef LEADER_ENABLE
    QK_LEAD, KEYCODE_NAME7('Q', 'K', '_', 'L', 'E', 'A', 'D'),
#endif // LEADER_ENABLE
#ifdef KEY_LOCK_ENABLE
    QK_LOCK, KEYCODE_NAME7('Q', 'K', '_', 'L', 'O', 'C', 'K'),
#endif // KEY_LOCK_ENABLE
#ifdef TRI_LAYER_ENABLE
    TL_LOWR, KEYCODE_NAME7('T', 'L', '_', 'L', 'O', 'W', 'R'),
    TL_UPPR, KEYCODE_NAME7('T', 'L', '_', 'U', 'P', 'P', 'R'),
#endif // TRI_LAYER_ENABLE
#ifdef GRAVE_ESC_ENABLE
    QK_GESC, KEYCODE_NAME7('Q', 'K', '_', 'G', 'E', 'S', 'C'),
#endif // GRAVE_ESC_ENABLE
#ifdef CAPS_WORD_ENABLE
    CW_TOGG, KEYCODE_NAME7('C', 'W', '_', 'T', 'O', 'G', 'G'),
#endif // CAPS_WORD_ENABLE
#ifdef SECURE_ENABLE
    SE_LOCK, KEYCODE_NAME7('S', 'E', '_', 'L', 'O', 'C', 'K'),
    SE_UNLK, KEYCODE_NAME7('S', 'E', '_', 'U', 'N', 'L', 'K'),
    SE_TOGG, KEYCODE_NAME7('S', 'E', '_', 'T', 'O', 'G', 'G'),
    SE_REQ , KEYCODE_NAME7('S', 'E', '_', 'R', 'E', 'Q',  0 ),
#endif // SECURE_ENABLE
#ifdef LAYER_LOCK_ENABLE
    QK_LLCK, KEYCODE_NAME7('Q', 'K', '_', 'L', 'L', 'C', 'K'),
#endif // LAYER_LOCK_ENABLE
    EE_CLR , KEYCODE_NAME7('E', 'E', '_', 'C', 'L', 'R',  0 ),
    QK_BOOT, KEYCODE_NAME7('Q', 'K', '_', 'B', 'O', 'O', 'T'),
    DB_TOGG, KEYCODE_NAME7('D', 'B', '_', 'T', 'O', 'G', 'G'),
};
// clang-format on

/** Users can override this to define names of additional keycodes. */
__attribute__((weak)) const keycode_string_name_t* keycode_string_names_data_user = NULL;
__attribute__((weak)) uint16_t                     keycode_string_names_size_user = 0;
/** Keyboard vendors can override this to define names of additional keycodes. */
__attribute__((weak)) const keycode_string_name_t* keycode_string_names_data_kb = NULL;
__attribute__((weak)) uint16_t                     keycode_string_names_size_kb = 0;
/** Names of the 4 mods on each hand. */
static const char mod_names[] PROGMEM = "CTL\0SFT\0ALT\0GUI";
/** Internal buffer for holding a stringified keycode. */
static char buffer[32];
#define BUFFER_MAX_LEN (sizeof(buffer) - 1)
static index_t buffer_len;

/** Finds the name of a keycode in `common_names` or returns NULL. */
static const char* search_common_names(uint16_t keycode) {
    static uint8_t buffer[8];

    for (int_fast16_t offset = 0; offset < ARRAY_SIZE(common_names); offset += 4) {
        if (keycode == pgm_read_word(common_names + offset)) {
            const uint16_t w0 = pgm_read_word(common_names + offset + 1);
            const uint16_t w1 = pgm_read_word(common_names + offset + 2);
            const uint16_t w2 = pgm_read_word(common_names + offset + 3);
            buffer[0]         = (uint8_t)w0;
            buffer[1]         = (uint8_t)(w0 >> 8);
            buffer[2]         = '_';
            buffer[3]         = (uint8_t)w1;
            buffer[4]         = (uint8_t)(w1 >> 8);
            buffer[5]         = (uint8_t)w2;
            buffer[6]         = (uint8_t)(w2 >> 8);
            buffer[7]         = 0;
            return (const char*)buffer;
        }
    }

    return NULL;
}

/**
 * @brief Finds the name of a keycode in table or returns NULL.
 *
 * @param data   Pointer to table to be searched.
 * @param size   Numer of entries in the table.
 * @return Name string for the keycode, or NULL if not found.
 */
static const char* search_table(const keycode_string_name_t* data, uint16_t size, uint16_t keycode) {
    if (data != NULL) {
        for (uint16_t i = 0; i < size; ++i) {
            if (data[i].keycode == keycode) {
                return data[i].name;
            }
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
    const bool    is_rhs = mods > 15;
    const uint8_t csag   = mods & 15;
    if (csag != 0 && (csag & (csag - 1)) == 0) { // One mod is set.
        append_P(PSTR("MOD_"));
        append_char(is_rhs ? 'R' : 'L');
        append_P(&mod_names[4 * biton(csag)]);
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

/**
 * @brief Writes a keycode of the format `name` + `number`.
 * @note `name` is a PROGMEM string.
 */
static void append_numbered_keycode(const char* name, uint16_t number) {
    append_P(name);
    append_number(number, 10);
}

/** Stringifies `keycode` and appends it to `buffer`. */
static void append_keycode(uint16_t keycode) {
    // In case there is overlap among tables, search `keycode_string_names_user`
    // first so that it takes precedence.
    const char* keycode_name = search_table(keycode_string_names_data_user, keycode_string_names_size_user, keycode);
    if (keycode_name) {
        append(keycode_name);
        return;
    }
    keycode_name = search_table(keycode_string_names_data_kb, keycode_string_names_size_kb, keycode);
    if (keycode_name) {
        append(keycode_name);
        return;
    }
    keycode_name = search_common_names(keycode);
    if (keycode_name) {
        append(keycode_name);
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
                append_P(&mod_names[4 * (i & 3)]);
            }
                return;

            // Letters A-Z.
            case KC_A ... KC_Z:
                append_P(PSTR("KC_"));
                append_char((char)(keycode + (UINT8_C('A') - KC_A)));
                return;

            // Digits 0-9 (NOTE: Unlike the ASCII order, KC_0 comes *after* KC_9.)
            case KC_1 ... KC_0:
                append_numbered_keycode(PSTR("KC_"), (keycode - (KC_1 - 1)) % 10);
                return;

            // Keypad digits.
            case KC_KP_1 ... KC_KP_0:
                append_numbered_keycode(PSTR("KC_KP_"), (keycode - (KC_KP_1 - 1)) % 10);
                return;

            // Function keys. F1-F12 and F13-F24 are coded in separate ranges.
            case KC_F1 ... KC_F12:
                append_numbered_keycode(PSTR("KC_F"), keycode - (KC_F1 - 1));
                return;

            case KC_F13 ... KC_F24:
                append_numbered_keycode(PSTR("KC_F"), keycode - (KC_F13 - 13));
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
            if (mods != 0 && (mods & (mods - 1)) == 0) { // One mod is set.
                const char* name = &mod_names[4 * biton(mods)];
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

#if !defined(NO_ACTION_ONESHOT)
        case QK_ONE_SHOT_MOD ... QK_ONE_SHOT_MOD_MAX: // One-shot mod OSM(mod) key.
            append_P(PSTR("OSM("));
            append_5_bit_mods(QK_ONE_SHOT_MOD_GET_MODS(keycode));
            append_char(')');
            return;
#endif // !defined(NO_ACTION_ONESHOT)

        // Various layer switch keys.
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX: // Layer-tap LT(layer,kc) key.
            append_P(PSTR("LT("));
            append_number(QK_LAYER_TAP_GET_LAYER(keycode), 10);
            append_char(',');
            append_keycode(QK_LAYER_TAP_GET_TAP_KEYCODE(keycode));
            append_char(')');
            return;

        case QK_LAYER_MOD ... QK_LAYER_MOD_MAX: // LM(layer,mod) key.
            append_P(PSTR("LM("));
            append_number(QK_LAYER_MOD_GET_LAYER(keycode), 10);
            append_char(',');
            append_5_bit_mods(QK_LAYER_MOD_GET_MODS(keycode));
            append_char(')');
            return;

        case QK_TO ... QK_TO_MAX: // TO(layer) key.
            append_unary_keycode(PSTR("TO"), number_string(QK_TO_GET_LAYER(keycode), 10));
            return;

        case QK_MOMENTARY ... QK_MOMENTARY_MAX: // MO(layer) key.
            append_unary_keycode(PSTR("MO"), number_string(QK_MOMENTARY_GET_LAYER(keycode), 10));
            return;

        case QK_DEF_LAYER ... QK_DEF_LAYER_MAX: // DF(layer) key.
            append_unary_keycode(PSTR("DF"), number_string(QK_DEF_LAYER_GET_LAYER(keycode), 10));
            return;

        case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX: // TG(layer) key.
            append_unary_keycode(PSTR("TG"), number_string(QK_TOGGLE_LAYER_GET_LAYER(keycode), 10));
            return;

#if !defined(NO_ACTION_ONESHOT)
        case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX: // OSL(layer) key.
            append_unary_keycode(PSTR("OSL"), number_string(QK_ONE_SHOT_LAYER_GET_LAYER(keycode), 10));
            return;
#endif // !defined(NO_ACTION_ONESHOT)

        case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX: // TT(layer) key.
            append_unary_keycode(PSTR("TT"), number_string(QK_LAYER_TAP_TOGGLE_GET_LAYER(keycode), 10));
            return;

        case QK_PERSISTENT_DEF_LAYER ... QK_PERSISTENT_DEF_LAYER_MAX: // PDF(layer) key.
            append_unary_keycode(PSTR("PDF"), number_string(QK_PERSISTENT_DEF_LAYER_GET_LAYER(keycode), 10));
            return;

        // Mod-tap MT(mod,kc) key. This implementation formats the MT keys where
        // one modifier is applied. For MT keys with multiple modifiers, the mod
        // arg is written numerically as a hex code.
        case QK_MOD_TAP ... QK_MOD_TAP_MAX: {
            uint8_t mods = QK_MOD_TAP_GET_MODS(keycode);
            const bool is_rhs = mods > 15;
            const uint8_t csag = mods & 15;
            if (csag != 0 && (csag & (csag - 1)) == 0) { // One mod is set.
                append_char(is_rhs ? 'R' : 'L');
                append_P(&mod_names[4 * biton(csag)]);
                append_P(PSTR("_T("));
            } else if (mods == MOD_HYPR) {
                append_P(PSTR("HYPR_T("));
            } else if (mods == MOD_MEH) {
                append_P(PSTR("MEH_T("));
            } else {
                append_P(PSTR("MT("));
                append_number(mods, 16);
                append_char(',');
            }
            append_keycode(QK_MOD_TAP_GET_TAP_KEYCODE(keycode));
            append_char(')');
        }   return;

        case QK_TAP_DANCE ... QK_TAP_DANCE_MAX: // Tap dance TD(i) key.
            append_unary_keycode(PSTR("TD"), number_string(QK_TAP_DANCE_GET_INDEX(keycode), 10));
            return;

#ifdef UNICODE_ENABLE
        case QK_UNICODE ... QK_UNICODE_MAX: // Unicode UC(codepoint) key.
            append_unary_keycode(PSTR("UC"), number_string(QK_UNICODE_GET_CODE_POINT(keycode), 16));
            return;
#elif defined(UNICODEMAP_ENABLE)
        case QK_UNICODEMAP ... QK_UNICODEMAP_MAX: // Unicode Map UM(i) key.
            append_unary_keycode(PSTR("UM"), number_string(QK_UNICODEMAP_GET_INDEX(keycode), 10));
            return;

        case QK_UNICODEMAP_PAIR ... QK_UNICODEMAP_PAIR_MAX: { // UP(i,j) key.
            const uint8_t i = QK_UNICODEMAP_PAIR_GET_UNSHIFTED_INDEX(keycode);
            const uint8_t j = QK_UNICODEMAP_PAIR_GET_SHIFTED_INDEX(keycode);
            append_P(PSTR("UP("));
            append_number(i, 10);
            append_char(',');
            append_number(j, 10);
            append_char(')');
        }   return;
#endif
#ifdef MOUSEKEY_ENABLE
        case MS_BTN1 ... MS_BTN8: // Mouse button keycode.
            append_numbered_keycode(PSTR("MS_BTN"), keycode - (MS_BTN1 - 1));
            return;
#endif // MOUSEKEY_ENABLE
#ifdef SWAP_HANDS_ENABLE
        case QK_SWAP_HANDS ... QK_SWAP_HANDS_MAX: // Swap Hands SH_T(kc) key.
            if (!IS_SWAP_HANDS_KEYCODE(keycode)) {
                append_P(PSTR("SH_T("));
                append_keycode(QK_SWAP_HANDS_GET_TAP_KEYCODE(keycode));
                append_char(')');
                return;
            }
            break;
#endif // SWAP_HANDS_ENABLE
#ifdef JOYSTICK_ENABLE
        case JOYSTICK_KEYCODE_RANGE: // Joystick JS_ key.
            append_numbered_keycode(PSTR("JS_"), keycode - JS_0);
            return;
#endif // JOYSTICK_ENABLE
#ifdef PROGRAMMABLE_BUTTON_ENABLE
        case PROGRAMMABLE_BUTTON_KEYCODE_RANGE: // Programmable button PB_ key.
            append_numbered_keycode(PSTR("PB_"), keycode - (PB_1 - 1));
            return;
#endif // PROGRAMMABLE_BUTTON_ENABLE

        case MACRO_KEYCODE_RANGE: // Macro range MC_ keycode.
            append_numbered_keycode(PSTR("MC_"), keycode - MC_0);
            return;

        case KB_KEYCODE_RANGE: // Keyboard range keycode.
            append_numbered_keycode(PSTR("QK_KB_"), keycode - QK_KB_0);
            return;

        case USER_KEYCODE_RANGE: // User range keycode.
            append_numbered_keycode(PSTR("QK_USER_"), keycode - QK_USER_0);
            return;

        // It would take a nontrivial amount of string data to cover some
        // feature-specific keycodes, such as those for MIDI and lighting. As a
        // fallback while still providing some information, we stringify
        // remaining keys in known code ranges as "QK_<feature>+<number>".
#ifdef MAGIC_ENABLE
        case MAGIC_KEYCODE_RANGE:
            append_numbered_keycode(PSTR("QK_MAGIC+"), keycode - QK_MAGIC);
            return;
#endif // MAGIC_ENABLE
#ifdef MIDI_ENABLE
        case MIDI_KEYCODE_RANGE:
            append_numbered_keycode(PSTR("QK_MIDI+"), keycode - QK_MIDI);
            return;
#endif // MIDI_ENABLE
#ifdef SEQUENCER_ENABLE
        case SEQUENCER_KEYCODE_RANGE:
            append_numbered_keycode(PSTR("QK_SEQUENCER+"), keycode - QK_SEQUENCER);
            return;
#endif // SEQUENCER_ENABLE
#ifdef AUDIO_ENABLE
        case AUDIO_KEYCODE_RANGE:
            append_numbered_keycode(PSTR("QK_AUDIO+"), keycode - QK_AUDIO);
            return;
#endif // AUDIO_ENABLE
#if defined(BACKLIGHT_ENABLE) || defined(LED_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLED) || defined(RGB_MATRIX_ENABLE) // Lighting-related features.
        case QK_LIGHTING ... QK_LIGHTING_MAX:
            append_numbered_keycode(PSTR("QK_LIGHTING+"), keycode - QK_LIGHTING);
            return;
#endif // defined(BACKLIGHT_ENABLE) || defined(LED_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLED) || defined(RGB_MATRIX_ENABLE)
#ifdef STENO_ENABLE
        case STENO_KEYCODE_RANGE:
            append_numbered_keycode(PSTR("QK_STENO+"), keycode - QK_STENO);
            return;
#endif // AUDIO_ENABLE
#ifdef BLUETOOTH_ENABLE
        case CONNECTION_KEYCODE_RANGE:
            append_numbered_keycode(PSTR("QK_CONNECTION+"), keycode - QK_CONNECTION);
            return;
#endif // BLUETOOTH_ENABLE
        case QUANTUM_KEYCODE_RANGE:
            append_numbered_keycode(PSTR("QK_QUANTUM+"), keycode - QK_QUANTUM);
            return;
    }
    // clang-format on

    append_number(keycode, 16); // Fallback: write keycode as hex value.
}

const char* get_keycode_string(uint16_t keycode) {
    buffer_len = 0;
    buffer[0]  = '\0';
    append_keycode(keycode);
    return buffer;
}
