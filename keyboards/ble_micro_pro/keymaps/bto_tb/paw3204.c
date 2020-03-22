
#include "paw3204.h"
#include "spi.h"
#include "apidef.h"

#define READ(addr) (addr)
#define WRITE(addr) (0x80 | addr)

#define REG_PID1 0x00
#define REG_PID2 0x01
#define REG_STAT 0x02
#define REG_X 0x03
#define REG_Y 0x04

typedef int (*spi_paw3204_t)(uint8_t *p_tx_buffer, size_t tx_length, uint8_t *p_rx_buffer, size_t rx_length, uint8_t cs_pin);

#ifndef PAW3204_SCLK
#    define PAW3204_SCLK 5
#endif

#ifndef PAW3204_DATA
#    define PAW3204_DATA 6
#endif

#ifndef PAW3204_POWER
#    define PAW3204_POWER 7
#endif

int spi_soft_half_duplex(uint8_t *p_tx_buffer, size_t tx_length, uint8_t *p_rx_buffer, size_t rx_length, uint8_t cs_pin) {
    if (tx_length != 2 || rx_length != 2) {
        p_rx_buffer[1] = 0xFF;
        return 1;
    }

    // clang-format off
    bmp_api_spim_config_t config = {
        .freq = SPI_FREQ_8M,
        .miso = 0xFF,
        .mosi = PAW3204_DATA,
        .sck = PAW3204_SCLK,
        .mode = CONFIG_SPI_MODE
    };
    // clang-format on

    // configure data pin as output mode
    BMPAPI->spim.init(&config);
    BMPAPI->spim.start(p_tx_buffer, 1, p_rx_buffer, 1, cs_pin);

    // configure data pin as input mode
    config.mosi = 0xFF;
    config.miso = PAW3204_DATA;

    BMPAPI->spim.init(&config);
    return BMPAPI->spim.start(p_tx_buffer + 1, 1, p_rx_buffer + 1, 1, cs_pin);
}

// spi_paw3204_t spi_paw3204 = spim_start;
spi_paw3204_t spi_paw3204 = spi_soft_half_duplex;

uint8_t read_pid_paw3204() {
    spim_init();

    uint8_t snd[] = {READ(REG_PID1), 0xFF};
    uint8_t rcv[] = {0xFF, 0xFF};

    spi_paw3204(snd, sizeof(snd), rcv, sizeof(rcv), 0xFF);

    return rcv[1];
}

// powering paw3204 by gpio (not recommended)
void init_paw3204() {
    const bmp_api_gpio_mode_t bmp_gpio_out_pp_hd = {.dir = BMP_MODE_OUTPUT, .pull = BMP_PULL_NONE, .drive = BMP_PIN_H0H1};

    BMPAPI->gpio.set_mode(PAW3204_POWER, &bmp_gpio_out_pp_hd);
    BMPAPI->gpio.set_pin(PAW3204_POWER);
}

int read_paw3204(uint8_t *stat, int8_t *x, int8_t *y) {
    {
        uint8_t snd[] = {READ(REG_STAT), 0xFF};
        uint8_t rcv[] = {0xFF, 0xFF};

        spi_paw3204(snd, sizeof(snd), rcv, sizeof(rcv), 0xFF);
        *stat = rcv[1];
    }
    {
        uint8_t snd[] = {READ(REG_X), 0xFF};
        uint8_t rcv[] = {0xFF, 0xFF};

        spi_paw3204(snd, sizeof(snd), rcv, sizeof(rcv), 0xFF);
        *x = *((int8_t *)(rcv + 1));
    }
    {
        uint8_t snd[] = {READ(REG_Y), 0xFF};
        uint8_t rcv[] = {0xFF, 0xFF};

        spi_paw3204(snd, sizeof(snd), rcv, sizeof(rcv), 0xFF);
        *y = *((int8_t *)(rcv + 1));
    }
    return 1;
}

void read_all_paw3204(paw3204_all_reg *dat) {
    for (uint8_t idx = 0; idx < sizeof(paw3204_all_reg); idx++) {
        uint8_t snd[] = {READ(idx), 0xFF};
        uint8_t rcv[] = {0xFF, 0xFF};

        spi_paw3204(snd, sizeof(snd), rcv, sizeof(rcv), 0xFF);
        dat->reg[idx] = rcv[1];
    }
}
