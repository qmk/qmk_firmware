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
#include "fsl_lpuart_hal.h"

#ifndef MBED_NO_LPUART

/*******************************************************************************
 * Code
 ******************************************************************************/
/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_HAL_Init
 * Description   : Initializes the LPUART controller to known state.
 *
 *END**************************************************************************/
void LPUART_HAL_Init(uint32_t baseAddr)
{
    HW_LPUART_BAUD_WR(baseAddr, 0x0F000004);
    HW_LPUART_STAT_WR(baseAddr, 0xC01FC000); 
    HW_LPUART_CTRL_WR(baseAddr, 0x00000000);
    HW_LPUART_MATCH_WR(baseAddr, 0x00000000);
    HW_LPUART_MODIR_WR(baseAddr, 0x00000000);    
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_HAL_SetBaudRate
 * Description   : Configures the LPUART baud rate.
 * In some LPUART instances the user must disable the transmitter/receiver
 * before calling this function.
 * Generally, this may be applied to all LPUARTs to ensure safe operation.
 *
 *END**************************************************************************/
lpuart_status_t LPUART_HAL_SetBaudRate(uint32_t baseAddr, uint32_t sourceClockInHz,
                                uint32_t desiredBaudRate)
{
    uint16_t sbr, sbrTemp, i;
    uint32_t osr, tempDiff, calculatedBaud, baudDiff;

    /* This lpuart instantiation uses a slightly different baud rate calculation */
    /* The idea is to use the best OSR (over-sampling rate) possible */
    /* Note, osr is typically hard-set to 16 in other lpuart instantiations */
    /* First calculate the baud rate using the minimum OSR possible (4) */
    osr = 4;
    sbr = (sourceClockInHz/(desiredBaudRate * osr));
    calculatedBaud = (sourceClockInHz / (osr * sbr));

    if (calculatedBaud > desiredBaudRate)
    {
        baudDiff = calculatedBaud - desiredBaudRate;
    }
    else
    {
        baudDiff = desiredBaudRate - calculatedBaud;
    }

    /* loop to find the best osr value possible, one that generates minimum baudDiff */
    /* iterate through the rest of the supported values of osr */
    for (i = 5; i <= 32; i++)
    {
        /* calculate the temporary sbr value   */
        sbrTemp = (sourceClockInHz/(desiredBaudRate * i));
        /* calculate the baud rate based on the temporary osr and sbr values */
        calculatedBaud = (sourceClockInHz / (i * sbrTemp));

        if (calculatedBaud > desiredBaudRate)
        {
            tempDiff = calculatedBaud - desiredBaudRate;
        }
        else
        {
            tempDiff = desiredBaudRate - calculatedBaud;
        }

        if (tempDiff <= baudDiff)
        {
            baudDiff = tempDiff;
            osr = i;  /* update and store the best osr value calculated */
            sbr = sbrTemp;  /* update store the best sbr value calculated */
        }
    }

    /* next, check to see if actual baud rate is within 3% of desired baud rate */
    /* based on the best calculate osr value */
    if (baudDiff < ((desiredBaudRate / 100) * 3))
    {
        /* Acceptable baud rate */
        /* Check if osr is between 4x and 7x oversampling */
        /* If so, then "BOTHEDGE" sampling must be turned on */
        if ((osr > 3) && (osr < 8))
        {
            BW_LPUART_BAUD_BOTHEDGE(baseAddr, 1);
        }

        /* program the osr value (bit value is one less than actual value) */
        BW_LPUART_BAUD_OSR(baseAddr, (osr-1));

        /* write the sbr value to the BAUD registers */
        BW_LPUART_BAUD_SBR(baseAddr, sbr);
    }
    else
    {
        /* Unacceptable baud rate difference of more than 3% */
        return kStatus_LPUART_BaudRatePercentDiffExceeded;
    }

    return kStatus_LPUART_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_HAL_SetBitCountPerChar
 * Description   : Configures the number of bits per character in the LPUART controller.
 * In some LPUART instances, the user should disable the transmitter/receiver
 * before calling this function.
 * Generally, this may be applied to all LPUARTs to ensure safe operation.
 *
 *END**************************************************************************/
void LPUART_HAL_SetBitCountPerChar(uint32_t baseAddr, lpuart_bit_count_per_char_t bitCountPerChar)
{
    if(bitCountPerChar == kLpuart10BitsPerChar)
    {
        BW_LPUART_BAUD_M10(baseAddr, 1); /* set M10 for 10-bit mode, M bit in C1 is don't care */
    }
    else
    {
        BW_LPUART_CTRL_M(baseAddr, bitCountPerChar);  /* config 8- (M=0) or 9-bits (M=1) */
        BW_LPUART_BAUD_M10(baseAddr, 0); /* clear M10 to make sure not 10-bit mode */
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_HAL_SetParityMode
 * Description   : Configures parity mode in the LPUART controller.
 * In some LPUART instances, the user should disable the transmitter/receiver
 * before calling this function.
 * Generally, this may be applied to all LPUARTs to ensure safe operation.
 *
 *END**************************************************************************/
void LPUART_HAL_SetParityMode(uint32_t baseAddr, lpuart_parity_mode_t parityModeType)
{
    /* configure the parity enable/type    */

    if ((parityModeType) == kLpuartParityDisabled)
    {
        /* parity disabled, hence parity type is don't care */
        BW_LPUART_CTRL_PE(baseAddr, 0);
    }
    else
    {
        /* parity enabled */
        BW_LPUART_CTRL_PE(baseAddr, 1);
        /* parity odd/even depending on parity mode setting */
        BW_LPUART_CTRL_PT(baseAddr, (parityModeType) & 0x1);
    }

}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_HAL_SetTxRxInversionCmd
 * Description   : Configures the transmit and receive inversion control in the LPUART controller.
 * This function should only be called when the LPUART is between transmit and receive packets.
 *
 *END**************************************************************************/
void LPUART_HAL_SetTxRxInversionCmd(uint32_t baseAddr, uint32_t rxInvert, uint32_t txInvert)
{
    /* 0 - receive data not inverted, 1 - receive data inverted */
    BW_LPUART_STAT_RXINV(baseAddr, rxInvert);
    /* 0 - transmit data not inverted, 1 - transmit data inverted */
    BW_LPUART_CTRL_TXINV(baseAddr, txInvert);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_HAL_EnableTransmitter
 * Description   : Enables the LPUART transmitter.
 *
 *END**************************************************************************/
void LPUART_HAL_EnableTransmitter(uint32_t baseAddr)
{
    /* enable the transmitter based on the lpuart baseAddr */

    /* for this lpuart baseAddr, there is a two step process to clear the transmit complete */
    /* status flag: */
    /* 1. Read the status register with the status bit set */
    /* 2. enable the transmitter (change TE from 0 to 1) */
    /* first read the status register */

    /* no need to store the read value, it's assumed the status bit is set */
    HW_LPUART_STAT_RD(baseAddr);
    /* second, enable the transmitter */
    BW_LPUART_CTRL_TE(baseAddr, 1);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_HAL_SetIntMode
 * Description   : Configures the LPUART module interrupts to enable/disable various interrupt sources.
 *
 *END**************************************************************************/
void LPUART_HAL_SetIntMode(uint32_t baseAddr, lpuart_interrupt_t interrupt, bool enable)
{
    uint32_t reg = (uint32_t)(interrupt) >> LPUART_SHIFT;
    uint32_t temp = 1U << (uint32_t)interrupt;

    switch ( reg )
    {
        case LPUART_BAUD_REG_ID:
            enable ? HW_LPUART_BAUD_SET(baseAddr, temp) : HW_LPUART_BAUD_CLR(baseAddr, temp);
            break;
        case LPUART_STAT_REG_ID:
            enable ? HW_LPUART_STAT_SET(baseAddr, temp) : HW_LPUART_STAT_CLR(baseAddr, temp);
            break;
        case LPUART_CTRL_REG_ID:
            enable ? HW_LPUART_CTRL_SET(baseAddr, temp) : HW_LPUART_CTRL_CLR(baseAddr, temp);
            break;
        case LPUART_DATA_REG_ID:
            enable ? HW_LPUART_DATA_SET(baseAddr, temp) : HW_LPUART_DATA_CLR(baseAddr, temp);
            break;
        case LPUART_MATCH_REG_ID:
            enable ? HW_LPUART_MATCH_SET(baseAddr, temp) : HW_LPUART_MATCH_CLR(baseAddr, temp);
            break;
        case LPUART_MODIR_REG_ID:
            enable ? HW_LPUART_MODIR_SET(baseAddr, temp) : HW_LPUART_MODIR_CLR(baseAddr, temp);
            break;
        default :
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_HAL_GetIntMode
 * Description   : Returns whether the LPUART module interrupts is enabled/disabled.
 *
 *END**************************************************************************/
bool LPUART_HAL_GetIntMode(uint32_t baseAddr, lpuart_interrupt_t interrupt)
{
    uint32_t reg = (uint32_t)(interrupt) >> LPUART_SHIFT;
	  bool retVal = false;

    switch ( reg )
    {
        case LPUART_BAUD_REG_ID:
            retVal = HW_LPUART_BAUD_RD(baseAddr) >> (uint32_t)(interrupt) & 1U;
            break;
        case LPUART_STAT_REG_ID:
            retVal = HW_LPUART_STAT_RD(baseAddr) >> (uint32_t)(interrupt) & 1U;
            break;
        case LPUART_CTRL_REG_ID:
            retVal = HW_LPUART_CTRL_RD(baseAddr) >> (uint32_t)(interrupt) & 1U;
            break;
        case LPUART_DATA_REG_ID:
            retVal = HW_LPUART_DATA_RD(baseAddr) >> (uint32_t)(interrupt) & 1U;
            break;
        case LPUART_MATCH_REG_ID:
            retVal = HW_LPUART_MATCH_RD(baseAddr) >> (uint32_t)(interrupt) & 1U;
            break;
        case LPUART_MODIR_REG_ID:
            retVal = HW_LPUART_MODIR_RD(baseAddr) >> (uint32_t)(interrupt) & 1U;
            break;
        default :
            break;
    }

    return retVal;
}

#if FSL_FEATURE_LPUART_HAS_DMA_ENABLE 
/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_HAL_ConfigureDma
 * Description   : LPUART configures DMA requests for Transmitter and Receiver.
 *
 *END**************************************************************************/
void LPUART_HAL_ConfigureDma(uint32_t baseAddr, bool txDmaConfig, bool  rxDmaConfig)
{
    /* TDMAE configures the transmit data register empty flag, S1[TDRE], */
    /* to generate a DMA request. */
    BW_LPUART_BAUD_TDMAE(baseAddr, txDmaConfig) ;/* set TDMAE to enable, clear to disable */
    /* RDMAE configures the receive data register fell flag, S1[RDRF], */
    /* to generate a DMA request. */
    BW_LPUART_BAUD_RDMAE(baseAddr, rxDmaConfig); /* set RDMAE to enable, clear to disable  */
}
#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_HAL_GetWaitModeOperationConfig
 * Description   : LPUART configures DMA requests for Transmitter and Receiver.
 *
 *END**************************************************************************/
lpuart_operation_config_t LPUART_HAL_GetWaitModeOperationConfig(uint32_t baseAddr)
{
    /* get configuration lpuart operation in wait mode */
    /* In CPU wait mode: 0 - lpuart clocks continue to run; 1 - lpuart clocks freeze  */
    if (BR_LPUART_CTRL_DOZEEN(baseAddr) == 0)
    {
         return kLpuartOperates;
    }
    else
    {
         return kLpuartStops;
    }

}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_HAL_SedLoopbackCmd
 * Description   : Configures the LPUART loopback operation (enable/disable loopback operation)
 * In some LPUART instances, the user should disable the transmitter/receiver
 * before calling this function.
 * Generally, this may be applied to all LPUARTs to ensure safe operation.
 *
 *END**************************************************************************/
void LPUART_HAL_SedLoopbackCmd(uint32_t baseAddr, bool enable)
{
    /* configure lpuart to enable/disable operation in loopback mode */

    /* configure LOOPS bit to enable(1)/disable(0) loopback mode, but also need to clear RSRC */
    BW_LPUART_CTRL_LOOPS(baseAddr, enable);

    /* clear RSRC for loopback mode, and if loopback disabled, */
    /* this bit has no meaning but clear anyway */
    /* to set it back to default value */
    BW_LPUART_CTRL_RSRC(baseAddr, 0);

}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_HAL_SetSingleWireCmd
 * Description   : Configures the LPUART single-wire operation (enable/disable single-wire mode)
 * In some LPUART instances, the user should disable the transmitter/receiver
 * before calling this function.
 * Generally, this may be applied to all LPUARTs to ensure safe operation.
 *
 *END**************************************************************************/
void LPUART_HAL_SetSingleWireCmd(uint32_t baseAddr, bool enable)
{
    /* configure lpuart to enable/disable operation in single mode */

    /* to enable single-wire mode, need both LOOPS and RSRC set, to disable, clear both */
    BW_LPUART_CTRL_LOOPS(baseAddr, enable);
    BW_LPUART_CTRL_RSRC(baseAddr, enable);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_HAL_PutReceiverInStandbyMode
 * Description   : Places the LPUART receiver in standby mode.
 * In some LPUART instances,
 * before placing LPUART in standby mode, first determine whether the receiver is set to
 * wake on idle or whether it is already in idle state.
 * NOTE that the RWU should only be set with C1[WAKE] = 0 (wakeup on  idle) if the channel is currently
 * not idle.
 * This can be determined by the S2[RAF] flag. If it is set to wake up an IDLE event and the channel is
 * already idle, it is possible that the LPUART will discard data since data must be received
 * (or a LIN break detect) after an IDLE is detected and before IDLE is allowed to reasserted.
 *
 *END**************************************************************************/
lpuart_status_t LPUART_HAL_PutReceiverInStandbyMode(uint32_t baseAddr)
{
    /* In some lpuart instances, there is a condition that must be met before placing */
    /* rx in standby mode. */
    /* Before placing lpuart in standby, need to first determine if receiver is set to */
    /* wake on idle and if receiver is already in idle state. Per ref manual: */
    /* NOTE: RWU should only be set with C1[WAKE] = 0 (wakeup on idle) if the channel is */
    /* currently not idle. */
    /* This can be determined by the STAT[RAF] flag. If set to wake up an IDLE event and */
    /* the channel is already idle, it is possible that the LPUART will discard data since data */
    /* must be received (or a LIN break detect) after an IDLE is detected before IDLE is */
    /* allowed to reasserted. */
    lpuart_wakeup_method_t rxWakeMethod;
    bool lpuart_current_rx_state;

    /* see if wake is set for idle or */
    rxWakeMethod = LPUART_HAL_GetReceiverWakeupMethod(baseAddr);
    lpuart_current_rx_state = LPUART_HAL_GetStatusFlag(baseAddr, kLpuartRxActive);

    /* if both rxWakeMethod is set for idle and current rx state is idle, don't put in standy */
    if ((rxWakeMethod == kLpuartIdleLineWake) && (lpuart_current_rx_state == 0))
    {
        return kStatus_LPUART_RxStandbyModeError;
    }
    else
    {
        /* set the RWU bit to place receiver into standby mode */
        BW_LPUART_CTRL_RWU(baseAddr, 1);
        return kStatus_LPUART_Success;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_HAL_GetReceiverWakeupMethod
 * Description   : Gets the LPUART receiver wakeup method (idle line or addr-mark) from standby mode.
 *
 *END**************************************************************************/
lpuart_wakeup_method_t LPUART_HAL_GetReceiverWakeupMethod(uint32_t baseAddr)
{
    /* get configuration of the WAKE bit for idle line wake or address mark wake */
    if(HW_LPUART_CTRL(baseAddr).B.WAKE == 1)
    {
        return kLpuartAddrMarkWake;
    }
    else
    {
        return kLpuartIdleLineWake;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_HAL_ConfigureIdleLineDetect
 * Description   : LPUART idle-line detect operation configuration (idle line bit-count start and wake
 * up affect on IDLE status bit).
 * In some LPUART instances, the user should disable the transmitter/receiver
 * before calling this function.
 * Generally, this may be applied to all LPUARTs to ensure safe operation.
 *
 *END**************************************************************************/
void LPUART_HAL_ConfigureIdleLineDetect(uint32_t baseAddr,
                                         const lpuart_idle_line_config_t *config)
{
    /* Configure the idle line detection configuration as follows: */
    /* configure the ILT to bit count after start bit or stop bit */
    /* configure RWUID to set or not set IDLE status bit upon detection of */
    /* an idle character when recevier in standby */
    BW_LPUART_CTRL_ILT(baseAddr, config->idleLineType);
    BW_LPUART_STAT_RWUID(baseAddr, config->rxWakeIdleDetect);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_HAL_SetMatchAddressOperation
 * Description   : LPUART configures match address mode control (Note: Feature available on
 *                 select LPUART instances)
 *
 *END**************************************************************************/
lpuart_status_t LPUART_HAL_SetMatchAddressOperation( uint32_t baseAddr,
                        bool matchAddrMode1, bool matchAddrMode2,
                        uint8_t matchAddrValue1, uint8_t matchAddrValue2, lpuart_match_config_t config)
{
    BW_LPUART_BAUD_MAEN1(baseAddr, matchAddrMode1); /* Match Address Mode Enable 1 */
    BW_LPUART_BAUD_MAEN2(baseAddr, matchAddrMode2); /* Match Address Mode Enable 2 */
    BW_LPUART_MATCH_MA1(baseAddr, matchAddrValue1); /* match address register 1 */
    BW_LPUART_MATCH_MA2(baseAddr, matchAddrValue2); /* match address register 2 */
    BW_LPUART_BAUD_MATCFG(baseAddr, config); /* Match Configuration */

    return kStatus_LPUART_Success;
}

#if FSL_FEATURE_LPUART_HAS_IR_SUPPORT
/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_HAL_SetInfraredOperation
 * Description   : Configures the LPUART infrared operation.
 *
 *END**************************************************************************/
void LPUART_HAL_SetInfraredOperation(uint32_t baseAddr, bool enable,
                                           lpuart_ir_tx_pulsewidth_t pulseWidth)
{
    /* enable or disable infrared */
    BW_LPUART_MODIR_IREN(baseAddr, enable);

    /* configure the narrow pulse width of the IR pulse */
    BW_LPUART_MODIR_TNP(baseAddr, pulseWidth);
}
#endif  /* FSL_FEATURE_LPUART_HAS_IR_SUPPORT */

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_HAL_GetStatusFlag
 * Description   : LPUART get status flag by passing flag enum.
 *
 *END**************************************************************************/
bool LPUART_HAL_GetStatusFlag(uint32_t baseAddr, lpuart_status_flag_t statusFlag)
{
    uint32_t reg = (uint32_t)(statusFlag) >> LPUART_SHIFT;
	  bool retVal = false;

    switch ( reg )
    {
        case LPUART_BAUD_REG_ID:
            retVal = HW_LPUART_BAUD_RD(baseAddr) >> (uint32_t)(statusFlag) & 1U;
            break;
        case LPUART_STAT_REG_ID:
            retVal = HW_LPUART_STAT_RD(baseAddr) >> (uint32_t)(statusFlag) & 1U;
            break;
        case LPUART_CTRL_REG_ID:
            retVal = HW_LPUART_CTRL_RD(baseAddr) >> (uint32_t)(statusFlag) & 1U;
            break;
        case LPUART_DATA_REG_ID:
            retVal = HW_LPUART_DATA_RD(baseAddr) >> (uint32_t)(statusFlag) & 1U;
            break;
        case LPUART_MATCH_REG_ID:
            retVal = HW_LPUART_MATCH_RD(baseAddr) >> (uint32_t)(statusFlag) & 1U;
            break;
        case LPUART_MODIR_REG_ID:
            retVal = HW_LPUART_MODIR_RD(baseAddr) >> (uint32_t)(statusFlag) & 1U;
            break;
        default:
            break;
    }

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_HAL_ClearStatusFlag
 * Description   : LPUART clears an individual status flag 
 * (see lpuart_status_flag_t for list of status bits).
 *
 *END**************************************************************************/
lpuart_status_t LPUART_HAL_ClearStatusFlag(uint32_t baseAddr, lpuart_status_flag_t statusFlag)
{
    lpuart_status_t returnCode = kStatus_LPUART_Success;

    /* clear the desired, individual status flag as passed in through statusFlag  */
    switch(statusFlag)
    {
        case kLpuartTxDataRegEmpty:
            /* This flag is cleared automatically by other lpuart operations */
            /* and cannot be manually cleared, return error code */
            returnCode = kStatus_LPUART_ClearStatusFlagError;
            break;

        case kLpuartTxComplete:
            /* This flag is cleared automatically by other lpuart operations */
            /* and cannot be manually cleared, return error code */
            returnCode = kStatus_LPUART_ClearStatusFlagError;
            break;

        case kLpuartRxDataRegFull:
            /* This flag is cleared automatically by other lpuart operations and */
            /* cannot be manually cleared, return error code */
            returnCode = kStatus_LPUART_ClearStatusFlagError;
            break;

        case kLpuartIdleLineDetect:
            /* write one to clear status flag */
            BW_LPUART_STAT_IDLE(baseAddr, 1);
            break;

        case kLpuartRxOverrun:
            /* write one to clear status flag */
            BW_LPUART_STAT_OR(baseAddr, 1);
            break;

        case kLpuartNoiseDetect:
            /* write one to clear status flag */
            BW_LPUART_STAT_NF(baseAddr, 1);
            break;

        case kLpuartFrameErr:
            /* write one to clear status flag */
            BW_LPUART_STAT_FE(baseAddr, 1);
            break;

        case kLpuartParityErr:
            /* write one to clear status flag */
            BW_LPUART_STAT_PF(baseAddr, 1);
            break;

        case kLpuartLineBreakDetect:
            /* write one to clear status flag */
            BW_LPUART_STAT_LBKDIF(baseAddr, 1);
            break;

        case kLpuartRxActiveEdgeDetect:
            /* write one to clear status flag */
            BW_LPUART_STAT_RXEDGIF(baseAddr, (1U));
            break;

        case kLpuartRxActive:
            /* This flag is cleared automatically by other lpuart operations and */
            /* cannot be manually cleared, return error code */
            returnCode = kStatus_LPUART_ClearStatusFlagError;
            break;

#if FSL_FEATURE_LPUART_HAS_EXTENDED_DATA_REGISTER_FLAGS
        case kLpuartNoiseInCurrentWord:
            /* This flag is not clearable, it simply reflects the status in the */
            /* current data word and changes with each new data word */
            returnCode = kStatus_LPUART_ClearStatusFlagError;
            break;

        case kLpuartParityErrInCurrentWord:
            /* This flag is not clearable, it simply reflects the status in the */
            /* current data word and changes with each new data word */
            returnCode = kStatus_LPUART_ClearStatusFlagError;
            break;
#endif

#if FSL_FEATURE_LPUART_HAS_ADDRESS_MATCHING
        case kLpuartMatchAddrOne:
            /* write one to clear status flag */
            BW_LPUART_STAT_MA1F(baseAddr, 1);
            break;
        case kLpuartMatchAddrTwo:
            /* write one to clear status flag */
            BW_LPUART_STAT_MA2F(baseAddr, 1);
            break;
#endif

        default:  /* catch inputs that are not recognized */
            returnCode = kStatus_LPUART_ClearStatusFlagError;
            break;
    }

    return (returnCode);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_HAL_ClearAllNonAutoclearStatusFlags
 * Description   : LPUART clears ALL status flags.
 *
 *END**************************************************************************/
void LPUART_HAL_ClearAllNonAutoclearStatusFlags(uint32_t baseAddr)
{
    /* clear the status flags that can be manually cleared */
    /* note, some flags are automatically cleared and cannot be cleared automatically */
    LPUART_HAL_ClearStatusFlag(baseAddr, kLpuartIdleLineDetect);
    LPUART_HAL_ClearStatusFlag(baseAddr, kLpuartRxOverrun);
    LPUART_HAL_ClearStatusFlag(baseAddr, kLpuartNoiseDetect);
    LPUART_HAL_ClearStatusFlag(baseAddr, kLpuartFrameErr);
    LPUART_HAL_ClearStatusFlag(baseAddr, kLpuartParityErr);
    LPUART_HAL_ClearStatusFlag(baseAddr, kLpuartLineBreakDetect);
    LPUART_HAL_ClearStatusFlag(baseAddr, kLpuartRxActiveEdgeDetect);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_HAL_Putchar9
 * Description   : Sends the LPUART 9-bit character.
 *
 *END**************************************************************************/
void LPUART_HAL_Putchar9(uint32_t baseAddr, uint16_t data)
{
    uint8_t ninthDataBit;

    ninthDataBit = (data >> 8U) & 0x1U;  /* isolate the ninth data bit */

    /* put 9-bit data to transmit */

    /* first, write to the ninth data bit (bit position T8, where T[0:7]=8-bits, T8=9th bit) */
    BW_LPUART_CTRL_R9T8(baseAddr, ninthDataBit);

    /* write to the data register last since this will trigger transmit complete status flag */
    /* also typecast to uint8_t to match register type */
    HW_LPUART_DATA_WR(baseAddr, (uint8_t)data);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_HAL_Putchar10
 * Description   : Sends the LPUART 10-bit character.
 *
 *END**************************************************************************/
lpuart_status_t LPUART_HAL_Putchar10(uint32_t baseAddr, uint16_t data)
{
    uint8_t ninthDataBit;
    uint8_t tenthDataBit;

    /* put 10-bit data to transmit */
    ninthDataBit = (data >> 8U) & 0x1U;  /* isolate the ninth data bit */
    tenthDataBit = (data >> 9U) & 0x1U;  /* isolate the tenth data bit */

    /* first, write to the tenth data bit (bit position T9, where T[0:7]=8-bits, */
    /* T9=10th bit, T8=9th bit) */
    BW_LPUART_CTRL_R8T9(baseAddr, tenthDataBit);

    /* next, write to the ninth data bit (bit position T8, where T[0:7]=8-bits, */
    /* T9=10th bit, T8=9th bit) */
    BW_LPUART_CTRL_R9T8(baseAddr, ninthDataBit);

    /* write to the data register last since this will trigger transmit complete status flag */
    /* also typecast to uint8_t to match register type */
    HW_LPUART_DATA_WR(baseAddr, (uint8_t)data);

    return kStatus_LPUART_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_HAL_Getchar
 * Description   : Gets the LPUART 8-bit character.
 *
 *END**************************************************************************/
void LPUART_HAL_Getchar(uint32_t baseAddr, uint8_t *readData)
{
    /* get 8-bit data from the lpuart data register */
    *readData = (uint8_t)HW_LPUART_DATA_RD(baseAddr);  /* read 8-bit data from data register */
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_HAL_Getchar9
 * Description   : Gets the LPUART 9-bit character.
 *
 *END**************************************************************************/
void  LPUART_HAL_Getchar9(uint32_t baseAddr, uint16_t *readData)
{
    uint16_t temp;

    /* get 9-bit data from the lpuart data register */
    /* read ninth data bit and left shift to bit position R8 before reading */
    /* the 8 other data bits R[7:0] */
    temp = HW_LPUART_CTRL(baseAddr).B.R8T9;  /* need this two step process to work around mishra rule */
    *readData = temp << 8;

    /* do last: get 8-bit data from the lpuart data register, will clear certain */
    /* receive status bits once completed */
    /* need to OR these 8-bits with the ninth bit value above */
    *readData |= (uint8_t)HW_LPUART_DATA_RD(baseAddr);  /* read 8-bit data from data register  */
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_HAL_Getchar10
 * Description   : Gets the LPUART 10-bit character.
 *
 *END**************************************************************************/
lpuart_status_t LPUART_HAL_Getchar10(uint32_t baseAddr, uint16_t *readData)
{
    /* get 10-bit data from the lpuart data register, available only on supported lpuarts */

    /* read tenth data bit and left shift to bit position R9 before reading the 9 other */
    /* data bits: R8 and R[7:0] */
    *readData = (uint16_t)((uint32_t)(HW_LPUART_CTRL(baseAddr).B.R9T8) << 9U);

    /* read ninth data bit and left shift to bit position R8 before reading the 8 other */
    /* data bits R[7:0] */
    *readData |= (uint16_t)((uint32_t)(HW_LPUART_CTRL(baseAddr).B.R8T9) << 8U);

    /* do last: get 8-bit data from the lpuart data register, will clear certain receive */
    /* status bits once completed */
    /* need to OR these 8-bits with the ninth bit value above */
    *readData |= HW_LPUART_DATA_RD(baseAddr);  /* read 8-bit data from data register */

    return kStatus_LPUART_Success;
}

#endif /* MBED_NO_LPUART */

/*******************************************************************************
 * EOF
 ******************************************************************************/

