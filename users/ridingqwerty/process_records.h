#pragma once
#include "ridingqwerty.h"

#if defined(KEYMAP_SAFE_RANGE)
  #define PLACEHOLDER_SAFE_RANGE KEYMAP_SAFE_RANGE
#else
  #define PLACEHOLDER_SAFE_RANGE SAFE_RANGE
#endif

/*
enum userspace_custom_keycodes {
   VRSN = PLACEHOLDER_SAFE_RANGE,
   KC_QWERTY,
   KC_COLEMAK,
   KC_DVORAK,
   // MACRO KEYCODES GO HERE
   NEW_SAFE_RANGE
};
*/

bool process_record_secrets(uint16_t keycode, keyrecord_t *record);
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);

// KEYCODE/LAYER/MODTAP redefines
// LT
//#define BK_LWER LT(_LOWER, KC_BSCP)
// OSM
//#define OS_LALT OSM(MOD_LALT)

//#define UC_IRNY UC(0x2E2E)
//#define UC_CLUE UC(0x203D)

enum userspace_custom_keycodes {
    FIRST = PLACEHOLDER_SAFE_RANGE,
    RUSTY,
    FUEL,
    C0RE,
    MUNKY,
    AR1ST,
    VAXIS,
    OS_LAB,
    CDLOCAL,
    SYSNOC,
    LM_QUOT,
    LAST
};

bool process_record_secrets(uint16_t keycode, keyrecord_t *record);
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);

/*
#define RUSTY KC_SECRET_1
#define FUEL KC_SECRET_2
#define C0RE KC_SECRET_3
#define MUNKY KC_SECRET_4
#define AR1ST KC_SECRET_5
#define VAXIS KC_SECRET_6
#define OS_LAB KC_SECRET_7
#define CDLOCAL KC_SECRET_8
#define SYSNOC KC_SECRET_9
*/
