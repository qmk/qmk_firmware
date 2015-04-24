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

#include "fsl_i2c_hal.h"
#include "fsl_misc_utilities.h" /* For ARRAY_SIZE*/

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @brief An entry in the I2C divider table.
 *
 * This struct pairs the value of the I2C_F.ICR bitfield with the resulting
 * clock divider value.
 */
typedef struct I2CDividerTableEntry {
    uint8_t icr;            /*!< F register ICR value.*/
    uint16_t sclDivider;    /*!< SCL clock divider.*/
} i2c_divider_table_entry_t;

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*!
 * @brief I2C divider values.
 *
 * This table is taken from the I2C Divider and Hold values section of the
 * reference manual. In the original table there are, in some cases, multiple
 * entries with the same divider but different hold values. This table
 * includes only one entry for every divider, selecting the lowest hold value.
 */
const i2c_divider_table_entry_t kI2CDividerTable[] = {
        /* ICR  Divider*/
        { 0x00, 20 },
        { 0x01, 22 },
        { 0x02, 24 },
        { 0x03, 26 },
        { 0x04, 28 },
        { 0x05, 30 },
        { 0x09, 32 },
        { 0x06, 34 },
        { 0x0a, 36 },
        { 0x07, 40 },
        { 0x0c, 44 },
        { 0x0d, 48 },
        { 0x0e, 56 },
        { 0x12, 64 },
        { 0x0f, 68 },
        { 0x13, 72 },
        { 0x14, 80 },
        { 0x15, 88 },
        { 0x19, 96 },
        { 0x16, 104 },
        { 0x1a, 112 },
        { 0x17, 128 },
        { 0x1c, 144 },
        { 0x1d, 160 },
        { 0x1e, 192 },
        { 0x22, 224 },
        { 0x1f, 240 },
        { 0x23, 256 },
        { 0x24, 288 },
        { 0x25, 320 },
        { 0x26, 384 },
        { 0x2a, 448 },
        { 0x27, 480 },
        { 0x2b, 512 },
        { 0x2c, 576 },
        { 0x2d, 640 },
        { 0x2e, 768 },
        { 0x32, 896 },
        { 0x2f, 960 },
        { 0x33, 1024 },
        { 0x34, 1152 },
        { 0x35, 1280 },
        { 0x36, 1536 },
        { 0x3a, 1792 },
        { 0x37, 1920 },
        { 0x3b, 2048 },
        { 0x3c, 2304 },
        { 0x3d, 2560 },
        { 0x3e, 3072 },
        { 0x3f, 3840 }
    };

/*******************************************************************************
 * Code
 ******************************************************************************/
/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_HAL_Init
 * Description   : Initialize I2C peripheral to reset state.
 *
 *END**************************************************************************/
void I2C_HAL_Init(uint32_t baseAddr)
{
    
    HW_I2C_A1_WR(baseAddr, 0u);
    HW_I2C_F_WR(baseAddr, 0u);
    HW_I2C_C1_WR(baseAddr, 0u);
    HW_I2C_S_WR(baseAddr, 0u);
    HW_I2C_D_WR(baseAddr, 0u);
    HW_I2C_C2_WR(baseAddr, 0u);
    HW_I2C_FLT_WR(baseAddr, 0u);
    HW_I2C_RA_WR(baseAddr, 0u);
    
#if FSL_FEATURE_I2C_HAS_SMBUS
    HW_I2C_SMB_WR(baseAddr, 0u);
    HW_I2C_A2_WR(baseAddr, 0xc2u);
    HW_I2C_SLTH_WR(baseAddr, 0u);
    HW_I2C_SLTL_WR(baseAddr, 0u);
#endif /* FSL_FEATURE_I2C_HAS_SMBUS*/
}

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_HAL_SetBaudRate
 * Description   : Sets the I2C bus frequency for master transactions.
 *
 *END**************************************************************************/
i2c_status_t I2C_HAL_SetBaudRate(uint32_t baseAddr, uint32_t sourceClockInHz, uint32_t kbps,
                                  uint32_t * absoluteError_Hz)
{
    uint32_t mult, i, multiplier;
    uint32_t hz = kbps * 1000u;
    uint32_t bestError = 0xffffffffu;
    uint32_t bestMult = 0u;
    uint32_t bestIcr = 0u;
       
    /* Check if the requested frequency is greater than the max supported baud.*/
    if ((kbps * 1000U) > (sourceClockInHz / (1U * 20U)))
    {
        return kStatus_I2C_OutOfRange;
    }
    
    /* Search for the settings with the lowest error.
     * mult is the MULT field of the I2C_F register, and ranges from 0-2. It selects the
     * multiplier factor for the divider. */
    for (mult = 0u; (mult <= 2u) && (bestError != 0); ++mult)
    {
        multiplier = 1u << mult;
        
        /* Scan table to find best match.*/
        for (i = 0u; i < ARRAY_SIZE(kI2CDividerTable); ++i)
        {
            uint32_t computedRate = sourceClockInHz / (multiplier * kI2CDividerTable[i].sclDivider);
            uint32_t absError = hz > computedRate ? hz - computedRate : computedRate - hz;
            
            if (absError < bestError)
            {
                bestMult = mult;
                bestIcr = kI2CDividerTable[i].icr;
                bestError = absError;
                
                /* If the error is 0, then we can stop searching
                 * because we won't find a better match.*/
                if (absError == 0)
                {
                    break;
                }
            }
        }
    }

    /* Set the resulting error.*/
    if (absoluteError_Hz)
    {
        *absoluteError_Hz = bestError;
    }
    
    /* Set frequency register based on best settings.*/
    HW_I2C_F_WR(baseAddr, BF_I2C_F_MULT(bestMult) | BF_I2C_F_ICR(bestIcr));
    
    return kStatus_I2C_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_HAL_SendStart
 * Description   : Send a START or Repeated START signal on the I2C bus.
 * This function is used to initiate a new master mode transfer by sending the
 * START signal. It is also used to send a Repeated START signal when a transfer
 * is already in progress.
 *
 *END**************************************************************************/
void I2C_HAL_SendStart(uint32_t baseAddr)
{
    /* Check if we're in a master mode transfer.*/
    if (BR_I2C_C1_MST(baseAddr))
    {
#if FSL_FEATURE_I2C_HAS_ERRATA_6070
        /* Errata 6070: Repeat start cannot be generated if the I2Cx_F[MULT] field is set to a
         * non- zero value.
         * The workaround is to either always keep MULT set to 0, or to temporarily set it to
         * 0 while performing the repeated start and then restore it.*/
        uint32_t savedMult = 0;
        if (BR_I2C_F_MULT(baseAddr) != 0)
        {
            savedMult = BR_I2C_F_MULT(baseAddr);
            BW_I2C_F_MULT(baseAddr, 0U);
        }
#endif /* FSL_FEATURE_I2C_HAS_ERRATA_6070*/

        /* We are already in a transfer, so send a repeated start.*/
        BW_I2C_C1_RSTA(baseAddr, 1U);

#if FSL_FEATURE_I2C_HAS_ERRATA_6070
        if (savedMult)
        {
            BW_I2C_F_MULT(baseAddr, savedMult);
        }
#endif /* FSL_FEATURE_I2C_HAS_ERRATA_6070*/
    }
    else
    {
        /* Initiate a transfer by sending the start signal.*/
        HW_I2C_C1_SET(baseAddr, BM_I2C_C1_MST | BM_I2C_C1_TX);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_HAL_SetAddress7bit
 * Description   : Sets the primary 7-bit slave address.
 *
 *END**************************************************************************/
void I2C_HAL_SetAddress7bit(uint32_t baseAddr, uint8_t address)
{
    /* Set 7-bit slave address.*/
    HW_I2C_A1_WR(baseAddr, address << 1U);
    
    /* Disable the address extension option, selecting 7-bit mode.*/
    BW_I2C_C2_ADEXT(baseAddr, 0U);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_HAL_SetAddress10bit
 * Description   : Sets the primary slave address and enables 10-bit address mode.
 *
 *END**************************************************************************/
void I2C_HAL_SetAddress10bit(uint32_t baseAddr, uint16_t address)
{
    
    uint8_t temp;

    /* Set bottom 7 bits of slave address.*/
    temp = address & 0x7FU;
    HW_I2C_A1_WR(baseAddr, temp << 1U);
    
    /* Enable 10-bit address extension.*/
    BW_I2C_C2_ADEXT(baseAddr, 1U);
    
    /* Set top 3 bits of slave address.*/
    BW_I2C_C2_AD(baseAddr, (address & 0x0380U) >> 7U);
}

/*******************************************************************************
 * EOF
 ******************************************************************************/


