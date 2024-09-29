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
enum { ENABLED_LED_MATRIX_EFFECTS = 0
    | (1ULL << 0x00)

#ifdef ENABLE_LED_MATRIX_ALPHAS_MODS
    | (1ULL << 0x01)
#endif

#ifdef ENABLE_LED_MATRIX_BREATHING
    | (1ULL << 0x02)
#endif

#ifdef ENABLE_LED_MATRIX_BAND
    | (1ULL << 0x03)
#endif

#ifdef ENABLE_LED_MATRIX_BAND_PINWHEEL
    | (1ULL << 0x04)
#endif

#ifdef ENABLE_LED_MATRIX_BAND_SPIRAL
    | (1ULL << 0x05)
#endif

#ifdef ENABLE_LED_MATRIX_CYCLE_LEFT_RIGHT
    | (1ULL << 0x06)
#endif

#ifdef ENABLE_LED_MATRIX_CYCLE_UP_DOWN
    | (1ULL << 0x07)
#endif

#ifdef ENABLE_LED_MATRIX_CYCLE_OUT_IN
    | (1ULL << 0x08)
#endif

#ifdef ENABLE_LED_MATRIX_DUAL_BEACON
    | (1ULL << 0x09)
#endif

#ifdef ENABLE_LED_MATRIX_WAVE_LEFT_RIGHT
    | (1ULL << 0x0A)
#endif

#ifdef ENABLE_LED_MATRIX_WAVE_UP_DOWN
    | (1ULL << 0x0B)
#endif

#ifdef LED_MATRIX_KEYREACTIVE_ENABLED

#ifdef ENABLE_LED_MATRIX_SOLID_REACTIVE_SIMPLE
    | (1ULL << 0x0C)
#endif
#endif

#ifdef LED_MATRIX_KEYREACTIVE_ENABLED

#ifdef ENABLE_LED_MATRIX_SOLID_REACTIVE_WIDE
    | (1ULL << 0x0D)
#endif
#endif

#ifdef LED_MATRIX_KEYREACTIVE_ENABLED

#ifdef ENABLE_LED_MATRIX_SOLID_REACTIVE_MULTIWIDE
    | (1ULL << 0x0E)
#endif
#endif

#ifdef LED_MATRIX_KEYREACTIVE_ENABLED

#ifdef ENABLE_LED_MATRIX_SOLID_REACTIVE_CROSS
    | (1ULL << 0x0F)
#endif
#endif

#ifdef LED_MATRIX_KEYREACTIVE_ENABLED

#ifdef ENABLE_LED_MATRIX_SOLID_REACTIVE_MULTICROSS
    | (1ULL << 0x10)
#endif
#endif

#ifdef LED_MATRIX_KEYREACTIVE_ENABLED

#ifdef ENABLE_LED_MATRIX_SOLID_REACTIVE_NEXUS
    | (1ULL << 0x11)
#endif
#endif

#ifdef LED_MATRIX_KEYREACTIVE_ENABLED

#ifdef ENABLE_LED_MATRIX_SOLID_REACTIVE_MULTINEXUS
    | (1ULL << 0x12)
#endif
#endif

#ifdef LED_MATRIX_KEYREACTIVE_ENABLED

#ifdef ENABLE_LED_MATRIX_SOLID_SPLASH
    | (1ULL << 0x13)
#endif
#endif

#ifdef LED_MATRIX_KEYREACTIVE_ENABLED

#ifdef ENABLE_LED_MATRIX_SOLID_MULTISPLASH
    | (1ULL << 0x14)
#endif
#endif
};
static const uint8_t led_matrix_effect_map[][2] PROGMEM = {
{ 0x00, LED_MATRIX_SOLID},

#ifdef ENABLE_LED_MATRIX_ALPHAS_MODS
{ 0x01, LED_MATRIX_ALPHAS_MODS},
#endif

#ifdef ENABLE_LED_MATRIX_BREATHING
{ 0x02, LED_MATRIX_BREATHING},
#endif

#ifdef ENABLE_LED_MATRIX_BAND
{ 0x03, LED_MATRIX_BAND},
#endif

#ifdef ENABLE_LED_MATRIX_BAND_PINWHEEL
{ 0x04, LED_MATRIX_BAND_PINWHEEL},
#endif

#ifdef ENABLE_LED_MATRIX_BAND_SPIRAL
{ 0x05, LED_MATRIX_BAND_SPIRAL},
#endif

#ifdef ENABLE_LED_MATRIX_CYCLE_LEFT_RIGHT
{ 0x06, LED_MATRIX_CYCLE_LEFT_RIGHT},
#endif

#ifdef ENABLE_LED_MATRIX_CYCLE_UP_DOWN
{ 0x07, LED_MATRIX_CYCLE_UP_DOWN},
#endif

#ifdef ENABLE_LED_MATRIX_CYCLE_OUT_IN
{ 0x08, LED_MATRIX_CYCLE_OUT_IN},
#endif

#ifdef ENABLE_LED_MATRIX_DUAL_BEACON
{ 0x09, LED_MATRIX_DUAL_BEACON},
#endif

#ifdef ENABLE_LED_MATRIX_WAVE_LEFT_RIGHT
{ 0x0A, LED_MATRIX_WAVE_LEFT_RIGHT},
#endif

#ifdef ENABLE_LED_MATRIX_WAVE_UP_DOWN
{ 0x0B, LED_MATRIX_WAVE_UP_DOWN},
#endif

#ifdef LED_MATRIX_KEYREACTIVE_ENABLED

#ifdef ENABLE_LED_MATRIX_SOLID_REACTIVE_SIMPLE
{ 0x0C, LED_MATRIX_SOLID_REACTIVE_SIMPLE},
#endif
#endif

#ifdef LED_MATRIX_KEYREACTIVE_ENABLED

#ifdef ENABLE_LED_MATRIX_SOLID_REACTIVE_WIDE
{ 0x0D, LED_MATRIX_SOLID_REACTIVE_WIDE},
#endif
#endif

#ifdef LED_MATRIX_KEYREACTIVE_ENABLED

#ifdef ENABLE_LED_MATRIX_SOLID_REACTIVE_MULTIWIDE
{ 0x0E, LED_MATRIX_SOLID_REACTIVE_MULTIWIDE},
#endif
#endif

#ifdef LED_MATRIX_KEYREACTIVE_ENABLED

#ifdef ENABLE_LED_MATRIX_SOLID_REACTIVE_CROSS
{ 0x0F, LED_MATRIX_SOLID_REACTIVE_CROSS},
#endif
#endif

#ifdef LED_MATRIX_KEYREACTIVE_ENABLED

#ifdef ENABLE_LED_MATRIX_SOLID_REACTIVE_MULTICROSS
{ 0x10, LED_MATRIX_SOLID_REACTIVE_MULTICROSS},
#endif
#endif

#ifdef LED_MATRIX_KEYREACTIVE_ENABLED

#ifdef ENABLE_LED_MATRIX_SOLID_REACTIVE_NEXUS
{ 0x11, LED_MATRIX_SOLID_REACTIVE_NEXUS},
#endif
#endif

#ifdef LED_MATRIX_KEYREACTIVE_ENABLED

#ifdef ENABLE_LED_MATRIX_SOLID_REACTIVE_MULTINEXUS
{ 0x12, LED_MATRIX_SOLID_REACTIVE_MULTINEXUS},
#endif
#endif

#ifdef LED_MATRIX_KEYREACTIVE_ENABLED

#ifdef ENABLE_LED_MATRIX_SOLID_SPLASH
{ 0x13, LED_MATRIX_SOLID_SPLASH},
#endif
#endif

#ifdef LED_MATRIX_KEYREACTIVE_ENABLED

#ifdef ENABLE_LED_MATRIX_SOLID_MULTISPLASH
{ 0x14, LED_MATRIX_SOLID_MULTISPLASH},
#endif
#endif
};

uint8_t led_matrix_effect_to_id(uint8_t val) {
    for(uint8_t i = 0; i < ARRAY_SIZE(led_matrix_effect_map); i++) {
        if (pgm_read_byte(&led_matrix_effect_map[i][1]) == val)
            return pgm_read_byte(&led_matrix_effect_map[i][0]);
    }
    return 0xFF;
}

uint8_t led_matrix_id_to_effect(uint8_t val) {
    for(uint8_t i = 0; i < ARRAY_SIZE(led_matrix_effect_map); i++) {
        if (pgm_read_byte(&led_matrix_effect_map[i][0]) == val)
            return pgm_read_byte(&led_matrix_effect_map[i][1]);
    }
    return 0xFF;
}
