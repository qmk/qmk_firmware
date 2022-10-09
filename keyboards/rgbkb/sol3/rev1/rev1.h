/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <https://github.com/Legonut> wrote this file.  As long as you retain this
 * notice you can do whatever you want with this stuff. If we meet some day, and
 * you think this stuff is worth it, you can buy me a beer in return. David Rauseo
 * ----------------------------------------------------------------------------
 */

#pragma once

#include "sol3.h"

// clang-format off
/* Blank ascii map to reuse, with labeled possible encoder positions, *rgb encoder only
┌──────┬──────┬──────┬──────┬──────┬──────┬──────┐  ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┐
│      │      │      │      │      │      │  E2  │  │  E5  │      │      │      │      │      │      │
├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
│      │      │      │      │      │      │      │  │      │      │      │      │      │      │      │
├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
│      │      │      │      │      │      │      │  │      │      │      │      │      │      │      │
├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
│      │      │      │      │      │      │  E2  │  │  E5  │      │      │      │      │      │      │
├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
│      │      │      │  E1  │  E1  │      │  E0* │  │  E3* │      │  E4  │  E4  │      │      │      │
└──────┴──────┴──────┴──────┴──────┤      ├──────┤  ├──────┤      ├──────┴──────┴──────┴──────┴──────┘
                                   │      │  E0  │  │  E3  │      │
                                   └──────┴──────┘  └──────┴──────┘
┌──────┬──────┬──────┬──────┬──────┬──────┐                ┌──────┬──────┬──────┬──────┬──────┬──────┐
│  E0↑ │  E0↓ │  E1↑ │  E1↓ │  E2↑ │  E2↓ │                │  E3↑ │  E3↓ │  E4↑ │  E4↓ │  E5↑ │  E5↓ │
└──────┴──────┴──────┴──────┴──────┴──────┘                └──────┴──────┴──────┴──────┴──────┴──────┘
┌──────┬──────┬──────┬──────┬──────┐                              ┌──────┬──────┬──────┬──────┬──────┐
│      │      │      │      │      │                              │      │      │      │      │      │
└──────┴──────┴──────┴──────┴──────┘                              └──────┴──────┴──────┴──────┴──────┘
*/

#define LAYOUT( \
    L00, L01, L02, L03, L04, L05, L06,           R00, R01, R02, R03, R04, R05, R06, \
    L10, L11, L12, L13, L14, L15, L16,           R10, R11, R12, R13, R14, R15, R16, \
    L20, L21, L22, L23, L24, L25, L26,           R20, R21, R22, R23, R24, R25, R26, \
    L30, L31, L32, L33, L34, L35, L36,           R30, R31, R32, R33, R34, R35, R36, \
    L40, L41, L42, L43, L44, L45, L46, L47, R40, R41, R42, R43, R44, R45, R46, R47, \
    \
    E0L, E0R, E1L, E1R, E2L, E2R,                     E3L, E3R, E4L, E4R, E5L, E5R, \
    LT0, LT1, LT2, LSL, LSR,                               RT0, RT1, RT2, RSL, RSR \
) \
{ \
    /* Left Half */ \
    { L00, L01, L02, L03, L04, L05, L06, LT0   }, \
    { L10, L11, L12, L13, L14, L15, L16, LT1   }, \
    { L20, L21, L22, L23, L24, L25, L26, LT2   }, \
    { L30, L31, L32, L33, L34, L35, L36, KC_NO }, \
    { L40, L41, L42, L43, L44, L45, L46, L47   }, \
    { E0L, E0R, E1L, E1R, E2L, E2R, LSL, LSR   }, \
    /* Right Half */ \
    { R06, R05, R04, R03, R02, R01, R00, RT0   }, \
    { R16, R15, R14, R13, R12, R11, R10, RT1   }, \
    { R26, R25, R24, R23, R22, R21, R20, RT2   }, \
    { R36, R35, R34, R33, R32, R31, R30, KC_NO }, \
    { R47, R46, R45, R44, R43, R42, R41, R40   }, \
    { E3L, E3R, E4L, E4R, E5L, E5R, RSL, RSR   } \
}
// clang-format on

// weak functions overridable by the user
void render_layer_status(void);
void render_leds_status(void);
void render_touch_status(void);
void render_audio_status(void);

#ifdef RGB_MATRIX_ENABLE
// utility function to cycle active led zones
void rgb_matrix_increase_flags(void);
#endif