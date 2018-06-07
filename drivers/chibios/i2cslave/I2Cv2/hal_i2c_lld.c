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
TODO:
1. Make sure slave mode registers updated OK
2. Test what of the newly inserted defines etc is actually necessary
3. Check whether all relevant features available on all ports on all processors (they are on F7, F051)
4. Do we need timer to get involved on master mode transactions? (May be multimaster requirement)
5. What about multimaster? Possibly nothing special to do, other than support all transitions round master and slave modes.
(Manual: "By default, it operates in slave mode. The interface automatically switches from slave to
master when it generates a START condition, and from master to slave if an arbitration loss
or a STOP generation occurs, allowing multimaster capability")
6. Understand use of lock timer - may only be relevant for multimaster, or even unnecessary
7. Check slave transfers > 255 bytes

NOTES:
1. 10-bit addressing, masking options not currently supported in software in slave mode
		(OAR1 hardware supports single 10-bit address matching; OAR2 supports 7-bit addressing with mask)
2. Address zero supported by setting 'General Call' flag in CR1 in slave mode (set with call to match address zero)
3. Clock stretching always enabled
4. Relevant configurable bits in CR1:
		ANFOFF (analog noise filter)
		DNF (digital noise filter bits)
5. Setting STM32_I2C_DEBUG_ENABLE to TRUE logs various events into a short circular buffer, which can then be examined using
the debugger. Alternatively, a call to i2cPrintQ(BaseSequentialStream *chp) prints the buffer. Note that the buffer only
has a write pointer, so once full its necessary to infer the start and end of the data

 */
 
/**
 * @file    STM32/I2Cv2/i2c_lld.c
 * @brief   STM32 I2C subsystem low level driver source.
 *
 * @addtogroup I2C
 * @{
 */

#include "hal.h"

#if HAL_USE_I2C || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

#if STM32_I2C_USE_DMA == TRUE
#define DMAMODE_COMMON                                                      \
  (STM32_DMA_CR_PSIZE_BYTE | STM32_DMA_CR_MSIZE_BYTE |                      \
   STM32_DMA_CR_MINC       | STM32_DMA_CR_DMEIE      |                      \
   STM32_DMA_CR_TEIE       | STM32_DMA_CR_TCIE)

#define I2C1_RX_DMA_CHANNEL                                                 \
  STM32_DMA_GETCHANNEL(STM32_I2C_I2C1_RX_DMA_STREAM,                        \
                       STM32_I2C1_RX_DMA_CHN)

#define I2C1_TX_DMA_CHANNEL                                                 \
  STM32_DMA_GETCHANNEL(STM32_I2C_I2C1_TX_DMA_STREAM,                        \
                       STM32_I2C1_TX_DMA_CHN)

#define I2C2_RX_DMA_CHANNEL                                                 \
  STM32_DMA_GETCHANNEL(STM32_I2C_I2C2_RX_DMA_STREAM,                        \
                       STM32_I2C2_RX_DMA_CHN)

#define I2C2_TX_DMA_CHANNEL                                                 \
  STM32_DMA_GETCHANNEL(STM32_I2C_I2C2_TX_DMA_STREAM,                        \
                       STM32_I2C2_TX_DMA_CHN)

#define I2C3_RX_DMA_CHANNEL                                                 \
  STM32_DMA_GETCHANNEL(STM32_I2C_I2C3_RX_DMA_STREAM,                        \
                       STM32_I2C3_RX_DMA_CHN)

#define I2C3_TX_DMA_CHANNEL                                                 \
  STM32_DMA_GETCHANNEL(STM32_I2C_I2C3_TX_DMA_STREAM,                        \
                       STM32_I2C3_TX_DMA_CHN)

#define I2C4_RX_DMA_CHANNEL                                                 \
  STM32_DMA_GETCHANNEL(STM32_I2C_I2C4_RX_DMA_STREAM,                        \
                       STM32_I2C4_RX_DMA_CHN)

#define I2C4_TX_DMA_CHANNEL                                                 \
  STM32_DMA_GETCHANNEL(STM32_I2C_I2C4_TX_DMA_STREAM,                        \
                       STM32_I2C4_TX_DMA_CHN)
#endif /* STM32_I2C_USE_DMA == TRUE */

#if STM32_I2C_USE_DMA == TRUE
#define i2c_lld_get_rxbytes(i2cp) dmaStreamGetTransactionSize((i2cp)->dmarx)
#define i2c_lld_get_txbytes(i2cp) dmaStreamGetTransactionSize((i2cp)->dmatx)
#else
#define i2c_lld_get_rxbytes(i2cp) (i2cp)->rxbytes
#define i2c_lld_get_txbytes(i2cp) (i2cp)->txbytes
#endif

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/
#define I2C_ERROR_MASK                                                      \
  ((uint32_t)(I2C_ISR_BERR | I2C_ISR_ARLO | I2C_ISR_OVR | I2C_ISR_PECERR |  \
              I2C_ISR_TIMEOUT | I2C_ISR_ALERT))

#define I2C_INT_MASK                                                        \
  ((uint32_t)(I2C_ISR_TCR | I2C_ISR_TC | I2C_ISR_STOPF | I2C_ISR_NACKF |    \
              I2C_ISR_ADDR | I2C_ISR_RXNE | I2C_ISR_TXIS))

/* Mask of interrupt bits cleared automatically - we mustn't clear ADDR else clock stretching doesn't happen */
#define I2C_INT_CLEAR_MASK                                                        \
  ((uint32_t)(I2C_ISR_TCR | I2C_ISR_TC | I2C_ISR_STOPF | I2C_ISR_NACKF |    \
              I2C_ISR_RXNE | I2C_ISR_TXIS))


/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/** @brief I2C1 driver identifier.*/
#if STM32_I2C_USE_I2C1 || defined(__DOXYGEN__)
I2CDriver I2CD1;
#endif

/** @brief I2C2 driver identifier.*/
#if STM32_I2C_USE_I2C2 || defined(__DOXYGEN__)
I2CDriver I2CD2;
#endif

/** @brief I2C3 driver identifier.*/
#if STM32_I2C_USE_I2C3 || defined(__DOXYGEN__)
I2CDriver I2CD3;
#endif

/** @brief I2C4 driver identifier.*/
#if STM32_I2C_USE_I2C4 || defined(__DOXYGEN__)
I2CDriver I2CD4;
#endif

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

#if STM32_I2C_DEBUG_ENABLE
/* 
 *	Quick and dirty queue to record event interrupts (useful for debug) 
 *
 *	Assigned codes (may be others not noted here):
 *	0x02 - NAK received
 *	0x03 - transfer complete received
 *	0x04 - Address match (records current mode before any error recovery etc)
 *	0x05 - STOP received
 *	0x06 - Part transfer complete interrupt
 *  0x07 - Recovery from untidily finished previous transaction
 *  0x08 - Recovery from untidily finished previous transaction
 *  0x09 - Recovery from untidily finished previous transaction
 *  0x10 - error in slave address match - send
 *  0x11 - error in slave address match - receive
 *  0x12 - address match - send
 *  0x13 - address match - receive
 *  0x14 - start slave receive operation
 *  0x15 - lock on pending slave receive operation (no buffer)
 *  0x16 - start slave transmit operation
 *  0x17 - lock on pending slave transmit operation (no buffer available)
 *  0x80 - new reply set
 *  0x81 - reply used immediately
 *  0x82 - new receive buffer set
 *  0x83 - receive buffer used immediately
 *  0xcc - clearing down after transmission - triggered by NAK received (usually valid)
 *  0xd0 - Slave error being signalled
 *  0xd1 - Slave error due to timeout
*/
#define QEVENTS 32

typedef struct i2cQ_t {
  uint8_t code;
  uint8_t state;            // Channel state
  uint8_t mode;             // Mode (mostly for slave)
  uint16_t param;           // Parameter sometimes used
} i2cQ_t;
i2cQ_t i2cQ[QEVENTS];
unsigned i2cI = QEVENTS;
#define qEvt(posn,info) {if (++i2cI >= QEVENTS) i2cI = 0; \
  i2cQ[i2cI].code=(posn); i2cQ[i2cI].state=(i2cp->state); i2cQ[i2cI].mode=(i2cp->mode); i2cQ[i2cI].param=(info); }

#include "chprintf.h"

void i2cPrintQ(BaseSequentialStream *chp)
{
  uint8_t i;
  if (QEVENTS == 0)
  {
    chprintf(chp, "I2C Debug queue disabled\r\n");
  }
  else
  {
    chprintf(chp, "I2C debug ring - write pointer currently %02d\r\n", i2cI);
  }
  for (i = 0; i < QEVENTS; i++)
  {
    chprintf(chp, "%02d: %02x->%02x %02x %04x\r\n", i, i2cQ[i].code, i2cQ[i].state, i2cQ[i].mode, i2cQ[i].param);
    if (i2cQ[i].code == 0) break;           // Handle partially filled queue
  }
}

#else
#define qEvt(posn,info)
#endif




#if HAL_USE_I2C_SLAVE   /* I2C slave mode support */


void I2CSlaveDummyCB(I2CDriver *i2cp)
/*
  dummy callback -- placeholder to ignore event
*/
{(void)i2cp;}

  /* lock bus on receive or reply message */
const I2CSlaveMsg I2CSlaveLockOnMsg = {
  0, NULL, I2CSlaveDummyCB, I2CSlaveDummyCB, I2CSlaveDummyCB
};

#endif

/*===========================================================================*/
/* 			Driver local functions.                                          */
/*===========================================================================*/

#if HAL_USE_I2C_MASTER
/**
 * @brief   Slave (remote) address setup in master mode.
 * @note    The RW bit is set to zero internally.
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 * @param[in] addr      slave device address
 *
 * @notapi
 */
static void i2c_lld_set_address(I2CDriver *i2cp, i2caddr_t addr) {
  I2C_TypeDef *dp = i2cp->i2c;

  /* Address alignment depends on the addressing mode selected.*/
  if ((i2cp->config->cr2 & I2C_CR2_ADD10) == 0U)
    dp->CR2 = (uint32_t)addr << 1U;
  else
    dp->CR2 = (uint32_t)addr;
}
#endif



/**
 * @brief   I2C RX transfer setup.
 * @note	Configures transfer count and related flags
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 *
 * @notapi
 */
static void i2c_lld_setup_rx_transfer(I2CDriver *i2cp) {
  I2C_TypeDef *dp = i2cp->i2c;
  uint32_t reload;
  size_t n;

  /* The unit can transfer 255 bytes maximum in a single operation (device constraint). */
#if STM32_I2C_USE_DMA
  if (i2cp->config->rxchar_cb)
  {
    n = i2cp->rxbytes;        // Always interrupt-driven if we have a receive callback
  }
  else
  {
    n = i2c_lld_get_rxbytes(i2cp);      // Otherwise get length from DMA or counter as appropriate
  }
#else
  n = i2cp->rxbytes;
#endif
  if (n > 255U) {
    n = 255U;
    reload = I2C_CR2_RELOAD;
  }
  else {
    reload = 0U;
  }

  /* Configures the CR2 registers with both the calculated and static
     settings. (Nothing much relevant in static settings - just PEC for SMBUS? */
  dp->CR2 = (dp->CR2 & ~(I2C_CR2_NBYTES | I2C_CR2_RELOAD)) | i2cp->config->cr2 | I2C_CR2_RD_WRN |
            (n << 16U) | reload;
}



/**
 * @brief   I2C TX transfer setup.
 * @note	Configures transfer count and related flags
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 *
 * @notapi
 */
static void i2c_lld_setup_tx_transfer(I2CDriver *i2cp) {
  I2C_TypeDef *dp = i2cp->i2c;
  uint32_t reload;
  size_t n;

  /* The unit can transfer 255 bytes maximum in a single operation. */
  n = i2c_lld_get_txbytes(i2cp);            // Get transaction size from DMA or buffer as configured
  if (n > 255U) {
    n = 255U;
    reload = I2C_CR2_RELOAD;
  }
  else {
    reload = 0U;
  }

  /* Configures the CR2 registers with both the calculated and static
     settings.*/
  dp->CR2 = (dp->CR2 & ~(I2C_CR2_NBYTES | I2C_CR2_RELOAD)) | i2cp->config->cr2 |
            (n << 16U) | reload;
}



/**
 * @brief   Aborts an I2C transaction.
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 *
 * @notapi
 */
static void i2c_lld_abort_operation(I2CDriver *i2cp) {
  I2C_TypeDef *dp = i2cp->i2c;

// Note: clearing PE doesn't affect configuration bits (including slave addresses)
  if (dp->CR1 & I2C_CR1_PE) {
    /* Stops the I2C peripheral.*/
    dp->CR1 &= ~I2C_CR1_PE;
    while (dp->CR1 & I2C_CR1_PE)
      dp->CR1 &= ~I2C_CR1_PE;
    dp->CR1 |= I2C_CR1_PE;
  }

#if STM32_I2C_USE_DMA == TRUE
  /* Stops the associated DMA streams.*/
  dmaStreamDisable(i2cp->dmatx);
  dmaStreamDisable(i2cp->dmarx);
#else
  dp->CR1 &= ~(I2C_CR1_TXIE | I2C_CR1_RXIE);		// Stop byte-orientated interrupts
#endif
}



#if HAL_USE_I2C_SLAVE || HAL_USE_I2C_LOCK
/**
 * @brief   stop transaction timeout countdown
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 *
 * @notapi
 */
static inline void stopTimer(I2CDriver *i2cp)
{
    osalSysLockFromISR();
    chVTResetI(&i2cp->timer);
    osalSysUnlockFromISR();
}
#else
#define stopTimer(ignored)  {}
#endif



#if HAL_USE_I2C_SLAVE   /* I2C slave mode support */

/**
 * @brief   report error via slave exception callback
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 *
 * @note     moves back to the idle mode
 * @notapi
 */
static inline void reportSlaveError(I2CDriver *i2cp) {
  if (i2cp->mode >= i2cIsMaster) return;
  qEvt(0xd0, i2cp->slaveErrors);
  const I2CSlaveMsg *xfer = i2cp->mode >= i2cSlaveReplying ?
                                          i2cp->slaveReply : i2cp->slaveRx;
  if (xfer->exception)
      xfer->exception(i2cp);
  i2cp->mode = i2cIdle;
  i2cp->targetAdr = i2cInvalidAdr;
}


/**
 * @brief   Handling of stalled slave mode I2C transactions - timer handler.
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 *
 * @notapi
 */
static void slaveTimeExpired(void *i2cv) {
  I2CDriver *i2cp = i2cv;

  if (i2cp->mode < i2cIsMaster)
  {
    i2c_lld_abort_operation(i2cp);
    reportSlaveError(i2cp);
    qEvt(0xd1, 0);
  }
}


/**
 * @brief   start or restart slave mode transaction
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 * @param[in] targetAdr slave address which was matched
 *
 * @notapi
 */
static inline void i2cStartSlaveAction(I2CDriver *i2cp, i2caddr_t targetAdr)
{
  stopTimer(i2cp);
  i2cp->targetAdr = targetAdr;
  i2cp->slaveBytes = 0;
  i2cp->slaveErrors = 0;
  if (i2cp->slaveTimeout != TIME_INFINITE)
  {
    osalSysLockFromISR();
    chVTSetI(&i2cp->timer, i2cp->slaveTimeout, slaveTimeExpired, i2cp);
    osalSysUnlockFromISR();
  }
}


/**
 * @brief   end slave receive message DMA
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 *
 * @notapi
 */
static inline void i2cEndSlaveRxDMA(I2CDriver *i2cp)
{
  size_t bytesRemaining = i2c_lld_get_rxbytes(i2cp);
  if (i2cp->slaveBytes)
    i2cp->slaveBytes += 0xffff - bytesRemaining;
  else
    i2cp->slaveBytes = i2cp->slaveRx->size - bytesRemaining;
#if STM32_I2C_USE_DMA == TRUE
      /* Disabling RX DMA channel.*/
      dmaStreamDisable(i2cp->dmarx);
#else
  i2cp->i2c->CR1 &= ~(I2C_CR1_RXIE);
#endif
}



/**
 * @brief   end slave transmit DMA
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 * @param[in] bytesRemaining  bytes lost in output queue
 *
 * @notapi
 */
static inline void i2cEndSlaveTxDMA(I2CDriver *i2cp, size_t bytesRemaining)
{
  bytesRemaining += i2c_lld_get_rxbytes(i2cp);
  if (i2cp->slaveBytes)
    i2cp->slaveBytes += 0xffff - bytesRemaining;
  else
    i2cp->slaveBytes = i2cp->slaveReply->size - bytesRemaining;
#if STM32_I2C_USE_DMA == TRUE
      /* Disabling TX DMA channel.*/
      dmaStreamDisable(i2cp->dmatx);
#else
  i2cp->i2c->CR1 &= ~(I2C_CR1_TXIE);
#endif
}

#endif




/**
 *	@brief	Start a receive transaction (by enabling DMA, or enabling Rx character interrupts)
 *
 *	@note   All registers etc must be set up first
 */
static inline void i2cStartReceive(I2CDriver *i2cp)
{
#if STM32_I2C_USE_DMA == TRUE
  if (i2cp->config->rxchar_cb)
  {
    // Callback in use - use interrupt-driven transfer
    i2cp->i2c->CR1 |= I2C_CR1_TCIE | I2C_CR1_RXIE;
  }
  else
  {
    /* Enabling RX DMA.*/
    dmaStreamEnable(i2cp->dmarx);

    /* Transfer complete interrupt enabled.*/
    i2cp->i2c->CR1 |= I2C_CR1_TCIE;
  }
#else

  /* Transfer complete and RX interrupts enabled.*/
  i2cp->i2c->CR1 |= I2C_CR1_TCIE | I2C_CR1_RXIE;
#endif
}


/**
 *	@brief	Disable transmit data transfer, whether DMA or interrupt-driven
 */
static inline void i2cDisableTransmitOperation(I2CDriver *i2cp)
{
#if STM32_I2C_USE_DMA == TRUE
      /* Disabling TX DMA channel.*/
      dmaStreamDisable(i2cp->dmatx);
#else
  i2cp->i2c->CR1 &= ~(I2C_CR1_TXIE);
#endif
}


/**
 *	@brief	Disable receive data transfer, whether DMA or interrupt-driven
 */
static inline void i2cDisableReceiveOperation(I2CDriver *i2cp)
{
#if STM32_I2C_USE_DMA == TRUE
      /* Disabling RX DMA channel.*/
      dmaStreamDisable(i2cp->dmarx);
#else
  i2cp->i2c->CR1 &= ~(I2C_CR1_RXIE);
#endif
}



/*===========================================================================*/
/* 			            Shared ISR Code			                             */
/*===========================================================================*/

/**
 * @brief   I2C shared ISR code - 'Normal' (non-error) interrupts.
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 * @param[in] isr       content of the ISR register to be decoded (no masking applied)
 *
 * @notapi
 */
static void i2c_lld_serve_interrupt(I2CDriver *i2cp, uint32_t isr) {
  I2C_TypeDef *dp = i2cp->i2c;

  /* Check for received NACK, the transfer is aborted. Do this in all modes */
  if ((isr & I2C_ISR_NACKF) != 0U)
  {
	qEvt(2, 0);

	i2cDisableReceiveOperation(i2cp);
	i2cDisableTransmitOperation(i2cp);
    #if HAL_USE_I2C_SLAVE
    /* NACK of last byte transmitted in slave response is NORMAL -- not an error! */
      if (i2cp->mode == i2cSlaveReplying)
      {
        qEvt(0xcc,0);
        i2cEndSlaveTxDMA(i2cp, 1);
        if (i2cp->slaveReply->processMsg)
            i2cp->slaveReply->processMsg(i2cp);
        i2cp->targetAdr = i2cInvalidAdr;
        stopTimer(i2cp);
        return;
      }
    #endif

    /* Error flag.*/
    i2cp->errors |= I2C_ACK_FAILURE;

    /* Transaction finished, send the STOP. */
    dp->CR2 |= I2C_CR2_STOP;

    /* Make sure no more interrupts.*/
    dp->CR1 &= ~(I2C_CR1_TCIE | I2C_CR1_TXIE | I2C_CR1_RXIE | I2C_CR1_STOPIE);

    if (i2cp->mode < i2cIsMaster)
    {
      i2cp->mode = i2cIdle;
    }
    else
    {
      /* Master mode - Errors are signalled to the upper layer.*/
      i2cp->mode = i2cIdle;
      // Must only wake up thread in master mode.
      _i2c_wakeup_isr(i2cp);          // This is a normal completion
    }

    return;
  }


#if STM32_I2C_USE_DMA == FALSE
  /* Handling of data transfer if the DMA mode is disabled - done character by character. Mode should be irrelevant */
  {
    uint32_t cr1 = dp->CR1;

    if ((i2cp->state == I2C_ACTIVE_TX) || (i2cp->mode == i2cSlaveReplying))
	{
      /* Transmission phase.*/
      if (((cr1 &I2C_CR1_TXIE) != 0U) && ((isr & I2C_ISR_TXIS) != 0U)) {
        dp->TXDR = (uint32_t)*i2cp->txptr;
        i2cp->txptr++;
        i2cp->txbytes--;
        if (i2cp->txbytes == 0U) {
          dp->CR1 &= ~I2C_CR1_TXIE;		// Last byte sent - stop Tx interrupt
        }
      }
    }
    else 
	{
      /* Receive phase.*/
      if (((cr1 & I2C_CR1_RXIE) != 0U) && ((isr & I2C_ISR_RXNE) != 0U)) {
        uint8_t c;
        *i2cp->rxptr = c = (uint8_t)dp->RXDR;
        i2cp->rxptr++;
        i2cp->rxbytes--;
        if (i2cp->config->rxchar_cb)
        {
          if (i2cp->config->rxchar_cb(i2cp, c) > 0)
          {
            /* Transaction finished, send the STOP. */
            dp->CR2 |= I2C_CR2_STOP;

            /* Make sure no more interrupts.*/
            dp->CR1 &= ~(I2C_CR1_TCIE | I2C_CR1_TXIE | I2C_CR1_RXIE | I2C_CR1_STOPIE);

            if (i2cp->mode < i2cIsMaster)
            {
              i2cp->mode = i2cIdle;
            }
            else
            {
              /* Master mode - Errors are signalled to the upper layer.*/
              i2cp->mode = i2cIdle;
              // Must only wake up thread in master mode.
              _i2c_wakeup_isr(i2cp);          // This is a normal completion
            }

            return;
          }
        }
        if (i2cp->rxbytes == 0U) {
          dp->CR1 &= ~I2C_CR1_RXIE;			// Buffer full - stop reception (TODO: Should we send NAK?? Only possible in slave mode)
        }
      }
    }
  }
#else
  /* Receive character phase with callback enabled. */
  if ((i2cp->state == I2C_ACTIVE_RX) || (i2cp->mode == i2cMasterRxing))
  {
    uint32_t cr1 = dp->CR1;
    if (((cr1 & I2C_CR1_RXIE) != 0U) && ((isr & I2C_ISR_RXNE) != 0U)) {
      uint8_t c;
      c = (uint8_t)dp->RXDR;
      *i2cp->rxptr = c;
      i2cp->rxptr++;
      i2cp->rxbytes--;
      if (i2cp->config->rxchar_cb)
      {
        if (i2cp->config->rxchar_cb(i2cp, c) > 0)
        {
          /* Transaction finished, send the STOP. */
          dp->CR2 |= I2C_CR2_STOP;

          /* Make sure no more interrupts.*/
          dp->CR1 &= ~(I2C_CR1_TCIE | I2C_CR1_TXIE | I2C_CR1_RXIE | I2C_CR1_STOPIE);

          if (i2cp->mode < i2cIsMaster)
          {
            i2cp->mode = i2cIdle;
          }
          else
          {
            /* Master mode - Errors are signalled to the upper layer.*/
            i2cp->mode = i2cIdle;
            // Must only wake up thread in master mode.
            _i2c_wakeup_isr(i2cp);          // This is a normal completion
          }

          return;
        }
      }
      if (i2cp->rxbytes == 0U) {
        dp->CR1 &= ~I2C_CR1_RXIE;         // Buffer full - stop reception (TODO: Should we send NAK?? Only possible in slave mode)
      }
    }
  }
#endif



  /* Partial transfer handling, restarting the transfer and returning. */
  if ((isr & I2C_ISR_TCR) != 0U)
  {
    qEvt(0x06, 0);
    if ((i2cp->state == I2C_ACTIVE_TX) || (i2cp->mode == i2cSlaveReplying)) {
      i2c_lld_setup_tx_transfer(i2cp);
    }
    if ((i2cp->state == I2C_ACTIVE_RX) || (i2cp->mode == i2cSlaveRxing)) {
      i2c_lld_setup_rx_transfer(i2cp);
    }
    return;
  }



  /* The following condition is true if a transfer phase has been completed. */
  if ((isr & I2C_ISR_TC) != 0U) 
  {
    qEvt(3,i2cp->state);
#if HAL_USE_I2C_SLAVE
    switch (i2cp->mode)
    {
    case i2cLockedRxing :     /* stretching clock before receiving message - Rx buffer might be full */
    case i2cLockedReplying :
      break;                // TODO: Two unsupported cases to consider - maybe they can't happen
    case i2cSlaveReplying :                     // Must have just finished sending a reply in slave mode
      break;                                    // Just go on to send STOP bit and tidy up

    case i2cSlaveRxing :                        // Must have just received a message - process if we can
      i2cEndSlaveRxDMA(i2cp);
      qEvt(0x20, 0);
      if (i2cp->slaveRx->processMsg)
          i2cp->slaveRx->processMsg(i2cp);
      // TODO: Should get a reply message set - if so, start to send it and return
      return;           // For now, see what happens if we just return
      break;
    default :               // Assume a master mode
#endif
      if (i2cp->state == I2C_ACTIVE_TX) {
        /* End of the transmit phase.*/

          i2cDisableTransmitOperation(i2cp);			// Disable

        /* Starting receive phase if necessary.*/
        if (i2c_lld_get_rxbytes(i2cp) > 0U) {
          /* Setting up the peripheral.*/
          i2c_lld_setup_rx_transfer(i2cp);

  #if STM32_I2C_USE_DMA == TRUE
  // If receive callback enabled, always transfer using interrupts
          if (i2cp->config->rxchar_cb)
          {
            /* RX interrupt enabled.*/
            dp->CR1 |= I2C_CR1_RXIE;
          }
          else
          {
            /* Enabling RX DMA.*/
            dmaStreamEnable(i2cp->dmarx);
          }
  #else
          /* RX interrupt enabled.*/
          dp->CR1 |= I2C_CR1_RXIE;
  #endif

          /* Starts the read operation.*/
          dp->CR2 |= I2C_CR2_START;

          /* State change.*/
          i2cp->state = I2C_ACTIVE_RX;
          i2cp->mode = i2cMasterRxing;

          /* Note, returning because the transaction is not over yet.*/
          return;
        }
      }
      else
      {
        /* End of the receive phase.*/
          i2cDisableReceiveOperation(i2cp);
      }

#if HAL_USE_I2C_SLAVE
    }
#endif

    /* Transaction finished sending the STOP. */
    dp->CR2 |= I2C_CR2_STOP;

    /* Make sure no more 'Transfer Complete' interrupts. */
    dp->CR1 &= ~I2C_CR1_TCIE;

    /* Normal transaction end.*/
    if (i2cp->mode < i2cIsMaster)
    {
      // Slave mode - just move to idle state
      i2cp->mode = i2cIdle;
    }
    else
    {
      i2cp->mode = i2cIdle;
      // Must only wake up thread in master mode
      _i2c_wakeup_isr(i2cp);
    }
  }


#if HAL_USE_I2C_SLAVE
	uint8_t abort = 0;
	/* Check for address match - if so, we're slave */
	if ((isr & I2C_ISR_ADDR) != 0U) 
	{
		i2caddr_t targetAdr = (isr & I2C_ISR_ADDCODE) >> 17;        // Identify which slave address used
		uint8_t xferDir = (isr & I2C_ISR_DIR) ? 0 : 1;				// Status bit is 0 for receive, 1 for transmit. xferDir inverts sense
		dp->CR1 |= I2C_CR1_STOPIE;									// Enable STOP interrupt so we know when slave transaction done

        /* First, tidy up from previous transactions as necessary */
        qEvt(0x04, 0);
        switch (i2cp->mode) {
            case i2cIdle:
                break;
            case i2cSlaveRxing:             /* Previous transaction not completed properly, or
                                              maybe we were sent a message without being asked for a reply */
                qEvt(0x07, 0);
                i2cEndSlaveRxDMA(i2cp);
                if (i2cp->slaveRx->processMsg)
                    i2cp->slaveRx->processMsg(i2cp);            // Execute callback if defined
                break;
            case i2cSlaveReplying:   /* Master did not NACK last transmitted byte (most likely picked up by NAK handler) */
              qEvt(0x08, 0);
              if (!xferDir)
              {
                qEvt(0x09, 0);
                i2cEndSlaveTxDMA(i2cp, 2);
                if (i2cp->slaveReply->processMsg)
                    i2cp->slaveReply->processMsg(i2cp);
                break;
              }
              // Intentionally don't break if we're addressed to receive
            default:
                // todo: Does this lot happen in the right order? Is an abort appropriate? Or should we just continue?
                qEvt(0x10 + xferDir, 0);
                i2cp->slaveErrors = I2C_UNKNOWN_ERROR + i2cp->mode;
                i2c_lld_abort_operation(i2cp);        /* reset and reinit */
                stopTimer(i2cp);
                reportSlaveError(i2cp);                 // This clears down to idle
                abort = 1;
            }
        if (!abort)
        {
            qEvt(0x12 + xferDir, (i2cp->slaveNextRx->size));
            if (xferDir)
            {
                /* Start Receive */
	            /* If receive buffer still full, need to extend clock for timeout. Otherwise set up to receive */
                dp->CR1 &= ~I2C_CR1_SBC;                           // Not needed with receive
	            i2cStartSlaveAction(i2cp, targetAdr);
				
				const I2CSlaveMsg *rx = i2cp->slaveNextRx;
				if (rx->adrMatched)                                 // Q: Can rx ever be NULL?
					rx->adrMatched(i2cp);							// Execute callback on address match if specified
				rx = i2cp->slaveRx = i2cp->slaveNextRx;             // Reload message pointer in case callback changed it
				if (rx->body && rx->size)
				{
					/* Receive buffer available - can receive immediately. Set up slave RX DMA */
	                i2c_lld_setup_rx_transfer(i2cp);
					#if STM32_I2C_USE_DMA == TRUE
					  /* RX DMA setup.*/
					  dmaStreamSetMode(i2cp->dmarx, i2cp->rxdmamode);
					  dmaStreamSetMemory0(i2cp->dmarx, rx->body);
					  dmaStreamSetTransactionSize(i2cp->dmarx, rx->size);
					#else
					  i2cp->rxptr   = rx->body;
					  i2cp->rxbytes = rx->size;
					#endif

					i2cStartReceive(i2cp);
					dp->ICR = I2C_ISR_ADDR;                          // We can release the clock stretch now
                    i2cp->mode = i2cSlaveRxing;
					qEvt(0x14,0);
				}
				else
				{
				  /* No reply set up - hold clock low and wait (happens automatically) */
                  qEvt(0x15,0);
                  i2cp->mode = i2cLockedRxing;
				}
            }
            else
            {
                /* Start Transmit */
				i2cStartSlaveAction(i2cp, targetAdr);
				const I2CSlaveMsg *reply = i2cp->slaveNextReply;
                const I2CSlaveMsg *rx = i2cp->slaveNextRx;              // Receive control block
                if (rx->adrMatched)                                     // Q: Can rx ever be NULL?
                    rx->adrMatched(i2cp);                               // Execute callback on address match if specified
				reply = i2cp->slaveReply = i2cp->slaveNextReply;		// Reload message pointer in case callback changed it
				if (reply->body && reply->size) 
				{
					/* Reply message available - can send immediately. Set up slave TX DMA */
                    #if STM32_I2C_USE_DMA == TRUE
					dmaStreamSetMode(i2cp->dmatx, i2cp->txdmamode);
					dmaStreamSetMemory0(i2cp->dmatx, reply->body);
					dmaStreamSetTransactionSize(i2cp->dmatx, reply->size);
	                /* Start transmission */
	                i2c_lld_setup_tx_transfer(i2cp);

                    /* Enabling TX DMA.*/
                    dmaStreamEnable(i2cp->dmatx);

                    /* Transfer complete interrupt enabled.*/
                    dp->CR1 |= I2C_CR1_TCIE;
                    #else
                      /* Start transmission */
                      i2cp->txptr   = reply->body;
                      i2cp->txbytes = reply->size;
                      i2c_lld_setup_tx_transfer(i2cp);
                      /* Transfer complete and TX character interrupts enabled.*/
                      dp->CR1 |= I2C_CR1_TCIE | I2C_CR1_TXIE;
                    #endif
                      qEvt(0x16,0);
                      i2cp->mode = i2cSlaveReplying;
                      dp->CR1 |= I2C_CR1_SBC;                           // Need this to enable byte counter in transmit mode
                      dp->ICR = I2C_ISR_ADDR;                          // We can release the clock stretch now
				}
				else
				{
					// clock is automatically stretched if we don't clear the status bit
					//dp->CR2 &= (uint16_t)(~I2C_CR2_ITEVTEN);
				    qEvt(0x17, 0);
					i2cp->mode = i2cLockedReplying;
				}
		  }
        }   /* if !abort */
	  }
	  if ((isr & I2C_ISR_STOPF) != 0U) {
	  /*
	   *	STOP received:
	   *		in master mode, if generated by peripheral - can probably just ignore
	   *		in slave mode, if detected on bus (from any source?)
	   *
	   *	Clear everything down - particularly relevant in slave mode
	   */
	    qEvt(0x05, 0);
		dp->CR1 &= ~I2C_CR1_STOPIE;					// Disable STOP interrupt
	    i2cDisableReceiveOperation(i2cp);           // These two may not be necessary
	    i2cDisableTransmitOperation(i2cp);
	    stopTimer(i2cp);
		i2cp->mode = i2cIdle;
	  }
#endif
}



/**
 * @brief   I2C error handler.
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 * @param[in] isr       content of the ISR register to be decoded (no masking applied)
 *
 * @notapi
 */
static void i2c_lld_serve_error_interrupt(I2CDriver *i2cp, uint32_t isr) {

	i2cDisableReceiveOperation(i2cp);
	i2cDisableTransmitOperation(i2cp);
	stopTimer(i2cp);

#if HAL_USE_I2C_SLAVE
    // In slave mode, just clock errors and return
	if (i2cp->mode < i2cIsMaster)
	{
	  reportSlaveError(i2cp);           // This clears down to idle
	  return;
	}
#endif

  if (isr & I2C_ISR_BERR)
    i2cp->errors |= I2C_BUS_ERROR;

  if (isr & I2C_ISR_ARLO)
    i2cp->errors |= I2C_ARBITRATION_LOST;

  if (isr & I2C_ISR_OVR)
    i2cp->errors |= I2C_OVERRUN;

  if (isr & I2C_ISR_TIMEOUT)
    i2cp->errors |= I2C_TIMEOUT;

  /* If some error has been identified then wake up the waiting thread.*/
  if (i2cp->errors != I2C_NO_ERROR)
  {
	i2cp->mode = i2cIdle;
    _i2c_wakeup_error_isr(i2cp);
  }
}





#if HAL_USE_I2C_LOCK    /* I2C bus locking support */

/**
 * @brief   Handling of expired master bus lock timer
 *
 * @param[in] i2cv      pointer to the @p I2CDriver object
 *
 * @notapi
 */
static void lockExpired(void *i2cv) {
  I2CDriver *i2cp = i2cv;

  if (i2cp->mode == i2cIsMaster && !i2cp->thread) {  /* between transactions */
    i2cp->i2c->CR2 |= I2C_CR2_STOP;
    i2cp->mode = i2cIdle;
  }
  i2cp->lockDuration = TIME_IMMEDIATE;
}




/**
 * @brief   Lock I2C bus at the beginning of the next message
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 * @param[in] lockDuration   max number of ticks to hold bus locked
 *                      - @a TIME_INFINITE no timeout.
 *                      - @a TIME_IMMEDIATE unlock the bus immediately
 *                      .
 *
 *  Lock I2C bus at the beginning of the next message sent
 *  for a maximum of lockDuration ticks.  No other I2C masters will
 *  be allowed to interrupt until i2cUnlock() is called.
 *
 * @notapi
 **/
void i2c_lld_lock(I2CDriver *i2cp, systime_t lockDuration)
{
  i2cp->lockDuration = lockDuration;
  if (i2cp->mode >= i2cIsMaster) {
    stopTimer(i2cp);
    if (lockDuration == TIME_IMMEDIATE)
      lockExpired(i2cp);
    else if (lockDuration != TIME_INFINITE)
      chVTSetI(&i2cp->timer, lockDuration, lockExpired, i2cp);
  }
}

#endif

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

#if STM32_I2C_USE_I2C1 || defined(__DOXYGEN__)
#if defined(STM32_I2C1_GLOBAL_HANDLER) || defined(__DOXYGEN__)
/**
 * @brief   I2C1 event interrupt handler.
 *
 * @notapi
 */
OSAL_IRQ_HANDLER(STM32_I2C1_GLOBAL_HANDLER) {
  uint32_t isr = I2CD1.i2c->ISR;

  OSAL_IRQ_PROLOGUE();

  /* Clearing IRQ bits.*/
  I2CD1.i2c->ICR = isr & ~I2C_ISR_ADDR;

  if (isr & I2C_ERROR_MASK)
    i2c_lld_serve_error_interrupt(&I2CD1, isr);
  else if (isr & I2C_INT_MASK)
    i2c_lld_serve_interrupt(&I2CD1, isr);

  OSAL_IRQ_EPILOGUE();
}

#elif defined(STM32_I2C1_EVENT_HANDLER) && defined(STM32_I2C1_ERROR_HANDLER)
OSAL_IRQ_HANDLER(STM32_I2C1_EVENT_HANDLER) {
  uint32_t isr = I2CD1.i2c->ISR;

  OSAL_IRQ_PROLOGUE();

  /* Clearing IRQ bits.*/
  I2CD1.i2c->ICR = isr & I2C_INT_CLEAR_MASK;

  i2c_lld_serve_interrupt(&I2CD1, isr);

  OSAL_IRQ_EPILOGUE();
}

OSAL_IRQ_HANDLER(STM32_I2C1_ERROR_HANDLER) {
  uint32_t isr = I2CD1.i2c->ISR;

  OSAL_IRQ_PROLOGUE();

  /* Clearing IRQ bits.*/
  I2CD1.i2c->ICR = isr & I2C_ERROR_MASK;

  i2c_lld_serve_error_interrupt(&I2CD1, isr);

  OSAL_IRQ_EPILOGUE();
}

#else
#error "I2C1 interrupt handlers not defined"
#endif
#endif /* STM32_I2C_USE_I2C1 */

#if STM32_I2C_USE_I2C2 || defined(__DOXYGEN__)
#if defined(STM32_I2C2_GLOBAL_HANDLER) || defined(__DOXYGEN__)
/**
 * @brief   I2C2 event interrupt handler.
 *
 * @notapi
 */
OSAL_IRQ_HANDLER(STM32_I2C2_GLOBAL_HANDLER) {
  uint32_t isr = I2CD2.i2c->ISR;

  OSAL_IRQ_PROLOGUE();

  /* Clearing IRQ bits.*/
  I2CD2.i2c->ICR = isr & ~I2C_ISR_ADDR;

  if (isr & I2C_ERROR_MASK)
    i2c_lld_serve_error_interrupt(&I2CD2, isr);
  else if (isr & I2C_INT_MASK)
    i2c_lld_serve_interrupt(&I2CD2, isr);

  OSAL_IRQ_EPILOGUE();
}

#elif defined(STM32_I2C2_EVENT_HANDLER) && defined(STM32_I2C2_ERROR_HANDLER)
OSAL_IRQ_HANDLER(STM32_I2C2_EVENT_HANDLER) {
  uint32_t isr = I2CD2.i2c->ISR;

  OSAL_IRQ_PROLOGUE();

  /* Clearing IRQ bits.*/
  I2CD2.i2c->ICR = isr & I2C_INT_CLEAR_MASK;

  i2c_lld_serve_interrupt(&I2CD2, isr);

  OSAL_IRQ_EPILOGUE();
}

OSAL_IRQ_HANDLER(STM32_I2C2_ERROR_HANDLER) {
  uint32_t isr = I2CD2.i2c->ISR;

  OSAL_IRQ_PROLOGUE();

  /* Clearing IRQ bits.*/
  I2CD2.i2c->ICR = isr & I2C_ERROR_MASK;

  i2c_lld_serve_error_interrupt(&I2CD2, isr);

  OSAL_IRQ_EPILOGUE();
}

#else
#error "I2C2 interrupt handlers not defined"
#endif
#endif /* STM32_I2C_USE_I2C2 */

#if STM32_I2C_USE_I2C3 || defined(__DOXYGEN__)
#if defined(STM32_I2C3_GLOBAL_HANDLER) || defined(__DOXYGEN__)
/**
 * @brief   I2C3 event interrupt handler.
 *
 * @notapi
 */
OSAL_IRQ_HANDLER(STM32_I2C3_GLOBAL_HANDLER) {
  uint32_t isr = I2CD3.i2c->ISR;

  OSAL_IRQ_PROLOGUE();

  /* Clearing IRQ bits.*/
  I2CD3.i2c->ICR = isr & ~I2C_ISR_ADDR;

  if (isr & I2C_ERROR_MASK)
    i2c_lld_serve_error_interrupt(&I2CD3, isr);
  else if (isr & I2C_INT_MASK)
    i2c_lld_serve_interrupt(&I2CD3, isr);

  OSAL_IRQ_EPILOGUE();
}

#elif defined(STM32_I2C3_EVENT_HANDLER) && defined(STM32_I2C3_ERROR_HANDLER)
OSAL_IRQ_HANDLER(STM32_I2C3_EVENT_HANDLER) {
  uint32_t isr = I2CD3.i2c->ISR;

  OSAL_IRQ_PROLOGUE();

  /* Clearing IRQ bits.*/
  I2CD3.i2c->ICR = isr & I2C_INT_CLEAR_MASK;

  i2c_lld_serve_interrupt(&I2CD3, isr);

  OSAL_IRQ_EPILOGUE();
}

OSAL_IRQ_HANDLER(STM32_I2C3_ERROR_HANDLER) {
  uint32_t isr = I2CD3.i2c->ISR;

  OSAL_IRQ_PROLOGUE();

  /* Clearing IRQ bits.*/
  I2CD3.i2c->ICR = isr & I2C_ERROR_MASK;

  i2c_lld_serve_error_interrupt(&I2CD3, isr);

  OSAL_IRQ_EPILOGUE();
}

#else
#error "I2C3 interrupt handlers not defined"
#endif
#endif /* STM32_I2C_USE_I2C3 */

#if STM32_I2C_USE_I2C4 || defined(__DOXYGEN__)
#if defined(STM32_I2C4_GLOBAL_HANDLER) || defined(__DOXYGEN__)
/**
 * @brief   I2C4 event interrupt handler.
 *
 * @notapi
 */
OSAL_IRQ_HANDLER(STM32_I2C4_GLOBAL_HANDLER) {
  uint32_t isr = I2CD4.i2c->ISR;

  OSAL_IRQ_PROLOGUE();

  /* Clearing IRQ bits.*/
  I2CD4.i2c->ICR = isr & ~I2C_ISR_ADDR;

  if (isr & I2C_ERROR_MASK)
    i2c_lld_serve_error_interrupt(&I2CD4, isr);
  else if (isr & I2C_INT_MASK)
    i2c_lld_serve_interrupt(&I2CD4, isr);

  OSAL_IRQ_EPILOGUE();
}

#elif defined(STM32_I2C4_EVENT_HANDLER) && defined(STM32_I2C4_ERROR_HANDLER)
OSAL_IRQ_HANDLER(STM32_I2C4_EVENT_HANDLER) {
  uint32_t isr = I2CD4.i2c->ISR;

  OSAL_IRQ_PROLOGUE();

  /* Clearing IRQ bits.*/
  I2CD4.i2c->ICR = isr & I2C_INT_CLEAR_MASK;

  i2c_lld_serve_interrupt(&I2CD4, isr);

  OSAL_IRQ_EPILOGUE();
}

OSAL_IRQ_HANDLER(STM32_I2C4_ERROR_HANDLER) {
  uint32_t isr = I2CD4.i2c->ISR;

  OSAL_IRQ_PROLOGUE();

  /* Clearing IRQ bits.*/
  I2CD4.i2c->ICR = isr & I2C_ERROR_MASK;

  i2c_lld_serve_error_interrupt(&I2CD4, isr);

  OSAL_IRQ_EPILOGUE();
}

#else
#error "I2C4 interrupt handlers not defined"
#endif
#endif /* STM32_I2C_USE_I2C4 */

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Low level I2C driver initialization.
 *
 * @notapi
 */
void i2c_lld_init(void) {

#if STM32_I2C_USE_I2C1
  i2cObjectInit(&I2CD1);
  I2CD1.thread = NULL;
  I2CD1.i2c    = I2C1;
#if STM32_I2C_USE_DMA == TRUE
  I2CD1.dmarx  = STM32_DMA_STREAM(STM32_I2C_I2C1_RX_DMA_STREAM);
  I2CD1.dmatx  = STM32_DMA_STREAM(STM32_I2C_I2C1_TX_DMA_STREAM);
#endif
#endif /* STM32_I2C_USE_I2C1 */

#if STM32_I2C_USE_I2C2
  i2cObjectInit(&I2CD2);
  I2CD2.thread = NULL;
  I2CD2.i2c    = I2C2;
#if STM32_I2C_USE_DMA == TRUE
  I2CD2.dmarx  = STM32_DMA_STREAM(STM32_I2C_I2C2_RX_DMA_STREAM);
  I2CD2.dmatx  = STM32_DMA_STREAM(STM32_I2C_I2C2_TX_DMA_STREAM);
#endif
#endif /* STM32_I2C_USE_I2C2 */

#if STM32_I2C_USE_I2C3
  i2cObjectInit(&I2CD3);
  I2CD3.thread = NULL;
  I2CD3.i2c    = I2C3;
#if STM32_I2C_USE_DMA == TRUE
  I2CD3.dmarx  = STM32_DMA_STREAM(STM32_I2C_I2C3_RX_DMA_STREAM);
  I2CD3.dmatx  = STM32_DMA_STREAM(STM32_I2C_I2C3_TX_DMA_STREAM);
#endif
#endif /* STM32_I2C_USE_I2C3 */

#if STM32_I2C_USE_I2C4
  i2cObjectInit(&I2CD4);
  I2CD4.thread = NULL;
  I2CD4.i2c    = I2C4;
#if STM32_I2C_USE_DMA == TRUE
  I2CD4.dmarx  = STM32_DMA_STREAM(STM32_I2C_I2C4_RX_DMA_STREAM);
  I2CD4.dmatx  = STM32_DMA_STREAM(STM32_I2C_I2C4_TX_DMA_STREAM);
#endif
#endif /* STM32_I2C_USE_I2C4 */
}

/**
 * @brief   Configures and activates the I2C peripheral.
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 *
 * @notapi
 */
void i2c_lld_start(I2CDriver *i2cp) {
  I2C_TypeDef *dp = i2cp->i2c;

#if STM32_I2C_USE_DMA == TRUE
  /* Common DMA modes.*/
  i2cp->txdmamode = DMAMODE_COMMON | STM32_DMA_CR_DIR_M2P;
  i2cp->rxdmamode = DMAMODE_COMMON | STM32_DMA_CR_DIR_P2M;
#endif

  /* Make sure I2C peripheral is disabled */
  dp->CR1 &= ~I2C_CR1_PE;
  i2cp->mode = i2cStopped;

  /* If in stopped state then enables the I2C and DMA clocks.*/
  if (i2cp->state == I2C_STOP) {

#if STM32_I2C_USE_I2C1
    if (&I2CD1 == i2cp) {

      rccResetI2C1();
      rccEnableI2C1(FALSE);
#if STM32_I2C_USE_DMA == TRUE
      {
        bool b;

        b = dmaStreamAllocate(i2cp->dmarx,
                              STM32_I2C_I2C1_IRQ_PRIORITY,
                              NULL,
                              (void *)i2cp);
        osalDbgAssert(!b, "stream already allocated");
        b = dmaStreamAllocate(i2cp->dmatx,
                              STM32_I2C_I2C1_IRQ_PRIORITY,
                              NULL,
                              (void *)i2cp);
        osalDbgAssert(!b, "stream already allocated");

        i2cp->rxdmamode |= STM32_DMA_CR_CHSEL(I2C1_RX_DMA_CHANNEL) |
                           STM32_DMA_CR_PL(STM32_I2C_I2C1_DMA_PRIORITY);
        i2cp->txdmamode |= STM32_DMA_CR_CHSEL(I2C1_TX_DMA_CHANNEL) |
                           STM32_DMA_CR_PL(STM32_I2C_I2C1_DMA_PRIORITY);
      }
#endif /* STM32_I2C_USE_DMA == TRUE */

#if defined(STM32_I2C1_GLOBAL_NUMBER) || defined(__DOXYGEN__)
      nvicEnableVector(STM32_I2C1_GLOBAL_NUMBER, STM32_I2C_I2C1_IRQ_PRIORITY);
#elif defined(STM32_I2C1_EVENT_NUMBER) && defined(STM32_I2C1_ERROR_NUMBER)
      nvicEnableVector(STM32_I2C1_EVENT_NUMBER, STM32_I2C_I2C1_IRQ_PRIORITY);
      nvicEnableVector(STM32_I2C1_ERROR_NUMBER, STM32_I2C_I2C1_IRQ_PRIORITY);
#else
#error "I2C1 interrupt numbers not defined"
#endif
    }
#endif /* STM32_I2C_USE_I2C1 */

#if STM32_I2C_USE_I2C2
    if (&I2CD2 == i2cp) {

      rccResetI2C2();
      rccEnableI2C2(FALSE);
#if STM32_I2C_USE_DMA == TRUE
      {
        bool b;

        b = dmaStreamAllocate(i2cp->dmarx,
                              STM32_I2C_I2C2_IRQ_PRIORITY,
                              NULL,
                              (void *)i2cp);
        osalDbgAssert(!b, "stream already allocated");
        b = dmaStreamAllocate(i2cp->dmatx,
                              STM32_I2C_I2C2_IRQ_PRIORITY,
                              NULL,
                              (void *)i2cp);
        osalDbgAssert(!b, "stream already allocated");

        i2cp->rxdmamode |= STM32_DMA_CR_CHSEL(I2C2_RX_DMA_CHANNEL) |
                           STM32_DMA_CR_PL(STM32_I2C_I2C2_DMA_PRIORITY);
        i2cp->txdmamode |= STM32_DMA_CR_CHSEL(I2C2_TX_DMA_CHANNEL) |
                           STM32_DMA_CR_PL(STM32_I2C_I2C2_DMA_PRIORITY);
      }
#endif /*STM32_I2C_USE_DMA == TRUE */

#if defined(STM32_I2C2_GLOBAL_NUMBER) || defined(__DOXYGEN__)
      nvicEnableVector(STM32_I2C2_GLOBAL_NUMBER, STM32_I2C_I2C2_IRQ_PRIORITY);
#elif defined(STM32_I2C2_EVENT_NUMBER) && defined(STM32_I2C2_ERROR_NUMBER)
      nvicEnableVector(STM32_I2C2_EVENT_NUMBER, STM32_I2C_I2C2_IRQ_PRIORITY);
      nvicEnableVector(STM32_I2C2_ERROR_NUMBER, STM32_I2C_I2C2_IRQ_PRIORITY);
#else
#error "I2C2 interrupt numbers not defined"
#endif
    }
#endif /* STM32_I2C_USE_I2C2 */

#if STM32_I2C_USE_I2C3
    if (&I2CD3 == i2cp) {

      rccResetI2C3();
      rccEnableI2C3(FALSE);
#if STM32_I2C_USE_DMA == TRUE
      {
        bool b;

        b = dmaStreamAllocate(i2cp->dmarx,
                              STM32_I2C_I2C3_IRQ_PRIORITY,
                              NULL,
                              (void *)i2cp);
        osalDbgAssert(!b, "stream already allocated");
        b = dmaStreamAllocate(i2cp->dmatx,
                              STM32_I2C_I2C3_IRQ_PRIORITY,
                              NULL,
                              (void *)i2cp);
        osalDbgAssert(!b, "stream already allocated");

        i2cp->rxdmamode |= STM32_DMA_CR_CHSEL(I2C3_RX_DMA_CHANNEL) |
                           STM32_DMA_CR_PL(STM32_I2C_I2C3_DMA_PRIORITY);
        i2cp->txdmamode |= STM32_DMA_CR_CHSEL(I2C3_TX_DMA_CHANNEL) |
                           STM32_DMA_CR_PL(STM32_I2C_I2C3_DMA_PRIORITY);
      }
#endif /*STM32_I2C_USE_DMA == TRUE */

#if defined(STM32_I2C3_GLOBAL_NUMBER) || defined(__DOXYGEN__)
      nvicEnableVector(STM32_I2C3_GLOBAL_NUMBER, STM32_I2C_I2C3_IRQ_PRIORITY);
#elif defined(STM32_I2C3_EVENT_NUMBER) && defined(STM32_I2C3_ERROR_NUMBER)
      nvicEnableVector(STM32_I2C3_EVENT_NUMBER, STM32_I2C_I2C3_IRQ_PRIORITY);
      nvicEnableVector(STM32_I2C3_ERROR_NUMBER, STM32_I2C_I2C3_IRQ_PRIORITY);
#else
#error "I2C3 interrupt numbers not defined"
#endif
    }
#endif /* STM32_I2C_USE_I2C3 */

#if STM32_I2C_USE_I2C4
    if (&I2CD4 == i2cp) {

      rccResetI2C4();
      rccEnableI2C4(FALSE);
#if STM32_I2C_USE_DMA == TRUE
      {
        bool b;

        b = dmaStreamAllocate(i2cp->dmarx,
                              STM32_I2C_I2C4_IRQ_PRIORITY,
                              NULL,
                              (void *)i2cp);
        osalDbgAssert(!b, "stream already allocated");
        b = dmaStreamAllocate(i2cp->dmatx,
                              STM32_I2C_I2C4_IRQ_PRIORITY,
                              NULL,
                              (void *)i2cp);
        osalDbgAssert(!b, "stream already allocated");

        i2cp->rxdmamode |= STM32_DMA_CR_CHSEL(I2C4_RX_DMA_CHANNEL) |
                           STM32_DMA_CR_PL(STM32_I2C_I2C4_DMA_PRIORITY);
        i2cp->txdmamode |= STM32_DMA_CR_CHSEL(I2C4_TX_DMA_CHANNEL) |
                           STM32_DMA_CR_PL(STM32_I2C_I2C4_DMA_PRIORITY);
      }
#endif /*STM32_I2C_USE_DMA == TRUE */

#if defined(STM32_I2C4_GLOBAL_NUMBER) || defined(__DOXYGEN__)
      nvicEnableVector(STM32_I2C4_GLOBAL_NUMBER, STM32_I2C_I2C4_IRQ_PRIORITY);
#elif defined(STM32_I2C4_EVENT_NUMBER) && defined(STM32_I2C4_ERROR_NUMBER)
      nvicEnableVector(STM32_I2C4_EVENT_NUMBER, STM32_I2C_I2C4_IRQ_PRIORITY);
      nvicEnableVector(STM32_I2C4_ERROR_NUMBER, STM32_I2C_I2C4_IRQ_PRIORITY);
#else
#error "I2C4 interrupt numbers not defined"
#endif
    }
#endif /* STM32_I2C_USE_I2C4 */
  }

#if STM32_I2C_USE_DMA == TRUE
  /* I2C registers pointed by the DMA.*/
  dmaStreamSetPeripheral(i2cp->dmarx, &dp->RXDR);
  dmaStreamSetPeripheral(i2cp->dmatx, &dp->TXDR);
  /* Reset i2c peripheral, the TCIE bit will be handled separately. */
  // TODO: Mask out config bits which user mustn't fiddle with
  dp->CR1 = (i2cp->config->cr1 | I2C_CR1_ERRIE | I2C_CR1_NACKIE |
      I2C_CR1_TXDMAEN | I2C_CR1_RXDMAEN);
#else
  /* Reset i2c peripheral, the TCIE bit will be handled separately. No DMA interrupts */
  dp->CR1 = (i2cp->config->cr1 | I2C_CR1_ERRIE | I2C_CR1_NACKIE);
#endif

  /* Setup I2C parameters.*/
  dp->TIMINGR = i2cp->config->timingr;

  /* Ready to go.*/
  i2cp->mode = i2cIdle;
#if HAL_USE_I2C_LOCK
    i2cp->lockDuration = TIME_IMMEDIATE;
#endif
#if HAL_USE_I2C_SLAVE   /* I2C slave mode support */
    i2cp->slaveNextReply = i2cp->slaveNextRx = &I2CSlaveLockOnMsg;
    i2cp->targetAdr = i2cInvalidAdr;
    i2cp->slaveTimeout = TIME_INFINITE;
#endif

    dp->CR1 |= I2C_CR1_PE;          // Enable peripheral
}


/**
 * @brief   Deactivates the I2C peripheral.
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 *
 * @notapi
 */
void i2c_lld_stop(I2CDriver *i2cp) {

  /* If not in stopped state then disables the I2C clock.*/
  if (i2cp->state != I2C_STOP) {
	i2cp->mode = i2cStopped;
	
    /* I2C disable.*/
	stopTimer(i2cp);
    i2c_lld_abort_operation(i2cp);
#if STM32_I2C_USE_DMA == TRUE
    dmaStreamRelease(i2cp->dmatx);
    dmaStreamRelease(i2cp->dmarx);
#endif

#if STM32_I2C_USE_I2C1
    if (&I2CD1 == i2cp) {
#if defined(STM32_I2C1_GLOBAL_NUMBER) || defined(__DOXYGEN__)
      nvicDisableVector(STM32_I2C1_GLOBAL_NUMBER);
#elif defined(STM32_I2C1_EVENT_NUMBER) && defined(STM32_I2C1_ERROR_NUMBER)
      nvicDisableVector(STM32_I2C1_EVENT_NUMBER);
      nvicDisableVector(STM32_I2C1_ERROR_NUMBER);
#else
#error "I2C1 interrupt numbers not defined"
#endif

      rccDisableI2C1(FALSE);
    }
#endif

#if STM32_I2C_USE_I2C2
    if (&I2CD2 == i2cp) {
#if defined(STM32_I2C2_GLOBAL_NUMBER) || defined(__DOXYGEN__)
      nvicDisableVector(STM32_I2C2_GLOBAL_NUMBER);
#elif defined(STM32_I2C2_EVENT_NUMBER) && defined(STM32_I2C2_ERROR_NUMBER)
      nvicDisableVector(STM32_I2C2_EVENT_NUMBER);
      nvicDisableVector(STM32_I2C2_ERROR_NUMBER);
#else
#error "I2C2 interrupt numbers not defined"
#endif

      rccDisableI2C2(FALSE);
    }
#endif

#if STM32_I2C_USE_I2C3
    if (&I2CD3 == i2cp) {
#if defined(STM32_I2C3_GLOBAL_NUMBER) || defined(__DOXYGEN__)
      nvicDisableVector(STM32_I2C3_GLOBAL_NUMBER);
#elif defined(STM32_I2C3_EVENT_NUMBER) && defined(STM32_I2C3_ERROR_NUMBER)
      nvicDisableVector(STM32_I2C3_EVENT_NUMBER);
      nvicDisableVector(STM32_I2C3_ERROR_NUMBER);
#else
#error "I2C3 interrupt numbers not defined"
#endif

      rccDisableI2C3(FALSE);
    }
#endif

#if STM32_I2C_USE_I2C4
    if (&I2CD4 == i2cp) {
#if defined(STM32_I2C4_GLOBAL_NUMBER) || defined(__DOXYGEN__)
      nvicDisableVector(STM32_I2C4_GLOBAL_NUMBER);
#elif defined(STM32_I2C4_EVENT_NUMBER) && defined(STM32_I2C4_ERROR_NUMBER)
      nvicDisableVector(STM32_I2C4_EVENT_NUMBER);
      nvicDisableVector(STM32_I2C4_ERROR_NUMBER);
#else
#error "I2C4 interrupt numbers not defined"
#endif

      rccDisableI2C4(FALSE);
    }
#endif
  }
}



#if HAL_USE_I2C_MASTER == TRUE
/**
 *	Utility routine brings out common code for master timeout
 */
static msg_t calcMasterTimeout(I2CDriver *i2cp)
{
  systime_t start, end;

  osalDbgAssert((i2cp->mode <= i2cIsMaster), "busy");

  /* Calculating the time window for the timeout on the busy bus condition.*/
  start = osalOsGetSystemTimeX();
  end = start + OSAL_MS2ST(STM32_I2C_BUSY_TIMEOUT);

  /* Waits until BUSY flag is reset or, alternatively, for a timeout
     condition.*/
  while (true) {
    osalSysLock();

    /* If the bus is not busy then the operation can continue, note, the
       loop is exited in the locked state.*/
//    if (!(i2cp->i2c->ISR & I2C_ISR_BUSY) && !(i2cp->i2c->CR1 & I2C_CR1_STOP))
    if (!(i2cp->i2c->ISR & I2C_ISR_BUSY))
      break;

    /* If the system time went outside the allowed window then a timeout
       condition is returned.*/
    if (!osalOsIsTimeWithinX(osalOsGetSystemTimeX(), start, end))
      return MSG_TIMEOUT;

    osalSysUnlock();
    // TODO: Should we relinquish thread here for a while?
    chThdSleepMilliseconds(2);
  }
  i2cp->mode = i2cIsMaster;			// We can set master mode now
  return MSG_OK;
}


/**
 *	Start a master mode transaction
 *
 *  Note: may need adjustment to work in multi-master mode as well - see i2c_lld_safety_timeout()
 */
static msg_t startMasterAction(I2CDriver *i2cp, systime_t timeout)
{
#if STM32_I2C_USE_DMA == TRUE
#else
#endif
  msg_t msg;

  /* Starts the operation.*/
  i2cp->i2c->CR2 |= I2C_CR2_START;

  /* Waits for the operation completion or a timeout.*/
  msg = osalThreadSuspendTimeoutS(&i2cp->thread, timeout);

  /* In case of a software timeout a STOP is sent as an extreme attempt
     to release the bus.*/
  if (msg == MSG_TIMEOUT) {
    i2cp->i2c->CR2 |= I2C_CR2_STOP;
    i2cp->mode = i2cIdle;                   // TODO: Is this enough?
  }
	return msg;
}


/**
 * @brief   Receives data via the I2C bus as master.
 * @details Number of receiving bytes must be more than 1 on STM32F1x. This is
 *          hardware restriction.
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 * @param[in] addr      slave device address
 * @param[out] rxbuf    pointer to the receive buffer
 * @param[in] rxbytes   number of bytes to be received
 * @param[in] timeout   the number of ticks before the operation timeouts,
 *                      the following special values are allowed:
 *                      - @a TIME_INFINITE no timeout.
 *                      .
 * @return              The operation status.
 * @retval MSG_OK       if the function succeeded.
 * @retval MSG_RESET    if one or more I2C errors occurred, the errors can
 *                      be retrieved using @p i2cGetErrors().
 * @retval MSG_TIMEOUT  if a timeout occurred before operation end. <b>After a
 *                      timeout the driver must be stopped and restarted
 *                      because the bus is in an uncertain state</b>.
 *
 * @notapi
 */
msg_t i2c_lld_master_receive_timeout(I2CDriver *i2cp, i2caddr_t addr,
                                     uint8_t *rxbuf, size_t rxbytes,
                                     systime_t timeout) {
//  I2C_TypeDef *dp = i2cp->i2c;

  osalDbgAssert((i2cp->thread==NULL), "#3 - reentry");

  /* Resetting error flags for this transfer.*/
  i2cp->errors = I2C_NO_ERROR;

  /* Releases the lock from high level driver.*/
  osalSysUnlock();

  calcMasterTimeout(i2cp);              // This has to be done before we change the state of the connection


#if STM32_I2C_USE_DMA == TRUE
  /* RX DMA setup.*/
  dmaStreamSetMode(i2cp->dmarx, i2cp->rxdmamode);
  dmaStreamSetMemory0(i2cp->dmarx, rxbuf);
  dmaStreamSetTransactionSize(i2cp->dmarx, rxbytes);
#endif
  // Always set up the receive buffer in case callbacks enabled
  i2cp->rxptr   = rxbuf;
  i2cp->rxbytes = rxbytes;

  /* Setting up the slave address.*/
  i2c_lld_set_address(i2cp, addr);

  /* Setting up the peripheral.*/
  i2c_lld_setup_rx_transfer(i2cp);

  i2cStartReceive(i2cp);
  i2cp->mode = i2cMasterRxing;
  
  return startMasterAction(i2cp, timeout);
}



/**
 * @brief   Transmits data via the I2C bus as master.
 * @details Number of receiving bytes must be 0 or more than 1 on STM32F1x.
 *          This is hardware restriction.
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 * @param[in] addr      slave device address
 * @param[in] txbuf     pointer to the transmit buffer
 * @param[in] txbytes   number of bytes to be transmitted
 * @param[out] rxbuf    pointer to the receive buffer
 * @param[in] rxbytes   number of bytes to be received
 * @param[in] timeout   the number of ticks before the operation timeouts,
 *                      the following special values are allowed:
 *                      - @a TIME_INFINITE no timeout.
 *                      .
 * @return              The operation status.
 * @retval MSG_OK       if the function succeeded.
 * @retval MSG_RESET    if one or more I2C errors occurred, the errors can
 *                      be retrieved using @p i2cGetErrors().
 * @retval MSG_TIMEOUT  if a timeout occurred before operation end. <b>After a
 *                      timeout the driver must be stopped and restarted
 *                      because the bus is in an uncertain state</b>.
 *
 * @notapi
 */
msg_t i2c_lld_master_transmit_timeout(I2CDriver *i2cp, i2caddr_t addr,
                                      const uint8_t *txbuf, size_t txbytes,
                                      uint8_t *rxbuf, size_t rxbytes,
                                      systime_t timeout) {
  I2C_TypeDef *dp = i2cp->i2c;

  osalDbgAssert((i2cp->thread==NULL), "#3 - reentry");

  /* Resetting error flags for this transfer.*/
  i2cp->errors = I2C_NO_ERROR;

  /* Releases the lock from high level driver.*/
  osalSysUnlock();

  calcMasterTimeout(i2cp);              // This has to be done before we change the state of the connection


#if STM32_I2C_USE_DMA == TRUE
  /* TX DMA setup.*/
  dmaStreamSetMode(i2cp->dmatx, i2cp->txdmamode);
  dmaStreamSetMemory0(i2cp->dmatx, txbuf);
  dmaStreamSetTransactionSize(i2cp->dmatx, txbytes);

  /* RX DMA setup, note, rxbytes can be zero but we write the value anyway.*/
  dmaStreamSetMode(i2cp->dmarx, i2cp->rxdmamode);
  dmaStreamSetMemory0(i2cp->dmarx, rxbuf);
  dmaStreamSetTransactionSize(i2cp->dmarx, rxbytes);
#else
  i2cp->txptr   = txbuf;
  i2cp->txbytes = txbytes;
#endif
  // Always set up the receive buffer in case callbacks enabled
  i2cp->rxptr   = rxbuf;
  i2cp->rxbytes = rxbytes;

  /* Setting up the slave address.*/
  i2c_lld_set_address(i2cp, addr);

  /* Preparing the transfer.*/
  i2c_lld_setup_tx_transfer(i2cp);

#if STM32_I2C_USE_DMA == TRUE
  /* Enabling TX DMA.*/
  dmaStreamEnable(i2cp->dmatx);

  /* Transfer complete interrupt enabled.*/
  dp->CR1 |= I2C_CR1_TCIE;
#else
  /* Transfer complete and TX interrupts enabled.*/
  dp->CR1 |= I2C_CR1_TCIE | I2C_CR1_TXIE;
#endif

  i2cp->mode = i2cMasterTxing;

  return startMasterAction(i2cp, timeout);
}
#endif      /* #if HAL_USE_I2C_MASTER == TRUE */




#if HAL_USE_I2C_SLAVE
/************************************************************************/
/*					SLAVE MODE SUPPORT									*/
/************************************************************************/

/**
 * @brief   Reconfigure I2C channel to respond to passed address
 *          in addition to those previously made active
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
 *                      Number of supported addresses is chip-dependent - 2+general call on I2CV2
 *                      Address masking capabilities of OAR2 not supported
 *
 * @notapi
 **/
msg_t i2c_lld_matchAddress(I2CDriver *i2cp, i2caddr_t i2cadr)
{
  I2C_TypeDef *dp = i2cp->i2c;
  if (i2cadr == 0) {
    dp->CR1 |= I2C_CR1_GCEN;			        // Just enable General Call
    dp->CR1 |= I2C_CR1_ADDRIE;                  // Make sure address match interrupt enabled
  }
  else 
  {
    uint32_t adr = i2cadr << 1;
    if ((dp->OAR1 & (0x7f<<1)) == adr) { return I2C_OK; };		// Already matched in OAR1
    if ((dp->OAR2 & (0x7f<<1)) == adr) { return I2C_OK; };		// Already matched in OAR2

	if (!(dp->OAR1 & I2C_OAR1_OA1EN)) {
		dp->OAR1 =  adr | I2C_OAR1_OA1EN;		// OAR1 previously unused
		dp->CR1 |= I2C_CR1_ADDRIE;              // Make sure address match interrupt enabled
	}
	else
	if (!(dp->OAR2 & I2C_OAR2_OA2EN)) {
		dp->OAR2 =  adr | I2C_OAR2_OA2EN;		// OAR2 previously unused
        dp->CR1 |= I2C_CR1_ADDRIE;              // Make sure address match interrupt enabled
	}
	else
      return I2C_ERROR;    /* cannot add this address to set of those matched */
  }
  return I2C_OK;
}


/**
 * @brief   Reconfigure I2C channel to no longer match specified address
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 * @param[in] i2cadr    I2C network address
 *
 * @details   A message being transferred that has already matched the
 *            specified address will continue being processed.
 *  Requests to unmatch an address that is not currently being matched
 *  are ignored.
 *  Does not support 10-bit addressing.
 *
 * @notapi
 **/
void i2c_lld_unmatchAddress(I2CDriver *i2cp, i2caddr_t  i2cadr)
{
  I2C_TypeDef *dp = i2cp->i2c;
  if (i2cadr == 0) {
    dp->CR1 &= (uint32_t)~I2C_CR1_GCEN;			// Disable General Call
  } 
  else {
    uint32_t adr = i2cadr << 1;
    if ((dp->OAR1 & (0x7f<<1)) == adr) {
		// Matched in OAR1
		dp->OAR1 &= ~I2C_OAR1_OA1EN;					// Just disable - OAR2 is a bit different
    } 
	else 
	if ((dp->OAR2 & I2C_OAR2_OA2EN) && (dp->OAR2 & (0x7f<<1)) == adr)
      dp->OAR2 &= ~I2C_OAR2_OA2EN;
  }
  if (!((dp->CR1 & (uint32_t)I2C_CR1_GCEN) || (dp->OAR1 & I2C_OAR1_OA1EN) || (dp->OAR2 & I2C_OAR2_OA2EN))) {
    dp->CR1 &= (uint32_t)~(I2C_CR1_ADDRIE);        // Disable Address match interrupts if nothing can generate them (strictly necessary??)
  }
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
 * @notapi
 **/
void i2c_lld_unmatchAll(I2CDriver *i2cp)
{
  I2C_TypeDef *dp = i2cp->i2c;
  dp->CR1 &= (uint32_t)~(I2C_CR1_GCEN | I2C_CR1_ADDRIE);		// Disable General Call
  dp->OAR1 = 0;
  dp->OAR2 = 0;
}


/**
 * @brief   Configure callbacks & buffers to receive messages
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 * @param[in] replyMsg  @p I2CSlaveMsg struct for processing subsequent received messages
 *
 * @details             Call i2cMatchAddress() after this to start processing
 *     Enabling match addresses before installing handler callbacks can
 *     result in locking the I2C bus when a master accesses those
 *     unconfigured slave addresses
 *
 * @notapi
 */
void i2c_lld_slaveReceive(I2CDriver *i2cp, const I2CSlaveMsg *rxMsg)
{
  osalDbgCheck((rxMsg && rxMsg->size <= 0xffff));
  qEvt(0x82, rxMsg->size);
  i2cp->slaveNextRx = rxMsg;
  if (i2cp->mode == i2cLockedRxing && rxMsg->body && rxMsg->size) {
    /* We can receive now! */
    i2cp->slaveRx = rxMsg;
    /* slave RX DMA setup */
#if STM32_I2C_USE_DMA == TRUE
  /* RX DMA setup.*/
    dmaStreamSetMode(i2cp->dmarx, i2cp->rxdmamode);
    dmaStreamSetMemory0(i2cp->dmarx, rxMsg->body);
    dmaStreamSetTransactionSize(i2cp->dmarx, rxMsg->size);
#else
  i2cp->rxptr   = rxMsg->body;
  i2cp->rxbytes = rxMsg->size;
#endif

    i2cp->mode = i2cSlaveRxing;
	i2c_lld_setup_rx_transfer(i2cp);			        // Set up the transfer
	qEvt(0x83, 0);
	i2cStartReceive(i2cp);
	i2cp->i2c->CR1 &= ~I2C_CR1_SBC;                     // Not needed with receive
    i2cp->i2c->ICR = I2C_ISR_ADDR;                      // We can release the clock stretch now
  }
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
 * @notapi
 */
void i2c_lld_slaveReply(I2CDriver *i2cp, const I2CSlaveMsg *replyMsg)
{
  osalDbgCheck((replyMsg && replyMsg->size <= 0xffff));
  qEvt(0x80, replyMsg->size);
  i2cp->slaveNextReply = replyMsg;
  if (i2cp->mode == i2cLockedReplying && replyMsg->body && replyMsg->size)
  {
    i2cp->slaveReply = replyMsg;
    /* slave TX setup -- we can reply now! */
    #if STM32_I2C_USE_DMA == TRUE
      dmaStreamSetMode(i2cp->dmatx, i2cp->txdmamode);
      dmaStreamSetMemory0(i2cp->dmatx, replyMsg->body);
      dmaStreamSetTransactionSize(i2cp->dmatx, replyMsg->size);
      i2cp->mode = i2cSlaveReplying;
      /* Start transmission */
      i2c_lld_setup_tx_transfer(i2cp);

      /* Enabling TX DMA.*/
      dmaStreamEnable(i2cp->dmatx);

      /* Transfer complete interrupt enabled.*/
      i2cp->i2c->CR1 |= I2C_CR1_TCIE;
    #else
      /* Start transmission */
      i2cp->txptr   = replyMsg->body;
      i2cp->txbytes = replyMsg->size;
      i2c_lld_setup_tx_transfer(i2cp);
      /* Transfer complete and TX character interrupts enabled.*/
      i2cp->i2c->CR1 |= I2C_CR1_TCIE | I2C_CR1_TXIE;
    #endif
      qEvt(0x81, 0);
      i2cp->i2c->CR1 |= I2C_CR1_SBC;                           // Need this to enable byte counter in transmit mode
      i2cp->i2c->ICR = I2C_ISR_ADDR;                          // We can release the clock stretch now
  }
}

#endif /* HAL_USE_I2C_SLAVE */


#endif /* HAL_USE_I2C */

/** @} */
