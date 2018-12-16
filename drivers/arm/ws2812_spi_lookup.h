#pragma once

#include "hal.h"
#include "quantum.h"

#define RGB_PORT PAL_PORT(RGB_DI_PIN)
#define RGB_PAD PAL_PAD(RGB_DI_PIN)

// static SPIConfig getSPIConfig(void){
//   SPIConfig spicfg = {
//     NULL,
//     RGB_PORT,
//     RGB_PAD,
//     (SPI_CR1_BR_1|SPI_CR1_BR_0) // baudrate : fpclk / 8 => 1tick is 0.32us (2.25 MHz)
//   };

//   #ifdef STM32F103_MCUCONF
//     if(RGB_PORT == GPIOB && RGB_PAD == 15U){
//       spicfg.cr1 = (SPI_CR1_BR_1|SPI_CR1_BR_0);
//       return spicfg;
//     } else if(RGB_PORT == GPIOA && RGB_PAD == 7U) {
//       spicfg.cr1 = (SPI_CR1_BR_2);
//       return spicfg;
//     }
//   #elif STM32F303_MCUCONF
//   #else
//   #endif
//   return spicfg;
// }

