/*
Copyright 2016 Jun Wako <wakojun@gmail.com>

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

#include <stdint.h>
#include <stdbool.h>

// USB HID host
#include "Usb.h"
#include "usbhub.h"
#include "hid.h"
#include "hidboot.h"
#include "parser.h"

#include "keycode.h"
#include "util.h"
#include "print.h"
#include "debug.h"
#include "timer.h"
#include "matrix.h"
#include "led.h"
#include "host.h"
#include "keyboard.h"

extern "C" {
#include "quantum.h"
}

/* KEY CODE to Matrix
 *
 * HID keycode(1 byte):
 * Higher 5 bits indicates ROW and lower 3 bits COL.
 *
 *  7 6 5 4 3 2 1 0
 * +---------------+
 * |  ROW  |  COL  |
 * +---------------+
 *
 * Matrix space(16 * 16):
 *   r\c0123456789ABCDEF
 *   0 +----------------+
 *   : |                |
 *   : |                |
 *  16 +----------------+
 */
#define ROW_MASK 0xF0
#define COL_MASK 0x0F
#define CODE(row, col)  (((row) << 4) | (col))
#define ROW(code)       (((code) & ROW_MASK) >> 4)
#define COL(code)       ((code) & COL_MASK)
#define ROW_BITS(code)  (1 << COL(code))


// Integrated key state of all keyboards
static report_keyboard_t local_keyboard_report;

static bool matrix_is_mod = false;

/*
 * USB Host Shield HID keyboards
 * This supports two cascaded hubs and four keyboards
 */
USB usb_host;
HIDBoot<HID_PROTOCOL_KEYBOARD>    kbd1(&usb_host);
HIDBoot<HID_PROTOCOL_KEYBOARD>    kbd2(&usb_host);
HIDBoot<HID_PROTOCOL_KEYBOARD>    kbd3(&usb_host);
HIDBoot<HID_PROTOCOL_KEYBOARD>    kbd4(&usb_host);
KBDReportParser kbd_parser1;
KBDReportParser kbd_parser2;
KBDReportParser kbd_parser3;
KBDReportParser kbd_parser4;
USBHub hub1(&usb_host);
USBHub hub2(&usb_host);


extern "C"
{
    uint8_t matrix_rows(void) { return MATRIX_ROWS; }
    uint8_t matrix_cols(void) { return MATRIX_COLS; }
    bool matrix_has_ghost(void) { return false; }
    void matrix_init(void) {
        // USB Host Shield setup
        usb_host.Init();
        kbd1.SetReportParser(0, (HIDReportParser*)&kbd_parser1);
        kbd2.SetReportParser(0, (HIDReportParser*)&kbd_parser2);
        kbd3.SetReportParser(0, (HIDReportParser*)&kbd_parser3);
        kbd4.SetReportParser(0, (HIDReportParser*)&kbd_parser4);
        matrix_init_quantum();
    }

    static void or_report(report_keyboard_t report) {
        // integrate reports into local_keyboard_report
        local_keyboard_report.mods |= report.mods;
        for (uint8_t i = 0; i < KEYBOARD_REPORT_KEYS; i++) {
            if (IS_ANY(report.keys[i])) {
                for (uint8_t j = 0; j < KEYBOARD_REPORT_KEYS; j++) {
                    if (! local_keyboard_report.keys[j]) {
                        local_keyboard_report.keys[j] = report.keys[i];
                        break;
                    }
                }
            }
        }
    }

    __attribute__ ((weak))
    void matrix_init_kb(void) {
        matrix_init_user();
    }

    __attribute__ ((weak))
    void matrix_init_user(void) {
    }

    __attribute__ ((weak))
    void matrix_scan_kb(void) {
        matrix_scan_user();
    }

    __attribute__ ((weak))
    void matrix_scan_user(void) {
    }

    uint8_t matrix_scan(void) {
        static uint16_t last_time_stamp1 = 0;
        static uint16_t last_time_stamp2 = 0;
        static uint16_t last_time_stamp3 = 0;
        static uint16_t last_time_stamp4 = 0;

        // check report came from keyboards
        if (kbd_parser1.time_stamp != last_time_stamp1 ||
            kbd_parser2.time_stamp != last_time_stamp2 ||
            kbd_parser3.time_stamp != last_time_stamp3 ||
            kbd_parser4.time_stamp != last_time_stamp4) {

            last_time_stamp1 = kbd_parser1.time_stamp;
            last_time_stamp2 = kbd_parser2.time_stamp;
            last_time_stamp3 = kbd_parser3.time_stamp;
            last_time_stamp4 = kbd_parser4.time_stamp;

            // clear and integrate all reports
            local_keyboard_report = {};
            or_report(kbd_parser1.report);
            or_report(kbd_parser2.report);
            or_report(kbd_parser3.report);
            or_report(kbd_parser4.report);

            matrix_is_mod = true;

            dprintf("state:  %02X %02X", local_keyboard_report.mods, local_keyboard_report.reserved);
            for (uint8_t i = 0; i < KEYBOARD_REPORT_KEYS; i++) {
                dprintf(" %02X", local_keyboard_report.keys[i]);
            }
            dprint("\r\n");
        } else {
            matrix_is_mod = false;
        }

        uint16_t timer;
        timer = timer_read();
        usb_host.Task();
        timer = timer_elapsed(timer);
        if (timer > 100) {
            dprintf("host.Task: %d\n", timer);
        }

        static uint8_t usb_state = 0;
        if (usb_state != usb_host.getUsbTaskState()) {
            usb_state = usb_host.getUsbTaskState();
            dprintf("usb_state: %02X\n", usb_state);

            // restore LED state when keyboard comes up
            if (usb_state == USB_STATE_RUNNING) {
                dprintf("speed: %s\n", usb_host.getVbusState()==FSHOST ? "full" : "low");
                keyboard_set_leds(host_keyboard_leds());
            }
        }
        matrix_scan_quantum();
        return 1;
    }

    bool matrix_is_on(uint8_t row, uint8_t col) {
        uint8_t code = CODE(row, col);

        if (IS_MOD(code)) {
            if (local_keyboard_report.mods & ROW_BITS(code)) {
                return true;
            }
        }
        for (uint8_t i = 0; i < KEYBOARD_REPORT_KEYS; i++) {
            if (local_keyboard_report.keys[i] == code) {
                return true;
            }
        }
        return false;
    }

    matrix_row_t matrix_get_row(uint8_t row) {
        uint16_t row_bits = 0;

        if (IS_MOD(CODE(row, 0)) && local_keyboard_report.mods) {
            row_bits |= local_keyboard_report.mods;
        }

        for (uint8_t i = 0; i < KEYBOARD_REPORT_KEYS; i++) {
            if (IS_ANY(local_keyboard_report.keys[i])) {
                if (row == ROW(local_keyboard_report.keys[i])) {
                    row_bits |= ROW_BITS(local_keyboard_report.keys[i]);
                }
            }
        }
        return row_bits;
    }

    uint8_t matrix_key_count(void) {
        uint8_t count = 0;

        count += bitpop(local_keyboard_report.mods);
        for (uint8_t i = 0; i < KEYBOARD_REPORT_KEYS; i++) {
            if (IS_ANY(local_keyboard_report.keys[i])) {
                count++;
            }
        }
        return count;
    }

    void matrix_print(void) {
        print("\nr/c 0123456789ABCDEF\n");
        for (uint8_t row = 0; row < matrix_rows(); row++) {
            xprintf("%02d: ", row);
            print_bin_reverse16(matrix_get_row(row));
            print("\n");
        }
    }

    void led_set(uint8_t usb_led)
    {
        if (kbd1.isReady()) kbd1.SetReport(0, 0, 2, 0, 1, &usb_led);
        if (kbd2.isReady()) kbd2.SetReport(0, 0, 2, 0, 1, &usb_led);
        if (kbd3.isReady()) kbd3.SetReport(0, 0, 2, 0, 1, &usb_led);
        if (kbd4.isReady()) kbd4.SetReport(0, 0, 2, 0, 1, &usb_led);
        led_set_kb(usb_led);
    }

};
