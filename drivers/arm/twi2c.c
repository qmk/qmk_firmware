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
#include "matrix.h"

#ifdef I2C_SLAVE_ENABLE

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

#endif

static uint8_t twi2c_address;

static const I2CConfig i2cconfig = {
  STM32_TIMINGR_PRESC(15U) |
  STM32_TIMINGR_SCLDEL(4U) | STM32_TIMINGR_SDADEL(2U) |
  STM32_TIMINGR_SCLH(15U)  | STM32_TIMINGR_SCLL(21U),
  0,
  0
};

char initialReplyBody[50] = "Initial reply";        // 'Status' response if read without preceding write


uint32_t messageCounter = 0;                /* Counts number of messages received to return as part of response */

uint8_t  rxBody[2];                       /* stores last message master sent us (intentionally a few bytes smaller than txBody) */
uint8_t  txBody[MATRIX_ROWS/2];                       /* Return message buffer for computed replies */

BaseSequentialStream *chp = NULL;           // Used for serial logging


#ifdef I2C_SLAVE_ENABLE







// Handler when something sent to us
const I2CSlaveMsg echoRx =
{
  sizeof(rxBody),       /* max sizeof received msg body */
  rxBody,               /* body of received msg */
  NULL,                 /* do nothing on address match */
  twi2c_slave_message_process,     /* Routine to process received messages */
  twi2c_catch_error            /* Error hook */
};


// // 'Empty' reply when nothing to say, and no message received. In RAM, to allow update
I2CSlaveMsg initialReply =
{
  sizeof(initialReplyBody),   /* trailing zero byte will be repeated as needed */
  (uint8_t *)initialReplyBody,
  NULL,                 /* do nothing on address match */
  NULL,                 /* do nothing after reply sent */
  twi2c_catch_error            /* Error hook */
};

// // 'Empty' reply when nothing to say, and no message received. In RAM, to allow update
// I2CSlaveMsg initialReply =
// {
//   0,  /* trailing zero byte will be repeated as needed */
//   NULL,
//   NULL,                 /* do nothing on address match */
//   NULL,                 /* do nothing after reply sent */
//   twi2c_catch_error            /* Error hook */
// };


// Response to received messages
I2CSlaveMsg echoReply = {  /* this is in RAM so size may be updated */
  MATRIX_ROWS / 2,                    /* filled in with the length of the message to send */
  txBody,               /* Response message */
  NULL,                 /* do nothing special on address match */
  twi2c_clear_after_send,       /* Clear receive buffer once replied */
  twi2c_catch_error            /* Error hook */
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

extern void matrix_copy(matrix_row_t * copy);

const char hexString[16] = "0123456789abcdef";



/**
 *  Message processor - looks at received message, determines reply as quickly as possible
 *
 *  Responds with the value of the messageCounter (in hex), followed by the received message in [..]
 *
 *  Note: Called in interrupt context, so need to be quick!
 */
void twi2c_slave_message_process(I2CDriver *i2cp) {

  // size_t len = i2cSlaveBytes(i2cp);         // Number of bytes received

  // memset(txBody, 0, MATRIX_ROWS / 2 * sizeof(matrix_row_t));
  matrix_copy(txBody);

  echoReply.size =  MATRIX_ROWS / 2;
  i2cSlaveReplyI(i2cp, &echoReply);
}


/**
 * Callback after sending of response complete - restores default reply in case polled
 */
void twi2c_clear_after_send(I2CDriver *i2cp)
{
  // echoReply.size = 0;               // Clear receive message
  // i2cSlaveReplyI(i2cp, &initialReply);
}


/**
 * Start the I2C Slave port to accept comms from master CPU
 *
 * We then go into a loop checking for errors, and never return
 */

void twi2c_slave_init(twi2c_message_received * cb, uint8_t address) {

  twi2c_init();


  i2cStart(&I2C_DRIVER, &i2cconfig);
#if HAL_USE_I2C_SLAVE
  I2C_DRIVER.slaveTimeout = MS2ST(100);       // Time for complete message
#endif

  // i2cSlaveConfigure(&I2C_DRIVER, &echoRx, &initialReply);

  memset(txBody, 0, MATRIX_ROWS / 2 * sizeof(matrix_row_t));

  i2cSlaveConfigure(&I2C_DRIVER, &echoRx, &echoReply);

  // Enable match address after everything else set up
  i2cMatchAddress(&I2C_DRIVER, address/2);
//  i2cMatchAddress(&I2C_DRIVER, myOtherI2Caddress/2);
 // i2cMatchAddress(&I2C_DRIVER, 0);  /* "all call" */

  printf("Slave I2C started\n\r");

}

void twi2c_slave_task(void) {
    if (gotI2cError) {
      gotI2cError = 0;
        printf("I2cError: %04x\r\n", lastI2cErrorFlags);
    }
}

#endif

uint8_t twi2c_start(uint8_t address) {
  twi2c_address = address;
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

uint8_t twi2c_transmit(uint8_t address, uint8_t* data, uint16_t length) {
  twi2c_address = address;
  i2cStart(&I2C_DRIVER, &i2cconfig);
  return i2cMasterTransmitTimeout(&I2C_DRIVER, twi2c_address/2, data, length, 0, 0, MS2ST(100));
}

uint8_t twi2c_incoming_body[512];
uint8_t twi2c_outgoing_body[512];

// Response to received messages
I2CSlaveMsg twi2c_incoming_message = {
  sizeof(twi2c_incoming_body),
  twi2c_incoming_body,
  NULL,
  twi2c_incoming_message_process,
  twi2c_catch_error                   /* Error hook */
};

void twi2c_incoming_message_process(I2CDriver *i2cp) {
  size_t len = i2cSlaveBytes(i2cp);
  twi2c_message_received_callback(twi2c_incoming_body, len);
}

// Response to received messages
I2CSlaveMsg twi2c_outgoing_message = {  /* this is in RAM so size may be updated */
  sizeof(twi2c_outgoing_body),                    /* filled in with the length of the message to send */
  twi2c_outgoing_body,
  NULL,
  twi2c_clear_after_send,
  twi2c_catch_error                   /* Error hook */
};

uint8_t twi2c_reply(uint8_t * data, uint16_t length) {
  twi2c_outgoing_body = data;
  twi2c_outgoing_message.size = length;
  i2cSlaveReplyI(i2cp, &twi2c_outgoing_message);
}

uint8_t twi2c_transmit_receive(uint8_t address, uint8_t * tx_body, uint16_t tx_length, uint8_t rx_body, uint16_t rx_length) {
  return i2cMasterTransmitTimeout(&I2C_DRIVER, address/2, tx_body, tx_length, rx_body, rx_length, MS2ST(100));
}

uint8_t twi2c_start_listening(uint8_t address, twi2c_message_received callback) {
  twi2c_message_received_callback = callback;
  i2cStart(&I2C_DRIVER, &i2cconfig);
  I2C_DRIVER.slaveTimeout = MS2ST(100);
  i2cSlaveConfigure(&I2C_DRIVER, &twi2c_incoming_message, &twi2c_outgoing_message);
  i2cMatchAddress(&I2C_DRIVER, address/2);
  return 0;
}
