/*
Copyright 2011 Jun Wako <wakojun@gmail.com>

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
#include "usb_keyboard.h"
#include "usb_mouse.h"
#include "usb_extra.h"
#include "host_driver.h"
#include "pjrc.h"


/*------------------------------------------------------------------*
 * Host driver
 *------------------------------------------------------------------*/
static uint8_t keyboard_leds(void);
static void send_keyboard(report_keyboard_t *report);
static void send_mouse(report_mouse_t *report);
static void send_system(uint16_t data);
static void send_consumer(uint16_t data);

static host_driver_t driver = {
        keyboard_leds,
        send_keyboard,
        send_mouse,
        send_system,
        send_consumer
};

host_driver_t *pjrc_driver(void)
{
    return &driver;
}

static uint8_t keyboard_leds(void) {
    return usb_keyboard_leds;
}

static void send_keyboard(report_keyboard_t *report)
{
    usb_keyboard_send_report(report);
}

static void send_mouse(report_mouse_t *report)
{
#ifdef MOUSE_ENABLE
    usb_mouse_send(report->x, report->y, report->v, report->h, report->buttons);
#endif
}

static void send_system(uint16_t data)
{
#ifdef EXTRAKEY_ENABLE
    usb_extra_system_send(data);
#endif
}

static void send_consumer(uint16_t data)
{
#ifdef EXTRAKEY_ENABLE
    usb_extra_consumer_send(data);
#endif
}
