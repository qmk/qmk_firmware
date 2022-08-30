// Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifndef OLED_UPDATE_INTERVAL
#    ifdef OLED_DRIVER_SH1107
#        define OLED_UPDATE_INTERVAL 75
#    else
#        ifdef SPLIT_KEYBOARD
#            define OLED_UPDATE_INTERVAL 60
#        else
#            define OLED_UPDATE_INTERVAL 15
#        endif
#    endif
#endif
#define OLED_DISABLE_TIMEOUT
#ifdef OLED_FONT_H
#    undef OLED_FONT_H
#endif
#define OLED_FONT_H "oled/drashna_font.h"
#define OLED_FONT_END 255
// #    define OLED_FONT_5X5
// #    define OLED_FONT_AZTECH
// #    define OLED_FONT_BMPLAIN
// #    define OLED_FONT_CRACKERS
#define OLED_FONT_DEAD_MEAL
// #    define OLED_FONT_EIN
// #    define OLED_FONT_HISKYF21
// #    define OLED_FONT_SQUASH
// #    define OLED_FONT_ZXPIX
// #    define OLED_FONT_SUPER_DIGG

// #    define OLED_LOGO_BEBOP
// #    define OLED_LOGO_CORNE
// #    define OLED_LOGO_GMK_BAD
// #    define OLED_LOGO_GOTHAM
// #    define OLED_LOGO_HUE_MANITEE
// #    define OLED_LOGO_LOOSE
#define OLED_LOGO_SCIFI
// #    define OLED_LOGO_SETS3N
// #    define OLED_LOGO_SKEEB

#ifdef OLED_DRIVER_SH1107
#    define OLED_DISPLAY_CUSTOM
#    define OLED_IC_SH1107 2
#    define OLED_DISPLAY_128X128
#    define OLED_DISPLAY_WIDTH 128
#    define OLED_DISPLAY_HEIGHT 128
#    define OLED_MATRIX_SIZE (OLED_DISPLAY_HEIGHT / 8 * OLED_DISPLAY_WIDTH)
#    define OLED_BLOCK_TYPE uint32_t
#    define OLED_SOURCE_MAP \
        { 0, 8, 16, 24, 32, 40, 48, 56 }
#    define OLED_TARGET_MAP \
        { 56, 48, 40, 32, 24, 16, 8, 0 }
#    define OLED_BLOCK_COUNT (sizeof(OLED_BLOCK_TYPE) * 8)
#    define OLED_BLOCK_SIZE (OLED_MATRIX_SIZE / OLED_BLOCK_COUNT)
#    define OLED_COM_PINS COM_PINS_ALT
#    define OLED_IC OLED_IC_SH1107
#    ifndef OLED_BRIGHTNESS
#        define OLED_BRIGHTNESS 50
#    endif
#endif
