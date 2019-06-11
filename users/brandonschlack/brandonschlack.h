#pragma once

#include "quantum.h"
#include "eeprom.h"
#include "process_records.h"
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
#   include "rgb_bs.h"
#endif

// Define layer names
#ifndef IS_MACROPAD
enum bs_layers {
    _MAC = 0,
    _MACFN,
    _WIN,
    _WINFN
};
#else
enum macropad_layers {
    _NAVI = 0,
    _REEDER,
    _MEDIA,
    _KEYPAD,
    KEYMAP_LAYERS
};
#endif
#define _MAGIC 15

void matrix_scan_keymap(void);
