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

#pragma once

#include "../serial.h"

void bluefruit_serial_send(uint8_t data);

// https://learn.adafruit.com/introducing-bluefruit-ez-key-diy-bluetooth-hid-keyboard/sending-keys-via-serial#raw-hid-consumer-reports-8-14
static inline uint16_t CONSUMER2BLUEFRUIT(uint16_t usage) {
    switch (usage) {
        case AC_HOME:
            return 0x0001;
        case AL_KEYBOARD_LAYOUT:
            return 0x0002;
        case AC_SEARCH:
            return 0x0004;
        case SNAPSHOT:
            return 0x0008;
        case AUDIO_VOL_UP:
            return 0x0010;
        case AUDIO_VOL_DOWN:
            return 0x0020;
        case TRANSPORT_PLAY_PAUSE:
            return 0x0040;
        case TRANSPORT_FAST_FORWARD:
            return 0x0080;
        case TRANSPORT_REWIND:
            return 0x0100;
        case TRANSPORT_NEXT_TRACK:
            return 0x0200;
        case TRANSPORT_PREV_TRACK:
            return 0x0400;
        case TRANSPORT_RANDOM_PLAY:
            return 0x0800;
        case TRANSPORT_STOP:
            return 0x1000;
        default:
            return 0;
    }
}

// https://cdn.sparkfun.com/datasheets/Wireless/Bluetooth/bluetooth_cr_UG-v1.0r.pdf#G7.663734
static inline uint16_t CONSUMER2RN42(uint16_t usage) {
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
