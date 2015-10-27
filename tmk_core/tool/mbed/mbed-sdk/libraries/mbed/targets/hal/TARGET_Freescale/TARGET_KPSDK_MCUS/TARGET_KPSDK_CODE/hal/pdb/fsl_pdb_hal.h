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

#ifndef __FSL_PDB_HAL_H__
#define __FSL_PDB_HAL_H__

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_device_registers.h"
#include "fsl_pdb_features.h"

/*!
 * @addtogroup pdb_hal
 * @{
 */

/******************************************************************************
 * Definitions
 *****************************************************************************/

/*!
 * @brief PDB status return codes.
 */
typedef enum _pdb_status
{
    kStatus_PDB_Success = 0U, /*!< Success. */
    kStatus_PDB_InvalidArgument = 1U, /*!< Invalid argument existed. */
    kStatus_PDB_Failed = 2U /*!< Execution failed. */
} pdb_status_t;

/*!
 * @brief Defines the type of value load mode for the PDB module.
 *
 * Some timing related registers, such as the MOD, IDLY, CHnDLYm, INTx and POyDLY, 
 * buffer the setting values. Only the load operation is triggered.
 * The setting value is loaded from a buffer and takes effect. There are
 * four loading modes to fit different applications.
 */
typedef enum _pdb_load_mode
{
    kPdbLoadImmediately = 0U, 
        /*!<  Loaded immediately after load operation. */
    kPdbLoadAtModuloCounter = 1U, 
        /*!< Loaded when counter hits the modulo after load operation. */
    kPdbLoadAtNextTrigger = 2U,
        /*!< Loaded when detecting an input trigger after load operation. */
    kPdbLoadAtModuloCounterOrNextTrigger = 3U 
        /*!< Loaded when counter hits the modulo or detecting an input trigger after load operation. */
} pdb_load_mode_t;

/*!
 * @brief Defines the type of prescaler divider for the PDB counter clock.
 */
typedef enum _pdb_clk_prescaler_div_mode
{
    kPdbClkPreDivBy1   = 0U, /*!< Counting divided by multiplication factor selected by MULT. */
    kPdbClkPreDivBy2   = 1U, /*!< Counting divided by multiplication factor selected by 2 times ofMULT. */
    kPdbClkPreDivBy4   = 2U, /*!< Counting divided by multiplication factor selected by 4 times ofMULT. */
    kPdbClkPreDivBy8   = 3U, /*!< Counting divided by multiplication factor selected by 8 times ofMULT. */
    kPdbClkPreDivBy16  = 4U, /*!< Counting divided by multiplication factor selected by 16 times ofMULT. */
    kPdbClkPreDivBy32  = 5U, /*!< Counting divided by multiplication factor selected by 32 times ofMULT. */
    kPdbClkPreDivBy64  = 6U, /*!< Counting divided by multiplication factor selected by 64 times ofMULT. */
    kPdbClkPreDivBy128 = 7U, /*!< Counting divided by multiplication factor selected by 128 times ofMULT. */
} pdb_clk_prescaler_div_mode_t;

/*!
 * @brief Defines the type of trigger source mode for the PDB.
 *
 * Selects the trigger input source for the PDB. The trigger input source can
 * be internal or external (EXTRG pin), or the software trigger.
 */
typedef enum _pdb_trigger_src_mode
{
    kPdbTrigger0  = 0U,  /*!< Select trigger-In 0. */
    kPdbTrigger1  = 1U,  /*!< Select trigger-In 1. */
    kPdbTrigger2  = 2U,  /*!< Select trigger-In 2. */
    kPdbTrigger3  = 3U,  /*!< Select trigger-In 3. */
    kPdbTrigger4  = 4U,  /*!< Select trigger-In 4. */
    kPdbTrigger5  = 5U,  /*!< Select trigger-In 5. */
    kPdbTrigger6  = 6U,  /*!< Select trigger-In 6. */
    kPdbTrigger7  = 7U,  /*!< Select trigger-In 7. */
    kPdbTrigger8  = 8U,  /*!< Select trigger-In 8. */
    kPdbTrigger9  = 9U,  /*!< Select trigger-In 8. */
    kPdbTrigger10 = 10U, /*!< Select trigger-In 10. */
    kPdbTrigger11 = 11U, /*!< Select trigger-In 11. */
    kPdbTrigger12 = 12U, /*!< Select trigger-In 12. */
    kPdbTrigger13 = 13U, /*!< Select trigger-In 13. */
    kPdbTrigger14 = 14U, /*!< Select trigger-In 14. */
    kPdbSoftTrigger = 15U, /*!< Select software trigger. */
} pdb_trigger_src_mode_t;

/*!
 * @brief Defines the type of the multiplication source mode for PDB.
 *
 * Selects the multiplication factor of the prescaler divider for the PDB counter clock.
 */
typedef enum _pdb_mult_factor_mode
{
    kPdbMultFactorAs1  = 0U, /*!< Multiplication factor is 1. */
    kPdbMultFactorAs10 = 1U, /*!< Multiplication factor is 10. */
    kPdbMultFactorAs20 = 2U, /*!< Multiplication factor is 20. */
    kPdbMultFactorAs40 = 3U  /*!< Multiplication factor is 40. */
} pdb_mult_factor_mode_t;

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @brief Resets the PDB registers to a known state.
 *
 * This function resets the PDB registers to a known state. This state is
 * defined in a reference manual and is power on reset value.
 *
 * @param baseAddr Register base address for the module.
 */
void PDB_HAL_Init(uint32_t baseAddr);

/*!
 * @brief Sets the load mode for timing registers.
 *
 * This function sets the load mode for some timing registers including
 * MOD, IDLY, CHnDLYm, INTx and POyDLY.
 *
 * @param baseAddr Register base address for the module.
 * @param mode  Selection of mode, see to "pdb_load_mode_t".
 */
static inline void PDB_HAL_SetLoadMode(uint32_t baseAddr, pdb_load_mode_t mode)
{
    BW_PDB_SC_LDMOD(baseAddr, (uint32_t)mode);
}

/*!
 * @brief Switches to enable the PDB sequence error interrupt.
 *
 * This function switches to enable the PDB sequence error interrupt.
 *
 * @param baseAddr Register base address for the module.
 * @param enable The switcher to assert the feature.
 */
static inline void PDB_HAL_SetSeqErrIntCmd(uint32_t baseAddr, bool enabled)
{
    BW_PDB_SC_PDBEIE(baseAddr, (enabled ? 1U : 0U) );
}

/*!
 * @brief Triggers the DAC by software if enabled.
 *
 * If enabled, this function triggers the DAC by using software.
 *
 * @param baseAddr Register base address for the module.
 */
static inline void PDB_HAL_SetSoftTriggerCmd(uint32_t baseAddr)
{
    BW_PDB_SC_SWTRIG(baseAddr, 1U);
}

/*!
 * @brief Switches to enable the PDB DMA support.
 *
 * This function switches to enable the PDB DMA support.
 *
 * @param baseAddr Register base address for the module.
 * @param enable The switcher to assert the feature.
 */
static inline void PDB_HAL_SetDmaCmd(uint32_t baseAddr, bool enable)
{
    BW_PDB_SC_DMAEN(baseAddr, (enable ? 1U : 0U) );
}

/*!
 * @brief Sets the prescaler divider from the peripheral bus clock for the PDB.
 *
 * This function sets the prescaler divider from the peripheral bus clock for the PDB.
 *
 * @param baseAddr Register base address for the module.
 * @param mode Selection of mode, see to "pdb_clk_prescaler_div_mode_t".
 */
static inline void PDB_HAL_SetPreDivMode(uint32_t baseAddr, pdb_clk_prescaler_div_mode_t mode)
{
    BW_PDB_SC_PRESCALER(baseAddr, (uint32_t)mode);
}

/*!
 * @brief Sets the trigger source mode for the PDB module.
 *
 * This function sets the trigger source mode for the PDB module.
 *
 * @param baseAddr Register base address for the module.
 * @param mode Selection of mode, see to "pdb_trigger_src_mode_t".
 */
static inline void PDB_HAL_SetTriggerSrcMode(uint32_t baseAddr, pdb_trigger_src_mode_t mode)
{
    BW_PDB_SC_TRGSEL(baseAddr, (uint32_t)mode);
}

/*!
 * @brief Switches on to enable the PDB module.
 *
 * This function switches on to enable the PDB module.
 *
 * @param baseAddr Register base address for the module.
 */
static inline void PDB_HAL_Enable(uint32_t baseAddr)
{
    BW_PDB_SC_PDBEN(baseAddr, 1U);
}

/*!
 * @brief Switches off to enable the PDB module.
 *
 * This function switches off to enable the PDB module.
 *
 * @param baseAddr Register base address for the module.
 */
static inline void PDB_HAL_Disable(uint32_t baseAddr)
{
    BW_PDB_SC_PDBEN(baseAddr, 0U);
}

/*!
 * @brief Gets the PDB delay interrupt flag.
 *
 * This function gets the PDB delay interrupt flag.
 *
 * @param baseAddr Register base address for the module.
 * @return Flat status, true if the flag is set.
 */
static inline bool PDB_HAL_GetIntFlag(uint32_t baseAddr)
{
    return (1U == BR_PDB_SC_PDBIF(baseAddr));
}

/*!
 * @brief Clears the PDB delay interrupt flag.
 *
 * This function clears PDB delay interrupt flag.
 *
 * @param baseAddr Register base address for the module.
 * @return Flat status, true if the flag is set.
 */
static inline void PDB_HAL_ClearIntFlag(uint32_t baseAddr)
{
    BW_PDB_SC_PDBIF(baseAddr, 0U);
}

/*!
 * @brief Switches to enable the PDB interrupt.
 *
 * This function switches to enable the PDB interrupt.
 *
 * @param baseAddr Register base address for the module.
 * @param enable The switcher to assert the feature.
 */
static inline void PDB_HAL_SetIntCmd(uint32_t baseAddr, bool enable)
{
    BW_PDB_SC_PDBIE(baseAddr, (enable ? 1U : 0U) );
}

/*!
 * @brief Sets the PDB prescaler multiplication factor.
 *
 * This function sets the PDB prescaler multiplication factor.
 *
 * @param baseAddr Register base address for the module.
 * @param mode Selection of mode, see to "pdb_mult_factor_mode_t".
 */
static inline void PDB_HAL_SetPreMultFactorMode(uint32_t baseAddr,
    pdb_mult_factor_mode_t mode)
{
    BW_PDB_SC_MULT(baseAddr, (uint32_t)mode);
}

/*!
 * @brief Switches to enable the PDB continuous mode.
 *
 * This function switches to enable the PDB continuous mode.
 *
 * @param baseAddr Register base address for the module.
 * @param enable The switcher to assert the feature.
 */
static inline void PDB_HAL_SetContinuousModeCmd(uint32_t baseAddr, bool enable)
{
    BW_PDB_SC_CONT(baseAddr, (enable ? 1U : 0U) );
}

/*!
 * @brief Loads the delay registers value for the PDB module.
 *
 * This function sets the LDOK bit and loads the delay registers value.
 * Writing one  to this bit updates the internal registers MOD, IDLY, CHnDLYm, 
 * DACINTx, and POyDLY with the values written to their buffers. The MOD, IDLY, 
 * CHnDLYm, DACINTx, and POyDLY take effect according to the load mode settings.
 *
 * After one is written to the LDOK bit, the values in the buffers of above mentioned registers 
 * are not effective and cannot be written until the values in the
 * buffers are loaded into their internal registers. 
 * The LDOK can be written only when the the PDB is enabled or as alone with it. It is
 * automatically cleared either when the values in the buffers are loaded into the
 * internal registers or when the PDB is disabled.
 *
 * @param baseAddr Register base address for the module.
 */
static inline void PDB_HAL_SetLoadRegsCmd(uint32_t baseAddr)
{
    BW_PDB_SC_LDOK(baseAddr, 1U);
}

/*!
 * @brief Sets the modulus value for the PDB module.
 *
 * This function sets the modulus value for the PDB module.
 * When the counter reaches the setting value, it is automatically reset to zero.
 * When in continuous mode, the counter begins to increase
 * again.
 *
 * @param baseAddr Register base address for the module.
 * @param value The setting value of upper limit for PDB counter.
 */
static inline void PDB_HAL_SetModulusValue(uint32_t baseAddr, uint32_t value)
{
    BW_PDB_MOD_MOD(baseAddr, value);
}

/*!
 * @brief Gets the modulus value for the PDB module.
 *
 * This function gets the modulus value for the PDB module.
 *
 * @param baseAddr Register base address for the module.
 * @return The current value of upper limit for counter.
 */
static inline uint32_t PDB_HAL_GetModulusValue(uint32_t baseAddr)
{
    return BR_PDB_MOD_MOD(baseAddr);
}

/*!
 * @brief Gets the PDB counter value.
 *
 * This function gets the PDB counter value.
 *
 * @param baseAddr Register base address for the module.
 * @return The current counter value.
 */
static inline uint32_t PDB_HAL_GetCounterValue(uint32_t baseAddr)
{
    return BR_PDB_CNT_CNT(baseAddr);
}

/*!
 * @brief Sets the interrupt delay milestone of the PDB counter.
 *
 * This function sets the interrupt delay milestone of the PDB counter.
 * If enabled, a PDB interrupt is generated when the counter is equal to the 
 * setting value. 
 *
 * @param baseAddr Register base address for the module.
 * @param value The setting value for interrupt delay milestone of PDB counter.
 */
static inline void PDB_HAL_SetIntDelayValue(uint32_t baseAddr, uint32_t value)
{
    BW_PDB_IDLY_IDLY(baseAddr, value);
}

/*!
 * @brief Gets the current interrupt delay milestone of the PDB counter.
 *
 * This function gets the current interrupt delay milestone of the PDB counter.
 *
 * @param baseAddr Register base address for the module.
 * @return The current setting value for interrupt delay milestone of PDB counter.
 */
static inline uint32_t PDB_HAL_GetIntDelayValue(uint32_t baseAddr)
{
    return BR_PDB_IDLY_IDLY(baseAddr);
}

/*!
 * @brief Switches to enable the pre-trigger back-to-back mode.
 *
 * This function switches to enable the pre-trigger back-to-back mode.
 *
 * @param baseAddr Register base address for the module.
 * @param chn ADC instance index for trigger.
 * @param preChn ADC channel group index for trigger.
 * @param enable Switcher to assert the feature.
 */
void PDB_HAL_SetPreTriggerBackToBackCmd(uint32_t baseAddr, uint32_t chn, uint32_t preChn, bool enable);

/*!
 * @brief Switches to enable the pre-trigger output.
 *
 * This function switches to enable pre-trigger output.
 *
 * @param baseAddr Register base address for the module.
 * @param chn ADC instance index for trigger.
 * @param preChn ADC channel group index for trigger.
 * @param enable Switcher to assert the feature.
 */
void PDB_HAL_SetPreTriggerOutputCmd(uint32_t baseAddr, uint32_t chn, uint32_t preChn, bool enable);

/*!
 * @brief Switches to enable the pre-trigger.
 *
 * This function switches to enable the pre-trigger.
 *
 * @param baseAddr Register base address for the module.
 * @param chn ADC instance index for trigger.
 * @param preChn ADC channel group index for trigger.
 * @param enable Switcher to assert the feature.
 */
void PDB_HAL_SetPreTriggerCmd(uint32_t baseAddr, uint32_t chn, uint32_t preChn, bool enable);

/*!
 * @brief Gets the flag which indicates whether the PDB counter has reached the pre-trigger delay value.
 *
 * This function gets the flag which indicates the PDB counter has reached the
 * pre-trigger delay value.
 *
 * @param baseAddr Register base address for the module.
 * @param chn ADC instance index for trigger.
 * @param preChn ADC channel group index for trigger.
 * @return Flag status. True if the event is asserted.
 */
static inline bool PDB_HAL_GetPreTriggerFlag(uint32_t baseAddr, uint32_t chn, uint32_t preChn)
{
    assert(chn < HW_PDB_CHnC1_COUNT);
    assert(preChn < FSL_FEATURE_PDB_ADC_PRE_CHANNEL_COUNT);
    return ( ((1U<< preChn) & BR_PDB_CHnS_CF(baseAddr, chn))? true: false);
}

/*!
 * @brief Clears the flag which indicates that the PDB counter has reached the pre-trigger delay value.
 *
 * This function clears the flag which indicates that the PDB counter has reached  the
 * pre-trigger delay value.
 *
 * @param baseAddr Register base address for the module.
 * @param chn ADC instance index for trigger.
 * @param preChn ADC channel group index for trigger.
 */
void PDB_HAL_ClearPreTriggerFlag(uint32_t baseAddr, uint32_t chn, uint32_t preChn);

/*!
 * @brief Gets the flag which indicates whether a sequence error is detected.
 *
 * This function gets the flag which indicates whether a sequence error is detected.
 *
 * @param baseAddr Register base address for the module.
 * @param chn ADC instance index for trigger.
 * @param preChn ADC channel group index for trigger.
 * @return Flag status. True if the event is asserted.
 */
static inline bool PDB_HAL_GetPreTriggerSeqErrFlag(uint32_t baseAddr, uint32_t chn, uint32_t preChn)
{
    assert(chn < HW_PDB_CHnC1_COUNT);
    assert(preChn < FSL_FEATURE_PDB_ADC_PRE_CHANNEL_COUNT);
    return ( ((1U<< preChn) & BR_PDB_CHnS_ERR(baseAddr, chn))? true: false);
}

/*!
 * @brief Clears the flag which indicates that a sequence error has been detected.
 *
 * This function clears the flag which indicates that the sequence error has been detected.
 *
 * @param baseAddr Register base address for the module.
 * @param chn ADC instance index for trigger.
 * @param preChn ADC channel group index for trigger.
 */
void PDB_HAL_ClearPreTriggerSeqErrFlag(uint32_t baseAddr, uint32_t chn, uint32_t preChn);

/*!
 * @brief Sets the pre-trigger delay value.
 *
 * This function sets the pre-trigger delay value.
 *
 * @param baseAddr Register base address for the module.
 * @param chn ADC instance index for trigger.
 * @param preChn ADC channel group index for trigger.
 * @param value Setting value for pre-trigger's delay value.
 */
void PDB_HAL_SetPreTriggerDelayCount(uint32_t baseAddr, uint32_t chn, uint32_t preChn, uint32_t value);

/*!
 * @brief Switches to enable the DAC external trigger input.
 *
 * This function switches to enable the DAC external trigger input.
 *
 * @param baseAddr Register base address for the module.
 * @param dacChn DAC instance index for trigger.
 * @param value Setting value for pre-trigger's delay value.
 */
static inline void PDB_HAL_SetDacExtTriggerInputCmd(uint32_t baseAddr, uint32_t dacChn, bool enable)
{
    assert(dacChn < HW_PDB_DACINTCn_COUNT);
    BW_PDB_DACINTCn_EXT(baseAddr, dacChn, (enable ? 1U: 0U) );
}

/*!
 * @brief Switches to enable the DAC external trigger input.
 *
 * This function switches to enable the DAC external trigger input.
 *
 * @param baseAddr Register base address for the module.
 * @param dacChn DAC instance index for trigger.
 * @param enable Switcher to assert the feature.
 */
static inline void PDB_HAL_SetDacIntervalTriggerCmd(uint32_t baseAddr, uint32_t dacChn, bool enable)
{
    assert(dacChn < HW_PDB_DACINTCn_COUNT);
    BW_PDB_DACINTCn_TOE(baseAddr, dacChn, (enable ? 1U: 0U) );
}

/*!
 * @brief Sets the interval value for the DAC trigger.
 *
 * This function sets the interval value for the DAC trigger.
 *
 * @param baseAddr Register base address for the module.
 * @param dacChn DAC instance index for trigger.
 * @param value Setting value for DAC trigger interval.
 */
static inline void PDB_HAL_SetDacIntervalValue(uint32_t baseAddr, uint32_t dacChn, uint32_t value)
{
    assert(dacChn < HW_PDB_DACINTn_COUNT);
    BW_PDB_DACINTn_INT(baseAddr, dacChn, value);
}

/*!
 * @brief Gets the interval value for the DAC trigger.
 *
 * This function gets the interval value for the DAC trigger.
 *
 * @param baseAddr Register base address for the module.
 * @param dacChn DAC instance index for trigger.
 * @return The current setting value for DAC trigger interval.
 */
static inline uint32_t PDB_HAL_GetDacIntervalValue(uint32_t baseAddr, uint32_t dacChn)
{
    assert(dacChn < HW_PDB_DACINTn_COUNT);
    return BR_PDB_DACINTn_INT(baseAddr, dacChn);
}

/*!
 * @brief Switches to enable the pulse-out trigger.
 *
 * This function switches to enable the pulse-out trigger.
 *
 * @param baseAddr Register base address for the module.
 * @param pulseChn Pulse-out channle index for trigger.
 * @param enable Switcher to assert the feature.
 */
void PDB_HAL_SetPulseOutCmd(uint32_t baseAddr, uint32_t pulseChn, bool enable);

/*!
 * @brief Sets the counter delay value for the pulse-out goes high.
 *
 * This function sets the counter delay value for the pulse-out goes high.
 *
 * @param baseAddr Register base address for the module.
 * @param pulseChn Pulse-out channel index for trigger.
 * @param value Setting value for PDB delay .
 */
static inline void PDB_HAL_SetPulseOutDelayForHigh(uint32_t baseAddr, uint32_t pulseChn, uint32_t value)
{
    assert(pulseChn < HW_PDB_POnDLY_COUNT);
    BW_PDB_POnDLY_DLY1(baseAddr, pulseChn, value);
}

/*!
 * @brief Sets the counter delay value for the pulse-out goes low.
 *
 * This function sets the counter delay value for the pulse-out goes low.
 *
 * @param baseAddr Register base address for the module.
 * @param pulseChn Pulse-out channel index for trigger.
 * @param value Setting value for PDB delay .
 */
static inline void PDB_HAL_SetPulseOutDelayForLow(uint32_t baseAddr, uint32_t pulseChn, uint32_t value)
{
    assert(pulseChn < HW_PDB_POnDLY_COUNT);
    BW_PDB_POnDLY_DLY2(baseAddr, pulseChn, value);
}

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */

#endif /* __FSL_PDB_HAL_H__ */

/******************************************************************************
 * EOF
 *****************************************************************************/

