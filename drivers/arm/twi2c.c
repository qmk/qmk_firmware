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
#include "hal_i2cslave.h"
#include "chprintf.h"
#include "memstreams.h"
#include "printf.h"
#include "matrix.h"

#ifndef I2C_DRIVER
	#define I2C_DRIVER I2CD1
#endif

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

static const I2CConfig uniI2CConfig = {
  STM32_TIMINGR_PRESC(15U) |
  STM32_TIMINGR_SCLDEL(4U) | STM32_TIMINGR_SDADEL(2U) |
  STM32_TIMINGR_SCLH(15U)  | STM32_TIMINGR_SCLL(21U),
  0,
  0,
  NULL
};

char initialReplyBody[50] = "Initial reply";        // 'Status' response if read without preceding write


uint32_t messageCounter = 0;                /* Counts number of messages received to return as part of response */

uint8_t  rxBody[240];                       /* stores last message master sent us (intentionally a few bytes smaller than txBody) */
uint8_t  txBody[256];                       /* Return message buffer for computed replies */

BaseSequentialStream *chp = NULL;           // Used for serial logging

// Handler when something sent to us
const I2CSlaveMsg echoRx =
{
  sizeof(rxBody),       /* max sizeof received msg body */
  rxBody,               /* body of received msg */
  NULL,                 /* do nothing on address match */
  twi2c_slave_message_process,     /* Routine to process received messages */
  catchError            /* Error hook */
};


// 'Empty' reply when nothing to say, and no message received. In RAM, to allow update
I2CSlaveMsg initialReply =
{
  sizeof(initialReplyBody),  /* trailing zero byte will be repeated as needed */
  (uint8_t *)initialReplyBody,
  NULL,                 /* do nothing on address match */
  NULL,                 /* do nothing after reply sent */
  catchError            /* Error hook */
};


// Response to received messages
I2CSlaveMsg echoReply = {  /* this is in RAM so size may be updated */
  0,                    /* filled in with the length of the message to send */
  txBody,               /* Response message */
  NULL,                 /* do nothing special on address match */
  clearAfterSend,       /* Clear receive buffer once replied */
  catchError            /* Error hook */
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
void catchError(I2CDriver *i2cp)
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
  uint8_t *txPtr = txBody;
  uint8_t txLen;

  size_t len = i2cSlaveBytes(i2cp);         // Number of bytes received

  if (len >= 2 && rxBody[0] == 0x01 && rxBody[1] == 0x00) {
    matrix_row_t matrix[MATRIX_ROWS / 2];
    matrix_copy(matrix);
    memcpy(txPtr, matrix, MATRIX_ROWS / 2);
    txLen = MATRIX_ROWS / 2;
  }

  echoReply.size = txLen;
  i2cSlaveReplyI(i2cp, &echoReply);
}


/**
 * Callback after sending of response complete - restores default reply in case polled
 */
void clearAfterSend(I2CDriver *i2cp)
{
  echoReply.size = 0;               // Clear receive message
  i2cSlaveReplyI(i2cp, &initialReply);
}


/**
 * Start the I2C Slave port to accept comms from master CPU
 *
 * We then go into a loop checking for errors, and never return
 */

void twi2c_slave_init(void) {

  palSetGroupMode(GPIOB,8,9, PAL_MODE_INPUT);       // Try releasing special pins for a short time
  chThdSleepMilliseconds(10);

  /* I2C1 SCL on PF1, SDA on PF0 */
  palSetPadMode(GPIOB, 9, PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_PUPDR_PULLUP);
  palSetPadMode(GPIOB, 8, PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_PUPDR_PULLUP);


  i2cStart(&I2C_DRIVER, &uniI2CConfig);
#if HAL_USE_I2C_SLAVE
  I2C_DRIVER.slaveTimeout = MS2ST(100);       // Time for complete message
#endif

  i2cSlaveConfigure(&I2C_DRIVER, &echoRx, &initialReply);

  // Enable match address after everything else set up
  i2cMatchAddress(&I2C_DRIVER, slaveI2Caddress/2);
//  i2cMatchAddress(&I2C_DRIVER, myOtherI2Caddress/2);
//  i2cMatchAddress(&I2C_DRIVER, 0);  /* "all call" */

  printf("Slave I2C started\n\r");

}

void twi2c_slave_task(void) {
    if (gotI2cError) {
      gotI2cError = 0;
        printf("I2cError: %04x\r\n", lastI2cErrorFlags);
    }
}

void twi2c_master_init(void) {
  i2cStart(&I2C_DRIVER, &uniI2CConfig);
}

msg_t twi2c_master_send(i2caddr_t address, const uint8_t * txbuf, uint8_t * rxbuf, systime_t timeout) {
  return i2cMasterTransmitTimeout(&I2C_DRIVER, address, txbuf, sizeof(txbuf), rxbuf, sizeof(rxbuf), timeout);
}
