/*
    ChibiOS - Copyright (C) 2006..2015 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
/*
   Concepts and parts of this file have been contributed by Uladzimir Pylinsky
   aka barthess.
 */

/**
 * @file    i2c.c
 * @brief   I2C Driver code.
 *
 * @addtogroup I2C
 * @{
 */
#include "hal.h"

#if (HAL_USE_I2C == TRUE) || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   I2C Driver initialization.
 * @note    This function is implicitly invoked by @p halInit(), there is
 *          no need to explicitly initialize the driver.
 *
 * @init
 */
void i2cInit(void) {

  i2c_lld_init();
}

/**
 * @brief   Initializes the standard part of a @p I2CDriver structure.
 *
 * @param[out] i2cp     pointer to the @p I2CDriver object
 *
 * @init
 */
void i2cObjectInit(I2CDriver *i2cp) {

  i2cp->state  = I2C_STOP;
  i2cp->config = NULL;

#if I2C_USE_MUTUAL_EXCLUSION == TRUE
#if CH_CFG_USE_MUTEXES
  osalMutexObjectInit(&i2cp->mutex);
#else
  osalSemObjectInit(&i2cp->semaphore, 1);
#endif /* CH_CFG_USE_MUTEXES */
#endif /* I2C_USE_MUTUAL_EXCLUSION */

#if defined(I2C_DRIVER_EXT_INIT_HOOK)
  I2C_DRIVER_EXT_INIT_HOOK(i2cp);
#endif
}

/**
 * @brief   Configures and activates the I2C peripheral.
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 * @param[in] config    pointer to the @p I2CConfig object
 *
 * @api
 */
void i2cStart(I2CDriver *i2cp, const I2CConfig *config) {

  osalDbgCheck((i2cp != NULL) && (config != NULL));
  osalDbgAssert((i2cp->state == I2C_STOP) || (i2cp->state == I2C_READY) ||
                (i2cp->state == I2C_LOCKED), "invalid state");

  osalSysLock();
  i2cp->config = config;
  i2c_lld_start(i2cp);
  i2cp->state = I2C_READY;
  osalSysUnlock();
}

/**
 * @brief   Deactivates the I2C peripheral.
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 *
 * @api
 */
void i2cStop(I2CDriver *i2cp) {

  osalDbgCheck(i2cp != NULL);
  osalDbgAssert((i2cp->state == I2C_STOP) || (i2cp->state == I2C_READY) ||
                (i2cp->state == I2C_LOCKED), "invalid state");

  osalSysLock();
  i2c_lld_stop(i2cp);
  i2cp->state = I2C_STOP;
  osalSysUnlock();
}

/**
 * @brief   Returns the errors mask associated to the previous operation.
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 * @return              The errors mask.
 *
 * @api
 */
i2cflags_t i2cGetErrors(I2CDriver *i2cp) {

  osalDbgCheck(i2cp != NULL);

  return i2c_lld_get_errors(i2cp);
}

/**
 * @brief   Sends data via the I2C bus.
 * @details Function designed to realize "read-through-write" transfer
 *          paradigm. If you want transmit data without any further read,
 *          than set @b rxbytes field to 0.
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 * @param[in] addr      slave device address (7 bits) without R/W bit
 * @param[in] txbuf     pointer to transmit buffer
 * @param[in] txbytes   number of bytes to be transmitted
 * @param[out] rxbuf    pointer to receive buffer
 * @param[in] rxbytes   number of bytes to be received, set it to 0 if
 *                      you want transmit only
 * @param[in] timeout   the number of ticks before the operation timeouts,
 *                      the following special values are allowed:
 *                      - @a TIME_INFINITE no timeout.
 *                      .
 *
 * @return              The operation status.
 * @retval MSG_OK       if the function succeeded.
 * @retval MSG_RESET    if one or more I2C errors occurred, the errors can
 *                      be retrieved using @p i2cGetErrors().
 * @retval MSG_TIMEOUT  if a timeout occurred before operation end.
 *
 * @api
 */
msg_t i2cMasterTransmitTimeout(I2CDriver *i2cp,
                               i2caddr_t addr,
                               const uint8_t *txbuf,
                               size_t txbytes,
                               uint8_t *rxbuf,
                               size_t rxbytes,
                               systime_t timeout) {
  msg_t rdymsg;

  osalDbgCheck((i2cp != NULL) && (addr != 0U) &&
               (txbytes > 0U) && (txbuf != NULL) &&
               ((rxbytes == 0U) || ((rxbytes > 0U) && (rxbuf != NULL))) &&
               (timeout != TIME_IMMEDIATE));

  osalDbgAssert(i2cp->state == I2C_READY, "not ready");

  osalSysLock();
  i2cp->errors = I2C_NO_ERROR;
  i2cp->state = I2C_ACTIVE_TX;
  rdymsg = i2c_lld_master_transmit_timeout(i2cp, addr, txbuf, txbytes,
                                           rxbuf, rxbytes, timeout);
  if (rdymsg == MSG_TIMEOUT) {
    i2cp->state = I2C_LOCKED;
  }
  else {
    i2cp->state = I2C_READY;
  }
  osalSysUnlock();
  return rdymsg;
}

/**
 * @brief   Receives data from the I2C bus.
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 * @param[in] addr      slave device address (7 bits) without R/W bit
 * @param[out] rxbuf    pointer to receive buffer
 * @param[in] rxbytes   number of bytes to be received
 * @param[in] timeout   the number of ticks before the operation timeouts,
 *                      the following special values are allowed:
 *                      - @a TIME_INFINITE no timeout.
 *                      .
 *
 * @return              The operation status.
 * @retval MSG_OK       if the function succeeded.
 * @retval MSG_RESET    if one or more I2C errors occurred, the errors can
 *                      be retrieved using @p i2cGetErrors().
 * @retval MSG_TIMEOUT  if a timeout occurred before operation end.
 *
 * @api
 */
msg_t i2cMasterReceiveTimeout(I2CDriver *i2cp,
                              i2caddr_t addr,
                              uint8_t *rxbuf,
                              size_t rxbytes,
                              systime_t timeout){

  msg_t rdymsg;

  osalDbgCheck((i2cp != NULL) && (addr != 0U) &&
               (rxbytes > 0U) && (rxbuf != NULL) &&
               (timeout != TIME_IMMEDIATE));

  osalDbgAssert(i2cp->state == I2C_READY, "not ready");

  osalSysLock();
  i2cp->errors = I2C_NO_ERROR;
  i2cp->state = I2C_ACTIVE_RX;
  rdymsg = i2c_lld_master_receive_timeout(i2cp, addr, rxbuf, rxbytes, timeout);
  if (rdymsg == MSG_TIMEOUT) {
    i2cp->state = I2C_LOCKED;
  }
  else {
    i2cp->state = I2C_READY;
  }
  osalSysUnlock();
  return rdymsg;
}


#if HAL_USE_I2C_LOCK    /* I2C slave mode support */

/**
 * @brief   Lock I2C bus at the beginning of the next message sent
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 * @param[in] lockDuration   max number of ticks to hold bus locked
 *                      - @a TIME_INFINITE no timeout.
 *                      - @a TIME_IMMEDIATE unlock the bus immediately
 *                      .
 *
 * @api
 */
void i2cLock(I2CDriver *i2cp, systime_t lockDuration)
{
  chDbgCheck((i2cp != NULL), "i2cLock");
  chSysLock();
  i2c_lld_lock(i2cp, lockDuration);
  chSysUnlock();
}

/**
 * @brief   Unlock I2C bus after the end of the next transaction
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 *
 * @api
 **/
void i2cUnlock(I2CDriver *i2cp)
{
  chDbgCheck((i2cp != NULL), "i2cUnlock");
  chSysLock();
  i2c_lld_unlock(i2cp);
  chSysUnlock();
}
#endif


#if HAL_USE_I2C_SLAVE   /* I2C slave mode support */

/**
 * @brief   Reconfigure I2C channel to respond to indicated address
 *          in addition to those already matched
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 * @param[in] i2cadr    I2C network address
 *
 * @return              Length of message OR the type of event received
 * @retval I2C_OK       Success
 * @retval I2C_ERROR    Cannot match address in addition of those already
 *
 * @details             MatchAddress calls are cumulative.
 *                      Specify address zero to match I2C "all call"
 *                      Does not support 10-bit addressing.
 *
 * @api
 **/
msg_t i2cMatchAddress(I2CDriver *i2cp, i2caddr_t  i2cadr)
{
  osalDbgCheck((i2cp != NULL));
  chSysLock();
  msg_t result = i2c_lld_matchAddress(i2cp, i2cadr);
  chSysUnlock();
  return result;
}


/**
 * @brief   Configure to ignore messages directed to the given i2cadr
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 * @param[in] i2cadr    I2C bus address
 *                      - @a 0 matches "all call"
 *                      .
 * @details A message being transferred that has already matched the
 *          specified address will continue being processed.
 *          Requests to unmatch an address that is not currently being matched
 *          are ignored.
 *
 * @api
 */
void i2cUnmatchAddress(I2CDriver *i2cp, i2caddr_t  i2cadr)
{
  osalDbgCheck((i2cp != NULL));
  chSysLock();
  i2c_lld_unmatchAddress(i2cp, i2cadr);
  chSysUnlock();
}


/**
 * @brief   Reconfigure I2C channel to no longer match any address
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 *
 * @details   Causes all subsequent messages to be ignored.
 *            A message being transferred that has already matched a
 *            slave address will continue being processed.
 *
 * @api
 **/
void i2cUnmatchAll(I2CDriver *i2cp)
{
  osalDbgCheck((i2cp != NULL));
  chSysLock();
  i2c_lld_unmatchAll(i2cp);
  chSysUnlock();
}


/**
 * @brief   Configure callbacks & buffers for message reception & query reply
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 * @param[in] rxMsg     @p I2CSlaveMsg struct for processing subsequent messages
 * @param[in] replyMsg  @p I2CSlaveMsg struct for processing subsequent queries
 *
 * @details             Must be called from a thread
 *                      Call i2cMatchAddress() after this to start processing
 *     Enabling match addresses before installing handler callbacks can
 *     result in locking the I2C bus when a master accesses those
 *     unconfigured slave addresses
 *
 * @api
 */
void i2cSlaveConfigure(I2CDriver *i2cp,
                   const I2CSlaveMsg *rxMsg, const I2CSlaveMsg *replyMsg)
{
  osalDbgCheck((i2cp != NULL));
  chSysLock();
  i2c_lld_slaveReceive(i2cp, rxMsg);
  i2c_lld_slaveReply(i2cp, replyMsg);
  chSysUnlock();
}


/**
 * @brief   Configure callbacks & buffers for query reply
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 * @param[in] replyMsg  @p I2CSlaveMsg struct for processing subsequent queries
 *
 * @details             Call i2cMatchAddress() after this to start processing
 *     Enabling match addresses before installing handler callbacks can
 *     result in locking the I2C bus when a master accesses those
 *     unconfigured slave addresses
 *
 * @api
 */
void i2cSlaveReceive(I2CDriver *i2cp, const I2CSlaveMsg *rxMsg)
{
  osalDbgCheck((i2cp != NULL && rxMsg != NULL));
  chSysLock();
  i2c_lld_slaveReceive(i2cp, rxMsg);
  chSysUnlock();
}


/**
 * @brief   Configure callbacks & buffers for query reply
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 * @param[in] replyMsg  @p I2CSlaveMsg struct for processing subsequent queries
 *
 * @details             Call i2cMatchAddress() after this to start processing
 *     Enabling match addresses before installing handler callbacks can
 *     result in locking the I2C bus when a master accesses those
 *     unconfigured slave addresses
 *
 * @api
 */
void i2cSlaveReply(I2CDriver *i2cp, const I2CSlaveMsg *replyMsg)
{
  osalDbgCheck((i2cp != NULL && replyMsg != NULL));
  chSysLock();
  i2c_lld_slaveReply(i2cp, replyMsg);
  chSysUnlock();
}

#endif /* HAL_USE_I2C_SLAVE */


#if I2C_USE_MUTUAL_EXCLUSION == TRUE || defined(__DOXYGEN__)
/**
 * @brief   Gains exclusive access to the I2C bus.
 * @details This function tries to gain ownership to the I2C bus, if the bus
 *          is already being used then the invoking thread is queued.
 * @pre     In order to use this function the option @p I2C_USE_MUTUAL_EXCLUSION
 *          must be enabled.
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 *
 * @api
 */
void i2cAcquireBus(I2CDriver *i2cp) {

  osalDbgCheck(i2cp != NULL);

#if CH_CFG_USE_MUTEXES
  osalMutexLock(&i2cp->mutex);
#elif CH_CFG_USE_SEMAPHORES
  osalSemWait(&i2cp->semaphore);
#endif /* CH_CFG_USE_MUTEXES */
}


/**
 * @brief   Releases exclusive access to the I2C bus.
 * @pre     In order to use this function the option @p I2C_USE_MUTUAL_EXCLUSION
 *          must be enabled.
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 *
 * @api
 */
void i2cReleaseBus(I2CDriver *i2cp) {

  osalDbgCheck(i2cp != NULL);

#if CH_CFG_USE_MUTEXES
  osalMutexUnlock(&i2cp->mutex);
#elif CH_CFG_USE_SEMAPHORES
  osalSemSignal(&i2cp->semaphore);
#endif /* CH_CFG_USE_MUTEXES */
}

#endif /* I2C_USE_MUTUAL_EXCLUSION == TRUE */

#endif /* HAL_USE_I2C == TRUE */

/** @} */
