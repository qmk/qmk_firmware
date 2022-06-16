/**
  ******************************************************************************
  * @file    stm324x9i_eval_sdram.c
  * @author  MCD Application Team
  * @version V2.2.3
  * @date    22-April-2016
  * @brief   This file includes the SDRAM driver for the MT48LC4M32B2B5-7 memory 
  *          device mounted on STM324x9I-EVAL evaluation board.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
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

/* File Info : -----------------------------------------------------------------
                                   User NOTES
1. How To use this driver:
--------------------------
   - This driver is used to drive the MT48LC4M32B2B5-7 SDRAM external memory mounted
     on STM324x9I-EVAL evaluation board.
   - This driver does not need a specific component driver for the SDRAM device
     to be included with.

2. Driver description:
---------------------
  + Initialization steps:
     o Initialize the SDRAM external memory using the BSP_SDRAM_Init() function. This 
       function includes the MSP layer hardware resources initialization and the
       FMC controller configuration to interface with the external SDRAM memory.
     o It contains the SDRAM initialization sequence to program the SDRAM external 
       device using the function BSP_SDRAM_Initialization_sequence(). Note that this 
       sequence is standard for all SDRAM devices, but can include some differences
       from a device to another. If it is the case, the right sequence should be 
       implemented separately.
  
  + SDRAM read/write operations
     o SDRAM external memory can be accessed with read/write operations once it is
       initialized.
       Read/write operation can be performed with AHB access using the functions
       BSP_SDRAM_ReadData()/BSP_SDRAM_WriteData(), or by DMA transfer using the functions
       BSP_SDRAM_ReadData_DMA()/BSP_SDRAM_WriteData_DMA().
     o The AHB access is performed with 32-bit width transaction, the DMA transfer
       configuration is fixed at single (no burst) word transfer (see the 
       SDRAM_MspInit() static function).
     o User can implement his own functions for read/write access with his desired 
       configurations.
     o If interrupt mode is used for DMA transfer, the function BSP_SDRAM_DMA_IRQHandler()
       is called in IRQ handler file, to serve the generated interrupt once the DMA 
       transfer is complete.
     o You can send a command to the SDRAM device in runtime using the function 
       BSP_SDRAM_Sendcmd(), and giving the desired command as parameter chosen between 
       the predefined commands of the "FMC_SDRAM_CommandTypeDef" structure. 
 
------------------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#if GFX_COMPAT_V2 && GFX_COMPAT_OLDCOLORS
	#undef Red
	#undef Green
	#undef Blue
#endif
#include "stm324x9i_eval_sdram.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM324x9I_EVAL
  * @{
  */ 
  
/** @defgroup STM324x9I_EVAL_SDRAM STM324x9I EVAL SDRAM
  * @{
  */ 

/** @defgroup STM324x9I_EVAL_SDRAM_Private_Types_Definitions STM324x9I EVAL SDRAM Private Types Definitions
  * @{
  */ 
/**
  * @}
  */

/** @defgroup STM324x9I_EVAL_SDRAM_Private_Defines STM324x9I EVAL SDRAM Private Defines
  * @{
  */
/**
  * @}
  */

/** @defgroup STM324x9I_EVAL_SDRAM_Private_Macros STM324x9I EVAL SDRAM Private Macros
  * @{
  */  
/**
  * @}
  */

/** @defgroup STM324x9I_EVAL_SDRAM_Private_Variables STM324x9I EVAL SDRAM Private Variables
  * @{
  */       
static SDRAM_HandleTypeDef sdramHandle;
static FMC_SDRAM_TimingTypeDef Timing;
static FMC_SDRAM_CommandTypeDef Command;
/**
  * @}
  */ 

/** @defgroup STM324x9I_EVAL_SDRAM_Private_Function_Prototypes STM324x9I EVAL SDRAM Private Function Prototypes
  * @{
  */ 
static void SDRAM_MspInit(void); 
/**
  * @}
  */
    
/** @defgroup STM324x9I_EVAL_SDRAM_Private_Functions STM324x9I EVAL SDRAM Private Functions
  * @{
  */ 

/**
  * @brief  Initializes the SDRAM device.
  * @retval SDRAM status
  */
gU8 BSP_SDRAM_Init(void)
{ 
  static gU8 sdramstatus = SDRAM_ERROR;
  /* SDRAM device configuration */
  sdramHandle.Instance = FMC_SDRAM_DEVICE;
    
  /* Timing configuration for 90Mhz as SD clock frequency (System clock is up to 180Mhz */
  Timing.LoadToActiveDelay    = 2;
  Timing.ExitSelfRefreshDelay = 7;
  Timing.SelfRefreshTime      = 4;
  Timing.RowCycleDelay        = 7;
  Timing.WriteRecoveryTime    = 2;
  Timing.RPDelay              = 2;
  Timing.RCDDelay             = 2;
  
  sdramHandle.Init.SDBank             = FMC_SDRAM_BANK1;
  sdramHandle.Init.ColumnBitsNumber   = FMC_SDRAM_COLUMN_BITS_NUM_9;
  sdramHandle.Init.RowBitsNumber      = FMC_SDRAM_ROW_BITS_NUM_12;
  sdramHandle.Init.MemoryDataWidth    = SDRAM_MEMORY_WIDTH;
  sdramHandle.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
  sdramHandle.Init.CASLatency         = FMC_SDRAM_CAS_LATENCY_3;
  sdramHandle.Init.WriteProtection    = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
  sdramHandle.Init.SDClockPeriod      = SDCLOCK_PERIOD;
  sdramHandle.Init.ReadBurst          = FMC_SDRAM_RBURST_ENABLE;
  sdramHandle.Init.ReadPipeDelay      = FMC_SDRAM_RPIPE_DELAY_0;
  
  /* SDRAM controller initialization */
  SDRAM_MspInit();
  if(HAL_SDRAM_Init(&sdramHandle, &Timing) != HAL_OK)
  {
    sdramstatus = SDRAM_ERROR;
  }
  else
  {
    sdramstatus = SDRAM_OK;
  }
  
  /* SDRAM initialization sequence */
  BSP_SDRAM_Initialization_sequence(REFRESH_COUNT);
  
  return sdramstatus;
}

/**
  * @brief  Programs the SDRAM device.
  * @param  RefreshCount: SDRAM refresh counter value 
  */
void BSP_SDRAM_Initialization_sequence(gU32 RefreshCount)
{
  __IO gU32 tmpmrd = 0;
  
  /* Step 1: Configure a clock configuration enable command */
  Command.CommandMode            = FMC_SDRAM_CMD_CLK_ENABLE;
  Command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
  Command.AutoRefreshNumber      = 1;
  Command.ModeRegisterDefinition = 0;

  /* Send the command */
  HAL_SDRAM_SendCommand(&sdramHandle, &Command, SDRAM_TIMEOUT);

  /* Step 2: Insert 100 us minimum delay */ 
  /* Inserted delay is equal to 1 ms due to systick time base unit (ms) */
  HAL_Delay(1);
    
  /* Step 3: Configure a PALL (precharge all) command */ 
  Command.CommandMode            = FMC_SDRAM_CMD_PALL;
  Command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
  Command.AutoRefreshNumber      = 1;
  Command.ModeRegisterDefinition = 0;

  /* Send the command */
  HAL_SDRAM_SendCommand(&sdramHandle, &Command, SDRAM_TIMEOUT);  
  
  /* Step 4: Configure an Auto Refresh command */ 
  Command.CommandMode            = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
  Command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
  Command.AutoRefreshNumber      = 8;
  Command.ModeRegisterDefinition = 0;

  /* Send the command */
  HAL_SDRAM_SendCommand(&sdramHandle, &Command, SDRAM_TIMEOUT);
  
  /* Step 5: Program the external memory mode register */
  tmpmrd = (gU32)SDRAM_MODEREG_BURST_LENGTH_1          |\
                     SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |\
                     SDRAM_MODEREG_CAS_LATENCY_3           |\
                     SDRAM_MODEREG_OPERATING_MODE_STANDARD |\
                     SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;
  
  Command.CommandMode            = FMC_SDRAM_CMD_LOAD_MODE;
  Command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
  Command.AutoRefreshNumber      = 1;
  Command.ModeRegisterDefinition = tmpmrd;

  /* Send the command */
  HAL_SDRAM_SendCommand(&sdramHandle, &Command, SDRAM_TIMEOUT);
  
  /* Step 6: Set the refresh rate counter */
  /* Set the device refresh rate */
  HAL_SDRAM_ProgramRefreshRate(&sdramHandle, RefreshCount); 
}

/**
  * @brief  Reads an mount of data from the SDRAM memory in polling mode. 
  * @param  uwStartAddress: Read start address
  * @param  pData: Pointer to data to be read  
  * @param  uwDataSize: Size of read data from the memory
  * @retval SDRAM status
  */
gU8 BSP_SDRAM_ReadData(gU32 uwStartAddress, gU32 *pData, gU32 uwDataSize)
{
  if(HAL_SDRAM_Read_32b(&sdramHandle, (gU32 *)uwStartAddress, pData, uwDataSize) != HAL_OK)
  {
    return SDRAM_ERROR;
  }
  else
  {
    return SDRAM_OK;
  } 
}

/**
  * @brief  Reads an mount of data from the SDRAM memory in DMA mode. 
  * @param  uwStartAddress: Read start address
  * @param  pData: Pointer to data to be read  
  * @param  uwDataSize: Size of read data from the memory
  * @retval SDRAM status
  */
gU8 BSP_SDRAM_ReadData_DMA(gU32 uwStartAddress, gU32 *pData, gU32 uwDataSize)
{
  if(HAL_SDRAM_Read_DMA(&sdramHandle, (gU32 *)uwStartAddress, pData, uwDataSize) != HAL_OK)
  {
    return SDRAM_ERROR;
  }
  else
  {
    return SDRAM_OK;
  }     
}

/**
  * @brief  Writes an mount of data to the SDRAM memory in polling mode.
  * @param  uwStartAddress: Write start address
  * @param  pData: Pointer to data to be written  
  * @param  uwDataSize: Size of written data from the memory
  * @retval SDRAM status
  */
gU8 BSP_SDRAM_WriteData(gU32 uwStartAddress, gU32 *pData, gU32 uwDataSize) 
{
  if(HAL_SDRAM_Write_32b(&sdramHandle, (gU32 *)uwStartAddress, pData, uwDataSize) != HAL_OK)
  {
    return SDRAM_ERROR;
  }
  else
  {
    return SDRAM_OK;
  }
}

/**
  * @brief  Writes an mount of data to the SDRAM memory in DMA mode.
  * @param  uwStartAddress: Write start address
  * @param  pData: Pointer to data to be written  
  * @param  uwDataSize: Size of written data from the memory
  * @retval SDRAM status
  */
gU8 BSP_SDRAM_WriteData_DMA(gU32 uwStartAddress, gU32 *pData, gU32 uwDataSize) 
{
  if(HAL_SDRAM_Write_DMA(&sdramHandle, (gU32 *)uwStartAddress, pData, uwDataSize) != HAL_OK)
  {
    return SDRAM_ERROR;
  }
  else
  {
    return SDRAM_OK;
  } 
}

/**
  * @brief  Sends command to the SDRAM bank.
  * @param  SdramCmd: Pointer to SDRAM command structure 
  * @retval HAL status
  */  
gU8 BSP_SDRAM_Sendcmd(FMC_SDRAM_CommandTypeDef *SdramCmd)
{
  if(HAL_SDRAM_SendCommand(&sdramHandle, SdramCmd, SDRAM_TIMEOUT) != HAL_OK)
  {
    return SDRAM_ERROR;
  }
  else
  {
    return SDRAM_OK;
  }
}

/**
  * @brief  Handles SDRAM DMA transfer interrupt request.
  */
void BSP_SDRAM_DMA_IRQHandler(void)
{
  HAL_DMA_IRQHandler(sdramHandle.hdma); 
}

/**
  * @brief  Initializes SDRAM MSP.
  */
static void SDRAM_MspInit(void)
{  
  static DMA_HandleTypeDef dmaHandle;
  GPIO_InitTypeDef GPIO_Init_Structure;
  SDRAM_HandleTypeDef  *hsdram = &sdramHandle; 
  
  /* Enable FMC clock */
  __FMC_CLK_ENABLE();
  
  /* Enable chosen DMAx clock */
  __DMAx_CLK_ENABLE();

  /* Enable GPIOs clock */
  __GPIOD_CLK_ENABLE();
  __GPIOE_CLK_ENABLE();
  __GPIOF_CLK_ENABLE();
  __GPIOG_CLK_ENABLE();
  __GPIOH_CLK_ENABLE();
  __GPIOI_CLK_ENABLE();  
  
  /* Common GPIO configuration */
  GPIO_Init_Structure.Mode      = GPIO_MODE_AF_PP;
  GPIO_Init_Structure.Pull      = GPIO_PULLUP;
  GPIO_Init_Structure.Speed     = GPIO_SPEED_FAST;
  GPIO_Init_Structure.Alternate = GPIO_AF12_FMC;
  
  /* GPIOD configuration */
  GPIO_Init_Structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_8| GPIO_PIN_9 | GPIO_PIN_10 |\
                              GPIO_PIN_14 | GPIO_PIN_15;
 
   
  HAL_GPIO_Init(GPIOD, &GPIO_Init_Structure);

  /* GPIOE configuration */  
  GPIO_Init_Structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_7| GPIO_PIN_8 | GPIO_PIN_9 |\
                              GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 |\
                              GPIO_PIN_15;
      
  HAL_GPIO_Init(GPIOE, &GPIO_Init_Structure);
  
  /* GPIOF configuration */  
  GPIO_Init_Structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2| GPIO_PIN_3 | GPIO_PIN_4 |\
                              GPIO_PIN_5 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 |\
                              GPIO_PIN_15;
    
  HAL_GPIO_Init(GPIOF, &GPIO_Init_Structure);
  
  /* GPIOG configuration */  
  GPIO_Init_Structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4| GPIO_PIN_5 | GPIO_PIN_8 |\
                              GPIO_PIN_15;
  HAL_GPIO_Init(GPIOG, &GPIO_Init_Structure);

  /* GPIOH configuration */  
  GPIO_Init_Structure.Pin   = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_5 | GPIO_PIN_8 | GPIO_PIN_9 |\
                              GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 |\
                              GPIO_PIN_15;
  HAL_GPIO_Init(GPIOH, &GPIO_Init_Structure); 
  
  /* GPIOI configuration */  
  GPIO_Init_Structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 |\
                              GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_9 | GPIO_PIN_10;
  HAL_GPIO_Init(GPIOI, &GPIO_Init_Structure);  
  
  /* Configure common DMA parameters */
  dmaHandle.Init.Channel             = SDRAM_DMAx_CHANNEL;
  dmaHandle.Init.Direction           = DMA_MEMORY_TO_MEMORY;
  dmaHandle.Init.PeriphInc           = DMA_PINC_ENABLE;
  dmaHandle.Init.MemInc              = DMA_MINC_ENABLE;
  dmaHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
  dmaHandle.Init.MemDataAlignment    = DMA_MDATAALIGN_WORD;
  dmaHandle.Init.Mode                = DMA_NORMAL;
  dmaHandle.Init.Priority            = DMA_PRIORITY_HIGH;
  dmaHandle.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;         
  dmaHandle.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
  dmaHandle.Init.MemBurst            = DMA_MBURST_SINGLE;
  dmaHandle.Init.PeriphBurst         = DMA_PBURST_SINGLE; 
  
  dmaHandle.Instance = SDRAM_DMAx_STREAM;
  
   /* Associate the DMA handle */
  __HAL_LINKDMA(hsdram, hdma, dmaHandle);
  
  /* Deinitialize the stream for new transfer */
  HAL_DMA_DeInit(&dmaHandle);
  
  /* Configure the DMA stream */
  HAL_DMA_Init(&dmaHandle); 
  
  /* NVIC configuration for DMA transfer complete interrupt */
  HAL_NVIC_SetPriority(SDRAM_DMAx_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(SDRAM_DMAx_IRQn);
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
  
/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
