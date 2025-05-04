#pragma once

#define HAL_USE_SPI TRUE
#define HAL_USE_SPI TRUE // enable ChibiOS SPI driver:contentReference[oaicite:0]{index=0}
#define HAL_USE_DMA TRUE // enable DMA support on RP2040
#define HAL_USE_PAL TRUE // enable GPIO (PAL) if using pin callbacks
#define SPI_USE_WAIT TRUE
#define SPI_SELECT_MODE SPI_SELECT_MODE_PAD

#include_next <halconf.h>