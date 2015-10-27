/**
  ******************************************************************************
  * @file    stm32_hal_legacy.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    15-December-2014
  * @brief   This file contains aliases definition for the STM32Cube HAL constants 
  *          macros and functions maintained for legacy purpose.
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
 UART * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32_HAL_LEGACY
#define __STM32_HAL_LEGACY

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup HAL_AES_Aliased_Defines HAL CRYP Aliased Defines maintained for legacy purpose
  * @{
  */
#define AES_FLAG_RDERR                 CRYP_FLAG_RDERR
#define AES_FLAG_WRERR                 CRYP_FLAG_WRERR
#define AES_CLEARFLAG_CCF               CRYP_CLEARFLAG_CCF
#define AES_CLEARFLAG_RDERR             CRYP_CLEARFLAG_RDERR
#define AES_CLEARFLAG_WRERR             CRYP_CLEARFLAG_WRERR

/**
  * @}
  */
  
/** @defgroup HAL_ADC_Aliased_Defines HAL ADC Aliased Defines maintained for legacy purpose
  * @{
  */
#define ADC_RESOLUTION12b               ADC_RESOLUTION_12B
#define ADC_RESOLUTION10b               ADC_RESOLUTION_10B
#define ADC_RESOLUTION8b                ADC_RESOLUTION_8B
#define ADC_RESOLUTION6b                ADC_RESOLUTION_6B
#define OVR_DATA_OVERWRITTEN            ADC_OVR_DATA_OVERWRITTEN
#define OVR_DATA_PRESERVED              ADC_OVR_DATA_PRESERVED
#define EOC_SINGLE_CONV                 ADC_EOC_SINGLE_CONV
#define EOC_SEQ_CONV                    ADC_EOC_SEQ_CONV
#define EOC_SINGLE_SEQ_CONV             ADC_EOC_SINGLE_SEQ_CONV
#define REGULAR_GROUP                   ADC_REGULAR_GROUP
#define INJECTED_GROUP                  ADC_INJECTED_GROUP
#define REGULAR_INJECTED_GROUP          ADC_REGULAR_INJECTED_GROUP
#define AWD_EVENT                       ADC_AWD_EVENT
#define AWD1_EVENT                      ADC_AWD1_EVENT
#define AWD2_EVENT                      ADC_AWD2_EVENT
#define AWD3_EVENT                      ADC_AWD3_EVENT
#define OVR_EVENT                       ADC_OVR_EVENT
#define JQOVF_EVENT                     ADC_JQOVF_EVENT
#define ALL_CHANNELS                    ADC_ALL_CHANNELS
#define REGULAR_CHANNELS                ADC_REGULAR_CHANNELS
#define INJECTED_CHANNELS               ADC_INJECTED_CHANNELS
#define SYSCFG_FLAG_SENSOR_ADC          ADC_FLAG_SENSOR
#define SYSCFG_FLAG_VREF_ADC            ADC_FLAG_VREFINT
#define ADC_CLOCKPRESCALER_PCLK_DIV1    ADC_CLOCK_SYNC_PCLK_DIV1
#define ADC_CLOCKPRESCALER_PCLK_DIV2    ADC_CLOCK_SYNC_PCLK_DIV2
#define ADC_CLOCKPRESCALER_PCLK_DIV4    ADC_CLOCK_SYNC_PCLK_DIV4
#define ADC_EXTERNALTRIG0_T6_TRGO       ADC_EXTERNALTRIGCONV_T6_TRGO 
#define ADC_EXTERNALTRIG1_T21_CC2       ADC_EXTERNALTRIGCONV_T21_CC2 
#define ADC_EXTERNALTRIG2_T2_TRGO       ADC_EXTERNALTRIGCONV_T2_TRGO 
#define ADC_EXTERNALTRIG3_T2_CC4        ADC_EXTERNALTRIGCONV_T2_CC4  
#define ADC_EXTERNALTRIG4_T22_TRGO      ADC_EXTERNALTRIGCONV_T22_TRGO
#define ADC_EXTERNALTRIG7_EXT_IT11      ADC_EXTERNALTRIGCONV_EXT_IT11
#define ADC_CLOCK_ASYNC                 ADC_CLOCK_ASYNC_DIV1


/**
  * @}
  */
  
/** @defgroup HAL_CEC_Aliased_Defines HAL CEC Aliased Defines maintained for legacy purpose
  * @{
  */ 
  
#define __HAL_CEC_GET_IT __HAL_CEC_GET_FLAG 

/**
  * @}
  */   
   
/** @defgroup HAL_COMP_Aliased_Defines HAL COMP Aliased Defines maintained for legacy purpose
  * @{
  */
  
#define COMP_WINDOWMODE_DISABLED    COMP_WINDOWMODE_DISABLE
#define COMP_WINDOWMODE_ENABLED     COMP_WINDOWMODE_ENABLE
#define COMP_EXTI_LINE_COMP1_EVENT  COMP_EXTI_LINE_COMP1
#define COMP_EXTI_LINE_COMP2_EVENT  COMP_EXTI_LINE_COMP2

/**
  * @}
  */

/** @defgroup HAL_CRC_Aliased_Defines HAL CRC Aliased Defines maintained for legacy purpose
  * @{
  */
  
#define CRC_OUTPUTDATA_INVERSION_DISABLED    CRC_OUTPUTDATA_INVERSION_DISABLE
#define CRC_OUTPUTDATA_INVERSION_ENABLED     CRC_OUTPUTDATA_INVERSION_ENABLE

/**
  * @}
  */

/** @defgroup HAL_DAC_Aliased_Defines HAL DAC Aliased Defines maintained for legacy purpose
  * @{
  */

#define DAC1_CHANNEL_1                                  DAC_CHANNEL_1
#define DAC1_CHANNEL_2                                  DAC_CHANNEL_2
#define DAC2_CHANNEL_1                                  DAC_CHANNEL_1

/**
  * @}
  */


/** @defgroup HAL_FLASH_Aliased_Defines HAL FLASH Aliased Defines maintained for legacy purpose
  * @{
  */
  
#define TYPEPROGRAM_BYTE              FLASH_TYPEPROGRAM_BYTE
#define TYPEPROGRAM_HALFWORD          FLASH_TYPEPROGRAM_HALFWORD
#define TYPEPROGRAM_WORD              FLASH_TYPEPROGRAM_WORD
#define TYPEPROGRAM_DOUBLEWORD        FLASH_TYPEPROGRAM_DOUBLEWORD
#define TYPEERASE_SECTORS             FLASH_TYPEERASE_SECTORS
#define TYPEERASE_PAGES               FLASH_TYPEERASE_PAGES
#define TYPEERASE_PAGEERASE           FLASH_TYPEERASE_PAGES
#define TYPEERASE_MASSERASE           FLASH_TYPEERASE_MASSERASE
#define WRPSTATE_DISABLE              OB_WRPSTATE_DISABLE
#define WRPSTATE_ENABLE               OB_WRPSTATE_ENABLE
#define HAL_FLASH_TIMEOUT_VALUE       FLASH_TIMEOUT_VALUE
#define OBEX_PCROP                    OPTIONBYTE_PCROP
#define OBEX_BOOTCONFIG               OPTIONBYTE_BOOTCONFIG
#define PCROPSTATE_DISABLE            OB_PCROP_STATE_DISABLE
#define PCROPSTATE_ENABLE             OB_PCROP_STATE_ENABLE
#define TYPEERASEDATA_BYTE            FLASH_TYPEERASEDATA_BYTE
#define TYPEERASEDATA_HALFWORD        FLASH_TYPEERASEDATA_HALFWORD
#define TYPEERASEDATA_WORD            FLASH_TYPEERASEDATA_WORD
#define TYPEPROGRAMDATA_BYTE          FLASH_TYPEPROGRAMDATA_BYTE
#define TYPEPROGRAMDATA_HALFWORD      FLASH_TYPEPROGRAMDATA_HALFWORD
#define TYPEPROGRAMDATA_WORD          FLASH_TYPEPROGRAMDATA_WORD
#define TYPEPROGRAMDATA_FASTBYTE      FLASH_TYPEPROGRAMDATA_FASTBYTE
#define TYPEPROGRAMDATA_FASTHALFWORD  FLASH_TYPEPROGRAMDATA_FASTHALFWORD
#define TYPEPROGRAMDATA_FASTWORD      FLASH_TYPEPROGRAMDATA_FASTWORD
#define PAGESIZE                      FLASH_PAGE_SIZE
#define TYPEPROGRAM_FASTBYTE          FLASH_TYPEPROGRAM_BYTE
#define TYPEPROGRAM_FASTHALFWORD      FLASH_TYPEPROGRAM_HALFWORD
#define TYPEPROGRAM_FASTWORD          FLASH_TYPEPROGRAM_WORD
#define VOLTAGE_RANGE_1               FLASH_VOLTAGE_RANGE_1
#define VOLTAGE_RANGE_2               FLASH_VOLTAGE_RANGE_2
#define VOLTAGE_RANGE_3               FLASH_VOLTAGE_RANGE_3
#define VOLTAGE_RANGE_4               FLASH_VOLTAGE_RANGE_4
#define TYPEPROGRAM_FAST              FLASH_TYPEPROGRAM_FAST
#define TYPEPROGRAM_FAST_AND_LAST     FLASH_TYPEPROGRAM_FAST_AND_LAST
#define WRPAREA_BANK1_AREAA           OB_WRPAREA_BANK1_AREAA
#define WRPAREA_BANK1_AREAB           OB_WRPAREA_BANK1_AREAB
#define WRPAREA_BANK2_AREAA           OB_WRPAREA_BANK2_AREAA
#define WRPAREA_BANK2_AREAB           OB_WRPAREA_BANK2_AREAB
#define IWDG_STDBY_FREEZE             OB_IWDG_STDBY_FREEZE
#define IWDG_STDBY_ACTIVE             OB_IWDG_STDBY_RUN
#define IWDG_STOP_FREEZE              OB_IWDG_STOP_FREEZE
#define IWDG_STOP_ACTIVE              OB_IWDG_STOP_RUN
#define IS_NBSECTORS                  IS_FLASH_NBSECTORS
#define FLASH_ERROR_NONE              HAL_FLASH_ERROR_NONE
#define FLASH_ERROR_RD                HAL_FLASH_ERROR_RD
#define FLASH_ERROR_PG                HAL_FLASH_ERROR_PROG
#define FLASH_ERROR_PGP               HAL_FLASH_ERROR_PGS
#define FLASH_ERROR_WRP               HAL_FLASH_ERROR_WRP
#define FLASH_ERROR_OPTV              HAL_FLASH_ERROR_OPTV
#define FLASH_ERROR_OPTVUSR           HAL_FLASH_ERROR_OPTVUSR
#define FLASH_ERROR_PROG              HAL_FLASH_ERROR_PROG
#define FLASH_ERROR_OP                HAL_FLASH_ERROR_OPERATION
#define FLASH_ERROR_PGA               HAL_FLASH_ERROR_PGA
#define FLASH_ERROR_SIZE              HAL_FLASH_ERROR_SIZE
#define FLASH_ERROR_SIZ               HAL_FLASH_ERROR_SIZE
#define FLASH_ERROR_PGS               HAL_FLASH_ERROR_PGS
#define FLASH_ERROR_MIS               HAL_FLASH_ERROR_MIS
#define FLASH_ERROR_FAST              HAL_FLASH_ERROR_FAST
#define FLASH_ERROR_FWWERR            HAL_FLASH_ERROR_FWWERR
#define FLASH_ERROR_NOTZERO           HAL_FLASH_ERROR_NOTZERO
#define FLASH_ERROR_OPERATION         HAL_FLASH_ERROR_OPERATION
#define FLASH_ERROR_ERS               HAL_FLASH_ERROR_ERS

/**
  * @}
  */
  
/** @defgroup HAL_SYSCFG_Aliased_Defines HAL SYSCFG Aliased Defines maintained for legacy purpose
  * @{
  */
  
#define SYSCFG_FASTMODEPLUS_I2C_PB6    I2C_FASTMODEPLUS_PB6
#define SYSCFG_FASTMODEPLUS_I2C_PB7    I2C_FASTMODEPLUS_PB7
#define SYSCFG_FASTMODEPLUS_I2C_PB8    I2C_FASTMODEPLUS_PB8
#define SYSCFG_FASTMODEPLUS_I2C_PB9    I2C_FASTMODEPLUS_PB9
#define SYSCFG_FASTMODEPLUS_I2C1       I2C_FASTMODEPLUS_I2C1
#define SYSCFG_FASTMODEPLUS_I2C2       I2C_FASTMODEPLUS_I2C2
#define SYSCFG_FASTMODEPLUS_I2C3       I2C_FASTMODEPLUS_I2C3

/**
  * @}
  */
  

/** @defgroup LL_FSMC_Aliased_Defines LL FSMC Aliased Defines maintained for legacy purpose
  * @{
  */
  
#define FSMC_NORSRAM_TYPEDEF                      FSMC_NORSRAM_TypeDef
#define FSMC_NORSRAM_EXTENDED_TYPEDEF             FSMC_NORSRAM_EXTENDED_TypeDef
/**
  * @}
  */

/** @defgroup HAL_GPIO_Aliased_Macros HAL GPIO Aliased Macros maintained for legacy purpose
  * @{
  */
#define GET_GPIO_SOURCE                           GPIO_GET_INDEX
#define GET_GPIO_INDEX                            GPIO_GET_INDEX
/**
  * @}
  */


/** @defgroup HAL_I2C_Aliased_Defines HAL I2C Aliased Defines maintained for legacy purpose
  * @{
  */
#define I2C_DUALADDRESS_DISABLED                I2C_DUALADDRESS_DISABLE
#define I2C_DUALADDRESS_ENABLED                 I2C_DUALADDRESS_ENABLE
#define I2C_GENERALCALL_DISABLED                I2C_GENERALCALL_DISABLE
#define I2C_GENERALCALL_ENABLED                 I2C_GENERALCALL_ENABLE
#define I2C_NOSTRETCH_DISABLED                  I2C_NOSTRETCH_DISABLE
#define I2C_NOSTRETCH_ENABLED                   I2C_NOSTRETCH_ENABLE
#define I2C_ANALOGFILTER_ENABLED                I2C_ANALOGFILTER_ENABLE
#define I2C_ANALOGFILTER_DISABLED               I2C_ANALOGFILTER_DISABLE
/**
  * @}
  */

/** @defgroup HAL_IRDA_Aliased_Defines HAL IRDA Aliased Defines maintained for legacy purpose
  * @{
  */
#define IRDA_ONE_BIT_SAMPLE_DISABLED            IRDA_ONE_BIT_SAMPLE_DISABLE
#define IRDA_ONE_BIT_SAMPLE_ENABLED             IRDA_ONE_BIT_SAMPLE_ENABLE

/**
  * @}
  */

/** @defgroup HAL_IWDG_Aliased_Defines HAL IWDG Aliased Defines maintained for legacy purpose
  * @{
  */
#define KR_KEY_RELOAD                   IWDG_KEY_RELOAD
#define KR_KEY_ENABLE                   IWDG_KEY_ENABLE
#define KR_KEY_EWA                      IWDG_KEY_WRITE_ACCESS_ENABLE
#define KR_KEY_DWA                      IWDG_KEY_WRITE_ACCESS_DISABLE
/**
  * @}
  */

/** @defgroup HAL_NAND_Aliased_Defines HAL NAND Aliased Defines maintained for legacy purpose
  * @{
  */
#define NAND_AddressTypedef             NAND_AddressTypeDef

/**
  * @}
  */
   
/** @defgroup HAL_NOR_Aliased_Defines HAL NOR Aliased Defines maintained for legacy purpose
  * @{
  */
#define NOR_StatusTypedef              HAL_NOR_StatusTypeDef
#define NOR_SUCCESS                    HAL_NOR_STATUS_SUCCESS
#define NOR_ONGOING                    HAL_NOR_STATUS_ONGOING
#define NOR_ERROR                      HAL_NOR_STATUS_ERROR
#define NOR_TIMEOUT                    HAL_NOR_STATUS_TIMEOUT

/**
  * @}
  */

/** @defgroup HAL_OPAMP_Aliased_Defines HAL OPAMP Aliased Defines maintained for legacy purpose
  * @{
  */

#define OPAMP_NONINVERTINGINPUT_VP0           OPAMP_NONINVERTINGINPUT_IO0
#define OPAMP_NONINVERTINGINPUT_VP1           OPAMP_NONINVERTINGINPUT_IO1
#define OPAMP_NONINVERTINGINPUT_VP2           OPAMP_NONINVERTINGINPUT_IO2
#define OPAMP_NONINVERTINGINPUT_VP3           OPAMP_NONINVERTINGINPUT_IO3
                                              
#define OPAMP_SEC_NONINVERTINGINPUT_VP0       OPAMP_SEC_NONINVERTINGINPUT_IO0
#define OPAMP_SEC_NONINVERTINGINPUT_VP1       OPAMP_SEC_NONINVERTINGINPUT_IO1
#define OPAMP_SEC_NONINVERTINGINPUT_VP2       OPAMP_SEC_NONINVERTINGINPUT_IO2
#define OPAMP_SEC_NONINVERTINGINPUT_VP3       OPAMP_SEC_NONINVERTINGINPUT_IO3   

#define OPAMP_INVERTINGINPUT_VM0              OPAMP_INVERTINGINPUT_IO0
#define OPAMP_INVERTINGINPUT_VM1              OPAMP_INVERTINGINPUT_IO1

#define IOPAMP_INVERTINGINPUT_VM0             OPAMP_INVERTINGINPUT_IO0
#define IOPAMP_INVERTINGINPUT_VM1             OPAMP_INVERTINGINPUT_IO1

#define OPAMP_SEC_INVERTINGINPUT_VM0          OPAMP_SEC_INVERTINGINPUT_IO0
#define OPAMP_SEC_INVERTINGINPUT_VM1          OPAMP_SEC_INVERTINGINPUT_IO1    

#define OPAMP_INVERTINGINPUT_VINM             OPAMP_SEC_INVERTINGINPUT_IO1
                                                                      
#define OPAMP_PGACONNECT_NO                   OPAMP_PGA_CONNECT_INVERTINGINPUT_NO             
#define OPAMP_PGACONNECT_VM0                  OPAMP_PGA_CONNECT_INVERTINGINPUT_IO0            
#define OPAMP_PGACONNECT_VM1                  OPAMP_PGA_CONNECT_INVERTINGINPUT_IO1          
                                                        
/**
  * @}
  */

/** @defgroup HAL_I2S_Aliased_Defines HAL I2S Aliased Defines maintained for legacy purpose
  * @{
  */
#define I2S_STANDARD_PHILLIPS      I2S_STANDARD_PHILIPS
/**
  * @}
  */

/** @defgroup HAL_PCCARD_Aliased_Defines HAL PCCARD Aliased Defines maintained for legacy purpose
  * @{
  */

/* Compact Flash-ATA registers description */
#define CF_DATA                       ATA_DATA                
#define CF_SECTOR_COUNT               ATA_SECTOR_COUNT        
#define CF_SECTOR_NUMBER              ATA_SECTOR_NUMBER       
#define CF_CYLINDER_LOW               ATA_CYLINDER_LOW        
#define CF_CYLINDER_HIGH              ATA_CYLINDER_HIGH       
#define CF_CARD_HEAD                  ATA_CARD_HEAD           
#define CF_STATUS_CMD                 ATA_STATUS_CMD          
#define CF_STATUS_CMD_ALTERNATE       ATA_STATUS_CMD_ALTERNATE
#define CF_COMMON_DATA_AREA           ATA_COMMON_DATA_AREA    

/* Compact Flash-ATA commands */
#define CF_READ_SECTOR_CMD            ATA_READ_SECTOR_CMD 
#define CF_WRITE_SECTOR_CMD           ATA_WRITE_SECTOR_CMD
#define CF_ERASE_SECTOR_CMD           ATA_ERASE_SECTOR_CMD
#define CF_IDENTIFY_CMD               ATA_IDENTIFY_CMD

#define PCCARD_StatusTypedef          HAL_PCCARD_StatusTypeDef
#define PCCARD_SUCCESS                HAL_PCCARD_STATUS_SUCCESS
#define PCCARD_ONGOING                HAL_PCCARD_STATUS_ONGOING
#define PCCARD_ERROR                  HAL_PCCARD_STATUS_ERROR
#define PCCARD_TIMEOUT                HAL_PCCARD_STATUS_TIMEOUT
/**
  * @}
  */
  
/** @defgroup HAL_RTC_Aliased_Defines HAL RTC Aliased Defines maintained for legacy purpose
  * @{
  */
  
#define FORMAT_BIN                  RTC_FORMAT_BIN
#define FORMAT_BCD                  RTC_FORMAT_BCD

#define RTC_ALARMSUBSECONDMASK_None     RTC_ALARMSUBSECONDMASK_NONE
#define RTC_TAMPERERASEBACKUP_ENABLED   RTC_TAMPER_ERASE_BACKUP_ENABLE
#define RTC_TAMPERERASEBACKUP_DISABLED  RTC_TAMPER_ERASE_BACKUP_DISABLE
#define RTC_TAMPERMASK_FLAG_DISABLED    RTC_TAMPERMASK_FLAG_DISABLE
#define RTC_TAMPERMASK_FLAG_ENABLED     RTC_TAMPERMASK_FLAG_ENABLE

#define RTC_MASKTAMPERFLAG_DISABLED    RTC_TAMPERMASK_FLAG_DISABLE 
#define RTC_MASKTAMPERFLAG_ENABLED      RTC_TAMPERMASK_FLAG_ENABLE 
#define RTC_TAMPERERASEBACKUP_ENABLED  RTC_TAMPER_ERASE_BACKUP_ENABLE
#define RTC_TAMPERERASEBACKUP_DISABLED   RTC_TAMPER_ERASE_BACKUP_DISABLE 
#define RTC_MASKTAMPERFLAG_DISABLED   RTC_TAMPERMASK_FLAG_DISABLE 
#define RTC_MASKTAMPERFLAG_ENABLED      RTC_TAMPERMASK_FLAG_ENABLE
#define RTC_TAMPER1_2_INTERRUPT          RTC_ALL_TAMPER_INTERRUPT 
#define RTC_TAMPER1_2_3_INTERRUPT     RTC_ALL_TAMPER_INTERRUPT 

/**
  * @}
  */

  
/** @defgroup HAL_SMARTCARD_Aliased_Defines HAL SMARTCARD Aliased Defines maintained for legacy purpose
  * @{
  */
#define SMARTCARD_NACK_ENABLED                  SMARTCARD_NACK_ENABLE
#define SMARTCARD_NACK_DISABLED                 SMARTCARD_NACK_DISABLE

#define SMARTCARD_ONEBIT_SAMPLING_DISABLED      SMARTCARD_ONE_BIT_SAMPLE_DISABLE
#define SMARTCARD_ONEBIT_SAMPLING_ENABLED       SMARTCARD_ONE_BIT_SAMPLE_ENABLE
#define SMARTCARD_ONEBIT_SAMPLING_DISABLE       SMARTCARD_ONE_BIT_SAMPLE_DISABLE
#define SMARTCARD_ONEBIT_SAMPLING_ENABLE        SMARTCARD_ONE_BIT_SAMPLE_ENABLE

#define SMARTCARD_TIMEOUT_DISABLED              SMARTCARD_TIMEOUT_DISABLE
#define SMARTCARD_TIMEOUT_ENABLED               SMARTCARD_TIMEOUT_ENABLE

#define SMARTCARD_LASTBIT_DISABLED              SMARTCARD_LASTBIT_DISABLE
#define SMARTCARD_LASTBIT_ENABLED               SMARTCARD_LASTBIT_ENABLE
/**
  * @}
  */

  
  /** @defgroup HAL_SMBUS_Aliased_Defines HAL SMBUS Aliased Defines maintained for legacy purpose
  * @{
  */
#define SMBUS_DUALADDRESS_DISABLED      SMBUS_DUALADDRESS_DISABLE
#define SMBUS_DUALADDRESS_ENABLED       SMBUS_DUALADDRESS_ENABLE
#define SMBUS_GENERALCALL_DISABLED      SMBUS_GENERALCALL_DISABLE
#define SMBUS_GENERALCALL_ENABLED       SMBUS_GENERALCALL_ENABLE
#define SMBUS_NOSTRETCH_DISABLED        SMBUS_NOSTRETCH_DISABLE
#define SMBUS_NOSTRETCH_ENABLED         SMBUS_NOSTRETCH_ENABLE
#define SMBUS_ANALOGFILTER_ENABLED      SMBUS_ANALOGFILTER_ENABLE
#define SMBUS_ANALOGFILTER_DISABLED     SMBUS_ANALOGFILTER_DISABLE
#define HAL_SMBUS_STATE_SLAVE_LISTEN    HAL_SMBUS_STATE_LISTEN
/**
  * @}
  */
  
  /** @defgroup HAL_SPI_Aliased_Defines HAL SPI Aliased Defines maintained for legacy purpose
  * @{
  */
#define SPI_TIMODE_DISABLED             SPI_TIMODE_DISABLE
#define SPI_TIMODE_ENABLED              SPI_TIMODE_ENABLE

#define SPI_CRCCALCULATION_DISABLED     SPI_CRCCALCULATION_DISABLE
#define SPI_CRCCALCULATION_ENABLED      SPI_CRCCALCULATION_ENABLE

#define SPI_NSS_PULSE_DISABLED          SPI_NSS_PULSE_DISABLE
#define SPI_NSS_PULSE_ENABLED           SPI_NSS_PULSE_ENABLE

/**
  * @}
  */
  
/** @defgroup HAL_TIM_Aliased_Defines HAL TIM Aliased Defines maintained for legacy purpose
  * @{
  */
#define CCER_CCxE_MASK                   TIM_CCER_CCxE_MASK
#define CCER_CCxNE_MASK                  TIM_CCER_CCxNE_MASK
  
#define TIM_DMABase_CR1                  TIM_DMABASE_CR1
#define TIM_DMABase_CR2                  TIM_DMABASE_CR2
#define TIM_DMABase_SMCR                 TIM_DMABASE_SMCR
#define TIM_DMABase_DIER                 TIM_DMABASE_DIER
#define TIM_DMABase_SR                   TIM_DMABASE_SR
#define TIM_DMABase_EGR                  TIM_DMABASE_EGR
#define TIM_DMABase_CCMR1                TIM_DMABASE_CCMR1
#define TIM_DMABase_CCMR2                TIM_DMABASE_CCMR2
#define TIM_DMABase_CCER                 TIM_DMABASE_CCER
#define TIM_DMABase_CNT                  TIM_DMABASE_CNT
#define TIM_DMABase_PSC                  TIM_DMABASE_PSC
#define TIM_DMABase_ARR                  TIM_DMABASE_ARR
#define TIM_DMABase_RCR                  TIM_DMABASE_RCR
#define TIM_DMABase_CCR1                 TIM_DMABASE_CCR1
#define TIM_DMABase_CCR2                 TIM_DMABASE_CCR2
#define TIM_DMABase_CCR3                 TIM_DMABASE_CCR3
#define TIM_DMABase_CCR4                 TIM_DMABASE_CCR4
#define TIM_DMABase_BDTR                 TIM_DMABASE_BDTR
#define TIM_DMABase_DCR                  TIM_DMABASE_DCR
#define TIM_DMABase_DMAR                 TIM_DMABASE_DMAR
#define TIM_DMABase_OR1                  TIM_DMABASE_OR1
#define TIM_DMABase_CCMR3                TIM_DMABASE_CCMR3
#define TIM_DMABase_CCR5                 TIM_DMABASE_CCR5
#define TIM_DMABase_CCR6                 TIM_DMABASE_CCR6
#define TIM_DMABase_OR2                  TIM_DMABASE_OR2
#define TIM_DMABase_OR3                  TIM_DMABASE_OR3

#define TIM_EventSource_Update           TIM_EVENTSOURCE_UPDATE
#define TIM_EventSource_CC1              TIM_EVENTSOURCE_CC1
#define TIM_EventSource_CC2              TIM_EVENTSOURCE_CC2
#define TIM_EventSource_CC3              TIM_EVENTSOURCE_CC3
#define TIM_EventSource_CC4              TIM_EVENTSOURCE_CC4
#define TIM_EventSource_COM              TIM_EVENTSOURCE_COM
#define TIM_EventSource_Trigger          TIM_EVENTSOURCE_TRIGGER
#define TIM_EventSource_Break            TIM_EVENTSOURCE_BREAK
#define TIM_EventSource_Break2           TIM_EVENTSOURCE_BREAK2

#define TIM_DMABurstLength_1Transfer     TIM_DMABURSTLENGTH_1TRANSFER
#define TIM_DMABurstLength_2Transfers    TIM_DMABURSTLENGTH_2TRANSFERS
#define TIM_DMABurstLength_3Transfers    TIM_DMABURSTLENGTH_3TRANSFERS
#define TIM_DMABurstLength_4Transfers    TIM_DMABURSTLENGTH_4TRANSFERS
#define TIM_DMABurstLength_5Transfers    TIM_DMABURSTLENGTH_5TRANSFERS
#define TIM_DMABurstLength_6Transfers    TIM_DMABURSTLENGTH_6TRANSFERS
#define TIM_DMABurstLength_7Transfers    TIM_DMABURSTLENGTH_7TRANSFERS
#define TIM_DMABurstLength_8Transfers    TIM_DMABURSTLENGTH_8TRANSFERS
#define TIM_DMABurstLength_9Transfers    TIM_DMABURSTLENGTH_9TRANSFERS
#define TIM_DMABurstLength_10Transfers   TIM_DMABURSTLENGTH_10TRANSFERS
#define TIM_DMABurstLength_11Transfers   TIM_DMABURSTLENGTH_11TRANSFERS
#define TIM_DMABurstLength_12Transfers   TIM_DMABURSTLENGTH_12TRANSFERS
#define TIM_DMABurstLength_13Transfers   TIM_DMABURSTLENGTH_13TRANSFERS
#define TIM_DMABurstLength_14Transfers   TIM_DMABURSTLENGTH_14TRANSFERS
#define TIM_DMABurstLength_15Transfers   TIM_DMABURSTLENGTH_15TRANSFERS
#define TIM_DMABurstLength_16Transfers   TIM_DMABURSTLENGTH_16TRANSFERS
#define TIM_DMABurstLength_17Transfers   TIM_DMABURSTLENGTH_17TRANSFERS
#define TIM_DMABurstLength_18Transfers   TIM_DMABURSTLENGTH_18TRANSFERS

/**
  * @}
  */

/** @defgroup HAL_UART_Aliased_Defines HAL UART Aliased Defines maintained for legacy purpose
  * @{
  */
#define UART_ONEBIT_SAMPLING_DISABLED   UART_ONE_BIT_SAMPLE_DISABLE
#define UART_ONEBIT_SAMPLING_ENABLED    UART_ONE_BIT_SAMPLE_ENABLE
#define UART_ONE_BIT_SAMPLE_DISABLED    UART_ONE_BIT_SAMPLE_DISABLE
#define UART_ONE_BIT_SAMPLE_ENABLED     UART_ONE_BIT_SAMPLE_ENABLE

#define __HAL_UART_ONEBIT_ENABLE        __HAL_UART_ONE_BIT_SAMPLE_ENABLE
#define __HAL_UART_ONEBIT_DISABLE       __HAL_UART_ONE_BIT_SAMPLE_DISABLE

#define __DIV_SAMPLING16                UART_DIV_SAMPLING16
#define __DIVMANT_SAMPLING16            UART_DIVMANT_SAMPLING16
#define __DIVFRAQ_SAMPLING16            UART_DIVFRAQ_SAMPLING16
#define __UART_BRR_SAMPLING16           UART_BRR_SAMPLING16

#define __DIV_SAMPLING8                 UART_DIV_SAMPLING8
#define __DIVMANT_SAMPLING8             UART_DIVMANT_SAMPLING8
#define __DIVFRAQ_SAMPLING8             UART_DIVFRAQ_SAMPLING8
#define __UART_BRR_SAMPLING8            UART_BRR_SAMPLING8

#define UART_WAKEUPMETHODE_IDLELINE     UART_WAKEUPMETHOD_IDLELINE
#define UART_WAKEUPMETHODE_ADDRESSMARK  UART_WAKEUPMETHOD_ADDRESSMARK

/**
  * @}
  */

  
/** @defgroup HAL_USART_Aliased_Defines HAL USART Aliased Defines maintained for legacy purpose
  * @{
  */

#define USART_CLOCK_DISABLED            USART_CLOCK_DISABLE
#define USART_CLOCK_ENABLED             USART_CLOCK_ENABLE

#define USARTNACK_ENABLED               USART_NACK_ENABLE
#define USARTNACK_DISABLED              USART_NACK_DISABLE
/**
  * @}
  */

/** @defgroup HAL_WWDG_Aliased_Defines HAL WWDG Aliased Defines maintained for legacy purpose
  * @{
  */
#define CFR_BASE                    WWDG_CFR_BASE

/**
  * @}
  */

/** @defgroup HAL_CAN_Aliased_Defines HAL CAN Aliased Defines maintained for legacy purpose
  * @{
  */
#define CAN_FilterFIFO0             CAN_FILTER_FIFO0
#define CAN_FilterFIFO1             CAN_FILTER_FIFO1
#define CAN_IT_RQCP0                CAN_IT_TME
#define CAN_IT_RQCP1                CAN_IT_TME
#define CAN_IT_RQCP2                CAN_IT_TME
#define INAK_TIMEOUT                CAN_TIMEOUT_VALUE
#define SLAK_TIMEOUT                CAN_TIMEOUT_VALUE
#define CAN_TXSTATUS_FAILED         ((uint8_t)0x00)
#define CAN_TXSTATUS_OK             ((uint8_t)0x01)
#define CAN_TXSTATUS_PENDING        ((uint8_t)0x02)

/**
  * @}
  */
  
/** @defgroup HAL_ETH_Aliased_Defines HAL ETH Aliased Defines maintained for legacy purpose
  * @{
  */

#define VLAN_TAG                ETH_VLAN_TAG
#define MIN_ETH_PAYLOAD         ETH_MIN_ETH_PAYLOAD
#define MAX_ETH_PAYLOAD         ETH_MAX_ETH_PAYLOAD
#define JUMBO_FRAME_PAYLOAD     ETH_JUMBO_FRAME_PAYLOAD
#define MACMIIAR_CR_MASK        ETH_MACMIIAR_CR_MASK
#define MACCR_CLEAR_MASK        ETH_MACCR_CLEAR_MASK
#define MACFCR_CLEAR_MASK       ETH_MACFCR_CLEAR_MASK
#define DMAOMR_CLEAR_MASK       ETH_DMAOMR_CLEAR_MASK

#define ETH_MMCCR              ((uint32_t)0x00000100)  
#define ETH_MMCRIR             ((uint32_t)0x00000104)  
#define ETH_MMCTIR             ((uint32_t)0x00000108)  
#define ETH_MMCRIMR            ((uint32_t)0x0000010C)  
#define ETH_MMCTIMR            ((uint32_t)0x00000110)  
#define ETH_MMCTGFSCCR         ((uint32_t)0x0000014C)  
#define ETH_MMCTGFMSCCR        ((uint32_t)0x00000150)  
#define ETH_MMCTGFCR           ((uint32_t)0x00000168)  
#define ETH_MMCRFCECR          ((uint32_t)0x00000194)  
#define ETH_MMCRFAECR          ((uint32_t)0x00000198)  
#define ETH_MMCRGUFCR          ((uint32_t)0x000001C4) 

/**
  * @}
  */

/** @defgroup HAL_PPP_Aliased_Defines HAL PPP Aliased Defines maintained for legacy purpose
  * @{
  */
  
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @defgroup HAL_CRYP_Aliased_Functions HAL CRYP Aliased Functions maintained for legacy purpose
  * @{
  */
#define HAL_CRYP_ComputationCpltCallback     HAL_CRYPEx_ComputationCpltCallback
/**
  * @}
  */  

/** @defgroup HAL_HASH_Aliased_Functions HAL HASH Aliased Functions maintained for legacy purpose
  * @{
  */ 
  
#define HAL_HMAC_MD5_Finish          HAL_HASH_MD5_Finish
#define HAL_HMAC_SHA1_Finish         HAL_HASH_SHA1_Finish
#define HAL_HMAC_SHA224_Finish       HAL_HASH_SHA224_Finish
#define HAL_HMAC_SHA256_Finish       HAL_HASH_SHA256_Finish

/*HASH Algorithm Selection*/

#define HASH_AlgoSelection_SHA1      HASH_ALGOSELECTION_SHA1 
#define HASH_AlgoSelection_SHA224    HASH_ALGOSELECTION_SHA224
#define HASH_AlgoSelection_SHA256    HASH_ALGOSELECTION_SHA256
#define HASH_AlgoSelection_MD5       HASH_ALGOSELECTION_MD5

#define HASH_AlgoMode_HASH         HASH_ALGOMODE_HASH 
#define HASH_AlgoMode_HMAC         HASH_ALGOMODE_HMAC

#define HASH_HMACKeyType_ShortKey  HASH_HMAC_KEYTYPE_SHORTKEY
#define HASH_HMACKeyType_LongKey   HASH_HMAC_KEYTYPE_LONGKEY
/**
  * @}
  */
  
/** @defgroup HAL_Aliased_Functions HAL Generic Aliased Functions maintained for legacy purpose
  * @{
  */
#define HAL_EnableDBGSleepMode HAL_DBGMCU_EnableDBGSleepMode
#define HAL_DisableDBGSleepMode HAL_DBGMCU_DisableDBGSleepMode
#define HAL_EnableDBGStopMode HAL_DBGMCU_EnableDBGStopMode
#define HAL_DisableDBGStopMode HAL_DBGMCU_DisableDBGStopMode
#define HAL_EnableDBGStandbyMode HAL_DBGMCU_EnableDBGStandbyMode
#define HAL_DisableDBGStandbyMode HAL_DBGMCU_DisableDBGStandbyMode
#define HAL_DBG_LowPowerConfig(Periph, cmd) ((cmd==ENABLE)? HAL_DBGMCU_DBG_EnableLowPowerConfig(Periph) : HAL_DBGMCU_DBG_DisableLowPowerConfig(Periph))
#define HAL_VREFINT_OutputSelect  HAL_SYSCFG_VREFINT_OutputSelect
#define HAL_Lock_Cmd(cmd) ((cmd==ENABLE) ? HAL_SYSCFG_Enable_Lock_VREFINT() : HAL_SYSCFG_Disable_Lock_VREFINT())
#define HAL_VREFINT_Cmd(cmd) ((cmd==ENABLE)? HAL_SYSCFG_EnableVREFINT() : HAL_SYSCFG_DisableVREFINT())
#define HAL_ADC_EnableBuffer_Cmd(cmd)  ((cmd==ENABLE) ? HAL_ADCEx_EnableVREFINT() : HAL_ADCEx_DisableVREFINT())
#define HAL_ADC_EnableBufferSensor_Cmd(cmd) ((cmd==ENABLE) ?  HAL_ADCEx_EnableVREFINTTempSensor() : HAL_ADCEx_DisableVREFINTTempSensor())
/**
  * @}
  */

/** @defgroup HAL_FLASH_Aliased_Functions HAL FLASH Aliased Functions maintained for legacy purpose
  * @{
  */
#define FLASH_HalfPageProgram      HAL_FLASHEx_HalfPageProgram
#define FLASH_EnableRunPowerDown   HAL_FLASHEx_EnableRunPowerDown
#define FLASH_DisableRunPowerDown  HAL_FLASHEx_DisableRunPowerDown
#define HAL_DATA_EEPROMEx_Unlock   HAL_FLASHEx_DATAEEPROM_Unlock
#define HAL_DATA_EEPROMEx_Lock     HAL_FLASHEx_DATAEEPROM_Lock
#define HAL_DATA_EEPROMEx_Erase    HAL_FLASHEx_DATAEEPROM_Erase
#define HAL_DATA_EEPROMEx_Program  HAL_FLASHEx_DATAEEPROM_Program

 /**
  * @}
  */

/** @defgroup HAL_I2C_Aliased_Functions HAL I2C Aliased Functions maintained for legacy purpose
  * @{
  */
#define HAL_I2CEx_AnalogFilter_Config      HAL_I2CEx_ConfigAnalogFilter
#define HAL_I2CEx_DigitalFilter_Config     HAL_I2CEx_ConfigDigitalFilter

#define HAL_I2CFastModePlusConfig(SYSCFG_I2CFastModePlus, cmd) ((cmd==ENABLE)? HAL_I2CEx_EnableFastModePlus(SYSCFG_I2CFastModePlus): HAL_I2CEx_DisableFastModePlus(SYSCFG_I2CFastModePlus))
 /**
  * @}
  */

/** @defgroup HAL_PWR_Aliased HAL PWR Aliased maintained for legacy purpose
  * @{
  */
#define HAL_PWR_PVDConfig                             HAL_PWR_ConfigPVD
#define HAL_PWR_DisableBkUpReg                        HAL_PWREx_DisableBkUpReg
#define HAL_PWR_DisableFlashPowerDown                 HAL_PWREx_DisableFlashPowerDown
#define HAL_PWR_DisableVddio2Monitor                  HAL_PWREx_DisableVddio2Monitor
#define HAL_PWR_EnableBkUpReg                         HAL_PWREx_EnableBkUpReg
#define HAL_PWR_EnableFlashPowerDown                  HAL_PWREx_EnableFlashPowerDown
#define HAL_PWR_EnableVddio2Monitor                   HAL_PWREx_EnableVddio2Monitor
#define HAL_PWR_PVD_PVM_IRQHandler                    HAL_PWREx_PVD_PVM_IRQHandler
#define HAL_PWR_PVDLevelConfig                        HAL_PWR_ConfigPVD
#define HAL_PWR_Vddio2Monitor_IRQHandler              HAL_PWREx_Vddio2Monitor_IRQHandler
#define HAL_PWR_Vddio2MonitorCallback                 HAL_PWREx_Vddio2MonitorCallback
#define HAL_PWREx_ActivateOverDrive                   HAL_PWREx_EnableOverDrive
#define HAL_PWREx_DeactivateOverDrive                 HAL_PWREx_DisableOverDrive
#define HAL_PWREx_DisableSDADCAnalog                  HAL_PWREx_DisableSDADC
#define HAL_PWREx_EnableSDADCAnalog                   HAL_PWREx_EnableSDADC
#define HAL_PWREx_PVMConfig                           HAL_PWREx_ConfigPVM

#define PWR_MODE_NORMAL                               PWR_PVD_MODE_NORMAL
#define PWR_MODE_IT_RISING                            PWR_PVD_MODE_IT_RISING
#define PWR_MODE_IT_FALLING                           PWR_PVD_MODE_IT_FALLING
#define PWR_MODE_IT_RISING_FALLING                    PWR_PVD_MODE_IT_RISING_FALLING
#define PWR_MODE_EVENT_RISING                         PWR_PVD_MODE_EVENT_RISING
#define PWR_MODE_EVENT_FALLING                        PWR_PVD_MODE_EVENT_FALLING
#define PWR_MODE_EVENT_RISING_FALLING                 PWR_PVD_MODE_EVENT_RISING_FALLING

#define CR_OFFSET_BB                                  PWR_CR_OFFSET_BB
#define CSR_OFFSET_BB                                 PWR_CSR_OFFSET_BB

#define DBP_BitNumber                                 DBP_BIT_NUMBER
#define PVDE_BitNumber                                PVDE_BIT_NUMBER
#define PMODE_BitNumber                               PMODE_BIT_NUMBER
#define EWUP_BitNumber                                EWUP_BIT_NUMBER
#define FPDS_BitNumber                                FPDS_BIT_NUMBER
#define ODEN_BitNumber                                ODEN_BIT_NUMBER
#define ODSWEN_BitNumber                              ODSWEN_BIT_NUMBER
#define MRLVDS_BitNumber                              MRLVDS_BIT_NUMBER
#define LPLVDS_BitNumber                              LPLVDS_BIT_NUMBER
#define BRE_BitNumber                                 BRE_BIT_NUMBER

#define PWR_MODE_EVT                                  PWR_PVD_MODE_NORMAL
 
 /**
  * @}
  */  

/** @defgroup HAL_RCC_Aliased_Functions HAL RCC Aliased Functions maintained for legacy purpose
  * @{
  */
#define HAL_RCC_CCSCallback HAL_RCC_CSSCallback
#define HAL_RC48_EnableBuffer_Cmd(cmd) ((cmd==ENABLE) ? HAL_RCCEx_EnableHSI48_VREFINT() : HAL_RCCEx_DisableHSI48_VREFINT())
 
 /**
  * @}
  */
  
/** @defgroup HAL_SMBUS_Aliased_Functions HAL SMBUS Aliased Functions maintained for legacy purpose
  * @{
  */
#define HAL_SMBUS_Slave_Listen_IT          HAL_SMBUS_EnableListen_IT
#define HAL_SMBUS_SlaveAddrCallback        HAL_SMBUS_AddrCallback         
#define HAL_SMBUS_SlaveListenCpltCallback  HAL_SMBUS_ListenCpltCallback   
/**
  * @}
  */

/** @defgroup HAL_SPI_Aliased_Functions HAL SPI Aliased Functions maintained for legacy purpose
  * @{
  */
#define HAL_SPI_FlushRxFifo                HAL_SPIEx_FlushRxFifo
/**
  * @}
  */  

/** @defgroup HAL_TIM_Aliased_Functions HAL TIM Aliased Functions maintained for legacy purpose
  * @{
  */
#define HAL_TIM_DMADelayPulseCplt                       TIM_DMADelayPulseCplt
#define HAL_TIM_DMAError                                TIM_DMAError
#define HAL_TIM_DMACaptureCplt                          TIM_DMACaptureCplt
#define HAL_TIMEx_DMACommutationCplt                    TIMEx_DMACommutationCplt
/**
  * @}
  */
   
/** @defgroup HAL_UART_Aliased_Functions HAL UART Aliased Functions maintained for legacy purpose
  * @{
  */ 
#define HAL_UART_WakeupCallback HAL_UARTEx_WakeupCallback
/**
  * @}
  */
   
  
   /** @defgroup HAL_PPP_Aliased_Functions HAL PPP Aliased Functions maintained for legacy purpose
  * @{
  */
  
/**
  * @}
  */

/* Exported macros ------------------------------------------------------------*/

/** @defgroup HAL_AES_Aliased_Macros HAL CRYP Aliased Macros maintained for legacy purpose
  * @{
  */
#define AES_IT_CC                      CRYP_IT_CC
#define AES_IT_ERR                     CRYP_IT_ERR
#define AES_FLAG_CCF                   CRYP_FLAG_CCF
/**
  * @}
  */  
  
/** @defgroup HAL_Aliased_Macros HAL Generic Aliased Macros maintained for legacy purpose
  * @{
  */
#define __HAL_GET_BOOT_MODE                   __HAL_SYSCFG_GET_BOOT_MODE
#define __HAL_REMAPMEMORY_FLASH               __HAL_SYSCFG_REMAPMEMORY_FLASH
#define __HAL_REMAPMEMORY_SYSTEMFLASH         __HAL_SYSCFG_REMAPMEMORY_SYSTEMFLASH
#define __HAL_REMAPMEMORY_SRAM                __HAL_SYSCFG_REMAPMEMORY_SRAM
#define __HAL_REMAPMEMORY_FMC                 __HAL_SYSCFG_REMAPMEMORY_FMC
#define __HAL_REMAPMEMORY_FMC_SDRAM           __HAL_SYSCFG_REMAPMEMORY_FMC_SDRAM 
#define __HAL_FMC_BANK                        __HAL_SYSCFG_FMC_BANK
#define __HAL_GET_FLAG                        __HAL_SYSCFG_GET_FLAG
#define __HAL_CLEAR_FLAG                      __HAL_SYSCFG_CLEAR_FLAG
#define SYSCFG_FLAG_VREF_READY                SYSCFG_FLAG_VREFINT_READY
#define SYSCFG_FLAG_RC48                      RCC_FLAG_HSI48
#define IS_SYSCFG_FASTMODEPLUS_CONFIG         IS_I2C_FASTMODEPLUS
#define UFB_MODE_BitNumber                    UFB_MODE_BIT_NUMBER
#define CMP_PD_BitNumber                      CMP_PD_BIT_NUMBER

/**
  * @}
  */

   
/** @defgroup HAL_ADC_Aliased_Macros HAL ADC Aliased Macros maintained for legacy purpose
  * @{
  */
#define __ADC_ENABLE                                     __HAL_ADC_ENABLE
#define __ADC_DISABLE                                    __HAL_ADC_DISABLE
#define __HAL_ADC_ENABLING_CONDITIONS                    ADC_ENABLING_CONDITIONS
#define __HAL_ADC_DISABLING_CONDITIONS                   ADC_DISABLING_CONDITIONS
#define __HAL_ADC_IS_ENABLED                             ADC_IS_ENABLE
#define __ADC_IS_ENABLED                                 ADC_IS_ENABLE
#define __HAL_ADC_IS_SOFTWARE_START_REGULAR              ADC_IS_SOFTWARE_START_REGULAR
#define __HAL_ADC_IS_SOFTWARE_START_INJECTED             ADC_IS_SOFTWARE_START_INJECTED
#define __HAL_ADC_IS_CONVERSION_ONGOING_REGULAR_INJECTED ADC_IS_CONVERSION_ONGOING_REGULAR_INJECTED
#define __HAL_ADC_IS_CONVERSION_ONGOING_REGULAR          ADC_IS_CONVERSION_ONGOING_REGULAR
#define __HAL_ADC_IS_CONVERSION_ONGOING_INJECTED         ADC_IS_CONVERSION_ONGOING_INJECTED
#define __HAL_ADC_IS_CONVERSION_ONGOING                  ADC_IS_CONVERSION_ONGOING
#define __HAL_ADC_CLEAR_ERRORCODE                        ADC_CLEAR_ERRORCODE

#define __HAL_ADC_GET_RESOLUTION                         ADC_GET_RESOLUTION
#define __HAL_ADC_JSQR_RK                                ADC_JSQR_RK
#define __HAL_ADC_CFGR_AWD1CH                            ADC_CFGR_AWD1CH_SHIFT
#define __HAL_ADC_CFGR_AWD23CR                           ADC_CFGR_AWD23CR
#define __HAL_ADC_CFGR_INJECT_AUTO_CONVERSION            ADC_CFGR_INJECT_AUTO_CONVERSION
#define __HAL_ADC_CFGR_INJECT_CONTEXT_QUEUE              ADC_CFGR_INJECT_CONTEXT_QUEUE
#define __HAL_ADC_CFGR_INJECT_DISCCONTINUOUS             ADC_CFGR_INJECT_DISCCONTINUOUS
#define __HAL_ADC_CFGR_REG_DISCCONTINUOUS                ADC_CFGR_REG_DISCCONTINUOUS
#define __HAL_ADC_CFGR_DISCONTINUOUS_NUM                 ADC_CFGR_DISCONTINUOUS_NUM
#define __HAL_ADC_CFGR_AUTOWAIT                          ADC_CFGR_AUTOWAIT
#define __HAL_ADC_CFGR_CONTINUOUS                        ADC_CFGR_CONTINUOUS
#define __HAL_ADC_CFGR_OVERRUN                           ADC_CFGR_OVERRUN
#define __HAL_ADC_CFGR_DMACONTREQ                        ADC_CFGR_DMACONTREQ
#define __HAL_ADC_CFGR_EXTSEL                            ADC_CFGR_EXTSEL_SET
#define __HAL_ADC_JSQR_JEXTSEL                           ADC_JSQR_JEXTSEL_SET
#define __HAL_ADC_OFR_CHANNEL                            ADC_OFR_CHANNEL
#define __HAL_ADC_DIFSEL_CHANNEL                         ADC_DIFSEL_CHANNEL
#define __HAL_ADC_CALFACT_DIFF_SET                       ADC_CALFACT_DIFF_SET
#define __HAL_ADC_CALFACT_DIFF_GET                       ADC_CALFACT_DIFF_GET
#define __HAL_ADC_TRX_HIGHTHRESHOLD                      ADC_TRX_HIGHTHRESHOLD

#define __HAL_ADC_OFFSET_SHIFT_RESOLUTION                ADC_OFFSET_SHIFT_RESOLUTION
#define __HAL_ADC_AWD1THRESHOLD_SHIFT_RESOLUTION         ADC_AWD1THRESHOLD_SHIFT_RESOLUTION
#define __HAL_ADC_AWD23THRESHOLD_SHIFT_RESOLUTION        ADC_AWD23THRESHOLD_SHIFT_RESOLUTION
#define __HAL_ADC_COMMON_REGISTER                        ADC_COMMON_REGISTER
#define __HAL_ADC_COMMON_CCR_MULTI                       ADC_COMMON_CCR_MULTI
#define __HAL_ADC_MULTIMODE_IS_ENABLED                   ADC_MULTIMODE_IS_ENABLE
#define __ADC_MULTIMODE_IS_ENABLED                       ADC_MULTIMODE_IS_ENABLE
#define __HAL_ADC_NONMULTIMODE_OR_MULTIMODEMASTER        ADC_NONMULTIMODE_OR_MULTIMODEMASTER
#define __HAL_ADC_COMMON_ADC_OTHER                       ADC_COMMON_ADC_OTHER
#define __HAL_ADC_MULTI_SLAVE                            ADC_MULTI_SLAVE

#define __HAL_ADC_SQR1_L                                 ADC_SQR1_L_SHIFT
#define __HAL_ADC_JSQR_JL                                ADC_JSQR_JL_SHIFT
#define __HAL_ADC_JSQR_RK_JL                             ADC_JSQR_RK_JL
#define __HAL_ADC_CR1_DISCONTINUOUS_NUM                  ADC_CR1_DISCONTINUOUS_NUM
#define __HAL_ADC_CR1_SCAN                               ADC_CR1_SCAN_SET
#define __HAL_ADC_CONVCYCLES_MAX_RANGE                   ADC_CONVCYCLES_MAX_RANGE
#define __HAL_ADC_CLOCK_PRESCALER_RANGE                  ADC_CLOCK_PRESCALER_RANGE
#define __HAL_ADC_GET_CLOCK_PRESCALER                    ADC_GET_CLOCK_PRESCALER

#define __HAL_ADC_SQR1                                   ADC_SQR1
#define __HAL_ADC_SMPR1                                  ADC_SMPR1
#define __HAL_ADC_SMPR2                                  ADC_SMPR2
#define __HAL_ADC_SQR3_RK                                ADC_SQR3_RK
#define __HAL_ADC_SQR2_RK                                ADC_SQR2_RK
#define __HAL_ADC_SQR1_RK                                ADC_SQR1_RK
#define __HAL_ADC_CR2_CONTINUOUS                         ADC_CR2_CONTINUOUS
#define __HAL_ADC_CR1_DISCONTINUOUS                      ADC_CR1_DISCONTINUOUS
#define __HAL_ADC_CR1_SCANCONV                           ADC_CR1_SCANCONV
#define __HAL_ADC_CR2_EOCSelection                       ADC_CR2_EOCSelection
#define __HAL_ADC_CR2_DMAContReq                         ADC_CR2_DMAContReq
#define __HAL_ADC_GET_RESOLUTION                         ADC_GET_RESOLUTION
#define __HAL_ADC_JSQR                                   ADC_JSQR

#define __HAL_ADC_CHSELR_CHANNEL                         ADC_CHSELR_CHANNEL
#define __HAL_ADC_CFGR1_REG_DISCCONTINUOUS               ADC_CFGR1_REG_DISCCONTINUOUS
#define __HAL_ADC_CFGR1_AUTOOFF                          ADC_CFGR1_AUTOOFF
#define __HAL_ADC_CFGR1_AUTOWAIT                         ADC_CFGR1_AUTOWAIT
#define __HAL_ADC_CFGR1_CONTINUOUS                       ADC_CFGR1_CONTINUOUS
#define __HAL_ADC_CFGR1_OVERRUN                          ADC_CFGR1_OVERRUN
#define __HAL_ADC_CFGR1_SCANDIR                          ADC_CFGR1_SCANDIR
#define __HAL_ADC_CFGR1_DMACONTREQ                       ADC_CFGR1_DMACONTREQ

/**
  * @}
  */

/** @defgroup HAL_DAC_Aliased_Macros HAL DAC Aliased Macros maintained for legacy purpose
  * @{
  */
#define __HAL_DHR12R1_ALIGNEMENT                        DAC_DHR12R1_ALIGNMENT
#define __HAL_DHR12R2_ALIGNEMENT                        DAC_DHR12R2_ALIGNMENT
#define __HAL_DHR12RD_ALIGNEMENT                        DAC_DHR12RD_ALIGNMENT
   
/**
  * @}
  */
   
/** @defgroup HAL_DBGMCU_Aliased_Macros HAL DBGMCU Aliased Macros maintained for legacy purpose
  * @{
  */
#define __HAL_FREEZE_TIM1_DBGMCU __HAL_DBGMCU_FREEZE_TIM1
#define __HAL_UNFREEZE_TIM1_DBGMCU __HAL_DBGMCU_UNFREEZE_TIM1
#define __HAL_FREEZE_TIM2_DBGMCU __HAL_DBGMCU_FREEZE_TIM2
#define __HAL_UNFREEZE_TIM2_DBGMCU __HAL_DBGMCU_UNFREEZE_TIM2
#define __HAL_FREEZE_TIM3_DBGMCU __HAL_DBGMCU_FREEZE_TIM3
#define __HAL_UNFREEZE_TIM3_DBGMCU __HAL_DBGMCU_UNFREEZE_TIM3
#define __HAL_FREEZE_TIM4_DBGMCU __HAL_DBGMCU_FREEZE_TIM4
#define __HAL_UNFREEZE_TIM4_DBGMCU __HAL_DBGMCU_UNFREEZE_TIM4
#define __HAL_FREEZE_TIM5_DBGMCU __HAL_DBGMCU_FREEZE_TIM5
#define __HAL_UNFREEZE_TIM5_DBGMCU __HAL_DBGMCU_UNFREEZE_TIM5
#define __HAL_FREEZE_TIM6_DBGMCU __HAL_DBGMCU_FREEZE_TIM6
#define __HAL_UNFREEZE_TIM6_DBGMCU __HAL_DBGMCU_UNFREEZE_TIM6
#define __HAL_FREEZE_TIM7_DBGMCU __HAL_DBGMCU_FREEZE_TIM7
#define __HAL_UNFREEZE_TIM7_DBGMCU __HAL_DBGMCU_UNFREEZE_TIM7
#define __HAL_FREEZE_TIM8_DBGMCU __HAL_DBGMCU_FREEZE_TIM8
#define __HAL_UNFREEZE_TIM8_DBGMCU __HAL_DBGMCU_UNFREEZE_TIM8

#define __HAL_FREEZE_TIM9_DBGMCU __HAL_DBGMCU_FREEZE_TIM9
#define __HAL_UNFREEZE_TIM9_DBGMCU __HAL_DBGMCU_UNFREEZE_TIM9
#define __HAL_FREEZE_TIM10_DBGMCU __HAL_DBGMCU_FREEZE_TIM10
#define __HAL_UNFREEZE_TIM10_DBGMCU __HAL_DBGMCU_UNFREEZE_TIM10
#define __HAL_FREEZE_TIM11_DBGMCU __HAL_DBGMCU_FREEZE_TIM11
#define __HAL_UNFREEZE_TIM11_DBGMCU __HAL_DBGMCU_UNFREEZE_TIM11
#define __HAL_FREEZE_TIM12_DBGMCU __HAL_DBGMCU_FREEZE_TIM12
#define __HAL_UNFREEZE_TIM12_DBGMCU __HAL_DBGMCU_UNFREEZE_TIM12
#define __HAL_FREEZE_TIM13_DBGMCU __HAL_DBGMCU_FREEZE_TIM13
#define __HAL_UNFREEZE_TIM13_DBGMCU __HAL_DBGMCU_UNFREEZE_TIM13
#define __HAL_FREEZE_TIM14_DBGMCU __HAL_DBGMCU_FREEZE_TIM14
#define __HAL_UNFREEZE_TIM14_DBGMCU __HAL_DBGMCU_UNFREEZE_TIM14
#define __HAL_FREEZE_CAN2_DBGMCU __HAL_DBGMCU_FREEZE_CAN2
#define __HAL_UNFREEZE_CAN2_DBGMCU __HAL_DBGMCU_UNFREEZE_CAN2


#define __HAL_FREEZE_TIM15_DBGMCU __HAL_DBGMCU_FREEZE_TIM15
#define __HAL_UNFREEZE_TIM15_DBGMCU __HAL_DBGMCU_UNFREEZE_TIM15
#define __HAL_FREEZE_TIM16_DBGMCU __HAL_DBGMCU_FREEZE_TIM16
#define __HAL_UNFREEZE_TIM16_DBGMCU __HAL_DBGMCU_UNFREEZE_TIM16
#define __HAL_FREEZE_TIM17_DBGMCU __HAL_DBGMCU_FREEZE_TIM17
#define __HAL_UNFREEZE_TIM17_DBGMCU __HAL_DBGMCU_UNFREEZE_TIM17
#define __HAL_FREEZE_RTC_DBGMCU __HAL_DBGMCU_FREEZE_RTC
#define __HAL_UNFREEZE_RTC_DBGMCU __HAL_DBGMCU_UNFREEZE_RTC
#define __HAL_FREEZE_WWDG_DBGMCU __HAL_DBGMCU_FREEZE_WWDG
#define __HAL_UNFREEZE_WWDG_DBGMCU __HAL_DBGMCU_UNFREEZE_WWDG
#define __HAL_FREEZE_IWDG_DBGMCU __HAL_DBGMCU_FREEZE_IWDG
#define __HAL_UNFREEZE_IWDG_DBGMCU __HAL_DBGMCU_UNFREEZE_IWDG
#define __HAL_FREEZE_I2C1_TIMEOUT_DBGMCU __HAL_DBGMCU_FREEZE_I2C1_TIMEOUT
#define __HAL_UNFREEZE_I2C1_TIMEOUT_DBGMCU __HAL_DBGMCU_UNFREEZE_I2C1_TIMEOUT
#define __HAL_FREEZE_I2C2_TIMEOUT_DBGMCU __HAL_DBGMCU_FREEZE_I2C2_TIMEOUT
#define __HAL_UNFREEZE_I2C2_TIMEOUT_DBGMCU __HAL_DBGMCU_UNFREEZE_I2C2_TIMEOUT
#define __HAL_FREEZE_I2C3_TIMEOUT_DBGMCU __HAL_DBGMCU_FREEZE_I2C3_TIMEOUT
#define __HAL_UNFREEZE_I2C3_TIMEOUT_DBGMCU __HAL_DBGMCU_UNFREEZE_I2C3_TIMEOUT
#define __HAL_FREEZE_CAN1_DBGMCU __HAL_DBGMCU_FREEZE_CAN1
#define __HAL_UNFREEZE_CAN1_DBGMCU __HAL_DBGMCU_UNFREEZE_CAN1
#define __HAL_FREEZE_LPTIM1_DBGMCU __HAL_DBGMCU_FREEZE_LPTIM1
#define __HAL_UNFREEZE_LPTIM1_DBGMCU __HAL_DBGMCU_UNFREEZE_LPTIM1
#define __HAL_FREEZE_LPTIM2_DBGMCU __HAL_DBGMCU_FREEZE_LPTIM2
#define __HAL_UNFREEZE_LPTIM2_DBGMCU __HAL_DBGMCU_UNFREEZE_LPTIM2

/**
  * @}
  */

/** @defgroup HAL_COMP_Aliased_Macros HAL COMP Aliased Macros maintained for legacy purpose
  * @{
  */

#define __HAL_COMP_EXTI_RISING_IT_ENABLE(__EXTILINE__)   (((__EXTILINE__)  == COMP_EXTI_LINE_COMP1) ? __HAL_COMP_COMP1_EXTI_ENABLE_RISING_EDGE() : \
                                                          __HAL_COMP_COMP2_EXTI_ENABLE_RISING_EDGE())
#define __HAL_COMP_EXTI_RISING_IT_DISABLE(__EXTILINE__)  (((__EXTILINE__)  == COMP_EXTI_LINE_COMP1) ? __HAL_COMP_COMP1_EXTI_ENABLE_RISING_EDGE() : \
                                                          __HAL_COMP_COMP2_EXTI_DISABLE_RISING_EDGE())
#define __HAL_COMP_EXTI_FALLING_IT_ENABLE(__EXTILINE__)  (((__EXTILINE__)  == COMP_EXTI_LINE_COMP1) ? __HAL_COMP_COMP1_EXTI_ENABLE_FALLING_EDGE() : \
                                                          __HAL_COMP_COMP2_EXTI_ENABLE_FALLING_EDGE())
#define __HAL_COMP_EXTI_FALLING_IT_DISABLE(__EXTILINE__)   (((__EXTILINE__)  == COMP_EXTI_LINE_COMP1) ? __HAL_COMP_COMP1_EXTI_ENABLE_FALLING_EDGE() : \
                                                          __HAL_COMP_COMP2_EXTI_DISABLE_FALLING_EDGE())
#define __HAL_COMP_EXTI_ENABLE_IT(__EXTILINE__)   (((__EXTILINE__)  == COMP_EXTI_LINE_COMP1) ? __HAL_COMP_COMP1_EXTI_ENABLE_IT() : \
                                                          __HAL_COMP_COMP2_EXTI_ENABLE_IT())
#define __HAL_COMP_EXTI_DISABLE_IT(__EXTILINE__)   (((__EXTILINE__)  == COMP_EXTI_LINE_COMP1) ? __HAL_COMP_COMP1_EXTI_DISABLE_IT() : \
                                                          __HAL_COMP_COMP2_EXTI_DISABLE_IT())
#define __HAL_COMP_EXTI_GET_FLAG(__FLAG__)   (((__FLAG__)  == COMP_EXTI_LINE_COMP1) ? __HAL_COMP_COMP1_EXTI_GET_FLAG() : \
                                                          __HAL_COMP_COMP2_EXTI_GET_FLAG())
#define __HAL_COMP_EXTI_CLEAR_FLAG(__FLAG__)   (((__FLAG__)  == COMP_EXTI_LINE_COMP1) ? __HAL_COMP_COMP1_EXTI_CLEAR_FLAG() : \
                                                          __HAL_COMP_COMP2_EXTI_CLEAR_FLAG())
#define __HAL_COMP_GET_EXTI_LINE  COMP_GET_EXTI_LINE

/**
  * @}
  */

/** @defgroup HAL_FLASH_Aliased_Macros HAL FLASH Aliased Macros maintained for legacy purpose
  * @{
  */

#define IS_WRPAREA          IS_OB_WRPAREA
#define IS_TYPEPROGRAM      IS_FLASH_TYPEPROGRAM
#define IS_TYPEPROGRAMFLASH IS_FLASH_TYPEPROGRAM
#define IS_TYPEERASE        IS_FLASH_TYPEERASE

/**
  * @}
  */
  
/** @defgroup HAL_I2C_Aliased_Macros HAL I2C Aliased Macros maintained for legacy purpose
  * @{
  */
  
#define __HAL_I2C_RESET_CR2             I2C_RESET_CR2
#define __HAL_I2C_GENERATE_START        I2C_GENERATE_START
#define __HAL_I2C_FREQ_RANGE            I2C_FREQ_RANGE
#define __HAL_I2C_RISE_TIME             I2C_RISE_TIME
#define __HAL_I2C_SPEED_STANDARD        I2C_SPEED_STANDARD
#define __HAL_I2C_SPEED_FAST            I2C_SPEED_FAST
#define __HAL_I2C_SPEED                 I2C_SPEED
#define __HAL_I2C_7BIT_ADD_WRITE        I2C_7BIT_ADD_WRITE
#define __HAL_I2C_7BIT_ADD_READ         I2C_7BIT_ADD_READ
#define __HAL_I2C_10BIT_ADDRESS         I2C_10BIT_ADDRESS
#define __HAL_I2C_10BIT_HEADER_WRITE    I2C_10BIT_HEADER_WRITE
#define __HAL_I2C_10BIT_HEADER_READ     I2C_10BIT_HEADER_READ
#define __HAL_I2C_MEM_ADD_MSB           I2C_MEM_ADD_MSB
#define __HAL_I2C_MEM_ADD_LSB           I2C_MEM_ADD_LSB
#define __HAL_I2C_FREQRANGE             I2C_FREQRANGE
/**
  * @}
  */
  
/** @defgroup HAL_I2S_Aliased_Macros HAL I2S Aliased Macros maintained for legacy purpose
  * @{
  */
  
#define IS_I2S_INSTANCE                 IS_I2S_ALL_INSTANCE
#define IS_I2S_INSTANCE_EXT             IS_I2S_ALL_INSTANCE_EXT

/**
  * @}
  */

/** @defgroup HAL_IRDA_Aliased_Macros HAL IRDA Aliased Macros maintained for legacy purpose
  * @{
  */
  
#define __IRDA_DISABLE                  __HAL_IRDA_DISABLE
#define __IRDA_ENABLE                   __HAL_IRDA_ENABLE

#define __HAL_IRDA_GETCLOCKSOURCE       IRDA_GETCLOCKSOURCE
#define __HAL_IRDA_MASK_COMPUTATION     IRDA_MASK_COMPUTATION
#define __IRDA_GETCLOCKSOURCE           IRDA_GETCLOCKSOURCE
#define __IRDA_MASK_COMPUTATION         IRDA_MASK_COMPUTATION

#define IS_IRDA_ONEBIT_SAMPLE           IS_IRDA_ONE_BIT_SAMPLE                  


/**
  * @}
  */


/** @defgroup HAL_IWDG_Aliased_Macros HAL IWDG Aliased Macros maintained for legacy purpose
  * @{
  */
#define __HAL_IWDG_ENABLE_WRITE_ACCESS  IWDG_ENABLE_WRITE_ACCESS
#define __HAL_IWDG_DISABLE_WRITE_ACCESS IWDG_DISABLE_WRITE_ACCESS
/**
  * @}
  */


/** @defgroup HAL_LPTIM_Aliased_Macros HAL LPTIM Aliased Macros maintained for legacy purpose
  * @{
  */

#define __HAL_LPTIM_ENABLE_INTERRUPT    __HAL_LPTIM_ENABLE_IT
#define __HAL_LPTIM_DISABLE_INTERRUPT   __HAL_LPTIM_DISABLE_IT
#define __HAL_LPTIM_GET_ITSTATUS        __HAL_LPTIM_GET_IT_SOURCE

/**
  * @}
  */

/** @defgroup HAL_PWR_Aliased_Macros HAL PWR Aliased Macros maintained for legacy purpose
  * @{
  */
#define __HAL_PVD_EVENT_DISABLE                                  __HAL_PWR_PVD_EXTI_DISABLE_EVENT
#define __HAL_PVD_EVENT_ENABLE                                   __HAL_PWR_PVD_EXTI_ENABLE_EVENT
#define __HAL_PVD_EXTI_FALLINGTRIGGER_DISABLE                    __HAL_PWR_PVD_EXTI_DISABLE_FALLING_EDGE
#define __HAL_PVD_EXTI_FALLINGTRIGGER_ENABLE                     __HAL_PWR_PVD_EXTI_ENABLE_FALLING_EDGE
#define __HAL_PVD_EXTI_RISINGTRIGGER_DISABLE                     __HAL_PWR_PVD_EXTI_DISABLE_RISING_EDGE
#define __HAL_PVD_EXTI_RISINGTRIGGER_ENABLE                      __HAL_PWR_PVD_EXTI_ENABLE_RISING_EDGE
#define __HAL_PVM_EVENT_DISABLE                                  __HAL_PWR_PVM_EVENT_DISABLE
#define __HAL_PVM_EVENT_ENABLE                                   __HAL_PWR_PVM_EVENT_ENABLE
#define __HAL_PVM_EXTI_FALLINGTRIGGER_DISABLE                    __HAL_PWR_PVM_EXTI_FALLINGTRIGGER_DISABLE
#define __HAL_PVM_EXTI_FALLINGTRIGGER_ENABLE                     __HAL_PWR_PVM_EXTI_FALLINGTRIGGER_ENABLE
#define __HAL_PVM_EXTI_RISINGTRIGGER_DISABLE                     __HAL_PWR_PVM_EXTI_RISINGTRIGGER_DISABLE
#define __HAL_PVM_EXTI_RISINGTRIGGER_ENABLE                      __HAL_PWR_PVM_EXTI_RISINGTRIGGER_ENABLE
#define __HAL_PWR_INTERNALWAKEUP_DISABLE                         HAL_PWREx_DisableInternalWakeUpLine
#define __HAL_PWR_INTERNALWAKEUP_ENABLE                          HAL_PWREx_EnableInternalWakeUpLine
#define __HAL_PWR_PULL_UP_DOWN_CONFIG_DISABLE                    HAL_PWREx_DisablePullUpPullDownConfig
#define __HAL_PWR_PULL_UP_DOWN_CONFIG_ENABLE                     HAL_PWREx_EnablePullUpPullDownConfig
#define __HAL_PWR_PVD_EXTI_CLEAR_EGDE_TRIGGER()                  __HAL_PWR_PVD_EXTI_DISABLE_RISING_EDGE();__HAL_PWR_PVD_EXTI_DISABLE_FALLING_EDGE()
#define __HAL_PWR_PVD_EXTI_EVENT_DISABLE                         __HAL_PWR_PVD_EXTI_DISABLE_EVENT
#define __HAL_PWR_PVD_EXTI_EVENT_ENABLE                          __HAL_PWR_PVD_EXTI_ENABLE_EVENT
#define __HAL_PWR_PVD_EXTI_FALLINGTRIGGER_DISABLE                __HAL_PWR_PVD_EXTI_DISABLE_FALLING_EDGE
#define __HAL_PWR_PVD_EXTI_FALLINGTRIGGER_ENABLE                 __HAL_PWR_PVD_EXTI_ENABLE_FALLING_EDGE
#define __HAL_PWR_PVD_EXTI_RISINGTRIGGER_DISABLE                 __HAL_PWR_PVD_EXTI_DISABLE_RISING_EDGE
#define __HAL_PWR_PVD_EXTI_RISINGTRIGGER_ENABLE                  __HAL_PWR_PVD_EXTI_ENABLE_RISING_EDGE
#define __HAL_PWR_PVD_EXTI_SET_FALLING_EGDE_TRIGGER              __HAL_PWR_PVD_EXTI_ENABLE_FALLING_EDGE
#define __HAL_PWR_PVD_EXTI_SET_RISING_EDGE_TRIGGER               __HAL_PWR_PVD_EXTI_ENABLE_RISING_EDGE
#define __HAL_PWR_PVM_DISABLE()                                  HAL_PWREx_DisablePVM1();HAL_PWREx_DisablePVM2();HAL_PWREx_DisablePVM3();HAL_PWREx_DisablePVM4()
#define __HAL_PWR_PVM_ENABLE()                                   HAL_PWREx_EnablePVM1();HAL_PWREx_EnablePVM2();HAL_PWREx_EnablePVM3();HAL_PWREx_EnablePVM4()
#define __HAL_PWR_SRAM2CONTENT_PRESERVE_DISABLE                  HAL_PWREx_DisableSRAM2ContentRetention
#define __HAL_PWR_SRAM2CONTENT_PRESERVE_ENABLE                   HAL_PWREx_EnableSRAM2ContentRetention
#define __HAL_PWR_VDDIO2_DISABLE                                 HAL_PWREx_DisableVddIO2
#define __HAL_PWR_VDDIO2_ENABLE                                  HAL_PWREx_EnableVddIO2
#define __HAL_PWR_VDDIO2_EXTI_CLEAR_EGDE_TRIGGER                 __HAL_PWR_VDDIO2_EXTI_DISABLE_FALLING_EDGE
#define __HAL_PWR_VDDIO2_EXTI_SET_FALLING_EGDE_TRIGGER           __HAL_PWR_VDDIO2_EXTI_ENABLE_FALLING_EDGE
#define __HAL_PWR_VDDUSB_DISABLE                                 HAL_PWREx_DisableVddUSB
#define __HAL_PWR_VDDUSB_ENABLE                                  HAL_PWREx_EnableVddUSB

#if defined (STM32F4)
#define __HAL_PVD_EXTI_ENABLE_IT(PWR_EXTI_LINE_PVD)         __HAL_PWR_PVD_EXTI_ENABLE_IT()
#define __HAL_PVD_EXTI_DISABLE_IT(PWR_EXTI_LINE_PVD)        __HAL_PWR_PVD_EXTI_DISABLE_IT()
#define __HAL_PVD_EXTI_GET_FLAG(PWR_EXTI_LINE_PVD)          __HAL_PWR_PVD_EXTI_GET_FLAG()   
#define __HAL_PVD_EXTI_CLEAR_FLAG(PWR_EXTI_LINE_PVD)        __HAL_PWR_PVD_EXTI_CLEAR_FLAG()
#define __HAL_PVD_EXTI_GENERATE_SWIT(PWR_EXTI_LINE_PVD)     __HAL_PWR_PVD_EXTI_GENERATE_SWIT()
#else
#define __HAL_PVD_EXTI_CLEAR_FLAG                                __HAL_PWR_PVD_EXTI_CLEAR_FLAG
#define __HAL_PVD_EXTI_DISABLE_IT                                __HAL_PWR_PVD_EXTI_DISABLE_IT
#define __HAL_PVD_EXTI_ENABLE_IT                                 __HAL_PWR_PVD_EXTI_ENABLE_IT
#define __HAL_PVD_EXTI_GENERATE_SWIT                             __HAL_PWR_PVD_EXTI_GENERATE_SWIT
#define __HAL_PVD_EXTI_GET_FLAG                                  __HAL_PWR_PVD_EXTI_GET_FLAG 
#endif /* STM32F4 */
/**   
  * @}
  */  
  
  
/** @defgroup HAL_RCC_Aliased_Macros HAL RCC Aliased Macros maintained for legacy purpose
  * @{
  */
#define __ADC_CLK_DISABLE __HAL_RCC_ADC_CLK_DISABLE
#define __ADC_CLK_ENABLE __HAL_RCC_ADC_CLK_ENABLE
#define __ADC_CLK_SLEEP_DISABLE __HAL_RCC_ADC_CLK_SLEEP_DISABLE
#define __ADC_CLK_SLEEP_ENABLE __HAL_RCC_ADC_CLK_SLEEP_ENABLE
#define __ADC_FORCE_RESET __HAL_RCC_ADC_FORCE_RESET
#define __ADC_RELEASE_RESET __HAL_RCC_ADC_RELEASE_RESET
#define __ADC1_CLK_DISABLE __HAL_RCC_ADC1_CLK_DISABLE
#define __ADC1_CLK_ENABLE __HAL_RCC_ADC1_CLK_ENABLE
#define __ADC1_FORCE_RESET __HAL_RCC_ADC1_FORCE_RESET
#define __ADC1_RELEASE_RESET __HAL_RCC_ADC1_RELEASE_RESET
#define __ADC2_CLK_DISABLE __HAL_RCC_ADC2_CLK_DISABLE
#define __ADC2_CLK_ENABLE __HAL_RCC_ADC2_CLK_ENABLE
#define __ADC2_FORCE_RESET __HAL_RCC_ADC2_FORCE_RESET
#define __ADC2_RELEASE_RESET __HAL_RCC_ADC2_RELEASE_RESET
#define __ADC3_CLK_DISABLE __HAL_RCC_ADC3_CLK_DISABLE
#define __ADC3_CLK_ENABLE __HAL_RCC_ADC3_CLK_ENABLE
#define __ADC3_FORCE_RESET __HAL_RCC_ADC3_FORCE_RESET
#define __ADC3_RELEASE_RESET __HAL_RCC_ADC3_RELEASE_RESET
#define __AES_CLK_DISABLE __HAL_RCC_AES_CLK_DISABLE
#define __AES_CLK_ENABLE __HAL_RCC_AES_CLK_ENABLE
#define __AES_CLK_SLEEP_DISABLE __HAL_RCC_AES_CLK_SLEEP_DISABLE
#define __AES_CLK_SLEEP_ENABLE __HAL_RCC_AES_CLK_SLEEP_ENABLE
#define __AES_FORCE_RESET __HAL_RCC_AES_FORCE_RESET
#define __AES_RELEASE_RESET __HAL_RCC_AES_RELEASE_RESET
#define __CRYP_CLK_SLEEP_ENABLE      __HAL_RCC_CRYP_CLK_SLEEP_ENABLE
#define __CRYP_CLK_SLEEP_DISABLE  __HAL_RCC_CRYP_CLK_SLEEP_DISABLE
#define __CRYP_CLK_ENABLE  __HAL_RCC_CRYP_CLK_ENABLE
#define __CRYP_CLK_DISABLE  __HAL_RCC_CRYP_CLK_DISABLE
#define __CRYP_FORCE_RESET  __HAL_RCC_CRYP_FORCE_RESET
#define __CRYP_RELEASE_RESET  __HAL_RCC_CRYP_RELEASE_RESET
#define __AFIO_CLK_DISABLE __HAL_RCC_AFIO_CLK_DISABLE
#define __AFIO_CLK_ENABLE __HAL_RCC_AFIO_CLK_ENABLE
#define __AFIO_FORCE_RESET __HAL_RCC_AFIO_FORCE_RESET
#define __AFIO_RELEASE_RESET __HAL_RCC_AFIO_RELEASE_RESET
#define __AHB_FORCE_RESET __HAL_RCC_AHB_FORCE_RESET
#define __AHB_RELEASE_RESET __HAL_RCC_AHB_RELEASE_RESET
#define __AHB1_FORCE_RESET __HAL_RCC_AHB1_FORCE_RESET
#define __AHB1_RELEASE_RESET __HAL_RCC_AHB1_RELEASE_RESET
#define __AHB2_FORCE_RESET __HAL_RCC_AHB2_FORCE_RESET
#define __AHB2_RELEASE_RESET __HAL_RCC_AHB2_RELEASE_RESET
#define __AHB3_FORCE_RESET __HAL_RCC_AHB3_FORCE_RESET
#define __AHB3_RELEASE_RESET __HAL_RCC_AHB3_RELEASE_RESET
#define __APB1_FORCE_RESET __HAL_RCC_APB1_FORCE_RESET
#define __APB1_RELEASE_RESET __HAL_RCC_APB1_RELEASE_RESET
#define __APB2_FORCE_RESET __HAL_RCC_APB2_FORCE_RESET
#define __APB2_RELEASE_RESET __HAL_RCC_APB2_RELEASE_RESET
#define __BKP_CLK_DISABLE __HAL_RCC_BKP_CLK_DISABLE
#define __BKP_CLK_ENABLE __HAL_RCC_BKP_CLK_ENABLE
#define __BKP_FORCE_RESET __HAL_RCC_BKP_FORCE_RESET
#define __BKP_RELEASE_RESET __HAL_RCC_BKP_RELEASE_RESET
#define __CAN1_CLK_DISABLE __HAL_RCC_CAN1_CLK_DISABLE
#define __CAN1_CLK_ENABLE __HAL_RCC_CAN1_CLK_ENABLE
#define __CAN1_CLK_SLEEP_DISABLE __HAL_RCC_CAN1_CLK_SLEEP_DISABLE
#define __CAN1_CLK_SLEEP_ENABLE __HAL_RCC_CAN1_CLK_SLEEP_ENABLE
#define __CAN1_FORCE_RESET __HAL_RCC_CAN1_FORCE_RESET
#define __CAN1_RELEASE_RESET __HAL_RCC_CAN1_RELEASE_RESET
#define __CAN2_CLK_DISABLE __HAL_RCC_CAN2_CLK_DISABLE
#define __CAN2_CLK_ENABLE __HAL_RCC_CAN2_CLK_ENABLE
#define __CAN2_FORCE_RESET __HAL_RCC_CAN2_FORCE_RESET
#define __CAN2_RELEASE_RESET __HAL_RCC_CAN2_RELEASE_RESET
#define __CEC_CLK_DISABLE __HAL_RCC_CEC_CLK_DISABLE
#define __CEC_CLK_ENABLE __HAL_RCC_CEC_CLK_ENABLE
#define __CEC_FORCE_RESET __HAL_RCC_CEC_FORCE_RESET
#define __CEC_RELEASE_RESET __HAL_RCC_CEC_RELEASE_RESET
#define __CRC_CLK_DISABLE __HAL_RCC_CRC_CLK_DISABLE
#define __CRC_CLK_ENABLE __HAL_RCC_CRC_CLK_ENABLE
#define __CRC_CLK_SLEEP_DISABLE __HAL_RCC_CRC_CLK_SLEEP_DISABLE
#define __CRC_CLK_SLEEP_ENABLE __HAL_RCC_CRC_CLK_SLEEP_ENABLE
#define __CRC_FORCE_RESET __HAL_RCC_CRC_FORCE_RESET
#define __CRC_RELEASE_RESET __HAL_RCC_CRC_RELEASE_RESET
#define __DAC_CLK_DISABLE __HAL_RCC_DAC_CLK_DISABLE
#define __DAC_CLK_ENABLE __HAL_RCC_DAC_CLK_ENABLE
#define __DAC_FORCE_RESET __HAL_RCC_DAC_FORCE_RESET
#define __DAC_RELEASE_RESET __HAL_RCC_DAC_RELEASE_RESET
#define __DAC1_CLK_DISABLE __HAL_RCC_DAC1_CLK_DISABLE
#define __DAC1_CLK_ENABLE __HAL_RCC_DAC1_CLK_ENABLE
#define __DAC1_CLK_SLEEP_DISABLE __HAL_RCC_DAC1_CLK_SLEEP_DISABLE
#define __DAC1_CLK_SLEEP_ENABLE __HAL_RCC_DAC1_CLK_SLEEP_ENABLE
#define __DAC1_FORCE_RESET __HAL_RCC_DAC1_FORCE_RESET
#define __DAC1_RELEASE_RESET __HAL_RCC_DAC1_RELEASE_RESET
#define __DFSDM_CLK_DISABLE __HAL_RCC_DFSDM_CLK_DISABLE
#define __DFSDM_CLK_ENABLE __HAL_RCC_DFSDM_CLK_ENABLE
#define __DFSDM_CLK_SLEEP_DISABLE __HAL_RCC_DFSDM_CLK_SLEEP_DISABLE
#define __DFSDM_CLK_SLEEP_ENABLE __HAL_RCC_DFSDM_CLK_SLEEP_ENABLE
#define __DFSDM_FORCE_RESET __HAL_RCC_DFSDM_FORCE_RESET
#define __DFSDM_RELEASE_RESET __HAL_RCC_DFSDM_RELEASE_RESET
#define __DMA1_CLK_DISABLE __HAL_RCC_DMA1_CLK_DISABLE
#define __DMA1_CLK_ENABLE __HAL_RCC_DMA1_CLK_ENABLE
#define __DMA1_CLK_SLEEP_DISABLE __HAL_RCC_DMA1_CLK_SLEEP_DISABLE
#define __DMA1_CLK_SLEEP_ENABLE __HAL_RCC_DMA1_CLK_SLEEP_ENABLE
#define __DMA1_FORCE_RESET __HAL_RCC_DMA1_FORCE_RESET
#define __DMA1_RELEASE_RESET __HAL_RCC_DMA1_RELEASE_RESET
#define __DMA2_CLK_DISABLE __HAL_RCC_DMA2_CLK_DISABLE
#define __DMA2_CLK_ENABLE __HAL_RCC_DMA2_CLK_ENABLE
#define __DMA2_CLK_SLEEP_DISABLE __HAL_RCC_DMA2_CLK_SLEEP_DISABLE
#define __DMA2_CLK_SLEEP_ENABLE __HAL_RCC_DMA2_CLK_SLEEP_ENABLE
#define __DMA2_FORCE_RESET __HAL_RCC_DMA2_FORCE_RESET
#define __DMA2_RELEASE_RESET __HAL_RCC_DMA2_RELEASE_RESET
#define __ETHMAC_CLK_DISABLE __HAL_RCC_ETHMAC_CLK_DISABLE
#define __ETHMAC_CLK_ENABLE __HAL_RCC_ETHMAC_CLK_ENABLE
#define __ETHMAC_FORCE_RESET __HAL_RCC_ETHMAC_FORCE_RESET
#define __ETHMAC_RELEASE_RESET __HAL_RCC_ETHMAC_RELEASE_RESET
#define __ETHMACRX_CLK_DISABLE __HAL_RCC_ETHMACRX_CLK_DISABLE
#define __ETHMACRX_CLK_ENABLE __HAL_RCC_ETHMACRX_CLK_ENABLE
#define __ETHMACTX_CLK_DISABLE __HAL_RCC_ETHMACTX_CLK_DISABLE
#define __ETHMACTX_CLK_ENABLE __HAL_RCC_ETHMACTX_CLK_ENABLE
#define __FIREWALL_CLK_DISABLE __HAL_RCC_FIREWALL_CLK_DISABLE
#define __FIREWALL_CLK_ENABLE __HAL_RCC_FIREWALL_CLK_ENABLE
#define __FLASH_CLK_DISABLE __HAL_RCC_FLASH_CLK_DISABLE
#define __FLASH_CLK_ENABLE __HAL_RCC_FLASH_CLK_ENABLE
#define __FLASH_CLK_SLEEP_DISABLE __HAL_RCC_FLASH_CLK_SLEEP_DISABLE
#define __FLASH_CLK_SLEEP_ENABLE __HAL_RCC_FLASH_CLK_SLEEP_ENABLE
#define __FLASH_FORCE_RESET __HAL_RCC_FLASH_FORCE_RESET
#define __FLASH_RELEASE_RESET __HAL_RCC_FLASH_RELEASE_RESET
#define __FLITF_CLK_DISABLE __HAL_RCC_FLITF_CLK_DISABLE
#define __FLITF_CLK_ENABLE __HAL_RCC_FLITF_CLK_ENABLE
#define __FMC_CLK_DISABLE __HAL_RCC_FMC_CLK_DISABLE
#define __FMC_CLK_ENABLE __HAL_RCC_FMC_CLK_ENABLE
#define __FMC_CLK_SLEEP_DISABLE __HAL_RCC_FMC_CLK_SLEEP_DISABLE
#define __FMC_CLK_SLEEP_ENABLE __HAL_RCC_FMC_CLK_SLEEP_ENABLE
#define __FMC_FORCE_RESET __HAL_RCC_FMC_FORCE_RESET
#define __FMC_RELEASE_RESET __HAL_RCC_FMC_RELEASE_RESET
#define __FSMC_CLK_DISABLE __HAL_RCC_FSMC_CLK_DISABLE
#define __FSMC_CLK_ENABLE __HAL_RCC_FSMC_CLK_ENABLE
#define __GPIOA_CLK_DISABLE __HAL_RCC_GPIOA_CLK_DISABLE
#define __GPIOA_CLK_ENABLE __HAL_RCC_GPIOA_CLK_ENABLE
#define __GPIOA_CLK_SLEEP_DISABLE __HAL_RCC_GPIOA_CLK_SLEEP_DISABLE
#define __GPIOA_CLK_SLEEP_ENABLE __HAL_RCC_GPIOA_CLK_SLEEP_ENABLE
#define __GPIOA_FORCE_RESET __HAL_RCC_GPIOA_FORCE_RESET
#define __GPIOA_RELEASE_RESET __HAL_RCC_GPIOA_RELEASE_RESET
#define __GPIOB_CLK_DISABLE __HAL_RCC_GPIOB_CLK_DISABLE
#define __GPIOB_CLK_ENABLE __HAL_RCC_GPIOB_CLK_ENABLE
#define __GPIOB_CLK_SLEEP_DISABLE __HAL_RCC_GPIOB_CLK_SLEEP_DISABLE
#define __GPIOB_CLK_SLEEP_ENABLE __HAL_RCC_GPIOB_CLK_SLEEP_ENABLE
#define __GPIOB_FORCE_RESET __HAL_RCC_GPIOB_FORCE_RESET
#define __GPIOB_RELEASE_RESET __HAL_RCC_GPIOB_RELEASE_RESET
#define __GPIOC_CLK_DISABLE __HAL_RCC_GPIOC_CLK_DISABLE
#define __GPIOC_CLK_ENABLE __HAL_RCC_GPIOC_CLK_ENABLE
#define __GPIOC_CLK_SLEEP_DISABLE __HAL_RCC_GPIOC_CLK_SLEEP_DISABLE
#define __GPIOC_CLK_SLEEP_ENABLE __HAL_RCC_GPIOC_CLK_SLEEP_ENABLE
#define __GPIOC_FORCE_RESET __HAL_RCC_GPIOC_FORCE_RESET
#define __GPIOC_RELEASE_RESET __HAL_RCC_GPIOC_RELEASE_RESET
#define __GPIOD_CLK_DISABLE __HAL_RCC_GPIOD_CLK_DISABLE
#define __GPIOD_CLK_ENABLE __HAL_RCC_GPIOD_CLK_ENABLE
#define __GPIOD_CLK_SLEEP_DISABLE __HAL_RCC_GPIOD_CLK_SLEEP_DISABLE
#define __GPIOD_CLK_SLEEP_ENABLE __HAL_RCC_GPIOD_CLK_SLEEP_ENABLE
#define __GPIOD_FORCE_RESET __HAL_RCC_GPIOD_FORCE_RESET
#define __GPIOD_RELEASE_RESET __HAL_RCC_GPIOD_RELEASE_RESET
#define __GPIOE_CLK_DISABLE __HAL_RCC_GPIOE_CLK_DISABLE
#define __GPIOE_CLK_ENABLE __HAL_RCC_GPIOE_CLK_ENABLE
#define __GPIOE_CLK_SLEEP_DISABLE __HAL_RCC_GPIOE_CLK_SLEEP_DISABLE
#define __GPIOE_CLK_SLEEP_ENABLE __HAL_RCC_GPIOE_CLK_SLEEP_ENABLE
#define __GPIOE_FORCE_RESET __HAL_RCC_GPIOE_FORCE_RESET
#define __GPIOE_RELEASE_RESET __HAL_RCC_GPIOE_RELEASE_RESET
#define __GPIOF_CLK_DISABLE __HAL_RCC_GPIOF_CLK_DISABLE
#define __GPIOF_CLK_ENABLE __HAL_RCC_GPIOF_CLK_ENABLE
#define __GPIOF_CLK_SLEEP_DISABLE __HAL_RCC_GPIOF_CLK_SLEEP_DISABLE
#define __GPIOF_CLK_SLEEP_ENABLE __HAL_RCC_GPIOF_CLK_SLEEP_ENABLE
#define __GPIOF_FORCE_RESET __HAL_RCC_GPIOF_FORCE_RESET
#define __GPIOF_RELEASE_RESET __HAL_RCC_GPIOF_RELEASE_RESET
#define __GPIOG_CLK_DISABLE __HAL_RCC_GPIOG_CLK_DISABLE
#define __GPIOG_CLK_ENABLE __HAL_RCC_GPIOG_CLK_ENABLE
#define __GPIOG_CLK_SLEEP_DISABLE __HAL_RCC_GPIOG_CLK_SLEEP_DISABLE
#define __GPIOG_CLK_SLEEP_ENABLE __HAL_RCC_GPIOG_CLK_SLEEP_ENABLE
#define __GPIOG_FORCE_RESET __HAL_RCC_GPIOG_FORCE_RESET
#define __GPIOG_RELEASE_RESET __HAL_RCC_GPIOG_RELEASE_RESET
#define __GPIOH_CLK_DISABLE __HAL_RCC_GPIOH_CLK_DISABLE
#define __GPIOH_CLK_ENABLE __HAL_RCC_GPIOH_CLK_ENABLE
#define __GPIOH_CLK_SLEEP_DISABLE __HAL_RCC_GPIOH_CLK_SLEEP_DISABLE
#define __GPIOH_CLK_SLEEP_ENABLE __HAL_RCC_GPIOH_CLK_SLEEP_ENABLE
#define __GPIOH_FORCE_RESET __HAL_RCC_GPIOH_FORCE_RESET
#define __GPIOH_RELEASE_RESET __HAL_RCC_GPIOH_RELEASE_RESET
#define __I2C1_CLK_DISABLE __HAL_RCC_I2C1_CLK_DISABLE
#define __I2C1_CLK_ENABLE __HAL_RCC_I2C1_CLK_ENABLE
#define __I2C1_CLK_SLEEP_DISABLE __HAL_RCC_I2C1_CLK_SLEEP_DISABLE
#define __I2C1_CLK_SLEEP_ENABLE __HAL_RCC_I2C1_CLK_SLEEP_ENABLE
#define __I2C1_FORCE_RESET __HAL_RCC_I2C1_FORCE_RESET
#define __I2C1_RELEASE_RESET __HAL_RCC_I2C1_RELEASE_RESET
#define __I2C2_CLK_DISABLE __HAL_RCC_I2C2_CLK_DISABLE
#define __I2C2_CLK_ENABLE __HAL_RCC_I2C2_CLK_ENABLE
#define __I2C2_CLK_SLEEP_DISABLE __HAL_RCC_I2C2_CLK_SLEEP_DISABLE
#define __I2C2_CLK_SLEEP_ENABLE __HAL_RCC_I2C2_CLK_SLEEP_ENABLE
#define __I2C2_FORCE_RESET __HAL_RCC_I2C2_FORCE_RESET
#define __I2C2_RELEASE_RESET __HAL_RCC_I2C2_RELEASE_RESET
#define __I2C3_CLK_DISABLE __HAL_RCC_I2C3_CLK_DISABLE
#define __I2C3_CLK_ENABLE __HAL_RCC_I2C3_CLK_ENABLE
#define __I2C3_CLK_SLEEP_DISABLE __HAL_RCC_I2C3_CLK_SLEEP_DISABLE
#define __I2C3_CLK_SLEEP_ENABLE __HAL_RCC_I2C3_CLK_SLEEP_ENABLE
#define __I2C3_FORCE_RESET __HAL_RCC_I2C3_FORCE_RESET
#define __I2C3_RELEASE_RESET __HAL_RCC_I2C3_RELEASE_RESET
#define __LCD_CLK_DISABLE __HAL_RCC_LCD_CLK_DISABLE
#define __LCD_CLK_ENABLE __HAL_RCC_LCD_CLK_ENABLE
#define __LCD_CLK_SLEEP_DISABLE __HAL_RCC_LCD_CLK_SLEEP_DISABLE
#define __LCD_CLK_SLEEP_ENABLE __HAL_RCC_LCD_CLK_SLEEP_ENABLE
#define __LCD_FORCE_RESET __HAL_RCC_LCD_FORCE_RESET
#define __LCD_RELEASE_RESET __HAL_RCC_LCD_RELEASE_RESET
#define __LPTIM1_CLK_DISABLE __HAL_RCC_LPTIM1_CLK_DISABLE
#define __LPTIM1_CLK_ENABLE __HAL_RCC_LPTIM1_CLK_ENABLE
#define __LPTIM1_CLK_SLEEP_DISABLE __HAL_RCC_LPTIM1_CLK_SLEEP_DISABLE
#define __LPTIM1_CLK_SLEEP_ENABLE __HAL_RCC_LPTIM1_CLK_SLEEP_ENABLE
#define __LPTIM1_FORCE_RESET __HAL_RCC_LPTIM1_FORCE_RESET
#define __LPTIM1_RELEASE_RESET __HAL_RCC_LPTIM1_RELEASE_RESET
#define __LPTIM2_CLK_DISABLE __HAL_RCC_LPTIM2_CLK_DISABLE
#define __LPTIM2_CLK_ENABLE __HAL_RCC_LPTIM2_CLK_ENABLE
#define __LPTIM2_CLK_SLEEP_DISABLE __HAL_RCC_LPTIM2_CLK_SLEEP_DISABLE
#define __LPTIM2_CLK_SLEEP_ENABLE __HAL_RCC_LPTIM2_CLK_SLEEP_ENABLE
#define __LPTIM2_FORCE_RESET __HAL_RCC_LPTIM2_FORCE_RESET
#define __LPTIM2_RELEASE_RESET __HAL_RCC_LPTIM2_RELEASE_RESET
#define __LPUART1_CLK_DISABLE __HAL_RCC_LPUART1_CLK_DISABLE
#define __LPUART1_CLK_ENABLE __HAL_RCC_LPUART1_CLK_ENABLE
#define __LPUART1_CLK_SLEEP_DISABLE __HAL_RCC_LPUART1_CLK_SLEEP_DISABLE
#define __LPUART1_CLK_SLEEP_ENABLE __HAL_RCC_LPUART1_CLK_SLEEP_ENABLE
#define __LPUART1_FORCE_RESET __HAL_RCC_LPUART1_FORCE_RESET
#define __LPUART1_RELEASE_RESET __HAL_RCC_LPUART1_RELEASE_RESET
#define __OPAMP_CLK_DISABLE __HAL_RCC_OPAMP_CLK_DISABLE
#define __OPAMP_CLK_ENABLE __HAL_RCC_OPAMP_CLK_ENABLE
#define __OPAMP_CLK_SLEEP_DISABLE __HAL_RCC_OPAMP_CLK_SLEEP_DISABLE
#define __OPAMP_CLK_SLEEP_ENABLE __HAL_RCC_OPAMP_CLK_SLEEP_ENABLE
#define __OPAMP_FORCE_RESET __HAL_RCC_OPAMP_FORCE_RESET
#define __OPAMP_RELEASE_RESET __HAL_RCC_OPAMP_RELEASE_RESET
#define __OTGFS_CLK_DISABLE __HAL_RCC_OTGFS_CLK_DISABLE
#define __OTGFS_CLK_ENABLE __HAL_RCC_OTGFS_CLK_ENABLE
#define __OTGFS_CLK_SLEEP_DISABLE __HAL_RCC_OTGFS_CLK_SLEEP_DISABLE
#define __OTGFS_CLK_SLEEP_ENABLE __HAL_RCC_OTGFS_CLK_SLEEP_ENABLE
#define __OTGFS_FORCE_RESET __HAL_RCC_OTGFS_FORCE_RESET
#define __OTGFS_RELEASE_RESET __HAL_RCC_OTGFS_RELEASE_RESET
#define __PWR_CLK_DISABLE __HAL_RCC_PWR_CLK_DISABLE
#define __PWR_CLK_ENABLE __HAL_RCC_PWR_CLK_ENABLE
#define __PWR_CLK_SLEEP_DISABLE __HAL_RCC_PWR_CLK_SLEEP_DISABLE
#define __PWR_CLK_SLEEP_ENABLE __HAL_RCC_PWR_CLK_SLEEP_ENABLE
#define __PWR_FORCE_RESET __HAL_RCC_PWR_FORCE_RESET
#define __PWR_RELEASE_RESET __HAL_RCC_PWR_RELEASE_RESET
#define __QSPI_CLK_DISABLE __HAL_RCC_QSPI_CLK_DISABLE
#define __QSPI_CLK_ENABLE __HAL_RCC_QSPI_CLK_ENABLE
#define __QSPI_CLK_SLEEP_DISABLE __HAL_RCC_QSPI_CLK_SLEEP_DISABLE
#define __QSPI_CLK_SLEEP_ENABLE __HAL_RCC_QSPI_CLK_SLEEP_ENABLE
#define __QSPI_FORCE_RESET __HAL_RCC_QSPI_FORCE_RESET
#define __QSPI_RELEASE_RESET __HAL_RCC_QSPI_RELEASE_RESET
#define __RNG_CLK_DISABLE __HAL_RCC_RNG_CLK_DISABLE
#define __RNG_CLK_ENABLE __HAL_RCC_RNG_CLK_ENABLE
#define __RNG_CLK_SLEEP_DISABLE __HAL_RCC_RNG_CLK_SLEEP_DISABLE
#define __RNG_CLK_SLEEP_ENABLE __HAL_RCC_RNG_CLK_SLEEP_ENABLE
#define __RNG_FORCE_RESET __HAL_RCC_RNG_FORCE_RESET
#define __RNG_RELEASE_RESET __HAL_RCC_RNG_RELEASE_RESET
#define __SAI1_CLK_DISABLE __HAL_RCC_SAI1_CLK_DISABLE
#define __SAI1_CLK_ENABLE __HAL_RCC_SAI1_CLK_ENABLE
#define __SAI1_CLK_SLEEP_DISABLE __HAL_RCC_SAI1_CLK_SLEEP_DISABLE
#define __SAI1_CLK_SLEEP_ENABLE __HAL_RCC_SAI1_CLK_SLEEP_ENABLE
#define __SAI1_FORCE_RESET __HAL_RCC_SAI1_FORCE_RESET
#define __SAI1_RELEASE_RESET __HAL_RCC_SAI1_RELEASE_RESET
#define __SAI2_CLK_DISABLE __HAL_RCC_SAI2_CLK_DISABLE
#define __SAI2_CLK_ENABLE __HAL_RCC_SAI2_CLK_ENABLE
#define __SAI2_CLK_SLEEP_DISABLE __HAL_RCC_SAI2_CLK_SLEEP_DISABLE
#define __SAI2_CLK_SLEEP_ENABLE __HAL_RCC_SAI2_CLK_SLEEP_ENABLE
#define __SAI2_FORCE_RESET __HAL_RCC_SAI2_FORCE_RESET
#define __SAI2_RELEASE_RESET __HAL_RCC_SAI2_RELEASE_RESET
#define __SDIO_CLK_DISABLE __HAL_RCC_SDIO_CLK_DISABLE
#define __SDIO_CLK_ENABLE __HAL_RCC_SDIO_CLK_ENABLE
#define __SDMMC_CLK_DISABLE __HAL_RCC_SDMMC_CLK_DISABLE
#define __SDMMC_CLK_ENABLE __HAL_RCC_SDMMC_CLK_ENABLE
#define __SDMMC_CLK_SLEEP_DISABLE __HAL_RCC_SDMMC_CLK_SLEEP_DISABLE
#define __SDMMC_CLK_SLEEP_ENABLE __HAL_RCC_SDMMC_CLK_SLEEP_ENABLE
#define __SDMMC_FORCE_RESET __HAL_RCC_SDMMC_FORCE_RESET
#define __SDMMC_RELEASE_RESET __HAL_RCC_SDMMC_RELEASE_RESET
#define __SPI1_CLK_DISABLE __HAL_RCC_SPI1_CLK_DISABLE
#define __SPI1_CLK_ENABLE __HAL_RCC_SPI1_CLK_ENABLE
#define __SPI1_CLK_SLEEP_DISABLE __HAL_RCC_SPI1_CLK_SLEEP_DISABLE
#define __SPI1_CLK_SLEEP_ENABLE __HAL_RCC_SPI1_CLK_SLEEP_ENABLE
#define __SPI1_FORCE_RESET __HAL_RCC_SPI1_FORCE_RESET
#define __SPI1_RELEASE_RESET __HAL_RCC_SPI1_RELEASE_RESET
#define __SPI2_CLK_DISABLE __HAL_RCC_SPI2_CLK_DISABLE
#define __SPI2_CLK_ENABLE __HAL_RCC_SPI2_CLK_ENABLE
#define __SPI2_CLK_SLEEP_DISABLE __HAL_RCC_SPI2_CLK_SLEEP_DISABLE
#define __SPI2_CLK_SLEEP_ENABLE __HAL_RCC_SPI2_CLK_SLEEP_ENABLE
#define __SPI2_FORCE_RESET __HAL_RCC_SPI2_FORCE_RESET
#define __SPI2_RELEASE_RESET __HAL_RCC_SPI2_RELEASE_RESET
#define __SPI3_CLK_DISABLE __HAL_RCC_SPI3_CLK_DISABLE
#define __SPI3_CLK_ENABLE __HAL_RCC_SPI3_CLK_ENABLE
#define __SPI3_CLK_SLEEP_DISABLE __HAL_RCC_SPI3_CLK_SLEEP_DISABLE
#define __SPI3_CLK_SLEEP_ENABLE __HAL_RCC_SPI3_CLK_SLEEP_ENABLE
#define __SPI3_FORCE_RESET __HAL_RCC_SPI3_FORCE_RESET
#define __SPI3_RELEASE_RESET __HAL_RCC_SPI3_RELEASE_RESET
#define __SRAM_CLK_DISABLE __HAL_RCC_SRAM_CLK_DISABLE
#define __SRAM_CLK_ENABLE __HAL_RCC_SRAM_CLK_ENABLE
#define __SRAM1_CLK_SLEEP_DISABLE __HAL_RCC_SRAM1_CLK_SLEEP_DISABLE
#define __SRAM1_CLK_SLEEP_ENABLE __HAL_RCC_SRAM1_CLK_SLEEP_ENABLE
#define __SRAM2_CLK_SLEEP_DISABLE __HAL_RCC_SRAM2_CLK_SLEEP_DISABLE
#define __SRAM2_CLK_SLEEP_ENABLE __HAL_RCC_SRAM2_CLK_SLEEP_ENABLE
#define __SWPMI1_CLK_DISABLE __HAL_RCC_SWPMI1_CLK_DISABLE
#define __SWPMI1_CLK_ENABLE __HAL_RCC_SWPMI1_CLK_ENABLE
#define __SWPMI1_CLK_SLEEP_DISABLE __HAL_RCC_SWPMI1_CLK_SLEEP_DISABLE
#define __SWPMI1_CLK_SLEEP_ENABLE __HAL_RCC_SWPMI1_CLK_SLEEP_ENABLE
#define __SWPMI1_FORCE_RESET __HAL_RCC_SWPMI1_FORCE_RESET
#define __SWPMI1_RELEASE_RESET __HAL_RCC_SWPMI1_RELEASE_RESET
#define __SYSCFG_CLK_DISABLE __HAL_RCC_SYSCFG_CLK_DISABLE
#define __SYSCFG_CLK_ENABLE __HAL_RCC_SYSCFG_CLK_ENABLE
#define __SYSCFG_CLK_SLEEP_DISABLE __HAL_RCC_SYSCFG_CLK_SLEEP_DISABLE
#define __SYSCFG_CLK_SLEEP_ENABLE __HAL_RCC_SYSCFG_CLK_SLEEP_ENABLE
#define __SYSCFG_FORCE_RESET __HAL_RCC_SYSCFG_FORCE_RESET
#define __SYSCFG_RELEASE_RESET __HAL_RCC_SYSCFG_RELEASE_RESET
#define __TIM1_CLK_DISABLE __HAL_RCC_TIM1_CLK_DISABLE
#define __TIM1_CLK_ENABLE __HAL_RCC_TIM1_CLK_ENABLE
#define __TIM1_CLK_SLEEP_DISABLE __HAL_RCC_TIM1_CLK_SLEEP_DISABLE
#define __TIM1_CLK_SLEEP_ENABLE __HAL_RCC_TIM1_CLK_SLEEP_ENABLE
#define __TIM1_FORCE_RESET __HAL_RCC_TIM1_FORCE_RESET
#define __TIM1_RELEASE_RESET __HAL_RCC_TIM1_RELEASE_RESET
#define __TIM10_CLK_DISABLE __HAL_RCC_TIM10_CLK_DISABLE
#define __TIM10_CLK_ENABLE __HAL_RCC_TIM10_CLK_ENABLE
#define __TIM10_FORCE_RESET __HAL_RCC_TIM10_FORCE_RESET
#define __TIM10_RELEASE_RESET __HAL_RCC_TIM10_RELEASE_RESET
#define __TIM11_CLK_DISABLE __HAL_RCC_TIM11_CLK_DISABLE
#define __TIM11_CLK_ENABLE __HAL_RCC_TIM11_CLK_ENABLE
#define __TIM11_FORCE_RESET __HAL_RCC_TIM11_FORCE_RESET
#define __TIM11_RELEASE_RESET __HAL_RCC_TIM11_RELEASE_RESET
#define __TIM12_CLK_DISABLE __HAL_RCC_TIM12_CLK_DISABLE
#define __TIM12_CLK_ENABLE __HAL_RCC_TIM12_CLK_ENABLE
#define __TIM12_FORCE_RESET __HAL_RCC_TIM12_FORCE_RESET
#define __TIM12_RELEASE_RESET __HAL_RCC_TIM12_RELEASE_RESET
#define __TIM13_CLK_DISABLE __HAL_RCC_TIM13_CLK_DISABLE
#define __TIM13_CLK_ENABLE __HAL_RCC_TIM13_CLK_ENABLE
#define __TIM13_FORCE_RESET __HAL_RCC_TIM13_FORCE_RESET
#define __TIM13_RELEASE_RESET __HAL_RCC_TIM13_RELEASE_RESET
#define __TIM14_CLK_DISABLE __HAL_RCC_TIM14_CLK_DISABLE
#define __TIM14_CLK_ENABLE __HAL_RCC_TIM14_CLK_ENABLE
#define __TIM14_FORCE_RESET __HAL_RCC_TIM14_FORCE_RESET
#define __TIM14_RELEASE_RESET __HAL_RCC_TIM14_RELEASE_RESET
#define __TIM15_CLK_DISABLE __HAL_RCC_TIM15_CLK_DISABLE
#define __TIM15_CLK_ENABLE __HAL_RCC_TIM15_CLK_ENABLE
#define __TIM15_CLK_SLEEP_DISABLE __HAL_RCC_TIM15_CLK_SLEEP_DISABLE
#define __TIM15_CLK_SLEEP_ENABLE __HAL_RCC_TIM15_CLK_SLEEP_ENABLE
#define __TIM15_FORCE_RESET __HAL_RCC_TIM15_FORCE_RESET
#define __TIM15_RELEASE_RESET __HAL_RCC_TIM15_RELEASE_RESET
#define __TIM16_CLK_DISABLE __HAL_RCC_TIM16_CLK_DISABLE
#define __TIM16_CLK_ENABLE __HAL_RCC_TIM16_CLK_ENABLE
#define __TIM16_CLK_SLEEP_DISABLE __HAL_RCC_TIM16_CLK_SLEEP_DISABLE
#define __TIM16_CLK_SLEEP_ENABLE __HAL_RCC_TIM16_CLK_SLEEP_ENABLE
#define __TIM16_FORCE_RESET __HAL_RCC_TIM16_FORCE_RESET
#define __TIM16_RELEASE_RESET __HAL_RCC_TIM16_RELEASE_RESET
#define __TIM17_CLK_DISABLE __HAL_RCC_TIM17_CLK_DISABLE
#define __TIM17_CLK_ENABLE __HAL_RCC_TIM17_CLK_ENABLE
#define __TIM17_CLK_SLEEP_DISABLE __HAL_RCC_TIM17_CLK_SLEEP_DISABLE
#define __TIM17_CLK_SLEEP_ENABLE __HAL_RCC_TIM17_CLK_SLEEP_ENABLE
#define __TIM17_FORCE_RESET __HAL_RCC_TIM17_FORCE_RESET
#define __TIM17_RELEASE_RESET __HAL_RCC_TIM17_RELEASE_RESET
#define __TIM2_CLK_DISABLE __HAL_RCC_TIM2_CLK_DISABLE
#define __TIM2_CLK_ENABLE __HAL_RCC_TIM2_CLK_ENABLE
#define __TIM2_CLK_SLEEP_DISABLE __HAL_RCC_TIM2_CLK_SLEEP_DISABLE
#define __TIM2_CLK_SLEEP_ENABLE __HAL_RCC_TIM2_CLK_SLEEP_ENABLE
#define __TIM2_FORCE_RESET __HAL_RCC_TIM2_FORCE_RESET
#define __TIM2_RELEASE_RESET __HAL_RCC_TIM2_RELEASE_RESET
#define __TIM3_CLK_DISABLE __HAL_RCC_TIM3_CLK_DISABLE
#define __TIM3_CLK_ENABLE __HAL_RCC_TIM3_CLK_ENABLE
#define __TIM3_CLK_SLEEP_DISABLE __HAL_RCC_TIM3_CLK_SLEEP_DISABLE
#define __TIM3_CLK_SLEEP_ENABLE __HAL_RCC_TIM3_CLK_SLEEP_ENABLE
#define __TIM3_FORCE_RESET __HAL_RCC_TIM3_FORCE_RESET
#define __TIM3_RELEASE_RESET __HAL_RCC_TIM3_RELEASE_RESET
#define __TIM4_CLK_DISABLE __HAL_RCC_TIM4_CLK_DISABLE
#define __TIM4_CLK_ENABLE __HAL_RCC_TIM4_CLK_ENABLE
#define __TIM4_CLK_SLEEP_DISABLE __HAL_RCC_TIM4_CLK_SLEEP_DISABLE
#define __TIM4_CLK_SLEEP_ENABLE __HAL_RCC_TIM4_CLK_SLEEP_ENABLE
#define __TIM4_FORCE_RESET __HAL_RCC_TIM4_FORCE_RESET
#define __TIM4_RELEASE_RESET __HAL_RCC_TIM4_RELEASE_RESET
#define __TIM5_CLK_DISABLE __HAL_RCC_TIM5_CLK_DISABLE
#define __TIM5_CLK_ENABLE __HAL_RCC_TIM5_CLK_ENABLE
#define __TIM5_CLK_SLEEP_DISABLE __HAL_RCC_TIM5_CLK_SLEEP_DISABLE
#define __TIM5_CLK_SLEEP_ENABLE __HAL_RCC_TIM5_CLK_SLEEP_ENABLE
#define __TIM5_FORCE_RESET __HAL_RCC_TIM5_FORCE_RESET
#define __TIM5_RELEASE_RESET __HAL_RCC_TIM5_RELEASE_RESET
#define __TIM6_CLK_DISABLE __HAL_RCC_TIM6_CLK_DISABLE
#define __TIM6_CLK_ENABLE __HAL_RCC_TIM6_CLK_ENABLE
#define __TIM6_CLK_SLEEP_DISABLE __HAL_RCC_TIM6_CLK_SLEEP_DISABLE
#define __TIM6_CLK_SLEEP_ENABLE __HAL_RCC_TIM6_CLK_SLEEP_ENABLE
#define __TIM6_FORCE_RESET __HAL_RCC_TIM6_FORCE_RESET
#define __TIM6_RELEASE_RESET __HAL_RCC_TIM6_RELEASE_RESET
#define __TIM7_CLK_DISABLE __HAL_RCC_TIM7_CLK_DISABLE
#define __TIM7_CLK_ENABLE __HAL_RCC_TIM7_CLK_ENABLE
#define __TIM7_CLK_SLEEP_DISABLE __HAL_RCC_TIM7_CLK_SLEEP_DISABLE
#define __TIM7_CLK_SLEEP_ENABLE __HAL_RCC_TIM7_CLK_SLEEP_ENABLE
#define __TIM7_FORCE_RESET __HAL_RCC_TIM7_FORCE_RESET
#define __TIM7_RELEASE_RESET __HAL_RCC_TIM7_RELEASE_RESET
#define __TIM8_CLK_DISABLE __HAL_RCC_TIM8_CLK_DISABLE
#define __TIM8_CLK_ENABLE __HAL_RCC_TIM8_CLK_ENABLE
#define __TIM8_CLK_SLEEP_DISABLE __HAL_RCC_TIM8_CLK_SLEEP_DISABLE
#define __TIM8_CLK_SLEEP_ENABLE __HAL_RCC_TIM8_CLK_SLEEP_ENABLE
#define __TIM8_FORCE_RESET __HAL_RCC_TIM8_FORCE_RESET
#define __TIM8_RELEASE_RESET __HAL_RCC_TIM8_RELEASE_RESET
#define __TIM9_CLK_DISABLE __HAL_RCC_TIM9_CLK_DISABLE
#define __TIM9_CLK_ENABLE __HAL_RCC_TIM9_CLK_ENABLE
#define __TIM9_FORCE_RESET __HAL_RCC_TIM9_FORCE_RESET
#define __TIM9_RELEASE_RESET __HAL_RCC_TIM9_RELEASE_RESET
#define __TSC_CLK_DISABLE __HAL_RCC_TSC_CLK_DISABLE
#define __TSC_CLK_ENABLE __HAL_RCC_TSC_CLK_ENABLE
#define __TSC_CLK_SLEEP_DISABLE __HAL_RCC_TSC_CLK_SLEEP_DISABLE
#define __TSC_CLK_SLEEP_ENABLE __HAL_RCC_TSC_CLK_SLEEP_ENABLE
#define __TSC_FORCE_RESET __HAL_RCC_TSC_FORCE_RESET
#define __TSC_RELEASE_RESET __HAL_RCC_TSC_RELEASE_RESET
#define __UART4_CLK_DISABLE __HAL_RCC_UART4_CLK_DISABLE
#define __UART4_CLK_ENABLE __HAL_RCC_UART4_CLK_ENABLE
#define __UART4_CLK_SLEEP_DISABLE __HAL_RCC_UART4_CLK_SLEEP_DISABLE
#define __UART4_CLK_SLEEP_ENABLE __HAL_RCC_UART4_CLK_SLEEP_ENABLE
#define __UART4_FORCE_RESET __HAL_RCC_UART4_FORCE_RESET
#define __UART4_RELEASE_RESET __HAL_RCC_UART4_RELEASE_RESET
#define __UART5_CLK_DISABLE __HAL_RCC_UART5_CLK_DISABLE
#define __UART5_CLK_ENABLE __HAL_RCC_UART5_CLK_ENABLE
#define __UART5_CLK_SLEEP_DISABLE __HAL_RCC_UART5_CLK_SLEEP_DISABLE
#define __UART5_CLK_SLEEP_ENABLE __HAL_RCC_UART5_CLK_SLEEP_ENABLE
#define __UART5_FORCE_RESET __HAL_RCC_UART5_FORCE_RESET
#define __UART5_RELEASE_RESET __HAL_RCC_UART5_RELEASE_RESET
#define __USART1_CLK_DISABLE __HAL_RCC_USART1_CLK_DISABLE
#define __USART1_CLK_ENABLE __HAL_RCC_USART1_CLK_ENABLE
#define __USART1_CLK_SLEEP_DISABLE __HAL_RCC_USART1_CLK_SLEEP_DISABLE
#define __USART1_CLK_SLEEP_ENABLE __HAL_RCC_USART1_CLK_SLEEP_ENABLE
#define __USART1_FORCE_RESET __HAL_RCC_USART1_FORCE_RESET
#define __USART1_RELEASE_RESET __HAL_RCC_USART1_RELEASE_RESET
#define __USART2_CLK_DISABLE __HAL_RCC_USART2_CLK_DISABLE
#define __USART2_CLK_ENABLE __HAL_RCC_USART2_CLK_ENABLE
#define __USART2_CLK_SLEEP_DISABLE __HAL_RCC_USART2_CLK_SLEEP_DISABLE
#define __USART2_CLK_SLEEP_ENABLE __HAL_RCC_USART2_CLK_SLEEP_ENABLE
#define __USART2_FORCE_RESET __HAL_RCC_USART2_FORCE_RESET
#define __USART2_RELEASE_RESET __HAL_RCC_USART2_RELEASE_RESET
#define __USART3_CLK_DISABLE __HAL_RCC_USART3_CLK_DISABLE
#define __USART3_CLK_ENABLE __HAL_RCC_USART3_CLK_ENABLE
#define __USART3_CLK_SLEEP_DISABLE __HAL_RCC_USART3_CLK_SLEEP_DISABLE
#define __USART3_CLK_SLEEP_ENABLE __HAL_RCC_USART3_CLK_SLEEP_ENABLE
#define __USART3_FORCE_RESET __HAL_RCC_USART3_FORCE_RESET
#define __USART3_RELEASE_RESET __HAL_RCC_USART3_RELEASE_RESET
#define __USB_CLK_DISABLE __HAL_RCC_USB_CLK_DISABLE
#define __USB_CLK_ENABLE __HAL_RCC_USB_CLK_ENABLE
#define __USB_FORCE_RESET __HAL_RCC_USB_FORCE_RESET
#define __USB_OTG_FS_CLK_DISABLE __HAL_RCC_USB_OTG_FS_CLK_DISABLE
#define __USB_OTG_FS_CLK_ENABLE __HAL_RCC_USB_OTG_FS_CLK_ENABLE
#define __USB_RELEASE_RESET __HAL_RCC_USB_RELEASE_RESET
#define __WWDG_CLK_DISABLE __HAL_RCC_WWDG_CLK_DISABLE
#define __WWDG_CLK_ENABLE __HAL_RCC_WWDG_CLK_ENABLE
#define __WWDG_CLK_SLEEP_DISABLE __HAL_RCC_WWDG_CLK_SLEEP_DISABLE
#define __WWDG_CLK_SLEEP_ENABLE __HAL_RCC_WWDG_CLK_SLEEP_ENABLE
#define __WWDG_FORCE_RESET __HAL_RCC_WWDG_FORCE_RESET
#define __WWDG_RELEASE_RESET __HAL_RCC_WWDG_RELEASE_RESET
#define __TIM21_CLK_ENABLE   __HAL_RCC_TIM21_CLK_ENABLE
#define __TIM21_CLK_DISABLE   __HAL_RCC_TIM21_CLK_DISABLE
#define __TIM21_FORCE_RESET   __HAL_RCC_TIM21_FORCE_RESET
#define __TIM21_RELEASE_RESET  __HAL_RCC_TIM21_RELEASE_RESET
#define __TIM21_CLK_SLEEP_ENABLE   __HAL_RCC_TIM21_CLK_SLEEP_ENABLE
#define __TIM21_CLK_SLEEP_DISABLE   __HAL_RCC_TIM21_CLK_SLEEP_DISABLE
#define __TIM22_CLK_ENABLE   __HAL_RCC_TIM22_CLK_ENABLE
#define __TIM22_CLK_DISABLE   __HAL_RCC_TIM22_CLK_DISABLE
#define __TIM22_FORCE_RESET   __HAL_RCC_TIM22_FORCE_RESET
#define __TIM22_RELEASE_RESET  __HAL_RCC_TIM22_RELEASE_RESET
#define __TIM22_CLK_SLEEP_ENABLE   __HAL_RCC_TIM22_CLK_SLEEP_ENABLE
#define __TIM22_CLK_SLEEP_DISABLE   __HAL_RCC_TIM22_CLK_SLEEP_DISABLE
#define __CRS_CLK_DISABLE __HAL_RCC_CRS_CLK_DISABLE
#define __CRS_CLK_ENABLE __HAL_RCC_CRS_CLK_ENABLE
#define __CRS_CLK_SLEEP_DISABLE __HAL_RCC_CRS_CLK_SLEEP_DISABLE
#define __CRS_CLK_SLEEP_ENABLE __HAL_RCC_CRS_CLK_SLEEP_ENABLE
#define __CRS_FORCE_RESET __HAL_RCC_CRS_FORCE_RESET
#define __CRS_RELEASE_RESET __HAL_RCC_CRS_RELEASE_RESET
#define __RCC_BACKUPRESET_FORCE __HAL_RCC_BACKUPRESET_FORCE
#define __RCC_BACKUPRESET_RELEASE __HAL_RCC_BACKUPRESET_RELEASE

#define __USB_OTG_FS_FORCE_RESET  __HAL_RCC_USB_OTG_FS_FORCE_RESET
#define __USB_OTG_FS_RELEASE_RESET  __HAL_RCC_USB_OTG_FS_RELEASE_RESET
#define __USB_OTG_FS_CLK_SLEEP_ENABLE  __HAL_RCC_USB_OTG_FS_CLK_SLEEP_ENABLE
#define __USB_OTG_FS_CLK_SLEEP_DISABLE  __HAL_RCC_USB_OTG_FS_CLK_SLEEP_DISABLE
#define __USB_OTG_HS_CLK_DISABLE  __HAL_RCC_USB_OTG_HS_CLK_DISABLE
#define __USB_OTG_HS_CLK_ENABLE          __HAL_RCC_USB_OTG_HS_CLK_ENABLE
#define __USB_OTG_HS_ULPI_CLK_ENABLE  __HAL_RCC_USB_OTG_HS_ULPI_CLK_ENABLE
#define __USB_OTG_HS_ULPI_CLK_DISABLE  __HAL_RCC_USB_OTG_HS_ULPI_CLK_DISABLE  
#define __FLITF_CLK_SLEEP_ENABLE  __HAL_RCC_FLITF_CLK_SLEEP_ENABLE
#define __FLITF_CLK_SLEEP_DISABLE  __HAL_RCC_FLITF_CLK_SLEEP_DISABLE
#define __ADC1_CLK_SLEEP_ENABLE          __HAL_RCC_ADC1_CLK_SLEEP_ENABLE  
#define __TIM9_CLK_SLEEP_ENABLE          __HAL_RCC_TIM9_CLK_SLEEP_ENABLE
#define __TIM9_CLK_SLEEP_DISABLE  __HAL_RCC_TIM9_CLK_SLEEP_DISABLE  
#define __TIM10_CLK_SLEEP_ENABLE  __HAL_RCC_TIM10_CLK_SLEEP_ENABLE
#define __TIM10_CLK_SLEEP_DISABLE  __HAL_RCC_TIM10_CLK_SLEEP_DISABLE  
#define __TIM11_CLK_SLEEP_ENABLE  __HAL_RCC_TIM11_CLK_SLEEP_ENABLE
#define __TIM11_CLK_SLEEP_DISABLE  __HAL_RCC_TIM11_CLK_SLEEP_DISABLE  
#define __ETHMACPTP_CLK_SLEEP_ENABLE  __HAL_RCC_ETHMACPTP_CLK_SLEEP_ENABLE
#define __ETHMACPTP_CLK_SLEEP_DISABLE  __HAL_RCC_ETHMACPTP_CLK_SLEEP_DISABLE
#define __ETHMACPTP_CLK_ENABLE          __HAL_RCC_ETHMACPTP_CLK_ENABLE
#define __ETHMACPTP_CLK_DISABLE          __HAL_RCC_ETHMACPTP_CLK_DISABLE  
#define __HASH_CLK_ENABLE          __HAL_RCC_HASH_CLK_ENABLE
#define __HASH_FORCE_RESET          __HAL_RCC_HASH_FORCE_RESET
#define __HASH_RELEASE_RESET          __HAL_RCC_HASH_RELEASE_RESET
#define __HASH_CLK_SLEEP_ENABLE          __HAL_RCC_HASH_CLK_SLEEP_ENABLE
#define __HASH_CLK_SLEEP_DISABLE  __HAL_RCC_HASH_CLK_SLEEP_DISABLE
#define __HASH_CLK_DISABLE            __HAL_RCC_HASH_CLK_DISABLE  
#define __SPI5_CLK_ENABLE          __HAL_RCC_SPI5_CLK_ENABLE
#define __SPI5_CLK_DISABLE              __HAL_RCC_SPI5_CLK_DISABLE
#define __SPI5_FORCE_RESET          __HAL_RCC_SPI5_FORCE_RESET
#define __SPI5_RELEASE_RESET          __HAL_RCC_SPI5_RELEASE_RESET
#define __SPI5_CLK_SLEEP_ENABLE          __HAL_RCC_SPI5_CLK_SLEEP_ENABLE
#define __SPI5_CLK_SLEEP_DISABLE  __HAL_RCC_SPI5_CLK_SLEEP_DISABLE  
#define __SPI6_CLK_ENABLE          __HAL_RCC_SPI6_CLK_ENABLE
#define __SPI6_CLK_DISABLE          __HAL_RCC_SPI6_CLK_DISABLE
#define __SPI6_FORCE_RESET          __HAL_RCC_SPI6_FORCE_RESET
#define __SPI6_RELEASE_RESET         __HAL_RCC_SPI6_RELEASE_RESET
#define __SPI6_CLK_SLEEP_ENABLE          __HAL_RCC_SPI6_CLK_SLEEP_ENABLE
#define __SPI6_CLK_SLEEP_DISABLE  __HAL_RCC_SPI6_CLK_SLEEP_DISABLE  
#define __LTDC_CLK_ENABLE          __HAL_RCC_LTDC_CLK_ENABLE
#define __LTDC_CLK_DISABLE          __HAL_RCC_LTDC_CLK_DISABLE
#define __LTDC_FORCE_RESET          __HAL_RCC_LTDC_FORCE_RESET
#define __LTDC_RELEASE_RESET          __HAL_RCC_LTDC_RELEASE_RESET
#define __LTDC_CLK_SLEEP_ENABLE          __HAL_RCC_LTDC_CLK_SLEEP_ENABLE  
#define __ETHMAC_CLK_SLEEP_ENABLE  __HAL_RCC_ETHMAC_CLK_SLEEP_ENABLE
#define __ETHMAC_CLK_SLEEP_DISABLE  __HAL_RCC_ETHMAC_CLK_SLEEP_DISABLE  
#define __ETHMACTX_CLK_SLEEP_ENABLE  __HAL_RCC_ETHMACTX_CLK_SLEEP_ENABLE
#define __ETHMACTX_CLK_SLEEP_DISABLE  __HAL_RCC_ETHMACTX_CLK_SLEEP_DISABLE  
#define __ETHMACRX_CLK_SLEEP_ENABLE  __HAL_RCC_ETHMACRX_CLK_SLEEP_ENABLE
#define __ETHMACRX_CLK_SLEEP_DISABLE  __HAL_RCC_ETHMACRX_CLK_SLEEP_DISABLE  
#define __TIM12_CLK_SLEEP_ENABLE  __HAL_RCC_TIM12_CLK_SLEEP_ENABLE
#define __TIM12_CLK_SLEEP_DISABLE  __HAL_RCC_TIM12_CLK_SLEEP_DISABLE  
#define __TIM13_CLK_SLEEP_ENABLE  __HAL_RCC_TIM13_CLK_SLEEP_ENABLE
#define __TIM13_CLK_SLEEP_DISABLE  __HAL_RCC_TIM13_CLK_SLEEP_DISABLE  
#define __TIM14_CLK_SLEEP_ENABLE  __HAL_RCC_TIM14_CLK_SLEEP_ENABLE
#define __TIM14_CLK_SLEEP_DISABLE  __HAL_RCC_TIM14_CLK_SLEEP_DISABLE  
#define __BKPSRAM_CLK_ENABLE          __HAL_RCC_BKPSRAM_CLK_ENABLE
#define __BKPSRAM_CLK_DISABLE          __HAL_RCC_BKPSRAM_CLK_DISABLE
#define __BKPSRAM_CLK_SLEEP_ENABLE  __HAL_RCC_BKPSRAM_CLK_SLEEP_ENABLE
#define __BKPSRAM_CLK_SLEEP_DISABLE  __HAL_RCC_BKPSRAM_CLK_SLEEP_DISABLE  
#define __CCMDATARAMEN_CLK_ENABLE  __HAL_RCC_CCMDATARAMEN_CLK_ENABLE
#define __CCMDATARAMEN_CLK_DISABLE  __HAL_RCC_CCMDATARAMEN_CLK_DISABLE  
#define __USART6_CLK_ENABLE          __HAL_RCC_USART6_CLK_ENABLE
#define __USART6_CLK_DISABLE          __HAL_RCC_USART6_CLK_DISABLE
#define __USART6_FORCE_RESET        __HAL_RCC_USART6_FORCE_RESET
#define __USART6_RELEASE_RESET        __HAL_RCC_USART6_RELEASE_RESET
#define __USART6_CLK_SLEEP_ENABLE  __HAL_RCC_USART6_CLK_SLEEP_ENABLE
#define __USART6_CLK_SLEEP_DISABLE  __HAL_RCC_USART6_CLK_SLEEP_DISABLE  
#define __SPI4_CLK_ENABLE          __HAL_RCC_SPI4_CLK_ENABLE
#define __SPI4_CLK_DISABLE          __HAL_RCC_SPI4_CLK_DISABLE
#define __SPI4_FORCE_RESET          __HAL_RCC_SPI4_FORCE_RESET
#define __SPI4_RELEASE_RESET        __HAL_RCC_SPI4_RELEASE_RESET
#define __SPI4_CLK_SLEEP_ENABLE   __HAL_RCC_SPI4_CLK_SLEEP_ENABLE
#define __SPI4_CLK_SLEEP_DISABLE  __HAL_RCC_SPI4_CLK_SLEEP_DISABLE  
#define __GPIOI_CLK_ENABLE          __HAL_RCC_GPIOI_CLK_ENABLE
#define __GPIOI_CLK_DISABLE          __HAL_RCC_GPIOI_CLK_DISABLE
#define __GPIOI_FORCE_RESET          __HAL_RCC_GPIOI_FORCE_RESET
#define __GPIOI_RELEASE_RESET          __HAL_RCC_GPIOI_RELEASE_RESET
#define __GPIOI_CLK_SLEEP_ENABLE  __HAL_RCC_GPIOI_CLK_SLEEP_ENABLE
#define __GPIOI_CLK_SLEEP_DISABLE  __HAL_RCC_GPIOI_CLK_SLEEP_DISABLE  
#define __GPIOJ_CLK_ENABLE          __HAL_RCC_GPIOJ_CLK_ENABLE
#define __GPIOJ_CLK_DISABLE          __HAL_RCC_GPIOJ_CLK_DISABLE
#define __GPIOJ_FORCE_RESET         __HAL_RCC_GPIOJ_FORCE_RESET
#define __GPIOJ_RELEASE_RESET          __HAL_RCC_GPIOJ_RELEASE_RESET
#define __GPIOJ_CLK_SLEEP_ENABLE  __HAL_RCC_GPIOJ_CLK_SLEEP_ENABLE
#define __GPIOJ_CLK_SLEEP_DISABLE  __HAL_RCC_GPIOJ_CLK_SLEEP_DISABLE  
#define __GPIOK_CLK_ENABLE          __HAL_RCC_GPIOK_CLK_ENABLE
#define __GPIOK_CLK_DISABLE          __HAL_RCC_GPIOK_CLK_DISABLE
#define __GPIOK_RELEASE_RESET          __HAL_RCC_GPIOK_RELEASE_RESET
#define __GPIOK_CLK_SLEEP_ENABLE  __HAL_RCC_GPIOK_CLK_SLEEP_ENABLE
#define __GPIOK_CLK_SLEEP_DISABLE  __HAL_RCC_GPIOK_CLK_SLEEP_DISABLE  
#define __ETH_CLK_ENABLE          __HAL_RCC_ETH_CLK_ENABLE
#define __ETH_CLK_DISABLE          __HAL_RCC_ETH_CLK_DISABLE  
#define __DCMI_CLK_ENABLE          __HAL_RCC_DCMI_CLK_ENABLE
#define __DCMI_CLK_DISABLE          __HAL_RCC_DCMI_CLK_DISABLE
#define __DCMI_FORCE_RESET          __HAL_RCC_DCMI_FORCE_RESET
#define __DCMI_RELEASE_RESET          __HAL_RCC_DCMI_RELEASE_RESET
#define __DCMI_CLK_SLEEP_ENABLE   __HAL_RCC_DCMI_CLK_SLEEP_ENABLE
#define __DCMI_CLK_SLEEP_DISABLE  __HAL_RCC_DCMI_CLK_SLEEP_DISABLE  
#define __UART7_CLK_ENABLE          __HAL_RCC_UART7_CLK_ENABLE
#define __UART7_CLK_DISABLE          __HAL_RCC_UART7_CLK_DISABLE
#define __UART7_RELEASE_RESET       __HAL_RCC_UART7_RELEASE_RESET
#define __UART7_FORCE_RESET       __HAL_RCC_UART7_FORCE_RESET
#define __UART7_CLK_SLEEP_ENABLE  __HAL_RCC_UART7_CLK_SLEEP_ENABLE
#define __UART7_CLK_SLEEP_DISABLE  __HAL_RCC_UART7_CLK_SLEEP_DISABLE  
#define __UART8_CLK_ENABLE          __HAL_RCC_UART8_CLK_ENABLE
#define __UART8_CLK_DISABLE          __HAL_RCC_UART8_CLK_DISABLE
#define __UART8_FORCE_RESET          __HAL_RCC_UART8_FORCE_RESET
#define __UART8_RELEASE_RESET          __HAL_RCC_UART8_RELEASE_RESET
#define __UART8_CLK_SLEEP_ENABLE  __HAL_RCC_UART8_CLK_SLEEP_ENABLE
#define __UART8_CLK_SLEEP_DISABLE  __HAL_RCC_UART8_CLK_SLEEP_DISABLE  
#define __OTGHS_CLK_SLEEP_ENABLE  __HAL_RCC_OTGHS_CLK_SLEEP_ENABLE
#define __OTGHS_CLK_SLEEP_DISABLE  __HAL_RCC_OTGHS_CLK_SLEEP_DISABLE
#define __OTGHS_FORCE_RESET          __HAL_RCC_OTGHS_FORCE_RESET
#define __OTGHS_RELEASE_RESET          __HAL_RCC_OTGHS_RELEASE_RESET  
#define __OTGHSULPI_CLK_SLEEP_ENABLE  __HAL_RCC_OTGHSULPI_CLK_SLEEP_ENABLE
#define __OTGHSULPI_CLK_SLEEP_DISABLE  __HAL_RCC_OTGHSULPI_CLK_SLEEP_DISABLE  
#define __CRYP_FORCE_RESET          __HAL_RCC_CRYP_FORCE_RESET  
#define __SRAM3_CLK_SLEEP_ENABLE  __HAL_RCC_SRAM3_CLK_SLEEP_ENABLE  
#define __CAN2_CLK_SLEEP_ENABLE          __HAL_RCC_CAN2_CLK_SLEEP_ENABLE
#define __CAN2_CLK_SLEEP_DISABLE  __HAL_RCC_CAN2_CLK_SLEEP_DISABLE  
#define __DAC_CLK_SLEEP_ENABLE          __HAL_RCC_DAC_CLK_SLEEP_ENABLE
#define __DAC_CLK_SLEEP_DISABLE   __HAL_RCC_DAC_CLK_SLEEP_DISABLE  
#define __ADC2_CLK_SLEEP_ENABLE   __HAL_RCC_ADC2_CLK_SLEEP_ENABLE
#define __ADC2_CLK_SLEEP_DISABLE  __HAL_RCC_ADC2_CLK_SLEEP_DISABLE  
#define __ADC3_CLK_SLEEP_ENABLE          __HAL_RCC_ADC3_CLK_SLEEP_ENABLE
#define __ADC3_CLK_SLEEP_DISABLE  __HAL_RCC_ADC3_CLK_SLEEP_DISABLE  
#define __FSMC_FORCE_RESET          __HAL_RCC_FSMC_FORCE_RESET
#define __FSMC_RELEASE_RESET          __HAL_RCC_FSMC_RELEASE_RESET
#define __FSMC_CLK_SLEEP_ENABLE          __HAL_RCC_FSMC_CLK_SLEEP_ENABLE
#define __FSMC_CLK_SLEEP_DISABLE  __HAL_RCC_FSMC_CLK_SLEEP_DISABLE  
#define __SDIO_FORCE_RESET          __HAL_RCC_SDIO_FORCE_RESET
#define __SDIO_RELEASE_RESET          __HAL_RCC_SDIO_RELEASE_RESET
#define __SDIO_CLK_SLEEP_DISABLE  __HAL_RCC_SDIO_CLK_SLEEP_DISABLE
#define __SDIO_CLK_SLEEP_ENABLE          __HAL_RCC_SDIO_CLK_SLEEP_ENABLE  
#define __DMA2D_CLK_ENABLE          __HAL_RCC_DMA2D_CLK_ENABLE
#define __DMA2D_CLK_DISABLE          __HAL_RCC_DMA2D_CLK_DISABLE
#define __DMA2D_FORCE_RESET          __HAL_RCC_DMA2D_FORCE_RESET
#define __DMA2D_RELEASE_RESET          __HAL_RCC_DMA2D_RELEASE_RESET
#define __DMA2D_CLK_SLEEP_ENABLE  __HAL_RCC_DMA2D_CLK_SLEEP_ENABLE
#define __DMA2D_CLK_SLEEP_DISABLE  __HAL_RCC_DMA2D_CLK_SLEEP_DISABLE

/* alias define maintained for legacy */
#define __HAL_RCC_OTGFS_FORCE_RESET    __HAL_RCC_USB_OTG_FS_FORCE_RESET
#define __HAL_RCC_OTGFS_RELEASE_RESET  __HAL_RCC_USB_OTG_FS_RELEASE_RESET

#define __HAL_RCC_I2SCLK            __HAL_RCC_I2S_CONFIG
#define __HAL_RCC_I2SCLK_CONFIG     __HAL_RCC_I2S_CONFIG

#define __RCC_PLLSRC           RCC_GET_PLL_OSCSOURCE

#define HSION_BitNumber        RCC_HSION_BIT_NUMBER
#define CSSON_BitNumber        RCC_CSSON_BIT_NUMBER
#define PLLON_BitNumber        RCC_PLLON_BIT_NUMBER
#define PLLI2SON_BitNumber     RCC_PLLI2SON_BIT_NUMBER
#define I2SSRC_BitNumber       RCC_I2SSRC_BIT_NUMBER
#define RTCEN_BitNumber        RCC_RTCEN_BIT_NUMBER
#define BDRST_BitNumber        RCC_BDRST_BIT_NUMBER
#define LSION_BitNumber        RCC_LSION_BIT_NUMBER
#define PLLSAION_BitNumber     RCC_PLLSAION_BIT_NUMBER
#define TIMPRE_BitNumber       RCC_TIMPRE_BIT_NUMBER

#define CR_BYTE2_ADDRESS       RCC_CR_BYTE2_ADDRESS
#define CIR_BYTE1_ADDRESS      RCC_CIR_BYTE1_ADDRESS
#define CIR_BYTE2_ADDRESS      RCC_CIR_BYTE2_ADDRESS
#define BDCR_BYTE0_ADDRESS     RCC_BDCR_BYTE0_ADDRESS
#define DBP_TIMEOUT_VALUE      RCC_DBP_TIMEOUT_VALUE
#define LSE_TIMEOUT_VALUE      RCC_LSE_TIMEOUT_VALUE

#define CR_HSION_BB            RCC_CR_HSION_BB
#define CR_CSSON_BB            RCC_CR_CSSON_BB
#define CR_PLLON_BB            RCC_CR_PLLON_BB
#define CR_PLLI2SON_BB         RCC_CR_PLLI2SON_BB
#define CFGR_I2SSRC_BB         RCC_CFGR_I2SSRC_BB
#define BDCR_RTCEN_BB          RCC_BDCR_RTCEN_BB
#define BDCR_BDRST_BB          RCC_BDCR_BDRST_BB
#define CSR_LSION_BB           RCC_CSR_LSION_BB
#define CR_PLLSAION_BB         RCC_CR_PLLSAION_BB
#define DCKCFGR_TIMPRE_BB      RCC_DCKCFGR_TIMPRE_BB

/**
  * @}
  */

/** @defgroup HAL_RNG_Aliased_Macros HAL RNG Aliased Macros maintained for legacy purpose
  * @{
  */
#define  HAL_RNG_ReadyCallback(__HANDLE__)  HAL_RNG_ReadyDataCallback(__HANDLE__, uint32_t random32bit)                                       

/**
  * @}
  */
  
/** @defgroup HAL_RTC_Aliased_Macros HAL RTC Aliased Macros maintained for legacy purpose
  * @{
  */
  
#define __HAL_RTC_CLEAR_FLAG                      __HAL_RTC_EXTI_CLEAR_FLAG
#define __HAL_RTC_DISABLE_IT                      __HAL_RTC_EXTI_DISABLE_IT
#define __HAL_RTC_ENABLE_IT                       __HAL_RTC_EXTI_ENABLE_IT
#if defined (RTC_EXTI_LINE_WAKEUPTIMER_EVENT)
#define __HAL_RTC_EXTI_CLEAR_FLAG(__EXTI_LINE__)  ((__EXTI_LINE__ == RTC_EXTI_LINE_ALARM_EVENT) ? __HAL_RTC_ALARM_EXTI_CLEAR_FLAG() : \
((__EXTI_LINE__ == RTC_EXTI_LINE_WAKEUPTIMER_EVENT) ? __HAL_RTC_WAKEUPTIMER_EXTI_CLEAR_FLAG() : \
                                                      __HAL_RTC_TAMPER_TIMESTAMP_EXTI_CLEAR_FLAG()))
#define __HAL_RTC_EXTI_ENABLE_IT(__EXTI_LINE__)   ((__EXTI_LINE__  == RTC_EXTI_LINE_ALARM_EVENT) ? __HAL_RTC_ALARM_EXTI_ENABLE_IT() : \
                                                  ((__EXTI_LINE__ == RTC_EXTI_LINE_WAKEUPTIMER_EVENT) ? __HAL_RTC_WAKEUPTIMER_EXTI_ENABLE_IT() : \
                                                      __HAL_RTC_TAMPER_TIMESTAMP_EXTI_ENABLE_IT()))
#define __HAL_RTC_EXTI_DISABLE_IT(__EXTI_LINE__)  ((__EXTI_LINE__ == RTC_EXTI_LINE_ALARM_EVENT) ? __HAL_RTC_ALARM_EXTI_DISABLE_IT() : \
                                                  ((__EXTI_LINE__ == RTC_EXTI_LINE_WAKEUPTIMER_EVENT) ? __HAL_RTC_WAKEUPTIMER_EXTI_DISABLE_IT() : \
                                                      __HAL_RTC_TAMPER_TIMESTAMP_EXTI_DISABLE_IT()))
#define __HAL_RTC_EXTI_GET_FLAG(__EXTI_LINE__)    ((__EXTI_LINE__ == RTC_EXTI_LINE_ALARM_EVENT) ? __HAL_RTC_ALARM_EXTI_GET_FLAG() : \
                                                  ((__EXTI_LINE__ == RTC_EXTI_LINE_WAKEUPTIMER_EVENT) ? __HAL_RTC_WAKEUPTIMER_EXTI_GET_FLAG() : \
                                                      __HAL_RTC_TAMPER_TIMESTAMP_EXTI_GET_FLAG()))
#define __HAL_RTC_EXTI_GENERATE_SWIT(__EXTI_LINE__)   ((__EXTI_LINE__ == RTC_EXTI_LINE_ALARM_EVENT) ? __HAL_RTC_ALARM_EXTI_GENERATE_SWIT() : \
                                                      ((__EXTI_LINE__ == RTC_EXTI_LINE_WAKEUPTIMER_EVENT) ? __HAL_RTC_WAKEUPTIMER_EXTI_GENERATE_SWIT() :  \
                                                          __HAL_RTC_TAMPER_TIMESTAMP_EXTI_GENERATE_SWIT()))

#else
#define __HAL_RTC_EXTI_CLEAR_FLAG(RTC_EXTI_LINE_ALARM_EVENT)  __HAL_RTC_ALARM_EXTI_CLEAR_FLAG()

#define __HAL_RTC_EXTI_ENABLE_IT(RTC_EXTI_LINE_ALARM_EVENT)   __HAL_RTC_ALARM_EXTI_ENABLE_IT()

#define __HAL_RTC_EXTI_DISABLE_IT(RTC_EXTI_LINE_ALARM_EVENT)  __HAL_RTC_ALARM_EXTI_DISABLE_IT()

#define __HAL_RTC_EXTI_GET_FLAG(RTC_EXTI_LINE_ALARM_EVENT)    __HAL_RTC_ALARM_EXTI_GET_FLAG()

#define __HAL_RTC_EXTI_GENERATE_SWIT(RTC_EXTI_LINE_ALARM_EVENT)   __HAL_RTC_ALARM_EXTI_GENERATE_SWIT()

#endif

#define IS_ALARM                                  IS_RTC_ALARM
#define IS_ALARM_MASK                             IS_RTC_ALARM_MASK
#define IS_TAMPER                                 IS_RTC_TAMPER
#define IS_TAMPER_ERASE_MODE                      IS_RTC_TAMPER_ERASE_MODE
#define IS_TAMPER_FILTER                          IS_RTC_TAMPER_FILTER 
#define IS_TAMPER_INTERRUPT                       IS_RTC_TAMPER_INTERRUPT
#define IS_TAMPER_MASKFLAG_STATE                  IS_RTC_TAMPER_MASKFLAG_STATE
#define IS_TAMPER_PRECHARGE_DURATION              IS_RTC_TAMPER_PRECHARGE_DURATION
#define IS_TAMPER_PULLUP_STATE                    IS_RTC_TAMPER_PULLUP_STATE
#define IS_TAMPER_SAMPLING_FREQ                   IS_RTC_TAMPER_SAMPLING_FREQ
#define IS_TAMPER_TIMESTAMPONTAMPER_DETECTION     IS_RTC_TAMPER_TIMESTAMPONTAMPER_DETECTION
#define IS_TAMPER_TRIGGER                         IS_RTC_TAMPER_TRIGGER
#define IS_WAKEUP_CLOCK                           IS_RTC_WAKEUP_CLOCK
#define IS_WAKEUP_COUNTER                         IS_RTC_WAKEUP_COUNTER

#define __RTC_WRITEPROTECTION_ENABLE  __HAL_RTC_WRITEPROTECTION_ENABLE
#define __RTC_WRITEPROTECTION_DISABLE  __HAL_RTC_WRITEPROTECTION_DISABLE

/**
  * @}
  */

/** @defgroup HAL_SD_Aliased_Macros HAL SD Aliased Macros maintained for legacy purpose
  * @{
  */

#define SD_OCR_CID_CSD_OVERWRIETE   SD_OCR_CID_CSD_OVERWRITE
#define SD_CMD_SD_APP_STAUS         SD_CMD_SD_APP_STATUS
  
/**
  * @}
  */

/** @defgroup HAL_SMARTCARD_Aliased_Macros HAL SMARTCARD Aliased Macros maintained for legacy purpose
  * @{
  */

#define __SMARTCARD_ENABLE_IT           __HAL_SMARTCARD_ENABLE_IT
#define __SMARTCARD_DISABLE_IT          __HAL_SMARTCARD_DISABLE_IT
#define __SMARTCARD_ENABLE              __HAL_SMARTCARD_ENABLE
#define __SMARTCARD_DISABLE             __HAL_SMARTCARD_DISABLE
#define __SMARTCARD_DMA_REQUEST_ENABLE  __HAL_SMARTCARD_DMA_REQUEST_ENABLE
#define __SMARTCARD_DMA_REQUEST_DISABLE __HAL_SMARTCARD_DMA_REQUEST_DISABLE

#define __HAL_SMARTCARD_GETCLOCKSOURCE  SMARTCARD_GETCLOCKSOURCE
#define __SMARTCARD_GETCLOCKSOURCE      SMARTCARD_GETCLOCKSOURCE

#define IS_SMARTCARD_ONEBIT_SAMPLING    IS_SMARTCARD_ONE_BIT_SAMPLE                  

/**
  * @}
  */

/** @defgroup HAL_SMBUS_Aliased_Macros HAL SMBUS Aliased Macros maintained for legacy purpose
  * @{
  */
#define __HAL_SMBUS_RESET_CR1           SMBUS_RESET_CR1
#define __HAL_SMBUS_RESET_CR2           SMBUS_RESET_CR2
#define __HAL_SMBUS_GENERATE_START      SMBUS_GENERATE_START
#define __HAL_SMBUS_GET_ADDR_MATCH      SMBUS_GET_ADDR_MATCH
#define __HAL_SMBUS_GET_DIR             SMBUS_GET_DIR
#define __HAL_SMBUS_GET_STOP_MODE       SMBUS_GET_STOP_MODE
#define __HAL_SMBUS_GET_PEC_MODE        SMBUS_GET_PEC_MODE
#define __HAL_SMBUS_GET_ALERT_ENABLED   SMBUS_GET_ALERT_ENABLED
/**
  * @}
  */

/** @defgroup HAL_SPI_Aliased_Macros HAL SPI Aliased Macros maintained for legacy purpose
  * @{
  */

#define __HAL_SPI_1LINE_TX              SPI_1LINE_TX
#define __HAL_SPI_1LINE_RX              SPI_1LINE_RX
#define __HAL_SPI_RESET_CRC             SPI_RESET_CRC

/**
  * @}
  */
  
/** @defgroup HAL_UART_Aliased_Macros HAL UART Aliased Macros maintained for legacy purpose
  * @{
  */

#define __HAL_UART_GETCLOCKSOURCE       UART_GETCLOCKSOURCE
#define __HAL_UART_MASK_COMPUTATION     UART_MASK_COMPUTATION
#define __UART_GETCLOCKSOURCE           UART_GETCLOCKSOURCE
#define __UART_MASK_COMPUTATION         UART_MASK_COMPUTATION

#define IS_UART_WAKEUPMETHODE           IS_UART_WAKEUPMETHOD

#define IS_UART_ONEBIT_SAMPLE           IS_UART_ONE_BIT_SAMPLE                  
#define IS_UART_ONEBIT_SAMPLING         IS_UART_ONE_BIT_SAMPLE                  

/**
  * @}
  */


/** @defgroup HAL_USART_Aliased_Macros HAL USART Aliased Macros maintained for legacy purpose
  * @{
  */

#define __USART_ENABLE_IT               __HAL_USART_ENABLE_IT
#define __USART_DISABLE_IT              __HAL_USART_DISABLE_IT
#define __USART_ENABLE                  __HAL_USART_ENABLE
#define __USART_DISABLE                 __HAL_USART_DISABLE

#define __HAL_USART_GETCLOCKSOURCE      USART_GETCLOCKSOURCE
#define __USART_GETCLOCKSOURCE          USART_GETCLOCKSOURCE

/**
  * @}
  */

/** @defgroup HAL_USB_Aliased_Macros HAL USB Aliased Macros maintained for legacy purpose
  * @{
  */
#define USB_EXTI_LINE_WAKEUP                               USB_WAKEUP_EXTI_LINE

#define USB_FS_EXTI_TRIGGER_RISING_EDGE                    USB_OTG_FS_WAKEUP_EXTI_RISING_EDGE
#define USB_FS_EXTI_TRIGGER_FALLING_EDGE                   USB_OTG_FS_WAKEUP_EXTI_FALLING_EDGE
#define USB_FS_EXTI_TRIGGER_BOTH_EDGE                      USB_OTG_FS_WAKEUP_EXTI_RISING_FALLING_EDGE
#define USB_FS_EXTI_LINE_WAKEUP                            USB_OTG_FS_WAKEUP_EXTI_LINE

#define USB_HS_EXTI_TRIGGER_RISING_EDGE                    USB_OTG_HS_WAKEUP_EXTI_RISING_EDGE
#define USB_HS_EXTI_TRIGGER_FALLING_EDGE                   USB_OTG_HS_WAKEUP_EXTI_FALLING_EDGE
#define USB_HS_EXTI_TRIGGER_BOTH_EDGE                      USB_OTG_HS_WAKEUP_EXTI_RISING_FALLING_EDGE
#define USB_HS_EXTI_LINE_WAKEUP                            USB_OTG_HS_WAKEUP_EXTI_LINE

#define __HAL_USB_EXTI_ENABLE_IT                           __HAL_USB_WAKEUP_EXTI_ENABLE_IT
#define __HAL_USB_EXTI_DISABLE_IT                          __HAL_USB_WAKEUP_EXTI_DISABLE_IT
#define __HAL_USB_EXTI_GET_FLAG                            __HAL_USB_WAKEUP_EXTI_GET_FLAG
#define __HAL_USB_EXTI_CLEAR_FLAG                          __HAL_USB_WAKEUP_EXTI_CLEAR_FLAG
#define __HAL_USB_EXTI_SET_RISING_EDGE_TRIGGER             __HAL_USB_WAKEUP_EXTI_ENABLE_RISING_EDGE
#define __HAL_USB_EXTI_SET_FALLING_EDGE_TRIGGER            __HAL_USB_WAKEUP_EXTI_ENABLE_FALLING_EDGE
#define __HAL_USB_EXTI_SET_FALLINGRISING_TRIGGER           __HAL_USB_WAKEUP_EXTI_ENABLE_RISING_FALLING_EDGE

#define __HAL_USB_FS_EXTI_ENABLE_IT                        __HAL_USB_OTG_FS_WAKEUP_EXTI_ENABLE_IT
#define __HAL_USB_FS_EXTI_DISABLE_IT                       __HAL_USB_OTG_FS_WAKEUP_EXTI_DISABLE_IT
#define __HAL_USB_FS_EXTI_GET_FLAG                         __HAL_USB_OTG_FS_WAKEUP_EXTI_GET_FLAG
#define __HAL_USB_FS_EXTI_CLEAR_FLAG                       __HAL_USB_OTG_FS_WAKEUP_EXTI_CLEAR_FLAG
#define __HAL_USB_FS_EXTI_SET_RISING_EGDE_TRIGGER          __HAL_USB_OTG_FS_WAKEUP_EXTI_ENABLE_RISING_EDGE
#define __HAL_USB_FS_EXTI_SET_FALLING_EGDE_TRIGGER         __HAL_USB_OTG_FS_WAKEUP_EXTI_ENABLE_FALLING_EDGE
#define __HAL_USB_FS_EXTI_SET_FALLINGRISING_TRIGGER        __HAL_USB_OTG_FS_WAKEUP_EXTI_ENABLE_RISING_FALLING_EDGE
#define __HAL_USB_FS_EXTI_GENERATE_SWIT                    __HAL_USB_OTG_FS_WAKEUP_EXTI_GENERATE_SWIT

#define __HAL_USB_HS_EXTI_ENABLE_IT                        __HAL_USB_OTG_HS_WAKEUP_EXTI_ENABLE_IT
#define __HAL_USB_HS_EXTI_DISABLE_IT                       __HAL_USB_OTG_HS_WAKEUP_EXTI_DISABLE_IT
#define __HAL_USB_HS_EXTI_GET_FLAG                         __HAL_USB_OTG_HS_WAKEUP_EXTI_GET_FLAG
#define __HAL_USB_HS_EXTI_CLEAR_FLAG                       __HAL_USB_OTG_HS_WAKEUP_EXTI_CLEAR_FLAG
#define __HAL_USB_HS_EXTI_SET_RISING_EGDE_TRIGGER          __HAL_USB_OTG_HS_WAKEUP_EXTI_ENABLE_RISING_EDGE
#define __HAL_USB_HS_EXTI_SET_FALLING_EGDE_TRIGGER         __HAL_USB_OTG_HS_WAKEUP_EXTI_ENABLE_FALLING_EDGE
#define __HAL_USB_HS_EXTI_SET_FALLINGRISING_TRIGGER        __HAL_USB_OTG_HS_WAKEUP_EXTI_ENABLE_RISING_FALLING_EDGE
#define __HAL_USB_HS_EXTI_GENERATE_SWIT                    __HAL_USB_OTG_HS_WAKEUP_EXTI_GENERATE_SWIT

#define HAL_PCD_ActiveRemoteWakeup                         HAL_PCD_ActivateRemoteWakeup
#define HAL_PCD_DeActiveRemoteWakeup                       HAL_PCD_DeActivateRemoteWakeup

#define HAL_PCD_SetTxFiFo                                  HAL_PCDEx_SetTxFiFo
#define HAL_PCD_SetRxFiFo                                  HAL_PCDEx_SetRxFiFo
/**
  * @}
  */

/** @defgroup HAL_TIM_Aliased_Macros HAL TIM Aliased Macros maintained for legacy purpose
  * @{
  */
#define __HAL_TIM_SetICPrescalerValue   TIM_SET_ICPRESCALERVALUE
#define __HAL_TIM_ResetICPrescalerValue TIM_RESET_ICPRESCALERVALUE

#define TIM_GET_ITSTATUS                __HAL_TIM_GET_IT_SOURCE
#define TIM_GET_CLEAR_IT                __HAL_TIM_CLEAR_IT

#define __HAL_TIM_DIRECTION_STATUS      __HAL_TIM_IS_TIM_COUNTING_DOWN
#define __HAL_TIM_PRESCALER             __HAL_TIM_SET_PRESCALER
#define __HAL_TIM_SetCounter            __HAL_TIM_SET_COUNTER
#define __HAL_TIM_GetCounter            __HAL_TIM_GET_COUNTER
#define __HAL_TIM_SetAutoreload         __HAL_TIM_SET_AUTORELOAD
#define __HAL_TIM_GetAutoreload         __HAL_TIM_GET_AUTORELOAD
#define __HAL_TIM_SetClockDivision      __HAL_TIM_SET_CLOCKDIVISION
#define __HAL_TIM_GetClockDivision      __HAL_TIM_GET_CLOCKDIVISION
#define __HAL_TIM_SetICPrescaler        __HAL_TIM_SET_ICPRESCALER
#define __HAL_TIM_GetICPrescaler        __HAL_TIM_GET_ICPRESCALER
#define __HAL_TIM_SetCompare            __HAL_TIM_SET_COMPARE
#define __HAL_TIM_GetCompare            __HAL_TIM_GET_COMPARE

#define TIM_TS_ITR0                        ((uint32_t)0x0000)
#define TIM_TS_ITR1                        ((uint32_t)0x0010)
#define TIM_TS_ITR2                        ((uint32_t)0x0020)
#define TIM_TS_ITR3                        ((uint32_t)0x0030)
#define IS_TIM_INTERNAL_TRIGGER_SELECTION(SELECTION) (((SELECTION) == TIM_TS_ITR0) || \
                                                      ((SELECTION) == TIM_TS_ITR1) || \
                                                      ((SELECTION) == TIM_TS_ITR2) || \
                                                      ((SELECTION) == TIM_TS_ITR3))

#define TIM_CHANNEL_1                      ((uint32_t)0x0000)
#define TIM_CHANNEL_2                      ((uint32_t)0x0004)
#define IS_TIM_PWMI_CHANNELS(CHANNEL) (((CHANNEL) == TIM_CHANNEL_1) || \
                                       ((CHANNEL) == TIM_CHANNEL_2))

#define TIM_OUTPUTNSTATE_DISABLE            ((uint32_t)0x0000)
#define TIM_OUTPUTNSTATE_ENABLE             (TIM_CCER_CC1NE)

#define IS_TIM_OUTPUTN_STATE(STATE) (((STATE) == TIM_OUTPUTNSTATE_DISABLE) || \
                                     ((STATE) == TIM_OUTPUTNSTATE_ENABLE))

#define TIM_OUTPUTSTATE_DISABLE            ((uint32_t)0x0000)
#define TIM_OUTPUTSTATE_ENABLE             (TIM_CCER_CC1E)

#define IS_TIM_OUTPUT_STATE(STATE) (((STATE) == TIM_OUTPUTSTATE_DISABLE) || \
                                    ((STATE) == TIM_OUTPUTSTATE_ENABLE))  
/**
  * @}
  */

/** @defgroup HAL_ETH_Aliased_Macros HAL ETH Aliased Macros maintained for legacy purpose
  * @{
  */
  
#define __HAL_ETH_EXTI_ENABLE_IT                   __HAL_ETH_WAKEUP_EXTI_ENABLE_IT
#define __HAL_ETH_EXTI_DISABLE_IT                  __HAL_ETH_WAKEUP_EXTI_DISABLE_IT
#define __HAL_ETH_EXTI_GET_FLAG                    __HAL_ETH_WAKEUP_EXTI_GET_FLAG
#define __HAL_ETH_EXTI_CLEAR_FLAG                  __HAL_ETH_WAKEUP_EXTI_CLEAR_FLAG
#define __HAL_ETH_EXTI_SET_RISING_EGDE_TRIGGER     __HAL_ETH_WAKEUP_EXTI_ENABLE_RISING_EDGE_TRIGGER
#define __HAL_ETH_EXTI_SET_FALLING_EGDE_TRIGGER    __HAL_ETH_WAKEUP_EXTI_ENABLE_FALLING_EDGE_TRIGGER
#define __HAL_ETH_EXTI_SET_FALLINGRISING_TRIGGER   __HAL_ETH_WAKEUP_EXTI_ENABLE_FALLINGRISING_TRIGGER

#define ETH_PROMISCIOUSMODE_ENABLE   ETH_PROMISCUOUS_MODE_ENABLE 
#define ETH_PROMISCIOUSMODE_DISABLE  ETH_PROMISCUOUS_MODE_DISABLE
#define IS_ETH_PROMISCIOUS_MODE      IS_ETH_PROMISCUOUS_MODE
/**
  * @}
  */

/** @defgroup HAL_LTDC_Aliased_Macros HAL LTDC Aliased Macros maintained for legacy purpose
  * @{
  */
#define __HAL_LTDC_LAYER LTDC_LAYER
/**
  * @}
  */

/** @defgroup HAL_SAI_Aliased_Macros HAL SAI Aliased Macros maintained for legacy purpose
  * @{
  */
#define SAI_OUTPUTDRIVE_DISABLED          SAI_OUTPUTDRIVE_DISABLE
#define SAI_OUTPUTDRIVE_ENABLED           SAI_OUTPUTDRIVE_ENABLE
#define SAI_MASTERDIVIDER_ENABLED         SAI_MASTERDIVIDER_ENABLE
#define SAI_MASTERDIVIDER_DISABLED        SAI_MASTERDIVIDER_DISABLE
#define SAI_STREOMODE                     SAI_STEREOMODE
#define SAI_FIFOStatus_Empty              SAI_FIFOSTATUS_EMPTY              
#define SAI_FIFOStatus_Less1QuarterFull   SAI_FIFOSTATUS_LESS1QUARTERFULL    
#define SAI_FIFOStatus_1QuarterFull       SAI_FIFOSTATUS_1QUARTERFULL       
#define SAI_FIFOStatus_HalfFull           SAI_FIFOSTATUS_HALFFULL           
#define SAI_FIFOStatus_3QuartersFull      SAI_FIFOSTATUS_3QUARTERFULL       
#define SAI_FIFOStatus_Full               SAI_FIFOSTATUS_FULL               
#define IS_SAI_BLOCK_MONO_STREO_MODE     IS_SAI_BLOCK_MONO_STEREO_MODE

/**
  * @}
  */


/** @defgroup HAL_PPP_Aliased_Macros HAL PPP Aliased Macros maintained for legacy purpose
  * @{
  */
  
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* ___STM32_HAL_LEGACY */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

