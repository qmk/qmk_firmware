// Copyright 2026 Quentin LEBASTARD <bstkbd@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define RAW_USAGE_PAGE 0xFF60
#define RAW_USAGE_ID 0x61

#ifdef EXTRA_EXTRA_LONG_COMBOS
#undef EXTRA_EXTRA_LONG_COMBOS
#endif

#ifdef EXTRA_SHORT_COMBOS
#undef EXTRA_SHORT_COMBOS
#endif

#ifdef EXTRA_LONG_COMBOS
#undef EXTRA_LONG_COMBOS
#endif

// enables custom global combo term by Argos
#ifndef COMBO_TERM_PER_COMBO
#define COMBO_TERM_PER_COMBO
#endif

// enables custom global tapping term by Argos
#ifndef TAPPING_TERM_PER_KEY
#define TAPPING_TERM_PER_KEY
#endif

// Macro text delay, otherwise keys can overwrite themselves and skip
#undef DYNAMIC_KEYMAP_MACRO_DELAY
#define DYNAMIC_KEYMAP_MACRO_DELAY 8

// More available live storage! Useful for tap dances and RGB
// Also, better read write endurance
#define WEAR_LEVELING_LOGICAL_SIZE 65536
#define WEAR_LEVELING_BACKING_SIZE (WEAR_LEVELING_LOGICAL_SIZE * 4)

#define SPLIT_TRANSACTION_IDS_KB RPC_ID_RGB_SYNC

#if defined(POINTING_DEVICE_DRIVER_pmw3360) || defined(POINTING_DEVICE_DRIVER_digitizer) || defined(POINTING_DEVICE_DRIVER_cirque_pinnacle_spi)
    #define BK_HAS_POINTING_DEVICE 1
#endif

#ifndef SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LAYER_STATE_ENABLE
#endif
#ifndef SPLIT_LED_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
#endif