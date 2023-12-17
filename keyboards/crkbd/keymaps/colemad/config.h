// Copyright 2022 Álvaro Cortés (@ACortesDev)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define SPLIT_USB_DETECT // Added for Elite-C to work

#define QUICK_TAP_TERM 0
#define TAPPING_TERM 200

#ifdef RGB_MATRIX_ENABLE
    #define RGB_MATRIX_KEYPRESSES
    #define RGB_MATRIX_FRAMEBUFFER_EFFECTS
    #define RGB_MATRIX_SLEEP
    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150
    #define RGB_MATRIX_LED_FLUSH_LIMIT 16
    #define RGB_MATRIX_HUE_STEP 8
    #define RGB_MATRIX_SAT_STEP 8
    #define RGB_MATRIX_VAL_STEP 5
    #define RGB_MATRIX_SPD_STEP 10
    
    // Effects
    #define ENABLE_RGB_MATRIX_BREATHING
#endif 

#ifdef OLED_ENABLE
    #define SPLIT_LAYER_STATE_ENABLE
    #define SPLIT_LED_STATE_ENABLE
    #define SPLIT_MODS_ENABLE
    #define SPLIT_OLED_ENABLE
    #define OLED_TIMEOUT 60000
    #define OLED_FONT_H "keyboards/crkbd/keymaps/colemad/glcdfont.c"
#endif
