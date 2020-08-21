#pragma once

#define PRODUCT         Corne Keyboard Rev.1 (Split Common)

#define USE_SERIAL
#define SOFT_SERIAL_PIN D2

#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_SPLIT { 27, 27 }
#endif

#define DIODE_DIRECTION COL2ROW
