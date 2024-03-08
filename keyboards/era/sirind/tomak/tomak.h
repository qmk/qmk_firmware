// Copyright 2023 Hyojin Bak (@eerraa)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

enum tomak_keycodes {
    IN_TOGG = QK_KB_0,   // indicator toggle
    IN_OVER,             // indicator override toggle
	IN_BRI,              // indicator brightness increase
	IN_BRD,              // indicator brightness decrease
    IN_HUEI,             // indicator hue increase
    IN_HUED,             // indicator hue decrease
    IN_SATI,             // indicator saturation increase
    IN_SATD              // indicator saturation decrease
};

typedef union {
    uint32_t raw;
    struct {
        bool indicator_toggle:1;           // | byte
        bool indicator_override:1;         // 1 byte
        HSV indicator_hsv;                 // 3 bytes
    } __attribute__((packed));             // total 4 bytes
} tomak_config_t;

extern tomak_config_t g_tomak_config;

#ifdef VIA_ENABLE
// via value id declaration
enum tomak_custom_value_id {
    id_custom_indicator_toggle = 0,
    id_custom_indicator_override,
    id_custom_indicator_brightness,
    id_custom_indicator_color
};

// function declaration
void indicator_config_set_value( uint8_t *data );
void indicator_config_get_value( uint8_t *data );
void indicator_config_save ( void );
void _set_color(HSV *color, uint8_t *data);
void _get_color(HSV *color, uint8_t *data);
#endif