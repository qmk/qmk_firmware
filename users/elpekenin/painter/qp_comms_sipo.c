// Copyright 2021 Nick Brassel (@tzarc)
// Copyright 2023 Pablo Martinez (@elpekenin)
// SPDX-License-Identifier: GPL-2.0-or-later

#ifdef QUANTUM_PAINTER_SPI_ENABLE

#    include "sipo_pins.h"
#    include "qp_comms_spi.h"
#    include "custom_spi_master.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Base SPI support

bool qp_comms_spi_init(painter_device_t device) {
    painter_driver_t *     driver       = (painter_driver_t *)device;
    qp_comms_spi_config_t *comms_config = (qp_comms_spi_config_t *)driver->comms_config;

    // Initialize the SPI peripheral
    custom_spi_init(SCREENS_SPI_DRIVER_ID);

    // Set up CS as output high
    sipo_write_high(comms_config->chip_select_pin);

    return true;
}

bool qp_comms_spi_start(painter_device_t device) {
    painter_driver_t *     driver       = (painter_driver_t *)device;
    qp_comms_spi_config_t *comms_config = (qp_comms_spi_config_t *)driver->comms_config;
    return custom_spi_start(DUMMY_PIN, comms_config->lsb_first, comms_config->mode, comms_config->divisor, SCREENS_SPI_DRIVER_ID);
}

uint32_t qp_comms_spi_send_data(painter_device_t device, const void *data, uint32_t byte_count) {
    uint32_t       bytes_remaining = byte_count;
    const uint8_t *p               = (const uint8_t *)data;
    uint32_t       max_msg_length  = 1024;

    while (bytes_remaining > 0) {
        uint32_t bytes_this_loop = QP_MIN(bytes_remaining, max_msg_length);
        custom_spi_transmit(p, bytes_this_loop, SCREENS_SPI_DRIVER_ID);
        p += bytes_this_loop;
        bytes_remaining -= bytes_this_loop;
    }

    return byte_count - bytes_remaining;
}

void qp_comms_spi_stop(painter_device_t device) {
    painter_driver_t *     driver       = (painter_driver_t *)device;
    qp_comms_spi_config_t *comms_config = (qp_comms_spi_config_t *)driver->comms_config;
    custom_spi_stop(SCREENS_SPI_DRIVER_ID);
    sipo_write_high(comms_config->chip_select_pin);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SPI with D/C and RST pins

#    ifdef QUANTUM_PAINTER_SPI_DC_RESET_ENABLE

bool qp_comms_spi_dc_reset_init(painter_device_t device) {
    if (!qp_comms_spi_init(device)) {
        return false;
    }

    painter_driver_t *              driver       = (painter_driver_t *)device;
    qp_comms_spi_dc_reset_config_t *comms_config = (qp_comms_spi_dc_reset_config_t *)driver->comms_config;

    // Set up D/C as output low, if specified
    sipo_buffer_low(comms_config->dc_pin); // SIPO buffer flushed by next line

    // Use RST as to perform a reset
    sipo_write_low(comms_config->reset_pin);
    wait_ms(20);
    sipo_write_high(comms_config->reset_pin);
    wait_ms(20);

    return true;
}

uint32_t qp_comms_spi_dc_reset_send_data(painter_device_t device, const void *data, uint32_t byte_count) {
    painter_driver_t *              driver       = (painter_driver_t *)device;
    qp_comms_spi_dc_reset_config_t *comms_config = (qp_comms_spi_dc_reset_config_t *)driver->comms_config;

    sipo_buffer_high(comms_config->dc_pin); // SIPO buffer flushed by next line
    sipo_write_low(comms_config->spi_config.chip_select_pin);
    uint32_t ret = qp_comms_spi_send_data(device, data, byte_count);
    sipo_write_high(comms_config->spi_config.chip_select_pin);

    return ret;
}

void qp_comms_spi_dc_reset_send_command(painter_device_t device, uint8_t cmd) {
    painter_driver_t *              driver       = (painter_driver_t *)device;
    qp_comms_spi_dc_reset_config_t *comms_config = (qp_comms_spi_dc_reset_config_t *)driver->comms_config;

    sipo_buffer_low(comms_config->dc_pin); // SIPO buffer flushed by next line
    sipo_write_low(comms_config->spi_config.chip_select_pin);
    custom_spi_write(cmd, SCREENS_SPI_DRIVER_ID);
    sipo_write_high(comms_config->spi_config.chip_select_pin);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SPI with D/C and RST pins but sending one byte at a time, needed for some devices

void qp_comms_spi_dc_reset_single_byte_send_command(painter_device_t device, uint8_t cmd) {
    painter_driver_t *              driver       = (painter_driver_t *)device;
    qp_comms_spi_dc_reset_config_t *comms_config = (qp_comms_spi_dc_reset_config_t *)driver->comms_config;

    sipo_buffer_low(comms_config->dc_pin); // SIPO buffer flushed by next line
    sipo_write_low(comms_config->spi_config.chip_select_pin);
    custom_spi_write(cmd, SCREENS_SPI_DRIVER_ID);
    sipo_write_high(comms_config->spi_config.chip_select_pin);
}

uint32_t qp_comms_spi_dc_reset_single_byte_send_data(painter_device_t device, const void *data, uint32_t byte_count) {
    painter_driver_t *              driver       = (painter_driver_t *)device;
    qp_comms_spi_dc_reset_config_t *comms_config = (qp_comms_spi_dc_reset_config_t *)driver->comms_config;

    uint32_t       bytes_remaining = byte_count;
    const uint8_t *p               = (const uint8_t *)data;
    uint32_t       max_msg_length  = 1;

    sipo_buffer_high(comms_config->dc_pin); // SIPO buffer flushed by next line
    while (bytes_remaining > 0) {
        uint32_t bytes_this_loop = QP_MIN(bytes_remaining, max_msg_length);
        sipo_write_low(comms_config->spi_config.chip_select_pin);
        custom_spi_transmit(p, bytes_this_loop, SCREENS_SPI_DRIVER_ID);
        sipo_write_high(comms_config->spi_config.chip_select_pin);
        p += bytes_this_loop;
        bytes_remaining -= bytes_this_loop;
    }

    return byte_count - bytes_remaining;
}

void qp_comms_spi_dc_reset_single_byte_bulk_command_sequence(painter_device_t device, const uint8_t *sequence, size_t sequence_len) {
    for (size_t i = 0; i < sequence_len;) {
        uint8_t command   = sequence[i];
        uint8_t delay     = sequence[i + 1];
        uint8_t num_bytes = sequence[i + 2];
        qp_comms_spi_dc_reset_single_byte_send_command(device, command);
        if (num_bytes > 0) {
            qp_comms_spi_dc_reset_single_byte_send_data(device, &sequence[i + 3], num_bytes);
        }
        if (delay > 0) {
            wait_ms(delay);
        }
        i += (3 + num_bytes);
    }
}
#    endif // QUANTUM_PAINTER_SPI_DC_RESET_ENABLE
#endif // QUANTUM_PAINTER_SPI_ENABLE
