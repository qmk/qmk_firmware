#pragma once

#include "helix.h"

#ifndef SPLIT_KEYBOARD
  extern bool is_helix_master(void);
  #define is_keyboard_master() is_helix_master()
#endif

// Each keymap.c should use is_keyboard_master() instead of 'is_master', 'has_usb()'.
// But keep 'is_master' for a while for backwards compatibility
//  for the old keymap.c.
extern uint8_t is_master; // 'is_master' will be obsolete, it is recommended to use 'is_keyboard_master ()' instead.
#define has_usb() is_keyboard_master()

#ifndef FLIP_HALF
  // Standard Keymap
  // (TRRS jack on the left half is to the right, TRRS jack on the right half is to the left)
#define LAYOUT( \
    L00, L01, L02, L03, L04, L05,           R00, R01, R02, R03, R04, R05, \
    L10, L11, L12, L13, L14, L15,           R10, R11, R12, R13, R14, R15, \
    L20, L21, L22, L23, L24, L25,           R20, R21, R22, R23, R24, R25, \
    L30, L31, L32, L33, L34, L35, L36, R36, R30, R31, R32, R33, R34, R35  \
) { \
    { L00, L01, L02, L03, L04, L05, KC_NO }, \
    { L10, L11, L12, L13, L14, L15, KC_NO }, \
    { L20, L21, L22, L23, L24, L25, KC_NO }, \
    { L30, L31, L32, L33, L34, L35, L36 }, \
    { R05, R04, R03, R02, R01, R00, KC_NO }, \
    { R15, R14, R13, R12, R11, R10, KC_NO }, \
    { R25, R24, R23, R22, R21, R20, KC_NO }, \
    { R35, R34, R33, R32, R31, R30, R36 }, \
}
#else
    // Keymap with right side flipped
    // (TRRS jack on both halves are to the right)
    #define LAYOUT( \
        L00, L01, L02, L03, L04, L05,           R00, R01, R02, R03, R04, R05, \
        L10, L11, L12, L13, L14, L15,           R10, R11, R12, R13, R14, R15, \
        L20, L21, L22, L23, L24, L25,           R20, R21, R22, R23, R24, R25, \
        L30, L31, L32, L33, L34, L35, L36, R36, R30, R31, R32, R33, R34, R35  \
    ) { \
        { L00, L01, L02, L03, L04, L05, KC_NO }, \
        { L10, L11, L12, L13, L14, L15, KC_NO }, \
        { L20, L21, L22, L23, L24, L25, KC_NO }, \
        { L30, L31, L32, L33, L34, L35, L36 }, \
        { KC_NO, R00, R01, R02, R03, R04, R05 }, \
        { KC_NO, R10, R11, R12, R13, R14, R15 }, \
        { KC_NO, R20, R21, R22, R23, R24, R25 }, \
        { R36, R30, R31, R32, R33, R34, R35 }, \
  }
#endif
