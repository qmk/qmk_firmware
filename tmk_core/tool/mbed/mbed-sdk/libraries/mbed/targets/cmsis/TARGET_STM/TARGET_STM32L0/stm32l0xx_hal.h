/**
  ******************************************************************************
  * @file    stm32l0xx_hal.h
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    06-February-2015
  * @brief   This file contains all the functions prototypes for the HAL 
  *          module driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
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
#ifndef __STM32L0xx_HAL_H
#define __STM32L0xx_HAL_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal_conf.h"

/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */

/** @defgroup HAL HAL
  * @{
  */ 
/** @defgroup HAL_Exported_Constants HAL Exported constants
  * @{
  */ 

/** @defgroup SYSCFG_BootMode Boot Mode
  * @{
  */
#define SYSCFG_BOOT_MAINFLASH          ((uint32_t)0x00000000)
#define SYSCFG_BOOT_SYSTEMFLASH        ((uint32_t)SYSCFG_CFGR1_MEM_MODE_0)
#define SYSCFG_BOOT_SRAM               ((uint32_t)SYSCFG_CFGR1_BOOT_MODE)     

/**
  * @}
  */ 

/** @defgroup DBGMCU_Low_Power_Config 
  * @{
  */
#define DBGMCU_SLEEP                 DBGMCU_CR_DBG_SLEEP
#define DBGMCU_STOP                  DBGMCU_CR_DBG_STOP
#define DBGMCU_STANDBY               DBGMCU_CR_DBG_STANDBY
#define IS_DBGMCU_PERIPH(__PERIPH__) ((((__PERIPH__) & (~(DBGMCU_CR_DBG))) == 0x00) && ((__PERIPH__) != 0x00))


/**
  * @}
  */
  
/** @defgroup HAL_SYSCFG_LCD_EXT_CAPA 
  * @{
  */
#define SYSCFG_LCD_EXT_CAPA             SYSCFG_CFGR2_CAPA /*!< Connection of internal Vlcd rail to external capacitors */
#define SYSCFG_VLCD_PB2_EXT_CAPA_ON     SYSCFG_CFGR2_CAPA_0  /*!< Connection on PB2   */
#define SYSCFG_VLCD_PB12_EXT_CAPA_ON    SYSCFG_CFGR2_CAPA_1  /*!< Connection on PB12  */
#define SYSCFG_VLCD_PE11_EXT_CAPA_ON    SYSCFG_CFGR2_CAPA_2  /*!< Connection on PB0   */
#if defined (SYSCFG_CFGR2_CAPA_3)
#define SYSCFG_VLCD_PB0_EXT_CAPA_ON     SYSCFG_CFGR2_CAPA_3  /*!< Connection on PE11  */
#endif
#if defined (SYSCFG_CFGR2_CAPA_4)
#define SYSCFG_VLCD_PE12_EXT_CAPA_ON    SYSCFG_CFGR2_CAPA_4  /*!< Connection on PE12  */
#endif                        

/**
  * @}
  */

/** @defgroup HAL_SYSCFG_VREFINT_OUT_SELECT 
  * @{
  */ 
#define SYSCFG_VREFINT_OUT_NONE          ((uint32_t)0x00000000) /* no pad connected */  
#define SYSCFG_VREFINT_OUT_PB0           SYSCFG_CFGR3_VREF_OUT_0 /* Selects PBO as output for the Vrefint */
#define SYSCFG_VREFINT_OUT_PB1           SYSCFG_CFGR3_VREF_OUT_1 /* Selects PB1 as output for the Vrefint */
#define SYSCFG_VREFINT_OUT_PB0_PB1       SYSCFG_CFGR3_VREF_OUT   /* Selects PBO and PB1 as output for the Vrefint */

#define IS_SYSCFG_VREFINT_OUT_SELECT(OUTPUT)   (((OUTPUT) == SYSCFG_VREFINT_OUT_NONE)  || \
                                                ((OUTPUT) == SYSCFG_VREFINT_OUT_PB0)  || \
                                                ((OUTPUT) == SYSCFG_VREFINT_OUT_PB1)  || \
                                                ((OUTPUT) == SYSCFG_VREFINT_OUT_PB0_PB1))
/**
  * @}
  */ 

/** @defgroup HAL_SYSCFG_flags_definition 
  * @{
  */
#define SYSCFG_FLAG_VREFINT_READY      SYSCFG_CFGR3_VREFINT_RDYF

#define IS_SYSCFG_FLAG(FLAG)           ((FLAG) == SYSCFG_FLAG_VREFINT_READY))

/**
  * @}
  */
 /**
  * @}
  */ 
  
 /** @defgroup HAL_Exported_Macros HAL Exported Macros
  * @{
  */  

/** @brief  Freeze/Unfreeze Peripherals in Debug mode 
  */
#if defined (DBGMCU_APB1_FZ_DBG_TIM2_STOP)
/**
  * @brief  TIM2 Peripherals Debug mode 
  */ 
#define __HAL_DBGMCU_FREEZE_TIM2()     SET_BIT(DBGMCU->APB1FZ,DBGMCU_APB1_FZ_DBG_TIM2_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM2()   CLEAR_BIT(DBGMCU->APB1FZ,DBGMCU_APB1_FZ_DBG_TIM2_STOP)
#endif

#if defined (DBGMCU_APB1_FZ_DBG_TIM3_STOP)
/**
  * @brief  TIM3 Peripherals Debug mode 
  */ 
#define __HAL_DBGMCU_FREEZE_TIM3()     SET_BIT(DBGMCU->APB1FZ,DBGMCU_APB1_FZ_DBG_TIM3_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM3()   CLEAR_BIT(DBGMCU->APB1FZ,DBGMCU_APB1_FZ_DBG_TIM3_STOP)
#endif

#if defined (DBGMCU_APB1_FZ_DBG_TIM6_STOP)
/**
  * @brief  TIM6 Peripherals Debug mode 
  */
#define __HAL_DBGMCU_FREEZE_TIM6()     SET_BIT(DBGMCU->APB1FZ, DBGMCU_APB1_FZ_DBG_TIM6_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM6()   CLEAR_BIT(DBGMCU->APB1FZ, DBGMCU_APB1_FZ_DBG_TIM6_STOP)
#endif

#if defined (DBGMCU_APB1_FZ_DBG_TIM7_STOP)
/**
  * @brief  TIM7 Peripherals Debug mode 
  */
#define __HAL_DBGMCU_FREEZE_TIM7()     SET_BIT(DBGMCU->APB1FZ, DBGMCU_APB1_FZ_DBG_TIM7_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM7()   CLEAR_BIT(DBGMCU->APB1FZ, DBGMCU_APB1_FZ_DBG_TIM7_STOP)
#endif

#if defined (DBGMCU_APB1_FZ_DBG_RTC_STOP)
/**
  * @brief  RTC Peripherals Debug mode 
  */
#define __HAL_DBGMCU_FREEZE_RTC()      SET_BIT(DBGMCU->APB1FZ, DBGMCU_APB1_FZ_DBG_RTC_STOP)
#define __HAL_DBGMCU_UNFREEZE_RTC()    CLEAR_BIT(DBGMCU->APB1FZ, DBGMCU_APB1_FZ_DBG_RTC_STOP)
#endif

#if defined (DBGMCU_APB1_FZ_DBG_WWDG_STOP)
/**
  * @brief  WWDG Peripherals Debug mode 
  */
#define __HAL_DBGMCU_FREEZE_WWDG()     SET_BIT(DBGMCU->APB1FZ, DBGMCU_APB1_FZ_DBG_WWDG_STOP)
#define __HAL_DBGMCU_UNFREEZE_WWDG()   CLEAR_BIT(DBGMCU->APB1FZ, DBGMCU_APB1_FZ_DBG_WWDG_STOP)
#endif

#if defined (DBGMCU_APB1_FZ_DBG_IWDG_STOP)
/**
  * @brief  IWDG Peripherals Debug mode 
  */
#define __HAL_DBGMCU_FREEZE_IWDG()     SET_BIT(DBGMCU->APB1FZ, DBGMCU_APB1_FZ_DBG_IWDG_STOP)
#define __HAL_DBGMCU_UNFREEZE_IWDG()   CLEAR_BIT(DBGMCU->APB1FZ, DBGMCU_APB1_FZ_DBG_IWDG_STOP)
#endif

#if defined (DBGMCU_APB1_FZ_DBG_I2C1_STOP)
/**
  * @brief  I2C1 Peripherals Debug mode 
  */
#define __HAL_DBGMCU_FREEZE_I2C1_TIMEOUT()   SET_BIT(DBGMCU->APB1FZ, DBGMCU_APB1_FZ_DBG_I2C1_STOP)
#define __HAL_DBGMCU_UNFREEZE_I2C1_TIMEOUT_DBGMCU() CLEAR_BIT(DBGMCU->APB1FZ, DBGMCU_APB1_FZ_DBG_I2C1_STOP)
#endif

#if defined (DBGMCU_APB1_FZ_DBG_I2C2_STOP)
/**
  * @brief  I2C2 Peripherals Debug mode 
  */
#define __HAL_DBGMCU_FREEZE_I2C2_TIMEOUT_DBGMCU()   SET_BIT(DBGMCU->APB1FZ, DBGMCU_APB1_FZ_DBG_I2C2_STOP)
#define __HAL_DBGMCU_UNFREEZE_I2C2_TIMEOUT_DBGMCU() CLEAR_BIT(DBGMCU->APB1FZ, DBGMCU_APB1_FZ_DBG_I2C2_STOP)
#endif

#if defined (DBGMCU_APB1_FZ_DBG_I2C3_STOP)
/**
  * @brief  I2C3 Peripherals Debug mode 
  */
#define __HAL_DBGMCU_FREEZE_I2C3_TIMEOUT()   SET_BIT(DBGMCU->APB1FZ, DBGMCU_APB1_FZ_DBG_I2C3_STOP)
#define __HAL_DBGMCU_UNFREEZE_I2C3_TIMEOUT() CLEAR_BIT(DBGMCU->APB1FZ, DBGMCU_APB1_FZ_DBG_I2C3_STOP)
#endif

#if defined (DBGMCU_APB1_FZ_DBG_LPTIMER_STOP)
/**
  * @brief  LPTIMER Peripherals Debug mode 
  */
#define __HAL_DBGMCU_FREEZE_LPTIMER()        SET_BIT(DBGMCU->APB1FZ ,DBGMCU_APB1_FZ_DBG_LPTIMER_STOP)
#define __HAL_DBGMCU_UNFREEZE_LPTIMER()      CLEAR_BIT(DBGMCU->APB1FZ ,DBGMCU_APB1_FZ_DBG_LPTIMER_STOP)
#endif

#if defined (DBGMCU_APB2_FZ_DBG_TIM22_STOP)
/**
  * @brief  TIM22 Peripherals Debug mode 
  */
#define __HAL_DBGMCU_FREEZE_TIM22()          SET_BIT(DBGMCU->APB2FZ, DBGMCU_APB2_FZ_DBG_TIM22_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM22()        CLEAR_BIT(DBGMCU->APB2FZ, DBGMCU_APB2_FZ_DBG_TIM22_STOP)
#endif

#if defined (DBGMCU_APB2_FZ_DBG_TIM21_STOP)
/**
  * @brief  TIM21 Peripherals Debug mode 
  */
#define __HAL_DBGMCU_FREEZE_TIM21()          SET_BIT(DBGMCU->APB2FZ, DBGMCU_APB2_FZ_DBG_TIM21_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM21()        CLEAR_BIT(DBGMCU->APB2FZ, DBGMCU_APB2_FZ_DBG_TIM21_STOP)
#endif

/** @brief  Main Flash memory mapped at 0x00000000
  */
#define __HAL_SYSCFG_REMAPMEMORY_FLASH()     CLEAR_BIT(SYSCFG->CFGR1, SYSCFG_CFGR1_MEM_MODE)

/** @brief  System Flash memory mapped at 0x00000000
  */
#define __HAL_SYSCFG_REMAPMEMORY_SYSTEMFLASH()      MODIFY_REG(SYSCFG->CFGR1, SYSCFG_CFGR1_MEM_MODE, SYSCFG_CFGR1_MEM_MODE_0)


/** @brief  Embedded SRAM mapped at 0x00000000
  */                                      
#define __HAL_SYSCFG_REMAPMEMORY_SRAM()             MODIFY_REG(SYSCFG->CFGR1, SYSCFG_CFGR1_MEM_MODE, SYSCFG_CFGR1_MEM_MODE_0 | SYSCFG_CFGR1_MEM_MODE_1)

/** @brief  Configuration of the DBG Low Power mode.
  * @param  __DBGLPMODE__: bit field to indicate in wich Low Power mode DBG is still active.
  *         This parameter can be a value of @ref HAL_DBGMCU_Low_Power_Config
  */
#define __HAL_SYSCFG_DBG_LP_CONFIG(__DBGLPMODE__)    do {assert_param(IS_DBGMCU_PERIPH(__DBGLPMODE__)); \
                                                       MODIFY_REG(DBGMCU->CR, DBGMCU_CR_DBG, (__DBGLPMODE__)); \
                                                     } while (0) 
/**
  * @brief  Returns the boot mode as configured by user.
  * @retval The boot mode as configured by user. The returned can be a value of @ref HAL_SYSCFG_BootMode 
  */
#define __HAL_SYSCFG_GET_BOOT_MODE()          READ_BIT(SYSCFG->CFGR1, SYSCFG_CFGR1_BOOT_MODE)


/** @brief  Check whether the specified SYSCFG flag is set or not.
  * @param  __FLAG__: specifies the flag to check.
  *         This parameter can a value of @ref HAL_SYSCFG_flags_definition
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_SYSCFG_GET_FLAG(__FLAG__) (((SYSCFG->CFGR3) & (__FLAG__)) == (__FLAG__))

/**                  
  * @}
  */

/** @defgroup HAL_Exported_Functions HAL Exported Functions
  * @{
  */
/** @defgroup HAL_Exported_Functions_Group1 Initialization and de-initialization functions
 *  @brief    Initialization and de-initialization functions
 * @{
  */
HAL_StatusTypeDef HAL_Init(void);
HAL_StatusTypeDef HAL_DeInit(void);
void HAL_MspInit(void);
void HAL_MspDeInit(void);
HAL_StatusTypeDef HAL_InitTick (uint32_t TickPriority);

/**                  
  * @}
  */
  
 /** @defgroup HAL_Exported_Functions_Group2 Peripheral Control functions 
  *  @brief    Peripheral Control functions
  * @{
  */
void HAL_IncTick(void);
void HAL_Delay(__IO uint32_t Delay);
uint32_t HAL_GetTick(void);
void HAL_SuspendTick(void);
void HAL_ResumeTick(void);
uint32_t HAL_GetHalVersion(void);
uint32_t HAL_GetREVID(void);
uint32_t HAL_GetDEVID(void);
void HAL_DBGMCU_EnableDBGSleepMode(void);
void HAL_DBGMCU_DisableDBGSleepMode(void);
void HAL_DBGMCU_EnableDBGStopMode(void);
void HAL_DBGMCU_DisableDBGStopMode(void);
void HAL_DBGMCU_EnableDBGStandbyMode(void);
void HAL_DBGMCU_DisableDBGStandbyMode(void);
void HAL_DBGMCU_DBG_EnableLowPowerConfig(uint32_t Periph);
void HAL_DBGMCU_DBG_DisableLowPowerConfig(uint32_t Periph);
uint32_t  HAL_SYSCFG_GetBootMode(void);
void HAL_SYSCFG_EnableVREFINT(void);
void HAL_SYSCFG_DisableVREFINT(void);
void HAL_SYSCFG_Enable_Lock_VREFINT(void);
void HAL_SYSCFG_Disable_Lock_VREFINT(void);
void HAL_SYSCFG_VREFINT_OutputSelect(uint32_t SYSCFG_Vrefint_OUTPUT);

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

#endif /* __STM32L0xx_HAL_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

