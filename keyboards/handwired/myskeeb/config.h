#pragma once

#include "config_common.h"

// Key Matrix Size //
// Rows are Doubled-up
#define MATRIX_ROWS 10
#define MATRIX_COLS 7

// Wiring of Each Half
#define DIODE_DIRECTION COL2ROW
#define MATRIX_ROW_PINS { C6, D7, E6, B4, B5 }
#define MATRIX_COL_PINS { B6, B2, B3, B1, F6, F7, F5 }
#define MATRIX_COL_PINS_RIGHT { F5, B3, F7, B1, F6, B2, B6 }

// Comunication and Split Detection

#define SOFT_SERIAL_PIN D3
#define SELECT_SOFT_SERIAL_SPEED 1
#define SPLIT_USB_DETECT
#define EE_HANDS
#define SPLIT_USB_TIMEOUT 1000

// OLED Display Config

#define OLED_DISPLAY_128X64
#define OLED_FONT_HEIGHT 8
#define OLED_FONT_WIDTH 6
#define OLED_FONT_H "skeeb_font.c"

// Tap Dance

#define TAPPING_TERM 200

// Other

#define DEBOUNCE 0

