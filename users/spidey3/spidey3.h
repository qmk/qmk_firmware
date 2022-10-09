// Copyright 2022 Joshua Diamond josh@windowoffire.com (@spidey3)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include QMK_KEYBOARD_H

#ifdef UNICODEMAP_ENABLE
#    include "unicode.h"
#endif

enum userspace_layers {
    _BASE = 0,
    _NUMPAD,
    _FN,
    _GLYPH,
};

enum custom_keycodes {
    CH_CPNL = SAFE_RANGE,  // AL Control Panel
    CH_ASST,               // AL Context-aware Desktop Assistant
    CH_SUSP,               // Suspend

    SPI_NORMAL,
    SPI_WIDE,
    SPI_SCRIPT,
    SPI_BLOCKS,
    SPI_CIRCLE,
    SPI_SQUARE,
    SPI_PARENS,
    SPI_FRAKTR,
    SPI_BOLD,
    SPI_MATH,
    SPI_GFLOCK,
    SPI_KP_00,
    SPI_GLO,
};

#ifdef RGBLIGHT_ENABLE

enum layer_base {
    LAYER_BASE_DEFAULT = _BASE,
    LAYER_BASE_REGULAR = _NUMPAD,
    LAYER_BASE_END     = _FN + 1,
};

typedef enum layer_ack {
    ACK_NO = 0,
    ACK_YES,
    ACK_MEH,
    ACK_HUH,
} layer_ack_t;

#    define RGB_LAYER_ACK_DURATION 500

void          matrix_init_user_rgb(void);
void          matrix_scan_user_rgb(void);
void          keyboard_post_init_user_rgb(void);
bool          process_record_user_rgb(uint16_t keycode, keyrecord_t *record);
void          post_process_record_user_rgb(uint16_t keycode, keyrecord_t *record);
layer_state_t layer_state_set_user_rgb(layer_state_t state);
layer_state_t default_layer_state_set_user_rgb(layer_state_t state);
bool          led_update_user_rgb(led_t led_state);
void          rgb_layer_ack(layer_ack_t n);
void          rgb_layer_ack_yn(bool yn);
void          clear_rgb_layers(void);
void          shutdown_user_rgb(void);
#endif

#ifdef UNICODEMAP_ENABLE
void eeconfig_init_user_unicode(void);
#endif

#ifdef SPI_DEBUG_SCAN_RATE
#    ifndef SPI_SCAN_RATE_INTERVAL
#        define SPI_SCAN_RATE_INTERVAL 10
#    endif
#endif
