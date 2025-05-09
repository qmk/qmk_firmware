/*
 * matrix.c testing macros
 *   MATRIX_DEBUG_SCAN:  Measuring execution time of `matrix_scan()`
 *   MATRIX_DEBUG_DELAY: Observation of delay after `unselect_row()`
 */
#pragma once
#ifndef __ASSEMBLER__
#include <gpio.h>

static inline void setDebugPinOutput_Low(void) {
    gpio_set_pin_output(MATRIX_DEBUG_PIN);
    gpio_write_pin_low(MATRIX_DEBUG_PIN);
}

#define MATRIX_DEBUG_PIN_INIT()   setDebugPinOutput_Low()

#ifdef MATRIX_DEBUG_SCAN
#  define MATRIX_DEBUG_SCAN_START() gpio_write_pin_high(MATRIX_DEBUG_PIN)
#  define MATRIX_DEBUG_SCAN_END()   gpio_write_pin_low(MATRIX_DEBUG_PIN)
#else
#  define MATRIX_DEBUG_SCAN_START()
#  define MATRIX_DEBUG_SCAN_END()
#endif

#ifdef MATRIX_DEBUG_DELAY
#  define MATRIX_DEBUG_DELAY_START() gpio_write_pin_high(MATRIX_DEBUG_PIN)
#  define MATRIX_DEBUG_DELAY_END()   gpio_write_pin_low(MATRIX_DEBUG_PIN)
#else
#  define MATRIX_DEBUG_DELAY_START()
#  define MATRIX_DEBUG_DELAY_END()
#endif

#endif // __ASSEMBLER__
