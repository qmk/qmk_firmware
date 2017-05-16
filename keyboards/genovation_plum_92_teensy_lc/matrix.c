#include "ch.h"
#include "hal.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "wait.h"
#include "timer.h"
static uint8_t debouncing = DEBOUNCE;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static matrix_row_t read_cols(void);
static void init_cols(void);
static void unselect_row(uint8_t row);
static void select_row(uint8_t row);

#ifdef PRINT_SCAN_PER_SECOND
static uint32_t scan_count = 0;
static uint32_t time_start = 0;
#endif

inline
uint8_t matrix_rows(void)
{
    return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void)
{
    return MATRIX_COLS;
}

void matrix_init(void)
{
    //should be in some sort of led_init function, but works fine here
    palSetPadMode(TEENSY_PIN17_IOPORT, TEENSY_PIN17, PAL_MODE_OUTPUT_PUSHPULL);
    // initialize row and col
    init_cols();
    // initialize matrix state: all keys off, rows hi-z
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        unselect_row(i);
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }
    debug_matrix = false;
}

uint8_t matrix_scan(void)
{
    #ifdef PRINT_SCAN_PER_SECOND
    if (scan_count == 10000){
        print_decs(10000000/timer_elapsed(time_start));
        print(" scans per second\n");
        scan_count = 1;
        time_start = timer_read();
    }else{
        scan_count++;
    }
    #endif
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        select_row(i);
        //chThdSleepMicroseconds(1);
        matrix_row_t cols = read_cols();
        if (matrix_debouncing[i] != cols) {
            matrix_debouncing[i] = cols;
            debouncing = DEBOUNCE;
        }
        unselect_row(i);
    }

    if (debouncing) {
        if (!(--debouncing)) {
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
                matrix[i] = matrix_debouncing[i];
            }
            //matrix_print();
        }
    }

    return 1;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & ((matrix_row_t)1<<col));
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

void matrix_print(void)
{
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        matrix_row_t data = matrix_get_row(row);
        for (int col = 0; col < MATRIX_COLS; col++) {
            if (data & (1<<col)){
                print("K");
                print_hex4(row);
                print_hex4(col);
                print(", ");
            }
        }
    }
    print("\n");
}

/* Column pin configuration
 */
static void  init_cols(void)
{
    // internal pull-up
    palSetPadMode(TEENSY_PIN8_IOPORT, TEENSY_PIN8, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(TEENSY_PIN9_IOPORT, TEENSY_PIN9, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(TEENSY_PIN10_IOPORT, TEENSY_PIN10, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(TEENSY_PIN11_IOPORT, TEENSY_PIN11, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(TEENSY_PIN12_IOPORT, TEENSY_PIN12, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(TEENSY_PIN14_IOPORT, TEENSY_PIN14, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(TEENSY_PIN15_IOPORT, TEENSY_PIN15, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(TEENSY_PIN16_IOPORT, TEENSY_PIN16, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(TEENSY_PIN18_IOPORT, TEENSY_PIN18, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(TEENSY_PIN19_IOPORT, TEENSY_PIN19, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(TEENSY_PIN20_IOPORT, TEENSY_PIN20, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(TEENSY_PIN21_IOPORT, TEENSY_PIN21, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(TEENSY_PIN22_IOPORT, TEENSY_PIN22, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(TEENSY_PIN23_IOPORT, TEENSY_PIN23, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(TEENSY_PIN24_IOPORT, TEENSY_PIN24, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(TEENSY_PIN25_IOPORT, TEENSY_PIN25, PAL_MODE_INPUT_PULLUP);
}

/* Returns status of switches(1:on, 0:off) */
static matrix_row_t read_cols(void)
{
    return ((palReadPad(TEENSY_PIN8_IOPORT, TEENSY_PIN8)==PAL_HIGH) ? 0 : (1<<0))
         | ((palReadPad(TEENSY_PIN9_IOPORT, TEENSY_PIN9)==PAL_HIGH) ? 0 : (1<<1))
         | ((palReadPad(TEENSY_PIN10_IOPORT, TEENSY_PIN10)==PAL_HIGH) ? 0 : (1<<2))
         | ((palReadPad(TEENSY_PIN11_IOPORT, TEENSY_PIN11)==PAL_HIGH) ? 0 : (1<<3))
         | ((palReadPad(TEENSY_PIN12_IOPORT, TEENSY_PIN12)==PAL_HIGH) ? 0 : (1<<4))
         | ((palReadPad(TEENSY_PIN14_IOPORT, TEENSY_PIN14)==PAL_HIGH) ? 0 : (1<<5))
         | ((palReadPad(TEENSY_PIN15_IOPORT, TEENSY_PIN15)==PAL_HIGH) ? 0 : (1<<6))
         | ((palReadPad(TEENSY_PIN16_IOPORT, TEENSY_PIN16)==PAL_HIGH) ? 0 : (1<<7))
         | ((palReadPad(TEENSY_PIN18_IOPORT, TEENSY_PIN18)==PAL_HIGH) ? 0 : (1<<8))
         | ((palReadPad(TEENSY_PIN19_IOPORT, TEENSY_PIN19)==PAL_HIGH) ? 0 : (1<<9))
         | ((palReadPad(TEENSY_PIN20_IOPORT, TEENSY_PIN20)==PAL_HIGH) ? 0 : (1<<10))
         | ((palReadPad(TEENSY_PIN21_IOPORT, TEENSY_PIN21)==PAL_HIGH) ? 0 : (1<<11))
         | ((palReadPad(TEENSY_PIN22_IOPORT, TEENSY_PIN22)==PAL_HIGH) ? 0 : (1<<12))
         | ((palReadPad(TEENSY_PIN23_IOPORT, TEENSY_PIN23)==PAL_HIGH) ? 0 : (1<<13))
         | ((palReadPad(TEENSY_PIN24_IOPORT, TEENSY_PIN24)==PAL_HIGH) ? 0 : (1<<14))
         | ((palReadPad(TEENSY_PIN25_IOPORT, TEENSY_PIN25)==PAL_HIGH) ? 0 : (1<<15));
}

/* Row pin configuration
 */
static void unselect_row(uint8_t row)
{
    (void)row;
    // Output low to select
    switch (row) {
        case 0:
            palSetPadMode(TEENSY_PIN0_IOPORT, TEENSY_PIN0, PAL_MODE_INPUT); // hi-Z
            break;
        case 1:
            palSetPadMode(TEENSY_PIN1_IOPORT, TEENSY_PIN1, PAL_MODE_INPUT); // hi-Z
            break;
        case 2:
            palSetPadMode(TEENSY_PIN2_IOPORT, TEENSY_PIN2, PAL_MODE_INPUT); // hi-Z
            break;
        case 3:
            palSetPadMode(TEENSY_PIN3_IOPORT, TEENSY_PIN3, PAL_MODE_INPUT); // hi-Z
            break;
        case 4:
            palSetPadMode(TEENSY_PIN4_IOPORT, TEENSY_PIN4, PAL_MODE_INPUT); // hi-Z
            break;
        case 5:
            palSetPadMode(TEENSY_PIN5_IOPORT, TEENSY_PIN5, PAL_MODE_INPUT); // hi-Z
            break;
        case 6:
            palSetPadMode(TEENSY_PIN6_IOPORT, TEENSY_PIN6, PAL_MODE_INPUT); // hi-Z
            break;
        case 7:
            palSetPadMode(TEENSY_PIN7_IOPORT, TEENSY_PIN7, PAL_MODE_INPUT); // hi-Z
            break;
    }
}

static void select_row(uint8_t row)
{
    (void)row;
    // Output low to select
    switch (row) {
        case 0:
            palSetPadMode(TEENSY_PIN0_IOPORT, TEENSY_PIN0, PAL_MODE_OUTPUT_PUSHPULL);
            palClearPad(TEENSY_PIN0_IOPORT, TEENSY_PIN0);
            break;
        case 1:
            palSetPadMode(TEENSY_PIN1_IOPORT, TEENSY_PIN1, PAL_MODE_OUTPUT_PUSHPULL);
            palClearPad(TEENSY_PIN1_IOPORT, TEENSY_PIN1);
            break;
        case 2:
            palSetPadMode(TEENSY_PIN2_IOPORT, TEENSY_PIN2, PAL_MODE_OUTPUT_PUSHPULL);
            palClearPad(TEENSY_PIN2_IOPORT, TEENSY_PIN2);
            break;
        case 3:
            palSetPadMode(TEENSY_PIN3_IOPORT, TEENSY_PIN3, PAL_MODE_OUTPUT_PUSHPULL);
            palClearPad(TEENSY_PIN3_IOPORT, TEENSY_PIN3);
            break;
        case 4:
            palSetPadMode(TEENSY_PIN4_IOPORT, TEENSY_PIN4, PAL_MODE_OUTPUT_PUSHPULL);
            palClearPad(TEENSY_PIN4_IOPORT, TEENSY_PIN4);
            break;
        case 5:
            palSetPadMode(TEENSY_PIN5_IOPORT, TEENSY_PIN5, PAL_MODE_OUTPUT_PUSHPULL);
            palClearPad(TEENSY_PIN5_IOPORT, TEENSY_PIN5);
            break;
        case 6:
            palSetPadMode(TEENSY_PIN6_IOPORT, TEENSY_PIN6, PAL_MODE_OUTPUT_PUSHPULL);
            palClearPad(TEENSY_PIN6_IOPORT, TEENSY_PIN6);
            break;
        case 7:
            palSetPadMode(TEENSY_PIN7_IOPORT, TEENSY_PIN7, PAL_MODE_OUTPUT_PUSHPULL);
            palClearPad(TEENSY_PIN7_IOPORT, TEENSY_PIN7);
            break;
    }
}
