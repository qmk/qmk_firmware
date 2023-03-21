// Copyright 2023 zzeneg (@zzeneg)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <lv_conf.h>

/* undef and define MIN/MAX as a workaround for gif library */
#undef MIN
#undef MAX
#undef LV_USE_GIF
#define LV_USE_GIF 1
#define MIN(A, B) ((A) < (B) ? (A) : (B))
#define MAX(A, B) ((A) > (B) ? (A) : (B))

#undef LV_FONT_MONTSERRAT_14

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

/* Custom fonts:
    - montserrat_24_en_ru_4bpp - english/cyrillic symbols, range 0x20-0x7F,0x0410-0x044F,0x0401,0x0451
    - montserrat_48_digits - digits, dot and colon only, range 0x2E,0x30-0x3A
 */

#undef LV_FONT_CUSTOM_DECLARE
#define LV_FONT_CUSTOM_DECLARE LV_FONT_DECLARE(montserrat_24_en_ru) LV_FONT_DECLARE(montserrat_48_digits)

#undef LV_FONT_DEFAULT
#define LV_FONT_DEFAULT &montserrat_24_en_ru
