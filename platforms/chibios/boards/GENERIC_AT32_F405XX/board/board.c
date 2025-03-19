/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio
    ChibiOS - Copyright (C) 2023..2024 HorrorTroll
    ChibiOS - Copyright (C) 2023..2024 Zhaqian
    ChibiOS - Copyright (C) 2003..2024 Maxjta

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

#include "hal.h"

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
 * @brief   Type of AT32 GPIO port setup.
 */
typedef struct {
  uint32_t              cfgr;
  uint32_t              omode;
  uint32_t              odrvr;
  uint32_t              pull;
  uint32_t              odt;
  uint32_t              muxl;
  uint32_t              muxh;
  uint32_t              hdrv;
} gpio_setup_t;


/**
 * @brief   Type of AT32 GPIO initialization data.
 */
typedef struct {
#if AT32_HAS_GPIOA || defined(__DOXYGEN__)
  gpio_setup_t          PAData;
#endif
#if AT32_HAS_GPIOB || defined(__DOXYGEN__)
  gpio_setup_t          PBData;
#endif
#if AT32_HAS_GPIOC || defined(__DOXYGEN__)
  gpio_setup_t          PCData;
#endif
#if AT32_HAS_GPIOD || defined(__DOXYGEN__)
  gpio_setup_t          PDData;
#endif
#if AT32_HAS_GPIOF || defined(__DOXYGEN__)
  gpio_setup_t          PFData;
#endif
} gpio_config_t;

/**
 * @brief   STM32 GPIO static initialization data.
 */
static const gpio_config_t gpio_default_config = {
#if AT32_HAS_GPIOA
  {VAL_GPIOA_MODE, VAL_GPIOA_OUTPUT, VAL_GPIOA_ODRVR, VAL_GPIOA_PULL,
   VAL_GPIOA_ODT,   VAL_GPIOA_MUXL,   VAL_GPIOA_MUXH, VAL_GPIOA_HDRV},
#endif
#if AT32_HAS_GPIOB
  {VAL_GPIOB_MODE, VAL_GPIOB_OUTPUT, VAL_GPIOB_ODRVR, VAL_GPIOB_PULL,
   VAL_GPIOB_ODT,   VAL_GPIOB_MUXL,   VAL_GPIOB_MUXH, VAL_GPIOB_HDRV},
#endif
#if AT32_HAS_GPIOC
  {VAL_GPIOC_MODE, VAL_GPIOC_OUTPUT, VAL_GPIOC_ODRVR, VAL_GPIOC_PULL,
   VAL_GPIOC_ODT,   VAL_GPIOC_MUXL,   VAL_GPIOC_MUXH, VAL_GPIOC_HDRV},
#endif
#if AT32_HAS_GPIOD
  {VAL_GPIOD_MODE, VAL_GPIOD_OUTPUT, VAL_GPIOD_ODRVR, VAL_GPIOD_PULL,
   VAL_GPIOD_ODT,   VAL_GPIOD_MUXL,   VAL_GPIOD_MUXH, VAL_GPIOD_HDRV},
#endif
#if AT32_HAS_GPIOF
  {VAL_GPIOF_MODE, VAL_GPIOF_OUTPUT, VAL_GPIOF_ODRVR, VAL_GPIOF_PULL,
   VAL_GPIOF_ODT,   VAL_GPIOF_MUXL,   VAL_GPIOF_MUXH, VAL_GPIOF_HDRV},
#endif
};

/**
 * @brief   PAL setup.
 * @details Digital I/O ports static configuration as defined in @p board.h.
 *          This variable is used by the HAL when initializing the PAL driver.
 */

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/
static void gpio_init_lld(at32_gpio_t *gpiop, const gpio_setup_t *config) {

  gpiop->OMODE  = config->omode;
  gpiop->ODRVR = config->odrvr;
  gpiop->PULL   = config->pull;
  gpiop->ODT     = config->odt;
  gpiop->MUXL    = config->muxl;
  gpiop->MUXH    = config->muxh;
  gpiop->CFGR   = config->cfgr;
  gpiop->HDRV   = config->hdrv;

}

static void at32_gpio_init(void) {

  /* Enabling GPIO-related clocks, the mask comes from the
     registry header file.*/
  crmEnableAHB1(AT32_GPIO_EN_MASK, false);
  crmResetAHB1(AT32_GPIO_EN_MASK);

  /* Initializing all the defined GPIO ports.*/
#if AT32_HAS_GPIOA
  gpio_init_lld(GPIOA, &gpio_default_config.PAData);
#endif
#if AT32_HAS_GPIOB
  gpio_init_lld(GPIOB, &gpio_default_config.PBData);
#endif
#if AT32_HAS_GPIOC
  gpio_init_lld(GPIOC, &gpio_default_config.PCData);
#endif
#if AT32_HAS_GPIOD
  gpio_init_lld(GPIOD, &gpio_default_config.PDData);
#endif
#if AT32_HAS_GPIOF
  gpio_init_lld(GPIOF, &gpio_default_config.PFData);
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
 * @details System clocks are initialized before everything else.
 */
void __early_init(void) {
  at32_clock_init();
  at32_gpio_init();
}

#if HAL_USE_SDC || defined(__DOXYGEN__)
/**
 * @brief   SDC card detection.
 */
bool sdc_lld_is_card_inserted(SDCDriver *sdcp) {
  static bool last_status = false;

  if (blkIsTransferring(sdcp))
    return last_status;
  return last_status = (bool)palReadPad(GPIOA, GPIOA_ARD_A2);
}

/**
 * @brief   SDC card write protection detection.
 */
bool sdc_lld_is_write_protected(SDCDriver *sdcp) {

  (void)sdcp;
  return false;
}
#endif /* HAL_USE_SDC */

/**
 * @brief   Board-specific initialization code.
 * @note    You can add your board-specific code here.
 */
void boardInit(void) {

}
