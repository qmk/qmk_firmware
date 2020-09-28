/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/*
 * This file has been automatically generated using ChibiStudio board
 * generator plugin. Do not edit manually.
 */

#include "hal.h"
#include "stm32_gpio.h"

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/**
 * @brief   Type of STM32 GPIO port setup.
 */
typedef struct {
  uint32_t              moder;
  uint32_t              otyper;
  uint32_t              ospeedr;
  uint32_t              pupdr;
  uint32_t              odr;
  uint32_t              afrl;
  uint32_t              afrh;
} gpio_setup_t;

/**
 * @brief   Type of STM32 GPIO initialization data.
 */
typedef struct {
#if STM32_HAS_GPIOA || defined(__DOXYGEN__)
  gpio_setup_t          PAData;
#endif
#if STM32_HAS_GPIOB || defined(__DOXYGEN__)
  gpio_setup_t          PBData;
#endif
#if STM32_HAS_GPIOC || defined(__DOXYGEN__)
  gpio_setup_t          PCData;
#endif
#if STM32_HAS_GPIOD || defined(__DOXYGEN__)
  gpio_setup_t          PDData;
#endif
#if STM32_HAS_GPIOE || defined(__DOXYGEN__)
  gpio_setup_t          PEData;
#endif
#if STM32_HAS_GPIOF || defined(__DOXYGEN__)
  gpio_setup_t          PFData;
#endif
#if STM32_HAS_GPIOG || defined(__DOXYGEN__)
  gpio_setup_t          PGData;
#endif
#if STM32_HAS_GPIOH || defined(__DOXYGEN__)
  gpio_setup_t          PHData;
#endif
#if STM32_HAS_GPIOI || defined(__DOXYGEN__)
  gpio_setup_t          PIData;
#endif
#if STM32_HAS_GPIOJ || defined(__DOXYGEN__)
  gpio_setup_t          PJData;
#endif
#if STM32_HAS_GPIOK || defined(__DOXYGEN__)
  gpio_setup_t          PKData;
#endif
} gpio_config_t;

/**
 * @brief   STM32 GPIO static initialization data.
 */
static const gpio_config_t gpio_default_config = {
#if STM32_HAS_GPIOA
  {VAL_GPIOA_MODER, VAL_GPIOA_OTYPER, VAL_GPIOA_OSPEEDR, VAL_GPIOA_PUPDR,
   VAL_GPIOA_ODR,   VAL_GPIOA_AFRL,   VAL_GPIOA_AFRH},
#endif
#if STM32_HAS_GPIOB
  {VAL_GPIOB_MODER, VAL_GPIOB_OTYPER, VAL_GPIOB_OSPEEDR, VAL_GPIOB_PUPDR,
   VAL_GPIOB_ODR,   VAL_GPIOB_AFRL,   VAL_GPIOB_AFRH},
#endif
#if STM32_HAS_GPIOC
  {VAL_GPIOC_MODER, VAL_GPIOC_OTYPER, VAL_GPIOC_OSPEEDR, VAL_GPIOC_PUPDR,
   VAL_GPIOC_ODR,   VAL_GPIOC_AFRL,   VAL_GPIOC_AFRH},
#endif
#if STM32_HAS_GPIOD
  {VAL_GPIOD_MODER, VAL_GPIOD_OTYPER, VAL_GPIOD_OSPEEDR, VAL_GPIOD_PUPDR,
   VAL_GPIOD_ODR,   VAL_GPIOD_AFRL,   VAL_GPIOD_AFRH},
#endif
#if STM32_HAS_GPIOE
  {VAL_GPIOE_MODER, VAL_GPIOE_OTYPER, VAL_GPIOE_OSPEEDR, VAL_GPIOE_PUPDR,
   VAL_GPIOE_ODR,   VAL_GPIOE_AFRL,   VAL_GPIOE_AFRH},
#endif
#if STM32_HAS_GPIOF
  {VAL_GPIOF_MODER, VAL_GPIOF_OTYPER, VAL_GPIOF_OSPEEDR, VAL_GPIOF_PUPDR,
   VAL_GPIOF_ODR,   VAL_GPIOF_AFRL,   VAL_GPIOF_AFRH},
#endif
#if STM32_HAS_GPIOG
  {VAL_GPIOG_MODER, VAL_GPIOG_OTYPER, VAL_GPIOG_OSPEEDR, VAL_GPIOG_PUPDR,
   VAL_GPIOG_ODR,   VAL_GPIOG_AFRL,   VAL_GPIOG_AFRH},
#endif
#if STM32_HAS_GPIOH
  {VAL_GPIOH_MODER, VAL_GPIOH_OTYPER, VAL_GPIOH_OSPEEDR, VAL_GPIOH_PUPDR,
   VAL_GPIOH_ODR,   VAL_GPIOH_AFRL,   VAL_GPIOH_AFRH},
#endif
#if STM32_HAS_GPIOI
  {VAL_GPIOI_MODER, VAL_GPIOI_OTYPER, VAL_GPIOI_OSPEEDR, VAL_GPIOI_PUPDR,
   VAL_GPIOI_ODR,   VAL_GPIOI_AFRL,   VAL_GPIOI_AFRH},
#endif
#if STM32_HAS_GPIOJ
  {VAL_GPIOJ_MODER, VAL_GPIOJ_OTYPER, VAL_GPIOJ_OSPEEDR, VAL_GPIOJ_PUPDR,
   VAL_GPIOJ_ODR,   VAL_GPIOJ_AFRL,   VAL_GPIOJ_AFRH},
#endif
#if STM32_HAS_GPIOK
  {VAL_GPIOK_MODER, VAL_GPIOK_OTYPER, VAL_GPIOK_OSPEEDR, VAL_GPIOK_PUPDR,
   VAL_GPIOK_ODR,   VAL_GPIOK_AFRL,   VAL_GPIOK_AFRH}
#endif
};

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

static void gpio_init(stm32_gpio_t *gpiop, const gpio_setup_t *config) {

  gpiop->OTYPER  = config->otyper;
  gpiop->OSPEEDR = config->ospeedr;
  gpiop->PUPDR   = config->pupdr;
  gpiop->ODR     = config->odr;
  gpiop->AFRL    = config->afrl;
  gpiop->AFRH    = config->afrh;
  gpiop->MODER   = config->moder;
}

static void stm32_gpio_init(void) {

  /* Enabling GPIO-related clocks, the mask comes from the
     registry header file.*/
  rccResetAHB1(STM32_GPIO_EN_MASK);
  rccEnableAHB1(STM32_GPIO_EN_MASK, true);

  /* Initializing all the defined GPIO ports.*/
#if STM32_HAS_GPIOA
  gpio_init(GPIOA, &gpio_default_config.PAData);
#endif
#if STM32_HAS_GPIOB
  gpio_init(GPIOB, &gpio_default_config.PBData);
#endif
#if STM32_HAS_GPIOC
  gpio_init(GPIOC, &gpio_default_config.PCData);
#endif
#if STM32_HAS_GPIOD
  gpio_init(GPIOD, &gpio_default_config.PDData);
#endif
#if STM32_HAS_GPIOE
  gpio_init(GPIOE, &gpio_default_config.PEData);
#endif
#if STM32_HAS_GPIOF
  gpio_init(GPIOF, &gpio_default_config.PFData);
#endif
#if STM32_HAS_GPIOG
  gpio_init(GPIOG, &gpio_default_config.PGData);
#endif
#if STM32_HAS_GPIOH
  gpio_init(GPIOH, &gpio_default_config.PHData);
#endif
#if STM32_HAS_GPIOI
  gpio_init(GPIOI, &gpio_default_config.PIData);
#endif
#if STM32_HAS_GPIOJ
  gpio_init(GPIOJ, &gpio_default_config.PJData);
#endif
#if STM32_HAS_GPIOK
  gpio_init(GPIOK, &gpio_default_config.PKData);
#endif
}

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Early initialization code.
 * @details GPIO ports and system clocks are initialized before everything
 *          else.
 */
void __early_init(void) {
  extern void enter_bootloader_mode_if_requested(void);
  enter_bootloader_mode_if_requested();

  stm32_gpio_init();
  stm32_clock_init();
}

#if HAL_USE_SDC || defined(__DOXYGEN__)
/**
 * @brief   SDC card detection.
 */
bool sdc_lld_is_card_inserted(SDCDriver *sdcp) {

  (void)sdcp;
  /* TODO: Fill the implementation.*/
  return true;
}

/**
 * @brief   SDC card write protection detection.
 */
bool sdc_lld_is_write_protected(SDCDriver *sdcp) {

  (void)sdcp;
  /* TODO: Fill the implementation.*/
  return false;
}
#endif /* HAL_USE_SDC */

#if HAL_USE_MMC_SPI || defined(__DOXYGEN__)
/**
 * @brief   MMC_SPI card detection.
 */
bool mmc_lld_is_card_inserted(MMCDriver *mmcp) {

  (void)mmcp;
  /* TODO: Fill the implementation.*/
  return true;
}

/**
 * @brief   MMC_SPI card write protection detection.
 */
bool mmc_lld_is_write_protected(MMCDriver *mmcp) {

  (void)mmcp;
  /* TODO: Fill the implementation.*/
  return false;
}
#endif

/**
 * @brief   Board-specific initialization code.
 * @todo    Add your board-specific code, if any.
 */
void boardInit(void) {

}
