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
#ifndef __FSL_SDHC_HAL_H__
#define __FSL_SDHC_HAL_H__

#include <assert.h>
#include <stdbool.h>
#include "fsl_device_registers.h"
#include "fsl_sdhc_features.h"

#ifndef MBED_NO_SDHC

/*! @addtogroup sdhc_hal */
/*! @{ */

/* PRSSTA */
#define SDHC_HAL_DAT0_LEVEL             (BM_SDHC_PRSSTAT_DLSL & (1 << 24))

/* XFERTYP */
#define SDHC_HAL_MAX_BLOCK_COUNT        ((1 << BS_SDHC_BLKATTR_BLKCNT) - 1)
#define SDHC_HAL_ENABLE_DMA             BM_SDHC_XFERTYP_DMAEN

#define SDHC_HAL_CMD_TYPE_SUSPEND       (BF_SDHC_XFERTYP_CMDTYP(1))
#define SDHC_HAL_CMD_TYPE_RESUME        (BF_SDHC_XFERTYP_CMDTYP(2))
#define SDHC_HAL_CMD_TYPE_ABORT         (BF_SDHC_XFERTYP_CMDTYP(3))

#define SDHC_HAL_ENABLE_BLOCK_COUNT     BM_SDHC_XFERTYP_BCEN
#define SDHC_HAL_ENABLE_AUTO_CMD12      BM_SDHC_XFERTYP_AC12EN
#define SDHC_HAL_ENABLE_DATA_READ       BM_SDHC_XFERTYP_DTDSEL
#define SDHC_HAL_MULTIPLE_BLOCK         BM_SDHC_XFERTYP_MSBSEL

#define SDHC_HAL_RESP_LEN_136           ((0x1 << BP_SDHC_XFERTYP_RSPTYP) & BM_SDHC_XFERTYP_RSPTYP)
#define SDHC_HAL_RESP_LEN_48            ((0x2 << BP_SDHC_XFERTYP_RSPTYP) & BM_SDHC_XFERTYP_RSPTYP)
#define SDHC_HAL_RESP_LEN_48_BC         ((0x3 << BP_SDHC_XFERTYP_RSPTYP) & BM_SDHC_XFERTYP_RSPTYP)

#define SDHC_HAL_ENABLE_CRC_CHECK       BM_SDHC_XFERTYP_CCCEN
#define SDHC_HAL_ENABLE_INDEX_CHECK     BM_SDHC_XFERTYP_CICEN
#define SDHC_HAL_DATA_PRESENT           BM_SDHC_XFERTYP_DPSEL

/* SYSCTL */
#define SDHC_HAL_MAX_DVS                (16U)
#define SDHC_HAL_INITIAL_DVS            (1U)            /* initial value of divisor to calculate clock rate */
#define SDHC_HAL_INITIAL_CLKFS          (2U)            /* initial value of clock selector to calculate clock rate */
#define SDHC_HAL_NEXT_DVS(x)            do { ((x) += 1); } while(0)
#define SDHC_HAL_PREV_DVS(x)            do { ((x) -= 1); } while(0)
#define SDHC_HAL_MAX_CLKFS              (256U)
#define SDHC_HAL_NEXT_CLKFS(x)          do { ((x) <<= 1); } while(0)
#define SDHC_HAL_PREV_CLKFS(x)          do { ((x) >>= 1); } while(0)

/* IRQSTAT */
#define SDHC_HAL_CMD_COMPLETE_INT       BM_SDHC_IRQSTAT_CC
#define SDHC_HAL_DATA_COMPLETE_INT      BM_SDHC_IRQSTAT_TC
#define SDHC_HAL_BLOCK_GAP_EVENT_INT    BM_SDHC_IRQSTAT_BGE
#define SDHC_HAL_DMA_INT                BM_SDHC_IRQSTAT_DINT
#define SDHC_HAL_DMA_ERR_INT            BM_SDHC_IRQSTAT_DMAE
#define SDHC_HAL_BUF_WRITE_READY_INT    BM_SDHC_IRQSTAT_BWR
#define SDHC_HAL_BUF_READ_READY_INT     BM_SDHC_IRQSTAT_BRR
#define SDHC_HAL_CARD_INSERTION_INT     BM_SDHC_IRQSTAT_CINS
#define SDHC_HAL_CARD_REMOVAL_INT       BM_SDHC_IRQSTAT_CRM
#define SDHC_HAL_CARD_INT               BM_SDHC_IRQSTAT_CINT
#define SDHC_HAL_CMD_TIMEOUT_ERR_INT    BM_SDHC_IRQSTAT_CTOE
#define SDHC_HAL_CMD_CRC_ERR_INT        BM_SDHC_IRQSTAT_CCE
#define SDHC_HAL_CMD_END_BIT_ERR_INT    BM_SDHC_IRQSTAT_CEBE
#define SDHC_HAL_CMD_INDEX_ERR_INT      BM_SDHC_IRQSTAT_CIE
#define SDHC_HAL_DATA_TIMEOUT_ERR_INT   BM_SDHC_IRQSTAT_DTOE
#define SDHC_HAL_DATA_CRC_ERR_INT       BM_SDHC_IRQSTAT_DCE
#define SDHC_HAL_DATA_END_BIT_ERR_INT   BM_SDHC_IRQSTAT_DEBE
#define SDHC_HAL_AUTO_CMD12_ERR_INT     BM_SDHC_IRQSTAT_AC12E

#define SDHC_HAL_CMD_ERR_INT            ((uint32_t)(SDHC_HAL_CMD_TIMEOUT_ERR_INT | \
                                        SDHC_HAL_CMD_CRC_ERR_INT | \
                                        SDHC_HAL_CMD_END_BIT_ERR_INT | \
                                        SDHC_HAL_CMD_INDEX_ERR_INT))
#define SDHC_HAL_DATA_ERR_INT           ((uint32_t)(SDHC_HAL_DATA_TIMEOUT_ERR_INT | \
                                        SDHC_HAL_DATA_CRC_ERR_INT | \
                                        SDHC_HAL_DATA_END_BIT_ERR_INT))
#define SDHC_HAL_DATA_ALL_INT           ((uint32_t)(SDHC_HAL_DATA_ERR_INT | \
                                        SDHC_HAL_DATA_COMPLETE_INT | \
                                        SDHC_HAL_BUF_READ_READY_INT | \
                                        SDHC_HAL_BUF_WRITE_READY_INT | \
                                        SDHC_HAL_DMA_ERR_INT | SDHC_HAL_DMA_INT))
#define SDHC_HAL_CMD_ALL_INT            ((uint32_t)(SDHC_HAL_CMD_ERR_INT | \
                                        SDHC_HAL_CMD_COMPLETE_INT | \
                                        SDHC_HAL_AUTO_CMD12_ERR_INT))
#define SDHC_HAL_CD_ALL_INT             ((uint32_t)(SDHC_HAL_CARD_INSERTION_INT | \
                                        SDHC_HAL_CARD_REMOVAL_INT))
#define SDHC_HAL_ALL_ERR_INT            ((uint32_t)(SDHC_HAL_CMD_ERR_INT | \
                                        SDHC_HAL_DATA_ERR_INT | \
                                        SDHC_HAL_AUTO_CMD12_ERR_INT | \
                                        SDHC_HAL_DMA_ERR_INT))

/* AC12ERR */
#define SDHC_HAL_ACMD12_NOT_EXEC_ERR    BM_SDHC_AC12ERR_AC12NE
#define SDHC_HAL_ACMD12_TIMEOUT_ERR     BM_SDHC_AC12ERR_AC12TOE
#define SDHC_HAL_ACMD12_END_BIT_ERR     BM_SDHC_AC12ERR_AC12EBE
#define SDHC_HAL_ACMD12_CRC_ERR         BM_SDHC_AC12ERR_AC12CE
#define SDHC_HAL_ACMD12_INDEX_ERR       BM_SDHC_AC12ERR_AC12IE
#define SDHC_HAL_ACMD12_NOT_ISSUE_ERR   BM_SDHC_AC12ERR_CNIBAC12E

/* HTCAPBLT */
#define SDHC_HAL_SUPPORT_ADMA           BM_SDHC_HTCAPBLT_ADMAS
#define SDHC_HAL_SUPPORT_HIGHSPEED     BM_SDHC_HTCAPBLT_HSS
#define SDHC_HAL_SUPPORT_DMA            BM_SDHC_HTCAPBLT_DMAS
#define SDHC_HAL_SUPPORT_SUSPEND_RESUME BM_SDHC_HTCAPBLT_SRS
#define SDHC_HAL_SUPPORT_3_3_V          BM_SDHC_HTCAPBLT_VS33
#define SDHC_HAL_SUPPORT_3_0_V          BM_SDHC_HTCAPBLT_VS30
#define SDHC_HAL_SUPPORT_1_8_V          BM_SDHC_HTCAPBLT_VS18

/* FEVT */
#define SDHC_HAL_ACMD12_NOT_EXEC_ERR_EVENT  BM_SDHC_FEVT_AC12NE
#define SDHC_HAL_ACMD12_TIMEOUT_ERR_EVENT   BM_SDHC_FEVT_AC12TOE
#define SDHC_HAL_ACMD12_CRC_ERR_EVENT       BM_SDHC_FEVT_AC12CE
#define SDHC_HAL_ACMD12_END_BIT_ERR_EVENT   BM_SDHC_FEVT_AC12EBE
#define SDHC_HAL_ACMD12_INDEX_ERR_EVENT     BM_SDHC_FEVT_AC12IE
#define SDHC_HAL_ACMD12_NOT_ISSUE_ERR_EVENT BM_SDHC_FEVT_CNIBAC12E
#define SDHC_HAL_CMD_TIMEOUT_ERR_EVENT      BM_SDHC_FEVT_CTOE
#define SDHC_HAL_CMD_CRC_ERR_EVENT          BM_SDHC_FEVT_CCE
#define SDHC_HAL_CMD_END_BIT_ERR_EVENT      BM_SDHC_FEVT_CEBE
#define SDHC_HAL_CMD_INDEX_ERR_EVENT        BM_SDHC_FEVT_CIE
#define SDHC_HAL_DATA_TIMEOUT_ERR_EVENT     BM_SDHC_FEVT_DTOE
#define SDHC_HAL_DATA_CRC_ERR_EVENT         BM_SDHC_FEVT_DCE
#define SDHC_HAL_DATA_END_BIT_ERR_EVENT     BM_SDHC_FEVT_DEBE
#define SDHC_HAL_ACMD12_ERR_EVENT           BM_SDHC_FEVT_AC12E
#define SDHC_HAL_CARD_INT_EVENT             BM_SDHC_FEVT_CINT
#define SDHC_HAL_DMA_ERROR_EVENT            BM_SDHC_FEVT_DMAE

/* MMCBOOT */
typedef enum _sdhc_hal_mmcboot {
    kSdhcHalMmcbootNormal = 0,
    kSdhcHalMmcbootAlter = 1,
} sdhc_hal_mmcboot_t;

/* PROCTL */
typedef enum _sdhc_hal_led {
    kSdhcHalLedOff = 0,
    kSdhcHalLedOn = 1,
} sdhc_hal_led_t;

typedef enum _sdhc_hal_dtw {
    kSdhcHalDtw1Bit = 0,
    kSdhcHalDtw4Bit = 1,
    kSdhcHalDtw8Bit = 2,
} sdhc_hal_dtw_t;

typedef enum _sdhc_hal_endian {
    kSdhcHalEndianBig = 0,
    kSdhcHalEndianHalfWordBig = 1,
    kSdhcHalEndianLittle = 2,
} sdhc_hal_endian_t;

typedef enum _sdhc_hal_dma_mode {
    kSdhcHalDmaSimple = 0,
    kSdhcHalDmaAdma1 = 1,
    kSdhcHalDmaAdma2 = 2,
} sdhc_hal_dma_mode_t;

#define SDHC_HAL_ADMA1_ADDR_ALIGN           (4096)
#define SDHC_HAL_ADMA1_LEN_ALIGN            (4096)
#define SDHC_HAL_ADMA2_ADDR_ALIGN           (4)
#define SDHC_HAL_ADMA2_LEN_ALIGN            (4)

/*
 * ADMA1 descriptor table
 * |------------------------|---------|--------------------------|
 * | Address/page Field     |reserved |         Attribute        |
 * |------------------------|---------|--------------------------|
 * |31                    12|11      6|05  |04  |03|02 |01 |00   |
 * |------------------------|---------|----|----|--|---|---|-----|
 * | address or data length | 000000  |Act2|Act1| 0|Int|End|Valid|
 * |------------------------|---------|----|----|--|---|---|-----|
 *
 *
 * |------|------|-----------------|-------|-------------|
 * | Act2 | Act1 |     Comment     | 31-28 | 27 - 12     |
 * |------|------|-----------------|---------------------|
 * |   0  |   0  | No op           | Don't care          |
 * |------|------|-----------------|-------|-------------|
 * |   0  |   1  | Set data length |  0000 | Data Length |
 * |------|------|-----------------|-------|-------------|
 * |   1  |   0  | Transfer data   | Data address        |
 * |------|------|-----------------|---------------------|
 * |   1  |   1  | Link descriptor | Descriptor address  |
 * |------|------|-----------------|---------------------|
 *
 */
typedef uint32_t sdhc_hal_adma1_descriptor_t;
#define SDHC_HAL_ADMA1_DESC_VALID_MASK           (1 << 0)
#define SDHC_HAL_ADMA1_DESC_END_MASK             (1 << 1)
#define SDHC_HAL_ADMA1_DESC_INT_MASK             (1 << 2)
#define SDHC_HAL_ADMA1_DESC_ACT1_MASK            (1 << 4)
#define SDHC_HAL_ADMA1_DESC_ACT2_MASK            (1 << 5)
#define SDHC_HAL_ADMA1_DESC_TYPE_NOP             (SDHC_HAL_ADMA1_DESC_VALID_MASK)
#define SDHC_HAL_ADMA1_DESC_TYPE_TRAN            (SDHC_HAL_ADMA1_DESC_ACT2_MASK | SDHC_HAL_ADMA1_DESC_VALID_MASK)
#define SDHC_HAL_ADMA1_DESC_TYPE_LINK            (SDHC_HAL_ADMA1_DESC_ACT1_MASK | SDHC_HAL_ADMA1_DESC_ACT2_MASK | SDHC_HAL_ADMA1_DESC_VALID_MASK)
#define SDHC_HAL_ADMA1_DESC_TYPE_SET             (SDHC_HAL_ADMA1_DESC_ACT1_MASK | SDHC_HAL_ADMA1_DESC_VALID_MASK)
#define SDHC_HAL_ADMA1_DESC_ADDRESS_SHIFT        (12)
#define SDHC_HAL_ADMA1_DESC_ADDRESS_MASK         (0xFFFFFU)
#define SDHC_HAL_ADMA1_DESC_LEN_SHIFT            (12)
#define SDHC_HAL_ADMA1_DESC_LEN_MASK             (0xFFFFU)
#define SDHC_HAL_ADMA1_DESC_MAX_LEN_PER_ENTRY    (SDHC_HAL_ADMA1_DESC_LEN_MASK + 1)

/*
 * ADMA2 descriptor table
 * |----------------|---------------|-------------|--------------------------|
 * | Address Field  |     length    | reserved    |         Attribute        |
 * |----------------|---------------|-------------|--------------------------|
 * |63            32|31           16|15         06|05  |04  |03|02 |01 |00   |
 * |----------------|---------------|-------------|----|----|--|---|---|-----|
 * | 32-bit address | 16-bit length | 0000000000  |Act2|Act1| 0|Int|End|Valid|
 * |----------------|---------------|-------------|----|----|--|---|---|-----|
 *
 *
 * | Act2 | Act1 |     Comment     | Operation                                                         |
 * |------|------|-----------------|-------------------------------------------------------------------|
 * |   0  |   0  | No op           | Don't care                                                        |
 * |------|------|-----------------|-------------------------------------------------------------------|
 * |   0  |   1  | Reserved        | Read this line and go to next one                                 |
 * |------|------|-----------------|-------------------------------------------------------------------|
 * |   1  |   0  | Transfer data   | Transfer data with address and length set in this descriptor line |
 * |------|------|-----------------|-------------------------------------------------------------------|
 * |   1  |   1  | Link descriptor | Link to another descriptor                                        |
 * |------|------|-----------------|-------------------------------------------------------------------|
 *
 */
typedef struct SdhcHalAdma2Descriptor {
    uint32_t attribute;
    uint32_t *address;
} sdhc_hal_adma2_descriptor_t;

#define SDHC_HAL_ADMA2_DESC_VALID_MASK           (1 << 0)
#define SDHC_HAL_ADMA2_DESC_END_MASK             (1 << 1)
#define SDHC_HAL_ADMA2_DESC_INT_MASK             (1 << 2)
#define SDHC_HAL_ADMA2_DESC_ACT1_MASK            (1 << 4)
#define SDHC_HAL_ADMA2_DESC_ACT2_MASK            (1 << 5)
#define SDHC_HAL_ADMA2_DESC_TYPE_NOP             (SDHC_HAL_ADMA2_DESC_VALID_MASK)
#define SDHC_HAL_ADMA2_DESC_TYPE_RCV             (SDHC_HAL_ADMA2_DESC_ACT1_MASK | SDHC_HAL_ADMA2_DESC_VALID_MASK)
#define SDHC_HAL_ADMA2_DESC_TYPE_TRAN            (SDHC_HAL_ADMA2_DESC_ACT2_MASK | SDHC_HAL_ADMA2_DESC_VALID_MASK)
#define SDHC_HAL_ADMA2_DESC_TYPE_LINK            (SDHC_HAL_ADMA2_DESC_ACT1_MASK | SDHC_HAL_ADMA2_DESC_ACT2_MASK | SDHC_HAL_ADMA2_DESC_VALID_MASK)
#define SDHC_HAL_ADMA2_DESC_LEN_SHIFT            (16)
#define SDHC_HAL_ADMA2_DESC_LEN_MASK             (0xFFFFU)
#define SDHC_HAL_ADMA2_DESC_MAX_LEN_PER_ENTRY    (SDHC_HAL_ADMA2_DESC_LEN_MASK + 1)

#define SDHC_HAL_RST_TYPE_ALL               BM_SDHC_SYSCTL_RSTA
#define SDHC_HAL_RST_TYPE_CMD               BM_SDHC_SYSCTL_RSTC
#define SDHC_HAL_RST_TYPE_DATA              BM_SDHC_SYSCTL_RSTD

#define SDHC_HAL_MAX_BLKLEN_512B            (0U)
#define SDHC_HAL_MAX_BLKLEN_1024B           (1U)
#define SDHC_HAL_MAX_BLKLEN_2048B           (2U)
#define SDHC_HAL_MAX_BLKLEN_4096B           (3U)

/*************************************************************************************************
 * API
 ************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*! @name SDHC HAL FUNCTION */
/*@{ */

/*!
 * @brief Configures the DMA address.
 *
 * @param baseAddr SDHC base address
 * @param address the DMA address
 */
static inline void SDHC_HAL_SetDmaAddress(uint32_t baseAddr, uint32_t address)
{
    HW_SDHC_DSADDR_WR(baseAddr, BF_SDHC_DSADDR_DSADDR(address));
}

/*!
 * @brief Gets the DMA address.
 *
 * @param baseAddr SDHC base address
 * @return the DMA address
 */
static inline uint32_t SDHC_HAL_GetDmaAddress(uint32_t baseAddr)
{
    return HW_SDHC_DSADDR_RD(baseAddr);
}

/*!
 * @brief Gets the block size configured.
 *
 * @param baseAddr SDHC base address
 * @return the block size already configured
 */
static inline uint32_t SDHC_HAL_GetBlockSize(uint32_t baseAddr)
{
    return BR_SDHC_BLKATTR_BLKSIZE(baseAddr);
}

/*!
 * @brief Sets the block size.
 *
 * @param baseAddr SDHC base address
 * @param blockSize the block size
 */
static inline void SDHC_HAL_SetBlockSize(uint32_t baseAddr, uint32_t blockSize)
{
    BW_SDHC_BLKATTR_BLKSIZE(baseAddr, blockSize);
}

/*!
 * @brief Sets the block count.
 *
 * @param baseAddr SDHC base address
 * @param blockCount the block count
 */
static inline void SDHC_HAL_SetBlockCount(uint32_t baseAddr, uint32_t blockCount)
{
    BW_SDHC_BLKATTR_BLKCNT(baseAddr, blockCount);
}

/*!
 * @brief Gets the block count configured.
 *
 * @param baseAddr SDHC base address
 * @return the block count already configured
 */
static inline uint32_t SDHC_HAL_GetBlockCount(uint32_t baseAddr)
{
    return BR_SDHC_BLKATTR_BLKCNT(baseAddr);
}

/*!
 * @brief Configures the command argument.
 *
 * @param baseAddr SDHC base address
 * @param arg the command argument
 */
static inline void SDHC_HAL_SetCmdArgument(uint32_t baseAddr, uint32_t arg)
{
    BW_SDHC_CMDARG_CMDARG(baseAddr, arg);
}

/*!
 * @brief Sends a command.
 *
 * @param baseAddr SDHC base address
 * @param index command index
 * @param flags transfer type flags
 */
static inline void SDHC_HAL_SendCmd(uint32_t baseAddr, uint32_t index, uint32_t flags)
{
    HW_SDHC_XFERTYP_WR(baseAddr, ((index << BP_SDHC_XFERTYP_CMDINX) & BM_SDHC_XFERTYP_CMDINX)
            | (flags & ( BM_SDHC_XFERTYP_DMAEN | BM_SDHC_XFERTYP_MSBSEL | BM_SDHC_XFERTYP_DPSEL
                | BM_SDHC_XFERTYP_CMDTYP | BM_SDHC_XFERTYP_BCEN | BM_SDHC_XFERTYP_CICEN
                | BM_SDHC_XFERTYP_CCCEN | BM_SDHC_XFERTYP_RSPTYP | BM_SDHC_XFERTYP_DTDSEL
                | BM_SDHC_XFERTYP_AC12EN)));
}

/*!
 * @brief Fills the the data port.
 *
 * @param baseAddr SDHC base address
 * @param data the data about to be sent
 */
static inline void SDHC_HAL_SetData(uint32_t baseAddr, uint32_t data)
{
    HW_SDHC_DATPORT_WR(baseAddr, data);
}

/*!
 * @brief Retrieves the data from the data port.
 *
 * @param baseAddr SDHC base address
 * @return data the data read
 */
static inline uint32_t SDHC_HAL_GetData(uint32_t baseAddr)
{
    return BR_SDHC_DATPORT_DATCONT(baseAddr);
}

/*!
 * @brief Checks whether the command inhibit bit is set or not.
 *
 * @param baseAddr SDHC base address
 * @return 1 if command inhibit, 0 if not.
 */
static inline uint32_t SDHC_HAL_IsCmdInhibit(uint32_t baseAddr)
{
    return BR_SDHC_PRSSTAT_CIHB(baseAddr);
}

/*!
 * @brief Checks whether data inhibit bit is set or not.
 *
 * @param baseAddr SDHC base address
 * @return 1 if data inhibit, 0 if not.
 */
static inline uint32_t SDHC_HAL_IsDataInhibit(uint32_t baseAddr)
{
    return BR_SDHC_PRSSTAT_CDIHB(baseAddr);
}

/*!
 * @brief Checks whether data line is active.
 *
 * @param baseAddr SDHC base address
 * @return 1 if it's active, 0 if not.
 */
static inline uint32_t SDHC_HAL_IsDataLineActive(uint32_t baseAddr)
{
    return BR_SDHC_PRSSTAT_DLA(baseAddr);
}

/*!
 * @brief Checks whether the SD clock is stable or not.
 *
 * @param baseAddr SDHC base address
 * @return 1 if it's stable, 0 if not.
 */
static inline uint32_t SDHC_HAL_IsSdClockStable(uint32_t baseAddr)
{
    return BR_SDHC_PRSSTAT_SDSTB(baseAddr);
}

/*!
 * @brief Checks whether the  IPG clock is off or not.
 *
 * @param baseAddr SDHC base address
 * @return 1 if it's off, 0 if not.
 */
static inline uint32_t SDHC_HAL_IsIpgClockOff(uint32_t baseAddr)
{
    return BR_SDHC_PRSSTAT_IPGOFF(baseAddr);
}

/*!
 * @brief Checks whether the system clock is off or not.
 *
 * @param baseAddr SDHC base address
 * @return 1 if it's off, 0 if not.
 */
static inline uint32_t SDHC_HAL_IsSysClockOff(uint32_t baseAddr)
{
    return BR_SDHC_PRSSTAT_HCKOFF(baseAddr);
}

/*!
 * @brief Checks whether the peripheral clock is off or not.
 *
 * @param baseAddr SDHC base address.
 * @return 1 if it's off, 0 if not.
 */
static inline uint32_t SDHC_HAL_IsPeripheralClockOff(uint32_t baseAddr)
{
    return BR_SDHC_PRSSTAT_PEROFF(baseAddr);
}

/*!
 * @brief Checks whether  the  SD clock is off or not.
 *
 * @param baseAddr SDHC base address
 * @return 1 if it's off, 0 if not.
 */
static inline uint32_t SDHC_HAL_IsSdClkOff(uint32_t baseAddr)
{
    return BR_SDHC_PRSSTAT_SDOFF(baseAddr);
}

/*!
 * @brief Checks whether the write transfer is active or not.
 *
 * @param baseAddr SDHC base address
 * @return 1 if it's active, 0 if not.
 */
static inline uint32_t SDHC_HAL_IsWriteTransferActive(uint32_t baseAddr)
{
    return BR_SDHC_PRSSTAT_WTA(baseAddr);
}

/*!
 * @brief Checks whether the read transfer is active or not.
 *
 * @param baseAddr SDHC base address
 * @return 1 if it's off, 0 if not.
 */
static inline uint32_t SDHC_HAL_IsReadTransferActive(uint32_t baseAddr)
{
    return BR_SDHC_PRSSTAT_RTA(baseAddr);
}

/*!
 * @brief Check whether the buffer write is enabled or not.
 *
 * @param baseAddr SDHC base address
 * @return 1 if it's isEnabledd, 0 if not.
 */
static inline uint32_t SDHC_HAL_IsBuffWriteEnabled(uint32_t baseAddr)
{
    return BR_SDHC_PRSSTAT_BWEN(baseAddr);
}

/*!
 * @brief Checks whether the buffer read is enabled or not.
 *
 * @param baseAddr SDHC base address
 * @return 1 if it's isEnabledd, 0 if not.
 */
static inline uint32_t SDHC_HAL_IsBuffReadEnabled(uint32_t baseAddr)
{
    return BR_SDHC_PRSSTAT_BREN(baseAddr);
}

/*!
 * @brief Checks whether the  card is inserted or not.
 *
 * @param baseAddr SDHC base address.
 * @return 1 if it's inserted, 0 if not.
 */
static inline uint32_t SDHC_HAL_IsCardInserted(uint32_t baseAddr)
{
    return BR_SDHC_PRSSTAT_CINS(baseAddr);
}

/*!
 * @brief Checks whether the command line signal is high or not.
 *
 * @param baseAddr SDHC base address
 * @return 1 if it's high, 0 if not.
 */
static inline uint32_t SDHC_HAL_IsCmdLineLevelHigh(uint32_t baseAddr)
{
    return BR_SDHC_PRSSTAT_CLSL(baseAddr);
}

/*!
 * @brief Gets the data line signal level or not.
 *
 * @param baseAddr SDHC base address
 * @return [7:0] data line signal level
 */
static inline uint32_t SDHC_HAL_GetDataLineLevel(uint32_t baseAddr)
{
    return BR_SDHC_PRSSTAT_DLSL(baseAddr);
}

/*!
 * @brief Sets the LED state.
 *
 * @param baseAddr SDHC base address
 * @param state the LED state
 */
static inline void SDHC_HAL_SetLedState(uint32_t baseAddr, sdhc_hal_led_t state)
{
    BW_SDHC_PROCTL_LCTL(baseAddr, state);
}

/*!
 * @brief Sets the data transfer width.
 *
 * @param baseAddr SDHC base address
 * @param dtw data transfer width
 */
static inline void SDHC_HAL_SetDataTransferWidth(uint32_t baseAddr, sdhc_hal_dtw_t dtw)
{
    BW_SDHC_PROCTL_DTW(baseAddr, dtw);
}

/*!
 * @brief Checks whether the DAT3 is taken as card detect pin.
 *
 * @param baseAddr SDHC base address
 * @return if DAT3 as card detect pin is enabled
 */
static inline bool SDHC_HAL_IsD3cdEnabled(uint32_t baseAddr)
{
    return BR_SDHC_PROCTL_D3CD(baseAddr);
}

/*!
 * @brief Enables the DAT3 as a card detect pin.
 *
 * @param baseAddr SDHC base address
 * @param enable to enable DAT3 as card detect pin
 */
static inline void SDHC_HAL_SetD3cd(uint32_t baseAddr, bool enable)
{
    BW_SDHC_PROCTL_D3CD(baseAddr, enable ? 1 : 0);
}

/*!
 * @brief Configures the endian mode.
 *
 * @param baseAddr SDHC base address
 * @param endianMode endian mode
 */
static inline void SDHC_HAL_SetEndian(uint32_t baseAddr, sdhc_hal_endian_t endianMode)
{
    BW_SDHC_PROCTL_EMODE(baseAddr, endianMode);
}

/*!
* @brief Gets the card detect test level.
*
* @param baseAddr SDHC base address
* @return card detect test level
*/
static inline uint32_t SDHC_HAL_GetCdTestLevel(uint32_t baseAddr)
{
    return BR_SDHC_PROCTL_CDTL(baseAddr);
}

/*!
* @brief Enables the card detect test.
*
* @param baseAddr SDHC base address
* @param enable to enable card detect signal for test purpose
*/
static inline void SDHC_HAL_SetCdTest(uint32_t baseAddr, bool enable)
{
    BW_SDHC_PROCTL_CDSS(baseAddr, enable ? 1 : 0);
}

/*!
* @brief Sets the DMA mode.
*
* @param baseAddr SDHC base address
* @param dmaMode the DMA mode
*/
static inline void SDHC_HAL_SetDmaMode(uint32_t baseAddr, sdhc_hal_dma_mode_t dmaMode)
{
    BW_SDHC_PROCTL_DMAS(baseAddr, dmaMode);
}

/*!
* @brief Enables stop at the block gap.
*
* @param baseAddr SDHC base address
* @param enable to stop at block gap request
*/
static inline void SDHC_HAL_SetStopAtBlockGap(uint32_t baseAddr, bool enable)
{
    BW_SDHC_PROCTL_SABGREQ(baseAddr, enable ? 1 : 0);
}

/*!
* @brief Restarts a transaction which has stopped at the block gap.
*
* @param baseAddr SDHC base address
*/
static inline void SDHC_HAL_SetContinueRequest(uint32_t baseAddr)
{
    BW_SDHC_PROCTL_CREQ(baseAddr, 1);
}

/*!
* @brief Enables the read wait control for the SDIO cards.
*
* @param baseAddr SDHC base address
* @param enable to enable read wait control
*/
static inline void SDHC_HAL_SetReadWaitCtrl(uint32_t baseAddr, bool enable)
{
    BW_SDHC_PROCTL_RWCTL(baseAddr, enable ? 1 : 0);
}

/*!
* @brief Enables  stop at the block gap requests.
*
* @param baseAddr SDHC base address
* @param enable to enable interrupt at block gap
*/
static inline void SDHC_HAL_SetIntStopAtBlockGap(uint32_t baseAddr, bool enable)
{
    BW_SDHC_PROCTL_IABG(baseAddr, enable ? 1 : 0);
}

/*!
* @brief Enables wakeup event on the card interrupt.
*
* @param baseAddr SDHC base address
* @param enable to enable wakeup event on card interrupt
*/
static inline void SDHC_HAL_SetWakeupOnCardInt(uint32_t baseAddr, bool enable)
{
    BW_SDHC_PROCTL_WECINT(baseAddr, enable ? 1 : 0);
}

/*!
* @brief Enables wakeup event on the card insertion.
*
* @param baseAddr SDHC base address
* @param enable to enable wakeup event on card insertion
*/
static inline void SDHC_HAL_SetWakeupOnCardInsertion(uint32_t baseAddr, bool enable)
{
    BW_SDHC_PROCTL_WECINS(baseAddr, enable ? 1 : 0);
}

/*!
* @brief Enables  wakeup event on card removal.
*
* @param baseAddr SDHC base address
* @param enable to enable wakeup event on card removal
*/
static inline void SDHC_HAL_SetWakeupOnCardRemoval(uint32_t baseAddr, bool enable)
{
    BW_SDHC_PROCTL_WECRM(baseAddr, enable ? 1 : 0);
}

/*!
* @brief Enables the IPG clock and no automatic clock gating off.
*
* @param baseAddr SDHC base address
* @param enable to enable IPG clock
*/
static inline void SDHC_HAL_SetIpgClock(uint32_t baseAddr, bool enable)
{
    BW_SDHC_SYSCTL_IPGEN(baseAddr, enable ? 1 : 0);
}

/*!
* @brief Enables the system clock and no automatic clock gating off.
*
* @param baseAddr SDHC base address
* @param enable to enable SYS clock
*/
static inline void SDHC_HAL_SetSysClock(uint32_t baseAddr, bool enable)
{
    BW_SDHC_SYSCTL_HCKEN(baseAddr, enable ? 1 : 0);
}

/*!
* @brief Enables the peripheral clock and no automatic clock gating off.
*
* @param baseAddr SDHC base address
* @param enable to enable Peripheral clock
*/
static inline void SDHC_HAL_SetPeripheralClock(uint32_t baseAddr, bool enable)
{
    BW_SDHC_SYSCTL_PEREN(baseAddr, enable ? 1 : 0);
}

/*!
* @brief Enables the SD clock. It should be disabled before changing the SD clock
* frequency.
*
* @param baseAddr SDHC base address
* @param enable to enable SD clock or not 
*/
static inline void SDHC_HAL_SetSdClock(uint32_t baseAddr, bool enable)
{
    BW_SDHC_SYSCTL_SDCLKEN(baseAddr, enable ? 1 : 0);
}

/*!
* @brief Sets the SD clock frequency divisor.
*
* @param baseAddr SDHC base address
* @param divisor the divisor
*/
static inline void SDHC_HAL_SetClockDivisor(uint32_t baseAddr, uint32_t divisor)
{
    BW_SDHC_SYSCTL_DVS(baseAddr, divisor);
}

/*!
* @brief Sets the SD clock frequency select.
*
* @param baseAddr SDHC base address
* @param frequency the frequency selector
*/
static inline void SDHC_HAL_SetClockFrequency(uint32_t baseAddr, uint32_t frequency)
{
    BW_SDHC_SYSCTL_SDCLKFS(baseAddr, frequency);
}

/*!
* @brief Sets the data timeout counter value.
*
* @param baseAddr SDHC base address
* @param timeout Data timeout counter value
*/
static inline void SDHC_HAL_SetDataTimeout(uint32_t baseAddr, uint32_t timeout)
{
    BW_SDHC_SYSCTL_DTOCV(baseAddr, timeout);
}

/*!
* @brief Gets the current interrupt status.
*
* @param baseAddr SDHC base address
* @return current interrupt flags
*/
static inline uint32_t SDHC_HAL_GetIntFlags(uint32_t baseAddr)
{
    return HW_SDHC_IRQSTAT_RD(baseAddr);
}

/*!
* @brief Clears a specified interrupt status.
*
* @param baseAddr SDHC base address
* @param mask to specify interrupts' flags to be cleared
*/
static inline void SDHC_HAL_ClearIntFlags(uint32_t baseAddr, uint32_t mask)
{
    HW_SDHC_IRQSTAT_WR(baseAddr, mask);
}

/*!
* @brief Gets the currently enabled interrupt signal.
*
* @param baseAddr SDHC base address
* @return currently enabled interrupt signal
*/
static inline uint32_t SDHC_HAL_GetIntSignal(uint32_t baseAddr)
{
    return HW_SDHC_IRQSIGEN_RD(baseAddr);
}

/*!
* @brief Gets the currently enabled interrupt state.
*
* @param baseAddr SDHC base address
* @return currently enabled interrupts' state
*/
static inline uint32_t SDHC_HAL_GetIntState(uint32_t baseAddr)
{
    return HW_SDHC_IRQSTATEN_RD(baseAddr);
}

/*!
* @brief Gets the auto cmd12 error.
*
* @param baseAddr SDHC base address
* @return auto cmd12 error status
*/
static inline uint32_t SDHC_HAL_GetAc12Error(uint32_t baseAddr)
{
    return HW_SDHC_AC12ERR_RD(baseAddr);
}

/*!
* @brief Gets the maximum block length supported.
*
* @param baseAddr SDHC base address
* @return the maximum block length support
*/
static inline uint32_t SDHC_HAL_GetMaxBlockLength(uint32_t baseAddr)
{
    return BR_SDHC_HTCAPBLT_MBL(baseAddr);
}

/*!
* @brief Checks whether the ADMA is supported.
*
* @param baseAddr SDHC base address
* @return if ADMA is supported
*/
static inline uint32_t SDHC_HAL_DoesHostSupportAdma(uint32_t baseAddr)
{
    return BR_SDHC_HTCAPBLT_ADMAS(baseAddr);
}

/*!
* @brief Checks whether the  high speed is supported.
*
* @param baseAddr SDHC base address
* @return if high speed is supported
*/
static inline uint32_t SDHC_HAL_DoesHostSupportHighspeed(uint32_t baseAddr)
{
    return BR_SDHC_HTCAPBLT_HSS(baseAddr);
}

/*!
* @brief Checks whether the  DMA is supported.
*
* @param baseAddr SDHC base address
* @return if high speed is supported
*/
static inline uint32_t SDHC_HAL_DoesHostSupportDma(uint32_t baseAddr)
{
    return BR_SDHC_HTCAPBLT_DMAS(baseAddr);
}

/*!
* @brief Checks whether the suspend/resume is supported.
*
* @param baseAddr SDHC base address
* @return if suspend and resume is supported
*/
static inline uint32_t SDHC_HAL_DoesHostSupportSuspendResume(uint32_t baseAddr)
{
    return BR_SDHC_HTCAPBLT_SRS(baseAddr);
}

/*!
* @brief Checks whether the  voltage 3.3 is supported.
*
* @param baseAddr SDHC base address
* @return if voltage 3.3 is supported
*/
static inline uint32_t SDHC_HAL_DoesHostSupportV330(uint32_t baseAddr)
{
    return BR_SDHC_HTCAPBLT_VS33(baseAddr);
}

/*!
* @brief Checks whether the  voltage 3.0 is supported.
*
* @param baseAddr SDHC base address
* @return if voltage 3.0 is supported
*/
static inline uint32_t SDHC_HAL_DoesHostSupportV300(uint32_t baseAddr)
{
#if defined(FSL_FEATURE_SDHC_HAS_V300_SUPPORT) && FSL_FEATURE_SDHC_HAS_V300_SUPPORT
    return BR_SDHC_HTCAPBLT_VS30(baseAddr);
#else
    return 0;
#endif
}

/*!
* @brief Checks whether the voltage 1.8 is supported.
*
* @param baseAddr SDHC base address
* @return if voltage 1.8 is supported
*/
static inline uint32_t SDHC_HAL_DoesHostSupportV180(uint32_t baseAddr)
{
#if defined(FSL_FEATURE_SDHC_HAS_V180_SUPPORT) && FSL_FEATURE_SDHC_HAS_V180_SUPPORT
    return BR_SDHC_HTCAPBLT_VS18(baseAddr);
#else
    return 0;
#endif
}

/*!
* @brief Sets the watermark for writing.
*
* @param baseAddr SDHC base address
* @param watermark for writing
*/
static inline void SDHC_HAL_SetWriteWatermarkLevel(uint32_t baseAddr, uint32_t watermark)
{
    BW_SDHC_WML_WRWML(baseAddr, watermark);
}

/*!
* @brief Sets the watermark for reading.
*
* @param baseAddr SDHC base address
* @param watermark for reading
*/
static inline void SDHC_HAL_SetReadWatermarkLevel(uint32_t baseAddr, uint32_t watermark)
{
    BW_SDHC_WML_RDWML(baseAddr, watermark);
}

/*!
* @brief Sets the force events according to the given mask.
*
* @param baseAddr SDHC base address
* @param mask to specify the force events' flags to be set
*/
static inline void SDHC_HAL_SetForceEventFlags(uint32_t baseAddr, uint32_t mask)
{
    HW_SDHC_FEVT_WR(baseAddr, mask);
}

/*!
* @brief Checks whether the ADMA error is length mismatch.
*
* @param baseAddr SDHC base address
* @return if ADMA error is length mismatch
*/
static inline uint32_t SDHC_HAL_IsAdmaLengthMismatchError(uint32_t baseAddr)
{
    return BR_SDHC_ADMAES_ADMALME(baseAddr);
}

/*!
* @brief Checks the SD clock.
*
* Checks whether the clock to the SD is enabled.
*
* @param baseAddr SDHC base address
* @return true if enabled
*/
static inline bool SDHC_HAL_IsSdClockOff(uint32_t baseAddr)
{
    return BR_SDHC_SYSCTL_SDCLKEN(baseAddr);
}

/*!
* @brief Returns the state of the ADMA error.
*
* @param baseAddr SDHC base address
* @return error state
*/
static inline uint32_t SDHC_HAL_GetAdmaErrorState(uint32_t baseAddr)
{
    return BR_SDHC_ADMAES_ADMAES(baseAddr);
}

/*!
* @brief Checks whether the  ADMA error is a descriptor error.
*
* @param baseAddr SDHC base address
* @return if ADMA error is descriptor error
*/
static inline uint32_t SDHC_HAL_IsAdmaDescriptionError(uint32_t baseAddr)
{
    return BR_SDHC_ADMAES_ADMADCE(baseAddr);
}

/*!
* @brief Sets the ADMA address.
*
* @param baseAddr SDHC base address
* @param address for ADMA transfer
*/
static inline void SDHC_HAL_SetAdmaAddress(uint32_t baseAddr, uint32_t address)
{
    HW_SDHC_ADSADDR_WR(baseAddr, address);
}

/*!
* @brief Enables the external DMA request.
*
* @param baseAddr SDHC base address
* @param enable to external DMA
*/
static inline void SDHC_HAL_SetExternalDmaRequest(uint32_t baseAddr, bool enable)
{
    BW_SDHC_VENDOR_EXTDMAEN(baseAddr, enable ? 1 : 0);
}

/*!
* @brief Enables the exact block number for the SDIO CMD53.
*
* @param baseAddr SDHC base address
* @param enable to enable exact block number block read for SDIO CMD53
*/
static inline void SDHC_HAL_SetExactBlockNumber(uint32_t baseAddr, bool enable)
{
    BW_SDHC_VENDOR_EXBLKNU(baseAddr, enable ? 1 : 0);
}

/*!
* @brief Sets the timeout value for the boot ACK.
*
* @param baseAddr SDHC base address
* @param timeout boot ack time out counter value
*/
static inline void SDHC_HAL_SetBootAckTimeout(uint32_t baseAddr, uint32_t timeout)
{
    BW_SDHC_MMCBOOT_DTOCVACK(baseAddr, timeout);
}

/*!
* @brief Enables the boot ACK.
*
* @param baseAddr SDHC base address
* @param enable to enable boot ack mode
*/
static inline void SDHC_HAL_SetBootAck(uint32_t baseAddr, bool enable)
{
    BW_SDHC_MMCBOOT_BOOTACK(baseAddr, enable ? 1 : 0);
}

/*!
* @brief Configures the boot mode.
*
* @param baseAddr SDHC base address
* @param mode the boot mode
*/
static inline void SDHC_HAL_SetBootMode(uint32_t baseAddr, sdhc_hal_mmcboot_t mode)
{
    BW_SDHC_MMCBOOT_BOOTMODE(baseAddr, mode);
}

/*!
* @brief Enables the fast boot.
*
* @param baseAddr SDHC base address
* @param enable to enable fast boot
*/
static inline void SDHC_HAL_SetFastboot(uint32_t baseAddr, bool enable)
{
    BW_SDHC_MMCBOOT_BOOTEN(baseAddr, enable ? 1 : 0);
}

/*!
* @brief Enables the automatic stop at the block gap.
*
* @param baseAddr SDHC base address
* @param enable to enable auto stop at block gap function, when boot.
*/
static inline void SDHC_HAL_SetAutoStopAtBlockGap(uint32_t baseAddr, bool enable)
{
    BW_SDHC_MMCBOOT_AUTOSABGEN(baseAddr, enable ? 1 : 0);
}

/*!
* @brief Configures the the block count for the boot.
*
* @param baseAddr SDHC base address
* @param blockCount the block count for boot
*/
static inline void SDHC_HAL_SetBootBlockCount(uint32_t baseAddr, uint32_t blockCount)
{
    BW_SDHC_MMCBOOT_BOOTBLKCNT(baseAddr, blockCount);
}

/*!
* @brief Gets a specification version.
*
* @param baseAddr SDHC base address
* @return specification version
*/
static inline uint32_t SDHC_HAL_GetSpecificationVersion(uint32_t baseAddr)
{
    return BR_SDHC_HOSTVER_SVN(baseAddr);
}

/*!
* @brief Gets the vendor version.
*
* @param baseAddr SDHC base address
* @return vendor version
*/
static inline uint32_t SDHC_HAL_GetVendorVersion(uint32_t baseAddr)
{
    return BR_SDHC_HOSTVER_VVN(baseAddr);
}

/*!
 * @brief Gets the command response.
 *
 * @param baseAddr SDHC base address
 * @param index of response register, range from 0 to 3
 */
uint32_t SDHC_HAL_GetResponse(uint32_t baseAddr, uint32_t index);

/*!
* @brief Enables the specified interrupts.
*
* @param baseAddr SDHC base address
* @param enable enable or disable
* @param mask to specify interrupts to be isEnabledd
*/
void SDHC_HAL_SetIntSignal(uint32_t baseAddr, bool enable, uint32_t mask);

/*!
* @brief Enables the specified interrupt state.
*
* @param baseAddr SDHC base address
* @param enable enable or disable
* @param mask to specify interrupts' state to be enabled
*/
void SDHC_HAL_SetIntState(uint32_t baseAddr, bool enable, uint32_t mask);

/*!
* @brief Performs an SDHC reset.
*
* @param baseAddr SDHC base address
* @param type the type of reset
* @param timeout timeout for reset
* @return 0 on success, else on error
*/
uint32_t SDHC_HAL_Reset(uint32_t baseAddr, uint32_t type, uint32_t timeout);

/*!
* @brief Sends 80 clocks to the card to initialize the card.
*
* @param baseAddr SDHC base address
* @param timeout timeout for initialize card
* @return 0 on success, else on error
*/
uint32_t SDHC_HAL_InitCard(uint32_t baseAddr, uint32_t timeout);

/*!
* @brief Gets the IRQ ID for a given host controller.
*
* @param baseAddr SDHC base address
* @return IRQ number for specific SDHC instance
*/
IRQn_Type SDHC_HAL_GetIrqId(uint32_t baseAddr);

/*!
 * @brief Initializes the SDHC HAL.
 *
 * @param baseAddr SDHC base address
 */
void SDHC_HAL_Init(uint32_t baseAddr);

/*@} */
#if defined(__cplusplus)
}
#endif
/*! @} */

#endif /* MBED_NO_SDHC */

#endif

/*************************************************************************************************
 * EOF
 ************************************************************************************************/

