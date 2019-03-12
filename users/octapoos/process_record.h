#pragma once
#include "octapoos.h"

#if defined(KEYMAP_SAFE_RANGE)
  #define PLACEHOLDER_SAFE_RANGE KEYMAP_SAFE_RANGE
#else
  #define PLACEHOLDER_SAFE_RANGE SAFE_RANGE
#endif

enum userspace_cutsom_keycodes {
  VRSN = PLACEHOLDER_SAFE_RANGE,
  KC_QWERTY,
  KC_COLEMAK,        // Sets default layer to COLEMAK
  KC_DVORAK,         // Sets default layer to DVORAK
  KC_WORKMAN,        // Sets default layer to WORKMAN
  KC_CCCV            // Hold to copy, tap to paste
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record);

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ADJUST MO(_ADJUST)

#define QWERTY KC_QWERTY
#define COLEMAK KC_COLEMAK
#define DVORAK KC_DVORAK
#define WORKMAN KC_WORKMAN

#define KC_RESET RESET
#define KC_RST KC_RESET

#define MACRO_TIMER 5

#ifndef TAPPING_TERM
#define TAPPING_TERM 100
#endif
