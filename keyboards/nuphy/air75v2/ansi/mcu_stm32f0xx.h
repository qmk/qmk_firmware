/*
Copyright 2023 NuPhy & Persama (@Persama)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#include "hal.h"
#include "stm32f0xx.h"
// ================================================================================
// ================================================================================

typedef enum { ST_RESET = 0,
               ST_SET   = !ST_RESET } ST_FlagStatus,
    ST_ITStatus;

//////////////////////////////////////////////////////////////////////////////
// PWR

/** @defgroup PWR_PVD_detection_level
 * @{
 */

#define PWR_PVDLevel_0          PWR_CR_PLS_LEV0
#define PWR_PVDLevel_1          PWR_CR_PLS_LEV1
#define PWR_PVDLevel_2          PWR_CR_PLS_LEV2
#define PWR_PVDLevel_3          PWR_CR_PLS_LEV3
#define PWR_PVDLevel_4          PWR_CR_PLS_LEV4
#define PWR_PVDLevel_5          PWR_CR_PLS_LEV5
#define PWR_PVDLevel_6          PWR_CR_PLS_LEV6
#define PWR_PVDLevel_7          PWR_CR_PLS_LEV7

#define IS_PWR_PVD_LEVEL(LEVEL) (((LEVEL) == PWR_PVDLevel_0) || ((LEVEL) == PWR_PVDLevel_1) || \
                                 ((LEVEL) == PWR_PVDLevel_2) || ((LEVEL) == PWR_PVDLevel_3) || \
                                 ((LEVEL) == PWR_PVDLevel_4) || ((LEVEL) == PWR_PVDLevel_5) || \
                                 ((LEVEL) == PWR_PVDLevel_6) || ((LEVEL) == PWR_PVDLevel_7))
/**
 * @}
 */

/** @defgroup PWR_WakeUp_Pins
 * @{
 */

#define PWR_WakeUpPin_1        PWR_CSR_EWUP1
#define PWR_WakeUpPin_2        PWR_CSR_EWUP2
#define IS_PWR_WAKEUP_PIN(PIN) (((PIN) == PWR_WakeUpPin_1) || \
                                ((PIN) == PWR_WakeUpPin_2))
/**
 * @}
 */

/** @defgroup PWR_Regulator_state_is_Sleep_STOP_mode
 * @{
 */

#define PWR_Regulator_ON            ((uint32_t)0x00000000)
#define PWR_Regulator_LowPower      ((uint32_t)0x00000001)
#define IS_PWR_REGULATOR(REGULATOR) (((REGULATOR) == PWR_Regulator_ON) || \
                                     ((REGULATOR) == PWR_Regulator_LowPower))
/**
 * @}
 */

/** @defgroup PWR_SLEEP_mode_entry
 * @{
 */

#define PWR_SLEEPEntry_WFI        ((uint8_t)0x01)
#define PWR_SLEEPEntry_WFE        ((uint8_t)0x02)
#define IS_PWR_SLEEP_ENTRY(ENTRY) (((ENTRY) == PWR_SLEEPEntry_WFI) || ((ENTRY) == PWR_SLEEPEntry_WFE))

/**
 * @}
 */

/** @defgroup PWR_STOP_mode_entry
 * @{
 */

#define PWR_STOPEntry_WFI         ((uint8_t)0x01)
#define PWR_STOPEntry_WFE         ((uint8_t)0x02)
#define IS_PWR_STOP_ENTRY(ENTRY)  (((ENTRY) == PWR_STOPEntry_WFI) || ((ENTRY) == PWR_STOPEntry_WFE))

/**
 * @}
 */

/** @defgroup PWR_Flag
 * @{
 */

#define PWR_FLAG_WU               PWR_CSR_WUF
#define PWR_FLAG_SB               PWR_CSR_SBF
#define PWR_FLAG_PVDO             PWR_CSR_PVDO
#define PWR_FLAG_VREFINTRDY       PWR_CSR_VREFINTRDYF

#define IS_PWR_GET_FLAG(FLAG)     (((FLAG) == PWR_FLAG_WU) || ((FLAG) == PWR_FLAG_SB) || \
                               ((FLAG) == PWR_FLAG_PVDO) || ((FLAG) == PWR_FLAG_VREFINTRDY))

#define IS_PWR_CLEAR_FLAG(FLAG) (((FLAG) == PWR_FLAG_WU) || ((FLAG) == PWR_FLAG_SB))
/**
 * @}
 */

/**
 * @}
 */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* Function used to set the PWR configuration to the default reset state ******/
void PWR_DeInit(void);

/* Backup Domain Access function **********************************************/
void PWR_BackupAccessCmd(FunctionalState NewState);

/* PVD configuration functions ************************************************/
void PWR_PVDLevelConfig(uint32_t PWR_PVDLevel);
void PWR_PVDCmd(FunctionalState NewState);

/* WakeUp pins configuration functions ****************************************/
void PWR_WakeUpPinCmd(uint32_t PWR_WakeUpPin, FunctionalState NewState);

/* Low Power modes configuration functions ************************************/
void PWR_EnterSleepMode(uint8_t PWR_SLEEPEntry);
void PWR_EnterSTOPMode(uint32_t PWR_Regulator, uint8_t PWR_STOPEntry);
void PWR_EnterSTANDBYMode(void);

/* Flags management functions *************************************************/
FlagStatus PWR_GetFlagStatus(uint32_t PWR_FLAG);
void PWR_ClearFlag(uint32_t PWR_FLAG);

//////////////////////////////////////////////////////////////////////////////
// EXTI
/**
 * @brief  EXTI mode enumeration
 */

typedef enum {
    EXTI_Mode_Interrupt = 0x00,
    EXTI_Mode_Event     = 0x04
} EXTIMode_TypeDef;

#define IS_EXTI_MODE(MODE) (((MODE) == EXTI_Mode_Interrupt) || ((MODE) == EXTI_Mode_Event))

/**
 * @brief  EXTI Trigger enumeration
 */

typedef enum {
    EXTI_Trigger_Rising         = 0x08,
    EXTI_Trigger_Falling        = 0x0C,
    EXTI_Trigger_Rising_Falling = 0x10
} EXTITrigger_TypeDef;

#define IS_EXTI_TRIGGER(TRIGGER) (((TRIGGER) == EXTI_Trigger_Rising) ||  \
                                  ((TRIGGER) == EXTI_Trigger_Falling) || \
                                  ((TRIGGER) == EXTI_Trigger_Rising_Falling))
/**
 * @brief  EXTI Init Structure definition
 */

typedef struct
{
    uint32_t EXTI_Line; /*!< Specifies the EXTI lines to be enabled or disabled.
                             This parameter can be any combination of @ref EXTI_Lines */

    EXTIMode_TypeDef EXTI_Mode; /*!< Specifies the mode for the EXTI lines.
                                     This parameter can be a value of @ref EXTIMode_TypeDef */

    EXTITrigger_TypeDef EXTI_Trigger; /*!< Specifies the trigger signal active edge for the EXTI lines.
                                           This parameter can be a value of @ref EXTIMode_TypeDef */

    FunctionalState EXTI_LineCmd; /*!< Specifies the new state of the selected EXTI lines.
                                       This parameter can be set either to ENABLE or DISABLE */
} EXTI_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup EXTI_Exported_Constants
 * @{
 */
/** @defgroup EXTI_Lines
 * @{
 */

#define EXTI_Line0             ((uint32_t)0x00000001) /*!< External interrupt line 0  */
#define EXTI_Line1             ((uint32_t)0x00000002) /*!< External interrupt line 1  */
#define EXTI_Line2             ((uint32_t)0x00000004) /*!< External interrupt line 2  */
#define EXTI_Line3             ((uint32_t)0x00000008) /*!< External interrupt line 3  */
#define EXTI_Line4             ((uint32_t)0x00000010) /*!< External interrupt line 4  */
#define EXTI_Line5             ((uint32_t)0x00000020) /*!< External interrupt line 5  */
#define EXTI_Line6             ((uint32_t)0x00000040) /*!< External interrupt line 6  */
#define EXTI_Line7             ((uint32_t)0x00000080) /*!< External interrupt line 7  */
#define EXTI_Line8             ((uint32_t)0x00000100) /*!< External interrupt line 8  */
#define EXTI_Line9             ((uint32_t)0x00000200) /*!< External interrupt line 9  */
#define EXTI_Line10            ((uint32_t)0x00000400) /*!< External interrupt line 10 */
#define EXTI_Line11            ((uint32_t)0x00000800) /*!< External interrupt line 11 */
#define EXTI_Line12            ((uint32_t)0x00001000) /*!< External interrupt line 12 */
#define EXTI_Line13            ((uint32_t)0x00002000) /*!< External interrupt line 13 */
#define EXTI_Line14            ((uint32_t)0x00004000) /*!< External interrupt line 14 */
#define EXTI_Line15            ((uint32_t)0x00008000) /*!< External interrupt line 15 */
#define EXTI_Line16            ((uint32_t)0x00010000) /*!< External interrupt line 16 \
                                                           Connected to the PVD Output */
#define EXTI_Line17            ((uint32_t)0x00020000) /*!< Internal interrupt line 17 \
                                                           Connected to the RTC Alarm \
                                                           event */
#define EXTI_Line19            ((uint32_t)0x00080000) /*!< Internal interrupt line 19  \
                                                           Connected to the RTC Tamper \
                                                           and Time Stamp events */
#define EXTI_Line21            ((uint32_t)0x00200000) /*!< Internal interrupt line 21    \
                                                           Connected to the Comparator 1 \
                                                           event */
#define EXTI_Line22            ((uint32_t)0x00400000) /*!< Internal interrupt line 22    \
                                                           Connected to the Comparator 2 \
                                                           event */
#define EXTI_Line23            ((uint32_t)0x00800000) /*!< Internal interrupt line 23   \
                                                           Connected to the I2C1 wakeup \
                                                           event */
#define EXTI_Line25            ((uint32_t)0x02000000) /*!< Internal interrupt line 25     \
                                                           Connected to the USART1 wakeup \
                                                           event */
#define EXTI_Line27            ((uint32_t)0x08000000) /*!< Internal interrupt line 27  \
                                                           Connected to the CEC wakeup \
                                                           event */

#define IS_EXTI_LINE(LINE)     ((((LINE) & (uint32_t)0xF5140000) == 0x00) && ((LINE) != (uint16_t)0x00))

#define IS_GET_EXTI_LINE(LINE) (((LINE) == EXTI_Line0) || ((LINE) == EXTI_Line1) ||   \
                                ((LINE) == EXTI_Line2) || ((LINE) == EXTI_Line3) ||   \
                                ((LINE) == EXTI_Line4) || ((LINE) == EXTI_Line5) ||   \
                                ((LINE) == EXTI_Line6) || ((LINE) == EXTI_Line7) ||   \
                                ((LINE) == EXTI_Line8) || ((LINE) == EXTI_Line9) ||   \
                                ((LINE) == EXTI_Line10) || ((LINE) == EXTI_Line11) || \
                                ((LINE) == EXTI_Line12) || ((LINE) == EXTI_Line13) || \
                                ((LINE) == EXTI_Line14) || ((LINE) == EXTI_Line15) || \
                                ((LINE) == EXTI_Line16) || ((LINE) == EXTI_Line17) || \
                                ((LINE) == EXTI_Line19) || ((LINE) == EXTI_Line21) || \
                                ((LINE) == EXTI_Line22))

/**
 * @}
 */

/**
 * @}
 */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/* Function used to set the EXTI configuration to the default reset state *****/
void EXTI_DeInit(void);

/* Initialization and Configuration functions *********************************/
void EXTI_Init(EXTI_InitTypeDef* EXTI_InitStruct);
void EXTI_StructInit(EXTI_InitTypeDef* EXTI_InitStruct);
void EXTI_GenerateSWInterrupt(uint32_t EXTI_Line);

/* Interrupts and flags management functions **********************************/
FlagStatus EXTI_GetFlagStatus(uint32_t EXTI_Line);
void EXTI_ClearFlag(uint32_t EXTI_Line);
ITStatus EXTI_GetITStatus(uint32_t EXTI_Line);
void EXTI_ClearITPendingBit(uint32_t EXTI_Line);

//////////////////////////////////////////////////////////////////////////////
// RCC
static __I uint8_t APBAHBPrescTable[16] = {0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9};

#define RCC_AHBPeriph_GPIOA   RCC_AHBENR_GPIOAEN
#define RCC_AHBPeriph_GPIOB   RCC_AHBENR_GPIOBEN
#define RCC_AHBPeriph_GPIOC   RCC_AHBENR_GPIOCEN
#define RCC_AHBPeriph_GPIOD   RCC_AHBENR_GPIODEN
#define RCC_AHBPeriph_GPIOF   RCC_AHBENR_GPIOFEN
#define RCC_AHBPeriph_TS      RCC_AHBENR_TSEN
#define RCC_AHBPeriph_CRC     RCC_AHBENR_CRCEN
#define RCC_AHBPeriph_FLITF   RCC_AHBENR_FLITFEN
#define RCC_AHBPeriph_SRAM    RCC_AHBENR_SRAMEN
#define RCC_AHBPeriph_DMA1    RCC_AHBENR_DMA1EN

#define RCC_APB2Periph_SYSCFG RCC_APB2ENR_SYSCFGEN
#define RCC_APB2Periph_ADC1   RCC_APB2ENR_ADC1EN
#define RCC_APB2Periph_TIM1   RCC_APB2ENR_TIM1EN
#define RCC_APB2Periph_SPI1   RCC_APB2ENR_SPI1EN
#define RCC_APB2Periph_USART1 RCC_APB2ENR_USART1EN
#define RCC_APB2Periph_TIM15  RCC_APB2ENR_TIM15EN
#define RCC_APB2Periph_TIM16  RCC_APB2ENR_TIM16EN
#define RCC_APB2Periph_TIM17  RCC_APB2ENR_TIM17EN
#define RCC_APB2Periph_DBGMCU RCC_APB2ENR_DBGMCUEN

#define RCC_APB1Periph_TIM2   RCC_APB1ENR_TIM2EN
#define RCC_APB1Periph_TIM3   RCC_APB1ENR_TIM3EN
#define RCC_APB1Periph_TIM6   RCC_APB1ENR_TIM6EN
#define RCC_APB1Periph_TIM14  RCC_APB1ENR_TIM14EN
#define RCC_APB1Periph_WWDG   RCC_APB1ENR_WWDGEN
#define RCC_APB1Periph_SPI2   RCC_APB1ENR_SPI2EN
#define RCC_APB1Periph_USART2 RCC_APB1ENR_USART2EN
#define RCC_APB1Periph_I2C1   RCC_APB1ENR_I2C1EN
#define RCC_APB1Periph_I2C2   RCC_APB1ENR_I2C2EN
#define RCC_APB1Periph_PWR    RCC_APB1ENR_PWREN
#define RCC_APB1Periph_DAC    RCC_APB1ENR_DACEN
#define RCC_APB1Periph_CEC    RCC_APB1ENR_CECEN

#define HSI_VALUE             ((uint32_t)8000000)
#define HSE_VALUE             ((uint32_t)8000000)
#define LSE_VALUE             ((uint32_t)32768)

#define RCC_CFGR_PLLMULL      ((uint32_t)0x003C0000) /*!< PLLMUL[3:0] bits (PLL multiplication factor) */
// #define  RCC_CFGR_PLLSRC                     ((uint32_t)0x00010000)        /*!< PLL entry clock source */

/*******************  Bit definition for RCC_CFGR2 register  ******************/
/*!< PREDIV1 configuration */
#define RCC_CFGR2_PREDIV1     ((uint32_t)0x0000000F) /*!< PREDIV1[3:0] bits */
#define RCC_CFGR2_PREDIV1_0   ((uint32_t)0x00000001) /*!< Bit 0 */
#define RCC_CFGR2_PREDIV1_1   ((uint32_t)0x00000002) /*!< Bit 1 */
#define RCC_CFGR2_PREDIV1_2   ((uint32_t)0x00000004) /*!< Bit 2 */
#define RCC_CFGR2_PREDIV1_3   ((uint32_t)0x00000008) /*!< Bit 3 */

/*******************  Bit definition for RCC_CFGR3 register  ******************/
/*!< USART1 Clock source selection */
// #define  RCC_CFGR3_USART1SW                  ((uint32_t)0x00000003)        /*!< USART1SW[1:0] bits */
// #define  RCC_CFGR3_USART1SW_0                ((uint32_t)0x00000001)        /*!< Bit 0 */
// #define  RCC_CFGR3_USART1SW_1                ((uint32_t)0x00000002)        /*!< Bit 1 */
/*!< I2C1 Clock source selection */
// #define  RCC_CFGR3_I2C1SW                    ((uint32_t)0x00000010)        /*!< I2C1SW bits */
// #define  RCC_CFGR3_CECSW                     ((uint32_t)0x00000040)        /*!< CECSW bits */
#define RCC_CFGR3_ADCSW       ((uint32_t)0x00000100) /*!< ADCSW bits */

#define HSI14_VALUE           ((uint32_t)14000000) /*!< Value of the Internal High Speed oscillator for ADC in Hz. \
                                                       The real value may vary depending on the variations         \
                                                       in voltage and temperature.  */

typedef struct
{
    uint32_t SYSCLK_Frequency;
    uint32_t HCLK_Frequency;
    uint32_t PCLK_Frequency;
    uint32_t ADCCLK_Frequency;
    uint32_t CECCLK_Frequency;
    uint32_t I2C1CLK_Frequency;
    uint32_t USART1CLK_Frequency;
} RCC_ClocksTypeDef;

/**
 * @brief  Forces or releases AHB peripheral reset.
 * @param  RCC_AHBPeriph: specifies the AHB peripheral to reset.
 *         This parameter can be any combination of the following values:
 *             @arg RCC_AHBPeriph_GPIOA:         GPIOA clock
 *             @arg RCC_AHBPeriph_GPIOB:         GPIOB clock
 *             @arg RCC_AHBPeriph_GPIOC:         GPIOC clock
 *             @arg RCC_AHBPeriph_GPIOD:         GPIOD clock
 *             @arg RCC_AHBPeriph_GPIOF:         GPIOF clock
 *             @arg RCC_AHBPeriph_TS:            TS clock
 * @param  NewState: new state of the specified peripheral reset.
 *         This parameter can be: ENABLE or DISABLE.
 * @retval None
 */
void RCC_AHBPeriphResetCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState)
{
    if (NewState != DISABLE) {
        RCC->AHBRSTR |= RCC_AHBPeriph;
    } else {
        RCC->AHBRSTR &= ~RCC_AHBPeriph;
    }
}

/**
 * @brief  Forces or releases High Speed APB (APB2) peripheral reset.
 * @param  RCC_APB2Periph: specifies the APB2 peripheral to reset.
 *         This parameter can be any combination of the following values:
 *             @arg RCC_APB2Periph_SYSCFG:      SYSCFG clock
 *             @arg RCC_APB2Periph_ADC1:        ADC1 clock
 *             @arg RCC_APB2Periph_TIM1:        TIM1 clock
 *             @arg RCC_APB2Periph_SPI1:        SPI1 clock
 *             @arg RCC_APB2Periph_USART1:      USART1 clock
 *             @arg RCC_APB2Periph_TIM15:       TIM15 clock
 *             @arg RCC_APB2Periph_TIM16:       TIM16 clock
 *             @arg RCC_APB2Periph_TIM17:       TIM17 clock
 *             @arg RCC_APB2Periph_DBGMCU:      DBGMCU clock
 * @param  NewState: new state of the specified peripheral reset.
 *         This parameter can be: ENABLE or DISABLE.
 * @retval None
 */
void RCC_APB2PeriphResetCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)
{
    if (NewState != DISABLE) {
        RCC->APB2RSTR |= RCC_APB2Periph;
    } else {
        RCC->APB2RSTR &= ~RCC_APB2Periph;
    }
}

/**
 * @brief  Forces or releases Low Speed APB (APB1) peripheral reset.
 * @param  RCC_APB1Periph: specifies the APB1 peripheral to reset.
 *         This parameter can be any combination of the following values:
 *           @arg RCC_APB1Periph_TIM2:      TIM2 clock
 *           @arg RCC_APB1Periph_TIM3:      TIM3 clock
 *           @arg RCC_APB1Periph_TIM6:      TIM6 clock
 *           @arg RCC_APB1Periph_TIM14:     TIM14 clock
 *           @arg RCC_APB1Periph_WWDG:      WWDG clock
 *           @arg RCC_APB1Periph_SPI2:      SPI2 clock
 *           @arg RCC_APB1Periph_USART2:    USART2 clock
 *           @arg RCC_APB1Periph_I2C1:      I2C1 clock
 *           @arg RCC_APB1Periph_I2C2:      I2C2 clock
 *           @arg RCC_APB1Periph_PWR:       PWR clock
 *           @arg RCC_APB1Periph_DAC:       DAC clock
 *           @arg RCC_APB1Periph_CEC:       CEC clock
 * @param  NewState: new state of the specified peripheral clock.
 *         This parameter can be: ENABLE or DISABLE.
 * @retval None
 */
void RCC_APB1PeriphResetCmd(uint32_t RCC_APB1Periph, FunctionalState NewState)
{
    if (NewState != DISABLE) {
        RCC->APB1RSTR |= RCC_APB1Periph;
    } else {
        RCC->APB1RSTR &= ~RCC_APB1Periph;
    }
}

/**
 * @brief  Enables or disables the AHB peripheral clock.
 * @note   After reset, the peripheral clock (used for registers read/write access)
 *         is disabled and the application software has to enable this clock before
 *         using it.
 * @param  RCC_AHBPeriph: specifies the AHB peripheral to gates its clock.
 *         This parameter can be any combination of the following values:
 *             @arg RCC_AHBPeriph_GPIOA:         GPIOA clock
 *             @arg RCC_AHBPeriph_GPIOB:         GPIOB clock
 *             @arg RCC_AHBPeriph_GPIOC:         GPIOC clock
 *             @arg RCC_AHBPeriph_GPIOD:         GPIOD clock
 *             @arg RCC_AHBPeriph_GPIOF:         GPIOF clock
 *             @arg RCC_AHBPeriph_TS:            TS clock
 *             @arg RCC_AHBPeriph_CRC:           CRC clock
 *             @arg RCC_AHBPeriph_FLITF: (has effect only when the Flash memory is in power down mode)
 *             @arg RCC_AHBPeriph_SRAM:          SRAM clock
 *             @arg RCC_AHBPeriph_DMA1:          DMA1 clock
 * @param  NewState: new state of the specified peripheral clock.
 *         This parameter can be: ENABLE or DISABLE.
 * @retval None
 */
void RCC_AHBPeriphClockCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState)
{
    if (NewState != DISABLE) {
        RCC->AHBENR |= RCC_AHBPeriph;
    } else {
        RCC->AHBENR &= ~RCC_AHBPeriph;
    }
}

void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)
{
    if (NewState != DISABLE) {
        RCC->APB2ENR |= RCC_APB2Periph;
    } else {
        RCC->APB2ENR &= ~RCC_APB2Periph;
    }
}

/**
 * @brief  Enables or disables the Low Speed APB (APB1) peripheral clock.
 * @note   After reset, the peripheral clock (used for registers read/write access)
 *         is disabled and the application software has to enable this clock before
 *         using it.
 * @param  RCC_APB1Periph: specifies the APB1 peripheral to gates its clock.
 *         This parameter can be any combination of the following values:
 *           @arg RCC_APB1Periph_TIM2:      TIM2 clock
 *           @arg RCC_APB1Periph_TIM3:      TIM3 clock
 *           @arg RCC_APB1Periph_TIM6:      TIM6 clock
 *           @arg RCC_APB1Periph_TIM14:     TIM14 clock
 *           @arg RCC_APB1Periph_WWDG:      WWDG clock
 *           @arg RCC_APB1Periph_SPI2:      SPI2 clock
 *           @arg RCC_APB1Periph_USART2:    USART2 clock
 *           @arg RCC_APB1Periph_I2C1:      I2C1 clock
 *           @arg RCC_APB1Periph_I2C2:      I2C2 clock
 *           @arg RCC_APB1Periph_PWR:       PWR clock
 *           @arg RCC_APB1Periph_DAC:       DAC clock
 *           @arg RCC_APB1Periph_CEC:       CEC clock
 * @param  NewState: new state of the specified peripheral clock.
 *         This parameter can be: ENABLE or DISABLE.
 * @retval None
 */
void RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState)
{
    if (NewState != DISABLE) {
        RCC->APB1ENR |= RCC_APB1Periph;
    } else {
        RCC->APB1ENR &= ~RCC_APB1Periph;
    }
}

/**
 * @brief  Returns the frequencies of the System, AHB and APB busses clocks.
 * @note    The frequency returned by this function is not the real frequency
 *           in the chip. It is calculated based on the predefined constant and
 *           the source selected by RCC_SYSCLKConfig():
 *
 * @note     If SYSCLK source is HSI, function returns constant HSI_VALUE(*)
 *
 * @note     If SYSCLK source is HSE, function returns constant HSE_VALUE(**)
 *
 * @note     If SYSCLK source is PLL, function returns constant HSE_VALUE(**)
 *             or HSI_VALUE(*) multiplied by the PLL factors.
 *
 *         (*) HSI_VALUE is a constant defined in stm32f0xx.h file (default value
 *             8 MHz) but the real value may vary depending on the variations
 *             in voltage and temperature, refer to RCC_AdjustHSICalibrationValue().
 *
 *         (**) HSE_VALUE is a constant defined in stm32f0xx.h file (default value
 *              8 MHz), user has to ensure that HSE_VALUE is same as the real
 *              frequency of the crystal used. Otherwise, this function may
 *              return wrong result.
 *
 *         - The result of this function could be not correct when using fractional
 *           value for HSE crystal.
 *
 * @param  RCC_Clocks: pointer to a RCC_ClocksTypeDef structure which will hold
 *         the clocks frequencies.
 *
 * @note     This function can be used by the user application to compute the
 *           baudrate for the communication peripherals or configure other parameters.
 * @note     Each time SYSCLK, HCLK and/or PCLK clock changes, this function
 *           must be called to update the structure's field. Otherwise, any
 *           configuration based on this function will be incorrect.
 *
 * @retval None
 */
void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks)
{
    uint32_t tmp = 0, pllmull = 0, pllsource = 0, prediv1factor = 0, presc = 0;

    /* Get SYSCLK source -------------------------------------------------------*/
    tmp = RCC->CFGR & RCC_CFGR_SWS;

    switch (tmp) {
        case 0x00: /* HSI used as system clock */
            RCC_Clocks->SYSCLK_Frequency = HSI_VALUE;
            break;
        case 0x04: /* HSE used as system clock */
            RCC_Clocks->SYSCLK_Frequency = HSE_VALUE;
            break;
        case 0x08: /* PLL used as system clock */
            /* Get PLL clock source and multiplication factor ----------------------*/
            pllmull   = RCC->CFGR & RCC_CFGR_PLLMULL;
            pllsource = RCC->CFGR & RCC_CFGR_PLLSRC;
            pllmull   = (pllmull >> 18) + 2;

            if (pllsource == 0x00) {
                /* HSI oscillator clock divided by 2 selected as PLL clock entry */
                RCC_Clocks->SYSCLK_Frequency = (HSI_VALUE >> 1) * pllmull;
            } else {
                prediv1factor                = (RCC->CFGR2 & RCC_CFGR2_PREDIV1) + 1;
                /* HSE oscillator clock selected as PREDIV1 clock entry */
                RCC_Clocks->SYSCLK_Frequency = (HSE_VALUE / prediv1factor) * pllmull;
            }
            break;
        default: /* HSI used as system clock */
            RCC_Clocks->SYSCLK_Frequency = HSI_VALUE;
            break;
    }
    /* Compute HCLK, PCLK clocks frequencies -----------------------------------*/
    /* Get HCLK prescaler */
    tmp                        = RCC->CFGR & RCC_CFGR_HPRE;
    tmp                        = tmp >> 4;
    presc                      = APBAHBPrescTable[tmp];
    /* HCLK clock frequency */
    RCC_Clocks->HCLK_Frequency = RCC_Clocks->SYSCLK_Frequency >> presc;

    /* Get PCLK prescaler */
    tmp                        = RCC->CFGR & RCC_CFGR_PPRE;
    tmp                        = tmp >> 8;
    presc                      = APBAHBPrescTable[tmp];
    /* PCLK clock frequency */
    RCC_Clocks->PCLK_Frequency = RCC_Clocks->HCLK_Frequency >> presc;

    /* ADCCLK clock frequency */
    if ((RCC->CFGR3 & RCC_CFGR3_ADCSW) != RCC_CFGR3_ADCSW) {
        /* ADC Clock is HSI14 Osc. */
        RCC_Clocks->ADCCLK_Frequency = HSI14_VALUE;
    } else {
        if ((RCC->CFGR & RCC_CFGR_ADCPRE) != RCC_CFGR_ADCPRE) {
            /* ADC Clock is derived from PCLK/2 */
            RCC_Clocks->ADCCLK_Frequency = RCC_Clocks->PCLK_Frequency >> 1;
        } else {
            /* ADC Clock is derived from PCLK/4 */
            RCC_Clocks->ADCCLK_Frequency = RCC_Clocks->PCLK_Frequency >> 2;
        }
    }

    /* CECCLK clock frequency */
    if ((RCC->CFGR3 & RCC_CFGR3_CECSW) != RCC_CFGR3_CECSW) {
        /* CEC Clock is HSI/256 */
        RCC_Clocks->CECCLK_Frequency = HSI_VALUE / 244;
    } else {
        /* CECC Clock is LSE Osc. */
        RCC_Clocks->CECCLK_Frequency = LSE_VALUE;
    }

    /* I2C1CLK clock frequency */
    if ((RCC->CFGR3 & RCC_CFGR3_I2C1SW) != RCC_CFGR3_I2C1SW) {
        /* I2C1 Clock is HSI Osc. */
        RCC_Clocks->I2C1CLK_Frequency = HSI_VALUE;
    } else {
        /* I2C1 Clock is System Clock */
        RCC_Clocks->I2C1CLK_Frequency = RCC_Clocks->SYSCLK_Frequency;
    }

    /* USART1CLK clock frequency */
    if ((RCC->CFGR3 & RCC_CFGR3_USART1SW) == 0x0) {
        /* USART1 Clock is PCLK */
        RCC_Clocks->USART1CLK_Frequency = RCC_Clocks->PCLK_Frequency;
    } else if ((RCC->CFGR3 & RCC_CFGR3_USART1SW) == RCC_CFGR3_USART1SW_0) {
        /* USART1 Clock is System Clock */
        RCC_Clocks->USART1CLK_Frequency = RCC_Clocks->SYSCLK_Frequency;
    } else if ((RCC->CFGR3 & RCC_CFGR3_USART1SW) == RCC_CFGR3_USART1SW_1) {
        /* USART1 Clock is LSE Osc. */
        RCC_Clocks->USART1CLK_Frequency = LSE_VALUE;
    } else if ((RCC->CFGR3 & RCC_CFGR3_USART1SW) == RCC_CFGR3_USART1SW) {
        /* USART1 Clock is HSI Osc. */
        RCC_Clocks->USART1CLK_Frequency = HSI_VALUE;
    }
}

#define CR_DS_MASK  ((uint32_t)0xFFFFFFFC)
#define CR_PLS_MASK ((uint32_t)0xFFFFFF1F)
/**
 * @brief  Enters STOP mode.
 * @note   In Stop mode, all I/O pins keep the same state as in Run mode.
 * @note   When exiting Stop mode by issuing an interrupt or a wakeup event,
 *         the HSI RC oscillator is selected as system clock.
 * @note   When the voltage regulator operates in low power mode, an additional
 *         startup delay is incurred when waking up from Stop mode.
 *         By keeping the internal regulator ON during Stop mode, the consumption
 *         is higher although the startup time is reduced.
 * @param  PWR_Regulator: specifies the regulator state in STOP mode.
 *         This parameter can be one of the following values:
 *             @arg PWR_Regulator_ON: STOP mode with regulator ON
 *             @arg PWR_Regulator_LowPower: STOP mode with regulator in low power mode
 * @param  PWR_STOPEntry: specifies if STOP mode in entered with WFI or WFE instruction.
 *         This parameter can be one of the following values:
 *             @arg PWR_STOPEntry_WFI: enter STOP mode with WFI instruction
 *             @arg PWR_STOPEntry_WFE: enter STOP mode with WFE instruction
 * @retval None
 */
void PWR_EnterSTOPMode(uint32_t PWR_Regulator, uint8_t PWR_STOPEntry)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */

    /* Select the regulator state in STOP mode ---------------------------------*/
    tmpreg = PWR->CR;
    /* Clear PDDS and LPDSR bits */
    tmpreg &= CR_DS_MASK;

    /* Set LPDSR bit according to PWR_Regulator value */
    tmpreg |= PWR_Regulator;

    /* Store the new value */
    PWR->CR = tmpreg;

    /* Set SLEEPDEEP bit of Cortex-M0 System Control Register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    /* Select STOP mode entry --------------------------------------------------*/
    if (PWR_STOPEntry == PWR_STOPEntry_WFI) {
        /* Request Wait For Interrupt */
        __WFI();
    } else {
        /* Request Wait For Event */
        __WFE();
    }
    /* Reset SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR &= (uint32_t) ~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
}

/**
 * @brief  Enters Sleep mode.
 * @note   In Sleep mode, all I/O pins keep the same state as in Run mode.
 * @param  PWR_SLEEPEntry: specifies if SLEEP mode in entered with WFI or WFE instruction.
 *         This parameter can be one of the following values:
 *             @arg PWR_SLEEPEntry_WFI: enter SLEEP mode with WFI instruction
 *             @arg PWR_SLEEPEntry_WFE: enter SLEEP mode with WFE instruction
 * @retval None
 */
void PWR_EnterSleepMode(uint8_t PWR_SLEEPEntry)
{
    /* Clear SLEEPDEEP bit of Cortex-M0 System Control Register */
    SCB->SCR &= (uint32_t) ~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);

    /* Select SLEEP mode entry -------------------------------------------------*/
    if (PWR_SLEEPEntry == PWR_SLEEPEntry_WFI) {
        /* Request Wait For Interrupt */
        __WFI();
    } else {
        /* Request Wait For Event */
        __WFE();
    }
}

//////////////////////////////////////////////////////////////////////////////
// GPIO

/** @defgroup Configuration_Mode_enumeration
 * @{
 */
typedef enum {
    GPIO_Mode_IN  = 0x00, /*!< GPIO Input Mode              */
    GPIO_Mode_OUT = 0x01, /*!< GPIO Output Mode             */
    GPIO_Mode_AF  = 0x02, /*!< GPIO Alternate function Mode */
    GPIO_Mode_AN  = 0x03  /*!< GPIO Analog In/Out Mode      */
} GPIOMode_TypeDef;

#define IS_GPIO_MODE(MODE) (((MODE) == GPIO_Mode_IN) || ((MODE) == GPIO_Mode_OUT) || \
                            ((MODE) == GPIO_Mode_AF) || ((MODE) == GPIO_Mode_AN))
/**
 * @}
 */

/** @defgroup Output_type_enumeration
 * @{
 */
typedef enum {
    GPIO_OType_PP = 0x00,
    GPIO_OType_OD = 0x01
} GPIOOType_TypeDef;

#define IS_GPIO_OTYPE(OTYPE) (((OTYPE) == GPIO_OType_PP) || ((OTYPE) == GPIO_OType_OD))

/**
 * @}
 */

/** @defgroup Output_Maximum_frequency_enumeration
 * @{
 */
typedef enum {
    GPIO_Speed_Level_1 = 0x01, /*!< Medium Speed */
    GPIO_Speed_Level_2 = 0x02, /*!< Fast Speed   */
    GPIO_Speed_Level_3 = 0x03  /*!< High Speed   */
} GPIOSpeed_TypeDef;

#define IS_GPIO_SPEED(SPEED) (((SPEED) == GPIO_Speed_Level_1) || ((SPEED) == GPIO_Speed_Level_2) || \
                              ((SPEED) == GPIO_Speed_Level_3))
/**
 * @}
 */

/** @defgroup Configuration_Pull-Up_Pull-Down_enumeration
 * @{
 */
typedef enum {
    GPIO_PuPd_NOPULL = 0x00,
    GPIO_PuPd_UP     = 0x01,
    GPIO_PuPd_DOWN   = 0x02
} GPIOPuPd_TypeDef;

#define IS_GPIO_PUPD(PUPD) (((PUPD) == GPIO_PuPd_NOPULL) || ((PUPD) == GPIO_PuPd_UP) || \
                            ((PUPD) == GPIO_PuPd_DOWN))
/**
 * @}
 */

/** @defgroup Bit_SET_and_Bit_RESET_enumeration
 * @{
 */
typedef enum {
    Bit_RESET = 0,
    Bit_SET
} BitAction;

/**
 * @brief  GPIO Init structure definition
 */
typedef struct
{
    uint32_t GPIO_Pin; /*!< Specifies the GPIO pins to be configured.
                            This parameter can be any value of @ref GPIO_pins_define */

    GPIOMode_TypeDef GPIO_Mode; /*!< Specifies the operating mode for the selected pins.
                                     This parameter can be a value of @ref GPIOMode_TypeDef   */

    GPIOSpeed_TypeDef GPIO_Speed; /*!< Specifies the speed for the selected pins.
                                       This parameter can be a value of @ref GPIOSpeed_TypeDef  */

    GPIOOType_TypeDef GPIO_OType; /*!< Specifies the operating output type for the selected pins.
                                       This parameter can be a value of @ref GPIOOType_TypeDef  */

    GPIOPuPd_TypeDef GPIO_PuPd; /*!< Specifies the operating Pull-up/Pull down for the selected pins.
                                     This parameter can be a value of @ref GPIOPuPd_TypeDef   */
} GPIO_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup GPIO_Exported_Constants
 * @{
 */

/** @defgroup GPIO_pins_define
 * @{
 */
#define GPIO_Pin_0           ((uint16_t)0x0001) /*!< Pin 0 selected    */
#define GPIO_Pin_1           ((uint16_t)0x0002) /*!< Pin 1 selected    */
#define GPIO_Pin_2           ((uint16_t)0x0004) /*!< Pin 2 selected    */
#define GPIO_Pin_3           ((uint16_t)0x0008) /*!< Pin 3 selected    */
#define GPIO_Pin_4           ((uint16_t)0x0010) /*!< Pin 4 selected    */
#define GPIO_Pin_5           ((uint16_t)0x0020) /*!< Pin 5 selected    */
#define GPIO_Pin_6           ((uint16_t)0x0040) /*!< Pin 6 selected    */
#define GPIO_Pin_7           ((uint16_t)0x0080) /*!< Pin 7 selected    */
#define GPIO_Pin_8           ((uint16_t)0x0100) /*!< Pin 8 selected    */
#define GPIO_Pin_9           ((uint16_t)0x0200) /*!< Pin 9 selected    */
#define GPIO_Pin_10          ((uint16_t)0x0400) /*!< Pin 10 selected   */
#define GPIO_Pin_11          ((uint16_t)0x0800) /*!< Pin 11 selected   */
#define GPIO_Pin_12          ((uint16_t)0x1000) /*!< Pin 12 selected   */
#define GPIO_Pin_13          ((uint16_t)0x2000) /*!< Pin 13 selected   */
#define GPIO_Pin_14          ((uint16_t)0x4000) /*!< Pin 14 selected   */
#define GPIO_Pin_15          ((uint16_t)0x8000) /*!< Pin 15 selected   */
#define GPIO_Pin_All         ((uint16_t)0xFFFF) /*!< All pins selected */

#define IS_GPIO_PIN(PIN)     ((PIN) != (uint16_t)0x00)

#define IS_GET_GPIO_PIN(PIN) (((PIN) == GPIO_Pin_0) ||  \
                              ((PIN) == GPIO_Pin_1) ||  \
                              ((PIN) == GPIO_Pin_2) ||  \
                              ((PIN) == GPIO_Pin_3) ||  \
                              ((PIN) == GPIO_Pin_4) ||  \
                              ((PIN) == GPIO_Pin_5) ||  \
                              ((PIN) == GPIO_Pin_6) ||  \
                              ((PIN) == GPIO_Pin_7) ||  \
                              ((PIN) == GPIO_Pin_8) ||  \
                              ((PIN) == GPIO_Pin_9) ||  \
                              ((PIN) == GPIO_Pin_10) || \
                              ((PIN) == GPIO_Pin_11) || \
                              ((PIN) == GPIO_Pin_12) || \
                              ((PIN) == GPIO_Pin_13) || \
                              ((PIN) == GPIO_Pin_14) || \
                              ((PIN) == GPIO_Pin_15))

/**
 * @}
 */

/** @defgroup GPIO_Pin_sources
 * @{
 */
#define GPIO_PinSource0               ((uint8_t)0x00)
#define GPIO_PinSource1               ((uint8_t)0x01)
#define GPIO_PinSource2               ((uint8_t)0x02)
#define GPIO_PinSource3               ((uint8_t)0x03)
#define GPIO_PinSource4               ((uint8_t)0x04)
#define GPIO_PinSource5               ((uint8_t)0x05)
#define GPIO_PinSource6               ((uint8_t)0x06)
#define GPIO_PinSource7               ((uint8_t)0x07)
#define GPIO_PinSource8               ((uint8_t)0x08)
#define GPIO_PinSource9               ((uint8_t)0x09)
#define GPIO_PinSource10              ((uint8_t)0x0A)
#define GPIO_PinSource11              ((uint8_t)0x0B)
#define GPIO_PinSource12              ((uint8_t)0x0C)
#define GPIO_PinSource13              ((uint8_t)0x0D)
#define GPIO_PinSource14              ((uint8_t)0x0E)
#define GPIO_PinSource15              ((uint8_t)0x0F)

#define IS_GPIO_PIN_SOURCE(PINSOURCE) (((PINSOURCE) == GPIO_PinSource0) ||  \
                                       ((PINSOURCE) == GPIO_PinSource1) ||  \
                                       ((PINSOURCE) == GPIO_PinSource2) ||  \
                                       ((PINSOURCE) == GPIO_PinSource3) ||  \
                                       ((PINSOURCE) == GPIO_PinSource4) ||  \
                                       ((PINSOURCE) == GPIO_PinSource5) ||  \
                                       ((PINSOURCE) == GPIO_PinSource6) ||  \
                                       ((PINSOURCE) == GPIO_PinSource7) ||  \
                                       ((PINSOURCE) == GPIO_PinSource8) ||  \
                                       ((PINSOURCE) == GPIO_PinSource9) ||  \
                                       ((PINSOURCE) == GPIO_PinSource10) || \
                                       ((PINSOURCE) == GPIO_PinSource11) || \
                                       ((PINSOURCE) == GPIO_PinSource12) || \
                                       ((PINSOURCE) == GPIO_PinSource13) || \
                                       ((PINSOURCE) == GPIO_PinSource14) || \
                                       ((PINSOURCE) == GPIO_PinSource15))
/**
 * @}
 */

/** @defgroup GPIO_Alternate_function_selection_define
 * @{
 */

/**
 * @brief  AF 0 selection
 */
#define GPIO_AF_0      ((uint8_t)0x00) /* WKUP, EVENTOUT, TIM15, SPI1, TIM17, \
                                          MCO, SWDAT, SWCLK, TIM14, BOOT,     \
                                          USART1, CEC, IR_OUT, SPI2 */
/**
 * @brief  AF 1 selection
 */
#define GPIO_AF_1      ((uint8_t)0x01) /* USART2, CEC, Tim3, USART1, USART2, \
                                          EVENTOUT, I2C1, I2C2, TIM15 */
/**
 * @brief  AF 2 selection
 */
#define GPIO_AF_2      ((uint8_t)0x02) /* TIM2, TIM1, EVENTOUT, TIM16, TIM17 */
/**
 * @brief  AF 3 selection
 */
#define GPIO_AF_3      ((uint8_t)0x03) /* TS, I2C1, TIM15, EVENTOUT */

/**
 * @brief  AF 4 selection
 */
#define GPIO_AF_4      ((uint8_t)0x04) /* TIM14 */
/**
 * @brief  AF 5 selection
 */
#define GPIO_AF_5      ((uint8_t)0x05) /* TIM16, TIM17 */

/**
 * @brief  AF 6 selection
 */
#define GPIO_AF_6      ((uint8_t)0x06) /* EVENTOUT */
/**
 * @brief  AF 7 selection
 */
#define GPIO_AF_7      ((uint8_t)0x07) /* COMP1 OUT and COMP2 OUT */

#define IS_GPIO_AF(AF) (((AF) == GPIO_AF_0) || ((AF) == GPIO_AF_1) || \
                        ((AF) == GPIO_AF_2) || ((AF) == GPIO_AF_3) || \
                        ((AF) == GPIO_AF_4) || ((AF) == GPIO_AF_5) || \
                        ((AF) == GPIO_AF_6) || ((AF) == GPIO_AF_7))

/**
 * @}
 */

/** @defgroup GPIO_Speed_Legacy
 * @{
 */

#define GPIO_Speed_10MHz GPIO_Speed_Level_1 /*!< Fast Speed:10MHz   */
#define GPIO_Speed_2MHz  GPIO_Speed_Level_2 /*!< Medium Speed:2MHz  */
#define GPIO_Speed_50MHz GPIO_Speed_Level_3 /*!< High Speed:50MHz   */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @brief  Deinitializes the GPIOx peripheral registers to their default reset
 *         values.
 * @param  GPIOx: where x can be (A, B, C, D or F) to select the GPIO peripheral.
 * @retval None
 */
void GPIO_DeInit(GPIO_TypeDef* GPIOx)
{
    if (GPIOx == (GPIO_TypeDef*)GPIOA) {
        RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOA, ENABLE);
        RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOA, DISABLE);
    } else if (GPIOx == (GPIO_TypeDef*)GPIOB) {
        RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOB, ENABLE);
        RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOB, DISABLE);
    } else if (GPIOx == (GPIO_TypeDef*)GPIOC) {
        RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOC, ENABLE);
        RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOC, DISABLE);
    } else if (GPIOx == (GPIO_TypeDef*)GPIOD) {
        RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOD, ENABLE);
        RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOD, DISABLE);
    } else {
        if (GPIOx == (GPIO_TypeDef*)GPIOF) {
            RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOF, ENABLE);
            RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOF, DISABLE);
        }
    }
}

/**
 * @brief  Initializes the GPIOx peripheral according to the specified
 *         parameters in the GPIO_InitStruct.
 * @param  GPIOx: where x can be (A, B, C, D or F) to select the GPIO peripheral.
 * @param  GPIO_InitStruct: pointer to a GPIO_InitTypeDef structure that contains
 *         the configuration information for the specified GPIO peripheral.
 * @note   The configured pins can be: GPIO_Pin_0 -> GPIO_Pin_15 for GPIOA, GPIOB and GPIOC,
 *         GPIO_Pin_0 -> GPIO_Pin_2 for GPIOD, GPIO_Pin_0 -> GPIO_Pin_3 for GPIOF.
 * @retval None
 */
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
    uint32_t pinpos = 0x00, pos = 0x00, currentpin = 0x00;

    /*-------------------------- Configure the port pins -----------------------*/
    /*-- GPIO Mode Configuration --*/
    for (pinpos = 0x00; pinpos < 0x10; pinpos++) {
        pos = ((uint32_t)0x01) << pinpos;

        /* Get the port pins position */
        currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;

        if (currentpin == pos) {
            if ((GPIO_InitStruct->GPIO_Mode == GPIO_Mode_OUT) || (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_AF)) {
                /* Speed mode configuration */
                GPIOx->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR0 << (pinpos * 2));
                GPIOx->OSPEEDR |= ((uint32_t)(GPIO_InitStruct->GPIO_Speed) << (pinpos * 2));

                /* Output mode configuration */
                GPIOx->OTYPER &= ~((GPIO_OTYPER_OT_0) << ((uint16_t)pinpos));
                GPIOx->OTYPER |= (uint16_t)(((uint16_t)GPIO_InitStruct->GPIO_OType) << ((uint16_t)pinpos));
            }

            GPIOx->MODER &= ~(GPIO_MODER_MODER0 << (pinpos * 2));

            GPIOx->MODER |= (((uint32_t)GPIO_InitStruct->GPIO_Mode) << (pinpos * 2));

            /* Pull-up Pull down resistor configuration */
            GPIOx->PUPDR &= ~(GPIO_PUPDR_PUPDR0 << ((uint16_t)pinpos * 2));
            GPIOx->PUPDR |= (((uint32_t)GPIO_InitStruct->GPIO_PuPd) << (pinpos * 2));
        }
    }
}

/**
 * @brief  Fills each GPIO_InitStruct member with its default value.
 * @param  GPIO_InitStruct: pointer to a GPIO_InitTypeDef structure which will
 *         be initialized.
 * @retval None
 */
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct)
{
    /* Reset GPIO init structure parameters values */
    GPIO_InitStruct->GPIO_Pin   = GPIO_Pin_All;
    GPIO_InitStruct->GPIO_Mode  = GPIO_Mode_IN;
    GPIO_InitStruct->GPIO_Speed = GPIO_Speed_Level_2;
    GPIO_InitStruct->GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct->GPIO_PuPd  = GPIO_PuPd_NOPULL;
}

/**
 * @brief  Sets the selected data port bits.
 * @param  GPIOx: where x can be (A, B, C, D or F) to select the GPIO peripheral.
 * @param  GPIO_Pin: specifies the port bits to be written.
 * @note   This parameter can be GPIO_Pin_x where x can be:(0..15) for GPIOA,
 *         GPIOB or GPIOC,(0..2) for GPIOD and(0..3) for GPIOF.
 * @retval None
 */
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    GPIOx->BSRR = GPIO_Pin;
}

/**
 * @brief  Clears the selected data port bits.
 * @param  GPIOx: where x can be (A, B, C, D or F) to select the GPIO peripheral.
 * @param  GPIO_Pin: specifies the port bits to be written.
 * @note   This parameter can be GPIO_Pin_x where x can be: (0..15) for GPIOA,
 *         GPIOB or GPIOC,(0..2) for GPIOD and(0..3) for GPIOF.
 * @retval None
 */
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    GPIOx->BRR = GPIO_Pin;
}

/**
 * @brief  Sets or clears the selected data port bit.
 * @param  GPIOx: where x can be (A, B, C, D or F) to select the GPIO peripheral.
 * @param  GPIO_Pin: specifies the port bit to be written.
 * @param  BitVal: specifies the value to be written to the selected bit.
 *   This parameter can be one of the BitAction enumeration values:
 *     @arg Bit_RESET: to clear the port pin
 *     @arg Bit_SET: to set the port pin
 * @note   The GPIO_Pin parameter can be GPIO_Pin_x where x can be: (0..15) for GPIOA,
 *         GPIOB or GPIOC,(0..2) for GPIOD and(0..3) for GPIOF.
 * @retval None
 */
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal)
{
    if (BitVal != Bit_RESET) {
        GPIOx->BSRR = GPIO_Pin;
    } else {
        GPIOx->BRR = GPIO_Pin;
    }
}

/**
 * @brief  Writes data to the specified GPIO data port.
 * @param  GPIOx: where x can be (A or B) to select the GPIO peripheral.
 * @param  GPIO_PinSource: specifies the pin for the Alternate function.
 *   This parameter can be GPIO_PinSourcex where x can be (0..15).
 * @param  GPIO_AF: selects the pin to used as Alternate function.
 *   This parameter can be one of the following value:
 *     @arg GPIO_AF_0:WKUP, EVENTOUT, TIM15, SPI1, TIM17,MCO, SWDAT, SWCLK, TIM14,
 *                    BOOT,USART1, CEC, IR_OUT, SPI2
 *     @arg GPIO_AF_1:USART2, CEC, Tim3, USART1, USART2,EVENTOUT, I2C1, I2C2, TIM15
 *     @arg GPIO_AF_2:TIM2, TIM1, EVENTOUT, TIM16, TIM17.
 *     @arg GPIO_AF_3:TS, I2C1, TIM15, EVENTOUT
 *     @arg GPIO_AF_4:TIM14.
 *     @arg GPIO_AF_5:TIM16, TIM17.
 *     @arg GPIO_AF_6:EVENTOUT.
 *     @arg GPIO_AF_7:COMP1 OUT, COMP2 OUT
 * @note  The pin should already been configured in Alternate Function mode(AF)
 *        using GPIO_InitStruct->GPIO_Mode = GPIO_Mode_AF
 * @note  Refer to the Alternate function mapping table in the device datasheet
 *        for the detailed mapping of the system and peripherals'alternate
 *        function I/O pins.
 * @retval None
 */
void GPIO_PinAFConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_PinSource, uint8_t GPIO_AF)
{
    uint32_t temp   = 0x00;
    uint32_t temp_2 = 0x00;

    temp = ((uint32_t)(GPIO_AF) << ((uint32_t)((uint32_t)GPIO_PinSource & (uint32_t)0x07) * 4));
    GPIOx->AFR[GPIO_PinSource >> 0x03] &= ~((uint32_t)0xF << ((uint32_t)((uint32_t)GPIO_PinSource & (uint32_t)0x07) * 4));
    temp_2                             = GPIOx->AFR[GPIO_PinSource >> 0x03] | temp;
    GPIOx->AFR[GPIO_PinSource >> 0x03] = temp_2;
}

//////////////////////////////////////////////////////////////////////////////
// ????
typedef struct
{
    uint32_t USART_BaudRate; /*!< This member configures the USART communication baud rate.
                                  The baud rate is computed using the following formula:
                                   - IntegerDivider = ((PCLKx) / (16 * (USART_InitStruct->USART_BaudRate)))
                                   - FractionalDivider = ((IntegerDivider - ((u32) IntegerDivider)) * 16) + 0.5 */

    uint16_t USART_WordLength; /*!< Specifies the number of data bits transmitted or received in a frame.
                                    This parameter can be a value of @ref USART_Word_Length */

    uint16_t USART_StopBits; /*!< Specifies the number of stop bits transmitted.
                                  This parameter can be a value of @ref USART_Stop_Bits */

    uint16_t USART_Parity; /*!< Specifies the parity mode.
                                This parameter can be a value of @ref USART_Parity
                                @note When parity is enabled, the computed parity is inserted
                                      at the MSB position of the transmitted data (9th bit when
                                      the word length is set to 9 data bits; 8th bit when the
                                      word length is set to 8 data bits). */

    uint16_t USART_Mode; /*!< Specifies wether the Receive or Transmit mode is enabled or disabled.
                              This parameter can be a value of @ref USART_Mode */

    uint16_t USART_HardwareFlowControl; /*!< Specifies wether the hardware flow control mode is enabled
                                             or disabled.
                                             This parameter can be a value of @ref USART_Hardware_Flow_Control */
} USART_InitTypeDef;

#define USART_WordLength_8b               ((uint32_t)0x00000000)

#define USART_StopBits_1                  ((uint32_t)0x00000000)
#define USART_StopBits_2                  ((uint32_t)USART_CR2_STOP_1)
#define USART_StopBits_1_5                ((uint32_t)USART_CR2_STOP_0 | USART_CR2_STOP_1)

#define USART_Parity_No                   ((uint32_t)0x00000000)
#define USART_Parity_Even                 ((uint32_t)USART_CR1_PCE)
#define USART_Parity_Odd                  ((uint32_t)USART_CR1_PCE | USART_CR1_PS)

#define USART_HardwareFlowControl_None    ((uint32_t)0x00000000)
#define USART_HardwareFlowControl_RTS     ((uint32_t)USART_CR3_RTSE)
#define USART_HardwareFlowControl_CTS     ((uint32_t)USART_CR3_CTSE)
#define USART_HardwareFlowControl_RTS_CTS ((uint32_t)USART_CR3_RTSE | USART_CR3_CTSE)

#define USART_Mode_Rx                     USART_CR1_RE
#define USART_Mode_Tx                     USART_CR1_TE

#define USART_FLAG_REACK                  USART_ISR_REACK
#define USART_FLAG_TEACK                  USART_ISR_TEACK
#define USART_FLAG_WU                     USART_ISR_WUF
#define USART_FLAG_RWU                    USART_ISR_RWU
#define USART_FLAG_SBK                    USART_ISR_SBKF
#define USART_FLAG_CM                     USART_ISR_CMF
#define USART_FLAG_BUSY                   USART_ISR_BUSY
#define USART_FLAG_ABRF                   USART_ISR_ABRF
#define USART_FLAG_ABRE                   USART_ISR_ABRE
#define USART_FLAG_EOB                    USART_ISR_EOBF
#define USART_FLAG_RTO                    USART_ISR_RTOF
#define USART_FLAG_nCTSS                  USART_ISR_CTS
#define USART_FLAG_CTS                    USART_ISR_CTSIF
#define USART_FLAG_LBD                    USART_ISR_LBD
#define USART_FLAG_TXE                    USART_ISR_TXE
#define USART_FLAG_TC                     USART_ISR_TC
#define USART_FLAG_RXNE                   USART_ISR_RXNE
#define USART_FLAG_IDLE                   USART_ISR_IDLE
#define USART_FLAG_ORE                    USART_ISR_ORE
#define USART_FLAG_NE                     USART_ISR_NE
#define USART_FLAG_FE                     USART_ISR_FE
#define USART_FLAG_PE                     USART_ISR_PE

#define USART_IT_WU                       ((uint32_t)0x00140316)
#define USART_IT_CM                       ((uint32_t)0x0011010E)
#define USART_IT_EOB                      ((uint32_t)0x000C011B)
#define USART_IT_RTO                      ((uint32_t)0x000B011A)
#define USART_IT_PE                       ((uint32_t)0x00000108)
#define USART_IT_TXE                      ((uint32_t)0x00070107)
#define USART_IT_TC                       ((uint32_t)0x00060106)
#define USART_IT_RXNE                     ((uint32_t)0x00050105)
#define USART_IT_IDLE                     ((uint32_t)0x00040104)
#define USART_IT_LBD                      ((uint32_t)0x00080206)
#define USART_IT_CTS                      ((uint32_t)0x0009030A)
#define USART_IT_ERR                      ((uint32_t)0x00000300)
#define USART_IT_ORE                      ((uint32_t)0x00030300)
#define USART_IT_NE                       ((uint32_t)0x00020300)
#define USART_IT_FE                       ((uint32_t)0x00010300)

/*!< USART CR1 register clear Mask ((~(uint32_t)0xFFFFE6F3)) */
#define CR1_CLEAR_MASK                    ((uint32_t)(USART_CR1_M | USART_CR1_PCE | \
                                   USART_CR1_PS | USART_CR1_TE |                    \
                                   USART_CR1_RE))

/*!< USART CR2 register clock bits clear Mask ((~(uint32_t)0xFFFFF0FF)) */
#define CR2_CLOCK_CLEAR_MASK ((uint32_t)(USART_CR2_CLKEN | USART_CR2_CPOL | \
                                         USART_CR2_CPHA | USART_CR2_LBCL))

/*!< USART CR3 register clear Mask ((~(uint32_t)0xFFFFFCFF)) */
#define CR3_CLEAR_MASK ((uint32_t)(USART_CR3_RTSE | USART_CR3_CTSE))

/*!< USART Interrupts mask */
#define IT_MASK        ((uint32_t)0x000000FF)

/**
 * @brief  Initializes the USARTx peripheral according to the specified
 *   parameters in the USART_InitStruct .
 * @param  USARTx: where x can be 1 or 2 to select the USART peripheral.
 * @param  USART_InitStruct: pointer to a USART_InitTypeDef structure
 *   that contains the configuration information for the specified USART peripheral.
 * @retval None
 */
void USART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct)
{
    uint32_t tmpreg = 0, apbclock = 0;
    uint32_t integerdivider    = 0;
    uint32_t fractionaldivider = 0;
    RCC_ClocksTypeDef RCC_ClocksStatus;

    /* Disable USART */
    USARTx->CR1 &= (uint32_t) ~((uint32_t)USART_CR1_UE);

    /*---------------------------- USART CR2 Configuration -----------------------*/
    tmpreg = USARTx->CR2;
    /* Clear STOP[13:12] bits */
    tmpreg &= (uint32_t) ~((uint32_t)USART_CR2_STOP);

    /* Configure the USART Stop Bits, Clock, CPOL, CPHA and LastBit ------------*/
    /* Set STOP[13:12] bits according to USART_StopBits value */
    tmpreg |= (uint32_t)USART_InitStruct->USART_StopBits;

    /* Write to USART CR2 */
    USARTx->CR2 = tmpreg;

    /*---------------------------- USART CR1 Configuration -----------------------*/
    tmpreg = USARTx->CR1;
    /* Clear M, PCE, PS, TE and RE bits */
    tmpreg &= (uint32_t) ~((uint32_t)CR1_CLEAR_MASK);

    /* Configure the USART Word Length, Parity and mode ----------------------- */
    /* Set the M bits according to USART_WordLength value */
    /* Set PCE and PS bits according to USART_Parity value */
    /* Set TE and RE bits according to USART_Mode value */
    tmpreg |= (uint32_t)USART_InitStruct->USART_WordLength | USART_InitStruct->USART_Parity |
              USART_InitStruct->USART_Mode;

    /* Write to USART CR1 */
    USARTx->CR1 = tmpreg;

    /*---------------------------- USART CR3 Configuration -----------------------*/
    tmpreg = USARTx->CR3;
    /* Clear CTSE and RTSE bits */
    tmpreg &= (uint32_t) ~((uint32_t)CR3_CLEAR_MASK);

    /* Configure the USART HFC -------------------------------------------------*/
    /* Set CTSE and RTSE bits according to USART_HardwareFlowControl value */
    tmpreg |= USART_InitStruct->USART_HardwareFlowControl;

    /* Write to USART CR3 */
    USARTx->CR3 = tmpreg;

    /*---------------------------- USART BRR Configuration -----------------------*/
    /* Configure the USART Baud Rate -------------------------------------------*/
    RCC_GetClocksFreq(&RCC_ClocksStatus);

    if (USARTx == USART1) {
        apbclock = RCC_ClocksStatus.USART1CLK_Frequency;
    } else {
        apbclock = RCC_ClocksStatus.PCLK_Frequency;
    }
    /* Determine the integer part */
    if ((USARTx->CR1 & USART_CR1_OVER8) != 0) {
        /* Integer part computing in case Oversampling mode is 8 Samples */
        integerdivider = ((25 * apbclock) / (2 * (USART_InitStruct->USART_BaudRate)));
    } else /* if ((USARTx->CR1 & CR1_OVER8_Set) == 0) */
    {
        /* Integer part computing in case Oversampling mode is 16 Samples */
        integerdivider = ((25 * apbclock) / (4 * (USART_InitStruct->USART_BaudRate)));
    }
    tmpreg = (integerdivider / 100) << 4;

    /* Determine the fractional part */
    fractionaldivider = integerdivider - (100 * (tmpreg >> 4));

    /* Implement the fractional part in the register */
    if ((USARTx->CR1 & USART_CR1_OVER8) != 0) {
        tmpreg |= ((((fractionaldivider * 8) + 50) / 100)) & ((uint8_t)0x07);
    } else /* if ((USARTx->CR1 & CR1_OVER8_Set) == 0) */
    {
        tmpreg |= ((((fractionaldivider * 16) + 50) / 100)) & ((uint8_t)0x0F);
    }

    /* Write to USART BRR */
    USARTx->BRR = (uint16_t)tmpreg;
}

/**
 * @brief  Enables or disables the specified USART peripheral.
 * @param  USARTx: where x can be 1 or 2 to select the USART peripheral.
 * @param  NewState: new state of the USARTx peripheral.
 *   This parameter can be: ENABLE or DISABLE.
 * @retval None
 */
void USART_Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
    if (NewState != DISABLE) {
        /* Enable the selected USART by setting the UE bit in the CR1 register */
        USARTx->CR1 |= USART_CR1_UE;
    } else {
        /* Disable the selected USART by clearing the UE bit in the CR1 register */
        USARTx->CR1 &= (uint32_t) ~((uint32_t)USART_CR1_UE);
    }
}

/**
 * @brief  Checks whether the specified USART flag is set or not.
 * @param  USARTx: where x can be 1 or 2 to select the USART peripheral.
 * @param  USART_FLAG: specifies the flag to check.
 *   This parameter can be one of the following values:
 *     @arg USART_FLAG_REACK:  Receive Enable acknowledge flag.
 *     @arg USART_FLAG_TEACK:  Transmit Enable acknowledge flag.
 *     @arg USART_FLAG_WUF:  Wake up flag.
 *     @arg USART_FLAG_RWU:  Receive Wake up flag.
 *     @arg USART_FLAG_SBK:  Send Break flag.
 *     @arg USART_FLAG_CMF:  Character match flag.
 *     @arg USART_FLAG_BUSY:  Busy flag.
 *     @arg USART_FLAG_ABRF:  Auto baud rate flag.
 *     @arg USART_FLAG_ABRE:  Auto baud rate error flag.
 *     @arg USART_FLAG_EOBF:  End of block flag.
 *     @arg USART_FLAG_RTOF:  Receive time out flag.
 *     @arg USART_FLAG_nCTSS:  Inverted nCTS input bit status.
 *     @arg USART_FLAG_CTS:  CTS Change flag.
 *     @arg USART_FLAG_LBD:  LIN Break detection flag.
 *     @arg USART_FLAG_TXE:  Transmit data register empty flag.
 *     @arg USART_FLAG_TC:  Transmission Complete flag.
 *     @arg USART_FLAG_RXNE:  Receive data register not empty flag.
 *     @arg USART_FLAG_IDLE:  Idle Line detection flag.
 *     @arg USART_FLAG_ORE:  OverRun Error flag.
 *     @arg USART_FLAG_NE:  Noise Error flag.
 *     @arg USART_FLAG_FE:  Framing Error flag.
 *     @arg USART_FLAG_PE:  Parity Error flag.
 * @retval The new state of USART_FLAG (SET or RESET).
 */
ST_FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, uint32_t USART_FLAG)
{
    ST_FlagStatus bitstatus = ST_RESET;

    if ((USARTx->ISR & USART_FLAG) != (uint16_t)ST_RESET) {
        bitstatus = ST_SET;
    } else {
        bitstatus = ST_RESET;
    }
    return bitstatus;
}

/**
 * @brief  Clears the USARTx's pending flags.
 * @param  USARTx: where x can be 1 or 2 to select the USART peripheral.
 * @param  USART_FLAG: specifies the flag to clear.
 *   This parameter can be any combination of the following values:
 *     @arg USART_FLAG_WUF:  Wake up flag.
 *     @arg USART_FLAG_CMF:  Character match flag.
 *     @arg USART_FLAG_EOBF:  End of block flag.
 *     @arg USART_FLAG_RTOF:  Receive time out flag.
 *     @arg USART_FLAG_CTS:  CTS Change flag.
 *     @arg USART_FLAG_LBD:  LIN Break detection flag.
 *     @arg USART_FLAG_TC:  Transmission Complete flag.
 *     @arg USART_FLAG_IDLE:  IDLE line detected flag.
 *     @arg USART_FLAG_ORE:  OverRun Error flag.
 *     @arg USART_FLAG_NE: Noise Error flag.
 *     @arg USART_FLAG_FE: Framing Error flag.
 *     @arg USART_FLAG_PE:   Parity Errorflag.
 *
 * @note     RXNE pending bit is cleared by a read to the USART_RDR register
 *           (USART_ReceiveData()) or by writing 1 to the RXFRQ in the register
 *           USART_RQR (USART_RequestCmd()).
 * @note     TC flag can be also cleared by software sequence: a read operation
 *           to USART_SR register (USART_GetFlagStatus()) followed by a write
 *           operation to USART_TDR register (USART_SendData()).
 * @note     TXE flag is cleared by a write to the USART_TDR register (USART_SendData())
 *           or by writing 1 to the TXFRQ in the register USART_RQR (USART_RequestCmd()).
 * @note     SBKF flag is cleared by 1 to the SBKRQ in the register USART_RQR
 *           (USART_RequestCmd()).
 * @retval None
 */
void USART_ClearFlag(USART_TypeDef* USARTx, uint32_t USART_FLAG)
{
    USARTx->ICR = USART_FLAG;
}

/**
 * @brief  Enables or disables the specified USART interrupts.
 * @param  USARTx: where x can be 1 or 2 to select the USART peripheral.
 * @param  USART_IT: specifies the USART interrupt sources to be enabled or disabled.
 *   This parameter can be one of the following values:
 *     @arg USART_IT_WU:  Wake up interrupt.
 *     @arg USART_IT_CM:  Character match interrupt.
 *     @arg USART_IT_EOB:  End of block interrupt.
 *     @arg USART_IT_RTO:  Receive time out interrupt.
 *     @arg USART_IT_CTS:  CTS change interrupt.
 *     @arg USART_IT_LBD:  LIN Break detection interrupt.
 *     @arg USART_IT_TXE:  Tansmit Data Register empty interrupt.
 *     @arg USART_IT_TC:  Transmission complete interrupt.
 *     @arg USART_IT_RXNE:  Receive Data register not empty interrupt.
 *     @arg USART_IT_IDLE:  Idle line detection interrupt.
 *     @arg USART_IT_PE:  Parity Error interrupt.
 *     @arg USART_IT_ERR:  Error interrupt(Frame error, noise error, overrun error)
 * @param  NewState: new state of the specified USARTx interrupts.
 *   This parameter can be: ENABLE or DISABLE.
 * @retval None
 */
void USART_ITConfig(USART_TypeDef* USARTx, uint32_t USART_IT, FunctionalState NewState)
{
    uint32_t usartreg = 0, itpos = 0, itmask = 0;
    uint32_t usartxbase = 0;

    usartxbase = (uint32_t)USARTx;

    /* Get the USART register index */
    usartreg = (((uint16_t)USART_IT) >> 0x08);

    /* Get the interrupt position */
    itpos  = USART_IT & IT_MASK;
    itmask = (((uint32_t)0x01) << itpos);

    if (usartreg == 0x02) /* The IT is in CR2 register */
    {
        usartxbase += 0x04;
    } else if (usartreg == 0x03) /* The IT is in CR3 register */
    {
        usartxbase += 0x08;
    } else /* The IT is in CR1 register */
    {
    }
    if (NewState != DISABLE) {
        *(__IO uint32_t*)usartxbase |= itmask;
    } else {
        *(__IO uint32_t*)usartxbase &= ~itmask;
    }
}

/**
 * @brief  Returns the most recent received data by the USARTx peripheral.
 * @param  USARTx: where x can be 1 or 2 to select the USART peripheral.
 * @retval The received data.
 */
uint16_t USART_ReceiveData(USART_TypeDef* USARTx)
{
    /* Receive Data */
    return (uint16_t)(USARTx->RDR & (uint16_t)0x01FF);
}

//////////////////////////////////////////////////////////////////////////////
// NVIC

typedef struct
{
    uint8_t NVIC_IRQChannel; /*!< Specifies the IRQ channel to be enabled or disabled.
                                  This parameter can be a value of @ref IRQn_Type
                                  (For the complete STM32 Devices IRQ Channels list,
                                  please refer to stm32f0xx.h file) */

    uint8_t NVIC_IRQChannelPriority; /*!< Specifies the priority level for the IRQ channel specified
                                          in NVIC_IRQChannel. This parameter can be a value
                                          between 0 and 3.  */

    FunctionalState NVIC_IRQChannelCmd; /*!< Specifies whether the IRQ channel defined in NVIC_IRQChannel
                                             will be enabled or disabled.
                                             This parameter can be set either to ENABLE or DISABLE */
} NVIC_InitTypeDef;

/**
 * @brief  Initializes the NVIC peripheral according to the specified
 *         parameters in the NVIC_InitStruct.
 * @note   To configure interrupts priority correctly, the NVIC_PriorityGroupConfig()
 *         function should be called before.
 * @param  NVIC_InitStruct: pointer to a NVIC_InitTypeDef structure that contains
 *         the configuration information for the specified NVIC peripheral.
 * @retval None
 */
void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct)
{
    uint32_t tmppriority = 0x00;

    if (NVIC_InitStruct->NVIC_IRQChannelCmd != DISABLE) {
        /* Compute the Corresponding IRQ Priority --------------------------------*/
        tmppriority = NVIC->IP[NVIC_InitStruct->NVIC_IRQChannel >> 0x02];
        tmppriority &= (uint32_t)(~(((uint32_t)0xFF) << ((NVIC_InitStruct->NVIC_IRQChannel & 0x03) * 8)));
        tmppriority |= (uint32_t)((((uint32_t)NVIC_InitStruct->NVIC_IRQChannelPriority << 6) & 0xFF) << ((NVIC_InitStruct->NVIC_IRQChannel & 0x03) * 8));

        NVIC->IP[NVIC_InitStruct->NVIC_IRQChannel >> 0x02] = tmppriority;

        /* Enable the Selected IRQ Channels --------------------------------------*/
        NVIC->ISER[0] = (uint32_t)0x01 << (NVIC_InitStruct->NVIC_IRQChannel & (uint8_t)0x1F);
    } else {
        /* Disable the Selected IRQ Channels -------------------------------------*/
        NVIC->ICER[0] = (uint32_t)0x01 << (NVIC_InitStruct->NVIC_IRQChannel & (uint8_t)0x1F);
    }
}

//////////////////////////////////////////////////////////////////////////////
// TIMER

#define TIM_PSCReloadMode_Update       ((uint16_t)0x0000)
#define TIM_PSCReloadMode_Immediate    ((uint16_t)0x0001)

#define TIM_FLAG_Update                ((uint16_t)0x0001)
#define TIM_FLAG_CC1                   ((uint16_t)0x0002)
#define TIM_FLAG_CC2                   ((uint16_t)0x0004)
#define TIM_FLAG_CC3                   ((uint16_t)0x0008)
#define TIM_FLAG_CC4                   ((uint16_t)0x0010)
#define TIM_FLAG_COM                   ((uint16_t)0x0020)
#define TIM_FLAG_Trigger               ((uint16_t)0x0040)
#define TIM_FLAG_Break                 ((uint16_t)0x0080)
#define TIM_FLAG_CC1OF                 ((uint16_t)0x0200)
#define TIM_FLAG_CC2OF                 ((uint16_t)0x0400)
#define TIM_FLAG_CC3OF                 ((uint16_t)0x0800)
#define TIM_FLAG_CC4OF                 ((uint16_t)0x1000)

#define TIM_CounterMode_Up             ((uint16_t)0x0000)
#define TIM_CounterMode_Down           ((uint16_t)0x0010)
#define TIM_CounterMode_CenterAligned1 ((uint16_t)0x0020)
#define TIM_CounterMode_CenterAligned2 ((uint16_t)0x0040)
#define TIM_CounterMode_CenterAligned3 ((uint16_t)0x0060)

#define TIM_IT_Update                  ((uint16_t)0x0001)
#define TIM_IT_CC1                     ((uint16_t)0x0002)
#define TIM_IT_CC2                     ((uint16_t)0x0004)
#define TIM_IT_CC3                     ((uint16_t)0x0008)
#define TIM_IT_CC4                     ((uint16_t)0x0010)
#define TIM_IT_COM                     ((uint16_t)0x0020)
#define TIM_IT_Trigger                 ((uint16_t)0x0040)
#define TIM_IT_Break                   ((uint16_t)0x0080)

typedef struct
{
    uint16_t TIM_Prescaler; /*!< Specifies the prescaler value used to divide the TIM clock.
                                 This parameter can be a number between 0x0000 and 0xFFFF */

    uint16_t TIM_CounterMode; /*!< Specifies the counter mode.
                                   This parameter can be a value of @ref TIM_Counter_Mode */

    uint32_t TIM_Period; /*!< Specifies the period value to be loaded into the active
                              Auto-Reload Register at the next update event.
                              This parameter must be a number between 0x0000 and 0xFFFF.  */

    uint16_t TIM_ClockDivision; /*!< Specifies the clock division.
                                    This parameter can be a value of @ref TIM_Clock_Division_CKD */

    uint8_t TIM_RepetitionCounter; /*!< Specifies the repetition counter value. Each time the RCR downcounter
                                        reaches zero, an update event is generated and counting restarts
                                        from the RCR value (N).
                                        This means in PWM mode that (N+1) corresponds to:
                                           - the number of PWM periods in edge-aligned mode
                                           - the number of half PWM period in center-aligned mode
                                        This parameter must be a number between 0x00 and 0xFF.
                                        @note This parameter is valid only for TIM1. */
} TIM_TimeBaseInitTypeDef;

/**
 * @brief  Initializes the TIMx Time Base Unit peripheral according to
 *         the specified parameters in the TIM_TimeBaseInitStruct.
 * @param  TIMx: where x can be 1, 2, 3, 6, 14, 15, 16 and 17 to select the TIM
 *         peripheral.
 * @param  TIM_TimeBaseInitStruct: pointer to a TIM_TimeBaseInitTypeDef
 *         structure that contains the configuration information for
 *         the specified TIM peripheral.
 * @retval None
 */
void TIM_TimeBaseInit(TIM_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct)
{
    uint16_t tmpcr1 = 0;

    tmpcr1 = TIMx->CR1;

    if ((TIMx == TIM1) || (TIMx == TIM2) || (TIMx == TIM3)) {
        /* Select the Counter Mode */
        tmpcr1 &= (uint16_t)(~((uint16_t)(TIM_CR1_DIR | TIM_CR1_CMS)));
        tmpcr1 |= (uint32_t)TIM_TimeBaseInitStruct->TIM_CounterMode;
    }

    if (TIMx != TIM6) {
        /* Set the clock division */
        tmpcr1 &= (uint16_t)(~((uint16_t)TIM_CR1_CKD));
        tmpcr1 |= (uint32_t)TIM_TimeBaseInitStruct->TIM_ClockDivision;
    }

    TIMx->CR1 = tmpcr1;

    /* Set the Autoreload value */
    TIMx->ARR = TIM_TimeBaseInitStruct->TIM_Period;

    /* Set the Prescaler value */
    TIMx->PSC = TIM_TimeBaseInitStruct->TIM_Prescaler;

    if ((TIMx == TIM1) || (TIMx == TIM15) || (TIMx == TIM16) || (TIMx == TIM17)) {
        /* Set the Repetition Counter value */
        TIMx->RCR = TIM_TimeBaseInitStruct->TIM_RepetitionCounter;
    }

    /* Generate an update event to reload the Prescaler and the Repetition counter
       values immediately */
    TIMx->EGR = TIM_PSCReloadMode_Immediate;
}

/**
 * @brief  Enables or disables the specified TIM interrupts.
 * @param  TIMx: where x can be 1, 2, 3, 6, 14, 15, 16 or 17 to select the TIMx peripheral.
 * @param  TIM_IT: specifies the TIM interrupts sources to be enabled or disabled.
 *   This parameter can be any combination of the following values:
 *     @arg TIM_IT_Update: TIM update Interrupt source
 *     @arg TIM_IT_CC1: TIM Capture Compare 1 Interrupt source
 *     @arg TIM_IT_CC2: TIM Capture Compare 2 Interrupt source
 *     @arg TIM_IT_CC3: TIM Capture Compare 3 Interrupt source
 *     @arg TIM_IT_CC4: TIM Capture Compare 4 Interrupt source
 *     @arg TIM_IT_COM: TIM Commutation Interrupt source
 *     @arg TIM_IT_Trigger: TIM Trigger Interrupt source
 *     @arg TIM_IT_Break: TIM Break Interrupt source
 * @note
 *   - TIM6 can only generate an update interrupt.
 *   - TIM15 can have only TIM_IT_Update, TIM_IT_CC1,
 *     TIM_IT_CC2 or TIM_IT_Trigger.
 *   - TIM14, TIM16 and TIM17 can have TIM_IT_Update or TIM_IT_CC1.
 *   - TIM_IT_Break is used only with TIM1 and TIM15.
 *   - TIM_IT_COM is used only with TIM1, TIM15, TIM16 and TIM17.
 * @param  NewState: new state of the TIM interrupts.
 *   This parameter can be: ENABLE or DISABLE.
 * @retval None
 */
void TIM_ITConfig(TIM_TypeDef* TIMx, uint16_t TIM_IT, FunctionalState NewState)
{
    if (NewState != DISABLE) {
        /* Enable the Interrupt sources */
        TIMx->DIER |= TIM_IT;
    } else {
        /* Disable the Interrupt sources */
        TIMx->DIER &= (uint16_t)~TIM_IT;
    }
}

/**
 * @brief  Checks whether the specified TIM flag is set or not.
 * @param  TIMx: where x can be 1, 2, 3, 6, 14, 15, 16 or 17 to select the TIM peripheral.
 * @param  TIM_FLAG: specifies the flag to check.
 *   This parameter can be one of the following values:
 *     @arg TIM_FLAG_Update: TIM update Flag
 *     @arg TIM_FLAG_CC1: TIM Capture Compare 1 Flag
 *     @arg TIM_FLAG_CC2: TIM Capture Compare 2 Flag
 *     @arg TIM_FLAG_CC3: TIM Capture Compare 3 Flag
 *     @arg TIM_FLAG_CC4: TIM Capture Compare 4 Flag
 *     @arg TIM_FLAG_COM: TIM Commutation Flag
 *     @arg TIM_FLAG_Trigger: TIM Trigger Flag
 *     @arg TIM_FLAG_Break: TIM Break Flag
 *     @arg TIM_FLAG_CC1OF: TIM Capture Compare 1 overcapture Flag
 *     @arg TIM_FLAG_CC2OF: TIM Capture Compare 2 overcapture Flag
 *     @arg TIM_FLAG_CC3OF: TIM Capture Compare 3 overcapture Flag
 *     @arg TIM_FLAG_CC4OF: TIM Capture Compare 4 overcapture Flag
 * @note
 *   - TIM6 can have only one update flag.
 *   - TIM15 can have only TIM_FLAG_Update, TIM_FLAG_CC1, TIM_FLAG_CC2 or
 *     TIM_FLAG_Trigger.
 *   - TIM14, TIM16 and TIM17 can have TIM_FLAG_Update or TIM_FLAG_CC1.
 *   - TIM_FLAG_Break is used only with TIM1 and TIM15.
 *   - TIM_FLAG_COM is used only with TIM1 TIM15, TIM16 and TIM17.
 * @retval The new state of TIM_FLAG (SET or RESET).
 */
ST_FlagStatus TIM_GetFlagStatus(TIM_TypeDef* TIMx, uint16_t TIM_FLAG)
{
    ST_FlagStatus bitstatus = ST_RESET;

    if ((TIMx->SR & TIM_FLAG) != (uint16_t)ST_RESET) {
        bitstatus = ST_SET;
    } else {
        bitstatus = ST_RESET;
    }
    return bitstatus;
}

/**
 * @brief  Clears the TIMx's pending flags.
 * @param  TIMx: where x can be 1, 2, 3, 6, 14, 15, 16 or 17 to select the TIM peripheral.
 * @param  TIM_FLAG: specifies the flag bit to clear.
 *   This parameter can be any combination of the following values:
 *     @arg TIM_FLAG_Update: TIM update Flag
 *     @arg TIM_FLAG_CC1: TIM Capture Compare 1 Flag
 *     @arg TIM_FLAG_CC2: TIM Capture Compare 2 Flag
 *     @arg TIM_FLAG_CC3: TIM Capture Compare 3 Flag
 *     @arg TIM_FLAG_CC4: TIM Capture Compare 4 Flag
 *     @arg TIM_FLAG_COM: TIM Commutation Flag
 *     @arg TIM_FLAG_Trigger: TIM Trigger Flag
 *     @arg TIM_FLAG_Break: TIM Break Flag
 *     @arg TIM_FLAG_CC1OF: TIM Capture Compare 1 overcapture Flag
 *     @arg TIM_FLAG_CC2OF: TIM Capture Compare 2 overcapture Flag
 *     @arg TIM_FLAG_CC3OF: TIM Capture Compare 3 overcapture Flag
 *     @arg TIM_FLAG_CC4OF: TIM Capture Compare 4 overcapture Flag
 * @note
 *   - TIM6 can have only one update flag.
 *   - TIM15 can have only TIM_FLAG_Update, TIM_FLAG_CC1,TIM_FLAG_CC2 or
 *     TIM_FLAG_Trigger.
 *   - TIM14, TIM16 and TIM17 can have TIM_FLAG_Update or TIM_FLAG_CC1.
 *   - TIM_FLAG_Break is used only with TIM1 and TIM15.
 *   - TIM_FLAG_COM is used only with TIM1, TIM15, TIM16 and TIM17.
 * @retval None
 */
void TIM_ClearFlag(TIM_TypeDef* TIMx, uint16_t TIM_FLAG)
{
    /* Clear the flags */
    TIMx->SR = (uint16_t)~TIM_FLAG;
}

/**
 * @brief  Enables or disables the specified TIM peripheral.
 * @param  TIMx: where x can be 1, 2, 3, 6, 14, 15, 16 and 17to select the TIMx
 *         peripheral.
 * @param  NewState: new state of the TIMx peripheral.
 *         This parameter can be: ENABLE or DISABLE.
 * @retval None
 */
void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState)
{
    if (NewState != DISABLE) {
        /* Enable the TIM Counter */
        TIMx->CR1 |= TIM_CR1_CEN;
    } else {
        /* Disable the TIM Counter */
        TIMx->CR1 &= (uint16_t)(~((uint16_t)TIM_CR1_CEN));
    }
}

