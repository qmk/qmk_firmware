
#pragma once

#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_COLOR
#define RGB_MATRIX_STARTUP_HUE 162 /* blue (170) minus 1 step */
#define RGB_MATRIX_STARTUP_VAL 191 /* max bri minus 4 steps */
#define RGB_MATRIX_STARTUP_SPD 111 /* default 127 minus 1 step */

#define TAPPING_TERM 175

#define ONESHOT_TAP_TOGGLE 5  /* Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TIMEOUT 5000  /* Time (in ms) before the one shot key is released */
