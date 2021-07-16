/* This program is free software: you can redistribute it and/or modify
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

#include "quantum.h"
#include "bmp_matrix.h"

#include "debug.h"
#include "i2c_master.h"

#include "apidef.h"
#include "debug.h"

#define LEN(x) (sizeof(x) / sizeof(x[0]))

// bool bmp_config_overwrite(bmp_api_config_t const *const config_on_storage,
//                           bmp_api_config_t *const       keyboard_config) {
//     // User can overwrite partial settings
//     keyboard_config->mode            = config_on_storage->mode;
//     keyboard_config->startup         = config_on_storage->startup;
//     keyboard_config->matrix.debounce = config_on_storage->matrix.debounce;
//     keyboard_config->matrix.is_left_hand =
//         config_on_storage->matrix.is_left_hand;
//     keyboard_config->param_central    = config_on_storage->param_central;
//     keyboard_config->param_peripheral = config_on_storage->param_peripheral;
//     keyboard_config->keymap           = config_on_storage->keymap;
//     keyboard_config->reserved[2]      = config_on_storage->reserved[2];
//
//     return true;
// }

static void create_status_file() {}

void keyboard_post_init_kb() {
    create_status_file();

    debug_enable   = false;
    debug_keyboard = false;
    debug_mouse    = false;
}

static uint8_t buf[256];
static uint8_t widx, ridx, cnt;

void uart_recv_callback(uint8_t dat) {
    buf[widx] = dat;
    widx      = (widx + 1) % 256;
    cnt++;
}

uint8_t uart_available() { return cnt; }

uint8_t uart_getchar() {
    uint8_t c = buf[ridx];
    cnt--;
    ridx = (ridx + 1) % 256;

    dprintf("%02X ", c);
    return c;
}

void uart_flush_rx_buffer() { BMPAPI->uart.send(NULL, 0); }

void qt_matrix_init() {
    bmp_uart_config_t uart_config;
    uart_config.tx_pin      = 1;
    uart_config.rx_pin      = 2;
    uart_config.rx_callback = uart_recv_callback;
    uart_config.baudrate    = 115200;

    BMPAPI->uart.init(&uart_config);
}

uint32_t qt_get_device_row() { return MATRIX_ROWS_DEFAULT; }
uint32_t qt_get_device_col() { return MATRIX_COLS_DEFAULT; }
uint32_t qt_matrix_scan(matrix_row_t *matrix_raw) {
    bool changed = process_packet(matrix_raw);

    uart_flush_rx_buffer();

    return changed ? 1 : 0;
}

static const bmp_matrix_func_t matrix_func = {
    qt_matrix_init, qt_get_device_row, qt_get_device_col, qt_matrix_scan};

const bmp_matrix_func_t *get_matrix_func_user() { return &matrix_func; }

void bmp_before_sleep() {}

bool checkSafemodeFlag(bmp_api_config_t const *const config) { return false; }

uint8_t matrix_scan_impl(matrix_row_t* _matrix){
    return qt_matrix_scan(_matrix);
}
