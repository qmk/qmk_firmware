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

#ifndef __FSL_ENET_HAL_H__
#define __FSL_ENET_HAL_H__

#include <stdint.h>
#include <stdbool.h>
#include "fsl_device_registers.h"
#include "fsl_enet_features.h"
#include <assert.h>

#ifndef MBED_NO_ENET

/*!
 * @addtogroup enet_hal
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Defines the system endian type.*/
#define SYSTEM_LITTLE_ENDIAN      (1)

/*! @brief Define macro to do the endianness swap*/
#define BSWAP_16(x)	(uint16_t)((uint16_t)(((uint16_t)(x) & (uint16_t)0xFF00) >> 0x8) | (uint16_t)(((uint16_t)(x) & (uint16_t)0xFF) << 0x8))
#define BSWAP_32(x) (uint32_t)((((uint32_t)(x) & 0x00FFU) << 24) | (((uint32_t)(x) & 0x00FF00U) << 8) | (((uint32_t)(x) & 0xFF0000U) >> 8) | (((uint32_t)(x) & 0xFF000000U) >> 24))
#if SYSTEM_LITTLE_ENDIAN && FSL_FEATURE_ENET_DMA_BIG_ENDIAN_ONLY 
#define HTONS(n)                      BSWAP_16(n)
#define HTONL(n)                      BSWAP_32(n)
#define NTOHS(n)                      BSWAP_16(n)
#define NTOHL(n)                      BSWAP_32(n)
#else
#define HTONS(n)                       (n)
#define HTONL(n)                       (n)
#define NTOHS(n)                       (n)
#define NTOHL(n)                       (n)
#endif

/*! @brief Defines the Status return codes.*/
typedef enum _enet_status
{
    kStatus_ENET_Success = 0,
    kStatus_ENET_InvalidInput,       /*!< Invalid ENET input parameter */
    kStatus_ENET_MemoryAllocateFail, /*!< Memory allocate failure*/
    kStatus_ENET_GetClockFreqFail,   /*!< Get clock frequency failure*/
    kStatus_ENET_Initialized,        /*!< ENET device already initialized*/
    kStatus_ENET_Layer2QueueNull,    /*!< NULL L2 PTP buffer queue pointer*/
    kStatus_ENET_Layer2OverLarge,    /*!< Layer2 packet length over large*/
    kStatus_ENET_Layer2BufferFull,   /*!< Layer2 packet buffer full*/
    kStatus_ENET_PtpringBufferFull,  /*!< PTP ring buffer full*/
    kStatus_ENET_PtpringBufferEmpty, /*!< PTP ring buffer empty*/
    kStatus_ENET_Miiuninitialized,   /*!< MII uninitialized*/
    kStatus_ENET_RxbdInvalid,        /*!< Receive buffer descriptor invalid*/
    kStatus_ENET_RxbdEmpty,          /*!< Receive buffer descriptor empty*/
    kStatus_ENET_RxbdTrunc,          /*!< Receive buffer descriptor truncate*/
    kStatus_ENET_RxbdError,          /*!< Receive buffer descriptor error*/
    kStatus_ENET_RxBdFull,           /*!< Receive buffer descriptor full*/
    kStatus_ENET_SmallBdSize,        /*!< Small receive buffer size*/
    kStatus_ENET_LargeBufferFull,    /*!< Receive large buffer full*/
    kStatus_ENET_TxbdFull,           /*!< Transmit buffer descriptor full*/
    kStatus_ENET_TxbdNull,           /*!< Transmit buffer descriptor Null*/
    kStatus_ENET_TxBufferNull,       /*!< Transmit data buffer Null*/
    kStatus_ENET_NoRxBufferLeft,       /*!< No more receive buffer left*/
    kStatus_ENET_UnknownCommand,     /*!< Invalid ENET PTP IOCTL command*/
    kStatus_ENET_TimeOut,            /*!< ENET Timeout*/
    kStatus_ENET_MulticastPointerNull, /*!< Null multicast group pointer*/
    kStatus_ENET_AlreadyAddedMulticast /*!< Have Already added to multicast group*/
} enet_status_t;


#if FSL_FEATURE_ENET_DMA_BIG_ENDIAN_ONLY && SYSTEM_LITTLE_ENDIAN
/*! @brief Defines the control and status regions of the receive buffer descriptor.*/
typedef enum _enet_rx_bd_control_status
{
    kEnetRxBdBroadCast = 0x8000,       /*!< Broadcast */
    kEnetRxBdMultiCast = 0x4000,       /*!< Multicast*/
    kEnetRxBdLengthViolation = 0x2000, /*!< Receive length violation*/
    kEnetRxBdNoOctet = 0x1000,         /*!< Receive non-octet aligned frame*/
    kEnetRxBdCrc = 0x0400,             /*!< Receive CRC error*/
    kEnetRxBdOverRun = 0x0200,         /*!< Receive FIFO overrun*/
    kEnetRxBdTrunc = 0x0100,           /*!< Frame is truncated */
    kEnetRxBdEmpty = 0x0080,           /*!< Empty bit*/
    kEnetRxBdRxSoftOwner1 = 0x0040,    /*!< Receive software owner*/
    kEnetRxBdWrap = 0x0020,            /*!< Update buffer descriptor*/
    kEnetRxBdRxSoftOwner2 = 0x0010,    /*!< Receive software owner*/
    kEnetRxBdLast = 0x0008,            /*!< Last BD in the frame*/
    kEnetRxBdMiss = 0x0001             /*!< Receive for promiscuous mode*/
} enet_rx_bd_control_status_t;

/*! @brief Defines the control extended regions of the receive buffer descriptor.*/
typedef enum _enet_rx_bd_control_extend
{  
    kEnetRxBdUnicast = 0x0001,              /*!< Unicast frame*/
    kEnetRxBdCollision = 0x0002,            /*!< BD collision*/
    kEnetRxBdPhyErr = 0x0004,               /*!< PHY error*/
    kEnetRxBdMacErr = 0x0080,               /*!< Mac error*/
    kEnetRxBdIpv4 = 0x0100,                 /*!< Ipv4 frame*/
    kEnetRxBdIpv6 = 0x0200,                 /*!< Ipv6 frame*/
    kEnetRxBdVlan = 0x0400,                 /*!< VLAN*/
    kEnetRxBdProtocolChecksumErr = 0x1000,  /*!< Protocol checksum error*/
    kEnetRxBdIpHeaderChecksumErr = 0x2000,  /*!< IP header checksum error*/
    kEnetRxBdIntrrupt = 0x8000              /*!< BD interrupt*/
} enet_rx_bd_control_extend_t;

/*! @brief Defines the control status region of the transmit buffer descriptor.*/
typedef enum _enet_tx_bd_control_status
{
    kEnetTxBdReady = 0x0080,         /*!<  Ready bit*/
    kEnetTxBdTxSoftOwner1 = 0x0040,  /*!<  Transmit software owner*/
    kEnetTxBdWrap = 0x0020,          /*!<  Wrap buffer descriptor*/
    kEnetTxBdTxSoftOwner2 = 0x0010,  /*!<  Transmit software owner*/
    kEnetTxBdLast = 0x0008,          /*!<  Last BD in the frame*/
    kEnetTxBdTransmitCrc = 0x0004    /*!<  Receive for transmit CRC*/
} enet_tx_bd_control_status_t;

/*! @brief Defines the control extended region of the transmit buffer descriptor.*/
typedef enum _enet_tx_bd_control_extend
{
    kEnetTxBdTxErr = 0x0080,                 /*!<  Transmit error*/
    kEnetTxBdTxUnderFlowErr = 0x0020,        /*!<  Underflow error*/
    kEnetTxBdExcessCollisionErr = 0x0010,    /*!<  Excess collision error*/
    kEnetTxBdTxFrameErr = 0x0008,            /*!<  Frame error*/
    kEnetTxBdLatecollisionErr = 0x0004,      /*!<  Late collision error*/
    kEnetTxBdOverFlowErr = 0x0002,           /*!<  Overflow error*/
    kEnetTxTimestampErr = 0x0001             /*!<  Timestamp error*/
} enet_tx_bd_control_extend_t;

/*! @brief Defines the control extended2 region of the transmit buffer descriptor.*/
typedef enum _enet_tx_bd_control_extend2
{
    kEnetTxBdTxInterrupt = 0x0040, /*!< Transmit interrupt*/
    kEnetTxBdTimeStamp = 0x0020    /*!< Transmit timestamp flag */
} enet_tx_bd_control_extend2_t;
#else
/*! @brief Defines the control and status region of the receive buffer descriptor.*/
typedef enum _enet_rx_bd_control_status
{
    kEnetRxBdEmpty = 0x8000,           /*!< Empty bit*/
    kEnetRxBdRxSoftOwner1 = 0x4000,    /*!< Receive software owner*/
    kEnetRxBdWrap = 0x2000,            /*!< Update buffer descriptor*/
    kEnetRxBdRxSoftOwner2 = 0x1000,    /*!< Receive software owner*/
    kEnetRxBdLast = 0x0800,            /*!< Last BD in the frame*/
    kEnetRxBdMiss = 0x0100,            /*!< Receive for promiscuous mode*/
    kEnetRxBdBroadCast = 0x0080,       /*!< Broadcast */
    kEnetRxBdMultiCast = 0x0040,       /*!< Multicast*/
    kEnetRxBdLengthViolation = 0x0020, /*!< Receive length violation*/
    kEnetRxBdNoOctet = 0x0010,         /*!< Receive non-octet aligned frame*/
    kEnetRxBdCrc = 0x0004,             /*!< Receive CRC error*/
    kEnetRxBdOverRun = 0x0002,         /*!< Receive FIFO overrun*/
    kEnetRxBdTrunc = 0x0001            /*!< Frame is truncated    */
} enet_rx_bd_control_status_t;

/*! @brief Defines the control extended region of the receive buffer descriptor.*/
typedef enum _enet_rx_bd_control_extend
{  
    kEnetRxBdIpv4 = 0x0001,                 /*!< Ipv4 frame*/
    kEnetRxBdIpv6 = 0x0002,                 /*!< Ipv6 frame*/
    kEnetRxBdVlan = 0x0004,                 /*!< VLAN*/
    kEnetRxBdProtocolChecksumErr = 0x0010,  /*!< Protocol checksum error*/
    kEnetRxBdIpHeaderChecksumErr = 0x0020,  /*!< IP header checksum error*/
    kEnetRxBdIntrrupt = 0x0080,             /*!< BD interrupt*/
    kEnetRxBdUnicast = 0x0100,              /*!< Unicast frame*/
    kEnetRxBdCollision = 0x0200,            /*!< BD collision*/
    kEnetRxBdPhyErr = 0x0400,               /*!< PHY error*/
    kEnetRxBdMacErr = 0x8000                /*!< Mac error */
} enet_rx_bd_control_extend_t;

/*! @brief Defines the control status of the transmit buffer descriptor.*/
typedef enum _enet_tx_bd_control_status
{
    kEnetTxBdReady = 0x8000,         /*!<  Ready bit*/
    kEnetTxBdTxSoftOwner1 = 0x4000,  /*!<  Transmit software owner*/
    kEnetTxBdWrap = 0x2000,          /*!<  Wrap buffer descriptor*/
    kEnetTxBdTxSoftOwner2 = 0x1000,  /*!<  Transmit software owner*/
    kEnetTxBdLast = 0x0800,          /*!<  Last BD in the frame*/
    kEnetTxBdTransmitCrc = 0x0400    /*!<  Receive for transmit CRC   */
} enet_tx_bd_control_status_t;

/*! @brief Defines the control extended of the transmit buffer descriptor.*/
typedef enum _enet_tx_bd_control_extend
{
    kEnetTxBdTxErr = 0x8000,                /*!<  Transmit error*/
    kEnetTxBdTxUnderFlowErr = 0x2000,       /*!<  Underflow error*/
    kEnetTxBdExcessCollisionErr = 0x1000,   /*!<  Excess collision error*/
    kEnetTxBdTxFrameErr = 0x0800,           /*!<  Frame error*/
    kEnetTxBdLatecollisionErr = 0x0400,     /*!<  Late collision error*/
    kEnetTxBdOverFlowErr = 0x0200,          /*!<  Overflow error*/
    kEnetTxTimestampErr = 0x0100            /*!<  Timestamp error*/
} enet_tx_bd_control_extend_t;

/*! @brief Defines the control extended2 of the transmit buffer descriptor.*/
typedef enum _enet_tx_bd_control_extend2
{
    kEnetTxBdTxInterrupt = 0x4000, /*!< Transmit interrupt*/
    kEnetTxBdTimeStamp = 0x2000    /*!< Transmit timestamp flag */
} enet_tx_bd_control_extend2_t;
#endif

/*! @brief Defines the macro to the different ENET constant value.*/
typedef enum _enet_constant_parameter
{
    kEnetMacAddrLen = 6,       /*!< ENET mac address length*/
    kEnetHashValMask = 0x1f,   /*!< ENET hash value mask*/
    kEnetRxBdCtlJudge1 = 0x0080,/*!< ENET receive buffer descriptor control judge value1*/
    kEnetRxBdCtlJudge2 = 0x8000 /*!< ENET receive buffer descriptor control judge value2*/
} enet_constant_parameter_t;

/*! @brief Defines the RMII or MII mode for data interface between the MAC and the PHY.*/
typedef enum _enet_config_rmii
{
    kEnetCfgMii = 0,   /*!< MII mode for data interface*/
    kEnetCfgRmii = 1   /*!< RMII mode for data interface*/
} enet_config_rmii_t;

/*! @brief Defines the 10 Mbps or 100 Mbps speed mode for the data transfer.*/
typedef enum _enet_config_speed
{
    kEnetCfgSpeed100M = 0,  /*!< Speed 100 M mode*/
    kEnetCfgSpeed10M = 1    /*!< Speed 10 M mode*/
} enet_config_speed_t;

/*! @brief Defines the half or full duplex mode for the data transfer.*/
typedef enum _enet_config_duplex
{
    kEnetCfgHalfDuplex = 0, /*!< Half duplex mode*/
    kEnetCfgFullDuplex = 1  /*!< Full duplex mode*/
} enet_config_duplex_t;

/*! @brief Defines the write/read operation for the MII.*/
typedef enum _enet_mii_operation
{
    kEnetWriteNoCompliant = 0, /*!< Write frame operation, but not MII compliant.*/
    kEnetWriteValidFrame = 1,  /*!< Write frame operation for a valid MII management frame*/
    kEnetReadValidFrame = 2,   /*!< Read frame operation for a valid MII management frame.*/
    kEnetReadNoCompliant = 3   /*!< Read frame operation, but not MII compliant*/
}enet_mii_operation_t;

/*! @brief Define holdon time on MDIO output*/
typedef enum _enet_mdio_holdon_clkcycle
{
    kEnetMdioHoldOneClkCycle = 0, /*!< MDIO output hold on one clock cycle*/
    kEnetMdioHoldTwoClkCycle = 1, /*!< MDIO output hold on two clock cycles*/
    kEnetMdioHoldThreeClkCycle = 2, /*!< MDIO output hold on three clock cycles*/
    kEnetMdioHoldFourClkCycle = 3, /*!< MDIO output hold on four clock cycles*/
    kEnetMdioHoldFiveClkCycle = 4, /*!< MDIO output hold on five clock cycles*/
    kEnetMdioHoldSixClkCycle = 5, /*!< MDIO output hold on six clock cycles*/
    kEnetMdioHoldSevenClkCycle = 6, /*!< MDIO output hold seven two clock cycles*/
    kEnetMdioHoldEightClkCycle = 7, /*!< MDIO output hold on eight clock cycles*/
}enet_mdio_holdon_clkcycle_t;

/*! @brief Defines the initialization, enables or disables the operation for a special address filter */
typedef enum _enet_special_address_filter
{
    kEnetSpecialAddressInit= 0,     /*!< Initializes the special address filter.*/
    kEnetSpecialAddressEnable = 1,  /*!< Enables the special address filter.*/
    kEnetSpecialAddressDisable = 2  /*!< Disables the special address filter.*/
} enet_special_address_filter_t;

/*! @brief Defines the capture or compare mode for 1588 timer channels.*/
typedef enum _enet_timer_channel_mode
{
    kEnetChannelDisable = 0,         /*!< Disable timer channel*/
    kEnetChannelRisingCapture = 1,   /*!< Input capture on rising edge*/
    kEnetChannelFallingCapture = 2,  /*!< Input capture on falling edge*/
    kEnetChannelBothCapture = 3,     /*!< Input capture on both edges*/
    kEnetChannelSoftCompare = 4,     /*!< Output compare software only*/
    kEnetChannelToggleCompare = 5,   /*!< Toggle output on compare*/
    kEnetChannelClearCompare = 6,    /*!< Clear output on compare*/
    kEnetChannelSetCompare = 7,      /*!< Set output on compare*/
    kEnetChannelClearCompareSetOverflow = 10, /*!< Clear output on compare, set output on overflow*/
    kEnetChannelSetCompareClearOverflow = 11, /*!< Set output on compare, clear output on overflow*/
    kEnetChannelPulseLowonCompare = 14, /*!< Pulse output low on compare for one 1588 clock cycle*/
    kEnetChannelPulseHighonCompare = 15 /*!< Pulse output high on compare for one 1588 clock cycle*/
} enet_timer_channel_mode_t;

/*! @brief Defines the RXFRAME/RXBYTE/TXFRAME/TXBYTE/MII/TSTIMER/TSAVAIL interrupt source for ENET.*/
typedef enum _enet_interrupt_request
{
    kEnetBabrInterrupt = 0x40000000,   /*!< BABR interrupt source*/
    kEnetBabtInterrupt = 0x20000000,   /*!< BABT interrupt source*/
    kEnetGraInterrupt = 0x10000000,    /*!< GRA interrupt source*/
    kEnetTxFrameInterrupt = 0x8000000, /*!< TXFRAME interrupt source */
    kEnetTxByteInterrupt = 0x4000000,  /*!< TXBYTE interrupt source*/
    kEnetRxFrameInterrupt = 0x2000000, /*!< RXFRAME interrupt source */
    kEnetRxByteInterrupt = 0x1000000,  /*!< RXBYTE interrupt source */
    kEnetMiiInterrupt = 0x0800000,     /*!< MII interrupt source*/
    kEnetEBERInterrupt = 0x0400000,    /*!< EBERR interrupt source*/
    kEnetLcInterrupt = 0x0200000,      /*!< LC interrupt source*/
    kEnetRlInterrupt = 0x0100000,      /*!< RL interrupt source*/
    kEnetUnInterrupt = 0x0080000,      /*!< UN interrupt source*/
    kEnetPlrInterrupt = 0x0040000,     /*!< PLR interrupt source*/
    kEnetWakeupInterrupt = 0x0020000,  /*!< WAKEUP interrupt source*/
    kEnetTsAvailInterrupt = 0x0010000, /*!< TS AVAIL interrupt source*/
    kEnetTsTimerInterrupt = 0x0008000, /*!< TS WRAP interrupt source*/
    kEnetAllInterrupt = 0x7FFFFFFF     /*!< All interrupt*/
} enet_interrupt_request_t;

/*! @brief Defines the six-byte Mac address type.*/
typedef uint8_t enetMacAddr[kEnetMacAddrLen];

#if (!FSL_FEATURE_ENET_DMA_BIG_ENDIAN_ONLY) && SYSTEM_LITTLE_ENDIAN
/*! @brief Defines the buffer descriptor structure for the little-Endian system and endianness configurable IP.*/
typedef struct ENETBdStruct
{
    uint16_t  length;           /*!< Buffer descriptor data length*/
    uint16_t  control;          /*!< Buffer descriptor control*/
    uint8_t   *buffer;          /*!< Data buffer pointer*/
    uint16_t  controlExtend0;   /*!< Extend buffer descriptor control0*/
    uint16_t  controlExtend1;   /*!< Extend buffer descriptor control1*/
    uint16_t  payloadCheckSum;  /*!< Internal payload checksum*/
    uint8_t   headerLength;     /*!< Header length*/
    uint8_t   protocalTyte;     /*!< Protocol type*/
    uint16_t  reserved0;
    uint16_t  controlExtend2;   /*!< Extend buffer descriptor control2*/
    uint32_t  timestamp;        /*!< Timestamp */
    uint16_t  reserved1;
    uint16_t  reserved2;
    uint16_t  reserved3;
    uint16_t  reserved4;
} enet_bd_struct_t;
#define TX_DESC_UPDATED_MASK  (0x8000)
#else
/*! @brief Defines the buffer descriptors structure for the Big-Endian system.*/
typedef struct ENETBdStruct
{
    uint16_t  control;          /*!< Buffer descriptor control   */
    uint16_t   length;          /*!< Buffer descriptor data length*/
    uint8_t   *buffer;          /*!< Data buffer pointer*/
    uint16_t  controlExtend1;   /*!< Extend buffer descriptor control1*/
    uint16_t  controlExtend0;   /*!< Extend buffer descriptor control0*/
    uint8_t   headerLength;     /*!< Header length*/
    uint8_t   protocalTyte;     /*!< Protocol type*/
    uint16_t  payloadCheckSum;  /*!< Internal payload checksum*/
    uint16_t  controlExtend2;   /*!< Extend buffer descriptor control2*/
    uint16_t  reserved0;  
    uint32_t  timestamp;        /*!< Timestamp pointer*/
    uint16_t  reserved1;
    uint16_t  reserved2;
    uint16_t  reserved3;
    uint16_t  reserved4;
} enet_bd_struct_t;
#define TX_DESC_UPDATED_MASK  (0x0080)
#endif

/*! @brief Defines the configuration structure for the 1588 PTP timer.*/
typedef struct ENETConfigPtpTimer
{
    bool isSlaveEnabled;        /*!< Master or slave PTP timer*/
    uint32_t clockIncease;      /*!< Timer increase value each clock period*/
    uint32_t period;            /*!< Timer period for generate interrupt event  */
} enet_config_ptp_timer_t;

/*! @brief Defines the transmit accelerator configuration.*/
typedef struct ENETConfigTxAccelerator
{
    bool  isIpCheckEnabled;         /*!< Insert IP header checksum */
    bool  isProtocolCheckEnabled;   /*!< Insert protocol checksum*/
    bool  isShift16Enabled;         /*!< Tx FIFO shift-16*/
} enet_config_tx_accelerator_t;

/*! @brief Defines the receive accelerator configuration.*/
typedef struct ENETConfigRxAccelerator
{
    bool isIpcheckEnabled;        /*!< Discard with wrong IP header checksum */
    bool isProtocolCheckEnabled;  /*!< Discard with wrong protocol checksum*/
    bool isMacCheckEnabled;       /*!< Discard with Mac layer errors*/
    bool isPadRemoveEnabled;      /*!< Padding removal for short IP frames*/
    bool isShift16Enabled;        /*!< Rx FIFO shift-16*/
} enet_config_rx_accelerator_t;

/*! @brief Defines the transmit FIFO configuration.*/
typedef struct ENETConfigTxFifo
{
    bool isStoreForwardEnabled;   /*!< Transmit FIFO store and forward */
    uint8_t txFifoWrite;          /*!< Transmit FIFO write */
    uint8_t txEmpty;              /*!< Transmit FIFO section empty threshold*/
    uint8_t txAlmostEmpty;        /*!< Transmit FIFO section almost empty threshold*/
    uint8_t txAlmostFull;         /*!< Transmit FIFO section almost full threshold*/
} enet_config_tx_fifo_t;

/*! @brief Defines the receive FIFO configuration.*/
typedef struct ENETConfigRxFifo
{
    uint8_t rxFull;           /*!< Receive FIFO section full threshold*/
    uint8_t rxAlmostFull;     /*!< Receive FIFO section almost full threshold*/
    uint8_t rxEmpty;          /*!< Receive FIFO section empty threshold*/
    uint8_t rxAlmostEmpty;    /*!< Receive FIFO section almost empty threshold*/
} enet_config_rx_fifo_t;

/*******************************************************************************
 * API                              
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Resets the ENET module.
 *
 * @param instance The ENET instance number
 */
static inline void enet_hal_reset_ethernet(uint32_t instance)
{
   // assert(instance < HW_ENET_INSTANCE_COUNT);
   
   HW_ENET_ECR_SET(instance, BM_ENET_ECR_RESET);
}

/*!
 * @brief Gets the ENET status to check whether the reset has completed.
 *
 * @param instance The ENET instance number
 * @return Current status of the reset operation
 *         - true if ENET reset completed.
 *         - false if ENET reset has not completed.
 */
static inline bool enet_hal_is_reset_completed(uint32_t instance)
{
   // assert(instance < HW_ENET_INSTANCE_COUNT);
   
   return (BR_ENET_ECR_RESET(instance) == 0);
}
   
/*!
 * @brief Enable or disable stop mode.
 *
 * Enable stop mode will control device behavior in doze mode.
 * In doze mode, if this filed is set then all clock of the enet assemably are
 * disabled, except the RMII/MII clock. 
 *
 * @param instance The ENET instance number.
 * @param isEnabled The switch to enable/disable stop mode.
 *               - true to enabale the stop mode.
 *               - false to disable the stop mode.
 */
static inline void enet_hal_enable_stop(uint32_t instance, bool isEnabled)
{
    // assert(instance < HW_ENET_INSTANCE_COUNT);
    BW_ENET_ECR_STOPEN(instance, isEnabled);
}
/*!
 * @brief Enable or disable sleep mode.
 *
 * Enable sleep mode will disable normal operating mode. When enable the sleep
 * mode, the magic packet detection is also enabled so that a remote agent can 
 * wakeup the node.
 *
 * @param instance The ENET instance number.
 * @param isEnabled The switch to enable/disable the sleep mode.
 *               - true to enabale the sleep mode.
 *               - false to disable the sleep mode.
 */
 static inline void enet_hal_enable_sleep(uint32_t instance, bool isEnabled)
{
    // assert(instance < HW_ENET_INSTANCE_COUNT);
    BW_ENET_ECR_SLEEP(instance, isEnabled);
    BW_ENET_ECR_MAGICEN(instance, isEnabled);
}

/*!
 * @brief Sets the Mac address.
 *
 * This interface sets the six-byte Mac address of the ENET interface.
 *
 * @param instance The ENET instance number
 * @param hwAddr The mac address pointer store for six bytes Mac address
 */
void enet_hal_set_mac_address(uint32_t instance, enetMacAddr hwAddr);

/*!
 * @brief Sets the hardware addressing filtering to a multicast group address.
 *
 * This interface is used to add the ENET device to a multicast group address.
 * After joining the group,  Mac  receives all frames with the group Mac address.
 *
 * @param instance The ENET instance number
 * @param crcValue The CRC value of the special address
 * @param mode The operation for init/enable/disable the specified hardware address
 */
void enet_hal_set_group_hashtable(uint32_t instance, uint32_t crcValue, enet_special_address_filter_t mode);

/*!
 * @brief Sets the hardware addressing filtering to an individual address.
 *
 * This interface is used to add an individual address to the hardware address
 * filter. Mac  receives all frames with the individual address as a destination address.
 *
 * @param instance The ENET instance number
 * @param crcValue The CRC value of the special address
 * @param mode The operation for init/enable/disable the specified hardware address
 */
void enet_hal_set_individual_hashtable(uint32_t instance, uint32_t crcValue, enet_special_address_filter_t mode);

/*!
 * @brief Enable/disable payload length check.
 * 
 * If the length/type is less than 0x600,When enable payload length check 
 * the core checks the fame's payload length. If the length/type is greater
 * than or equal to 0x600. The MAC interprets the field as a type and no
 * payload length check is performanced.
 *
 * @param instance The ENET instance number
 * @param isEnabled The switch to enable/disable payload length check
 *             - True to enabale payload length check.
 *             - False to disable payload legnth check.
 */
static inline void enet_hal_enable_payloadcheck(uint32_t instance, bool isEnabled)
{
    // assert(instance < HW_ENET_INSTANCE_COUNT);
    BW_ENET_RCR_NLC(instance, isEnabled);
}

/*!
 * @brief Enable/disable append CRC to transmitted frames.
 * 
 * If transmit CRC forward is enabled, the transmit buffer descriptor controls
 * whether the frame has a CRC from the application. If transmit CRC forward is disabled,
 * transmitter does not append any CRC to transmitted frames.
 * 
 * @param instance The ENET instance number
 * @param isEnabled The switch to enable/disable transmit the receive CRC
 *             - True the transmitter control CRC through transmit buffer descriptor.
 *             - False the transmitter does not append any CRC to transmitted frames.
 */
static inline void enet_hal_enable_txcrcforward(uint32_t instance, bool isEnabled)
{
    // assert(instance < HW_ENET_INSTANCE_COUNT);
    BW_ENET_TCR_CRCFWD(instance, !isEnabled);
}

/*!
 * @brief Enable/disable forward the CRC filed of the received frame.
 * 
 * This is used to deceide whether the CRC field of received frame is transmitted
 * or stripped. Enable this feature to strip CRC field from the frame.
 * If padding remove is enabled, this feature will be ignored and 
 * the CRC field is checked and always terminated and removed.
 * 
 * @param instance The ENET instance number
 * @param isEnabled The switch to enable/disable transmit the receive CRC
 *             - True to  transmit the received CRC.
 *             - False to strip the received CRC.
 */
static inline void enet_hal_enable_rxcrcforward(uint32_t instance, bool isEnabled)
{
    // assert(instance < HW_ENET_INSTANCE_COUNT);
    BW_ENET_RCR_CRCFWD(instance, !isEnabled);
}
/*!
 * @brief Enable/disable forward PAUSE frames.
 * 
 * This is used to deceide whether PAUSE frames is forwarded or discarded.
 * 
 * @param instance The ENET instance number
 * @param isEnabled The switch to enable/disable forward PAUSE frames
 *             - True to forward PAUSE frames.
 *             - False to terminate and discard PAUSE frames.
 */
static inline void enet_hal_enable_pauseforward(uint32_t instance, bool isEnabled)
{
    // assert(instance < HW_ENET_INSTANCE_COUNT);
    BW_ENET_RCR_PAUFWD(instance, isEnabled);
}

/*!
 * @brief Enable/disable frame padding remove on receive.
 * 
 * Enable frame padding remove will remove the padding from the received frames.
 * 
 * @param instance The ENET instance number
 * @param isEnabled The switch to enable/disable remove padding
 *             - True to remove padding from frames.
 *             - False to disable padding remove.
 */
static inline void enet_hal_enable_padremove(uint32_t instance, bool isEnabled)
{
    // assert(instance < HW_ENET_INSTANCE_COUNT);
    BW_ENET_RCR_PADEN(instance, isEnabled);
}

/*!
 * @brief Enable/disable flow control.
 * 
 * If flow control is enabled, the receive detects PAUSE frames.
 * Upon PAUSE frame detection, the transmitter stops transmitting
 * data frames for a given duration. 
 *
 * @param instance The ENET instance number
 * @param isEnabled The switch to enable/disable flow control
 *             - True to enable the flow control.
 *             - False to disable the flow control.
 */
static inline void enet_hal_enable_flowcontrol(uint32_t instance, bool isEnabled)
{
    // assert(instance < HW_ENET_INSTANCE_COUNT);
    BW_ENET_RCR_CFEN(instance, isEnabled);
    BW_ENET_RCR_FCE(instance, isEnabled);
}

/*!
 * @brief Enable/disable broadcast frame reject.
 * 
 * If broadcast frame reject is enabled, frames with destination address 
 * equal to 0xffff_ffff_ffff are rejected unless the promiscuous mode is open.
 *
 * @param instance The ENET instance number
 * @param isEnabled The switch to enable/disable reject broadcast frames
 *             - True to reject broadcast frames.
 *             - False to accept broadcast frames.
 */
static inline void enet_hal_enable_broadcastreject(uint32_t instance, bool isEnabled)
{
    // assert(instance < HW_ENET_INSTANCE_COUNT);
    BW_ENET_RCR_BC_REJ(instance, isEnabled);
}

/*!
 * @brief Sets PAUSE duration for a PAUSE frame.
 * 
 * This function is used to set the pause duraion used in transmission 
 * of a PAUSE frame. When another node detects a PAUSE frame, that node
 * pauses transmission for the pause duration.
 *
 * @param instance The ENET instance number
 * @param pauseDuration The PAUSE duration for the transmitted PAUSE frame
 *                      the maximum pause duration is 0xFFFF.
 */
static inline void enet_hal_set_pauseduration(uint32_t instance, uint32_t pauseDuration)
{
    // assert(instance < HW_ENET_INSTANCE_COUNT);
    assert(pauseDuration <= BM_ENET_OPD_PAUSE_DUR);
    BW_ENET_OPD_PAUSE_DUR(instance, pauseDuration);
}

/*!
 * @brief Gets receive PAUSE frame status.
 * 
 * This function is used to get the received PAUSE frame status. 
 *
 * @param instance The ENET instance number
 * @return The status of the received flow control frames
 *         true if the flow control pause frame is received.
 *         false if there is no flow control frame received or the pause duration is complete. 
 */
static inline bool enet_hal_get_rxpause_status(uint32_t instance)
{
    // assert(instance < HW_ENET_INSTANCE_COUNT);
    return BR_ENET_TCR_RFC_PAUSE(instance);
}
/*!
 * @brief Enables transmit frame control PAUSE.
 * 
 * This function enables pauses frame transmission. 
 * When this is set, with transmission of data frames stopped, the MAC
 * transmits a MAC control PAUSE frame. NEXT, the MAC clear the  
 * and resumes transmitting data frames.
 *
 * @param instance The ENET instance number
 * @param isEnabled The switch to enable/disable PAUSE control frame transmission
 *              - True enable PAUSE control frame transmission.
 *              - Flase disable PAUSE control frame transmission.
 */
static inline void enet_hal_enable_txpause(uint32_t instance, bool isEnabled)
{
    // assert(instance < HW_ENET_INSTANCE_COUNT);
    BW_ENET_TCR_TFC_PAUSE(instance, isEnabled);
}

/*!
 * @brief Sets transmit PAUSE frame.
 * 
 * This function Sets ENET transmit controller with pause duration. 
 * And set the transmit control to do PAUSE frame transmission
 * This should be called when a PAUSE frame is dynamically wanted.
 *
 * @param instance The ENET instance number
 */
void enet_hal_set_txpause(uint32_t instance, uint32_t pauseDuration);

/*!
 * @brief Sets the transmit inter-packet gap.
 * 
 * This function indicates the IPG, in bytes, between transmitted frames. 
 * Valid values range from 8 to 27. If value is less than 8, the IPG is 8.
 * If value is greater than 27, the IPG is 27.
 *
 * @param instance The ENET instance number
 * @param ipgValue The IPG for transmitted frames
 *                 The default value is 12, the maximum value set to ipg is 0x1F.
 *              
 */
static inline void enet_hal_set_txipg(uint32_t instance, uint32_t ipgValue)
{
    // assert(instance < HW_ENET_INSTANCE_COUNT);
    assert(ipgValue <= BM_ENET_TIPG_IPG);
    BW_ENET_TIPG_IPG(instance, ipgValue);
}

/*!
 * @brief Sets the receive frame truncation length.
 * 
 * This function indicates the value a receive frame is truncated,
 * if it is greater than this value. The frame truncation length must be greater
 * than or equal to the receive maximum frame length.
 *
 * @param instance The ENET instance number
 * @param length The truncation length. The maximum value is 0x3FFF
 *               The default truncation length is 2047(0x7FF).
 *              
 */
static inline void enet_hal_set_truncationlen(uint32_t instance, uint32_t length)
{
    // assert(instance < HW_ENET_INSTANCE_COUNT);
    assert(length <= BM_ENET_FTRL_TRUNC_FL);
    BW_ENET_FTRL_TRUNC_FL(instance, length);
}

/*!
 * @brief Sets the maximum receive buffer size and the maximum frame size.
 * 
 * @param instance The ENET instance number
 * @param maxBufferSize The maximum receive buffer size, which  should not be smaller than 256
 *        It should be evenly divisible by 16 and the maximum receive size should not be larger than 0x3ff0.
 * @param maxFrameSize The maximum receive frame size, the reset value is 1518 or 1522 if the VLAN tags are 
 *        supported. The length is measured starting at DA and including the CRC.
 */
static inline void enet_hal_set_rx_max_size(uint32_t instance, uint32_t maxBufferSize, uint32_t maxFrameSize)
{
    // assert(instance < HW_ENET_INSTANCE_COUNT);
    /* max buffer size must larger than 256 to minimize bus usage*/
    assert(maxBufferSize >= 256); 
    assert(maxFrameSize <= (BM_ENET_RCR_MAX_FL >> BP_ENET_RCR_MAX_FL));
	
    BW_ENET_RCR_MAX_FL(instance, maxFrameSize);
    HW_ENET_MRBR_WR(instance, (maxBufferSize & BM_ENET_MRBR_R_BUF_SIZE));
}

/*!
 * @brief Configures the ENET transmit FIFO.
 *
 * @param instance The ENET instance number
 * @param thresholdCfg The FIFO threshold configuration
 */
void enet_hal_config_tx_fifo(uint32_t instance, enet_config_tx_fifo_t *thresholdCfg);

/*!
 * @brief Configures the ENET receive FIFO.
 *
 * @param instance The ENET instance number
 * @param thresholdCfg The FIFO threshold configuration
 */
void enet_hal_config_rx_fifo(uint32_t instance, enet_config_rx_fifo_t *thresholdCfg);

/*!
 * @brief Sets the start address for ENET receive buffer descriptors.
 *
 * This interface provides the beginning of the receive 
 * and receive buffer descriptor queue in the external memory. The
 * txbdAddr is recommended to be 128-bit aligned, must be evenly divisible by 16.
 *
 * @param instance The ENET instance number
 * @param rxBdAddr The start address of receive buffer descriptors
 */
static inline void enet_hal_set_rxbd_address(uint32_t instance, uint32_t rxBdAddr)
{
    // assert(instance < HW_ENET_INSTANCE_COUNT);

    HW_ENET_RDSR_WR(instance,rxBdAddr);   /* Initialize receive buffer descriptor start address*/
}
/*!
 * @brief Sets the start address for ENET transmit buffer descriptors.
 *
 * This interface provides the beginning of the receive 
 * and transmit buffer descriptor queue in the external memory. The
 * txbdAddr is recommended to be 128-bit aligned, must be evenly divisible by 16.
 *
 * @param instance The ENET instance number
 * @param txBdAddr The start address of transmit buffer descriptors
 */
static inline void enet_hal_set_txbd_address(uint32_t instance, uint32_t txBdAddr)
{
    // assert(instance < HW_ENET_INSTANCE_COUNT);

    HW_ENET_TDSR_WR(instance,txBdAddr);   /* Initialize transmit buffer descriptor start address*/
}

/*!
 * @brief Initializes the receive buffer descriptors.
 *
 * To make sure the uDMA will do the right data transfer after you activate
 * with wrap flag and all the buffer descriptors should be initialized with an empty bit.
 * 
 * @param rxBds The current receive buffer descriptor
 * @param buffer The data buffer on buffer descriptor
 * @param isLastBd The flag to indicate the last receive buffer descriptor
 */
void enet_hal_init_rxbds(void *rxBds, uint8_t *buffer, bool isLastBd);

/*!
 * @brief Initializes the  transmit buffer descriptors.
 *
 * To make sure the uDMA will do the right data transfer after you active
 * with wrap flag. 
 * 
 * @param txBds The current transmit buffer descriptor.
 * @param isLastBd The last transmit buffer descriptor flag.
 */
void enet_hal_init_txbds(void *txBds, bool isLastBd);

/*!
 * @brief Updates the receive buffer descriptors.
 *
 * This interface mainly clears the status region and updates the received
 * buffer descriptor to ensure that the BD is  correctly used.
 *
 * @param rxBds The current receive buffer descriptor
 * @param data The data buffer address
 * @param isbufferUpdate The data buffer update flag. When you want to update 
 *        the data buffer of the buffer descriptor ensure that this flag
 *        is set.
 */
void enet_hal_update_rxbds(void *rxBds, uint8_t *data, bool isbufferUpdate);

/*!
 * @brief Initializes the transmit buffer descriptors.
 *
 * Ensures that the uDMA transfer data correctly after the user activates
 * with the wrap flag. 
 * 
 * @param txBds The current transmit buffer descriptor
 * @param isLastBd The last transmit buffer descriptor flag
 */
void enet_hal_init_txbds(void *txBds, bool isLastBd);

/*!
 * @brief Updates the transmit buffer descriptors.
 *
 * This interface mainly clears the status region and updates the transmit
 * buffer descriptor to ensure tat this BD is  correctly used again.
 * You should set the isTxtsCfged when the transmit timestamp feature is required. 
 *
 * @param txBds The current transmit buffer descriptor
 * @param buffer The data buffer on buffer descriptor
 * @param length The data length on buffer descriptor
 * @param isTxtsCfged The timestamp configure flag. The timestamp is 
 *        added to the transmit buffer descriptor when this flag is set.
 */
void enet_hal_update_txbds(void *txBds,uint8_t *buffer, uint16_t length, bool isTxtsCfged);

/*!
 * @brief Clears the context in the transmit buffer descriptors.
 *
 * Clears the data, length, control, and status region of the transmit buffer descriptor.
 *
 * @param curBd The current buffer descriptor
 */
static inline void enet_hal_clear_txbds(void *curBd)
{
    assert(curBd);

    volatile enet_bd_struct_t *bdPtr = (enet_bd_struct_t *)curBd;
    bdPtr->length = 0;                /* Set data length*/
    bdPtr->buffer = (uint8_t *)(NULL);/* Set data buffer*/
    bdPtr->control &= (kEnetTxBdWrap);/* Set control */
}

/*!
 * @brief Gets the control and the status region of the receive buffer descriptors.
 *
 * This interface can get the whole control and status region of the 
 * receive buffer descriptor. The enet_rx_bd_control_status_t enum type 
 * definition should be used if you want to get each status bit of
 * the control and status region.
 *
 * @param curBd The current receive buffer descriptor
 * @return The control and status data on buffer descriptors
 */
uint16_t enet_hal_get_rxbd_control(void *curBd);

/*!
 * @brief Gets the control and the status region of the transmit buffer descriptors.
 *
 * This interface can get the whole control and status region of the 
 * transmit buffer descriptor. The enet_tx_bd_control_status_t enum type 
 * definition should be used if you want to get each status bit of
 * the control and status region.
 *
 * @param curBd The current transmit buffer descriptor
 * @return The extended control region of transmit buffer descriptor
 */
uint16_t enet_hal_get_txbd_control(void *curBd);

/*!
 * @brief Gets the extended control region of the receive buffer descriptors.
 *
 * This interface can get the whole control and status region of the 
 * receive buffer descriptor. The enet_rx_bd_control_extend_t enum type 
 * definition should be used if you want to get each status bit of
 * the control and status region.
 *
 * @param curBd The current receive buffer descriptor
 * @param controlRegion The different control region
 * @return The extended control region data of receive buffer descriptor
 *         - true when the control region is set 
 *         - false when the control region is not set
 */
bool enet_hal_get_rxbd_control_extend(void *curBd,enet_rx_bd_control_extend_t controlRegion);
/*!
 * @brief Gets the extended control region of the transmit buffer descriptors.
 *
 * This interface can get the whole control and status region of the 
 * transmit buffer descriptor. The enet_tx_bd_control_extend_t enum type 
 * definition should be used if you want to get each status bit of
 * the control and status region.
 *
 * @param curBd The current transmit buffer descriptor
 * @return The extended control data
 */
uint16_t enet_hal_get_txbd_control_extend(void *curBd);

/*!
 * @brief Gets  the data length of the buffer descriptors.
 *
 * @param curBd The current buffer descriptor
 * @return The data length of the buffer descriptor
 */
uint16_t enet_hal_get_bd_length(void *curBd);

/*!
 * @brief Gets the buffer address of the buffer descriptors.
 *
 * @param curBd The current buffer descriptor
 * @return The buffer address of the buffer descriptor
 */ 
uint8_t* enet_hal_get_bd_buffer(void *curBd);

/*!
 * @brief Gets  the timestamp of the buffer descriptors.
 *
 * @param curBd The current buffer descriptor
 * @return The time stamp of the frame in the buffer descriptor.
 *         Notice that the frame timestamp is only set in the last  
 *         buffer descriptor of the frame. 
 */
uint32_t enet_hal_get_bd_timestamp(void *curBd);

/*!
 * @brief Activates the receive buffer descriptor.
 *
 * The buffer descriptor activation
 * should be done after the ENET module is enabled. Otherwise, the activation  fails.
 *
 * @param instance The ENET instance number
 */
 static inline void enet_hal_active_rxbd(uint32_t instance)
{
    // assert(instance < HW_ENET_INSTANCE_COUNT);

    HW_ENET_RDAR_SET(instance, BM_ENET_RDAR_RDAR);
}

/*!
 * @brief Activates the transmit buffer descriptor.
 *
 * The  buffer descriptor activation should be done after the ENET module is
 * enabled. Otherwise, the activation  fails.
 * 
 * @param instance The ENET instance number
 */
static inline void enet_hal_active_txbd(uint32_t instance)
{
    // assert(instance < HW_ENET_INSTANCE_COUNT);

    HW_ENET_TDAR_SET(instance, BM_ENET_TDAR_TDAR);
}

/*!
 * @brief Configures the (R)MII of ENET.
 *
 * @param instance The ENET instance number
 * @param mode The RMII or MII mode
 * @param speed The speed of RMII
 * @param duplex The full or half duplex mode
 * @param isRxOnTxDisabled The Receive on transmit disable flag
 * @param isLoopEnabled The loop enable flag
 */
void enet_hal_config_rmii(uint32_t instance, enet_config_rmii_t mode, enet_config_speed_t speed, enet_config_duplex_t duplex, bool isRxOnTxDisabled,  bool isLoopEnabled);

/*!
 * @brief Configures the MII of ENET.
 *
 * Sets the MII interface between Mac and PHY. The miiSpeed is 
 * a value that controls the frequency of the MDC, relative to the internal module clock(InterClockSrc).
 * A value of zero in this parameter turns the MDC off and leaves it in the low voltage state.
 * Any non-zero value results in the MDC frequency MDC = InterClockSrc/((miiSpeed + 1)*2).
 * So miiSpeed = InterClockSrc/(2*MDC) - 1.
 * The Maximum MDC clock is 2.5MHZ(maximum). We should round up and plus one to simlplify:
 *  miiSpeed = InterClockSrc/(2*2.5MHZ).
 *
 * @param instance The ENET instance number
 * @param miiSpeed The MII speed and it is ranged from 0~0x3F
 * @param time The holdon clock cycles for MDIO output
 * @param isPreambleDisabled The preamble disabled flag
 */
static inline void enet_hal_config_mii(uint32_t instance, uint32_t miiSpeed, 
                              enet_mdio_holdon_clkcycle_t clkCycle, bool isPreambleDisabled)
{
    // assert(instance < HW_ENET_INSTANCE_COUNT);
    
    BW_ENET_MSCR_MII_SPEED(instance, miiSpeed);          /* MII speed set*/
    BW_ENET_MSCR_DIS_PRE(instance, isPreambleDisabled);  /* Preamble is disabled*/
    BW_ENET_MSCR_HOLDTIME(instance, clkCycle);  /* hold on clock cycles for MDIO output*/

}

/*!
 * @brief Gets the MII configuration status.
 *
 * This interface is usually called to check the MII interface before 
 * the Mac  writes or reads the PHY registers.
 *
 * @param instance The ENET instance number
 * @return The MII configuration status
 *         - true if the MII has been configured. 
 *         - false if the MII has not been configured.
 */
static inline bool enet_hal_is_mii_enabled(uint32_t instance)
{
    // assert(instance < HW_ENET_INSTANCE_COUNT);

    return (HW_ENET_MSCR_RD(instance) & 0x7E)!= 0;	
}

/*!
 * @brief Reads data from PHY. 
 *
 * @param instance The ENET instance number
 * @return The data read from PHY
 */
static inline uint32_t enet_hal_get_mii_data(uint32_t instance)
{
    // assert(instance < HW_ENET_INSTANCE_COUNT);

    return (uint32_t)BR_ENET_MMFR_DATA(instance);
}

/*!
 * @brief Sets the MII command.
 *
 * @param instance The ENET instance number
 * @param phyAddr The PHY address
 * @param phyReg The PHY register
 * @param operation The read or write operation
 * @param data The data written to PHY
 */
void enet_hal_set_mii_command(uint32_t instance, uint32_t phyAddr, uint32_t phyReg, enet_mii_operation_t operation, uint32_t data);

/*!
 * @brief Enables/Disables the ENET module.
 *
 * @param instance The ENET instance number
 * @param isEnhanced The enhanced 1588 feature switch
 * @param isEnabled The ENET module enable switch
 */
void enet_hal_config_ethernet(uint32_t instance, bool isEnhanced, bool isEnabled);

/*!
 * @brief Enables/Disables the ENET interrupt.
 *
 * @param instance The ENET instance number
 * @param source The interrupt sources. enet_interrupt_request_t enum types
 *        is recommended as the interrupt source.
 * @param isEnabled The interrupt enable switch
 */
void enet_hal_config_interrupt(uint32_t instance, uint32_t source, bool isEnabled);

/*!
 * @brief Clears  ENET interrupt events. 
 *
 * @param instance The ENET instance number
 * @param source The interrupt source to be cleared. enet_interrupt_request_t 
 *        enum types is recommended as the interrupt source.
 */
static inline void enet_hal_clear_interrupt(uint32_t instance, uint32_t source)
{
    // assert(instance < HW_ENET_INSTANCE_COUNT);
 
    HW_ENET_EIR_WR(instance,source);    
}

/*!
 * @brief Gets the ENET interrupt status.
 *
 * @param instance The ENET instance number
 * @param source The interrupt sources. enet_interrupt_request_t 
 *        enum types is recommended as the interrupt source.
 * @return The event status of the interrupt source
 *         - true if the interrupt event happened. 
 *         - false if the interrupt event has not happened.
 */
static inline bool enet_hal_get_interrupt_status(uint32_t instance, uint32_t source)
{
    // assert(instance < HW_ENET_INSTANCE_COUNT);

    return ((HW_ENET_EIR_RD(instance) & source) != 0);  
}

/*
 * @brief Enables/disables the ENET promiscuous mode.
 *
 * @param instance The ENET instance number
 * @param isEnabled The enable switch
 */
static inline void enet_hal_config_promiscuous(uint32_t instance, bool isEnabled)
{
    // assert(instance < HW_ENET_INSTANCE_COUNT);

    BW_ENET_RCR_PROM(instance,isEnabled);	
}

/*!
 * @brief Enables/disables the clear MIB counter. 
 *
 * @param instance The ENET instance number
 * @param isEnabled The enable switch
 */
static inline void enet_hal_clear_mib(uint32_t instance, bool isEnabled)
{
    // assert(instance < HW_ENET_INSTANCE_COUNT);

    BW_ENET_MIBC_MIB_CLEAR(instance, isEnabled);

}

/*!
 * @brief Sets the enable/disable of the MIB block. 
 *
 * @param instance The ENET instance number
 * @param isEnabled The enable flag
 *             - True to enabale MIB block.
 *             - False to disable MIB block.
 */
static inline void enet_hal_enable_mib(uint32_t instance, bool isEnabled)
{
    // assert(instance < HW_ENET_INSTANCE_COUNT);

    BW_ENET_MIBC_MIB_DIS(instance,!isEnabled);

}

/*!
 * @brief Gets the MIB idle status. 
 *
 * @param instance The ENET instance number
 * @return true if in MIB idle and MIB is not updating else false.
 */
static inline bool enet_hal_get_mib_status(uint32_t instance)
{
    // assert(instance < HW_ENET_INSTANCE_COUNT);
    
    return BR_ENET_MIBC_MIB_IDLE(instance);
}

/*!
 * @brief Sets the transmit accelerator.
 *
 * @param instance The ENET instance number
 * @param txCfgPtr The transmit accelerator configuration 
 */
void enet_hal_config_tx_accelerator(uint32_t instance, enet_config_tx_accelerator_t *txCfgPtr);

/*!
 * @brief Sets the receive accelerator. 
 *
 * @param instance The ENET instance number
 * @param rxCfgPtr The receive accelerator configuration 
 */
void enet_hal_config_rx_accelerator(uint32_t instance, enet_config_rx_accelerator_t *rxCfgPtr);

/*!
 * @brief Initializes the 1588 timer.
 *
 * This interface  initializes the 1588 context structure.
 * Initialize 1588 parameters according to the user configuration structure.
 *
 * @param instance The ENET instance number
 * @param ptpCfg The 1588 timer configuration
 */
void enet_hal_init_ptp_timer(uint32_t instance, enet_config_ptp_timer_t *ptpCfgPtr);

/*!
 * @brief Enables or disables the 1588 timer.
 *
 * Enable the PTP timer will starts the timer. Disable the timer will stop timer
 * at the current value.
 *
 * @param instance The ENET instance number.
 * @param isEnabled The 1588 timer Enable switch
 *              - True enbaled the 1588 PTP timer.
 *              - False disable or stop the 1588 PTP timer.
 */
static inline void enet_hal_enable_ptp_timer(uint32_t instance, uint32_t isEnabled)
{
    // assert(instance < HW_ENET_INSTANCE_COUNT);

    BW_ENET_ATCR_EN(instance,isEnabled);                          
}

/*!
 * @brief Restarts the 1588 timer.
 *
 * Restarting the PTP timer  clears all PTP-timer counters to zero.
 *
 * @param instance The ENET instance number
 */
static inline void enet_hal_restart_ptp_timer(uint32_t instance)
{
    // assert(instance < HW_ENET_INSTANCE_COUNT);

    BW_ENET_ATCR_RESTART(instance,1);                          
}

/*!
 * @brief Adjusts the 1588 timer.
 *
 * Adjust the 1588 timer according to the increase and correction period of the configured correction.
 *
 * @param instance The ENET instance number
 * @param inceaseCorrection The increase correction for 1588 timer
 * @param periodCorrection The period correction for 1588 timer
 */
static inline void enet_hal_adjust_ptp_timer(uint32_t instance, uint32_t increaseCorrection, uint32_t periodCorrection)
{
    // assert(instance < HW_ENET_INSTANCE_COUNT);

    HW_ENET_ATINC_SET(instance,((increaseCorrection << ENET_ATINC_INC_CORR_SHIFT) & ENET_ATINC_INC_CORR_MASK));      /* set correction for ptp timer increase*/
    /* set correction for ptp timer period*/
    HW_ENET_ATCOR_SET(instance, (BM_ENET_ATCOR_COR & periodCorrection));
}

/*!
 * @brief Initializes the 1588 timer channel.
 *
 * @param instance The ENET instance number
 * @Param channel The 1588 timer channel number
 * @param mode Compare or capture mode for the 1588 timer channel
 */
static inline void enet_hal_init_timer_channel(uint32_t instance, uint32_t channel, enet_timer_channel_mode_t mode)
{
    // assert(instance < HW_ENET_INSTANCE_COUNT);
    assert(channel < HW_ENET_TCSRn_COUNT);
    HW_ENET_TCSRn_SET(instance, channel, 
        (BM_ENET_TCSRn_TMODE &(mode << BP_ENET_TCSRn_TMODE)));
    HW_ENET_TCSRn_SET(instance, channel, BM_ENET_TCSRn_TIE);   
}

/*!
 * @brief Sets the compare value for the 1588 timer channel.
 *
 * @param instance The ENET instance number
 * @Param channel The 1588 timer channel number
 * @param compareValue Compare value for 1588 timer channel
 */
static inline void enet_hal_set_timer_channel_compare(uint32_t instance, uint32_t channel, uint32_t compareValue)
{
    assert(instance < HW_ENET_INSTANCE_COUNT);
    assert(channel < HW_ENET_TCSRn_COUNT);
    HW_ENET_TCCRn_WR(instance,channel, compareValue);   
}

/*!
 * @brief Gets the 1588 timer channel status.
 *
 * @param instance The ENET instance number
 * @param channel The 1588 timer channel number
 * @return Compare or capture operation status
 *         - True if the compare or capture has occurred.
 *         - False if the compare or capture has not occurred. 
 */
static inline bool enet_hal_get_timer_channel_status(uint32_t instance, uint32_t channel)
{
    // assert(instance < HW_ENET_INSTANCE_COUNT);
    assert(channel < HW_ENET_TCSRn_COUNT);

    return BR_ENET_TCSRn_TF(instance,channel);  
}

/*!
 * @brief Clears the 1588 timer channel flag.
 *
 * @param instance The ENET instance number
 * @param channel The 1588 timer channel number
 */
static inline void enet_hal_clear_timer_channel_flag(uint32_t instance, uint32_t channel)
{
    // assert(instance < HW_ENET_INSTANCE_COUNT);
    assert(channel < HW_ENET_TCSRn_COUNT);
    HW_ENET_TCSRn_SET(instance, channel, BM_ENET_TCSRn_TF);/* clear interrupt flag*/
    HW_ENET_TGSR_WR(instance,(1U << channel));            /* clear channel flag*/
}

/*!
 * @brief Sets the capture command to the 1588 timer.
 *
 * This is used before reading the current time register.
 * After set timer capture, please wait for about 1us before read
 * the captured timer. 
 *
 * @param instance The ENET instance number
 */
static inline void enet_hal_set_timer_capture(uint32_t instance)
{
    assert(instance < HW_ENET_INSTANCE_COUNT);

    HW_ENET_ATCR_SET(instance, BM_ENET_ATCR_CAPTURE);
}

/*!
 * @brief Sets the 1588 timer.
 *
 * @param instance The ENET instance number
 * @param nanSecond The nanosecond set to 1588 timer
 */
static inline void enet_hal_set_current_time(uint32_t instance, uint32_t nanSecond)
{
    // assert(instance < HW_ENET_INSTANCE_COUNT);

    HW_ENET_ATVR_WR(instance,nanSecond);
}

/*!
 * @brief Gets the time from the 1588 timer.
 *
 * @param instance The ENET instance number
 * @return the current time from 1588 timer
 */
static inline uint32_t enet_hal_get_current_time(uint32_t instance)
{
    // assert(instance < HW_ENET_INSTANCE_COUNT);

    return HW_ENET_ATVR_RD(instance);   
}

/*!
 * @brief Gets the transmit timestamp.
 *
 * @param instance The ENET instance number
 * @return The timestamp of the last transmitted frame
 */
static inline uint32_t enet_hal_get_tx_timestamp(uint32_t instance)
{
    // assert(instance < HW_ENET_INSTANCE_COUNT);

    return HW_ENET_ATSTMP_RD(instance);
}

/*!
 * @brief Gets the transmit buffer descriptor timestamp flag.
 *
 * @param curBd The ENET transmit buffer descriptor
 * @return true if timestamp region is set else false.
 */
bool enet_hal_get_txbd_timestamp_flag(void *curBd);

/*!
 * @brief Gets the buffer descriptor timestamp.
 *
 * @param null
 * @return The the size of the buffer descriptor
 */
static inline uint32_t enet_hal_get_bd_size(void)
{
    return sizeof(enet_bd_struct_t);
}

/* @} */

#if defined(__cplusplus)
}
#endif

#endif

/*! @}*/
#endif /*!< __FSL_ENET_HAL_H__*/

/*******************************************************************************
 * EOF
 ******************************************************************************/

