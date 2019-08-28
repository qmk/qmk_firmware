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
