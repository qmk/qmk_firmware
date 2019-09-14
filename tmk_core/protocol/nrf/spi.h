
#pragma once

#include "apidef.h"

#include <stdint.h>
#include <stddef.h>

#ifndef CONFIG_SCK_PIN
#define CONFIG_SCK_PIN 16
#endif

#ifndef CONFIG_MISO_PIN
#define CONFIG_MISO_PIN 15
#endif

#ifndef CONFIG_MOSI_PIN
#define CONFIG_MOSI_PIN 14
#endif

#ifndef CONFIG_SS_PIN
#define CONFIG_SS_PIN 17
#endif

#ifndef CONFIG_SPI_FREQ
#define CONFIG_SPI_FREQ SPI_FREQ_500K
#endif

#ifndef CONFIG_SPI_MODE
#define CONFIG_SPI_MODE 3
#endif

static inline int spim_init()
{
  bmp_api_spim_config_t config = {
    .freq = CONFIG_SPI_FREQ,
    .miso = CONFIG_MISO_PIN,
    .mosi = CONFIG_MOSI_PIN,
    .sck = CONFIG_SCK_PIN,
    .mode = CONFIG_SPI_MODE
  };
  return BMPAPI->spim.init(&config);
}

static inline int spim_start(uint8_t * p_tx_buffer, size_t tx_length,
    uint8_t * p_rx_buffer,
    size_t rx_length, uint8_t cs_pin)
{
  return BMPAPI->spim.start(p_tx_buffer, tx_length, p_rx_buffer,
  rx_length, cs_pin);
};
