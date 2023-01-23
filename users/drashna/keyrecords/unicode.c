// Copyright 2020 @ridingqwerty
// Copyright 2020 @tzarc
// Copyright 2021 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "drashna.h"
#include "unicode.h"
#include "process_unicode_common.h"

uint8_t unicode_typing_mode = UCTM_NO_MODE;
const char unicode_mode_str[UNCODES_MODE_END][13] PROGMEM = {
    "      Normal\0",
    "        Wide\0",
    "      Script\0",
    "      Blocks\0",
    "    Regional\0",
    "      Aussie\0",
    "       Zalgo\0",
    "Super Script\0",
    "       Comic\0",
};

/**
 * @brief Registers the unicode keystrokes based on desired unicode
 *
 * @param glyph Unicode character, supports up to 0x1FFFF (or higher)
 */
void tap_unicode_glyph_nomods(uint32_t glyph) {
    uint8_t temp_mod = get_mods();
    clear_mods();
    clear_oneshot_mods();
    register_unicode(glyph);
    set_mods(temp_mod);
}

typedef uint32_t (*translator_function_t)(bool is_shifted, uint32_t keycode);

#define DEFINE_UNICODE_RANGE_TRANSLATOR(translator_name, lower_alpha, upper_alpha, zero_glyph, number_one, space_glyph) \
    static inline uint32_t translator_name(bool is_shifted, uint32_t keycode) {                                         \
        switch (keycode) {                                                                                              \
            case KC_A ... KC_Z:                                                                                         \
                return (is_shifted ? upper_alpha : lower_alpha) + keycode - KC_A;                                       \
            case KC_0:                                                                                                  \
                return zero_glyph;                                                                                      \
            case KC_1 ... KC_9:                                                                                         \
                return (number_one + keycode - KC_1);                                                                   \
            case KC_SPACE:                                                                                              \
                return space_glyph;                                                                                     \
        }                                                                                                               \
        return keycode;                                                                                                 \
    }

#define DEFINE_UNICODE_LUT_TRANSLATOR(translator_name, ...)                     \
    static inline uint32_t translator_name(bool is_shifted, uint32_t keycode) { \
        static const uint32_t translation[] = {__VA_ARGS__};                    \
        uint32_t              ret           = keycode;                          \
        if ((keycode - KC_A) < ARRAY_SIZE(translation)) {      \
            ret = translation[keycode - KC_A];                                  \
        }                                                                       \
        return ret;                                                             \
    }

/**
 * @brief Handler function for outputting unicode.
 *
 * @param keycode Keycode from matrix.
 * @param record keyrecord_t data structure
 * @param translator translator lut for different unicode modes
 * @return true Continue processing matrix press, and send to host
 * @return false Replace keycode, and do not send to host
 */
bool process_record_glyph_replacement(uint16_t keycode, keyrecord_t *record, translator_function_t translator) {
    uint8_t temp_mod   = get_mods();
    uint8_t temp_osm   = get_oneshot_mods();
    bool    is_shifted = (temp_mod | temp_osm) & MOD_MASK_SHIFT;
    if (((temp_mod | temp_osm) & (MOD_MASK_CTRL | MOD_MASK_ALT | MOD_MASK_GUI)) == 0) {
        if (KC_A <= keycode && keycode <= KC_Z) {
            if (record->event.pressed) {
                tap_unicode_glyph_nomods(translator(is_shifted, keycode));
            }
            return false;
        } else if (KC_1 <= keycode && keycode <= KC_0) {
            if (is_shifted) { // skip shifted numbers, so that we can still use symbols etc.
                return process_record_keymap(keycode, record);
            }
            if (record->event.pressed) {
                register_unicode(translator(is_shifted, keycode));
            }
            return false;
        } else if (keycode == KC_SPACE) {
            if (record->event.pressed) {
                register_unicode(translator(is_shifted, keycode));
            }
            return false;
        }
    }
    return true;
}

DEFINE_UNICODE_RANGE_TRANSLATOR(unicode_range_translator_wide, 0xFF41, 0xFF21, 0xFF10, 0xFF11, 0x2003);
DEFINE_UNICODE_RANGE_TRANSLATOR(unicode_range_translator_script, 0x1D4EA, 0x1D4D0, 0x1D7CE, 0x1D7C1, 0x2002);
DEFINE_UNICODE_RANGE_TRANSLATOR(unicode_range_translator_boxes, 0x1F170, 0x1F170, '0', '1', 0x2002);
DEFINE_UNICODE_RANGE_TRANSLATOR(unicode_range_translator_regional, 0x1F1E6, 0x1F1E6, '0', '1', 0x2003);

// DEFINE_UNICODE_LUT_TRANSLATOR(unicode_lut_translator_normal,
//                               'a', // a
//                               'b', // b
//                               'c', // c
//                               'd', // d
//                               'e', // e
//                               'f', // f
//                               'g', // g
//                               'h', // h
//                               'i', // i
//                               'j', // j
//                               'k', // k
//                               'l', // l
//                               'm', // m
//                               'n', // n
//                               'o', // o
//                               'p', // p
//                               'q', // q
//                               'r', // r
//                               's', // s
//                               't', // t
//                               'u', // u
//                               'v', // v
//                               'w', // w
//                               'x', // x
//                               'y', // y
//                               'z', // z
//                               '1', // 1
//                               '2', // 2
//                               '3', // 3
//                               '4', // 4
//                               '5', // 5
//                               '6', // 6
//                               '7', // 7
//                               '8', // 8
//                               '9', // 9
//                               '0'  // 0
// );

DEFINE_UNICODE_LUT_TRANSLATOR(unicode_lut_translator_aussie,
                              0x0250, // a
                              'q',    // b
                              0x0254, // c
                              'p',    // d
                              0x01DD, // e
                              0x025F, // f
                              0x0183, // g
                              0x0265, // h
                              0x1D09, // i
                              0x027E, // j
                              0x029E, // k
                              'l',    // l
                              0x026F, // m
                              'u',    // n
                              'o',    // o
                              'd',    // p
                              'b',    // q
                              0x0279, // r
                              's',    // s
                              0x0287, // t
                              'n',    // u
                              0x028C, // v
                              0x028D, // w
                              0x2717, // x
                              0x028E, // y
                              'z',    // z
                              0x0269, // 1
                              0x3139, // 2
                              0x0190, // 3
                              0x3123, // 4
                              0x03DB, // 5
                              '9',    // 6
                              0x3125, // 7
                              '8',    // 8
                              '6',    // 9
                              '0'     // 0
);

DEFINE_UNICODE_LUT_TRANSLATOR(unicode_lut_translator_super,
                              0x1D43, // a
                              0x1D47, // b
                              0x1D9C, // c
                              0x1D48, // d
                              0x1D49, // e
                              0x1DA0, // f
                              0x1D4D, // g
                              0x02B0, // h
                              0x2071, // i
                              0x02B2, // j
                              0x1D4F, // k
                              0x02E1, // l
                              0x1D50, // m
                              0x207F, // n
                              0x1D52, // o
                              0x1D56, // p
                              0x06F9, // q
                              0x02B3, // r
                              0x02E2, // s
                              0x1D57, // t
                              0x1D58, // u
                              0x1D5B, // v
                              0x02B7, // w
                              0x02E3, // x
                              0x02B8, // y
                              0x1DBB, // z
                              0x00B9, // 1
                              0x00B2, // 2
                              0x00B3, // 3
                              0x2074, // 4
                              0x2075, // 5
                              0x2076, // 6
                              0x2077, // 7
                              0x2078, // 8
                              0x2079, // 9
                              0x2070  // 0
);

DEFINE_UNICODE_LUT_TRANSLATOR(unicode_lut_translator_comic,
                              0x212B, // a
                              0x212C, // b
                              0x2102, // c
                              0x2145, // d
                              0x2107, // e
                              0x2132, // f
                              0x2141, // g
                              0x210D, // h
                              0x2148, // i
                              0x2111, // j
                              'k', // k
                              0x2143, // l
                              'm', // m
                              0x2115, // n
                              0x2134, // o
                              0x2119, // p
                              0x211A, // q
                              0x211B, // r
                              0x20B7, // s
                              0x20B8, // t
                              0x2127, // u
                              'v', // v
                              0x20A9, // w
                              'x', // x
                              0x213D, // y
                              'z', // z
                              '1', // 1
                              '2', // 2
                              '3', // 3
                              '4', // 4
                              '5', // 5
                              '6', // 6
                              '7', // 7
                              '8', // 8
                              '9', // 9
                              '0'  // 0
);

bool process_record_aussie(uint16_t keycode, keyrecord_t *record) {
    bool is_shifted = (get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT;
    if ((KC_A <= keycode) && (keycode <= KC_0)) {
        if (record->event.pressed) {
            if (!process_record_glyph_replacement(keycode, record, unicode_lut_translator_aussie)) {
                tap_code16_nomods(KC_LEFT);
                return false;
            }
        }
    } else if (record->event.pressed && keycode == KC_SPACE) {
        tap_code16_nomods(KC_SPACE);
        tap_code16_nomods(KC_LEFT);
        return false;
    } else if (record->event.pressed && keycode == KC_ENTER) {
        tap_code16_nomods(KC_END);
        tap_code16_nomods(KC_ENTER);
        return false;
    } else if (record->event.pressed && keycode == KC_HOME) {
        tap_code16_nomods(KC_END);
        return false;
    } else if (record->event.pressed && keycode == KC_END) {
        tap_code16_nomods(KC_HOME);
        return false;
    } else if (record->event.pressed && keycode == KC_BSPC) {
        tap_code16_nomods(KC_DEL);
        return false;
    } else if (record->event.pressed && keycode == KC_DEL) {
        tap_code16_nomods(KC_BSPC);
        return false;
    } else if (record->event.pressed && keycode == KC_QUOT) {
        tap_unicode_glyph_nomods(is_shifted ? 0x201E : 0x201A);
        tap_code16_nomods(KC_LEFT);
        return false;
    } else if (record->event.pressed && keycode == KC_COMMA) {
        tap_unicode_glyph_nomods(is_shifted ? '<' : 0x2018);
        tap_code16_nomods(KC_LEFT);
        return false;
    } else if (record->event.pressed && keycode == KC_DOT) {
        tap_unicode_glyph_nomods(is_shifted ? '>' : 0x02D9);
        tap_code16_nomods(KC_LEFT);
        return false;
    } else if (record->event.pressed && keycode == KC_SLASH) {
        tap_unicode_glyph_nomods(is_shifted ? 0x00BF : '/');
        tap_code16_nomods(KC_LEFT);
        return false;
    }
    return true;
}

bool process_record_zalgo(uint16_t keycode, keyrecord_t *record) {
    if ((KC_A <= keycode) && (keycode <= KC_0)) {
        if (record->event.pressed) {
            tap_code16_nomods(keycode);

            int number = (rand() % (8 + 1 - 2)) + 2;
            for (int index = 0; index < number; index++) {
                uint16_t hex = (rand() % (0x036F + 1 - 0x0300)) + 0x0300;
                register_unicode(hex);
            }

            return false;
        }
    }
    return true;
}

/**
 * @brief Main handler for unicode input
 *
 * @param keycode Keycode from switch matrix
 * @param record keyrecord_t data struture
 * @return true Send keycode from matrix to host
 * @return false Stop processing and do not send to host
 */

bool process_record_unicode(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case UC_FLIP: // (ノಠ痊ಠ)ノ彡┻━┻
            if (record->event.pressed) {
                send_unicode_string("(ノಠ痊ಠ)ノ彡┻━┻");
            }
            break;

        case UC_TABL: // ┬─┬ノ( º _ ºノ)
            if (record->event.pressed) {
                send_unicode_string("┬─┬ノ( º _ ºノ)");
            }
            break;

        case UC_SHRG: // ¯\_(ツ)_/¯
            if (record->event.pressed) {
                send_unicode_string("¯\\_(ツ)_/¯");
            }
            break;

        case UC_DISA: // ಠ_ಠ
            if (record->event.pressed) {
                send_unicode_string("ಠ_ಠ");
            }
            break;

        case UC_IRNY: // ⸮
            if (record->event.pressed) {
                register_unicode(0x2E2E);
            }
            break;
        case UC_CLUE: // ‽
            if (record->event.pressed) {
                register_unicode(0x203D);
            }
            break;
        case KC_NOMODE ... KC_COMIC:
            if (record->event.pressed) {
                if (unicode_typing_mode != keycode - KC_NOMODE) {
                    unicode_typing_mode = keycode - KC_NOMODE;
                } else {
                    unicode_typing_mode = UCTM_NO_MODE;
                }
            }
            break;
    }

    if (((get_mods() | get_oneshot_mods()) & ~MOD_MASK_SHIFT) != 0) {
        return true;
    }

    if (IS_QK_MOD_TAP(keycode) && record->tap.count) {
        keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
    }
    if (IS_QK_LAYER_TAP(keycode) && record->tap.count) {
        keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
    }

    if (unicode_typing_mode == UCTM_WIDE) {
        if (((KC_A <= keycode) && (keycode <= KC_0)) || keycode == KC_SPACE) {
            return process_record_glyph_replacement(keycode, record, unicode_range_translator_wide);
        }
    } else if (unicode_typing_mode == UCTM_SCRIPT) {
        if (((KC_A <= keycode) && (keycode <= KC_0)) || keycode == KC_SPACE) {
            return process_record_glyph_replacement(keycode, record, unicode_range_translator_script);
        }
    } else if (unicode_typing_mode == UCTM_BLOCKS) {
        if (((KC_A <= keycode) && (keycode <= KC_0)) || keycode == KC_SPACE) {
            return process_record_glyph_replacement(keycode, record, unicode_range_translator_boxes);
        }
    } else if (unicode_typing_mode == UCTM_REGIONAL) {
        if (((KC_A <= keycode) && (keycode <= KC_0)) || keycode == KC_SPACE) {
            if (!process_record_glyph_replacement(keycode, record, unicode_range_translator_regional)) {
                wait_us(500);
                tap_unicode_glyph_nomods(0x200C);
                return false;
            }
        }
    } else if (unicode_typing_mode == UCTM_SUPER) {
        if (((KC_A <= keycode) && (keycode <= KC_0))) {
            return process_record_glyph_replacement(keycode, record, unicode_lut_translator_super);
        }
    } else if (unicode_typing_mode == UCTM_COMIC) {
        if (((KC_A <= keycode) && (keycode <= KC_0))) {
            return process_record_glyph_replacement(keycode, record, unicode_lut_translator_comic);
        }
    } else if (unicode_typing_mode == UCTM_AUSSIE) {
        return process_record_aussie(keycode, record);
    } else if (unicode_typing_mode == UCTM_ZALGO) {
        return process_record_zalgo(keycode, record);
    }
    return true;
}

/**
 * @brief Initialize the default unicode mode on firmware startup
 *
 */
void keyboard_post_init_unicode(void) {
    unicode_input_mode_init();
}
