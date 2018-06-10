/* Copyright 2018 Jack Humbert
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

#include "twi2c.h"
#include <string.h>
#include <hal.h>
#include "chprintf.h"
#include "memstreams.h"
#include "printf.h"
#include "hal_i2cslave.h"

/**
 * I2C slave test routine.
 *
 * To use: Add file to a project, call startComms() with the address of a serial stream
 *
 * There are two different responses:
 *  a) A read-only transaction - returns the "Initial Reply" message
 *  b) A write then read transaction - calls a message processor and returns the generated reply.
 *          Stretches clock until reply available.
 */
// static const I2CConfig masterI2CConfig = {
//   400000
// };

I2CSlaveMsgCB twi2c_incoming_message_process, twi2c_catch_error, twi2c_clear_after_send;
twi2c_message_received twi2c_message_received_callback;

static uint8_t twi2c_address;

static const I2CConfig i2cconfig = {
  STM32_TIMINGR_PRESC(15U) |
  STM32_TIMINGR_SCLDEL(4U) | STM32_TIMINGR_SDADEL(2U) |
  STM32_TIMINGR_SCLH(15U)  | STM32_TIMINGR_SCLL(21U),
  0,
  0
};

/**
 * Track I2C errors
 */
uint8_t gotI2cError = 0;
uint32_t lastI2cErrorFlags = 0;

// Called from ISR to log error
void noteI2cError(uint32_t flags)
{
  lastI2cErrorFlags = flags;
  gotI2cError = 1;
}

/**
 * Generic error handler
 *
 * Called in interrupt context, so need to watch what we do
 */
void twi2c_catch_error(I2CDriver *i2cp)
{
  noteI2cError(i2cp->errors);
}

/**
 * Callback after sending of response complete - restores default reply in case polled
 */
void twi2c_clear_after_send(I2CDriver *i2cp)
{
  // echoReply.size = 0;               // Clear receive message
  // i2cSlaveReplyI(i2cp, &initialReply);
}

uint8_t twi2c_start(void) {
  i2cStart(&I2C_DRIVER, &i2cconfig);
  return 0;
}

void twi2c_init(void) {
  palSetGroupMode(GPIOB,6,7, PAL_MODE_INPUT);       // Try releasing special pins for a short time
  chThdSleepMilliseconds(10);

  palSetPadMode(GPIOB, 6, PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_PUPDR_PULLUP);
  palSetPadMode(GPIOB, 7, PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_PUPDR_PULLUP);

  // try high drive (from kiibohd)
  // I2C_DRIVER.i2c->C2 |= I2Cx_C2_HDRS;
  // try glitch fixing (from kiibohd)
  // I2C_DRIVER.i2c->FLT = 4;
}

uint8_t twi2c_write(uint8_t data) {
  return i2cMasterTransmitTimeout(&I2C_DRIVER, twi2c_address/2, &data, 1, 0, 0, MS2ST(100));
}

uint8_t twi2c_transmit(uint8_t address, uint8_t * data, uint16_t length) {
  return i2cMasterTransmitTimeout(&I2C_DRIVER, address/2, data, length, 0, 0, MS2ST(100));
}

uint8_t twi2c_receive(uint8_t address, uint8_t * data, uint16_t length) {
  return i2cMasterReceiveTimeout(&I2C_DRIVER, address/2, data, length, MS2ST(100));
}


uint8_t twi2c_incoming_body[50];
uint8_t twi2c_outgoing_body[1024];

// Response to received messages
I2CSlaveMsg twi2c_incoming_message = {
  sizeof(twi2c_incoming_body),
  twi2c_incoming_body,
  NULL,
  twi2c_incoming_message_process,
  twi2c_catch_error                   /* Error hook */
};

void twi2c_incoming_message_process(I2CDriver * i2cp) {
  size_t len = i2cSlaveBytes(i2cp);
  (*twi2c_message_received_callback)(i2cp, twi2c_incoming_body, len);
}

// Response to received messages
I2CSlaveMsg twi2c_outgoing_message = {
  sizeof(twi2c_outgoing_body),
  twi2c_outgoing_body,
  NULL,
  twi2c_clear_after_send,
  twi2c_catch_error
};

uint8_t twi2c_reply(I2CDriver * i2cp, uint8_t * data, uint16_t length) {
  memcpy(twi2c_outgoing_body, data, length);
  twi2c_outgoing_message.size = length;
  i2cSlaveReplyI(i2cp, &twi2c_outgoing_message);
  return 0;
}

uint8_t twi2c_transmit_receive(uint8_t address, uint8_t * tx_body, uint16_t tx_length, uint8_t * rx_body, uint16_t rx_length) {
  return i2cMasterTransmitTimeout(&I2C_DRIVER, address/2, tx_body, tx_length, rx_body, rx_length, MS2ST(100));
}

uint8_t twi2c_start_listening(uint8_t address, twi2c_message_received callback) {
  twi2c_message_received_callback = callback;
  I2C_DRIVER.slaveTimeout = MS2ST(100);
  i2cSlaveConfigure(&I2C_DRIVER, &twi2c_incoming_message, &twi2c_outgoing_message);
  i2cMatchAddress(&I2C_DRIVER, address/2);
  return 0;
}

uint8_t twi2c_restart_listening(uint8_t address) {
  i2cMatchAddress(&I2C_DRIVER, address/2);
  return 0;
}

void twi2c_stop(void) {
  i2cUnmatchAll(&I2C_DRIVER);
  i2cStop(&I2C_DRIVER);
}
