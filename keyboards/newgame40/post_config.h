#pragma once

#ifndef IOS_DEVICE_ENABLE
#    if RGBLED_NUM <= 6
#        define RGBLIGHT_LIMIT_VAL 255
#    else
#        define RGBLIGHT_LIMIT_VAL 130
#    endif
#    define RGBLIGHT_VAL_STEP 17
#else
#    if RGBLED_NUM <= 6
#        define RGBLIGHT_LIMIT_VAL 90
#    else
#        define RGBLIGHT_LIMIT_VAL 45
#    endif
#    define RGBLIGHT_VAL_STEP 4
#endif
