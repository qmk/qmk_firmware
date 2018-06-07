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
   aka barthess.  I2C Slave API contributed by Brent Roman (brent@mbari.org)
 */

/**
 * @file    STM32/I2Cv1/i2c_lld.h
 * @brief   STM32 I2C subsystem low level driver header.
 *
 * @addtogroup I2C
 * @{
 */

#ifndef _I2C_LLD_H_
#define _I2C_LLD_H_

#if HAL_USE_I2C || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @brief   Peripheral clock frequency.
 */
#define I2C_CLK_FREQ  ((STM32_PCLK1) / 1000000)

/**
 * @brief   Invalid I2C bus address
 */
#define i2cInvalidAdr  ((i2caddr_t) -1)


/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    Configuration options
 * @{
 */
/**
 * @brief   I2C1 driver enable switch.
 * @details If set to @p TRUE the support for I2C1 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(STM32_I2C_USE_I2C1) || defined(__DOXYGEN__)
#define STM32_I2C_USE_I2C1              FALSE
#endif

/**
 * @brief   I2C2 driver enable switch.
 * @details If set to @p TRUE the support for I2C2 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(STM32_I2C_USE_I2C2) || defined(__DOXYGEN__)
#define STM32_I2C_USE_I2C2              FALSE
#endif

/**
 * @brief   I2C3 driver enable switch.
 * @details If set to @p TRUE the support for I2C3 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(STM32_I2C_USE_I2C3) || defined(__DOXYGEN__)
#define STM32_I2C_USE_I2C3              FALSE
#endif

/**
 *	@brief	Enables support for I2C slave mode operation
 */
#if !defined(HAL_USE_I2C_SLAVE) || defined(__DOXYGEN__)
#define HAL_USE_I2C_SLAVE					FALSE
#define HAL_USE_I2C_STARTFIX				FALSE
#endif

/**
 *	@brief  Enables additional code needed with V1 I2C
 */
#if !defined(HAL_USE_I2C_STARTFIX) || defined(__DOXYGEN__)
#define HAL_USE_I2C_STARTFIX				FALSE
#endif


/**
 * @brief   I2C timeout on busy condition in milliseconds.
 */
#if !defined(STM32_I2C_BUSY_TIMEOUT) || defined(__DOXYGEN__)
#define STM32_I2C_BUSY_TIMEOUT              50
#endif

/**
 * @brief   I2C1 interrupt priority level setting.
 */
#if !defined(STM32_I2C_I2C1_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define STM32_I2C_I2C1_IRQ_PRIORITY     10
#endif

/**
 * @brief   I2C2 interrupt priority level setting.
 */
#if !defined(STM32_I2C_I2C2_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define STM32_I2C_I2C2_IRQ_PRIORITY     10
#endif

/**
 * @brief   I2C3 interrupt priority level setting.
 */
#if !defined(STM32_I2C_I2C3_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define STM32_I2C_I2C3_IRQ_PRIORITY     10
#endif

/**
* @brief   I2C1 DMA priority (0..3|lowest..highest).
* @note    The priority level is used for both the TX and RX DMA streams but
*          because of the streams ordering the RX stream has always priority
*          over the TX stream.
*/
#if !defined(STM32_I2C_I2C1_DMA_PRIORITY) || defined(__DOXYGEN__)
#define STM32_I2C_I2C1_DMA_PRIORITY         1
#endif

/**
* @brief   I2C2 DMA priority (0..3|lowest..highest).
* @note    The priority level is used for both the TX and RX DMA streams but
*          because of the streams ordering the RX stream has always priority
*          over the TX stream.
*/
#if !defined(STM32_I2C_I2C2_DMA_PRIORITY) || defined(__DOXYGEN__)
#define STM32_I2C_I2C2_DMA_PRIORITY         1
#endif

/**
* @brief   I2C3 DMA priority (0..3|lowest..highest).
* @note    The priority level is used for both the TX and RX DMA streams but
*          because of the streams ordering the RX stream has always priority
*          over the TX stream.
*/
#if !defined(STM32_I2C_I2C3_DMA_PRIORITY) || defined(__DOXYGEN__)
#define STM32_I2C_I2C3_DMA_PRIORITY         1
#endif

/**
 * @brief   I2C DMA error hook.
 * @note    The default action for DMA errors is a system halt because DMA
 *          error can only happen because programming errors.
 */
#if !defined(STM32_I2C_DMA_ERROR_HOOK) || defined(__DOXYGEN__)
#define STM32_I2C_DMA_ERROR_HOOK(i2cp)      osalSysHalt("DMA failure")
#endif

#if STM32_ADVANCED_DMA || defined(__DOXYGEN__)

/**
 * @brief   DMA stream used for I2C1 RX operations.
 * @note    This option is only available on platforms with enhanced DMA.
 */
#if !defined(STM32_I2C_I2C1_RX_DMA_STREAM) || defined(__DOXYGEN__)
#define STM32_I2C_I2C1_RX_DMA_STREAM     STM32_DMA_STREAM_ID(1, 0)
#endif

/**
 * @brief   DMA stream used for I2C1 TX operations.
 * @note    This option is only available on platforms with enhanced DMA.
 */
#if !defined(STM32_I2C_I2C1_TX_DMA_STREAM) || defined(__DOXYGEN__)
#define STM32_I2C_I2C1_TX_DMA_STREAM     STM32_DMA_STREAM_ID(1, 6)
#endif

/**
 * @brief   DMA stream used for I2C2 RX operations.
 * @note    This option is only available on platforms with enhanced DMA.
 */
#if !defined(STM32_I2C_I2C2_RX_DMA_STREAM) || defined(__DOXYGEN__)
#define STM32_I2C_I2C2_RX_DMA_STREAM     STM32_DMA_STREAM_ID(1, 2)
#endif

/**
 * @brief   DMA stream used for I2C2 TX operations.
 * @note    This option is only available on platforms with enhanced DMA.
 */
#if !defined(STM32_I2C_I2C2_TX_DMA_STREAM) || defined(__DOXYGEN__)
#define STM32_I2C_I2C2_TX_DMA_STREAM     STM32_DMA_STREAM_ID(1, 7)
#endif

/**
 * @brief   DMA stream used for I2C3 RX operations.
 * @note    This option is only available on platforms with enhanced DMA.
 */
#if !defined(STM32_I2C_I2C3_RX_DMA_STREAM) || defined(__DOXYGEN__)
#define STM32_I2C_I2C3_RX_DMA_STREAM     STM32_DMA_STREAM_ID(1, 2)
#endif

/**
 * @brief   DMA stream used for I2C3 TX operations.
 * @note    This option is only available on platforms with enhanced DMA.
 */
#if !defined(STM32_I2C_I2C3_TX_DMA_STREAM) || defined(__DOXYGEN__)
#define STM32_I2C_I2C3_TX_DMA_STREAM     STM32_DMA_STREAM_ID(1, 4)
#endif

#else /* !STM32_ADVANCED_DMA */

/* Fixed streams for platforms using the old DMA peripheral, the values are
   valid for both STM32F1xx and STM32L1xx.*/
#define STM32_I2C_I2C1_RX_DMA_STREAM     STM32_DMA_STREAM_ID(1, 7)
#define STM32_I2C_I2C1_TX_DMA_STREAM     STM32_DMA_STREAM_ID(1, 6)
#define STM32_I2C_I2C2_RX_DMA_STREAM     STM32_DMA_STREAM_ID(1, 5)
#define STM32_I2C_I2C2_TX_DMA_STREAM     STM32_DMA_STREAM_ID(1, 4)

#endif /* !STM32_ADVANCED_DMA*/

/* Flag for the whole STM32F1XX family. */
#if defined(STM32F10X_LD_VL) || defined(STM32F10X_MD_VL) || \
    defined(STM32F10X_HD_VL) || defined(STM32F10X_LD)    || \
    defined(STM32F10X_MD)    || defined(STM32F10X_HD)    || \
    defined(STM32F10X_XL)    || defined(STM32F10X_CL)
#define STM32F1XX_I2C
#endif
/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/** @brief  error checks */
#if STM32_I2C_USE_I2C1 && !STM32_HAS_I2C1
#error "I2C1 not present in the selected device"
#endif

#if STM32_I2C_USE_I2C2 && !STM32_HAS_I2C2
#error "I2C2 not present in the selected device"
#endif

#if STM32_I2C_USE_I2C3 && !STM32_HAS_I2C3
#error "I2C3 not present in the selected device"
#endif

#if !STM32_I2C_USE_I2C1 && !STM32_I2C_USE_I2C2 &&                           \
    !STM32_I2C_USE_I2C3
#error "I2C driver activated but no I2C peripheral assigned"
#endif

#if STM32_I2C_USE_I2C1 &&                                                   \
    !OSAL_IRQ_IS_VALID_PRIORITY(STM32_I2C_I2C1_IRQ_PRIORITY)
#error "Invalid IRQ priority assigned to I2C1"
#endif

#if STM32_I2C_USE_I2C2 &&                                                   \
    !OSAL_IRQ_IS_VALID_PRIORITY(STM32_I2C_I2C2_IRQ_PRIORITY)
#error "Invalid IRQ priority assigned to I2C2"
#endif

#if STM32_I2C_USE_I2C3 &&                                                   \
    !OSAL_IRQ_IS_VALID_PRIORITY(STM32_I2C_I2C3_IRQ_PRIORITY)
#error "Invalid IRQ priority assigned to I2C3"
#endif

#if STM32_I2C_USE_I2C1 &&                                                   \
    !STM32_DMA_IS_VALID_PRIORITY(STM32_I2C_I2C1_DMA_PRIORITY)
#error "Invalid DMA priority assigned to I2C1"
#endif

#if STM32_I2C_USE_I2C2 &&                                                   \
    !STM32_DMA_IS_VALID_PRIORITY(STM32_I2C_I2C2_DMA_PRIORITY)
#error "Invalid DMA priority assigned to I2C2"
#endif

#if STM32_I2C_USE_I2C3 &&                                                   \
    !STM32_DMA_IS_VALID_PRIORITY(STM32_I2C_I2C3_DMA_PRIORITY)
#error "Invalid DMA priority assigned to I2C3"
#endif

/* The following checks are only required when there is a DMA able to
   reassign streams to different channels.*/
#if STM32_ADVANCED_DMA
/* Check on the presence of the DMA streams settings in mcuconf.h.*/
#if STM32_I2C_USE_I2C1 && (!defined(STM32_I2C_I2C1_RX_DMA_STREAM) ||        \
                           !defined(STM32_I2C_I2C1_TX_DMA_STREAM))
#error "I2C1 DMA streams not defined"
#endif

#if STM32_I2C_USE_I2C2 && (!defined(STM32_I2C_I2C2_RX_DMA_STREAM) ||        \
                           !defined(STM32_I2C_I2C2_TX_DMA_STREAM))
#error "I2C2 DMA streams not defined"
#endif

/* Check on the validity of the assigned DMA channels.*/
#if STM32_I2C_USE_I2C1 &&                                                   \
    !STM32_DMA_IS_VALID_ID(STM32_I2C_I2C1_RX_DMA_STREAM,                    \
                           STM32_I2C1_RX_DMA_MSK)
#error "invalid DMA stream associated to I2C1 RX"
#endif

#if STM32_I2C_USE_I2C1 &&                                                   \
    !STM32_DMA_IS_VALID_ID(STM32_I2C_I2C1_TX_DMA_STREAM,                    \
                           STM32_I2C1_TX_DMA_MSK)
#error "invalid DMA stream associated to I2C1 TX"
#endif

#if STM32_I2C_USE_I2C2 &&                                                   \
    !STM32_DMA_IS_VALID_ID(STM32_I2C_I2C2_RX_DMA_STREAM,                    \
                           STM32_I2C2_RX_DMA_MSK)
#error "invalid DMA stream associated to I2C2 RX"
#endif

#if STM32_I2C_USE_I2C2 &&                                                   \
    !STM32_DMA_IS_VALID_ID(STM32_I2C_I2C2_TX_DMA_STREAM,                    \
                           STM32_I2C2_TX_DMA_MSK)
#error "invalid DMA stream associated to I2C2 TX"
#endif

#if STM32_I2C_USE_I2C3 &&                                                   \
    !STM32_DMA_IS_VALID_ID(STM32_I2C_I2C3_RX_DMA_STREAM,                    \
                           STM32_I2C3_RX_DMA_MSK)
#error "invalid DMA stream associated to I2C3 RX"
#endif

#if STM32_I2C_USE_I2C3 &&                                                   \
    !STM32_DMA_IS_VALID_ID(STM32_I2C_I2C3_TX_DMA_STREAM,                    \
                           STM32_I2C3_TX_DMA_MSK)
#error "invalid DMA stream associated to I2C3 TX"
#endif
#endif /* STM32_ADVANCED_DMA */

#if !defined(STM32_DMA_REQUIRED)
#define STM32_DMA_REQUIRED
#endif

/* Check clock range. */
#if defined(STM32F4XX)
#if !(I2C_CLK_FREQ >= 2) && (I2C_CLK_FREQ <= 42)
#error "I2C peripheral clock frequency out of range."
#endif

#elif defined(STM32L1XX)
#if !(I2C_CLK_FREQ >= 2) && (I2C_CLK_FREQ <= 32)
#error "I2C peripheral clock frequency out of range."
#endif

#elif defined(STM32F2XX)
#if !(I2C_CLK_FREQ >= 2) && (I2C_CLK_FREQ <= 30)
#error "I2C peripheral clock frequency out of range."
#endif

#elif defined(STM32F10X_LD_VL) || defined(STM32F10X_MD_VL) ||               \
      defined(STM32F10X_HD_VL)
#if !(I2C_CLK_FREQ >= 2) && (I2C_CLK_FREQ <= 24)
#error "I2C peripheral clock frequency out of range."
#endif

#elif defined(STM32F10X_LD) || defined(STM32F10X_MD) ||                     \
      defined(STM32F10X_HD) || defined(STM32F10X_XL) ||                     \
      defined(STM32F10X_CL)
#if !(I2C_CLK_FREQ >= 2) && (I2C_CLK_FREQ <= 36)
#error "I2C peripheral clock frequency out of range."
#endif
#else
#error "unspecified, unsupported or invalid STM32 platform"
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   Type representing an I2C address.
 */
typedef uint16_t i2caddr_t;

/**
 * @brief   Type of I2C driver condition flags.
 */
typedef uint32_t i2cflags_t;

/**
 * @brief   Supported modes for the I2C bus.
 */
typedef enum {
  OPMODE_I2C = 1,
  OPMODE_SMBUS_DEVICE = 2,
  OPMODE_SMBUS_HOST = 3,
} i2copmode_t;

/**
 * @brief   Supported duty cycle modes for the I2C bus.
 */
typedef enum {
  STD_DUTY_CYCLE = 1,
  FAST_DUTY_CYCLE_2 = 2,
  FAST_DUTY_CYCLE_16_9 = 3,
} i2cdutycycle_t;

/**
 * @brief   Type of a structure representing an I2C driver.
 */
typedef struct I2CDriver I2CDriver;

/**
 * @brief Driver configuration structure.
 */
typedef struct {
  i2copmode_t     op_mode;       /**< @brief Specifies the I2C mode.        */
  uint32_t        clock_speed;   /**< @brief Specifies the clock frequency.
                                      @note Must be set to a value lower
                                      than 400kHz.                          */
  i2cdutycycle_t  duty_cycle;    /**< @brief Specifies the I2C fast mode
                                      duty cycle.                           */
#if HAL_USE_I2C_STARTFIX && HAL_USE_I2C_SLAVE
  void (*armStartDetect)(void);   /**< @brief Arm Start Condition Detector    */
  void (*disarmStartDetect)(void);/**< @brief Disarm Start Condition Detector */
#endif
} I2CConfig;


#if HAL_USE_I2C_SLAVE   /* I2C slave mode support */

typedef struct I2CSlaveMsg I2CSlaveMsg;

/*
  returns the current I2C slave message receive configuration
*/
I2CSlaveMsg *i2cSlaveGetReceiveMsg(I2CDriver *i2cp);


/*
  returns the current I2C slave message reply configuration
*/
I2CSlaveMsg *i2cSlaveGetReplyMsg(I2CDriver *i2cp);


/*
  I2C Slave Message Call Back.
  Invoked from interrupt context just after
  the last byte of the message is transferred or slaveAdr is matched.

  Use i2cSlaveReceiveMsg() or i2cSlaveReplyMsg() to access
  the relevant message handling configuration
*/
typedef void I2CSlaveMsgCB(I2CDriver *i2cp);


/*
  I2CSlaveMsg message handling configurations are normally
  stored in read-only memory.
  They describe either a buffer to contain incoming messages from
  a bus master and associated callback functions, or one
  preloaded with an outgoing reply to a read request and its callbacks.
*/

struct I2CSlaveMsg {
  size_t     size;     /* sizeof(body) -- zero if master must wait */
  uint8_t   *body;     /* message contents -- or NULL if master must wait */
  I2CSlaveMsgCB *adrMatched;  /* invoked when slave address matches */
  I2CSlaveMsgCB *processMsg;  /* invoked after message is transferred */
  I2CSlaveMsgCB *exception;   /* invoked if error or timeout during transfer */
};


I2CSlaveMsgCB I2CSlaveDummyCB;
/*
  dummy callback -- placeholder to ignore event
*/

  /* lock bus on receive or reply -- force master to wait */
extern const I2CSlaveMsg I2CSlaveLockOnMsg;

#endif  /* HAL_USE_I2C_SLAVE */


/**
 * @brief Structure representing an I2C driver.
 */
struct I2CDriver {
  /**
   * @brief   Driver state.
   */
  i2cstate_t                state;
  /**
   * @brief   Current configuration data.
   */
  const I2CConfig           *config;
  /**
   * @brief   Error flags.
   */
  i2cflags_t                errors;
#if I2C_USE_MUTUAL_EXCLUSION || defined(__DOXYGEN__)
#if CH_CFG_USE_MUTEXES || defined(__DOXYGEN__)
  /**
   * @brief   Mutex protecting the bus.
   */
  mutex_t                     mutex;
#elif CH_CFG_USE_SEMAPHORES
  semaphore_t                 semaphore;
#endif
#endif /* I2C_USE_MUTUAL_EXCLUSION */
#if defined(I2C_DRIVER_EXT_FIELDS)
  I2C_DRIVER_EXT_FIELDS
#endif
  /* End of the mandatory fields.*/
  /**
   * @brief   Thread waiting for I/O completion.
   */
  thread_reference_t        thread;
  /**
   * @brief     Current slave address without R/W bit.
   */
  i2caddr_t                 addr;
  /**
   * @brief Master RX DMA buffer size.
   */
  uint16_t                  masterRxbytes;
  /**
   * @brief Master TX DMA buffer size.
   */
  uint16_t                  masterTxbytes;
  /**
   * @brief Master RX DMA buffer base.
   */
  uint8_t                   *masterRxbuf;
  /**
   * @brief Master TX DMA buffer base.
   */
  const uint8_t             *masterTxbuf;
  /**
   * @brief RX DMA mode bit mask.
   */
  uint32_t                  rxdmamode;
  /**
   * @brief TX DMA mode bit mask.
   */
  uint32_t                  txdmamode;
  /**
   * @brief     Receive DMA channel.
   */
  const stm32_dma_stream_t  *dmarx;
  /**
   * @brief     Transmit DMA channel.
   */
  const stm32_dma_stream_t  *dmatx;
  /**
   * @brief     Pointer to the I2Cx registers block.
   */
  I2C_TypeDef               *i2c;

  /**
   * @brief     low level I2C interface / protocol state
   */
  enum i2cMode {
    i2cIdle=1,          /* awaiting address or inactive */
    i2cSlaveRxing,      /* receiving message */
    i2cLockedRxing,     /* stretching clock before receiving message */
    i2cSlaveReplying,   /* replying to query */
    i2cLockedReplying,  /* stretching clock before replying to query */

    i2cIsMaster=0x11,   /* sent start bit (mastering bus) */
    i2cMasterStarted,   /* repeated start after write */
    i2cMasterSelecting, /* sending slave address */
    i2cMasterRxing,     /* receiving reply from slave */
    i2cMasterTxing      /* sending message to slave */
    }  mode;

#if HAL_USE_I2C_LOCK || HAL_USE_I2C_SLAVE
  /**
   * @brief     I2C transaction timer
   */
  virtual_timer_t           timer;
#endif
#if HAL_USE_I2C_LOCK
  /**
   * @brief     I2C bus lock duration
   */
  systime_t                 lockDuration;
#endif
#if HAL_USE_I2C_SLAVE
  /* additional fields to support I2C slave transactions */

  /**
   * @brief     slave address of message being processed
   */
  i2caddr_t                 targetAdr;
  /**
   * @brief     Error Mask for last slave message
   */
  i2cflags_t                slaveErrors;
  /**
   * @brief     Length of most recently transferred slave message
   */
  uint32_t                  slaveBytes;
  /**
   * @brief     Maximum # of ticks slave may stretch the I2C clock
   */
  systime_t                 slaveTimeout;
  /**
   * @brief     Pointer to slave message reception handler
   */
  const I2CSlaveMsg         *slaveRx;
  /**
   * @brief     Pointer to slave message Reply handler
   */
  const I2CSlaveMsg         *slaveReply;
  /**
   * @brief     Pointer to handler for next slave received message
   */
  const I2CSlaveMsg         *slaveNextRx;
  /**
   * @brief     Pointer to handler for next slave reply message
   */
  const I2CSlaveMsg         *slaveNextReply;
#endif
};

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/**
 * @brief   Get errors from I2C driver.
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 *
 * @notapi
 */
#define i2c_lld_get_errors(i2cp) ((i2cp)->errors)


#if HAL_USE_I2C_LOCK
/**
 * @brief   Unlock I2C bus after the end of the next transaction
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 *
 * @notapi
 **/
#define i2c_lld_unlock(i2cp) (i2cp->lockDuration = TIME_IMMEDIATE)
#endif


#if HAL_USE_I2C_SLAVE   /* I2C slave mode support */
/**
 * @brief   Get slave errors from I2C driver.
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 *
 * @notapi
 */
#define i2c_lld_get_slaveErrors(i2cp) ((i2cp)->slaveErrors)

/**
 * @brief   Get slave message bytes transferred from I2C driver.
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 *
 * @notapi
 */
#define i2c_lld_get_slaveBytes(i2cp) ((i2cp)->slaveBytes)


/**
 * @brief   Get slave timeout in ticks from I2C driver.
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 *
 * @notapi
 */
#define i2c_lld_get_slaveTimeout(i2cp) ((i2cp)->slaveTimeout)

/**
 * @brief   Set slave timeout in ticks for I2C driver.
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 *
 * @notapi
 */
#define i2c_lld_set_slaveTimeout(i2cp,ticks) ((i2cp)->slaveTimeout=(ticks))

/**
 * @brief   Get slave target address from I2C driver.
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 *
 * @notapi
 */
#define i2c_lld_get_slaveTargetAdr(i2cp) ((i2cp)->targetAdr)

/**
 * @brief   Get slave receive message descriptor from I2C driver.
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 *
 * @notapi
 */
#define i2c_lld_get_slaveReceive(i2cp) ((i2cp)->slaveNextRx)

/**
 * @brief   Get slave reply message descriptor from I2C driver.
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 *
 * @notapi
 */
#define i2c_lld_get_slaveReply(i2cp) ((i2cp)->slaveNextReply)

#endif

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if !defined(__DOXYGEN__)
#if STM32_I2C_USE_I2C1
extern I2CDriver I2CD1;
#endif

#if STM32_I2C_USE_I2C2
extern I2CDriver I2CD2;
#endif

#if STM32_I2C_USE_I2C3
extern I2CDriver I2CD3;
#endif
#endif /* !defined(__DOXYGEN__) */

#ifdef __cplusplus
extern "C" {
#endif
  void i2c_lld_init(void);
  void i2c_lld_start(I2CDriver *i2cp);
  void i2c_lld_stop(I2CDriver *i2cp);
  msg_t i2c_lld_master_transmit_timeout(I2CDriver *i2cp, i2caddr_t addr,
                                        const uint8_t *txbuf, size_t txbytes,
                                        uint8_t *rxbuf, size_t rxbytes,
                                        systime_t timeout);
  msg_t i2c_lld_master_receive_timeout(I2CDriver *i2cp, i2caddr_t addr,
                                       uint8_t *rxbuf, size_t rxbytes,
                                       systime_t timeout);

#if HAL_USE_I2C_LOCK    /* I2C slave mode support */
  void i2c_lld_lock(I2CDriver *i2cp, systime_t lockDuration);
#endif
#if HAL_USE_I2C_SLAVE   /* I2C slave mode support */
  msg_t i2c_lld_matchAddress(I2CDriver *i2cp, i2caddr_t  i2cadr);
  void  i2c_lld_unmatchAddress(I2CDriver *i2cp, i2caddr_t  i2cadr);
  void  i2c_lld_unmatchAll(I2CDriver *i2cp);
  void  i2c_lld_slaveReceive(I2CDriver *i2cp, const I2CSlaveMsg *rxMsg);
  void  i2c_lld_slaveReply(I2CDriver *i2cp, const I2CSlaveMsg *replyMsg);
#if HAL_USE_I2C_STARTFIX
  void  i2c_lld_startDetected(I2CDriver *i2cp);
  void  i2c_lld_noStartDetector(void);
#define i2cNoStartDetector  i2c_lld_noStartDetector
#endif
#endif /* HAL_USE_I2C_SLAVE */

#ifdef __cplusplus
}
#endif

#endif /* HAL_USE_I2C  */

#endif /* _I2C_LLD_H_ */

/** @} */
