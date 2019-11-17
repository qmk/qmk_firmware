
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "bmp_extended_keycode_converter.h"
#include "bmp_custom_keycode.h"

#define PREFIX_PAIR(prefix) [prefix] = #prefix
static const char* prefix_str[] = {
    [NO_EXKC] = "",
    PREFIX_PAIR(LTE),
    PREFIX_PAIR(TLT),
    PREFIX_PAIR(TDD),
    PREFIX_PAIR(TDH),
};

#define ARRAY_LEN(x) sizeof(x) / sizeof(x[0])
static exkc_type_t get_exkc_type(bmp_ex_keycode_t const* const ek);
static int         ekc_lte_to_str(bmp_ex_keycode_t const* const ek, char* str, uint16_t len, KEYMAP_LOCALE locale, bool use_ascii);
static int         ekc_tlt_to_str(bmp_ex_keycode_t const* const ek, char* str, uint16_t len, KEYMAP_LOCALE locale, bool use_ascii);
static int         ekc_tdd_to_str(bmp_ex_keycode_t const* const ek, char* str, uint16_t len, KEYMAP_LOCALE locale, bool use_ascii);
static int         ekc_tdh_to_str(bmp_ex_keycode_t const* const ek, char* str, uint16_t len, KEYMAP_LOCALE locale, bool use_ascii);

static exkc_type_t get_str_exkc_type(const char* str, uint16_t len);
static int         str2ekc_lte(bmp_ex_keycode_t* const ek_res, const char* str, uint16_t len, KEYMAP_LOCALE locale);
static int         str2ekc_tlt(bmp_ex_keycode_t* const ek_res, const char* str, uint16_t len, KEYMAP_LOCALE locale);
static int         str2ekc_tdd(bmp_ex_keycode_t* const ek_res, const char* str, uint16_t len, KEYMAP_LOCALE locale);
static int         str2ekc_tdh(bmp_ex_keycode_t* const ek_res, const char* str, uint16_t len, KEYMAP_LOCALE locale);

uint8_t bmp_ex_keycode2str_locale(bmp_ex_keycode_t const* const ek, char* str, uint16_t len, KEYMAP_LOCALE locale, bool use_ascii) {
    exkc_type_t ek_type     = get_exkc_type(ek);
    uint32_t    written_len = 0;

    switch (ek_type) {
        case LTE:
            written_len = ekc_lte_to_str(ek, str, len, locale, use_ascii);
            break;
        case TLT:
            written_len = ekc_tlt_to_str(ek, str, len, locale, use_ascii);
            break;
        case TDD:
            written_len = ekc_tdd_to_str(ek, str, len, locale, use_ascii);
            break;
        case TDH:
            written_len = ekc_tdh_to_str(ek, str, len, locale, use_ascii);
            break;
        default:
            break;
    }

    return written_len;
}

uint8_t str2bmp_ex_keycode_locale(bmp_ex_keycode_t* ek_res, const char* str, uint32_t len, KEYMAP_LOCALE locale) {
    // Delete ANY() if contained
    if (str[0] == 'A' && str[1] == 'N' && str[2] == 'Y') {
        len = get_inner_element(&str, len);
    }

    // Delete EX()
    len = get_inner_element(&str, len);

    // Delete PREFIX()
    exkc_type_t ek_type = get_str_exkc_type(str, len);
    len                 = get_inner_element(&str, len);

    switch (ek_type) {
        case LTE:
            str2ekc_lte(ek_res, str, len, locale);
            break;
        case TLT:
            str2ekc_tlt(ek_res, str, len, locale);
            break;
        case TDD:
            str2ekc_tdd(ek_res, str, len, locale);
            break;
        case TDH:
            str2ekc_tdh(ek_res, str, len, locale);
            break;
        default:
            ek_res->byte[0] = NO_EXKC;
            break;
    }

    return 0;
}

static int ekc_lte_to_str(bmp_ex_keycode_t const* const ek, char* str, uint16_t len, KEYMAP_LOCALE locale, bool use_ascii) {
    uint8_t  layer = lte_get_layer(ek);
    uint16_t qkc   = lte_get_tapcode(ek);

    uint32_t write_offset = snprintf(str, len, "EX(LTE(%d,", layer);

    write_offset += quantum_keycode2str_locale(qkc, str + write_offset, len - write_offset, locale, false); // always use no_ascii mode

    write_offset += snprintf(str + write_offset, len - write_offset, "))");

    return write_offset;
}

static int ekc_tlt_to_str(bmp_ex_keycode_t const* const ek, char* str, uint16_t len, KEYMAP_LOCALE locale, bool use_ascii) {
    uint8_t  layer1 = tlt_get_layer1(ek);
    uint8_t  layer2 = tlt_get_layer2(ek);
    uint8_t  layer3 = tlt_get_layer3(ek);
    uint16_t qkc    = tlt_get_tapcode(ek);

    uint32_t write_offset = snprintf(str, len, "EX(TLT(%d,%d,%d,", layer1, layer2, layer3);

    write_offset += quantum_keycode2str_locale(qkc, str + write_offset, len - write_offset, locale, false); // always use no_ascii mode

    write_offset += snprintf(str + write_offset, len - write_offset, "))");

    return write_offset;
}

static int ekc_tdd_to_str(bmp_ex_keycode_t const* const ek, char* str, uint16_t len, KEYMAP_LOCALE locale, bool use_ascii) {
    uint16_t qkc1 = ((uint16_t)ek->byte[2] << 8) | ek->byte[1];
    uint16_t qkc2 = ((uint16_t)ek->byte[4] << 8) | ek->byte[3];

    uint32_t write_offset = snprintf(str, len, "EX(TDD(");

    write_offset += quantum_keycode2str_locale(qkc1, str + write_offset, len - write_offset, locale, false); // always use no_ascii mode

    write_offset += snprintf(str + write_offset, len - write_offset, ",");

    write_offset += quantum_keycode2str_locale(qkc2, str + write_offset, len - write_offset, locale, false); // always use no_ascii mode

    write_offset += snprintf(str + write_offset, len - write_offset, "))");

    return write_offset;
}

static int ekc_tdh_to_str(bmp_ex_keycode_t const* const ek, char* str, uint16_t len, KEYMAP_LOCALE locale, bool use_ascii) {
    uint16_t qkc1 = ((uint16_t)ek->byte[2] << 8) | ek->byte[1];
    uint16_t qkc2 = ((uint16_t)ek->byte[4] << 8) | ek->byte[3];

    uint32_t write_offset = snprintf(str, len, "EX(TDH(");

    write_offset += quantum_keycode2str_locale(qkc1, str + write_offset, len - write_offset, locale, false); // always use no_ascii mode

    write_offset += snprintf(str + write_offset, len - write_offset, ",");

    write_offset += quantum_keycode2str_locale(qkc2, str + write_offset, len - write_offset, locale, false); // always use no_ascii mode

    write_offset += snprintf(str + write_offset, len - write_offset, "))");

    return write_offset;
}

bool               check_prefix(const char* str, const char* prefix);
static exkc_type_t get_str_exkc_type(const char* str, uint16_t len) {
    int prefix_idx = 1;  // skip 0:NO_EXKC
    for (prefix_idx = 1; prefix_idx < ARRAY_LEN(prefix_str); prefix_idx++) {
        if (check_prefix(str, prefix_str[prefix_idx])) {
            break;
        }
    }

    return prefix_idx < ARRAY_LEN(prefix_str) ? (exkc_type_t)prefix_idx : NO_EXKC;
}

static inline void skip_space(const char** str, uint16_t* len) {
    while (**str == ' ') {
        (*str)++;
        (*len)--;
    }
}

static inline void move_to_next_separetor(const char** str) {
    do {
        if (**str == '\\') {
            *str = *str + 1;
        }
        *str = *str + 1;
    } while (**str != ',');
    *str = *str + 1;
}

// convert string to qkc
// @param len length of qkc string or 0 (string len will be deterined in func)
static uint16_t get_qkc_from_str(const char* str, uint16_t len, KEYMAP_LOCALE locale) {
    char kc_str[32];

    if (len == 0) {
        len = get_kc_strlen(str, strlen(str));
    }

    if (len > sizeof(kc_str)) {
        len = sizeof(kc_str);
    }

    memcpy(kc_str, str, len);
    kc_str[len] = '\0';

    return str2quantum_keycode_locale(kc_str, len, locale);
}

static int str2ekc_lte(bmp_ex_keycode_t* const ek_res, const char* str, uint16_t len, KEYMAP_LOCALE locale) {
    uint8_t layer = atoi(str);
    move_to_next_separetor(&str);
    skip_space(&str, &len);

    uint16_t kc = get_qkc_from_str(str, 0, locale);

    *ek_res = LTE(layer, kc);

    return 0;
}

static int str2ekc_tlt(bmp_ex_keycode_t* const ek_res, const char* str, uint16_t len, KEYMAP_LOCALE locale) {
    uint8_t layers[3];
    for (int i = 0; i < ARRAY_LEN(layers); i++) {
        layers[i] = atoi(str);
        move_to_next_separetor(&str);
        skip_space(&str, &len);
    }

    uint16_t kc = get_qkc_from_str(str, 0, locale);

    *ek_res = TLT(layers[0], layers[1], layers[2], kc);

    return 0;
}

static int str2ekc_tdd(bmp_ex_keycode_t* const ek_res, const char* str, uint16_t len, KEYMAP_LOCALE locale) {
    const char* kc_str[2];
    uint16_t    kc_str_len[2];

    get_element_array(str, len, kc_str, kc_str_len, 2);

    skip_space(&kc_str[0], &len);
    uint16_t kc1 = get_qkc_from_str(kc_str[0], kc_str_len[0], locale);

    skip_space(&kc_str[1], &len);
    uint16_t kc2 = get_qkc_from_str(kc_str[1], kc_str_len[1], locale);

    *ek_res = TDD(kc1, kc2);

    return 0;
}

static int str2ekc_tdh(bmp_ex_keycode_t* const ek_res, const char* str, uint16_t len, KEYMAP_LOCALE locale) {
    const char* kc_str[2];
    uint16_t    kc_str_len[2];

    get_element_array(str, len, kc_str, kc_str_len, 2);

    skip_space(&kc_str[0], &len);
    uint16_t kc1 = get_qkc_from_str(kc_str[0], kc_str_len[0], locale);

    skip_space(&kc_str[1], &len);
    uint16_t kc2 = get_qkc_from_str(kc_str[1], kc_str_len[1], locale);

    *ek_res = TDH(kc1, kc2);

    return 0;
}
