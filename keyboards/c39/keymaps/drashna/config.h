#pragma once

// place overrides here
#undef MATRIX_COL_PINS
#define MATRIX_COL_PINS \
    { A3, A2, A1, A0, B13, B14, B15, B9, B3, B2, B4, A10, A9 }
#undef MATRIX_ROW_PINS
#define MATRIX_ROW_PINS \
    { B7, B1, B0 }

#define RGB_DI_PIN B10
#define RGBLED_NUM 15

#define SOLENOID_PIN B11
