#pragma once

#undef MANUFACTURER
#undef PRODUCT

#define MANUFACTURER    Potato Inc.
#define PRODUCT         Qt3.14

/* send tap key if no layer key was used even after tap delay */
#define TAPPING_TERM 250
#define RETRO_TAPPING

/* turn off RGB when computer sleeps */
#ifdef RGB_DI_PIN
#define RGBLIGHT_SLEEP
#endif

/* number of backlight levels */
#ifdef BACKLIGHT_LEVELS
#undef BACKLIGHT_LEVELS
#endif
#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 8
#endif
