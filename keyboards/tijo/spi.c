#include <stdint.h>

#include "hal.h"

#define LEN (255)
uint8_t txbuf[LEN], rxbuf[LEN];

// Configure SPI0 (RP2040_SSI0) as master, e.g. mode 0, 1MHz
const SPIConfig spi_cfg = {
    // On RP2040, only clock rate and polarity/phase matter; other fields are dummy.
    .end_cb = NULL,
    .ssport = 0,
    .sspad  = 0,
};

inline void custom_spi_init(void) {
    spiStart(&SPID0, &spi_cfg);
}
inline void custom_irq_spi_xfer(void) {
    spiSelectI(&SPID0);
    spiStartExchangeI(&SPID0, LEN, txbuf, rxbuf);
    spiUnselectI(&SPID0);
}