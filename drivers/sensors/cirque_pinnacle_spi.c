// Copyright (c) 2018 Cirque Corp. Restrictions apply. See: www.cirque.com/sw-license
#include "cirque_pinnacle.h"
#include "spi_master.h"
#include "print.h"
#include "debug.h"

// Masks for Cirque Register Access Protocol (RAP)
#define WRITE_MASK 0x80
#define READ_MASK 0xA0

extern bool touchpad_init;

/*  RAP Functions */
// Reads <count> Pinnacle registers starting at <address>
void RAP_ReadBytes(uint8_t address, uint8_t* data, uint8_t count) {
    uint8_t cmdByte = READ_MASK | address;  // Form the READ command byte
    if (touchpad_init) {
        if (spi_start(CIRQUE_PINNACLE_SPI_CS_PIN, CIRQUE_TRACKPAD_SPI_LSBFIRST, CIRQUE_PINNACLE_SPI_MODE, CIRQUE_PINNACLE_SPI_DIVISOR)) {
            spi_write(cmdByte);
            spi_read();  // filler
            spi_read();  // filler
            for (uint8_t i = 0; i < count; i++) {
                data[i] = spi_read();  // each sepsequent read gets another register's contents
            }
        } else {
#ifdef CONSOLE_ENABLE
            dprintf("error right touchpad\n");
#endif
            touchpad_init = false;
            j
        }
        spi_stop();
    }
}

// Writes single-byte <data> to <address>
void RAP_Write(uint8_t address, uint8_t data) {
    uint8_t cmdByte = WRITE_MASK | address;  // Form the WRITE command byte

    if (touchpad_init) {
        if (spi_start(CIRQUE_PINNACLE_SPI_CS_PIN, CIRQUE_TRACKPAD_SPI_LSBFIRST, CIRQUE_PINNACLE_SPI_MODE, CIRQUE_PINNACLE_SPI_DIVISOR)) {
            spi_write(cmdByte);
            spi_write(data);
        } else {
#ifdef CONSOLE_ENABLE
            dprintf("error right touchpad\n");
#endif
            touchpad_init = false;
        }
        spi_stop();
    }
}
