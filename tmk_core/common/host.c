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
//#include <avr/interrupt.h>
#include "keyboard.h"
#include "keycode.h"
#include "host.h"
#include "util.h"
#include "debug.h"
#include "digitizer.h"

#ifdef NKRO_ENABLE
#    include "keycode_config.h"
extern keymap_config_t keymap_config;
#endif

static host_driver_t *driver;
static uint16_t       last_system_report   = 0;
static uint16_t       last_consumer_report = 0;

void host_set_driver(host_driver_t *d) { driver = d; }

host_driver_t *host_get_driver(void) { return driver; }

#ifdef SPLIT_KEYBOARD
uint8_t split_led_state = 0;
void    set_split_host_keyboard_leds(uint8_t led_state) { split_led_state = led_state; }
#endif

uint8_t host_keyboard_leds(void) {
#ifdef SPLIT_KEYBOARD
    if (!is_keyboard_master()) return split_led_state;
#endif
    if (!driver) return 0;
    return (*driver->keyboard_leds)();
}

led_t host_keyboard_led_state(void) { return (led_t)host_keyboard_leds(); }

/* send report */
void host_keyboard_send(report_keyboard_t *report) {
    if (!driver) return;
#if defined(NKRO_ENABLE) && defined(NKRO_SHARED_EP)
    if (keyboard_protocol && keymap_config.nkro) {
        /* The callers of this function assume that report->mods is where mods go in.
         * But report->nkro.mods can be at a different offset if core keyboard does not have a report ID.
         */
        report->nkro.mods      = report->mods;
        report->nkro.report_id = REPORT_ID_NKRO;
    } else
#endif
    {
#ifdef KEYBOARD_SHARED_EP
        report->report_id = REPORT_ID_KEYBOARD;
#endif
    }
    (*driver->send_keyboard)(report);

    if (debug_keyboard) {
        dprint("keyboard_report: ");
        for (uint8_t i = 0; i < KEYBOARD_REPORT_SIZE; i++) {
            dprintf("%02X ", report->raw[i]);
        }
        dprint("\n");
    }
}

void host_mouse_send(report_mouse_t *report) {
    if (!driver) return;
#ifdef MOUSE_SHARED_EP
    report->report_id = REPORT_ID_MOUSE;
#endif
    (*driver->send_mouse)(report);
}

void host_system_send(uint16_t report) {
    if (report == last_system_report) return;
    last_system_report = report;

    if (!driver) return;
    (*driver->send_system)(report);
}

void host_consumer_send(uint16_t report) {
    if (report == last_consumer_report) return;
    last_consumer_report = report;

    if (!driver) return;
    (*driver->send_consumer)(report);
}

void host_digitizer_send(digitizer_t *digitizer) {
    if (!driver) return;

    report_digitizer_t report = {
#ifdef DIGITIZER_SHARED_EP
        .report_id = REPORT_ID_DIGITIZER,
#endif
        .tip     = digitizer->tipswitch & 0x1,
        .inrange = digitizer->inrange & 0x1,
        .x       = (uint16_t)(digitizer->x * 0x7FFF),
        .y       = (uint16_t)(digitizer->y * 0x7FFF),
    };

    send_digitizer(&report);
}

__attribute__((weak)) void send_digitizer(report_digitizer_t *report) {}

uint16_t host_last_system_report(void) { return last_system_report; }

uint16_t host_last_consumer_report(void) { return last_consumer_report; }
