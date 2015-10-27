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
#include "fsl_edma_hal.h"

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_Init
 * Description   : Initializes eDMA module to known state.
 *
 *END**************************************************************************/
void EDMA_HAL_Init(uint32_t baseAddr)
{
    uint32_t i;

    /* Risk there, in SoCs with more than 1 group, we can't set the CR
     * register to 0, or fault may happens. Stange that in K70 spec, 
     * the RM tell the reset value is 0. */
    HW_DMA_CR_WR(baseAddr, 0U);

    for (i = 0; i < FSL_FEATURE_EDMA_MODULE_CHANNEL; i++)
    {
        EDMA_HAL_HTCDClearReg(baseAddr, i);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_CancelTransfer
 * Description   : Cancels the remaining data transfer.
 *
 *END**************************************************************************/
void EDMA_HAL_CancelTransfer(uint32_t baseAddr)
{
    BW_DMA_CR_CX(baseAddr, 1U);
    while (BR_DMA_CR_CX(baseAddr))
    {}
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_ErrorCancelTransfer
 * Description   : Cancels the remaining data transfer and treat it as error.
 *
 *END**************************************************************************/
void EDMA_HAL_ErrorCancelTransfer(uint32_t baseAddr)
{
    BW_DMA_CR_ECX(baseAddr, 1U);
    while (BR_DMA_CR_ECX(baseAddr))
    {}
}

#if (FSL_FEATURE_EDMA_CHANNEL_GROUP_COUNT > 0x1U)
/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_SetGroupPriority
 * Description   :
 *
 *END**************************************************************************/
void EDMA_HAL_SetGroupPriority(uint32_t baseAddr, edma_group_priority_t groupPriority)
{

    if (groupPriority == kEDMAGroup0PriorityLowGroup1PriorityHigh)
    {
        BW_DMA_CR_GRP0PRI(baseAddr, 0U);
        BW_DMA_CR_GRP1PRI(baseAddr, 1U);
    }
    else
    {
        BW_DMA_CR_GRP0PRI(baseAddr, 1U);
        BW_DMA_CR_GRP1PRI(baseAddr, 0U);
    }

}
#endif
/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_SetErrorIntCmd
 * Description   : Enable/Disable error interrupt for channels.
 *
 *END**************************************************************************/
void EDMA_HAL_SetErrorIntCmd(uint32_t baseAddr, bool enable, edma_channel_indicator_t channel)
{

    if (enable)
    {
        HW_DMA_SEEI_WR(baseAddr, channel);
    }
    else
    {
        HW_DMA_CEEI_WR(baseAddr, channel);
    }
}
/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_SetDmaRequestCmd
 * Description   : Enable/Disable dma request for channel or all channels.
 *
 *END**************************************************************************/
void EDMA_HAL_SetDmaRequestCmd(uint32_t baseAddr, edma_channel_indicator_t channel,bool enable)
{

    if (enable)
    {
        HW_DMA_SERQ_WR(baseAddr, channel);
    }
    else
    {
        HW_DMA_CERQ_WR(baseAddr, channel);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_GetErrorIntCmd
 * Description   : Gets eDMA channel error interrupt enable status.
 *
 *END**************************************************************************/
bool EDMA_HAL_GetErrorIntCmd(uint32_t baseAddr, uint32_t channel)
{
    return (bool)((HW_DMA_EEI_RD(baseAddr) >> channel) & 1U);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_HTCDClearReg
 * Description   : Set registers to 0 for hardware TCD of eDMA channel.
 *
 *END**************************************************************************/
void EDMA_HAL_HTCDClearReg(uint32_t baseAddr,uint32_t channel)
{
    HW_DMA_TCDn_SADDR_WR(baseAddr, channel, 0U);
    HW_DMA_TCDn_SOFF_WR(baseAddr, channel, 0U);
    HW_DMA_TCDn_ATTR_WR(baseAddr, channel, 0U);
    HW_DMA_TCDn_NBYTES_MLNO_WR(baseAddr, channel, 0U);
    HW_DMA_TCDn_SLAST_WR(baseAddr, channel, 0U);
    HW_DMA_TCDn_DADDR_WR(baseAddr, channel, 0U);
    HW_DMA_TCDn_DOFF_WR(baseAddr, channel, 0U);
    HW_DMA_TCDn_CITER_ELINKNO_WR(baseAddr, channel, 0U);
    HW_DMA_TCDn_DLASTSGA_WR(baseAddr, channel, 0U);
    HW_DMA_TCDn_CSR_WR(baseAddr, channel, 0U);
    HW_DMA_TCDn_BITER_ELINKNO_WR(baseAddr, channel, 0U);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_HTCDSetAttribute
 * Description   : Configures the transfer attribute for eDMA channel.
 *
 *END**************************************************************************/
void EDMA_HAL_HTCDSetAttribute(
                uint32_t baseAddr, uint32_t channel,
                edma_modulo_t srcModulo, edma_modulo_t destModulo,
                edma_transfer_size_t srcTransferSize, edma_transfer_size_t destTransferSize)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);

    HW_DMA_TCDn_ATTR_WR(baseAddr, channel,
            BF_DMA_TCDn_ATTR_SMOD(srcModulo) | BF_DMA_TCDn_ATTR_DMOD(destModulo) |
            BF_DMA_TCDn_ATTR_SSIZE(srcTransferSize) | BF_DMA_TCDn_ATTR_DSIZE(destTransferSize));

}
/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_SetNbytes
 * Description   : Configures the nbytes for eDMA channel.
 *
 *END**************************************************************************/
void EDMA_HAL_HTCDSetNbytes(uint32_t baseAddr, uint32_t channel, uint32_t nbytes)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);

    if (BR_DMA_CR_EMLM(baseAddr))
    {
        if (!(BR_DMA_TCDn_NBYTES_MLOFFNO_SMLOE(baseAddr, channel) ||
                                 BR_DMA_TCDn_NBYTES_MLOFFNO_DMLOE(baseAddr, channel)))
        {
            BW_DMA_TCDn_NBYTES_MLOFFNO_NBYTES(baseAddr, channel, nbytes);
        }
        else
        {
            BW_DMA_TCDn_NBYTES_MLOFFYES_NBYTES(baseAddr, channel, nbytes);
        }

    }
    else
    {
        BW_DMA_TCDn_NBYTES_MLOFFNO_NBYTES(baseAddr, channel, nbytes);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_GetHTCDNbytes
 * Description   : Get nbytes configuration data.
 *
 *END**************************************************************************/
uint32_t EDMA_HAL_HTCDGetNbytes(uint32_t baseAddr, uint32_t channel)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);

    if (BR_DMA_CR_EMLM(baseAddr))
    {
        if (BR_DMA_TCDn_NBYTES_MLOFFYES_SMLOE(baseAddr, channel) ||
                BR_DMA_TCDn_NBYTES_MLOFFYES_SMLOE(baseAddr, channel))
        {
            return BR_DMA_TCDn_NBYTES_MLOFFYES_NBYTES(baseAddr, channel);
        }
        else
        {
            return BR_DMA_TCDn_NBYTES_MLOFFNO_NBYTES(baseAddr, channel);
        }
    }
    else
    {
        return BR_DMA_TCDn_NBYTES_MLNO_NBYTES(baseAddr, channel);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_HTCD_SetMinorLoopOffset
 * Description   : Configures the minorloop offset for the hardware TCD.
 *
 *END**************************************************************************/
void EDMA_HAL_HTCDSetMinorLoopOffset(
                uint32_t baseAddr, uint32_t channel, edma_minorloop_offset_config_t *config)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);
    if ((config->enableSrcMinorloop == true) || (config->enableDestMinorloop == true))
    {
        BW_DMA_CR_EMLM(baseAddr, true);
        BW_DMA_TCDn_NBYTES_MLOFFYES_SMLOE(baseAddr, channel, config->enableSrcMinorloop);
        BW_DMA_TCDn_NBYTES_MLOFFYES_DMLOE(baseAddr, channel, config->enableDestMinorloop);
        BW_DMA_TCDn_NBYTES_MLOFFYES_MLOFF(baseAddr, channel, config->offset);
    }
}
/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_HTCDSetScatterGatherLink
 * Description   : Configures the memory address for the next transfer TCD for the hardware TCD.
 *
 *END**************************************************************************/
void EDMA_HAL_HTCDSetScatterGatherLink(
                uint32_t baseAddr, uint32_t channel, edma_software_tcd_t *stcd)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);
    BW_DMA_TCDn_CSR_ESG(baseAddr, channel, true);
    BW_DMA_TCDn_DLASTSGA_DLASTSGA(baseAddr, channel, (uint32_t)stcd);
}
/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_HTCD_SetChannelMinorLink
 * Description   : Set Channel minor link for hardware TCD.
 *
 *END**************************************************************************/
void EDMA_HAL_HTCDSetChannelMinorLink(
                uint32_t baseAddr, uint32_t channel, uint32_t linkChannel, bool enable)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);

    if (enable)
    {
        BW_DMA_TCDn_BITER_ELINKYES_ELINK(baseAddr, channel, enable);
        BW_DMA_TCDn_BITER_ELINKYES_LINKCH(baseAddr, channel, linkChannel);
        BW_DMA_TCDn_CITER_ELINKYES_ELINK(baseAddr, channel, enable);
        BW_DMA_TCDn_CITER_ELINKYES_LINKCH(baseAddr, channel, linkChannel);
    }
    else
    {
        BW_DMA_TCDn_BITER_ELINKNO_ELINK(baseAddr, channel, enable);
        BW_DMA_TCDn_CITER_ELINKNO_ELINK(baseAddr, channel, enable);
    }
}
/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_HTCD_HTCDSetMajorCount
 * Description   : Sets the major iteration count according to minor loop channel link setting.
 *
 *END**************************************************************************/
void EDMA_HAL_HTCDSetMajorCount(uint32_t baseAddr, uint32_t channel, uint32_t count)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);

    if (BR_DMA_TCDn_BITER_ELINKNO_ELINK(baseAddr, channel))
    {
        BW_DMA_TCDn_BITER_ELINKYES_BITER(baseAddr, channel, count);
        BW_DMA_TCDn_CITER_ELINKYES_CITER(baseAddr, channel, count);
    }
    else
    {
        BW_DMA_TCDn_BITER_ELINKNO_BITER(baseAddr, channel, count);
        BW_DMA_TCDn_CITER_ELINKNO_CITER(baseAddr, channel, count);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_HTCD_HTCDSetMajorCount
 * Description   : Gets the begin major iteration count according to minor loop channel link setting.
 *
 *END**************************************************************************/
uint32_t EDMA_HAL_HTCDGetBeginMajorCount(uint32_t baseAddr, uint32_t channel)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);

    if (BR_DMA_TCDn_BITER_ELINKNO_ELINK(baseAddr, channel))
    {
        return BR_DMA_TCDn_BITER_ELINKYES_BITER(baseAddr, channel);
    }
    else
    {
        return BR_DMA_TCDn_BITER_ELINKNO_BITER(baseAddr, channel);
    }    
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_HTCD_HTCDGetCurrentMajorCount
 * Description   : Gets the current major iteration count according to minor loop channel link setting.
 *
 *END**************************************************************************/
uint32_t EDMA_HAL_HTCDGetCurrentMajorCount(uint32_t baseAddr, uint32_t channel)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);

    if (BR_DMA_TCDn_BITER_ELINKNO_ELINK(baseAddr, channel))
    {
        return BR_DMA_TCDn_CITER_ELINKYES_CITER(baseAddr, channel);
    }
    else
    {
        return BR_DMA_TCDn_CITER_ELINKNO_CITER(baseAddr, channel);
    }    
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_HTCDGetUnfinishedBytes
 * Description   : Get the bytes number of bytes haven't been transferred for this hardware TCD.
 *
 *END**************************************************************************/
uint32_t EDMA_HAL_HTCDGetUnfinishedBytes(uint32_t baseAddr, uint32_t channel)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);

    uint32_t nbytes;

    nbytes = EDMA_HAL_HTCDGetNbytes(baseAddr, channel);

    if (BR_DMA_TCDn_BITER_ELINKNO_ELINK(baseAddr, channel))
    {
        return (BR_DMA_TCDn_CITER_ELINKYES_CITER(baseAddr, channel) * nbytes);

    }
    else
    {
        return (BR_DMA_TCDn_CITER_ELINKNO_CITER(baseAddr, channel) * nbytes);

    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_HTCDGetFinishedBytes
 * Description   : Get the bytes number of bytes already be transferred for this hardware TCD.
 *
 *END**************************************************************************/
uint32_t EDMA_HAL_HTCDGetFinishedBytes(uint32_t baseAddr, uint32_t channel)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);

    uint32_t nbytes, begin_majorcount, current_majorcount;

    nbytes = EDMA_HAL_HTCDGetNbytes(baseAddr, channel);
    begin_majorcount = EDMA_HAL_HTCDGetBeginMajorCount(baseAddr,channel);
    current_majorcount = EDMA_HAL_HTCDGetCurrentMajorCount(baseAddr,channel);

    return ((begin_majorcount - current_majorcount) * nbytes);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_STCDSetAttribute
 * Description   : Configures the transfer attribute for software TCD.
 *
 *END**************************************************************************/
void EDMA_HAL_STCDSetAttribute(
                edma_software_tcd_t *stcd,
                edma_modulo_t srcModulo, edma_modulo_t destModulo,
                edma_transfer_size_t srcTransferSize, edma_transfer_size_t destTransferSize)
{
    assert(stcd);

    stcd->ATTR = DMA_ATTR_SMOD(srcModulo) | DMA_ATTR_DMOD(destModulo) |
                    DMA_ATTR_SSIZE(srcTransferSize) | DMA_ATTR_DSIZE(destTransferSize);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_STCDSetNbytes
 * Description   : Configures the nbytes for software TCD
 *
 *END**************************************************************************/
void EDMA_HAL_STCDSetNbytes(uint32_t baseAddr, edma_software_tcd_t *stcd, uint32_t nbytes)
{
    assert(stcd);

    if (BR_DMA_CR_EMLM(baseAddr))
    {
        if (stcd->NBYTES.MLOFFNO | (DMA_NBYTES_MLOFFNO_SMLOE_MASK | DMA_NBYTES_MLOFFNO_DMLOE_MASK))
        {
            stcd->NBYTES.MLOFFYES = (stcd->NBYTES.MLOFFYES & ~DMA_NBYTES_MLOFFYES_NBYTES_MASK) |
                            DMA_NBYTES_MLOFFYES_NBYTES(nbytes);
        }
        else
        {
            stcd->NBYTES.MLOFFNO = (stcd->NBYTES.MLOFFNO & ~DMA_NBYTES_MLOFFNO_NBYTES_MASK) |
                             DMA_NBYTES_MLOFFNO_NBYTES(nbytes);
        }
    }
    else
    {
        stcd->NBYTES.MLNO = (stcd->NBYTES.MLNO & ~DMA_NBYTES_MLNO_NBYTES_MASK) |
                         DMA_NBYTES_MLNO_NBYTES(nbytes);
    }

}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_STCDSetMinorLoopOffset
 * Description   :
 *
 *END**************************************************************************/
void EDMA_HAL_STCDSetMinorLoopOffset(
                uint32_t baseAddr, edma_software_tcd_t *stcd, edma_minorloop_offset_config_t *config)
{
    assert(stcd);
    stcd->NBYTES.MLOFFYES = (stcd->NBYTES.MLOFFYES &
            ~(DMA_NBYTES_MLOFFYES_SMLOE_MASK | DMA_NBYTES_MLOFFYES_DMLOE_MASK)) |
            (((uint32_t)config->enableSrcMinorloop << DMA_NBYTES_MLOFFYES_SMLOE_SHIFT) |
            ((uint32_t)config->enableDestMinorloop << DMA_NBYTES_MLOFFYES_DMLOE_SHIFT));

    if ((config->enableSrcMinorloop == true) || (config->enableDestMinorloop == true))
    {
        BW_DMA_CR_EMLM(baseAddr, true);
        stcd->NBYTES.MLOFFYES = (stcd->NBYTES.MLOFFYES & ~DMA_NBYTES_MLOFFYES_MLOFF_MASK) |
                                    DMA_NBYTES_MLOFFYES_MLOFF(config->offset);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name :
 * Description   :
 *
 *END**************************************************************************/
void EDMA_HAL_STCDSetScatterGatherLink(
                edma_software_tcd_t *stcd, edma_software_tcd_t *nextStcd)
{
    assert(stcd);
    assert(nextStcd);
    EDMA_HAL_STCDSetScatterGatherCmd(stcd, true);
    stcd->DLAST_SGA = DMA_DLAST_SGA_DLASTSGA((uint32_t)nextStcd);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_STCDSetChannelMinorLink
 * Description   :
 *
 *END**************************************************************************/
void EDMA_HAL_STCDSetChannelMinorLink(
                edma_software_tcd_t *stcd, uint32_t linkChannel, bool enable)
{
    assert(stcd);

    if (enable)
    {
        stcd->BITER.ELINKYES = (stcd->BITER.ELINKYES & ~DMA_BITER_ELINKYES_ELINK_MASK) |
                            ((uint32_t)enable << DMA_BITER_ELINKYES_ELINK_SHIFT);
        stcd->BITER.ELINKYES = (stcd->BITER.ELINKYES & ~DMA_BITER_ELINKYES_LINKCH_MASK) |
                            DMA_BITER_ELINKYES_LINKCH(linkChannel);
        stcd->CITER.ELINKYES = (stcd->CITER.ELINKYES & ~DMA_CITER_ELINKYES_ELINK_MASK) |
                            ((uint32_t)enable << DMA_CITER_ELINKYES_ELINK_SHIFT);
        stcd->CITER.ELINKYES = (stcd->CITER.ELINKYES & ~DMA_CITER_ELINKYES_LINKCH_MASK) |
                            DMA_CITER_ELINKYES_LINKCH(linkChannel);
    }
    else
    {
        stcd->BITER.ELINKNO = (stcd->BITER.ELINKNO & ~DMA_BITER_ELINKNO_ELINK_MASK) |
                            ((uint32_t)enable << DMA_BITER_ELINKNO_ELINK_SHIFT);
        stcd->CITER.ELINKNO = (stcd->CITER.ELINKNO & ~DMA_CITER_ELINKNO_ELINK_MASK) |
                            ((uint32_t)enable << DMA_CITER_ELINKNO_ELINK_SHIFT);
    }
}
/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_STCDSetMajorCount
 * Description   : Sets the major iteration count according to minor loop channel link setting.
 *
 *END**************************************************************************/
void EDMA_HAL_STCDSetMajorCount(edma_software_tcd_t *stcd, uint32_t count)
{
    assert(stcd);

    if (stcd->BITER.ELINKNO & DMA_BITER_ELINKNO_ELINK_MASK)
    {
        stcd->BITER.ELINKYES = (stcd->BITER.ELINKYES & ~DMA_BITER_ELINKYES_BITER_MASK) |
                            DMA_BITER_ELINKYES_BITER(count);
        stcd->CITER.ELINKYES = (stcd->CITER.ELINKYES & ~DMA_CITER_ELINKYES_CITER_MASK) |
                            DMA_CITER_ELINKYES_CITER(count);
    }
    else
    {
        stcd->BITER.ELINKNO = (stcd->BITER.ELINKNO & ~DMA_BITER_ELINKNO_BITER_MASK) |
                            DMA_BITER_ELINKNO_BITER(count);
        stcd->CITER.ELINKNO = (stcd->CITER.ELINKNO & ~DMA_CITER_ELINKNO_CITER_MASK) |
                            DMA_CITER_ELINKNO_CITER(count);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_PushSTCDToHTCD
 * Description   : Copy the configuration data from the software TCD to hardware TCD.
 *
 *END**************************************************************************/
void EDMA_HAL_PushSTCDToHTCD(uint32_t baseAddr, uint32_t channel, edma_software_tcd_t *stcd)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);
    assert(stcd);

    HW_DMA_TCDn_SADDR_WR(baseAddr, channel, stcd->SADDR);
    HW_DMA_TCDn_SOFF_WR(baseAddr, channel, stcd->SOFF);
    HW_DMA_TCDn_ATTR_WR(baseAddr, channel, stcd->ATTR);
    HW_DMA_TCDn_NBYTES_MLNO_WR(baseAddr, channel, stcd->NBYTES.MLNO);
    HW_DMA_TCDn_SLAST_WR(baseAddr, channel, stcd->SLAST);
    HW_DMA_TCDn_DADDR_WR(baseAddr, channel, stcd->DADDR);
    HW_DMA_TCDn_DOFF_WR(baseAddr, channel, stcd->DOFF);
    HW_DMA_TCDn_CITER_ELINKYES_WR(baseAddr, channel, stcd->CITER.ELINKYES);
    HW_DMA_TCDn_DLASTSGA_WR(baseAddr, channel, stcd->DLAST_SGA);
    HW_DMA_TCDn_CSR_WR(baseAddr, channel, stcd->CSR);
    HW_DMA_TCDn_BITER_ELINKYES_WR(baseAddr, channel, stcd->BITER.ELINKYES);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_SetSTCDBasicTransfer
 * Description   : Set the basic transfer for software TCD.
 *
 *END**************************************************************************/
edma_status_t EDMA_HAL_STCDSetBasicTransfer(
            uint32_t baseAddr, edma_software_tcd_t *stcd, edma_transfer_config_t *config,
            bool enableInt, bool disableDmaRequest)
{
    assert(stcd);

    EDMA_HAL_STCDSetSrcAddr(stcd, config->srcAddr);
    EDMA_HAL_STCDSetDestAddr(stcd, config->destAddr);

    EDMA_HAL_STCDSetSrcOffset(stcd, config->srcOffset);
    EDMA_HAL_STCDSetDestOffset(stcd, config->destOffset);

    EDMA_HAL_STCDSetAttribute(stcd, config->srcModulo, config->destModulo,
            config->srcTransferSize, config->destTransferSize);

    EDMA_HAL_STCDSetSrcLastAdjust(stcd, config->srcLastAddrAdjust);
    EDMA_HAL_STCDSetDestLastAdjust(stcd, config->destLastAddrAdjust);
    EDMA_HAL_STCDSetNbytes(baseAddr, stcd, config->minorLoopCount);
    EDMA_HAL_STCDSetMajorCount(stcd, config->majorLoopCount);

    EDMA_HAL_STCDSetIntCmd(stcd, enableInt);
    EDMA_HAL_STCDSetDisableDmaRequestAfterTCDDoneCmd(stcd, disableDmaRequest);
    return kStatus_EDMA_Success;
}

#if (FSL_FEATURE_EDMA_ASYNCHRO_REQUEST_CHANNEL_COUNT > 0x0U)
/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_HAL_SetAsyncRequestInStopModeCmd
 * Description   : Enables/Disables an asynchronous request in stop mode.
 *
 *END**************************************************************************/
void EDMA_HAL_SetAsyncRequestInStopModeCmd(uint32_t baseAddr, uint32_t channel, bool enable)
{
    assert(channel < FSL_FEATURE_EDMA_MODULE_CHANNEL);

    if(enable) 
    {
        HW_DMA_EARS_SET(baseAddr, 1U << channel);
    }
    else
    {
        HW_DMA_EARS_CLR(baseAddr, 1U << channel);
    }
}
#endif
/*******************************************************************************
 * EOF
 ******************************************************************************/

