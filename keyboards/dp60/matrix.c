#include "quantum.h"

static uint8_t debouncing = DEBOUNCE;

static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static uint8_t read_rows(void);
static void init_rows(void);
static void init_cols(void);
static void unselect_cols(void);
static void select_col(uint8_t col);


__attribute__ ((weak))
void matrix_init_kb(void)
{
}

__attribute__ ((weak))
void matrix_scan_kb(void)
{
}

__attribute__ ((weak))
void matrix_init_user(void) {}

__attribute__ ((weak))
void matrix_scan_user(void) {}

void matrix_init(void)
{
  //setPinOutput(F0);
  //writePinHigh(F0);
  setPinOutput(B4);
  writePinLow(B4);

  init_cols();
  init_rows();

  for (uint8_t i=0; i < MATRIX_ROWS; i++)  {
    matrix[i] = 0;
    matrix_debouncing[i] = 0;
  }

  matrix_init_quantum();
}

uint8_t matrix_scan(void)
{
  for (uint8_t col = 0; col < MATRIX_COLS; col++) {
    select_col(col);
    _delay_us(3);

    uint8_t rows = read_rows();

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
      bool prev_bit = matrix_debouncing[row] & ((matrix_row_t)1<<col);
      bool curr_bit = rows & (1<<row);
      if (prev_bit != curr_bit) {
        matrix_debouncing[row] ^= ((matrix_row_t)1<<col);
        debouncing = DEBOUNCE;
      }
    }
    unselect_cols();
  }

  if (debouncing) {
    if (--debouncing) {
      _delay_ms(1);
    } else {
      for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        matrix[i] = matrix_debouncing[i];
      }
    }
  }

  matrix_scan_quantum();
  return 1;
}

inline matrix_row_t matrix_get_row(uint8_t row)
{
  return matrix[row];
}

void matrix_print(void)
{
  print("\nr/c 0123456789ABCDEF\n");
  for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
    xprintf("%02X: %032lb\n", row, bitrev32(matrix_get_row(row)));
  }
}

/*
 * Row pin configuration
 * row: 0    1    2    3    4
 * pin: PE6  PF6  PF7  PB7  PD4
 */
static void init_rows(void)
{
  setPinInputHigh(E6);
  setPinInputHigh(F6);
  setPinInputHigh(F7);
  setPinInputHigh(B7);
  setPinInputHigh(D4);
}

static uint8_t read_rows()
{
  return ((readPin(E6) ? 0 : (1 << 0)) |
          (readPin(F6) ? 0 : (1 << 1)) |
          (readPin(F7) ? 0 : (1 << 2)) |
          (readPin(B7) ? 0 : (1 << 3)) |
          (readPin(D4) ? 0 : (1 << 4)));
}

/*
 * Columns 0 - 13
 * These columns uses two 74LVC138 3 to 8 bit demultiplexers.
 * EN Pin, PF5, PD6
 *
 * col / pin:    PF0  PF1  PF4
 * 0:             0    0    0
 * 1:             1    0    0
 * 2:             0    1    0
 * 3:             1    1    0
 * 4:             0    0    1
 * 5:             1    0    1
 * 6:             0    1    1
 *               PD2  PD3  PD5
 * 7:             0    0    0
 * 8:             1    0    0
 * 9:             0    1    0
 * 10:            1    1    0
 * 11:            0    0    1
 * 12:            1    0    1
 * 13:            0    1    1
 *
 */
static void init_cols(void)
{
  setPinOutput(F0);
  setPinOutput(F1);
  setPinOutput(F4);
  setPinOutput(F5);

  setPinOutput(D2);
  setPinOutput(D3);
  setPinOutput(D5);
  setPinOutput(D6);

  unselect_cols();
}

static void unselect_cols(void)
{
  writePinHigh(F0);
  writePinHigh(F1);
  writePinHigh(F4);
  writePinHigh(F5);

  writePinHigh(D2);
  writePinHigh(D3);
  writePinHigh(D5);
  writePinHigh(D6);
}

static void select_col(uint8_t col) {

   switch (col) {
        case 0:
          writePinLow(F0);
          writePinLow(F1);
          writePinLow(F4);
          break;
        case 1:
          writePinHigh(F0);
          writePinLow(F1);
          writePinLow(F4);
          break;
        case 2:
          writePinLow(F0);
          writePinHigh(F1);
          writePinLow(F4);
          break;
        case 3:
          writePinHigh(F0);
          writePinHigh(F1);
          writePinLow(F4);
          break;
        case 4:
          writePinLow(F0);
          writePinLow(F1);
          writePinHigh(F4);
          break;
        case 5:
          writePinHigh(F0);
          writePinLow(F1);
          writePinHigh(F4);
          break;
        case 6:
          writePinLow(F0);
          writePinHigh(F1);
          writePinHigh(F4);
          break;
        case 7:
          writePinLow(D2);
          writePinLow(D3);
          writePinLow(D5);
          break;
        case 8:
          writePinHigh(D2);
          writePinLow(D3);
          writePinLow(D5);
          break;
        case 9:
          writePinLow(D2);
          writePinHigh(D3);
          writePinLow(D5);
          break;
        case 10:
          writePinHigh(D2);
          writePinHigh(D3);
          writePinLow(D5);
          break;
        case 11:
          writePinLow(D2);
          writePinLow(D3);
          writePinHigh(D5);
          break;
        case 12:
          writePinHigh(D2);
          writePinLow(D3);
          writePinHigh(D5);
          break;
        case 13:
          writePinLow(D2);
          writePinHigh(D3);
          writePinHigh(D5);
          break;
    }
}
