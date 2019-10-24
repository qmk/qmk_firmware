
#pragma once

#include <stdint.h>

typedef struct {
    uint8_t byte[6];
} bmp_ex_keycode_t;

typedef enum {
    NO_EXKC = 0,
    LTE,
    TLT,
    TDD,
    TDH,
    EXKC_TYPE_END,
} exkc_type_t;

#define LTE(layer, qkc) \
    (bmp_ex_keycode_t) { .byte[0] = LTE, .byte[1] = layer, .byte[2] = qkc & 0xFF, .byte[3] = (qkc >> 8) & 0xFF, .byte[4] = 0, .byte[5] = 0 }
static inline uint8_t  lte_get_layer(bmp_ex_keycode_t const* const exkc) { return exkc->byte[1]; }
static inline uint16_t lte_get_tapcode(bmp_ex_keycode_t const* const exkc) { return exkc->byte[2] | (((uint16_t)exkc->byte[3]) << 8); }

#define TLT(layer1, layer2, layer3, qkc) \
    (bmp_ex_keycode_t) { .byte[0] = TLT, .byte[1] = layer1, .byte[2] = layer2, .byte[3] = layer3, .byte[4] = qkc & 0xFF, .byte[5] = (qkc >> 8) & 0xFF }
static inline uint8_t  tlt_get_layer1(bmp_ex_keycode_t const* const exkc) { return exkc->byte[1]; }
static inline uint8_t  tlt_get_layer2(bmp_ex_keycode_t const* const exkc) { return exkc->byte[2]; }
static inline uint8_t  tlt_get_layer3(bmp_ex_keycode_t const* const exkc) { return exkc->byte[3]; }
static inline uint16_t tlt_get_tapcode(bmp_ex_keycode_t const* const exkc) { return exkc->byte[4] | (((uint16_t)exkc->byte[5]) << 8); }

#define TDD(qkc1, qkc2) \
    (bmp_ex_keycode_t) { .byte[0] = TDD, .byte[1] = qkc1 & 0xFF, .byte[2] = (qkc1 >> 8) & 0xFF, .byte[3] = qkc2 & 0xFF, .byte[4] = (qkc2 >> 8) & 0xFF, .byte[5] = 0 }

static inline uint16_t tdd_get_kc1(bmp_ex_keycode_t const * const exkc) { return exkc->byte[1] | (((uint16_t)exkc->byte[2]) << 8); }
static inline uint16_t tdd_get_kc2(bmp_ex_keycode_t const * const exkc) { return exkc->byte[3] | (((uint16_t)exkc->byte[4]) << 8); }

#define TDH(qkc1, qkc2) \
    (bmp_ex_keycode_t) { .byte[0] = TDH, .byte[1] = qkc1 & 0xFF, .byte[2] = (qkc1 >> 8) & 0xFF, .byte[3] = qkc2 & 0xFF, .byte[4] = (qkc2 >> 8) & 0xFF, .byte[5] = 0 }

static inline uint16_t tdh_get_kc1(bmp_ex_keycode_t const * const exkc) { return exkc->byte[1] | (((uint16_t)exkc->byte[2]) << 8); }
static inline uint16_t tdh_get_kc2(bmp_ex_keycode_t const * const exkc) { return exkc->byte[3] | (((uint16_t)exkc->byte[4]) << 8); }

#define EX(x) x

static inline exkc_type_t get_exkc_type(bmp_ex_keycode_t const* const ek) {
    uint8_t type = ek->byte[0];

    return (type < EXKC_TYPE_END) ? (exkc_type_t)type : NO_EXKC;
}
