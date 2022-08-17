// Copyright 2021 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#ifdef QUANTUM_PAINTER_SPI_ENABLE

#    include "spi_master.h"
#    include "qp_comms_spi.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Base SPI support

bool qp_comms_spi_init(painter_device_t device) {
    struct painter_driver_t *     driver       = (struct painter_driver_t *)device;
    struct qp_comms_spi_config_t *comms_config = (struct qp_comms_spi_config_t *)driver->comms_config;

    // Initialize the SPI peripheral
    spi_init();

    // Set up CS as output high
    setPinOutput(comms_config->chip_select_pin);
    writePinHigh(comms_config->chip_select_pin);

    return true;
}

bool qp_comms_spi_start(painter_device_t device) {
    struct painter_driver_t *     driver       = (struct painter_driver_t *)device;
    struct qp_comms_spi_config_t *comms_config = (struct qp_comms_spi_config_t *)driver->comms_config;

    return spi_start(comms_config->chip_select_pin, comms_config->lsb_first, comms_config->mode, comms_config->divisor);
}

uint32_t qp_comms_spi_send_data(painter_device_t device, const void *data, uint32_t byte_count) {
    uint32_t       bytes_remaining = byte_count;
    const uint8_t *p               = (const uint8_t *)data;
    while (bytes_remaining > 0) {
        uint32_t bytes_this_loop = bytes_remaining < 1024 ? bytes_remaining : 1024;
        spi_transmit(p, bytes_this_loop);
        p += bytes_this_loop;
        bytes_remaining -= bytes_this_loop;
    }

    return byte_count - bytes_remaining;
}

void qp_comms_spi_stop(painter_device_t device) {
    struct painter_driver_t *     driver       = (struct painter_driver_t *)device;
    struct qp_comms_spi_config_t *comms_config = (struct qp_comms_spi_config_t *)driver->comms_config;
    spi_stop();
    writePinHigh(comms_config->chip_select_pin);
}

const struct painter_comms_vtable_t spi_comms_vtable = {
    .comms_init  = qp_comms_spi_init,
    .comms_start = qp_comms_spi_start,
    .comms_send  = qp_comms_spi_send_data,
    .comms_stop  = qp_comms_spi_stop,
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SPI with D/C and RST pins

#    ifdef QUANTUM_PAINTER_SPI_DC_RESET_ENABLE

bool qp_comms_spi_dc_reset_init(painter_device_t device) {
    if (!qp_comms_spi_init(device)) {
        return false;
    }

    struct painter_driver_t *              driver       = (struct painter_driver_t *)device;
    struct qp_comms_spi_dc_reset_config_t *comms_config = (struct qp_comms_spi_dc_reset_config_t *)driver->comms_config;

    // Set up D/C as output low, if specified
    if (comms_config->dc_pin != NO_PIN) {
        setPinOutput(comms_config->dc_pin);
        writePinLow(comms_config->dc_pin);
    }

    // Set up RST as output, if specified, performing a reset in the process
    if (comms_config->reset_pin != NO_PIN) {
        setPinOutput(comms_config->reset_pin);
        writePinLow(comms_config->reset_pin);
        wait_ms(20);
        writePinHigh(comms_config->reset_pin);
        wait_ms(20);
    }

    return true;
}

uint32_t qp_comms_spi_dc_reset_send_data(painter_device_t device, const void *data, uint32_t byte_count) {
    struct painter_driver_t *              driver       = (struct painter_driver_t *)device;
    struct qp_comms_spi_dc_reset_config_t *comms_config = (struct qp_comms_spi_dc_reset_config_t *)driver->comms_config;
    writePinHigh(comms_config->dc_pin);
    return qp_comms_spi_send_data(device, data, byte_count);
}

void qp_comms_spi_dc_reset_send_command(painter_device_t device, uint8_t cmd) {
    struct painter_driver_t *              driver       = (struct painter_driver_t *)device;
    struct qp_comms_spi_dc_reset_config_t *comms_config = (struct qp_comms_spi_dc_reset_config_t *)driver->comms_config;
    writePinLow(comms_config->dc_pin);
    spi_write(cmd);
}

void qp_comms_spi_dc_reset_bulk_command_sequence(painter_device_t device, const uint8_t *sequence, size_t sequence_len) {
    for (size_t i = 0; i < sequence_len;) {
        uint8_t command   = sequence[i];
        uint8_t delay     = sequence[i + 1];
        uint8_t num_bytes = sequence[i + 2];
        qp_comms_spi_dc_reset_send_command(device, command);
        if (num_bytes > 0) {
            qp_comms_spi_dc_reset_send_data(device, &sequence[i + 3], num_bytes);
        }
        if (delay > 0) {
            wait_ms(delay);
        }
        i += (3 + num_bytes);
    }
}

const struct painter_comms_with_command_vtable_t spi_comms_with_dc_vtable = {
    .base =
        {
            .comms_init  = qp_comms_spi_dc_reset_init,
            .comms_start = qp_comms_spi_start,
            .comms_send  = qp_comms_spi_dc_reset_send_data,
            .comms_stop  = qp_comms_spi_stop,
        },
    .send_command          = qp_comms_spi_dc_reset_send_command,
    .bulk_command_sequence = qp_comms_spi_dc_reset_bulk_command_sequence,
};

#    endif // QUANTUM_PAINTER_SPI_DC_RESET_ENABLE

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // QUANTUM_PAINTER_SPI_ENABLE
