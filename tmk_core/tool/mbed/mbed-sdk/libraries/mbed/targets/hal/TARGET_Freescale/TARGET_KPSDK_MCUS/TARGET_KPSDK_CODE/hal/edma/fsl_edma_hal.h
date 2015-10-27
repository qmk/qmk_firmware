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
#ifndef __EDMA_HAL_H__
#define __EDMA_HAL_H__

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_edma_features.h"
#include "fsl_device_registers.h"

/*!
 * @addtogroup edma_hal
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Error code for the eDMA Driver. */
typedef enum _edma_status {
    kStatus_EDMA_Success = 0U,
    kStatus_EDMA_InvalidArgument = 1U,  /*!< Parameter is invalid. */
    kStatus_EDMA_Fail = 2U              /*!< Failed operation. */
} edma_status_t;

/*! @brief eDMA channel arbitration algorithm used for selection among channels. */
typedef enum _edma_channel_arbitration {
    kEDMAChnArbitrationFixedPriority = 0U,  /*!< Fixed Priority arbitration is used for selection
                                                 among channels. */
    kEDMAChnArbitrationRoundrobin           /*!< Round-Robin arbitration is used for selection among
                                                 channels. */
} edma_channel_arbitration_t;

/*! @brief eDMA channel priority setting */
typedef enum _edma_chn_priority {
    kEDMAChnPriority0 = 0U,
    kEDMAChnPriority1,
    kEDMAChnPriority2,
    kEDMAChnPriority3,
    kEDMAChnPriority4,
    kEDMAChnPriority5,
    kEDMAChnPriority6,
    kEDMAChnPriority7,
    kEDMAChnPriority8,
    kEDMAChnPriority9,
    kEDMAChnPriority10,
    kEDMAChnPriority11,
    kEDMAChnPriority12,
    kEDMAChnPriority13,
    kEDMAChnPriority14,
    kEDMAChnPriority15
} edma_channel_priority_t;

#if (FSL_FEATURE_EDMA_CHANNEL_GROUP_COUNT > 0x1U)
/*! @brief eDMA group arbitration algorithm used for selection among channels. */
typedef enum _edma_group_arbitration
{
    kEDMAGroupArbitrationFixedPriority = 0U,    /*!< Fixed Priority arbitration is used for
                                                     selection among eDMA groups. */
    kEDMAGroupArbitrationRoundrobin             /*!< Round-Robin arbitration is used for selection
                                                     among eDMA channels. */
} edma_group_arbitration_t;

/*! @brief eDMA group priority setting */
typedef enum _edma_group_priority {
    kEDMAGroup0PriorityLowGroup1PriorityHigh,    /*!< eDMA group 0's priority is lower priority.
                                                      eDMA group 1's priority is higher priority. */
    kEDMAGroup0PriorityHighGroup1PriorityLow     /*!< eDMA group 0's priority is higher priority.
                                                      eDMA group 1's priority is lower priority. */
} edma_group_priority_t;
#endif

/*! @brief eDMA modulo configuration */
typedef enum _edma_modulo {
    kEDMAModuloDisable = 0U,
    kEDMAModulo2bytes,
    kEDMAModulo4bytes,
    kEDMAModulo8bytes,
    kEDMAModulo16bytes,
    kEDMAModulo32bytes,
    kEDMAModulo64bytes,
    kEDMAModulo128bytes,
    kEDMAModulo256bytes,
    kEDMAModulo512bytes,
    kEDMAModulo1Kbytes,
    kEDMAModulo2Kbytes,
    kEDMAModulo4Kbytes,
    kEDMAModulo8Kbytes,
    kEDMAModulo16Kbytes,
    kEDMAModulo32Kbytes,
    kEDMAModulo64Kbytes,
    kEDMAModulo128Kbytes,
    kEDMAModulo256Kbytes,
    kEDMAModulo512Kbytes,
    kEDMAModulo1Mbytes,
    kEDMAModulo2Mbytes,
    kEDMAModulo4Mbytes,
    kEDMAModulo8Mbytes,
    kEDMAModulo16Mbytes,
    kEDMAModulo32Mbytes,
    kEDMAModulo64Mbytes,
    kEDMAModulo128Mbytes,
    kEDMAModulo256Mbytes,
    kEDMAModulo512Mbytes,
    kEDMAModulo1Gbytes,
    kEDMAModulo2Gbytes
} edma_modulo_t;

/*! @brief eDMA transfer configuration */
typedef enum _edma_transfer_size {
    kEDMATransferSize_1Bytes = 0x0U,
    kEDMATransferSize_2Bytes = 0x1U,
    kEDMATransferSize_4Bytes = 0x2U,
    kEDMATransferSize_16Bytes = 0x4U,
    kEDMATransferSize_32Bytes = 0x5U
} edma_transfer_size_t;

/*!
 * @brief eDMA transfer size configuration.
 * 
 * This structure configures the basic source/destination transfer attribute.
 * This figure shows the eDMA's transfer model:
 *  _________________________________________________
 *              | Transfer Size |                    |
 *   Minor Loop |_______________| Major loop Count 1 |
 *     Count    | Transfer Size |                    |
 *  ____________|_______________|____________________|--> Minor loop complete
 *               ____________________________________
 *              |               |                    |
 *              |_______________| Major Loop Count 2 |
 *              |               |                    |
 *              |_______________|____________________|--> Minor loop  Complete
 *                                                                      
 *               ---------------------------------------------------------> Major loop complete
 *
 */
typedef struct EDMATransferConfig {
    uint32_t srcAddr;               /*!< Memory address pointing to the source data. */
    uint32_t destAddr;              /*!< Memory address pointing to the destination data. */
    edma_transfer_size_t srcTransferSize;   /*!< Source data transfer size. */
    edma_transfer_size_t destTransferSize;  /*!< Destination data transfer size. */
    int16_t srcOffset;         /*!< Sign-extended offset applied to the current source address to
                                    form the next-state value as each source read/write is
                                    completed. */
    int16_t destOffset;
    uint32_t srcLastAddrAdjust;    /*!< Last source address adjustment. */
    uint32_t destLastAddrAdjust;   /*!< Last destination address adjustment. Note here it is only
                                        valid when scatter/gather feature is not enabled. */
    edma_modulo_t srcModulo;       /*!< Source address modulo. */
    edma_modulo_t destModulo;       /*!< Destination address modulo. */
    uint32_t minorLoopCount;    /*!< Minor bytes transfer count. Number of bytes to be transferred
                                     in each service request of the channel. */
    uint16_t majorLoopCount;    /*!< Major iteration count. */
} edma_transfer_config_t;

/*! @brief eDMA channel configuration. */
typedef enum _edma_channel_indicator {
    kEDMAChannel0 = 0U,     /*!< Channel 0. */
    kEDMAChannel1 = 1U,
    kEDMAChannel2 = 2U,
    kEDMAChannel3 = 3U,
#if (FSL_FEATURE_EDMA_MODULE_CHANNEL > 4U)
    kEDMAChannel4 = 4U,
    kEDMAChannel5 = 5U,
    kEDMAChannel6 = 6U,
    kEDMAChannel7 = 7U,
    kEDMAChannel8 = 8U,
    kEDMAChannel9 = 9U,
    kEDMAChannel10 = 10U,
    kEDMAChannel11 = 11U,
    kEDMAChannel12 = 12U,
    kEDMAChannel13 = 13U,
    kEDMAChannel14 = 14U,
    kEDMAChannel15 = 15U,
#endif
#if (FSL_FEATURE_EDMA_MODULE_CHANNEL == 32U)
    kEDMAChannel16 = 16U,
    kEDMAChannel17 = 17U,
    kEDMAChannel18 = 18U,
    kEDMAChannel19 = 19U,
    kEDMAChannel20 = 20U,
    kEDMAChannel21 = 21U,
    kEDMAChannel22 = 22U,
    kEDMAChannel23 = 23U,
    kEDMAChannel24 = 24U,
    kEDMAChannel25 = 25U,
    kEDMAChannel26 = 26U,
    kEDMAChannel27 = 27U,
    kEDMAChannel28 = 28U,
    kEDMAChannel29 = 29U,
    kEDMAChannel30 = 30U,
    kEDMAChannel31 = 31U,
#endif
    kEDMAAllChannel = 64U
} edma_channel_indicator_t;

/*! @brief eDMA TCD Minor loop mapping configuration */
typedef struct EDMAMinorLoopOffsetConfig {
    bool enableSrcMinorloop;    /*!< Enable(true) or Disable(false) source minor loop offset. */
    bool enableDestMinorloop;   /*!< Enable(true) or Disable(false) destination minor loop offset. */
    uint32_t offset;            /*!< Offset for minor loop mapping. */
} edma_minorloop_offset_config_t;

/*! @brief Error status of the eDMA module */
typedef union EDMAErrorStatusAll {
    struct {
        uint32_t destinationBusError : 1;               /*!< Bus error on destination address */
        uint32_t sourceBusError : 1;                    /*!< Bus error on the SRC address */
        uint32_t scatterOrGatherConfigurationError : 1; /*!< Error on the Scatter/Gather address */
        uint32_t nbyteOrCiterConfigurationError : 1;    /*!< NBYTES/CITER configuration error */
        uint32_t destinationOffsetError : 1;            /*!< Destination offset error */
        uint32_t destinationAddressError : 1;           /*!< Destination address error */
        uint32_t sourceOffsetError : 1;                 /*!< Source offset error */
        uint32_t sourceAddressError : 1;                /*!< Source address error */
        uint32_t errorChannel : 5;                      /*!< Error channel number of the cancelled
                                                             channel number */
        uint32_t _reserved1 : 1;
        uint32_t channelPriorityError : 1;              /*!< Channel priority error */
        uint32_t groupPriorityError : 1;                /*!< Group priority error */
        uint32_t transferCancelledError : 1;            /*!< Transfer cancelled */
        uint32_t _reserved0 : 14;
        uint32_t orOfAllError : 1;                      /*!< Logical OR  all ERR status bits */
    } U;
    uint32_t B;
} edma_error_status_all_t;

/*! @brief Bandwidth control configuration */
typedef enum _edma_bandwidth_config {
    kEDMABandwidthStallNone = 0U,    /*!< No eDMA engine stalls. */
    kEDMABandwidthStall4Cycle = 2U,  /*!< eDMA engine stalls for 4 cycles after each read/write. */
    kEDMABandwidthStall8Cycle = 3U   /*!< eDMA engine stalls for 8 cycles after each read/write. */
} edma_bandwidth_config_t;

/*! @brief eDMA TCD */
typedef struct EDMASoftwareTcd {
    uint32_t SADDR;
    uint16_t SOFF;
    uint16_t ATTR;
    union {
        uint32_t MLNO;
        uint32_t MLOFFNO;
        uint32_t MLOFFYES;
    } NBYTES;
    uint32_t SLAST;
    uint32_t DADDR;
    uint16_t DOFF;
    union {
        uint16_t ELINKNO;
        uint16_t ELINKYES;
    } CITER;
    uint32_t DLAST_SGA;
    uint16_t CSR;
    union {
        uint16_t ELINKNO;
        uint16_t ELINKYES;
    } BITER;
} edma_software_tcd_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*! 
 * @name eDMA HAL driver module level operation
 * @{
 */

/*!
 * @brief Initializes eDMA module to known state.
 *
 * @param baseAddr Register base address for eDMA module.
 */
void EDMA_HAL_Init(uint32_t baseAddr);

/*!
 * @brief Cancels the remaining data transfer.
 *
 * This function stops the executing channel and forces the minor loop
 * to finish. The cancellation takes effect after the last write of the
 * current read/write sequence. The CX clears itself after the cancel has
 * been honored. This cancel retires the channel normally as if the minor
 * loop had completed.
 *
 * @param baseAddr Register base address for eDMA module.
 */
void EDMA_HAL_CancelTransfer(uint32_t baseAddr);

/*!
 * @brief Cancels the remaining data transfer and treats it as an error condition.
 *
 * This function stops the executing channel and forces the minor loop
 * to finish. The cancellation takes effect after the last write of the
 * current read/write sequence. The CX clears itself after the cancel has
 * been honored. This cancel retires the channel normally as if the minor
 * loop had completed. Additional thing is to treat this operation as an error
 * condition.
 *
 * @param baseAddr Register base address for eDMA module.
 */
void EDMA_HAL_ErrorCancelTransfer(uint32_t baseAddr);

/*!
 * @brief Halts/Un-halts the DMA Operations.
 *
 * This function stalls/un-stalls the start of any new channels. Executing channels are allowed
 * to be completed. 
 *
 * @param baseAddr Register base address for eDMA module.
 * @param halt Halts (true) or un-halts (false) eDMA transfer.
 */
static inline void EDMA_HAL_SetHaltCmd(uint32_t baseAddr, bool halt)
{
    BW_DMA_CR_HALT(baseAddr, halt);
}

/*!
 * @brief Halts or does not halt the eDMA module when an error occurs.
 *
 * An error causes the HALT bit to be set. Subsequently, all service requests are ignored until the
 * HALT bit is cleared.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param haltOnError Halts (true) or not halt (false) eDMA module when an error occurs. 
 */
static inline void EDMA_HAL_SetHaltOnErrorCmd(uint32_t baseAddr, bool haltOnError)
{	
    BW_DMA_CR_HOE(baseAddr, haltOnError);
}

/*!
 * @brief Enables/Disables the eDMA DEBUG mode.
 *
 * This function enables/disables the eDMA Debug mode.
 * When in debug mode, the DMA stalls the start of a new 
 * channel. Executing channels are allowed to complete. Channel execution resumes 
 * either when the system exits debug mode or when the EDBG bit is cleared. 
 *
 * @param baseAddr Register base address for eDMA module.
 * @param enable Enables (true) or Disable (false) eDMA module debug mode.
 */
static inline void EDMA_HAL_SetDebugCmd(uint32_t baseAddr, bool enable)
{
    BW_DMA_CR_EDBG(baseAddr, enable);
}
/* @} */

/*! 
 * @name eDMA HAL driver channel priority and arbitration configuration.
 * @{
 */
/*!
 * @brief Sets the preempt and preemption feature for the eDMA channel.
 *
 * This function sets the preempt and preemption features. 
 *
 * @param baseAddr Register base address for eDMA module.
 * @param channel eDMA channel number.
 * @param preempt eDMA channel can't suspend a lower priority channel (true). eDMA channel can
 * suspend a lower priority channel (false).
 * @param preemption eDMA channel can be temporarily suspended by the service request of a higher
 * priority channel (true). eDMA channel can't be suspended by a higher priority channel (false).
 */
static inline void EDMA_HAL_SetChannelPreemptMode(
                uint32_t baseAddr, uint32_t channel, bool preempt, bool preemption)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);
    BW_DMA_DCHPRIn_DPA(baseAddr, HW_DMA_DCHPRIn_CHANNEL(channel), preempt);
    BW_DMA_DCHPRIn_ECP(baseAddr, HW_DMA_DCHPRIn_CHANNEL(channel), preemption);
}

/*!
 * @brief Sets the eDMA channel priority.
 *
 * @param baseAddr Register base address for eDMA module. 
 * @param channel eDMA channel number.
 * @param priority Priority of the DMA channel. Different channels should have different priority
 * setting inside a group.
 */
static inline void EDMA_HAL_SetChannelPriority(
                uint32_t baseAddr, uint32_t channel, edma_channel_priority_t priority)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);
    BW_DMA_DCHPRIn_CHPRI(baseAddr, HW_DMA_DCHPRIn_CHANNEL(channel), priority);
}
/*!
 * @brief Sets the channel arbitration algorithm.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param channelArbitration Round-Robin way for fixed priority way.
 */
static inline void EDMA_HAL_SetChannelArbitrationMode(
                uint32_t baseAddr, edma_channel_arbitration_t channelArbitration)
{
    BW_DMA_CR_ERCA(baseAddr, channelArbitration);
}

#if (FSL_FEATURE_EDMA_CHANNEL_GROUP_COUNT > 0x1U)
/*!
 * @brief Configures the group priority.
 *
 * This function configures the priority for group 0 and group 1.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param groupPriority Group priority configuration. Note that each group get its own
 * group priority.
 */
void EDMA_HAL_SetGroupPriority(uint32_t baseAddr, edma_group_priority_t groupPriority);

/*!
 * @brief Sets the eDMA group arbitration algorithm.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param groupArbitration Group arbitration way. Fixed-Priority way or Round-Robin way.
 */
static inline void EDMA_HAL_SetGroupArbitrationMode(
                    uint32_t baseAddr, edma_group_arbitration_t groupArbitration)
{
    BW_DMA_CR_ERGA(baseAddr, groupArbitration);
}
#endif
/* @} */

/*! 
 * @name eDMA HAL driver configuration and operation.
 * @{
 */
/*!
 * @brief Enables/Disables the minor loop mapping.
 *
 * This function enables/disables the minor loop mapping feature.
 * If enabled, the NBYTES is redefined to include the individual enable fields and the NBYTES field. The
 * individual enable fields allow the minor loop offset to be applied to the source address, the 
 * destination address, or both. The NBYTES field is reduced when either offset is enabled.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param enable Enables (true) or Disable (false) minor loop mapping.
 */
static inline void EDMA_HAL_SetMinorLoopMappingCmd(uint32_t baseAddr, bool enable)
{
    BW_DMA_CR_EMLM(baseAddr, enable);
}

/*!
 * @brief Enables or disables the continuous transfer mode.
 *
 * This function enables or disables the continuous transfer. If set, a minor loop channel link
 * does not go through the channel arbitration before being activated again. Upon minor loop
 * completion, the channel activates again if that channel has a minor loop channel link enabled and
 * the link channel is itself. 
 *
 * @param baseAddr Register base address for eDMA module.
 * @param continuous Enables (true) or Disable (false) continuous transfer mode.
 */
static inline void EDMA_HAL_SetContinuousLinkCmd(uint32_t baseAddr, bool continuous)
{
    BW_DMA_CR_CLM(baseAddr, continuous);
}

/*!
 * @brief Gets the error status of the eDMA module.
 *
 * @param baseAddr Register base address for eDMA module. 
 * @return Detailed information of the error type in the eDMA module.
 */
static inline uint32_t EDMA_HAL_GetErrorStatus(uint32_t baseAddr)
{
    return HW_DMA_ES_RD(baseAddr);
}

/*!
 * @brief Enables/Disables the error interrupt for channels.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param enable Enable(true) or Disable (false) error interrupt.
 * @param channel Channel indicator. If kEDMAAllChannel is selected, all channels' error interrupt
 * will be enabled/disabled.
 */
void EDMA_HAL_SetErrorIntCmd(uint32_t baseAddr, bool enable, edma_channel_indicator_t channel);

/*!
 * @brief Checks whether the eDMA channel error interrupt is enabled or disabled.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param channel eDMA channel number.
 * @return Error interrupt is enabled (true) or disabled (false).
 */
bool EDMA_HAL_GetErrorIntCmd(uint32_t baseAddr, uint32_t channel);

/*!
 * @brief Gets the eDMA error interrupt status.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param channel eDMA channel number.
 * @return 32 bit variable indicating error channels. If error happens on eDMA channel n, the bit n
 * of this variable is '1'. If not, the bit n of this variable is '0'.
 */
static inline uint32_t EDMA_HAL_GetErrorIntStatusFlag(uint32_t baseAddr)
{
    return HW_DMA_ERR_RD(baseAddr);
}

/*!
 * @brief Clears the error interrupt status for the eDMA channel or channels.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param enable Enable(true) or Disable (false) error interrupt.
 * @param channel Channel indicator. If kEDMAAllChannel is selected, all channels' error interrupt
 * status will be cleared.
 */
static inline void EDMA_HAL_ClearErrorIntStatusFlag(
                uint32_t baseAddr, edma_channel_indicator_t channel)
{
    HW_DMA_CERR_WR(baseAddr, channel);
}

/*!
 * @brief Enables/Disables the DMA request for the channel or all channels.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param enable Enable(true) or Disable (false) DMA request.
 * @param channel Channel indicator. If kEDMAAllChannel is selected, all channels DMA request
 * are enabled/disabled.
 */
void EDMA_HAL_SetDmaRequestCmd(uint32_t baseAddr, edma_channel_indicator_t channel,bool enable);

/*!
 * @brief Checks whether the eDMA channel DMA request is enabled or disabled.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param channel eDMA channel number.
 * @return DMA request is enabled (true) or disabled (false).
 */
static inline bool EDMA_HAL_GetDmaRequestCmd(uint32_t baseAddr, uint32_t channel)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);

    return ((HW_DMA_ERQ_RD(baseAddr) >> channel) & 1U); 
}

/*!
 * @brief Gets the eDMA channel DMA request status.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param channel eDMA channel number.
 * @return Hardware request is triggered in this eDMA channel (true) or not be triggered in this
 * channel (false). 
 */
static inline bool EDMA_HAL_GetDmaRequestStatusFlag(uint32_t baseAddr, uint32_t channel)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);
    return (((uint32_t)HW_DMA_HRS_RD(baseAddr) >> channel) & 1U); 
}

/*!
 * @brief Clears the done status for a channel or all channels.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param channel Channel indicator. If kEDMAAllChannel is selected, all channels' done status will
 * be cleared. 
 */
static inline void EDMA_HAL_ClearDoneStatusFlag(uint32_t baseAddr, edma_channel_indicator_t channel)
{
    HW_DMA_CDNE_WR(baseAddr, channel);
}

/*!
 * @brief Triggers the eDMA channel.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param channel Channel indicator. If kEDMAAllChannel is selected, all channels are tirggere.
 */
static inline void EDMA_HAL_TriggerChannelStart(uint32_t baseAddr, edma_channel_indicator_t channel)
{
    HW_DMA_SSRT_WR(baseAddr, channel);
}

/*!
 * @brief Gets the eDMA channel interrupt request status.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param channel eDMA channel number.
 * @return Interrupt request happens in this eDMA channel (true) or not happen in this
 * channel (false). 
 */
static inline bool EDMA_HAL_GetIntStatusFlag(uint32_t baseAddr, uint32_t channel)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);

    return (((uint32_t)HW_DMA_INT_RD(baseAddr) >> channel) & 1U); 
}

/*!
 * @brief Gets the eDMA all channel's interrupt request status.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param channel eDMA channel number.
 * @return Interrupt status flag of all channels.
 */
static inline uint32_t EDMA_HAL_GetAllIntStatusFlag(uint32_t baseAddr)
{
    return (uint32_t)HW_DMA_INT_RD(baseAddr);
}

/*!
 * @brief Clears the interrupt status for the eDMA channel or all channels.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param enable Enable(true) or Disable (false) error interrupt.
 * @param channel Channel indicator. If kEDMAAllChannel is selected, all channels' interrupt
 * status will be cleared.
 */
static inline void EDMA_HAL_ClearIntStatusFlag(
                uint32_t baseAddr, edma_channel_indicator_t channel)
{
    HW_DMA_CINT_WR(baseAddr, channel);
}

#if (FSL_FEATURE_EDMA_ASYNCHRO_REQUEST_CHANNEL_COUNT > 0x0U)
/*!
 * @brief Enables/Disables an asynchronous request in stop mode.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param channel eDMA channel number.
 * @param enable Enable (true) or Disable (false) async DMA request.
 */
void EDMA_HAL_SetAsyncRequestInStopModeCmd(uint32_t baseAddr, uint32_t channel, bool enable);
#endif

/* @} */

/*! 
 * @name eDMA HAL driver hardware TCD configuration functions.
 * @{
 */
 
/*!
 * @brief Clears all registers to 0 for the hardware TCD.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param channel eDMA channel number.
 */
void EDMA_HAL_HTCDClearReg(uint32_t baseAddr, uint32_t channel);

/*!
 * @brief Configures the source address for the hardware TCD.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param channel eDMA channel number.
 * @param address The pointer to the source memory address.
 */
static inline void EDMA_HAL_HTCDSetSrcAddr(uint32_t baseAddr, uint32_t channel, uint32_t address)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);
    BW_DMA_TCDn_SADDR_SADDR(baseAddr, channel, address);
}

/*!
 * @brief Configures the source address signed offset for the hardware TCD.
 *
 * Sign-extended offset applied to the current source address to form the next-state value as each
 * source read is complete.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param channel eDMA channel number.
 * @param offset signed-offset for source address.
 */
static inline void EDMA_HAL_HTCDSetSrcOffset(uint32_t baseAddr, uint32_t channel, int16_t offset)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);
    BW_DMA_TCDn_SOFF_SOFF(baseAddr, channel, offset);
}

/*!
 * @brief Configures the transfer attribute for the eDMA channel. 
 *
 * @param baseAddr Register base address for eDMA module.
 * @param channel eDMA channel number.
 * @param srcModulo enumeration type for an allowed source modulo. The value defines a specific address range
 * specified as the value after the SADDR + SOFF calculation is performed on the original register
 * value. Setting this field provides the ability to implement a circular data. For data queues 
 * requiring power-of-2 size bytes, the queue should start at a 0-modulo-size address and the SMOD
 * field should be set to the appropriate value for the queue, freezing the desired number of upper
 * address bits. The value programmed into this field specifies the number of the lower address bits
 * allowed to change. For a circular queue application, the SOFF is typically set to the transfer
 * size to implement post-increment addressing with SMOD function restricting the addresses to a
 * 0-modulo-size range.
 * @param destModulo Enum type for an allowed destination modulo.
 * @param srcTransferSize Enum type for source transfer size.
 * @param destTransferSize Enum type for destination transfer size.
 */
void EDMA_HAL_HTCDSetAttribute(
                uint32_t baseAddr, uint32_t channel,
                edma_modulo_t srcModulo, edma_modulo_t destModulo,
                edma_transfer_size_t srcTransferSize, edma_transfer_size_t destTransferSize);

/*!
 * @brief Configures the nbytes for the eDMA channel.
 *
 * Note here that user need firstly configure the minor loop mapping feature and then call this
 * function.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param channel eDMA channel number.
 * @param nbytes Number of bytes to be transferred in each service request of the channel
 */
void EDMA_HAL_HTCDSetNbytes(uint32_t baseAddr, uint32_t channel, uint32_t nbytes);

/*!
 * @brief Gets the nbytes configuration data for the hardware TCD.
 *
 * This function  decides whether the minor loop mapping is enabled or whether the source/dest
 * minor loop mapping is enabled. Then, the nbytes are returned accordingly.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param channel eDMA channel number.
 * @return nbytes configuration according to minor loop setting.
 */
uint32_t EDMA_HAL_HTCDGetNbytes(uint32_t baseAddr, uint32_t channel);

/*!
 * @brief Configures the minor loop offset for the hardware TCD.
 *
 * Configures both the enable bits and the offset value. If neither source nor destination offset is enabled,
 * offset  is not configured. Note here if source or destination offset is required, the eDMA module
 * EMLM bit will be set in this function. User need to know this side effect.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param channel eDMA channel number.
 * @param config Configuration data structure for the minor loop offset
 */
void EDMA_HAL_HTCDSetMinorLoopOffset(
                uint32_t baseAddr, uint32_t channel, edma_minorloop_offset_config_t *config);

/*!
 * @brief Configures the last source address adjustment for the hardware TCD.
 *
 * Adjustment value added to the source address at the completion of the major iteration count. This
 * value can be applied to restore the source address to the initial value, or adjust the address to
 * reference the next data structure.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param channel eDMA channel number.
 * @param size adjustment value
 */
static inline void EDMA_HAL_HTCDSetSrcLastAdjust(uint32_t baseAddr, uint32_t channel, int32_t size)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);
    BW_DMA_TCDn_SLAST_SLAST(baseAddr, channel, size);
}

/*!
 * @brief Configures the destination address for the hardware TCD.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param channel eDMA channel number.
 * @param address The pointer to the destination address.
 */
static inline void EDMA_HAL_HTCDSetDestAddr(uint32_t baseAddr, uint32_t channel, uint32_t address)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);
    BW_DMA_TCDn_DADDR_DADDR(baseAddr, channel, address);
}

/*!
 * @brief Configures the destination address signed offset for the hardware TCD.
 *
 * Sign-extended offset applied to the current source address to form the next-state value as each
 * destination write is complete.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param channel eDMA channel number.
 * @param offset signed-offset
 */
static inline void EDMA_HAL_HTCDSetDestOffset(uint32_t baseAddr, uint32_t channel, int16_t offset)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);
    BW_DMA_TCDn_DOFF_DOFF(baseAddr, channel, offset);
}

/*!
 * @brief Configures the last source address adjustment.
 *
 * This function adds an adjustment value added to the source address at the completion of the major 
 * iteration count. This value can be applied to restore the source address to the initial value, or 
 * adjust the address to reference the next data structure.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param channel eDMA channel number.
 * @param adjust adjustment value
 */
static inline void EDMA_HAL_HTCDSetDestLastAdjust(
                uint32_t baseAddr, uint32_t channel, uint32_t adjust)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);
    BW_DMA_TCDn_DLASTSGA_DLASTSGA(baseAddr, channel, adjust);
}

/*!
 * @brief Configures the memory address for the next transfer TCD for the hardware TCD.
 *
 *
 * This function enables the scatter/gather feature for the hardware TCD and configures the next
 * TCD's address. This address points to the beginning of a 0-modulo-32 byte region containing 
 * the next transfer TCD to be loaded into this channel. The channel reload is performed as the
 * major iteration count completes. The scatter/gather address must be 0-modulo-32-byte. Otherwise, 
 * a configuration error is reported.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param channel eDMA channel number.
 * @param stcd The pointer to the TCD to be linked to this hardware TCD.
 */
void EDMA_HAL_HTCDSetScatterGatherLink(
                uint32_t baseAddr, uint32_t channel, edma_software_tcd_t *stcd);

/*!
 * @brief Configures the bandwidth for the hardware TCD.
 *
 * Throttles the amount of bus bandwidth consumed by the eDMA. In general, as the eDMA processes the
 * minor loop, it continuously generates read/write sequences until the minor count is exhausted.
 * This field forces the eDMA to stall after the completion of each read/write access to control the
 * bus request bandwidth seen by the crossbar switch.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param channel eDMA channel number.
 * @param bandwidth enum type for bandwidth control
 */
static inline void EDMA_HAL_HTCDSetBandwidth(
                uint32_t baseAddr, uint32_t channel, edma_bandwidth_config_t bandwidth)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);
    BW_DMA_TCDn_CSR_BWC(baseAddr, channel, bandwidth);
}

/*!
 * @brief Configures the major channel link the hardware TCD.
 *
 * If the major link is enabled, after the major loop counter is exhausted, the eDMA engine initiates a
 * channel service request at the channel defined by these six bits by setting that channel start
 * bits.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param channel eDMA channel number.
 * @param majorChannel channel number for major link
 * @param enable Enables (true) or Disables (false) channel major link.
 */
static inline void EDMA_HAL_HTCDSetChannelMajorLink(
                uint32_t baseAddr, uint32_t channel, uint32_t majorChannel, bool enable)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);
    BW_DMA_TCDn_CSR_MAJORLINKCH(baseAddr, channel, majorChannel);
    BW_DMA_TCDn_CSR_MAJORELINK(baseAddr, channel, enable);
}

/*!
 * @brief Gets the major link channel for the hardware TCD.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param channel eDMA channel number.
 * @return major link channel number
 */
static inline uint32_t EDMA_HAL_HTCDGetMajorLinkChannel(uint32_t baseAddr, uint32_t channel)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);
    return BR_DMA_TCDn_CSR_MAJORLINKCH(baseAddr, channel);
}

/*!
 * @brief Enables/Disables the scatter/gather feature for the hardware TCD.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param channel eDMA channel number.
 * @param enable Enables (true) /Disables (false) scatter/gather feature.
 */
static inline void EDMA_HAL_HTCDSetScatterGatherCmd(
                uint32_t baseAddr, uint32_t channel, bool enable)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);
    BW_DMA_TCDn_CSR_ESG(baseAddr, channel, enable);
}

/*!
 * @brief Checks whether the scatter/gather feature is enabled for the hardware TCD.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param channel eDMA channel number.
 * @return True stand for enabled. False stands for disabled. 
 */
static inline bool EDMA_HAL_HTCDGetScatterGatherCmd(uint32_t baseAddr, uint32_t channel)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);
    return BR_DMA_TCDn_CSR_ESG(baseAddr, channel);

}

/*!
 * @brief Disables/Enables the DMA request after the major loop completes for the hardware TCD.
 *
 * If disabled, the eDMA hardware automatically clears the corresponding DMA request when the
 * current major iteration count reaches zero.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param channel eDMA channel number.
 * @param disable Disable (true)/Enable (true) DMA request after TCD complete.
 */
static inline void EDMA_HAL_HTCDSetDisableDmaRequestAfterTCDDoneCmd(
                uint32_t baseAddr, uint32_t channel, bool disable)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);
    BW_DMA_TCDn_CSR_DREQ(baseAddr, channel, disable);
}  

/*!
 * @brief Enables/Disables the half complete interrupt for the hardware TCD.
 *
 * If set, the channel generates an interrupt request by setting the appropriate bit in the
 * interrupt register when the current major iteration count reaches the halfway point. Specifically,
 * the comparison performed by the eDMA engine is (CITER == (BITER >> 1)). This half-way point
 * interrupt request is provided to support the double-buffered schemes or other types of data movement
 * where the processor needs an early indication of the transfer's process.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param channel eDMA channel number.
 * @param enable Enable (true) /Disable (false) half complete interrupt.
 */
static inline void EDMA_HAL_HTCDSetHalfCompleteIntCmd(
                uint32_t baseAddr, uint32_t channel, bool enable) 
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);
    BW_DMA_TCDn_CSR_INTHALF(baseAddr, channel, enable);
}

/*!
 * @brief Enables/Disables the interrupt after the major loop completes for the hardware TCD.
 *
 * If enabled, the channel generates an interrupt request by setting the appropriate bit in the 
 * interrupt register when the current major iteration count reaches zero.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param channel eDMA channel number.
 * @param enable Enable (true) /Disable (false) interrupt after TCD done.
 */
static inline void EDMA_HAL_HTCDSetIntCmd(
                uint32_t baseAddr, uint32_t channel, bool enable)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);
    BW_DMA_TCDn_CSR_INTMAJOR(baseAddr, channel, enable);
}

/*!
 * @brief Triggers the start bits for the hardware TCD.
 *
 * The eDMA hardware automatically clears this flag after the channel begins execution.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param channel eDMA channel number.
 */
static inline void EDMA_HAL_HTCDTriggerChannelStart(uint32_t baseAddr, uint32_t channel)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);
    BW_DMA_TCDn_CSR_START(baseAddr, channel, true); 
}

/*!
 * @brief Checks whether the channel is running for the hardware TCD.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param channel eDMA channel number.
 * @return True stands for running. False stands for not. 
 */
static inline bool EDMA_HAL_HTCDGetChannelActiveStatus(uint32_t baseAddr, uint32_t channel)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);
    return BR_DMA_TCDn_CSR_ACTIVE(baseAddr, channel); 
}

/*!
 * @brief Sets the channel minor link for the hardware TCD.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param channel eDMA channel number.
 * @param linkChannel Channel to be linked on minor loop complete.
 * @param enable Enable (true)/Disable (false) channel minor link.
 */
void EDMA_HAL_HTCDSetChannelMinorLink(
                uint32_t baseAddr, uint32_t channel, uint32_t linkChannel, bool enable);

/*!
 * @brief Sets the major iteration count according to minor loop channel link setting.
 *
 * Note here that user need to first set the minor loop channel link and then call this function.
 * The execute flow inside this function is dependent on the minor loop channel link setting.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param channel eDMA channel number.
 * @param count major loop count
 */
void EDMA_HAL_HTCDSetMajorCount(uint32_t baseAddr, uint32_t channel, uint32_t count);

/*!
 * @brief Gets the number of beginning major counts for the hardware TCD.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param channel eDMA channel number.
 * @return Begin major counts.
 */
uint32_t EDMA_HAL_HTCDGetBeginMajorCount(uint32_t baseAddr, uint32_t channel);

/*!
 * @brief Gets the number of current major counts for the hardware TCD.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param channel eDMA channel number.
 * @return Current major counts.
 */
uint32_t EDMA_HAL_HTCDGetCurrentMajorCount(uint32_t baseAddr, uint32_t channel);

/*!
 * @brief Gets the number of bytes already transferred for the hardware TCD.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param channel eDMA channel number.
 * @return data bytes already transferred
 */
uint32_t EDMA_HAL_HTCDGetFinishedBytes(uint32_t baseAddr, uint32_t channel);

/*!
 * @brief Gets the number of bytes haven't transferred for the hardware TCD.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param channel eDMA channel number.
 * @return data bytes already transferred
 */
uint32_t EDMA_HAL_HTCDGetUnfinishedBytes(uint32_t baseAddr, uint32_t channel);

/*!
 * @brief Gets the channel done status.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param channel eDMA channel number.
 * @return If channel done.
 */
static inline bool EDMA_HAL_HTCDGetDoneStatusFlag(uint32_t baseAddr, uint32_t channel)
{
    return BR_DMA_TCDn_CSR_DONE(baseAddr,channel);
}

/* @} */

/*!
 * @name EDMA HAL driver software TCD configuration functions.
 * @{
 */
/*!
 * @brief Configures the source address for the software TCD.
 *
 * @param stcd The pointer to the software TCD.
 * @param channel eDMA channel number.
 * @param address The pointer to the source memory address.
 */
static inline void EDMA_HAL_STCDSetSrcAddr(edma_software_tcd_t *stcd, uint32_t address)
{
    assert(stcd);
    stcd->SADDR = DMA_SADDR_SADDR(address); 
}

/*!
 * @brief Configures the source address signed offset for the software TCD.
 *
 * Sign-extended offset applied to the current source address to form the next-state value as each
 * source read is complete.
 *
 * @param stcd The pointer to the software TCD.
 * @param offset signed-offset for source address.
 */
static inline void EDMA_HAL_STCDSetSrcOffset(edma_software_tcd_t *stcd, int16_t offset)
{
    assert(stcd);
    stcd->SOFF = DMA_SOFF_SOFF(offset);
}

/*!
 * @brief Configures the transfer attribute for software TCD. 
 *
 * @param stcd The pointer to the software TCD.
 * @param srcModulo enum type for an allowed source modulo. The value defines a specific address range
 * specified as the value after the SADDR + SOFF calculation is performed on the original register
 * value. Setting this field provides the ability to implement a circular data. For data queues 
 * requiring power-of-2 size bytes, the queue should start at a 0-modulo-size address and the SMOD
 * field should be set to the appropriate value for the queue, freezing the desired number of upper
 * address bits. The value programmed into this field specifies the number of the lower address bits
 * allowed to change. For a circular queue application, the SOFF is typically set to the transfer
 * size to implement post-increment addressing with SMOD function restricting the addresses to a
 * 0-modulo-size range.
 * @param destModulo Enum type for an allowed destination modulo.
 * @param srcTransferSize Enum type for source transfer size.
 * @param destTransferSize Enum type for destinatio transfer size.
 */
void EDMA_HAL_STCDSetAttribute(
                edma_software_tcd_t *stcd,
                edma_modulo_t srcModulo, edma_modulo_t destModulo,
                edma_transfer_size_t srcTransferSize, edma_transfer_size_t destTransferSize);

/*!
 * @brief Configures the nbytes for software TCD.
 *
 * Note here that user need firstly configure the minor loop mapping feature and then call this
 * function.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param stcd The pointer to the software TCD.
 * @param nbytes Number of bytes to be transferred in each service request of the channel
 */
void EDMA_HAL_STCDSetNbytes(uint32_t baseAddr, edma_software_tcd_t *stcd, uint32_t nbytes);

/*!
 * @brief Configures the minorloop offset for the software TCD.
 *
 * Configures both the enable bits and the offset value. If neither source nor dest offset is enabled,
 * offset  is not configured. Note here if source or destination offset is requred, the eDMA module
 * EMLM bit will be set in this function. User need to know this side effect.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param stcd The pointer to the software TCD.
 * @param config Configuration data structure for the minorloop offset
 */
void EDMA_HAL_STCDSetMinorLoopOffset(
            uint32_t baseAddr, edma_software_tcd_t *stcd, edma_minorloop_offset_config_t *config);

/*!
 * @brief Configures the last source address adjustment for the software TCD.
 *
 * Adjustment value added to the source address at the completion of the major iteration count. This
 * value can be applied to restore the source address to the initial value, or adjust the address to
 * reference the next data structure.
 *
 * @param stcd The pointer to the software TCD.
 * @param size adjustment value
 */
static inline void EDMA_HAL_STCDSetSrcLastAdjust(edma_software_tcd_t *stcd, int32_t size)
{
    assert(stcd);
    stcd->SLAST = (stcd->SLAST & ~DMA_SLAST_SLAST_MASK) | DMA_SLAST_SLAST(size);
}

/*!
 * @brief Configures the destination address for the software TCD.
 *
 * @param stcd The pointer to the software TCD.
 * @param address The pointer to the destination addresss.
 */
static inline void EDMA_HAL_STCDSetDestAddr(edma_software_tcd_t *stcd, uint32_t address)
{
    assert(stcd);
    stcd->DADDR = DMA_DADDR_DADDR(address); 
}

/*!
 * @brief Configures the destination address signed offset for the software TCD.
 *
 * Sign-extended offset applied to the current source address to form the next-state value as each
 * destination write is complete.
 *
 * @param stcd The pointer to the software TCD.
 * @param offset signed-offset
 */
static inline void EDMA_HAL_STCDSetDestOffset(edma_software_tcd_t *stcd, int16_t offset)
{
    assert(stcd);
    stcd->DOFF = DMA_DOFF_DOFF(offset);
}

/*!
 * @brief Configures the last source address adjustment.
 *
 * This function add an adjustment value added to the source address at the completion of the major 
 * iteration count. This value can be applied to restore the source address to the initial value, or 
 * adjust the address to reference the next data structure.
 *
 * @param stcd The pointer to the software TCD.
 * @param adjust adjustment value
 */
static inline void EDMA_HAL_STCDSetDestLastAdjust(
                edma_software_tcd_t *stcd, uint32_t adjust)
{
    assert(stcd);
    stcd->DLAST_SGA = DMA_DLAST_SGA_DLASTSGA(adjust);
}

/*!
 * @brief Configures the memory address for the next transfer TCD for the software TCD.
 *
 *
 * This function enable the scatter/gather feature for the software TCD and configure the next
 * TCD's address.This address points to the beginning of a 0-modulo-32 byte region containing 
 * the next transfer TCD to be loaded into this channel. The channel reload is performed as the
 * major iteration count completes. The scatter/gather address must be 0-modulo-32-byte. Otherwise, 
 * a configuration error is reported.
 *
 * @param stcd The pointer to the software TCD.
 * @param nextStcd The pointer to the TCD to be linked to this software TCD.
 */
void EDMA_HAL_STCDSetScatterGatherLink(
                edma_software_tcd_t *stcd, edma_software_tcd_t *nextStcd);

/*!
 * @brief Configures the bandwidth for the software TCD.
 *
 * Throttles the amount of bus bandwidth consumed by the eDMA. In general, as the eDMA processes the
 * minor loop, it continuously generates read/write sequences until the minor count is exhausted.
 * This field forces the eDMA to stall after the completion of each read/write access to control the
 * bus request bandwidth seen by the crossbar switch.
 *
 * @param stcd The pointer to the software TCD.
 * @param bandwidth enum type for bandwidth control
 */
static inline void EDMA_HAL_STCDSetBandwidth(
                edma_software_tcd_t *stcd, edma_bandwidth_config_t bandwidth)
{
    assert(stcd);
    stcd->CSR = (stcd->CSR & ~DMA_CSR_BWC_MASK) | DMA_CSR_BWC(bandwidth);
}

/*!
 * @brief Configures the major channel link the software TCD.
 *
 * If the majorlink is enabled, after the major loop counter is exhausted, the eDMA engine initiates a
 * channel service request at the channel defined by these six bits by setting that channel start
 * bits.
 *
 * @param stcd The pointer to the software TCD.
 * @param majorChannel channel number for major link
 * @param enable Enables (true) or Disables (false) channel major link.
 */
static inline void EDMA_HAL_STCDSetChannelMajorLink(
                edma_software_tcd_t *stcd, uint32_t majorChannel, bool enable)
{
    assert(stcd);
    stcd->CSR = (stcd->CSR & ~DMA_CSR_MAJORLINKCH_MASK) | DMA_CSR_MAJORLINKCH(majorChannel);
    stcd->CSR = (stcd->CSR & ~DMA_CSR_MAJORELINK_MASK) |
                         ((uint32_t)enable << DMA_CSR_MAJORELINK_SHIFT);
}


/*!
 * @brief Enables/Disables the scatter/gather feature for the software TCD.
 *
 * @param stcd The pointer to the software TCD.
 * @param enable Enables (true) /Disables (false) scatter/gather feature.
 */
static inline void EDMA_HAL_STCDSetScatterGatherCmd(
                edma_software_tcd_t *stcd, bool enable)
{
    assert(stcd);
    stcd->CSR = (stcd->CSR & ~DMA_CSR_ESG_MASK) | ((uint32_t)enable << DMA_CSR_ESG_SHIFT);
}


/*!
 * @brief Disables/Enables the DMA request after the major loop completes for the software TCD.
 *
 * If disabled, the eDMA hardware automatically clears the corresponding DMA request when the
 * current major iteration count reaches zero.
 *
 * @param stcd The pointer to the software TCD.
 * @param disable Disable (true)/Enable (true) dma request after TCD complete.
 */
static inline void EDMA_HAL_STCDSetDisableDmaRequestAfterTCDDoneCmd(
                edma_software_tcd_t *stcd, bool disable)
{
    assert(stcd);
    stcd->CSR = (stcd->CSR & ~DMA_CSR_DREQ_MASK) | ((uint32_t)disable << DMA_CSR_DREQ_SHIFT);
}  

/*!
 * @brief Enables/Disables the half complete interrupt for the software TCD.
 *
 * If set, the channel generates an interrupt request by setting the appropriate bit in the
 * interrupt register when the current major iteration count reaches the halfway point. Specifically,
 * the comparison performed by the eDMA engine is (CITER == (BITER >> 1)). This half-way point
 * interrupt request is provided to support the double-buffered schemes or other types of data movement
 * where the processor needs an early indication of the transfer's process.
 *
 * @param stcd The pointer to the software TCD.
 * @param enable Enable (true) /Disable (false) half complete interrupt.
 */
static inline void EDMA_HAL_STCDSetHalfCompleteIntCmd(
                edma_software_tcd_t *stcd, bool enable) 
{
    assert(stcd);
    stcd->CSR = (stcd->CSR & ~DMA_CSR_INTHALF_MASK) | ((uint32_t)enable << DMA_CSR_INTHALF_SHIFT);
}

/*!
 * @brief Enables/Disables the interrupt after the major loop completes for the software TCD.
 *
 * If enabled, the channel generates an interrupt request by setting the appropriate bit in the 
 * interrupt register when the current major iteration count reaches zero.
 *
 * @param stcd The pointer to the software TCD.
 * @param enable Enable (true) /Disable (false) interrupt after TCD done.
 */
static inline void EDMA_HAL_STCDSetIntCmd(edma_software_tcd_t *stcd, bool enable)
{
    assert(stcd);
    stcd->CSR = (stcd->CSR & ~DMA_CSR_INTMAJOR_MASK) | ((uint32_t)enable << DMA_CSR_INTMAJOR_SHIFT);
}

/*!
 * @brief Triggers the start bits for the software TCD.
 *
 * The eDMA hardware automatically clears this flag after the channel begins execution.
 *
 * @param stcd The pointer to the software TCD.
 */
static inline void EDMA_HAL_STCDTriggerChannelStart(edma_software_tcd_t *stcd)
{
    assert(stcd);
    stcd->CSR |= DMA_CSR_START_MASK;
}

/*!
 * @brief Set Channel minor link for software TCD.
 *
 * @param stcd The pointer to the software TCD.
 * @param linkChannel Channel to be linked on minor loop complete.
 * @param enable Enable (true)/Disable (false) channel minor link.
 */
void EDMA_HAL_STCDSetChannelMinorLink(
                edma_software_tcd_t *stcd, uint32_t linkChannel, bool enable);

/*!
 * @brief Sets the major iteration count according to minor loop channel link setting.
 *
 * Note here that user need to first set the minor loop channel link and then call this function.
 * The execute flow inside this function is dependent on the minor loop channel link setting.
 *
 * @param stcd The pointer to the software TCD.
 * @param count major loop count
 */
void EDMA_HAL_STCDSetMajorCount(edma_software_tcd_t *stcd, uint32_t count);

/*!
 * @brief Copy the software TCD configuration to the hardware TCD.
 *
 * @param baseAddr Register base address for eDMA module.
 * @param channel eDMA channel number.
 * @param stcd The pointer to the software TCD.
 */
void EDMA_HAL_PushSTCDToHTCD(uint32_t baseAddr, uint32_t channel, edma_software_tcd_t *stcd);

/*!
 * @brief Set the basic transfer for software TCD.
 *
 * This function is used to setup the basic transfer for software TCD. The minor loop setting is not
 * involved here cause minor loop's configuration will lay a impact on the global eDMA setting. And
 * the source minor loop offset is relevant to the dest minor loop offset. For these reasons, minor
 * loop offset configuration is treated as an advanced configuration. User can call the
 * EDMA_HAL_STCDSetMinorLoopOffset() to configure the minor loop offset feature.
 *
 * @param baseAddr Register base address for eDMA module. 
 * @param stcd The pointer to the software TCD.
 * @param config The pointer to the transfer configuration structure.
 * @param enableInt Enables (true) or Disables (false) interrupt on TCD complete.
 * @param disableDmaRequest Disables (true) or Enable (false) dma request on TCD complete.
 */
edma_status_t EDMA_HAL_STCDSetBasicTransfer(
            uint32_t baseAddr, edma_software_tcd_t *stcd, edma_transfer_config_t *config,
            bool enableInt, bool disableDmaRequest);


/* @} */


#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* __EDMA_HAL_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/


