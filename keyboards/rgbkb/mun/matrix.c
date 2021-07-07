/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <https://github.com/KarlK90> wrote this file.  As long as you retain this
 * notice you can do whatever you want with this stuff. If we meet some day, and
 * you think this stuff is worth it, you can buy me a beer in return. KarlK90
 * ----------------------------------------------------------------------------
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "util.h"
#include "matrix.h"
#include "debounce.h"
#include "quantum.h"
#include "split_util.h"
#include "config.h"
#include "transactions.h"

#define ERROR_DISCONNECT_COUNT 5
#define ROWS_PER_HAND (MATRIX_ROWS / 2)

static const pin_t row_pins[ROWS_PER_HAND] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS]   = MATRIX_COL_PINS;

/* matrix state(1:on, 0:off) */
extern matrix_row_t raw_matrix[MATRIX_ROWS];  // raw values
extern matrix_row_t matrix[MATRIX_ROWS];      // debounced values

// row offsets for each hand
uint8_t thisHand, thatHand;

// user-defined overridable functions
__attribute__((weak)) void matrix_slave_scan_kb(void) { matrix_slave_scan_user(); }
__attribute__((weak)) void matrix_slave_scan_user(void) {}

static void init_pins(void) {
    for (size_t i = 0; i < MATRIX_COLS; i++) {
        setPinInputHigh(col_pins[i]);
    }
    for (size_t i = 0; i < ROWS_PER_HAND; i++) {
        setPinOutput(row_pins[i]);
        writePinHigh(row_pins[i]);
    }
}

void matrix_init(void) {
    split_pre_init();

    thisHand = isLeftHand ? 0 : (ROWS_PER_HAND);
    thatHand = ROWS_PER_HAND - thisHand;

    // initialize key pins
    init_pins();

    // initialize matrix state: all keys off
    memset(raw_matrix, 0, sizeof(raw_matrix));
    memset(matrix, 0, sizeof(matrix));

    debounce_init(ROWS_PER_HAND);

    matrix_init_quantum();

    split_post_init();
}

bool matrix_post_scan(void) {
    bool changed = false;
    if (is_keyboard_master()) {
        static uint8_t error_count;

        matrix_row_t slave_matrix[ROWS_PER_HAND] = {0};
        if (!transport_master(matrix + thisHand, slave_matrix)) {
            error_count++;

            if (error_count > ERROR_DISCONNECT_COUNT) {
                // reset other half if disconnected
                memset(&matrix[thatHand], 0, sizeof(slave_matrix));
                memset(slave_matrix, 0, sizeof(slave_matrix));

                changed = true;
            }
        } else {
            error_count = 0;

            if (memcmp(&matrix[thatHand], slave_matrix, sizeof(slave_matrix)) != 0) {
                memcpy(&matrix[thatHand], slave_matrix, sizeof(slave_matrix));
                changed = true;
            }
        }

        matrix_scan_quantum();
    } else {
        transport_slave(matrix + thatHand, matrix + thisHand);

        matrix_slave_scan_kb();
    }

    return changed;
}

uint8_t matrix_scan(void) {
    bool         local_changed = false;
    matrix_row_t current_matrix[ROWS_PER_HAND];

    for (size_t row_idx = 0; row_idx < ROWS_PER_HAND; row_idx++) {
        /* Drive row pin low. */
        ATOMIC_BLOCK_FORCEON { writePinLow(row_pins[row_idx]); }
        matrix_output_select_delay();

        /* Read all columns in one go, aka port scanning. */
        uint16_t porta = palReadPort(GPIOA);
        uint16_t portb = palReadPort(GPIOB);

        /* Order of pins on the mun is: A0, B11, B0, B10, B12, B2, A8
           Pin is active low, therefore we have to invert the result. */
        matrix_row_t cols = ~(((porta & (0x1 << 0)) >> 0)      // A0 (0)
                              | ((portb & (0x1 << 11)) >> 10)  // B11 (1)
                              | ((portb & (0x1 << 0)) << 2)    // B0 (2)
                              | ((portb & (0x1 << 10)) >> 7)   // B10 (3)
                              | ((portb & (0x1 << 12)) >> 8)   // B12 (4)
                              | ((portb & (0x1 << 2)) << 3)    // B2 (5)
                              | ((porta & (0x1 << 8)) >> 2));  // A8 (6)

        /* Reverse the order of columns for left hand as the board is flipped. */
        //         if (isLeftHand) {
        // #if defined(__arm__)
        //             /* rbit assembly reverses bit order of 32bit registers. */
        //             uint32_t temp = cols;
        //             __asm__("rbit %0, %1" : "=r"(temp) : "r"(temp));
        //             cols = temp >> 24;
        // #else
        //             /* RISC-V bit manipulation extension not present. Use bit-hack.
        //             https://graphics.stanford.edu/~seander/bithacks.html#ReverseByteWith32Bits */
        //             cols = (matrix_row_t)(((cols * 0x0802LU & 0x22110LU) | (cols * 0x8020LU & 0x88440LU)) * 0x10101LU >> 16);
        // #endif
        //         }

        current_matrix[row_idx] = cols;

        /* Drive row pin high again. */
        ATOMIC_BLOCK_FORCEON { writePinHigh(row_pins[row_idx]); }
        matrix_output_unselect_delay();
    }

    if (memcmp(raw_matrix, current_matrix, sizeof(current_matrix)) != 0) {
        memcpy(raw_matrix, current_matrix, sizeof(current_matrix));
        local_changed = true;
    }

    debounce(raw_matrix, matrix + thisHand, ROWS_PER_HAND, local_changed);

    bool remote_changed = matrix_post_scan();
    return (uint8_t)(local_changed || remote_changed);
}