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
#ifndef __FSL_FLEXCAN_HAL_H__
#define __FSL_FLEXCAN_HAL_H__

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include "fsl_flexcan_features.h"
#include "fsl_device_registers.h"

#ifndef MBED_NO_FLEXCAN

/*!
 * @addtogroup flexcan_hal
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief FlexCAN constants*/
enum _flexcan_constants
{
    kFlexCanMessageSize = 8,               /*!< FlexCAN message buffer data size in bytes*/
};

/*! @brief The Status enum is used to report current status of the FlexCAN interface.*/
enum _flexcan_err_status
{
    kFlexCan_RxWrn   = 0x0080, /*!< Reached warning level for RX errors*/
    kFlexCan_TxWrn   = 0x0100, /*!< Reached warning level for TX errors*/
    kFlexCan_StfErr  = 0x0200, /*!< Stuffing Error*/
    kFlexCan_FrmErr  = 0x0400, /*!< Form Error*/
    kFlexCan_CrcErr  = 0x0800, /*!< Cyclic Redundancy Check Error*/
    kFlexCan_AckErr  = 0x1000, /*!< Received no ACK on transmission*/
    kFlexCan_Bit0Err = 0x2000, /*!< Unable to send dominant bit*/
    kFlexCan_Bit1Err = 0x4000, /*!< Unable to send recessive bit*/
};

/*! @brief FlexCAN status return codes*/
typedef enum _flexcan_status
{
    kStatus_FLEXCAN_Success = 0,
    kStatus_FLEXCAN_OutOfRange,
    kStatus_FLEXCAN_UnknownProperty,
    kStatus_FLEXCAN_InvalidArgument,
    kStatus_FLEXCAN_Fail,
    kStatus_FLEXCAN_TimeOut,
} flexcan_status_t;


/*! @brief FlexCAN operation modes*/
typedef enum _flexcan_operation_modes {
    kFlexCanNormalMode,        /*!< Normal mode or user mode*/
    kFlexCanListenOnlyMode,    /*!< Listen-only mode*/
    kFlexCanLoopBackMode,      /*!< Loop-back mode*/
    kFlexCanFreezeMode,        /*!< Freeze mode*/
    kFlexCanDisableMode,       /*!< Module disable mode*/
} flexcan_operation_modes_t;

/*! @brief FlexCAN message buffer CODE for Rx buffers*/
typedef enum _flexcan_mb_code_rx {
    kFlexCanRX_Inactive  = 0x0, /*!< MB is not active.*/
    kFlexCanRX_Full      = 0x2, /*!< MB is full.*/
    kFlexCanRX_Empty     = 0x4, /*!< MB is active and empty.*/
    kFlexCanRX_Overrun   = 0x6, /*!< MB is overwritten into a full buffer.*/
    kFlexCanRX_Busy      = 0x8, /*!< FlexCAN is updating the contents of the MB.*/
                                /*!  The CPU must not access the MB.*/
    kFlexCanRX_Ranswer   = 0xA, /*!< A frame was configured to recognize a Remote Request Frame*/
                                /*!  and transmit a Response Frame in return.*/
    kFlexCanRX_NotUsed   = 0xF, /*!< Not used*/
} flexcan_mb_code_rx_t;

/*! @brief FlexCAN message buffer CODE FOR Tx buffers*/
typedef enum _flexcan_mb_code_tx {
    kFlexCanTX_Inactive  = 0x08, /*!< MB is not active.*/
    kFlexCanTX_Abort     = 0x09, /*!< MB is aborted.*/
    kFlexCanTX_Data      = 0x0C, /*!< MB is a TX Data Frame(MB RTR must be 0).*/
    kFlexCanTX_Remote    = 0x1C, /*!< MB is a TX Remote Request Frame (MB RTR must be 1).*/
    kFlexCanTX_Tanswer   = 0x0E, /*!< MB is a TX Response Request Frame from.*/
                                 /*!  an incoming Remote Request Frame.*/
    kFlexCanTX_NotUsed   = 0xF,  /*!< Not used*/
} flexcan_mb_code_tx_t;

/*! @brief FlexCAN message buffer transmission types*/
typedef enum _flexcan_mb_transmission_type {
    kFlexCanMBStatusType_TX,          /*!< Transmit MB*/
    kFlexCanMBStatusType_TXRemote,    /*!< Transmit remote request MB*/
    kFlexCanMBStatusType_RX,          /*!< Receive MB*/
    kFlexCanMBStatusType_RXRemote,    /*!< Receive remote request MB*/
    kFlexCanMBStatusType_RXTXRemote,  /*!< FlexCAN remote frame receives remote request and*/
                                      /*!  transmits MB.*/
} flexcan_mb_transmission_type_t;

typedef enum _flexcan_rx_fifo_id_element_format {
    kFlexCanRxFifoIdElementFormat_A, /*!< One full ID (standard and extended) per ID Filter Table*/
                                     /*!  element.*/
    kFlexCanRxFifoIdElementFormat_B, /*!< Two full standard IDs or two partial 14-bit (standard and*/
                                     /*!  extended) IDs per ID Filter Table element.*/
    kFlexCanRxFifoIdElementFormat_C, /*!< Four partial 8-bit Standard IDs per ID Filter Table*/
                                     /*!  element.*/
    kFlexCanRxFifoIdElementFormat_D, /*!< All frames rejected.*/
} flexcan_rx_fifo_id_element_format_t;

/*! @brief FlexCAN Rx FIFO filters number*/
typedef enum _flexcan_rx_fifo_id_filter_number {
    kFlexCanRxFifoIDFilters_8   = 0x0,         /*!<   8 Rx FIFO Filters*/
    kFlexCanRxFifoIDFilters_16  = 0x1,         /*!<  16 Rx FIFO Filters*/
    kFlexCanRxFifoIDFilters_24  = 0x2,         /*!<  24 Rx FIFO Filters*/
    kFlexCanRxFifoIDFilters_32  = 0x3,         /*!<  32 Rx FIFO Filters*/
    kFlexCanRxFifoIDFilters_40  = 0x4,         /*!<  40 Rx FIFO Filters*/
    kFlexCanRxFifoIDFilters_48  = 0x5,         /*!<  48 Rx FIFO Filters*/
    kFlexCanRxFifoIDFilters_56  = 0x6,         /*!<  56 Rx FIFO Filters*/
    kFlexCanRxFifoIDFilters_64  = 0x7,         /*!<  64 Rx FIFO Filters*/
    kFlexCanRxFifoIDFilters_72  = 0x8,         /*!<  72 Rx FIFO Filters*/
    kFlexCanRxFifoIDFilters_80  = 0x9,         /*!<  80 Rx FIFO Filters*/
    kFlexCanRxFifoIDFilters_88  = 0xA,         /*!<  88 Rx FIFO Filters*/
    kFlexCanRxFifoIDFilters_96  = 0xB,         /*!<  96 Rx FIFO Filters*/
    kFlexCanRxFifoIDFilters_104 = 0xC,         /*!< 104 Rx FIFO Filters*/
    kFlexCanRxFifoIDFilters_112 = 0xD,         /*!< 112 Rx FIFO Filters*/
    kFlexCanRxFifoIDFilters_120 = 0xE,         /*!< 120 Rx FIFO Filters*/
    kFlexCanRxFifoIDFilters_128 = 0xF          /*!< 128 Rx FIFO Filters*/
} flexcan_rx_fifo_id_filter_num_t;

/*! @brief FlexCAN RX FIFO ID filter table structure*/
typedef struct FLEXCANIdTable {
    bool is_remote_mb;      /*!< Remote frame*/
    bool is_extended_mb;    /*!< Extended frame*/
    uint32_t *id_filter;    /*!< Rx FIFO ID filter elements*/
} flexcan_id_table_t;

/*! @brief FlexCAN RX mask type.*/
typedef enum _flexcan_rx_mask_type {
    kFlexCanRxMask_Global,      /*!< Rx global mask*/
    kFlexCanRxMask_Individual,  /*!< Rx individual mask*/
} flexcan_rx_mask_type_t;

/*! @brief FlexCAN MB ID type*/
typedef enum _flexcan_mb_id_type {
    kFlexCanMbId_Std,         /*!< Standard ID*/
    kFlexCanMbId_Ext,         /*!< Extended ID*/
} flexcan_mb_id_type_t;

/*! @brief FlexCAN clock source*/
typedef enum _flexcan_clk_source {
    kFlexCanClkSource_Osc,    /*!< Oscillator clock*/
    kFlexCanClkSource_Ipbus,  /*!< Peripheral clock*/
} flexcan_clk_source_t;

/*! @brief FlexCAN error interrupt types*/
typedef enum _flexcan_int_type {
    kFlexCanInt_Buf,           /*!< OR'd message buffers interrupt*/
    kFlexCanInt_Err,           /*!< Error interrupt*/
    kFlexCanInt_Boff,          /*!< Bus off interrupt*/
    kFlexCanInt_Wakeup,        /*!< Wakeup interrupt*/
    kFlexCanInt_Txwarning,     /*!< TX warning interrupt*/
    kFlexCanInt_Rxwarning,     /*!< RX warning interrupt*/
} flexcan_int_type_t;

/*! @brief FlexCAN bus error counters*/
typedef struct FLEXCANBerrCounter {
    uint16_t txerr;           /*!< Transmit error counter*/
    uint16_t rxerr;           /*!< Receive error counter*/
} flexcan_berr_counter_t;

/*! @brief FlexCAN MB code and status for transmit and receive */
typedef struct FLEXCANMbCodeStatus {
    uint32_t code;                    /*!< MB code for TX or RX buffers.
                                        Defined by flexcan_mb_code_rx_t and flexcan_mb_code_tx_t */
    flexcan_mb_id_type_t msg_id_type; /*!< Type of message ID (standard or extended)*/
    uint32_t data_length;             /*!< Length of Data in Bytes*/
} flexcan_mb_code_status_t;

/*! @brief FlexCAN message buffer structure*/
typedef struct FLEXCANMb {
    uint32_t cs;                        /*!< Code and Status*/
    uint32_t msg_id;                    /*!< Message Buffer ID*/
    uint8_t data[kFlexCanMessageSize];  /*!< Bytes of the FlexCAN message*/
} flexcan_mb_t;

/*! @brief FlexCAN configuration*/
typedef struct FLEXCANUserConfig {
    uint32_t max_num_mb;                            /*!< The maximum number of Message Buffers*/
    flexcan_rx_fifo_id_filter_num_t num_id_filters; /*!< The number of Rx FIFO ID filters needed*/
    bool is_rx_fifo_needed;                         /*!< 1 if needed; 0 if not*/
} flexcan_user_config_t;

/*! @brief FlexCAN timing related structures*/
typedef struct FLEXCANTimeSegment {
    uint32_t propseg;     /*!< Propagation segment*/
    uint32_t pseg1;       /*!< Phase segment 1*/
    uint32_t pseg2;       /*!< Phase segment 2*/
    uint32_t pre_divider; /*!< Clock pre divider*/
    uint32_t rjw;         /*!< Resync jump width*/
} flexcan_time_segment_t;


/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Configuration
 * @{
 */

/*!
 * @brief Enables FlexCAN controller.
 *
 * @param   canBaseAddr    The FlexCAN base address
 * @return  0 if successful; non-zero failed
 */
flexcan_status_t FLEXCAN_HAL_Enable(uint32_t canBaseAddr);

/*!
 * @brief Disables FlexCAN controller.
 *
 * @param   canBaseAddr    The FlexCAN base address
 * @return  0 if successful; non-zero failed
 */
flexcan_status_t FLEXCAN_HAL_Disable(uint32_t canBaseAddr);

/*!
 * @brief Checks whether the FlexCAN is enabled or disabled.
 *
 * @param   canBaseAddr    The FlexCAN base address
 * @return  State of FlexCAN enable(0)/disable(1)
 */
static inline bool FLEXCAN_HAL_IsEnabled(uint32_t canBaseAddr)
{
    return BR_CAN_MCR_MDIS(canBaseAddr);
}

/*!
 * @brief Selects the clock source for FlexCAN.
 *
 * @param   canBaseAddr The FlexCAN base address
 * @param   clk         The FlexCAN clock source
 * @return  0 if successful; non-zero failed
 */
flexcan_status_t FLEXCAN_HAL_SelectClock(uint32_t canBaseAddr, flexcan_clk_source_t clk);

/*!
 * @brief Initializes the FlexCAN controller.
 *
 * @param   canBaseAddr  The FlexCAN base address
 * @param   data         The FlexCAN platform data.
 * @return  0 if successful; non-zero failed
 */
flexcan_status_t FLEXCAN_HAL_Init(uint32_t canBaseAddr, const flexcan_user_config_t *data);

/*!
 * @brief Sets the FlexCAN time segments for setting up bit rate.
 *
 * @param   canBaseAddr The FlexCAN base address
 * @param   time_seg    FlexCAN time segments, which need to be set for the bit rate.
 * @return  0 if successful; non-zero failed
 */
void FLEXCAN_HAL_SetTimeSegments(uint32_t canBaseAddr, flexcan_time_segment_t *time_seg);

/*!
 * @brief Gets the  FlexCAN time segments to calculate the bit rate.
 *
 * @param   canBaseAddr The FlexCAN base address
 * @param   time_seg    FlexCAN time segments read for bit rate
 * @return  0 if successful; non-zero failed
 */
void FLEXCAN_HAL_GetTimeSegments(uint32_t canBaseAddr, flexcan_time_segment_t *time_seg);

/*!
 * @brief Un freezes the FlexCAN module.
 *
 * @param   canBaseAddr     The FlexCAN base address
 * @return  0 if successful; non-zero failed.
 */
void FLEXCAN_HAL_ExitFreezeMode(uint32_t canBaseAddr);

/*!
 * @brief Freezes the FlexCAN module.
 *
 * @param   canBaseAddr     The FlexCAN base address
 */
void FLEXCAN_HAL_EnterFreezeMode(uint32_t canBaseAddr);

/*!
 * @brief Enables operation mode.
 *
 * @param   canBaseAddr  The FlexCAN base address
 * @param   mode         An operation mode to be enabled
 * @return  0 if successful; non-zero failed.
 */
flexcan_status_t FLEXCAN_HAL_EnableOperationMode(
    uint32_t canBaseAddr,
    flexcan_operation_modes_t mode);

/*!
 * @brief Disables operation mode.
 *
 * @param   canBaseAddr  The FlexCAN base address
 * @param   mode         An operation mode to be disabled
 * @return  0 if successful; non-zero failed.
 */
flexcan_status_t FLEXCAN_HAL_DisableOperationMode(
    uint32_t canBaseAddr,
    flexcan_operation_modes_t mode);

/*@}*/

/*!
 * @name Data transfer
 * @{
 */

/*!
 * @brief Sets the FlexCAN message buffer fields for transmitting.
 *
 * @param   canBaseAddr  The FlexCAN base address
 * @param   data         The FlexCAN platform data
 * @param   mb_idx       Index of the message buffer
 * @param   cs           CODE/status values (TX)
 * @param   msg_id       ID of the message to transmit
 * @param   mb_data      Bytes of the FlexCAN message
 * @return  0 if successful; non-zero failed
 */
flexcan_status_t FLEXCAN_HAL_SetMbTx(
    uint32_t canBaseAddr,
    const flexcan_user_config_t *data,
    uint32_t mb_idx,
    flexcan_mb_code_status_t *cs,
    uint32_t msg_id,
    uint8_t *mb_data);

/*!
 * @brief Sets the FlexCAN message buffer fields for receiving.
 *
 * @param   canBaseAddr  The FlexCAN base address
 * @param   data         The FlexCAN platform data
 * @param   mb_idx       Index of the message buffer
 * @param   cs           CODE/status values (RX)
 * @param   msg_id       ID of the message to receive
 * @return  0 if successful; non-zero failed
 */
flexcan_status_t FLEXCAN_HAL_SetMbRx(
    uint32_t canBaseAddr,
    const flexcan_user_config_t *data,
    uint32_t mb_idx,
    flexcan_mb_code_status_t *cs,
    uint32_t msg_id);

/*!
 * @brief Gets the FlexCAN message buffer fields.
 *
 * @param   canBaseAddr  The FlexCAN base address
 * @param   data         The FlexCAN platform data
 * @param   mb_idx       Index of the message buffer
 * @param   mb           The fields of the message buffer
 * @return  0 if successful; non-zero failed
 */
flexcan_status_t FLEXCAN_HAL_GetMb(
    uint32_t canBaseAddr,
    const flexcan_user_config_t *data,
    uint32_t mb_idx,
    flexcan_mb_t *mb);

/*!
 * @brief Locks the FlexCAN Rx message buffer.
 *
 * @param   canBaseAddr  The FlexCAN base address
 * @param   data         The FlexCAN platform data
 * @param   mb_idx       Index of the message buffer
 * @return  0 if successful; non-zero failed
 */
flexcan_status_t FLEXCAN_HAL_LockRxMb(
    uint32_t canBaseAddr,
    const flexcan_user_config_t *data,
    uint32_t mb_idx);

/*!
 * @brief Unlocks the FlexCAN Rx message buffer.
 *
 * @param   canBaseAddr     The FlexCAN base address
 * @return  0 if successful; non-zero failed
 */
static inline void FLEXCAN_HAL_UnlockRxMb(uint32_t canBaseAddr)
{
    /* Unlock the mailbox */
    HW_CAN_TIMER_RD(canBaseAddr);
}

/*!
 * @brief Enables the Rx FIFO.
 *
 * @param   canBaseAddr     The FlexCAN base address
 */
void FLEXCAN_HAL_EnableRxFifo(uint32_t canBaseAddr);

/*!
 * @brief Disables the Rx FIFO.
 *
 * @param   canBaseAddr     The FlexCAN base address
 */
void FLEXCAN_HAL_DisableRxFifo(uint32_t canBaseAddr);

/*!
 * @brief Sets the number of the Rx FIFO filters.
 *
 * @param   canBaseAddr  The FlexCAN base address
 * @param   number       The number of Rx FIFO filters
 */
void FLEXCAN_HAL_SetRxFifoFiltersNumber(uint32_t canBaseAddr, uint32_t number);

/*!
 * @brief Sets  the maximum number of Message Buffers.
 *
 * @param   canBaseAddr  The FlexCAN base address
 * @param   data         The FlexCAN platform data
 */
void FLEXCAN_HAL_SetMaxMbNumber(
    uint32_t canBaseAddr,
    const flexcan_user_config_t *data);

/*!
 * @brief Sets the Rx FIFO ID filter table elements.
 *
 * @param   canBaseAddr      The FlexCAN base address
 * @param   data             The FlexCAN platform data
 * @param   id_format        The format of the Rx FIFO ID Filter Table Elements
 * @param   id_filter_table  The ID filter table elements which contain if RTR bit,
 *                           IDE bit and RX message ID need to be set.
 * @return  0 if successful; non-zero failed.
 */
flexcan_status_t FLEXCAN_HAL_SetIdFilterTableElements(
    uint32_t canBaseAddr,
    const flexcan_user_config_t *data,
    flexcan_rx_fifo_id_element_format_t id_format,
    flexcan_id_table_t *id_filter_table);

/*!
 * @brief Sets the FlexCAN Rx FIFO fields.
 *
 * @param   canBaseAddr             The FlexCAN base address
 * @param   data                    The FlexCAN platform data
 * @param   id_format               The format of the Rx FIFO ID Filter Table Elements
 * @param   id_filter_table         The ID filter table elements which contain RTR bit, IDE bit,
 *                                  and RX message ID.
 * @return  0 if successful; non-zero failed.
 */
flexcan_status_t FLEXCAN_HAL_SetRxFifo(
    uint32_t canBaseAddr,
    const flexcan_user_config_t *data,
    flexcan_rx_fifo_id_element_format_t id_format,
    flexcan_id_table_t *id_filter_table);

/*!
 * @brief Gets the FlexCAN Rx FIFO data.
 *
 * @param   canBaseAddr  The FlexCAN base address
 * @param   rx_fifo      The FlexCAN receive FIFO data
 * @return  0 if successful; non-zero failed.
 */
flexcan_status_t FLEXCAN_HAL_ReadFifo(
    uint32_t canBaseAddr,
    flexcan_mb_t *rx_fifo);

/*@}*/

/*!
 * @name Interrupts
 * @{
 */

/*!
 * @brief Enables the FlexCAN Message Buffer interrupt.
 *
 * @param   canBaseAddr  The FlexCAN base address
 * @param   data         The FlexCAN platform data
 * @param   mb_idx       Index of the message buffer
 * @return  0 if successful; non-zero failed
 */
flexcan_status_t FLEXCAN_HAL_EnableMbInt(
    uint32_t canBaseAddr,
    const flexcan_user_config_t *data,
    uint32_t mb_idx);

/*!
 * @brief Disables the FlexCAN Message Buffer interrupt.
 *
 * @param   canBaseAddr  The FlexCAN base address
 * @param   data         The FlexCAN platform data
 * @param   mb_idx       Index of the message buffer
 * @return  0 if successful; non-zero failed
 */
flexcan_status_t FLEXCAN_HAL_DisableMbInt(
    uint32_t canBaseAddr,
    const flexcan_user_config_t *data,
    uint32_t mb_idx);

/*!
 * @brief Enables error interrupt of the FlexCAN module.
 * @param   canBaseAddr     The FlexCAN base address
 */
void FLEXCAN_HAL_EnableErrInt(uint32_t canBaseAddr);

/*!
 * @brief Disables error interrupt of the FlexCAN module.
 *
 * @param   canBaseAddr     The FlexCAN base address
 */
void FLEXCAN_HAL_DisableErrInt(uint32_t canBaseAddr);

/*!
 * @brief Enables Bus off interrupt of the FlexCAN module.
 *
 * @param   canBaseAddr     The FlexCAN base address
 */
void FLEXCAN_HAL_EnableBusOffInt(uint32_t canBaseAddr);

/*!
 * @brief Disables Bus off interrupt of the FlexCAN module.
 *
 * @param   canBaseAddr     The FlexCAN base address
 */
void FLEXCAN_HAL_DisableBusOffInt(uint32_t canBaseAddr);

/*!
 * @brief Enables Wakeup interrupt of the FlexCAN module.
 *
 * @param   canBaseAddr     The FlexCAN base address
 */
void FLEXCAN_HAL_EnableWakeupInt(uint32_t canBaseAddr);

/*!
 * @brief Disables Wakeup interrupt of the FlexCAN module.
 *
 * @param   canBaseAddr     The FlexCAN base address
 */
void FLEXCAN_HAL_DisableWakeupInt(uint32_t canBaseAddr);

/*!
 * @brief Enables TX warning interrupt of the FlexCAN module
 *
 * @param   canBaseAddr     The FlexCAN base address
 */
void FLEXCAN_HAL_EnableTxWarningInt(uint32_t canBaseAddr);

/*!
 * @brief Disables TX warning interrupt of the FlexCAN module.
 *
 * @param   canBaseAddr     The FlexCAN base address
 */
void FLEXCAN_HAL_DisableTxWarningInt(uint32_t canBaseAddr);

/*!
 * @brief Enables RX warning interrupt of the FlexCAN module.
 *
 * @param   canBaseAddr     The FlexCAN base address
 */
void FLEXCAN_HAL_EnableRxWarningInt(uint32_t canBaseAddr);

/*!
 * @brief Disables RX warning interrupt of the FlexCAN module.
 *
 * @param   canBaseAddr     The FlexCAN base address
 */
void FLEXCAN_HAL_DisableRxWarningInt(uint32_t canBaseAddr);

/*@}*/

/*!
 * @name Status
 * @{
 */

/*!
 * @brief Gets the value of FlexCAN freeze ACK.
 *
 * @param   canBaseAddr     The FlexCAN base address
 * @return  freeze ACK state (1-freeze mode, 0-not in freeze mode).
 */
static inline uint32_t FLEXCAN_HAL_GetFreezeAck(uint32_t canBaseAddr)
{
    return HW_CAN_MCR(canBaseAddr).B.FRZACK;
}

/*!
 * @brief Gets the individual FlexCAN MB interrupt flag.
 *
 * @param   canBaseAddr  The FlexCAN base address
 * @param   data         The FlexCAN platform data
 * @param   mb_idx       Index of the message buffer
 * @return  the individual MB interrupt flag (0 and 1 are the flag value)
 */
uint8_t FLEXCAN_HAL_GetMbIntFlag(
    uint32_t canBaseAddr,
    const flexcan_user_config_t *data,
    uint32_t mb_idx);

/*!
 * @brief Gets all FlexCAN MB interrupt flags.
 *
 * @param   canBaseAddr     The FlexCAN base address
 * @return  all MB interrupt flags
 */
static inline uint32_t FLEXCAN_HAL_GetAllMbIntFlags(uint32_t canBaseAddr)
{
    return HW_CAN_IFLAG1_RD(canBaseAddr);
}

/*!
 * @brief Clears the interrupt flag of the message buffers.
 *
 * @param   canBaseAddr  The FlexCAN base address
 * @param   reg_val      The value to be written to the interrupt flag1 register.
 */
/* See fsl_flexcan_hal.h for documentation of this function.*/
static inline void FLEXCAN_HAL_ClearMbIntFlag(
    uint32_t canBaseAddr,
    uint32_t reg_val)
{
    /* Clear the corresponding message buffer interrupt flag*/
    HW_CAN_IFLAG1_SET(canBaseAddr, reg_val);
}

/*!
 * @brief Gets the transmit error counter and receives the error counter.
 *
 * @param   canBaseAddr  The FlexCAN base address
 * @param   err_cnt      Transmit error counter and receive error counter
 */
void FLEXCAN_HAL_GetErrCounter(
    uint32_t canBaseAddr,
    flexcan_berr_counter_t *err_cnt);

/*!
 * @brief Gets error and status.
 *
 * @param   canBaseAddr     The FlexCAN base address
 * @return  The current error and status
 */
static inline uint32_t FLEXCAN_HAL_GetErrStatus(uint32_t canBaseAddr)
{
    return HW_CAN_ESR1_RD(canBaseAddr);
}

/*!
 * @brief Clears all other interrupts in ERRSTAT register (Error, Busoff, Wakeup).
 *
 * @param   canBaseAddr     The FlexCAN base address
 */
void FLEXCAN_HAL_ClearErrIntStatus(uint32_t canBaseAddr);

/*@}*/

/*!
 * @name Mask
 * @{
 */

/*!
 * @brief Sets the Rx masking type.
 *
 * @param   canBaseAddr  The FlexCAN base address
 * @param   type         The FlexCAN Rx mask type
 */
void FLEXCAN_HAL_SetMaskType(uint32_t canBaseAddr, flexcan_rx_mask_type_t type);

/*!
 * @brief Sets the FlexCAN RX FIFO global standard mask.
 *
 * @param   canBaseAddr  The FlexCAN base address
 * @param   std_mask     Standard mask
 */
void FLEXCAN_HAL_SetRxFifoGlobalStdMask(
    uint32_t canBaseAddr,
    uint32_t std_mask);

/*!
 * @brief Sets the FlexCAN Rx FIFO global extended mask.
 *
 * @param   canBaseAddr  The FlexCAN base address
 * @param   ext_mask     Extended mask
 */
void FLEXCAN_HAL_SetRxFifoGlobalExtMask(
    uint32_t canBaseAddr,
    uint32_t ext_mask);

/*!
 * @brief Sets the FlexCAN Rx individual standard mask for ID filtering in the Rx MBs and the Rx FIFO.
 *
 * @param   canBaseAddr  The FlexCAN base address
 * @param   data         The FlexCAN platform data
 * @param   mb_idx       Index of the message buffer
 * @param   std_mask     Individual standard mask
 * @return  0 if successful; non-zero failed
*/
flexcan_status_t FLEXCAN_HAL_SetRxIndividualStdMask(
    uint32_t canBaseAddr,
    const flexcan_user_config_t * data,
    uint32_t mb_idx,
    uint32_t std_mask);

/*!
 * @brief Sets the FlexCAN Rx individual extended mask for ID filtering in the Rx MBs and the Rx FIFO.
 *
 * @param   canBaseAddr  The FlexCAN base address
 * @param   data         The FlexCAN platform data
 * @param   mb_idx       Index of the message buffer
 * @param   ext_mask     Individual extended mask
 * @return  0 if successful; non-zero failed
*/
flexcan_status_t FLEXCAN_HAL_SetRxIndividualExtMask(
    uint32_t canBaseAddr,
    const flexcan_user_config_t * data,
    uint32_t mb_idx,
    uint32_t ext_mask);

/*!
 * @brief Sets the FlexCAN Rx MB global standard mask.
 *
 * @param   canBaseAddr  The FlexCAN base address
 * @param   std_mask     Standard mask
 */
void FLEXCAN_HAL_SetRxMbGlobalStdMask(
    uint32_t canBaseAddr,
    uint32_t std_mask);

/*!
 * @brief Sets the FlexCAN RX MB BUF14 standard mask.
 *
 * @param   canBaseAddr  The FlexCAN base address
 * @param   std_mask     Standard mask
 */
void FLEXCAN_HAL_SetRxMbBuf14StdMask(
    uint32_t canBaseAddr,
    uint32_t std_mask);

/*!
 * @brief Sets the FlexCAN Rx MB BUF15 standard mask.
 *
 * @param   canBaseAddr  The FlexCAN base address
 * @param   std_mask     Standard mask
 * @return  0 if successful; non-zero failed
 */
void FLEXCAN_HAL_SetRxMbBuf15StdMask(
    uint32_t canBaseAddr,
    uint32_t std_mask);

/*!
 * @brief Sets the FlexCAN RX MB global extended mask.
 *
 * @param   canBaseAddr  The FlexCAN base address
 * @param   ext_mask     Extended mask
 */
void FLEXCAN_HAL_SetRxMbGlobalExtMask(
    uint32_t canBaseAddr,
    uint32_t ext_mask);

/*!
 * @brief Sets the FlexCAN RX MB BUF14 extended mask.
 *
 * @param   canBaseAddr  The FlexCAN base address
 * @param   ext_mask     Extended mask
 */
void FLEXCAN_HAL_SetRxMbBuf14ExtMask(
    uint32_t canBaseAddr,
    uint32_t ext_mask);

/*!
 * @brief Sets the FlexCAN RX MB BUF15 extended mask.
 *
 * @param   canBaseAddr  The FlexCAN base address
 * @param   ext_mask     Extended mask
 */
void FLEXCAN_HAL_SetRxMbBuf15ExtMask(
    uint32_t canBaseAddr,
    uint32_t ext_mask);

/*!
 * @brief Gets the FlexCAN ID acceptance filter hit indicator on Rx FIFO.
 *
 * @param   canBaseAddr  The FlexCAN base address
 * @return  RX FIFO information
 */
static inline uint32_t  FLEXCAN_HAL_GetIdAcceptanceFilterRxFifo(uint32_t canBaseAddr)
{
    return BR_CAN_RXFIR_IDHIT(canBaseAddr);
}

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* MBED_NO_FLEXCAN */

#endif /* __FSL_FLEXCAN_HAL_H__*/

/*******************************************************************************
 * EOF
 ******************************************************************************/

