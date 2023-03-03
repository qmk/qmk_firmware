// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "spi_master.h"
#include "touch_driver.h"
#include "wait.h"

WEAK bool touch_spi_init(touch_device_t device) {
    touch_driver_t           *driver      = (touch_driver_t *)device;
    spi_touch_comms_config_t comms_config = driver->spi_config;

    // Initialize the SPI peripheral
    spi_init();

    // Set up CS as output high
    setPinOutput(comms_config.chip_select_pin);
    writePinHigh(comms_config.chip_select_pin);

    // Set up IRQ as input
    setPinInput(comms_config.irq_pin);

    return true;
}

WEAK bool touch_spi_start(spi_touch_comms_config_t comms_config) {
    return spi_start(comms_config.chip_select_pin, comms_config.lsb_first, comms_config.mode, comms_config.divisor);
}

WEAK void touch_spi_stop(spi_touch_comms_config_t comms_config) {
    spi_stop();
    writePinHigh(comms_config.chip_select_pin);
}

static inline void read_data(int16_t *x, int16_t *y, spi_touch_comms_config_t comms_config) {
    spi_write(comms_config.x_cmd);
    *x = ((spi_write(0) << 8) | spi_write(0)) >> 3;

    spi_write(comms_config.y_cmd);
    *y = ((spi_write(0) << 8) | spi_write(0)) >> 3;
}

void report_from(int16_t x, int16_t y, touch_driver_t *driver, touch_report_t *report) {
    ts_dprintf("SPI reading (%d, %d)", x, y);

    // Map to correct range
    x = x * driver->scale_x + driver->offset_x;
    y = y * driver->scale_y + driver->offset_y;
    ts_dprintf("  ||  Scaled (%d, %d)", x, y);

    // Handle edge cases
    x = MIN(MAX(x, 0), driver->width);
    y = MIN(MAX(y, 0), driver->height);
    ts_dprintf("  ||  Edge cases (%d, %d)", x, y);

    // Apply updside-down adjustment
    if (driver->upside_down) {
        report->x = driver->width - x;
        ts_dprintf("  ||  Upside down (%d, %d)", x, y);
    }

    uint16_t _x = x;
    uint16_t _y = y;

    // Apply rotation adjustments
    switch (driver->rotation) {
        case TOUCH_ROTATION_0:
            report->x = _x;
            report->y = _y;
            break;


        case TOUCH_ROTATION_90:
            report->x = driver->height - _y;
            report->y = _x;
            break;

        case TOUCH_ROTATION_180:
            report->x = driver->width  - _x;
            report->y = driver->height - _y;
            break;

        case TOUCH_ROTATION_270:
            report->x = _y;
            report->y = driver->width - _x;
            break;
    }

    ts_dprintf("  >>  Final value (%d, %d)\n", report->x, report->y);
}

WEAK touch_report_t get_spi_touch_report(touch_device_t device, bool check_irq) {
    touch_driver_t           *driver      = (touch_driver_t *)device;
    spi_touch_comms_config_t comms_config = driver->spi_config;

    // Static variable so previous report is stored
    // Goal: When the screen is not pressed anymore, we can see the latest point pressed
    static touch_report_t report = {
        .x = 0,
        .y = 0,
        .pressed = false
    };

    if (check_irq && readPin(comms_config.irq_pin)) {
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
    int16_t x = 0;
    int16_t y = 0;
    read_data(&x, &y, comms_config);

    // Handles edge cases, scaling, offset, upside down & rotation
    report_from(x, y, driver, &report);

    touch_spi_stop(comms_config);

    return report;
}
