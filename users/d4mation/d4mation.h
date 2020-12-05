#pragma once

#include "quantum.h"

#ifdef UNICODE_ENABLE
#include "macros.h"
#endif

#ifdef TAP_DANCE_ENABLE
#include "tap-dance.h"
#endif

bool process_record_keymap( uint16_t keycode, keyrecord_t *record );

void matrix_init_keymap( void );

void matrix_scan_keymap( void );