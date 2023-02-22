#pragma once

#undef MANUFACTURER
#undef PRODUCT

#define MANUFACTURER    "Potato Inc."
#define PRODUCT         "Trash Panda"

/* for bootloader */
#define QMK_ESC_OUTPUT B2
#define QMK_ESC_INPUT D0
#define QMK_LED B0

/* send tap key if no layer key was used even after tap delay */
#undef TAPPING_TERM
#define TAPPING_TERM 250
#define RETRO_TAPPING
#define TAPPING_TOGGLE 2
