/*
 * io_expander.c
 *
 *  Created on: 2018/12/16
 *      Author: sekigon-gonnoc
 */

#if defined(USE_I2C_IOEXPANDER) || defined(USE_SPI_IOEXPANDER)
#include <stdint.h>
#include "i2c.h"
#include "spi.h"
#include "io_expander.h"
#include "matrix.h"

extern const IOEXPANDER_TYPEDEF ioexpander_types[];
extern const uint8_t ioexpander_addrs[];
#ifdef USE_SPI_IOEXPANDER
extern const uint8_t ioexpander_cs_pins[];
#endif

matrix_row_t read_row_ioexpander (uint8_t row) {
  matrix_row_t  matrix_row_state = 0;
  uint8_t dat[2] = {0xFF, 0xFF};
  uint8_t spi_send[4];
  uint8_t spi_recv[4] = { 0xFF };
  if (row > MATRIX_ROWS) {
    return 0;
  }
  switch (ioexpander_types[row]) {
  case TCA9555:
    i2c_init();
    i2c_readReg(ioexpander_addrs[row], 0, dat, 2, 0);
    matrix_row_state = ~((((uint16_t)dat[1]) << 8) | dat[0]);
    i2c_uninit();
    break;
  case PCA9654:
    i2c_init();
    i2c_receive(ioexpander_addrs[row], dat, 1);
    matrix_row_state = ~dat[0];
    i2c_uninit();
    break;
#ifdef USE_SPI_IOEXPANDER
  case MCP23S17:
    spi_send[0] = 0x40 | (ioexpander_addrs[row] << 1) | 1;
    spi_send[1] = 0x12;
    spi_send[2] = 0;
    spi_send[3] = 0;
    spim_start(spi_send, 4, spi_recv, 4, ioexpander_cs_pins[row]);
    matrix_row_state = ~((((uint16_t)spi_recv[3]) << 8) | spi_recv[2]);
    break;
#endif
  default:
    break;
  }
  return matrix_row_state;
}
#endif
