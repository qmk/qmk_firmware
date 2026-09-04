// Copyright 2026 Quentin LEBASTARD <bstkbd@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
    Here we do a bit of shenanigans.
    I can't find a way to dynamically pull the amount of combo entries and size of a combo entry
    from argos.h, so instead we set it manually.
    TODO: fix.
*/

// for rgb mostly
#define SPLIT_LAYER_STATE_ENABLE

// increase layer amount
#ifdef DYNAMIC_KEYMAP_LAYER_COUNT
#undef DYNAMIC_KEYMAP_LAYER_COUNT
#endif
#define DYNAMIC_KEYMAP_LAYER_COUNT 8

// Do we have a pointing device? Then we want to save some memory for it.
// TODO cirque configuration
// TODO later switch to per-module eeprom management
#ifdef BK_HAS_POINTING_DEVICE
#define ARGOS_SIZE_POINTER_CONFIG 12 // a bit extra just in case
#define ARGOS_OFFSET_POINTER_CONFIG 0
#define ARGOS_OFFSET_CONFIG (ARGOS_OFFSET_POINTER_CONFIG + ARGOS_SIZE_POINTER_CONFIG)
#else
#define ARGOS_OFFSET_CONFIG 0
#endif

#define ARGOS_SIZE_CONFIG 7

#define ARGOS_OFFSET_COMBO (ARGOS_OFFSET_CONFIG + ARGOS_SIZE_CONFIG)
#define ARGOS_COMBO_ENTRIES 16 // this was already defined in argos.h, TODO fix this hardcoding...
#define ARGOS_SIZE_COMBO 13
#define ARGOS_SIZE_COMBOS (ARGOS_COMBO_ENTRIES * ARGOS_SIZE_COMBO)

#define ARGOS_OFFSET_TAP_DANCE (ARGOS_OFFSET_COMBO + ARGOS_SIZE_COMBOS)
#define ARGOS_TAP_DANCE_ENTRIES 50 // should be enough for anyone
#define ARGOS_SIZE_TAP_DANCE 11
#define ARGOS_SIZE_TAP_DANCES (ARGOS_TAP_DANCE_ENTRIES * ARGOS_SIZE_TAP_DANCE)

#define ARGOS_OFFSET_RGB_MATRIX (ARGOS_OFFSET_TAP_DANCE + ARGOS_SIZE_TAP_DANCES)
#if defined(POINTING_DEVICE_DRIVER_digitizer) || defined(POINTING_DEVICE_DRIVER_cirque_pinnacle_spi)
// TODO manage dilemma trackball
// dilemma, with underglow
// TODO: we use too many LEDs, as the thumb cluster row is usually not fully used.
#define RGB_ENTRIES_PER_LAYER MATRIX_COLS*MATRIX_ROWS*2
#else
// others, no underglow
#define RGB_ENTRIES_PER_LAYER MATRIX_COLS*MATRIX_ROWS
#endif
// TODO remove hardcoded 10 layers max value
#define ARGOS_RGB_MATRIX_ENTRIES RGB_ENTRIES_PER_LAYER*10 // up to 10 layers supported
#define ARGOS_SIZE_RGB_MATRIX_KEY_DATA 5
#define ARGOS_SIZE_RGB_MATRIX_ENTRIES (ARGOS_RGB_MATRIX_ENTRIES * ARGOS_SIZE_RGB_MATRIX_KEY_DATA)

#define ARGOS_EEPROM_SIZE_CALC (\
    ARGOS_SIZE_CONFIG + \
    ARGOS_SIZE_COMBOS + \
    ARGOS_SIZE_TAP_DANCES + \
    ARGOS_SIZE_RGB_MATRIX_ENTRIES)

// Reduce max address for dynamic keymap to ensure we don't overlap with Argos' EEPROM storage
// much easier than trying to set the start address.
#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR (TOTAL_EEPROM_BYTE_COUNT - 1 - ARGOS_EEPROM_SIZE_CALC)

// By default, macro space takes all the rest of the available space.
// This is made with AVR in mind, as that space will be very small.
// Here, it will be very big. This could cause issues with wear, since re-writing a macro
//    actually re-writes the whole macro space.
// So instead we define a smaller space manually.
#define DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE 16*512