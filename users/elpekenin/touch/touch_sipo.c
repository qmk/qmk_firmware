// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "custom_spi_master.h"
#include "sipo_pins.h"
#include "touch_driver.h"
#include "wait.h"

bool touch_spi_init(touch_device_t device) {
    touch_driver_t *          driver       = (touch_driver_t *)device;
    spi_touch_comms_config_t  comms_config = driver->spi_config;

    // Initialize the SPI peripheral
    custom_spi_init(TOUCH_SPI_DRIVER_ID);

    // Set up CS as output high
    sipo_write_high(comms_config.chip_select_pin);

    // Set up IRQ as input
    if (comms_config.irq_pin != NO_PIN) {
        setPinInput(comms_config.irq_pin);
    }

    return true;
}

bool touch_spi_start(spi_touch_comms_config_t comms_config) {
    return custom_spi_start(DUMMY_PIN, comms_config.lsb_first, comms_config.mode, comms_config.divisor, TOUCH_SPI_DRIVER_ID);
}

void touch_spi_stop(spi_touch_comms_config_t comms_config) {
    custom_spi_stop(TOUCH_SPI_DRIVER_ID);
    sipo_write_high(comms_config.chip_select_pin);
}

static inline int16_t read_coord(uint8_t cmd, spi_touch_comms_config_t comms_config) {
    sipo_write_low(comms_config.chip_select_pin);
    custom_spi_write(cmd, TOUCH_SPI_DRIVER_ID);
    sipo_write_high(comms_config.chip_select_pin);

    sipo_write_low(comms_config.chip_select_pin);
    int16_t coord = ((custom_spi_write(0, TOUCH_SPI_DRIVER_ID) << 8) | custom_spi_write(0, TOUCH_SPI_DRIVER_ID)) >> 3;
    sipo_write_high(comms_config.chip_select_pin);

    return coord;
}

touch_report_t get_spi_touch_report(touch_device_t device, bool check_irq) {
    touch_driver_t           *driver      = (touch_driver_t *)device;
    spi_touch_comms_config_t comms_config = driver->spi_config;

    // Static variable so previous report is stored
    // Goal: When the screen is not pressed anymore, we can see the latest point pressed
    static touch_report_t report = {
        .x = 0,
        .y = 0,
        .pressed = false
    };

    if (check_irq && comms_config.irq_pin != NO_PIN && readPin(comms_config.irq_pin)) {
        report.pressed = false;
        return report;
    }

    if (!touch_spi_start(comms_config)) {
        ts_dprintf("Couldn't start touch comms\n");
    }

    report.pressed = true;

    // wait a bit so measurement is less noisy
    wait_ms(20);

    // Read data from sensor, 0-rotation based
    int16_t x = read_coord(driver->spi_config.x_cmd, comms_config);
    int16_t y = read_coord(driver->spi_config.y_cmd, comms_config);

    // Handles edge cases, scaling, offset, upside down & rotation
    report_from(x, y, driver, &report);

    touch_spi_stop(comms_config);

    return report;
}
