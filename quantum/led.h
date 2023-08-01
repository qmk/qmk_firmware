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

#pragma once

#include <stdint.h>
#include <stdbool.h>

/* FIXME: Add doxygen comments here. */

/* keyboard LEDs */
#define USB_LED_NUM_LOCK 0
#define USB_LED_CAPS_LOCK 1
#define USB_LED_SCROLL_LOCK 2
#define USB_LED_COMPOSE 3
#define USB_LED_KANA 4

#ifdef __cplusplus
extern "C" {
#endif

typedef union {
    uint8_t raw;
    struct {
        bool    num_lock : 1;
        bool    caps_lock : 1;
        bool    scroll_lock : 1;
        bool    compose : 1;
        bool    kana : 1;
        uint8_t reserved : 3;
    };
} led_t;

void led_set(uint8_t usb_led);

void led_init_ports(void);

void led_suspend(void);

void led_wakeup(void);

void led_task(void);

/* Deprecated callbacks */
void led_set_user(uint8_t usb_led);

/* Callbacks */
bool led_update_user(led_t led_state);
bool led_update_kb(led_t led_state);
void led_update_ports(led_t led_state);

uint32_t last_led_activity_time(void);    // Timestamp of the LED activity
uint32_t last_led_activity_elapsed(void); // Number of milliseconds since the last LED activity

#ifdef __cplusplus
}
#endif
