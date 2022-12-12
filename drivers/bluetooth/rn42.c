/* Copyright 2021
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

#include "rn42.h"

#include "report.h"
#include "uart.h"

#ifndef RN42_BAUD_RATE
#    define RN42_BAUD_RATE 115200
#endif

// https://cdn.sparkfun.com/datasheets/Wireless/Bluetooth/bluetooth_cr_UG-v1.0r.pdf#G7.663734
static inline uint16_t rn42_consumer_usage_to_bitmap(uint16_t usage) {
    switch (usage) {
        case AC_HOME:
            return 0x0001;
        case AL_EMAIL:
            return 0x0002;
        case AC_SEARCH:
            return 0x0004;
        case AL_KEYBOARD_LAYOUT:
            return 0x0008;
        case AUDIO_VOL_UP:
            return 0x0010;
        case AUDIO_VOL_DOWN:
            return 0x0020;
        case AUDIO_MUTE:
            return 0x0040;
        case TRANSPORT_PLAY_PAUSE:
            return 0x0080;
        case TRANSPORT_NEXT_TRACK:
            return 0x0100;
        case TRANSPORT_PREV_TRACK:
            return 0x0200;
        case TRANSPORT_STOP:
            return 0x0400;
        case TRANSPORT_EJECT:
            return 0x0800;
        case TRANSPORT_FAST_FORWARD:
            return 0x1000;
        case TRANSPORT_REWIND:
            return 0x2000;
        case TRANSPORT_STOP_EJECT:
            return 0x4000;
        case AL_LOCAL_BROWSER:
            return 0x8000;
        default:
            return 0;
    }
}

void rn42_init(void) {
    uart_init(RN42_BAUD_RATE);
}

void rn42_send_keyboard(report_keyboard_t *report) {
    uart_write(0xFD);
    uart_write(0x09);
    uart_write(0x01);

    uart_write(report->mods);
    uart_write(0x00);
    uart_write(report->keys[0]);
    uart_write(report->keys[1]);
    uart_write(report->keys[2]);
    uart_write(report->keys[3]);
    uart_write(report->keys[4]);
    uart_write(report->keys[5]);
}

void rn42_send_mouse(report_mouse_t *report) {
    uart_write(0xFD);
    uart_write(0x05);
    uart_write(0x02);

    uart_write(report->buttons);
    uart_write(report->x);
    uart_write(report->y);
    uart_write(report->v);
}

void rn42_send_consumer(uint16_t usage) {
    uint16_t bitmap = rn42_consumer_usage_to_bitmap(usage);

    uart_write(0xFD);
    uart_write(0x03);
    uart_write(0x03);

    uart_write(bitmap & 0xFF);
    uart_write(bitmap >> 8);
}
