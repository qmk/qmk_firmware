// Copyright 2020 Nick Brassel (tzarc)
// Copyright 2022 Stefan Kerkmann (KarlK90)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "spi_master.h"

#include "timer.h"

// TODO HANDLE KINETIS CASE
// TODO static SPIConfig spi_config = {.end_cb = NULL, 0, 0, 0};

static SPIConfig spi_config = {false, NULL, 0, 0, 0, 0};

static pin_t current_slave_pin = NO_PIN;

__attribute__((weak)) void spi_init(void) {
    static bool is_initialised = false;
    if (!is_initialised) {
        is_initialised = true;

        // Try releasing special pins for a short time
        setPinInput(SPI_SCK_PIN);
        setPinInput(SPI_MOSI_PIN);
        setPinInput(SPI_MISO_PIN);

        chThdSleepMilliseconds(10);

        // TODO REFACTOR THIS?!
#if defined(USE_GPIOV1)
        palSetPadMode(PAL_PORT(SPI_SCK_PIN), PAL_PAD(SPI_SCK_PIN), SPI_SCK_PAL_MODE);
        palSetPadMode(PAL_PORT(SPI_MOSI_PIN), PAL_PAD(SPI_MOSI_PIN), SPI_MOSI_PAL_MODE);
        palSetPadMode(PAL_PORT(SPI_MISO_PIN), PAL_PAD(SPI_MISO_PIN), SPI_MISO_PAL_MODE);
#else
        palSetPadMode(PAL_PORT(SPI_SCK_PIN), PAL_PAD(SPI_SCK_PIN), PAL_MODE_ALTERNATE(SPI_SCK_PAL_MODE) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST);
        palSetPadMode(PAL_PORT(SPI_MOSI_PIN), PAL_PAD(SPI_MOSI_PIN), PAL_MODE_ALTERNATE(SPI_MOSI_PAL_MODE) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST);
        palSetPadMode(PAL_PORT(SPI_MISO_PIN), PAL_PAD(SPI_MISO_PIN), PAL_MODE_ALTERNATE(SPI_MISO_PAL_MODE) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST);
#endif
    }
}

int32_t round_clock_divisor(uint16_t clock_divisor) {
    uint16_t rounded_divisor = 2;
    while (rounded_divisor < clock_divisor) {
        rounded_divisor <<= 1;
    }

    if (rounded_divisor < 2 || rounded_divisor > 256) {
        return -1;
    }

    return rounded_divisor;
}

bool spi_start(const pin_t slave_pin, const bool lsb_first, const uint8_t spi_mode, const uint16_t clock_divisor) {
    if (current_slave_pin != NO_PIN || slave_pin == NO_PIN) {
        return false;
    }

    if (!spi_start_lld(&spi_config, lsb_first, spi_mode, clock_divisor)) {
        return false;
    }

    current_slave_pin = slave_pin;
    spi_config.ssport = PAL_PORT(slave_pin);
    spi_config.sspad  = PAL_PAD(slave_pin);

    setPinOutput(slave_pin);
    spiStart(&SPI_DRIVER, &spi_config);
    spiSelect(&SPI_DRIVER);

    return true;
}

uint8_t spi_write(uint8_t data) {
    uint8_t rx_data;
    spiExchange(&SPI_DRIVER, 1, &data, &rx_data);

    return rx_data;
}

uint8_t spi_read(void) {
    uint8_t data = 0;
    spiReceive(&SPI_DRIVER, 1, &data);

    return data;
}

spi_status_t spi_transmit(const uint8_t *data, uint16_t length) {
    spiSend(&SPI_DRIVER, length, data);
    return SPI_STATUS_SUCCESS;
}

spi_status_t spi_receive(uint8_t *data, uint16_t length) {
    spiReceive(&SPI_DRIVER, length, data);
    return SPI_STATUS_SUCCESS;
}

void spi_stop(void) {
    if (current_slave_pin != NO_PIN) {
        spiUnselect(&SPI_DRIVER);
        spiStop(&SPI_DRIVER);
        current_slave_pin = NO_PIN;
    }
}
