#pragma once

#define TAPPING_TOGGLE 2
#define TAPPING_TERM 200
#define PERMISSIVE_HOLD

#ifdef RGBLIGHT_ENABLE
#   define RGBLIGHT_SLEEP
#endif

#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
#   define RGB_THEME_ENABLE
#endif

#define TAP_CODE_DELAY 5

/* Disable unused and unneeded features to reduce on firmware size */
#ifdef LOCKING_SUPPORT_ENABLE
#    undef LOCKING_SUPPORT_ENABLE
#endif
#ifdef LOCKING_RESYNC_ENABLE
#    undef LOCKING_RESYNC_ENABLE
#endif
