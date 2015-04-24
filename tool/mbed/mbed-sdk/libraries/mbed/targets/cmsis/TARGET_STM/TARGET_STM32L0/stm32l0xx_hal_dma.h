/**
  ******************************************************************************
  * @file    stm32l0xx_hal_dma.h
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    06-February-2015
  * @brief   Header file of DMA HAL module.
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
#ifndef __STM32L0xx_HAL_DMA_H
#define __STM32L0xx_HAL_DMA_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal_def.h"

/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */

/** @defgroup DMA DMA
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/ 

/** 
  * @brief  DMA Configuration Structure definition  
  */
typedef struct
{
  uint32_t Request;                   /*!< Specifies the request selected for the specified channel. 
                                           This parameter can be a value of @ref DMA_request */
    
  uint32_t Direction;                 /*!< Specifies if the data will be transferred from memory to peripheral, 
                                           from memory to memory or from peripheral to memory.
                                           This parameter can be a value of @ref DMA_Data_transfer_direction */

  uint32_t PeriphInc;                 /*!< Specifies whether the Peripheral address register should be incremented or not.
                                           When Memory to Memory transfer is used, this is the Source Increment mode
                                           This parameter can be a value of @ref DMA_Peripheral_incremented_mode */  

  uint32_t MemInc;                    /*!< Specifies whether the memory address register should be incremented or not.
                                           When Memory to Memory transfer is used, this is the Destination Increment mode
                                           This parameter can be a value of @ref DMA_Memory_incremented_mode */
  
  uint32_t PeriphDataAlignment;       /*!< Specifies the Peripheral data width.
                                           When Memory to Memory transfer is used, this is the Source Alignment format
                                           This parameter can be a value of @ref DMA_Peripheral_data_size */   

  uint32_t MemDataAlignment;          /*!< Specifies the Memory data width.
                                           When Memory to Memory transfer is used, this is the Destination Alignment format
                                           This parameter can be a value of @ref DMA_Memory_data_size */

  uint32_t Mode;                      /*!< Specifies the operation mode of the DMAy Channelx (Normal or Circular).
                                           This parameter can be a value of @ref DMA_mode
                                           @note The circular buffer mode cannot be used if the memory-to-memory
                                                 data transfer is configured on the selected Channel */ 

  uint32_t Priority;                   /*!< Specifies the software priority for the DMAy Channelx.
                                            This parameter can be a value of @ref DMA_Priority_level */
} DMA_InitTypeDef;

/** 
  * @brief DMA Configuration enumeration values definition 
  */  
typedef enum 
{
  DMA_MODE            = 0,      /*!< Control related DMA mode Parameter in DMA_InitTypeDef        */
  DMA_PRIORITY        = 1,      /*!< Control related priority level Parameter in DMA_InitTypeDef  */
  
} DMA_ControlTypeDef;

/** 
  * @brief  HAL DMA State structures definition  
  */ 
typedef enum
{
  HAL_DMA_STATE_RESET             = 0x00,  /*!< DMA not yet initialized or disabled */  
  HAL_DMA_STATE_READY             = 0x01,  /*!< DMA process success and ready for use   */
  HAL_DMA_STATE_BUSY              = 0x02,  /*!< DMA process is ongoing              */     
  HAL_DMA_STATE_TIMEOUT           = 0x03,  /*!< DMA timeout state                   */  
  HAL_DMA_STATE_ERROR             = 0x04,  /*!< DMA error state                     */
  HAL_DMA_STATE_READY_HALF        = 0x05,  /*!< DMA Half process success            */
}HAL_DMA_StateTypeDef;

/** 
  * @brief  HAL DMA Error Code structure definition  
  */ 
typedef enum
{
  HAL_DMA_FULL_TRANSFER      = 0x00,    /*!< Full transfer     */
  HAL_DMA_HALF_TRANSFER      = 0x01,    /*!< Half Transfer     */

}HAL_DMA_LevelCompleteTypeDef;


/** 
  * @brief  DMA handle Structure definition  
  */ 
typedef struct __DMA_HandleTypeDef
{  
  DMA_Channel_TypeDef    *Instance;                                                   /*!< Register base address                  */
  
  DMA_InitTypeDef       Init;                                                         /*!< DMA communication parameters           */ 
  
  HAL_LockTypeDef       Lock;                                                         /*!< DMA locking object                     */  
  
  __IO HAL_DMA_StateTypeDef  State;                                                   /*!< DMA transfer state                     */
  
  void                  *Parent;                                                      /*!< Parent object state                    */  
  
  void                  (* XferCpltCallback)( struct __DMA_HandleTypeDef * hdma);     /*!< DMA transfer complete callback         */
  
  void                  (* XferHalfCpltCallback)( struct __DMA_HandleTypeDef * hdma); /*!< DMA Half transfer complete callback    */

  void                  (* XferErrorCallback)( struct __DMA_HandleTypeDef * hdma);    /*!< DMA transfer error callback            */
  
  __IO uint32_t          ErrorCode;                                                    /*!< DMA Error code                         */
  
} DMA_HandleTypeDef;    

/* Exported constants --------------------------------------------------------*/

/** @defgroup DMA_Exported_Constants DMA Exported Constants
  * @{
  */

/** @defgroup DMA_Error_Code DMA Error Codes
  * @{
  */ 
#define HAL_DMA_ERROR_NONE      ((uint32_t)0x00000000)    /*!< No error             */
#define HAL_DMA_ERROR_TE        ((uint32_t)0x00000001)    /*!< Transfer error       */
#define HAL_DMA_ERROR_TIMEOUT   ((uint32_t)0x00000020)    /*!< Timeout error        */

#define IS_DMA_ALL_PERIPH(PERIPH) (((PERIPH) == DMA1_Channel1) || \
                                   ((PERIPH) == DMA1_Channel2) || \
                                   ((PERIPH) == DMA1_Channel3) || \
                                   ((PERIPH) == DMA1_Channel4) || \
                                   ((PERIPH) == DMA1_Channel5) || \
                                   ((PERIPH) == DMA1_Channel6) || \
                                   ((PERIPH) == DMA1_Channel7))

#define IS_DMA_ALL_CONTROLLER(CONTROLLER) (((CONTROLLER) == DMA1))

/**
  * @}
  */

/** @defgroup DMA_request DMA request defintiions
  * @{
  */ 

#if defined (STM32L071xx) || defined (STM32L072xx) || defined (STM32L073xx) || defined (STM32L081xx) || defined (STM32L082xx) || defined (STM32L083xx)

#define DMA_REQUEST_0                     ((uint32_t)0x00000000)
#define DMA_REQUEST_1                     ((uint32_t)0x00000001)
#define DMA_REQUEST_2                     ((uint32_t)0x00000002)
#define DMA_REQUEST_3                     ((uint32_t)0x00000003)
#define DMA_REQUEST_4                     ((uint32_t)0x00000004)
#define DMA_REQUEST_5                     ((uint32_t)0x00000005)
#define DMA_REQUEST_6                     ((uint32_t)0x00000006)
#define DMA_REQUEST_7                     ((uint32_t)0x00000007)
#define DMA_REQUEST_8                     ((uint32_t)0x00000008)
#define DMA_REQUEST_9                     ((uint32_t)0x00000009)
#define DMA_REQUEST_10                    ((uint32_t)0x0000000A)
#define DMA_REQUEST_11                    ((uint32_t)0x0000000B)
#define DMA_REQUEST_12                    ((uint32_t)0x0000000C)
#define DMA_REQUEST_13                    ((uint32_t)0x0000000D)
#define DMA_REQUEST_14                    ((uint32_t)0x0000000E)
#define DMA_REQUEST_15                    ((uint32_t)0x0000000F)

#define IS_DMA_ALL_REQUEST(REQUEST) (((REQUEST) == DMA_REQUEST_0) || \
                                     ((REQUEST) == DMA_REQUEST_1) || \
                                     ((REQUEST) == DMA_REQUEST_2) || \
                                     ((REQUEST) == DMA_REQUEST_3) || \
                                     ((REQUEST) == DMA_REQUEST_4) || \
                                     ((REQUEST) == DMA_REQUEST_5) || \
                                     ((REQUEST) == DMA_REQUEST_6) || \
                                     ((REQUEST) == DMA_REQUEST_7) || \
                                     ((REQUEST) == DMA_REQUEST_8) || \
                                     ((REQUEST) == DMA_REQUEST_9) || \
                                     ((REQUEST) == DMA_REQUEST_10) || \
                                     ((REQUEST) == DMA_REQUEST_11) || \
                                     ((REQUEST) == DMA_REQUEST_12) || \
                                     ((REQUEST) == DMA_REQUEST_13) || \
                                     ((REQUEST) == DMA_REQUEST_14) || \
                                     ((REQUEST) == DMA_REQUEST_15))

#else /* #if STM32L071xx || STM32L072xx || STM32L073xx || STM32L081xx || STM32L082xx || STM32L083xx */
                                       
#define DMA_REQUEST_0                     ((uint32_t)0x00000000)
#define DMA_REQUEST_1                     ((uint32_t)0x00000001)
#define DMA_REQUEST_2                     ((uint32_t)0x00000002)
#define DMA_REQUEST_3                     ((uint32_t)0x00000003)
#define DMA_REQUEST_4                     ((uint32_t)0x00000004)
#define DMA_REQUEST_5                     ((uint32_t)0x00000005)
#define DMA_REQUEST_6                     ((uint32_t)0x00000006)
#define DMA_REQUEST_7                     ((uint32_t)0x00000007)
#define DMA_REQUEST_8                     ((uint32_t)0x00000008)
#define DMA_REQUEST_9                     ((uint32_t)0x00000009)
#define DMA_REQUEST_11                    ((uint32_t)0x0000000B)

#define IS_DMA_ALL_REQUEST(REQUEST) (((REQUEST) == DMA_REQUEST_0) || \
                                     ((REQUEST) == DMA_REQUEST_1) || \
                                     ((REQUEST) == DMA_REQUEST_2) || \
                                     ((REQUEST) == DMA_REQUEST_3) || \
                                     ((REQUEST) == DMA_REQUEST_4) || \
                                     ((REQUEST) == DMA_REQUEST_5) || \
                                     ((REQUEST) == DMA_REQUEST_6) || \
                                     ((REQUEST) == DMA_REQUEST_7) || \
                                     ((REQUEST) == DMA_REQUEST_8) || \
                                     ((REQUEST) == DMA_REQUEST_9) || \
                                     ((REQUEST) == DMA_REQUEST_11))
#endif /* #if defined (STM32L072xx) || defined (STM32L073xx) || defined (STM32L082xx) || defined (STM32L083xx) */

/**
  * @}
  */

/** @defgroup DMA_Data_transfer_direction DMA Data Transfer directions
  * @{
  */ 
#define DMA_PERIPH_TO_MEMORY         ((uint32_t)0x00000000)        /*!< Peripheral to memory direction */
#define DMA_MEMORY_TO_PERIPH         ((uint32_t)DMA_CCR_DIR)       /*!< Memory to peripheral direction */
#define DMA_MEMORY_TO_MEMORY         ((uint32_t)(DMA_CCR_MEM2MEM)) /*!< Memory to memory direction     */

#define IS_DMA_DIRECTION(DIRECTION) (((DIRECTION) == DMA_PERIPH_TO_MEMORY ) || \
                                     ((DIRECTION) == DMA_MEMORY_TO_PERIPH)  || \
                                     ((DIRECTION) == DMA_MEMORY_TO_MEMORY)) 
/**
  * @}
  */

/** @defgroup DMA_Data_buffer_size
  * @{
  */ 
#define IS_DMA_BUFFER_SIZE(SIZE) (((SIZE) >= 0x1) && ((SIZE) < 0x10000))
/**
  * @}
  */     
    
/** @defgroup DMA_Peripheral_incremented_mode
  * @{
  */ 
#define DMA_PINC_ENABLE        ((uint32_t)DMA_CCR_PINC)  /*!< Peripheral increment mode Enable */
#define DMA_PINC_DISABLE       ((uint32_t)0x00000000)    /*!< Peripheral increment mode Disable */

#define IS_DMA_PERIPHERAL_INC_STATE(STATE) (((STATE) == DMA_PINC_ENABLE) || \
                                            ((STATE) == DMA_PINC_DISABLE))
/**
  * @}
  */ 

/** @defgroup DMA_Memory_incremented_mode
  * @{
  */ 
#define DMA_MINC_ENABLE         ((uint32_t)DMA_CCR_MINC)  /*!< Memory increment mode Enable  */
#define DMA_MINC_DISABLE        ((uint32_t)0x00000000)    /*!< Memory increment mode Disable */

#define IS_DMA_MEMORY_INC_STATE(STATE) (((STATE) == DMA_MINC_ENABLE)  || \
                                        ((STATE) == DMA_MINC_DISABLE))
/**
  * @}
  */

/** @defgroup DMA_Peripheral_data_size
  * @{
  */ 
#define DMA_PDATAALIGN_BYTE          ((uint32_t)0x00000000)       /*!< Peripheral data alignment : Byte     */
#define DMA_PDATAALIGN_HALFWORD      ((uint32_t)DMA_CCR_PSIZE_0)  /*!< Peripheral data alignment : HalfWord */
#define DMA_PDATAALIGN_WORD          ((uint32_t)DMA_CCR_PSIZE_1)  /*!< Peripheral data alignment : Word     */

#define IS_DMA_PERIPHERAL_DATA_SIZE(SIZE) (((SIZE) == DMA_PDATAALIGN_BYTE)     || \
                                           ((SIZE) == DMA_PDATAALIGN_HALFWORD) || \
                                           ((SIZE) == DMA_PDATAALIGN_WORD))
/**
  * @}
  */ 


/** @defgroup DMA_Memory_data_size
  * @{ 
  */
#define DMA_MDATAALIGN_BYTE          ((uint32_t)0x00000000)       /*!< Memory data alignment : Byte     */
#define DMA_MDATAALIGN_HALFWORD      ((uint32_t)DMA_CCR_MSIZE_0)  /*!< Memory data alignment : HalfWord */
#define DMA_MDATAALIGN_WORD          ((uint32_t)DMA_CCR_MSIZE_1)  /*!< Memory data alignment : Word     */

#define IS_DMA_MEMORY_DATA_SIZE(SIZE) (((SIZE) == DMA_MDATAALIGN_BYTE)     || \
                                       ((SIZE) == DMA_MDATAALIGN_HALFWORD) || \
                                       ((SIZE) == DMA_MDATAALIGN_WORD ))
/**
  * @}
  */

/** @defgroup DMA_mode
  * @{
  */ 
#define DMA_NORMAL         ((uint32_t)0x00000000)       /*!< Normal Mode                  */
#define DMA_CIRCULAR       ((uint32_t)DMA_CCR_CIRC)    /*!< Circular Mode                */

#define IS_DMA_MODE(MODE) (((MODE) == DMA_NORMAL )  || \
                           ((MODE) == DMA_CIRCULAR)) 
/**
  * @}
  */

/** @defgroup DMA_Priority_level
  * @{
  */
#define DMA_PRIORITY_LOW             ((uint32_t)0x00000000)    /*!< Priority level : Low       */
#define DMA_PRIORITY_MEDIUM          ((uint32_t)DMA_CCR_PL_0)  /*!< Priority level : Medium    */
#define DMA_PRIORITY_HIGH            ((uint32_t)DMA_CCR_PL_1)  /*!< Priority level : High      */
#define DMA_PRIORITY_VERY_HIGH       ((uint32_t)DMA_CCR_PL)    /*!< Priority level : Very_High */

#define IS_DMA_PRIORITY(PRIORITY) (((PRIORITY) == DMA_PRIORITY_LOW )   || \
                                   ((PRIORITY) == DMA_PRIORITY_MEDIUM) || \
                                   ((PRIORITY) == DMA_PRIORITY_HIGH)   || \
                                   ((PRIORITY) == DMA_PRIORITY_VERY_HIGH)) 
/**
  * @}
  */ 


/** @defgroup DMA_interrupt_enable_definitions
  * @{
  */

#define DMA_IT_TC                         ((uint32_t)DMA_CCR_TCIE)
#define DMA_IT_HT                         ((uint32_t)DMA_CCR_HTIE)
#define DMA_IT_TE                         ((uint32_t)DMA_CCR_TEIE)

/**
  * @}
  */

/** @defgroup DMA_flag_definitions
  * @{
  */ 

#define DMA_FLAG_GL1                      ((uint32_t)0x00000001)
#define DMA_FLAG_TC1                      ((uint32_t)0x00000002)
#define DMA_FLAG_HT1                      ((uint32_t)0x00000004)
#define DMA_FLAG_TE1                      ((uint32_t)0x00000008)
#define DMA_FLAG_GL2                      ((uint32_t)0x00000010)
#define DMA_FLAG_TC2                      ((uint32_t)0x00000020)
#define DMA_FLAG_HT2                      ((uint32_t)0x00000040)
#define DMA_FLAG_TE2                      ((uint32_t)0x00000080)
#define DMA_FLAG_GL3                      ((uint32_t)0x00000100)
#define DMA_FLAG_TC3                      ((uint32_t)0x00000200)
#define DMA_FLAG_HT3                      ((uint32_t)0x00000400)
#define DMA_FLAG_TE3                      ((uint32_t)0x00000800)
#define DMA_FLAG_GL4                      ((uint32_t)0x00001000)
#define DMA_FLAG_TC4                      ((uint32_t)0x00002000)
#define DMA_FLAG_HT4                      ((uint32_t)0x00004000)
#define DMA_FLAG_TE4                      ((uint32_t)0x00008000)
#define DMA_FLAG_GL5                      ((uint32_t)0x00010000)
#define DMA_FLAG_TC5                      ((uint32_t)0x00020000)
#define DMA_FLAG_HT5                      ((uint32_t)0x00040000)
#define DMA_FLAG_TE5                      ((uint32_t)0x00080000)
#define DMA_FLAG_GL6                      ((uint32_t)0x00100000)
#define DMA_FLAG_TC6                      ((uint32_t)0x00200000)
#define DMA_FLAG_HT6                      ((uint32_t)0x00400000)
#define DMA_FLAG_TE6                      ((uint32_t)0x00800000)
#define DMA_FLAG_GL7                      ((uint32_t)0x01000000)
#define DMA_FLAG_TC7                      ((uint32_t)0x02000000)
#define DMA_FLAG_HT7                      ((uint32_t)0x04000000)
#define DMA_FLAG_TE7                      ((uint32_t)0x08000000)


/**
  * @}
  */

/**
  * @}
  */  
   
/* Exported macro ------------------------------------------------------------*/

/** @defgroup DMA_Exported_Macros DMA Exported Macros
 * @{
 */  

/** @brief Reset DMA handle state
  * @param  __HANDLE__: DMA handle
  * @retval None
  */
#define __HAL_DMA_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_DMA_STATE_RESET)

/**
  * @brief  Enable the specified DMA Channel.
  * @param  __HANDLE__: DMA handle
  * @retval None.
  */
#define __HAL_DMA_ENABLE(__HANDLE__)        ((__HANDLE__)->Instance->CCR |=  DMA_CCR_EN)

/**
  * @brief  Disable the specified DMA Channel.
  * @param  __HANDLE__: DMA handle
  * @retval None.
  */
#define __HAL_DMA_DISABLE(__HANDLE__)       ((__HANDLE__)->Instance->CCR &=  ~DMA_CCR_EN)


/* Interrupt & Flag management */

/**
  * @brief  Returns the current DMA Channel transfer complete flag.
  * @param  __HANDLE__: DMA handle
  * @retval The specified transfer complete flag index.
  */

#define __HAL_DMA_GET_TC_FLAG_INDEX(__HANDLE__) \
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel1))? DMA_FLAG_TC1 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel2))? DMA_FLAG_TC2 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel3))? DMA_FLAG_TC3 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel4))? DMA_FLAG_TC4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel5))? DMA_FLAG_TC5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel6))? DMA_FLAG_TC6 :\
   DMA_FLAG_TC7)

/**
  * @brief  Returns the current DMA Channel half transfer complete flag.
  * @param  __HANDLE__: DMA handle
  * @retval The specified half transfer complete flag index.
  */      
#define __HAL_DMA_GET_HT_FLAG_INDEX(__HANDLE__)\
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel1))? DMA_FLAG_HT1 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel2))? DMA_FLAG_HT2 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel3))? DMA_FLAG_HT3 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel4))? DMA_FLAG_HT4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel5))? DMA_FLAG_HT5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel6))? DMA_FLAG_HT6 :\
   DMA_FLAG_HT7)

/**
  * @brief  Returns the current DMA Channel transfer error flag.
  * @param  __HANDLE__: DMA handle
  * @retval The specified transfer error flag index.
  */
#define __HAL_DMA_GET_TE_FLAG_INDEX(__HANDLE__)\
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel1))? DMA_FLAG_TE1 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel2))? DMA_FLAG_TE2 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel3))? DMA_FLAG_TE3 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel4))? DMA_FLAG_TE4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel5))? DMA_FLAG_TE5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel6))? DMA_FLAG_TE6 :\
   DMA_FLAG_TE7)

/**
  * @brief  Returns the current DMA Channel Global interrupt flag.
  * @param  __HANDLE__: DMA handle
  * @retval The specified transfer error flag index.
  */
#define __HAL_DMA_GET_GI_FLAG_INDEX(__HANDLE__)\
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel1))? DMA_ISR_GIF1 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel2))? DMA_ISR_GIF2 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel3))? DMA_ISR_GIF3 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel4))? DMA_ISR_GIF4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel5))? DMA_ISR_GIF5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel6))? DMA_ISR_GIF6 :\
   DMA_ISR_GIF7)
/**
  * @brief  Get the DMA Channel pending flags.
  * @param  __HANDLE__: DMA handle
  * @param  __FLAG__: Get the specified flag.
  *          This parameter can be any combination of the following values:
  *            @arg DMA_FLAG_TCIFx:  Transfer complete flag
  *            @arg DMA_FLAG_HTIFx:  Half transfer complete flag
  *            @arg DMA_FLAG_TEIFx:  Transfer error flag
  *            @arg DMA_ISR_GIFx: Global interrupt flag
  *         Where x can be 0_4, 1_5, 2_6 or 3_7 to select the DMA Channel flag.   
  * @retval The state of FLAG (SET or RESET).
  */
#define __HAL_DMA_GET_FLAG(__HANDLE__, __FLAG__) (DMA1->ISR & (__FLAG__))

/**
  * @brief  Clears the DMA Channel pending flags.
  * @param  __HANDLE__: DMA handle
  * @param  __FLAG__: specifies the flag to clear.
  *          This parameter can be any combination of the following values:
  *            @arg DMA_FLAG_TCIFx:  Transfer complete flag
  *            @arg DMA_FLAG_HTIFx:  Half transfer complete flag
  *            @arg DMA_FLAG_TEIFx:  Transfer error flag
  *            @arg DMA_ISR_GIFx: Global interrupt flag
  *         Where x can be 0_4, 1_5, 2_6 or 3_7 to select the DMA Channel flag.   
  * @retval None
  */
#define __HAL_DMA_CLEAR_FLAG(__HANDLE__, __FLAG__) (DMA1->IFCR = (__FLAG__))

/**
  * @brief  Enables the specified DMA Channel interrupts.
  * @param  __HANDLE__: DMA handle
  * @param __INTERRUPT__: specifies the DMA interrupt sources to be enabled or disabled. 
  *          This parameter can be any combination of the following values:
  *            @arg DMA_IT_TC:  Transfer complete interrupt mask
  *            @arg DMA_IT_HT:  Half transfer complete interrupt mask
  *            @arg DMA_IT_TE:  Transfer error interrupt mask
  * @retval None
  */
#define __HAL_DMA_ENABLE_IT(__HANDLE__, __INTERRUPT__)   ((__HANDLE__)->Instance->CCR |= (__INTERRUPT__))

/**
  * @brief  Disables the specified DMA Channel interrupts.
  * @param  __HANDLE__: DMA handle
  * @param __INTERRUPT__: specifies the DMA interrupt sources to be enabled or disabled. 
  *          This parameter can be any combination of the following values:
  *            @arg DMA_IT_TC:  Transfer complete interrupt mask
  *            @arg DMA_IT_HT:  Half transfer complete interrupt mask
  *            @arg DMA_IT_TE:  Transfer error interrupt mask
  * @retval None
  */
#define __HAL_DMA_DISABLE_IT(__HANDLE__, __INTERRUPT__)  ((__HANDLE__)->Instance->CCR &= ~(__INTERRUPT__))

/**
  * @brief  Checks whether the specified DMA Channel interrupt has occurred or not.
  * @param  __HANDLE__: DMA handle
  * @param  __INTERRUPT__: specifies the DMA interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg DMA_IT_TC:  Transfer complete interrupt mask
  *            @arg DMA_IT_HT:  Half transfer complete interrupt mask
  *            @arg DMA_IT_TE:  Transfer error interrupt mask
  * @retval The state of DMA_IT (SET or RESET).
  */
#define __HAL_DMA_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)  (((__HANDLE__)->Instance->CCR & (__INTERRUPT__)))

/**
  * @}
  */  

/* Exported functions --------------------------------------------------------*/

/** @defgroup DMA_Exported_Functions DMA Exported Functions
  * @{
  */

/** @defgroup DMA_Exported_Functions_Group1 Initialization/de-initialization functions
  * @{
  */

/* Initialization and de-initialization functions *****************************/
HAL_StatusTypeDef HAL_DMA_Init(DMA_HandleTypeDef *hdma); 
HAL_StatusTypeDef HAL_DMA_DeInit (DMA_HandleTypeDef *hdma);

/**
  * @}
  */

/** @defgroup DMA_Exported_Functions_Group2 I/O operation functions
  * @{
  */

/* IO operation functions *****************************************************/
HAL_StatusTypeDef HAL_DMA_Start (DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength);
HAL_StatusTypeDef HAL_DMA_Start_IT(DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength);
HAL_StatusTypeDef HAL_DMA_Abort(DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMA_PollForTransfer(DMA_HandleTypeDef *hdma, uint32_t CompleteLevel, uint32_t Timeout);
void HAL_DMA_IRQHandler(DMA_HandleTypeDef *hdma);
/**
  * @}
  */

/** @defgroup DMA_Exported_Functions_Group3 Peripheral State functions
  * @{
  */

/* Peripheral State and Error functions ***************************************/
HAL_DMA_StateTypeDef HAL_DMA_GetState(DMA_HandleTypeDef *hdma);
uint32_t             HAL_DMA_GetError(DMA_HandleTypeDef *hdma);

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

#endif /* __STM32L0xx_HAL_DMA_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

