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

#ifndef __FSL_SAI_HAL_H__
#define __FSL_SAI_HAL_H__


#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_device_registers.h"
#include "fsl_sai_features.h"


/*!
 * @addtogroup sai_hal
 * @{
 */
 
/*! @file */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Define the bit limits of in a word*/
#define SAI_BIT_MIN	8
#define SAI_BIT_MAX	32

/* Define the max div and fract value for master clock divider. */
#define SAI_FRACT_MAX	256
#define SAI_DIV_MAX		4096

/*! @brief Define the bus type of sai */
typedef enum _sai_protocol
{
    kSaiBusI2SLeft = 0x0,
    kSaiBusI2SRight = 0x1,
    kSaiBusI2SType = 0x2,
    kSaiBusPCMA = 0x3,
    kSaiBusPCMB = 0x4,
    kSaiBusAC97 = 0x5
 } sai_protocol_t;

/*! @brief Master or slave mode */
typedef enum _sai_master_slave
{
    kSaiMaster = 0x0,/*!< Master mode */
    kSaiSlave = 0x1/*!< Slave mode */
} sai_master_slave_t;

/*! @brief Polarity of SAI clock. */
typedef enum _sai_clk_polarity
{
    kSaiClkPolarityHigh = 0x0, /*!< Clock active high */
    kSaiClkPolarityLow = 0x1 /*!< Clock active low */
} sai_clk_polarity_t;

/*! @brief Clock generate direction. */
typedef enum _sai_clk_direction
{
    kSaiClkInternal = 0x0, /*!< Clock generated internal. */
    kSaiClkExternal = 0x1 /*!< Clock generated external. */
} sai_clk_direction_t;

/*! @brief Data transfer polarity, means MSB first of LSB first.*/
typedef enum _sai_data_order
{
    kSaiLSBFirst = 0x0, /*!< Least significant bit transferred first. */
    kSaiMSBFirst = 0x1 /*!< Most significant bit transferred first. */
} sai_data_order_t;

/*! @brief Synchronous or asynchronous mode */
typedef enum _sai_sync_mode
{
    kSaiModeAsync = 0x0,/*!< Asynchronous mode */
    kSaiModeSync = 0x1,/*!< Synchronous mode (with receiver or transmit) */
    kSaiModeSyncWithOtherTx = 0x2,/*!< Synchronous with another SAI transmit */
    kSaiModeSyncWithOtherRx = 0x3/*!< Synchronous with another SAI receiver */
} sai_sync_mode_t;

/*! @brief Mater clock source */
typedef enum _sai_mclk_source
{
    kSaiMclkSourceSysclk = 0x0,/*!< Master clock from the system clock */
    kSaiMclkSourceSelect1 = 0x1,/*!< Master clock from source 1 */
    kSaiMclkSourceSelect2 = 0x2,/*!< Master clock from source 2 */
    kSaiMclkSourceSelect3 = 0x3/*!< Master clock from source 3 */ 
} sai_mclk_source_t;

/*! @brief Bit clock source */
typedef enum _sai_bclk_source
{
    kSaiBclkSourceBusclk = 0x0,/*!< Bit clock using bus clock */
    kSaiBclkSourceMclkDiv = 0x1,/*!< Bit clock using master clock divider */
    kSaiBclkSourceOtherSai0 = 0x2,/*!< Bit clock from other SAI device */
    kSaiBclkSourceOtherSai1 = 0x3/*!< Bit clock from other SAI device */
} sai_bclk_source_t;

/*! @brief The SAI state flag. */
typedef enum _sai_interrupt_request
{
    kSaiIntrequestWordStart = 0x0,/*!< Word start flag, means the first word in a frame detected */
    kSaiIntrequestSyncError = 0x1,/*!< Sync error flag, means the sync error is detected */
    kSaiIntrequestFIFOWarning = 0x2,/*!< FIFO warning flag, means the FIFO is empty */
    kSaiIntrequestFIFOError = 0x3,/*!< FIFO error flag */
    kSaiIntrequestFIFORequest = 0x4/*!< FIFO request, means reached watermark */
} sai_interrupt_request_t;


/*! @brief The DMA request sources */
typedef enum _sai_dma_request
{
    kSaiDmaReqFIFOWarning = 0x0,/*!< FIFO warning caused by the DMA request */
    kSaiDmaReqFIFORequest = 0x1/*!< FIFO request caused by the DMA request */
} sai_dma_request_t;

/*! @brief The SAI state flag */
typedef enum _sai_state_flag
{
    kSaiStateFlagWordStart = 0x0,/*!< Word start flag, means the first word in a frame detected. */
    kSaiStateFlagSyncError = 0x1,/*!< Sync error flag, means the sync error is detected */
    kSaiStateFlagFIFOError = 0x2,/*!< FIFO error flag */
    kSaiStateFlagFIFORequest = 0x3,
    kSaiStateFlagFIFOWarning = 0x4,
    kSaiStateFlagSoftReset = 0x5 /*!< Software reset flag */
} sai_state_flag_t;

/*! @brief The reset type */
typedef enum _sai_reset_type
{
    kSaiResetTypeSoftware = 0x0,/*!< Software reset, reset the logic state */
    kSaiResetTypeFIFO = 0x1/*!< FIFO reset, reset the FIFO read and write pointer */
} sai_reset_type_t;

/*
 * @brief The SAI running mode
 * The mode includes normal mode, debug mode, and stop mode.
 */
typedef enum _sai_running_mode
{
    kSaiRunModeDebug = 0x0,/*!< In debug mode */ 
    kSaiRunModeStop = 0x1/*!< In stop mode */
} sai_run_mode_t;

#if FSL_FEATURE_SAI_HAS_FIFO_PACKING

/*
 * @brief The SAI packing mode
 * The mode includes 8 bit and 16 bit packing.
 */
typedef enum _sai_fifo_packing
{
    kSaiFifoPackingDisabled = 0x0, /*!< Packing disabled. */
    kSaiFifoPacking8bit = 0x2,/*!< 8 bit packing enabled. */
    kSaiFifoPacking16bit = 0x3 /*!< 16bit packing enabled. */
} sai_fifo_packing_t;

#endif

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
* @name Module control
* @{
*/

/*!
 * @brief  Initializes the SAI Tx.
 *
 * The initialization resets the SAI module by setting the SR bit of TCSR register.
 * Note that the function writes 0 to every control registers.
 * @param saiBaseAddr Register base address of SAI module.
 */
void SAI_HAL_TxInit(uint32_t saiBaseAddr);

/*!
 * @brief  Initializes the SAI Rx.
 *
 * The initialization resets the SAI module by setting the SR bit of RCSR register.
 * Note that the function writes 0 to every control registers.
 * @param saiBaseAddr Register base address of SAI module.
 */
void SAI_HAL_RxInit(uint32_t saiBaseAddr);

/*!
 * @brief Sets Tx protocol relevant settings.
 *
 * The bus mode means which protocol SAI uses. It can be I2S left, right and so on. Each protocol
 * has a different configuration on bit clock and frame sync.
 * @param saiBaseAddr Register base address of SAI module.
 * @param protocol The protocol selection. It can be I2S left aligned, I2S right aligned, etc.
 */
void SAI_HAL_TxSetProtocol(uint32_t saiBaseAddr, sai_protocol_t protocol);

/*!
 * @brief Sets Rx protocol relevant settings.
 *
 * The bus mode means which protocol SAI uses. It can be I2S left, right and so on. Each protocol
 * has a different configuration on bit clock and frame sync.
 * @param saiBaseAddr Register base address of SAI module.
 * @param protocol The protocol selection. It can be I2S left aligned, I2S right aligned, etc.
 */
void SAI_HAL_RxSetProtocol(uint32_t saiBaseAddr, sai_protocol_t protocol);

/*!
 * @brief Sets master or slave mode.
 *
 * The function determines master or slave mode. Master mode  provides its
 * own clock and slave mode  uses an external clock.
 * @param saiBaseAddr Register base address of SAI module.
 * @param master_slave_mode Mater or slave mode.
 */
void SAI_HAL_TxSetMasterSlave(uint32_t saiBaseAddr, sai_master_slave_t master_slave_mode);

/*!
 * @brief Sets master or slave mode.
 *
 * The function determines master or slave mode. Master mode provides its
 * own clock and slave mode  uses external clock.
 * @param saiBaseAddr Register base address of SAI module.
 * @param master_slave_mode Mater or slave mode.
 */
void SAI_HAL_RxSetMasterSlave(uint32_t saiBaseAddr, sai_master_slave_t master_slave_mode);

/*! @}*/

/*!
* @name Master clock configuration
* @{
*/

/*!
 * @brief Sets the master clock source.
 *
 * The source of the clock is different from socs.
 * This function sets the clock source for SAI master clock source.
 * Master clock is used to produce the bit clock for the data transfer.
 * @param saiBaseAddr Register base address of SAI module.
 * @param source Mater clock source
 */
static inline void SAI_HAL_SetMclkSrc(uint32_t saiBaseAddr, sai_mclk_source_t source)
{
    BW_I2S_MCR_MICS(saiBaseAddr,source);
}

/*!
 * @brief Gets the master clock source.
 *
 * The source of the clock is different from socs.
 * This function gets the clock source for SAI master clock source.
 * Master clock is used to produce the bit clock for the data transfer.
 * @param saiBaseAddr Register base address of SAI module.
 * @return Mater clock source
 */
static inline uint32_t SAI_HAL_GetMclkSrc(uint32_t saiBaseAddr)
{
    return BR_I2S_MCR_MICS(saiBaseAddr);
}

/*!
 * @brief Sets the direction of the SAI master clock.
 * 
 * This function would decides the direction of bit clock generated.
 * @param saiBaseAddr Register base address of SAI module.
 * @param enable True means enable, false means disable.
 */
static inline void SAI_HAL_SetMclkDividerCmd(uint32_t saiBaseAddr, bool enable)
{
    BW_I2S_MCR_MOE(saiBaseAddr,enable);
}

/*!
 * @brief Sets the divider of the master clock.
 *
 * Using the divider to get the master clock frequency wanted from the source. 
 * mclk = clk_source * fract/divide. The input is the master clock frequency needed and the source clock frequency.
 * The master clock is decided by the sample rate and the multi-clock number.
 * Notice that mclk should less than src_clk, or it would do hang as the HW refuses to write in this situation.
 * @param saiBaseAddr Register base address of SAI module.
 * @param mclk Master clock frequency needed.
 * @param src_clk The source clock frequency.
 */
void SAI_HAL_SetMclkDiv(uint32_t saiBaseAddr, uint32_t mclk, uint32_t src_clk);

/*!
 * @brief Flag to see if the master clock divider is re-divided.
 * @param saiBaseAddr Register base address of SAI module.
 * @return True if the divider updated otherwise false.
 */
static inline bool SAI_HAL_GetMclkDivUpdatingCmd(uint32_t saiBaseAddr)
{
    return BR_I2S_MCR_DUF(saiBaseAddr);
}

/*! @}*/

/*!
* @name Bit clock configuration
* @{
*/

/*!
 * @brief Sets the bit clock source of Tx. It is generated by the master clock, bus clock and other devices.
 *
 * The function sets the source of the bit clock. The bit clock can be produced by the master
 * clock and from the bus clock or other SAI Tx/Rx. Tx and Rx in the SAI module use the same bit 
 * clock either from Tx or Rx.
 * @param saiBaseAddr Register base address of SAI module.
 * @param source Bit clock source.
 */
static inline void SAI_HAL_TxSetBclkSrc(uint32_t saiBaseAddr, sai_bclk_source_t source)
{
    BW_I2S_TCR2_MSEL(saiBaseAddr,source);
}

/*!
 * @brief Sets bit clock source of the Rx. It is generated by the master clock, bus clock and other devices.
 *
 * The function sets the source of the bit clock. The bit clock can be produced by the master
 * clock, and from the bus clock or other SAI Tx/Rx. Tx and Rx in the SAI module use the same bit 
 * clock either from Tx or Rx.
 * @param saiBaseAddr Register base address of SAI module.
 * @param source Bit clock source.
 */
static inline void SAI_HAL_RxSetBclkSrc(uint32_t saiBaseAddr, sai_bclk_source_t source)
{
    BW_I2S_RCR2_MSEL(saiBaseAddr,source);
}

/*!
 * @brief Gets the bit clock source of Tx. It is generated by the master clock, bus clock and other devices.
 *
 * The function gets the source of the bit clock. The bit clock can be produced by the master
 * clock and from the bus clock or other SAI Tx/Rx. Tx and Rx in the SAI module use the same bit 
 * clock either from Tx or Rx.
 * @param saiBaseAddr Register base address of SAI module.
 * @return Bit clock source.
 */
static inline uint32_t SAI_HAL_TxGetBclkSrc(uint32_t saiBaseAddr)
{
    return BR_I2S_TCR2_MSEL(saiBaseAddr);
}

/*!
 * @brief Gets bit clock source of the Rx. It is generated by the master clock, bus clock and other devices.
 *
 * The function gets the source of the bit clock. The bit clock can be produced by the master
 * clock, and from the bus clock or other SAI Tx/Rx. Tx and Rx in the SAI module use the same bit 
 * clock either from Tx or Rx.
 * @param saiBaseAddr Register base address of SAI module.
 * @return Bit clock source.
 */
static inline uint32_t SAI_HAL_RxGetBclkSrc(uint32_t saiBaseAddr)
{
    return BR_I2S_RCR2_MSEL(saiBaseAddr);
}

/*!
 * @brief Sets the Tx bit clock divider value.
 *
 * bclk = mclk / divider. At the same time, bclk = sample_rate * channel * bits. This means
 * how much time is needed to transfer one bit.
 * Notice: The function is called while the bit clock source is the master clock.
 * @param saiBaseAddr Register base address of SAI module.
 * @param divider The divide number of bit clock.
 */
static inline void SAI_HAL_TxSetBclkDiv(uint32_t saiBaseAddr, uint32_t divider)
{
    BW_I2S_TCR2_DIV(saiBaseAddr,divider/2 -1);
}

/*!
 * @brief Sets the Rx bit clock divider value.
 *
 * bclk = mclk / divider. At the same time, bclk = sample_rate * channel * bits. This means
 * how much time is needed to transfer one bit.
 * Notice: The function is called while the bit clock source is the master clock.
 * @param saiBaseAddr Register base address of SAI module.
 * @param divider The divide number of bit clock.
 */
static inline void SAI_HAL_RxSetBclkDiv(uint32_t saiBaseAddr, uint32_t divider)
{
    BW_I2S_RCR2_DIV(saiBaseAddr,divider/2 -1);
}

/*!
 * @brief Enables or disables the Tx  bit clock.
 * 
 * @param saiBaseAddr Register base address of SAI module.
 * @param enable True means enable, false means disable.
 */
static inline void SAI_HAL_TxSetBclkCmd(uint32_t saiBaseAddr, bool enable)
{
    BW_I2S_TCSR_BCE(saiBaseAddr,enable);
}

/*!
 * @brief Enables or disables the Rx bit clock.
 * 
 * @param saiBaseAddr Register base address of SAI module.
 * @param enable True means enable, false means disable.
 */
static inline void SAI_HAL_RxSetBclkCmd(uint32_t saiBaseAddr, bool enable)
{
    BW_I2S_RCSR_BCE(saiBaseAddr, enable);
}

/*!
 * @brief Enables or disables the Tx bit clock input bit.
 * 
 * @param saiBaseAddr Register base address of SAI module.
 * @param enable True means enable, false means disable.
 */
static inline void SAI_HAL_TxSetBclkInputCmd(uint32_t saiBaseAddr, bool enable)
{
    BW_I2S_TCR2_BCI(saiBaseAddr,enable);
}

/*!
 * @brief Enables or disables the Rx bit clock input bit.
 * 
 * @param saiBaseAddr Register base address of SAI module.
 * @param enable True means enable, false means disable.
 */
static inline void SAI_HAL_RxSetBclkInputCmd(uint32_t saiBaseAddr, bool enable)
{
    BW_I2S_RCR2_BCI(saiBaseAddr,enable);
}

/*!
 * @brief Sets the Tx bit clock swap.
 *
 * This field swaps the bit clock used by the transmitter. When the transmitter is configured in 
 * asynchronous mode and this bit is set, the transmitter is clocked by the receiver bit clock. 
 * This allows the transmitter and receiver to share the same bit clock, but the transmitter 
 * continues to use the transmit frame sync (SAI_TX_SYNC).
 * When the transmitter is configured in synchronous mode, the transmitter BCS field and receiver
 * BCS field must be set to the same value. When both are set, the transmitter and receiver are both
 * clocked by the transmitter bit clock (SAI_TX_BCLK) but use the receiver frame sync (SAI_RX_SYNC).
 * @param saiBaseAddr Register base address of SAI module.
 * @param enable True means swap bit closk, false means no swap.
 */
static inline void SAI_HAL_TxSetSwapBclkCmd(uint32_t saiBaseAddr, bool enable)
{
    BW_I2S_TCR2_BCS(saiBaseAddr,enable);
}

/*!
 * @brief Sets the Rx bit clock swap.
 *
 * This field swaps the bit clock used by the receiver. When the receiver is configured in 
 * asynchronous mode and this bit is set, the receiver is clocked by the transmitter bit clock
 * (SAI_TX_BCLK). This allows the transmitter and receiver to share the same bit clock, but the 
 * receiver continues to use the receiver frame sync (SAI_RX_SYNC). 
 * When the receiver is configured in synchronous mode, the transmitter BCS field and receiver BCS 
 * field must be set to the same value. When both are set, the transmitter and receiver are both 
 * clocked by the receiver bit clock (SAI_RX_BCLK) but use the transmitter frame sync (SAI_TX_SYNC).
 * @param saiBaseAddr Register base address of SAI module.
 * @param enable True means swap bit closk, false means no swap.
 */
static inline void SAI_HAL_RxSetSwapBclkCmd(uint32_t saiBaseAddr, bool enable)
{
    BW_I2S_RCR2_BCS(saiBaseAddr, enable);
}

/*!
 * @brief Sets the direction of the Tx SAI bit clock.
 * 
 * This function sets the direction of the bit clock generated.
 * @param saiBaseAddr Register base address of SAI module.
 * @param direction Bit clock generated internal or external.
 */
static inline void SAI_HAL_TxSetBclkDir(uint32_t saiBaseAddr,  sai_clk_direction_t direction)
{
    BW_I2S_TCR2_BCD(saiBaseAddr,direction);
}

/*!
 * @brief Sets the direction of the Rx SAI bit clock.
 * 
 * This function sets the direction of the  bit clock generated.
 * @param saiBaseAddr Register base address of SAI module.
 * @param direction Bit clock generated internal or external.
 */
static inline void SAI_HAL_RxSetBclkDir(uint32_t saiBaseAddr, sai_clk_direction_t direction)
{
    BW_I2S_RCR2_BCD(saiBaseAddr,direction);
}

/*!
 * @brief Sets the polarity of the Tx SAI bit clock.
 *
 * @param saiBaseAddr Register base address of SAI module.
 * @param pol Polarity of the SAI bit clock, which can be configured to active high or low.
 */
static inline void SAI_HAL_TxSetBclkPolarity(uint32_t saiBaseAddr, sai_clk_polarity_t pol)
{
    BW_I2S_TCR2_BCP(saiBaseAddr, pol);
}

/*!
 * @brief Sets the polarity of the Rx SAI bit clock.
 *
 * @param saiBaseAddr Register base address of SAI module.
 * @param pol Polarity of SAI bit clock, which can be configured to active high or low.
 */
static inline void SAI_HAL_RxSetBclkPolarity(uint32_t saiBaseAddr, sai_clk_polarity_t pol)
{
    BW_I2S_RCR2_BCP(saiBaseAddr, pol);
}
/*! @} */

/*!
* @name Frame sync configuration
* @{
*/

/*!
 * @brief Sets the Tx frame size. 
 *
 * The frame size means how many words are in a frame. For example 2-channel
 * audio data, the frame size is 2, which means 2 words in a frame.
 * @param saiBaseAddr Register base address of SAI module.
 * @param size Words number in a frame.
 */
static inline void SAI_HAL_TxSetFrameSize(uint32_t saiBaseAddr, uint32_t size)
{
    BW_I2S_TCR4_FRSZ(saiBaseAddr,size -1);
}

/*!
 * @brief Sets the Rx frame size. 
 *
 * The frame size means how many words are in a frame. For example 2-channel
 * audio data, the frame size is 2, which means 2 words in a frame.
 * @param saiBaseAddr Register base address of SAI module.
 * @param size Words number in a frame.
 */
static inline void SAI_HAL_RxSetFrameSize(uint32_t saiBaseAddr, uint32_t size)
{
    BW_I2S_RCR4_FRSZ(saiBaseAddr,size - 1);
}

/*!
 * @brief Gets the Tx frame size. 
 *
 * @param saiBaseAddr Register base address of SAI module.
 */
static inline uint32_t SAI_HAL_TxGetFrameSize(uint32_t saiBaseAddr)
{
    return BR_I2S_TCR4_FRSZ(saiBaseAddr);
}

/*!
 * @brief Gets the Tx frame size. 
 *
 * @param saiBaseAddr Register base address of SAI module.
 */
static inline uint32_t SAI_HAL_RxGetFrameSize(uint32_t saiBaseAddr)
{
    return BR_I2S_RCR4_FRSZ(saiBaseAddr);
}

/*!
 * @brief Sets the Tx sync width.
 *
 * A sync is the number of bit clocks of a frame. The sync width cannot be longer than the 
 * length of the first word of the frame.
 * @param saiBaseAddr Register base address of SAI module.
 * @param width How many bit clock in a sync.
 */
static inline void SAI_HAL_TxSetFrameSyncWidth(uint32_t saiBaseAddr, uint32_t width)
{
    BW_I2S_TCR4_SYWD(saiBaseAddr, width -1);
}

/*!
 * @brief Sets the Rx sync width.
 *
 * A sync is the number of bit clocks of a frame. The sync width cannot be longer than the 
 * length of the first word of the frame.
 * @param saiBaseAddr Register base address of SAI module.
 * @param width How many bit clock in a sync.
 */
static inline void SAI_HAL_RxSetFrameSyncWidth(uint32_t saiBaseAddr, uint32_t width)
{
    BW_I2S_RCR4_SYWD(saiBaseAddr, width -1);
}

/*!
 * @brief Sets the polarity of the Tx frame sync.
 *
 * @param saiBaseAddr Register base address of SAI module.
 * @param pol Polarity of sai frame sync, can be configured to active high or low.
 */
static inline void SAI_HAL_TxSetFrameSyncPolarity(uint32_t saiBaseAddr, sai_clk_polarity_t pol)
{
    BW_I2S_TCR4_FSP(saiBaseAddr,pol);
}

/*!
 * @brief Sets the polarity of the Rx frame sync.
 *
 * @param saiBaseAddr Register base address of SAI module..
 * @param pol Polarity of SAI frame sync, can be configured to active high or low.
 */
static inline void SAI_HAL_RxSetFrameSyncPolarity(uint32_t saiBaseAddr, sai_clk_polarity_t pol)
{
    BW_I2S_RCR4_FSP(saiBaseAddr,pol);
}

/*!
 * @brief Sets the direction of the SAI Tx frame sync.
 * 
 * This function sets the  direction of frame sync.
 * @param saiBaseAddr Register base address of SAI module.
 * @param direction Frame sync generated internal or external.
 */
static inline void SAI_HAL_TxSetFrameSyncDir(uint32_t saiBaseAddr,sai_clk_direction_t direction)
{
    BW_I2S_TCR4_FSD(saiBaseAddr,direction);
}

/*!
 * @brief Sets the direction of the SAI Rx frame sync.
 * 
 * This function sets the  direction of frame sync.
 * @param saiBaseAddr Register base address of SAI module.
 * @param direction Frame sync generated internal or external.
 */
static inline void SAI_HAL_RxSetFrameSyncDir(uint32_t saiBaseAddr,sai_clk_direction_t direction)
{
    BW_I2S_RCR4_FSD(saiBaseAddr,direction);
}

/*!
 * @brief Sets the Tx data transfer order.
 *
 * This function sets the data transfer order. It can be set to MSB first or LSB first.
 * @param saiBaseAddr Register base address of SAI module.
 * @param order MSB transmit first or LSB transmit first.
 */
static inline void SAI_HAL_TxSetBitOrder(uint32_t saiBaseAddr, sai_data_order_t order)
{
    BW_I2S_TCR4_MF(saiBaseAddr,order);
}

/*!
 * @brief Sets the Rx data transfer order.
 *
 * This function sets the data transfer order. It can be set to MSB first or LSB first.
 * @param saiBaseAddr Register base address of SAI module.
 * @param order MSB transmit first or LSB transmit first.
 */
static inline void SAI_HAL_RxSetBitOrder(uint32_t saiBaseAddr, sai_data_order_t order)
{
    BW_I2S_RCR4_MF(saiBaseAddr,order);
}

/*!
 * @brief Tx Frame sync one bit early.
 *
 * @param saiBaseAddr Register base address of SAI module.
 * @param enable True means the frame sync one bit early and false means no early.
 */
static inline void SAI_HAL_TxSetFrameSyncEarlyCmd(uint32_t saiBaseAddr, bool enable)
{
    BW_I2S_TCR4_FSE(saiBaseAddr,enable);
}

/*!
 * @brief Rx Frame sync one bit early.
 *
 * @param saiBaseAddr Register base address of SAI module.
 * @param enable True means the frame sync one bit early and false means no early.
 */
static inline void SAI_HAL_RxSetFrameSyncEarlyCmd(uint32_t saiBaseAddr, bool enable)
{
    BW_I2S_RCR4_FSE(saiBaseAddr,enable);
}

/*! @} */

/*!
* @name Word configurations
* @{
*/

/*!
 * @brief Sets the word size for Tx.
 *
 * The word size means the quantization level of audio file. 
 * SAI supports the 8 bit, 16 bit, 24 bit, and 32 bit formats.
 * @param saiBaseAddr Register base address of SAI module.
 * @param bits How many bits in a word.
*/
static inline void SAI_HAL_TxSetWordSize(uint32_t saiBaseAddr,uint32_t bits)
{
    BW_I2S_TCR5_WNW(saiBaseAddr,bits-1);
}

/*!
 * @brief Sets the word size for Rx.
 *
 * The word size means the quantization level of audio file. 
 * SAI supports 8 bit, 16 bit, 24 bit, and 32 bit formats.
 * @param saiBaseAddr Register base address of SAI module.
 * @param bits How many bits in a word.
*/
static inline void SAI_HAL_RxSetWordSize(uint32_t saiBaseAddr,uint32_t bits)
{
    BW_I2S_RCR5_WNW(saiBaseAddr,bits-1);
}

/*!
 * @brief Gets the Tx word size.
 * @param saiBaseAddr Register base address of SAI module.
*/
static inline uint32_t SAI_HAL_TxGetWordSize(uint32_t saiBaseAddr)
{
    return BR_I2S_TCR5_WNW(saiBaseAddr);
}

/*!
 * @brief Gets the Rx word size.
 * @param saiBaseAddr Register base address of SAI module.
*/
static inline uint32_t SAI_HAL_RxGetWordSize(uint32_t saiBaseAddr)
{
    return BR_I2S_RCR5_WNW(saiBaseAddr);
}

/*!
 * @brief Sets the size of the first word of the Tx frame .
 *
 * In I2S protocol, the size of the first word is the same as the size of other words. In some protocols,
 * for example, AC'97, the first word is not the same size as others. This function
 * sets the length of the first word which is, in most situations, the same as others.
 * @param saiBaseAddr Register base address of SAI module.
 * @param size The length of frame head word.
 */
static inline void SAI_HAL_TxSetFirstWordSize(uint32_t saiBaseAddr, uint8_t size)
{
    BW_I2S_TCR5_W0W(saiBaseAddr, size-1);
}

/*!
 * @brief Sets the size of the first word of Rx frame .
 *
 * In I2S protocol, the size of the first word is the same as the size of other words. In some protocols,
 * for example, AC'97, the first word is not the same size as others. This function
 * sets the length of the first word which is, in most situations, the same as others.
 * @param saiBaseAddr Register base address of SAI module.
 * @param size The length of frame head word.
 */
static inline void SAI_HAL_RxSetFirstWordSize(uint32_t saiBaseAddr, uint8_t size)
{
    BW_I2S_RCR5_W0W(saiBaseAddr, size-1);
}

/*!
 * @brief Sets the FIFO index for the first bit data.
 *
 * The FIFO is 32-bit in SAI. However, not all audio data is 32-bit, but is mostly  16-bit.
 * In this situation, the codec needs to know which bit of the FIFO marks the valid audio data.
 * @param saiBaseAddr Register base address of SAI module.
 * @param index First bit shifted in FIFO.
 */
static inline void SAI_HAL_TxSetFirstBitShifted(uint32_t saiBaseAddr, uint32_t index)
{
    BW_I2S_TCR5_FBT(saiBaseAddr, index-1);
}

/*!
 * @brief Sets the index in FIFO for the first bit data.
 *
 * The FIFO is 32-bit in SAI. However, not all audio data is 32-bit, but is mostly  16-bit.
 * In this situation, the codec needs to know which bit of the FIFO marks the valid audio data.
 * @param saiBaseAddr Register base address of SAI module.
 * @param index First bit shifted in FIFO.
 */
static inline void SAI_HAL_RxSetFirstBitShifted(uint32_t saiBaseAddr, uint32_t index)
{
    BW_I2S_RCR5_FBT(saiBaseAddr, index-1);
}

/*!@}*/

/*!
* @name watermark settings
* @{
*/

/*!
 * @brief Sets the Tx watermark value.
 *
 * While the value in the FIFO is less or equal to the watermark , it generates an interrupt 
 * request or a DMA request. The watermark value cannot be greater than the depth of FIFO.
 * @param saiBaseAddr Register base address of SAI module.
 * @param watermark Watermark value of a FIFO.
 */
static inline void SAI_HAL_TxSetWatermark(uint32_t saiBaseAddr, uint32_t watermark)
{
    BW_I2S_TCR1_TFW(saiBaseAddr, watermark);
}

/*!
 * @brief Sets the Tx watermark value.
 *
 * While the value in the FIFO is more or equal to the watermark , it generates an interrupt 
 * request or a DMA request. The watermark value cannot be greater than the depth of FIFO.
 * @param saiBaseAddr Register base address of SAI module.
 * @param watermark Watermark value of a FIFO.
 */
static inline void SAI_HAL_RxSetWatermark(uint32_t saiBaseAddr, uint32_t watermark)
{
    BW_I2S_RCR1_RFW(saiBaseAddr, watermark);
}

/*!
 * @brief Gets the Tx watermark value.
 *
 * @param saiBaseAddr Register base address of SAI module.
 */
static inline uint32_t SAI_HAL_TxGetWatermark(uint32_t saiBaseAddr)
{
    return BR_I2S_TCR1_TFW(saiBaseAddr);
}

/*!
 * @brief Gets the Rx watermark value.
 *
 * @param saiBaseAddr Register base address of SAI module.
 */
static inline uint32_t SAI_HAL_RxGetWatermark(uint32_t saiBaseAddr)
{
    return BR_I2S_RCR1_RFW(saiBaseAddr);
}

/*! @}*/

/*!
 * @brief SAI Tx sync mode setting. 
 *
 * The mode can be asynchronous mode, synchronous, or synchronous with another SAI device.
 * When configured for a synchronous mode of operation, the receiver must be configured for the 
 * asynchronous operation.
 * @param saiBaseAddr Register base address of SAI module.
 * @param sync_mode Synchronous mode or Asynchronous mode.
 */
void SAI_HAL_TxSetSyncMode(uint32_t saiBaseAddr, sai_sync_mode_t sync_mode);

/*!
 * @brief SAI Rx sync mode setting. 
 *
 * The mode can be asynchronous mode, synchronous, or synchronous with another SAI device.
 * When configured for a synchronous mode of operation, the receiver must be configured for the 
 * asynchronous operation.
 * @param saiBaseAddr Register base address of SAI module.
 * @param sync_mode Synchronous mode or Asynchronous mode.
 */
void SAI_HAL_RxSetSyncMode(uint32_t saiBaseAddr, sai_sync_mode_t sync_mode);

/*!
 * @brief Gets the Tx FIFO read pointer.
 *
 * It is used to determine whether the FIFO is full or empty and know how much space there is for FIFO.
 * If read_ptr == write_ptr, the FIFO is empty. While the bit of the read_ptr and the write_ptr are
 * equal except for the MSB, the FIFO is full.
 * @param saiBaseAddr Register base address of SAI module.
 * @param fifo_channel FIFO channel selected.
 * @return FIFO read pointer value.
 */
static inline uint8_t SAI_HAL_TxGetFifoReadPointer(uint32_t saiBaseAddr,  uint32_t fifo_channel)
{
    return BR_I2S_TFRn_RFP(saiBaseAddr,fifo_channel);
}

/*!
 * @brief Gets the Rx FIFO read pointer.
 *
 * It is used to determine whether the FIFO is full or empty and know how much space there is for FIFO.
 * If read_ptr == write_ptr, the FIFO is empty. While the bit of the read_ptr and the write_ptr are
 * equal except for the MSB, the FIFO is full.
 * @param saiBaseAddr Register base address of SAI module.
 * @param fifo_channel FIFO channel selected.
 * @return FIFO read pointer value.
 */
static inline uint8_t SAI_HAL_RxGetFifoReadPointer(uint32_t saiBaseAddr,  uint32_t fifo_channel)
{
    return BR_I2S_RFRn_RFP(saiBaseAddr,fifo_channel);
}

/*!
 * @brief Gets the Tx FIFO write pointer.
 *
 * It is used to determine whether the FIFO is full or empty and know how much space there is for FIFO.
 * If read_ptr == write_ptr, the FIFO is empty. While the bit of the read_ptr and write_ptr are
 * equal except for the MSB, the FIFO is full.
 * @param saiBaseAddr Register base address of SAI module.
 * @param fifo_channel FIFO channel selected.
 * @return FIFO read pointer value.
 */
static inline uint8_t SAI_HAL_TxGetFifoWritePointer(uint32_t saiBaseAddr,uint32_t fifo_channel)
{
    return BR_I2S_TFRn_WFP(saiBaseAddr,fifo_channel);
}

/*!
 * @brief Gets the Rx FIFO write pointer.
 *
 * It is used to determine whether the FIFO is full or empty and know how much space there is for FIFO.
 * If read_ptr == write_ptr, the FIFO is empty. While the bit of the read_ptr and write_ptr are
 * equal except for the MSB, the FIFO is full.
 * @param saiBaseAddr Register base address of SAI module.
 * @param fifo_channel FIFO channel selected.
 * @return FIFO read pointer value.
 */
static inline uint8_t SAI_HAL_RxGetFifoWritePointer(uint32_t saiBaseAddr,uint32_t fifo_channel)
{
    return BR_I2S_RFRn_WFP(saiBaseAddr,fifo_channel);
}

/*!
 * @brief Gets the TDR register address.
 *
 * This function determines the dest/src address of the DMA transfer.
 * @param saiBaseAddr Register base address of SAI module.
 * @param fifo_channel FIFO channel selected.
 * @return TDR register or RDR register address
 */
static inline uint32_t* SAI_HAL_TxGetFifoAddr(uint32_t saiBaseAddr, uint32_t fifo_channel)
{
    return (uint32_t *)HW_I2S_TDRn_ADDR(saiBaseAddr, fifo_channel);
}

/*!
 * @brief Gets the RDR register address.
 *
 * This function determines the dest/src address of the DMA transfer.
 * @param saiBaseAddr Register base address of SAI module.
 * @param fifo_channel FIFO channel selected.
 * @return TDR register or RDR register address
 */
static inline uint32_t* SAI_HAL_RxGetFifoAddr(uint32_t saiBaseAddr, uint32_t fifo_channel)
{
    return (uint32_t *)HW_I2S_RDRn_ADDR(saiBaseAddr, fifo_channel);
}

/*!
 * @brief Enables the SAI Tx module.
 *
 * Enables the Tx. This function enables both the bit clock and the transfer channel.
 * @param saiBaseAddr Register base address of SAI module.
 */
static inline void SAI_HAL_TxEnable(uint32_t saiBaseAddr)
{
    BW_I2S_TCSR_BCE(saiBaseAddr,true);
    BW_I2S_TCSR_TE(saiBaseAddr,true);
}

/*!
 * @brief Enables the SAI Rx module.
 *
 * Enables the Rx. This function enables both the bit clock and the receive channel.
 * @param saiBaseAddr Register base address of SAI module.
 */
static inline void SAI_HAL_RxEnable(uint32_t saiBaseAddr)
{
    BW_I2S_RCSR_BCE(saiBaseAddr,true);    
    BW_I2S_RCSR_RE(saiBaseAddr,true);
}

/*!
 * @brief Disables the Tx module.
 *
 * Disables the Tx. This function disables both the bit clock and the transfer channel.
 * @param saiBaseAddr Register base address of SAI module.
 */
static inline void SAI_HAL_TxDisable(uint32_t saiBaseAddr)
{
    BW_I2S_TCSR_TE(saiBaseAddr,false);
    BW_I2S_TCSR_BCE(saiBaseAddr,false);
}

/*!
 * @brief Disables the Rx module.
 *
 * Disables the Rx. This function disables both the bit clock and the receive channel.
 * @param saiBaseAddr Register base address of SAI module.
 */
static inline void SAI_HAL_RxDisable(uint32_t saiBaseAddr)
{
    BW_I2S_RCSR_RE(saiBaseAddr,false);
    BW_I2S_RCSR_BCE(saiBaseAddr,false);
}

/*!
 * @brief Enables the Tx interrupt from different interrupt sources.
 *
 * The interrupt source can be : Word start flag, Sync error flag, FIFO error flag, FIFO warning flag, FIFO request flag.
 * This function sets which flag causes an interrupt request. 
 * @param saiBaseAddr Register base address of SAI module.
 * @param source SAI interrupt request source.
 * @param enable Enable or disable.
 */
void SAI_HAL_TxSetIntCmd(uint32_t saiBaseAddr,sai_interrupt_request_t source, bool enable);

/*!
 * @brief Enables the Rx interrupt from different interrupt sources.
 *
 * The interrupt source can be : Word start flag, Sync error flag, FIFO error flag, FIFO warning flag, FIFO request flag.
 * This function sets which flag causes an interrupt request. 
 * @param saiBaseAddr Register base address of SAI module.
 * @param source SAI interrupt request source.
 * @param enable Enable or disable.
 */
void SAI_HAL_RxSetIntCmd(uint32_t saiBaseAddr,sai_interrupt_request_t source, bool enable);

/*!
 * @brief Gets the status as to whether the Tx interrupt source is enabled.
 *
 * The interrupt source can be : Word start flag, Sync error flag, FIFO error flag, FIFO warning flag, FIFO request flag.
 * This function sets which flag causes an interrupt request. 
 * @param saiBaseAddr Register base address of SAI module.
 * @param source SAI interrupt request source.
 * @return Enabled or disabled.
 */
bool SAI_HAL_TxGetIntCmd(uint32_t saiBaseAddr,sai_interrupt_request_t source);

/*!
 * @brief Gets the status as to whether the Rx interrupt source is enabled.
 *
 * The interrupt source can be : Word start flag, Sync error flag, FIFO error flag, FIFO warning flag, FIFO request flag.
 * This function sets which flag causes an interrupt request. 
 * @param saiBaseAddr Register base address of SAI module.
 * @param source SAI interrupt request source.
 * @return Enabled or disabled.
 */
bool SAI_HAL_RxGetIntCmd(uint32_t saiBaseAddr,sai_interrupt_request_t source);

/*!
 * @brief Enables the Tx DMA request from different sources.
 *
 * The DMA sources can be: FIFO warning and FIFO request.
 * This function enables the DMA request from different DMA request sources.
 * @param saiBaseAddr Register base address of SAI module.
 * @param source SAI DMA request source.
 * @param enable Enable or disable.
 */
void SAI_HAL_TxSetDmaCmd(uint32_t saiBaseAddr, sai_dma_request_t source, bool enable);

/*!
 * @brief Enables the Rx DMA request from different sources.
 *
 * The DMA sources can be: FIFO warning and FIFO request.
 * This function enables the DMA request from different DMA request sources.
 * @param saiBaseAddr Register base address of SAI module.
 * @param source SAI DMA request source.
 * @param enable Enable or disable.
 */
void SAI_HAL_RxSetDmaCmd(uint32_t saiBaseAddr, sai_dma_request_t source, bool enable);

/*!
 * @brief Gets the status whether the Tx DMA source is enabled.
 *
 * The DMA sources can be: FIFO warning and FIFO request.
 * This function enables the DMA request from different DMA request sources.
 * @param saiBaseAddr Register base address of SAI module.
 * @param source SAI DMA request source.
 * @param Enable or disable.
 */
bool SAI_HAL_TxGetDmaCmd(uint32_t saiBaseAddr, sai_dma_request_t source);

/*!
 * @brief Gets the status whether the Rx DMA source is enabled.
 *
 * The DMA sources can be: FIFO warning and FIFO request.
 * This function enables the DMA request from different DMA request sources.
 * @param saiBaseAddr Register base address of SAI module.
 * @param source SAI DMA request source.
 * @return Enable or disable.
 */
bool SAI_HAL_RxGetDmaCmd(uint32_t saiBaseAddr, sai_dma_request_t source);

/*!
 * @brief Clears the Tx state flags.
 *
 * The function is used to clear the flags manually. It can clear word start, FIFO warning, FIFO error,
 * FIFO request flag.
 * @param saiBaseAddr Register base address of SAI module.
 * @param flag SAI state flag type. The flag can be word start, sync error, FIFO error/warning.
 */
void SAI_HAL_TxClearStateFlag(uint32_t saiBaseAddr, sai_state_flag_t flag);

/*!
 * @brief Clears the Rx state flags.
 *
 * The function is used to clear the flags manually. It can clear word start, FIFO warning, FIFO error,
 * FIFO request flag.
 * @param saiBaseAddr Register base address of SAI module.
 * @param flag SAI state flag type. The flag can be word start, sync error, FIFO error/warning.
 */
void SAI_HAL_RxClearStateFlag(uint32_t saiBaseAddr, sai_state_flag_t flag);

/*!
 * @brief Resets the Tx module.
 *
 * There are two kinds of resets: Software reset and FIFO reset.
 * Software reset: resets all transmitter internal logic, including the bit clock generation, 
 * status flags and FIFO pointers. It does not reset the configuration registers.
 * FIFO reset: synchronizes the FIFO write pointer to the same value as the FIFO read pointer. 
 * This empties the FIFO contents and is to be used after the Transmit FIFO Error Flag is set,
 * and before the FIFO is re-initialized and the Error Flag is cleared.
 * @param saiBaseAddr Register base address of SAI module.
 * @param type SAI reset type.
 */
void SAI_HAL_TxSetReset(uint32_t saiBaseAddr, sai_reset_type_t type);

/*!
 * @brief Resets the Rx module.
 *
 * There are two kinds of resets: Software reset and FIFO reset.
 * Software reset: resets all transmitter internal logic, including the bit clock generation, 
 * status flags and FIFO pointers. It does not reset the configuration registers.
 * FIFO reset: synchronizes the FIFO write pointer to the same value as the FIFO read pointer. 
 * This empties the FIFO contents and is to be used after the Transmit FIFO Error Flag is set,
 * and before the FIFO is re-initialized and the Error Flag is cleared.
 * @param saiBaseAddr Register base address of SAI module.
 * @param type SAI reset type.
 */
void SAI_HAL_RxSetReset(uint32_t saiBaseAddr, sai_reset_type_t type);

/*!
 * @brief Sets the Tx mask word of the frame.
 *
 * Each bit number represent the mask word index. For example, 0 represents mask the 0th word, 3 
 * represents mask 0th and 1st word. The TMR register can be different from frame to frame. If the
 * user wants a mono audio, set the mask to 0/1.
 * @param saiBaseAddr Register base address of SAI module.
 * @param mask Which bits need to be masked in a frame.
 */
static inline void SAI_HAL_TxSetWordMask(uint32_t saiBaseAddr, uint32_t mask)
{
    BW_I2S_TMR_TWM(saiBaseAddr, mask);
}

/*!
 * @brief Sets the Rx mask word of the frame.
 *
 * Each bit number represent the mask word index. For example, 0 represents mask the 0th word, 3 
 * represents mask 0th and 1st word. The TMR register can be different from frame to frame. If the
 * user wants a mono audio, set the mask to 0/1.
 * @param saiBaseAddr Register base address of SAI module.
 * @param mask Which bits need to be masked in a frame.
 */
static inline void SAI_HAL_RxSetWordMask(uint32_t saiBaseAddr,  uint32_t mask)
{
    BW_I2S_RMR_RWM(saiBaseAddr, mask);
}

/*!
 * @brief Sets the Tx FIFO channel.
 *
 * A SAI saiBaseAddr includes a Tx and an Rx. Each has several channels according to 
 * different platforms. A channel means a path for the audio data input/output.
 * @param saiBaseAddr Register base address of SAI module.
 * @param fifo_channel FIFO channel number.
 */
static inline void SAI_HAL_TxSetDataChn(uint32_t saiBaseAddr, uint8_t fifo_channel)
{
    BW_I2S_TCR3_TCE(saiBaseAddr, 1u << fifo_channel);
}

/*!
 * @brief Sets the Rx FIFO channel.
 *
 * A SAI saiBaseAddr includes a Tx and a Rx. Each has several channels according to 
 * different platforms. A channel means a path for the audio data input/output.
 * @param saiBaseAddr Register base address of SAI module.
 * @param fifo_channel FIFO channel number.
 */
static inline void SAI_HAL_RxSetDataChn(uint32_t saiBaseAddr, uint8_t fifo_channel)
{
    BW_I2S_RCR3_RCE(saiBaseAddr, 1u << fifo_channel);
}

/*!
 * @brief Sets the running mode of the Tx. There is a debug mode, stop mode, and a normal mode.
 *
 * This function can set the working mode of the SAI saiBaseAddr. Stop mode is always 
 * used in low power cases, and the debug mode disables the  SAI after the current 
 * transmit/receive is completed.
 * @param saiBaseAddr Register base address of SAI module.
 * @param run_mode SAI running mode.
 * @param enable Enable or disable a mode.
 */
void SAI_HAL_TxSetRunModeCmd(uint32_t saiBaseAddr, sai_run_mode_t run_mode, bool enable);

/*!
 * @brief Sets the running mode of the Rx. There is a debug mode, stop mode, and a normal mode.
 *
 * This function can set the working mode of the SAI saiBaseAddr. Stop mode is always 
 * used in low power cases, and the debug mode disables the  SAI after the current 
 * transmit/receive is completed.
 * @param saiBaseAddr Register base address of SAI module.
 * @param run_mode SAI running mode.
 * @param enable Enable or disable a mode.
 */
void SAI_HAL_RxSetRunModeCmd(uint32_t saiBaseAddr, sai_run_mode_t run_mode, bool enable);

/*!
 * @brief Configures at which word the start of word flag is set in the Tx.
 *
 * @param saiBaseAddr Register base address of SAI module.
 * @param index Which word triggers word start flag.
 */
static inline void SAI_HAL_TxSetWordStartIndex(uint32_t saiBaseAddr,uint32_t index)
{
    assert(index <= FSL_FEATURE_SAI_MAX_WORDS_PER_FRAME);
    BW_I2S_TCR3_WDFL(saiBaseAddr, index -1);
}

/*!
 * @brief Configures at which word the start of word flag is set in the Tx.
 *
 * @param saiBaseAddr Register base address of SAI module.
 * @param index Which word triggers word start flag.
 */
static inline void SAI_HAL_RxSetWordStartIndex(uint32_t saiBaseAddr,uint32_t index)
{
    assert(index <= FSL_FEATURE_SAI_MAX_WORDS_PER_FRAME);
    BW_I2S_RCR3_WDFL(saiBaseAddr, index -1);
}

/*!
 * @brief Gets the state of the flags in the TCSR.
 * @param saiBaseAddr Register base address of SAI module.
 * @param flag State flag type, it can be FIFO error, FIFO warning and so on.
 * @return True if detect word start otherwise false.
 */
bool SAI_HAL_TxGetStateFlag(uint32_t saiBaseAddr, sai_state_flag_t flag);

/*!
 * @brief Gets the state of the flags in the RCSR.
 * @param saiBaseAddr Register base address of SAI module.
 * @param flag State flag type, it can be FIFO error, FIFO warning and so on.
 * @return True if detect word start otherwise false.
 */
bool SAI_HAL_RxGetStateFlag(uint32_t saiBaseAddr, sai_state_flag_t flag);

/*!
 * @brief Receives the data from the FIFO.
 * @param saiBaseAddr Register base address of SAI module.
 * @param rx_channel Rx FIFO channel.
 * @param data Pointer to the address to be written in.
 */
static inline uint32_t SAI_HAL_ReceiveData(uint32_t saiBaseAddr, uint32_t rx_channel)
{
    assert(rx_channel < FSL_FEATURE_SAI_CHANNEL_COUNT);   
    return HW_I2S_RDRn_RD(saiBaseAddr, rx_channel);
}

/*!
 * @brief Transmits data to the FIFO.
 * @param saiBaseAddr Register base address of SAI module.
 * @param tx_channel Tx FIFO channel.
 * @param data Data value which needs to be written into FIFO.
 */
static inline void SAI_HAL_SendData(uint32_t saiBaseAddr, uint32_t tx_channel, uint32_t data)
{
    assert(tx_channel < FSL_FEATURE_SAI_CHANNEL_COUNT);  
    HW_I2S_TDRn_WR(saiBaseAddr,tx_channel,data);
}

/*!
* @brief Uses blocking to receive data.
* @param saiBaseAddr The SAI saiBaseAddr.
* @param rx_channel Rx FIFO channel.
* @return Received data.
*/
uint32_t SAI_HAL_ReceiveDataBlocking(uint32_t saiBaseAddr, uint32_t rx_channel);

/*!
* @brief Uses blocking to send data.
* @param saiBaseAddr The SAI saiBaseAddr.
* @param tx_channel Tx FIFO channel.
* @param data Data value which needs to be written into FIFO.
*/
void SAI_HAL_SendDataBlocking(uint32_t saiBaseAddr, uint32_t tx_channel, uint32_t data);

#if FSL_FEATURE_SAI_HAS_ON_DEMAND_MODE
/*!
 * @brief Tx on-demand mode setting.
 *
 * When set, the frame sync is generated internally. A frame sync is only generated when the 
 * FIFO warning flag is clear.
 * @param saiBaseAddr Register base address of SAI module.
 * @param enable True means on demand mode enable, false means disable.
 */
static inline void SAI_HAL_TxSetOndemandCmd(uint32_t saiBaseAddr, bool enable)
{
    BW_I2S_TCR4_ONDEM(saiBaseAddr, enable);
}

/*!
 * @brief Rx on-demand mode setting.
 *
 * When set, the frame sync is generated internally. A frame sync is only generated when the 
 * FIFO warning flag is clear.
 * @param saiBaseAddr Register base address of SAI module.
 * @param enable True means on demand mode enable, false means disable.
 */
static inline void SAI_HAL_RxSetOndemandCmd(uint32_t saiBaseAddr, bool enable)
{
    BW_I2S_RCR4_ONDEM(saiBaseAddr, enable);
}
#endif

#if FSL_FEATURE_SAI_HAS_FIFO_FUNCTION_AFTER_ERROR
/*!
 * @brief Tx FIFO continues on error.
 *
 * Configures when the SAI continues transmitting after a FIFO error has been detected.
 * @param saiBaseAddr Register base address of SAI module.
 * @param enable True means on demand mode enable, false means disable.
 */
static inline void SAI_HAL_TxSetFIFOErrorContinueCmd(uint32_t saiBaseAddr, bool enable)
{
    BW_I2S_TCR4_FCONT(saiBaseAddr, enable);
}

/*!
 * @brief Rx FIFO continues on error.
 *
 * Configures when the SAI continues transmitting after a FIFO error has been detected.
 * @param saiBaseAddr Register base address of SAI module.
 * @param enable True means on demand mode enable, false means disable.
 */
static inline void SAI_HAL_RxSetFIFOErrorContinueCmd(uint32_t saiBaseAddr, bool enable)
{
    BW_I2S_RCR4_FCONT(saiBaseAddr, enable);
}
#endif

#if FSL_FEATURE_SAI_HAS_FIFO_PACKING
/*!
 * @brief Tx FIFO packing mode setting.
 *
 * Enables packing 8-bit data or 16-bit data into each 32-bit FIFO word. If the word size is 
 * greater than 8-bit or 16-bit, only the first 8-bit or 16-bits are loaded from the FIFO. 
 * The first word in each frame always starts with a new 32-bit FIFO word and the first bit shifted
 * must be configured within the first packed word. When FIFO packing is enabled, the FIFO write
 * pointer only increments when the full 32-bit FIFO word has been written by software.
 * @param saiBaseAddr Register base address of SAI module.
 * @param mode FIFO packing mode.
 */
static inline void SAI_HAL_TxSetFIFOPackingMode(uint32_t saiBaseAddr, sai_fifo_packing_t mode)
{
    BW_I2S_TCR4_FPACK(saiBaseAddr,mode);
}

/*!
 * @brief Rx FIFO packing mode setting.
 *
 * Enables packing 8-bit data or 16-bit data into each 32-bit FIFO word. If the word size is 
 * greater than 8-bit or 16-bit, only the first 8-bit or 16-bits are loaded from the FIFO. 
 * The first word in each frame always starts with a new 32-bit FIFO word and the first bit shifted
 * must be configured within the first packed word. When FIFO packing is enabled, the FIFO write
 * pointer only increments when the full 32-bit FIFO word has been written by software.
 * @param saiBaseAddr Register base address of SAI module.
 * @param mode FIFO packing mode.
 */
static inline void SAI_HAL_RxSetFIFOPackingMode(uint32_t saiBaseAddr, sai_fifo_packing_t mode)
{
    BW_I2S_RCR4_FPACK(saiBaseAddr,mode);
}
#endif

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* __FSL_SAI_HAL_H__ */
/*******************************************************************************
* EOF
*******************************************************************************/
