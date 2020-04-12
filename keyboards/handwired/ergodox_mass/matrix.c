/* Copyright 2018 Andrew Mass
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "matrix.h"

#include "debounce.h"
#include "quantum.h"

typedef enum {
  R0 = 0,
  R1 = 1,
  R2 = 2,
  L0 = 3,
  L1 = 4,
  L2 = 5
} GPIOChip_t;

#define SS  B0
#define SCK B1
#define SDO B2
#define SDI B3

// Forward declarations
void spi_init(void);
uint8_t spi_send(uint8_t byte);
uint8_t gpx_control_byte(GPIOChip_t idx, bool read);
uint16_t gpx_read_reg(GPIOChip_t idx, uint8_t addr);
void gpx_write_reg(GPIOChip_t idx, uint8_t addr, uint16_t val);

// GPIO Expander Register Addresses
#define GPX_IODIR   0x00
#define GPX_IPOL    0x02
#define GPX_GPINTEN 0x04
#define GPX_DEFVAL  0x06
#define GPX_INTCON  0x08
#define GPX_IOCON   0x0A
#define GPX_GPPU    0x0C
#define GPX_INTF    0x0E
#define GPX_INTCAP  0x10
#define GPX_GPIO    0x12
#define GPX_OLAT    0x14

// Store raw and debounced switch state
static matrix_row_t raw_matrix[MATRIX_ROWS];
static matrix_row_t deb_matrix[MATRIX_ROWS];

/**
 * Define weak empty shells for these functions in case they don't get defined elsewhere
 */

__attribute__ ((weak))
void matrix_init_quantum(void) {
  matrix_init_kb();
}

__attribute__ ((weak))
void matrix_scan_quantum(void) {
  matrix_scan_kb();
}

__attribute__ ((weak))
void matrix_init_kb(void) {
  matrix_init_user();
}

__attribute__ ((weak))
void matrix_scan_kb(void) {
  matrix_scan_user();
}

__attribute__ ((weak))
void matrix_init_user(void) {
}

__attribute__ ((weak))
void matrix_scan_user(void) {
}

/**
 * Define matrix functions
 */

inline
bool matrix_is_on(uint8_t row, uint8_t col) {
  return (deb_matrix[row] & (matrix_row_t)(1 << col));
}

inline
matrix_row_t matrix_get_row(uint8_t row) {
  return deb_matrix[row];
}

inline
void matrix_print(void) {}

/**
 * Initialize the matrix reading circuitry. Called once at the start
 */
void matrix_init(void) {
  for (uint8_t i = 0; i < MATRIX_ROWS; ++i) {
    raw_matrix[i] = 0;
    deb_matrix[i] = 0;
  }

  debounce_init(MATRIX_ROWS);

  spi_init();

  // Initialize all GPIO expanders
  for (int i = R0; i <= L2; ++i) {
    gpx_write_reg(i, GPX_IODIR, 0xFFFF); // Inputs
    gpx_write_reg(i, GPX_IPOL,  0xFFFF); // Flip polarity
    gpx_write_reg(i, GPX_GPPU,  0xFFFF); // Enable pullups
    gpx_write_reg(i, GPX_IOCON, 0x0808); // Defaults, but enable hardware addressing
  }

  matrix_init_quantum();
}

/**
 * Read the matrix. Called continuously
 */
uint8_t matrix_scan(void) {
  bool rawChanged = false;

  for (int i = R0; i <= L2; ++i) {
    // A Bank: Upper 8 bits, odd matrix rows
    // B Bank: Lower 8 bits, even matrix rows
    uint16_t gpio = gpx_read_reg(i, GPX_GPIO);

    rawChanged |= (raw_matrix[i*2] != (gpio & 0xFF));
    raw_matrix[i*2] = gpio & 0xFF;

    rawChanged |= (raw_matrix[i*2+1] != ((gpio >> 8) & 0xFF));
    raw_matrix[i*2+1] = (gpio >> 8) & 0xFF;
  }

  debounce(raw_matrix, deb_matrix, MATRIX_ROWS, rawChanged);

  matrix_scan_quantum();

  return (uint8_t) rawChanged;
}

/**
 * Initialize the SPI bus
 */
void spi_init(void) {
  // Disable power saving
  PRR0 &= ~(1<<2); // PRSPI

  // Initialize SPI pins
  setPinOutput(SS);
  writePinHigh(SS);
  setPinOutput(SCK);
  setPinOutput(SDO);
  setPinInput(SDI);

  // Initialize SPCR register
  SPCR &= ~(1<<7); // SPIE (No interrupts)
  SPCR &= ~(1<<5); // DORD (MSB first)
  SPCR |= (1<<4); // MSTR (SPI Master)
  SPCR &= ~(1<<3); // CPOL (Mode 0)
  SPCR &= ~(1<<2); // CPHA (Mode 0)
  SPCR &= ~(0b11<<0); // SCK Frequency (F_osc / 4)

  // Enable SPI
  SPCR |= (1<<6); // SPE
}

/**
 * SPI functions
 */

uint8_t spi_send(uint8_t byte) {
  SPDR = byte;
  while (!(SPSR & (1<<7))); // Wait for transmission
  return SPDR;
}

/**
 * GPIO expander fucntions
 */

uint8_t gpx_control_byte(GPIOChip_t idx, bool read) {
  uint8_t control = 0b01000000;
  switch (idx) {
    case R0: control |= 0b0010; break;
    case R1: control |= 0b0100; break;
    case R2: control |= 0b0110; break;
    case L0: control |= 0b1000; break;
    case L1: control |= 0b1010; break;
    case L2: control |= 0b1100; break;
  }
  if (read)
    control |= 0b1;
  return control;
}

uint16_t gpx_read_reg(GPIOChip_t idx, uint8_t addr) {
  writePinLow(SS);

  spi_send(gpx_control_byte(idx, true));
  spi_send(addr);
  uint8_t resp1 = spi_send(0x00);
  uint8_t resp2 = spi_send(0x00);

  writePinHigh(SS);

  return resp1 << 8 | resp2;
}

void gpx_write_reg(GPIOChip_t idx, uint8_t addr, uint16_t val) {
  writePinLow(SS);

  spi_send(gpx_control_byte(idx, false));
  spi_send(addr);
  spi_send((val >> 8) & 0xFF);
  spi_send(val & 0xFF);

  writePinHigh(SS);
}
