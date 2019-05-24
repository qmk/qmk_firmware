#ifndef REV2_H
#define REV2_CONFIG_H

#include "../helix.h"

//void promicro_bootloader_jmp(bool program);
#include "quantum.h"

#ifdef RGBLIGHT_ENABLE
//rgb led driver
#include "ws2812.h"
#endif

#ifdef USE_I2C
#include <stddef.h>
#ifdef __AVR__
  #include <avr/io.h>
  #include <avr/interrupt.h>
#endif
#endif

//void promicro_bootloader_jmp(bool program);

#ifndef FLIP
// Standard Keymap
// (TRRS jack on the left half is to the right, TRRS jack on the right half is to the left)
#define LAYOUT( \
  L00, L01, L02, L03, L04,                     R00, R01, R02, R03, R04, \
  L10, L11, L12, L13, L14,                     R10, R11, R12, R13, R14, \
  L20, L21, L22, L23, L24, L25, L26, R26, R25, R20, R21, R22, R23, R24 \
  ) \
  { \
    { L00, L01, L02, L03, L04, KC_NO, KC_NO }, \
    { L10, L11, L12, L13, L14, KC_NO, KC_NO }, \
    { L20, L21, L22, L23, L24, L25,   L26,}, \
    { R00, R01, R02, R03, R04, KC_NO, KC_NO }, \
    { R10, R11, R12, R13, R14, KC_NO, KC_NO }, \
    { R20, R21, R22, R23, R24, R25,   R26,} \
  }
#else
// Keymap with right side flipped
// (TRRS jack on both halves are to the right)
#define LAYOUT( \
  L00, L01, L02, L03, L04,                     R00, R01, R02, R03, R04, \
  L10, L11, L12, L13, L14,                     R10, R11, R12, R13, R14, \
  L20, L21, L22, L23, L24, L25, L26, R26, R25, R20, R21, R22, R23, R24 \
  ) \
  { \
    { L00, L01, L02, L03, L04, KC_NO, KC_NO }, \
    { L10, L11, L12, L13, L14, KC_NO, KC_NO }, \
    { L20, L21, L22, L23, L24, L25,   L26   }, \
    { KC_NO, KC_NO, R04, R03, R02, R01, R00 }, \
    { KC_NO, KC_NO, R14, R13, R12, R11, R10 }, \
    { R26,   R25,   R24, R23, R22, R21, R20 } \
  }
#endif

// Used to create a keymap using only KC_ prefixed keys

#define LAYOUT_kc( \
  L00, L01, L02, L03, L04,                     R00, R01, R02, R03, R04, \
  L10, L11, L12, L13, L14,                     R10, R11, R12, R13, R14, \
  L20, L21, L22, L23, L24, L25, L26, R26, R25, R20, R21, R22, R23, R24 \
  ) \
  LAYOUT( \
    KC_##L00, KC_##L01, KC_##L02, KC_##L03, KC_##L04,                                         KC_##R00, KC_##R01, KC_##R02, KC_##R03, KC_##R04, \
    KC_##L10, KC_##L11, KC_##L12, KC_##L13, KC_##L14,                                         KC_##R10, KC_##R11, KC_##R12, KC_##R13, KC_##R14, \
    KC_##L20, KC_##L21, KC_##L22, KC_##L23, KC_##L24, KC_##L25, KC_##L26, KC_##R26, KC_##R25, KC_##R20, KC_##R21, KC_##R22, KC_##R23, KC_##R24 \
  )


#endif

