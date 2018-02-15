#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "hal.h"
#include "timer.h"
#include "wait.h"
#include "printf.h"
#include "backlight.h"
#include "matrix.h"

#include "usb_main.h"
#include "twi2c.h"

/* QMK Handwire
 *
 * Column pins are input with internal pull-down.
 * Row pins are output and strobe with high.
 * Key is high or 1 when it turns on.
 *
 *     col: { A13, A14, A15, B3, B4, B5, B6 }
 *     row: { B10, B2, B1, B0, A7, A6 }
 */
/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];
static bool debouncing = false;
static uint16_t debouncing_time = 0;

static bool master = false;
static bool right_hand = false;

__attribute__ ((weak))
void matrix_init_user(void) {}

__attribute__ ((weak))
void matrix_scan_user(void) {}

__attribute__ ((weak))
void matrix_init_kb(void) {
  matrix_init_user();
}

__attribute__ ((weak))
void matrix_scan_kb(void) {
  matrix_scan_user();
}

void matrix_init(void) {
    printf("matrix init\n");
    // debug_matrix = true;

    // C13 is connected to VCC on the right hand
    palSetPadMode(GPIOC, 13, PAL_MODE_INPUT);
    wait_us(20);
    right_hand = palReadPad(GPIOC, 13);

    // if USB is active, this is the master
    // master = usbGetDriverStateI(&USB_DRIVER) == USB_ACTIVE;
    master = right_hand;

    if (master) {
      twi2c_master_init();
    } else {
      twi2c_slave_init();
    }

    /* Column(sense) */
    palSetPadMode(GPIOA, 13, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOA, 14, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOA, 15, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 3,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 4,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 5,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 6,  PAL_MODE_INPUT_PULLDOWN);

    /* Row(strobe) */
    palSetPadMode(GPIOB, 10, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 2,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 1,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 0,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOA, 7,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOA, 6,  PAL_MODE_OUTPUT_PUSHPULL);

    memset(matrix, 0, MATRIX_ROWS * sizeof(matrix_row_t));
    memset(matrix_debouncing, 0, MATRIX_ROWS * sizeof(matrix_row_t));

    // palClearPad(GPIOB, 7);  // Turn off capslock
    matrix_init_quantum();
}

matrix_row_t matrix_scan_common(uint8_t row) {
  matrix_row_t data;

  // strobe row { A6, A7, B0, B1, B2, B10 }
  switch (row) {
      case 5: palSetPad(GPIOA, 6); break;
      case 4: palSetPad(GPIOA, 7); break;
      case 3: palSetPad(GPIOB, 0); break;
      case 2: palSetPad(GPIOB, 1); break;
      case 1: palSetPad(GPIOB, 2); break;
      case 0: palSetPad(GPIOB, 10); break;
  }

  // need wait to settle pin state
  wait_us(20);

  // read col data {  B6, B5, B4, B3, A15, A14, A13 }
  data = (
      (palReadPad(GPIOB, 6)  << 6 ) |
      (palReadPad(GPIOB, 5)  << 5 ) |
      (palReadPad(GPIOB, 4)  << 4 ) |
      (palReadPad(GPIOB, 3)  << 3 ) |
      (palReadPad(GPIOA, 15) << 2 ) |
      (palReadPad(GPIOA, 14) << 1 ) |
      (palReadPad(GPIOA, 13) << 0 )
  );

  // unstrobe row { A6, A7, B0, B1, B2, B10 }
  switch (row) {
      case 5: palClearPad(GPIOA, 6); break;
      case 4: palClearPad(GPIOA, 7); break;
      case 3: palClearPad(GPIOB, 0); break;
      case 2: palClearPad(GPIOB, 1); break;
      case 1: palClearPad(GPIOB, 2); break;
      case 0: palClearPad(GPIOB, 10); break;
  }

  return data;
}

const uint8_t command[2] = { 0x01, 0x00 };
uint8_t other_matrix[MATRIX_ROWS] = { 0 };

void matrix_scan_master(void) {

  msg_t resp;
  resp = twi2c_master_send(slaveI2Caddress/2, command, other_matrix, TIME_IMMEDIATE);
  // printf("%x\n", resp);

  if (resp == MSG_OK) {
    uint8_t * matrix_pointer;
    if (right_hand) {
      matrix_pointer = matrix;
    } else {
      matrix_pointer = matrix + (MATRIX_ROWS / 2);
    }

    memcpy(matrix_pointer, other_matrix, MATRIX_ROWS / 2);
  }
}

uint8_t matrix_scan(void) {

    for (int row = 0; row < MATRIX_ROWS; row++) {
        matrix_row_t data = 0;

        if ((right_hand && row >= 6) || (!right_hand && row < 6)) {
          data = matrix_scan_common(row % 6);
        }

        if (matrix_debouncing[row] != data) {
            matrix_debouncing[row] = data;
            debouncing = true;
            debouncing_time = timer_read();
        }
    }

    if (debouncing && timer_elapsed(debouncing_time) > DEBOUNCE) {
        for (int row = 0; row < MATRIX_ROWS; row++) {
            matrix[row] = matrix_debouncing[row];
        }
        debouncing = false;
    }

    if (master) {
      matrix_scan_master();
    }

    matrix_scan_quantum();

    return 1;
}

bool matrix_is_on(uint8_t row, uint8_t col) {
    return (matrix[row] & (1<<col));
}

matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}

void matrix_copy(matrix_row_t * copy) {
  uint8_t * matrix_pointer;
  if (right_hand) {
    matrix_pointer = matrix + (MATRIX_ROWS / 2);
  } else {
    matrix_pointer = matrix;
  }
  memcpy(copy, matrix_pointer, MATRIX_ROWS / 2);
}

void matrix_print(void) {
    printf("\nr/c 01234567\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        printf("%X0: ", row);
        matrix_row_t data = matrix_get_row(row);
        for (int col = 0; col < MATRIX_COLS; col++) {
            if (data & (1<<col))
                printf("1");
            else
                printf("0");
        }
        printf("\n");
    }
}
