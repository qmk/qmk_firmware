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

/* see keymaps/via/keymap.c and keymaps/via/config.h
   for matrix compression implementation details */
#ifdef COMPRESS_MATRIX
/* Maps value encoding a (row, col) index in a scan matrix
   val = ((row) << 4) + (col))
   to a 1-byte HID keycode.  There are only 142 HID keycodes of interest in the LAYOUT macro,
   so a 9x16 (144-element) array is sufficient.

Esc  F13  F14  F15  F16  F17  F18  F19  F20  F21  F22  F23  F24  F1   F2   F3
F4   F5   F6   F7   F8   F9   F10  F11  F12  Prn  Scr  Pau  VDn  VUp  Mut  Pwr
Hlp  `    1    2    3    4    5    6    7    8    9    0    -    =    JPY  Bsp
Ins  Hom  PgU  NmL  /    *    -    Stp  Agn  Tab  Q    W    E    R    T    Y
U    I    O    P    [    ]    \    Del  End  PgD  7    8    9    +    Mnu  Und
CLk  A    S    D    F    G    H    J    K    L    ;    :    #    Ent  4    5
6    KP,  Sel  Cpy  <    Z    X    C    V    B    N    M    ,    .    /    R0
Up   1    2    3    KP=  Exe  Pst  MHN  HNJ  Spc  H/E  HNK  KAN  App  Lft  Dn
LCt  LSh  LAl  LGu  Rct  RSh  Ral  RGu  Rt   0    .    Ent  Fnd  Cut
 */
static const uint8_t hidindex[144] PROGMEM = {
  /* 0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F */
  0x29, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x3A, 0x3B, 0x3C, /* 0 */
  0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x81, 0x80, 0x7F, 0x66, /* 1 */
  0x75, 0x35, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x2D, 0x2E, 0x89, 0x2A, /* 2 */
  0x49, 0x4A, 0x4B, 0x53, 0x54, 0x55, 0x56, 0x78, 0x79, 0x2B, 0x14, 0x1A, 0x08, 0x15, 0x17, 0x1C, /* 3 */
  0x18, 0x0C, 0x12, 0x13, 0x2F, 0x30, 0x31, 0x4C, 0x4D, 0x4E, 0x5F, 0x60, 0x61, 0x57, 0x76, 0x7A, /* 4 */
  0x39, 0x04, 0x16, 0x07, 0x09, 0x0A, 0x0B, 0x0D, 0x0E, 0x0F, 0x33, 0x34, 0x32, 0x28, 0x5C, 0x5D, /* 5 */
  0x5E, 0x85, 0x77, 0x7C, 0x64, 0x1D, 0x1B, 0x06, 0x19, 0x05, 0x11, 0x10, 0x36, 0x37, 0x38, 0x87, /* 6 */
  0x52, 0x59, 0x5A, 0x5B, 0x67, 0x74, 0x7D, 0x8B, 0x91, 0x2C, 0x90, 0x8A, 0x88, 0x65, 0x50, 0x51, /* 7 */
  0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0x4F, 0x62, 0x63, 0x58, 0x7E, 0x7B, 0x00, 0x00  /* 8 */
};


/* Maps 1-byte HID keycode to a value encoding a (row, col) index in a 9x16 scan matrix:
   val = ((row) << 4) + (col)) */
#define XBAD 0xFF
static const uint8_t matrixindex[256] PROGMEM = {
/*  0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F   */
  XBAD, XBAD, XBAD, XBAD, 0x51, 0x69, 0x67, 0x53, 0x3C, 0x54, 0x55, 0x56, 0x41, 0x57, 0x58, 0x59, /* 0 */
  0x6B, 0x6A, 0x42, 0x43, 0x3A, 0x3D, 0x52, 0x3E, 0x40, 0x68, 0x3B, 0x66, 0x3F, 0x65, 0x22, 0x23, /* 1 */
  0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x5D, 0x00, 0x2F, 0x39, 0x79, 0x2C, 0x2D, 0x44, /* 2 */
  0x45, 0x46, 0x5C, 0x5A, 0x5B, 0x21, 0x6C, 0x6D, 0x6E, 0x50, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, /* 3 */
  0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x30, 0x31, 0x32, 0x47, 0x48, 0x49, 0x88, /* 4 */
  0x7E, 0x7F, 0x70, 0x33, 0x34, 0x35, 0x36, 0x4D, 0x8B, 0x71, 0x72, 0x73, 0x5E, 0x5F, 0x60, 0x4A, /* 5 */
  0x4B, 0x4C, 0x89, 0x8A, 0x64, 0x7D, 0x1F, 0x74, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, /* 6 */
  0x09, 0x0A, 0x0B, 0x0C, 0x75, 0x20, 0x4E, 0x62, 0x37, 0x38, 0x4F, 0x8D, 0x63, 0x76, 0x8C, 0x1E, /* 7 */
  0x1D, 0x1C, XBAD, XBAD, XBAD, 0x61, XBAD, 0x6F, 0x7C, 0x2E, 0x7B, 0x77, XBAD, XBAD, XBAD, XBAD, /* 8 */
  0x7A, 0x78, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, /* 9 */
  XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, /* A */
  XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, /* B */
  XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, /* C */
  XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, /* D */
  0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, /* E */
  XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, XBAD, /* F */
};
#define ROW_MASK 0xF0
#define COL_MASK 0x0F
#define CODE(row, col) (pgm_read_byte(&hidindex[(((row) << 4) | (col))]))
#define ROW(code)      ((pgm_read_byte(&matrixindex[(code)]) & ROW_MASK) >> 4)
#define COL(code)      (pgm_read_byte(&matrixindex[(code)]) & COL_MASK)
#define ROW_BITS(code) (1 << COL(code))
#else // NOT COMPRESS_MATRIX
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
#define CODE(row, col) (((row) << 4) | (col))
#define ROW(code)      (((code) & ROW_MASK) >> 4)
#define COL(code)      ((code) & COL_MASK)
#define ROW_BITS(code) (1 << COL(code))
#endif // COMPRESS_MATRIX

// Integrated key state of all keyboards
static report_keyboard_t local_keyboard_report;

static bool matrix_is_mod = false;

/*
 * USB Host Shield HID keyboards
 * This supports two cascaded hubs and four keyboards
 */
USB usb_host;
HIDBoot<HID_PROTOCOL_KEYBOARD> kbd1(&usb_host);
HIDBoot<HID_PROTOCOL_KEYBOARD> kbd2(&usb_host);
HIDBoot<HID_PROTOCOL_KEYBOARD> kbd3(&usb_host);
HIDBoot<HID_PROTOCOL_KEYBOARD> kbd4(&usb_host);
KBDReportParser kbd_parser1;
KBDReportParser kbd_parser2;
KBDReportParser kbd_parser3;
KBDReportParser kbd_parser4;
USBHub hub1(&usb_host);
USBHub hub2(&usb_host);

extern "C" {
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
                led_set(host_keyboard_leds());
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

    void led_set(uint8_t usb_led) {
        if (kbd1.isReady()) kbd1.SetReport(0, 0, 2, 0, 1, &usb_led);
        if (kbd2.isReady()) kbd2.SetReport(0, 0, 2, 0, 1, &usb_led);
        if (kbd3.isReady()) kbd3.SetReport(0, 0, 2, 0, 1, &usb_led);
        if (kbd4.isReady()) kbd4.SetReport(0, 0, 2, 0, 1, &usb_led);
        led_set_kb(usb_led);
    }
}
