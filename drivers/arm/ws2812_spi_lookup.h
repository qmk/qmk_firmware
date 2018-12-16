#pragma once

#include "hal.h"
#include "quantum.h"

#define RGB_PORT PAL_PORT(RGB_DI_PIN)
#define RGB_PAD PAL_PAD(RGB_DI_PIN)

void populateSPIConfig(SPIConfig* spicfg){
  spicfg->end_cb = NULL;
  spicfg->ssport = RGB_PORT;
  spicfg->sspad = RGB_PAD;

  #ifdef STM32F103_MCUCONF
    if(RGB_PORT == GPIOB && RGB_PAD == 15U){
      spicfg->cr1 = (SPI_CR1_BR_1|SPI_CR1_BR_0);
    } else if(RGB_PORT == GPIOA && RGB_PAD == 7U) {
      spicfg->cr1 = (SPI_CR1_BR_2);
    }
  #elif STM32F303_MCUCONF
    if(RGB_PORT == GPIOB && RGB_PAD == 15U){
      spicfg->cr1 = (SPI_CR1_BR_1|SPI_CR1_BR_0);
    } else if(RGB_PORT == GPIOA && RGB_PAD == 7U) {
      spicfg->cr1 = (SPI_CR1_BR_2);
    }
  #else
  #endif
}

