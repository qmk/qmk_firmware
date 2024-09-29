// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

/*******************************************************************************
  88888888888 888      d8b                .d888 d8b 888               d8b
      888     888      Y8P               d88P"  Y8P 888               Y8P
      888     888                        888        888
      888     88888b.  888 .d8888b       888888 888 888  .d88b.       888 .d8888b
      888     888 "88b 888 88K           888    888 888 d8P  Y8b      888 88K
      888     888  888 888 "Y8888b.      888    888 888 88888888      888 "Y8888b.
      888     888  888 888      X88      888    888 888 Y8b.          888      X88
      888     888  888 888  88888P'      888    888 888  "Y8888       888  88888P'
                                                        888                 888
                                                        888                 888
                                                        888                 888
     .d88b.   .d88b.  88888b.   .d88b.  888d888 8888b.  888888 .d88b.   .d88888
    d88P"88b d8P  Y8b 888 "88b d8P  Y8b 888P"      "88b 888   d8P  Y8b d88" 888
    888  888 88888888 888  888 88888888 888    .d888888 888   88888888 888  888
    Y88b 888 Y8b.     888  888 Y8b.     888    888  888 Y88b. Y8b.     Y88b 888
     "Y88888  "Y8888  888  888  "Y8888  888    "Y888888  "Y888 "Y8888   "Y88888
         888
    Y8b d88P
     "Y88P"
*******************************************************************************/

#pragma once
// clang-format off
enum { ENABLED_RGBLIGHT_EFFECTS = 0
    | (1ULL << 0x00)

#ifdef RGBLIGHT_EFFECT_BREATHING
    | (1ULL << 0x01)
#endif

#ifdef RGBLIGHT_EFFECT_BREATHING
    | (1ULL << 0x02)
#endif

#ifdef RGBLIGHT_EFFECT_BREATHING
    | (1ULL << 0x03)
#endif

#ifdef RGBLIGHT_EFFECT_BREATHING
    | (1ULL << 0x04)
#endif

#ifdef RGBLIGHT_EFFECT_RAINBOW_MOOD
    | (1ULL << 0x05)
#endif

#ifdef RGBLIGHT_EFFECT_RAINBOW_MOOD
    | (1ULL << 0x06)
#endif

#ifdef RGBLIGHT_EFFECT_RAINBOW_MOOD
    | (1ULL << 0x07)
#endif

#ifdef RGBLIGHT_EFFECT_RAINBOW_SWIRL
    | (1ULL << 0x08)
#endif

#ifdef RGBLIGHT_EFFECT_RAINBOW_SWIRL
    | (1ULL << 0x09)
#endif

#ifdef RGBLIGHT_EFFECT_RAINBOW_SWIRL
    | (1ULL << 0x0A)
#endif

#ifdef RGBLIGHT_EFFECT_RAINBOW_SWIRL
    | (1ULL << 0x0B)
#endif

#ifdef RGBLIGHT_EFFECT_RAINBOW_SWIRL
    | (1ULL << 0x0C)
#endif

#ifdef RGBLIGHT_EFFECT_RAINBOW_SWIRL
    | (1ULL << 0x0D)
#endif

#ifdef RGBLIGHT_EFFECT_SNAKE
    | (1ULL << 0x0E)
#endif

#ifdef RGBLIGHT_EFFECT_SNAKE
    | (1ULL << 0x0F)
#endif

#ifdef RGBLIGHT_EFFECT_SNAKE
    | (1ULL << 0x10)
#endif

#ifdef RGBLIGHT_EFFECT_SNAKE
    | (1ULL << 0x11)
#endif

#ifdef RGBLIGHT_EFFECT_SNAKE
    | (1ULL << 0x12)
#endif

#ifdef RGBLIGHT_EFFECT_SNAKE
    | (1ULL << 0x13)
#endif

#ifdef RGBLIGHT_EFFECT_KNIGHT
    | (1ULL << 0x14)
#endif

#ifdef RGBLIGHT_EFFECT_KNIGHT
    | (1ULL << 0x15)
#endif

#ifdef RGBLIGHT_EFFECT_KNIGHT
    | (1ULL << 0x16)
#endif

#ifdef RGBLIGHT_EFFECT_CHRISTMAS
    | (1ULL << 0x17)
#endif

#ifdef RGBLIGHT_EFFECT_STATIC_GRADIENT
    | (1ULL << 0x18)
#endif

#ifdef RGBLIGHT_EFFECT_STATIC_GRADIENT
    | (1ULL << 0x19)
#endif

#ifdef RGBLIGHT_EFFECT_STATIC_GRADIENT
    | (1ULL << 0x1A)
#endif

#ifdef RGBLIGHT_EFFECT_STATIC_GRADIENT
    | (1ULL << 0x1B)
#endif

#ifdef RGBLIGHT_EFFECT_STATIC_GRADIENT
    | (1ULL << 0x1C)
#endif

#ifdef RGBLIGHT_EFFECT_STATIC_GRADIENT
    | (1ULL << 0x1D)
#endif

#ifdef RGBLIGHT_EFFECT_STATIC_GRADIENT
    | (1ULL << 0x1E)
#endif

#ifdef RGBLIGHT_EFFECT_STATIC_GRADIENT
    | (1ULL << 0x1F)
#endif

#ifdef RGBLIGHT_EFFECT_STATIC_GRADIENT
    | (1ULL << 0x20)
#endif

#ifdef RGBLIGHT_EFFECT_STATIC_GRADIENT
    | (1ULL << 0x21)
#endif

#ifdef RGBLIGHT_EFFECT_RGB_TEST
    | (1ULL << 0x22)
#endif

#ifdef RGBLIGHT_EFFECT_ALTERNATING
    | (1ULL << 0x23)
#endif

#ifdef RGBLIGHT_EFFECT_TWINKLE
    | (1ULL << 0x24)
#endif

#ifdef RGBLIGHT_EFFECT_TWINKLE
    | (1ULL << 0x25)
#endif

#ifdef RGBLIGHT_EFFECT_TWINKLE
    | (1ULL << 0x26)
#endif

#ifdef RGBLIGHT_EFFECT_TWINKLE
    | (1ULL << 0x27)
#endif

#ifdef RGBLIGHT_EFFECT_TWINKLE
    | (1ULL << 0x28)
#endif

#ifdef RGBLIGHT_EFFECT_TWINKLE
    | (1ULL << 0x29)
#endif
};
static const uint8_t rgblight_effect_map[][2] PROGMEM = {
{ 0x00, RGBLIGHT_MODE_STATIC_LIGHT},

#ifdef RGBLIGHT_EFFECT_BREATHING
{ 0x01, RGBLIGHT_MODE_BREATHING},
#endif

#ifdef RGBLIGHT_EFFECT_BREATHING
{ 0x02, RGBLIGHT_MODE_BREATHING + 1},
#endif

#ifdef RGBLIGHT_EFFECT_BREATHING
{ 0x03, RGBLIGHT_MODE_BREATHING + 2},
#endif

#ifdef RGBLIGHT_EFFECT_BREATHING
{ 0x04, RGBLIGHT_MODE_BREATHING + 3},
#endif

#ifdef RGBLIGHT_EFFECT_RAINBOW_MOOD
{ 0x05, RGBLIGHT_MODE_RAINBOW_MOOD},
#endif

#ifdef RGBLIGHT_EFFECT_RAINBOW_MOOD
{ 0x06, RGBLIGHT_MODE_RAINBOW_MOOD + 1},
#endif

#ifdef RGBLIGHT_EFFECT_RAINBOW_MOOD
{ 0x07, RGBLIGHT_MODE_RAINBOW_MOOD + 2},
#endif

#ifdef RGBLIGHT_EFFECT_RAINBOW_SWIRL
{ 0x08, RGBLIGHT_MODE_RAINBOW_SWIRL},
#endif

#ifdef RGBLIGHT_EFFECT_RAINBOW_SWIRL
{ 0x09, RGBLIGHT_MODE_RAINBOW_SWIRL + 1},
#endif

#ifdef RGBLIGHT_EFFECT_RAINBOW_SWIRL
{ 0x0A, RGBLIGHT_MODE_RAINBOW_SWIRL + 2},
#endif

#ifdef RGBLIGHT_EFFECT_RAINBOW_SWIRL
{ 0x0B, RGBLIGHT_MODE_RAINBOW_SWIRL + 3},
#endif

#ifdef RGBLIGHT_EFFECT_RAINBOW_SWIRL
{ 0x0C, RGBLIGHT_MODE_RAINBOW_SWIRL + 4},
#endif

#ifdef RGBLIGHT_EFFECT_RAINBOW_SWIRL
{ 0x0D, RGBLIGHT_MODE_RAINBOW_SWIRL + 5},
#endif

#ifdef RGBLIGHT_EFFECT_SNAKE
{ 0x0E, RGBLIGHT_MODE_SNAKE},
#endif

#ifdef RGBLIGHT_EFFECT_SNAKE
{ 0x0F, RGBLIGHT_MODE_SNAKE + 1},
#endif

#ifdef RGBLIGHT_EFFECT_SNAKE
{ 0x10, RGBLIGHT_MODE_SNAKE + 2},
#endif

#ifdef RGBLIGHT_EFFECT_SNAKE
{ 0x11, RGBLIGHT_MODE_SNAKE + 3},
#endif

#ifdef RGBLIGHT_EFFECT_SNAKE
{ 0x12, RGBLIGHT_MODE_SNAKE + 4},
#endif

#ifdef RGBLIGHT_EFFECT_SNAKE
{ 0x13, RGBLIGHT_MODE_SNAKE + 5},
#endif

#ifdef RGBLIGHT_EFFECT_KNIGHT
{ 0x14, RGBLIGHT_MODE_KNIGHT},
#endif

#ifdef RGBLIGHT_EFFECT_KNIGHT
{ 0x15, RGBLIGHT_MODE_KNIGHT + 1},
#endif

#ifdef RGBLIGHT_EFFECT_KNIGHT
{ 0x16, RGBLIGHT_MODE_KNIGHT + 2},
#endif

#ifdef RGBLIGHT_EFFECT_CHRISTMAS
{ 0x17, RGBLIGHT_MODE_CHRISTMAS},
#endif

#ifdef RGBLIGHT_EFFECT_STATIC_GRADIENT
{ 0x18, RGBLIGHT_MODE_STATIC_GRADIENT},
#endif

#ifdef RGBLIGHT_EFFECT_STATIC_GRADIENT
{ 0x19, RGBLIGHT_MODE_STATIC_GRADIENT + 1},
#endif

#ifdef RGBLIGHT_EFFECT_STATIC_GRADIENT
{ 0x1A, RGBLIGHT_MODE_STATIC_GRADIENT + 2},
#endif

#ifdef RGBLIGHT_EFFECT_STATIC_GRADIENT
{ 0x1B, RGBLIGHT_MODE_STATIC_GRADIENT + 3},
#endif

#ifdef RGBLIGHT_EFFECT_STATIC_GRADIENT
{ 0x1C, RGBLIGHT_MODE_STATIC_GRADIENT + 4},
#endif

#ifdef RGBLIGHT_EFFECT_STATIC_GRADIENT
{ 0x1D, RGBLIGHT_MODE_STATIC_GRADIENT + 5},
#endif

#ifdef RGBLIGHT_EFFECT_STATIC_GRADIENT
{ 0x1E, RGBLIGHT_MODE_STATIC_GRADIENT + 6},
#endif

#ifdef RGBLIGHT_EFFECT_STATIC_GRADIENT
{ 0x1F, RGBLIGHT_MODE_STATIC_GRADIENT + 7},
#endif

#ifdef RGBLIGHT_EFFECT_STATIC_GRADIENT
{ 0x20, RGBLIGHT_MODE_STATIC_GRADIENT + 8},
#endif

#ifdef RGBLIGHT_EFFECT_STATIC_GRADIENT
{ 0x21, RGBLIGHT_MODE_STATIC_GRADIENT + 9},
#endif

#ifdef RGBLIGHT_EFFECT_RGB_TEST
{ 0x22, RGBLIGHT_MODE_RGB_TEST},
#endif

#ifdef RGBLIGHT_EFFECT_ALTERNATING
{ 0x23, RGBLIGHT_MODE_ALTERNATING},
#endif

#ifdef RGBLIGHT_EFFECT_TWINKLE
{ 0x24, RGBLIGHT_MODE_TWINKLE},
#endif

#ifdef RGBLIGHT_EFFECT_TWINKLE
{ 0x25, RGBLIGHT_MODE_TWINKLE + 1},
#endif

#ifdef RGBLIGHT_EFFECT_TWINKLE
{ 0x26, RGBLIGHT_MODE_TWINKLE + 2},
#endif

#ifdef RGBLIGHT_EFFECT_TWINKLE
{ 0x27, RGBLIGHT_MODE_TWINKLE + 3},
#endif

#ifdef RGBLIGHT_EFFECT_TWINKLE
{ 0x28, RGBLIGHT_MODE_TWINKLE + 4},
#endif

#ifdef RGBLIGHT_EFFECT_TWINKLE
{ 0x29, RGBLIGHT_MODE_TWINKLE + 5},
#endif
};

uint8_t rgblight_effect_to_id(uint8_t val) {
    for(uint8_t i = 0; i < ARRAY_SIZE(rgblight_effect_map); i++) {
        if (pgm_read_byte(&rgblight_effect_map[i][1]) == val)
            return pgm_read_byte(&rgblight_effect_map[i][0]);
    }
    return 0xFF;
}

uint8_t rgblight_id_to_effect(uint8_t val) {
    for(uint8_t i = 0; i < ARRAY_SIZE(rgblight_effect_map); i++) {
        if (pgm_read_byte(&rgblight_effect_map[i][0]) == val)
            return pgm_read_byte(&rgblight_effect_map[i][1]);
    }
    return 0xFF;
}
