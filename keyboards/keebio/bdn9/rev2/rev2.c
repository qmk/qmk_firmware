#include "rev2.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    // Key Matrix to LED Index
    { 0, 1, 2 },
    { 3, 4, 5 },
    { 6, 7, 8 }
}, {
    // LED Index to Physical Position
    { 0, 0 }, { 112, 0 }, { 224, 0 },
    { 0, 32 }, { 112, 32 }, { 224, 32 },
    { 0, 64 }, { 112, 64 }, { 224, 64 },
    { 56, 64 }, { 168, 64 },
}, {
    // LED Index to Flag
    4, 4, 4,
    4, 4, 4,
    4, 4, 4,
    2, 2
} };
#endif

void eeconfig_init_kb(void) {
#ifdef RGBLIGHT_ENABLE
    rgblight_enable();             // Enable RGB by default
    rgblight_sethsv(0, 255, 255);  // Set default HSV - red hue, full saturation, full brightness
#    ifdef RGBLIGHT_ANIMATIONS
    rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL + 2);  // set to RGB_RAINBOW_SWIRL by default
#    endif
#endif

#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_enable();  // Enable RGB by default
#endif

    eeconfig_update_kb(0);
    eeconfig_init_user();
}
