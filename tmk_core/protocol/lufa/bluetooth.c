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

#include <stdint.h>
#include "report.h"
#include "print.h"
#include "debug.h"
#include "bluetooth.h"

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

void bluefruit_serial_send(uint8_t data) { serial_send(data); }