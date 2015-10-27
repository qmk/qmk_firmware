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
#include "fsl_uart_hal.h"

/*******************************************************************************
 * Code
 ******************************************************************************/
/*******************************************************************************
 * UART Common Configurations
 ******************************************************************************/
/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_Init
 * Description   : This function initializes the module to a known state.
 *
 *END**************************************************************************/
void UART_HAL_Init(uint32_t baseAddr)
{
    HW_UART_BDH_WR(baseAddr, 0U);
    HW_UART_BDL_WR(baseAddr, 4U);
    HW_UART_C1_WR(baseAddr, 0U);
    HW_UART_C2_WR(baseAddr, 0U);
    HW_UART_S2_WR(baseAddr, 0U);
    HW_UART_C3_WR(baseAddr, 0U);
    HW_UART_D_WR(baseAddr, 0U);
#if FSL_FEATURE_UART_HAS_ADDRESS_MATCHING
    HW_UART_MA1_WR(baseAddr, 0U);
    HW_UART_MA2_WR(baseAddr, 0U);
#endif
    HW_UART_C4_WR(baseAddr, 0U);
#if FSL_FEATURE_UART_HAS_DMA_ENABLE
    HW_UART_C5_WR(baseAddr, 0U);
#endif
#if FSL_FEATURE_UART_HAS_MODEM_SUPPORT
    HW_UART_MODEM_WR(baseAddr, 0U);
#endif
#if FSL_FEATURE_UART_HAS_IR_SUPPORT
    HW_UART_IR_WR(baseAddr, 0U);
#endif
#if FSL_FEATURE_UART_HAS_FIFO
    HW_UART_PFIFO_WR(baseAddr, 0U);
    HW_UART_CFIFO_WR(baseAddr, 0U);
    HW_UART_SFIFO_WR(baseAddr, 0xC0U);
    HW_UART_TWFIFO_WR(baseAddr, 0U);
    HW_UART_RWFIFO_WR(baseAddr, 1U);
#endif
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_SetBaudRate
 * Description   : Configure the UART baud rate.
 * This function programs the UART baud rate to the desired value passed in by the
 * user. The user must also pass in the module source clock so that the function can
 * calculate the baud rate divisors to their appropriate values.
 *
 *END**************************************************************************/
uart_status_t UART_HAL_SetBaudRate(uint32_t baseAddr, uint32_t sourceClockInHz, uint32_t baudRate)
{
    /* BaudRate = (SourceClkInHz)/[16 * (SBR +  BRFA)]
     * First, calculate SBR (integer part) then calculate the BRFA (fine adjust fractional field). */
    uint16_t brfa, sbr;

    /* calculate the baud rate modulo divisor, sbr*/
    sbr = sourceClockInHz / (baudRate * 16);

    /* check to see if sbr is out of range of register bits */
    if ( (sbr > 0x1FFF) || (sbr < 1) )
    {
        /* unsupported baud rate for given source clock input*/
        return kStatus_UART_BaudRateCalculationError;
    }

    /* write the sbr value to the BDH and BDL registers*/
    BW_UART_BDH_SBR(baseAddr, (uint8_t)(sbr >> 8));
    BW_UART_BDL_SBR(baseAddr, (uint8_t)sbr);

#if FSL_FEATURE_UART_HAS_BAUD_RATE_FINE_ADJUST_SUPPORT
    /* determine if a fractional divider is needed to fine tune closer to the desired baud
     * each value of brfa is in 1/32 increments, hence the multiply-by-32. */
    brfa = (32*sourceClockInHz/(baudRate*16)) - 32*sbr;

    /* write the brfa value to the register*/
    BW_UART_C4_BRFA(baseAddr, brfa);
#endif

    return kStatus_UART_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_SetBaudRateDivisor
 * Description   : Set the UART baud rate modulo divisor value.
 * This function allows the user to program the baud rate divisor directly in
 * situations where the divisor value is known. In this case, the user may not want to
 * call the UART_HAL_SetBaudRate() function as the divisor is already known to them.
 *
 *END**************************************************************************/
void UART_HAL_SetBaudRateDivisor(uint32_t baseAddr, uint16_t baudRateDivisor)
{
    /* check to see if baudRateDivisor is out of range of register bits */
    assert( (baudRateDivisor < 0x1FFF) && (baudRateDivisor > 1) );

    /* program the sbr (baudRateDivisor) value to the BDH and BDL registers*/
    BW_UART_BDH_SBR(baseAddr, (uint8_t)(baudRateDivisor >> 8));
    BW_UART_BDL_SBR(baseAddr, (uint8_t)baudRateDivisor);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_SetTxRxInversionCmd
 * Description   : Configure the transmit and receive inversion control in UART
 * controller. This function allows the user to invert the transmit and receive
 * signals, independently.  This function should only be called when the UART is
 * between transmit and receive packets.
 *
 *END**************************************************************************/
void UART_HAL_SetTxRxInversionCmd(uint32_t baseAddr, bool rxInvertEnable, bool txInvertEnable)
{
    /* 0 - receive data not inverted, 1 - receive data inverted */
    BW_UART_S2_RXINV(baseAddr, (uint8_t)rxInvertEnable);
    /* 0 - transmit data not inverted, 1 - transmit data inverted*/
    BW_UART_C3_TXINV(baseAddr, (uint8_t)txInvertEnable);
}

/*******************************************************************************
 * UART Transfer Functions
 ******************************************************************************/
/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_Putchar
 * Description   : This function allows the user to send an 8-bit character from the UART
 *                 data register.
 *
 *END**************************************************************************/
void UART_HAL_Putchar(uint32_t baseAddr, uint8_t data)
{
    /* put 8-bit data into the uart data register*/
    /* in addition to sending a char, this function also clears the transmit status flags
     * for this uart baseAddr, there is a two step process to clear the
     * transmit status flags:
     * 1. Read the status register with the status bit set
     * 2. write to the data register */
    HW_UART_S1_RD(baseAddr);
    HW_UART_D_WR(baseAddr, data);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_Putchar9
 * Description   : This function allows the user to send a 9-bit character from the UART
 *                 data register.
 *
 *END**************************************************************************/
void UART_HAL_Putchar9(uint32_t baseAddr, uint16_t data)
{
    uint8_t ninthDataBit;

    ninthDataBit = (data >> 8U) & 0x1U;  /* isolate the ninth data bit*/

    /* put 9-bit data to transmit*/
    /* first, write to the ninth data bit (bit position T8, where T[0:7]=8-bits, T8=9th bit)*/
    BW_UART_C3_T8(baseAddr, ninthDataBit);

    /* in addition to sending a char, this function also clears the transmit status flags
     * for this uart baseAddr, there is a two step process to clear the
     * transmit status flags:
     * 1. Read the status register with the status bit set
     * 2. write to the data register */
    HW_UART_S1_RD(baseAddr);
    /* write to the data register last since this will trigger transmit complete status flags
     * also typecast to uint8_t to match register type */
    HW_UART_D_WR(baseAddr, (uint8_t)data);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_Getchar
 * Description   : This function gets a received 8-bit character from the UART data register.
 *
 *END**************************************************************************/
void UART_HAL_Getchar(uint32_t baseAddr, uint8_t *readData)
{
    /* get 8-bit data from the uart data register*/
    /* in addition to getting a char, this function also clears the receive status flag RDRF
     * along with IDLE, OR, NF, FE, and PF (these can also be cleared in separate functions)
     * for this uart baseAddr, there is a two step process to clear the receive
     * status flag:
     * 1. Read the status register with the status bit set
     * 2. read from the data register */
    HW_UART_S1_RD(baseAddr);
    /* second, perform a read from the data register */
    *readData = HW_UART_D_RD(baseAddr);  /* read 8-bit data from data register*/
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_Getchar9
 * Description   : This function gets a received 9-bit character from the UART data register.
 *
 *END**************************************************************************/
void  UART_HAL_Getchar9(uint32_t baseAddr, uint16_t *readData)
{
    uint16_t temp;

    /* get 9-bit data from the uart data register*/
    /* read ninth data bit and left shift to bit position R8 before reading
     * the 8 other data bits R[7:0]
     * *readData = (HW_UART_C3(baseAddr).B.R8) << 8; */
    temp = (HW_UART_C3(baseAddr).B.R8);
    *readData = temp << 8;

    /* in addition to getting a char, this function also clears the receive status flag RDRF
     * along with IDLE, OR, NF, FE, and PF (these can also be cleared in separate functions)
     * for this uart baseAddr, there is a two step process to clear the receive
     * status flag:
     * 1. Read the status register with the status bit set
     * 2. read from the data register */
    HW_UART_S1_RD(baseAddr);
    /* do last: get 8-bit data from the uart data register,
     * will clear certain receive status bits once completed
     * need to OR these 8-bits with the ninth bit value above. */
    *readData |= HW_UART_D_RD(baseAddr);  /* read 8-bit data from data register*/
}

/*******************************************************************************
 * UART Interrupts and DMA
 ******************************************************************************/
/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_ConfigureInterrupts
 * Description   : Configure the UART module interrupts to enable/disable various
 * interrupt sources.
 *
 *END**************************************************************************/
void UART_HAL_SetIntMode(uint32_t baseAddr, uart_interrupt_t interrupt, bool enable)
{
    uint8_t reg = (uint32_t)interrupt >> UART_SHIFT;
    uint32_t temp = 1U << (uint8_t)interrupt;

    switch ( reg )
    {
        case 0 :
            enable ? HW_UART_BDH_SET(baseAddr, temp) : HW_UART_BDH_CLR(baseAddr, temp);
            break;
        case 1 :
            enable ? HW_UART_C2_SET(baseAddr, temp) : HW_UART_C2_CLR(baseAddr, temp);
            break;
        case 2 :
            enable ? HW_UART_C3_SET(baseAddr, temp) : HW_UART_C3_CLR(baseAddr, temp);
            break;
#if FSL_FEATURE_UART_HAS_FIFO
        case 3 :
            enable ? HW_UART_CFIFO_SET(baseAddr, temp) : HW_UART_CFIFO_CLR(baseAddr, temp);
            break;
#endif
        default :
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_GetIntMode
 * Description   : Return whether the UART module interrupts is enabled/disabled.
 *
 *END**************************************************************************/
bool UART_HAL_GetIntMode(uint32_t baseAddr, uart_interrupt_t interrupt)
{
    uint8_t reg = (uint32_t)interrupt >> UART_SHIFT;
    uint8_t temp = 0;

    switch ( reg )
    {
        case 0 :
            temp = HW_UART_BDH_RD(baseAddr) >> (uint8_t)(interrupt) & 1U;
            break;
        case 1 :
            temp = HW_UART_C2_RD(baseAddr) >> (uint8_t)(interrupt) & 1U;
            break;
        case 2 :
            temp = HW_UART_C3_RD(baseAddr) >> (uint8_t)(interrupt) & 1U;
            break;
#if FSL_FEATURE_UART_HAS_FIFO
        case 3 :
            temp = HW_UART_CFIFO_RD(baseAddr) >> (uint8_t)(interrupt) & 1U;
            break;
#endif
        default :
            break;
    }
    return (bool)temp;
}
#if FSL_FEATURE_UART_HAS_DMA_SELECT 
/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_ConfigureDma
 * Description   : Configure the UART DMA requests for the Transmitter and Receiver.
 * This function allows the user to configure the transmit data register empty flag to
 * generate an interrupt request (default) or a DMA request.  Similarly, this function
 * allows the user to conigure the receive data register full flag to generate an interrupt
 * request (default) or a DMA request.
 *
 *END**************************************************************************/
void UART_HAL_ConfigureDma(uint32_t baseAddr, bool txDmaConfig, bool  rxDmaConfig)
{

    /* TDMAS configures the transmit data register empty flag, TDRE, to generate interrupt
     * or DMA requests if TIE is set.
     * NOTE: If UART_C2[TIE] is cleared, TDRE DMA and TDRE interrupt request signals are
     * not asserted when the TDRE flag is set, regardless of the state of TDMAS.
     * If UART_C2[TIE] and TDMAS are both set, then UART_C2[TCIE] must be cleared, and UART_D
     * must not be written outside of servicing of a DMA request.
     * 0 If TIE is set and the TDRE flag is set, the TDRE interrupt request signal is asserted
     * to request interrupt service.
     * 1 If TIE is set and the TDRE flag is set, the TDRE DMA request signal is asserted
     * to request a DMA transfer.
     */
    if (txDmaConfig == 1)
    {
        /* enable uart to generate transmit DMA request*/
        BW_UART_C5_TDMAS(baseAddr, 1U); /* set TDMAS */
        BW_UART_C2_TCIE(baseAddr, 0U); /* clear TCIE */
        BW_UART_C2_TIE(baseAddr, 1U); /* set TIE */
    }
    else
    {
        /* disable uart transmit DMA request*/
        BW_UART_C2_TIE(baseAddr, 0U); /* clear TIE to disable */
        BW_UART_C5_TDMAS(baseAddr, 0U); /* clear TDMAS to disable */
    }

    /* RDMAS configures the receiver data register full flag, RDRF, to generate interrupt or
     * DMA requests if RIEis set.
     * NOTE: If RIE is cleared, the RDRF DMA and RDRF interrupt request signals are not
     * asserted when the RDRF flag is set, regardless of the state of RDMAS.
     * 0 If RIE is set and the RDRF flag is set, the RDRF interrupt request signal is
     * asserted to request interrupt service.
     * 1 If RIE is set and the RDRF flag is set, the RDRF DMA request signal is asserted
     * to request a DMA transfer.
     */
    if (rxDmaConfig == 1)
    {
        /* enable uart to generate receive DMA request*/
        BW_UART_C5_RDMAS(baseAddr, 1U); /* set RDMAS */
        BW_UART_C2_RIE(baseAddr, 1U); /* set RIE */
    }
    else
    {
        /* disable uart receive DMA request*/
        BW_UART_C2_RIE(baseAddr, 0U); /* clear RIE to disable */
        BW_UART_C5_RDMAS(baseAddr, 0U); /* clear RDMAS to disable */
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_IsTxdmaEnabled
 * Description   : Get the UART Transmit DMA request configuration setting.
 * This function returns to the user the configuration setting of the Transmit DMA request.
 *
 *END**************************************************************************/
bool UART_HAL_IsTxdmaEnabled(uint32_t baseAddr)
{
    /* create variable for this to work around MISRA rule 12.4 since this is a volatile value*/
    uint32_t tcieBitStatus;
    tcieBitStatus = HW_UART_C2(baseAddr).B.TCIE;

    /* TDMAS configures the transmit data register empty flag, TDRE, to generate interrupt or
     * DMA requests if TIE is set.
     * NOTE: If UART_C2[TIE] is cleared, TDRE DMA and TDRE interrupt request signals are
     * not asserted when the TDRE flag is set, regardless of the state of TDMAS.
     * If UART_C2[TIE] and TDMAS are both set, then UART_C2[TCIE] must be cleared, and UART_D
     * must not be written outside of servicing of a DMA request.
     * 0 If TIE is set and the TDRE flag is set, the TDRE interrupt request signal is asserted
     * to request interrupt service.
     * 1 If TIE is set and the TDRE flag is set, the TDRE DMA request signal is asserted to
     * request a DMA transfer.
     */
    if (BR_UART_C5_TDMAS(baseAddr) == 1)
    {
        /* in order to enable transmit DMA request, TIE must be set and TCIE must be cleared*/
        if ((BR_UART_C2_TIE(baseAddr) == 1) && (tcieBitStatus == 0))
        {
            /* UART module is configured to generate TxDMA request*/
            return 1;
        }
        else
        {
            /* UART module is NOT configured to generate TxDMA request*/
            return 0;
        }
    }
    else
    {
        /* UART module is NOT configured to generate TxDMA request*/
        return 0;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_IsRxdmaEnabled
 * Description   : Get the UART Receive DMA request configuration setting.
 * This function returns to the user the configuration setting of the Receive DMA request.
 *
 *END**************************************************************************/
bool UART_HAL_IsRxdmaEnabled(uint32_t baseAddr)
{
    /* RDMAS configures the receiver data register full flag, RDRF, to generate interrupt or
     * DMA requests if RIE is set.
     * NOTE: If RIE is cleared, the RDRF DMA and RDRF interrupt request signals are not
     * asserted when the RDRF flag is set, regardless of the state of RDMAS.
     * 0 If RIE is set and the RDRF flag is set, the RDRF interrupt request signal is asserted
     * to requestinterrupt service.
     * 1 If RIE is set and the RDRF flag is set, the RDRF DMA request signal is asserted to
     * request a DMA transfer.
     */
    if (BR_UART_C5_RDMAS(baseAddr) == 1)
    {
        /* enable uart to generate receive DMA request*/
        if (BR_UART_C2_RIE(baseAddr) == 1)
        {
            /* UART module is configured to generate RxDMA request*/
            return 1;
        }
        else
        {
            /* UART module is NOT configured to generate RxDMA request*/
            return 0;
        }
    }
    else
    {
        /* UART module is NOT configured to generate RxDMA request*/
        return 0;
    }
}
#endif
/*******************************************************************************
 * UART UART Status Flags
 ******************************************************************************/
/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_GetStatusFlag
 * Description   : Get UART status flag states.
 *
 *END**************************************************************************/
bool UART_HAL_GetStatusFlag(uint32_t baseAddr, uart_status_flag_t statusFlag)
{
    uint8_t reg = (uint32_t)statusFlag >> UART_SHIFT;
    uint8_t temp = 0;

    switch ( reg )
    {
        case 0 :
            temp = HW_UART_S1_RD(baseAddr) >> (uint8_t)(statusFlag) & 1U;
            break;
        case 1 :
            temp = HW_UART_S2_RD(baseAddr) >> (uint8_t)(statusFlag) & 1U;
            break;
#if FSL_FEATURE_UART_HAS_EXTENDED_DATA_REGISTER_FLAGS
        case 2 :
            temp = HW_UART_ED_RD(baseAddr) >> (uint8_t)(statusFlag) & 1U;
            break;
#endif
#if FSL_FEATURE_UART_HAS_FIFO
        case 3 :
            temp = HW_UART_SFIFO_RD(baseAddr) >> (uint8_t)(statusFlag) & 1U;
            break;
#endif
        default :
            break;
    }
    return (bool)temp;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_ClearStatusFlag
 * Description   : Clear an individual and specific UART status flag.
 * This function allows the user to clear an individual and specific UART status flag. Refer to
 * structure definition uart_status_flag_t for list of status bits.
 *
 *END**************************************************************************/
uart_status_t UART_HAL_ClearStatusFlag(uint32_t baseAddr, uart_status_flag_t statusFlag)
{
    uart_status_t returnCode;       /* return code variable */
    returnCode = kStatus_UART_Success;  /* default return code, unless changed by error condition*/

    /* clear the desired, individual status flag as passed in through statusFlag  */
    switch(statusFlag)
    {
        case kUartTxDataRegEmpty:
            /* This flag is cleared automatically by other uart operations and
             * cannot be manually cleared, return error code
             */
            returnCode = kStatus_UART_ClearStatusFlagError;
            break;

        case kUartTxComplete:
            /* This flag is cleared automatically by other uart operations and
             * cannot be manually cleared, return error code
             */
            returnCode = kStatus_UART_ClearStatusFlagError;
            break;

        case kUartRxDataRegFull:
            /* This flag is cleared automatically by other uart operations and
             * cannot be manually cleared, return error code
             */
            returnCode = kStatus_UART_ClearStatusFlagError;
            break;

        case kUartIdleLineDetect:
            /* to clear the status is a two-step process:
             * first, read S1 register with the status flag set
             */
            HW_UART_S1_RD(baseAddr);
            /* second, read the data register*/
            HW_UART_D_RD(baseAddr);
            break;

        case kUartRxOverrun:
            /* to clear the status is a two-step process:
             * first, read S1 register with the status flag set
             */
            HW_UART_S1_RD(baseAddr);
            /* second, read the data register*/
            HW_UART_D_RD(baseAddr);
            break;

        case kUartNoiseDetect:
            /* to clear the status is a two-step process:
             * first, read S1 register with the status flag set
             */
            HW_UART_S1_RD(baseAddr);
            /* second, read the data register*/
            HW_UART_D_RD(baseAddr);
            break;

        case kUartFrameErr:
            /* to clear the status is a two-step process:
             * first, read S1 register with the status flag set
             */
            HW_UART_S1_RD(baseAddr);
            /* second, read the data register*/
            HW_UART_D_RD(baseAddr);
            break;

        case kUartParityErr:
            /* to clear the status is a two-step process:
             * first, read S1 register with the status flag set
             */
            HW_UART_S1_RD(baseAddr);
            /* second, read the data register*/
            HW_UART_D_RD(baseAddr);
            break;

        case kUartLineBreakDetect:
            /* write one to clear status flag */
            HW_UART_S2_SET(baseAddr, BM_UART_S2_LBKDIF);
            break;

        case kUartRxActiveEdgeDetect:
            /* write one to clear status flag */
            HW_UART_S2_SET(baseAddr, BM_UART_S2_RXEDGIF);
            break;

        case kUartRxActive:
            /* This flag is cleared automatically by other uart operations and
             * cannot be manually cleared, return error code
             */
            returnCode = kStatus_UART_ClearStatusFlagError;
            break;

#if FSL_FEATURE_UART_HAS_EXTENDED_DATA_REGISTER_FLAGS
        case kUartNoiseInCurrentWord:
            /* This flag is not clearable, it simply reflects the status in the
             * current data word and changes with each new data word
             */
            returnCode = kStatus_UART_ClearStatusFlagError;
            break;

        case kUartParityErrInCurrentWord:
            /* This flag is not clearable, it simply reflects the status in the
             * current data word and changes with each new data word
             */
            returnCode = kStatus_UART_ClearStatusFlagError;
            break;
#endif
#if FSL_FEATURE_UART_HAS_FIFO
        case kUartTxBuffEmpty:
            /* This flag is not clearable, it simply reflects the current
             * status of the buffer/FIFO
             */
            returnCode = kStatus_UART_ClearStatusFlagError;
            break;

        case kUartRxBuffEmpty:
            /* This flag is not clearable, it simply reflects the current
             * status of the buffer/FIFO
             */
            returnCode = kStatus_UART_ClearStatusFlagError;
            break;

        case kUartTxBuffOverflow:
            /* write one to clear status flag */
            HW_UART_SFIFO_SET(baseAddr, BM_UART_SFIFO_TXOF);
            break;

        case kUartRxBuffUnderflow:
            /* write one to clear status flag */
            HW_UART_SFIFO_SET(baseAddr, BM_UART_SFIFO_RXUF);
            break;
#endif
        default:  /* catch inputs that are not recognized*/
            returnCode = kStatus_UART_ClearStatusFlagError;
            break;
    }

    return (returnCode);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_ClearAllNonAutoclearStatusFlags
 * Description   : Clear ALL of the UART status flags.
 * This function tries to clear all of the UART status flags.  In some cases, some of the status
 * flags may not get cleared because of the condition that set the flag may still exist.
 *
 *END**************************************************************************/
void UART_HAL_ClearAllNonAutoclearStatusFlags(uint32_t baseAddr)
{
    /* clear the status flags that can be manually cleared
     * note, some flags are automatically cleared and cannot be cleared automatically
     */
    UART_HAL_ClearStatusFlag(baseAddr, kUartIdleLineDetect);
    UART_HAL_ClearStatusFlag(baseAddr, kUartRxOverrun);
    UART_HAL_ClearStatusFlag(baseAddr, kUartNoiseDetect);
    UART_HAL_ClearStatusFlag(baseAddr, kUartFrameErr);
    UART_HAL_ClearStatusFlag(baseAddr, kUartParityErr);
    UART_HAL_ClearStatusFlag(baseAddr, kUartLineBreakDetect);
    UART_HAL_ClearStatusFlag(baseAddr, kUartRxActiveEdgeDetect);
#if FSL_FEATURE_UART_HAS_FIFO
    UART_HAL_ClearStatusFlag(baseAddr, kUartTxBuffOverflow);
    UART_HAL_ClearStatusFlag(baseAddr, kUartRxBuffUnderflow);
#endif
}

/*******************************************************************************
 * UART FIFO Configurations
 ******************************************************************************/
#if FSL_FEATURE_UART_HAS_FIFO
/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_SetTxFifo
 * Description   : Enable or disable the UART transmit FIFO.
 * This function allows the user to enable or disable the UART transmit FIFO.
 * It is required that the transmitter/receiver should be disabled before calling this
 * function and when the FIFO is empty. Additionally, TXFLUSH and RXFLUSH commands
 * should be issued after calling this function.
 *
 *END**************************************************************************/
uart_status_t UART_HAL_SetTxFifoCmd(uint32_t baseAddr, bool enable)
{
    /* before enabling the tx fifo, UARTx_C2[TE] (transmitter) and
     * UARTx_C2[RE] (receiver) must be disabled
     * if not, return an error code */
    uint8_t txEnable = BR_UART_C2_TE(baseAddr);
    uint8_t rxEnable = BR_UART_C2_RE(baseAddr);

    if (txEnable || rxEnable)
    {
        return kStatus_UART_TxOrRxNotDisabled;
    }
    else
    {
        BW_UART_PFIFO_TXFE(baseAddr, enable);
        return kStatus_UART_Success;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_SetRxFifoCmd
 * Description   : Enable or disable the UART receive FIFO.
 * This function allows the user to enable or disable the UART receive FIFO.
 * It is required that the transmitter/receiver should be disabled before calling
 * this function and when the FIFO is empty. Additionally, TXFLUSH and RXFLUSH
 * commands should be issued after calling this function.
 *
 *END**************************************************************************/
uart_status_t UART_HAL_SetRxFifoCmd(uint32_t baseAddr, bool enable)
{
    /* before enabling the rx fifo, UARTx_C2[TE] (transmitter) and
     * UARTx_C2[RE] (receiver) must be disabled
     * if not, return an error code */
    uint8_t txEnable = BR_UART_C2_TE(baseAddr);
    uint8_t rxEnable = BR_UART_C2_RE(baseAddr);

    if (txEnable || rxEnable)
    {
        return kStatus_UART_TxOrRxNotDisabled;
    }
    else
    {
        BW_UART_PFIFO_RXFE(baseAddr, enable);
        return kStatus_UART_Success;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_FlushTxFifo
 * Description   : Flush the UART transmit FIFO.
 * This function allows you to flush the UART transmit FIFO for a particular modulei
 * baseAddr. Flushing the FIFO may result in data loss. It is recommended that the
 * transmitter should be disabled before calling this function.
 *
 *END**************************************************************************/
uart_status_t UART_HAL_FlushTxFifo(uint32_t baseAddr)
{
    /* in order to flush the tx fifo, UARTx_C2[TE] (transmitter) must be disabled
     * if not, return an error code */
    if (BR_UART_C2_TE(baseAddr) != 0)
    {
        return kStatus_UART_TxNotDisabled;
    }
    else
    {
        /* Set the bit to flush fifo*/
        BW_UART_CFIFO_TXFLUSH(baseAddr, 1U);
        return kStatus_UART_Success;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_FlushRxFifo
 * Description   : Flush the UART receive FIFO.
 * This function allows you to flush the UART receive FIFO for a particular module
 * baseAddr. Flushing the FIFO may result in data loss. It is recommended that the
 * receiver should be disabled before calling this function.
 *
 *END**************************************************************************/
uart_status_t UART_HAL_FlushRxFifo(uint32_t baseAddr)
{
    /* in order to flush the rx fifo, UARTx_C2[RE] (receiver) must be disabled
     * if not, return an error code. */
    if (BR_UART_C2_RE(baseAddr) != 0)
    {
        return kStatus_UART_RxNotDisabled;
    }
    else
    {
        /* Set the bit to flush fifo*/
        BW_UART_CFIFO_RXFLUSH(baseAddr, 1U);
        return kStatus_UART_Success;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_SetTxFifoWatermark
 * Description   : Set the UART transmit FIFO watermark value.
 * Programming the transmit watermark should be done when UART the transmitter is
 * disabled and the value must be set less than the size obtained from
 * UART_HAL_GetTxFifoSize.
 *
 *END**************************************************************************/
uart_status_t UART_HAL_SetTxFifoWatermark(uint32_t baseAddr, uint8_t watermark)
{
    /* in order to set the tx watermark, UARTx_C2[TE] (transmitter) must be disabled
     * if not, return an error code
     */
    if (BR_UART_C2_TE(baseAddr) != 0)
    {
        return kStatus_UART_TxNotDisabled;
    }
    else
    {
        /* Programming the transmit watermark should be done when the transmitter is
         * disabled and the value must be set less than the size given in
         * PFIFO[TXFIFOSIZE] */
        HW_UART_TWFIFO_WR(baseAddr, watermark);
        return kStatus_UART_Success;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_SetRxFifoWatermark
 * Description   : Set the UART receive FIFO watermark value.
 * Programming the receive watermark should be done when the receiver is disabled
 * and the value must be set less than the size obtained from UART_HAL_GetRxFifoSize
 * and greater than zero.
 *
 *END**************************************************************************/
uart_status_t UART_HAL_SetRxFifoWatermark(uint32_t baseAddr, uint8_t watermark)
{
    /* in order to set the rx watermark, UARTx_C2[RE] (receiver) must be disabled
     * if not, return an error code. */
    if (BR_UART_C2_RE(baseAddr) != 0)
    {
        return kStatus_UART_RxNotDisabled;
    }
    else
    {
        /* Programming the receive watermark should be done when the receiver is
         * disabled and the value must be set less than the size given in
         * PFIFO[RXFIFOSIZE] and greater than zero.  */
        HW_UART_RWFIFO_WR(baseAddr, watermark);
        return kStatus_UART_Success;
    }
}
#endif  /* FSL_FEATURE_UART_HAS_FIFO*/

/*******************************************************************************
 * UART Special Feature Configurations
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_PutReceiverInStandbyMode
 * Description   : Place the UART receiver in standby mode.
 * This function, when called, will place the UART receiver into standby mode.
 * In some UART baseAddrs, there is a condition that must be met before placing rx in standby mode.
 * Before placing UART in standby, you need to first determine if receiver is set to
 * wake on idle and if receiver is already in idle state. Per ref manual:
 * NOTE: RWU should only be set with C1[WAKE] = 0 (wakeup on idle) if the channel is currently
 * not idle.
 * This can be determined by the S2[RAF] flag. If set to wake up FROM an IDLE event and the channel
 * is already idle, it is possible that the UART will discard data since data must be received
 * (or a LIN break detect) after an IDLE is detected before IDLE is allowed to reasserted.
 *
 *END**************************************************************************/
uart_status_t UART_HAL_PutReceiverInStandbyMode(uint32_t baseAddr)
{
    /* In some uart baseAddrs, there is a condition that must be met before placing
     * rx in standby mode.
     * Before placing uart in standby, need to first determine if receiver is set to
     * wake on idle and if receiver is already in idle state. Per ref manual:
     * NOTE: RWU should only be set with C1[WAKE] = 0 (wakeup on idle) if the channel is
     * currently not idle.
     * This can be determined by the S2[RAF] flag. If set to wake up an IDLE event and
     * the channel is already idle, it is possible that the UART will discard data since data
     * must be received (or a LIN break detect) after an IDLE is detected before IDLE is
     * allowed to reasserted.
     */
    uart_wakeup_method_t rxWakeMethod;
    bool uart_current_rx_state;

    /* see if wake is set for idle or */
    rxWakeMethod = UART_HAL_GetReceiverWakeupMethod(baseAddr);
    uart_current_rx_state = UART_HAL_GetStatusFlag(baseAddr, kUartRxActive);

    /* if both rxWakeMethod is set for idle and current rx state is idle, don't put in standy*/
    if ((rxWakeMethod == kUartIdleLineWake) && (uart_current_rx_state == 0))
    {
        return kStatus_UART_RxStandbyModeError;
    }
    else
    {
        /* set the RWU bit to place receiver into standby mode*/
        HW_UART_C2_SET(baseAddr, BM_UART_C2_RWU);
        return kStatus_UART_Success;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_ConfigIdleLineDetect
 * Description   : Configure the operation options of the UART idle line detect.
 * This function allows the user to configure the UART idle-line detect operation. There are two
 * separate operations for the user to configure, the idle line bit-count start and the receive
 * wake up affect on IDLE status bit. The user will pass in a stucture of type
 * uart_idle_line_config_t.
 *
 *END**************************************************************************/
void UART_HAL_ConfigIdleLineDetect(uint32_t baseAddr, uint8_t idleLine, uint8_t rxWakeIdleDetect)
{
    /* Configure the idle line detection configuration as follows:
     * configure the ILT to bit count after start bit or stop bit
     * configure RWUID to set or not set IDLE status bit upon detection of
     * an idle character when recevier in standby */
    BW_UART_C1_ILT(baseAddr, idleLine);
    BW_UART_S2_RWUID(baseAddr, rxWakeIdleDetect);
}
#if FSL_FEATURE_UART_HAS_ADDRESS_MATCHING
/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_SetMatchAddress
 * Description   : Configure the UART match address mode control operation. (Note: Feature
 *                 available on select UART baseAddrs)
 * The function allows the user to configure the UART match address control operation. The user
 * has the option to enable the match address mode and to program the match address value. There
 * are two match address modes, each with it's own enable and programmable match address value.
 *
 *END**************************************************************************/
void UART_HAL_SetMatchAddress( uint32_t baseAddr, bool matchAddrMode1, bool matchAddrMode2,
                               uint8_t matchAddrValue1, uint8_t matchAddrValue2)
{
    BW_UART_C4_MAEN1(baseAddr, matchAddrMode1); /* Match Address Mode Enable 1 */
    BW_UART_C4_MAEN2(baseAddr, matchAddrMode2); /* Match Address Mode Enable 2 */
    HW_UART_MA1_WR(baseAddr, matchAddrValue1); /* match address register 1 */
    HW_UART_MA2_WR(baseAddr, matchAddrValue2); /* match address register 2 */
}
#endif

#if FSL_FEATURE_UART_HAS_IR_SUPPORT
/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_SetInfraredOperation
 * Description   : Configure the UART infrared operation.
 * The function allows the user to enable or disable the UART infrared (IR) operation
 * and to configure the IR pulse width.
 *
 *END**************************************************************************/
void UART_HAL_SetInfraredOperation(uint32_t baseAddr, bool enable,
                                           uart_ir_tx_pulsewidth_t pulseWidth)
{
    /* enable or disable infrared */
    BW_UART_IR_IREN(baseAddr, enable);
    /* configure the narrow pulse width of the IR pulse */
    BW_UART_IR_TNP(baseAddr, pulseWidth);
}
#endif  /* FSL_FEATURE_UART_HAS_IR_SUPPORT */


/*******************************************************************************
 * EOF
 ******************************************************************************/

