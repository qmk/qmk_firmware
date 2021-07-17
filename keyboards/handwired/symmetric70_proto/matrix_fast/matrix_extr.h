#pragma once
// clang-format off

#define DIRECT_SWITCH 1
#define DIODE_ROW2COL 2
#define DIODE_COL2ROW 3

#ifndef ROW2COL
#    define COL2ROW 0
#    define ROW2COL 1
#endif

#ifdef DIRECT_PINS
#    define MATRIX_TYPE DIRECT_SWITCH
#else
#    if DIODE_DIRECTION == ROW2COL
#        define MATRIX_TYPE DIODE_ROW2COL
#    endif
#    if DIODE_DIRECTION == COL2ROW
#        define MATRIX_TYPE DIODE_COL2ROW
#    endif
#endif

#ifndef MATRIX_TYPE
#   error "MATRIX_TYPE could not be determined."
#endif

#if (MATRIX_ROWS <= 8)
typedef uint8_t matrix_col_t;
#elif (MATRIX_ROWS <= 16)
typedef uint16_t matrix_col_t;
#elif (MATRIX_ROWS <= 32)
typedef uint32_t matrix_col_t;
#else
#    error "MATRIX_ROWS: invalid value"
#endif
