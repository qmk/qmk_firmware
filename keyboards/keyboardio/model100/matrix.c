/* Copyright 2018 James Laird-Wah
 * Copyright 2025 QMK
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
#include <string.h>
#include "model100.h"
#include "ch.h"
#include "hal.h"

#define ROWS_PER_HAND (MATRIX_ROWS / 2)

/* ---------------------------------------------------------------------------
 * Polled (non-DMA) I2C for the ATtiny key scanners.
 *
 * ChibiOS's STM32 I2Cv1 driver completes transfers via DMA. On the GD32F303
 * (which we build as an STM32F103) the DMA<->I2C wiring does not behave as the
 * ST driver expects, so transfers never complete — i2c_receive/i2c_transmit
 * just time out even though the peripheral, clock and pins are all configured
 * correctly. Keyboardio's own DAPBoot bootloader talks to these exact scanners
 * with a polled loop and works fine, so we do the same: drive I2C1 by polling
 * the status registers, with no interrupt and no DMA.
 *
 * This is also shared with the LED driver (leds.c) via i2c_poll_write() — the
 * LEDs sit on the same bus, so they must use the same working path; mixing in
 * the broken ChibiOS DMA driver corrupts the bus for everyone.
 *
 * The I2C register bit masks (CR1/SR1/SR2) come from the CMSIS device header
 * pulled in by hal.h; TXE is not always exposed, so define our own below.
 * --------------------------------------------------------------------------- */
#ifndef I2C_SR1_TXE
#define I2C_SR1_TXE     (1U << 7)
#endif

/* The scanners clock-stretch (hold SCL low) while they service a request, so
 * the waits must tolerate that without being so long that an unresponsive hand
 * stalls the whole scan. ~20000 loop iterations is a few I2C byte-times here. */
#define POLL_TIMEOUT_LOOPS 20000U

/* Bring up I2C1 for polled use by hand. We deliberately do NOT use ChibiOS's
 * i2cStart(): it leaves the I2C event interrupt armed, and our manual START
 * would then fire that ISR with no active transfer, halting the system. */
static void i2c_poll_setup(void) {
  rccEnableI2C1(true);
  rccResetI2C1();

  /* PB6 = SCL, PB7 = SDA, alternate-function open-drain. */
  palSetLineMode(B6, PAL_MODE_STM32_ALTERNATE_OPENDRAIN);
  palSetLineMode(B7, PAL_MODE_STM32_ALTERNATE_OPENDRAIN);

  uint32_t pclk1_mhz = STM32_PCLK1 / 1000000U;
  I2CD1.i2c->CR1   = 0;                          /* disable while configuring */
  I2CD1.i2c->CR2   = pclk1_mhz;                  /* FREQ = PCLK1 in MHz */
  /* Standard mode 100 kHz: CCR = PCLK1 / (2 * 100k); TRISE = PCLK1(MHz) + 1. */
  I2CD1.i2c->CCR   = STM32_PCLK1 / (2U * 100000U);
  I2CD1.i2c->TRISE = pclk1_mhz + 1U;
  I2CD1.i2c->CR1   = I2C_CR1_PE;                 /* enable */
}

/* Wait until (SR1 & mask) == mask, or bail. Returns false on timeout. */
static bool i2c_wait_sr1(uint32_t mask) {
  for (uint32_t i = 0; i < POLL_TIMEOUT_LOOPS; i++) {
    if ((I2CD1.i2c->SR1 & mask) == mask) return true;
  }
  return false;
}

/* Wait for a just-issued STOP to complete (CR1.STOP self-clears) and BUSY to
 * drop, so the bus is genuinely idle before the next hand's transaction. */
static void i2c_wait_stop(void) {
  for (uint32_t i = 0; i < POLL_TIMEOUT_LOOPS; i++) {
    if (!(I2CD1.i2c->CR1 & I2C_CR1_STOP) && !(I2CD1.i2c->SR2 & I2C_SR2_BUSY)) return;
  }
}

/* Blocking, polled read of `n` bytes from a pre-shifted 8-bit address (QMK's
 * convention). Returns the number of bytes actually read. */
static int i2c_poll_read(uint8_t addr8, uint8_t *dst, int n) {
  uint8_t addr7 = addr8 >> 1;

  /* ChibiOS gates the I2C1 clock when it thinks the peripheral is unused (we
   * don't hold its driver), so re-assert it each transaction. */
  rccEnableI2C1(true);
  I2CD1.i2c->CR1 |= I2C_CR1_PE | I2C_CR1_ACK;

  for (uint32_t i = 0; (I2CD1.i2c->SR2 & I2C_SR2_BUSY); i++) {
    if (i >= POLL_TIMEOUT_LOOPS) return 0;
  }

  I2CD1.i2c->CR1 |= I2C_CR1_START;
  if (!i2c_wait_sr1(I2C_SR1_SB)) return 0;

  I2CD1.i2c->DR = (uint32_t)((addr7 << 1) | 1U);   /* read */
  if (!i2c_wait_sr1(I2C_SR1_ADDR)) { I2CD1.i2c->CR1 |= I2C_CR1_STOP; i2c_wait_stop(); return 0; }
  (void)I2CD1.i2c->SR2;                            /* clear ADDR */

  int got = 0;
  while (n > 0) {
    if (n == 1) {
      I2CD1.i2c->CR1 &= ~I2C_CR1_ACK;              /* NACK the last byte */
      I2CD1.i2c->CR1 |= I2C_CR1_STOP;
      if (!i2c_wait_sr1(I2C_SR1_RXNE)) { i2c_wait_stop(); return got; }
      dst[got++] = (uint8_t)I2CD1.i2c->DR;
      n = 0;
    } else {
      if (!i2c_wait_sr1(I2C_SR1_RXNE)) { I2CD1.i2c->CR1 |= I2C_CR1_STOP; i2c_wait_stop(); return got; }
      dst[got++] = (uint8_t)I2CD1.i2c->DR;
      n--;
    }
  }
  i2c_wait_stop();
  return got;
}

/* Blocking, polled write. Returns true on success. Shared with leds.c via
 * model100.h so the LED driver uses the same working polled path. */
bool i2c_poll_write(uint8_t addr8, const uint8_t *src, int n) {
  uint8_t addr7 = addr8 >> 1;

  rccEnableI2C1(true);
  I2CD1.i2c->CR1 |= I2C_CR1_PE;

  for (uint32_t i = 0; (I2CD1.i2c->SR2 & I2C_SR2_BUSY); i++) {
    if (i >= POLL_TIMEOUT_LOOPS) return false;
  }

  I2CD1.i2c->CR1 |= I2C_CR1_START;
  if (!i2c_wait_sr1(I2C_SR1_SB)) return false;

  I2CD1.i2c->DR = (uint32_t)(addr7 << 1);          /* write */
  if (!i2c_wait_sr1(I2C_SR1_ADDR)) { I2CD1.i2c->CR1 |= I2C_CR1_STOP; return false; }
  (void)I2CD1.i2c->SR2;

  for (int i = 0; i < n; i++) {
    if (!i2c_wait_sr1(I2C_SR1_TXE)) { I2CD1.i2c->CR1 |= I2C_CR1_STOP; return false; }
    I2CD1.i2c->DR = src[i];
    if (!i2c_wait_sr1(I2C_SR1_BTF)) { I2CD1.i2c->CR1 |= I2C_CR1_STOP; i2c_wait_stop(); return false; }
  }
  I2CD1.i2c->CR1 |= I2C_CR1_STOP;
  i2c_wait_stop();
  return true;
}

static void i2c_read_hand(int hand, matrix_row_t current_matrix[]) {
  uint8_t buf[5] = {0};
  if (i2c_poll_read(I2C_ADDR(hand), buf, sizeof(buf)) != (int)sizeof(buf)) {
    return;
  }
  /* Only KEYDATA replies carry a fresh row snapshot; the scanner returns other
   * reply types (or no-data) when nothing new is available — leave the matrix
   * untouched in that case so held keys stay held. */
  if (buf[0] != TWI_REPLY_KEYDATA) {
    return;
  }

  int start_row = hand ? ROWS_PER_HAND : 0;
  memcpy(&current_matrix[start_row], &buf[1], ROWS_PER_HAND);
}

static void i2c_set_keyscan_interval(int hand, int delay) {
  uint8_t buf[] = {TWI_CMD_KEYSCAN_INTERVAL, (uint8_t)delay};
  i2c_poll_write(I2C_ADDR(hand), buf, sizeof(buf));
}

void matrix_init_custom(void) {
  /* Turn on the switched 5V network that powers the scanners. On the Model 100
   * this is an open-drain output driven LOW to enable (unlike the Model 01's
   * push-pull C7). The ATtiny scanners take ~65-76ms to boot after power-up
   * (Keyboardio's DAPBoot notes it works at 76ms but not 75ms and waits 125ms);
   * talk to them too soon and they never answer, so match DAPBoot's 125ms. */
  gpio_set_pin_output_open_drain(B9);
  gpio_write_pin_low(B9);
  wait_ms(125);

  i2c_poll_setup();

  i2c_set_keyscan_interval(LEFT, 2);
  i2c_set_keyscan_interval(RIGHT, 2);
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
  matrix_row_t last_matrix[MATRIX_ROWS];
  memcpy(last_matrix, current_matrix, sizeof(last_matrix));

  i2c_read_hand(LEFT, current_matrix);
  i2c_read_hand(RIGHT, current_matrix);

  return memcmp(last_matrix, current_matrix, sizeof(last_matrix)) != 0;
}

/* vim: set ts=2 sw=2 et: */
