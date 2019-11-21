#pragma once
#include "ridingqwerty.h"

#if defined(KEYMAP_SAFE_RANGE)
  #define PLACEHOLDER_SAFE_RANGE KEYMAP_SAFE_RANGE
#else
  #define PLACEHOLDER_SAFE_RANGE SAFE_RANGE
#endif

bool process_record_secrets(uint16_t keycode, keyrecord_t *record);
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);

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
    RG_QUOT,
    LAST
};

bool process_record_secrets(uint16_t keycode, keyrecord_t *record);
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
