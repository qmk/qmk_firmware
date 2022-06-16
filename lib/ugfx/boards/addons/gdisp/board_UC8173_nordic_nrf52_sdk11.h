#ifndef _GDISP_LLD_BOARD_H
#define _GDISP_LLD_BOARD_H

#include "nrf_gpio.h"
#include "nrf_drv_spi.h"
#include "app_util_platform.h"

#define PIN_CS			29
#define PIN_SCK			 3
#define PIN_MOSI		 4
#define PIN_DC			12
#define PIN_RESET		11
#define PIN_BUSY		27

#define SPI_INSTANCE	0

static const nrf_drv_spi_t spi = NRF_DRV_SPI_INSTANCE(SPI_INSTANCE);

static GFXINLINE gBool init_board(GDisplay* g)
{
	nrf_drv_spi_config_t spi_config;
	ret_code_t err = NRF_SUCCESS;

	(void)g;

	// Initialize RESET pin
	nrf_gpio_cfg_output(PIN_RESET);

	// Initialize RESET pin
	nrf_gpio_cfg_output(PIN_DC);
	
	// Initialize BUSY pin
	nrf_gpio_cfg_input(PIN_BUSY, NRF_GPIO_PIN_NOPULL);

	// Initialize RESET pin
	nrf_gpio_cfg_output(PIN_CS);

	// Initialize SPI
	spi_config.sck_pin		= PIN_SCK;
	spi_config.mosi_pin		= PIN_MOSI;
	spi_config.miso_pin		= NRF_DRV_SPI_PIN_NOT_USED;
	spi_config.ss_pin		= NRF_DRV_SPI_PIN_NOT_USED;	// We have to control the CS line ourself for burst writes > 255 bytes
	spi_config.irq_priority	= APP_IRQ_PRIORITY_LOW;
	spi_config.orc			= 0xFF;
	spi_config.frequency	= NRF_DRV_SPI_FREQ_4M;
	spi_config.mode			= NRF_DRV_SPI_MODE_0;
	spi_config.bit_order	= NRF_DRV_SPI_BIT_ORDER_MSB_FIRST;
	err = nrf_drv_spi_init(&spi, &spi_config, 0);
	if (err != NRF_SUCCESS) {
		return gFalse;
	}

	return gTrue;
}

static GFXINLINE void post_init_board(GDisplay* g)
{
	(void)g;
}

static GFXINLINE void setpin_reset(GDisplay *g, gBool state)
{
	(void)g;

	if (state) {
		nrf_gpio_pin_set(PIN_RESET);
	} else {
		nrf_gpio_pin_clear(PIN_RESET);
	}
}

static GFXINLINE gBool getpin_busy(GDisplay* g)
{
	(void)g;
	
	if (nrf_gpio_pin_read(PIN_BUSY) == 1) {
		return gTrue;
	} else {
		return gFalse;
	}
}

static GFXINLINE void acquire_bus(GDisplay* g)
{
	(void)g;

	nrf_gpio_pin_clear(PIN_CS);
}

static GFXINLINE void release_bus(GDisplay* g)
{
	(void)g;

	nrf_gpio_pin_set(PIN_CS);
}

static GFXINLINE void write_cmd(GDisplay* g, gU8 cmd)
{
	(void)g;

	nrf_gpio_pin_clear(PIN_DC);
	nrf_drv_spi_transfer(&spi, &cmd, 1, 0, 0);
}

static GFXINLINE void write_data(GDisplay* g, gU8 data)
{
	(void)g;
	
	nrf_gpio_pin_set(PIN_DC);
	nrf_drv_spi_transfer(&spi, &data, 1, 0, 0);
}

static GFXINLINE void write_data_burst(GDisplay* g, gU8* data, gU8 length)
{
	(void)g;
	
	nrf_gpio_pin_set(PIN_DC);
	nrf_drv_spi_transfer(&spi, data, length, 0, 0);
}

#endif /* _GDISP_LLD_BOARD_H */
