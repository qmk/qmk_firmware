/*
 * matrix.c testing macros
 *   MATRIX_DEBUG_SCAN:  Measuring execution time of `matrix_scan()`
 *   MATRIX_DEBUG_DELAY: Observation of delay after `unselect_row()`
 */
#pragma once
#ifndef __ASSEMBLER__

#define _GET_ITEM_1(_1, ...) _1
#define _GET_ITEM_2(_1,_2, ...) _2
#define GET_ITEM_1(...) _GET_ITEM_1(__VA_ARGS__)
#define GET_ITEM_2(...) _GET_ITEM_2(__VA_ARGS__)

#ifdef MATRIX_DEBUG_SCAN
#    define MATRIX_DEBUG_SCAN_PIN     GET_ITEM_1(MATRIX_DEBUG_PIN)
#    define MATRIX_DEBUG_SCAN_PIN_INIT() setPinOutput(MATRIX_DEBUG_SCAN_PIN);  writePinLow(MATRIX_DEBUG_SCAN_PIN);
#    define MATRIX_DEBUG_SCAN_START() writePinHigh(MATRIX_DEBUG_SCAN_PIN)
#    define MATRIX_DEBUG_SCAN_END()   writePinLow(MATRIX_DEBUG_SCAN_PIN)
#    define MATRIX_DEBUG_WAIT(x)      wait_cpuclock(x)
#else
#    define MATRIX_DEBUG_SCAN_PIN_INIT()
#endif

#ifdef MATRIX_DEBUG_DELAY
#    define MATRIX_DEBUG_DELAY_PIN     GET_ITEM_2(MATRIX_DEBUG_PIN)
#    define MATRIX_DEBUG_DELAY_PIN_INIT()  setPinOutput(MATRIX_DEBUG_DELAY_PIN);  writePinLow(MATRIX_DEBUG_DELAY_PIN);
#    define MATRIX_DEBUG_DELAY_START() writePinHigh(MATRIX_DEBUG_DELAY_PIN)
#    define MATRIX_DEBUG_DELAY_END()   writePinLow(MATRIX_DEBUG_DELAY_PIN)
#    define MATRIX_DEBUG_WAIT(x)      wait_cpuclock(x)
#else
#    define MATRIX_DEBUG_DELAY_PIN_INIT()
#endif

#define MATRIX_DEBUG_PIN_INIT()   MATRIX_DEBUG_DELAY_PIN_INIT(); MATRIX_DEBUG_SCAN_PIN_INIT()

#endif // __ASSEMBLER__
