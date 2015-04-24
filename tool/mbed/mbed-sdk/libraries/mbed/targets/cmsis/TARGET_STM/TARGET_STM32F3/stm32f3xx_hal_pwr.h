/**
  ******************************************************************************
  * @file    stm32f3xx_hal_pwr.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    12-Sept-2014
  * @brief   Header file of PWR HAL module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F3xx_HAL_PWR_H
#define __STM32F3xx_HAL_PWR_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal_def.h"

/** @addtogroup STM32F3xx_HAL_Driver
  * @{
  */

/** @addtogroup PWR PWR HAL Driver module
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup PWR_Alias_Exported_Constants PWR Alias Exported Constants
  * @{
  */ 
/* ------------- PWR registers bit address in the alias region ---------------*/
#define PWR_OFFSET               (PWR_BASE - PERIPH_BASE)

/* --- CR Register ---*/
#define CR_OFFSET                (PWR_OFFSET + 0x00)
/* Alias word address of DBP bit */
#define DBP_BitNumber            POSITION_VAL(PWR_CR_DBP)
#define CR_DBP_BB                (PERIPH_BB_BASE + (CR_OFFSET * 32) + (DBP_BitNumber * 4))

/* Alias word address of PVDE bit */
#define PVDE_BitNumber           POSITION_VAL(PWR_CR_PVDE)
#define CR_PVDE_BB               (PERIPH_BB_BASE + (CR_OFFSET * 32) + (PVDE_BitNumber * 4))

/* --- CSR Register ---*/
#define CSR_OFFSET               (PWR_OFFSET + 0x04)
/* Alias word address of EWUP1 bit */
#define EWUP1_BitNumber          POSITION_VAL(PWR_CSR_EWUP1)
#define CSR_EWUP1_BB             (PERIPH_BB_BASE + (CSR_OFFSET * 32) + (EWUP1_BitNumber * 4))

/* Alias word address of EWUP2 bit */
#define EWUP2_BitNumber          POSITION_VAL(PWR_CSR_EWUP2)
#define CSR_EWUP2_BB             (PERIPH_BB_BASE + (CSR_OFFSET * 32) + (EWUP2_BitNumber * 4))

/* Alias word address of EWUP3 bit */
#define EWUP3_BitNumber          POSITION_VAL(PWR_CSR_EWUP3)
#define CSR_EWUP3_BB             (PERIPH_BB_BASE + (CSR_OFFSET * 32) + (EWUP3_BitNumber * 4))
/**
  * @}
  */

/** @defgroup PWR_Exported_Constants PWR Exported Constants
  * @{
  */ 

/** @defgroup PWR_WakeUp_Pins PWR WakeUp Pins
  * @{
  */

#define PWR_WAKEUP_PIN1                 ((uint32_t)0x00)
#define PWR_WAKEUP_PIN2                 ((uint32_t)0x01)
#define PWR_WAKEUP_PIN3                 ((uint32_t)0x02)
#define IS_PWR_WAKEUP_PIN(PIN) (((PIN) == PWR_WAKEUP_PIN1) || \
                                ((PIN) == PWR_WAKEUP_PIN2) || \
                                ((PIN) == PWR_WAKEUP_PIN3))
/**
  * @}
  */

/** @defgroup PWR_Regulator_state_in_STOP_mode PWR Regulator state in STOP mode
  * @{
  */
#define PWR_MAINREGULATOR_ON                        ((uint32_t)0x00000000)
#define PWR_LOWPOWERREGULATOR_ON                    PWR_CR_LPDS

#define IS_PWR_REGULATOR(REGULATOR) (((REGULATOR) == PWR_MAINREGULATOR_ON) || \
                                     ((REGULATOR) == PWR_LOWPOWERREGULATOR_ON))
/**
  * @}
  */

/** @defgroup PWR_SLEEP_mode_entry PWR SLEEP mode entry
  * @{
  */
#define PWR_SLEEPENTRY_WFI              ((uint8_t)0x01)
#define PWR_SLEEPENTRY_WFE              ((uint8_t)0x02)
#define IS_PWR_SLEEP_ENTRY(ENTRY) (((ENTRY) == PWR_SLEEPENTRY_WFI) || ((ENTRY) == PWR_SLEEPENTRY_WFE))
/**
  * @}
  */

/** @defgroup PWR_STOP_mode_entry PWR STOP mode entry
  * @{
  */
#define PWR_STOPENTRY_WFI               ((uint8_t)0x01)
#define PWR_STOPENTRY_WFE               ((uint8_t)0x02)
#define IS_PWR_STOP_ENTRY(ENTRY) (((ENTRY) == PWR_STOPENTRY_WFI) || ((ENTRY) == PWR_STOPENTRY_WFE))
/**
  * @}
  */

/** @defgroup PWR_Flag PWR Flag
  * @{
  */
#define PWR_FLAG_WU                     PWR_CSR_WUF
#define PWR_FLAG_SB                     PWR_CSR_SBF
#define PWR_FLAG_PVDO                   PWR_CSR_PVDO
#define PWR_FLAG_VREFINTRDY             PWR_CSR_VREFINTRDYF
#define IS_PWR_GET_FLAG(FLAG) (((FLAG) == PWR_FLAG_WU) || ((FLAG) == PWR_FLAG_SB) || \
                               ((FLAG) == PWR_FLAG_PVDO) || ((FLAG) == PWR_FLAG_VREFINTRDY))


/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup PWR_Exported_Macro PWR Exported Macro
  * @{
  */

/** @brief  Check PWR flag is set or not.
  * @param  __FLAG__: specifies the flag to check.
  *           This parameter can be one of the following values:
  *            @arg PWR_FLAG_WU: Wake Up flag. This flag indicates that a wakeup event
  *                  was received from the WKUP pin or from the RTC alarm (Alarm A
  *                  or Alarm B), RTC Tamper event, RTC TimeStamp event or RTC Wakeup.
  *                  An additional wakeup event is detected if the WKUP pin is enabled
  *                  (by setting the EWUP bit) when the WKUP pin level is already high.
  *            @arg PWR_FLAG_SB: StandBy flag. This flag indicates that the system was
  *                  resumed from StandBy mode.
  *            @arg PWR_FLAG_PVDO: PVD Output. This flag is valid only if PVD is enabled
  *                  by the HAL_PWR_EnablePVD() function. The PVD is stopped by Standby mode
  *                  For this reason, this bit is equal to 0 after Standby or reset
  *                  until the PVDE bit is set.
  *            @arg PWR_FLAG_VREFINTRDY: This flag indicates that the internal reference
  *                  voltage VREFINT is ready.
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_PWR_GET_FLAG(__FLAG__) ((PWR->CSR & (__FLAG__)) == (__FLAG__))

/** @brief  Clear the PWR's pending flags.
  * @param  __FLAG__: specifies the flag to clear.
  *          This parameter can be one of the following values:
  *            @arg PWR_FLAG_WU: Wake Up flag
  *            @arg PWR_FLAG_SB: StandBy flag
  */
#define __HAL_PWR_CLEAR_FLAG(__FLAG__) (PWR->CR |=  (__FLAG__) << 2)

/**
  * @}
  */

/* Include PWR HAL Extended module */
#include "stm32f3xx_hal_pwr_ex.h"

/* Exported functions --------------------------------------------------------*/

/** @addtogroup PWR_Exported_Functions PWR Exported Functions
  * @{
  */
  
/** @addtogroup PWR_Exported_Functions_Group1 Initialization and de-initialization functions 
  * @{
  */

/* Initialization and de-initialization functions *****************************/
void HAL_PWR_DeInit(void);

/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group2 Peripheral Control functions 
  * @{
  */

/* Peripheral Control functions  **********************************************/
void HAL_PWR_EnableBkUpAccess(void);
void HAL_PWR_DisableBkUpAccess(void);

/* WakeUp pins configuration functions ****************************************/
void HAL_PWR_EnableWakeUpPin(uint32_t WakeUpPinx);
void HAL_PWR_DisableWakeUpPin(uint32_t WakeUpPinx);

/* Low Power modes configuration functions ************************************/
void HAL_PWR_EnterSTOPMode(uint32_t Regulator, uint8_t STOPEntry);
void HAL_PWR_EnterSLEEPMode(uint32_t Regulator, uint8_t SLEEPEntry);
void HAL_PWR_EnterSTANDBYMode(void);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif


#endif /* __STM32F3xx_HAL_PWR_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
