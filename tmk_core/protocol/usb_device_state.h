/*
 * Copyright 2021 Andrei Purdea <andrei@purdea.ro>
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

#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    USB_DEVICE_STATE_NO_INIT    = 0, // We're in this state before calling usb_device_state_init()
    USB_DEVICE_STATE_INIT       = 1, // Can consume up to 100mA
    USB_DEVICE_STATE_CONFIGURED = 2, // Can consume up to what is specified in configuration descriptor, typically 500mA
    USB_DEVICE_STATE_SUSPEND    = 3  // Can consume only suspend current
} usb_configure_state_t;

typedef enum {
    USB_PROTOCOL_BOOT   = 0,
    USB_PROTOCOL_REPORT = 1,
} usb_hid_protocol_t;

// note: we can't typedef this struct to usb_device_state_t because it would
// conflict with the previous definition in:
// lib/chibios-contrib/ext/nxp-middleware-usb/device/usb_device.h
struct usb_device_state {
    uint8_t               idle_rate;
    uint8_t               leds;
    usb_hid_protocol_t    protocol;
    usb_configure_state_t configure_state;
};

void                  usb_device_state_set_configuration(bool is_configured, uint8_t configuration_number);
void                  usb_device_state_set_suspend(bool is_configured, uint8_t configuration_number);
void                  usb_device_state_set_resume(bool is_configured, uint8_t configuration_number);
void                  usb_device_state_set_reset(void);
void                  usb_device_state_init(void);
usb_configure_state_t usb_device_state_get_configure_state(void);
void                  usb_device_state_set_protocol(usb_hid_protocol_t protocol);
usb_hid_protocol_t    usb_device_state_get_protocol(void);
void                  usb_device_state_set_leds(uint8_t leds);
uint8_t               usb_device_state_get_leds(void);
void                  usb_device_state_set_idle_rate(uint8_t idle_rate);
uint8_t               usb_device_state_get_idle_rate(void);
void                  usb_device_state_reset_hid_state(void);

void notify_usb_device_state_change_kb(struct usb_device_state usb_device_state);
void notify_usb_device_state_change_user(struct usb_device_state usb_device_state);
