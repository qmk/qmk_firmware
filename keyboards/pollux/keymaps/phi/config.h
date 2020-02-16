#pragma once

/* split keyboard setup */
#define USE_SERIAL              /* SERIAL or MATRIX_I2C */
#define USE_SERIAL_PD2
#define MASTER_LEFT             /* LEFT or RIGHT (or EE_HANDS) */

#define BACKLIGHT_NUM 22
#define UNDERGLOW_NUM 6
#define RGBLED_NUM (BACKLIGHT_NUM + UNDERGLOW_NUM)
