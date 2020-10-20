#pragma once

#if defined(KEYBOARD_crkbd_rev1_common) || defined(KEYBOARD_crkbd_rev1_legacy)
#    define EE_HANDS

#    if defined(RGBLIGHT_ENABLE)
/* Configure RGB for underglow only (first six LEDs on each side). */
#        undef RGBLED_SPLIT
#        define RGBLED_SPLIT \
            { 6, 6 }
#    endif

#    if defined(RGB_MATRIX_ENABLE)
/* Limit max RGB LED current to avoid tripping controller fuse. */
#        undef RGB_MATRIX_MAXIMUM_BRIGHTNESS
#        define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150
#    endif
#endif
