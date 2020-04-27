/*
Copyright 2019 Sekigon

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "quantum.h"
#include "paw3204.h"

#define READ(addr) (addr)
#define WRITE(addr) (0x80 | addr)

#define REG_PID1 0x00
#define REG_PID2 0x01
#define REG_STAT 0x02
#define REG_X 0x03
#define REG_Y 0x04

typedef int (*spi_paw3204_t)(uint8_t *p_tx_buffer, size_t tx_length, uint8_t *p_rx_buffer, size_t rx_length, uint8_t cs_pin);

#ifndef PAW3204_SCLK
#    define PAW3204_SCLK D0
#endif

#ifndef PAW3204_DATA
#    define PAW3204_DATA D1
#endif

int spi_soft_half_duplex(uint8_t *p_tx_buffer, size_t tx_length, uint8_t *p_rx_buffer, size_t rx_length, uint8_t cs_pin) {
    if (tx_length != 2 || rx_length != 2) {
        p_rx_buffer[1] = 0xFF;
        return 1;
    }

    writePin(PAW3204_DATA, readPin(PAW3204_DATA));
    setPinOutput(PAW3204_DATA);

    for (int8_t idx = 7; idx >= 0; idx--) {
        writePinLow(PAW3204_SCLK);
        writePin(PAW3204_DATA, (p_tx_buffer[0] >> idx) & 1);
        writePinHigh(PAW3204_SCLK);
    }

    _delay_us(5);
    setPinInputHigh(PAW3204_DATA);

    p_rx_buffer[1] = 0;
    for (int8_t idx = 7; idx >= 0; idx--) {
        writePinLow(PAW3204_SCLK);
        writePinHigh(PAW3204_SCLK);
        p_rx_buffer[1] |= readPin(PAW3204_DATA) << idx;
    }

    return 0;
}

// spi_paw3204_t spi_paw3204 = spim_start;
spi_paw3204_t spi_paw3204 = spi_soft_half_duplex;

uint8_t read_pid_paw3204() {
    uint8_t snd[] = {READ(REG_PID1), 0xFF};
    uint8_t rcv[] = {0xFF, 0xFF};

    spi_paw3204(snd, sizeof(snd), rcv, sizeof(rcv), 0xFF);

    return rcv[1];
}

// set IO pins
void init_paw3204() {
    setPinOutput(PAW3204_SCLK);
    setPinInputHigh(PAW3204_DATA);
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
