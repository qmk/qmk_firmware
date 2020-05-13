/*
Bluefruit Protocol for TMK firmware
Author: Benjamin Gould, 2013
        Jack Humbert, 2015
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

#include <stdbool.h>
#include "host_driver.h"
#include "bluetooth.h"
#include "../serial.h"

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

#define CONSUMER2RN42(usage) (usage == AUDIO_MUTE ? 0x0040 : (usage == AUDIO_VOL_UP ? 0x0010 : (usage == AUDIO_VOL_DOWN ? 0x0020 : (usage == TRANSPORT_NEXT_TRACK ? 0x0100 : (usage == TRANSPORT_PREV_TRACK ? 0x0200 : (usage == TRANSPORT_STOP ? 0x0400 : (usage == TRANSPORT_STOP_EJECT ? 0x0800 : (usage == TRANSPORT_PLAY_PAUSE ? 0x0080 : (usage == AL_EMAIL ? 0x0200 : (usage == AL_LOCAL_BROWSER ? 0x8000 : (usage == AC_SEARCH ? 0x0400 : (usage == AC_HOME ? 0x0100 : 0))))))))))))

static struct { bool initialized; } state;

void bluetooth_task() {
    if (!state.initialized) {
        serial_init();
        state.initialized = true;
    }
}

void bluetooth_send_keyboard(report_keyboard_t *report) {
#ifdef MODULE_RN42
    serial_send(0xFD);
    serial_send(0x09);
    serial_send(0x01);
    serial_send(report->mods);
    serial_send(report->reserved);
    for (uint8_t i = 0; i < KEYBOARD_REPORT_KEYS; i++) {
        serial_send(report->keys[i]);
    }
#else
    serial_send(0xFD);
    serial_send(report->mods);
    serial_send(report->reserved);
    for (uint8_t i = 0; i < KEYBOARD_REPORT_KEYS; i++) {
        serial_send(report->keys[i]);
    }
#endif
}

void bluetooth_send_consumer(uint16_t data) {
#ifdef MODULE_RN42
    static uint16_t last_data = 0;
    if (data == last_data) return;
    last_data       = data;
    uint16_t bitmap = CONSUMER2RN42(data);
    serial_send(0xFD);
    serial_send(0x03);
    serial_send(0x03);
    serial_send(bitmap & 0xFF);
    serial_send((bitmap >> 8) & 0xFF);
#else
    static uint16_t last_data = 0;
    if (data == last_data) return;
    last_data       = data;
    uint16_t bitmap = CONSUMER2BLUEFRUIT(data);
    serial_send(0xFD);
    serial_send(0x00);
    serial_send(0x02);
    serial_send((bitmap >> 8) & 0xFF);
    serial_send(bitmap & 0xFF);
    serial_send(0x00);
    serial_send(0x00);
    serial_send(0x00);
    serial_send(0x00);
#endif
}

#ifdef MOUSE_ENABLE
void bluetooth_send_mouse(report_mouse_t *report) {
    serial_send(0xFD);
    serial_send(0x00);
    serial_send(0x03);
    serial_send(report->buttons);
    serial_send(report->x);
    serial_send(report->y);
    serial_send(report->v);  // should try sending the wheel v here
    serial_send(report->h);  // should try sending the wheel h here
    serial_send(0x00);
}
#endif
