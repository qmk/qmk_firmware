#ifndef CLUEBOARD_66_REV1_CONFIG_H
#define CLUEBOARD_66_REV1_CONFIG_H

#include "config_common.h"

#define PRODUCT_ID      0x2301
#define DEVICE_VER      0x0003

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16

// ROWS: Top to bottom, COLS: Left to right
/* Column pin configuration
* col: 0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15
* pin: B3 F1 F4 F5 F6 C7 C6 B6 B5 B4 D7 D6 D4 F7 B0 B1
*/
#define MATRIX_COL_PINS { B3, F1, F4, F5, F6, C7, C6, B6, B5, B4, D7, D6, D4, F7, B0, B1 }
/* Row pin configuration
* row: 0  1  2  3  4
* pin: D1 D0 D2 D5 D3
*/
#define MATRIX_ROW_PINS { D1, D0, D2, D5, D3 }
#define UNUSED_PINS

/* Underlight configuration
 */
#define RGB_DI_PIN B2
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 14     // Number of LEDs
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17


#endif
