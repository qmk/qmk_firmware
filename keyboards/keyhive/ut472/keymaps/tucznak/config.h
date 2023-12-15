#pragma once

#undef MANUFACTURER
#undef PRODUCT

#define MANUFACTURER    "Potato Inc."
#define PRODUCT         "Qt3.14"

/* turn off RGB when computer sleeps */
#ifdef RGBLIGHT_ENABLE
#define RGBLIGHT_SLEEP
#endif

/* send tap key if no layer key was used even after tap delay */
#define TAPPING_TERM 50
#define RETRO_TAPPING
