/*
Bluefruit Protocol for TMK firmware
Author: Benjamin Gould, 2013
Based on code Copyright 2011 Jun Wako <wakojun@gmail.com>
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
#include "host.h"
#include "report.h"
#include "print.h"
#include "debug.h"
#include "host_driver.h"
#include "serial.h"
#include "bluefruit.h"

#define BLUEFRUIT_TRACE_SERIAL 1

static uint8_t bluefruit_keyboard_leds = 0;

static void bluefruit_serial_send(uint8_t);

void bluefruit_keyboard_print_report(report_keyboard_t *report) {
    if (!debug_keyboard) return;
    dprintf("keys: ");
    for (int i = 0; i < KEYBOARD_REPORT_KEYS; i++) {
        debug_hex8(report->keys[i]);
        dprintf(" ");
    }
    dprintf(" mods: ");
    debug_hex8(report->mods);
    dprintf(" reserved: ");
    debug_hex8(report->reserved);
    dprintf("\n");
}

#ifdef BLUEFRUIT_TRACE_SERIAL
static void bluefruit_trace_header() {
    dprintf("+------------------------------------+\n");
    dprintf("| HID report to Bluefruit via serial |\n");
    dprintf("+------------------------------------+\n|");
}

static void bluefruit_trace_footer() { dprintf("|\n+------------------------------------+\n\n"); }
#endif

static void bluefruit_serial_send(uint8_t data) {
#ifdef BLUEFRUIT_TRACE_SERIAL
    dprintf(" ");
    debug_hex8(data);
    dprintf(" ");
#endif
    serial_send(data);
}

/*------------------------------------------------------------------*
 * Host driver
 *------------------------------------------------------------------*/

static uint8_t keyboard_leds(void);
static void    send_keyboard(report_keyboard_t *report);
static void    send_mouse(report_mouse_t *report);
static void    send_system(uint16_t data);
static void    send_consumer(uint16_t data);

void sendString(char string[], int length) {
    for (int i = 0; i < length; i++) {
        serial_send(string[i]);
    }
}

static host_driver_t driver = {keyboard_leds, send_keyboard, send_mouse, send_system, send_consumer};

host_driver_t *bluefruit_driver(void) { return &driver; }

static uint8_t keyboard_leds(void) { return bluefruit_keyboard_leds; }

static void send_keyboard(report_keyboard_t *report) {
#ifdef BLUEFRUIT_TRACE_SERIAL
    bluefruit_trace_header();
#endif
    bluefruit_serial_send(0xFD);
    for (uint8_t i = 0; i < KEYBOARD_REPORT_SIZE; i++) {
        bluefruit_serial_send(report->raw[i]);
    }
#ifdef BLUEFRUIT_TRACE_SERIAL
    bluefruit_trace_footer();
#endif
}

static void send_mouse(report_mouse_t *report) {
#ifdef BLUEFRUIT_TRACE_SERIAL
    bluefruit_trace_header();
#endif
    bluefruit_serial_send(0xFD);
    bluefruit_serial_send(0x00);
    bluefruit_serial_send(0x03);
    bluefruit_serial_send(report->buttons);
    bluefruit_serial_send(report->x);
    bluefruit_serial_send(report->y);
    bluefruit_serial_send(report->v);  // should try sending the wheel v here
    bluefruit_serial_send(report->h);  // should try sending the wheel h here
    bluefruit_serial_send(0x00);
#ifdef BLUEFRUIT_TRACE_SERIAL
    bluefruit_trace_footer();
#endif
}

static void send_system(uint16_t data) {}

/*
+-----------------+-------------------+-------+
| Consumer Key    | Bit Map           | Hex   |
+-----------------+-------------------+-------+
| Home            | 00000001 00000000 | 01 00 |
| KeyboardLayout  | 00000010 00000000 | 02 00 |
| Search          | 00000100 00000000 | 04 00 |
| Snapshot        | 00001000 00000000 | 08 00 |
| VolumeUp        | 00010000 00000000 | 10 00 |
| VolumeDown      | 00100000 00000000 | 20 00 |
| Play/Pause      | 01000000 00000000 | 40 00 |
| Fast Forward    | 10000000 00000000 | 80 00 |
| Rewind          | 00000000 00000001 | 00 01 |
| Scan Next Track | 00000000 00000010 | 00 02 |
| Scan Prev Track | 00000000 00000100 | 00 04 |
| Random Play     | 00000000 00001000 | 00 08 |
| Stop            | 00000000 00010000 | 00 10 |
+-------------------------------------+-------+
*/
#define CONSUMER2BLUEFRUIT(usage) (usage == AUDIO_MUTE ? 0x0000 : (usage == AUDIO_VOL_UP ? 0x1000 : (usage == AUDIO_VOL_DOWN ? 0x2000 : (usage == TRANSPORT_NEXT_TRACK ? 0x0002 : (usage == TRANSPORT_PREV_TRACK ? 0x0004 : (usage == TRANSPORT_STOP ? 0x0010 : (usage == TRANSPORT_STOP_EJECT ? 0x0000 : (usage == TRANSPORT_PLAY_PAUSE ? 0x4000 : (usage == AL_CC_CONFIG ? 0x0000 : (usage == AL_EMAIL ? 0x0000 : (usage == AL_CALCULATOR ? 0x0000 : (usage == AL_LOCAL_BROWSER ? 0x0000 : (usage == AC_SEARCH ? 0x0400 : (usage == AC_HOME ? 0x0100 : (usage == AC_BACK ? 0x0000 : (usage == AC_FORWARD ? 0x0000 : (usage == AC_STOP ? 0x0000 : (usage == AC_REFRESH ? 0x0000 : (usage == AC_BOOKMARKS ? 0x0000 : 0)))))))))))))))))))

static void send_consumer(uint16_t data) {
    static uint16_t last_data = 0;
    if (data == last_data) return;
    last_data = data;

    uint16_t bitmap = CONSUMER2BLUEFRUIT(data);

#ifdef BLUEFRUIT_TRACE_SERIAL
    dprintf("\nData: ");
    debug_hex16(data);
    dprintf("; bitmap: ");
    debug_hex16(bitmap);
    dprintf("\n");
    bluefruit_trace_header();
#endif
    bluefruit_serial_send(0xFD);
    bluefruit_serial_send(0x00);
    bluefruit_serial_send(0x02);
    bluefruit_serial_send((bitmap >> 8) & 0xFF);
    bluefruit_serial_send(bitmap & 0xFF);
    bluefruit_serial_send(0x00);
    bluefruit_serial_send(0x00);
    bluefruit_serial_send(0x00);
    bluefruit_serial_send(0x00);
#ifdef BLUEFRUIT_TRACE_SERIAL
    bluefruit_trace_footer();
#endif
}