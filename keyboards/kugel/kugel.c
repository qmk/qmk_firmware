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
#include "debug.h"

#include QMK_KEYBOARD_H
#include "matrix.h"
#include "bmp_matrix.h"
#include "spi.h"

#include "report.h"

#define IO_RESET 8
#define IO_ROW 9
#define IO_INT 11
#define TB_POW 10
#define TB_INT 12
#define CS_PIN_IO 18
#define CS_PIN_TB 17

#define IO_NUM 3

const uint8_t ioexpander_addrs[IO_NUM]        = {0x00, 0x01, 0x02};
const uint8_t ioexpander_cs_pins[IO_NUM]      = {CS_PIN_IO, CS_PIN_IO, CS_PIN_IO};
static bool   ioexpander_init_flag            = false;
static bool   ioexpander_init_succeed[IO_NUM] = {false};
bool          trackball_init_flag             = false;

#define WRITE_TO(addr) (0x80 | addr)
#define READ_FROM(addr) (addr)
void reset_adns7530();

void keyboard_post_init_kb() { debug_enable = false; }

#define ToWord(p_byte) (*((uint16_t *)(p_byte)))
#define ToDWord(p_byte) (*((uint32_t *)(p_byte)))
static uint8_t  pixel_img[1024];
static uint32_t pix_to_read;
#define IMG_WIDTH 26

void create_user_file() {
    static const char qmk_configurator[] = "<meta http-equiv=\"refresh\" content=\"0;URL=\'https://sekigon-gonnoc.github.io/qmk_configurator/#/kugel/LAYOUT\'\"/>";
    BMPAPI->usb.create_file("MAP_EDITHTM", (uint8_t *)qmk_configurator, strlen(qmk_configurator));

    static const char build_guide[] = "<meta http-equiv=\"refresh\" content=\"0;URL=\'https://github.com/sekigon-gonnoc/Kugel-doc\'\"/>";
    BMPAPI->usb.create_file("BLDGUIDEHTM", (uint8_t *)build_guide, strlen(build_guide));

    // set bitmap header
    // 8bit 26*26 pixels
    pixel_img[0]            = 0x42;
    pixel_img[1]            = 0x4D;
    ToDWord(&pixel_img[2])  = 26 * 28 + 54;
    ToWord(&pixel_img[6])   = 0;
    ToWord(&pixel_img[8])   = 0;
    ToDWord(&pixel_img[10]) = 0x36;
    ToDWord(&pixel_img[14]) = 40;
    ToDWord(&pixel_img[18]) = 26;
    ToDWord(&pixel_img[22]) = 26;
    ToWord(&pixel_img[26])  = 1;
    ToWord(&pixel_img[28])  = 8;
    ToDWord(&pixel_img[30]) = 0;
    ToDWord(&pixel_img[34]) = 26 * 28;
    ToDWord(&pixel_img[38]) = 96;
    ToDWord(&pixel_img[42]) = 96;
    ToDWord(&pixel_img[46]) = 0;
    ToDWord(&pixel_img[50]) = 0;
    BMPAPI->usb.create_file("PIXEL   BMP", pixel_img, 26 * 28 + 54);
}

static void create_status_file() {
    static char status_str[128];
    // clang-format off
    tfp_sprintf(status_str,
                "IO exp1:%s\r\n"
                "IO exp2:%s\r\n"
                "IO exp3:%s\r\n"
                "Trackball:%s\r\n",
                ioexpander_init_succeed[0] ? "OK" : "NG",
                ioexpander_init_succeed[1] ? "OK" : "NG",
                ioexpander_init_succeed[2] ? "OK" : "NG",
                trackball_init_flag ? "OK" : "NG");
    // clang-format on
    BMPAPI->usb.create_file("STATUS  TXT", (uint8_t *)status_str, strlen(status_str));
}

void matrix_init_kb() {
    // reset io expanders
    setPinOutput(IO_RESET);
    setPinOd(IO_ROW);

    writePinLow(IO_RESET);

    writePinHigh(CS_PIN_IO);
    writePinHigh(CS_PIN_TB);
    setPinOutput(CS_PIN_IO);
    setPinOutput(CS_PIN_TB);

    // turn off trackball
    setPinOutput(TB_POW);
    writePinHigh(TB_POW);

    writePinHigh(IO_RESET);

    matrix_init_user();
}

static trackball_info_t tb_info;

const trackball_info_t *get_trackball_info() { return &tb_info; }

static inline void ioexp_init() {
    // set pull-up of io expanders
    {
        uint8_t mcp23s_snd[] = {0x40 | 0 | 0, 0x0C, 0xFF, 0xFF};
        uint8_t mcp23s_rcv[] = {0, 0, 0, 0};
        spim_start(mcp23s_snd, 4, mcp23s_rcv, 4, CS_PIN_IO);
    }

    // enable interrupt for all pins
    {
        uint8_t mcp23s_snd[] = {0x40 | 0 | 0, 0x04, 0xFF, 0xFF};
        uint8_t mcp23s_rcv[] = {0, 0, 0, 0};
        spim_start(mcp23s_snd, 4, mcp23s_rcv, 4, CS_PIN_IO);
    }

    // set addressing mode of io expanders, INT pin mirror, and INT pin open drain
    {
        uint8_t mcp23s_snd[] = {0x40 | 0 | 0, 0x0A, (1 << 6) | (1 << 3) | (1 << 2)};
        uint8_t mcp23s_rcv[] = {0, 0, 0};
        spim_start(mcp23s_snd, 3, mcp23s_rcv, 3, CS_PIN_IO);

        // read the register of each IC and check initialization results
        for (int idx = 0; idx < IO_NUM; idx++) {
            mcp23s_snd[0] = 0x40 | (ioexpander_addrs[idx] << 1) | 1;
            spim_start(mcp23s_snd, 3, mcp23s_rcv, 3, CS_PIN_IO);

            if (mcp23s_rcv[2] == mcp23s_snd[2]) {
                ioexpander_init_succeed[idx] = true;
            }
        }
    }

    ioexpander_init_flag = true;
    for (int idx = 0; idx < IO_NUM; idx++) {
        ioexpander_init_flag &= ioexpander_init_succeed[idx];
    }
}

static inline void check_tb_connection() {
    int32_t retry = 1000;

    // read trackball id
    uint8_t snd[] = {0, 0};
    uint8_t rcv[2];
    do {
        spim_start(snd, 2, rcv, 2, CS_PIN_TB);
    } while (rcv[1] != 0x31 && retry--);

    if (retry > 0) {
        trackball_init_flag = true;
    }
}

void matrix_scan_kb() {
    static int init_cnt;

    tb_info.x = 0;
    tb_info.y = 0;

    do {
        if (++init_cnt < 10) {
            // turn on trackball module
            writePinLow(TB_POW);
            break;
        } else if (init_cnt == 10) {
            spim_init();

            ioexp_init();

            create_status_file();

            reset_adns7530();
            check_tb_connection();
            if (trackball_init_flag) {
                // reset_adns7530();
                setPinInputHigh(TB_INT);
            }
            break;
        } else {
            init_cnt = 11;
        }

        if (!trackball_init_flag) {
            break;
        }

        // read motion data
        if (readPin(TB_INT) == 0 || debug_mouse) {
            // trackball communication packet
            uint8_t snd[] = {0x42, 0, 0, 0, 0, 0};
            uint8_t rcv[] = {0, 0, 0, 0, 0, 0};

            spim_start(snd, sizeof(snd), rcv, sizeof(rcv), CS_PIN_TB);

            tb_info.x           = (int16_t)(((int16_t)rcv[2] << 4) | (((int16_t)rcv[4] >> 4) << 12));
            tb_info.y           = (int16_t)(((int16_t)rcv[3] << 4) | (((int16_t)rcv[4] & 0x0F) << 12));
            tb_info.surface     = rcv[5];
            tb_info.motion_flag = rcv[1];
        } else {
            tb_info.motion_flag = 0;
        }

        if (pix_to_read && (tb_info.motion_flag & 0x40)) {
            // read pixel data if available
            uint8_t  snd[2] = {READ_FROM(0x35), 0};
            uint8_t  rcv[2];
            uint32_t col = (26 * 26 - pix_to_read) / 26;
            uint32_t row = (26 * 26 - pix_to_read) % 26;
            spim_start(snd, 2, rcv, 2, CS_PIN_TB);

            // write to bitmap file
            pixel_img[54 + 28 * row + col] = rcv[1];
            pix_to_read--;

            if (pix_to_read == 0) {
                tfp_printf("capture finished\n");
            } else if (pix_to_read % 100 == 0) {
                tfp_printf(".");
            }
        }
    } while (0);

    matrix_scan_user();
}

void reset_adns7530() {
    uint8_t rcv[256];

    {
        uint8_t snd[] = {
            WRITE_TO(0x3A), 0x5a, 0, 0, WRITE_TO(0x2E), 0, 0, 0,
        };
        spim_start(snd, sizeof(snd), rcv, sizeof(snd), CS_PIN_TB);
    }

    {
        uint8_t snd[] = {
            READ_FROM(0x2), 0, READ_FROM(0x3), 0, READ_FROM(0x4), 0, READ_FROM(0x5), 0,
        };
        spim_start(snd, sizeof(snd), rcv, sizeof(snd), CS_PIN_TB);
    }

    {
        uint8_t snd[] = {
            WRITE_TO(0x3C), 0x27, WRITE_TO(0x22), 0x0A, WRITE_TO(0x21), 0x01, WRITE_TO(0x3C), 0x32, WRITE_TO(0x23), 0x20, WRITE_TO(0x3C), 0x05,
        };
        spim_start(snd, sizeof(snd), rcv, sizeof(snd), CS_PIN_TB);
    }

    {
        // clang-format off
        // set laser power packet
        uint8_t snd[] = {
            WRITE_TO(0x1A), 0x40,
            WRITE_TO(0x1F), (uint8_t)((~0x40) & 0xFF),
            WRITE_TO(0x1C), 0xFF,
            WRITE_TO(0x1D), 0,
        };
        // clang-format on

        // get laser power config from CONFIG.JSN
        uint8_t laser_power = BMPAPI->app.get_config()->reserved[0];
        // set default value
        if (laser_power == 0) {
            laser_power = 0xFF;
        }

        snd[5] = laser_power;
        snd[7] = ~laser_power;

        spim_start(snd, sizeof(snd), rcv, sizeof(snd), CS_PIN_TB);
    }
}

static void kugel_matrix_init() { setPinInputHigh(IO_INT); }

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

    // skip if no pin is changed
    if (readPin(IO_INT)) {
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

#include "microshell/util/mscmd.h"

MSCMD_USER_RESULT usrcmd_trackball_pixel(MSOPT *msopt, MSCMD_USER_OBJECT usrobj) {
    tfp_printf("capture pixel image\n");

    uint8_t rcv[2];
    // reset pointer of pixel_grab to (0,0)
    {
        uint8_t snd[] = {WRITE_TO(0x35), 0x00};
        spim_start(snd, 2, rcv, 2, CS_PIN_TB);
    }

    // wait until PIXRDY set
    do {
        uint8_t snd[] = {READ_FROM(0x02), 0x00};
        spim_start(snd, 2, rcv, 2, CS_PIN_TB);
    } while (!(rcv[1] & 0x60));

    pix_to_read = 26 * 26;
    return 0;
}

void bmp_before_sleep() {
    setPinInputHigh(16);
    setPinInputHigh(14);
    setPinInputHigh(CS_PIN_TB);
    writePinHigh(TB_POW);
}

bool checkSafemodeFlag(bmp_api_config_t const *const config) { return false; }
