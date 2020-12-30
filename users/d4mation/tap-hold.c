#include "tap-hold.h"

#ifndef TAP_HOLD_TIME
#define TAP_HOLD_TIME 200
#endif

uint16_t tap_hold_timer;

void tap_or_hold( keyrecord_t *record, uint16_t tap, uint16_t hold ) {

  if ( record->event.pressed ) {
    tap_hold_timer = timer_read();
  } else {

    if ( tap_hold_timer &&
      timer_elapsed( tap_hold_timer ) > TAP_HOLD_TIME ) {
      /* Held down then released */
      tap_code( hold );
    } else {
      /* Quickly Tapped */
      tap_code( tap );
    }

    tap_hold_timer = 0;

  }

}