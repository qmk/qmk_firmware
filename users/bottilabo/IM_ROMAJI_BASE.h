#pragma once

// IM_ROMAJI_BASE

typedef struct {
    uint16_t code;
    char c;
} ROMAJI_BASE_CODE_CHAR_t;

typedef struct {
    uint16_t code;
    char ch2[2];
} ROMAJI_BASE_CC_t;

typedef struct {
    uint16_t keycode;
    uint16_t bit;
} ROMAJI_BASE_KEYCODE_BIT_t;

enum {
    ROMAJI_BASE_LSHIFT = 1U << 14,
    ROMAJI_BASE_RSHIFT = 1U << 15
};

#define ROMAJI_BASE_SPC ROMAJI_BASE_RSHIFT

#ifndef ROMAJI_BASE_TERM
#define ROMAJI_BASE_TERM STKIN_TERM
#endif
