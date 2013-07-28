/*
Copyright 2011,2012 Jun Wako <wakojun@gmail.com>

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
#include <avr/interrupt.h>
#include "keycode.h"
#include "host.h"
#include "util.h"
#include "debug.h"


#ifdef NKRO_ENABLE
bool keyboard_nkro = false;
#endif

report_keyboard_t *keyboard_report = &(report_keyboard_t){};
report_mouse_t mouse_report = {};


static host_driver_t *driver;
static uint16_t last_system_report = 0;
static uint16_t last_consumer_report = 0;

static inline void add_key_byte(uint8_t code);
static inline void del_key_byte(uint8_t code);
#ifdef NKRO_ENABLE
static inline void add_key_bit(uint8_t code);
static inline void del_key_bit(uint8_t code);
#endif


void host_set_driver(host_driver_t *d)
{
    driver = d;
}

host_driver_t *host_get_driver(void)
{
    return driver;
}

uint8_t host_keyboard_leds(void)
{
    if (!driver) return 0;
    return (*driver->keyboard_leds)();
}
/* send report */
void host_keyboard_send(report_keyboard_t *report)
{
    if (!driver) return;
    (*driver->send_keyboard)(report);

    if (debug_keyboard) {
        dprint("keyboard_report: ");
        for (uint8_t i = 0; i < REPORT_SIZE; i++) {
            dprintf("%02X ", keyboard_report->raw[i]);
        }
        dprint("\n");
    }
}

void host_mouse_send(report_mouse_t *report)
{
    if (!driver) return;
    (*driver->send_mouse)(report);
}

void host_system_send(uint16_t report)
{
    if (report == last_system_report) return;
    last_system_report = report;

    if (!driver) return;
    (*driver->send_system)(report);
}

void host_consumer_send(uint16_t report)
{
    if (report == last_consumer_report) return;
    last_consumer_report = report;

    if (!driver) return;
    (*driver->send_consumer)(report);
}



/* keyboard report utils */
void host_add_key(uint8_t key)
{
#ifdef NKRO_ENABLE
    if (keyboard_nkro) {
        add_key_bit(key);
        return;
    }
#endif
    add_key_byte(key);
}

void host_del_key(uint8_t key)
{
#ifdef NKRO_ENABLE
    if (keyboard_nkro) {
        del_key_bit(key);
        return;
    }
#endif
    del_key_byte(key);
}

void host_clear_keys(void)
{
    // not clea  mods
    for (int8_t i = 1; i < REPORT_SIZE; i++) {
        keyboard_report->raw[i] = 0;
    }
}

uint8_t host_get_mods(void)
{
    return keyboard_report->mods;
}

void host_add_mods(uint8_t mods)
{
    keyboard_report->mods |= mods;
}

void host_del_mods(uint8_t mods)
{
    keyboard_report->mods &= ~mods;
}

void host_set_mods(uint8_t mods)
{
    keyboard_report->mods = mods;
}

void host_clear_mods(void)
{
    keyboard_report->mods = 0;
}

uint8_t host_has_anykey(void)
{
    uint8_t cnt = 0;
    for (uint8_t i = 1; i < REPORT_SIZE; i++) {
        if (keyboard_report->raw[i])
            cnt++;
    }
    return cnt;
}

uint8_t host_has_anymod(void)
{
    return bitpop(keyboard_report->mods);
}

uint8_t host_get_first_key(void)
{
#ifdef NKRO_ENABLE
    if (keyboard_nkro) {
        uint8_t i = 0;
        for (; i < REPORT_BITS && !keyboard_report->nkro.bits[i]; i++)
            ;
        return i<<3 | biton(keyboard_report->nkro.bits[i]);
    }
#endif
    return keyboard_report->keys[0];
}

void host_send_keyboard_report(void)
{
    if (!driver) return;
    host_keyboard_send(keyboard_report);
}

uint8_t host_mouse_in_use(void)
{
    return (mouse_report.buttons | mouse_report.x | mouse_report.y | mouse_report.v | mouse_report.h);
}

uint16_t host_last_sysytem_report(void)
{
    return last_system_report;
}

uint16_t host_last_consumer_report(void)
{
    return last_consumer_report;
}

static inline void add_key_byte(uint8_t code)
{
    int8_t i = 0;
    int8_t empty = -1;
    for (; i < REPORT_KEYS; i++) {
        if (keyboard_report->keys[i] == code) {
            break;
        }
        if (empty == -1 && keyboard_report->keys[i] == 0) {
            empty = i;
        }
    }
    if (i == REPORT_KEYS) {
        if (empty != -1) {
            keyboard_report->keys[empty] = code;
        }
    }
}

static inline void del_key_byte(uint8_t code)
{
    for (uint8_t i = 0; i < REPORT_KEYS; i++) {
        if (keyboard_report->keys[i] == code) {
            keyboard_report->keys[i] = 0;
        }
    }
}

#ifdef NKRO_ENABLE
static inline void add_key_bit(uint8_t code)
{
    if ((code>>3) < REPORT_BITS) {
        keyboard_report->nkro.bits[code>>3] |= 1<<(code&7);
    } else {
        dprintf("add_key_bit: can't add: %02X\n", code);
    }
}

static inline void del_key_bit(uint8_t code)
{
    if ((code>>3) < REPORT_BITS) {
        keyboard_report->nkro.bits[code>>3] &= ~(1<<(code&7));
    } else {
        dprintf("del_key_bit: can't del: %02X\n", code);
    }
}
#endif
