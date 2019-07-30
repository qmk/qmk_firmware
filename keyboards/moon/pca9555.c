/* Copyright 2019
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
#include "i2c_master.h"
#include "pca9555.h"

#include "debug.h"

#define SLAVE_TO_ADDR(n) (n << 1)
#define TIMEOUT 100

enum {
  CMD_INPUT_0 = 0,
  CMD_INPUT_1,
  CMD_OUTPUT_0,
  CMD_OUTPUT_1,
  CMD_INVERSION_0,
  CMD_INVERSION_1,
  CMD_CONFIG_0,
  CMD_CONFIG_1,
};

void pca9555_init(uint8_t slave_addr) {
  static uint8_t s_init = 0;
  if (!s_init) {
    i2c_init();

    s_init = 1;
  }

  // TODO: could check device connected
  // i2c_start(SLAVE_TO_ADDR(slave) | I2C_WRITE);
  // i2c_stop();
}

void pca9555_set_config(uint8_t slave_addr, uint8_t port, uint8_t conf) {
  uint8_t addr = SLAVE_TO_ADDR(slave_addr);
  uint8_t cmd  = port ? CMD_CONFIG_1 : CMD_CONFIG_0;

  i2c_status_t ret = i2c_writeReg(addr, cmd, &conf, sizeof(conf), TIMEOUT);
  if (ret != I2C_STATUS_SUCCESS) {
    print("pca9555_set_config::FAILED\n");
  }
}

void pca9555_set_output(uint8_t slave_addr, uint8_t port, uint8_t conf) {
  uint8_t addr = SLAVE_TO_ADDR(slave_addr);
  uint8_t cmd  = port ? CMD_OUTPUT_1 : CMD_OUTPUT_0;

  i2c_status_t ret = i2c_writeReg(addr, cmd, &conf, sizeof(conf), TIMEOUT);
  if (ret != I2C_STATUS_SUCCESS) {
    print("pca9555_set_output::FAILED\n");
  }
}

uint8_t pca9555_readPins(uint8_t slave_addr, uint8_t port) {
  uint8_t addr = SLAVE_TO_ADDR(slave_addr);
  uint8_t cmd  = port ? CMD_INPUT_1 : CMD_INPUT_0;

  uint8_t      data = 0;
  i2c_status_t ret  = i2c_readReg(addr, cmd, &data, sizeof(data), TIMEOUT);
  if (ret != I2C_STATUS_SUCCESS) {
    print("pca9555_readPins::FAILED\n");
  }
  return data;
}
