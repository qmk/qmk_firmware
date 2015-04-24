/**
  ******************************************************************************
  * @file    stm32l1xx_ll_fsmc.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    5-September-2014
  * @brief   Header file of FSMC HAL module.
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
#ifndef __STM32L1xx_LL_FSMC_H
#define __STM32L1xx_LL_FSMC_H

#ifdef __cplusplus
 extern "C" {
#endif

#if defined (STM32L151xD) || defined (STM32L152xD) || defined (STM32L162xD)

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal_def.h"

/** @addtogroup STM32L1xx_HAL_Driver
  * @{
  */

/** @addtogroup FSMC_LL
  * @{
  */ 

/* Exported typedef ----------------------------------------------------------*/ 

/** @defgroup FSMC_NORSRAM_Exported_typedef FSMC NOR/SRAM Exported typedef
  * @{
  */ 
  
#define FSMC_NORSRAM_TYPEDEF            FSMC_Bank1_TypeDef
#define FSMC_NORSRAM_EXTENDED_TYPEDEF   FSMC_Bank1E_TypeDef

#define FSMC_NORSRAM_DEVICE             FSMC_Bank1
#define FSMC_NORSRAM_EXTENDED_DEVICE    FSMC_Bank1E

/** 
  * @brief  FSMC_NORSRAM Configuration Structure definition  
  */ 
typedef struct
{
  uint32_t NSBank;                       /*!< Specifies the NORSRAM memory device that will be used.
                                              This parameter can be a value of @ref FSMC_NORSRAM_Bank                     */  
                                                    
  uint32_t DataAddressMux;               /*!< Specifies whether the address and data values are
                                              multiplexed on the data bus or not. 
                                              This parameter can be a value of @ref FSMC_Data_Address_Bus_Multiplexing    */
  
  uint32_t MemoryType;                   /*!< Specifies the type of external memory attached to
                                              the corresponding memory device.
                                              This parameter can be a value of @ref FSMC_Memory_Type                      */
                                              
  uint32_t MemoryDataWidth;              /*!< Specifies the external memory device width.
                                              This parameter can be a value of @ref FSMC_NORSRAM_Data_Width               */
  
  uint32_t BurstAccessMode;              /*!< Enables or disables the burst access mode for Flash memory,
                                              valid only with synchronous burst Flash memories.
                                              This parameter can be a value of @ref FSMC_Burst_Access_Mode                */
                                               
  uint32_t WaitSignalPolarity;           /*!< Specifies the wait signal polarity, valid only when accessing
                                              the Flash memory in burst mode.
                                              This parameter can be a value of @ref FSMC_Wait_Signal_Polarity             */
  
  uint32_t WrapMode;                     /*!< Enables or disables the Wrapped burst access mode for Flash
                                              memory, valid only when accessing Flash memories in burst mode.
                                              This parameter can be a value of @ref FSMC_Wrap_Mode                        */
  
  uint32_t WaitSignalActive;             /*!< Specifies if the wait signal is asserted by the memory one
                                              clock cycle before the wait state or during the wait state,
                                              valid only when accessing memories in burst mode. 
                                              This parameter can be a value of @ref FSMC_Wait_Timing                      */
  
  uint32_t WriteOperation;               /*!< Enables or disables the write operation in the selected device by the FSMC. 
                                              This parameter can be a value of @ref FSMC_Write_Operation                  */
  
  uint32_t WaitSignal;                   /*!< Enables or disables the wait state insertion via wait
                                              signal, valid for Flash memory access in burst mode. 
                                              This parameter can be a value of @ref FSMC_Wait_Signal                      */
  
  uint32_t ExtendedMode;                 /*!< Enables or disables the extended mode.
                                              This parameter can be a value of @ref FSMC_Extended_Mode                    */
  
  uint32_t AsynchronousWait;             /*!< Enables or disables wait signal during asynchronous transfers,
                                              valid only with asynchronous Flash memories.
                                              This parameter can be a value of @ref FSMC_AsynchronousWait                 */
  
  uint32_t WriteBurst;                   /*!< Enables or disables the write burst operation.
                                              This parameter can be a value of @ref FSMC_Write_Burst                      */                                     

}FSMC_NORSRAM_InitTypeDef;


/** 
  * @brief  FSMC_NORSRAM Timing parameters structure definition  
  */
typedef struct
{
  uint32_t AddressSetupTime;             /*!< Defines the number of HCLK cycles to configure
                                              the duration of the address setup time. 
                                              This parameter can be a value between Min_Data = 0 and Max_Data = 15.
                                              @note This parameter is not used with synchronous NOR Flash memories.      */
  
  uint32_t AddressHoldTime;              /*!< Defines the number of HCLK cycles to configure
                                              the duration of the address hold time.
                                              This parameter can be a value between Min_Data = 1 and Max_Data = 15. 
                                              @note This parameter is not used with synchronous NOR Flash memories.      */
  
  uint32_t DataSetupTime;                /*!< Defines the number of HCLK cycles to configure
                                              the duration of the data setup time.
                                              This parameter can be a value between Min_Data = 1 and Max_Data = 255.
                                              @note This parameter is used for SRAMs, ROMs and asynchronous multiplexed 
                                              NOR Flash memories.                                                        */
  
  uint32_t BusTurnAroundDuration;        /*!< Defines the number of HCLK cycles to configure
                                              the duration of the bus turnaround.
                                              This parameter can be a value between Min_Data = 0 and Max_Data = 15.
                                              @note This parameter is only used for multiplexed NOR Flash memories.      */
  
  uint32_t CLKDivision;                  /*!< Defines the period of CLK clock output signal, expressed in number of 
                                              HCLK cycles. This parameter can be a value between Min_Data = 2 and Max_Data = 16.
                                              @note This parameter is not used for asynchronous NOR Flash, SRAM or ROM 
                                              accesses.                                                                  */
  
  uint32_t DataLatency;                  /*!< Defines the number of memory clock cycles to issue
                                              to the memory before getting the first data.
                                              The parameter value depends on the memory type as shown below:
                                              - It must be set to 0 in case of a CRAM
                                              - It is don't care in asynchronous NOR, SRAM or ROM accesses
                                              - It may assume a value between Min_Data = 2 and Max_Data = 17 in NOR Flash memories
                                                with synchronous burst mode enable                                       */
  
  uint32_t AccessMode;                   /*!< Specifies the asynchronous access mode. 
                                              This parameter can be a value of @ref FSMC_Access_Mode                      */
  
}FSMC_NORSRAM_TimingTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup FSMC_NORSRAM_Exported_constants FSMC NOR/SRAM Exported constants
  * @{
  */ 
  
/** @defgroup FSMC_NORSRAM_Bank FSMC NOR/SRAM Bank
  * @{
  */
#define FSMC_BANK1_NORSRAM1                       ((uint32_t)0x00000000)
#define FSMC_BANK1_NORSRAM2                       ((uint32_t)0x00000002)
#define FSMC_BANK1_NORSRAM3                       ((uint32_t)0x00000004)
#define FSMC_BANK1_NORSRAM4                       ((uint32_t)0x00000006)

/* To keep compatibility with previous families */
#define FSMC_NORSRAM_BANK1                        FSMC_BANK1_NORSRAM1
#define FSMC_NORSRAM_BANK2                        FSMC_BANK1_NORSRAM2
#define FSMC_NORSRAM_BANK3                        FSMC_BANK1_NORSRAM3
#define FSMC_NORSRAM_BANK4                        FSMC_BANK1_NORSRAM4

#define IS_FSMC_NORSRAM_BANK(__BANK__) (((__BANK__) == FSMC_BANK1_NORSRAM1) || \
                                        ((__BANK__) == FSMC_BANK1_NORSRAM2) || \
                                        ((__BANK__) == FSMC_BANK1_NORSRAM3) || \
                                        ((__BANK__) == FSMC_BANK1_NORSRAM4))
/**
  * @}
  */

/** @defgroup FSMC_Data_Address_Bus_Multiplexing FSMC Data Address Bus Multiplexing
  * @{
  */

#define FSMC_DATA_ADDRESS_MUX_DISABLE            ((uint32_t)0x00000000)
#define FSMC_DATA_ADDRESS_MUX_ENABLE             ((uint32_t)FSMC_BCRx_MUXEN)

#define IS_FSMC_MUX(__MUX__) (((__MUX__) == FSMC_DATA_ADDRESS_MUX_DISABLE) || \
                              ((__MUX__) == FSMC_DATA_ADDRESS_MUX_ENABLE))
/**
  * @}
  */

/** @defgroup FSMC_Memory_Type FSMC Memory Type
  * @{
  */

#define FSMC_MEMORY_TYPE_SRAM                    ((uint32_t)0x00000000)
#define FSMC_MEMORY_TYPE_PSRAM                   ((uint32_t)FSMC_BCRx_MTYP_0)
#define FSMC_MEMORY_TYPE_NOR                     ((uint32_t)FSMC_BCRx_MTYP_1)


#define IS_FSMC_MEMORY(__MEMORY__) (((__MEMORY__) == FSMC_MEMORY_TYPE_SRAM) || \
                                    ((__MEMORY__) == FSMC_MEMORY_TYPE_PSRAM)|| \
                                    ((__MEMORY__) == FSMC_MEMORY_TYPE_NOR))
/**
  * @}
  */

/** @defgroup FSMC_NORSRAM_Data_Width FSMC NOR/SRAM Data Width
  * @{
  */

#define FSMC_NORSRAM_MEM_BUS_WIDTH_8             ((uint32_t)0x00000000)
#define FSMC_NORSRAM_MEM_BUS_WIDTH_16            ((uint32_t)FSMC_BCRx_MWID_0)
#define FSMC_NORSRAM_MEM_BUS_WIDTH_32            ((uint32_t)FSMC_BCRx_MWID_1)

#define IS_FSMC_NORSRAM_MEMORY_WIDTH(__WIDTH__) (((__WIDTH__) == FSMC_NORSRAM_MEM_BUS_WIDTH_8)  || \
                                                 ((__WIDTH__) == FSMC_NORSRAM_MEM_BUS_WIDTH_16) || \
                                                 ((__WIDTH__) == FSMC_NORSRAM_MEM_BUS_WIDTH_32))
/**
  * @}
  */

/** @defgroup FSMC_NORSRAM_Flash_Access FSMC NOR/SRAM Flash Access
  * @{
  */
  
#define FSMC_NORSRAM_FLASH_ACCESS_ENABLE         ((uint32_t)FSMC_BCRx_FACCEN)
#define FSMC_NORSRAM_FLASH_ACCESS_DISABLE        ((uint32_t)0x00000000)
/**
  * @}
  */

/** @defgroup FSMC_Burst_Access_Mode FSMC Burst Access Mode
  * @{
  */

#define FSMC_BURST_ACCESS_MODE_DISABLE           ((uint32_t)0x00000000) 
#define FSMC_BURST_ACCESS_MODE_ENABLE            ((uint32_t)FSMC_BCRx_BURSTEN)

#define IS_FSMC_BURSTMODE(__STATE__) (((__STATE__) == FSMC_BURST_ACCESS_MODE_DISABLE) || \
                                      ((__STATE__) == FSMC_BURST_ACCESS_MODE_ENABLE))
/**
  * @}
  */
    

/** @defgroup FSMC_Wait_Signal_Polarity FSMC Wait Signal Polarity
  * @{
  */
  
#define FSMC_WAIT_SIGNAL_POLARITY_LOW            ((uint32_t)0x00000000)
#define FSMC_WAIT_SIGNAL_POLARITY_HIGH           ((uint32_t)FSMC_BCRx_WAITPOL)

#define IS_FSMC_WAIT_POLARITY(__POLARITY__) (((__POLARITY__) == FSMC_WAIT_SIGNAL_POLARITY_LOW) || \
                                             ((__POLARITY__) == FSMC_WAIT_SIGNAL_POLARITY_HIGH))
/**
  * @}
  */

/** @defgroup FSMC_Wrap_Mode FSMC Wrap Mode
  * @{
  */
  
#define FSMC_WRAP_MODE_DISABLE                   ((uint32_t)0x00000000)
#define FSMC_WRAP_MODE_ENABLE                    ((uint32_t)FSMC_BCRx_WRAPMOD)

#define IS_FSMC_WRAP_MODE(__MODE__) (((__MODE__) == FSMC_WRAP_MODE_DISABLE) || \
                                     ((__MODE__) == FSMC_WRAP_MODE_ENABLE)) 
/**
  * @}
  */

/** @defgroup FSMC_Wait_Timing FSMC Wait Timing
  * @{
  */
  
#define FSMC_WAIT_TIMING_BEFORE_WS               ((uint32_t)0x00000000)
#define FSMC_WAIT_TIMING_DURING_WS               ((uint32_t)FSMC_BCRx_WAITCFG)

#define IS_FSMC_WAIT_SIGNAL_ACTIVE(__ACTIVE__) (((__ACTIVE__) == FSMC_WAIT_TIMING_BEFORE_WS) || \
                                                ((__ACTIVE__) == FSMC_WAIT_TIMING_DURING_WS)) 
/**
  * @}
  */

/** @defgroup FSMC_Write_Operation FSMC Write Operation
  * @{
  */
  
#define FSMC_WRITE_OPERATION_DISABLE             ((uint32_t)0x00000000)
#define FSMC_WRITE_OPERATION_ENABLE              ((uint32_t)FSMC_BCRx_WREN)

#define IS_FSMC_WRITE_OPERATION(__OPERATION__) (((__OPERATION__) == FSMC_WRITE_OPERATION_DISABLE) || \
                                                ((__OPERATION__) == FSMC_WRITE_OPERATION_ENABLE))                        
/**
  * @}
  */

/** @defgroup FSMC_Wait_Signal FSMC Wait Signal
  * @{
  */
  
#define FSMC_WAIT_SIGNAL_DISABLE                 ((uint32_t)0x00000000)
#define FSMC_WAIT_SIGNAL_ENABLE                  ((uint32_t)FSMC_BCRx_WAITEN)

#define IS_FSMC_WAITE_SIGNAL(__SIGNAL__) (((__SIGNAL__) == FSMC_WAIT_SIGNAL_DISABLE) || \
                                          ((__SIGNAL__) == FSMC_WAIT_SIGNAL_ENABLE)) 

/**
  * @}
  */

/** @defgroup FSMC_Extended_Mode FSMC Extended Mode
  * @{
  */
  
#define FSMC_EXTENDED_MODE_DISABLE               ((uint32_t)0x00000000)
#define FSMC_EXTENDED_MODE_ENABLE                ((uint32_t)FSMC_BCRx_EXTMOD)

#define IS_FSMC_EXTENDED_MODE(__MODE__) (((__MODE__) == FSMC_EXTENDED_MODE_DISABLE) || \
                                         ((__MODE__) == FSMC_EXTENDED_MODE_ENABLE))
/**
  * @}
  */

/** @defgroup FSMC_AsynchronousWait FSMC Asynchronous Wait
  * @{
  */
  
#define FSMC_ASYNCHRONOUS_WAIT_DISABLE           ((uint32_t)0x00000000)
#define FSMC_ASYNCHRONOUS_WAIT_ENABLE            ((uint32_t)FSMC_BCRx_ASYNCWAIT)

#define IS_FSMC_ASYNWAIT(__STATE__) (((__STATE__) == FSMC_ASYNCHRONOUS_WAIT_DISABLE) || \
                                     ((__STATE__) == FSMC_ASYNCHRONOUS_WAIT_ENABLE))

/**
  * @}
  */  

/** @defgroup FSMC_Write_Burst FSMC Write Burst
  * @{
  */

#define FSMC_WRITE_BURST_DISABLE                 ((uint32_t)0x00000000)
#define FSMC_WRITE_BURST_ENABLE                  ((uint32_t)FSMC_BCRx_CBURSTRW)

#define IS_FSMC_WRITE_BURST(__BURST__) (((__BURST__) == FSMC_WRITE_BURST_DISABLE) || \
                                        ((__BURST__) == FSMC_WRITE_BURST_ENABLE)) 
/**
  * @}
  */

/** @defgroup FSMC_Address_Setup_Time FSMC Address Setup Time
  * @{
  */
  
#define IS_FSMC_ADDRESS_SETUP_TIME(__TIME__) ((__TIME__) <= 15)
/**
  * @}
  */

/** @defgroup FSMC_Address_Hold_Time FSMC Address Hold Time
  * @{
  */
  
#define IS_FSMC_ADDRESS_HOLD_TIME(__TIME__) (((__TIME__) > 0) && ((__TIME__) <= 15))
/**
  * @}
  */

/** @defgroup FSMC_Data_Setup_Time FSMC Data Setup Time
  * @{
  */
  
#define IS_FSMC_DATASETUP_TIME(__TIME__) (((__TIME__) > 0) && ((__TIME__) <= 255))
/**
  * @}
  */

/** @defgroup FSMC_Bus_Turn_around_Duration FSMC Bus Turn around Duration
  * @{
  */
  
#define IS_FSMC_TURNAROUND_TIME(__TIME__) ((__TIME__) <= 15)
/**
  * @}
  */

/** @defgroup FSMC_CLK_Division FSMC CLK Division
  * @{
  */
  
#define FSMC_CLK_DIV2                        ((uint32_t)0x00000002)
#define FSMC_CLK_DIV3                        ((uint32_t)0x00000003)
#define FSMC_CLK_DIV4                        ((uint32_t)0x00000004)
#define FSMC_CLK_DIV5                        ((uint32_t)0x00000005)
#define FSMC_CLK_DIV6                        ((uint32_t)0x00000006)
#define FSMC_CLK_DIV7                        ((uint32_t)0x00000007)
#define FSMC_CLK_DIV8                        ((uint32_t)0x00000008)
#define FSMC_CLK_DIV9                        ((uint32_t)0x00000009)
#define FSMC_CLK_DIV10                       ((uint32_t)0x0000000A)
#define FSMC_CLK_DIV11                       ((uint32_t)0x0000000B)
#define FSMC_CLK_DIV12                       ((uint32_t)0x0000000C)
#define FSMC_CLK_DIV13                       ((uint32_t)0x0000000D)
#define FSMC_CLK_DIV14                       ((uint32_t)0x0000000E)
#define FSMC_CLK_DIV15                       ((uint32_t)0x0000000F)
#define FSMC_CLK_DIV16                       ((uint32_t)0x00000010)
#define IS_FSMC_CLK_DIV(__DIV__) (((__DIV__) > 1) && ((__DIV__) <= 16))
/**
  * @}
  */

/** @defgroup FSMC_Data_Latency FSMC Data Latency
  * @{
  */
  
#define IS_FSMC_DATA_LATENCY(__LATENCY__) (((__LATENCY__) > 1) && ((__LATENCY__) <= 17))
/**
  * @}
  */  

/** @defgroup FSMC_Access_Mode FSMC Access Mode
  * @{
  */
  
#define FSMC_ACCESS_MODE_A                        ((uint32_t)0x00000000)
#define FSMC_ACCESS_MODE_B                        ((uint32_t)FSMC_BTRx_ACCMOD_0) 
#define FSMC_ACCESS_MODE_C                        ((uint32_t)FSMC_BTRx_ACCMOD_1)
#define FSMC_ACCESS_MODE_D                        ((uint32_t)(FSMC_BTRx_ACCMOD_0 | FSMC_BTRx_ACCMOD_1))

#define IS_FSMC_ACCESS_MODE(__MODE__) (((__MODE__) == FSMC_ACCESS_MODE_A) || \
                                       ((__MODE__) == FSMC_ACCESS_MODE_B) || \
                                       ((__MODE__) == FSMC_ACCESS_MODE_C) || \
                                       ((__MODE__) == FSMC_ACCESS_MODE_D))
/**
  * @}
  */
    
/** @defgroup FSMC_NORSRAM_Device_Instance FSMC NOR/SRAM Device Instance
  * @{
  */
  
#define IS_FSMC_NORSRAM_DEVICE(__INSTANCE__) ((__INSTANCE__) == FSMC_NORSRAM_DEVICE)

/**
  * @}
  */

/** @defgroup FSMC_NORSRAM_EXTENDED_Device_Instance FSMC NOR/SRAM EXTENDED Device Instance
  * @{
  */
  
#define IS_FSMC_NORSRAM_EXTENDED_DEVICE(__INSTANCE__) ((__INSTANCE__) == FSMC_NORSRAM_EXTENDED_DEVICE)

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/** @defgroup FSMC_NOR_Macros FSMC NOR/SRAM Exported Macros
 *  @brief macros to handle NOR device enable/disable and read/write operations
 *  @{
 */
 
/**
  * @brief  Enable the NORSRAM device access.
  * @param  __INSTANCE__: FSMC_NORSRAM Instance
  * @param  __BANK__: FSMC_NORSRAM Bank    
  * @retval none
  */ 
#define __FSMC_NORSRAM_ENABLE(__INSTANCE__, __BANK__)  ((__INSTANCE__)->BTCR[(__BANK__)] |= FSMC_BCRx_MBKEN)

/**
  * @brief  Disable the NORSRAM device access.
  * @param  __INSTANCE__: FSMC_NORSRAM Instance
  * @param  __BANK__: FSMC_NORSRAM Bank   
  * @retval none
  */ 
#define __FSMC_NORSRAM_DISABLE(__INSTANCE__, __BANK__) ((__INSTANCE__)->BTCR[(__BANK__)] &= ~FSMC_BCRx_MBKEN)  

/**
  * @}
  */ 

/* Exported functions --------------------------------------------------------*/

/** @addtogroup FSMC_Exported_Functions
 *  @{
 */

/** @addtogroup HAL_FSMC_NORSRAM_Group1
 *  @{
 */

/* FSMC_NORSRAM Controller functions ******************************************/
/* Initialization/de-initialization functions */
HAL_StatusTypeDef  FSMC_NORSRAM_Init(FSMC_NORSRAM_TYPEDEF *Device, FSMC_NORSRAM_InitTypeDef *Init);
HAL_StatusTypeDef  FSMC_NORSRAM_Timing_Init(FSMC_NORSRAM_TYPEDEF *Device, FSMC_NORSRAM_TimingTypeDef *Timing, uint32_t Bank);
HAL_StatusTypeDef  FSMC_NORSRAM_Extended_Timing_Init(FSMC_NORSRAM_EXTENDED_TYPEDEF *Device, FSMC_NORSRAM_TimingTypeDef *Timing, uint32_t Bank, uint32_t ExtendedMode);
HAL_StatusTypeDef  FSMC_NORSRAM_DeInit(FSMC_NORSRAM_TYPEDEF *Device, FSMC_NORSRAM_EXTENDED_TYPEDEF *ExDevice, uint32_t Bank);

/**
  * @}
  */ 

/** @addtogroup HAL_FSMC_NORSRAM_Group2
 *  @{
 */

/* FSMC_NORSRAM Control functions */
HAL_StatusTypeDef  FSMC_NORSRAM_WriteOperation_Enable(FSMC_NORSRAM_TYPEDEF *Device, uint32_t Bank);
HAL_StatusTypeDef  FSMC_NORSRAM_WriteOperation_Disable(FSMC_NORSRAM_TYPEDEF *Device, uint32_t Bank);

/**
  * @}
  */ 

#endif /* STM32L151xD || STM32L152xD || STM32L162xD */

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

#endif /* __STM32L1xx_LL_FSMC_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
