#pragma once

#include "j3ps.h"

extern bool is_helix_master(void);
#define is_keyboard_master() is_helix_master()

// Each keymap.c should use is_keyboard_master() instead of 'is_master', 'has_usb()'.
// But keep 'is_master' for a while for backwards compatibility
//  for the old keymap.c.
extern uint8_t is_master; // 'is_master' will be obsolete, it is recommended to use 'is_keyboard_master ()' instead.
#define has_usb() is_keyboard_master()
#define LAYOUT( \
    L00, L01, L02, L03, L04, L05, L06, R00, R01, R02, R03, R04, R05, R06, R07, \
    L10, L11, L12, L13, L14, L15, L16, R10, R11, R12, R13, R14, R15, R16, R17, \
    L20, L21, L22, L23, L24, L25, L26, R20, R21, R22, R23, R24, R25, R26, R27, \
    L30, L31, L32, L33, L34, L35, L36, R30, R31, R32, R33, R34, R35, R36, R37, \
    L40, L41, L42, L43, L44, L45, L46, R40, R41, R42, R43, R44, R45, R46, R47, R48 \
) { \
    { L00, L01, L02, L03, L04, L05, L06, KC_NO, KC_NO }, \
    { L10, L11, L12, L13, L14, L15, L16, KC_NO, KC_NO }, \
    { L20, L21, L22, L23, L24, L25, L26, KC_NO, KC_NO }, \
    { L30, L31, L32, L33, L34, L35, L36, KC_NO, KC_NO }, \
    { L40, L41, L42, L43, L44, L45, L46, KC_NO, KC_NO }, \
    { R00, R01, R02, R03, R04, R05, R06, R07,   KC_NO }, \
    { R10, R11, R12, R13, R14, R15, R16, R17,   KC_NO }, \
    { R20, R21, R22, R23, R24, R25, R26, R27,   KC_NO }, \
    { R30, R31, R32, R33, R34, R35, R36, R37,   KC_NO }, \
    { R40, R41, R42, R43, R44, R45, R46, R47,   R48   } \
}
