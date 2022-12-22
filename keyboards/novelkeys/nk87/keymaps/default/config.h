#pragma once

#ifdef RGB_MATRIX_ENABLE
    #define RGB_DISABLE_WHEN_USB_SUSPENDED true
    #define RGB_MATRIX_TIMEOUT 900000     // 15 minutes (15 * 60 * 1000ms)

    // Effects
    #define RGB_MATRIX_FRAMEBUFFER_EFFECTS  // Heatmap, Rain
    #define RGB_MATRIX_KEYPRESSES           // REACTIVE, SPLASH modes
#endif // RGB_MATRIX_ENABLE
