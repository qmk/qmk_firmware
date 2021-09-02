

#include  QMK_KEYBOARD_H
#include "kqb.h"

#include <string.h>

#include "quantum.h"
#include "bmp_matrix.h"
#include "apidef.h"

extern bool    ch559_update_mode;
extern bool    ch559_start;
extern int     reset_counter;
extern uint8_t qt_cmd_buf[3];
extern bool    qt_cmd_new;
#define BOOTPIN KQB_PIN_BOOT

bool          matrix_has_changed;
matrix_row_t* matrix_mouse_dest;

static uint8_t  spis_tx_buf[4] = {0xfe, 0xff, 0xff, 0xff};
static uint8_t  spis_rx_buf[1024];
static int16_t  spis_receive_len = -1;
static uint16_t led_on_count = 0;

void qt_spis_callback(uint16_t receive_len) {
    spis_receive_len = receive_len;
}

void qt_spis_receive(uint16_t receive_len) {
    int idx = 0;

    // discard heading bytes
    while (spis_rx_buf[idx] == 0xc0) {
        idx++;
    }

    for (; idx < receive_len; idx++) {
        uart_recv_callback(spis_rx_buf[idx]);
    }

    if (receive_len > 4) {
        led_on_count = 1;
    }

    // static int cnt;
    // static bool send_flag = false;
    // if (++cnt % 100 == 0 || send_flag == true) {
    // if (receive_len > 4) {
        // xprintf("SPIS Receive: %d bytes\n", receive_len);
        // for (int idx = 0; idx < receive_len; idx++) {
        //     xprintf("%02X ", spis_rx_buf[idx]);
        // }
        // xprintf("\n");
    // }

    if (qt_cmd_new) {
        memcpy(spis_tx_buf + 1, qt_cmd_buf, sizeof(qt_cmd_buf));
        memset(qt_cmd_buf, 0xff, sizeof(qt_cmd_buf));
        qt_cmd_new = false;
        // xprintf("SPIS Send:%d,%d,%d,%d\n", spis_tx_buf[0], spis_tx_buf[1], spis_tx_buf[2], spis_tx_buf[3]);
    } else {
        memset(spis_tx_buf + 1, 0xff, sizeof(spis_tx_buf) - 1);
    }

    BMPAPI->spis.start(spis_tx_buf, sizeof(spis_tx_buf), spis_rx_buf,
                       sizeof(spis_rx_buf));

}
void qt_spis_init() {
    bmp_api_spis_config_t config;
    config.mosi = KQB_PIN_MOSI;
    config.miso = KQB_PIN_MISO;
    config.sck = KQB_PIN_SCK;
    config.cs = KQB_PIN_CS;
    config.default_data = 0xff;
    config.over_read_data = 0xff;
    config.cs_pullup = 0;
    config.mode = 3;

    config.complete_callback = qt_spis_callback;

    BMPAPI->spis.init(&config);
    BMPAPI->spis.start(spis_tx_buf, sizeof(spis_tx_buf), spis_rx_buf, sizeof(spis_rx_buf));
}

void qt_matrix_init() {

    qt_spis_init();

    setPinOutput(KQB_PIN_CHRST);
    // Assert reset
    writePinHigh(KQB_PIN_CHRST);

    setPinOutput(KQB_PIN_CHBOOT);
    writePinLow(KQB_PIN_CHBOOT);

    setPinInputHigh(BOOTPIN);

    setPinOutput(KQB_PIN_LED0);

    // Deassrt reset
    writePinLow(KQB_PIN_CHRST);
    ch559_start = false;
}

uint32_t qt_get_device_row() { return MATRIX_ROWS_DEFAULT; }
uint32_t qt_get_device_col() { return MATRIX_COLS_DEFAULT; }
uint32_t qt_matrix_scan(matrix_row_t *matrix_raw) {
    if (spis_receive_len > 0) {
        qt_spis_receive(spis_receive_len);
    } else if (spis_receive_len != -1) {
        // restart spi if errors
        BMPAPI->spis.start(spis_tx_buf, sizeof(spis_tx_buf), spis_rx_buf,
                           sizeof(spis_rx_buf));
    }
    spis_receive_len = -1;

    if (led_on_count) {
        led_on_count--;
        writePinHigh(KQB_PIN_LED0);
    } else {
        writePinLow(KQB_PIN_LED0);
    }

    if (readPin(BOOTPIN) == 0 && reset_counter < 0) {
        reset_counter = 10;
    }

    if (ch559_update_mode) {
        return 0;
    }

    static uint32_t reset_timer = 0;
    if ((!ch559_start) && (!ch559_update_mode) &&
        timer_elapsed32(reset_timer) > 1000) {
        uart_buf_init();
        int res = send_reset_cmd();
        if (res == 0) {
            reset_timer = timer_read32();
        }
        // do not return to receive startup response
    }

    matrix_has_changed = 0;
    matrix_mouse_dest = &matrix_raw[MATRIX_MSBTN_ROW];
    matrix_has_changed |= process_packet(matrix_raw);

    // uart_flush_rx_buffer();

    return matrix_has_changed ? 1 : 0;
}
static const bmp_matrix_func_t matrix_func = {
    qt_matrix_init, qt_get_device_row, qt_get_device_col, qt_matrix_scan};

const bmp_matrix_func_t *get_matrix_func_user() { return &matrix_func; }

uint8_t matrix_scan_impl(matrix_row_t *_matrix) {
    return qt_matrix_scan(_matrix);
}

