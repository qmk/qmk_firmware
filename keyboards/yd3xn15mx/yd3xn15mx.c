// Copyright 2022 Thunderbird2086 (Thunderbird2086)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "yd3xn15mx.h"


#ifdef RGB_MATRIX_ENABLE

  // Logical Layout
  // Columns
  // 0  1  2  3  4  5
  //                   ROWS
  // 06 05 04 03 02 01   0
  // 25             26
  // 07 12 13 18 19      1
  // 24             27
  // 08 11 14 17 20      2
  //    23       22
  // 09 10 15 16 21      3
  //
  // Physical Layout
  // Columns
  //                   ROWS
  // 06 05 04 03 02 01   0
  // 25             26
  // 07 12 13 18 19      1
  // 24             27
  // 08 11 14 17 20      2
  //    23       22
  // 09 10 15 16 21      3

#define LED_LAYOUT( \
    L06, L05, L04, L03, L02, L01, \
    L25,                L26, \
    L07, L12, L13, L18, L19, \
    L24,                L27, \
    L08, L11, L14, L17, L20, \
    L23,                L22, \
    L09, L10, L15, L16, L21 ) \
  {\
    L01, L02, L03, L04, L05, L06, \
    L07, L08, L09, L10, L11, L12, \
    L13, L14, L15, L16, L17, L18, \
    L19, L20, L21, L22, L23, L24, \
    L25, L26, L27 \
  }
                      
#define POS( x, y ) { x, y }

led_config_t g_led_config = { {
    //  Key Matrix to LED Index
    {       6,      11,     12,     17,     18 },
    {       7,      10,     13,     16,     19 },
    {       8,       9,     14,     15,     21 },
    {  NO_LED,  NO_LED, NO_LED, NO_LED, NO_LED },
    {  NO_LED,       3, NO_LED,      2, NO_LED },
    {  NO_LED,  NO_LED, NO_LED, NO_LED, NO_LED },
    {       5,       4, NO_LED,      1,      0 },
}, LED_LAYOUT (
    // LED Index to Physical Position
    POS(  22,   0 ), POS(  44,   0 ), POS(  90,   0 ), POS( 134,   0 ), POS( 179,   0 ), POS( 201,  0 ),
    POS(   0,  32 ),                                                    POS( 224,  32 ),
    POS(   0,  32 ), POS(  68,  32 ), POS( 112,  32 ), POS( 157,  32 ), POS( 224,  32 ),
    POS(   0,  48 ),                                                    POS( 224,  48 ),
    POS(   0,  48 ), POS(  68,  48 ), POS( 112,  48 ), POS( 157,  48 ), POS( 224,  48 ),
    POS(  44,  64 ),                                                    POS( 179,  64 ), 
    POS(   0,  64 ), POS(  68,  64 ), POS( 112,  64 ), POS( 157,  64 ), POS( 224,  64 )
), LED_LAYOUT(
    // LED Index to Flag
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    LED_FLAG_UNDERGLOW,                                                         LED_FLAG_UNDERGLOW,
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    LED_FLAG_UNDERGLOW,                                                         LED_FLAG_UNDERGLOW,
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    LED_FLAG_UNDERGLOW,                                                         LED_FLAG_UNDERGLOW,
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT
) };
#endif
