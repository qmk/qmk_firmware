#include "spi_helper.h"
#include QMK_KEYBOARD_H

void spi_hw_setup(void) {
   /* setPinOutput(SPI_SS_PIN);
    writePinLow(SPI_SS_PIN);

    setPinOutput(SPI_DC_PIN);
    writePinLow(SPI_DC_PIN);

    setPinOutput(SPI_SCK_PIN);
    writePinHigh(SPI_SCK_PIN);

    setPinOutput(SPI_MOSI_PIN);
    writePinHigh(SPI_MOSI_PIN);

    setPinOutput(SPI_MISO_PIN);
    writePinLow(SPI_MISO_PIN);
    setPinOutput(SPI_RST_PIN);
    writePinHigh(SPI_RST_PIN);*/
}

void spi_prepare_commands(void) {
    setPinOutput(SPI_DC_PIN);
    writePinLow(SPI_DC_PIN);
    //wait_us(1);
}

void spi_prepare_data(void) {
    setPinOutput(SPI_DC_PIN);
    writePinHigh(SPI_DC_PIN);
    //wait_us(1);
}

void spi_reset(void) {
    setPinOutput(SPI_RST_PIN);

    //writePinHigh(SPI_RST_PIN);
    //wait_us(2);
    writePinLow(SPI_RST_PIN);
    wait_us(2);
    writePinHigh(SPI_RST_PIN);
    //wait_us(2);
}
