#pragma once

#define BACKLIGHT_LEVELS 8

#define LED_MATRIX_ROWS 5
#define LED_MATRIX_COLS 14

#define DRIVER_LED_TOTAL 61

/* Limit animations to 62.5 FPS to avoid tearing. (1/.016 = 62.5 FPS). */
#define RGB_MATRIX_LED_FLUSH_LIMIT 16
