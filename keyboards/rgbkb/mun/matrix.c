/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <https://github.com/KarlK90> wrote this file.  As long as you retain this
 * notice you can do whatever you want with this stuff. If we meet some day, and
 * you think this stuff is worth it, you can buy me a beer in return. KarlK90
 * ----------------------------------------------------------------------------
 */

#include "matrix.h"
#include "atomic_util.h"
#include "gpio.h"

#define ROWS_PER_HAND (MATRIX_ROWS / 2)
static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS]   = MATRIX_COL_PINS;

void matrix_init_pins(void) {
    for (size_t i = 0; i < MATRIX_COLS; i++) {
        setPinInputHigh(col_pins[i]);
    }
    for (size_t i = 0; i < ROWS_PER_HAND; i++) {
        setPinOutput(row_pins[i]);
        writePinHigh(row_pins[i]);
    }
}

void matrix_read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    /* Drive row pin low. */
    ATOMIC_BLOCK_FORCEON { writePinLow(row_pins[current_row]); }
    matrix_output_select_delay();

    /* Read all columns in one go, aka port scanning. */
    uint16_t porta = palReadPort(GPIOA);
    uint16_t portb = palReadPort(GPIOB);

// clang-format off
    /* Order of pins on the mun is: A0, B11, B0, B10, B12, B2, A8
        Pin is active low, therefore we have to invert the result. */
    matrix_row_t cols = ~(((porta & (0x1 <<  0)) >>  0)   // A0  (0)
                        | ((portb & (0x1 << 11)) >> 10)   // B11 (1)
                        | ((portb & (0x1 <<  0)) <<  2)   // B0  (2)
                        | ((portb & (0x1 << 10)) >>  7)   // B10 (3)
                        | ((portb & (0x1 << 12)) >>  8)   // B12 (4)
                        | ((portb & (0x1 <<  2)) <<  3)   // B2  (5)
                        | ((porta & (0x1 <<  8)) >>  2)); // A8  (6)
// clang-format on

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

    current_matrix[current_row] = cols;

    /* Drive row pin high again. */
    ATOMIC_BLOCK_FORCEON { writePinHigh(row_pins[current_row]); }
    matrix_output_unselect_delay(current_row, cols != 0);
}

#if defined(BUSY_WAIT)
void matrix_output_unselect_delay(uint8_t line, bool key_pressed) {
    for (int32_t i = 0; i < BUSY_WAIT_INSTRUCTIONS; i++) {
        __asm__ volatile("nop" ::: "memory");
    }
}
#endif
