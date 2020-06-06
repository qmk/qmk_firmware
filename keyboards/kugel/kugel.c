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
#include "bmp.h"
#include "bmp_matrix.h"
#include "spi.h"
#include "adns7530.h"
#include "paw3204.h"

#include "report.h"

#define IO_RESET 8
#define IO_ROW 9
#define IO_INT 11
#define TB_POW 10
#define TB_INT 12
#define CS_PIN_IO 18
#define CS_PIN_TB 17

#define IO_NUM 3

const uint8_t ioexpander_addrs[IO_NUM]   = {0x00, 0x01, 0x02};
const uint8_t ioexpander_cs_pins[IO_NUM] = {CS_PIN_IO, CS_PIN_IO, CS_PIN_IO};
static bool   ioexpander_init_flag       = false;
static bool   ioexpander_init_succeed[IO_NUM] = {false};

trackball_type_t trackball_init_flag = TRACKBALL_NONE;

void keyboard_post_init_kb() { debug_enable = false; }

void create_user_file() {
    static const char qmk_configurator[] =
        "<meta http-equiv=\"refresh\" "
        "content=\"0;URL=\'https://sekigon-gonnoc.github.io/qmk_configurator/#/"
        "kugel/LAYOUT\'\"/>";
    BMPAPI->usb.create_file("MAP_EDITHTM", (uint8_t *)qmk_configurator,
                            strlen(qmk_configurator));

    static const char build_guide[] =
        "<meta http-equiv=\"refresh\" "
        "content=\"0;URL=\'https://github.com/sekigon-gonnoc/Kugel-doc\'\"/>";
    BMPAPI->usb.create_file("BLDGUIDEHTM", (uint8_t *)build_guide,
                            strlen(build_guide));

    // set bitmap header
    // 8bit 26*26 pixels

    uint32_t       bitmap_size;
    const uint8_t *bitmap = get_pixel_bitmap_adns7530(&bitmap_size);
    BMPAPI->usb.create_file("PIXEL   BMP", bitmap, bitmap_size);
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
                trackball_init_flag == TRACKBALL_ADNS ? "ADNS" :
                (trackball_init_flag == TRACKBALL_BTO ? " BTO" : "NO"));
    // clang-format on
    BMPAPI->usb.create_file("STATUS  TXT", (uint8_t *)status_str,
                            strlen(status_str));
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

    // set addressing mode of io expanders, INT pin mirror, and INT pin open
    // drain
    {
        uint8_t mcp23s_snd[] = {0x40 | 0 | 0, 0x0A,
                                (1 << 6) | (1 << 3) | (1 << 2)};
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
    // read trackball id
    int32_t retry = 1000;
    do {
        if (read_pid_adns7530(CS_PIN_TB) == 0x31) {
            break;
        }
    } while (--retry > 0);

    if (retry > 0) {
        trackball_init_flag = TRACKBALL_ADNS;
        BMPAPI->adc.config_vcc_channel(8, 3000, 2000);
        return;
    }

    if (read_pid_paw3204() == 0x30) {
        trackball_init_flag = TRACKBALL_BTO;
        return;
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

            reset_adns7530(CS_PIN_TB);
            check_tb_connection();

            if (trackball_init_flag == TRACKBALL_ADNS) {
                setPinInputHigh(TB_INT);
            } else if (trackball_init_flag == TRACKBALL_NONE) {
                setPinInputHigh(TB_POW);
            }

            create_status_file();
            break;
        } else {
            init_cnt = 11;
        }

        if (trackball_init_flag == TRACKBALL_ADNS) {
            // read motion data
            adns7530_info_t adns7530_info;
            read_adns7530(readPin(TB_INT) == 0 || debug_mouse, CS_PIN_TB,
                          &adns7530_info);
            tb_info.x           = adns7530_info.x;
            tb_info.y           = adns7530_info.y;
            tb_info.surface     = adns7530_info.surface;
            tb_info.motion_flag = adns7530_info.motion_flag;
        } else if (trackball_init_flag == TRACKBALL_BTO) {
            // trackball communication packet
            static uint32_t last_read_time;
            static uint32_t last_active_time;

            if (timer_elapsed32(last_active_time) < 200 ||
                timer_elapsed32(last_read_time) > 50) {
                uint8_t stat = 0;
                int8_t  x = 0, y = 0;

                read_paw3204(&stat, &x, &y);
                last_read_time = timer_read32();

                tb_info.x           = -y * 16;
                tb_info.y           = x * 16;
                tb_info.surface     = 0;
                tb_info.motion_flag = stat;

                if (stat & 0x80) {
                    last_active_time = timer_read32();
                }
            } else {
                tb_info.x           = 0;
                tb_info.y           = 0;
                tb_info.motion_flag = 0;
                writePinHigh(5);
                writePinHigh(6);
            }
        }
    } while (0);

    if (!is_usb_connected()) {
        static uint32_t battery_check_cnt = 0;
        static float voltage = -1;
        static uint32_t low_battery_cnt = 0;

        if (voltage < 0) {
            // first measurement
            voltage = BMPAPI->app.get_vcc_mv();
            battery_check_cnt = timer_read32();
        } else if (timer_elapsed32(battery_check_cnt) > 1000) {
            battery_check_cnt = timer_read32();
            uint32_t v_mes =  BMPAPI->app.get_vcc_mv();

            if (v_mes > voltage) {
                voltage = (0.7f) * voltage + (0.3f) * v_mes;
            } else {
                if (voltage - v_mes > 100) {
                } else {
                    voltage = (0.95f) * voltage + (0.05f) * v_mes;
                }
            }

            if (voltage < 1000.0f - 100.0f) { // 100mV offset by series resistance
                low_battery_cnt++;
            }

            if (low_battery_cnt > 30) {
                sleep_enter_counter = 1;
            }
        }
    }

    matrix_scan_user();
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

    spim_init();

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

static const bmp_matrix_func_t matrix_func = {
    kugel_matrix_init, kugel_matrix_get_row, kugel_matrix_get_col,
    kugel_matrix_scan};

const bmp_matrix_func_t *get_matrix_func_user() { return &matrix_func; }

void bmp_before_sleep() {
    setPinInputHigh(16);
    setPinInputHigh(14);
    setPinInputHigh(CS_PIN_TB);
    writePinHigh(TB_POW);
}

bool checkSafemodeFlag(bmp_api_config_t const *const config) { return false; }

bool bmp_config_overwrite(bmp_api_config_t const *const config_on_storage,
                          bmp_api_config_t *const       keyboard_config) {
    // get vcc from a3
    BMPAPI->adc.config_vcc_channel(3, 1200, 700);
    // wait until voltage become stable
    for (int i = 0; i < 40000; i++) {
        BMPAPI->app.get_vcc_percent();
    }

    // User can overwrite partial settings
    keyboard_config->startup          = config_on_storage->startup;
    keyboard_config->matrix.debounce  = config_on_storage->matrix.debounce;
    keyboard_config->param_central    = config_on_storage->param_central;
    keyboard_config->param_peripheral = config_on_storage->param_peripheral;
    keyboard_config->keymap           = config_on_storage->keymap;
    keyboard_config->reserved[2]      = config_on_storage->reserved[2];
    return true;
}

#include "microshell/util/mscmd.h"

MSCMD_USER_RESULT usrcmd_trackball_pixel(MSOPT *           msopt,
                                         MSCMD_USER_OBJECT usrobj) {
    return capture_pixel_adns7530(CS_PIN_TB);
}
