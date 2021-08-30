#pragma once

#if __GNUC__ > 5
#    if __has_include("passwd.h")
#        include "passwd.h"
#    endif  // if file exists
#endif      // __GNUC__

#ifndef PASSWORD_A
    #define PASSWORD_A "1234567890"
#endif

#ifndef PASSWORD_B
    #define PASSWORD_B "pass123"
#endif

#define RGBLIGHT_LAYERS

#define LSPO_KEYS KC_LSFT, KC_TRNS, KC_5
#define RSPC_KEYS KC_RSFT, KC_TRNS, KC_MINS
