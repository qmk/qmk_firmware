/**
  ******************************************************************************
  * @file    stm32f1xx_ll_fsmc.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    15-December-2014
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
#ifndef __STM32F1xx_LL_FSMC_H
#define __STM32F1xx_LL_FSMC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal_def.h"

/** @addtogroup STM32F1xx_HAL_Driver
  * @{
  */

#if defined (STM32F101xE) || defined(STM32F103xE) || defined(STM32F101xG) || defined(STM32F103xG) || defined(STM32F100xE)

/** @addtogroup FSMC_LL
  * @{
  */ 

/** @addtogroup FSMC_LL_Private_Macros
  * @{
  */

#define IS_FSMC_NORSRAM_BANK(__BANK__) (((__BANK__) == FSMC_NORSRAM_BANK1) || \
                                        ((__BANK__) == FSMC_NORSRAM_BANK2) || \
                                        ((__BANK__) == FSMC_NORSRAM_BANK3) || \
                                        ((__BANK__) == FSMC_NORSRAM_BANK4))

#define IS_FSMC_MUX(__MUX__) (((__MUX__) == FSMC_DATA_ADDRESS_MUX_DISABLE) || \
                              ((__MUX__) == FSMC_DATA_ADDRESS_MUX_ENABLE))

#define IS_FSMC_MEMORY(__MEMORY__) (((__MEMORY__) == FSMC_MEMORY_TYPE_SRAM) || \
                                    ((__MEMORY__) == FSMC_MEMORY_TYPE_PSRAM)|| \
                                    ((__MEMORY__) == FSMC_MEMORY_TYPE_NOR))

#define IS_FSMC_NORSRAM_MEMORY_WIDTH(__WIDTH__) (((__WIDTH__) == FSMC_NORSRAM_MEM_BUS_WIDTH_8)  || \
                                                 ((__WIDTH__) == FSMC_NORSRAM_MEM_BUS_WIDTH_16) || \
                                                 ((__WIDTH__) == FSMC_NORSRAM_MEM_BUS_WIDTH_32))

#define IS_FSMC_ACCESS_MODE(__MODE__) (((__MODE__) == FSMC_ACCESS_MODE_A) || \
                                       ((__MODE__) == FSMC_ACCESS_MODE_B) || \
                                       ((__MODE__) == FSMC_ACCESS_MODE_C) || \
                                       ((__MODE__) == FSMC_ACCESS_MODE_D))

#define IS_FSMC_NAND_BANK(BANK) (((BANK) == FSMC_NAND_BANK2) || \
                                ((BANK) == FSMC_NAND_BANK3))

#define IS_FSMC_WAIT_FEATURE(FEATURE) (((FEATURE) == FSMC_NAND_PCC_WAIT_FEATURE_DISABLE) || \
                                      ((FEATURE) == FSMC_NAND_PCC_WAIT_FEATURE_ENABLE))

#define IS_FSMC_NAND_MEMORY_WIDTH(WIDTH) (((WIDTH) == FSMC_NAND_PCC_MEM_BUS_WIDTH_8) || \
                                         ((WIDTH) == FSMC_NAND_PCC_MEM_BUS_WIDTH_16))
                                         
#define IS_FSMC_ECC_STATE(STATE) (((STATE) == FSMC_NAND_ECC_DISABLE) || \
                                 ((STATE) == FSMC_NAND_ECC_ENABLE))
                                 
#define IS_FSMC_ECCPAGE_SIZE(SIZE) (((SIZE) == FSMC_NAND_ECC_PAGE_SIZE_256BYTE)  || \
                                   ((SIZE) == FSMC_NAND_ECC_PAGE_SIZE_512BYTE)  || \
                                   ((SIZE) == FSMC_NAND_ECC_PAGE_SIZE_1024BYTE) || \
                                   ((SIZE) == FSMC_NAND_ECC_PAGE_SIZE_2048BYTE) || \
                                   ((SIZE) == FSMC_NAND_ECC_PAGE_SIZE_4096BYTE) || \
                                   ((SIZE) == FSMC_NAND_ECC_PAGE_SIZE_8192BYTE))
/** @defgroup FSMC_TCLR_Setup_Time FSMC_TCLR_Setup_Time 
  * @{
  */
#define IS_FSMC_TCLR_TIME(TIME) ((TIME) <= 255)
/**
  * @}
  */

/** @defgroup FSMC_TAR_Setup_Time FSMC_TAR_Setup_Time 
  * @{
  */
#define IS_FSMC_TAR_TIME(TIME) ((TIME) <= 255)
/**
  * @}
  */

/** @defgroup FSMC_Setup_Time FSMC_Setup_Time 
  * @{
  */
#define IS_FSMC_SETUP_TIME(TIME) ((TIME) <= 255)
/**
  * @}
  */

/** @defgroup FSMC_Wait_Setup_Time FSMC_Wait_Setup_Time 
  * @{
  */
#define IS_FSMC_WAIT_TIME(TIME) ((TIME) <= 255)
/**
  * @}
  */

/** @defgroup FSMC_Hold_Setup_Time FSMC_Hold_Setup_Time 
  * @{
  */
#define IS_FSMC_HOLD_TIME(TIME) ((TIME) <= 255)
/**
  * @}
  */

/** @defgroup FSMC_HiZ_Setup_Time FSMC_HiZ_Setup_Time
  * @{
  */
#define IS_FSMC_HIZ_TIME(TIME) ((TIME) <= 255)
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

/** @defgroup FSMC_NAND_Device_Instance FSMC_NAND_Device_Instance
  * @{
  */
#define IS_FSMC_NAND_DEVICE(INSTANCE) ((INSTANCE) == FSMC_NAND_DEVICE)
/**
  * @}
  */  

/** @defgroup FSMC_PCCARD_Device_Instance FSMC_PCCARD_Device_Instance
  * @{
  */
#define IS_FSMC_PCCARD_DEVICE(INSTANCE) ((INSTANCE) == FSMC_PCCARD_DEVICE)

/**
  * @}
  */ 

#define IS_FSMC_BURSTMODE(__STATE__) (((__STATE__) == FSMC_BURST_ACCESS_MODE_DISABLE) || \
                                      ((__STATE__) == FSMC_BURST_ACCESS_MODE_ENABLE))

#define IS_FSMC_WAIT_POLARITY(__POLARITY__) (((__POLARITY__) == FSMC_WAIT_SIGNAL_POLARITY_LOW) || \
                                             ((__POLARITY__) == FSMC_WAIT_SIGNAL_POLARITY_HIGH))

#define IS_FSMC_WRAP_MODE(__MODE__) (((__MODE__) == FSMC_WRAP_MODE_DISABLE) || \
                                     ((__MODE__) == FSMC_WRAP_MODE_ENABLE)) 

#define IS_FSMC_WAIT_SIGNAL_ACTIVE(__ACTIVE__) (((__ACTIVE__) == FSMC_WAIT_TIMING_BEFORE_WS) || \
                                                ((__ACTIVE__) == FSMC_WAIT_TIMING_DURING_WS)) 

#define IS_FSMC_WRITE_OPERATION(__OPERATION__) (((__OPERATION__) == FSMC_WRITE_OPERATION_DISABLE) || \
                                                ((__OPERATION__) == FSMC_WRITE_OPERATION_ENABLE))                        

#define IS_FSMC_WAITE_SIGNAL(__SIGNAL__) (((__SIGNAL__) == FSMC_WAIT_SIGNAL_DISABLE) || \
                                          ((__SIGNAL__) == FSMC_WAIT_SIGNAL_ENABLE)) 

#define IS_FSMC_EXTENDED_MODE(__MODE__) (((__MODE__) == FSMC_EXTENDED_MODE_DISABLE) || \
                                         ((__MODE__) == FSMC_EXTENDED_MODE_ENABLE))

#define IS_FSMC_ASYNWAIT(__STATE__) (((__STATE__) == FSMC_ASYNCHRONOUS_WAIT_DISABLE) || \
                                     ((__STATE__) == FSMC_ASYNCHRONOUS_WAIT_ENABLE))

#define IS_FSMC_CLK_DIV(DIV) (((DIV) > 1) && ((DIV) <= 16))

/** @defgroup FSMC_Data_Latency FSMC Data Latency
  * @{
  */
  
#define IS_FSMC_DATA_LATENCY(__LATENCY__) (((__LATENCY__) > 1) && ((__LATENCY__) <= 17))
/**
  * @}
  */  

#define IS_FSMC_WRITE_BURST(__BURST__) (((__BURST__) == FSMC_WRITE_BURST_DISABLE) || \
                                        ((__BURST__) == FSMC_WRITE_BURST_ENABLE)) 
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

/**
  * @}
  */

/* Exported typedef ----------------------------------------------------------*/ 

/** @defgroup FSMC_NORSRAM_Exported_typedef FSMC Low Layer Exported Types
  * @{
  */ 
  
#define FSMC_NORSRAM_TypeDef            FSMC_Bank1_TypeDef
#define FSMC_NORSRAM_EXTENDED_TypeDef   FSMC_Bank1E_TypeDef
#define FSMC_NAND_TypeDef               FSMC_Bank2_3_TypeDef
#define FSMC_PCCARD_TypeDef             FSMC_Bank4_TypeDef

#define FSMC_NORSRAM_DEVICE             FSMC_Bank1            
#define FSMC_NORSRAM_EXTENDED_DEVICE    FSMC_Bank1E   
#define FSMC_NAND_DEVICE                FSMC_Bank2_3             
#define FSMC_PCCARD_DEVICE              FSMC_Bank4             

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

#if defined (STM32F101xE) || defined(STM32F103xE) || defined(STM32F101xG) || defined(STM32F103xG)
/** 
  * @brief  FSMC_NAND Configuration Structure definition  
  */ 
typedef struct
{
  uint32_t NandBank;               /*!< Specifies the NAND memory device that will be used.
                                        This parameter can be a value of @ref FSMC_NAND_Bank                    */           
  
  uint32_t Waitfeature;            /*!< Enables or disables the Wait feature for the NAND Memory device.
                                        This parameter can be any value of @ref FSMC_Wait_feature               */
  
  uint32_t MemoryDataWidth;        /*!< Specifies the external memory device width.
                                        This parameter can be any value of @ref FSMC_NAND_Data_Width            */
  
  uint32_t EccComputation;         /*!< Enables or disables the ECC computation.
                                        This parameter can be any value of @ref FSMC_ECC                        */
  
  uint32_t ECCPageSize;            /*!< Defines the page size for the extended ECC.
                                        This parameter can be any value of @ref FSMC_ECC_Page_Size              */
  
  uint32_t TCLRSetupTime;          /*!< Defines the number of HCLK cycles to configure the
                                        delay between CLE low and RE low.
                                        This parameter can be a value between Min_Data = 0 and Max_Data = 255  */
  
  uint32_t TARSetupTime;           /*!< Defines the number of HCLK cycles to configure the
                                        delay between ALE low and RE low.
                                        This parameter can be a number between Min_Data = 0 and Max_Data = 255 */
                                     
}FSMC_NAND_InitTypeDef;  

/** 
  * @brief  FSMC_NAND_PCCARD Timing parameters structure definition
  */
typedef struct
{
  uint32_t SetupTime;            /*!< Defines the number of HCLK cycles to setup address before
                                      the command assertion for NAND-Flash read or write access
                                      to common/Attribute or I/O memory space (depending on
                                      the memory space timing to be configured).
                                      This parameter can be a value between Min_Data = 0 and Max_Data = 255    */
  
  uint32_t WaitSetupTime;        /*!< Defines the minimum number of HCLK cycles to assert the
                                      command for NAND-Flash read or write access to
                                      common/Attribute or I/O memory space (depending on the
                                      memory space timing to be configured). 
                                      This parameter can be a number between Min_Data = 0 and Max_Data = 255   */
  
  uint32_t HoldSetupTime;        /*!< Defines the number of HCLK clock cycles to hold address
                                      (and data for write access) after the command de-assertion
                                      for NAND-Flash read or write access to common/Attribute
                                      or I/O memory space (depending on the memory space timing
                                      to be configured).
                                      This parameter can be a number between Min_Data = 0 and Max_Data = 255   */
  
  uint32_t HiZSetupTime;         /*!< Defines the number of HCLK clock cycles during which the
                                      data bus is kept in HiZ after the start of a NAND-Flash
                                      write access to common/Attribute or I/O memory space (depending
                                      on the memory space timing to be configured).
                                      This parameter can be a number between Min_Data = 0 and Max_Data = 255   */
  
}FSMC_NAND_PCC_TimingTypeDef;

/** 
  * @brief  FSMC_NAND Configuration Structure definition  
  */ 
typedef struct
{
  uint32_t Waitfeature;            /*!< Enables or disables the Wait feature for the PCCARD Memory device.
                                        This parameter can be any value of @ref FSMC_Wait_feature               */
  
  uint32_t TCLRSetupTime;          /*!< Defines the number of HCLK cycles to configure the
                                        delay between CLE low and RE low.
                                        This parameter can be a value between Min_Data = 0 and Max_Data = 255  */
  
  uint32_t TARSetupTime;           /*!< Defines the number of HCLK cycles to configure the
                                        delay between ALE low and RE low.
                                        This parameter can be a number between Min_Data = 0 and Max_Data = 255 */
                                     
}FSMC_PCCARD_InitTypeDef;  

#endif /* STM32F101xE || STM32F103xE || STM32F101xG || STM32F103xG */
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup FSMC_Exported_Constants FSMC Low Layer Exported Constants
  * @{
  */ 
  
/** @defgroup FSMC_NORSRAM_Exported_constants FSMC NOR/SRAM Exported constants
  * @{
  */ 
  
/** @defgroup FSMC_NORSRAM_Bank FSMC NOR/SRAM Bank
  * @{
  */
#define FSMC_NORSRAM_BANK1                       ((uint32_t)0x00000000)
#define FSMC_NORSRAM_BANK2                       ((uint32_t)0x00000002)
#define FSMC_NORSRAM_BANK3                       ((uint32_t)0x00000004)
#define FSMC_NORSRAM_BANK4                       ((uint32_t)0x00000006)

/**
  * @}
  */

/** @defgroup FSMC_Data_Address_Bus_Multiplexing FSMC Data Address Bus Multiplexing
  * @{
  */

#define FSMC_DATA_ADDRESS_MUX_DISABLE            ((uint32_t)0x00000000)
#define FSMC_DATA_ADDRESS_MUX_ENABLE             ((uint32_t)FSMC_BCRx_MUXEN)

/**
  * @}
  */

/** @defgroup FSMC_Memory_Type FSMC Memory Type
  * @{
  */

#define FSMC_MEMORY_TYPE_SRAM                    ((uint32_t)0x00000000)
#define FSMC_MEMORY_TYPE_PSRAM                   ((uint32_t)FSMC_BCRx_MTYP_0)
#define FSMC_MEMORY_TYPE_NOR                     ((uint32_t)FSMC_BCRx_MTYP_1)


/**
  * @}
  */

/** @defgroup FSMC_NORSRAM_Data_Width FSMC NOR/SRAM Data Width
  * @{
  */

#define FSMC_NORSRAM_MEM_BUS_WIDTH_8             ((uint32_t)0x00000000)
#define FSMC_NORSRAM_MEM_BUS_WIDTH_16            ((uint32_t)FSMC_BCRx_MWID_0)
#define FSMC_NORSRAM_MEM_BUS_WIDTH_32            ((uint32_t)FSMC_BCRx_MWID_1)

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

/**
  * @}
  */
    

/** @defgroup FSMC_Wait_Signal_Polarity FSMC Wait Signal Polarity
  * @{
  */
  
#define FSMC_WAIT_SIGNAL_POLARITY_LOW            ((uint32_t)0x00000000)
#define FSMC_WAIT_SIGNAL_POLARITY_HIGH           ((uint32_t)FSMC_BCRx_WAITPOL)

/**
  * @}
  */

/** @defgroup FSMC_Wrap_Mode FSMC Wrap Mode
  * @{
  */
  
#define FSMC_WRAP_MODE_DISABLE                   ((uint32_t)0x00000000)
#define FSMC_WRAP_MODE_ENABLE                    ((uint32_t)FSMC_BCRx_WRAPMOD)

/**
  * @}
  */

/** @defgroup FSMC_Wait_Timing FSMC Wait Timing
  * @{
  */
  
#define FSMC_WAIT_TIMING_BEFORE_WS               ((uint32_t)0x00000000)
#define FSMC_WAIT_TIMING_DURING_WS               ((uint32_t)FSMC_BCRx_WAITCFG)

/**
  * @}
  */

/** @defgroup FSMC_Write_Operation FSMC Write Operation
  * @{
  */
  
#define FSMC_WRITE_OPERATION_DISABLE             ((uint32_t)0x00000000)
#define FSMC_WRITE_OPERATION_ENABLE              ((uint32_t)FSMC_BCRx_WREN)

/**
  * @}
  */

/** @defgroup FSMC_Wait_Signal FSMC Wait Signal
  * @{
  */
  
#define FSMC_WAIT_SIGNAL_DISABLE                 ((uint32_t)0x00000000)
#define FSMC_WAIT_SIGNAL_ENABLE                  ((uint32_t)FSMC_BCRx_WAITEN)

/**
  * @}
  */

/** @defgroup FSMC_Extended_Mode FSMC Extended Mode
  * @{
  */
  
#define FSMC_EXTENDED_MODE_DISABLE               ((uint32_t)0x00000000)
#define FSMC_EXTENDED_MODE_ENABLE                ((uint32_t)FSMC_BCRx_EXTMOD)

/**
  * @}
  */

/** @defgroup FSMC_AsynchronousWait FSMC Asynchronous Wait
  * @{
  */
  
#define FSMC_ASYNCHRONOUS_WAIT_DISABLE           ((uint32_t)0x00000000)
#define FSMC_ASYNCHRONOUS_WAIT_ENABLE            ((uint32_t)FSMC_BCRx_ASYNCWAIT)

/**
  * @}
  */  

/** @defgroup FSMC_Write_Burst FSMC Write Burst
  * @{
  */

#define FSMC_WRITE_BURST_DISABLE                 ((uint32_t)0x00000000)
#define FSMC_WRITE_BURST_ENABLE                  ((uint32_t)FSMC_BCRx_CBURSTRW)

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

/**
  * @}
  */
    

/**
  * @}
  */

#if defined (STM32F101xE) || defined(STM32F103xE) || defined(STM32F101xG) || defined(STM32F103xG)
/** @defgroup FSMC_NAND_Controller FSMC NAND and PCCARD Controller
  * @{
  */

/** @defgroup FSMC_NAND_Bank FSMC_NAND_Bank
  * @{
  */  
#define FSMC_NAND_BANK2                          ((uint32_t)0x00000010)
#define FSMC_NAND_BANK3                          ((uint32_t)0x00000100)

/**
  * @}
  */

/** @defgroup FSMC_Wait_feature FSMC_Wait_feature
  * @{
  */
#define FSMC_NAND_PCC_WAIT_FEATURE_DISABLE           ((uint32_t)0x00000000)
#define FSMC_NAND_PCC_WAIT_FEATURE_ENABLE            ((uint32_t)0x00000002)

/**
  * @}
  */

/** @defgroup FSMC_PCR_Memory_Type FSMC_PCR_Memory_Type
  * @{
  */
#define FSMC_PCR_MEMORY_TYPE_PCCARD        ((uint32_t)0x00000000)
#define FSMC_PCR_MEMORY_TYPE_NAND          ((uint32_t)FSMC_PCRx_PTYP)
/**
  * @}
  */

/** @defgroup FSMC_NAND_Data_Width FSMC_NAND_Data_Width
  * @{
  */
#define FSMC_NAND_PCC_MEM_BUS_WIDTH_8                ((uint32_t)0x00000000)
#define FSMC_NAND_PCC_MEM_BUS_WIDTH_16               ((uint32_t)FSMC_PCRx_PWID_0)

/**
  * @}
  */

/** @defgroup FSMC_ECC FSMC_ECC
  * @{
  */
#define FSMC_NAND_ECC_DISABLE                    ((uint32_t)0x00000000)
#define FSMC_NAND_ECC_ENABLE                     ((uint32_t)FSMC_PCRx_ECCEN)

/**
  * @}
  */

/** @defgroup FSMC_ECC_Page_Size FSMC_ECC_Page_Size
  * @{
  */
#define FSMC_NAND_ECC_PAGE_SIZE_256BYTE          ((uint32_t)0x00000000)
#define FSMC_NAND_ECC_PAGE_SIZE_512BYTE          ((uint32_t)FSMC_PCRx_ECCPS_0)
#define FSMC_NAND_ECC_PAGE_SIZE_1024BYTE         ((uint32_t)FSMC_PCRx_ECCPS_1)
#define FSMC_NAND_ECC_PAGE_SIZE_2048BYTE         ((uint32_t)FSMC_PCRx_ECCPS_0|FSMC_PCRx_ECCPS_1)
#define FSMC_NAND_ECC_PAGE_SIZE_4096BYTE         ((uint32_t)FSMC_PCRx_ECCPS_2)
#define FSMC_NAND_ECC_PAGE_SIZE_8192BYTE         ((uint32_t)FSMC_PCRx_ECCPS_0|FSMC_PCRx_ECCPS_2)

/**
  * @}
  */

/** @defgroup FSMC_Interrupt_definition FSMC_Interrupt_definition
  * @brief FSMC Interrupt definition
  * @{
  */  
#define FSMC_IT_RISING_EDGE                ((uint32_t)FSMC_SRx_IREN)
#define FSMC_IT_LEVEL                      ((uint32_t)FSMC_SRx_ILEN)
#define FSMC_IT_FALLING_EDGE               ((uint32_t)FSMC_SRx_IFEN)

/**
  * @}
  */
    
/** @defgroup FSMC_Flag_definition FSMC_Flag_definition
  * @brief FSMC Flag definition
  * @{
  */ 
#define FSMC_FLAG_RISING_EDGE                    ((uint32_t)FSMC_SRx_IRS)
#define FSMC_FLAG_LEVEL                          ((uint32_t)FSMC_SRx_ILS)
#define FSMC_FLAG_FALLING_EDGE                   ((uint32_t)FSMC_SRx_IFS)
#define FSMC_FLAG_FEMPT                          ((uint32_t)FSMC_SRx_FEMPT)

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

/* Exported macro ------------------------------------------------------------*/

/** @defgroup FSMC_Exported_Macros FSMC Low Layer Exported Macros
  * @{
  */ 
  
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
#define __FSMC_NORSRAM_ENABLE(__INSTANCE__, __BANK__)  SET_BIT((__INSTANCE__)->BTCR[(__BANK__)], FSMC_BCRx_MBKEN)

/**
  * @brief  Disable the NORSRAM device access.
  * @param  __INSTANCE__: FSMC_NORSRAM Instance
  * @param  __BANK__: FSMC_NORSRAM Bank   
  * @retval none
  */ 
#define __FSMC_NORSRAM_DISABLE(__INSTANCE__, __BANK__) CLEAR_BIT((__INSTANCE__)->BTCR[(__BANK__)], FSMC_BCRx_MBKEN)

/**
  * @}
  */ 

#if defined (STM32F101xE) || defined(STM32F103xE) || defined(STM32F101xG) || defined(STM32F103xG)
/** @defgroup FSMC_NAND_Macros FSMC_NAND_Macros
 *  @brief macros to handle NAND device enable/disable
 *  @{
 */
 
/**
  * @brief  Enable the NAND device access.
  * @param  __INSTANCE__: FSMC_NAND Instance
  * @param  __BANK__: FSMC_NAND Bank    
  * @retval None
  */  
#define __FSMC_NAND_ENABLE(__INSTANCE__, __BANK__)  (((__BANK__) == FSMC_NAND_BANK2)? SET_BIT((__INSTANCE__)->PCR2, FSMC_PCRx_PBKEN): \
                                                    SET_BIT((__INSTANCE__)->PCR3, FSMC_PCRx_PBKEN))                                        

/**
  * @brief  Disable the NAND device access.
  * @param  __INSTANCE__: FSMC_NAND Instance
  * @param  __BANK__: FSMC_NAND Bank  
  * @retval None
  */                                          
#define __FSMC_NAND_DISABLE(__INSTANCE__, __BANK__) (((__BANK__) == FSMC_NAND_BANK2)? CLEAR_BIT((__INSTANCE__)->PCR2, FSMC_PCRx_PBKEN): \
                                                   CLEAR_BIT((__INSTANCE__)->PCR3, FSMC_PCRx_PBKEN))                                                                                
/**
  * @}
  */ 
  
/** @defgroup FSMC_PCCARD_Macros FSMC_PCCARD_Macros
 *  @brief macros to handle SRAM read/write operations 
 *  @{
 */

/**
  * @brief  Enable the PCCARD device access.
  * @param  __INSTANCE__: FSMC_PCCARD Instance  
  * @retval None
  */ 
#define __FSMC_PCCARD_ENABLE(__INSTANCE__)  SET_BIT((__INSTANCE__)->PCR4, FSMC_PCRx_PBKEN)

/**
  * @brief  Disable the PCCARD device access.
  * @param  __INSTANCE__: FSMC_PCCARD Instance     
  * @retval None
  */ 
#define __FSMC_PCCARD_DISABLE(__INSTANCE__) CLEAR_BIT((__INSTANCE__)->PCR4, FSMC_PCRx_PBKEN)
/**
  * @}
  */
  
/** @defgroup FSMC_Interrupt FSMC_Interrupt
 *  @brief macros to handle FSMC interrupts
 * @{
 */ 

/**
  * @brief  Enable the NAND device interrupt.
  * @param  __INSTANCE__:  FSMC_NAND Instance
  * @param  __BANK__:      FSMC_NAND Bank     
  * @param  __INTERRUPT__: FSMC_NAND interrupt 
  *         This parameter can be any combination of the following values:
  *            @arg FSMC_IT_RISING_EDGE: Interrupt rising edge.
  *            @arg FSMC_IT_LEVEL: Interrupt level.
  *            @arg FSMC_IT_FALLING_EDGE: Interrupt falling edge.       
  * @retval None
  */  
#define __FSMC_NAND_ENABLE_IT(__INSTANCE__, __BANK__, __INTERRUPT__)  (((__BANK__) == FSMC_NAND_BANK2)? SET_BIT((__INSTANCE__)->SR2, (__INTERRUPT__)): \
                                                                                                        SET_BIT((__INSTANCE__)->SR3, (__INTERRUPT__)))

/**
  * @brief  Disable the NAND device interrupt.
  * @param  __INSTANCE__:  FSMC_NAND Instance
  * @param  __BANK__:      FSMC_NAND Bank    
  * @param  __INTERRUPT__: FSMC_NAND interrupt
  *         This parameter can be any combination of the following values:
  *            @arg FSMC_IT_RISING_EDGE: Interrupt rising edge.
  *            @arg FSMC_IT_LEVEL: Interrupt level.
  *            @arg FSMC_IT_FALLING_EDGE: Interrupt falling edge.   
  * @retval None
  */
#define __FSMC_NAND_DISABLE_IT(__INSTANCE__, __BANK__, __INTERRUPT__)  (((__BANK__) == FSMC_NAND_BANK2)? CLEAR_BIT((__INSTANCE__)->SR2, (__INTERRUPT__)): \
                                                                                                         CLEAR_BIT((__INSTANCE__)->SR3, (__INTERRUPT__))) 
                                                                                                                             
/**
  * @brief  Get flag status of the NAND device.
  * @param  __INSTANCE__: FSMC_NAND Instance
  * @param  __BANK__:     FSMC_NAND Bank      
  * @param  __FLAG__: FSMC_NAND flag
  *         This parameter can be any combination of the following values:
  *            @arg FSMC_FLAG_RISING_EDGE: Interrupt rising edge flag.
  *            @arg FSMC_FLAG_LEVEL: Interrupt level edge flag.
  *            @arg FSMC_FLAG_FALLING_EDGE: Interrupt falling edge flag.
  *            @arg FSMC_FLAG_FEMPT: FIFO empty flag.   
  * @retval The state of FLAG (SET or RESET).
  */
#define __FSMC_NAND_GET_FLAG(__INSTANCE__, __BANK__, __FLAG__)  (((__BANK__) == FSMC_NAND_BANK2)? (((__INSTANCE__)->SR2 &(__FLAG__)) == (__FLAG__)): \
                                                                                                   (((__INSTANCE__)->SR3 &(__FLAG__)) == (__FLAG__)))
/**
  * @brief  Clear flag status of the NAND device.
  * @param  __INSTANCE__: FSMC_NAND Instance  
  * @param  __BANK__:     FSMC_NAND Bank  
  * @param  __FLAG__: FSMC_NAND flag
  *         This parameter can be any combination of the following values:
  *            @arg FSMC_FLAG_RISING_EDGE: Interrupt rising edge flag.
  *            @arg FSMC_FLAG_LEVEL: Interrupt level edge flag.
  *            @arg FSMC_FLAG_FALLING_EDGE: Interrupt falling edge flag.
  *            @arg FSMC_FLAG_FEMPT: FIFO empty flag.   
  * @retval None
  */
#define __FSMC_NAND_CLEAR_FLAG(__INSTANCE__, __BANK__, __FLAG__)  (((__BANK__) == FSMC_NAND_BANK2)? CLEAR_BIT((__INSTANCE__)->SR2, (__FLAG__)): \
                                                                                                    CLEAR_BIT((__INSTANCE__)->SR3, (__FLAG__))) 
/**
  * @brief  Enable the PCCARD device interrupt.
  * @param  __INSTANCE__: FSMC_PCCARD Instance  
  * @param  __INTERRUPT__: FSMC_PCCARD interrupt 
  *         This parameter can be any combination of the following values:
  *            @arg FSMC_IT_RISING_EDGE: Interrupt rising edge.
  *            @arg FSMC_IT_LEVEL: Interrupt level.
  *            @arg FSMC_IT_FALLING_EDGE: Interrupt falling edge.       
  * @retval None
  */ 
#define __FSMC_PCCARD_ENABLE_IT(__INSTANCE__, __INTERRUPT__)  SET_BIT((__INSTANCE__)->SR4, (__INTERRUPT__))

/**
  * @brief  Disable the PCCARD device interrupt.
  * @param  __INSTANCE__: FSMC_PCCARD Instance  
  * @param  __INTERRUPT__: FSMC_PCCARD interrupt 
  *         This parameter can be any combination of the following values:
  *            @arg FSMC_IT_RISING_EDGE: Interrupt rising edge.
  *            @arg FSMC_IT_LEVEL: Interrupt level.
  *            @arg FSMC_IT_FALLING_EDGE: Interrupt falling edge.       
  * @retval None
  */ 
#define __FSMC_PCCARD_DISABLE_IT(__INSTANCE__, __INTERRUPT__)  CLEAR_BIT((__INSTANCE__)->SR4, (__INTERRUPT__)) 

/**
  * @brief  Get flag status of the PCCARD device.
  * @param  __INSTANCE__: FSMC_PCCARD Instance  
  * @param  __FLAG__: FSMC_PCCARD flag
  *         This parameter can be any combination of the following values:
  *            @arg  FSMC_FLAG_RISING_EDGE: Interrupt rising edge flag.
  *            @arg  FSMC_FLAG_LEVEL: Interrupt level edge flag.
  *            @arg  FSMC_FLAG_FALLING_EDGE: Interrupt falling edge flag.
  *            @arg  FSMC_FLAG_FEMPT: FIFO empty flag.   
  * @retval The state of FLAG (SET or RESET).
  */
#define __FSMC_PCCARD_GET_FLAG(__INSTANCE__, __FLAG__)  (((__INSTANCE__)->SR4 &(__FLAG__)) == (__FLAG__))

/**
  * @brief  Clear flag status of the PCCARD device.
  * @param  __INSTANCE__: FSMC_PCCARD Instance  
  * @param  __FLAG__: FSMC_PCCARD flag
  *         This parameter can be any combination of the following values:
  *            @arg  FSMC_FLAG_RISING_EDGE: Interrupt rising edge flag.
  *            @arg  FSMC_FLAG_LEVEL: Interrupt level edge flag.
  *            @arg  FSMC_FLAG_FALLING_EDGE: Interrupt falling edge flag.
  *            @arg  FSMC_FLAG_FEMPT: FIFO empty flag.   
  * @retval None
  */
#define __FSMC_PCCARD_CLEAR_FLAG(__INSTANCE__, __FLAG__)  CLEAR_BIT((__INSTANCE__)->SR4, (__FLAG__))
 
/**
  * @}
  */ 

#endif /* STM32F101xE || STM32F103xE || STM32F101xG || STM32F103xG */

/**
  * @}
  */ 

/* Exported functions --------------------------------------------------------*/

/** @addtogroup FSMC_LL_Exported_Functions
 *  @{
 */

/** @addtogroup FSMC_NORSRAM
 *  @{
 */

/** @addtogroup FSMC_NORSRAM_Group1
 *  @{
 */

/* FSMC_NORSRAM Controller functions ******************************************/
/* Initialization/de-initialization functions */
HAL_StatusTypeDef  FSMC_NORSRAM_Init(FSMC_NORSRAM_TypeDef *Device, FSMC_NORSRAM_InitTypeDef *Init);
HAL_StatusTypeDef  FSMC_NORSRAM_Timing_Init(FSMC_NORSRAM_TypeDef *Device, FSMC_NORSRAM_TimingTypeDef *Timing, uint32_t Bank);
HAL_StatusTypeDef  FSMC_NORSRAM_Extended_Timing_Init(FSMC_NORSRAM_EXTENDED_TypeDef *Device, FSMC_NORSRAM_TimingTypeDef *Timing, uint32_t Bank, uint32_t ExtendedMode);
HAL_StatusTypeDef  FSMC_NORSRAM_DeInit(FSMC_NORSRAM_TypeDef *Device, FSMC_NORSRAM_EXTENDED_TypeDef *ExDevice, uint32_t Bank);

/**
  * @}
  */ 

/** @addtogroup FSMC_NORSRAM_Group2
 *  @{
 */

/* FSMC_NORSRAM Control functions */
HAL_StatusTypeDef  FSMC_NORSRAM_WriteOperation_Enable(FSMC_NORSRAM_TypeDef *Device, uint32_t Bank);
HAL_StatusTypeDef  FSMC_NORSRAM_WriteOperation_Disable(FSMC_NORSRAM_TypeDef *Device, uint32_t Bank);

/**
  * @}
  */ 

/**
  * @}
  */ 

#if defined (STM32F101xE) || defined(STM32F103xE) || defined(STM32F101xG) || defined(STM32F103xG)
/** @addtogroup FSMC_NAND
 *  @{
 */

/* FSMC_NAND Controller functions **********************************************/
/* Initialization/de-initialization functions */
/** @addtogroup FSMC_NAND_Exported_Functions_Group1
 *  @{
 */

HAL_StatusTypeDef  FSMC_NAND_Init(FSMC_NAND_TypeDef *Device, FSMC_NAND_InitTypeDef *Init);
HAL_StatusTypeDef  FSMC_NAND_CommonSpace_Timing_Init(FSMC_NAND_TypeDef *Device, FSMC_NAND_PCC_TimingTypeDef *Timing, uint32_t Bank);
HAL_StatusTypeDef  FSMC_NAND_AttributeSpace_Timing_Init(FSMC_NAND_TypeDef *Device, FSMC_NAND_PCC_TimingTypeDef *Timing, uint32_t Bank);
HAL_StatusTypeDef  FSMC_NAND_DeInit(FSMC_NAND_TypeDef *Device, uint32_t Bank);

/**
  * @}
  */ 

/* FSMC_NAND Control functions */
/** @addtogroup FSMC_NAND_Exported_Functions_Group2
 *  @{
 */

HAL_StatusTypeDef  FSMC_NAND_ECC_Enable(FSMC_NAND_TypeDef *Device, uint32_t Bank);
HAL_StatusTypeDef  FSMC_NAND_ECC_Disable(FSMC_NAND_TypeDef *Device, uint32_t Bank);
HAL_StatusTypeDef  FSMC_NAND_GetECC(FSMC_NAND_TypeDef *Device, uint32_t *ECCval, uint32_t Bank, uint32_t Timeout);

/**
  * @}
  */ 

/**
  * @}
  */ 

/** @addtogroup FSMC_PCCARD
 *  @{
 */

/* FSMC_PCCARD Controller functions ********************************************/
/* Initialization/de-initialization functions */
/** @addtogroup FSMC_PCCARD_Exported_Functions_Group1
 *  @{
 */

HAL_StatusTypeDef  FSMC_PCCARD_Init(FSMC_PCCARD_TypeDef *Device, FSMC_PCCARD_InitTypeDef *Init);
HAL_StatusTypeDef  FSMC_PCCARD_CommonSpace_Timing_Init(FSMC_PCCARD_TypeDef *Device, FSMC_NAND_PCC_TimingTypeDef *Timing);
HAL_StatusTypeDef  FSMC_PCCARD_AttributeSpace_Timing_Init(FSMC_PCCARD_TypeDef *Device, FSMC_NAND_PCC_TimingTypeDef *Timing);
HAL_StatusTypeDef  FSMC_PCCARD_IOSpace_Timing_Init(FSMC_PCCARD_TypeDef *Device, FSMC_NAND_PCC_TimingTypeDef *Timing); 
HAL_StatusTypeDef  FSMC_PCCARD_DeInit(FSMC_PCCARD_TypeDef *Device);

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

/**
  * @}
  */
  
#ifdef __cplusplus
}
#endif

#endif /* __STM32F1xx_LL_FSMC_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

