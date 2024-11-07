#pragma once

// Key matrix size
#define MATRIX_ROWS 5
#define MATRIX_COLS 5

// Pin configurations
#define MATRIX_ROW_PINS { B5, B4, E6, D7, C6 }
#define MATRIX_COL_PINS { F6, F7, B1, B3, B2 }
#define DIODE_DIRECTION COL2ROW

// RGB LED configuration (adjust pins and counts as necessary)
#define RGB_DI_PIN D3
#define RGBLED_NUM 12
#define RGBLIGHT_ANIMATIONS

// Encoder configuration
#define ENCODERS_PAD_A { D2 }
#define ENCODERS_PAD_B { D3 }
#define ENCODER_RESOLUTION 4

// OLED display configuration
#define OLED_DISPLAY_128X32
#define I2C_DRIVER I2CD1
