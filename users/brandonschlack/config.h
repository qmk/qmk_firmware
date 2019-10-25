#pragma once

#define TAPPING_TOGGLE 2
#define TAPPING_TERM 200
#define TAP_HOLD_CAPS_DELAY 200

#ifdef RGBLIGHT_ENABLE
#   define RGBLIGHT_SLEEP
#endif

#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
#   define RGB_THEME_ENABLE
#endif

#ifdef BOOTLOADER_USBASP
#    define TAP_CODE_DELAY 5
#endif

/* Disable unused and unneeded features to reduce on firmware size */
#ifdef LOCKING_SUPPORT_ENABLE
#    undef LOCKING_SUPPORT_ENABLE
#endif
#ifdef LOCKING_RESYNC_ENABLE
#    undef LOCKING_RESYNC_ENABLE
#endif
