/*
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
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

#include "fsl_pdb_hal.h"

/*FUNCTION*********************************************************************
 *
 * Function Name : PDB_HAL_Init
 * Description   : Reset PDB's registers to a known state. This state is
 * defined in Reference Manual, which is power on reset value.
 *
 *END*************************************************************************/
void PDB_HAL_Init(uint32_t baseAddr)
{
    uint32_t chn, preChn;
    HW_PDB_SC_WR(baseAddr, 0U);
    HW_PDB_MOD_WR(baseAddr, 0xFFFFU);
    HW_PDB_IDLY_WR(baseAddr, 0xFFFFU);
    /* For ADC trigger. */
    for (chn = 0U; chn < HW_PDB_CHnC1_COUNT; chn++)
    {
        HW_PDB_CHnC1_WR(baseAddr, chn, 0U);
        HW_PDB_CHnS_WR(baseAddr, chn,0xFU);
        for (preChn = 0U; preChn < FSL_FEATURE_PDB_ADC_PRE_CHANNEL_COUNT; preChn++)
        {
            PDB_HAL_SetPreTriggerDelayCount(baseAddr, chn, preChn, 0U);
        }
    }
    /* For DAC trigger. */
    for (chn = 0U; chn < HW_PDB_DACINTCn_COUNT; chn++)
    {
        HW_PDB_DACINTCn_WR(baseAddr, chn, 0U);
        HW_PDB_DACINTn_WR(baseAddr ,chn, 0U);
    }
    /* For Pulse out trigger. */
    HW_PDB_POEN_WR(baseAddr, 0U);
    for (chn = 0U; chn < HW_PDB_POnDLY_COUNT; chn++)
    {
        HW_PDB_POnDLY_WR(baseAddr, chn, 0U);
    }
    /* Load the setting value. */
    PDB_HAL_Enable(baseAddr);
    PDB_HAL_SetLoadRegsCmd(baseAddr);
    PDB_HAL_Disable(baseAddr);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : PDB_HAL_SetPreTriggerBackToBackCmd
 * Description   : Switch to enable pre-trigger's back to back mode.
 *
 *END*************************************************************************/
void PDB_HAL_SetPreTriggerBackToBackCmd(uint32_t baseAddr, uint32_t chn, uint32_t preChn, bool enable)
{
    assert(chn < HW_PDB_CHnC1_COUNT);
    assert(preChn < FSL_FEATURE_PDB_ADC_PRE_CHANNEL_COUNT);
    
    uint32_t tmp32 = HW_PDB_CHnC1_RD(baseAddr, chn);
    if (enable)
    {
        tmp32 |= (1U << (preChn + BP_PDB_CHnC1_BB));
    }
    else
    {
        tmp32 &= ~(1U << (preChn + BP_PDB_CHnC1_BB));
    }
    HW_PDB_CHnC1_WR(baseAddr, chn, tmp32);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : PDB_HAL_SetPreTriggerOutputCmd
 * Description   : Switch to enable pre-trigger's output.
 *
 *END*************************************************************************/
void PDB_HAL_SetPreTriggerOutputCmd(uint32_t baseAddr, uint32_t chn, uint32_t preChn, bool enable)
{
    assert(chn < HW_PDB_CHnC1_COUNT);
    assert(preChn < FSL_FEATURE_PDB_ADC_PRE_CHANNEL_COUNT);
    
    uint32_t tmp32 = HW_PDB_CHnC1_RD(baseAddr, chn);
    if (enable)
    {
        tmp32 |= (1U << (preChn + BP_PDB_CHnC1_TOS));
    }
    else
    {
        tmp32 &= ~(1U << (preChn + BP_PDB_CHnC1_TOS));
    }
    HW_PDB_CHnC1_WR(baseAddr, chn, tmp32);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : PDB_HAL_SetPreTriggerCmd
 * Description   : Switch to enable pre-trigger's.
 *
 *END*************************************************************************/
void PDB_HAL_SetPreTriggerCmd(uint32_t baseAddr, uint32_t chn, uint32_t preChn, bool enable)
{
    assert(chn < HW_PDB_CHnC1_COUNT);
    assert(preChn < FSL_FEATURE_PDB_ADC_PRE_CHANNEL_COUNT);
    uint32_t tmp32 = HW_PDB_CHnC1_RD(baseAddr, chn);
    
    if (enable)
    {
        tmp32 |= (1U << (preChn + BP_PDB_CHnC1_EN));
    }
    else
    {
        tmp32 &= ~(1U << (preChn + BP_PDB_CHnC1_EN));
    }
    HW_PDB_CHnC1_WR(baseAddr, chn, tmp32);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : PDB_HAL_ClearPreTriggerFlag
 * Description   : Clear the flag that the PDB counter reaches to the
 * pre-trigger's delay value.
 *
 *END*************************************************************************/
void PDB_HAL_ClearPreTriggerFlag(uint32_t baseAddr, uint32_t chn, uint32_t preChn)
{
    assert(chn < HW_PDB_CHnS_COUNT);
    assert(preChn < FSL_FEATURE_PDB_ADC_PRE_CHANNEL_COUNT);
    
    /* Write 0 to clear. */
    uint32_t tmp32 = HW_PDB_CHnS_RD(baseAddr, chn); /* Get current value. */
    tmp32 &= ~(1U << (preChn + BP_PDB_CHnS_CF)); /* Update the change. */
    tmp32 &= BM_PDB_CHnS_CF;  /* Limit the change range. */
    
    HW_PDB_CHnS_WR(baseAddr, chn, tmp32);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : PDB_HAL_ClearPreTriggerSeqErrFlag
 * Description   : Clear the flag that sequence error is detected.
 *
 *END*************************************************************************/
void PDB_HAL_ClearPreTriggerSeqErrFlag(uint32_t baseAddr, uint32_t chn, uint32_t preChn)
{
    assert(chn < HW_PDB_CHnS_COUNT);
    assert(preChn < FSL_FEATURE_PDB_ADC_PRE_CHANNEL_COUNT);
    
    /* Write 1 to clear. */
    uint32_t tmp32 = HW_PDB_CHnS_RD(baseAddr, chn); /* Get current value. */
    tmp32 &= ~BM_PDB_CHnS_ERR;/* Clear the operate controller. */
    tmp32 |= ( 1U << (preChn + BP_PDB_CHnS_ERR) );/* Add indicated clear operator. */
    
    HW_PDB_CHnS_WR(baseAddr, chn, tmp32);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : PDB_HAL_SetPreTriggerDelayCount
 * Description   : Set the delay value for pre-trigger.
 *
 *END*************************************************************************/
void PDB_HAL_SetPreTriggerDelayCount(uint32_t baseAddr, uint32_t chn, uint32_t preChn, uint32_t value)
{
    assert(chn < HW_PDB_CHnDLY0_COUNT);
    assert(preChn < FSL_FEATURE_PDB_ADC_PRE_CHANNEL_COUNT);
    switch (preChn)
    {
    case 0U:
        BW_PDB_CHnDLY0_DLY(baseAddr, chn, value);
        break;
#if (FSL_FEATURE_PDB_ADC_PRE_CHANNEL_COUNT > 1U)
    case 1U:
        BW_PDB_CHnDLY1_DLY(baseAddr, chn, value);
        break;
#endif /* FSL_FEATURE_PDB_ADC_PRE_CHANNEL_COUNT */
    default:
        break;
    }
}

/*FUNCTION*********************************************************************
 *
 * Function Name : PDB_HAL_SetPulseOutCmd
 * Description   : Switch to enable the pulse-out trigger.
 *
 *END*************************************************************************/
void PDB_HAL_SetPulseOutCmd(uint32_t baseAddr, uint32_t pulseChn, bool enable)
{
    assert(pulseChn < HW_PDB_POnDLY_COUNT);
    
    uint32_t tmp32 = HW_PDB_POEN_RD(baseAddr);
    
    if (enable)
    {
        tmp32 |= (1U << (pulseChn+BP_PDB_POEN_POEN));
    }
    else
    {
        tmp32 &= ~(1U << (pulseChn+BP_PDB_POEN_POEN));
    }
    HW_PDB_POEN_WR(baseAddr, tmp32);
}

/******************************************************************************
 * EOF
 *****************************************************************************/
