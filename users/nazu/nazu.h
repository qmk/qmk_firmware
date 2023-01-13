#pragma once
#include QMK_KEYBOARD_H

/* Define layer names */
enum userspace_layers {
    _QWERTY = 0,    // QWERTY layout for WIN or UNIX
    _COLEMAK,       // Colemak lazout
    _COLEMAK_DH,    // Colemak DHS layout
    _FN1,           //
    _FN2,           //
    _MEDIA,         //
    _LOWER,         //
    _RAISE,         //
    _ADJUST,        //
};


/* Tap Dance definitions */
#ifdef TAP_DANCE_ENABLE
#   include "keyrecords/tap_dances.h"
#   include "keyrecords/tap_dances.c"
#endif

#ifdef OLED_ENABLE
/* status variables */
#    include "oled/oled_rocket.c"
#    include "oled/oled_luna.c"
// #    include "oled/oled_status.c"
#endif

#include "keyrecords/wrappers.h"
#include "keyrecords/process_records.h"
#include "keyrecords/process_records.c"
