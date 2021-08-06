/* Copyright 2021 sekigon-gonnoc
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

#include "keyboard_quantizer.h"
#include "kqb.h"
#include "report_descriptor_parser.h"
#include "report_parser.h"

#include <string.h>

#include "quantum.h"
#include "bmp.h"
#include "bmp_matrix.h"

#include "debug.h"
#include "i2c_master.h"

#include "apidef.h"
#include "debug.h"

#define LEN(x) (sizeof(x) / sizeof(x[0]))

extern bool    ch559_update_mode;
extern uint8_t device_cnt;
extern uint8_t hid_info_cnt;

uint8_t qt_cmd_buf[3];
bool    qt_cmd_new;

bool bmp_config_overwrite(bmp_api_config_t const *const config_on_storage,
                          bmp_api_config_t *const       keyboard_config) {

    memcpy(keyboard_config, config_on_storage, sizeof(*keyboard_config));

    keyboard_config->mode = SINGLE;
    memcpy(&keyboard_config->device_info, &default_config.device_info,
           sizeof(keyboard_config->device_info));
    keyboard_config->param_peripheral.max_interval  = 30;
    keyboard_config->param_peripheral.min_interval  = 8;
    keyboard_config->param_peripheral.slave_latency = 7;

    return true;
}

void create_user_file() {
    static const char build_guide[] =
        "<meta http-equiv=\"refresh\" "
        "content=\"0;URL=\'https://github.com/sekigon-gonnoc/\'\"/>";
    BMPAPI->usb.create_file("BLDGUIDEHTM", (uint8_t *)build_guide,
                            strlen(build_guide));
}

// void keyboard_post_init_kb() {
//     create_status_file();
//
//     debug_enable   = false;
//     debug_keyboard = false;
//     debug_mouse    = false;
// }
//

static uint8_t buf[1024];
static uint16_t widx, ridx, cnt;

void uart_buf_init(void) {
    memset(buf, 0, sizeof(buf));
    widx = 0;
    ridx = 0;
    cnt  = 0;
}

void uart_recv_callback(uint8_t dat) {
    if (cnt < sizeof(buf) - 1) {
        buf[widx] = dat;
        widx      = (widx + 1) % sizeof(buf);
        cnt++;
    }
}

bool uart_available() { return cnt > 0; }

uint8_t uart_getchar() {
    uint8_t c = 0;
    if (cnt > 0) {
        c = buf[ridx];
        cnt--;
        ridx = (ridx + 1) % sizeof(buf);
    }

    return c;
}

void uart_putchar(uint8_t c) {
    BMPAPI->uart.send(&c, 1);
}

int send_reset_cmd(void) {
    // send reset command to ch559

    writePinHigh(KQB_PIN_CHRST);
    xprintf("send reset\n");
    writePinLow(KQB_PIN_CHRST);

    return 0;
}

int send_load_cmd(uint8_t time) {
    if (!qt_cmd_new) {
        dprintf("send load command:%d\n", time);
        qt_cmd_buf[0] = 'l';
        qt_cmd_buf[1] = time;
        qt_cmd_buf[2] = '\n';
        qt_cmd_new    = true;

        return 0;
    } else {
        return 1;
    }
}

int send_led_cmd(uint8_t led) {
    if (!qt_cmd_new) {
        dprintf("send led command:%d\n", led);
        qt_cmd_buf[0] = 0x80 | led;
        qt_cmd_new    = true;

        return 0;
    } else {
        return 1;
    }
}

void matrix_scan_kb(void) {
    bmp_api_config_t const * config = BMPAPI->app.get_config();
    static uint32_t timer = UINT32_MAX >> 1; // To run at first loop

    if ((!is_usb_connected()) &&
        config->reserved[3] > 0 &&
        timer_elapsed32(timer) > (uint32_t)config->reserved[3] * 1000) {
        uint32_t duty =  (config->reserved[4] < 50) ? config->reserved[4] : 50;
        uint32_t duration = (uint32_t)config->reserved[3] * duty / 10; //  /100*10 (% * 0.1s)
        int res = send_load_cmd(duration > 0xff ? 0xff : duration);

        if (res == 0) {
            timer = timer_read32();
        }
    }

    static uint8_t usb_led_indicator_recv;
    static uint8_t ble_led_indicator_recv;
    if (get_usb_enabled()) {
        uint8_t current = BMPAPI->usb.get_indicator_led();
        ble_led_indicator_recv = 0;
        if (current != usb_led_indicator_recv) {
            usb_led_indicator_recv = current;
            send_led_cmd(current);
        }
    } else if (get_ble_enabled()) {
        uint8_t current = BMPAPI->ble.get_indicator_led();
        usb_led_indicator_recv = 0;
        if (current != ble_led_indicator_recv) {
            ble_led_indicator_recv = current;
            send_led_cmd(current);
        }
    }

    matrix_scan_user();
}

void uart_flush_rx_buffer() { BMPAPI->uart.send(NULL, 0); }

void qt_uart_init() {
    bmp_uart_config_t uart_config;
    uart_config.tx_pin      = KQB_PIN_TX;
    uart_config.rx_pin      = KQB_PIN_RX;
    uart_config.rx_callback = uart_recv_callback;
    uart_config.baudrate    = 115200;
    uart_config.rx_protocol = 1;

    BMPAPI->uart.init(&uart_config);
}

void bmp_before_sleep() {
    bmp_api_config_t config = *BMPAPI->app.get_config();
    config.matrix.diode_direction = 0xff;
    BMPAPI->app.set_config(&config);
    setPinInputLow(KQB_PIN_LED0);
}

bool checkSafemodeFlag(bmp_api_config_t const *const config) { return false; }


#include "bmp_via.h"
#include "bmp_config.h"

void dynamic_keymap_reset() {
    for (int idx = 0; idx < DYNAMIC_KEYMAP_MAX_LEN; idx++) {
        const uint8_t layer = idx / (MATRIX_COLS_DEFAULT * MATRIX_ROWS_DEFAULT);
        const uint8_t offset =
            idx % (MATRIX_COLS_DEFAULT * MATRIX_ROWS_DEFAULT);
        const uint8_t          row = offset / MATRIX_COLS_DEFAULT;
        const uint8_t          col = offset % MATRIX_COLS_DEFAULT;
        const bmp_api_keypos_t key = {.row = row, .col = col};

        if (row < MATRIX_MODIFIER_ROW) {
            BMPAPI->app.set_keycode_to_keymap(
                layer, &key, idx % (MATRIX_COLS_DEFAULT * MATRIX_ROWS_DEFAULT));
        } else if (row == MATRIX_MODIFIER_ROW) {
            BMPAPI->app.set_keycode_to_keymap(layer, &key, KC_LCTRL + col);
        } else if (row == MATRIX_MSBTN_ROW) {
            BMPAPI->app.set_keycode_to_keymap(layer, &key, KC_BTN1 + col);
        } else if (row == MATRIX_MSGES_ROW) {
            if (col < MATRIX_MSWHEEL_COL) {
                BMPAPI->app.set_keycode_to_keymap(layer, &key, KC_NO);
            } else {
                BMPAPI->app.set_keycode_to_keymap(
                    layer, &key, KC_MS_WH_UP + col - MATRIX_MSWHEEL_COL);
            }
        }
    }

    save_keymap();
}

static uint8_t         pre_keyreport[8];

__attribute__((weak)) void report_descriptor_parser_user(uint8_t        dev_num,
                                                         uint8_t const *buf,
                                                         uint16_t       len) {
    if (BMPAPI->app.get_config()->matrix.diode_direction == 1) {
        // no descriptor parser
    } else {
        parse_report_descriptor(dev_num, buf, len);
    }
}

__attribute__((weak)) bool report_parser_user(uint8_t const *buf, uint16_t len,
                                              matrix_row_t *current_matrix) {
    packet_header_t const *packet_header = (packet_header_t const *)buf;

    if (BMPAPI->app.get_config()->matrix.diode_direction == 1) {
        return report_parser_fixed(buf, packet_header->len, pre_keyreport,
                                   current_matrix);
    } else {
        return parse_report(packet_header->dev_num, &packet_header->data_start,
                            packet_header->len);
    }
}

__attribute__((weak)) void on_disconnect_device_user(uint8_t device) {
    memset(pre_keyreport, 0, sizeof(pre_keyreport));
}

#include "microshell/core/msconf.h"
#include "microshell/util/mscmd.h"
#include "cli.h"

static void check_reset_command(uint8_t const *buf, uint8_t len) {
    if (len < 3) {
        return;
    }

    if (buf[0] == 0x57 && buf[1] == 0xab && buf[2] == 0xa2) {
        const uint8_t ret[] = {0x55, 0xaa, 0xa2, 0xe7, 0x02,
                               0x00, 0x00, 0x00, 0x8b};
        BMPAPI->usb.serial_puts(ret, sizeof(ret));

        reset_counter = 1;
    }
}

void pass_uart(void *_context) {
    uint8_t send_buf[128];
    int32_t btr = BMPAPI->usb.serial_byte_to_read();
    uint8_t idx = 0;

    while (uart_available()) {
        BMPAPI->usb.serial_putc(uart_getchar());
    }

    while (btr--) {
        send_buf[idx++] = BMPAPI->usb.serial_getc();

        if (idx >= sizeof(send_buf)) {
            break;
        }
    }

    check_reset_command(send_buf, idx);
    BMPAPI->uart.send(send_buf, idx);
}

MSCMD_USER_RESULT usrcmd_chboot(MSOPT *msopt, MSCMD_USER_OBJECT usrobj) {
    ch559_update_mode = true;

    writePinHigh(KQB_PIN_CHRST);
    // xprintf("Assert reset\n");
    setPinOutput(KQB_PIN_CHBOOT);
    writePinHigh(KQB_PIN_CHBOOT);
    // xprintf("Dessert reset\n");
    writePinLow(KQB_PIN_CHRST);

    BMPAPI->ble.disconnect(1);
    BMPAPI->spis.init(NULL);

    uart_buf_init();

    bmp_uart_config_t uart_config;
    uart_config.tx_pin      = KQB_PIN_TX;
    uart_config.rx_pin      = KQB_PIN_RX;
    uart_config.rx_callback = uart_recv_callback;
    uart_config.rx_protocol = 0;
    uart_config.baudrate    = 57600;

    BMPAPI->uart.init(&uart_config);

    cli_app_t cli_app = {.func = pass_uart, .data = NULL};
    set_cli_app(&cli_app);

    return 0;
}

MSCMD_USER_RESULT usrcmd_chreset(MSOPT *msopt, MSCMD_USER_OBJECT usrobj) {
    send_reset_cmd();

    return 0;
}

MSCMD_USER_RESULT usrcmd_chload(MSOPT *msopt, MSCMD_USER_OBJECT usrobj) {
    if (msopt->argc < 2) {
        xprintf("chload <time_100ms>\n");
        return 1;
    }

    char arg[16];
    msopt_get_argv(msopt, 1, arg, sizeof(arg));
    uint16_t time = (uint16_t)atoi(arg);
    send_load_cmd(time > 0xff ? 0xff : time);

    return 0;
}

MSCMD_USER_RESULT usrcmd_chled(MSOPT *msopt, MSCMD_USER_OBJECT usrobj) {
    char arg[16];
    msopt_get_argv(msopt, 1, arg, sizeof(arg));
    uint16_t led = (uint16_t)atoi(arg);
    send_led_cmd(led);

    return 0;
}

MSCMD_USER_RESULT usrcmd_chdev(MSOPT *msopt, MSCMD_USER_OBJECT usrobj) {
    char arg[16];
    msopt_get_argv(msopt, 1, arg, sizeof(arg));
    uint16_t dev = (uint16_t)atoi(arg);
    print_hid_device(dev);

    return 0;
}

MSCMD_USER_RESULT usrcmd_chver(MSOPT *msopt, MSCMD_USER_OBJECT usrobj) {
    extern uint32_t ch559_version;
    xprintf("CH559 FW ver: %d.%d.%d\n", ch559_version >> 16,
            (ch559_version >> 8) & 0xff, ch559_version & 0xff);
    return 0;
}

MSCMD_USER_RESULT usrcmd_chparser(MSOPT *msopt, MSCMD_USER_OBJECT usrobj) {
    char arg[16];
    msopt_get_argv(msopt, 1, arg, sizeof(arg));
    uint16_t type = (uint16_t)atoi(arg);

    if (type == 1) {
        xprintf("Set parser type: FIXED\n");
    } else {
        xprintf("Set parser type: DEFAULT\n");
        type = 0;
    }

    bmp_api_config_t config = *BMPAPI->app.get_config();
    config.matrix.diode_direction = type;

    BMPAPI->app.set_config(&config);

    return 0;
}
