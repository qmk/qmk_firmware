#pragma once

// Time out one shot layers after 3 seconds
#define ONESHOT_TIMEOUT 3000

#define RGBLED_NUM 16


// Undef and redefine default brightness to half of 255
#undef RGBLIGHT_LIMIT_VAL
#define RGBLIGHT_LIMIT_VAL 128

#define TAPPING_TERM 200
