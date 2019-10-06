#pragma once
// #include "quantum.h"
// #include "version.h"
// #include "eeprom.h"
#include "wrappers.h"
#include "process_records.h"

/* Define layer names */
enum userspace_layers {
    _QWERTY  = 0,
    _NUMLOCK = 0,
    _COLEMAK,
    _MODS, /* layer 8 */
    _MACROS,
    _MEDIA,
    _LOWER,
    _RAISE,
    _ADJUST,
};
