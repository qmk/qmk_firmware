/**
  ******************************************************************************
  * @file    stm32l1xx_ll_fsmc.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    5-September-2014
  * @brief   FSMC Low Layer HAL module driver.
  *    
  *          This file provides firmware functions to manage the following 
  *          functionalities of the Flexible Static Memory Controller (FSMC) peripheral memories:
  *           + Initialization/de-initialization functions
  *           + Peripheral Control functions 
  *           + Peripheral State functions
  *         
  @verbatim
  =============================================================================
                        ##### FSMC peripheral features #####
  =============================================================================
    [..] The Flexible static memory controller (FSMC) includes following memory controllers:
         (+) The NOR/PSRAM memory controller
       
    [..] The FSMC functional block makes the interface with synchronous and asynchronous static
         memories and SDRAM memories. Its main purposes are:
         (+) to translate AHB transactions into the appropriate external device protocol.
         (+) to meet the access time requirements of the external memory devices.
   
    [..] All external memories share the addresses, data and control signals with the controller.
         Each external device is accessed by means of a unique Chip Select. The FSMC performs
         only one access at a time to an external device.
         The main features of the FSMC controller are the following:
          (+) Interface with static-memory mapped devices including:
             (++) Static random access memory (SRAM).
             (++) NOR Flash memory.
             (++) PSRAM (4 memory banks).
          (+) Independent Chip Select control for each memory bank.
          (+) Independent configuration for each memory bank.          
        
  =============================================================================
                   ##### How to use NORSRAM device driver #####
  =============================================================================
 
  [..] 
    This driver contains a set of APIs to interface with the FSMC NORSRAM banks in order
    to run the NORSRAM external devices.
      
    (+) FSMC NORSRAM bank reset using the function FSMC_NORSRAM_DeInit() 
    (+) FSMC NORSRAM bank control configuration using the function FSMC_NORSRAM_Init()
    (+) FSMC NORSRAM bank timing configuration using the function FSMC_NORSRAM_Timing_Init()
    (+) FSMC NORSRAM bank extended timing configuration using the function 
        FSMC_NORSRAM_Extended_Timing_Init()
    (+) FSMC NORSRAM bank enable/disable write operation using the functions
        FSMC_NORSRAM_WriteOperation_Enable()/FSMC_NORSRAM_WriteOperation_Disable()

  @endverbatim
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

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal.h"

/** @addtogroup STM32L1xx_HAL_Driver
  * @{
  */

/** @defgroup FSMC_LL FSMC_LL
  * @brief FSMC driver modules
  * @{
  */

#if defined (HAL_SRAM_MODULE_ENABLED) || defined(HAL_NOR_MODULE_ENABLED)

#if defined (STM32L151xD) || defined (STM32L152xD) || defined (STM32L162xD)

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/    
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup FSMC_Exported_Functions FSMC Exported Functions
  * @{
  */

/** @defgroup HAL_FSMC_NORSRAM_Group1 Initialization/de-initialization functions 
  * @brief    Initialization and Configuration functions 
  *
  @verbatim    
  ==============================================================================
              ##### Initialization and de_initialization functions #####
  ==============================================================================
  [..]  
    This section provides functions allowing to:
    (+) Initialize and configure the FSMC NORSRAM interface
    (+) De-initialize the FSMC NORSRAM interface 
    (+) Configure the FSMC clock and associated GPIOs    
 
@endverbatim
  * @{
  */
  
/**
  * @brief  Initialize the FSMC_NORSRAM device according to the specified
  *         control parameters in the FSMC_NORSRAM_InitTypeDef
  * @param  Device: Pointer to NORSRAM device instance
  * @param  Init: Pointer to NORSRAM Initialization structure   
  * @retval HAL status
  */
HAL_StatusTypeDef  FSMC_NORSRAM_Init(FSMC_NORSRAM_TYPEDEF *Device, FSMC_NORSRAM_InitTypeDef* Init)
{ 
  uint32_t tmpr = 0;
    
  /* Check the parameters */
  assert_param(IS_FSMC_NORSRAM_BANK(Init->NSBank));
  assert_param(IS_FSMC_MUX(Init->DataAddressMux));
  assert_param(IS_FSMC_MEMORY(Init->MemoryType));
  assert_param(IS_FSMC_NORSRAM_MEMORY_WIDTH(Init->MemoryDataWidth));
  assert_param(IS_FSMC_BURSTMODE(Init->BurstAccessMode));
  assert_param(IS_FSMC_WAIT_POLARITY(Init->WaitSignalPolarity));
  assert_param(IS_FSMC_WRAP_MODE(Init->WrapMode));
  assert_param(IS_FSMC_WAIT_SIGNAL_ACTIVE(Init->WaitSignalActive));
  assert_param(IS_FSMC_WRITE_OPERATION(Init->WriteOperation));
  assert_param(IS_FSMC_WAITE_SIGNAL(Init->WaitSignal));
  assert_param(IS_FSMC_EXTENDED_MODE(Init->ExtendedMode));
  assert_param(IS_FSMC_ASYNWAIT(Init->AsynchronousWait));
  assert_param(IS_FSMC_WRITE_BURST(Init->WriteBurst));
  
  /* Set NORSRAM device control parameters */
  tmpr = (uint32_t)(Init->DataAddressMux       |\
                    Init->MemoryType           |\
                    Init->MemoryDataWidth      |\
                    Init->BurstAccessMode      |\
                    Init->WaitSignalPolarity   |\
                    Init->WrapMode             |\
                    Init->WaitSignalActive     |\
                    Init->WriteOperation       |\
                    Init->WaitSignal           |\
                    Init->ExtendedMode         |\
                    Init->AsynchronousWait     |\
                    Init->WriteBurst
                    );
                    
  if(Init->MemoryType == FSMC_MEMORY_TYPE_NOR)
  {
    tmpr |= (uint32_t)FSMC_NORSRAM_FLASH_ACCESS_ENABLE;
  }
  
  Device->BTCR[Init->NSBank] = tmpr;                   
  
  return HAL_OK;
}


/**
  * @brief  DeInitialize the FSMC_NORSRAM peripheral 
  * @param  Device: Pointer to NORSRAM device instance
  * @param  ExDevice: Pointer to NORSRAM extended mode device instance  
  * @param  Bank: NORSRAM bank number  
  * @retval HAL status
  */
HAL_StatusTypeDef FSMC_NORSRAM_DeInit(FSMC_NORSRAM_TYPEDEF *Device, FSMC_NORSRAM_EXTENDED_TYPEDEF *ExDevice, uint32_t Bank)
{
  /* Check the parameters */
  assert_param(IS_FSMC_NORSRAM_DEVICE(Device));
  assert_param(IS_FSMC_NORSRAM_EXTENDED_DEVICE(ExDevice));

  /* Disable the FSMC_NORSRAM device */
  __FSMC_NORSRAM_DISABLE(Device, Bank);
  
  /* De-initialize the FSMC_NORSRAM device */
  /* FSMC_NORSRAM_BANK1 */
  if(Bank == FSMC_BANK1_NORSRAM1)
  {
    Device->BTCR[Bank] = 0x000030DB;    
  }
  /* FSMC_BANK1_NORSRAM2, FSMC_BANK1_NORSRAM3 or FSMC_BANK1_NORSRAM4 */
  else
  {   
    Device->BTCR[Bank] = 0x000030D2; 
  }
  
  Device->BTCR[Bank + 1] = 0x0FFFFFFF;
  ExDevice->BWTR[Bank]   = 0x0FFFFFFF;
   
  return HAL_OK;
}


/**
  * @brief  Initialize the FSMC_NORSRAM Timing according to the specified
  *         parameters in the FSMC_NORSRAM_TimingTypeDef
  * @param  Device: Pointer to NORSRAM device instance
  * @param  Timing: Pointer to NORSRAM Timing structure
  * @param  Bank: NORSRAM bank number  
  * @retval HAL status
  */
HAL_StatusTypeDef FSMC_NORSRAM_Timing_Init(FSMC_NORSRAM_TYPEDEF *Device, FSMC_NORSRAM_TimingTypeDef *Timing, uint32_t Bank)
{
  uint32_t tmpr = 0;
  
  /* Check the parameters */
  assert_param(IS_FSMC_ADDRESS_SETUP_TIME(Timing->AddressSetupTime));
  assert_param(IS_FSMC_ADDRESS_HOLD_TIME(Timing->AddressHoldTime));
  assert_param(IS_FSMC_DATASETUP_TIME(Timing->DataSetupTime));
  assert_param(IS_FSMC_TURNAROUND_TIME(Timing->BusTurnAroundDuration));
  assert_param(IS_FSMC_CLK_DIV(Timing->CLKDivision));
  assert_param(IS_FSMC_DATA_LATENCY(Timing->DataLatency));
  assert_param(IS_FSMC_ACCESS_MODE(Timing->AccessMode));
  
  /* Set FSMC_NORSRAM device timing parameters */  
  tmpr = (uint32_t)(Timing->AddressSetupTime                                                    |\
                   ((Timing->AddressHoldTime)           << POSITION_VAL(FSMC_BTRx_ADDHLD))      |\
                   ((Timing->DataSetupTime)             << POSITION_VAL(FSMC_BTRx_DATAST))      |\
                   ((Timing->BusTurnAroundDuration)     << POSITION_VAL(FSMC_BTRx_BUSTURN))     |\
                   (((Timing->CLKDivision)-1)           << POSITION_VAL(FSMC_BTRx_CLKDIV))      |\
                   (((Timing->DataLatency)-2)           << POSITION_VAL(FSMC_BTRx_DATLAT))      |\
                    (Timing->AccessMode)
                    );
  
  Device->BTCR[Bank + 1] = tmpr; 
  
  return HAL_OK;   
}

/**
  * @brief  Initialize the FSMC_NORSRAM Extended mode Timing according to the specified
  *         parameters in the FSMC_NORSRAM_TimingTypeDef
  * @param  Device: Pointer to NORSRAM device instance
  * @param  Timing: Pointer to NORSRAM Timing structure
  * @param  Bank: NORSRAM bank number  
  * @param  ExtendedMode: FSMC Extended Mode
  *          This parameter can be one of the following values:
  *            @arg FSMC_EXTENDED_MODE_DISABLE
  *            @arg FSMC_EXTENDED_MODE_ENABLE
  * @retval HAL status
  */
HAL_StatusTypeDef  FSMC_NORSRAM_Extended_Timing_Init(FSMC_NORSRAM_EXTENDED_TYPEDEF *Device, FSMC_NORSRAM_TimingTypeDef *Timing, uint32_t Bank, uint32_t ExtendedMode)
{
  /* Set NORSRAM device timing register for write configuration, if extended mode is used */
  if(ExtendedMode == FSMC_EXTENDED_MODE_ENABLE)
  {
    /* Check the parameters */  
    assert_param(IS_FSMC_ADDRESS_SETUP_TIME(Timing->AddressSetupTime));
    assert_param(IS_FSMC_ADDRESS_HOLD_TIME(Timing->AddressHoldTime));
    assert_param(IS_FSMC_DATASETUP_TIME(Timing->DataSetupTime));
    assert_param(IS_FSMC_TURNAROUND_TIME(Timing->BusTurnAroundDuration));
    assert_param(IS_FSMC_ACCESS_MODE(Timing->AccessMode));
  
    Device->BWTR[Bank] = (uint32_t)(Timing->AddressSetupTime                 |\
                                   ((Timing->AddressHoldTime) << POSITION_VAL(FSMC_BWTRx_ADDHLD))          |\
                                   ((Timing->DataSetupTime) << POSITION_VAL(FSMC_BWTRx_DATAST))            |\
                                   ((Timing->BusTurnAroundDuration) << POSITION_VAL(FSMC_BWTRx_BUSTURN))   |\
                                   (Timing->AccessMode));
  }
  else                                        
  {
    Device->BWTR[Bank] = 0x0FFFFFFF;
  }   
  
  return HAL_OK;  
}


/**
  * @}
  */
  
  
/** @defgroup HAL_FSMC_NORSRAM_Group2 Control functions 
 *  @brief   management functions 
 *
@verbatim   
  ==============================================================================
                      ##### FSMC_NORSRAM Control functions #####
  ==============================================================================
  [..]
    This subsection provides a set of functions allowing to control dynamically
    the FSMC NORSRAM interface.

@endverbatim
  * @{
  */
    
/**
  * @brief  Enables dynamically FSMC_NORSRAM write operation.
  * @param  Device: Pointer to NORSRAM device instance
  * @param  Bank: NORSRAM bank number   
  * @retval HAL status
  */
HAL_StatusTypeDef FSMC_NORSRAM_WriteOperation_Enable(FSMC_NORSRAM_TYPEDEF *Device, uint32_t Bank)
{
  /* Enable write operation */
  Device->BTCR[Bank] |= FSMC_WRITE_OPERATION_ENABLE; 

  return HAL_OK;  
}

/**
  * @brief  Disables dynamically FSMC_NORSRAM write operation.
  * @param  Device: Pointer to NORSRAM device instance
  * @param  Bank: NORSRAM bank number   
  * @retval HAL status
  */
HAL_StatusTypeDef FSMC_NORSRAM_WriteOperation_Disable(FSMC_NORSRAM_TYPEDEF *Device, uint32_t Bank)
{ 
  /* Disable write operation */
  Device->BTCR[Bank] &= ~FSMC_WRITE_OPERATION_ENABLE; 

  return HAL_OK;  
}

/**
  * @}
  */

/**
  * @}
  */
  
#endif /* STM32L151xD || STM32L152xD || STM32L162xD */

#endif /* HAL_FSMC_MODULE_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
