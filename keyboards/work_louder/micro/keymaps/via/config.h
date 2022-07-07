#pragma once

#undef MATRIX_ROWS
#define MATRIX_ROWS 5
#undef MATRIX_ROW_PINS
#define MATRIX_ROW_PINS { F1, F4, F5, F6, NO_PIN }

#define ENCODERS 2

#define ENCODERS_CW_KEY \
    {                   \
        { 2, 4 }, {0,4 } \
    }
#define ENCODERS_CCW_KEY \
    {                    \
        { 3, 4 }, {1, 4} \
    }
