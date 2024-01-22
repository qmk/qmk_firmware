// Copyright 2023 zzeneg (@zzeneg)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* disable some things before lv_conf include */
#define LV_USE_CALENDAR 0
#define LV_USE_SPAN 0
#define LV_USE_ROLLER 0
#define LV_USE_TEXTAREA 0

#include_next <lv_conf.h>

/* Custom fonts:
    - montserrat_20_en_ru - english/cyrillic symbols, range 0x20-0x7F,0x0410-0x044F,0x0401,0x0451
    - montserrat_48_digits - digits, dot and colon only, range 0x2E,0x30-0x3A
 */

#undef LV_FONT_CUSTOM_DECLARE
#define LV_FONT_CUSTOM_DECLARE LV_FONT_DECLARE(montserrat_20_en_ru) LV_FONT_DECLARE(montserrat_48_digits)

#undef LV_FONT_DEFAULT
#define LV_FONT_DEFAULT &montserrat_20_en_ru

#undef LV_FONT_MONTSERRAT_20
#define LV_FONT_MONTSERRAT_20 0

#undef LV_FONT_MONTSERRAT_48
#define LV_FONT_MONTSERRAT_48 0

// #undef LV_FONT_MONTSERRAT_16
// #define LV_FONT_MONTSERRAT_16 1

// #undef LV_FONT_MONTSERRAT_18
// #define LV_FONT_MONTSERRAT_18 1

// #undef LV_FONT_MONTSERRAT_20
// #define LV_FONT_MONTSERRAT_20 1

// #undef LV_FONT_MONTSERRAT_22
// #define LV_FONT_MONTSERRAT_22 1

// #undef LV_FONT_MONTSERRAT_24
// #define LV_FONT_MONTSERRAT_24 1

// #undef LV_FONT_MONTSERRAT_26
// #define LV_FONT_MONTSERRAT_26 1

// #undef LV_FONT_MONTSERRAT_28
// #define LV_FONT_MONTSERRAT_28 1

// #undef LV_FONT_MONTSERRAT_30
// #define LV_FONT_MONTSERRAT_30 1

// #undef LV_FONT_MONTSERRAT_32
// #define LV_FONT_MONTSERRAT_32 1

// #undef LV_FONT_MONTSERRAT_34
// #define LV_FONT_MONTSERRAT_34 1

// #undef LV_FONT_MONTSERRAT_36
// #define LV_FONT_MONTSERRAT_36 1

// #undef LV_FONT_MONTSERRAT_38
// #define LV_FONT_MONTSERRAT_38 1

// #undef LV_FONT_MONTSERRAT_40
// #define LV_FONT_MONTSERRAT_40 1

// #undef LV_FONT_MONTSERRAT_42
// #define LV_FONT_MONTSERRAT_42 1

// #undef LV_FONT_MONTSERRAT_44
// #define LV_FONT_MONTSERRAT_44 1

// #undef LV_FONT_MONTSERRAT_46
// #define LV_FONT_MONTSERRAT_46 1

// #undef LV_FONT_MONTSERRAT_48
// #define LV_FONT_MONTSERRAT_48 1

/* disable widgets*/
#undef LV_USE_ANIMIMG
#define LV_USE_ANIMIMG 0
#undef LV_USE_BAR
#define LV_USE_BAR 0
#undef LV_USE_BTN
#define LV_USE_BTN 0
#undef LV_USE_BTNMATRIX
#define LV_USE_BTNMATRIX 0
#undef LV_USE_CANVAS
#define LV_USE_CANVAS 0
#undef LV_USE_CHECKBOX
#define LV_USE_CHECKBOX 0
#undef LV_USE_DROPDOWN
#define LV_USE_DROPDOWN 0
#undef LV_USE_LINE
#define LV_USE_LINE 0
#undef LV_USE_SLIDER
#define LV_USE_SLIDER 0
#undef LV_USE_SWITCH
#define LV_USE_SWITCH 0
#undef LV_USE_TABLE
#define LV_USE_TABLE 0

/* disable extra components */
#undef LV_USE_CHART
#define LV_USE_CHART 0
#undef LV_USE_COLORWHEEL
#define LV_USE_COLORWHEEL 0
#undef LV_USE_IMGBTN
#define LV_USE_IMGBTN 0
#undef LV_USE_KEYBOARD
#define LV_USE_KEYBOARD 0
#undef LV_USE_LED
#define LV_USE_LED 0
#undef LV_USE_LIST
#define LV_USE_LIST 0
#undef LV_USE_MENU
#define LV_USE_MENU 0
#undef LV_USE_METER
#define LV_USE_METER 0
#undef LV_USE_MSGBOX
#define LV_USE_MSGBOX 0
#undef LV_USE_SPINBOX
#define LV_USE_SPINBOX 0
#undef LV_USE_SPINNER
#define LV_USE_SPINNER 0
#undef LV_USE_TABVIEW
#define LV_USE_TABVIEW 0
#undef LV_USE_TILEVIEW
#define LV_USE_TILEVIEW 0
#undef LV_USE_WIN
#define LV_USE_WIN 0

/* disable themes */
#undef LV_USE_THEME_BASIC
#define LV_USE_THEME_BASIC 0
#undef LV_USE_THEME_MONO
#define LV_USE_THEME_MONO 0

/* disable layouts */
#undef LV_USE_GRID
#define LV_USE_GRID 0

/* disable build examples */
#undef LV_BUILD_EXAMPLES
#define LV_BUILD_EXAMPLES 0
