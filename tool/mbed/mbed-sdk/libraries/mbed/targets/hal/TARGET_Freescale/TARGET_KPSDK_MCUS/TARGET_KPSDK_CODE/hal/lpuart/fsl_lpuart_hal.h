/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
#ifndef __FSL_LPUART_HAL_H__
#define __FSL_LPUART_HAL_H__

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_lpuart_features.h"
#include "fsl_device_registers.h"

#ifndef MBED_NO_LPUART

/*!
 * @addtogroup lpuart_hal
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define LPUART_SHIFT (16U)
#define LPUART_BAUD_REG_ID (0U)
#define LPUART_STAT_REG_ID (1U)
#define LPUART_CTRL_REG_ID (2U)
#define LPUART_DATA_REG_ID (3U)
#define LPUART_MATCH_REG_ID (4U)
#define LPUART_MODIR_REG_ID (5U)

/*! @brief Error codes for the LPUART driver.*/
typedef enum _lpuart_status
{
    kStatus_LPUART_Success,
    kStatus_LPUART_BaudRateCalculationError ,  /*!< LPUART Baud Rate calculation error out of range. */
    kStatus_LPUART_BaudRatePercentDiffExceeded,   /*!< LPUART Baud Rate exceeds percentage difference*/
    kStatus_LPUART_BitCountNotSupported,  /*!< LPUART bit count configuration not supported.*/
    kStatus_LPUART_StopBitCountNotSupported,  /*!< LPUART stop bit count configuration not supported.*/
    kStatus_LPUART_RxStandbyModeError,  /*!< LPUART unable to place receiver in standby mode.*/
    kStatus_LPUART_ClearStatusFlagError,  /*!< LPUART clear status flag error.*/
    kStatus_LPUART_MSBFirstNotSupported,  /*!< LPUART MSB first feature not supported.*/
    kStatus_LPUART_Resync_NotSupported,  /*!< LPUART resync disable operation not supported.*/
    kStatus_LPUART_TxNotDisabled,  /*!< LPUART Transmitter not disabled before enabling feature*/
    kStatus_LPUART_RxNotDisabled,  /*!< LPUART Receiver not disabled before enabling feature*/
    kStatus_LPUART_TxOrRxNotDisabled,   /*!< LPUART Transmitter or Receiver not disabled*/
    kStatus_LPUART_TxBusy,  /*!< LPUART transmit still in progress.*/
    kStatus_LPUART_RxBusy,  /*!< LPUART receive still in progress.*/
    kStatus_LPUART_NoTransmitInProgress, /*!< LPUART no transmit in progress.*/
    kStatus_LPUART_NoReceiveInProgress, /*!< LPUART no receive in progress.*/
    kStatus_LPUART_InvalidInstanceNumber, /*!< Invalid LPUART base address */
    kStatus_LPUART_InvalidBitSetting,  /*!< Invalid setting for desired LPUART register bit field */
    kStatus_LPUART_OverSamplingNotSupported,  /*!< LPUART oversampling not supported.*/
    kStatus_LPUART_BothEdgeNotSupported,  /*!< LPUART both edge sampling not supported. */
    kStatus_LPUART_Timeout,  /*!< LPUART transfer timed out.*/
    kStatus_LPUART_Initialized,
} lpuart_status_t;

/*! @brief LPUART number of stop bits*/
typedef enum _lpuart_stop_bit_count {
    kLpuartOneStopBit = 0,  /*!< one stop bit*/
    kLpuartTwoStopBit = 1,  /*!< two stop bits*/
} lpuart_stop_bit_count_t;

/*! @brief LPUART parity mode*/
typedef enum _lpuart_parity_mode {
    kLpuartParityDisabled = 0x0,  /*!< parity disabled*/
    kLpuartParityEven     = 0x2,  /*!< parity enabled, type even, bit setting: PE|PT = 10*/
    kLpuartParityOdd      = 0x3,  /*!< parity enabled, type odd,  bit setting: PE|PT = 11*/
} lpuart_parity_mode_t;

/*! @brief LPUART number of bits in a character*/
typedef enum  _lpuart_bit_count_per_char {
    kLpuart8BitsPerChar = 0,   /*!< 8-bit data characters*/
    kLpuart9BitsPerChar = 1,   /*!< 9-bit data characters*/
    kLpuart10BitsPerChar = 2,  /*!< 10-bit data characters*/
} lpuart_bit_count_per_char_t;

/*! @brief LPUART operation configuration constants*/
typedef enum _lpuart_operation_config {
    kLpuartOperates = 0,/*!< LPUART continues to operate normally.*/
    kLpuartStops = 1,   /*!< LPUART stops operation. */
} lpuart_operation_config_t;

/*! @brief LPUART wakeup from standby method constants*/
typedef enum _lpuart_wakeup_method {
    kLpuartIdleLineWake = 0,  /*!< Idle-line wakes the LPUART receiver from standby. */
    kLpuartAddrMarkWake = 1,  /*!< Addr-mark wakes LPUART receiver from standby.*/
} lpuart_wakeup_method_t;

/*! @brief LPUART idle line detect selection types*/
typedef enum _lpuart_idle_line_select {
    kLpuartIdleLineAfterStartBit = 0, /*!< LPUART idle character bit count start after start bit */
    kLpuartIdleLineAfterStopBit = 1,  /*!< LPUART idle character bit count start after stop bit */
} lpuart_idle_line_select_t;

/*!
 * @brief LPUART break character length settings for transmit/detect.
 *
 * The actual maximum bit times may vary depending on the LPUART instance.
 */
typedef enum _lpuart_break_char_length {
    kLpuartBreakChar10BitMinimum = 0, /*!< LPUART break char length 10 bit times (if M = 0, SBNS = 0)
                                      or 11 (if M = 1, SBNS = 0 or M = 0, SBNS = 1) or 12 (if M = 1, 
                                      SBNS = 1 or M10 = 1, SNBS = 0) or 13 (if M10 = 1, SNBS = 1 .*/
    kLpuartBreakChar13BitMinimum = 1, /*!< LPUART break char length 13 bit times (if M = 0, SBNS = 0)
                                      or 14 (if M = 1, SBNS = 0 or M = 0, SBNS = 1) or 15 (if M = 1, 
                                      SBNS = 1 or M10 = 1, SNBS = 0) or 16 (if M10 = 1, SNBS = 1)*/
} lpuart_break_char_length_t;

/*! @brief LPUART single-wire mode TX direction*/
typedef enum _lpuart_singlewire_txdir {
    kLpuartSinglewireTxdirIn = 0,  /*!< LPUART Single Wire mode TXDIR input*/
    kLpuartSinglewireTxdirOut = 1, /*!< LPUART Single Wire mode TXDIR output*/
} lpuart_singlewire_txdir_t;

/*! @brief LPUART Configures the match addressing mode used.*/
typedef enum _lpuart_match_config {
    kLpuartAddressMatchWakeup = 0, /*!< LPUART Address Match Wakeup*/
    kLpuartIdleMatchWakeup = 1,    /*!< LPUART Idle Match Wakeup*/
    kLpuartMatchOnAndMatchOff = 2, /*!< LPUART Match On and Match Off*/
    kLpuartEnablesRwuOnDataMatch = 3, /*!< LPUART Enables RWU on Data Match and Match On/Off for transmitter CTS input*/
} lpuart_match_config_t;

/*! @brief LPUART infra-red transmitter pulse width options*/
typedef enum _lpuart_ir_tx_pulsewidth {
    kLpuartIrThreeSixteenthsWidth = 0,  /*!< 3/16 pulse*/
    kLpuartIrOneSixteenthWidth = 1,     /*!< 1/16 pulse*/
    kLpuartIrOneThirtysecondsWidth = 2, /*!< 1/32 pulse*/
    kLpuartIrOneFourthWidth = 3,        /*!< 1/4 pulse*/
} lpuart_ir_tx_pulsewidth_t;

/*! @brief LPUART Configures the number of idle characters that must be received before the IDLE flag is set. */
typedef enum _lpuart_idle_config {
    kLpuart_1_IdleChar = 0,   /*!< 1 idle character*/
    kLpuart_2_IdleChar = 1,   /*!< 2 idle character*/
    kLpuart_4_IdleChar = 2,   /*!< 4 idle character*/
    kLpuart_8_IdleChar = 3,   /*!< 8 idle character*/
    kLpuart_16_IdleChar = 4,  /*!< 16 idle character*/
    kLpuart_32_IdleChar = 5,  /*!< 32 idle character*/
    kLpuart_64_IdleChar = 6,  /*!< 64 idle character*/
    kLpuart_128_IdleChar = 7, /*!< 128 idle character*/
} lpuart_idle_config_t;

/*! @brief LPUART Transmits the CTS Configuration. Configures the source of the CTS input.*/
typedef enum _lpuart_cts_source {
    kLpuartCtsSourcePin = 0,  /*!< LPUART CTS input is the LPUART_CTS pin.*/
    kLpuartCtsSourceInvertedReceiverMatch = 1, /*!< LPUART CTS input is the inverted Receiver Match result.*/
} lpuart_cts_source_t;

/*! @brief LPUART Transmits CTS Source.Configures if the CTS state is checked at the start of each character or only when the transmitter is idle.*/
typedef enum _lpuart_cts_config {
    kLpuartCtsSampledOnEachCharacter = 0,  /*!< LPUART CTS input is sampled at the start of each character.*/
    kLpuartCtsSampledOnIdle = 1, /*!< LPUART CTS input is sampled when the transmitter is idle.*/
} lpuart_cts_config_t;

/*! @brief Structure for idle line configuration settings*/
typedef struct LpuartIdleLineConfig {
    unsigned idleLineType : 1; /*!< ILT, Idle bit count start: 0 - after start bit (default),*/
                               /*!  1 - after stop bit */
    unsigned rxWakeIdleDetect : 1; /*!< RWUID, Receiver Wake Up Idle Detect. IDLE status bit */
                                   /*!  operation during receive standbyControls whether idle */
                                   /*!  character that wakes up receiver will also set */
                                   /*!  IDLE status bit 0 - IDLE status bit doesn't */
                                   /*!  get set (default), 1 - IDLE status bit gets set*/
} lpuart_idle_line_config_t;

/*!
 * @brief LPUART status flags.
 *
 * This provides constants for the LPUART status flags for use in the UART functions.
 */
typedef enum _lpuart_status_flag {
    kLpuartTxDataRegEmpty            = LPUART_STAT_REG_ID << LPUART_SHIFT | BP_LPUART_STAT_TDRE,    /*!< Tx data register empty flag, sets when Tx buffer is empty */
    kLpuartTxComplete                = LPUART_STAT_REG_ID << LPUART_SHIFT | BP_LPUART_STAT_TC,      /*!< Transmission complete flag, sets when transmission activity complete */
    kLpuartRxDataRegFull             = LPUART_STAT_REG_ID << LPUART_SHIFT | BP_LPUART_STAT_RDRF,    /*!< Rx data register full flag, sets when the receive data buffer is full */
    kLpuartIdleLineDetect            = LPUART_STAT_REG_ID << LPUART_SHIFT | BP_LPUART_STAT_IDLE,    /*!< Idle line detect flag, sets when idle line detected */
    kLpuartRxOverrun                 = LPUART_STAT_REG_ID << LPUART_SHIFT | BP_LPUART_STAT_OR,      /*!< Rxr Overrun, sets when new data is received before data is read from receive register */
    kLpuartNoiseDetect               = LPUART_STAT_REG_ID << LPUART_SHIFT | BP_LPUART_STAT_NF,      /*!< Rxr takes 3 samples of each received bit.  If any of these samples differ, noise flag sets */
    kLpuartFrameErr                  = LPUART_STAT_REG_ID << LPUART_SHIFT | BP_LPUART_STAT_FE,      /*!< Frame error flag, sets if logic 0 was detected where stop bit expected */
    kLpuartParityErr                 = LPUART_STAT_REG_ID << LPUART_SHIFT | BP_LPUART_STAT_PF,      /*!< If parity enabled, sets upon parity error detection */
    kLpuartLineBreakDetect           = LPUART_STAT_REG_ID << LPUART_SHIFT | BP_LPUART_STAT_LBKDE,   /*!< LIN break detect interrupt flag, sets when LIN break char detected and LIN circuit enabled */
    kLpuartRxActiveEdgeDetect        = LPUART_STAT_REG_ID << LPUART_SHIFT | BP_LPUART_STAT_RXEDGIF, /*!< Rx pin active edge interrupt flag, sets when active edge detected */
    kLpuartRxActive                  = LPUART_STAT_REG_ID << LPUART_SHIFT | BP_LPUART_STAT_RAF,     /*!< Receiver Active Flag (RAF), sets at beginning of valid start bit */
#if FSL_FEATURE_LPUART_HAS_EXTENDED_DATA_REGISTER_FLAGS
    kLpuartNoiseInCurrentWord        = LPUART_DATA_REG_ID << LPUART_SHIFT | BP_LPUART_DATA_NOISY,     /*!< NOISY bit, sets if noise detected in current data word */
    kLpuartParityErrInCurrentWord    = LPUART_DATA_REG_ID << LPUART_SHIFT | BP_LPUART_DATA_PARITYE,   /*!< PARITYE bit, sets if noise detected in current data word */
#endif
#if FSL_FEATURE_LPUART_HAS_ADDRESS_MATCHING
    kLpuartMatchAddrOne              = LPUART_STAT_REG_ID << LPUART_SHIFT | BP_LPUART_STAT_MA1F,    /*!< Address one match flag */
    kLpuartMatchAddrTwo              = LPUART_STAT_REG_ID << LPUART_SHIFT | BP_LPUART_STAT_MA2F,    /*!< Address two match flag */
#endif
} lpuart_status_flag_t;

/*! @brief LPUART interrupt configuration structure, default settings are 0 (disabled)*/
typedef enum _lpuart_interrupt {
    kLpuartIntLinBreakDetect     = LPUART_BAUD_REG_ID << LPUART_SHIFT | BP_LPUART_BAUD_LBKDIE,  /*!< LIN break detect. */
    kLpuartIntRxActiveEdge       = LPUART_BAUD_REG_ID << LPUART_SHIFT | BP_LPUART_BAUD_RXEDGIE, /*!< RX Active Edge. */
    kLpuartIntTxDataRegEmpty     = LPUART_CTRL_REG_ID << LPUART_SHIFT | BP_LPUART_CTRL_TIE,     /*!< Transmit data register empty. */
    kLpuartIntTxComplete         = LPUART_CTRL_REG_ID << LPUART_SHIFT | BP_LPUART_CTRL_TCIE,    /*!< Transmission complete. */
    kLpuartIntRxDataRegFull      = LPUART_CTRL_REG_ID << LPUART_SHIFT | BP_LPUART_CTRL_RIE,     /*!< Receiver data register full. */
    kLpuartIntIdleLine           = LPUART_CTRL_REG_ID << LPUART_SHIFT | BP_LPUART_CTRL_ILIE,    /*!< Idle line. */
    kLpuartIntRxOverrun          = LPUART_CTRL_REG_ID << LPUART_SHIFT | BP_LPUART_CTRL_ORIE,    /*!< Receiver Overrun. */
    kLpuartIntNoiseErrFlag       = LPUART_CTRL_REG_ID << LPUART_SHIFT | BP_LPUART_CTRL_NEIE,    /*!< Noise error flag. */
    kLpuartIntFrameErrFlag       = LPUART_CTRL_REG_ID << LPUART_SHIFT | BP_LPUART_CTRL_FEIE,    /*!< Framing error flag. */
    kLpuartIntParityErrFlag      = LPUART_CTRL_REG_ID << LPUART_SHIFT | BP_LPUART_CTRL_PEIE,    /*!< Parity error flag. */
#if FSL_FEATURE_LPUART_HAS_ADDRESS_MATCHING
    kLpuartIntMatchAddrOne       = LPUART_CTRL_REG_ID << LPUART_SHIFT | BP_LPUART_CTRL_MA1IE,   /*!< Match address one flag. */
    kLpuartIntMatchAddrTwo       = LPUART_CTRL_REG_ID << LPUART_SHIFT | BP_LPUART_CTRL_MA2IE,   /*!< Match address two flag. */
#endif
} lpuart_interrupt_t;


/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name LPUART Common Configurations
 * @{
 */

/*!
 * @brief Initializes the LPUART controller to known state.
 *
 * @param baseAddr LPUART base address.
 */
void LPUART_HAL_Init(uint32_t baseAddr);

/*!
 * @brief Enables the LPUART transmitter.
 *
 * @param baseAddr LPUART base address.
 */
void LPUART_HAL_EnableTransmitter(uint32_t baseAddr);

/*!
 * @brief Disables the LPUART transmitter.
 *
 * @param baseAddr LPUART base address
 */
static inline void LPUART_HAL_DisableTransmitter(uint32_t baseAddr)
{
    BW_LPUART_CTRL_TE(baseAddr, 0);
}

/*!
 * @brief Gets the LPUART transmitter enabled/disabled configuration.
 *
 * @param baseAddr LPUART base address
 * @return State of LPUART transmitter enable(1)/disable(0)
 */
static inline bool LPUART_HAL_IsTransmitterEnabled(uint32_t baseAddr)
{
    return BR_LPUART_CTRL_TE(baseAddr);
}

/*!
 * @brief Enables the LPUART receiver.
 *
 * @param baseAddr LPUART base address
 */
static inline void LPUART_HAL_EnableReceiver(uint32_t baseAddr)
{
    BW_LPUART_CTRL_RE(baseAddr, 1);
}

/*!
 * @brief Disables the LPUART receiver.
 *
 * @param baseAddr LPUART base address
 */
static inline void LPUART_HAL_DisableReceiver(uint32_t baseAddr)
{
    BW_LPUART_CTRL_RE(baseAddr, 0);
}

/*!
 * @brief Gets the LPUART receiver enabled/disabled configuration.
 *
 * @param baseAddr LPUART base address
 * @return State of LPUART receiver enable(1)/disable(0)
 */
static inline bool LPUART_HAL_IsReceiverEnabled(uint32_t baseAddr)
{
    return BR_LPUART_CTRL_RE(baseAddr);
}

/*!
 * @brief Configures the LPUART baud rate.
 *
 *  In some LPUART instances the user must disable the transmitter/receiver
 *  before calling this function.
 *  Generally, this may be applied to all LPUARTs to ensure safe operation.
 *
 * @param baseAddr LPUART base address.
 * @param   sourceClockInHz      LPUART source input clock in Hz.
 * @param   desiredBaudRate      LPUART desired baud rate.
 * @return  An error code or kStatus_Success
 */
lpuart_status_t LPUART_HAL_SetBaudRate(uint32_t baseAddr, uint32_t sourceClockInHz,
                                uint32_t desiredBaudRate);

/*!
 * @brief Sets the LPUART baud rate modulo divisor.
 *
 * @param baseAddr LPUART base address.
 * @param   baudRateDivisor The baud rate modulo division "SBR"
 */
static inline void LPUART_HAL_SetBaudRateDivisor(uint32_t baseAddr, uint32_t baudRateDivisor)
{
    assert ((baudRateDivisor < 0x1FFF) && (baudRateDivisor > 1));
    BW_LPUART_BAUD_SBR(baseAddr, baudRateDivisor);
}

#if FSL_FEATURE_LPUART_HAS_BAUD_RATE_OVER_SAMPLING_SUPPORT
/*!
 * @brief Sets the LPUART baud rate oversampling ratio (Note: Feature available on select
 *        LPUART instances used together with baud rate programming)
 *        The oversampling ratio should be set between 4x (00011) and 32x (11111). Writing
 *        an invalid oversampling ratio results in an error and is set to a default
 *        16x (01111) oversampling ratio.
 *        IDisable the transmitter/receiver before calling
 *        this function.
 *
 * @param baseAddr LPUART base address.
 * @param   overSamplingRatio The oversampling ratio "OSR"
 */
static inline void LPUART_HAL_SetOversamplingRatio(uint32_t baseAddr, uint32_t overSamplingRatio)
{
    assert(overSamplingRatio < 0x1F);
    BW_LPUART_BAUD_OSR(baseAddr, overSamplingRatio);
}
#endif

#if FSL_FEATURE_LPUART_HAS_BOTH_EDGE_SAMPLING_SUPPORT
/*!
 * @brief Configures the LPUART baud rate both edge sampling (Note: Feature available on select
 *        LPUART instances used with baud rate programming)
 *        When enabled, the received data is sampled on both edges of the baud rate clock.
 *        This must be set when the oversampling ratio is between 4x and 7x.
 *        This function should only be called when the receiver is disabled.
 *
 * @param baseAddr LPUART base address.
 * @param   enableBothEdgeSampling Enable (1) or Disable (0) Both Edge Sampling
 * @return  An error code or kStatus_Success
 */
static inline void LPUART_HAL_SetBothEdgeSamplingCmd(uint32_t baseAddr, bool enableBothEdgeSampling)
{
    BW_LPUART_BAUD_BOTHEDGE(baseAddr, enableBothEdgeSampling);
}
#endif

/*!
 * @brief Configures the number of bits per character in the LPUART controller.
 *
 *  In some LPUART instances, the user should disable the transmitter/receiver
 *  before calling this function.
 *  Generally, this may be applied to all LPUARTs to ensure safe operation.
 *
 * @param baseAddr LPUART base address.
 * @param   bitCountPerChar   Number of bits per char (8, 9, or
 *                            10, depending on the LPUART instance)
 */
void LPUART_HAL_SetBitCountPerChar(uint32_t baseAddr, lpuart_bit_count_per_char_t bitCountPerChar);


/*!
 * @brief Configures parity mode in the LPUART controller.
 * 
 *  In some LPUART instances, the user should disable the transmitter/receiver
 *  before calling this function.
 *  Generally, this may be applied to all LPUARTs to ensure safe operation.
 *
 * @param baseAddr LPUART base address.
 * @param   parityModeType  Parity mode (enabled, disable, odd, even - see parity_mode_t struct)
 */
void LPUART_HAL_SetParityMode(uint32_t baseAddr, lpuart_parity_mode_t parityModeType);

/*!
 * @brief Configures the number of stop bits in the LPUART controller.
 *  In some LPUART instances, the user should disable the transmitter/receiver
 *  before calling this function.
 *  Generally, this may be applied to all LPUARTs to ensure safe operation.
 *
 * @param baseAddr LPUART base address.
 * @param   stopBitCount      Number of stop bits (1 or 2 - see lpuart_stop_bit_count_t struct)
 * @return  An error code (an unsupported setting in some LPUARTs) or kStatus_Success
 */
static inline void LPUART_HAL_SetStopBitCount(uint32_t baseAddr, lpuart_stop_bit_count_t stopBitCount)
{
    /* configure the number of stop bits */
    BW_LPUART_BAUD_SBNS(baseAddr, stopBitCount);
}

/*!
 * @brief Configures the transmit and receive inversion control in the LPUART controller.
 *
 * This function should only be called when the LPUART is between transmit and receive packets.
 *
 * @param baseAddr LPUART base address.
 * @param   rxInvert     Enable (1) or disable (0) receive inversion
 * @param   txInvert     Enable (1) or disable (0) transmit inversion
 */
void LPUART_HAL_SetTxRxInversionCmd(uint32_t baseAddr, uint32_t rxInvert, uint32_t txInvert);

/*@}*/

/*!
 * @name LPUART Interrupts and DMA
 * @{
 */

/*!
 * @brief Configures the LPUART module interrupts to enable/disable various interrupt sources.
 *
 * @param   baseAddr LPUART module base address.
 * @param   interrupt LPUART interrupt configuration data.
 * @param   enable   true: enable, false: disable.
 */
void LPUART_HAL_SetIntMode(uint32_t baseAddr, lpuart_interrupt_t interrupt, bool enable);

/*!
 * @brief Returns whether the LPUART module interrupts is enabled/disabled.
 *
 * @param   baseAddr LPUART module base address.
 * @param   interrupt LPUART interrupt configuration data.
 * @return  true: enable, false: disable.
 */
bool LPUART_HAL_GetIntMode(uint32_t baseAddr, lpuart_interrupt_t interrupt);

/*!
 * @brief Enable/Disable the transmission_complete_interrupt.
 *
 * @param baseAddr LPUART base address
 * @param   enable   true: enable, false: disable.
 */
static inline void LPUART_HAL_SetTxDataRegEmptyIntCmd(uint32_t baseAddr, bool enable)
{
    BW_LPUART_CTRL_TIE(baseAddr, enable);
}

/*!
 * @brief Gets the configuration of the transmission_data_register_empty_interrupt enable setting.
 *
 * @param baseAddr LPUART base address
 * @return  Bit setting of the interrupt enable bit
 */
static inline bool LPUART_HAL_GetTxDataRegEmptyIntCmd(uint32_t baseAddr)
{
    return BR_LPUART_CTRL_TIE(baseAddr);
}

/*!
 * @brief Enables the rx_data_register_full_interrupt.
 *
 * @param baseAddr LPUART base address
 * @param   enable   true: enable, false: disable.
 */
static inline void LPUART_HAL_SetRxDataRegFullIntCmd(uint32_t baseAddr, bool enable)
{
    BW_LPUART_CTRL_RIE(baseAddr, enable);
}

/*!
 * @brief Gets the configuration of the rx_data_register_full_interrupt enable.
 *
 * @param baseAddr LPUART base address
 * @return Bit setting of the interrupt enable bit
 */
static inline bool LPUART_HAL_GetRxDataRegFullIntCmd(uint32_t baseAddr)
{
    return BR_LPUART_CTRL_RIE(baseAddr);
}

#if FSL_FEATURE_LPUART_HAS_DMA_ENABLE 
/*!
 * @brief  LPUART configures DMA requests for Transmitter and Receiver.
 *
 * @param baseAddr LPUART base address
 * @param   txDmaConfig    Transmit DMA request configuration (enable:1 /disable: 0)
 * @param   rxDmaConfig    Receive DMA request configuration (enable: 1/disable: 0)
 */
void LPUART_HAL_ConfigureDma(uint32_t baseAddr, bool txDmaConfig, bool rxDmaConfig);

/*!
 * @brief  Gets the LPUART Transmit DMA request configuration.
 *
 * @param baseAddr LPUART base address
 * @return   Transmit DMA request configuration (enable: 1/disable: 0)
 */
static inline bool LPUART_HAL_IsTxDmaEnabled(uint32_t baseAddr)
{
    /* TDMAE configures the transmit data register empty flag, S1[TDRE], to */
    /* generate a DMA request. */
    return BR_LPUART_BAUD_TDMAE(baseAddr);
}

/*!
 * @brief  Gets the LPUART receive DMA request configuration.
 *
 * @param baseAddr LPUART base address
 * @return   Receives the DMA request configuration (enable: 1/disable: 0).
 */
static inline bool LPUART_HAL_IsRxDmaEnabled(uint32_t baseAddr)
{
    /* RDMAE configures the receive data register fell flag, S1[RDRF], to */
    /* generate a DMA request. */
    return BR_LPUART_BAUD_RDMAE(baseAddr);
}

#endif

/*@}*/

/*! 
 * @name LPUART Transfer Functions
 * @{
 */

/*!
 * @brief Sends the LPUART 8-bit character.
 *
 * @param baseAddr LPUART Instance
 * @param data     data to send (8-bit)
 */
static inline void LPUART_HAL_Putchar(uint32_t baseAddr, uint8_t data)
{
    /* put 8-bit data into the lpuart data register */
    HW_LPUART_DATA_WR(baseAddr, data);
}

/*!
 * @brief Sends the LPUART 9-bit character.
 *
 * @param baseAddr LPUART Instance
 * @param data     data to send (9-bit)
 */
void LPUART_HAL_Putchar9(uint32_t baseAddr, uint16_t data);

/*!
 * @brief Sends the LPUART 10-bit character (Note: Feature available on select LPUART instances).
 *
 * @param baseAddr LPUART Instance
 * @param   data        data to send (10-bit)
 * @return  An error code or kStatus_Success
 */
lpuart_status_t LPUART_HAL_Putchar10(uint32_t baseAddr, uint16_t data);

/*!
 * @brief Gets the LPUART 8-bit character.
 *
 * @param baseAddr LPUART base address
 * @param   readData    data read from receive (8-bit)
 */
void  LPUART_HAL_Getchar(uint32_t baseAddr, uint8_t *readData);

/*!
 * @brief Gets the LPUART 9-bit character.
 *
 * @param baseAddr LPUART base address
 * @param   readData    data read from receive (9-bit)
 */
void  LPUART_HAL_Getchar9(uint32_t baseAddr, uint16_t *readData);

/*!
 * @brief Gets the LPUART 10-bit character.
 *
 * @param baseAddr LPUART base address
 * @param   readData    data read from receive (10-bit)
 * @return  An error code or kStatus_Success
 */
lpuart_status_t LPUART_HAL_Getchar10(uint32_t baseAddr, uint16_t *readData);

/*!
 * @brief Configures the number of idle characters that must be received before the IDLE flag is set.
 *
 * @param baseAddr LPUART base address
 * @param   idle_config    idle characters configuration
 */
static inline void LPUART_HAL_IdleConfig(uint32_t baseAddr, lpuart_idle_config_t idleConfig)
{
    BW_LPUART_CTRL_IDLECFG(baseAddr, idleConfig);
}

/*!
 * @brief Gets the configuration of the number of idle characters that must be received before the IDLE flag is set.
 *
 * @param baseAddr LPUART base address
 * @return  idle characters configuration
 */
static inline lpuart_idle_config_t LPUART_HAL_GetIdleconfig(uint32_t baseAddr)
{
    /* get the receiver idle character config based on the LPUART baseAddr */
    return (lpuart_idle_config_t)BR_LPUART_CTRL_IDLECFG(baseAddr);
}

#if FSL_FEATURE_LPUART_HAS_EXTENDED_DATA_REGISTER_FLAGS
/*!
 * @brief  Configures  bit10 (if enabled) or bit9 (if disabled) as the parity bit in the serial
 *         transmission.
 * This sets LPUARTx_C4[M10] - it is also required to set LPUARTx_C1[M] and LPUARTx_C1[PE]
 *
 * @param baseAddr LPUART base address
 * @param  enable  Enable (1) to configure bit10 as the parity bit, disable (0) to
 *                 configure bit 9 as the parity bit in the serial transmission
 */
static inline void LPUART_HAL_ConfigureBit10AsParityBitOperation(uint32_t baseAddr, bool enable)
{
    /* to enable the parity bit as the tenth data bit, along with enabling LPUARTx_C4[M10] */
    /* need to also enable parity and set LPUARTx_CTRL[M] bit */
    /* assumed that the user has already set the appropriate bits */
    BW_LPUART_BAUD_M10(baseAddr, enable);
}

/*!
 * @brief  Gets the configuration of bit10 (if enabled) or bit9 (if disabled) as the
 *         parity bit in the serial transmission.
 *
 * @param baseAddr LPUART base address
 * @return  Configuration of bit10 (enabled (1)), or bit 9 (disabled (0)) as the
 *          parity bit in the serial transmission
 */
static inline bool LPUART_HAL_IsBit10SetAsParityBit(uint32_t baseAddr)
{
    /* to see if the parity bit is set as the tenth data bit, */
    /* return value of LPUARTx_BAUD[M10] */
    return BR_LPUART_BAUD_M10(baseAddr);
}

/*!
 * @brief  Checks whether the current data word was received with noise.
 *
 * @param baseAddr LPUART base address.
 * @return  The status of the NOISY bit in the LPUART extended data register
 */
static inline bool LPUART_HAL_IsCurrentDatawordReceivedWithNoise(uint32_t baseAddr)
{
    /* to see if the current dataword was received with noise, */
    /* return value of LPUARTx_DATA[NOISY] */
    return BR_LPUART_DATA_NOISY(baseAddr);
}

/*!
 * @brief  Checks whether the receive buffer is empty.
 *
 * @param baseAddr LPUART base address
 * @return   TRUE if the receive-buffer is empty.
 */
static inline bool LPUART_HAL_IsReceiveBufferEmpty(uint32_t baseAddr)
{
    /* to see if the current state of data buffer is empty, */
    /* return value of LPUARTx_DATA[RXEMPT] */
    return BR_LPUART_DATA_RXEMPT(baseAddr);
}

/*!
 * @brief  Checks whether  the previous BUS state was idle before this byte is received.
 *
 * @param baseAddr LPUART base address
 * @return   TRUE if the previous BUS state was IDLE.
 */
static inline bool LPUART_HAL_ItWasPreviousBusStateIdle(uint32_t baseAddr)
{
    /* to see if the current dataword was received with parity error, */
    /* return value of LPUARTx_DATA[PARITYE] */
    return BR_LPUART_DATA_IDLINE(baseAddr);
}

/*!
 * @brief  Checks whether  the current data word was received with parity error.
 *
 * @param baseAddr LPUART base address
 * @return  The status of the PARITYE bit in the LPUART extended data register
 */
static inline bool LPUART_HAL_IsCurrentDatawordReceivedWithParityError(uint32_t baseAddr)
{
    /* to see if the current dataword was received with parity error, */
    /* return value of LPUARTx_DATA[PARITYE] */
    return BR_LPUART_DATA_PARITYE(baseAddr);
}
#endif  /* FSL_FEATURE_LPUART_HAS_EXTENDED_DATA_REGISTER_FLAGS */

/*@}*/

/*! 
 * @name LPUART Special Feature Configurations
 * @{
 */

/*!
 * @brief Configures the LPUART operation in wait mode (operates or stops operations in wait mode).
 *  In some LPUART instances, the user should disable the transmitter/receiver
 *  before calling this function.
 *  Generally, this may be applied to all LPUARTs to ensure safe operation.
 *
 * @param baseAddr LPUART base address
 * @param   mode        LPUART wait mode operation - operates or stops to operate in wait mode.
 */
static inline void  LPUART_HAL_SetWaitModeOperation(uint32_t baseAddr, lpuart_operation_config_t mode)
{
    /* configure lpuart operation in wait mode */
    /* In CPU wait mode: 0 - lpuart clocks continue to run; 1 - lpuart clocks freeze */
    BW_LPUART_CTRL_DOZEEN(baseAddr, mode);
}

/*!
 * @brief Gets the LPUART operation in wait mode (operates or stops operations in wait mode).
 *
 * @param baseAddr LPUART base address
 * @return   LPUART wait mode operation configuration - kLpuartOperates or KLpuartStops in wait mode
 */
lpuart_operation_config_t LPUART_HAL_GetWaitModeOperationConfig(uint32_t baseAddr);

/*!
 * @brief Configures the LPUART loopback operation (enable/disable loopback operation)
 *
 *  In some LPUART instances, the user should disable the transmitter/receiver
 *  before calling this function.
 *  Generally, this may be applied to all LPUARTs to ensure safe operation.
 *
 * @param baseAddr LPUART base address
 * @param   enable        LPUART loopback mode - disabled (0) or enabled (1)
 */
void LPUART_HAL_SedLoopbackCmd(uint32_t baseAddr, bool enable);

/*!
 * @brief Configures the LPUART single-wire operation (enable/disable single-wire mode)
 *
 *  In some LPUART instances, the user should disable the transmitter/receiver
 *  before calling this function.
 *  Generally, this may be applied to all LPUARTs to ensure safe operation.
 *
 * @param baseAddr LPUART base address
 * @param   enable        LPUART loopback mode - disabled (0) or enabled (1)
 */
void LPUART_HAL_SetSingleWireCmd(uint32_t baseAddr, bool enable);

/*!
 * @brief Configures the LPUART transmit direction while in single-wire mode.
 *
 * @param baseAddr LPUART base address
 * @param   direction   LPUART single-wire transmit direction - input or output
 */
static inline void LPUART_HAL_ConfigureTxdirInSinglewireMode(uint32_t baseAddr,
                                                 lpuart_singlewire_txdir_t direction)
{
    /* configure LPUART transmit direction (input or output) when in single-wire mode */
    /* it is assumed LPUART is in single-wire mode */
    BW_LPUART_CTRL_TXDIR(baseAddr, direction);
}

/*!
 * @brief  Places the LPUART receiver in standby mode.
 *
 * In some LPUART instances,
 * before placing LPUART in standby mode, first determine whether the receiver is set to
 * wake on idle or whether it is already in idle state.
 * NOTE that the RWU should only be set with C1[WAKE] = 0 (wakeup on  idle) if the channel is currently
 * not idle.
 * This can be determined by the S2[RAF] flag. If it is set to wake up an IDLE event and the channel is
 * already idle, it is possible that the LPUART will discard data since data must be received
 * (or a LIN break detect) after an IDLE is detected and before IDLE is allowed to reasserted.
 *
 * @param baseAddr LPUART base address
 * @return Error code or kStatus_Success
 */
lpuart_status_t LPUART_HAL_PutReceiverInStandbyMode(uint32_t baseAddr);

/*!
 * @brief  Places the LPUART receiver in a normal mode (disable standby mode operation).
 *
 * @param baseAddr LPUART base address
 */
static inline void LPUART_HAL_PutReceiverInNormalMode(uint32_t baseAddr)
{
    /* clear the RWU bit to place receiver into normal mode (disable standby mode) */
    BW_LPUART_CTRL_RWU(baseAddr, 0);
}

/*!
 * @brief  Checks whether the LPUART receiver is in a standby mode.
 *
 * @param baseAddr LPUART base address
 * @return LPUART in normal more (0) or standby (1)
 */
static inline bool LPUART_HAL_IsReceiverInStandby(uint32_t baseAddr)
{
    /* return the RWU bit setting (0 - normal more, 1 - standby) */
    return BR_LPUART_CTRL_RWU(baseAddr);
}

/*!
 * @brief  LPUART receiver wakeup method (idle line or addr-mark) from standby mode
 *
 * @param baseAddr LPUART base address
 * @param   method        LPUART wakeup method: 0 - Idle-line wake (default), 1 - addr-mark wake
 */
static inline void LPUART_HAL_SelectReceiverWakeupMethod(uint32_t baseAddr, lpuart_wakeup_method_t method)
{
    /* configure the WAKE bit for idle line wake or address mark wake */
    BW_LPUART_CTRL_WAKE(baseAddr, method);
}

/*!
 * @brief  Gets the LPUART receiver wakeup method (idle line or addr-mark) from standby mode.
 *
 * @param baseAddr LPUART base address
 * @return  LPUART wakeup method: kLpuartIdleLineWake: 0 - Idle-line wake (default),
 *          kLpuartAddrMarkWake: 1 - addr-mark wake
 */
lpuart_wakeup_method_t LPUART_HAL_GetReceiverWakeupMethod(uint32_t baseAddr);

/*!
 * @brief  LPUART idle-line detect operation configuration (idle line bit-count start and wake
 *         up affect on IDLE status bit).
 *
 *  In some LPUART instances, the user should disable the transmitter/receiver
 *  before calling this function.
 *  Generally, this may be applied to all LPUARTs to ensure safe operation.
 *
 * @param baseAddr LPUART base address
 * @param   config        LPUART configuration data for idle line detect operation
 */
void LPUART_HAL_ConfigureIdleLineDetect(uint32_t baseAddr,
                                         const lpuart_idle_line_config_t *config);

/*!
 * @brief  LPUART break character transmit length configuration
 *  In some LPUART instances, the user should disable the transmitter before calling
 *  this function. Generally, this may be applied to all LPUARTs to ensure safe operation.
 *
 * @param baseAddr LPUART base address
 * @param   length   LPUART break character length setting: 0 - minimum 10-bit times (default),
 *                   1 - minimum 13-bit times
 */
static inline void LPUART_HAL_SetBreakCharTransmitLength(uint32_t baseAddr,
                                             lpuart_break_char_length_t length)
{
    /* Configure BRK13 - Break Character transmit length configuration */
    /* LPUART break character length setting: */
    /* 0 - minimum 10-bit times (default), */
    /* 1 - minimum 13-bit times */
    BW_LPUART_STAT_BRK13(baseAddr, length);
}

/*!
 * @brief  LPUART break character detect length configuration
 *
 * @param baseAddr LPUART base address
 * @param   length  LPUART break character length setting: 0 - minimum 10-bit times (default),
 *                  1 - minimum 13-bit times
 */
static inline void LPUART_HAL_SetBreakCharDetectLength(uint32_t baseAddr,
                                           lpuart_break_char_length_t length)
{
    /* Configure LBKDE - Break Character detect length configuration */
    /* LPUART break character length setting: */
    /* 0 - minimum 10-bit times (default), */
    /* 1 - minimum 13-bit times */
    BW_LPUART_STAT_LBKDE(baseAddr, length);
}

/*!
 * @brief  LPUART transmit sends break character configuration.
 *
 * @param baseAddr LPUART base address
 * @param   enable LPUART normal/queue break char - disabled (normal mode, default: 0) or
 *                 enabled (queue break char: 1)
 */
static inline void LPUART_HAL_QueueBreakCharToSend(uint32_t baseAddr, bool enable)
{
    /* Configure SBK - Send Break */
    /* LPUART send break character setting: */
    /* 0 - normal transmitter operation, */
    /* 1 - Queue break character(s) to be sent */

    BW_LPUART_CTRL_SBK(baseAddr, enable);
}

/*!
 * @brief  LPUART configures match address mode control (Note: Feature available on
 *         select LPUART instances)
 *
 * @param baseAddr LPUART base address
 * @param   matchAddrMode1   MAEN1: match address mode1 enable (1)/disable (0)
 * @param   matchAddrMode2   MAEN2: match address mode2 enable (1)/disable (0)
 * @param   matchAddrValue1   MA: match address value to program into match address register 1
 * @param   matchAddrValue2   MA: match address value to program into match address register 2
 * @param   config            MATCFG: Configures the match addressing mode used.
 * @return  An error code or kStatus_Success
 */
lpuart_status_t LPUART_HAL_SetMatchAddressOperation(uint32_t baseAddr,
                                   bool matchAddrMode1, bool matchAddrMode2,
                                   uint8_t matchAddrValue1, uint8_t matchAddrValue2,
                                   lpuart_match_config_t config);

/*!
 * @brief  LPUART sends the MSB first configuration (Note: Feature available on select LPUART instances)
 *  In some LPUART instances, the user should disable  the transmitter/receiver
 *  before calling this function.
 *  Generally, this may be applied to all LPUARTs to ensure safe operation.
 *
 * @param baseAddr LPUART base address
 * @param   enable  MSB first mode configuration, MSBF: 0 - LSB (default, feature disabled),
 *                  1 - MSB (feature enabled)
 */
static inline void LPUART_HAL_ConfigureSendMsbFirstOperation(uint32_t baseAddr, bool enable)
{
    BW_LPUART_STAT_MSBF(baseAddr, enable);
}

/*!
 * @brief  LPUART disables re-sync of received data configuration (Note: Feature available on
 *         select LPUART instances).
 *
 * @param baseAddr LPUART base address
 * @param   enable  disable re-sync of received data word configuration, RESYNCDIS:
 *                  0 - re-sync of received data word (default, feature disabled),
 *                  1 - disable the re-sync (feature enabled)
 */
static inline void LPUART_HAL_ConfigureReceiveResyncDisableOperation(uint32_t baseAddr, bool enable)
{
    /* When set, disables the resynchronization of the received data word when a data */
    /* one followed by data zero transition is detected. This bit should only be changed */
    /*  when the receiver is disabled. */
    BW_LPUART_BAUD_RESYNCDIS(baseAddr, enable);
}

#if FSL_FEATURE_LPUART_HAS_MODEM_SUPPORT
/*!
 * @brief  Transmits the CTS source configuration.
 *
 * @param baseAddr LPUART base address
 * @param   source    LPUART CTS source
 */
static inline void LPUART_HAL_SelectSourceCts(uint32_t baseAddr, lpuart_cts_source_t source)
{
    /* Set TXCTSSRC */
    BW_LPUART_MODIR_TXCTSSRC(baseAddr, source);
}

/*!
 * @brief  Transmits the CTS configuration.
 * Note: configures if the CTS state is checked at the start of each character or only when the transmitter is idle.
 *
 * @param baseAddr LPUART base address
 * @param   config    LPUART CTS configuration
 */
static inline void LPUART_HAL_ConfigureCts(uint32_t baseAddr, lpuart_cts_config_t config)
{
    /* Set TXCTSC */
    BW_LPUART_MODIR_TXCTSC(baseAddr, config);
}

/*!
 * @brief  Enables  the receiver request-to-send.
 * Note: do not enable both Receiver RTS (RXRTSE) and Transmit RTS (TXRTSE).
 *
 * @param baseAddr LPUART base address
 * @param   enable  disable(0)/enable(1) receiver RTS.
 */

static inline void LPUART_HAL_SetReceiverRts(uint32_t baseAddr, bool enable)
{
    BW_LPUART_MODIR_RXRTSE(baseAddr, enable);
}

/*!
 * @brief  Enables the transmitter request-to-send.
 * Note: do not enable both Receiver RTS (RXRTSE) and Transmit RTS (TXRTSE).
 *
 * @param baseAddr LPUART base address
 * @param   enable  disable(0)/enable(1) transmitter RTS.
 */
static inline void LPUART_HAL_SetTransmitterRtsCmd(uint32_t baseAddr, bool enable)
{
    BW_LPUART_MODIR_TXRTSE(baseAddr, enable);
}

/*!
 * @brief  Configures the transmitter RTS polarity: 0=active low, 1=active high.
 *
 * @param baseAddr LPUART base address
 * @param   polarity    Settings to choose RTS polarity.
 */
static inline void LPUART_HAL_SetTransmitterRtsPolarityMode(uint32_t baseAddr, bool polarity)
{
    /* Configure the transmitter rts polarity: 0=active low, 1=active high */
    BW_LPUART_MODIR_TXRTSPOL(baseAddr, polarity);
}

/*!
 * @brief  Enables the transmitter clear-to-send.
 *
 * @param baseAddr LPUART base address
 * @param   enable  disable(0)/enable(1) transmitter CTS.
 */
static inline void LPUART_HAL_SetTransmitterCtsCmd(uint32_t baseAddr, bool enable)
{
    BW_LPUART_MODIR_TXCTSE(baseAddr, enable);
}

#endif  /* FSL_FEATURE_LPUART_HAS_MODEM_SUPPORT */

#if FSL_FEATURE_LPUART_HAS_IR_SUPPORT
/*!
 * @brief  Configures the LPUART infrared operation.
 *
 * @param baseAddr LPUART base address
 * @param   enable    Enable (1) or disable (0) the infrared operation
 * @param   pulseWidth    The transmit narrow pulse width of type lpuart_ir_tx_pulsewidth_t
 */
void LPUART_HAL_SetInfraredOperation(uint32_t baseAddr, bool enable,
                                     lpuart_ir_tx_pulsewidth_t pulseWidth);
#endif  /* FSL_FEATURE_LPUART_HAS_IR_SUPPORT */

/*@}*/

/*!
 * @name LPUART Status Flags
 * @{
 */

/*!
 * @brief  LPUART get status flag
 *
 * @param baseAddr LPUART base address
 * @param   statusFlag  The status flag to query
 */
bool LPUART_HAL_GetStatusFlag(uint32_t baseAddr, lpuart_status_flag_t statusFlag);

/*!
 * @brief  Gets the LPUART Transmit data register empty flag.
 *
 * This function returns the state of the LPUART Transmit data register empty flag.
 *
 * @param baseAddr LPUART module base address.
 * @return The status of Transmit data register empty flag, which is set when transmit buffer
 *          is empty.
 */
static inline bool LPUART_HAL_IsTxDataRegEmpty(uint32_t baseAddr)
{
    /* return status condition of TDRE flag  */
    return BR_LPUART_STAT_TDRE(baseAddr);
}

/*!
 * @brief  Gets the LPUART receive data register full flag.
 *
 * @param baseAddr LPUART base address
 * @return  Status of the receive data register full flag, sets when the receive data buffer is full.
 */
static inline bool LPUART_HAL_IsRxDataRegFull(uint32_t baseAddr)
{
    /* return status condition of RDRF flag  */
    return BR_LPUART_STAT_RDRF(baseAddr);
}

/*!
 * @brief  Gets the LPUART transmission complete flag.
 *
 * @param   baseAddr    LPUART base address
 * @return  Status of Transmission complete flag, sets when transmitter is idle
 *          (transmission activity complete)
 */
static inline bool LPUART_HAL_IsTxComplete(uint32_t baseAddr)
{
    /* return status condition of TC flag  */
    return BR_LPUART_STAT_TC(baseAddr);
}

/*!
 * @brief  LPUART clears an individual status flag (see lpuart_status_flag_t for list of status bits).
 *
 * @param baseAddr LPUART base address
 * @param   statusFlag  Desired LPUART status flag to clear
 * @return  An error code or kStatus_Success
 */
lpuart_status_t LPUART_HAL_ClearStatusFlag(uint32_t baseAddr, lpuart_status_flag_t statusFlag);

/*!
 * @brief  LPUART clears ALL status flags.
 *
 * @param baseAddr LPUART base address
 */
void LPUART_HAL_ClearAllNonAutoclearStatusFlags(uint32_t baseAddr);

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* MBED_NO_LPUART */

#endif /* __FSL_LPUART_HAL_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/

