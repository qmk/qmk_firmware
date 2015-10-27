/**
  ******************************************************************************
  * @file    stm32f1xx_hal_pccard.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    15-December-2014
  * @brief   PCCARD HAL module driver.
  *          This file provides a generic firmware to drive PCCARD memories mounted 
  *          as external device.
  *         
  @verbatim
 ===============================================================================
                        ##### How to use this driver #####
 ===============================================================================  
   [..]
     This driver is a generic layered driver which contains a set of APIs used to 
     control PCCARD/compact flash memories. It uses the FSMC/FSMC layer functions 
     to interface with PCCARD devices. This driver is used for:
    
    (+) PCCARD/compact flash memory configuration sequence using the function 
        HAL_PCCARD_Init() with control and timing parameters for both common and 
        attribute spaces.
            
    (+) Read PCCARD/compact flash memory maker and device IDs using the function
        HAL_PCCARD_Read_ID(). The read information is stored in the CompactFlash_ID 
        structure declared by the function caller. 
        
    (+) Access PCCARD/compact flash memory by read/write operations using the functions
        HAL_PCCARD_Read_Sector()/HAL_PCCARD_Write_Sector(), to read/write sector. 
        
    (+) Perform PCCARD/compact flash Reset chip operation using the function HAL_PCCARD_Reset().
        
    (+) Perform PCCARD/compact flash erase sector operation using the function 
        HAL_PCCARD_Erase_Sector().
    
    (+) Read the PCCARD/compact flash status operation using the function HAL_PCCARD_ReadStatus().
     
    (+) You can monitor the PCCARD/compact flash  device HAL state by calling the function
        HAL_PCCARD_GetState()     
        
   [..]
     (@) This driver is a set of generic APIs which handle standard PCCARD/compact flash 
         operations. If a PCCARD/compact flash device contains different operations 
         and/or implementations, it should be implemented separately.
   
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

#ifdef HAL_PCCARD_MODULE_ENABLED
#if defined (STM32F101xE) || defined(STM32F103xE) || defined(STM32F101xG) || defined(STM32F103xG)

/** @defgroup PCCARD PCCARD
  * @brief PCCARD HAL module driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup PCCARD_Private_Constants PCCARD Private Constants
  * @{
  */

#define PCCARD_TIMEOUT_READ_ID      (uint32_t)0x0000FFFF
#define PCCARD_TIMEOUT_SECTOR       (uint32_t)0x0000FFFF
#define PCCARD_TIMEOUT_STATUS       (uint32_t)0x01000000

#define PCCARD_STATUS_OK            (uint8_t)0x58
#define PCCARD_STATUS_WRITE_OK      (uint8_t)0x50
/**
  * @}
  */ 

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions ---------------------------------------------------------*/

/** @defgroup PCCARD_Exported_Functions PCCARD Exported Functions
  * @{
  */

/** @defgroup PCCARD_Exported_Functions_Group1 Initialization and de-initialization functions 
  * @brief    Initialization and Configuration functions 
  *
  @verbatim    
  ==============================================================================
          ##### PCCARD Initialization and de-initialization functions #####
  ==============================================================================
  [..]  
    This section provides functions allowing to initialize/de-initialize
    the PCCARD memory
  
@endverbatim
  * @{
  */
    
/**
  * @brief  Perform the PCCARD memory Initialization sequence
  * @param  hpccard: pointer to a PCCARD_HandleTypeDef structure that contains
  *                the configuration information for PCCARD module.
  * @param  ComSpaceTiming: Common space timing structure
  * @param  AttSpaceTiming: Attribute space timing structure
  * @param  IOSpaceTiming: IO space timing structure     
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCCARD_Init(PCCARD_HandleTypeDef *hpccard, FSMC_NAND_PCC_TimingTypeDef *ComSpaceTiming, FSMC_NAND_PCC_TimingTypeDef *AttSpaceTiming, FSMC_NAND_PCC_TimingTypeDef *IOSpaceTiming)
{
  /* Check the PCCARD controller state */
  if(hpccard == NULL)
  {
     return HAL_ERROR;
  }
  
  if(hpccard->State == HAL_PCCARD_STATE_RESET)
  {  
    /* Allocate lock resource and initialize it */
    hpccard-> Lock = HAL_UNLOCKED;
    
    /* Initialize the low level hardware (MSP) */
    HAL_PCCARD_MspInit(hpccard);
  }
  
  /* Initialize the PCCARD state */
  hpccard->State = HAL_PCCARD_STATE_BUSY;    

  /* Initialize PCCARD control Interface */
  FSMC_PCCARD_Init(hpccard->Instance, &(hpccard->Init));
  
  /* Init PCCARD common space timing Interface */
  FSMC_PCCARD_CommonSpace_Timing_Init(hpccard->Instance, ComSpaceTiming);
  
  /* Init PCCARD attribute space timing Interface */  
  FSMC_PCCARD_AttributeSpace_Timing_Init(hpccard->Instance, AttSpaceTiming);
  
  /* Init PCCARD IO space timing Interface */  
  FSMC_PCCARD_IOSpace_Timing_Init(hpccard->Instance, IOSpaceTiming);
  
  /* Enable the PCCARD device */
  __FSMC_PCCARD_ENABLE(hpccard->Instance); 
  
  /* Update the PCCARD state */
  hpccard->State = HAL_PCCARD_STATE_READY;  
  
  return HAL_OK;

}

/**
  * @brief  Perform the PCCARD memory De-initialization sequence
  * @param  hpccard: pointer to a PCCARD_HandleTypeDef structure that contains
  *                the configuration information for PCCARD module.
  * @retval HAL status
  */
HAL_StatusTypeDef  HAL_PCCARD_DeInit(PCCARD_HandleTypeDef *hpccard)
{
  /* De-Initialize the low level hardware (MSP) */
  HAL_PCCARD_MspDeInit(hpccard);
   
  /* Configure the PCCARD registers with their reset values */
  FSMC_PCCARD_DeInit(hpccard->Instance);
  
  /* Update the PCCARD controller state */
  hpccard->State = HAL_PCCARD_STATE_RESET;

  /* Release Lock */
  __HAL_UNLOCK(hpccard);

  return HAL_OK; 
}

/**
  * @brief  PCCARD MSP Init
  * @param  hpccard: pointer to a PCCARD_HandleTypeDef structure that contains
  *                the configuration information for PCCARD module.
  * @retval None
  */
__weak void HAL_PCCARD_MspInit(PCCARD_HandleTypeDef *hpccard)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PCCARD_MspInit could be implemented in the user file
   */ 
}

/**
  * @brief  PCCARD MSP DeInit
  * @param  hpccard: pointer to a PCCARD_HandleTypeDef structure that contains
  *                the configuration information for PCCARD module.
  * @retval None
  */
__weak void HAL_PCCARD_MspDeInit(PCCARD_HandleTypeDef *hpccard)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PCCARD_MspDeInit could be implemented in the user file
   */ 
}

/**
  * @}
  */

/** @defgroup PCCARD_Exported_Functions_Group2 Input Output and memory functions 
  * @brief    Input Output and memory control functions 
  *
  @verbatim    
  ==============================================================================
                ##### PCCARD Input Output and memory functions #####
  ==============================================================================
  [..]  
    This section provides functions allowing to use and control the PCCARD memory
  
@endverbatim
  * @{
  */
  
/**
  * @brief  Read Compact Flash's ID.
  * @param  hpccard: pointer to a PCCARD_HandleTypeDef structure that contains
  *                the configuration information for PCCARD module.
  * @param  CompactFlash_ID: Compact flash ID structure.  
  * @param  pStatus: pointer to compact flash status         
  * @retval HAL status
  *   
  */ 
HAL_StatusTypeDef HAL_PCCARD_Read_ID(PCCARD_HandleTypeDef *hpccard, uint8_t CompactFlash_ID[], uint8_t *pStatus)
{
  uint32_t timeout = PCCARD_TIMEOUT_READ_ID, index = 0;
  uint8_t status = 0;
  
  /* Process Locked */
  __HAL_LOCK(hpccard);  
  
  /* Check the PCCARD controller state */
  if(hpccard->State == HAL_PCCARD_STATE_BUSY)
  {
     return HAL_BUSY;
  }
  
  /* Update the PCCARD controller state */
  hpccard->State = HAL_PCCARD_STATE_BUSY;
  
  /* Initialize the CF status */
  *pStatus = PCCARD_READY;  
  
  /* Send the Identify Command */
  *(__IO uint16_t *)(PCCARD_IO_SPACE_PRIMARY_ADDR | ATA_STATUS_CMD)  = 0xECEC;
    
  /* Read CF IDs and timeout treatment */
  do 
  {
     /* Read the CF status */
     status = *(__IO uint8_t *)(PCCARD_IO_SPACE_PRIMARY_ADDR | ATA_STATUS_CMD_ALTERNATE);
     
     timeout--;
  }while((status != PCCARD_STATUS_OK) && timeout); 
  
  if(timeout == 0)
  {
    *pStatus = PCCARD_TIMEOUT_ERROR;
  }
  else
  {
     /* Read CF ID bytes */
    for(index = 0; index < 16; index++)
    {
      CompactFlash_ID[index] = *(__IO uint8_t *)(PCCARD_IO_SPACE_PRIMARY_ADDR | ATA_DATA);
    }    
  }
  
  /* Update the PCCARD controller state */
  hpccard->State = HAL_PCCARD_STATE_READY;
  
  /* Process unlocked */
  __HAL_UNLOCK(hpccard);  
  
  return HAL_OK;
}
   
/**
  * @brief  Read sector from PCCARD memory
  * @param  hpccard: pointer to a PCCARD_HandleTypeDef structure that contains
  *                the configuration information for PCCARD module.
  * @param  pBuffer: pointer to destination read buffer
  * @param  SectorAddress: Sector address to read
  * @param  pStatus: pointer to CF status
  * @retval HAL status
  */    
HAL_StatusTypeDef HAL_PCCARD_Read_Sector(PCCARD_HandleTypeDef *hpccard, uint16_t *pBuffer, uint16_t SectorAddress, uint8_t *pStatus)
{
  uint32_t timeout = PCCARD_TIMEOUT_SECTOR, index = 0;
  uint8_t status = 0;

  /* Process Locked */
  __HAL_LOCK(hpccard);
  
  /* Check the PCCARD controller state */
  if(hpccard->State == HAL_PCCARD_STATE_BUSY)
  {
     return HAL_BUSY;
  }
  
  /* Update the PCCARD controller state */
  hpccard->State = HAL_PCCARD_STATE_BUSY;

  /* Initialize CF status */
  *pStatus = PCCARD_READY;

  /* Set the parameters to write a sector */
  *(__IO uint16_t *)(PCCARD_IO_SPACE_PRIMARY_ADDR | ATA_CYLINDER_HIGH) = (uint16_t)0x00;
  *(__IO uint16_t *)(PCCARD_IO_SPACE_PRIMARY_ADDR | ATA_SECTOR_COUNT)  = ((uint16_t)0x0100 ) | ((uint16_t)SectorAddress);
  *(__IO uint16_t *)(PCCARD_IO_SPACE_PRIMARY_ADDR | ATA_STATUS_CMD)    = (uint16_t)0xE4A0;  

  do
  {
    /* wait till the Status = 0x80 */
    status =  *(__IO uint16_t *)(PCCARD_IO_SPACE_PRIMARY_ADDR | ATA_STATUS_CMD_ALTERNATE);
    timeout--;
  }while((status == 0x80) && timeout);
  
  if(timeout == 0)
  {
    *pStatus = PCCARD_TIMEOUT_ERROR;
  }
  
  timeout = 0xFFFF;

  do
  {
    /* wait till the Status = PCCARD_STATUS_OK */
    status =  *(__IO uint16_t *)(PCCARD_IO_SPACE_PRIMARY_ADDR | ATA_STATUS_CMD_ALTERNATE);
    timeout--;
  }while((status != PCCARD_STATUS_OK) && timeout);
  
  if(timeout == 0)
  {
    *pStatus = PCCARD_TIMEOUT_ERROR;
  }
  
  /* Read bytes */
  for(; index < PCCARD_SECTOR_SIZE; index++)
  {
    *(uint16_t *)pBuffer++ = *(uint16_t *)(PCCARD_IO_SPACE_PRIMARY_ADDR);
  } 

  /* Update the PCCARD controller state */
  hpccard->State = HAL_PCCARD_STATE_READY;
  
  /* Process unlocked */
  __HAL_UNLOCK(hpccard);
      
  return HAL_OK;
}


/**
  * @brief  Write sector to PCCARD memory
  * @param  hpccard: pointer to a PCCARD_HandleTypeDef structure that contains
  *                the configuration information for PCCARD module.
  * @param  pBuffer: pointer to source write buffer
  * @param  SectorAddress: Sector address to write
  * @param  pStatus: pointer to CF status
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCCARD_Write_Sector(PCCARD_HandleTypeDef *hpccard, uint16_t *pBuffer, uint16_t SectorAddress,  uint8_t *pStatus)
{
  uint32_t timeout = PCCARD_TIMEOUT_SECTOR, index = 0;
  uint8_t status = 0;

  /* Process Locked */
  __HAL_LOCK(hpccard);  
  
  /* Check the PCCARD controller state */
  if(hpccard->State == HAL_PCCARD_STATE_BUSY)
  {
     return HAL_BUSY;
  }
   
  /* Update the PCCARD controller state */
  hpccard->State = HAL_PCCARD_STATE_BUSY;
    
  /* Initialize CF status */
  *pStatus = PCCARD_READY;  
    
  /* Set the parameters to write a sector */
  *(__IO uint16_t *)(PCCARD_IO_SPACE_PRIMARY_ADDR | ATA_CYLINDER_HIGH) = (uint16_t)0x00;
  *(__IO uint16_t *)(PCCARD_IO_SPACE_PRIMARY_ADDR | ATA_SECTOR_COUNT)  = ((uint16_t)0x0100 ) | ((uint16_t)SectorAddress);
  *(__IO uint16_t *)(PCCARD_IO_SPACE_PRIMARY_ADDR | ATA_STATUS_CMD)    = (uint16_t)0x30A0;
  
  do
  {
    /* Wait till the Status = PCCARD_STATUS_OK */
    status =  *(__IO uint8_t *)(PCCARD_IO_SPACE_PRIMARY_ADDR | ATA_STATUS_CMD_ALTERNATE);
    timeout--;
  }while((status != PCCARD_STATUS_OK) && timeout);
  
  if(timeout == 0)
  {
    *pStatus = PCCARD_TIMEOUT_ERROR;
  }
  
  /* Write bytes */
  for(; index < PCCARD_SECTOR_SIZE; index++)
  {
    *(uint16_t *)(PCCARD_IO_SPACE_PRIMARY_ADDR) = *(uint16_t *)pBuffer++;
  }

  do
  {
    /* Wait till the Status = PCCARD_STATUS_WRITE_OK */
    status =  *(__IO uint8_t *)(PCCARD_IO_SPACE_PRIMARY_ADDR | ATA_STATUS_CMD_ALTERNATE);
    timeout--;
  }while((status != PCCARD_STATUS_WRITE_OK) && timeout);

  if(timeout == 0)
  {
    *pStatus = PCCARD_TIMEOUT_ERROR;
  }  

  /* Update the PCCARD controller state */
  hpccard->State = HAL_PCCARD_STATE_READY;
  
  /* Process unlocked */
  __HAL_UNLOCK(hpccard);  
  
  return HAL_OK;
}


/**
  * @brief  Erase sector from PCCARD memory 
  * @param  hpccard: pointer to a PCCARD_HandleTypeDef structure that contains
  *                the configuration information for PCCARD module.
  * @param  SectorAddress: Sector address to erase
  * @param  pStatus: pointer to CF status
  * @retval HAL status
  */
HAL_StatusTypeDef  HAL_PCCARD_Erase_Sector(PCCARD_HandleTypeDef *hpccard, uint16_t SectorAddress, uint8_t *pStatus)
{
  uint32_t timeout = 0x400;
  uint8_t status = 0;
  
  /* Process Locked */
  __HAL_LOCK(hpccard);  
  
  /* Check the PCCARD controller state */
  if(hpccard->State == HAL_PCCARD_STATE_BUSY)
  {
     return HAL_BUSY;
  }

  /* Update the PCCARD controller state */
  hpccard->State = HAL_PCCARD_STATE_BUSY;
  
  /* Initialize CF status */ 
  *pStatus = PCCARD_READY;
    
  /* Set the parameters to write a sector */
  *(__IO uint8_t *)(PCCARD_IO_SPACE_PRIMARY_ADDR | ATA_CYLINDER_LOW)  = 0x00;
  *(__IO uint8_t *)(PCCARD_IO_SPACE_PRIMARY_ADDR | ATA_CYLINDER_HIGH) = 0x00;
  *(__IO uint8_t *)(PCCARD_IO_SPACE_PRIMARY_ADDR | ATA_SECTOR_NUMBER) = SectorAddress;
  *(__IO uint8_t *)(PCCARD_IO_SPACE_PRIMARY_ADDR | ATA_SECTOR_COUNT)  = 0x01;
  *(__IO uint8_t *)(PCCARD_IO_SPACE_PRIMARY_ADDR | ATA_CARD_HEAD)     = 0xA0;
  *(__IO uint8_t *)(PCCARD_IO_SPACE_PRIMARY_ADDR | ATA_STATUS_CMD)    = ATA_ERASE_SECTOR_CMD;
  
  /* wait till the CF is ready */
  status =  *(__IO uint8_t *)(PCCARD_IO_SPACE_PRIMARY_ADDR | ATA_STATUS_CMD_ALTERNATE);
  
  while((status != PCCARD_STATUS_WRITE_OK) && timeout)
  {
    status =  *(__IO uint8_t *)(PCCARD_IO_SPACE_PRIMARY_ADDR | ATA_STATUS_CMD_ALTERNATE);
    timeout--;
  } 
  
  if(timeout == 0)
  {
    *pStatus = PCCARD_TIMEOUT_ERROR;
  }
  
  /* Check the PCCARD controller state */
  hpccard->State = HAL_PCCARD_STATE_READY;
  
  /* Process unlocked */
  __HAL_UNLOCK(hpccard);   
  
  return HAL_OK;
}

/**
  * @brief  Reset the PCCARD memory 
  * @param  hpccard: pointer to a PCCARD_HandleTypeDef structure that contains
  *                the configuration information for PCCARD module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCCARD_Reset(PCCARD_HandleTypeDef *hpccard)
{
  /* Process Locked */
  __HAL_LOCK(hpccard);  
  
  /* Check the PCCARD controller state */
  if(hpccard->State == HAL_PCCARD_STATE_BUSY)
  {
     return HAL_BUSY;
  }

  /* Provide an SW reset and Read and verify the:
   - CF Configuration Option Register at address 0x98000200 --> 0x80
   - Card Configuration and Status Register at address 0x98000202 --> 0x00
   - Pin Replacement Register  at address 0x98000204 --> 0x0C
   - Socket and Copy Register at address 0x98000206 --> 0x00
  */

  /* Check the PCCARD controller state */
  hpccard->State = HAL_PCCARD_STATE_BUSY;
  
  *(__IO uint8_t *)(PCCARD_ATTRIBUTE_SPACE_ADDRESS | ATA_CARD_CONFIGURATION) = 0x01;
    
  /* Check the PCCARD controller state */
  hpccard->State = HAL_PCCARD_STATE_READY;
  
  /* Process unlocked */
  __HAL_UNLOCK(hpccard);  
  
  return HAL_OK;
}

/**
  * @brief  This function handles PCCARD device interrupt request.
  * @param  hpccard: pointer to a PCCARD_HandleTypeDef structure that contains
  *                the configuration information for PCCARD module.
  * @retval HAL status
*/
void HAL_PCCARD_IRQHandler(PCCARD_HandleTypeDef *hpccard)
{
  /* Check PCCARD interrupt Rising edge flag */
  if(__FSMC_PCCARD_GET_FLAG(hpccard->Instance, FSMC_FLAG_RISING_EDGE))
  {
    /* PCCARD interrupt callback*/
    HAL_PCCARD_ITCallback(hpccard);
  
    /* Clear PCCARD interrupt Rising edge pending bit */
    __FSMC_PCCARD_CLEAR_FLAG(hpccard->Instance, FSMC_FLAG_RISING_EDGE);
  }
  
  /* Check PCCARD interrupt Level flag */
  if(__FSMC_PCCARD_GET_FLAG(hpccard->Instance, FSMC_FLAG_LEVEL))
  {
    /* PCCARD interrupt callback*/
    HAL_PCCARD_ITCallback(hpccard);
  
    /* Clear PCCARD interrupt Level pending bit */
    __FSMC_PCCARD_CLEAR_FLAG(hpccard->Instance, FSMC_FLAG_LEVEL);
  }

  /* Check PCCARD interrupt Falling edge flag */
  if(__FSMC_PCCARD_GET_FLAG(hpccard->Instance, FSMC_FLAG_FALLING_EDGE))
  {
    /* PCCARD interrupt callback*/
    HAL_PCCARD_ITCallback(hpccard);
  
    /* Clear PCCARD interrupt Falling edge pending bit */
    __FSMC_PCCARD_CLEAR_FLAG(hpccard->Instance, FSMC_FLAG_FALLING_EDGE);
  }
  
  /* Check PCCARD interrupt FIFO empty flag */
  if(__FSMC_PCCARD_GET_FLAG(hpccard->Instance, FSMC_FLAG_FEMPT))
  {
    /* PCCARD interrupt callback*/
    HAL_PCCARD_ITCallback(hpccard);
  
    /* Clear PCCARD interrupt FIFO empty pending bit */
    __FSMC_PCCARD_CLEAR_FLAG(hpccard->Instance, FSMC_FLAG_FEMPT);
  }  

}

/**
  * @brief  PCCARD interrupt feature callback
  * @param  hpccard: pointer to a PCCARD_HandleTypeDef structure that contains
  *                the configuration information for PCCARD module.
  * @retval None
  */
__weak void HAL_PCCARD_ITCallback(PCCARD_HandleTypeDef *hpccard)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PCCARD_ITCallback could be implemented in the user file
   */
}
  
/**
  * @}
  */

/** @defgroup PCCARD_Exported_Functions_Group3 Peripheral State functions 
 *  @brief   Peripheral State functions 
 *
@verbatim   
  ==============================================================================
                   ##### PCCARD Peripheral State functions #####
  ==============================================================================  
  [..]
    This subsection permits to get in run-time the status of the PCCARD controller 
    and the data flow.

@endverbatim
  * @{
  */ 
  
/**
  * @brief  return the PCCARD controller state
  * @param  hpccard: pointer to a PCCARD_HandleTypeDef structure that contains
  *                the configuration information for PCCARD module.
  * @retval HAL state
  */
HAL_PCCARD_StateTypeDef HAL_PCCARD_GetState(PCCARD_HandleTypeDef *hpccard)
{
  return hpccard->State;
}  
 
/**
  * @brief  Get the compact flash memory status
  * @param  hpccard: pointer to a PCCARD_HandleTypeDef structure that contains
  *                the configuration information for PCCARD module.       
  * @retval New status of the CF operation. This parameter can be:
  *          - CompactFlash_TIMEOUT_ERROR: when the previous operation generate 
  *            a Timeout error
  *          - CompactFlash_READY: when memory is ready for the next operation     
  *                
  */
HAL_PCCARD_StatusTypeDef HAL_PCCARD_GetStatus(PCCARD_HandleTypeDef *hpccard)
{
  uint32_t timeout = PCCARD_TIMEOUT_STATUS, status_cf = 0;  
  
  /* Check the PCCARD controller state */
  if(hpccard->State == HAL_PCCARD_STATE_BUSY)
  {
     return HAL_PCCARD_STATUS_ONGOING;
  }

  status_cf =  *(__IO uint8_t *)(PCCARD_IO_SPACE_PRIMARY_ADDR | ATA_STATUS_CMD_ALTERNATE);
  
  while((status_cf == PCCARD_BUSY) && timeout)
  {
    status_cf =  *(__IO uint8_t *)(PCCARD_IO_SPACE_PRIMARY_ADDR | ATA_STATUS_CMD_ALTERNATE);
    timeout--;
  }

  if(timeout == 0)
  {          
    status_cf =  PCCARD_TIMEOUT_ERROR;      
  }   

  /* Return the operation status */
  return (HAL_PCCARD_StatusTypeDef) status_cf;      
}
  
/**
  * @brief  Reads the Compact Flash memory status using the Read status command
  * @param  hpccard: pointer to a PCCARD_HandleTypeDef structure that contains
  *                the configuration information for PCCARD module.      
  * @retval The status of the Compact Flash memory. This parameter can be:
  *          - CompactFlash_BUSY: when memory is busy
  *          - CompactFlash_READY: when memory is ready for the next operation    
  *          - CompactFlash_ERROR: when the previous operation gererates error                
  */
HAL_PCCARD_StatusTypeDef HAL_PCCARD_ReadStatus(PCCARD_HandleTypeDef *hpccard)
{
  uint8_t data = 0, status_cf = PCCARD_BUSY;
  
  /* Check the PCCARD controller state */
  if(hpccard->State == HAL_PCCARD_STATE_BUSY)
  {
     return HAL_PCCARD_STATUS_ONGOING;
  } 

  /* Read status operation */
  data =  *(__IO uint8_t *)(PCCARD_IO_SPACE_PRIMARY_ADDR | ATA_STATUS_CMD_ALTERNATE);

  if((data & PCCARD_TIMEOUT_ERROR) == PCCARD_TIMEOUT_ERROR)
  {
    status_cf = PCCARD_TIMEOUT_ERROR;
  } 
  else if((data & PCCARD_READY) == PCCARD_READY)
  {
    status_cf = PCCARD_READY;
  }
  
  return (HAL_PCCARD_StatusTypeDef) status_cf;
}  
 
/**
  * @}
  */
  
/**
  * @}
  */
/**
  * @}
  */
  
#endif /* STM32F101xE || STM32F103xE || STM32F101xG || STM32F103xG */
#endif /* HAL_PCCARD_MODULE_ENABLED */  

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
