#include QMK_KEYBOARD_H
#include "config.h"

// could probably be just 1us, but let's start here
#define CLOCK_WAIT_US 3
#define CLOCK_PIN D7
#define DATA_PIN B4
static uint8_t const column_pins[] = { F0, F1, F4, F5, F6, F7, B6, B5 };
#define K24_LED_PIN D3
#define K25_LED_PIN C6
#define K28_LED_PIN C7

void matrix_init_custom(void) {
  xprintf("matrix_init_custom() called");
  setPinOutput(DATA_PIN);
  setPinOutput(CLOCK_PIN);
  
  writePinHigh(DATA_PIN);
  writePinLow(CLOCK_PIN);
  for (uint8_t i = 0; i < MATRIX_COLS; ++i) {
    setPinInputHigh(column_pins[i]);
  }
  
  // fill out the shift registers with high bits
  for (uint8_t i=0; i<24; ++i) {
    // With data high, clock 3*8 times to fill the shift registers
    writePinHigh(CLOCK_PIN);
    wait_us(CLOCK_WAIT_US);
    writePinLow(CLOCK_PIN);
    wait_us(CLOCK_WAIT_US);
  }
  
  // enable once these pins have 220 or 470 ohm resistors inline
  // writePinLow(); to turn on LED if I have it right
  #if 0
	  setPinOutput(K24_LED_PIN);
	  writePinHigh(K24_LED_PIN);
	  setPinOutput(K25_LED_PIN);
	  writePinHigh(K25_LED_PIN);
	  setPinOutput(K28_LED_PIN);
	  writePinHigh(K28_LED_PIN);
  #endif
}

static matrix_row_t read_cols(void) {
  // Could be made faster by using the input registers but
  // let's be sure it works and is easy to read first
  matrix_row_t row = 0;
  for (uint8_t i = 0; i < MATRIX_COLS; ++i) {
    // pin is 0 if switch was pressed
    row |= readPin(column_pins[i]) ? 0 : (1UL << i);
  }
  return row;
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
  bool matrix_has_changed = false;

  // Clock in a single 0 into the first shift register
  writePinLow(DATA_PIN);
  writePinHigh(CLOCK_PIN);
  wait_us(CLOCK_WAIT_US);
  writePinHigh(DATA_PIN);
  writePinLow(CLOCK_PIN);
  wait_us(CLOCK_WAIT_US);

  for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
    // read whole row, set flag if different from value for current row
    matrix_row_t new_row_value = read_cols();
    matrix_has_changed |= (new_row_value != current_matrix[current_row]);
    current_matrix[current_row] = new_row_value;
    // Tick the clock once to move the 0 to the next row
    writePinHigh(CLOCK_PIN);
    wait_us(CLOCK_WAIT_US);
    writePinLow(CLOCK_PIN);
    wait_us(CLOCK_WAIT_US);
  }

  return matrix_has_changed;
}
