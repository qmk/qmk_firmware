#pragma once

#include_next <mcuconf.h>

#undef RP_SPI_USE_SPI0
#define RP_SPI_USE_SPI0 TRUE
#undef RP_SPI_USE_SPI1
#define RP_SPI_USE_SPI1 FALSE

// Assign DMA channels (use RP_DMA_CHANNEL_ID_ANY for auto-allocation)
#undef RP_SPI_SPI0_RX_DMA_CHANNEL
#define RP_SPI_SPI0_RX_DMA_CHANNEL RP_DMA_CHANNEL_ID_ANY
#undef RP_SPI_SPI0_TX_DMA_CHANNEL
#define RP_SPI_SPI0_TX_DMA_CHANNEL RP_DMA_CHANNEL_ID_ANY
