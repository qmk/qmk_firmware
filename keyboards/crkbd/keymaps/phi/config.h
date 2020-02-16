#pragma once

/* split keyboard setup */
#define USE_SERIAL              /* SERIAL or MATRIX_I2C */
#define USE_SERIAL_PD2
#define MASTER_LEFT             /* LEFT or RIGHT (or EE_HANDS) */

/* OLED setup */
#define USE_I2C
#define SSD1306OLED

#undef RGBLED_NUM
#define RGBLED_NUM 5
