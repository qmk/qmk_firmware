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
#ifndef __FSL_UART_HAL_H__
#define __FSL_UART_HAL_H__

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include "fsl_uart_features.h"
#include "fsl_device_registers.h"

/*!
 * @addtogroup uart_hal
 * @{
 */

/*! @file*/

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define UART_SHIFT (8U)

/*! @brief Error codes for the UART driver. */
typedef enum _uart_status
{
    kStatus_UART_Success                  = 0x0U,
    kStatus_UART_BaudRateCalculationError = 0x1U,
    kStatus_UART_RxStandbyModeError       = 0x2U, 
    kStatus_UART_ClearStatusFlagError     = 0x3U, 
    kStatus_UART_TxNotDisabled            = 0x4U, 
    kStatus_UART_RxNotDisabled            = 0x5U, 
    kStatus_UART_TxOrRxNotDisabled        = 0x6U, 
    kStatus_UART_TxBusy                   = 0x7U, 
    kStatus_UART_RxBusy                   = 0x8U,  
    kStatus_UART_NoTransmitInProgress     = 0x9U,
    kStatus_UART_NoReceiveInProgress      = 0xAU, 
    kStatus_UART_Timeout                  = 0xBU,
    kStatus_UART_Initialized              = 0xCU,
    kStatus_UART_RxCallBackEnd            = 0xDU
} uart_status_t;

/*!
 * @brief UART number of stop bits.
 *
 * These constants define the number of allowable stop bits to configure in a UART baseAddr.
 */
typedef enum _uart_stop_bit_count {
    kUartOneStopBit = 0U,  /*!< one stop bit */
    kUartTwoStopBit = 1U,  /*!< two stop bits */
} uart_stop_bit_count_t;

/*!
 * @brief UART parity mode.
 *
 * These constants define the UART parity mode options: disabled or enabled of type even or odd.
 */
typedef enum _uart_parity_mode {
    kUartParityDisabled = 0x0U,  /*!< parity disabled */
    kUartParityEven     = 0x2U,  /*!< parity enabled, type even, bit setting: PE|PT = 10 */
    kUartParityOdd      = 0x3U,  /*!< parity enabled, type odd,  bit setting: PE|PT = 11 */
} uart_parity_mode_t;

/*!
 * @brief UART number of bits in a character.
 *
 * These constants define the number of allowable data bits per UART character. Note, check the
 * UART documentation to determine if the desired UART baseAddr supports the desired number
 * of data bits per UART character.
 */
typedef enum  _uart_bit_count_per_char {
    kUart8BitsPerChar = 0U,   /*!< 8-bit data characters */
    kUart9BitsPerChar = 1U,   /*!< 9-bit data characters */
} uart_bit_count_per_char_t;

/*!
 * @brief UART operation configuration constants.
 *
 * This provides constants for UART operational states: "operates normally"
 * or "stops/ceases operation"
 */
typedef enum _uart_operation_config {
    kUartOperates = 0U,  /*!< UART continues to operate normally */
    kUartStops = 1U,     /*!< UART ceases operation */
} uart_operation_config_t;

/*! @brief UART receiver source select mode. */
typedef enum _uart_receiver_source {
    kUartLoopBack = 0U,  /*!< Internal loop back mode. */
    kUartSingleWire = 1U,/*!< Single wire mode. */
} uart_receiver_source_t ;

/*!
 * @brief UART wakeup from standby method constants.
 *
 * This provides constants for the two UART wakeup methods: idle-line or address-mark.
 */
typedef enum _uart_wakeup_method {
    kUartIdleLineWake = 0U,  /*!< The idle-line wakes UART receiver from standby */
    kUartAddrMarkWake = 1U,  /*!< The address-mark wakes UART receiver from standby */
} uart_wakeup_method_t;

/*!
 * @brief UART idle-line detect selection types.
 *
 * This provides constants for the UART idle character bit-count start: either after start or
 * stop bit.
 */
typedef enum _uart_idle_line_select {
    kUartIdleLineAfterStartBit = 0U,  /*!< UART idle character bit count start after start bit */
    kUartIdleLineAfterStopBit = 1U,   /*!< UART idle character bit count start after stop bit */
} uart_idle_line_select_t;

/*!
 * @brief UART break character length settings for transmit/detect.
 *
 * This provides constants for the UART break character length for both transmission and detection
 * purposes. Note that the actual maximum bit times may vary depending on the UART baseAddr.
 */
typedef enum _uart_break_char_length {
    kUartBreakChar10BitMinimum = 0U, /*!< UART break char length 10 bit times (if M = 0, SBNS = 0) or
                                     11 (if M = 1, SBNS = 0 or M = 0, SBNS = 1) or 12 (if M = 1,
                                     SBNS = 1 or M10 = 1, SNBS = 0) or 13 (if M10 = 1, SNBS = 1) */
    kUartBreakChar13BitMinimum = 1U, /*!< UART break char length 13 bit times (if M = 0, SBNS = 0) or
                                     14 (if M = 1, SBNS = 0 or M = 0, SBNS = 1) or 15 (if M = 1,
                                     SBNS = 1 or M10 = 1, SNBS = 0) or 16 (if M10 = 1, SNBS = 1) */
} uart_break_char_length_t;

/*!
 * @brief UART single-wire mode transmit direction.
 *
 *  This provides constants for the UART transmit direction when configured for single-wire mode.
 *  The transmit line TXDIR is either an input or output.
 */
typedef enum _uart_singlewire_txdir {
    kUartSinglewireTxdirIn = 0U,  /*!< UART Single-Wire mode TXDIR input */
    kUartSinglewireTxdirOut = 1U, /*!< UART Single-Wire mode TXDIR output */
} uart_singlewire_txdir_t;

/*!
 * @brief UART infrared transmitter pulse width options.
 *
 * This provides constants for the UART infrared (IR) pulse widths. Options include 3/16, 1/16
 * 1/32, and 1/4 pulse widths.
 */
typedef enum _uart_ir_tx_pulsewidth {
    kUartIrThreeSixteenthsWidth = 0U,   /*!< 3/16 pulse */
    kUartIrOneSixteenthWidth = 1U,      /*!< 1/16 pulse */
    kUartIrOneThirtysecondsWidth = 2U,  /*!< 1/32 pulse */
    kUartIrOneFourthWidth = 3U,         /*!< 1/4 pulse */
} uart_ir_tx_pulsewidth_t;

/*!
 * @brief UART status flags.
 *
 * This provides constants for the UART status flags for use in the UART functions.
 */
typedef enum _uart_status_flag {
    kUartTxDataRegEmpty = 0U << UART_SHIFT | BP_UART_S1_TDRE, /*!< Tx data register empty flag, sets when Tx buffer is empty */
    kUartTxComplete     = 0U << UART_SHIFT | BP_UART_S1_TC,   /*!< Transmission complete flag, sets when transmission activity complete */
    kUartRxDataRegFull  = 0U << UART_SHIFT | BP_UART_S1_RDRF, /*!< Rx data register full flag, sets when the receive data buffer is full */
    kUartIdleLineDetect = 0U << UART_SHIFT | BP_UART_S1_IDLE, /*!< Idle line detect flag, sets when idle line detected */
    kUartRxOverrun      = 0U << UART_SHIFT | BP_UART_S1_OR,   /*!< Rxr Overrun, sets when new data is received before data is read from receive register */
    kUartNoiseDetect    = 0U << UART_SHIFT | BP_UART_S1_NF,   /*!< Rxr takes 3 samples of each received bit.  If any of these samples differ, noise flag sets */
    kUartFrameErr       = 0U << UART_SHIFT | BP_UART_S1_FE,   /*!< Frame error flag, sets if logic 0 was detected where stop bit expected */
    kUartParityErr      = 0U << UART_SHIFT | BP_UART_S1_PF,   /*!< If parity enabled, sets upon parity error detection */
    kUartLineBreakDetect    = 1U << UART_SHIFT | BP_UART_S2_LBKDIF,  /*!< LIN break detect interrupt flag, sets when LIN break char detected and LIN circuit enabled */
    kUartRxActiveEdgeDetect = 1U << UART_SHIFT | BP_UART_S2_RXEDGIF, /*!< Rx pin active edge interrupt flag, sets when active edge detected */
    kUartRxActive           = 1U << UART_SHIFT | BP_UART_S2_RAF,     /*!< Receiver Active Flag (RAF), sets at beginning of valid start bit */
#if FSL_FEATURE_UART_HAS_EXTENDED_DATA_REGISTER_FLAGS
    kUartNoiseInCurrentWord     = 2U << UART_SHIFT | BP_UART_ED_NOISY,   /*!< NOISY bit, sets if noise detected in current data word */
    kUartParityErrInCurrentWord = 2U << UART_SHIFT | BP_UART_ED_PARITYE, /*!< PARITYE bit, sets if noise detected in current data word */
#endif
#if FSL_FEATURE_UART_HAS_FIFO
    kUartTxBuffEmpty     = 3U << UART_SHIFT | BP_UART_SFIFO_TXEMPT, /*!< TXEMPT bit, sets if Tx buffer is empty */
    kUartRxBuffEmpty     = 3U << UART_SHIFT | BP_UART_SFIFO_RXEMPT, /*!< RXEMPT bit, sets if Rx buffer is empty */
    kUartTxBuffOverflow  = 3U << UART_SHIFT | BP_UART_SFIFO_TXOF,   /*!< TXOF bit, sets if Tx buffer overflow occurred */
    kUartRxBuffUnderflow = 3U << UART_SHIFT | BP_UART_SFIFO_RXUF,   /*!< RXUF bit, sets if receive buffer underflow occurred */
#endif
} uart_status_flag_t;

/*!
 * @brief UART interrupt configuration structure, default settings are 0 (disabled).
 *
 * This structure contains the settings for all of the UART interrupt configurations.
 */
typedef enum _uart_interrupt {
    kUartIntLinBreakDetect  = 0U << UART_SHIFT | BP_UART_BDH_LBKDIE,  /*!< LIN break detect. */
    kUartIntRxActiveEdge    = 0U << UART_SHIFT | BP_UART_BDH_RXEDGIE, /*!< RX Active Edge. */
    kUartIntTxDataRegEmpty  = 1U << UART_SHIFT | BP_UART_C2_TIE,      /*!< Transmit data register empty. */
    kUartIntTxComplete      = 1U << UART_SHIFT | BP_UART_C2_TCIE,     /*!< Transmission complete. */
    kUartIntRxDataRegFull   = 1U << UART_SHIFT | BP_UART_C2_RIE,     /*!< Receiver data register full. */
    kUartIntIdleLine        = 1U << UART_SHIFT | BP_UART_C2_ILIE,     /*!< Idle line. */
    kUartIntRxOverrun       = 2U << UART_SHIFT | BP_UART_C3_ORIE,     /*!< Receiver Overrun. */
    kUartIntNoiseErrFlag    = 2U << UART_SHIFT | BP_UART_C3_NEIE,     /*!< Noise error flag. */
    kUartIntFrameErrFlag    = 2U << UART_SHIFT | BP_UART_C3_FEIE,     /*!< Framing error flag. */
    kUartIntParityErrFlag   = 2U << UART_SHIFT | BP_UART_C3_PEIE,     /*!< Parity error flag. */
#if FSL_FEATURE_UART_HAS_FIFO
    kUartIntTxFifoOverflow  = 3U << UART_SHIFT | BP_UART_CFIFO_TXOFE, /*!< TX FIFO Overflow. */
    kUartIntRxFifoUnderflow = 3U << UART_SHIFT | BP_UART_CFIFO_RXUFE, /*!< RX FIFO Underflow. */
#endif
} uart_interrupt_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name UART Common Configurations
 * @{
 */

/*!
 * @brief Initializes the UART controller.
 *
 * This function initializes the module to a known state.
 *
 * @param   baseAddr UART module base address.
 */
void UART_HAL_Init(uint32_t baseAddr);

/*!
 * @brief Enables the UART transmitter.
 *
 * This function allows the user to enable the UART transmitter.
 *
 * @param   baseAddr UART module base address.
 */
static inline void UART_HAL_EnableTransmitter(uint32_t baseAddr)
{
    BW_UART_C2_TE(baseAddr, 1U);
}

/*!
 * @brief Disables the UART transmitter.
 *
 * This function allows the user to disable the UART transmitter.
 *
 * @param   baseAddr UART module base address.
 */
static inline void UART_HAL_DisableTransmitter(uint32_t baseAddr)
{
    BW_UART_C2_TE(baseAddr, 0U);
}

/*!
 * @brief Gets the UART transmitter enabled/disabled configuration setting.
 *
 * This function allows the user to get the setting of the UART transmitter.
 *
 * @param   baseAddr UART module base address.
 * @return The state of UART transmitter enable(true)/disable(false) setting.
 */
static inline bool UART_HAL_IsTransmitterEnabled(uint32_t baseAddr)
{
    return (bool)BR_UART_C2_TE(baseAddr);
}

/*!
 * @brief Enables the UART receiver.
 *
 *  This function allows the user to enable the UART receiver.
 *
 * @param   baseAddr UART module base address.
 */
static inline void UART_HAL_EnableReceiver(uint32_t baseAddr)
{
    BW_UART_C2_RE(baseAddr, 1U);
}

/*!
 * @brief Disables the UART receiver.
 *
 *  This function allows the user to disable the UART receiver.
 *
 * @param   baseAddr UART module base address.
 */
static inline void UART_HAL_DisableReceiver(uint32_t baseAddr)
{
    BW_UART_C2_RE(baseAddr, 0U);
}

/*!
 * @brief Gets the UART receiver enabled/disabled configuration setting.
 *
 *  This function allows the user to get the setting of the UART receiver.
 *
 * @param   baseAddr UART module base address.
 * @return The state of UART receiver enable(true)/disable(false) setting.
 */
static inline bool UART_HAL_IsReceiverEnabled(uint32_t baseAddr)
{
    return (bool)BR_UART_C2_RE(baseAddr);
}

/*!
 * @brief Configures the UART baud rate.
 *
 * This function programs the UART baud rate to the desired value passed in by the user. The user
 * must also pass in the module source clock so that the function can calculate the baud
 * rate divisors to their appropriate values.
 * In some UART baseAddrs it is required that the transmitter/receiver be disabled
 * before calling this function.
 * Generally this is applied to all UARTs to ensure safe operation.
 *
 * @param   baseAddr UART module base address.
 * @param   sourceClockInHz UART source input clock in Hz.
 * @param   baudRate UART desired baud rate.
 * @return  An error code or kStatus_UART_Success
 */
uart_status_t UART_HAL_SetBaudRate(uint32_t baseAddr, uint32_t sourceClockInHz, uint32_t baudRate);

/*!
 * @brief Sets the UART baud rate modulo divisor value.
 *
 * This function allows the user to program the baud rate divisor directly in situations
 * where the divisor value is known. In this case, the user may not want to call the
 * UART_HAL_SetBaudRate() function, as the divisor is already known.
 *
 * @param   baseAddr UART module base address.
 * @param   baudRateDivisor The baud rate modulo division "SBR" value.
 */
void UART_HAL_SetBaudRateDivisor(uint32_t baseAddr, uint16_t baudRateDivisor);

#if FSL_FEATURE_UART_HAS_BAUD_RATE_FINE_ADJUST_SUPPORT
/*!
 * @brief Sets the UART baud rate fine adjust. (Note: Feature available on select
 *        UART baseAddrs used in conjunction with baud rate programming)
 *
 * This function, which programs the baud rate fine adjust, is used together with
 * programming the baud rate modulo divisor in situations where these divisors value are known.
 * In this case, the user may not want to call the UART_HAL_SetBaudRate() function, as the
 * divisors are already known.
 *
 * @param   baseAddr UART module base address.
 * @param   baudFineAdjust Value of 5-bit field used to add more timing resolution to average
 *                          baud rate frequency is 1/32 increments.
 */
static inline void UART_HAL_SetBaudRateFineAdjust(uint32_t baseAddr, uint8_t baudFineAdjust)
{
    assert(baudFineAdjust < 0x1F);
    BW_UART_C4_BRFA(baseAddr, baudFineAdjust);
}
#endif

/*!
 * @brief Configures the number of bits per character in the UART controller.
 *
 * This function allows the user to configure the number of bits per character according to the
 * typedef uart_bit_count_per_char_t.
 *
 * @param   baseAddr UART module base address.
 * @param   bitCountPerChar Number of bits per char (8, 9, or 10, depending on the UART baseAddr).
 */
static inline void UART_HAL_SetBitCountPerChar(uint32_t baseAddr,
                                          uart_bit_count_per_char_t bitCountPerChar)
{
    /* config 8- (M=0) or 9-bits (M=1) */
    BW_UART_C1_M(baseAddr, bitCountPerChar);
}

/*!
 * @brief Configures the parity mode in the UART controller.
 *
 * This function allows the user to configure the parity mode of the UART controller to disable
 * it or enable it for even parity or for odd parity.
 *
 * @param   baseAddr UART module base address.
 * @param   parityMode Parity mode setting (enabled, disable, odd, even - see
 *                         parity_mode_t struct).
 */
static inline void UART_HAL_SetParityMode(uint32_t baseAddr, uart_parity_mode_t parityMode)
{
    HW_UART_C1_SET(baseAddr, parityMode);
}

#if FSL_FEATURE_UART_HAS_STOP_BIT_CONFIG_SUPPORT
/*!
 * @brief Configures the number of stop bits in the UART controller.
 *
 * This function allows the user to configure the number of stop bits in the UART controller
 * to be one or two stop bits.
 *
 * @param   baseAddr UART module base address.
 * @param   stopBitCount Number of stop bits setting (1 or 2 - see uart_stop_bit_count_t struct).
 * @return  An error code (an unsupported setting in some UARTs) or kStatus_UART_Success.
 */
static inline void UART_HAL_SetStopBitCount(uint32_t baseAddr, uart_stop_bit_count_t stopBitCount)
{
    BW_UART_BDH_SBNS(baseAddr, stopBitCount);
}
#endif

/*!
 * @brief Configures the transmit and receive inversion control in UART controller.
 *
 * This function allows the user to invert the transmit and receive signals, independently.
 * This function should only be called when the UART is between transmit and receive packets.
 *
 * @param   baseAddr UART module base address.
 * @param   rxInvert Enable (true) or disable (false) receive inversion.
 * @param   txInvert Enable (true) or disable (false) transmit inversion.
 */
void UART_HAL_SetTxRxInversionCmd(uint32_t baseAddr, bool rxInvertEnable, bool txInvertEnable);

/*@}*/

/*!
 * @name UART Interrupts and DMA
 * @{
 */

/*!
 * @brief Configures the UART module interrupts to enable/disable various interrupt sources.
 *
 * @param   baseAddr UART module base address.
 * @param   interrupt UART interrupt configuration data.
 * @param   enable   true: enable, false: disable.
 */
void UART_HAL_SetIntMode(uint32_t baseAddr, uart_interrupt_t interrupt, bool enable);

/*!
 * @brief Returns whether the UART module interrupts is enabled/disabled.
 *
 * @param   baseAddr UART module base address.
 * @param   interrupt UART interrupt configuration data.
 * @return  true: enable, false: disable.
 */
bool UART_HAL_GetIntMode(uint32_t baseAddr, uart_interrupt_t interrupt);

/*!
 * @brief Enables or disables the tx_data_register_empty_interrupt.
 *
 * @param   baseAddr UART module base address.
 * @param   enable   true: enable, false: disable.
 */
static inline void UART_HAL_SetTxDataRegEmptyIntCmd(uint32_t baseAddr, bool enable)
{
    /* transmit interrupt enable for TDRE (transmit data register empty)*/
    BW_UART_C2_TIE(baseAddr, (uint8_t)enable);
}

/*!
 * @brief Gets the configuration of the tx_data_register_empty_interrupt enable setting.
 *
 * @param   baseAddr UART module base address.
 * @return  setting of the interrupt enable bit.
 */
static inline bool UART_HAL_GetTxDataRegEmptyIntCmd(uint32_t baseAddr)
{
    /* return interrupt enable condition of TIE  */
    return (bool)BR_UART_C2_TIE(baseAddr);
}

/*!
 * @brief Disables the rx_data_register_full_interrupt.
 *
 * @param   baseAddr UART module base address.
 * @param   enable   true: enable, false: disable.
 */
static inline void UART_HAL_SetRxDataRegFullIntCmd(uint32_t baseAddr, bool enable)
{
    /* receiver interrupt enable for receiver data register full (RDRF)*/
    BW_UART_C2_RIE(baseAddr, (uint8_t)enable);
}

/*!
 * @brief Gets the configuration of the rx_data_register_full_interrupt enable setting.
 *
 * @param   baseAddr UART module base address.
 * @return Bit setting of the interrupt enable bit.
 */
static inline bool UART_HAL_GetRxDataRegFullIntCmd(uint32_t baseAddr)
{
    /* return interrupt enable condition of RIE   */
    return (bool)BR_UART_C2_RIE(baseAddr);
}

/*!
 * @brief  Configures the UART DMA requests for the Transmitter and Receiver.
 *
 * This function allows the user to configure the transmit data register empty flag to
 * generate an interrupt request (default) or a DMA request.  Similarly, this function
 * allows the user to configure the receive data register full flag to generate an interrupt
 * request (default) or a DMA request.
 *
 * @param   baseAddr UART module base address.
 * @param   txDmaConfig Transmit DMA request configuration setting (enable: true /disable: false).
 * @param   rxDmaConfig Receive DMA request configuration setting (enable: true/disable: false).
 */
void UART_HAL_ConfigureDma(uint32_t baseAddr, bool txDmaConfig, bool rxDmaConfig);

/*!
 * @brief  Gets the UART Transmit DMA request configuration setting.
 *
 * This function returns the configuration setting of the Transmit DMA request.
 *
 * @param   baseAddr UART module base address.
 * @return   Transmit DMA request configuration setting (enable: true /disable: false).
 */
bool UART_HAL_IsTxdmaEnabled(uint32_t baseAddr);

/*!
 * @brief  Gets the UART Receive DMA request configuration setting.
 *
 * This function returns the configuration setting of the Receive DMA request.
 *
 * @param   baseAddr UART module base address.
 * @return   Receive DMA request configuration setting (enable: true /disable: false).
 */
bool UART_HAL_IsRxdmaEnabled(uint32_t baseAddr);

/*!
 * @brief  Get UART tx/rx data register address.
 *
 * This function is used for DMA transfer.
 *
 * @return  UART tx/rx data register address.
 */
static inline uint32_t UART_HAL_GetDataRegAddr(uint32_t baseAddr)
{
    return (uint32_t)HW_UART_D_ADDR(baseAddr);
}

/*@}*/

/*!
 * @name UART Transfer Functions
 * @{
 */

/*!
 * @brief This function allows the user to send an 8-bit character from the UART data register.
 *
 * @param   baseAddr UART module base address.
 * @param   data The data to send of size 8-bit.
 */
void UART_HAL_Putchar(uint32_t baseAddr, uint8_t data);

/*!
 * @brief This function allows the user to send a 9-bit character from the UART data register.
 *
 * @param   baseAddr UART module base address.
 * @param   data The data to send of size 9-bit.
 */
void UART_HAL_Putchar9(uint32_t baseAddr, uint16_t data);

/*!
 * @brief This function gets a received 8-bit character from the UART data register.
 *
 * @param   baseAddr UART module base address.
 * @param   readData The received data read from data register of size 8-bit.
 */
void  UART_HAL_Getchar(uint32_t baseAddr, uint8_t *readData);

/*!
 * @brief This function gets a received 9-bit character from the UART data register.
 *
 * @param   baseAddr UART module base address.
 * @param   readData The received data read from data register of size 9-bit.
 */
void  UART_HAL_Getchar9(uint32_t baseAddr, uint16_t *readData);

#if FSL_FEATURE_UART_HAS_EXTENDED_DATA_REGISTER_FLAGS
/*!
 * @brief  Configures the UART bit 10 (if enabled) or bit 9 (if disabled) as the parity bit in the
 *         serial transmission.
 *
 * This function configures bit 10 or bit 9 to be the parity bit.  To configure bit 10 as the parity
 * bit, the function sets UARTx_C4[M10]; it also sets UARTx_C1[M] and UARTx_C1[PE] as required.
 *
 * @param   baseAddr UART module base address.
 * @param  enable The setting to enable (true), which configures bit 10 as the parity bit or to
 *                disable (false), which configures bit 9 as the parity bit in the serial
 *                transmission.
 */
static inline void UART_HAL_SetBit10AsParitybit(uint32_t baseAddr, bool enable)
{
    /* to enable the parity bit as the tenth data bit, along with enabling UARTx_C4[M10]
     * need to also enable parity and set UARTx_C1[M] bit
     * assumed that the user has already set the appropriate bits */
    BW_UART_C4_M10(baseAddr, enable);
}

/*!
 * @brief  Gets the configuration of the UART bit 10 (if enabled) or bit 9 (if disabled) as the
 *         parity bit in the serial transmission.
 *
 * This function returns true if bit 10 is configured as the parity bit, otherwise it returns
 * false if bit 9 is configured as the parity bit.
 *
 * @param   baseAddr UART module base address.
 * @return  The configuration setting of bit 10 (true), or bit 9 (false) as the
 *          parity bit in the serial transmission.
 */
static inline bool UART_HAL_IsBit10SetAsParitybit(uint32_t baseAddr)
{
    /* to see if the parity bit is set as the tenth data bit,
     * return value of UARTx_C4[M10] */
    return BR_UART_C4_M10(baseAddr);
}

/*!
 * @brief  Determines whether the UART received data word was received with noise.
 *
 * This function returns true if the received data word was received with noise. Otherwise,
 * it returns false indicating no noise was detected.
 *
 * @param   baseAddr UART module base address.
 * @return  The status of the NOISY bit in the UART extended data register.
 */
static inline bool UART_HAL_IsCurrentDatawordReceivedWithNoise(uint32_t baseAddr)
{
    /* to see if the current dataword was received with noise,
     * return value of UARTx_ED[NOISY] */
    return BR_UART_ED_NOISY(baseAddr);
}

/*!
 * @brief  Determines whether the UART received data word was received with a parity error.
 *
 * This function returns true if the received data word was received with a parity error.
 * Otherwise, it returns false indicating no parity error was detected.
 *
 * @param   baseAddr UART module base address.
 * @return  The status of the PARITYE (parity error) bit in the UART extended data register.
 */
static inline bool UART_HAL_IsCurrentDatawordReceivedWithParityerror(uint32_t baseAddr)
{
    /* to see if the current dataword was received with parity error,
     * return value of UARTx_ED[PARITYE] */
    return BR_UART_ED_PARITYE(baseAddr);
}

#endif  /* FSL_FEATURE_UART_HAS_EXTENDED_DATA_REGISTER_FLAGS*/

/*@}*/

/*!
 * @name UART Special Feature Configurations
 * @{
 */

/*!
 * @brief Configures the UART to either operate or cease to operate in WAIT mode.
 *
 * The function configures the UART to either operate or cease to operate when WAIT mode is
 * entered.
 *
 * @param   baseAddr UART module base address.
 * @param   mode The UART WAIT mode operation - operates or ceases to operate in WAIT mode.
 */
static inline void UART_HAL_SetWaitModeOperation(uint32_t baseAddr, uart_operation_config_t mode)
{
	/*In CPU wait mode: 0 - uart is enabled; 1 - uart is disabled */
	BW_UART_C1_UARTSWAI(baseAddr, mode);
}

/*!
 * @brief Determines if the UART operates or ceases to operate in WAIT mode.
 *
 * This function returns kUartOperates if the UART has been configured to operate in WAIT mode.
 * Else it returns KUartStops if the UART has been configured to cease-to-operate in WAIT mode.
 *
 * @param   baseAddr UART module base address.
 * @return The UART WAIT mode operation configuration, returns either kUartOperates or KUartStops.
 */
static inline uart_operation_config_t UART_HAL_GetWaitModeOperation(uint32_t baseAddr)
{
    /*In CPU wait mode: 0 - uart is enabled; 1 - uart is disabled */
    return (uart_operation_config_t)BR_UART_C1_UARTSWAI(baseAddr);
}

/*!
 * @brief Configures the UART loopback operation.
 *
 * This function enables or disables the UART loopback operation.
 *
 * @param baseAddr UART module base address.
 * @param enable The UART loopback mode configuration, either disabled (false) or enabled (true).
 */
static inline void UART_HAL_SetLoopCmd(uint32_t baseAddr, bool enable)
{
    BW_UART_C1_LOOPS(baseAddr, enable); 
}

/*!
 * @brief Configures the UART single-wire operation.
 *
 * This function enables or disables the UART single-wire operation.
 * In some UART baseAddrs it is required that the transmitter/receiver be disabled
 * before calling this function.
 * This may be applied to all UARTs to ensure safe operation.
 *
 * @param baseAddr UART module base address.
 * @param enable The UART single-wire mode configuration, either disabled (false) or enabled (true).
 */
static inline void UART_HAL_SetReceiverSource(uint32_t baseAddr, uart_receiver_source_t source)
{
    BW_UART_C1_RSRC(baseAddr, source);
}
/*!
 * @brief Configures the UART transmit direction while in single-wire mode.
 *
 * This function configures the transmitter direction when the UART is configured for single-wire
 * operation.
 *
 * @param   baseAddr UART module base address.
 * @param   direction The UART single-wire mode transmit direction configuration of type
 *                    uart_singlewire_txdir_t (either kUartSinglewireTxdirIn or
 *                    kUartSinglewireTxdirOut.
 */
static inline void UART_HAL_SetTransmitterDir(uint32_t baseAddr, uart_singlewire_txdir_t direction)
{
    /* configure UART transmit direction (input or output) when in single-wire mode
     * it is assumed UART is in single-wire mode
     */
    BW_UART_C3_TXDIR(baseAddr, direction);
}

/*!
 * @brief  Places the UART receiver in standby mode.
 *
 * This function, when called, places the UART receiver into standby mode.
 * In some UART baseAddrs, there are conditions that must be met before placing Rx in standby mode.
 * Before placing UART in standby, determine if receiver is set to
 * wake on idle, and if receiver is already in idle state. 
 * NOTE: RWU should only be set with C1[WAKE] = 0 (wakeup on idle) if the channel is currently
 * not idle.
 * This can be determined by the S2[RAF] flag. If set to wake up FROM an IDLE event and the channel
 * is already idle, it is possible that the UART will discard data because data must be received
 * (or a LIN break detect) after an IDLE is detected before IDLE is allowed to be reasserted.
 *
 * @param baseAddr UART module base address.
 * @return Error code or kStatus_UART_Success.
 */
uart_status_t UART_HAL_PutReceiverInStandbyMode(uint32_t baseAddr);

/*!
 * @brief  Places the UART receiver in normal mode (disable standby mode operation).
 *
 * This function, when called, places the UART receiver into normal mode and out of
 * standby mode.
 *
 * @param   baseAddr UART module base address.
 */
static inline void UART_HAL_PutReceiverInNormalMode(uint32_t baseAddr)
{
    /* clear the RWU bit to place receiver into normal mode (disable standby mode)*/
    HW_UART_C2_CLR(baseAddr, BM_UART_C2_RWU);
}

/*!
 * @brief  Determines if the UART receiver is currently in standby mode.
 *
 * This function determines the state of the UART receiver. If it returns true, this means
 * that the UART receiver is in standby mode; if it returns false, the UART receiver
 * is in normal mode.
 *
 * @param   baseAddr UART module base address.
 * @return The UART receiver is in normal mode (false) or standby mode (true).
 */
static inline bool UART_HAL_IsReceiverInStandby(uint32_t baseAddr)
{
    /* return the RWU bit setting (0 - normal more, 1 - standby)*/
    return BR_UART_C2_RWU(baseAddr);
}

/*!
 * @brief  Selects the UART receiver wakeup method (idle-line or address-mark) from standby mode.
 *
 * This function configures the wakeup method of the UART receiver from standby mode.  The options
 * are idle-line wake or address-mark wake.
 *
 * @param   baseAddr UART module base address.
 * @param   method The UART receiver wakeup method options: kUartIdleLineWake - Idle-line wake or
 *                 kUartAddrMarkWake - address-mark wake.
 */
static inline void UART_HAL_SetReceiverWakeupMethod(uint32_t baseAddr, uart_wakeup_method_t method)
{
    /* configure the WAKE bit for idle line wake or address mark wake */
    BW_UART_C1_WAKE(baseAddr, method);
}

/*!
 * @brief  Gets the UART receiver wakeup method (idle-line or address-mark) from standby mode.
 *
 * This function returns how the UART receiver is configured to wake from standby mode. The
 * wake method options that can be returned are kUartIdleLineWake or kUartAddrMarkWake.
 *
 * @param   baseAddr UART module base address.
 * @return  The UART receiver wakeup from standby method, false: kUartIdleLineWake (idle-line wake)
 *          or true: kUartAddrMarkWake (address-mark wake).
 */
static inline uart_wakeup_method_t UART_HAL_GetReceiverWakeupMethod(uint32_t baseAddr)
{
    /* get configuration of the WAKE bit for idle line wake or address mark wake */
    return (uart_wakeup_method_t)BR_UART_C1_WAKE(baseAddr);
}

/*!
 * @brief  Configures the operation options of the UART idle line detect.
 *
 * This function allows the user to configure the UART idle-line detect operation. There are two
 * separate operations for the user to configure, the idle line bit-count start and the receive
 * wake up affect on IDLE status bit. The user will pass in a structure of type
 * uart_idle_line_config_t.
 *
 * @param   baseAddr UART module base address.
 * @param   idleLine Idle bit count start: 0 - after start bit (default), 1 - after stop bit 
 * @param   rxWakeIdleDetect Receiver Wake Up Idle Detect. IDLE status bit operation during receive
 *          standby. Controls whether idle character that wakes up receiver will also set IDLE status
 *          bit. 0 - IDLE status bit doesn't get set (default), 1 - IDLE status bit gets set
 */
void UART_HAL_ConfigIdleLineDetect(uint32_t baseAddr, uint8_t idleLine, uint8_t rxWakeIdleDetect);

/*!
 * @brief  Configures the UART break character transmit length.
 *
 * This function allows the user to configure the UART break character transmit length. Refer to
 * the typedef uart_break_char_length_t for setting options.
 * In some UART baseAddrs it is required that the transmitter be disabled before calling
 * this function. This may be applied to all UARTs to ensure safe operation.
 *
 * @param baseAddr UART module base address.
 * @param length The UART break character length setting of type uart_break_char_length_t, either a
 *               minimum 10-bit times or a minimum 13-bit times.
 */
static inline void UART_HAL_SetBreakCharTransmitLength(uint32_t baseAddr, 
                                                       uart_break_char_length_t length)
{
    /* Configure BRK13 - Break Character transmit length configuration
     * UART break character length setting:
     * 0 - minimum 10-bit times (default),
     * 1 - minimum 13-bit times */
    BW_UART_S2_BRK13(baseAddr, length);
}

/*!
 * @brief  Configures the UART break character detect length.
 *
 * This function allows the user to configure the UART break character detect length. Refer to
 * the typedef uart_break_char_length_t for setting options.
 *
 * @param baseAddr UART module base address.
 * @param length The UART break character length setting of type uart_break_char_length_t, either a
 *               minimum 10-bit times or a minimum 13-bit times.
 */
static inline void UART_HAL_SetBreakCharDetectLength(uint32_t baseAddr, uart_break_char_length_t length)
{
    /* Configure LBKDE - Break Character detect length configuration
     * UART break character length setting:
     * 0 - minimum 10-bit times (default),
     * 1 - minimum 13-bit times */
    BW_UART_S2_LBKDE(baseAddr, length);
}

/*!
 * @brief  Configures the UART transmit send break character operation.
 *
 * This function allows the user to queue a UART break character to send.  If true is passed into
 * the function, then a break character is queued for transmission.  A break character will
 * continuously be queued until this function is called again when a false is passed into this
 * function.
 *
 * @param   baseAddr UART module base address.
 * @param   enable If false, the UART normal/queue break character setting is disabled, which
 *                 configures the UART for normal transmitter operation. If true, a break
 *                 character is queued for transmission.
 */
static inline void UART_HAL_SetBreakCharCmd(uint32_t baseAddr, bool enable)
{
    BW_UART_C2_SBK(baseAddr, enable);
}

/*!
 * @brief  Configures the UART match address mode control operation. (Note: Feature available on
 *         select UART baseAddrs)
 *
 * The function allows the user to configure the UART match address control operation. The user
 * has the option to enable the match address mode and to program the match address value. There
 * are two match address modes, each with its own enable and programmable match address value.
 *
 * @param  baseAddr UART module base address.
 * @param  matchAddrMode1 If true, this enables match address mode 1 (MAEN1), where false disables.
 * @param  matchAddrMode2 If true, this enables match address mode 2 (MAEN2), where false disables.
 * @param  matchAddrValue1 The match address value to program for match address mode 1.
 * @param  matchAddrValue2 The match address value to program for match address mode 2.
 */
void UART_HAL_SetMatchAddress(uint32_t baseAddr, bool matchAddrMode1, bool matchAddrMode2,
                              uint8_t matchAddrValue1, uint8_t matchAddrValue2);

#if FSL_FEATURE_UART_HAS_BIT_ORDER_SELECT
/*!
 * @brief Configures the UART to send data MSB first
 * (Note: Feature available on select UART baseAddrs)
 *
 * The function allows the user to configure the UART to send data MSB first or LSB first.
 * In some UART baseAddrs it is required that the transmitter/receiver be disabled
 * before calling this function.
 * This may be applied to all UARTs to ensure safe operation.
 *
 * @param   baseAddr UART module base address.
 * @param   enable This configures send MSB first mode configuration. If true, the data is sent MSB
 *                 first; if false, it is sent LSB first.
 */
static inline void UART_HAL_SetSendMsbFirstCmd(uint32_t baseAddr, bool enable)
{
    BW_UART_S2_MSBF(baseAddr, enable);
}
#endif

#if FSL_FEATURE_UART_HAS_MODEM_SUPPORT
/*!
 * @brief  Enables the UART receiver request-to-send functionality.
 *
 * This function allows the user to enable the UART receiver request-to-send (RTS) functionality.
 * By enabling, it allows the RTS output to control the CTS input of the transmitting device to
 * prevent receiver overrun. RTS is deasserted if the number of characters in the receiver data
 * register (FIFO) is equal to or greater than RWFIFO[RXWATER]. RTS is asserted when the
 * number of characters in the receiver data register (FIFO) is less than RWFIFO[RXWATER].
 * Do not set both RXRTSE and TXRTSE.
 *
 * @param   baseAddr UART module base address.
 * @param   enable   Enable or disable receiver rts.
 */
static inline void UART_HAL_SetReceiverRtsCmd(uint32_t baseAddr, bool enable)
{
    /* Set RXRTSE */
    BW_UART_MODEM_RXRTSE(baseAddr, enable);
}

/*!
 * @brief  Enables the UART transmitter request-to-send functionality.
 *
 * This function allows the user to enable the UART transmitter request-to-send (RTS) functionality.
 * When enabled, it allows the UART to control the RTS assertion before and after a transmission
 * such that when a character is placed into an empty transmitter data buffer, RTS
 * asserts one bit time before the start bit is transmitted. RTS deasserts one bit time after all
 * characters in the transmitter data buffer and shift register are completely sent, including
 * the last stop bit.
 *
 * @param   baseAddr UART module base address.
 * @param   enable   Enable or disable transmitter RTS.
 */
static inline void UART_HAL_SetTransmitterRtsCmd(uint32_t baseAddr, bool enable)
{
    /* Set TXRTSE */
    BW_UART_MODEM_TXRTSE(baseAddr, enable);
}

/*!
 * @brief  Configures the UART transmitter RTS polarity.
 *
 * This function allows the user configure the transmitter RTS polarity to be either active low
 * or active high.
 *
 * @param baseAddr UART module base address.
 * @param polarity The UART transmitter RTS polarity setting (false - active low,
 *                 true - active high).
 */
static inline void UART_HAL_SetTransmitterRtsPolarityMode(uint32_t baseAddr, bool polarity)
{
    /* Configure the transmitter rts polarity: 0=active low, 1=active high */
    BW_UART_MODEM_TXRTSPOL(baseAddr, polarity);
}

/*!
 * @brief  Enables the UART transmitter clear-to-send functionality.
 *
 * This function allows the user to enable the UART transmitter clear-to-send (CTS) functionality.
 * When enabled, the transmitter checks the state of CTS each time it is ready to send a character.
 * If CTS is asserted, the character is sent. If CTS is deasserted, the signal TXD remains in
 * the mark state and transmission is delayed until CTS is asserted. Changes in CTS as a
 * character is being sent do not affect its transmission.
 *
 * @param   baseAddr UART module base address.
 * @param   enable   Enable or disable transmitter CTS.
 */
static inline void UART_HAL_SetTransmitterCtsCmd(uint32_t baseAddr, bool enable)
{
    /* Set TXCTSE */
    BW_UART_MODEM_TXCTSE(baseAddr, enable);
}

#endif  /* FSL_FEATURE_UART_HAS_MODEM_SUPPORT*/

#if FSL_FEATURE_UART_HAS_IR_SUPPORT
/*!
 * @brief  Configures the UART infrared operation.
 *
 * The function allows the user to enable or disable the UART infrared (IR) operation
 * and to configure the IR pulse width.
 *
 * @param   baseAddr UART module base address.
 * @param   enable Enable (true) or disable (false) the infrared operation.
 * @param   pulseWidth The UART transmit narrow pulse width setting of type uart_ir_tx_pulsewidth_t.
 */
void UART_HAL_SetInfraredOperation(uint32_t baseAddr, bool enable,
                                           uart_ir_tx_pulsewidth_t pulseWidth);
#endif  /* FSL_FEATURE_UART_HAS_IR_SUPPORT*/

/*@}*/

/*!
 * @name UART Status Flags
 * @{
 */

/*!
 * @brief  Gets all  UART status flag states.
 *
 * @param   baseAddr UART module base address.
 * @param   statusFlag Status flag name.
 */
bool UART_HAL_GetStatusFlag(uint32_t baseAddr, uart_status_flag_t statusFlag);

/*!
 * @brief  Gets the UART Transmit data register empty flag.
 *
 * This function returns the state of the UART Transmit data register empty flag.
 *
 * @param baseAddr UART module base address.
 * @return The status of Transmit data register empty flag, which is set when transmit buffer
 *          is empty.
 */
static inline bool UART_HAL_IsTxDataRegEmpty(uint32_t baseAddr)
{
    /* return status condition of TDRE flag  */
    return BR_UART_S1_TDRE(baseAddr);
}

/*!
 * @brief  Gets the UART Transmission complete flag.
 *
 * This function returns the state of the UART Transmission complete flag.
 *
 * @param baseAddr UART module base address.
 * @return The status of Transmission complete flag, which is set when the transmitter is idle
 *         (transmission activity complete).
 */
static inline bool UART_HAL_IsTxComplete(uint32_t baseAddr)
{
    /* return status condition of TC flag  */ 
    return BR_UART_S1_TC(baseAddr);
}

/*!
 * @brief  Gets the UART Receive data register full flag.
 *
 * This function returns the state of the UART Receive data register full flag.
 *
 * @param baseAddr UART module base address.
 * @return The status of Receive data register full flag, which is set when the receive data buffer
 *         is full.
 */
static inline bool UART_HAL_IsRxDataRegFull(uint32_t baseAddr)
{
    /* return status condition of RDRF flag  */
    return BR_UART_S1_RDRF(baseAddr);
}

/*!
 * @brief  Clears an individual and specific UART status flag.
 *
 * This function allows the user to clear an individual and specific UART status flag. Refer to
 * structure definition uart_status_flag_t for list of status bits.
 *
 * @param baseAddr UART module base address.
 * @param statusFlag The desired UART status flag to clear.
 * @return An error code or kStatus_UART_Success.
 */
uart_status_t UART_HAL_ClearStatusFlag(uint32_t baseAddr, uart_status_flag_t statusFlag);

/*!
 * @brief  Clears all UART status flags.
 *
 * This function tries to clear all of the UART status flags.  In some cases, some of the status
 * flags may not get cleared because the condition that set the flag may still exist.
 *
 * @param   baseAddr UART module base address.
 */
void UART_HAL_ClearAllNonAutoclearStatusFlags(uint32_t baseAddr);

/*@}*/

/*!
 * @name UART FIFO Configurations
 * @{
 */

#if FSL_FEATURE_UART_HAS_FIFO
/*!
 * @brief  Enables or disable the UART transmit FIFO.
 *
 * This function allows the user to enable or disable the UART transmit FIFO.
 * It is required that the transmitter/receiver be disabled before calling this function
 * when the FIFO is empty.
 * Additionally, TXFLUSH and RXFLUSH commands should be issued after calling this function.
 *
 * @param baseAddr UART module base address.
 * @param enable Enable or disable Tx FIFO.
 * @return Error code if it is detected that the transmitter or receiver is enabled or
 *         kStatus_UART_Success.
 */
uart_status_t UART_HAL_SetTxFifoCmd(uint32_t baseAddr, bool enable);

/*!
 * @brief  Enables or disable the UART receive FIFO.
 *
 * This function allows the user to enable or disable the UART receive FIFO.
 * It is required that the transmitter/receiver be disabled before calling this function
 * when the FIFO is empty.
 * Additionally, TXFLUSH and RXFLUSH commands should be issued after calling this function.
 *
 * @param baseAddr UART module base address.
 * @param enable Enable or disable Rx FIFO.
 * @return Error code if it is detected that the transmitter or receiver is enabled or
 *         kStatus_UART_Success.
 */
uart_status_t UART_HAL_SetRxFifoCmd(uint32_t baseAddr, bool enable);

/*!
 * @brief  Gets the size of the UART transmit FIFO.
 *
 * This function returns the size (number of entries) supported in the UART transmit FIFO for
 * a particular module baseAddr.
 *
 * @param baseAddr UART module base address.
 * @return  The UART transmit FIFO size as follows:
 *    0x0: 1 data word; 0x1: 4 data words; 0x2: 8 data words; 0x3: 16 data words
 *    0x4: 32 data words; 0x5: 64 data words; 0x6: 128 data words; 0x7: reserved
 */
static inline uint8_t UART_HAL_GetTxFifoSize(uint32_t baseAddr)
{
    return BR_UART_PFIFO_TXFIFOSIZE(baseAddr);
}

/*!
 * @brief  Gets the size of the UART receive FIFO.
 *
 * This function returns the size (number of entries) supported in the UART receive FIFO for
 * a particular module baseAddr.
 *
 * @param   baseAddr UART module base address.
 * @return  The receive FIFO size as follows:
 *    0x0: 1 data word; 0x1: 4 data words; 0x2: 8 data words; 0x3: 16 data words
 *    0x4: 32 data words; 0x5: 64 data words; 0x6: 128 data words; 0x7: reserved
 */
static inline uint8_t UART_HAL_GetRxFifoSize(uint32_t baseAddr)
{
    return BR_UART_PFIFO_RXFIFOSIZE(baseAddr);
}

/*!
 * @brief  Flushes the UART transmit FIFO.
 *
 * This function allows the user to flush the UART transmit FIFO for a particular module baseAddr.
 * Flushing the FIFO may result in data loss.
 * It is recommended that the transmitter be disabled before calling this function.
 *
 * @param baseAddr UART module base address.
 * @return Error code if it is detected that the transmitter or receiver is enabled or
 *         kStatus_UART_Success.
 */
uart_status_t UART_HAL_FlushTxFifo(uint32_t baseAddr);

/*!
 * @brief  Flushes the UART receive FIFO.
 *
 * This function allows the user to flush the UART receive FIFO for a particular module baseAddr.
 * Flushing the FIFO may result in data loss.
 * It is recommended that the receiver be disabled before calling this function.
 *
 * @param baseAddr UART module base address.
 * @return Error code if it is detected that the transmitter or receiver is enabled or
 *         kStatus_UART_Success.
 */
uart_status_t UART_HAL_FlushRxFifo(uint32_t baseAddr);

/*!
 * @brief  Gets the UART transmit FIFO empty status state.
 *
 * The function returns the state of the transmit FIFO empty status state, but does not take into
 * account data in the shift register.
 *
 * @param   baseAddr UART module base address.
 * @return  The UART transmit FIFO empty status: true=empty; false=not-empty.
 */
static inline bool UART_HAL_IsTxFifoEmpty(uint32_t baseAddr)
{
    return BR_UART_SFIFO_TXEMPT(baseAddr);
}

/*!
 * @brief  Gets the UART receive FIFO empty status state.
 *
 * The function returns the state of the receive FIFO empty status state, but does not take into
 * account data in the shift register.
 *
 * @param   baseAddr UART module base address.
 * @return  The UART receive FIFO empty status: true=empty; false=not-empty.
 */
static inline bool UART_HAL_IsRxFifoEmpty(uint32_t baseAddr)
{
    return BR_UART_SFIFO_RXEMPT(baseAddr);
}

/*!
 * @brief  Sets the UART transmit FIFO watermark value.
 *
 * Programming the transmit watermark should be done when UART the transmitter is disabled
 * and the value must be set less than the size obtained from UART_HAL_GetTxFifoSize.
 *
 * @param   baseAddr UART module base address.
 * @param   watermark  The UART transmit watermark value to be programmed.
 * @return  Error code if transmitter is enabled or kStatus_UART_Success.
 */
uart_status_t UART_HAL_SetTxFifoWatermark(uint32_t baseAddr, uint8_t watermark);

/*!
 * @brief  Gets the UART transmit FIFO watermark value.
 *
 * @param   baseAddr UART module base address.
 * @return  The value currently programmed for the UART transmit watermark.
 */
static inline uint8_t UART_HAL_GetTxFifoWatermark(uint32_t baseAddr)
{
    /* get watermark*/
    return HW_UART_TWFIFO_RD(baseAddr);
}

/*!
 * @brief  Gets the UART transmit FIFO data word count (number of words in the transmit FIFO).
 *
 * The function UART_HAL_GetTxDatawordCountInFifo excludes any data that may
 * be in the UART transmit shift register
 *
 * @param   baseAddr UART module base address.
 * @return  The number of data words currently in the UART transmit FIFO.
 */
static inline uint8_t UART_HAL_GetTxDatawordCountInFifo(uint32_t baseAddr)
{
    /* get the current number of datawords in the FIFO*/
    return HW_UART_TCFIFO_RD(baseAddr);
}

/*!
 * @brief  Sets the UART receive FIFO watermark value.
 *
 * Programming the receive watermark should be done when the receiver is disabled
 * and the value must be set less than the size obtained from UART_HAL_GetRxFifoSize and
 * greater than zero.
 *
 * @param   baseAddr UART module base address.
 * @param  watermark  The UART receive watermark value to be programmed.
 * @return  Error code if receiver is enabled or kStatus_UART_Success.
 */
uart_status_t UART_HAL_SetRxFifoWatermark(uint32_t baseAddr, uint8_t watermark);

/*!
 * @brief  Gets the UART receive FIFO data word count (number of words in the receive FIFO).
 *
 * The function UART_HAL_GetRxDatawordCountInFifo excludes any data that may be
 * in the receive shift register.
 *
 * @param   baseAddr UART module base address.
 * @return  The number of data words currently in the UART receive FIFO.
 */
static inline uint8_t UART_HAL_GetRxDatawordCountInFifo(uint32_t baseAddr)
{
    /* get the current number of datawords in the FIFO*/
    return HW_UART_RCFIFO_RD(baseAddr);
}

/*!
 * @brief  Gets the UART receive FIFO watermark value.
 *
 * @param   baseAddr UART module base address.
 * @return  The value currently programmed for the UART receive watermark.
 */
static inline uint8_t UART_HAL_GetRxFifoWatermark(uint32_t baseAddr)
{
    /* get watermark*/
    return HW_UART_RWFIFO_RD(baseAddr);
}

#endif  /* FSL_FEATURE_UART_HAS_FIFO*/

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* __FSL_UART_HAL_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

