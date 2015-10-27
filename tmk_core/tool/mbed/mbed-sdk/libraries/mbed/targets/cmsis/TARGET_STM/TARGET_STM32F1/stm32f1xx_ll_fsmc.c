/**
  ******************************************************************************
  * @file    stm32f1xx_ll_fsmc.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    15-December-2014
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
         (+) The NAND/PC Card memory controller (except STM32F100xE devices)
       
    [..] The FSMC functional block makes the interface with synchronous and asynchronous static
         memories and 16-bit PC memory cards. Its main purposes are:
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
             (++) 16-bit PC Card compatible devices
             (++) Two banks of NAND Flash memory with ECC hardware to check up to 8 Kbytes of
                data
          (+) Independent Chip Select control for each memory bank
          (+) Independent configuration for each memory bank
        
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
#include "stm32f1xx_hal.h"

/** @addtogroup STM32F1xx_HAL_Driver
  * @{
  */

#if defined (HAL_SRAM_MODULE_ENABLED) || defined(HAL_NOR_MODULE_ENABLED) || defined(HAL_PCCARD_MODULE_ENABLED) || defined(HAL_NAND_MODULE_ENABLED)

#if defined (STM32F101xE) || defined(STM32F103xE) || defined(STM32F101xG) || defined(STM32F103xG) || defined(STM32F100xE)

/** @defgroup FSMC_LL FSMC_LL
  * @brief FSMC driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup FSMC_LL_Private_Constants FSMC Low Layer Private Constants
  * @{
  */

/* ----------------------- FMC registers bit mask --------------------------- */
/* --- PCR Register ---*/
/* PCR register clear mask */ 
#define PCR_CLEAR_MASK    ((uint32_t)(FSMC_PCRx_PWAITEN | FSMC_PCRx_PTYP    | FSMC_PCRx_PWID  | \
                                      FSMC_PCRx_ECCEN   | FSMC_PCRx_TCLR    |                   \
                                      FSMC_PCRx_TAR     | FSMC_PCRx_ECCPS))

/* --- SR Register ---*/
/* SR register clear mask */ 
#define SR_CLEAR_MASK     ((uint32_t)(FSMC_SRx_IRS | FSMC_SRx_ILS | FSMC_SRx_IFS | \
                                      FSMC_SRx_IREN | FSMC_SRx_ILEN | FSMC_SRx_IFEN))

/* --- PMEM Register ---*/
/* PMEM register clear mask */ 
#define PMEM_CLEAR_MASK   ((uint32_t)(FSMC_PMEMx_MEMSETx  | FSMC_PMEMx_MEMWAITx |\
                                      FSMC_PMEMx_MEMHOLDx | FSMC_PMEMx_MEMHIZx))

/* --- PATT Register ---*/
/* PATT register clear mask */ 
#define PATT_CLEAR_MASK   ((uint32_t)(FSMC_PATTx_ATTSETx  | FSMC_PATTx_ATTWAITx |\
                                      FSMC_PATTx_ATTHOLDx | FSMC_PATTx_ATTHIZx))

/* --- PIO4 Register ---*/
/* PIO4 register clear mask */ 
#define PIO4_CLEAR_MASK   ((uint32_t)(FSMC_PIO4_IOSET4    | FSMC_PIO4_IOWAIT4   | \
                                      FSMC_PIO4_IOHOLD4   | FSMC_PIO4_IOHIZ4))
/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/    
/** @defgroup FSMC_LL_Private_Macros FSMC Low Layer Private Macros
  * @{
  */

/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup FSMC_LL_Exported_Functions FSMC Low Layer Exported Functions
  * @{
  */

/** @defgroup FSMC_NORSRAM FSMC NORSRAM Controller functions
  * @brief    NORSRAM Controller functions 
  *
  @verbatim 
  ==============================================================================   
                   ##### How to use NORSRAM device driver #####
  ==============================================================================
 
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
  * @{
  */

/** @defgroup FSMC_NORSRAM_Group1 Initialization/de-initialization functions 
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
HAL_StatusTypeDef  FSMC_NORSRAM_Init(FSMC_NORSRAM_TypeDef *Device, FSMC_NORSRAM_InitTypeDef* Init)
{ 
  /* Check the parameters */
  assert_param(IS_FSMC_NORSRAM_DEVICE(Device));
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
  
  /* Disable NORSRAM Device */
  __FSMC_NORSRAM_DISABLE(Device, Init->NSBank);  
  
  /* Set NORSRAM device control parameters */
  if(Init->MemoryType == FSMC_MEMORY_TYPE_NOR)
  {
    MODIFY_REG(Device->BTCR[Init->NSBank], \
      (FSMC_BCRx_FACCEN                 | FSMC_BCRx_MUXEN       | FSMC_BCRx_MTYP                                        | \
      FSMC_BCRx_MWID        | FSMC_BCRx_BURSTEN     | FSMC_BCRx_WAITPOL         | FSMC_BCRx_WRAPMOD | FSMC_BCRx_WAITCFG | \
      FSMC_BCRx_WREN        | FSMC_BCRx_WAITEN  | FSMC_BCRx_EXTMOD    | FSMC_BCRx_ASYNCWAIT     | FSMC_BCRx_CBURSTRW),    \
      (FSMC_NORSRAM_FLASH_ACCESS_ENABLE | Init->DataAddressMux  | Init->MemoryType                                      | \
      Init->MemoryDataWidth | Init->BurstAccessMode | Init->WaitSignalPolarity  | Init->WrapMode    | Init->WaitSignalActive |\
      Init->WriteOperation  | Init->WaitSignal  | Init->ExtendedMode  | Init->AsynchronousWait  | Init->WriteBurst )      \
      );
  }
  else
  {
    MODIFY_REG(Device->BTCR[Init->NSBank], \
      (FSMC_BCRx_FACCEN                  | FSMC_BCRx_MUXEN      | FSMC_BCRx_MTYP                                        | \
      FSMC_BCRx_MWID        | FSMC_BCRx_BURSTEN     | FSMC_BCRx_WAITPOL         | FSMC_BCRx_WRAPMOD | FSMC_BCRx_WAITCFG | \
      FSMC_BCRx_WREN        | FSMC_BCRx_WAITEN  | FSMC_BCRx_EXTMOD    | FSMC_BCRx_ASYNCWAIT     | FSMC_BCRx_CBURSTRW),    \
      (FSMC_NORSRAM_FLASH_ACCESS_DISABLE | Init->DataAddressMux | Init->MemoryType                                      | \
      Init->MemoryDataWidth | Init->BurstAccessMode | Init->WaitSignalPolarity  | Init->WrapMode    | Init->WaitSignalActive |\
      Init->WriteOperation  | Init->WaitSignal  | Init->ExtendedMode  | Init->AsynchronousWait  | Init->WriteBurst )      \
      );
  }
  
  return HAL_OK;
}


/**
  * @brief  DeInitialize the FSMC_NORSRAM peripheral 
  * @param  Device: Pointer to NORSRAM device instance
  * @param  ExDevice: Pointer to NORSRAM extended mode device instance  
  * @param  Bank: NORSRAM bank number  
  * @retval HAL status
  */
HAL_StatusTypeDef FSMC_NORSRAM_DeInit(FSMC_NORSRAM_TypeDef *Device, FSMC_NORSRAM_EXTENDED_TypeDef *ExDevice, uint32_t Bank)
{
  /* Check the parameters */
  assert_param(IS_FSMC_NORSRAM_DEVICE(Device));
  assert_param(IS_FSMC_NORSRAM_EXTENDED_DEVICE(ExDevice));
  assert_param(IS_FSMC_NORSRAM_BANK(Bank));

  /* Disable the FSMC_NORSRAM device */
  __FSMC_NORSRAM_DISABLE(Device, Bank);
  
  /* De-initialize the FSMC_NORSRAM device */
  /* FSMC_NORSRAM_BANK1 */
  if(Bank == FSMC_NORSRAM_BANK1)
  {
    Device->BTCR[Bank] = 0x000030DB;    
  }
  /* FSMC_NORSRAM_BANK2, FSMC_NORSRAM_BANK3 or FSMC_NORSRAM_BANK4 */
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
HAL_StatusTypeDef FSMC_NORSRAM_Timing_Init(FSMC_NORSRAM_TypeDef *Device, FSMC_NORSRAM_TimingTypeDef *Timing, uint32_t Bank)
{
  /* Check the parameters */
  assert_param(IS_FSMC_NORSRAM_DEVICE(Device));
  assert_param(IS_FSMC_ADDRESS_SETUP_TIME(Timing->AddressSetupTime));
  assert_param(IS_FSMC_ADDRESS_HOLD_TIME(Timing->AddressHoldTime));
  assert_param(IS_FSMC_DATASETUP_TIME(Timing->DataSetupTime));
  assert_param(IS_FSMC_TURNAROUND_TIME(Timing->BusTurnAroundDuration));
  assert_param(IS_FSMC_CLK_DIV(Timing->CLKDivision));
  assert_param(IS_FSMC_DATA_LATENCY(Timing->DataLatency));
  assert_param(IS_FSMC_ACCESS_MODE(Timing->AccessMode));
  assert_param(IS_FSMC_NORSRAM_BANK(Bank));
  
  /* Set FSMC_NORSRAM device timing parameters */  
  MODIFY_REG(Device->BTCR[Bank + 1],                                              \
    (FSMC_BTRx_ADDSET | FSMC_BTRx_ADDHLD | FSMC_BTRx_DATAST | FSMC_BTRx_BUSTURN | \
    FSMC_BTRx_CLKDIV | FSMC_BTRx_DATLAT | FSMC_BTRx_ACCMOD),                      \
    ( Timing->AddressSetupTime                                                  | \
    ((Timing->AddressHoldTime)        << POSITION_VAL(FSMC_BTRx_ADDHLD))        | \
    ((Timing->DataSetupTime)          << POSITION_VAL(FSMC_BTRx_DATAST))        | \
    ((Timing->BusTurnAroundDuration)  << POSITION_VAL(FSMC_BTRx_BUSTURN))       | \
    (((Timing->CLKDivision)-1)        << POSITION_VAL(FSMC_BTRx_CLKDIV))        | \
    (((Timing->DataLatency)-2)        << POSITION_VAL(FSMC_BTRx_DATLAT))        | \
    (Timing->AccessMode)));

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
HAL_StatusTypeDef  FSMC_NORSRAM_Extended_Timing_Init(FSMC_NORSRAM_EXTENDED_TypeDef *Device, FSMC_NORSRAM_TimingTypeDef *Timing, uint32_t Bank, uint32_t ExtendedMode)
{
  /* Check the parameters */
  assert_param(IS_FSMC_EXTENDED_MODE(ExtendedMode));
  
  /* Set NORSRAM device timing register for write configuration, if extended mode is used */
  if(ExtendedMode == FSMC_EXTENDED_MODE_ENABLE)
  {
    /* Check the parameters */  
    assert_param(IS_FSMC_NORSRAM_EXTENDED_DEVICE(Device));  
    assert_param(IS_FSMC_ADDRESS_SETUP_TIME(Timing->AddressSetupTime));
    assert_param(IS_FSMC_ADDRESS_HOLD_TIME(Timing->AddressHoldTime));
    assert_param(IS_FSMC_DATASETUP_TIME(Timing->DataSetupTime));
#if defined (STM32F101xE) || defined(STM32F103xE) || defined(STM32F101xG) || defined(STM32F103xG)
    assert_param(IS_FSMC_TURNAROUND_TIME(Timing->BusTurnAroundDuration));
#else
    assert_param(IS_FSMC_CLK_DIV(Timing->CLKDivision));
    assert_param(IS_FSMC_DATA_LATENCY(Timing->DataLatency));
#endif /* STM32F101xE || STM32F103xE || STM32F101xG || STM32F103xG */
    assert_param(IS_FSMC_ACCESS_MODE(Timing->AccessMode));
    assert_param(IS_FSMC_NORSRAM_BANK(Bank));  
  
#if defined (STM32F101xE) || defined(STM32F103xE) || defined(STM32F101xG) || defined(STM32F103xG)
    MODIFY_REG(Device->BWTR[Bank],                                                \
      (FSMC_BWTRx_ADDSET | FSMC_BWTRx_ADDHLD | FSMC_BWTRx_DATAST | FSMC_BWTRx_ACCMOD | FSMC_BWTRx_BUSTURN), \
      (Timing->AddressSetupTime                                                 | \
      ((Timing->AddressHoldTime)        << POSITION_VAL(FSMC_BWTRx_ADDHLD))     | \
      ((Timing->DataSetupTime)          << POSITION_VAL(FSMC_BWTRx_DATAST))     | \
      Timing->AccessMode                                                        | \
      ((Timing->BusTurnAroundDuration)  << POSITION_VAL(FSMC_BWTRx_BUSTURN))));
#else
    MODIFY_REG(Device->BWTR[Bank],                                                \
      (FSMC_BWTRx_ADDSET | FSMC_BWTRx_ADDHLD | FSMC_BWTRx_DATAST | FSMC_BWTRx_ACCMOD | FSMC_BWTRx_CLKDIV | FSMC_BWTRx_DATLAT), \
      (Timing->AddressSetupTime                 | \
      ((Timing->AddressHoldTime)  << POSITION_VAL(FSMC_BWTRx_ADDHLD))           | \
      ((Timing->DataSetupTime)    << POSITION_VAL(FSMC_BWTRx_DATAST))           | \
      Timing->AccessMode                                                        | \
      (((Timing->CLKDivision)-1)  << POSITION_VAL(FSMC_BTRx_CLKDIV))            | \
      (((Timing->DataLatency)-2)  << POSITION_VAL(FSMC_BWTRx_DATLAT))));
#endif /* STM32F101xE || STM32F103xE || STM32F101xG || STM32F103xG */
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
  
  
/** @defgroup FSMC_NORSRAM_Group2 Control functions 
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
HAL_StatusTypeDef FSMC_NORSRAM_WriteOperation_Enable(FSMC_NORSRAM_TypeDef *Device, uint32_t Bank)
{
  /* Check the parameters */
  assert_param(IS_FSMC_NORSRAM_DEVICE(Device));
  assert_param(IS_FSMC_NORSRAM_BANK(Bank));
  
  /* Enable write operation */
  SET_BIT(Device->BTCR[Bank], FSMC_WRITE_OPERATION_ENABLE); 

  return HAL_OK;  
}

/**
  * @brief  Disables dynamically FSMC_NORSRAM write operation.
  * @param  Device: Pointer to NORSRAM device instance
  * @param  Bank: NORSRAM bank number   
  * @retval HAL status
  */
HAL_StatusTypeDef FSMC_NORSRAM_WriteOperation_Disable(FSMC_NORSRAM_TypeDef *Device, uint32_t Bank)
{ 
  /* Check the parameters */
  assert_param(IS_FSMC_NORSRAM_DEVICE(Device));
  assert_param(IS_FSMC_NORSRAM_BANK(Bank));
    
  /* Disable write operation */
  CLEAR_BIT(Device->BTCR[Bank], FSMC_WRITE_OPERATION_ENABLE); 

  return HAL_OK;  
}

/**
  * @}
  */

/**
  * @}
  */
#if defined (STM32F101xE) || defined(STM32F103xE) || defined(STM32F101xG) || defined(STM32F103xG)
/** @defgroup FSMC_NAND FSMC NAND Controller functions
  * @brief    NAND Controller functions 
  *
  @verbatim 
  ==============================================================================
                    ##### How to use NAND device driver #####
  ==============================================================================
  [..]
    This driver contains a set of APIs to interface with the FSMC NAND banks in order
    to run the NAND external devices.
  
    (+) FSMC NAND bank reset using the function FSMC_NAND_DeInit() 
    (+) FSMC NAND bank control configuration using the function FSMC_NAND_Init()
    (+) FSMC NAND bank common space timing configuration using the function 
        FSMC_NAND_CommonSpace_Timing_Init()
    (+) FSMC NAND bank attribute space timing configuration using the function 
        FSMC_NAND_AttributeSpace_Timing_Init()
    (+) FSMC NAND bank enable/disable ECC correction feature using the functions
        FSMC_NAND_ECC_Enable()/FSMC_NAND_ECC_Disable()
    (+) FSMC NAND bank get ECC correction code using the function FSMC_NAND_GetECC()    

@endverbatim
  * @{
  */
    
/** @defgroup FSMC_NAND_Exported_Functions_Group1 Initialization and de-initialization functions
 *  @brief    Initialization and Configuration functions 
 *
@verbatim    
  ==============================================================================
              ##### Initialization and de_initialization functions #####
  ==============================================================================
  [..]  
    This section provides functions allowing to:
    (+) Initialize and configure the FSMC NAND interface
    (+) De-initialize the FSMC NAND interface 
    (+) Configure the FSMC clock and associated GPIOs
        
@endverbatim
  * @{
  */
  
/**
  * @brief  Initializes the FSMC_NAND device according to the specified
  *         control parameters in the FSMC_NAND_HandleTypeDef
  * @param  Device: Pointer to NAND device instance
  * @param  Init: Pointer to NAND Initialization structure
  * @retval HAL status
  */
HAL_StatusTypeDef FSMC_NAND_Init(FSMC_NAND_TypeDef *Device, FSMC_NAND_InitTypeDef *Init)
{
  /* Check the parameters */
  assert_param(IS_FSMC_NAND_DEVICE(Device));
  assert_param(IS_FSMC_NAND_BANK(Init->NandBank));
  assert_param(IS_FSMC_WAIT_FEATURE(Init->Waitfeature));
  assert_param(IS_FSMC_NAND_MEMORY_WIDTH(Init->MemoryDataWidth));
  assert_param(IS_FSMC_ECC_STATE(Init->EccComputation));
  assert_param(IS_FSMC_ECCPAGE_SIZE(Init->ECCPageSize));
  assert_param(IS_FSMC_TCLR_TIME(Init->TCLRSetupTime));
  assert_param(IS_FSMC_TAR_TIME(Init->TARSetupTime));   

  if(Init->NandBank == FSMC_NAND_BANK2)
  {
    /* NAND bank 2 registers configuration */
    MODIFY_REG(Device->PCR2, PCR_CLEAR_MASK, (Init->Waitfeature                  |\
                   FSMC_PCR_MEMORY_TYPE_NAND                                     |\
                   Init->MemoryDataWidth                                         |\
                   Init->EccComputation                                          |\
                   Init->ECCPageSize                                             |\
                   ((Init->TCLRSetupTime) << POSITION_VAL(FSMC_PCRx_TCLR))       |\
                   ((Init->TARSetupTime) << POSITION_VAL(FSMC_PCRx_TAR))));  
  }
  else
  {
    /* NAND bank 3 registers configuration */
    MODIFY_REG(Device->PCR3, PCR_CLEAR_MASK, (Init->Waitfeature                  |\
                   FSMC_PCR_MEMORY_TYPE_NAND                                     |\
                   Init->MemoryDataWidth                                         |\
                   Init->EccComputation                                          |\
                   Init->ECCPageSize                                             |\
                   ((Init->TCLRSetupTime) << POSITION_VAL(FSMC_PCRx_TCLR))       |\
                   ((Init->TARSetupTime) << POSITION_VAL(FSMC_PCRx_TAR))));  
  }
  
  return HAL_OK;

}

/**
  * @brief  Initializes the FSMC_NAND Common space Timing according to the specified
  *         parameters in the FSMC_NAND_PCC_TimingTypeDef
  * @param  Device: Pointer to NAND device instance
  * @param  Timing: Pointer to NAND timing structure
  * @param  Bank: NAND bank number   
  * @retval HAL status
  */
HAL_StatusTypeDef FSMC_NAND_CommonSpace_Timing_Init(FSMC_NAND_TypeDef *Device, FSMC_NAND_PCC_TimingTypeDef *Timing, uint32_t Bank)
{
  /* Check the parameters */
  assert_param(IS_FSMC_NAND_DEVICE(Device));
  assert_param(IS_FSMC_SETUP_TIME(Timing->SetupTime));
  assert_param(IS_FSMC_WAIT_TIME(Timing->WaitSetupTime));
  assert_param(IS_FSMC_HOLD_TIME(Timing->HoldSetupTime));
  assert_param(IS_FSMC_HIZ_TIME(Timing->HiZSetupTime));
  assert_param(IS_FSMC_NAND_BANK(Bank));
  
  if(Bank == FSMC_NAND_BANK2)
  {
    /* NAND bank 2 registers configuration */
    MODIFY_REG(Device->PMEM2, PMEM_CLEAR_MASK, (Timing->SetupTime                      |\
                   ((Timing->WaitSetupTime) << POSITION_VAL(FSMC_PMEMx_MEMWAITx))      |\
                   ((Timing->HoldSetupTime) << POSITION_VAL(FSMC_PMEMx_MEMHOLDx))      |\
                   ((Timing->HiZSetupTime) << POSITION_VAL(FSMC_PMEMx_MEMHIZx))));

  }
  else
  {
    /* NAND bank 3 registers configuration */
    MODIFY_REG(Device->PMEM3, PMEM_CLEAR_MASK, (Timing->SetupTime                      |\
                   ((Timing->WaitSetupTime) << POSITION_VAL(FSMC_PMEMx_MEMWAITx))      |\
                   ((Timing->HoldSetupTime) << POSITION_VAL(FSMC_PMEMx_MEMHOLDx))      |\
                   ((Timing->HiZSetupTime) << POSITION_VAL(FSMC_PMEMx_MEMHIZx))));
  }  
  
  return HAL_OK;  
}

/**
  * @brief  Initializes the FSMC_NAND Attribute space Timing according to the specified
  *         parameters in the FSMC_NAND_PCC_TimingTypeDef
  * @param  Device: Pointer to NAND device instance
  * @param  Timing: Pointer to NAND timing structure
  * @param  Bank: NAND bank number 
  * @retval HAL status
  */
HAL_StatusTypeDef FSMC_NAND_AttributeSpace_Timing_Init(FSMC_NAND_TypeDef *Device, FSMC_NAND_PCC_TimingTypeDef *Timing, uint32_t Bank)
{
  /* Check the parameters */ 
  assert_param(IS_FSMC_NAND_DEVICE(Device)); 
  assert_param(IS_FSMC_SETUP_TIME(Timing->SetupTime));
  assert_param(IS_FSMC_WAIT_TIME(Timing->WaitSetupTime));
  assert_param(IS_FSMC_HOLD_TIME(Timing->HoldSetupTime));
  assert_param(IS_FSMC_HIZ_TIME(Timing->HiZSetupTime));
  assert_param(IS_FSMC_NAND_BANK(Bank));
  
  if(Bank == FSMC_NAND_BANK2)
  {
    /* NAND bank 2 registers configuration */
    MODIFY_REG(Device->PATT2, PATT_CLEAR_MASK, (Timing->SetupTime                       |\
                   ((Timing->WaitSetupTime) << POSITION_VAL(FSMC_PATTx_ATTWAITx))       |\
                   ((Timing->HoldSetupTime) << POSITION_VAL(FSMC_PATTx_ATTHOLDx))       |\
                   ((Timing->HiZSetupTime) << POSITION_VAL(FSMC_PATTx_ATTHIZx))));
  }
  else
  {
    /* NAND bank 3 registers configuration */
    MODIFY_REG(Device->PATT3, PATT_CLEAR_MASK, (Timing->SetupTime                       |\
                   ((Timing->WaitSetupTime) << POSITION_VAL(FSMC_PATTx_ATTWAITx))       |\
                   ((Timing->HoldSetupTime) << POSITION_VAL(FSMC_PATTx_ATTHOLDx))       |\
                   ((Timing->HiZSetupTime) << POSITION_VAL(FSMC_PATTx_ATTHIZx))));
  }   
  
  return HAL_OK;
}


/**
  * @brief  DeInitializes the FSMC_NAND device 
  * @param  Device: Pointer to NAND device instance
  * @param  Bank: NAND bank number
  * @retval HAL status
  */
HAL_StatusTypeDef FSMC_NAND_DeInit(FSMC_NAND_TypeDef *Device, uint32_t Bank)
{
  /* Check the parameters */ 
  assert_param(IS_FSMC_NAND_DEVICE(Device)); 
  assert_param(IS_FSMC_NAND_BANK(Bank));
      
  /* Disable the NAND Bank */
  __FSMC_NAND_DISABLE(Device, Bank);
 
  /* De-initialize the NAND Bank */
  if(Bank == FSMC_NAND_BANK2)
  {
    /* Set the FSMC_NAND_BANK2 registers to their reset values */
    WRITE_REG(Device->PCR2,  0x00000018);
    WRITE_REG(Device->SR2,   0x00000040);
    WRITE_REG(Device->PMEM2, 0xFCFCFCFC);
    WRITE_REG(Device->PATT2, 0xFCFCFCFC);
  }
  /* FSMC_Bank3_NAND */  
  else
  {
    /* Set the FSMC_NAND_BANK3 registers to their reset values */
    WRITE_REG(Device->PCR3,  0x00000018);
    WRITE_REG(Device->SR3,   0x00000040);
    WRITE_REG(Device->PMEM3, 0xFCFCFCFC);
    WRITE_REG(Device->PATT3, 0xFCFCFCFC);
  }
  
  return HAL_OK;
}

/**
  * @}
  */
  
  
/** @defgroup FSMC_NAND_Exported_Functions_Group2 Peripheral Control functions 
 *  @brief   management functions 
 *
@verbatim   
  ==============================================================================
                       ##### FSMC_NAND Control functions #####
  ==============================================================================  
  [..]
    This subsection provides a set of functions allowing to control dynamically
    the FSMC NAND interface.

@endverbatim
  * @{
  */ 

    
/**
  * @brief  Enables dynamically FSMC_NAND ECC feature.
  * @param  Device: Pointer to NAND device instance
  * @param  Bank: NAND bank number
  * @retval HAL status
  */    
HAL_StatusTypeDef FSMC_NAND_ECC_Enable(FSMC_NAND_TypeDef *Device, uint32_t Bank)
{
  /* Check the parameters */ 
  assert_param(IS_FSMC_NAND_DEVICE(Device)); 
  assert_param(IS_FSMC_NAND_BANK(Bank));
    
  /* Enable ECC feature */
  if(Bank == FSMC_NAND_BANK2)
  {
    SET_BIT(Device->PCR2, FSMC_PCRx_ECCEN);
  }
  else
  {
    SET_BIT(Device->PCR3, FSMC_PCRx_ECCEN);
  } 
  
  return HAL_OK;  
}


/**
  * @brief  Disables dynamically FSMC_NAND ECC feature.
  * @param  Device: Pointer to NAND device instance
  * @param  Bank: NAND bank number
  * @retval HAL status
  */  
HAL_StatusTypeDef FSMC_NAND_ECC_Disable(FSMC_NAND_TypeDef *Device, uint32_t Bank)  
{  
  /* Check the parameters */ 
  assert_param(IS_FSMC_NAND_DEVICE(Device)); 
  assert_param(IS_FSMC_NAND_BANK(Bank));
    
  /* Disable ECC feature */
  if(Bank == FSMC_NAND_BANK2)
  {
    CLEAR_BIT(Device->PCR2, FSMC_PCRx_ECCEN);
  }
  else
  {
    CLEAR_BIT(Device->PCR3, FSMC_PCRx_ECCEN);
  } 

  return HAL_OK;  
}

/**
  * @brief  Disables dynamically FSMC_NAND ECC feature.
  * @param  Device: Pointer to NAND device instance
  * @param  ECCval: Pointer to ECC value
  * @param  Bank: NAND bank number
  * @param  Timeout: Timeout wait value  
  * @retval HAL status
  */
HAL_StatusTypeDef FSMC_NAND_GetECC(FSMC_NAND_TypeDef *Device, uint32_t *ECCval, uint32_t Bank, uint32_t Timeout)
{
  uint32_t tickstart = 0;

  /* Check the parameters */ 
  assert_param(IS_FSMC_NAND_DEVICE(Device)); 
  assert_param(IS_FSMC_NAND_BANK(Bank));
      
  /* Get tick */ 
  tickstart = HAL_GetTick();
  
  /* Wait untill FIFO is empty */
  while(__FSMC_NAND_GET_FLAG(Device, Bank, FSMC_FLAG_FEMPT) == RESET)
  {
    /* Check for the Timeout */
    if(Timeout != HAL_MAX_DELAY)
    {
      if((Timeout == 0)||((HAL_GetTick() - tickstart ) > Timeout))
      {
        return HAL_TIMEOUT;
      }
    }  
  }
     
  if(Bank == FSMC_NAND_BANK2)
  {    
    /* Get the ECCR2 register value */
    *ECCval = (uint32_t)Device->ECCR2;
  }
  else
  {    
    /* Get the ECCR3 register value */
    *ECCval = (uint32_t)Device->ECCR3;
  }

  return HAL_OK;  
}

/**
  * @}
  */
  
/**
  * @}
  */
    
/** @defgroup FSMC_PCCARD FSMC PCCARD Controller functions
  * @brief    PCCARD Controller functions 
  *
  @verbatim 
  ==============================================================================  
                    ##### How to use PCCARD device driver #####
  ==============================================================================
  [..]
    This driver contains a set of APIs to interface with the FSMC PCCARD bank in order
    to run the PCCARD/compact flash external devices.
  
    (+) FSMC PCCARD bank reset using the function FSMC_PCCARD_DeInit() 
    (+) FSMC PCCARD bank control configuration using the function FSMC_PCCARD_Init()
    (+) FSMC PCCARD bank common space timing configuration using the function 
        FSMC_PCCARD_CommonSpace_Timing_Init()
    (+) FSMC PCCARD bank attribute space timing configuration using the function 
        FSMC_PCCARD_AttributeSpace_Timing_Init()
    (+) FSMC PCCARD bank IO space timing configuration using the function 
        FSMC_PCCARD_IOSpace_Timing_Init()

       
@endverbatim
  * @{
  */
  
/** @defgroup FSMC_PCCARD_Exported_Functions_Group1 Initialization and de-initialization functions
 *  @brief    Initialization and Configuration functions 
 *
@verbatim    
  ==============================================================================
              ##### Initialization and de_initialization functions #####
  ==============================================================================
  [..]  
    This section provides functions allowing to:
    (+) Initialize and configure the FSMC PCCARD interface
    (+) De-initialize the FSMC PCCARD interface 
    (+) Configure the FSMC clock and associated GPIOs
        
@endverbatim
  * @{
  */
  
/**
  * @brief  Initializes the FSMC_PCCARD device according to the specified
  *         control parameters in the FSMC_PCCARD_HandleTypeDef
  * @param  Device: Pointer to PCCARD device instance
  * @param  Init: Pointer to PCCARD Initialization structure   
  * @retval HAL status
  */
HAL_StatusTypeDef FSMC_PCCARD_Init(FSMC_PCCARD_TypeDef *Device, FSMC_PCCARD_InitTypeDef *Init)
{
  /* Check the parameters */ 
  assert_param(IS_FSMC_PCCARD_DEVICE(Device));
  assert_param(IS_FSMC_WAIT_FEATURE(Init->Waitfeature));
  assert_param(IS_FSMC_TCLR_TIME(Init->TCLRSetupTime));
  assert_param(IS_FSMC_TAR_TIME(Init->TARSetupTime));     
  
  /* Set FSMC_PCCARD device control parameters */
  MODIFY_REG(Device->PCR4,                                  \
    (FSMC_PCRx_PTYP | FSMC_PCRx_PWAITEN |  FSMC_PCRx_PWID  | FSMC_PCRx_TCLR | FSMC_PCRx_TAR), \
    (FSMC_PCR_MEMORY_TYPE_PCCARD                          | \
    Init->Waitfeature                                     | \
    FSMC_NAND_PCC_MEM_BUS_WIDTH_16                        | \
    (Init->TCLRSetupTime << POSITION_VAL(FSMC_PCRx_TCLR)) | \
    (Init->TARSetupTime << POSITION_VAL(FSMC_PCRx_TAR))));
  
  return HAL_OK;

}

/**
  * @brief  Initializes the FSMC_PCCARD Common space Timing according to the specified
  *         parameters in the FSMC_NAND_PCC_TimingTypeDef
  * @param  Device: Pointer to PCCARD device instance
  * @param  Timing: Pointer to PCCARD timing structure 
  * @retval HAL status
  */
HAL_StatusTypeDef FSMC_PCCARD_CommonSpace_Timing_Init(FSMC_PCCARD_TypeDef *Device, FSMC_NAND_PCC_TimingTypeDef *Timing)
{
  /* Check the parameters */
  assert_param(IS_FSMC_PCCARD_DEVICE(Device));
  assert_param(IS_FSMC_SETUP_TIME(Timing->SetupTime));
  assert_param(IS_FSMC_WAIT_TIME(Timing->WaitSetupTime));
  assert_param(IS_FSMC_HOLD_TIME(Timing->HoldSetupTime));
  assert_param(IS_FSMC_HIZ_TIME(Timing->HiZSetupTime));

  /* Set PCCARD timing parameters */
  MODIFY_REG(Device->PMEM4, PMEM_CLEAR_MASK,                            \
      (Timing->SetupTime                                              | \
      ((Timing->WaitSetupTime) << POSITION_VAL(FSMC_PMEMx_MEMWAITx))  | \
      ((Timing->HoldSetupTime) << POSITION_VAL(FSMC_PMEMx_MEMHOLDx))  | \
      ((Timing->HiZSetupTime) << POSITION_VAL(FSMC_PMEMx_MEMHIZx)))); 

  return HAL_OK;  
}

/**
  * @brief  Initializes the FSMC_PCCARD Attribute space Timing according to the specified
  *         parameters in the FSMC_NAND_PCC_TimingTypeDef
  * @param  Device: Pointer to PCCARD device instance
  * @param  Timing: Pointer to PCCARD timing structure  
  * @retval HAL status
  */
HAL_StatusTypeDef FSMC_PCCARD_AttributeSpace_Timing_Init(FSMC_PCCARD_TypeDef *Device, FSMC_NAND_PCC_TimingTypeDef *Timing)
{
  /* Check the parameters */ 
  assert_param(IS_FSMC_PCCARD_DEVICE(Device)); 
  assert_param(IS_FSMC_SETUP_TIME(Timing->SetupTime));
  assert_param(IS_FSMC_WAIT_TIME(Timing->WaitSetupTime));
  assert_param(IS_FSMC_HOLD_TIME(Timing->HoldSetupTime));
  assert_param(IS_FSMC_HIZ_TIME(Timing->HiZSetupTime));

  /* Set PCCARD timing parameters */
  MODIFY_REG(Device->PATT4, PATT_CLEAR_MASK,                          \
    (Timing->SetupTime                                              | \
    ((Timing->WaitSetupTime) << POSITION_VAL(FSMC_PATTx_ATTWAITx))  | \
    ((Timing->HoldSetupTime) << POSITION_VAL(FSMC_PATTx_ATTHOLDx))   | \
    ((Timing->HiZSetupTime) << POSITION_VAL(FSMC_PATTx_ATTHIZx))));

  return HAL_OK;
}

/**
  * @brief  Initializes the FSMC_PCCARD IO space Timing according to the specified
  *         parameters in the FSMC_NAND_PCC_TimingTypeDef
  * @param  Device: Pointer to PCCARD device instance
  * @param  Timing: Pointer to PCCARD timing structure  
  * @retval HAL status
  */
HAL_StatusTypeDef FSMC_PCCARD_IOSpace_Timing_Init(FSMC_PCCARD_TypeDef *Device, FSMC_NAND_PCC_TimingTypeDef *Timing)
{
  /* Check the parameters */  
  assert_param(IS_FSMC_PCCARD_DEVICE(Device));
  assert_param(IS_FSMC_SETUP_TIME(Timing->SetupTime));
  assert_param(IS_FSMC_WAIT_TIME(Timing->WaitSetupTime));
  assert_param(IS_FSMC_HOLD_TIME(Timing->HoldSetupTime));
  assert_param(IS_FSMC_HIZ_TIME(Timing->HiZSetupTime));

  /* Set FSMC_PCCARD device timing parameters */
  MODIFY_REG(Device->PIO4, PIO4_CLEAR_MASK,                         \
    (Timing->SetupTime                                            | \
    (Timing->WaitSetupTime   << POSITION_VAL(FSMC_PIO4_IOWAIT4)) | \
    (Timing->HoldSetupTime   << POSITION_VAL(FSMC_PIO4_IOHOLD4)) | \
    (Timing->HiZSetupTime    << POSITION_VAL(FSMC_PIO4_IOHIZ4))));
  
  return HAL_OK;
}
                                           
/**
  * @brief  DeInitializes the FSMC_PCCARD device 
  * @param  Device: Pointer to PCCARD device instance
  * @retval HAL status
  */
HAL_StatusTypeDef FSMC_PCCARD_DeInit(FSMC_PCCARD_TypeDef *Device)
{
  /* Check the parameters */  
  assert_param(IS_FSMC_PCCARD_DEVICE(Device));
    
  /* Disable the FSMC_PCCARD device */
  __FSMC_PCCARD_DISABLE(Device);
  
  /* De-initialize the FSMC_PCCARD device */
  WRITE_REG(Device->PCR4,  0x00000018);
  WRITE_REG(Device->SR4,   0x00000040);
  WRITE_REG(Device->PMEM4, 0xFCFCFCFC);
  WRITE_REG(Device->PATT4, 0xFCFCFCFC);
  WRITE_REG(Device->PIO4,  0xFCFCFCFC);
  
  return HAL_OK;
}

/**
  * @}
  */
  
/**
  * @}
  */

#endif /* STM32F101xE || STM32F103xE || STM32F101xG || STM32F103xG */

/**
  * @}
  */

/**
  * @}
  */

#endif /* STM32F101xE || STM32F103xE || STM32F101xG || STM32F103xG || STM32F100xE */

#endif /* HAL_SRAM_MODULE_ENABLED || HAL_NOR_MODULE_ENABLED || HAL_PCCARD_MODULE_ENABLED || HAL_NAND_MODULE_ENABLED */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
