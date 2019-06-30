#pragma once
#include "quantum.h"

#ifdef TAP_DANCE_ENABLE

#include "process_tap_dance.h"

//Tap Dance Declarations
enum {
  COMM_QUOT = 0,
  BACKSPACE,
  DELETE,
  DOT
};

#define TD_COMM TD(COMM_QUOT)
#define TD_BSPC TD(BACKSPACE)
#define TD_DEL TD(DELETE)
#define TD_DOT TD(DOT)

#else

void run_tap_dance_double(uint8_t i);
bool process_tap_dance_double(uint16_t keycode, keyrecord_t *record);

#endif
