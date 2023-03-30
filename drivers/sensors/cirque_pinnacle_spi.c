// Copyright (c) 2018 Cirque Corp. Restrictions apply. See: www.cirque.com/sw-license
#include "cirque_pinnacle.h"
#include "spi_master.h"

// Masks for Cirque Register Access Protocol (RAP)
#define WRITE_MASK 0x80
#define READ_MASK 0xA0
#define FILLER_BYTE 0xFC

extern bool touchpad_init;

const cirque_rap_t                 cirque_rap_spi           = {.read = &cirque_read_spi, .write = &cirque_write_spi};
const pointing_device_driver_t     cirque_driver_spi_default = {.init = cirque_pinnacle_init_spi, .get_report = cirque_pinnacle_get_report_spi, .set_cpi = cirque_pinnacle_set_scale, .get_cpi = cirque_pinnacle_get_scale};
const pointing_device_spi_config_t cirque_config_spi_default = {.cs = CIRQUE_PINNACLE_SPI_CS_PIN, .mode = CIRQUE_PINNACLE_SPI_MODE, .divisor = CIRQUE_PINNACLE_SPI_DIVISOR};


/*  RAP Functions */
// Reads <count> Pinnacle registers starting at <address>
void cirque_read_spi(const void *config, uint8_t regaddr, uint8_t* data, uint8_t count) {
    uint8_t cmdByte = READ_MASK | regaddr; // Form the READ command byte
    pointing_device_spi_config_t *spi_config = (pointing_device_spi_config_t*)config;
    if (touchpad_init) {
        if (spi_start(spi_config->cs , false, spi_config->mode , spi_config->divisor)) {
            spi_write(cmdByte);     // write command byte, receive filler
            spi_write(FILLER_BYTE); // write & receive filler
            spi_write(FILLER_BYTE); // write & receive filler
            for (uint8_t i = 0; i < count; i++) {
                data[i] = spi_write(FILLER_BYTE); // write filler, receive data on the third filler send
            }
        } else {
            pd_dprintf("error cirque_pinnacle spi_start read\n");
            touchpad_init = false;
        }
        spi_stop();
    }
}

// Writes single-byte <data> to <address>
void cirque_write_spi(const void *config, uint8_t regaddr, uint8_t data) {
    uint8_t cmdByte = WRITE_MASK | regaddr; // Form the WRITE command byte
    pointing_device_spi_config_t *spi_config = (pointing_device_spi_config_t*)config;
    if (touchpad_init) {
        if (spi_start(spi_config->cs, false, spi_config->mode, spi_config->divisor)) {
            spi_write(cmdByte);
            spi_write(data);
        } else {
            pd_dprintf("error cirque_pinnacle spi_start write\n");
            touchpad_init = false;
        }
        spi_stop();
    }
}

void cirque_pinnacle_init_spi(const void *config) {
    cirque_pinnacle_init(&cirque_rap_spi, config);
}
report_mouse_t cirque_pinnacle_get_report_spi(const void *config) {
    return cirque_pinnacle_get_report(&cirque_rap_spi, config);
}
