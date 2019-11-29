/* Copyright 2019 sekigon-gonnoc
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "kugel.h"

#include <string.h>

#include QMK_KEYBOARD_H
#include "matrix.h"
#include "bmp_matrix.h"
#include "spi.h"

#include "report.h"

#define IO_RESET 8
#define IO_ROW 9
#define TB_POW 10
#define CS_PIN_IO 18
#define CS_PIN_TB 17

const uint8_t ioexpander_addrs[]   = {0x00, 0x01, 0x02};
const uint8_t ioexpander_cs_pins[] = {CS_PIN_IO, CS_PIN_IO, CS_PIN_IO};
static bool   ioexpander_init_flag = false;
bool          trackball_init_flag  = false;

#define WRITE_TO(addr) (0x80 | addr)
#define READ_FROM(addr) (addr)
void reset_adns7530();

void keyboard_post_init_kb() { debug_enable = false; }

void create_user_file() {
    static const char qmk_configurator[] = "<meta http-equiv=\"refresh\" content=\"0;URL=\'https://sekigon-gonnoc.github.io/qmk_configurator/#/kugel/LAYOUT\'\"/>";
    BMPAPI->usb.create_file("MAP_EDITHTM", (uint8_t *)qmk_configurator, strlen(qmk_configurator));

    static const char build_guide[] = "<meta http-equiv=\"refresh\" content=\"0;URL=\'https://github.com/sekigon-gonnoc/Kugel-doc\'\"/>";
    BMPAPI->usb.create_file("BLDGUIDEHTM", (uint8_t *)build_guide, strlen(build_guide));
}

void matrix_init_kb() {
    spim_init();

    // reset io expanders
    setPinOutput(IO_RESET);
    setPinOd(IO_ROW);

    writePinLow(IO_RESET);

    writePinHigh(CS_PIN_IO);
    writePinHigh(CS_PIN_TB);
    setPinOutput(CS_PIN_IO);
    setPinOutput(CS_PIN_TB);

    // turn on trackball
    setPinOutput(TB_POW);
    writePinLow(TB_POW);

    writePinHigh(IO_RESET);

    matrix_init_user();
}

static trackball_info_t tb_info;

const trackball_info_t *get_trackball_info() { return &tb_info; }

void matrix_scan_kb() {
    static int     init_cnt;
    // trackball communication packet
    static uint8_t snd[]         = {0x02, 0, 0x03, 0, 0x04, 0, 0x05, 0, 0x06, 0};
    static uint8_t rcv[]         = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    uint32_t       reset_timeout = 1000;

    tb_info.x = 0;
    tb_info.y = 0;

    do {
        if (++init_cnt < 10) {
            // skip until initialize done
            break;
        } else if (init_cnt == 10) {
            uint8_t snd[] = {0, 0};
            uint8_t rcv[] = {0, 0};
            do {
                // read trackball id
                spim_start(snd, 2, rcv, 2, CS_PIN_TB);
            } while (rcv[1] != 0x31 && reset_timeout--);

            if (reset_timeout > 0) {
                trackball_init_flag = true;
            }

            // set pull-up of io expanders
            uint8_t mcp23s_snd2[] = {0x40 | 0 | 0, 0x0C, 0xFF, 0xFF};
            uint8_t mcp23s_rcv2[] = {0, 0, 0, 0};
            spim_start(mcp23s_snd2, 4, mcp23s_rcv2, 4, CS_PIN_IO);

            // set addressing mode of io expanders
            uint8_t mcp23s_snd[] = {0x40 | 0 | 0, 0x0A, (1 << 3) | (1 << 2)};
            uint8_t mcp23s_rcv[] = {0, 0, 0};
            spim_start(mcp23s_snd, 3, mcp23s_rcv, 3, CS_PIN_IO);

            ioexpander_init_flag = true;

            if (trackball_init_flag) {
                reset_adns7530();
            }
            break;
        } else {
            init_cnt = 11;
        }

        if (!trackball_init_flag) {
            break;
        }

        spim_start(snd, 10, rcv, 10, CS_PIN_TB);

        tb_info.x           = (int16_t)(((int16_t)rcv[3] << 4) | (((int16_t)rcv[7] >> 4) << 12));
        tb_info.y           = (int16_t)(((int16_t)rcv[5] << 4) | (((int16_t)rcv[7] & 0x0F) << 12));
        tb_info.surface     = rcv[9];
        tb_info.motion_flag = rcv[1];
    } while (0);

    matrix_scan_user();
}

void reset_adns7530() {
    uint8_t snd1[] = {
        WRITE_TO(0x3A), 0x5a, 0, 0, WRITE_TO(0x2E), 0, 0, 0,
    };
    uint8_t rcv[256];

    spim_start(snd1, 8, rcv, 8, CS_PIN_TB);

    uint8_t snd2[] = {
        READ_FROM(0x2), 0, READ_FROM(0x3), 0, READ_FROM(0x4), 0, READ_FROM(0x5), 0,
    };
    spim_start(snd2, 8, rcv, 8, CS_PIN_TB);

    uint8_t snd3[] = {
        WRITE_TO(0x3C), 0x27, WRITE_TO(0x22), 0x0A, WRITE_TO(0x21), 0x01, WRITE_TO(0x3C), 0x32, WRITE_TO(0x23), 0x20, WRITE_TO(0x3C), 0x05,
    };
    spim_start(snd3, 12, rcv, 12, CS_PIN_TB);

    // set laser power
    uint8_t snd4[] = {
        WRITE_TO(0x1A), 0x40, WRITE_TO(0x1F), (uint8_t)((~0x40) & 0xFF), WRITE_TO(0x1C), 0xFF, WRITE_TO(0x1D), 0,
    };
    spim_start(snd4, 8, rcv, 8, CS_PIN_TB);
}

static void kugel_matrix_init() {}

static uint32_t kugel_matrix_get_row() { return MATRIX_ROWS_DEFAULT; }

static uint32_t kugel_matrix_get_col() { return MATRIX_COLS_DEFAULT; }

static uint32_t kugel_matrix_scan(matrix_row_t *matrix_raw) {
    uint8_t  spi_send[4];
    uint8_t  spi_recv[4] = {0xFF};
    uint32_t res         = 0;

    matrix_row_t row_state;

    if (ioexpander_init_flag == false) {
        return 0;
    }

    for (uint8_t row = 0; row < MATRIX_ROWS_DEFAULT; row++) {
        spi_send[0] = 0x40 | (ioexpander_addrs[row] << 1) | 1;
        spi_send[1] = 0x12;
        spi_send[2] = 0;
        spi_send[3] = 0;
        spi_recv[0] = 0xFF;
        spi_recv[1] = 0xFF;
        spi_recv[2] = 0xFF;
        spi_recv[3] = 0xFF;

        spim_start(spi_send, 4, spi_recv, 4, ioexpander_cs_pins[row]);

        row_state = ~((((uint16_t)spi_recv[3]) << 8) | spi_recv[2]);
        if (row_state == 0) {
            // may failed to read
            continue;
        } else if (row_state != matrix_raw[row]) {
            res |= 1;
        }
        matrix_raw[row] = row_state;
    }

    return res;
}

static const bmp_matrix_func_t matrix_func = {kugel_matrix_init, kugel_matrix_get_row, kugel_matrix_get_col, kugel_matrix_scan};

const bmp_matrix_func_t *get_matrix_func_user() { return &matrix_func; }
