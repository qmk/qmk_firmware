
#include "pmw3360.h"
#include "spi.h"
#include "apidef.h"

bmp_api_spim_config_t config = {
    .freq = SPI_FREQ_2M,
    .miso = PMW3360_MISO,
    .mosi = PMW3360_MOSI,
    .sck  = PMW3360_SCLK,
    .mode = PMW3360_SPI_MODE
};

bool pmw3360_init(void) {

    BMPAPI->spim.init(&config);

    pmw3360_reg_write(REG_Power_Up_Reset, 0x5a);

    wait_ms(50);

    pmw3360_reg_read(REG_Motion);

    pmw3360_reg_read(REG_Delta_X_L);

    pmw3360_reg_read(REG_Delta_X_H);

    pmw3360_reg_read(REG_Delta_Y_L);

    pmw3360_reg_read(REG_Delta_Y_H);

    pmw3360_reg_write(REG_Config2, 0x00);

    uint8_t pid = pmw3360_reg_read(REG_Product_ID);

    uint8_t rev = pmw3360_reg_read(REG_Revision_ID);

    return pid == 0x42 && rev == 0x01;
}

uint8_t pmw3360_reg_read(uint8_t addr) {
    spi_start();
    uint8_t snd = addr & 0x7f;
    uint8_t rcv = 0x00;
    BMPAPI->spim.start(&snd, 1, NULL, 0, 0xFF);
    wait_us(160);
    BMPAPI->spim.start(NULL, 0, &rcv, 1, 0xFF);
    spi_stop();
    wait_us(20);
    return rcv;
}

void pmw3360_reg_write(uint8_t addr, uint8_t data) {
    spi_start();
    uint8_t snd[] = {addr | 0x80, data};
    BMPAPI->spim.start(snd, sizeof(snd), NULL, 0, 0xFF);
    spi_stop();
    wait_us(180);
}

bool pmw3360_motion_read(pmw3360_motion_t *d) {
    // uint8_t mot = pmw3360_reg_read(REG_Motion);
    // if ((mot & 0x88) != 0x80) {
    //     return false;
    // }
    // d->x  = pmw3360_reg_read(REG_Delta_X_L);
    // d->x |= pmw3360_reg_read(REG_Delta_X_H) << 8;
    // d->y  = pmw3360_reg_read(REG_Delta_Y_L);
    // d->y |= pmw3360_reg_read(REG_Delta_Y_H) << 8;
    return true;
}

bool pmw3360_motion_burst(pmw3360_motion_t *d) {
    spi_start();
    uint8_t snd = REG_Motion_Burst;
    BMPAPI->spim.start(&snd, 1, NULL, 0, 0xFF);
    wait_us(35);

    uint8_t data[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    BMPAPI->spim.start(NULL, 0, data, sizeof(data), 0xFF);

    if ((data[0] & 0x88) != 0x80) {
        spi_stop();
        return false;
    }

    d->x = data[2];
    d->x |= data[3] << 8;

    d->y = data[4];
    d->y |= data[5] << 8;

    spi_stop();
    return true;
}

void spi_start() {
    setPinOutput(PMW3360_NCS_PIN);
    writePinLow(PMW3360_NCS_PIN);
}

void spi_stop() {
    setPinOutput(PMW3360_NCS_PIN);
    writePinHigh(PMW3360_NCS_PIN);
}
