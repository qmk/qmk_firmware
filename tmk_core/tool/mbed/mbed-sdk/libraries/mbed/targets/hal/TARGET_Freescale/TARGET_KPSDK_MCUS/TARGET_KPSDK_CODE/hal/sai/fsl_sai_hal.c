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
 
#include "fsl_sai_hal.h"

/******************************************************************************
*Code
******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_TxInit
 * Description   : Initialize the sai Tx register, just set the register vaule to zero.
 *This function just clear the register value of sai.
 *END**************************************************************************/
void SAI_HAL_TxInit(uint32_t saiBaseAddr)
{
    /* Software reset and FIFO reset */
    BW_I2S_TCSR_SR(saiBaseAddr, 1);
    BW_I2S_TCSR_FR(saiBaseAddr, 1);
    /* Clear all registers */
    HW_I2S_TCSR_WR(saiBaseAddr, 0);
    HW_I2S_TCR1_WR(saiBaseAddr, 0);
    HW_I2S_TCR2_WR(saiBaseAddr, 0);
    HW_I2S_TCR3_WR(saiBaseAddr, 0);
    HW_I2S_TCR4_WR(saiBaseAddr, 0);
    HW_I2S_TCR5_WR(saiBaseAddr, 0);
    HW_I2S_TMR_WR(saiBaseAddr,0);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_RxInit
 * Description   : Initialize the sai Rx register, just set the register vaule to zero.
 *This function just clear the register value of sai.
 *END**************************************************************************/
void SAI_HAL_RxInit(uint32_t saiBaseAddr)
{
    /* Software reset and FIFO reset */
    BW_I2S_RCSR_SR(saiBaseAddr, 1);
    BW_I2S_RCSR_FR(saiBaseAddr, 1);
    /* Clear all registers */
    HW_I2S_RCSR_WR(saiBaseAddr, 0);
    HW_I2S_RCR1_WR(saiBaseAddr, 0);
    HW_I2S_RCR2_WR(saiBaseAddr, 0);
    HW_I2S_RCR3_WR(saiBaseAddr, 0);
    HW_I2S_RCR4_WR(saiBaseAddr, 0);
    HW_I2S_RCR5_WR(saiBaseAddr, 0);
    HW_I2S_RMR_WR(saiBaseAddr,0);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_TxSetProtocol
 * Description   : According to the protocol type to set the registers for tx.
 *The protocol can be I2S left, I2S right, I2S and so on.
 *END**************************************************************************/
void SAI_HAL_TxSetProtocol(uint32_t saiBaseAddr,sai_protocol_t protocol)
{
    switch (protocol)
    {
        case kSaiBusI2SLeft:
            BW_I2S_TCR2_BCP(saiBaseAddr,1);/* Bit clock polarity */
            BW_I2S_TCR4_MF(saiBaseAddr,1);/* MSB transmitted fisrt */
            BW_I2S_TCR4_FSE(saiBaseAddr,0);/*Frame sync not early */
            BW_I2S_TCR4_FSP(saiBaseAddr,0);/* Frame sync polarity, left channel is high */
            BW_I2S_TCR4_FRSZ(saiBaseAddr,1);/* I2S uses 2 word in a frame */
            break;

        case kSaiBusI2SRight:
            BW_I2S_TCR2_BCP(saiBaseAddr,1);/* Bit clock polarity */
            BW_I2S_TCR4_MF(saiBaseAddr,1);/* MSB transmitted firsrt */
            BW_I2S_TCR4_FSE(saiBaseAddr,0);/*Frame sync not early */
            BW_I2S_TCR4_FSP(saiBaseAddr,0);/* Frame sync polarity, left chennel is high */
            BW_I2S_TCR4_FRSZ(saiBaseAddr,1);/* I2S uses 2 word in a frame */
            break;

        case kSaiBusI2SType:
            BW_I2S_TCR2_BCP(saiBaseAddr,1);/*Bit clock polarity */
            BW_I2S_TCR4_MF(saiBaseAddr,1);/*MSB transmitted firsrt */
            BW_I2S_TCR4_FSE(saiBaseAddr,1);/* Frame sync one bit early */
            BW_I2S_TCR4_FSP(saiBaseAddr,1);/* Frame sync polarity, left channel is low */
            BW_I2S_TCR4_FRSZ(saiBaseAddr,1);/* I2S uses 2 word in a frame */
            break;

        case kSaiBusPCMA:
            BW_I2S_TCR2_BCP(saiBaseAddr,0); /* Bit clock active low */
            BW_I2S_TCR4_MF(saiBaseAddr, 1); /* MSB transmitted first */
            BW_I2S_TCR4_SYWD(saiBaseAddr, 0); /* Only one bit clock in a frame sync */
            BW_I2S_TCR4_FSE(saiBaseAddr,1);/* Frame sync one bit early */
            BW_I2S_TCR4_FSP(saiBaseAddr,0);/* Frame sync polarity, left chennel is high */                
            BW_I2S_TCR4_FRSZ(saiBaseAddr,1);/* I2S uses 2 word in a frame */
            break;
            
        case kSaiBusPCMB:
            BW_I2S_TCR2_BCP(saiBaseAddr,0); /* Bit clock active high */
            BW_I2S_TCR4_MF(saiBaseAddr, 1); /* MSB transmitted first */
            BW_I2S_TCR4_FSE(saiBaseAddr,0);/* Frame sync not early */
            BW_I2S_TCR4_SYWD(saiBaseAddr, 0); /* Only one bit clock in a frame sync */
            BW_I2S_TCR4_FSP(saiBaseAddr,0);/* Frame sync polarity, left chennel is high */                
            BW_I2S_TCR4_FRSZ(saiBaseAddr,1);/* I2S uses 2 word in a frame */                
            break;
            
        case kSaiBusAC97:
            BW_I2S_TCR2_BCP(saiBaseAddr,1); /* Bit clock active high */
            BW_I2S_TCR4_MF(saiBaseAddr,1); /* MSB transmitted first */
            BW_I2S_TCR4_FSE(saiBaseAddr,1);/* Frame sync one bit early */
            BW_I2S_TCR4_FRSZ(saiBaseAddr,12); /* There are 13 words in a frame in AC'97 */
            BW_I2S_TCR4_SYWD(saiBaseAddr,15); /* Length of frame sync, 16 bit transmitted in first word */
            BW_I2S_TCR5_W0W(saiBaseAddr,15); /* The first word have 16 bits */
            BW_I2S_TCR5_WNW(saiBaseAddr,19); /* Other word is 20 bits */
            break;
            
        default:
            break;
        }
}  

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_RxSetProtocol
 * Description   : According to the protocol type to set the registers for rx.
 *The protocol can be I2S left, I2S right, I2S and so on.
 *END**************************************************************************/
void SAI_HAL_RxSetProtocol(uint32_t saiBaseAddr,sai_protocol_t protocol)
{
    switch (protocol)
    {
        case kSaiBusI2SLeft:
            BW_I2S_RCR2_BCP(saiBaseAddr,1);/* Bit clock polarity */
            BW_I2S_RCR4_MF(saiBaseAddr,1);/* MSB transmitted fisrt */
            BW_I2S_RCR4_FSE(saiBaseAddr,0);/*Frame sync one bit early */
            BW_I2S_RCR4_FSP(saiBaseAddr,0);/* Frame sync polarity, left channel is high */
            BW_I2S_RCR4_FRSZ(saiBaseAddr,1);/* I2S uses 2 word in a frame */
            break;

        case kSaiBusI2SRight:
            BW_I2S_RCR2_BCP(saiBaseAddr,1);/* Bit clock polarity */
            BW_I2S_RCR4_MF(saiBaseAddr,1);/* MSB transmitted fisrt */
            BW_I2S_RCR4_FSE(saiBaseAddr,0);/*Frame sync one bit early */
            BW_I2S_RCR4_FSP(saiBaseAddr,0);/* Frame sync polarity, left chennel is high */
            BW_I2S_RCR4_FRSZ(saiBaseAddr,1);/* I2S uses 2 word in a frame */
            break;

        case kSaiBusI2SType:
            BW_I2S_RCR2_BCP(saiBaseAddr,1);/*Bit clock polarity */
            BW_I2S_RCR4_MF(saiBaseAddr,1);/*MSB transmitted fisrt */
            BW_I2S_RCR4_FSE(saiBaseAddr,1);/* Frame sync one bit early */
            BW_I2S_RCR4_FSP(saiBaseAddr,1);/* Frame sync polarity, left channel is low */
            BW_I2S_RCR4_FRSZ(saiBaseAddr,1);/* I2S uses 2 word in a frame */
            break;

        case kSaiBusPCMA:
            BW_I2S_RCR2_BCP(saiBaseAddr,0); /* Bit clock active high */
            BW_I2S_RCR4_MF(saiBaseAddr, 1); /* MSB transmitted first */
            BW_I2S_RCR4_SYWD(saiBaseAddr, 0); /* Only one bit clock in a frame sync */
            BW_I2S_RCR4_FSE(saiBaseAddr,1);/* Frame sync one bit early */
            BW_I2S_RCR4_FSP(saiBaseAddr,0);/* Frame sync polarity, left chennel is high */                
            BW_I2S_RCR4_FRSZ(saiBaseAddr,1);/* I2S uses 2 word in a frame */
            break;
            
        case kSaiBusPCMB:
            BW_I2S_RCR2_BCP(saiBaseAddr,0); /* Bit clock active high */
            BW_I2S_RCR4_MF(saiBaseAddr, 1); /* MSB transmitted first */
            BW_I2S_RCR4_FSE(saiBaseAddr,0);/* Frame sync not early */
            BW_I2S_RCR4_SYWD(saiBaseAddr, 0); /* Only one bit clock in a frame sync */
            BW_I2S_RCR4_FSP(saiBaseAddr,0);/* Frame sync polarity, left chennel is high */                
            BW_I2S_RCR4_FRSZ(saiBaseAddr,1);/* I2S uses 2 word in a frame */                
            break;
            
        case kSaiBusAC97:
            BW_I2S_RCR2_BCP(saiBaseAddr,1); /* Bit clock active high */
            BW_I2S_RCR4_MF(saiBaseAddr,1); /* MSB transmitted first */
            BW_I2S_RCR4_FSE(saiBaseAddr,1);/* Frame sync one bit early */
            BW_I2S_RCR4_FRSZ(saiBaseAddr,12); /* There are 13 words in a frame in AC'97 */
            BW_I2S_RCR4_SYWD(saiBaseAddr,15); /* Length of frame sync, 16 bit transmitted in first word */
            BW_I2S_RCR5_W0W(saiBaseAddr,15); /* The first word have 16 bits */
            BW_I2S_RCR5_WNW(saiBaseAddr,19); /* Other word is 20 bits */
            break;

        default:
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_SetMclkDiv
 * Description   : Set the divider from the clock source to get the master clock.
 *The function would compute the divider number and set the number to the registers.
 *END**************************************************************************/
void SAI_HAL_SetMclkDiv(uint32_t saiBaseAddr, uint32_t mclk, uint32_t src_clk)
{
    uint32_t freq = src_clk;
    uint16_t fract, divide;
    uint32_t remaind = 0;
    uint32_t current_remainder = 0xffffffff;
    uint16_t current_fract = 0;
    uint16_t current_divide = 0;
    uint32_t mul_freq = 0;
    uint32_t max_fract = SAI_FRACT_MAX;
    /*In order to prevent overflow */
    freq /= 10;
    mclk/= 10;
    max_fract = mclk * SAI_DIV_MAX/freq;
    if(max_fract > SAI_FRACT_MAX)
    {
        max_fract = SAI_FRACT_MAX;
    }
    /* Looking for the closet frequency */
    for (fract = 1; fract < max_fract; fract ++)
    {
        mul_freq = freq * fract;
        remaind = mul_freq % mclk;
        divide = mul_freq/mclk;
        /* Find the exactly frequency */
        if (remaind == 0)
        {
            current_fract = fract;
            current_divide = mul_freq/mclk;
            break;
        }
        /* closer to next one */
        if (remaind > mclk/2)
        {
            remaind = mclk - remaind;
            divide += 1;
        }
        /* Update the closest div and fract */
        if (remaind < current_remainder)
        {
            current_fract = fract;
            current_divide = divide;
            current_remainder = remaind;
        }
    }
    BW_I2S_MDR_DIVIDE(saiBaseAddr, current_divide -1);
    /* Waiting for the divider updated */
    while(BR_I2S_MCR_DUF(saiBaseAddr))
    {}
    BW_I2S_MDR_FRACT(saiBaseAddr, current_fract - 1);
    /* Waiting for the divider updated */
    while(BR_I2S_MCR_DUF(saiBaseAddr))
    {}
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_TxSetMasterSlave
 * Description   : Set the tx master or slave mode.
 *The slave or master mode only would affect the clock direction relevant registers.
 *END**************************************************************************/
void SAI_HAL_TxSetMasterSlave(uint32_t saiBaseAddr, sai_master_slave_t master_slave_mode)
{
    if (master_slave_mode == kSaiMaster)
    {
        BW_I2S_TCR2_BCD(saiBaseAddr,1);/* Bit clock generated internal */
        BW_I2S_TCR4_FSD(saiBaseAddr,1);/* Frame sync generated internal */
        BW_I2S_MCR_MOE(saiBaseAddr,1);/* Master clock generated internal */
    }
    else
    {
        BW_I2S_TCR2_BCD(saiBaseAddr,0);/* Bit clock generated external */
        BW_I2S_TCR4_FSD(saiBaseAddr,0);/* Frame sync generated external */
        BW_I2S_MCR_MOE(saiBaseAddr,0);/* Master clock generated external */
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_RxSetMasterSlave
 * Description   : Set the rx master or slave mode.
 *The slave or master mode only would affect the clock direction relevant registers.
 *END**************************************************************************/
void SAI_HAL_RxSetMasterSlave(uint32_t saiBaseAddr, sai_master_slave_t master_slave_mode)
{
    if (master_slave_mode == kSaiMaster)
    {
        BW_I2S_RCR2_BCD(saiBaseAddr,1);/* Bit clock generated internal */
        BW_I2S_RCR4_FSD(saiBaseAddr,1);/* Frame sync generated internal */
        BW_I2S_MCR_MOE(saiBaseAddr,1);/* Master clock generated internal */
    }
    else
    {
        BW_I2S_RCR2_BCD(saiBaseAddr,0);/* Bit clock generated external */
        BW_I2S_RCR4_FSD(saiBaseAddr,0);/* Frame sync generated external */
        BW_I2S_MCR_MOE(saiBaseAddr,0);/* Master clock generated external */
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_TxSetSyncMode
 * Description   : Set the tx sync mode.
 *Theer are four kinds of sync mode, async, sync, sync with other sai tx, sync with other sai rx.
 *END**************************************************************************/
void SAI_HAL_TxSetSyncMode(uint32_t saiBaseAddr, sai_sync_mode_t sync_mode)
{
    switch (sync_mode)
    {
        case kSaiModeAsync:
            BW_I2S_TCR2_SYNC(saiBaseAddr,0);
            break;
        case kSaiModeSync:
            BW_I2S_TCR2_SYNC(saiBaseAddr,1);
            BW_I2S_RCR2_SYNC(saiBaseAddr,0);/* Receiver must be async mode */
            break;
        case kSaiModeSyncWithOtherTx:
            BW_I2S_TCR2_SYNC(saiBaseAddr,2);
            break;
        case kSaiModeSyncWithOtherRx:
            BW_I2S_TCR2_SYNC(saiBaseAddr,3);
            break;
        default:
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_RxSetSyncMode
 * Description   : Set the rx sync mode.
 *Theer are four kinds of sync mode, async, sync, sync with other sai tx, sync with other sai rx.
 *END**************************************************************************/
void SAI_HAL_RxSetSyncMode(uint32_t saiBaseAddr,sai_sync_mode_t sync_mode)
{
    switch (sync_mode)
    {
        case kSaiModeAsync:
            BW_I2S_RCR2_SYNC(saiBaseAddr,0);
            break;
        case kSaiModeSync:
            BW_I2S_RCR2_SYNC(saiBaseAddr,1);
            BW_I2S_TCR2_SYNC(saiBaseAddr,0);/* Receiver must be async mode */
            break;
        case kSaiModeSyncWithOtherTx:
            BW_I2S_RCR2_SYNC(saiBaseAddr,3);
            break;
        case kSaiModeSyncWithOtherRx:
            BW_I2S_RCR2_SYNC(saiBaseAddr,2);
            break;
        default:
            break;
    }    
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_TxSetIntCmd
 * Description   : Enable the interrupt request source for tx.
 *The source can be word start, sync error, FIFO empty, FIFO error and FIFO request.
 *END**************************************************************************/
void SAI_HAL_TxSetIntCmd(uint32_t saiBaseAddr, sai_interrupt_request_t source, bool enable)
{
    switch (source)
    {
        case kSaiIntrequestWordStart:
            BW_I2S_TCSR_WSIE(saiBaseAddr, enable);
            break;
        case kSaiIntrequestSyncError:
            BW_I2S_TCSR_SEIE(saiBaseAddr, enable);
            break;
        case kSaiIntrequestFIFOWarning:
            BW_I2S_TCSR_FWIE(saiBaseAddr, enable);
            break;
        case kSaiIntrequestFIFOError:
            BW_I2S_TCSR_FEIE(saiBaseAddr, enable);
            break;
        case kSaiIntrequestFIFORequest:
            BW_I2S_TCSR_FRIE(saiBaseAddr, enable);
            break;
        default:
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_RxSetIntCmd
 * Description   : Enable the interrupt request source for rx.
 *The source can be word start, sync error, FIFO empty, FIFO error and FIFO request.
 *END**************************************************************************/
void SAI_HAL_RxSetIntCmd(uint32_t saiBaseAddr,sai_interrupt_request_t source,bool enable)
{
    switch(source)
    {
        case kSaiIntrequestWordStart:
            BW_I2S_RCSR_WSIE(saiBaseAddr, enable);
            break;
        case kSaiIntrequestSyncError:
            BW_I2S_RCSR_SEIE(saiBaseAddr, enable);
            break;
        case kSaiIntrequestFIFOWarning:
            BW_I2S_RCSR_FWIE(saiBaseAddr, enable);
            break;
        case kSaiIntrequestFIFOError:
            BW_I2S_RCSR_FEIE(saiBaseAddr, enable);
            break;
        case kSaiIntrequestFIFORequest:
            BW_I2S_RCSR_FRIE(saiBaseAddr, enable);
            break;
        default:
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_TxGetIntCmd
 * Description   : Gets state of tx interrupt source.
 *The source can be word start, sync error, FIFO empty, FIFO error and FIFO request.
 *END**************************************************************************/
bool SAI_HAL_TxGetIntCmd(uint32_t saiBaseAddr, sai_interrupt_request_t source)
{
    bool ret = false;
    switch (source)
    {
        case kSaiIntrequestWordStart:
            ret = BR_I2S_TCSR_WSIE(saiBaseAddr);
            break;
        case kSaiIntrequestSyncError:
            ret = BR_I2S_TCSR_SEIE(saiBaseAddr);
            break;
        case kSaiIntrequestFIFOWarning:
            ret = BR_I2S_TCSR_FWIE(saiBaseAddr);
            break;
        case kSaiIntrequestFIFOError:
            ret = BR_I2S_TCSR_FEIE(saiBaseAddr);
            break;
        case kSaiIntrequestFIFORequest:
            ret = BR_I2S_TCSR_FRIE(saiBaseAddr);
            break;
        default:
            break;
    }
    return ret;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_RxGetIntCmd
 * Description   : Gets state of rx interrupt source.
 *The source can be word start, sync error, FIFO empty, FIFO error and FIFO request.
 *END**************************************************************************/
bool SAI_HAL_RxGetIntCmd(uint32_t saiBaseAddr,sai_interrupt_request_t source)
{
    bool ret = false;
    switch(source)
    {
        case kSaiIntrequestWordStart:
            ret = BR_I2S_RCSR_WSIE(saiBaseAddr);
            break;
        case kSaiIntrequestSyncError:
            ret = BR_I2S_RCSR_SEIE(saiBaseAddr);
            break;
        case kSaiIntrequestFIFOWarning:
            ret = BR_I2S_RCSR_FWIE(saiBaseAddr);
            break;
        case kSaiIntrequestFIFOError:
            ret = BR_I2S_RCSR_FEIE(saiBaseAddr);
            break;
        case kSaiIntrequestFIFORequest:
            ret= BR_I2S_RCSR_FRIE(saiBaseAddr);
            break;
        default:
            break;
    }
    return ret;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_TxSetDmaCmd
 * Description   : Enable the dma request source for tx.
 *The source can be FIFO empty or FIFO request.
 *END**************************************************************************/
void SAI_HAL_TxSetDmaCmd(uint32_t saiBaseAddr, sai_dma_request_t source, bool enable)
{
    switch (source)
    {
        case kSaiDmaReqFIFOWarning:
            BW_I2S_TCSR_FWDE(saiBaseAddr, enable);
            break;
        case kSaiDmaReqFIFORequest:
            BW_I2S_TCSR_FRDE(saiBaseAddr, enable);
            break;
        default:
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_RxSetDmaCmd
 * Description   : Enable the dma request source for rx.
 *The source can be FIFO empty or FIFO request.
 *END**************************************************************************/
void SAI_HAL_RxSetDmaCmd(uint32_t saiBaseAddr,sai_dma_request_t source,bool enable)
{
    switch (source)
    {
        case kSaiDmaReqFIFOWarning:
            BW_I2S_RCSR_FWDE(saiBaseAddr,enable);
            break;
        case kSaiDmaReqFIFORequest:
            BW_I2S_RCSR_FRDE(saiBaseAddr,enable);
            break;
        default:
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_TxGetDmaCmd
 * Description   : Gets state of tx dma request source.
 *The source can be FIFO empty or FIFO request.
 *END**************************************************************************/
bool SAI_HAL_TxGetDmaCmd(uint32_t saiBaseAddr, sai_dma_request_t source)
{
    bool ret = false;
    switch (source)
    {
        case kSaiDmaReqFIFOWarning:
            ret = BR_I2S_TCSR_FWDE(saiBaseAddr);
            break;
        case kSaiDmaReqFIFORequest:
            ret = BR_I2S_TCSR_FRDE(saiBaseAddr);
            break;
        default:
            break;
    }
    return ret;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_RxGetDmaCmd
 * Description   : Gets state of rx dma request source.
 *The source can be FIFO empty or FIFO request.
 *END**************************************************************************/
bool SAI_HAL_RxGetDmaCmd(uint32_t saiBaseAddr,sai_dma_request_t source)
{
    bool ret = false;
    switch (source)
    {
        case kSaiDmaReqFIFOWarning:
            ret = BR_I2S_RCSR_FWDE(saiBaseAddr);
            break;
        case kSaiDmaReqFIFORequest:
            ret = BR_I2S_RCSR_FRDE(saiBaseAddr);
            break;
        default:
            break;
    }
    return ret;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_TxClearStateFlag
 * Description   : Clear the state flag of tx registers.
 *The state flag incudes word start flag, sync error flag and fifo error flag.
 *END**************************************************************************/
void SAI_HAL_TxClearStateFlag(uint32_t saiBaseAddr, sai_state_flag_t flag)
{
    switch (flag)
    {
        case kSaiStateFlagWordStart:
            BW_I2S_TCSR_WSF(saiBaseAddr,1);/* Write logic 1 to clear this bit */
            break;
        case kSaiStateFlagSyncError:
            BW_I2S_TCSR_SEF(saiBaseAddr,1);/* Write logic 1 to clear this bit */
            break;
        case kSaiStateFlagFIFOError:
            BW_I2S_TCSR_FEF(saiBaseAddr,1);/* Write logic 1 to clear this bit */
            break;
        case kSaiStateFlagSoftReset:
            BW_I2S_TCSR_SR(saiBaseAddr, 0);
            break;
        default:
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_RxClearStateFlag
 * Description   : Clear the state flag of rx registers.
 *The state flag incudes word start flag, sync error flag and fifo error flag.
 *END**************************************************************************/
void SAI_HAL_RxClearStateFlag(uint32_t saiBaseAddr,sai_state_flag_t flag)
{
    switch (flag)
    {
        case kSaiStateFlagWordStart:
            BW_I2S_RCSR_WSF(saiBaseAddr,1);/* Write logic 1 to clear this bit */
            break;
        case kSaiStateFlagSyncError:
            BW_I2S_RCSR_SEF(saiBaseAddr,1);/* Write logic 1 to clear this bit */
            break;
        case kSaiStateFlagFIFOError:
            BW_I2S_RCSR_FEF(saiBaseAddr,1);/* Write logic 1 to clear this bit */
            break;
        case kSaiStateFlagSoftReset:
            BW_I2S_RCSR_SR(saiBaseAddr, 0);
            break;
        default:
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_TxSetReset
 * Description   : Reset tx according to reset mode.
 *The reset mode can be software reset and FIFO reset. 
 *END**************************************************************************/
void SAI_HAL_TxSetReset(uint32_t saiBaseAddr, sai_reset_type_t type)
{
    switch (type)
    {
        case kSaiResetTypeSoftware:
            BW_I2S_TCSR_SR(saiBaseAddr,1);
            break;
        case kSaiResetTypeFIFO:
            BW_I2S_TCSR_FR(saiBaseAddr, 1);
            break;
        default:
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_RxSetReset
 * Description   : Reset rx according to reset mode.
 *The reset mode can be software reset and FIFO reset. 
 *END**************************************************************************/
void SAI_HAL_RxSetReset(uint32_t saiBaseAddr,sai_reset_type_t type)
{
    switch (type)
    {
        case kSaiResetTypeSoftware:
            BW_I2S_RCSR_SR(saiBaseAddr,1);
            break;
        case kSaiResetTypeFIFO:
            BW_I2S_RCSR_FR(saiBaseAddr, 1);
            break;
        default:
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_TxSetRunModeCmd
 * Description   : Set the work mode for tx.
 *The work mode have stop mode, debug mode and normal mode. 
 *END**************************************************************************/
void SAI_HAL_TxSetRunModeCmd(uint32_t saiBaseAddr, sai_run_mode_t run_mode, bool enable)
{
    switch (run_mode)
    {
        case kSaiRunModeStop:
            BW_I2S_TCSR_STOPE(saiBaseAddr, enable);/* Stop mode */
            break;
        case kSaiRunModeDebug:
            BW_I2S_TCSR_DBGE(saiBaseAddr, enable);/* Debug mode */
            break;
        default:
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_RxSetRunModeCmd
 * Description   : Set the work mode for rx.
 *The work mode have stop mode, debug mode and normal mode. 
 *END**************************************************************************/
void SAI_HAL_RxSetRunModeCmd(uint32_t saiBaseAddr,sai_run_mode_t run_mode,bool enable)
{
    switch (run_mode)
    {
        case kSaiRunModeStop:
            BW_I2S_RCSR_STOPE(saiBaseAddr, enable);/* Stop mode */
            break;
        case kSaiRunModeDebug:
            BW_I2S_RCSR_DBGE(saiBaseAddr, enable);/* Debug mode */
            break;
        default:
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_TxGetFlagState
 * Description   : Get the state flag value of tx.
 *The state flag includes fifo error, fifo warning, fifo request, software reset,
 * sync error and word start.
 *END**************************************************************************/
bool SAI_HAL_TxGetStateFlag(uint32_t saiBaseAddr,sai_state_flag_t flag)
{
    bool ret = false;
    switch(flag)
    {
        case kSaiStateFlagFIFOError:
            ret = BR_I2S_TCSR_FEF(saiBaseAddr);
            break;
        case kSaiStateFlagFIFORequest:
            ret = BR_I2S_TCSR_FRF(saiBaseAddr);
            break;
        case kSaiStateFlagFIFOWarning:
            ret = BR_I2S_TCSR_FWF(saiBaseAddr);
            break;
        case kSaiStateFlagSoftReset:
            ret = BR_I2S_TCSR_SR(saiBaseAddr);
            break;
        case kSaiStateFlagSyncError:
            ret = BR_I2S_TCSR_SEF(saiBaseAddr);
            break;
        case kSaiStateFlagWordStart:
            ret = BR_I2S_TCSR_WSF(saiBaseAddr);
            break;
        default:
            break;
    }
    return ret;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_RxGetFlagState
 * Description   : Get the state flag value of rx.
 *The state flag includes fifo error, fifo warning, fifo request, software reset,
 * sync error and word start.
 *END**************************************************************************/
bool SAI_HAL_RxGetStateFlag(uint32_t saiBaseAddr,sai_state_flag_t flag)
{
    bool ret = false;
    switch(flag)
    {
        case kSaiStateFlagFIFOError:
            ret = BR_I2S_RCSR_FEF(saiBaseAddr);
            break;
        case kSaiStateFlagFIFORequest:
            ret = BR_I2S_RCSR_FRF(saiBaseAddr);
            break;
        case kSaiStateFlagFIFOWarning:
            ret = BR_I2S_RCSR_FWF(saiBaseAddr);
            break;
        case kSaiStateFlagSoftReset:
            ret = BR_I2S_RCSR_SR(saiBaseAddr);
            break;
        case kSaiStateFlagSyncError:
            ret = BR_I2S_RCSR_SEF(saiBaseAddr);
            break;
        case kSaiStateFlagWordStart:
            ret = BR_I2S_RCSR_WSF(saiBaseAddr);
            break;
        default:
            break;
    }
    return ret;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_ReceiveDataBlocking
 * Description   : Receive data in blocking way.
 *The sending would wait until there is vaild data in FIFO for reading.
 *END**************************************************************************/
uint32_t SAI_HAL_ReceiveDataBlocking(uint32_t saiBaseAddr,uint32_t rx_channel)
{
    assert(rx_channel < FSL_FEATURE_SAI_CHANNEL_COUNT);
    /* Wait while fifo is empty */
    uint8_t w_ptr = BR_I2S_RFRn_WFP(saiBaseAddr,rx_channel);
    uint8_t r_ptr = BR_I2S_RFRn_RFP(saiBaseAddr,rx_channel);
    while(w_ptr == r_ptr)
    {
        w_ptr = BR_I2S_RFRn_WFP(saiBaseAddr,rx_channel);
        r_ptr = BR_I2S_RFRn_RFP(saiBaseAddr,rx_channel);
    }
    return BR_I2S_RDRn_RDR(saiBaseAddr,rx_channel);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_HAL_SendDataBlocking
 * Description   : Send data in blocking way.
 *The sending would wait until there is space for writing.
 *END**************************************************************************/
void SAI_HAL_SendDataBlocking(uint32_t saiBaseAddr,uint32_t tx_channel,uint32_t data)
{
    assert(tx_channel < FSL_FEATURE_SAI_CHANNEL_COUNT);
    /* Wait while fifo is full */
    uint8_t w_ptr = BR_I2S_TFRn_WFP(saiBaseAddr,tx_channel);
    uint8_t r_ptr = BR_I2S_TFRn_RFP(saiBaseAddr,tx_channel);
    while((w_ptr ^ r_ptr) == 0x8)
    {
        w_ptr = BR_I2S_TFRn_WFP(saiBaseAddr,tx_channel);
        r_ptr = BR_I2S_TFRn_RFP(saiBaseAddr,tx_channel);
    }
    BW_I2S_TDRn_TDR(saiBaseAddr, tx_channel, data);
}

