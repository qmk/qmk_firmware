#pragma once

#undef MANUFACTURER
#undef PRODUCT
#undef DESCRIPTION

#define MANUFACTURER    Potato Inc.
#define PRODUCT         Trash Panda
#define DESCRIPTION     Qt3.14 smolkeeb

/* for bootloader */
#define QMK_ESC_OUTPUT B2
#define QMK_ESC_INPUT D0
#define QMK_LED B0

/* turn off RGB when computer sleeps */
#ifdef RGBLIGHT_ENABLE
#define RGBLIGHT_SLEEP
#endif

/* send tap key if no layer key was used even after tap delay */
#ifdef TAPPING_TERM
#undef TAPPING_TERM
#endif
#define TAPPING_TERM 250
#define RETRO_TAPPING
#define TAPPING_TOGGLE 2
