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
#include "fsl_sdhc_hal.h"

#ifndef MBED_NO_SDHC

/*FUNCTION****************************************************************
 *
 * Function Name: SDHC_HAL_Init
 * Description: Initialize sdhc hal
 *
 *END*********************************************************************/
void SDHC_HAL_Init(uint32_t baseAddr)
{
    SDHC_HAL_SetSdClock(baseAddr, false);
    SDHC_HAL_SetExternalDmaRequest(baseAddr, false);
    SDHC_HAL_SetIntState(baseAddr, false, (uint32_t)-1);
    SDHC_HAL_SetIntSignal(baseAddr, false, (uint32_t)-1);
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDHC_HAL_SetIntSignal
 * Description: Enable specified interrupts
 *
 *END*********************************************************************/
void SDHC_HAL_SetIntSignal(uint32_t baseAddr, bool enable, uint32_t mask)
{
    if (enable)
    {
        HW_SDHC_IRQSIGEN_SET(baseAddr, mask);
    }
    else
    {
        HW_SDHC_IRQSIGEN_CLR(baseAddr, mask);
    }
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDHC_HAL_SetIntState
 * Description: Enable specified interrupts' state
 *
 *END*********************************************************************/
void SDHC_HAL_SetIntState(uint32_t baseAddr, bool enable, uint32_t mask)
{
    if (enable)
    {
        HW_SDHC_IRQSTATEN_SET(baseAddr, mask);
    }
    else
    {
        HW_SDHC_IRQSTATEN_CLR(baseAddr, mask);
    }
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDHC_HAL_GetResponse
 * Description: get command response
 *
 *END*********************************************************************/
uint32_t SDHC_HAL_GetResponse(uint32_t baseAddr, uint32_t index)
{
    uint32_t ret = 0;

    assert(index < 4);

    switch(index)
    {
        case 0:
            ret = BR_SDHC_CMDRSP0_CMDRSP0(baseAddr);
            break;
        case 1:
            ret = BR_SDHC_CMDRSP1_CMDRSP1(baseAddr);
            break;
        case 2:
            ret = BR_SDHC_CMDRSP2_CMDRSP2(baseAddr);
            break;
        case 3:
            ret = BR_SDHC_CMDRSP3_CMDRSP3(baseAddr);
            break;
        default:
            break;
    }

    return ret;
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDHC_HAL_InitCard
 * Description: Initialize card by sending 80 clocks to card
 *
 *END*********************************************************************/
uint32_t SDHC_HAL_InitCard(uint32_t baseAddr, uint32_t timeout)
{
    assert(timeout);
    BW_SDHC_SYSCTL_INITA(baseAddr, 1);
    while((!BR_SDHC_SYSCTL_INITA(baseAddr)))
    {
        if (!timeout)
        {
            break;
        }
        timeout--;
    }
    return (!timeout);
}

/*FUNCTION****************************************************************
 *
 * Function Name: SDHC_HAL_Reset
 * Description: Perform different kinds of reset
 *
 *END*********************************************************************/
uint32_t SDHC_HAL_Reset(uint32_t baseAddr, uint32_t type, uint32_t timeout)
{
    uint32_t mask;
    assert(timeout);
    mask = type & (BM_SDHC_SYSCTL_RSTA
                 | BM_SDHC_SYSCTL_RSTC
                 | BM_SDHC_SYSCTL_RSTD);
    HW_SDHC_SYSCTL_SET(baseAddr, mask);
    while (!(HW_SDHC_SYSCTL_RD(baseAddr) & mask))
    {
        if (!timeout)
        {
            break;
        }
        timeout--;
    }
    return (!timeout);
}

#endif /* MBED_NO_SDHC */

/*************************************************************************************************
 * EOF
 ************************************************************************************************/
